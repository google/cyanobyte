"""CyanoByte Validator

The CyanoByte validator is used to ensure that a CyanoByte
document meets the specification.
"""

import sys
import json
import click
import os
import os.path as path
import yaml
from yaml.constructor import ConstructorError
try:
    from yaml import CLoader as Loader
except ImportError:
    from yaml import Loader
from jsonschema import validate, ValidationError

class CyanobyteValidationError:
    def __init__(self, input_file, err):
        self.input_file = input_file
        self.err = err

# See https://gist.github.com/pypt/94d747fe5180851196eb
def no_duplicates_constructor(loader, node, deep=False):
    """Check for duplicate keys."""

    mapping = {}
    for key_node, value_node in node.value:
        key = loader.construct_object(key_node, deep=deep)
        value = loader.construct_object(value_node, deep=deep)
        if key in mapping:
            raise ConstructorError("while constructing a mapping", node.start_mark,
                                   "found duplicate key (%s)" % key, key_node.start_mark)
        mapping[key] = value

    return loader.construct_mapping(node, deep)

yaml.add_constructor(yaml.resolver.BaseResolver.DEFAULT_MAPPING_TAG, no_duplicates_constructor, Loader=Loader)

def cyanobyte_validate(input_files):
    """
    Validate a list of CyanoByte documents.

    Args:
        input_files: A list of CyanoByte documents to validate.
    """
    # Load the JSON Schema file
    path = "cyanobyte-spec/cyanobyte.schema.json"
    try:
        import pkg_resources
        path = pkg_resources.resource_filename('cyanobyte-spec', 'cyanobyte.schema.json')
    except:pass

    with open(path, "r") as schema_json:
        schema = json.load(schema_json)

    # Validate each document against the schema
    errors = []
    for input_file in input_files:
        with open(input_file, "r") as document_yaml:
            try:
                document_dict = yaml.load(document_yaml, Loader=Loader)
                validate(instance=document_dict, schema=schema)
                print('✓ ' + input_file)
            except (ConstructorError, ValidationError) as err:
                print('✘ ' + input_file)
                errors.append(CyanobyteValidationError(input_file, err))

    # Dump all errors here
    print('')
    for e in errors:
        print(e.input_file + ':')
        print(e.err)


def unittest(input_files):
    # Load the python-unittest template file
    template = "cyanobyte-templates/python-unittest.py"
    try:
        import pkg_resources
        template = pkg_resources.resource_filename('cyanobyte-templates', 'python-unittest.py')
    except:pass

    if _DEBUG:
        print('cyanobyte-codegen \
            -c \
            -o ./tmp/ \
            -t ' + template + ' ' + ' \
            '.join(input_files))
    os.system('cyanobyte-codegen \
        -c \
        -o ./tmp/ \
        -t ' + template + ' ' + ' \
        '.join(input_files))
    for i in input_files:
        # Now execute each unittest
        file = i.replace('.yaml', '.py')
        file = path.basename(file)
        # NOTE: Won't work for different package names
        if _DEBUG:
            print('python3 -m unittest tmp/com/cyanobyte/' + file)
        os.system('python3 -m unittest tmp/com/cyanobyte/' + file)

@click.command()
@click.option("-d", "--debug", "debug", default=False)
@click.option("--validate-schema", "flag_schema", is_flag=True)
@click.option("--unit-test", "flag_unittest", is_flag=True)
@click.argument("input_files", type=click.Path(exists=True), nargs=-1)
def click_validate(input_files, flag_schema, flag_unittest, debug=False):
    """
    Main command line entrypoint

    Args:
        input_files: A list of CyanoByte documents to validate.
    """
    #pylint: disable=global-statement
    global _DEBUG
    _DEBUG = debug

    run_schema = True
    run_unittest = True
    # Default all modes to true unless there's a flag
    if flag_schema or flag_unittest:
        # Then we only allow a few modes
        if not flag_schema:
            run_schema = False
        if not flag_unittest:
            run_unittest = False

    if run_schema:
        cyanobyte_validate(input_files)
    if run_unittest:
        unittest(input_files)

if __name__ == "__main__":
    click_validate(sys.argv[1:])
