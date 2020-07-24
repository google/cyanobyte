import sys
import json
import yaml
from yaml import load, dump
try:
    from yaml import CLoader as Loader, CDumper as Dumper
except ImportError:
    from yaml import Loader, Dumper


def convert_json_to_yaml(json_file):
    content = json.load(open(json_file))

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
        
        struct_fixed_size_in_bits = struct_info["attribute"][0]["value"]["expression"]["constant"]["value"]
        yaml_struct_dict["total_size_in_byte"] = int(struct_fixed_size_in_bits)//8

        fields_list = struct_info["structure"]["field"]

        yaml_struct_dict["fields"] = {}
        for field_info in fields_list:
            field_name = field_info["name"]["name"]["text"]
            if "$" in field_name:
                continue

            offset_in_byte = field_info["location"]["start"]["constant"]["value"]
            size_in_byte = field_info["location"]["size"]["constant"]["value"]

            yaml_field_dict = { }
            yaml_struct_dict["fields"][field_name] = yaml_field_dict

            yaml_field_dict["offset_in_byte"] = int(offset_in_byte)
            yaml_field_dict["size_in_bit"] = int(size_in_byte) * 8
            yaml_field_dict["size_in_byte"] = int(size_in_byte)
            
            for attr_info in field_info["attribute"]:
                if attr_info["name"]["text"] == "byte_order":
                    byte_order = attr_info["value"]["string_constant"]["text"]
                    yaml_field_dict["byteorder"] = byte_order
             
    # fill in metadata
    yaml_dict["cyanobyte"] = "0.1.0"
    yaml_info = {
        "contact": {
            "name": "Nick Felker",
            "url": "https://github.com/google/cyanobyte",
            "email": "felker@google.com",
        },    
        "package": "com.cyanobyte",
        "title": yaml_dict["filename"],
        "description": "Generated from Emboss file",
        "copyright": {
            "name": "Google Inc.",
            "date": "2019",
        },
        "license": {
            "name": "Apache-2.0",    
        },
        "version": "0.1.0",
    }

    yaml_dict["info"] = yaml_info

    yaml_file = yaml_dict["filename"]+".yaml"
    yaml.dump(yaml_dict, open(yaml_file, "w"), default_flow_style=False, Dumper=Dumper)
    print("saved yaml to {}".format(yaml_file))


if __name__ == "__main__":
    if len(sys.argv) > 1:
        json_file = sys.argv[1]
        print("input file: {}".format(json_file))
    else:
        json_file = "float_emb_format.json"

    convert_json_to_yaml(json_file)