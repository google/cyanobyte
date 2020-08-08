#Support Importing Emboss Files for Serialization/Deserialization Functions
This project is an example of how to import emboss files(emb file), convert the file into essential yaml file and generate cpp code with modified template.

##Setup
Note: This project requires Python3 and a modified input yaml file
###Step1
Put the emboss file under the same directory of input yaml file
###Step2
Edit import line in the yaml file to the name of emboss file
###Step3
Set up emboss environment `git clone https://github.com/google/emboss.git`
###Step4
Change emboss directory in codegen.py to emboss path
##Step5
Run `python3 cyanobyte/codegen.py -t templates/raspberrypi.py -o build peripherals-yaml/example.yaml`
