#!/usr/bin/env python



samplesMC = [
		# Higgs - Cat0
		["HToUpsilon1SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ"],
		["HToUpsilon2SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ"],
		["HToUpsilon3SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ"],
		["HToJPsiGamma", "HtoJPsi", "Cat0", "ZZZZZZ"],
		["HDalitz", "HtoJPsi", "Cat0", "ZZZZZZ"],
		["HDalitz", "HtoUpsilon", "Cat0", "ZZZZZZ"],
		# Z - Cat0
		["ZToUpsilon1SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ"],
		["ZToUpsilon2SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ"],
		["ZToUpsilon3SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ"],
		["ZToJPsiGamma", "ZtoJPsi", "Cat0", "ZZZZZZ"],
		["ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat0", "ZZZZZZ"],
		["ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat0", "ZZZZZZ"],
		# Z - Cat1
		["ZToUpsilon1SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ"],
		["ZToUpsilon2SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ"],
		["ZToUpsilon3SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ"],
		["ZToJPsiGamma", "ZtoJPsi", "Cat1", "ZZZZZZ"],
		["ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat1", "ZZZZZZ"],
		["ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat1", "ZZZZZZ"],
		# Z - Cat2
		["ZToUpsilon1SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ"],
		["ZToUpsilon2SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ"],
		["ZToUpsilon3SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ"],
		["ZToJPsiGamma", "ZtoJPsi", "Cat2", "ZZZZZZ"],
		["ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat2", "ZZZZZZ"],
		["ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat2", "ZZZZZZ"],
		# Z - Cat3
		["ZToUpsilon1SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ"],
		["ZToUpsilon2SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ"],
		["ZToUpsilon3SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ"],
		["ZToJPsiGamma", "ZtoJPsi", "Cat3", "ZZZZZZ"],
		["ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat3", "ZZZZZZ"],
		["ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat3", "ZZZZZZ"],
	]


shapeSystMasksMC = [
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

shapeSystMasksData = [
	"default",
	]

samplesData = [
	# Higgs - Cat0
	["Data", "HtoJPsi", "Cat0"],
	["Data", "HtoUpsilon", "Cat0"],
	# Z - Cat0
	["Data", "ZtoJPsi", "Cat0"],
	["Data", "ZtoUpsilon", "Cat0"],
	# Z - Cat1
	["Data", "ZtoJPsi", "Cat1"],
	["Data", "ZtoUpsilon", "Cat1"],
	# Z - Cat2
	["Data", "ZtoJPsi", "Cat2"],
	["Data", "ZtoUpsilon", "Cat2"],
	# Z - Cat3
	["Data", "ZtoJPsi", "Cat3"],
	["Data", "ZtoUpsilon", "Cat3"],
	]

for sample in samplesData:
	for shape in shapeSystMasksData:
		print "#Merging ("+sample[0]+" - "+sample[1]+" - "+sample[2]+"):"
		print "mv outputHistos/outHistos_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ_"+shape+".root outputHistos/outHistos_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ.root"
		print "mv outputHistos/outTreeToFit_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ_"+shape+".root outputHistos/outTreeToFit_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ.root\n"

for sample in samplesMC:
	if (sample[0] == "ZGTo2MuG_MMuMu-2To15" or sample[0] == "HDalitz"):
		for shape in shapeSystMasksData:
			print "#Merging ("+sample[0]+" - "+sample[1]+" - "+sample[2]+"):"
			print "mv outputHistos/outHistos_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ_"+shape+".root outputHistos/outHistos_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ.root"
			print "mv outputHistos/outTreeToFit_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ_"+shape+".root outputHistos/outTreeToFit_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ.root\n"

for sample in samplesMC:
	if (sample[0] != "ZGTo2MuG_MMuMu-2To15" and sample[0] != "HDalitz"):
		print "#Merging ("+sample[0]+" - "+sample[1]+" - "+sample[2]+"):"
		haddStrHistos = "hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ.root"
		haddStrTree = "hadd -f -O outputHistos/outTreeToFit_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ.root"
		for shape in shapeSystMasksMC:
			haddStrHistos += " outputHistos/outHistos_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ_"+shape+".root"
			haddStrTree += " outputHistos/outTreeToFit_HZtoUpsilonPhoton_"+sample[0]+"_"+sample[1]+"_"+sample[2]+"_ZZZZZZ_"+shape+".root"
		print haddStrHistos+"\n"
		print haddStrTree+"\n"



