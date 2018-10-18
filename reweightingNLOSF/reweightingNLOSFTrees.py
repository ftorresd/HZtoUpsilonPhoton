#!/usr/bin/env python

# import ROOT in batch mode
import sys, os, commands
from array import array
# import multiprocessing.dummy as mp


# oldargv = sys.argv[:]
# sys.argv = [ '-b-' ]
from ROOT import *
gROOT.SetBatch(True)
# sys.argv = oldargv

# load FWLite C++ libraries
gSystem.Load("libFWCoreFWLite.so");
gSystem.Load("libDataFormatsFWLite.so");
FWLiteEnabler.enable()

# os.system("rm -rf outputTrees; mkdir outputTrees")

# load FWlite python libraries
from DataFormats.FWLite import Handle, Events
particles, particleLabel = Handle("std::vector<reco::GenParticle>"), "prunedGenParticles"
genEventInfo, generatorLabel = Handle("GenEventInfoProduct"), "generator"



def getListOfFiles(DASName):
    return commands.getstatusoutput('dasgoclient -query=\"file dataset='+DASName+'\"')[1].splitlines()

def parseFiles(filesList):
    files = []
    for f in filesList:
        files.append("root://cms-xrd-global.cern.ch/"+f)
    # return files
    print "\n\n### Source Files:"
    for f in files:
        print f
    return files

# def saveHisto(histo, isLog = False):
#     canv = TCanvas()
#     if isLog:
#         canv.SetLogy()
#     histo.Draw()
#     canv.SaveAs("outputTrees/"+histo.GetName()+".png")
#     canv.SaveAs("outputTrees/"+histo.GetName()+".pdf")
#     canv.SaveAs("outputTrees/"+histo.GetName()+".root")

def getBosons(configuration):
    print "####### <BEGIN> " +configuration["sampleName"]

    # C O N F I G
    sampleName = configuration["sampleName"]
    bosonPDGId = configuration["bosonPDGId"]
    upsilonPDGId = configuration["upsilonPDGId"]

    ### Don't change
    MAXEVENTS = -1
    treeFile = TFile("outputTrees/bosonsTree_"+sampleName+".root", "RECREATE")
    bosonTree = TTree( "bosonTree", "bosonTree" )

    # bosonEta
    bosonEta = array( 'f', [ 99999. ] )
    bosonTree.Branch("bosonEta", bosonEta, "bosonEta/F")

    # bosonPt = -1.
    bosonPt = array( 'f', [ -1. ] )
    bosonTree.Branch("bosonPt", bosonPt, "bosonPt/F")

    # weight
    weight = array( 'f', [ 1. ] )
    bosonTree.Branch("weight", weight, "weight/F")

    events = Events( parseFiles( getListOfFiles(configuration["DASName"]) ) )
    # events = Events("root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/ZToUpsilon1SGamma-TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/10000/18E2BF65-BD89-E711-B394-0CC47A0AD456.root")
    for iev,event in enumerate(events):
        if MAXEVENTS >= 0:
            if iev >= MAXEVENTS: break
        #Event loop
        print "\n--> "+sampleName+": Event %d: run %6d, lumi %4d, event %12d" % (iev,event.eventAuxiliary().run(), event.eventAuxiliary().luminosityBlock(),event.eventAuxiliary().event())
        # define the boson vector
        theBoson = TLorentzVector()
        # genEventInfo
        event.getByLabel(generatorLabel, genEventInfo)
        # print genEventInfo.product().weight()
        weight[0] = genEventInfo.product().weight()
        # GenParticles
        event.getByLabel(particleLabel, particles)
        for i,part in enumerate(particles.product()):
            if (sampleName == "DYJetsToLL_NLO"):
                if (part.pdgId() == 23 and part.isLastCopy()):
                    print "--> "+sampleName+": The Boson!"
                    theBoson.SetPtEtaPhiE(part.pt(), part.eta(), part.phi(), part.energy())
                    print "--> "+sampleName+": Boson -  pt "+str(theBoson.Pt())+", eta: "+str(theBoson.Eta())
            else:
                if (part.pdgId() == bosonPDGId):
                    if (part.numberOfDaughters() == 2):
                        if(( (part.daughter(0).pdgId() == 22) and (part.daughter(1).pdgId() == upsilonPDGId) ) or ( (part.daughter(1).pdgId() == 22) and (part.daughter(0).pdgId() == upsilonPDGId) )):
                            print "--> "+sampleName+": The Boson!"
                            theBoson.SetPtEtaPhiE(part.pt(), part.eta(), part.phi(), part.energy())
                            print "--> "+sampleName+": Boson -  pt "+str(theBoson.Pt())+", eta: "+str(theBoson.Eta())+ ", eta: "+str(weight[0])
        bosonEta[0] = theBoson.Eta()
        bosonPt[0] = theBoson.Pt()
        if (configuration["isZ"]):
            if (theBoson.M() >= 50):
                bosonTree.Fill()
        else:
            bosonTree.Fill()

    # Print Plots
    # saveHisto(h_ptEta)
    # saveHisto(h_pt, isLog = True)
    # saveHisto(h_eta)

    # Close File
    bosonTree.Print()
    # bosonTree.Scan()
    treeFile.Write()
    treeFile.Close()

    print "####### <END> " +configuration["sampleName"]
    print "\n\n\n"


