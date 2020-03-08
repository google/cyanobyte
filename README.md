# Peripheral Codegen
This project is an example of how to describe peripherals with an intermediary layer (YAML files) which can be used to generate library files for a peripheral.

It can also generate reference documentation for a periphreal, useful for embedding into datasheets.

This is not an official Google product.

## Setup
Note: This project requires Python3.

`pip install -r requirements.txt --user`

For more advanced development, also install the dev list.
`pip install -r requirements-dev.txt --user`

## Run Codegen
`python3 src/codegen.py -t templates/doc.md -o ./build -i peripherals/MCP4725.yaml`

### Args
* `-t` - A template file. You can provide multiple template files.
* `-i` - A peripheral file. You can provide multiple input files.
* `-o` - The output directory where files will be generated.
* `-d` - Debug flag to print out additional information
* `-c` - Clean the output directory before generating files

### Clean
`rm -rf ./build`

## Run Validator
`python3 src/validator.py -i peripherals/MCP9808.yaml`

### Args
* `-i` - A CyanoByte document. You can provide multiple input files.

## Peripheral YAML file
The current spec is described in `docs/cyanobyte.md`. You can find all examples in the `peripherals/` directory.

## Test
### Lint
`python3 -m pylint --rcfile=test/pylintrc src/*.py`
`python3 -m pylint --rcfile=test/pylintrc test/sampleData/*.py`

### Unit test
`python3 -m unittest test.test_codegen`

## Templates
The [templates](templates) directory includes a set of canonical templates which can be used with this codegen tool.

The [peripherals](peripherals) directory includes a set of peripheral description files that have been created along with
the project. It is not an exhaustive list.

## Contributors
Contributions are welcome! See [CONTRIBUTING.md](CONTRIBUTING.md) for more information.

When a pull request is submitted, a continuous integration task is run. The CI task must
be completed successfully before a patch is merged. You can see the specific rules run in
[cloudbuild.yaml](cloudbuild.yaml).

## License
See [LICENSE](LICENSE)
