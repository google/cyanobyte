# Peripheral Codegen
This project is an example of how to describe peripherals with an intermediary layer (YAML files) which can be used to generate library files for a peripheral.

It can also generate reference documentation for a periphreal, useful for embedding into datasheets.

This is not an official Google product.

## Setup
Note: This project requires Python3.
s
`pip install -r requirements.txt --user`

## Run
`python3 src/codegen.py -t templates/doc.md -o ./build -i peripherals/Mcp4725.yaml`

### Args
* `-t` - A template file. You can provide multiple template files.
* `-i` - A peripheral file. You can provide multiple input files.
* `-o` - The output directory where files will be generated.
* `-d` - Debug flag to print out additional information

### Clean
`rm -rf ./build`

## Peripheral YAML file
The current spec is described below. You can find all examples in the `peripherals/` directory.

```
name: The peripheral name
address: Device address
package: Package name, which may affect its directory output
little_endian: Whether bits are little endian. Default is False
registers:
  - name: Name of a 'virtual register', which may be smaller than or larger than a physical register
    description: Description of register
    address: Register address
    size: Virtual register size
    setter: Writable?
    getter: Readable?  
```

## Test
### Lint
`python3 -m pylint --rcfile=test/pylintrc src/*.py`
`python3 -m pylint --rcfile=test/pylintrc test/sampleData/*.py`

### Unit test
`python3 -m unittest test.test_codegen`

## Templates
The `templates` directory includes a set of canonical templates which can be used with this codegen tool.

The `peripherals` directory includes a set of peripheral description files that have been created along with
the project. It is not an exhaustive list.

## License
See `LICENSE`
