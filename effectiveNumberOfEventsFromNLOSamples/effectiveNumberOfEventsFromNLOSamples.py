#!/usr/bin/env python

from ROOT import *
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

class AutoVivification(dict):
    """Implementation of perl's autovivification feature."""
    def __getitem__(self, item):
        try:
            return dict.__getitem__(self, item)
        except KeyError:
            value = self[item] = type(self)()
            return value

effNGen = AutoVivification()

# Fill xSecs
# Z TO J/PSI + PHOTON	3.0494E-04
effNGen["ZToUpsilon1SGamma_NLO"]["xSec"] = 6.7965E-05
effNGen["ZToUpsilon2SGamma_NLO"]["xSec"] = 2.6887E-05
effNGen["ZToUpsilon3SGamma_NLO"]["xSec"] = 2.3400E-05
effNGen["ZGTo2MuG_MMuMu-2To15"]["xSec"] = 7.9260E-02

# H (VBF) TO J/PSI + PHOTON	6.7408E-07
effNGen["VBFH_HToUps1SG_NLO"]["xSec"] = 4.8960E-10
effNGen["VBFH_HToUps2SG_NLO"]["xSec"] = 1.0365E-10
effNGen["VBFH_HToUps3SG_NLO"]["xSec"] = 7.5027E-11

# H (TTH) TO J/PSI + PHOTON	9.0382E-08
effNGen["ttH_HToUps1SG_NLO"]["xSec"] = 6.5647E-11
effNGen["ttH_HToUps2SG_NLO"]["xSec"] = 1.3898E-11
effNGen["ttH_HToUps3SG_NLO"]["xSec"] = 1.0060E-11
	
# H (GGF) TO J/PSI + PHOTON	8.6586E-06
effNGen["ggH_HToUps1SG_NLO"]["xSec"] = 6.2890E-09
effNGen["ggH_HToUps2SG_NLO"]["xSec"] = 1.3314E-09
effNGen["ggH_HToUps3SG_NLO"]["xSec"] = 9.6373E-10
	
# H (WmH) TO J/PSI + PHOTON	9.4963E-08
effNGen["WmH_HToUps1SG_NLO"]["xSec"] = 6.8974E-11
effNGen["WmH_HToUps2SG_NLO"]["xSec"] = 1.4602E-11
effNGen["WmH_HToUps3SG_NLO"]["xSec"] = 1.0570E-11
	
# H (WpH) TO J/PSI + PHOTON	1.4972E-07
effNGen["WpH_HToUps1SG_NLO"]["xSec"] = 1.0874E-10
effNGen["WpH_HToUps2SG_NLO"]["xSec"] = 2.3021E-11
effNGen["WpH_HToUps3SG_NLO"]["xSec"] = 1.6664E-11
	
# H (ZH) TO J/PSI + PHOTON	1.5754E-07
effNGen["ZH_HToUps1SG_NLO"]["xSec"] = 1.1443E-10
effNGen["ZH_HToUps2SG_NLO"]["xSec"] = 2.4224E-11
effNGen["ZH_HToUps3SG_NLO"]["xSec"] = 1.7535E-11


effNGen["HDalitzNLO"]["xSec"] = 2.1337E-03


# Fill n Eff Evts
for s in nloSamples:
	haddSufix = " "
	for f in (commands.getstatusoutput("ls "+ s)[1].split("\n")):
		haddSufix += "root://eoscms.cern.ch/"+f.replace("/eos/cms","") + " "
	os.system("hadd -T -f temp.root" + haddSufix)
	fTemp = TFile("temp.root")
	# print (((fTemp.ggNtuplizer).Get("hGenWeight")).GetBinContent(1) - ((fTemp.ggNtuplizer).Get("hGenWeight")).GetBinContent(2))
	effNGen[s.replace("/eos/cms/store/user/ftorresd/HZtoUpsilonPlusPhotonSamples2016/MC/", "").replace("*/*/*/*/*/ggtree_mc_*.root", "")]["effNGen"] = (((fTemp.ggNtuplizer).Get("hGenWeight")).GetBinContent(1) - ((fTemp.ggNtuplizer).Get("hGenWeight")).GetBinContent(2))
	fTemp.Close()

print effNGen
os.system("rm effNGen.json")
with open('effNGen.json', 'w') as fp:
    json.dump(effNGen, fp, indent=4)


os.system("rm temp.root") 


