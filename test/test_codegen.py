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
    maxDiff = None

    def generatePeripheralTemplate(self, template):
        os.system('python3 cyanobyte/codegen.py \
            -c \
            -o ./tmp/ \
            -t templates/' + template + '\
            peripherals/ADS1015.yaml \
            peripherals/BH1750FVI.yaml \
            peripherals/BMP180.yaml \
            peripherals/BMP280.yaml \
            peripherals/LSM303D.yaml \
            peripherals/MCP4725.yaml \
            peripherals/MCP9808.yaml \
            peripherals/TCS3472.yaml \
            peripherals/example.yaml \
            > /dev/null')

    def generatePeripheralTag(self, tag):
        os.system('python3 cyanobyte/codegen.py \
            -c \
            -o ./tmp/ \
            -t ' + tag + '\
            peripherals/ADS1015.yaml \
            peripherals/BH1750FVI.yaml \
            peripherals/BMP180.yaml \
            peripherals/BMP280.yaml \
            peripherals/LSM303D.yaml \
            peripherals/MCP4725.yaml \
            peripherals/MCP9808.yaml \
            peripherals/TCS3472.yaml \
            peripherals/example.yaml \
            > /dev/null')

    def compareFiles(self, platformName, extension):
        peripherals = [
            'ADS1015', 'BH1750FVI', 'BMP180', 'BMP280', 'LSM303D',
            'MCP4725', 'MCP9808', 'TCS3472', 'Example'
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
        self.generatePeripheralTag('arduino')
        self.compareFiles('arduino', 'cpp')
        self.compareFiles('arduino', 'h')

    def test_CMSIS_SVD(self):
        self.generatePeripheralTemplate('cmsis.svd')
        self.compareFiles('cmsis-svd', 'svd')

    def test_EmbeddedC(self):
        self.generatePeripheralTag('embedded')
        self.compareFiles('embedded-c', 'c')
        self.compareFiles('embedded-c', 'h')

    def test_Esp32(self):
        self.generatePeripheralTag('esp32')
        self.compareFiles('esp32', 'cpp')
        self.compareFiles('esp32', 'h')

    def test_Espruino(self):
        self.generatePeripheralTag('espruino')
        self.compareFiles('espruino', 'js')

    def test_Micropython(self):
        self.generatePeripheralTag('i2cdevice')
        self.compareFiles('i2cdevice', 'py')

    def test_Kubos(self):
        self.generatePeripheralTag('kubos')
        self.compareFiles('kubos', 'c')
        self.compareFiles('kubos', 'h')

    def test_LaTeX(self):
        self.generatePeripheralTag('datasheet')
        self.compareFiles('datasheet', 'tex')
    
    def test_Markdown(self):
        self.generatePeripheralTag('doc')
        self.compareFiles('markdown', 'md')

    def test_Micropython(self):
        self.generatePeripheralTag('micropython')
        self.compareFiles('micropython', 'py')

    def test_RaspberryPi(self):
        self.generatePeripheralTag('raspberrypi')
        self.compareFiles('raspberrypi', 'py')

if __name__ == '__main__':
    unittest.main()
