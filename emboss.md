# Support Importing Emboss Files for Serialization/Deserialization Functions
This project is an example of how to import emboss files(emb file), convert the file into essential yaml file and generate cpp code with modified template.

## Setup
Note: This project requires Python3 and a modified input yaml file
1. Put the emboss file under the same directory of input yaml file
2. Edit import line in the yaml file to the name of emboss file
   **Example:**
   If float.emb is imported for serialization/deserialization functions, we need to edit line 33 in the [example.py](peripherals-yaml/example.yaml) file:  
   ```Yaml
   imports:
   	float: float.emb
   ```
3. Set up emboss environment `git clone https://github.com/google/emboss.git`
4. Change emboss directory in codegen.py to emboss path
   **Example:**
   If emboss folder is saved under the same directory as cyanobyte folder, we need to edit line 60 in the [codegen.py](cyanobyte/codegen.py) file:
   ```Python 
   base_path = "../emboss"
   ```
5. Run `python3 cyanobyte/codegen.py -t templates/raspberrypi.py -o build peripherals-yaml/example.yaml`
