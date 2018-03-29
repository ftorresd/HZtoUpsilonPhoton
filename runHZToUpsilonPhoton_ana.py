#!/usr/bin/env python

import os

from multiprocessing import Pool as ThreadPool 
# from multiprocessing.dummy import Pool as ThreadPool 


fileHeader = '''
{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	gROOT->ProcessLine(".L plugins/getFilesList.C+");
	gROOT->ProcessLine(".L ana_ZtoUpsilonPhoton.C+"); 
	gStyle->SetOptStat(0);

'''

fileBotton = '''
}

'''
filesMC = [
	"filesLists/filesListsOniaTriggers/fromEOS/MC_HToJPsiGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_HToUpsilon1SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_HToUpsilon2SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_HToUpsilon3SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_ZGTo2MuG_MMuMu-2To15.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_ZToJPsiGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_ZToUpsilon1SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_ZToUpsilon2SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_ZToUpsilon3SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_HDalitz.txt",
	]

filesData = [
	"filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016B.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016C.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016D.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016E.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016F.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016G.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MuOnia_Run2016H.txt",
	]





# MC
# Dummy
# dummyStringMC = "ana_ZtoUpsilonPhoton(getFilesList(\""+filesMC[0]+"\") , 1, \"DummyMC\", true, \"puWeight/pu_DummyMC.root\");"
with open( "run_AnaTemp_DummyMC.C", "w") as fileDummy:
    fileDummy.write(fileHeader+fileBotton)
os.system("root -b -q -l run_AnaTemp_DummyMC.C+ ")

def runAnaMC(file):
	sampleString = file.replace("filesLists/filesListsOniaTriggers/fromEOS/MC_", "").replace(".txt", "")
	execString = "ana_ZtoUpsilonPhoton(getFilesList(\""+file+"\"), -1, \""+sampleString+"\", true, \"puWeight/pu_"+sampleString+"_MuOniaTriggers.root\");"
	with open( "run_AnaTemp_"+sampleString+".C", "w") as anaTempFile:
	    anaTempFile.write(fileHeader+execString+fileBotton)
	os.system("root -b -q -l run_AnaTemp_"+sampleString+".C+")

pool = ThreadPool(len(filesMC)) 
results = pool.map(runAnaMC, filesMC)

pool.close() 
pool.join()






# # Data
# # Dummy
# # dummyStringMC = "ana_ZtoUpsilonPhoton(getFilesList(\""+filesData[0]+"\") , 1, \"DummyData\");"
# with open( "run_AnaTemp_DummyData.C", "w") as fileDummy:
#     fileDummy.write(fileHeader+fileBotton)
# os.system("root -b -q -l run_AnaTemp_DummyData.C+ ")

# def runAnaData(file):
# 	sampleString = file.replace("filesLists/filesListsOniaTriggers/fromEOS/MuOnia_", "").replace(".txt", "")
# 	execString = "ana_ZtoUpsilonPhoton(getFilesList(\""+file+"\"), -1, \""+sampleString+"\");"
# 	with open( "run_AnaTemp_"+sampleString+".C", "w") as anaTempFile:
# 	    anaTempFile.write(fileHeader+execString+fileBotton)
# 	os.system("root -b -q -l run_AnaTemp_"+sampleString+".C+")


# # pool = ThreadPool(len(filesData)) 
# pool = ThreadPool() 
# results = pool.map(runAnaData, filesData)

# pool.close() 
# pool.join()









os.system("rm -rf run_AnaTemp*.C")




