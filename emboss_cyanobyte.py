"""Main driver program for using cyanobyte as the backend for emboss"""

import argparse
import os
from os import path
import subprocess
import sys

def _parse_args(argv):
  parser = argparse.ArgumentParser(description="Emboss compiler with cyanobyte backend")
  parser.add_argument("--import-dir", "-I",
                      dest="import_dirs",
                      action="append",
                      default=["."],
                      help="A directory to use when searching for imported "
                           "embs.  If no import-dirs are specified, the "
                           "current directory will be used.")
  parser.add_argument("--template", "-T",
                      dest="template_file",
                      help="The template file to generate cpp code file.")
  parser.add_argument("--output-dir", "-O",
                      dest="output_dir",
                      default="./build",
                      help="the directory for storing the cpp code file.")
  parser.add_argument("input_file",
                      type=str,
                      nargs=1,
                      help=".emb file to compile.")
  return parser.parse_args(argv[1:])


def main(argv):
  flags = _parse_args(argv)
  base_path = path.dirname(__file__) or "."
  subprocess_environment = os.environ.copy()
  if subprocess_environment.get("PYTHONPATH"):
    subprocess_environment["PYTHONPATH"] = (
      base_path + ":" + subprocess_environment.get("PYTHONPATH"))
  else:
    subprocess_environment["PYTHONPATH"] = base_path

  # from emb to json
  front_end_args = [
      sys.executable,
      path.join(base_path, "compiler", "front_end", "emboss_front_end.py"),
      "--output-ir-to-stdout",
  ]
  for import_dir in flags.import_dirs:
    front_end_args.extend([
        "--import-dir",
        import_dir
    ])
  front_end_args.append(flags.input_file[0])
  front_end_status = subprocess.run(front_end_args,
                                    stdout=subprocess.PIPE,
                                    env=subprocess_environment)
  if front_end_status.returncode != 0:
    return front_end_status.returncode
   
  # from json to yaml
  subprocess.run(
      [
          sys.executable,
          path.join(base_path, "convert_json_to_yaml.py"),
      ],
      input=front_end_status.stdout,
      env=subprocess_environment)

  # from yaml to cpp 
  yaml_file = flags.input_file[0].split("/")[-1] + ".yaml"
  subprocess.run(
      [
          "cyanobyte-codegen",
          "-t",
          flags.template_file,
          "-o",
          flags.output_dir,
          yaml_file
      ],
      env=subprocess_environment)

  return 0


if __name__ == "__main__":
  sys.exit(main(sys.argv))
