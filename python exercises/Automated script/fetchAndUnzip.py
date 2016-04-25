import Share

import os.path
import json
from pprint import pprint
import shutil
import subprocess
import sys

###TargetDir is where all zip files will be copied to & unziped and packed again by nuget # "D:\\Temp\\"
###netshareChoice is the tag wether use "Project" or "BuildComponents" #Project
###inputDumpJson is the json file we created with parseLibVersion.py, contain json objects #"D:\\Temp\\TestJsonDump.json"
###postP4 is the tag wether to use PostP4=True of PostP4=False
def fetchAndUnzip(targetDir, inputDumpJson, netshareChoice, postP4):
	
	outData = processjson(inputDumpJson, targetDir, netshareChoice, postP4)
	#pprint(outData)
	outJsonFileName = targetDir + "outData.json"
	try:
		jfile = open(outJsonFileName, "w+")
		json.dump(outData, jfile, indent=4)
		jfile.close()
	except:
		print("Can't create file")

	# call the next python script to create nuspec file and update content.
	os.system("NuspecUpdateAndPack.py " + outJsonFileName + " " + "updatespec")

#---------------------------------

def processjson(inputDumpJson, targetDir, netshareChoice, postP4,):
	netsharePath = "\\\mannas1\AIM" if netshareChoice.lower() == "Project".lower() else "\\\mannas1\BuildComponents"

	jd = Share.readJson(inputDumpJson)

	print(len(jd))
	outData = []
	for j in jd:
		## Only process netShare == project AND postP4 == true
		if(j["NetShare"].lower() != netshareChoice.lower() or j["PostP4"].lower() != postP4.lower()):
			continue

		out = {}
		sourceLocation = os.path.join(netsharePath, j["Source"])
		baseName = os.path.basename(sourceLocation)

		targetLocation = os.path.join(targetDir, baseName)

		if not os.path.exists(os.path.dirname(targetLocation)):
			try:
				os.makedirs(os.path.dirname(targetLocation))
			except OSError as exc:
				if exc.errno != errno.EEXIST:
					riase
		shutil.copy2(sourceLocation, targetLocation)

		baseFolder = os.path.splitext(baseName)[0]
		print(baseFolder)
		unzipFolderDir = os.path.join(targetDir, baseFolder) # unzip foler might need to use j["target"]
		print(unzipFolderDir)
		#create folders for unzip
		if os.path.exists(unzipFolderDir):
			shutil.rmtree(unzipFolderDir)
		os.makedirs(unzipFolderDir)

		out["UnzipFolder"] = unzipFolderDir

		subprocess.call(["7z", "x", targetLocation, "-o"+ unzipFolderDir, "-y"] )

		#create nuspec file
		subprocess.call(["nuget", "spec", os.path.join(unzipFolderDir, baseFolder)])
		out["specFile"] = os.path.join(unzipFolderDir, baseFolder) + ".nuspec"
		outData.append(out)
	return outData

if __name__ == '__main__':
  fetchAndUnzip(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]) # targetDir, inputDumpJson, netshareChoice, postP4
