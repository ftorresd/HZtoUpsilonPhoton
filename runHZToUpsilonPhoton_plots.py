#!/usr/bin/env python

import os
import sys
import fileinput
from ROOT import *
from array import array
from multiprocessing import Pool 

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


command = sys.argv[1]
if (command == "run"):
	mcORdata = sys.argv[2]
	if (mcORdata == "Data"):
		sampleName = sys.argv[3]
		analysisBranch = sys.argv[3]
		category = sys.argv[4]


gSystem.AddIncludePath("-Iexternal");
gSystem.SetBuildDir("tmpdir", kTRUE);
gStyle.SetOptStat(0);

gROOT.ProcessLine(".L plugins/getFilesList.C+");
gROOT.ProcessLine(".L plots_ZtoUpsilonPhoton.C+");

def makeVector(list):
	listVec = vector('string')()
	for l in list:
		listVec.push_back(l)
	return listVec


# MuonEG
ntuplesToPlotFilesData = [
					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016B.root", 
					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016E.root", 
					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016G.root", 
					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016C.root", 
					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1.root", 
					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2.root", 
					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016D.root", 
					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2.root",  
					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3.root"
					]

# MuOnia
# ntuplesToPlotFilesData = [
# 					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016B.root", 
# 					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016C.root", 
# 					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016D.root", 
# 					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016E.root", 
# 					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016F.root", 
# 					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016G.root", 
# 					"outputFiles/outTree_ZtoUpsilonPhoton_Run2016H.root"
# 					]


samplesData = [
		# Higgs - Cat0
		[ntuplesToPlotFilesData, "Data", "HtoJPsi", "Cat0"],
		[ntuplesToPlotFilesData, "Data", "HtoUpsilon", "Cat0"],
		# Z - Cat0
		[ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat0"],
		[ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat0"],
		# Z - Cat1
		[ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat1"],
		[ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat1"],
		# Z - Cat2
		[ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat2"],
		[ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat2"],
		# Z - Cat3
		[ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat3"],
		[ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat3"],
	]

samplesMC = [
		# Higgs - Cat0
		[["outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon1SGamma.root"], "HToUpsilon1SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon2SGamma.root"], "HToUpsilon2SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon3SGamma.root"], "HToUpsilon3SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_HToJPsiGamma.root"], "HToJPsiGamma", "HtoJPsi", "Cat0", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_HDalitz.root"], "HDalitz", "HtoJPsi", "Cat0", "ZZZZZZ",  False, False],
		[["outputFiles/outTree_ZtoUpsilonPhoton_HDalitz.root"], "HDalitz", "HtoUpsilon", "Cat0", "ZZZZZZ",  False, False],
		# Z - Cat0
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root"], "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root"], "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"], "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma.root"], "ZToJPsiGamma", "ZtoJPsi", "Cat0", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"], "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat0", "ZZZZZZ",  False, False],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"], "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat0", "ZZZZZZ",  False, False],
		# Z - Cat1
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root"], "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root"], "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"], "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma.root"], "ZToJPsiGamma", "ZtoJPsi", "Cat1", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"], "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat1", "ZZZZZZ",  False, False],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"], "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat1", "ZZZZZZ",  False, False],
		# Z - Cat2
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root"], "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root"], "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"], "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma.root"], "ZToJPsiGamma", "ZtoJPsi", "Cat2", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"], "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat2", "ZZZZZZ",  False, False],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"], "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat2", "ZZZZZZ",  False, False],
		# Z - Cat3
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root"], "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root"], "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"], "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma.root"], "ZToJPsiGamma", "ZtoJPsi", "Cat3", "ZZZZZZ",  False, True],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"], "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat3", "ZZZZZZ",  False, False],
		[["outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"], "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat3", "ZZZZZZ",  False, False],
	]

def runPlotsMC(sample):
	plots_ZtoUpsilonPhoton(makeVector(sample[0]), sample[1], sample[2], sample[3], sample[4], sample[5], sample[6])

def runPlotsData(sample):
	plots_ZtoUpsilonPhoton(makeVector(sample[0]), sample[1], sample[2], sample[3])

# # clean up
# os.system("rm -rf outputHistos/*")
# os.system("rm -fr evtsCountFiles; mkdir evtsCountFiles")

# HISTOS AND TREES
# poolPlots = Pool(2) 
# resultsPlotsData = poolPlots.map(runPlotsData, samplesData)
# resultsPlotsMC = poolPlots.map(runPlotsMC, samplesMC)
# poolPlots.close() 
# poolPlots.join()
# map(runPlotsMC, samplesMC)
# map(runPlotsData, samplesData)

