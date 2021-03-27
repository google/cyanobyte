"""CyanoByte Validator

The CyanoByte validator is used to ensure that a CyanoByte
document meets the specification.
"""

import sys
import json
import click
import yaml
from yaml.constructor import ConstructorError
try:
    from yaml import CLoader as Loader
except ImportError:
    from yaml import Loader
from jsonschema import validate

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
    with open("spec/cyanobyte.schema.json", "r") as schema_json:
        schema = json.load(schema_json)

    # Validate each document against the schema
    for input_file in input_files:
        with open(input_file, "r") as document_yaml:
            document_dict = yaml.load(document_yaml, Loader=Loader)
            validate(instance=document_dict, schema=schema)
            print(input_file + ' is valid')


@click.command()
@click.argument("input_files", type=click.Path(exists=True), nargs=-1)
def click_validate(input_files):
    """
    Main command line entrypoint

    Args:
        input_files: A list of CyanoByte documents to validate.
    """
    cyanobyte_validate(input_files)


if __name__ == "__main__":
    click_validate(sys.argv[1:])
