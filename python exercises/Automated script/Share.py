import os.path
import json
from pprint import pprint
import shutil
import subprocess
import sys
import fileinput


##Util methods: 
###############
def readJson(file):
    with open(file) as jsonData:
        data = json.load(jsonData)
    return data




###############

## 

