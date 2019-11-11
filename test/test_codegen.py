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

    def compareFiles(self, filePath1, filePath2):
        print('Comparing', filePath1, 'and', filePath2)
        with open(filePath1) as file1:
            with open(filePath2) as file2:
                fileContents1 = file1.read()
                fileContents2 = file2.read()
                self.assertEqual(
                    fileContents1,
                    fileContents2,
                    msg="{0} and {1} are not the same".format(filePath1, filePath2)
                )

    def tearDown(self):
        print('\n')

    def test_ADS1015(self):
        self.generatePeripheral('ADS1015')
        self.compareFiles('tmp/com/cyanobyte/ADS1015.md', 'test/sampleData/ADS1015.md')
        self.compareFiles('tmp/com/cyanobyte/ADS1015.py', 'test/sampleData/ADS1015.py')
        self.compareFiles('tmp/com/cyanobyte/ADS1015.cpp', 'test/sampleData/ADS1015.cpp')
        self.compareFiles('tmp/com/cyanobyte/ADS1015.h', 'test/sampleData/ADS1015.h')

    def test_BMP280(self):
        self.generatePeripheral('BMP280')
        self.compareFiles('tmp/com/cyanobyte/BMP280.md', 'test/sampleData/BMP280.md')
        self.compareFiles('tmp/com/cyanobyte/BMP280.py', 'test/sampleData/BMP280.py')
        self.compareFiles('tmp/com/cyanobyte/BMP280.cpp', 'test/sampleData/BMP280.cpp')
        self.compareFiles('tmp/com/cyanobyte/BMP280.h', 'test/sampleData/BMP280.h')

    def test_LSM303D(self):
        self.generatePeripheral('LSM303D')
        self.compareFiles('tmp/com/cyanobyte/LSM303D.md', 'test/sampleData/LSM303D.md')
        self.compareFiles('tmp/com/cyanobyte/LSM303D.py', 'test/sampleData/LSM303D.py')
        self.compareFiles('tmp/com/cyanobyte/LSM303D.cpp', 'test/sampleData/LSM303D.cpp')
        self.compareFiles('tmp/com/cyanobyte/LSM303D.h', 'test/sampleData/LSM303D.h')

    def test_MCP4725(self):
        self.generatePeripheral('MCP4725')
        self.compareFiles('tmp/com/cyanobyte/MCP4725.md', 'test/sampleData/MCP4725.md')
        self.compareFiles('tmp/com/cyanobyte/MCP4725.py', 'test/sampleData/MCP4725.py')
        self.compareFiles('tmp/com/cyanobyte/MCP4725.cpp', 'test/sampleData/MCP4725.cpp')
        self.compareFiles('tmp/com/cyanobyte/MCP4725.h', 'test/sampleData/MCP4725.h')

    def test_MCP9808(self):
        self.generatePeripheral('MCP9808')
        self.compareFiles('tmp/com/cyanobyte/MCP9808.md', 'test/sampleData/MCP9808.md')
        self.compareFiles('tmp/com/cyanobyte/MCP9808.py', 'test/sampleData/MCP9808.py')
        self.compareFiles('tmp/com/cyanobyte/MCP9808.cpp', 'test/sampleData/MCP9808.cpp')
        self.compareFiles('tmp/com/cyanobyte/MCP9808.h', 'test/sampleData/MCP9808.h')

    def test_TCS3472(self):
        self.generatePeripheral('TCS3472')
        self.compareFiles('tmp/com/cyanobyte/TCS3472.md', 'test/sampleData/TCS3472.md')
        self.compareFiles('tmp/com/cyanobyte/TCS3472.py', 'test/sampleData/TCS3472.py')
        self.compareFiles('tmp/com/cyanobyte/TCS3472.cpp', 'test/sampleData/TCS3472.cpp')
        self.compareFiles('tmp/com/cyanobyte/TCS3472.h', 'test/sampleData/TCS3472.h')

if __name__ == '__main__':
    unittest.main()
