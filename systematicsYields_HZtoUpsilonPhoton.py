#!/usr/bin/env python

import json

def getSysterror(nominal, up, down):
	diff_up = up - nominal
	diff_down = down - nominal
	max_diff = max(abs(diff_down), abs(diff_up))
	# return float(format(max_diff/nominal*100, '.2f'))
	return max_diff/nominal*100.0




############################################################
# <BEGIN> Higgs/Z to Upsilon + Photon - MERGE
# Merge Higgs/Z Upsilon files
def mergeHZ(analysisBranch, selCategory):
	boson = analysisBranch[0]
	HZtoUpsilonSystMasks = [
					"ZZZZZZ", 
					"PZZZZZ", 
					"MZZZZZ", 
					"ZPZZZZ", 
					"ZMZZZZ", 
					"ZZPZZZ", 
					"ZZMZZZ", 
					"ZZZPZZ", 
					"ZZZMZZ", 
					"ZZZZPZ", 
					"ZZZZMZ", 
					"ZZZZZP", 
					"ZZZZZM", 
					]
	for hzMask in HZtoUpsilonSystMasks:
		HZ1SFile = open("evtsCountFiles/evtsCountFile_"+boson+"ToUpsilon1SGamma_"+boson+"toUpsilon_"+selCategory+"_"+hzMask+"_default.json","r")
		HZ2SFile = open("evtsCountFiles/evtsCountFile_"+boson+"ToUpsilon2SGamma_"+boson+"toUpsilon_"+selCategory+"_"+hzMask+"_default.json","r")
		HZ3SFile = open("evtsCountFiles/evtsCountFile_"+boson+"ToUpsilon3SGamma_"+boson+"toUpsilon_"+selCategory+"_"+hzMask+"_default.json","r")
		HZ1SJSON = json.load(HZ1SFile)
		HZ2SJSON = json.load(HZ2SFile)
		HZ3SJSON = json.load(HZ3SFile)
		with open("evtsCountFiles/evtsCountFile_"+boson+"ToUpsilonGamma_"+boson+"toUpsilon_"+selCategory+"_"+hzMask+"_default.json", "w") as outputHZJSONFile:  
		    outputHZJSONFile.write("{\n")
		    outputHZJSONFile.write("\"sample\" : \""+boson+"ToUpsilonGamma\",\n")
		    outputHZJSONFile.write("\"analysisBranch\" : \""+boson+"toUpsilon\",\n")
		    outputHZJSONFile.write("\"selCategory\" : \""+selCategory+"\",\n")
		    outputHZJSONFile.write("\"systMaskYields\" : \""+hzMask+"\",\n")
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
					outputHZJSONFile.write("\""+param+"\" : "+str(HZ1SJSON[param]+HZ2SJSON[param]+HZ3SJSON[param])+"\n")
				else:
					outputHZJSONFile.write("\""+param+"\" : "+str(HZ1SJSON[param]+HZ2SJSON[param]+HZ3SJSON[param])+",\n")
		    outputHZJSONFile.write("}")
		HZ1SFile.close()
		HZ2SFile.close()
		HZ3SFile.close()

mergeHZ("ZToUpsilon", "Cat0")
mergeHZ("ZToUpsilon", "Cat1")
mergeHZ("ZToUpsilon", "Cat2")
mergeHZ("ZToUpsilon", "Cat3")
mergeHZ("HToUpsilon", "Cat0")
# <END> Higgs/Z to Upsilon + Photon - MERGE
############################################################



