import unittest
from src.validator import cyanobyte_valdiate
from jsonschema.exceptions import ValidationError


class TestValidatorGeneral(unittest.TestCase):
    def test_blank_file(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/blank.yaml']
        )


class TestValidatorInfo(unittest.TestCase):
    def test_valid(self):
        self.assertIsNone(
            cyanobyte_valdiate(['test/sampleData/validator/info/valid.yaml'],)
        )

    def test_missing_cyanobyte_version(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/info/missing_cyanobyte_version.yaml']
        )

    def test_missing_info(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/info/missing_info.yaml']
        )

    def test_missing_title(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/info/missing_title.yaml']
        )

    def test_missing_description(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/info/missing_description.yaml']
        )

    def test_missing_contact(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/info/missing_contact.yaml']
        )

    def test_missing_contact_name(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/info/missing_contact_name.yaml']
        )

    def test_missing_contact_url(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/info/missing_contact_url.yaml']
        )

    def test_missing_contact_email(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/info/missing_title.yaml']
        )

    def test_missing_license(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/info/missing_license.yaml']
        )

    def test_missing_version(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/info/missing_version.yaml']
        )


class TestValidatorI2c(unittest.TestCase):
    def test_valid(self):
        self.assertIsNone(
            cyanobyte_valdiate(['test/sampleData/validator/i2c/valid.yaml'],)
        )

    def test_missing_address_type(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/i2c/missing_address_type.yaml']
        )

    def test_missing_address(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/i2c/missing_address.yaml']
        )

    def test_missing_address_mask(self):
        self.assertRaises(
            ValidationError,
            cyanobyte_valdiate,
            ['test/sampleData/validator/i2c/missing_address_mask.yaml']
        )


class TestValidatorPeripherals(unittest.TestCase):
    def test_mcp4725(self):
        self.assertIsNone(cyanobyte_valdiate(['peripherals/Mcp4725.yaml']))

    def test_mcp9808(self):
        self.assertIsNone(cyanobyte_valdiate(['peripherals/MCP9808.yaml']))

    def test_tcs3472(self):
        self.assertIsNone(cyanobyte_valdiate(['peripherals/Tcs3472.yaml']))

if __name__ == '__main__':
    unittest.main()
