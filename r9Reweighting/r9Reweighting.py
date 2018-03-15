#!/usr/bin/env python

import ROOT
import argparse
import sys
import os
from array import array
from math import *

import glob
import array

transfName = ["transfnonfull5x5R9EB"]

graphs = ROOT.TGraph()
hmcCorr = ROOT.TH1F("hmcCorr", "hmcCorr", 1000, 0.4, 1.1)
hmcCorr.SetTitle("R9Pho_applied_" + transfName[0]) 
trans = ""


from ROOT import * # import this here, otherwise it overwrites the argparse stuff
gROOT.SetBatch(True) # set ROOT to batch mode, this suppresses printing canvases
ROOT.gStyle.SetOptStat(0)



chainMC = TChain("ggNtuplizer/EventTree")
filesMC = glob.glob("/afs/cern.ch/user/f/ftorresd/workSpace/public/UERJPower_Storage1/ggNtuples2016/ggNtuples_MC/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToJPsiGamma_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_ggNtuples_V08_00_26_07_ZtoJPsi_cleanedMu_v11/ZToJPsiGamma-TuneCUETP8M1_13TeV-pythia8/ZToJPsiGamma_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV/171208_105337/0000/ggtree_mc_*.root")
for file in filesMC:
    chainMC.Add(file)

chainMC.SetBranchStatus("*",0)
chainMC.SetBranchStatus("HLTEleMuX",1)
chainMC.SetBranchStatus("nPho",1)
chainMC.SetBranchStatus("phoCalibEt",1)
chainMC.SetBranchStatus("phoEleVeto",1)
chainMC.SetBranchStatus("phoIDMVA",1)
chainMC.SetBranchStatus("phoSCEta",1)
chainMC.SetBranchStatus("phoR9",1)

chainData = TChain("ggNtuplizer/EventTree")
# filesData = glob.glob("/afs/cern.ch/user/f/ftorresd/workSpace/public/UERJPower_Storage1/ggNtuples2016/ggNtuples_Data/job_MuEG_Run2016G_SepRereco/MuonEG/crab_job_MuEG_Run2016G_SepRereco/170714_151718/0000/ggtree_data_*.root")
filesData = glob.glob("/afs/cern.ch/user/f/ftorresd/workSpace/public/UERJPower_Storage1/ggNtuples2016/ggNtuples_Data/job_MuEG_Run2016*/Muon*/crab*/*/0*/gg*.root")
for file in filesData[11:]:
    chainData.Add(file)
chainData.SetBranchStatus("*",0)
chainData.SetBranchStatus("HLTEleMuX",1)
chainData.SetBranchStatus("nPho",1)
chainData.SetBranchStatus("phoCalibEt",1)
chainData.SetBranchStatus("phoEleVeto",1)
chainData.SetBranchStatus("phoIDMVA",1)
chainData.SetBranchStatus("phoSCEta",1)
chainData.SetBranchStatus("phoR9",1)


h_R9MC_EB = ROOT.TH1F("h_R9MC_EB", "R9 - MC (EB)", 1000, 0., 1.)
h_R9Corr_EB = ROOT.TH1F("h_R9Corr_EB", "R9 - MC Corr'ed (EB)", 1000, 0., 1.)
h_R9Data_EB = ROOT.TH1F("h_R9Data_EB", "R9 - Data (EB)", 1000, 0., 1.)
h_R9Data_EB2 = ROOT.TH1F("h_R9Data_EB2", "R9 - Data (EB)", 1000, 0., 1.)

h_R9MC_EE = ROOT.TH1F("h_R9MC_EE", "R9 - MC (EE)", 1000, 0., 1.)
h_R9Corr_EE = ROOT.TH1F("h_R9Corr_EE", "R9 - MC Corr'ed (EE)", 1000, 0., 1.)
h_R9Data_EE = ROOT.TH1F("h_R9Data_EE", "R9 - Data (EE)", 1000, 0., 1.)
h_R9Data_EE2 = ROOT.TH1F("h_R9Data_EE2", "R9 - Data (EE)", 1000, 0., 1.)



