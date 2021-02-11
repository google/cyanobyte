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
"""
Command-line tool to generate source files from Jinja templates.
"""
import os
import re
import sys
import shutil
from os import path
import subprocess
import json
import click

from yaml import load
try:
    from yaml import CLoader as Loader
except ImportError:
    from yaml import Loader
from jinja2 import Environment, FileSystemLoader

from cyanobyte import __version__
# Use the module title to import correctly in a Pip bundle
try:
    from cyanobyte.convert_json_to_yaml import convert_json_to_yaml
except ImportError:
    from convert_json_to_yaml import convert_json_to_yaml

# via Python 3.7+, use this in Pip bundle to access correct resource filepath
try:
    import importlib.resources as pkg_resources
except ImportError:
    # Try backported to PY<37 `importlib_resources`.
    print('Info: Python v3.7+ is recommended with this package')
    import importlib_resources as pkg_resources


_VERSION = __version__
_DEBUG = False
_CLEAN = False
_TEMPLATES = dict(
    arduino=["arduino.cpp", "arduino.h"],
    circuitpython=["circuitpython.py"],
    cmsis=["cmsis.svd"],
    datasheet=["datasheet.tex"],
    doc=["doc.md"],
    embedded=["generic.c", "generic.h"],
    esp32=["arduino.cpp", "arduino.h"],
    espruino=["espruino.js"],
    i2cdevice=["i2c-device.py"],
    kubos=["kubos.c", "kubos.h"],
    micropython=["micropython.py"],
    raspberrypi=["raspberrypi.py"],
    webpage=["webpage.html"],
)
_OPTIONS = dict(
    esp32="esp32.options.yaml"
)

def convert_emb_to_yaml(emboss_filepath, emboss_basepath):
    """
    Converts a emb into a yaml
    """
    subprocess_environment = os.environ.copy()
    if subprocess_environment.get("PYTHONPATH"):
        subprocess_environment["PYTHONPATH"] = (
            emboss_basepath + ":" + subprocess_environment.get("PYTHONPATH"))
    else:
        subprocess_environment["PYTHONPATH"] = emboss_basepath

    # from emb to json
    front_end_args = [
        sys.executable,
        path.join(emboss_basepath, "compiler", "front_end",
                  "emboss_front_end.py"),
        "--output-ir-to-stdout",
    ]
    front_end_args.append(emboss_filepath)
    front_end_status = subprocess.run(
        front_end_args,
        stdout=subprocess.PIPE,
        env=subprocess_environment,
        check=True)
    content = json.loads(front_end_status.stdout)
    yaml_dict = convert_json_to_yaml(content)
    return yaml_dict

def camel_to_snake(camel_str):
    """
    Converts a camelCaseString into a snake_case_string
    """
    regex = re.compile('([A-Z])')
    result = regex.sub(r'_\g<0>', str(camel_str))
    return result.lower()

def regex_replace(in_str, regex_pattern, regex_replacement):
    """
    On a given text input, replace it with a regular expression
    """
    regex = re.compile(regex_pattern)
    return regex.sub(regex_replacement, in_str)

def generate_source_file(template, peripheral, opts, template_ext,
                         out_dir, emboss_path):
    """
    Generates a source file for a provided Jinja2 template.

    Args:
        template: A Jinja file that is part of the template.
        peripheral: A single Cyanobyte document to generate.
        options: A single options yaml file with additional optinos for merge
        template_ext: The file extension of the output.
        out_dir: The directory to output the generated files.
    """
    # Open peripheral file
    with open(peripheral, "r") as peripheral_file:
        peripheral_data = load(peripheral_file, Loader=Loader)
        # Add additional metadata to the spec data
        peripheral_data["version"] = _VERSION
        peripheral_data["fileName"] = peripheral

        if opts is not None:
            try:
                options_file = open(opts, "r")
            except:
                options_file = pkg_resources.open_text('templates', opts)
            options_data = load(options_file, Loader=Loader)
            peripheral_data["options"] = options_data

        # Load imports
        if 'imports' in peripheral_data:
            for emboss_key in peripheral_data['imports']:
                emboss_filename = peripheral_data['imports'][emboss_key]
                dir_path = os.path.dirname(os.path.realpath(peripheral))
                emboss_filepath = os.path.join(dir_path, emboss_filename)
                peripheral_data['imports'][emboss_key] = convert_emb_to_yaml(
                    emboss_filepath, emboss_path)
                if _DEBUG:
                    print('Imported ' + emboss_filename)

        if _DEBUG:
            print(peripheral_data)

        # Render file
        peripheral_gen = template.render(peripheral_data)
        # Get file path
        # Take into consideration the package
        if _DEBUG:
            print(peripheral_data["info"]["title"])
        if 'package' in peripheral_data["info"]:
            package_path = peripheral_data["info"]["package"].replace(".", "/")
        else:
            package_path = ''
        output_file_path = os.path.join(
            out_dir,
            os.path.normpath(package_path)
        )
        if not os.path.exists(output_file_path):
            try:
                os.makedirs(output_file_path)
            except OSError:
                print("Could not make file directory", output_file_path)
                sys.exit(1)

        peripheral_output_path = os.path.join(
            output_file_path,
            peripheral_data["info"]["title"] + template_ext
        )
        with open(peripheral_output_path, "x") as peripheral_output_file:
            peripheral_output_file.write(peripheral_gen)


