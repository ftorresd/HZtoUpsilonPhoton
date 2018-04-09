#!/usr/bin/env python


def splitter (fileName):
	fileNamePrefix = fileName.replace(".txt", "")
	number_of_files = 10
	with open(fileName) as infp:
	    files = [open(fileNamePrefix+'_%d.txt' % i, 'w') for i in range(number_of_files)]
	    for i, line in enumerate(infp):
	        files[i % number_of_files].write(line)
	    for f in files:
	        f.close()


files = [
		"job_MuEG_Run2016B_FebReminiAOD.txt",
		"job_MuEG_Run2016C_FebReminiAOD.txt",
		"job_MuEG_Run2016D_FebReminiAOD.txt",
		"job_MuEG_Run2016E_FebReminiAOD.txt",
		"job_MuEG_Run2016F_FebReminiAOD1.txt",
		"job_MuEG_Run2016F_FebReminiAOD2.txt",
		"job_MuEG_Run2016G_SepRereco.txt",
		"job_MuEG_Run2016H_PRv2.txt",
		"job_MuEG_Run2016H_PRv3.txt",
		]

# for f in files:
# 	splitter(f)



lista = """
	["filesLists/filesFromEOS/Data2016/job_MuEG_Run2016B_FebReminiAOD.txt", "Run2016B"],
	["filesLists/filesFromEOS/Data2016/job_MuEG_Run2016C_FebReminiAOD.txt", "Run2016C"],
	["filesLists/filesFromEOS/Data2016/job_MuEG_Run2016D_FebReminiAOD.txt", "Run2016D"],
	["filesLists/filesFromEOS/Data2016/job_MuEG_Run2016E_FebReminiAOD.txt", "Run2016E"],
	["filesLists/filesFromEOS/Data2016/job_MuEG_Run2016F_FebReminiAOD1.txt", "Run2016F1"],
	["filesLists/filesFromEOS/Data2016/job_MuEG_Run2016F_FebReminiAOD2.txt", "Run2016F2"],
	["filesLists/filesFromEOS/Data2016/job_MuEG_Run2016G_SepRereco.txt", "Run2016G"],
	["filesLists/filesFromEOS/Data2016/job_MuEG_Run2016H_PRv2.txt", "Run2016H2"],
	["filesLists/filesFromEOS/Data2016/job_MuEG_Run2016H_PRv3.txt", "Run2016H3"],
"""

for f in lista.splitlines():
	for i in range(10):
		print f.replace(".txt", "_"+str(i)+".txt").replace("\"],", "_"+str(i)+"\"],")
