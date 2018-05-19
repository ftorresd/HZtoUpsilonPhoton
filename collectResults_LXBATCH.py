#!/usr/bin/env python

import os
import sys

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


source = sys.argv[1]
arg = sys.argv[2]


samplesDataToMerge = [
	"Run2016B",
	"Run2016C",
	"Run2016D",
	"Run2016E",
	"Run2016F1",
	"Run2016F2",
	"Run2016G",
	"Run2016H2",
	"Run2016H3",
	]

samplesData = [
	"Run2016B_0",
	"Run2016B_1",
	"Run2016B_2",
	"Run2016B_3",
	"Run2016B_4",
	"Run2016B_5",
	"Run2016B_6",
	"Run2016B_7",
	"Run2016B_8",
	"Run2016B_9",
	"Run2016C_0",
	"Run2016C_1",
	"Run2016C_2",
	"Run2016C_3",
	"Run2016C_4",
	"Run2016C_5",
	"Run2016C_6",
	"Run2016C_7",
	"Run2016C_8",
	"Run2016C_9",
	"Run2016D_0",
	"Run2016D_1",
	"Run2016D_2",
	"Run2016D_3",
	"Run2016D_4",
	"Run2016D_5",
	"Run2016D_6",
	"Run2016D_7",
	"Run2016D_8",
	"Run2016D_9",
	"Run2016E_0",
	"Run2016E_1",
	"Run2016E_2",
	"Run2016E_3",
	"Run2016E_4",
	"Run2016E_5",
	"Run2016E_6",
	"Run2016E_7",
	"Run2016E_8",
	"Run2016E_9",
	"Run2016F1_0",
	"Run2016F1_1",
	"Run2016F1_2",
	"Run2016F1_3",
	"Run2016F1_4",
	"Run2016F1_5",
	"Run2016F1_6",
	"Run2016F1_7",
	"Run2016F1_8",
	"Run2016F1_9",
	"Run2016F2_0",
	"Run2016F2_1",
	"Run2016F2_2",
	"Run2016F2_3",
	"Run2016F2_4",
	"Run2016F2_5",
	"Run2016F2_6",
	"Run2016F2_7",
	"Run2016F2_8",
	"Run2016F2_9",
	"Run2016G_0",
	"Run2016G_1",
	"Run2016G_2",
	"Run2016G_3",
	"Run2016G_4",
	"Run2016G_5",
	"Run2016G_6",
	"Run2016G_7",
	"Run2016G_8",
	"Run2016G_9",
	"Run2016H2_0",
	"Run2016H2_1",
	"Run2016H2_2",
	"Run2016H2_3",
	"Run2016H2_4",
	"Run2016H2_5",
	"Run2016H2_6",
	"Run2016H2_7",
	"Run2016H2_8",
	"Run2016H2_9",
	"Run2016H3_0",
	"Run2016H3_1",
	"Run2016H3_2",
	"Run2016H3_3",
	"Run2016H3_4",
	"Run2016H3_5",
	"Run2016H3_6",
	"Run2016H3_7",
	"Run2016H3_8",
	"Run2016H3_9",
	]

samplesMC = [
	"ZToUpsilon1SGamma",
	"ZToUpsilon2SGamma",
	"ZToUpsilon3SGamma",
	"ZToJPsiGamma",
	"HToUpsilon1SGamma",
	"HToUpsilon2SGamma",
	"HToUpsilon3SGamma",
	"HToJPsiGamma",
	"HDalitz",
	"ZGTo2MuG_MMuMu-2To15",
	]

shapeSystMasks = []
if (source == "MC"):
	shapeSystMasks = [
		"default",
		# "statRocCorError_UP",
		# "statRocCorError_DOWN",
		# "refRocCorError_UP",
		# "refRocCorError_DOWN",
		# "profMassRocCorError_UP",
		# "profMassRocCorError_DOWN",
		# "fitMassRocCorError_UP",
		# "fitMassRocCorError_DOWN",
		"RocCorError_UP",
		"RocCorError_DOWN",
		"phoScale_stat_UP",
		"phoScale_stat_DOWN",
		"phoScale_syst_UP",
		"phoScale_syst_DOWN",
		"phoScale_gain_UP",
		"phoScale_gain_DOWN",
		"phoResol_rho_UP",
		"phoResol_rho_DOWN",
		"phoResol_phi_UP",
		"phoResol_phi_DOWN",
		]