if (command == "submitLXBATCH"):
	# clean up
	os.system("bsub -R \"rusage[mem=32800]\" -R \"pool>30000\" -q 8nh -oo LSFPlotsJobs.out -eo LSFPlotsJobs.error -J Plots runHZToUpsilonPhoton_plots_LXBATCH.sh")
	exit()

if (command == "submit"):
	# clean up
	os.system("rm -rf outputHistos/*")
	os.system("rm -fr evtsCountFiles; mkdir evtsCountFiles")
	os.system("./runHZToUpsilonPhoton_plots.py run MC > runPlotsMC.log 2> /dev/null ")
	for s in samplesData:
		# os.system("./runHZToUpsilonPhoton_plots.py run Data "+s[2]+ " "+ s[3] + " > runPlotsData_" + s[2] + "_" + s[3] + ".log 2>&1 &")
		pass
	exit()
	

if (command == "run"):
	if (mcORdata == "MC"):
		poolPlots = Pool() 
		# resultsPlotsData = poolPlots.map(runPlotsData, samplesData)
		resultsPlotsMC = poolPlots.map(runPlotsMC, samplesMC)
		poolPlots.close() 
		poolPlots.join()
	if (mcORdata == "Data"):
		sample = filter(lambda x: (x[1] == mcORdata and x[2] == analysisBranch and x[3] == category), samplesData)[0]
		plots_ZtoUpsilonPhoton(makeVector(sample[0]), sample[1], sample[2], sample[3])
	exit()



if (command == "checkData"):
	samplesSource = samplesData
	reSubmitStr = ""
	for sample in samplesSource:
		isGood = False
		try:
			with open("runPlotsData_" + sample[2] + "_" + sample[3] + ".log", 'r') as out_file:
				lastLine = ""
				for line in out_file:
					lastLine = line.rstrip()
					if (line.rstrip() == "Writing output file: (Data - "+sample[2]+" - "+sample[3]+" - ZZZZZZ)"):
						isGood = True
		except IOError:
			isGood = False
		if isGood:
			print bcolors.OKGREEN + "----> Sample ("+sample[2]+" - "+sample[3]+"): OK"+ bcolors.ENDC
		else:
			print bcolors.FAIL + "----> Sample ("+sample[2]+" - "+sample[3]+"): FAIL"+ bcolors.ENDC
			reSubmitStr += "rm -rf outputHistos/out*_HZtoUpsilonPhoton_Data_"+sample[2]+"_"+sample[3]+"_ZZZZZZ.root; ./runHZToUpsilonPhoton_plots.py run Data "+sample[2]+ " "+ sample[3] + " > runPlotsData_" + sample[2] + "_" + sample[3] + ".log 2>&1 &\n"
		if (isGood == False):
			print "Last line:"
			print lastLine+"\n"
	print "\n\nResubmit command:"
	print reSubmitStr
	exit()



if (command == "collect"):
	# Merge Z Fit Trees and Histograms
	os.system("hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root")
	os.system("hadd -f outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root")

	os.system("hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root")
	os.system("hadd -f outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root")

	os.system("hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root")
	os.system("hadd -f outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root")

	os.system("hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root")
	os.system("hadd -f outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root")

	# Merge Higgs Fit Trees and Histograms
	os.system("hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilon2SGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilon3SGamma_HtoUpsilon_Cat0_ZZZZZZ.root")
	os.system("hadd -f outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilon2SGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilon3SGamma_HtoUpsilon_Cat0_ZZZZZZ.root")


	# os.system("rm outputHistos/*_PZZZZZ.root")
	# os.system("rm outputHistos/*_MZZZZZ.root")
	# os.system("rm outputHistos/*_ZPZZZZ.root")
	# os.system("rm outputHistos/*_ZMZZZZ.root")
	# os.system("rm outputHistos/*_ZZPZZZ.root")
	# os.system("rm outputHistos/*_ZZMZZZ.root")
	# os.system("rm outputHistos/*_ZZZPZZ.root")
	# os.system("rm outputHistos/*_ZZZMZZ.root")
	# os.system("rm outputHistos/*_ZZZZPZ.root")
	# os.system("rm outputHistos/*_ZZZZMZ.root")
	# os.system("rm outputHistos/*_ZZZZZP.root")
	# os.system("rm outputHistos/*_ZZZZZM.root")


	os.system("python systematicsYields_HZtoUpsilonPhoton.py")
	os.system("python dumpEvtCountsAndSyst_HZtoUpsilonPhoton.py")
	exit()