if __name__ == "__main__":
    # C O N F I G
    configs = [
        {
            "sampleName" : "ZToUpsilon1SG_LO",
            "DASName" : "/ZToUpsilon1SGamma-TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
            "bosonPDGId" : 25,
            "upsilonPDGId" : 553,
            "isZ" : True,
        },
        # {
        #     "sampleName" : "ZToUpsilon2SG_LO",
        #     "DASName" : "/ZToUpsilon2SGamma-TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
        #     "bosonPDGId" : 25,
        #     "upsilonPDGId" : 100553,
        #     "isZ" : True,
        # },
        # {
        #     "sampleName" : "ZToUpsilon3SG_LO",
        #     "DASName" : "/ZToUpsilon3SGamma-TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
        #     "bosonPDGId" : 25,
        #     "upsilonPDGId" : 200553,
        #     "isZ" : True,
        # },
        # {
        #     "sampleName" : "HToUpsilon1SG_LO",
        #     "DASName" : "/HToUpsilon1SG_ToMuMuG_allProdMode_M125_TuneCUETP8M1_13TeV_Pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM",
        #     "bosonPDGId" : 25,
        #     "upsilonPDGId" : 553,
        #     "isZ" : False,
        # },
        # {
        #     "sampleName" : "HToUpsilon2SG_LO",
        #     "DASName" : "/HToUpsilon2SG_ToMuMuG_allProdMode_M125_TuneCUETP8M1_13TeV_Pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM",
        #     "bosonPDGId" : 25,
        #     "upsilonPDGId" : 100553,
        #     "isZ" : False,
        # },
        # {
        #     "sampleName" : "HToUpsilon3SG_LO",
        #     "DASName" : "/HToUpsilon3SG_ToMuMuG_allProdMode_M125_TuneCUETP8M1_13TeV_Pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
        #     "bosonPDGId" : 25,
        #     "upsilonPDGId" : 200553,
        #     "isZ" : False,
        # },
        {
            "sampleName" : "ZToUpsilon2SG_NLO",
            "DASName" : "/ZToUpsilon2SGamma_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
            "bosonPDGId" : 23,
            "upsilonPDGId" : 100553,
            "isZ" : True,
        },
        {
            "sampleName" : "DYJetsToLL_NLO",
            "DASName" : "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM",
            "bosonPDGId" : 23,
            "upsilonPDGId" : 13,
            "isZ" : False,
        },
        # {
        #     "sampleName" : "ggH_HToJPsiG_NLO",
        #     "DASName" : "/ggH_HToJPsiG_M125_NNPDF30_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
        #     "bosonPDGId" : 25,
        #     "upsilonPDGId" : 443,
        #     "isZ" : False,
        # },
        # {
        #     "sampleName" : "VBFH_HToJPsiG_NLO",
        #     "DASName" : "/VBFH_HToJPsiG_M125_NNPDF30_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
        #     "bosonPDGId" : 25,
        #     "upsilonPDGId" : 443,
        #     "isZ" : False,
        # },
        # {
        #     "sampleName" : "ZH_HToJPsiG_NLO",
        #     "DASName" : "/ZH_HToJPsiG_M125_NNPDF30_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
        #     "bosonPDGId" : 25,
        #     "upsilonPDGId" : 443,
        #     "isZ" : False,
        # },
        # {
        #     "sampleName" : "WpHJ_HToJPsiG_NLO",
        #     "DASName" : "/WpHJ_HToJPsiG_M125_NNPDF30_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
        #     "bosonPDGId" : 25,
        #     "upsilonPDGId" : 443,
        #     "isZ" : False,
        # },
        # {
        #     "sampleName" : "WmHJ_HToJPsiG_NLO",
        #     "DASName" : "/WmHJ_HToJPsiG_M125_NNPDF30_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
        #     "bosonPDGId" : 25,
        #     "upsilonPDGId" : 443,
        #     "isZ" : False,
        # },
        # {
        #     "sampleName" : "ttH_HToJPsiG_NLO",
        #     "DASName" : "/ttH_HToJPsiG_M125_NNPDF30_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
        #     "bosonPDGId" : 25,
        #     "upsilonPDGId" : 443,
        #     "isZ" : False,
        # },
    ]


    configToRun = sys.argv[1]
    for c in configs:
        if (c["sampleName"] == configToRun):
            getBosons(c)
