#!/usr/bin/env python

import json

def getSysterror(nominal, up, down):
	diff_up = up - nominal
	diff_down = down - nominal
	max_diff = max(abs(diff_down), abs(diff_up))
	# return float(format(max_diff/nominal*100, '.2f'))
	return max_diff/nominal*100.0




############################################################
# <BEGIN> Higgs to Upsilon + Photon - MERGE
# Merge Higgs Upsilon files
HtoUpsilonSystMasks = [
				"ZZZZZ", 
				"PZZZZ", 
				"MZZZZ", 
				"ZPZZZ", 
				"ZMZZZ", 
				"ZZPZZ", 
				"ZZMZZ", 
				"ZZZPZ", 
				"ZZZMZ", 
				"ZZZZP", 
				"ZZZZM", 
				]
for hMask in HtoUpsilonSystMasks:
	H1SFile = open("evtsCountFiles/evtsCountFile_HToUpsilon1SGamma_HtoUpsilon_Cat0_"+hMask+".json","r")
	H2SFile = open("evtsCountFiles/evtsCountFile_HToUpsilon2SGamma_HtoUpsilon_Cat0_"+hMask+".json","r")
	H3SFile = open("evtsCountFiles/evtsCountFile_HToUpsilon3SGamma_HtoUpsilon_Cat0_"+hMask+".json","r")
	H1SJSON = json.load(H1SFile)
	H2SJSON = json.load(H2SFile)
	H3SJSON = json.load(H3SFile)
	with open("evtsCountFiles/evtsCountFile_HToUpsilonGamma_HtoUpsilon_Cat0_"+hMask+".json", "w") as outputHJSONFile:  
	    outputHJSONFile.write("{\n")
	    outputHJSONFile.write("\"sample\" : \"HToUpsilonGamma\",\n")
	    outputHJSONFile.write("\"analysisBranch\" : \"HtoUpsilon\",\n")
	    outputHJSONFile.write("\"selCategory\" : \"Cat0\",\n")
	    outputHJSONFile.write("\"systMaskYields\" : \""+hMask+"\",\n")
	    paramsList = [
	    			"total", 
	    			"trigger", 
	    			"muon_presel", 
	    			"muon_id", 
	    			"photon_sel", 
	    			"deltaR_muon_to_photon", 
	    			"deltaRPhi_quarkonia_to_photon", 
	    			"quarkonia_mass_cut", 
	    			"ratio_cuts",
	    			"hz_mass_cut",
	    		 	]
	    for param in paramsList:
			if (param == "hz_mass_cut"):
				outputHJSONFile.write("\""+param+"\" : "+str(H1SJSON[param]+H2SJSON[param]+H3SJSON[param])+"\n")
			else:
				outputHJSONFile.write("\""+param+"\" : "+str(H1SJSON[param]+H2SJSON[param]+H3SJSON[param])+",\n")
	    outputHJSONFile.write("}")
	H1SFile.close()
	H2SFile.close()
	H3SFile.close()
# <END> Higgs to Upsilon + Photon - MERGE
############################################################