print "Looping over MC...\n"
for evt in chainMC: 
    if ( evt.nPho > 0 and (((evt.HLTEleMuX >> 8) & 1) == 1) ):
        if (evt.phoCalibEt[0] > 33.0 and evt.phoEleVeto[0] != 0 and evt.phoIDMVA[0] > 0.2):
            if fabs(evt.phoSCEta[0]) < 1.4442:
                h_R9MC_EB.Fill(evt.phoR9[0])
                # h_R9Corr_EB.Fill( graphEB.Eval(evt.phoR9[0]) )
            if fabs(evt.phoSCEta[0]) > 1.566:
                # h_R9Corr_EE.Fill( graphEE.Eval(evt.phoR9[0]) )
                h_R9MC_EE.Fill(evt.phoR9[0])

print "Looping over Data...\n"
for evt in chainData: 
    if ( evt.nPho > 0 and (((evt.HLTEleMuX >> 8) & 1) == 1) ):
        if (evt.phoCalibEt[0] > 33.0 and evt.phoEleVeto[0] != 0 and evt.phoIDMVA[0] > 0.2):
            if fabs(evt.phoSCEta[0]) < 1.4442:
                h_R9Data_EB.Fill(evt.phoR9[0])
            if fabs(evt.phoSCEta[0]) > 1.566:
                h_R9Data_EE.Fill(evt.phoR9[0])



def deriveTranfosmations(h_R9MC, h_R9Data):
    print "deriving transformations...\n"
    hmc = h_R9MC
    hdata = h_R9Data
    plotDef = (1000, 0., 1.)
    # NORMALIZE MC TO DATA
    hmc.Scale(hdata.Integral()/hmc.Integral())
    hcdfmc = hmc.GetCumulative()
    hcdfmc.Scale(1./hmc.Integral())

    # Make general
    uniform = ROOT.TH1F("uniform_R9", "", plotDef[0], plotDef[1], plotDef[2])
    for i in xrange(plotDef[0]):
        uniform.SetBinContent(i, 10) 

    uniform.Scale(hdata.Integral()/uniform.Integral())
    uniformcdf = uniform.GetCumulative()
    uniformcdf.Scale(1./hmc.Integral())

    xt = array.array('d', [x*0.001 for x in xrange(1000)])
    yt = array.array('d', [x*0.001 for x in xrange(1000)])

    hmc.GetQuantiles(len(yt), xt, yt)

    hcdfdata = hdata.GetCumulative()
    hcdfdata.Scale(1./hdata.Integral())

    xdatat = array.array('d', [x*0.001 for x in xrange(1000)])
    ydatat = array.array('d', [x*0.001 for x in xrange(1000)])
    hdata.GetQuantiles(len(ydatat), xdatat, ydatat)

    graph = ROOT.TGraph(len(xt), xt, xdatat)
    graph.SetName(transfName[0])

    return graph


graphEB = deriveTranfosmations(h_R9MC_EB , h_R9Data_EB)
print "EB.."
graphEE = deriveTranfosmations(h_R9MC_EE , h_R9Data_EE)
print "EE.."


print "Looping over Corrected MC...\n"
for evt in chainMC: 
    if ( evt.nPho > 0 and (((evt.HLTEleMuX >> 8) & 1) == 1) ):
        if (evt.phoCalibEt[0] > 33.0 and evt.phoEleVeto[0] != 0 and evt.phoIDMVA[0] > 0.2):
            if fabs(evt.phoSCEta[0]) < 1.4442:
                h_R9Corr_EB.Fill( graphEB.Eval(evt.phoR9[0]) )
            if fabs(evt.phoSCEta[0]) > 1.566:
                h_R9Corr_EE.Fill( graphEE.Eval(evt.phoR9[0]) )
                # h_R9MC_EE.Fill(evt.phoR9[0])



print "Looping over Another Dataset...\n"
chainData2 = TChain("ggNtuplizer/EventTree")
# print filesData
for file in filesData[0:10]:
    chainData2.Add(file)