def generate_files_for_template(env, template_file, in_files, opts,
                                out_dir, emboss_path):
    """
    Generates a series of source files for a provided template file.

    Args:
        env: Jinja2 environment used during generation.
        template_file: A single file that is part of the template.
        in_files: A list of Cyanobyte documents to generate.
        opts: A single YAML file with additional options to apply
        out_dir: The directory to output the generated files.
    """
    # Open template
    with open(template_file, "r") as template_contents:
        template_object = env.from_string(template_contents.read())
        _, template_extension = os.path.splitext(template_file)

        # Create output dir
        if not os.path.exists(out_dir):
            try:
                os.makedirs(out_dir)
            except OSError:
                print("Could not make output directory", out_dir)
                sys.exit(1)

        for peripheral in in_files:
            generate_source_file(
                template_object,
                peripheral,
                opts,
                template_extension,
                out_dir,
                emboss_path
            )

def generate_files_for_raw_text(env, template_file, template_text, in_files, opts,
                                out_dir, emboss_path):
    """
    Generates a series of source files for provided template text.
    This text may be loaded ahead of time from a static file resource.

    Args:
        env: Jinja2 environment used during generation.
        template_file: Original template file; needed for file extension.
        template_text: Direct text content of template.
        in_files: A list of Cyanobyte documents to generate.
        opts: A single YAML file with additional options to apply
        out_dir: The directory to output the generated files.
    """
    # Open template
    template_object = env.from_string(template_text)
    _, template_extension = os.path.splitext(template_file)

    # Create output dir
    if not os.path.exists(out_dir):
        try:
            os.makedirs(out_dir)
        except OSError:
            print("Could not make output directory", out_dir)
            sys.exit(1)

    for peripheral in in_files:
        generate_source_file(
            template_object,
            peripheral,
            opts,
            template_extension,
            out_dir,
            emboss_path
        )


@click.command()
@click.option("-t", "--template", "template_files", multiple=True)
@click.option("-o", "--output", "output_dir", default="./build",
              show_default=True)
@click.option("-e", "--emboss", "emboss_path", default="../emboss",
              show_default=True)
@click.option("-d", "--debug", "debug", default=False)
@click.option("-p", "--options", "options", default=None)
@click.option("-c", "--clean", "clean", is_flag=True)
@click.argument("input_files", type=click.Path(exists=True), nargs=-1)
def gen(input_files, template_files=None, output_dir='./build',
        emboss_path="../emboss", debug=False, options=None, clean=False):
    """
    Takes command line arguments and generates source files for every
    peripheral to each template file.

    Args:
        input_files: A list of CyanoByte documents to generate.
        template_files: A list of files that are part of the template.
        output_dir: The directory to output the generated files.
        debug: Print debug messages?
        clean: Clean the output directory before output?
    """
    #pylint: disable=global-statement
    global _DEBUG
    _DEBUG = debug

    if _DEBUG:
        print("Generating " + str(len(input_files)) + " file(s)")

    # Removes any files in the directory if clean flag is set
    if clean and os.path.exists(output_dir):
        shutil.rmtree(output_dir)

    # Setup Jinja2 environment
    env = Environment(
        loader=FileSystemLoader([
            "",
            # Do this in order to load the templates installed by Pip
            os.path.join(os.path.dirname(os.path.realpath(__file__)), '..', 'templates')
        ]),
        trim_blocks=True,
        lstrip_blocks=True,
        extensions=['jinja2.ext.loopcontrols']
    )
    env.filters['camel_to_snake'] = camel_to_snake
    env.filters['regex_replace'] = regex_replace
    for template_file in template_files:
        # Check template registry
        if template_file in _TEMPLATES:
            if template_file in _OPTIONS and options is None:
                options = _OPTIONS[template_file]
            # This will be an array of filepaths
            for filepath in _TEMPLATES[template_file]:
                generate_files_for_raw_text(
                    env,
                    filepath,
                    pkg_resources.read_text('templates', filepath),
                    input_files,
                    options,
                    output_dir,
                    emboss_path
                )
        else:
            generate_files_for_template(
                env,
                template_file,
                input_files,
                options,
                output_dir,
                emboss_path
            )


if __name__ == "__main__":
    gen(sys.argv[1:])
