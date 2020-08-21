"""
convert json file into yaml file
"""
import sys
import json
import copy
from collections import OrderedDict
import yaml

def extract_value(val_info, yaml_dict=None):
    """
    extract field value
    """
    res = None
    if "constant" in val_info:
        res = val_info["constant"]["value"]

    elif "constant_reference" in val_info:
        val_list = []
        for source_info in val_info["constant_reference"]["source_name"]:
            val_list.append(source_info["text"])
        res = ".".join(val_list)
        if yaml_dict is not None:
            if val_list[0] in yaml_dict["structs"] and\
                    val_list[1] in yaml_dict["structs"][val_list[0]]["fields"]:
                res_temp = yaml_dict["structs"][val_list[0]]
                res = res_temp["fields"][val_list[1]]["value"]
    return res

def process_enum(enum_info, yaml_struct_dict, yaml_dict):
    """
    process enum
    """
    yaml_struct_dict["fields"] = OrderedDict()
    for field_info in enum_info["enumeration"]["value"]:
        field_name = field_info["name"]["name"]["text"]
        if "constant" in field_info["value"]:
            field_val = extract_value(field_info["value"])

        elif "constant_reference" in field_info["value"]:
            field_val = extract_value(field_info["value"])

        elif "function" in field_info["value"]:
            arg_list = []
            for arg_info in field_info["value"]["function"]["args"]:
                arg_val = extract_value(arg_info, yaml_dict)
                arg_list.append(arg_val)
            function_temp = field_info["value"]["function"]
            function_symbol = function_temp["function_name"]["text"]
            field_val = {"symbol": function_symbol, "arg": arg_list}
        if isinstance(field_val, str) and\
                field_val in yaml_struct_dict["fields"]:
            field_val = yaml_struct_dict["fields"][field_val]["value"]
        yaml_struct_dict["fields"][field_name] = {"value": field_val}

def convert_json_to_yaml(content):
    """
    read in a json file and convert to yaml file
    """
    yaml_dict = {}

    source_file_full_name = content["module"][0]["source_file_name"]
    yaml_dict["filename"] = source_file_full_name.split("/")[-1]
    source_file_full_name_elem = [
        x.upper() for x in source_file_full_name.split("/")[:-1]]
    source_file_full_name_elem += [
        x.upper() for x in yaml_dict["filename"].split(".")]
    source_file_full_name_elem.append("H")
    yaml_dict["header_guard"] = "_".join(source_file_full_name_elem)

    yaml_dict["structs"] = {}
    struct_list = content["module"][0]["type"]
    for struct_info in struct_list:
        yaml_struct_dict = {}

        # e.g., Floats for floats, Doubles for doubles
        struct_name = struct_info["name"]["name"]["text"]
        yaml_dict["structs"][struct_name] = yaml_struct_dict

        if "enumeration" in struct_info:
            yaml_struct_dict["is_enum"] = True
            process_enum(struct_info, yaml_struct_dict, yaml_dict)
            continue

        if "structure" not in struct_info:
            del yaml_dict["structs"][struct_name]
            continue

        fields_list = struct_info["structure"]["field"]
        unit_in_bit = int(struct_info["addressable_unit"])

        yaml_struct_dict["fields"] = {}
        for field_info in fields_list:
            field_name = field_info["name"]["name"]["text"]
            if "$" in field_name:
                continue
            try:
                offset_in_unit = int(
                    field_info["location"]["start"]["constant"]["value"])
                size_in_unit = int(
                    field_info["location"]["size"]["constant"]["value"])
            except (ValueError, LookupError):
                if "read_transform" in field_info and \
                        "field_reference" in field_info["read_transform"]:
                    source_tmp = field_info["read_transform"]["field_reference"]
                    source_temp = source_tmp["path"][0]
                    source_name = source_temp["source_name"][0]["text"]
                    if source_name in yaml_struct_dict["fields"]:
                        yaml_struct_dict["fields"][field_name] = copy.deepcopy(
                            yaml_struct_dict["fields"][source_name])
                        del yaml_struct_dict["fields"][source_name]
                elif "read_transform" in field_info and \
                        "constant" in field_info["read_transform"]:
                    yaml_struct_dict["is_enum"] = True
                    temp = field_info["read_transform"]["constant"]["value"]
                    yaml_struct_dict["fields"][field_name] = {"value": temp}
                continue

            yaml_field_dict = {}
            yaml_struct_dict["fields"][field_name] = yaml_field_dict
            yaml_field_dict["offset_in_bit"] = int(offset_in_unit * unit_in_bit)
            yaml_field_dict["offset_in_byte"] = int(
                offset_in_unit * unit_in_bit / 8)
            yaml_field_dict["size_in_bit"] = int(size_in_unit * unit_in_bit)
            yaml_field_dict["size_in_byte"] = int(
                size_in_unit * unit_in_bit / 8)

        if len(yaml_struct_dict["fields"]) == 0:
            del yaml_dict["structs"][struct_name]

    return yaml_dict

if __name__ == "__main__":
    if len(sys.argv) > 1:
        json_file = sys.argv[1]
        print("input file: {}".format(json_file))
        content_file = json.load(open(json_file))
    else:
        content_file = json.loads(sys.stdin.read())

    yaml_dic = convert_json_to_yaml(content_file)

    yaml_file = yaml_dic["filename"]+".yaml"
    yaml.dump(
        yaml_dic,
        open(yaml_file, "w"),
        default_flow_style=False)
    print("saved yaml to {}".format(yaml_file))
