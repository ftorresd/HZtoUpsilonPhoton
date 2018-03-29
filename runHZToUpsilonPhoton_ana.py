#!/usr/bin/env python

import os
import fileinput
from ROOT import *
from multiprocessing import Pool 


gSystem.AddIncludePath("-Iexternal");
gSystem.SetBuildDir("tmpdir", kTRUE);
gStyle.SetOptStat(0);
gROOT.ProcessLine(".L plugins/getFilesList.C+"); 


filesData_MuOnia = [
	["filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016B.txt", "Run2016B"],
	["filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016C.txt", "Run2016C"],
	["filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016D.txt", "Run2016D"],
	["filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016E.txt", "Run2016E"],
	["filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016F.txt", "Run2016F"],
	["filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016G.txt", "Run2016G"],
	["filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016H.txt", "Run2016H"],
	]


filesMC_MuOnia = [
	["filesLists/filesListsOniaTriggers/fromEOS/MC_HToJPsiGamma.txt", "HToJPsiGamma", "puWeight/pu_HToJPsiGamma_MuOniaTriggers.root"],
	["filesLists/filesListsOniaTriggers/fromEOS/MC_HToUpsilon1SGamma.txt", "HToUpsilon1SGamma", "puWeight/pu_HToUpsilon1SGamma_MuOniaTriggers.root"],
	["filesLists/filesListsOniaTriggers/fromEOS/MC_HToUpsilon2SGamma.txt", "HToUpsilon2SGamma", "puWeight/pu_HToUpsilon2SGamma_MuOniaTriggers.root"],
	["filesLists/filesListsOniaTriggers/fromEOS/MC_HToUpsilon3SGamma.txt", "HToUpsilon3SGamma", "puWeight/pu_HToUpsilon3SGamma_MuOniaTriggers.root"],
	["filesLists/filesListsOniaTriggers/fromEOS/MC_ZGTo2MuG_MMuMu-2To15.txt", "ZGTo2MuG_MMuMu-2To15", "puWeight/pu_ZGTo2MuG_MMuMu-2To15_MuOniaTriggers.root"],
	["filesLists/filesListsOniaTriggers/fromEOS/MC_ZToJPsiGamma.txt", "ZToJPsiGamma", "puWeight/pu_ZToJPsiGamma_MuOniaTriggers.root"],
	["filesLists/filesListsOniaTriggers/fromEOS/MC_ZToUpsilon1SGamma.txt", "ZToUpsilon1SGamma", "puWeight/pu_ZToUpsilon1SGamma_MuOniaTriggers.root"],
	["filesLists/filesListsOniaTriggers/fromEOS/MC_ZToUpsilon2SGamma.txt", "ZToUpsilon2SGamma", "puWeight/pu_ZToUpsilon2SGamma_MuOniaTriggers.root"],
	["filesLists/filesListsOniaTriggers/fromEOS/MC_ZToUpsilon3SGamma.txt", "ZToUpsilon3SGamma", "puWeight/pu_ZToUpsilon3SGamma_MuOniaTriggers.root"],
	["filesLists/filesListsOniaTriggers/fromEOS/MC_HDalitz.txt", "HDalitz", "puWeight/pu_HDalitz_MuOniaTriggers.root"],
	]

filesData_MuonEG = [
	["filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016B_FebReminiAOD.txt", "Run2016B"],
	["filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016C_FebReminiAOD.txt", "Run2016C"],
	["filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016D_FebReminiAOD.txt", "Run2016D"],
	["filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016E_FebReminiAOD.txt", "Run2016E"],
	["filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016F_FebReminiAOD1.txt", "Run2016F1"],
	["filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016F_FebReminiAOD2.txt", "Run2016F2"],
	["filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016G_SepRereco.txt", "Run2016G"],
	["filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016H_PRv2.txt", "Run2016H2"],
	["filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016H_PRv3.txt", "Run2016H3"],
	]


filesMC_MuonEG = [
	["filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon1SGamma.txt", "ZToUpsilon1SGamma", "puWeight/pu_ZToUpsilon1SGamma.root"],
	["filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon2SGamma.txt", "ZToUpsilon2SGamma", "puWeight/pu_ZToUpsilon2SGamma.root"],
	["filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon3SGamma.txt", "ZToUpsilon3SGamma", "puWeight/pu_ZToUpsilon3SGamma.root"],
	["filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToJPsiGamma.txt", "ZToJPsiGamma", "puWeight/pu_ZToJPsiGamma.root"],
	["filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon1SGamma.txt", "HToUpsilon1SGamma", "puWeight/pu_HToUpsilon1SGamma.root"],
	["filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon2SGamma.txt", "HToUpsilon2SGamma", "puWeight/pu_HToUpsilon2SGamma.root"],
	["filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon3SGamma.txt", "HToUpsilon3SGamma", "puWeight/pu_HToUpsilon3SGamma.root"],
	["filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToJPsiGamma.txt", "HToJPsiGamma", "puWeight/pu_HToJPsiGamma.root"],
	["filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HDalitz.txt", "HDalitz", "puWeight/pu_HDalitz.root"],
	["filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZGTo2MuG_MMuMu-2To15.txt", "ZGTo2MuG_MMuMu-2To15", "puWeight/pu_ZGTo2MuG_MMuMu-2To15.root"],
	]









for line in fileinput.input("ana_ZtoUpsilonPhoton.C", inplace = 1):
	print line.replace("//#define IS_MC 1", "#define IS_MC 1"),


gROOT.ProcessLine(".L ana_ZtoUpsilonPhoton.C+");

def runAnaMC(file):
	ana_ZtoUpsilonPhoton(getFilesList(file[0]), -1, file[1], True, file[2]);

pool = Pool() 
results = pool.map(runAnaMC, filesMC_MuonEG)
pool.close() 
pool.join()

gROOT.ProcessLine(".U ana_ZtoUpsilonPhoton.C"); 







for line in fileinput.input("ana_ZtoUpsilonPhoton.C", inplace = 1):
	print line.replace("#define IS_MC 1", "//#define IS_MC 1"),


gROOT.ProcessLine(".L ana_ZtoUpsilonPhoton.C+");


def runAnaData(file):
	ana_ZtoUpsilonPhoton(getFilesList(file[0]), -1, file[1]);

pool = Pool() 
results = pool.map(runAnaData, filesData_MuonEG)
pool.close() 
pool.join()




for line in fileinput.input("ana_ZtoUpsilonPhoton.C", inplace = 1):
	print line.replace("//#define IS_MC 1", "#define IS_MC 1"),


