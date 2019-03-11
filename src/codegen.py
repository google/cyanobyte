# Copyright (C) 2019 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
import getopt, os, sys
from yaml import load, dump
try:
    from yaml import CLoader as Loader, CDumper as Dumper
except ImportError:
    from yaml import Loader, Dumper
from jinja2 import Template

VERSION = '0.0.1'

def gen(argv):
    inputFiles = []
    templateFiles = []
    outputDir = ''
    debug = False
    try:
        opts, args = getopt.getopt(
            argv,
            "t:o:i:d",
        )
    except getopt.GetoptError:
        print('Error parsing CLI')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-t':
            templateFiles.append(arg)
        elif opt == '-o':
            outputDir = arg
        elif opt == '-i':
            inputFiles.append(arg)
        elif opt == '-d':
            debug = True
    
    if debug:
        print("Generating " + str(len(inputFiles)) + " file(s)")
    for templateFile in templateFiles:
        # Open template
        templateContents = open(templateFile, "r")
        templateObject = Template(templateContents.read())
        _, templateExtension = os.path.splitext(templateFile)
        # Create output dir
        if not os.path.exists(outputDir):
            os.makedirs(outputDir)

        for peripheral in inputFiles:
            # Open peripheral file
            peripheralFile = open(peripheral, "r")
            peripheralData = load(peripheralFile, Loader=Loader)
            peripheralData['version'] = VERSION
            peripheralData['fileName'] = peripheral
            if debug:
                print(peripheralData)
            # Render file
            peripheralGen = templateObject.render(peripheralData)
            # Get file path
            # Take into consideration the package
            if debug:
                print(peripheralData['name'])
            outputFilePath = outputDir + "/" + peripheralData['package'].replace('.', '/')
            if not os.path.exists(outputFilePath):
                os.makedirs(outputFilePath)

            peripheralOutputPath = outputFilePath + "/" + peripheralData['name'] + templateExtension
            peripheralOutputFile = open(peripheralOutputPath, "x")
            peripheralOutputFile.write(peripheralGen)
            print("Wrote " + peripheralOutputPath)

if __name__ == "__main__":
    gen(sys.argv[1:])