chainData2.SetBranchStatus("*",0)
chainData2.SetBranchStatus("HLTEleMuX",1)
chainData2.SetBranchStatus("nPho",1)
chainData2.SetBranchStatus("phoCalibEt",1)
chainData2.SetBranchStatus("phoEleVeto",1)
chainData2.SetBranchStatus("phoIDMVA",1)
chainData2.SetBranchStatus("phoSCEta",1)
chainData2.SetBranchStatus("phoR9",1)

for evt in chainData2: 
    if ( evt.nPho > 0 and (((evt.HLTEleMuX >> 8) & 1) == 1) ):
        if (evt.phoCalibEt[0] > 33.0 and evt.phoEleVeto[0] != 0 and evt.phoIDMVA[0] > 0.2):
            if fabs(evt.phoSCEta[0]) < 1.4442:
                h_R9Data_EB2.Fill(evt.phoR9[0])
            if fabs(evt.phoSCEta[0]) > 1.566:
                h_R9Data_EE2.Fill(evt.phoR9[0])


c1 = ROOT.TCanvas("R9","R9",800*2, 600*2 )
h_R9MC_EB.SetLineColor(ROOT.kRed)
h_R9MC_EB.SetLineWidth(2)

h_R9Corr_EB.SetLineColor(ROOT.kAzure)
h_R9Corr_EB.SetLineWidth(2)

h_R9Data_EB2.SetMarkerColor(ROOT.kBlack)
h_R9Data_EB2.SetMarkerSize(1)
h_R9Data_EB2.SetMarkerStyle(20)

h_R9MC_EB.Scale(1.0/(h_R9MC_EB.Integral()))
h_R9Corr_EB.Scale(1.0/(h_R9Corr_EB.Integral()))
h_R9Data_EB2.Scale(1.0/(h_R9Data_EB2.Integral()))


h_R9MC_EB.Rebin(10)
h_R9Corr_EB.Rebin(10)
h_R9Data_EB2.Rebin(10)

h_R9MC_EB.Draw("HIST")
h_R9Corr_EB.Draw("HIST SAME")
h_R9Data_EB2.Draw("P SAME")

c1.BuildLegend(0.1, 0.7, 0.4, 0.9);

c1.SaveAs("h_R9Corr_EB.png")
c1.SaveAs("h_R9Corr_EB.pdf")
c1.SaveAs("h_R9Corr_EB.root")



c2 = ROOT.TCanvas("R9","R9",800*2, 600*2 )
h_R9MC_EE.SetLineColor(ROOT.kRed)
h_R9MC_EE.SetLineWidth(2)

h_R9Corr_EE.SetLineColor(ROOT.kAzure)
h_R9Corr_EE.SetLineWidth(2)

h_R9Data_EE2.SetMarkerColor(ROOT.kBlack)
h_R9Data_EE2.SetMarkerSize(1)
h_R9Data_EE2.SetMarkerStyle(20)

h_R9MC_EE.Scale(1.0/(h_R9MC_EE.Integral()))
h_R9Corr_EE.Scale(1.0/(h_R9Corr_EE.Integral()))
h_R9Data_EE2.Scale(1.0/(h_R9Data_EE2.Integral()))

h_R9MC_EE.Rebin(10)
h_R9Corr_EE.Rebin(10)
h_R9Data_EE2.Rebin(10)

h_R9MC_EE.Draw("HIST")
h_R9Corr_EE.Draw("HIST SAME")
h_R9Data_EE2.Draw("P SAME")

c2.BuildLegend(0.1, 0.7, 0.4, 0.9);

c2.SaveAs("h_R9Corr_EE.png")
c2.SaveAs("h_R9Corr_EE.pdf")
c2.SaveAs("h_R9Corr_EE.root")

out = ROOT.TFile("r9transformation.root", "recreate")
graphEB.Write()
graphEE.Write()
out.Close()
print "wrote r9transformation.root"

