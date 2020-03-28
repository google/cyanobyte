#!/usr/bin/env python3
#
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

import unittest
import os

class TestCodegen(unittest.TestCase):
    def generatePeripheral(self, template):
        os.system('python3 src/codegen.py \
            -c \
            -o ./tmp/ \
            -t templates/' + template + '\
            -i peripherals/ADS1015.yaml \
            -i peripherals/BMP280.yaml \
            -i peripherals/LSM303D.yaml \
            -i peripherals/MCP4725.yaml \
            -i peripherals/MCP9808.yaml \
            -i peripherals/TCS3472.yaml \
            -i peripherals/example.yaml \
            > /dev/null')

    def compareFiles(self, platformName, extension):
        peripherals = [
            'ADS1015', 'BMP280', 'LSM303D', 'MCP4725', 'MCP9808',
            'TCS3472', 'Example'
        ]
        testPath = 'test/sampleData'
        tmpPath  = 'tmp/com/cyanobyte'
        
        for peripheral in peripherals:
            fullTestPath = os.path.join(
                testPath,
                platformName,
                peripheral + '.' + extension
            )
            fullTmpPath  = os.path.join(
                tmpPath,
                peripheral + '.' + extension
            )
        
            print('Comparing', fullTestPath, 'and', fullTmpPath)
            with open(fullTestPath) as file1:
                with open(fullTmpPath) as file2:
                    fileContents1 = file1.read()
                    fileContents2 = file2.read()
                    self.assertEqual(
                        fileContents1,
                        fileContents2,
                        msg="{0} and {1} are not the same".format(fullTestPath, fullTmpPath)
                    )

    def tearDown(self):
        print('\n')

    def test_Arduino(self):
        self.generatePeripheral('arduino.cpp')
        self.compareFiles('arduino', 'cpp')
        self.generatePeripheral('arduino.h')
        self.compareFiles('arduino', 'h')

    def test_CMSIS_SVD(self):
        self.generatePeripheral('cmsis.svd')
        self.compareFiles('cmsis-svd', 'svd')

    def test_EmbeddedC(self):
        self.generatePeripheral('generic.c')
        self.compareFiles('embedded-c', 'c')
        self.generatePeripheral('generic.h')
        self.compareFiles('embedded-c', 'h')

    def test_Kubos(self):
        self.generatePeripheral('kubos.c')
        self.compareFiles('kubos', 'c')
        self.generatePeripheral('kubos.h')
        self.compareFiles('kubos', 'h')

    def test_LaTeX(self):
        self.generatePeripheral('datasheet.tex')
        self.compareFiles('datasheet', 'tex')
    
    def test_Markdown(self):
        self.generatePeripheral('doc.md')
        self.compareFiles('markdown', 'md')

    def test_RaspberryPi(self):
        self.generatePeripheral('raspberrypi.py')
        self.compareFiles('raspberrypi', 'py')

if __name__ == '__main__':
    unittest.main()
