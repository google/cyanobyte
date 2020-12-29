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
    """
    Test class around generating code from peripheral schemas.
    """
    maxDiff = None

    def gen_peripheral_template(self, template):
        """
        Generates all I2C peripheral files for a given template.
        """
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

    def gen_peripheral_tag(self, tag):
        """
        Generates all I2C peripherals for a given tag.
        """
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

    def compare_files(self, platformName, extension):
        """
        Compares the expected and actual file output for a given platform.
        """
        peripherals = [
            'ADS1015', 'BH1750FVI', 'BMP180', 'BMP280', 'LSM303D',
            'MCP4725', 'MCP9808', 'TCS3472', 'Example'
        ]
        test_path = 'test/sampleData'
        tmp_path  = 'tmp/com/cyanobyte'
        
        for peripheral in peripherals:
            full_test_path = os.path.join(
                test_path,
                platformName,
                peripheral + '.' + extension
            )
            full_tmp_path  = os.path.join(
                tmp_path,
                peripheral + '.' + extension
            )
        
            print('Comparing', full_test_path, 'and', full_tmp_path)
            with open(full_test_path) as file1:
                with open(full_tmp_path) as file2:
                    file_contents_1 = file1.read()
                    file_contents_2 = file2.read()
                    self.assertEqual(
                        file_contents_1,
                        file_contents_2,
                        msg="{0} and {1} are not the same".format(full_test_path, full_tmp_path)
                    )

    def tearDown(self):
        print('\n')

    def test_arduino(self):
        """
        Verify output of Arduino template.
        """
        self.gen_peripheral_tag('arduino')
        self.compare_files('arduino', 'cpp')
        self.compare_files('arduino', 'h')

    def test_circuitpython(self):
        """
        Verify output of CircuitPython template.
        """
        self.gen_peripheral_template('circuitpython.py')
        self.compare_files('circuitpython', 'py')

    def test_cmsis_svd(self):
        """
        Verify output of CMSIS template.
        """
        self.gen_peripheral_template('cmsis.svd')
        self.compare_files('cmsis-svd', 'svd')

    def test_embeddedc(self):
        """
        Verify output of Embedded C template.
        """
        self.gen_peripheral_tag('embedded')
        self.compare_files('embedded-c', 'c')
        self.compare_files('embedded-c', 'h')

    def test_esp32(self):
        """
        Verify output of ESP32 template.
        """
        self.gen_peripheral_tag('esp32')
        self.compare_files('esp32', 'cpp')
        self.compare_files('esp32', 'h')

    def test_espruino(self):
        """
        Verify output of Espruino template.
        """
        self.gen_peripheral_tag('espruino')
        self.compare_files('espruino', 'js')

    def test_i2c_device(self):
        """
        Verify output of Pimoroni i2c-device template.
        """
        self.gen_peripheral_tag('i2cdevice')
        self.compare_files('i2c-device', 'py')

    def test_kubos(self):
        """
        Verify output of Kubos template.
        """
        self.gen_peripheral_tag('kubos')
        self.compare_files('kubos', 'c')
        self.compare_files('kubos', 'h')

    def test_latex(self):
        """
        Verify output of LaTeX datasheet template.
        """
        self.gen_peripheral_tag('datasheet')
        self.compare_files('datasheet', 'tex')

    def test_markdown(self):
        """
        Verify output of Markdown web-hosting template.
        """
        self.gen_peripheral_tag('doc')
        self.compare_files('markdown', 'md')

    def test_micropython(self):
        """
        Verify output of Micropython template.
        """
        self.gen_peripheral_tag('micropython')
        self.compare_files('micropython', 'py')

    def test_raspberrypi(self):
        """
        Verify output of Raspberry Pi template.
        """
        self.gen_peripheral_tag('raspberrypi')
        self.compare_files('raspberrypi', 'py')

    def test_rpi_emboss(self):
        """
        Verify output of Raspberry Pi template with Emboss/SPI.
        """
        # Generate Peripheral Tag
        os.system('python3 cyanobyte/codegen.py \
            -c \
            --debug \
            -o ./tmp/ \
            -t templates/raspberrypi-spi-emboss.py\
            peripherals/examplespi-emboss.yaml \
            > /dev/null')
        # Compare files
        test_path = 'test/sampleData/raspberrypi/ExampleSpiEmboss.py'
        tmp_path  = 'tmp/com/cyanobyte/ExampleSpiEmboss.py'
        print('Comparing', test_path, 'and', tmp_path)
        with open(test_path) as file1:
            with open(tmp_path) as file2:
                file_contents_1 = file1.read()
                file_contents_2 = file2.read()
                self.assertEqual(
                    file_contents_1,
                    file_contents_2,
                    msg="{0} and {1} are not the same".format(test_path, tmp_path)
                )

    def test_webpage(self):
        """
        Verify output of webpage template.
        """
        self.gen_peripheral_tag('webpage')
        self.compare_files('webpage', 'html')

if __name__ == '__main__':
    unittest.main()
