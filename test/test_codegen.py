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
    def generatePeripheral(self, peripheral):
        os.system('python3 src/codegen.py \
            -c \
            -o ./tmp/ \
            -t templates/doc.md \
            -t templates/raspberrypi.py \
            -t templates/arduino.cpp \
            -t templates/arduino.h \
            -i peripherals/' + peripheral + '.yaml > /dev/null')
        os.system('python3 src/codegen.py \
            -c \
            -o ./tmpKubos/ \
            -t templates/kubos.c \
            -t templates/kubos.h \
            -i peripherals/' + peripheral + '.yaml > /dev/null')

    def compareFiles(self, driverName):
        drivers = [driverName.strip() + '.md',
                   driverName.strip() + '.py',
                   driverName.strip() + '.cpp',
                   driverName.strip() + '.h']
        driversKubos = [driverName.strip() + '.c',
                        driverName.strip() + '.h']
                   
        testPath = 'test/sampleData'
        testPathKubos = 'test/sampleDataKubos'
        tmpPath  = 'tmp/com/cyanobyte'
        tmpPathKubos = 'tmpKubos/com/cyanobyte'
        
        for driver in drivers:
            fullTestPath = os.path.join(testPath, driver)
            fullTmpPath  = os.path.join(tmpPath, driver)
        
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

        for driver in driversKubos:
            fullTestPath = os.path.join(testPathKubos, driver)
            fullTmpPath  = os.path.join(tmpPathKubos, driver)
        
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

    def test_ADS1015(self):
        self.generatePeripheral('ADS1015')
        self.compareFiles('ADS1015')
        
    def test_BMP280(self):
        self.generatePeripheral('BMP280')
        self.compareFiles('BMP280')
        
    def test_LSM303D(self):
        self.generatePeripheral('LSM303D')
        self.compareFiles('LSM303D')

    def test_MCP4725(self):
        self.generatePeripheral('MCP4725')
        self.compareFiles('MCP4725')

    def test_MCP9808(self):
        self.generatePeripheral('MCP9808')
        self.compareFiles('MCP9808')

    def test_TCS3472(self):
        self.generatePeripheral('TCS3472')
        self.compareFiles('TCS3472')

if __name__ == '__main__':
    unittest.main()
