#!/usr/bin/env python

import commands
import os
import json

nloSamples = [
				# Higgs
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/HDalitzNLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/VBFH_HToUps1SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/VBFH_HToUps2SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/VBFH_HToUps3SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/WmH_HToUps1SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/WmH_HToUps2SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/WmH_HToUps3SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/WpH_HToUps1SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/WpH_HToUps2SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/WpH_HToUps3SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ZH_HToUps1SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ZH_HToUps2SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ZH_HToUps3SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ggH_HToUps1SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ggH_HToUps2SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ggH_HToUps3SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ttH_HToUps1SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ttH_HToUps2SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ttH_HToUps3SG_NLO*/*/*/*/*/ggtree_mc_*.root",
				# Z
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ZGTo2MuG_MMuMu-2To15*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ZToUpsilon1SGamma_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ZToUpsilon2SGamma_NLO*/*/*/*/*/ggtree_mc_*.root",
				"/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/ZToUpsilon3SGamma_NLO*/*/*/*/*/ggtree_mc_*.root",
				]

for s in nloSamples:
	fileList = ""
	for f in (commands.getstatusoutput("ls "+ s)[1].split("\n")):
		fileList += "root://eoscms.cern.ch/"+f.replace("/eos/cms","") + "\n"
		with open(s.replace("/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/", "").replace("*/*/*/*/*/ggtree_mc_*.root", "")+".txt", 'w') as fp:
				fp.write(fileList)
	


