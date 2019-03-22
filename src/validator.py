import sys
import click
import yaml
import json
from jsonschema import validate


@click.command()
@click.option("-i", "--input", "input_files", multiple=True)
def valdiate(input_files):
    """
    Valdiate a list of CyanoByte documents.

    Args:
        input_files: A list of CyanoByte documents to validate.
    """
    # Load the JSON Schema file
    with open("spec/cyanobyte.schema.json", "r") as schema_json:
        schema = json.load(schema_json)

    # Validate each document against the schema
    for input_file in input_files:
        with open(input_file, "r") as document_yaml:
            document_dict = yaml.load(document_yaml)
            validate(instance=document_dict, schema=schema)


if __name__ == "__main__":
    valdiate(sys.argv[1:])
