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
    def compareFiles(self, filePath1, filePath2):
        print('Comparing', filePath1, 'and', filePath2)
        file1 = open(filePath1)
        fileContents1 = file1.read()
        file2 = open(filePath2)
        fileContents2 = file2.read()
        self.assertEqual(
            fileContents1,
            fileContents2,
            msg="{0} and {1} are not the same".format(filePath1, filePath2)
        )
        file1.close()
        file2.close()

    def setUp(self):
        # Clear out existing files
        os.system('rm -rf ./build/')
        print('\n')

    def test_Mcp4725(self):
        os.system('python3 src/codegen.py \
            -o ./build \
            -t templates/doc.md \
            -t templates/raspberrypi.py \
            -i peripherals/Mcp4725.yaml > /dev/null')
        self.compareFiles('build/com/example/Mcp4725.md', 'test/sampleData/Mcp4725.md')
        self.compareFiles('build/com/example/Mcp4725.py', 'test/sampleData/Mcp4725.py')

if __name__ == '__main__':
    unittest.main()
