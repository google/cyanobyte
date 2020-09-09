# Peripheral Codegen
This project is an example of how to describe peripherals with an intermediary layer (YAML files) which can be used to generate library files for a peripheral.

It can also generate reference documentation for a peripheral, useful for embedding into datasheets.

The tool works well for I2C devices, while SPI support is in alpha.

This is not an official Google product.

## Setup
Note: This project requires Python3. You can install using pip

`pip install cyanobyte`

## Run Codegen
`cyanobyte-codegen -t templates/doc.md -o ./build peripherals/MCP4725.yaml`

### Options
* `-t` - A template file. You can provide multiple template files.
* `-o` - The output directory where files will be generated.
* `-e` - The directory that emboss folder is stored.
* `-d` - Debug flag to print out additional information.
* `-c` - Clean the output directory before generating files.

One or multiple files can be passed as an argument.

### Clean
`rm -rf ./build`

## Run Validator
`cyanobyte-validator peripherals/MCP9808.yaml`

One or multiple files can be passed as an argument.

## Peripheral YAML file
The current spec is described in `docs/cyanobyte.md`. You can find all examples in the `peripherals/` directory.

## Test
### Lint
`python3 -m pylint --rcfile=test/pylintrc cyanobyte/*.py`  
`python3 -m pylint --rcfile=test/pylintrc test/sampleData/*.py`

### Unit test
`python3 -m unittest test.test_codegen`

## Templates
The [templates](templates) directory includes a set of canonical templates which can be used with this codegen tool.

The [peripherals](peripherals) directory includes a set of peripheral description files that have been created along with
the project. It is not an exhaustive list.

## Development setup
`pip install -r requirements.txt --user`


For more advanced development, also install the dev list.
`pip install -r requirements-dev.txt --user`

## Contributors
Contributions are welcome! See [CONTRIBUTING.md](CONTRIBUTING.md) for more information.

When a pull request is submitted, a continuous integration task is run. The CI task must
be completed successfully before a patch is merged. You can see the specific rules run in
[cloudbuild.yaml](cloudbuild.yaml).

## License
See [LICENSE](LICENSE)