samplesBranches = {
		"ZtoUpsilon_Cat0":["ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat1":["ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat2":["ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat3":["ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat0":["ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat1":["ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat2":["ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat3":["ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"HtoUpsilon_Cat0":["HToUpsilon1SGamma", "HToUpsilon2SGamma", "HToUpsilon3SGamma", "HToUpsilonGamma", "HDalitz"],
		"HtoJPsi_Cat0":["HToJPsiGamma", "HDalitz"]
		}

# print samplesBranches

outputJSON = {
			"ZtoUpsilon_Cat0":[],
			"ZtoUpsilon_Cat1":[],
			"ZtoUpsilon_Cat2":[],
			"ZtoUpsilon_Cat3":[],
			"ZtoJPsi_Cat0":[],
			"ZtoJPsi_Cat1":[],
			"ZtoJPsi_Cat2":[],
			"ZtoJPsi_Cat3":[],
			"HtoUpsilon_Cat0":[],
			"HtoJPsi_Cat0":[]
			}

for branch in samplesBranches:
	for sample in samplesBranches[branch]:
		ZZZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZZZ.json","r")  
		PZZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_PZZZZ.json","r")  
		MZZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_MZZZZ.json","r")  
		ZPZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZPZZZ.json","r")  
		ZMZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZMZZZ.json","r")  
		ZZPZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZPZZ.json","r")  
		ZZMZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZMZZ.json","r")  
		ZZZPZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZPZ.json","r")  
		ZZZMZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZMZ.json","r")  
		ZZZZPFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZZP.json","r")  
		ZZZZMFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZZM.json","r")  
		countsZZZZZ = json.load(ZZZZZFile)
		countsPZZZZ = json.load(PZZZZFile)
		countsMZZZZ = json.load(MZZZZFile)
		countsZPZZZ = json.load(ZPZZZFile)
		countsZMZZZ = json.load(ZMZZZFile)
		countsZZPZZ = json.load(ZZPZZFile)
		countsZZMZZ = json.load(ZZMZZFile)
		countsZZZPZ = json.load(ZZZPZFile)
		countsZZZMZ = json.load(ZZZMZFile)
		countsZZZZP = json.load(ZZZZPFile)
		countsZZZZM = json.load(ZZZZMFile)

		outputJSON[branch].append({
			"Analysis Branch": countsZZZZZ["analysisBranch"]+"Photon",
			"Analysis Sample": countsZZZZZ["sample"],
			"Category": countsZZZZZ["selCategory"],
			"Pileup": getSysterror(countsZZZZZ["hz_mass_cut"], countsPZZZZ["hz_mass_cut"], countsMZZZZ["hz_mass_cut"]),
			"Trigger": getSysterror(countsZZZZZ["hz_mass_cut"], countsZPZZZ["hz_mass_cut"], countsZMZZZ["hz_mass_cut"]),
			"Muon ID": getSysterror(countsZZZZZ["hz_mass_cut"], countsZZPZZ["hz_mass_cut"], countsZZMZZ["hz_mass_cut"]),
			"Photon ID": getSysterror(countsZZZZZ["hz_mass_cut"], countsZZZPZ["hz_mass_cut"], countsZZZMZ["hz_mass_cut"]),
			"Electron Veto": getSysterror(countsZZZZZ["hz_mass_cut"], countsZZZZP["hz_mass_cut"], countsZZZZM["hz_mass_cut"]),
			})

		ZZZZZFile.close()
		PZZZZFile.close()
		MZZZZFile.close()  
		ZPZZZFile.close()  
		ZMZZZFile.close()  
		ZZPZZFile.close()  
		ZZMZZFile.close()  
		ZZZPZFile.close()  
		ZZZMZFile.close()  
		ZZZZPFile.close() 

with open('evtsCountFiles/systErrorYields.json', 'w') as outputJSONFile:  
    json.dump(outputJSON, outputJSONFile, indent=2)
    outputJSONFile.write("\n")


###############################
# Print Final Yields
samplesBranchesFinalYields = {
		"ZtoUpsilon_Cat0":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat1":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat2":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat3":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat0":["Data", "ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat1":["Data", "ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat2":["Data", "ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat3":["Data", "ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"HtoUpsilon_Cat0":["Data", "HToUpsilon1SGamma", "HToUpsilon2SGamma", "HToUpsilon3SGamma", "HToUpsilonGamma", "HDalitz"],
		"HtoJPsi_Cat0":["Data", "HToJPsiGamma", "HDalitz"]
		}

outputJSONFinalYields = {
				"ZtoUpsilon_Cat0":[],
				"ZtoUpsilon_Cat1":[],
				"ZtoUpsilon_Cat2":[],
				"ZtoUpsilon_Cat3":[],
				"ZtoJPsi_Cat0":[],
				"ZtoJPsi_Cat1":[],
				"ZtoJPsi_Cat2":[],
				"ZtoJPsi_Cat3":[],
				"HtoUpsilon_Cat0":[],
				"HtoJPsi_Cat0":[]
				}

for branch in samplesBranchesFinalYields:
	for sample in samplesBranchesFinalYields[branch]:
		f = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZZZ.json","r")  
		counts = json.load(f)
		# outputJSON[samplesBranches[sample]] = []
		outputJSONFinalYields[branch].append({
			"Analysis Branch": counts["analysisBranch"]+"Photon",
			"Analysis Sample": counts["sample"],
			"Category": counts["selCategory"],
			"Total before selection": counts["total"],
			"Final Yield/Count": counts["hz_mass_cut"],
			})

		f.close()


with open('evtsCountFiles/FinalYields.json', 'w') as outputJSONFinalYieldsFile:  
    json.dump(outputJSONFinalYields, outputJSONFinalYieldsFile, indent=2)
    outputJSONFinalYieldsFile.write("\n")

