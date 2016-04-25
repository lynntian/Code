import os.path
import json
from pprint import pprint
import sys

### read LibVersion.txt
### parse and dump json file for automate script to use

def parseLibVersion(libversionPath, dumpFileName):

	if os.path.isfile(libversionPath)
		#lib = "LibVersions.txt"
		readFile(libversionPath, dumpFileName);
	else
		print "File " + libversionPath + " not exist!"


############################################
def readFile(infilePath,dumpFileName):
	f = open(infilePath, 'r')
	jdata = parseFile(f)
	pprint(jdata)
	f.close()
	outTestFile = dumpFileName #= "D:\\Temp\\TestJsonDump.json"
	try:
		jfile = open(outTestFile, "w+")
		json.dump(jdata, jfile, indent=4)
		jfile.close()
	except:
		print("Can't create file")

def parseFile(file):
	out = []
	temparr = []
	block = []

	for line in file:
		line = line.rstrip()
		if line: #only process lines with content
			block.append(line)

		else:
			temparr.append(block)
			block = []

	for a in temparr:
		if(len(a) != 6):
			continue
		data = {}
		data["name"] = a[0][1:-1]
		data["NetShare"] = a[1][9:]
		data["Source"] = a[2][7:]
		data["Target"] = a[3][7:]
		data["EraseFolder"] = a[4][12:]
		data["PostP4"] = a[5][7:]
		out.append(data)
	return out

############################################

if __name__ == '__main__':
	parseLibVersion(sys.argv[1])