if (source == "Data"):
	shapeSystMasks = ["default",]



# os.system("rm -rf LSFJobs/ ; mkdir LSFJobs")
os.system("mv LSFJobs_*_* LSFJobs/.  > /dev/null 2>&1")

samplesSource = []
if (source == "MC"):
	samplesSource = samplesMC
if (source == "Data"):
	samplesSource = samplesData

if (arg == "check"):
	reSubmitStr = ""
	for sample in samplesSource:
		for shape in shapeSystMasks:
			isGood = False
			try:
				with open("LSFJobs/LSFJobs_"+source+"_"+sample+"_"+shape+".out", 'r') as out_file:
					for line in out_file:
						if (line.rstrip() == "Writing output file... ("+sample+")"):
							isGood = True
			except IOError:
				isGood = False
			if (os.system("ls -lha ../outTree_ZtoUpsilonPhoton_"+sample+"_"+shape+".root  > /dev/null 2>&1") == 0):
				if (os.path.getsize("../outTree_ZtoUpsilonPhoton_"+sample+"_"+shape+".root") >= 10*1024*1024):
					isGood = True * isGood
			else:
				isGood = False 
			if isGood:
				print bcolors.OKGREEN + "----> Sample ("+sample+" - "+shape+"): OK"+ bcolors.ENDC
			else:
				print bcolors.FAIL + "----> Sample ("+sample+" - "+shape+"): FAIL"+ bcolors.ENDC
				queue = "8nh"
				if (source == "Data"):
					queue = "8nh"
				reSubmitStr += "bsub -R \"rusage[mem=32800]\" -R \"pool>30000\" -q "+queue+" -oo LSFJobs_MC_"+sample+"_"+shape+".out -eo LSFJobs_MC_"+sample+"_"+shape+".error -J MC_" + sample + "_"+shape+" runHZToUpsilonPhoton_ana_LXBATCH.sh MC " + sample + " " + shape +"\n"
	print "\n\nResubmit command:"
	print reSubmitStr


if (arg == "merge"): 
	# os.system("rm -rf outputFiles/*  > /dev/null 2>&1")
	for sample in samplesSource:
		for shape in shapeSystMasks:
			os.system("cp ../outTree_ZtoUpsilonPhoton_"+sample+"_"+shape+".root outputFiles/.")	
	os.system("rm -rf outputFiles/._out*root ")
	if (source == "MC"):
		for sample in samplesSource:
			haddStr =  "hadd -f -O outputFiles/outTree_ZtoUpsilonPhoton_"+sample+".root "
			for shape in shapeSystMasks:
				haddStr += " outputFiles/outTree_ZtoUpsilonPhoton_"+sample+"_"+shape+".root"
			# os.system(haddStr)
			# for shape in shapeSystMasks:
				# os.system("rm outputFiles/outTree_ZtoUpsilonPhoton_"+sample+"_"+shape+".root")
	if (source == "Data"):
		for sample in samplesDataToMerge:
			haddStr =  "hadd -f -O outputFiles/outTree_ZtoUpsilonPhoton_"+sample+".root "
			for i in range(10):
				haddStr += " outputFiles/outTree_ZtoUpsilonPhoton_"+sample+"_"+str(i)+"_default.root"
				os.system("mv outputFiles/outTree_ZtoUpsilonPhoton_"+sample+"_"+str(i)+"_default.root outputFiles/outTree_ZtoUpsilonPhoton_"+sample+"_"+str(i)+".root")
			# os.system(haddStr)
			# os.system("mv outputFiles/outTree_ZtoUpsilonPhoton_"+sample+"_"+str(i)+"_default.root outputFiles/outTree_ZtoUpsilonPhoton_"+sample+"_"+str(i)+".root")




