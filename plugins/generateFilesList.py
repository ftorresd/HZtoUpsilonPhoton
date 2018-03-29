import glob
import os

os.system ("rm -rf filesListsOniaTriggers ; mkdir -p filesListsOniaTriggers/fromEOS")
os.system ("mkdir -p filesListsOniaTriggers/fromUERJPOWER")

#Data
erasList = ["B", "C", "D", "E", "F", "G", "H"]
for era in erasList:
	fileList = glob.glob("/afs/cern.ch/user/f/ftorresd/workSpace/public/UERJPower_Storage1/HZtoUpsilonPlusPhotonSamples2016/MuOnia/MuOnia/MuOnia_Run2016"+era+"*/*/*/ggtree_data_*root")
	filesStr = "\n".join(fileList)
	with open("filesListsOniaTriggers/fromUERJPOWER/MuOnia_Run2016"+era+".txt", 'w') as out_file:
		out_file.write(filesStr)

#MC
samplesList = [
	"HToJPsiGamma", 
	"HToUpsilon1SGamma", 
	"HToUpsilon2SGamma", 
	"HToUpsilon3SGamma", 
	"ZToJPsiGamma", 
	"ZToUpsilon1SGamma", 
	"ZToUpsilon2SGamma", 
	"ZToUpsilon3SGamma",
	"ZGTo2MuG_MMuMu-2To15",
	]
for sample in samplesList:
	fileList = glob.glob("/afs/cern.ch/user/f/ftorresd/workSpace/public/UERJPower_Storage1/HZtoUpsilonPlusPhotonSamples2016/MC/"+sample+"*/*/*/*/*/*.root")
	filesStr = "\n".join(fileList)
	with open("filesListsOniaTriggers/fromUERJPOWER/MC_"+sample+".txt", 'w') as out_file:
		out_file.write(filesStr)


#Data
erasList = ["B", "C", "D", "E", "F", "G", "H"]
for era in erasList:
	fileList = glob.glob("/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MuOnia/MuOnia_Run2016"+era+"*/*/*/*/*/*.root")
	filesStr = "\n".join(fileList)
	fileList = [file.replace('/eos','root://eoscms//eos') for file in fileList]
	with open("filesListsOniaTriggers/fromEOS/MuOnia_Run2016"+era+".txt", 'w') as out_file:
		out_file.write(filesStr)

#MC
samplesList = [
	"HToJPsiGamma", 
	"HToUpsilon1SGamma", 
	"HToUpsilon2SGamma", 
	"HToUpsilon3SGamma", 
	"ZToJPsiGamma", 
	"ZToUpsilon1SGamma", 
	"ZToUpsilon2SGamma", 
	"ZToUpsilon3SGamma",
	"ZGTo2MuG_MMuMu-2To15",
	]
for sample in samplesList:
	fileList = glob.glob("/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/"+sample+"*/*/*/*/*/*.root")
	fileList = [file.replace('/eos','root://eoscms//eos') for file in fileList]
	filesStr = "\n".join(fileList)
	with open("filesListsOniaTriggers/fromEOS/MC_"+sample+".txt", 'w') as out_file:
		out_file.write(filesStr)



