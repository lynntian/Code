import Share

import os.path
import json
import shutil
import subprocess
import fileinput
import sys

### inJsonFile is input json with folder locaiton #"outData.json"
### mode is either "updatespec" or "pack"
def NuspecUpdateAndPack(inJsonFile, mode):
	#input file Current dir, outData.json
	inputJsonData = Share.readJson(inJsonFile)
	out = updateNuspecAndPack(inputJsonData, mode)


#####################################################
#!!!!!TODO output nuget pack locaiton
def updateNuspecAndPack(jdata, mode):
	outNugetPackageLocaltion = []
	for j in jdata:
		out = {}
		if mode == "updatespec":
			openNuspecAndUpdate(j["specFile"])
		
		#update version number in nuspec files before packing!!!
		if mode == "pack":
			subprocess.call(["nuget", "pack", j["specFile"], "-NoPackageAnalysis"], cwd=j["UnzipFolder"])
	return outNugetPackageLocaltion


def openNuspecAndUpdate(nuspecFileName):
	idnum = os.path.basename(nuspecFileName)
	idnum = os.path.splitext(idnum)[0]
	for line in fileinput.input(nuspecFileName, inplace=1):
		oriline = line.rstrip()
		line = line.strip()
		if line.startswith("<?xml version") or line.startswith("<package") or line.startswith("<metadata") or line.startswith("<version>"):
			print oriline
		elif line.startswith("<id>"):
			print "  <id>" + idnum+"</id>"
		elif line.startswith("<authors>"):
			print "    <authors>Autodesk</authors>"
		elif line.startswith("<owners>"):
			print "    <owners>Autodesk</owners>"
		elif line.startswith("<licenseUrl>") or line.startswith("<projectUrl>") or line.startswith("<iconUrl>"):
			continue
		elif line.startswith("<requireLicenseAcceptance>"):
			print oriline
		elif line.startswith("<description>"):
			print "    <description>" + idnum+"</description>"
		elif line.startswith("<releaseNotes>"):
			print "    <releaseNotes>None</releaseNotes>"
		elif line.startswith("<copyright>"):
			print "    <copyright>Copyright Autodesk 2016</copyright>"
		elif line.startswith("<tags>"):
			print "    <tags>" + idnum + " 2016</tags>"
		elif line.startswith("<dependencies>") or line.startswith("</dependencies>") or line.startswith("</package>"):
			print oriline
		elif line.startswith("</metadata>"):
			print oriline
			print "  <files>\n    <file src=\"**\" />\n  </files>"
		elif line.startswith("<dependency id"):
			continue

#####################################################

if __name__ == '__main__':
	NuspecUpdateAndPack(sys.argv[1], sys.argv[2])