#!/usr/bin/env python3
#
# Copyright (C) 2020 Google Inc.
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

from cmsis_svd.parser import SVDParser
import unittest
import os

class TestCodegen(unittest.TestCase):
    def verify_cmsis_output(self, filename):
        filepath = 'test/sampleData/cmsis-svd/' + filename + '.svd'
        print('Parsing ' + filepath)
        parser = SVDParser.for_xml_file(filepath)
        self.assertEqual(
            filename,
            parser.get_device().peripherals[0].name,
            msg="{0} is not the provided name in the CMSIS SVD file"
        )

    def tearDown(self):
        print('\n')

    def test_ADS1015(self):
        self.verify_cmsis_output('ADS1015')

    def test_BMP280(self):
        self.verify_cmsis_output('BMP280')

    def test_Example(self):
        self.verify_cmsis_output('Example')

    def test_LSM303D(self):
        self.verify_cmsis_output('LSM303D')

    def test_MCP4725(self):
        self.verify_cmsis_output('MCP4725')

    def test_MCP9808(self):
        self.verify_cmsis_output('MCP9808')

    def test_TCS3472(self):
        self.verify_cmsis_output('TCS3472')

if __name__ == '__main__':
    unittest.main()