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
import click
from yaml import load, dump
try:
    from yaml import CLoader as Loader, CDumper as Dumper
except ImportError:
    from yaml import Loader, Dumper
from jinja2 import Template

_VERSION = '0.1.0'
_DEBUG = False

def generateSourceFile(template, peripheral, templateExtension, outputDir):
  """
  Generates a source file for a provided Jinja2 template.
  """
  # Open peripheral file
  with open(peripheral, 'r') as peripheralFile:
    peripheralData = load(peripheralFile, Loader=Loader)
    # Add additional metadata to the spec data
    peripheralData['version'] = _VERSION
    peripheralData['fileName'] = peripheral

    if _DEBUG:
      print(peripheralData)
    
    # Render file
    peripheralGen = template.render(peripheralData)
    # Get file path
    # Take into consideration the package
    if _DEBUG:
      print(peripheralData['info']['title'])
    outputFilePath = outputDir + '/' + peripheralData['info']['package'].replace('.', '/')
    if not os.path.exists(outputFilePath):
      try:
        os.makedirs(outputFilePath)
      except:
        print('Could not make file directory', outputFilePath)
        sys.exit(1)

    peripheralOutputPath = outputFilePath + '/' + peripheralData['info']['title'] + templateExtension
    with open(peripheralOutputPath, 'x') as peripheralOutputFile:
      peripheralOutputFile.write(peripheralGen)

def generateSourceFilesForTemplate(templateFile, inputFiles, outputDir):
  """
  Generates a series of source files for a provided template file.
  """
  # Open template
  with open(templateFile, 'r') as templateContents:
    templateObject = Template(
      templateContents.read(),
      trim_blocks=True,
      lstrip_blocks=True
    )
    _, templateExtension = os.path.splitext(templateFile)
    
    # Create output dir
    if not os.path.exists(outputDir):
      try:
        os.makedirs(outputDir)
      except:
        print('Could not make output directory', outputDir)
        sys.exit(1)

    for peripheral in inputFiles:
      generateSourceFile(templateObject, peripheral, templateExtension, outputDir)

@click.command()
@click.option('-i', '--input', 'inputFiles', multiple=True)
@click.option('-t', '--template', 'templateFiles', multiple=True)
@click.option('-o', '--output', 'outputDir', default='./build', show_default=True)
@click.option('-d', '--debug', 'debug', default=False)
def gen(inputFiles, templateFiles, outputDir, debug):
  """
  Takes command line arguments and generates source files for every peripheral
  to each template file.
  """
  global _DEBUG
  _DEBUG = debug
    
  if _DEBUG:
    print("Generating " + str(len(inputFiles)) + " file(s)")
  for templateFile in templateFiles:
    generateSourceFilesForTemplate(templateFile, inputFiles, outputDir)

if __name__ == "__main__":
    gen(sys.argv[1:])
