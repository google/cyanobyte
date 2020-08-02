import sys
import json
import yaml
from yaml import load, dump
try:
    from yaml import CLoader as Loader, CDumper as Dumper
except ImportError:
    from yaml import Loader, Dumper


def convert_json_to_yaml(content):
    yaml_dict = {}

    source_file_full_name = content["module"][0]["source_file_name"]
    yaml_dict["filename"] = source_file_full_name.split("/")[-1]
    source_file_full_name_elem = [ x.upper() for x in source_file_full_name.split("/")[:-1]]
    source_file_full_name_elem += [x.upper() for x in yaml_dict["filename"].split(".")]
    source_file_full_name_elem.append("H")
    yaml_dict["header_guard"] = "_".join(source_file_full_name_elem)

    yaml_dict["structs"] = {}
    struct_list = content["module"][0]["type"]
    for struct_id in range(len(struct_list)):
        yaml_struct_dict = {}

        struct_info = struct_list[struct_id]

        # e.g., Floats for floats, Doubles for doubles
        struct_name = struct_info["name"]["name"]["text"]
        yaml_dict["structs"][struct_name] = yaml_struct_dict

        fields_list = struct_info["structure"]["field"]
        unit_in_bit = int(struct_info["addressable_unit"])

        yaml_struct_dict["fields"] = {}
        for field_info in fields_list:
            field_name = field_info["name"]["name"]["text"]
            if "$" in field_name:
                continue

            try:
                offset_in_unit = int(field_info["location"]["start"]["constant"]["value"])
                size_in_unit = int(field_info["location"]["size"]["constant"]["value"])
            except: 
                continue

            yaml_field_dict = { }
            yaml_struct_dict["fields"][field_name] = yaml_field_dict

            yaml_field_dict["offset_in_bit"] = int(offset_in_unit * unit_in_bit)
            yaml_field_dict["offset_in_byte"] = int(offset_in_unit * unit_in_bit / 8)
            yaml_field_dict["size_in_bit"] = int(size_in_unit * unit_in_bit)
            yaml_field_dict["size_in_byte"] = int(size_in_unit * unit_in_bit / 8)

    return yaml_dict


if __name__ == "__main__":
    if len(sys.argv) > 1:
        json_file = sys.argv[1]
        print("input file: {}".format(json_file))
        content = json.load(open(json_file))
    else:
        content = json.loads(sys.stdin.read())

    yaml_dict = convert_json_to_yaml(content)

    yaml_file = yaml_dict["filename"]+".yaml"
    yaml.dump(yaml_dict, open(yaml_file, "w"), default_flow_style=False, Dumper=Dumper)
    print("saved yaml to {}".format(yaml_file))