samplesBranches = {
		"ZtoUpsilon_Cat0":["ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat1":["ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat2":["ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat3":["ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat0":["ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat1":["ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat2":["ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat3":["ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"HtoUpsilon_Cat0":["HToUpsilon1SGamma", "HToUpsilon2SGamma", "HToUpsilon3SGamma", "HToUpsilonGamma", "HDalitz"],
		"HtoJPsi_Cat0":["HToJPsiGamma", "HDalitz"]
		}

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
		ZZZZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZZZZ_default.json","r")  
		PZZZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_PZZZZZ_default.json","r")  
		MZZZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_MZZZZZ_default.json","r")  
		ZPZZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZPZZZZ_default.json","r")  
		ZMZZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZMZZZZ_default.json","r")  
		ZZPZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZPZZZ_default.json","r")  
		ZZMZZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZMZZZ_default.json","r")  
		ZZZPZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZPZZ_default.json","r")  
		ZZZMZZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZMZZ_default.json","r")  
		ZZZZPZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZZPZ_default.json","r")  
		ZZZZMZFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZZMZ_default.json","r")  
		ZZZZZPFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZZZP_default.json","r")  
		ZZZZZMFile = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZZZM_default.json","r")  
		countsZZZZZZ = json.load(ZZZZZZFile)
		countsPZZZZZ = json.load(PZZZZZFile)
		countsMZZZZZ = json.load(MZZZZZFile)
		countsZPZZZZ = json.load(ZPZZZZFile)
		countsZMZZZZ = json.load(ZMZZZZFile)
		countsZZPZZZ = json.load(ZZPZZZFile)
		countsZZMZZZ = json.load(ZZMZZZFile)
		countsZZZPZZ = json.load(ZZZPZZFile)
		countsZZZMZZ = json.load(ZZZMZZFile)
		countsZZZZPZ = json.load(ZZZZPZFile)
		countsZZZZMZ = json.load(ZZZZMZFile)
		countsZZZZZP = json.load(ZZZZZPFile)
		countsZZZZZM = json.load(ZZZZZMFile)

		# print branch +" - "+ sample

		outputJSON[branch].append({
			"Analysis Branch": countsZZZZZZ["analysisBranch"]+"Photon",
			"Analysis Sample": countsZZZZZZ["sample"],
			"Category": countsZZZZZZ["selCategory"],
			"Pileup": getSysterror(countsZZZZZZ["hz_mass_cut"], countsPZZZZZ["hz_mass_cut"], countsMZZZZZ["hz_mass_cut"]),
			"Trigger": getSysterror(countsZZZZZZ["hz_mass_cut"], countsZPZZZZ["hz_mass_cut"], countsZMZZZZ["hz_mass_cut"]),
			"Muon ID": getSysterror(countsZZZZZZ["hz_mass_cut"], countsZZPZZZ["hz_mass_cut"], countsZZMZZZ["hz_mass_cut"]),
			"Photon ID": getSysterror(countsZZZZZZ["hz_mass_cut"], countsZZZPZZ["hz_mass_cut"], countsZZZMZZ["hz_mass_cut"]),
			"Electron Veto": getSysterror(countsZZZZZZ["hz_mass_cut"], countsZZZZPZ["hz_mass_cut"], countsZZZZMZ["hz_mass_cut"]),
			"Polarization": getSysterror(countsZZZZZZ["hz_mass_cut"], countsZZZZZZ["hz_mass_cut"], countsZZZZZZ["hz_mass_cut"]),
			})

		ZZZZZZFile.close()
		PZZZZZFile.close()
		MZZZZZFile.close()  
		ZPZZZZFile.close()  
		ZMZZZZFile.close()  
		ZZPZZZFile.close()  
		ZZMZZZFile.close()  
		ZZZPZZFile.close()  
		ZZZMZZFile.close()  
		ZZZZPZFile.close() 
		ZZZZMZFile.close() 
		ZZZZZPFile.close() 
		ZZZZZMFile.close() 

with open('evtsCountFiles/systErrorYields.json', 'w') as outputJSONFile:  
    json.dump(outputJSON, outputJSONFile, indent=2)
    outputJSONFile.write("\n")


###############################
# Print Final Yields
samplesBranchesFinalYields = {
		"ZtoUpsilon_Cat0":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat1":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat2":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat3":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
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
		f = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZZZZ_default.json","r")  
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

