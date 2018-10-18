#!/usr/bin/env python 

import ROOT, os
ROOT.gROOT.SetBatch(True)

os.system("rm -rf outputHisto; mkdir outputHisto")

# ROOT.gROOT.LoadMacro("plugins/tdrstyle.C")
import tdrstyle
tdrstyle.setTDRStyle()



def saveHisto(histo, name, isLog = False):
    canv = ROOT.TCanvas("canv", "canv", 1024, 576)
    if isLog:
        canv.SetLogy()
    histo.Draw()
    canv.SaveAs("outputHisto/"+histo.GetName()+"_"+name+".png")
    canv.SaveAs("outputHisto/"+histo.GetName()+"_"+name+".pdf")
    canv.SaveAs("outputHisto/"+histo.GetName()+"_"+name+".root")

def makeHistos(sample):
	# C O N F I G
	sampleName = sample["sampleName"]
	# Load file
	f = ROOT.TFile.Open("outputTrees/bosonsTree_"+sampleName+".root")

	# Define Outputs
	histoFile = ROOT.TFile("outputHisto/bosonsHisto_"+sampleName+".root", "RECREATE")
	nBinsPt = 190
	minPt = 0
	maxPt = 700
	if (sample["isZ"]):
		maxPt = 250
		nBinsPt = 80
	h_pt = ROOT.TH1D("h_pt", "h_pt_"+sampleName, nBinsPt, minPt, maxPt)
	h_pt.Sumw2()
	nBinsEta = 70
	minEta = -7
	maxEta = 7
	h_eta = ROOT.TH1D("h_eta", "h_eta_"+sampleName, nBinsEta, minEta, maxEta)
	h_eta.Sumw2()
	# 2d HISTO
	h_ptEta = ROOT.TH2D("h_ptEta", "h_ptEta_"+sampleName, nBinsPt, minPt, maxPt, nBinsEta, minEta, maxEta)
	h_ptEta.Sumw2()

	print "\n\n\n--> Making histograms - Sample: "+ sampleName
	for iev,ev in enumerate(f.bosonTree):
		h_pt.Fill(ev.bosonPt, ev.weight)
		h_eta.Fill(ev.bosonEta, ev.weight)
		h_ptEta.Fill(ev.bosonPt, ev.bosonEta, ev.weight)

	# Normalize to xSec
	h_pt.Scale(sample["xSec"]/h_pt.Integral())
	h_eta.Scale(sample["xSec"]/h_eta.Integral())
	h_ptEta.Scale(sample["xSec"]/h_ptEta.Integral())

	# Setup axis labels
	h_pt.GetXaxis().SetTitle("pT (GeV)")
	h_pt.GetYaxis().SetTitle("a.u.")
	h_pt.GetXaxis().SetTitleSize(.08)
	h_pt.GetYaxis().SetTitle("a.u.")
	h_pt.GetXaxis().SetTitleOffset(1.5)
	h_pt.GetYaxis().SetTitleOffset(1.5)
	h_eta.GetXaxis().SetTitle("#eta")
	h_eta.GetYaxis().SetTitle("a.u.")	
	h_eta.GetXaxis().SetTitleSize(.08)
	h_eta.GetYaxis().SetTitle("a.u.")
	h_eta.GetXaxis().SetTitleOffset(1.5)
	h_eta.GetYaxis().SetTitleOffset(1.5)
	h_ptEta.GetXaxis().SetTitle("pT (GeV)")
	h_ptEta.GetYaxis().SetTitle("#eta")
	# h_ptEta.GetXaxis().SetTitleSize(.08)
	# h_ptEta.GetYaxis().SetTitle("a.u.")
	h_ptEta.GetXaxis().SetTitleOffset(1.)
	h_ptEta.GetYaxis().SetTitleOffset(1.)




	# Print Plots
	# saveHisto(h_ptEta, sampleName)
	# saveHisto(h_pt, sampleName, isLog = True)
	# saveHisto(h_eta, sampleName)

	# Writes and closes Files
	histoFile.Write()
	histoFile.Close()
	f.Close()

def drawRatio(channel):
	channel1 = channel["channel1"]
	channel2 = channel["channel2"]
	print "\n\n\n--> Making ratio plots - Samples: "+ channel1 + " and " + channel2
	f1 = ROOT.TFile.Open("outputHisto/bosonsHisto_"+channel1+".root")
	f2 = ROOT.TFile.Open("outputHisto/bosonsHisto_"+channel2+".root")
	# pT
	canv_pt = ROOT.TCanvas("canv_pt", "canv_pt", 1024*2, 700*2)
	canv_pt.SetLeftMargin(0.5)
	canv_pt.SetBottomMargin(2)
	h_pt1 = f1.Get("h_pt")
	h_pt2 = f2.Get("h_pt")
	h_pt1.Scale(1./h_pt1.Integral())
	h_pt2.Scale(1./h_pt2.Integral())
	h_pt1.SetLineWidth(4);
	h_pt1.SetLineColor(ROOT.kOrange+8);
	h_pt1.SetLineStyle(1);
	h_pt2.SetLineWidth(4);
	h_pt2.SetLineColor(ROOT.kAzure+7);
	h_pt2.SetLineStyle(1);	
	canv_pt.SetLogy()
	ratioPlot_pt = ROOT.TRatioPlot(h_pt1, h_pt2)
	ratioPlot_pt.SetH1DrawOpt("hist")
	ratioPlot_pt.SetH2DrawOpt("hist")
	ratioPlot_pt.Draw("nohide")
	ratioPlot_pt.GetLowerRefYaxis().SetTitle("Ratio LO/NLO");
	ratioPlot_pt.SetLeftMargin(0.2)
	ratioPlot_pt.SetLowBottomMargin(0.4)
	ratioPlot_pt.GetLowerRefGraph().SetMinimum(0)
	ratioPlot_pt.GetLowerRefGraph().SetMaximum(4)
	ratioPlot_pt.GetLowerRefYaxis().SetNdivisions(100)
	ratioPlot_pt.GetLowerRefYaxis().SetLabelSize(0.02)
	ratioPlot_pt.GetLowerRefYaxis().SetTitleOffset (1.2)
	ratioPlot_pt.SetSeparationMargin(0.0);
	# legend
	legend_pt = ROOT.TLegend(0.68,0.73,0.97,0.9)
	legend_pt.SetHeader(channel["bosonName"]+ " Samples");
	legend_pt.SetBorderSize(0);
	legend_pt.SetFillStyle(0);
	legend_pt.AddEntry(h_pt1, "LO", "l");
	legend_pt.AddEntry(h_pt2, "NLO", "l");
	legend_pt.Draw();
	# ROOT.gPad.SetLeftMargin(0.3); 
	# ROOT.gPad.SetRightMargin(0.05); 
	# ROOT.gPad.SetTopMargin(0.08);
	# ROOT.gPad.SetBottomMargin(0.3);
	canv_pt.Update()
	canv_pt.SaveAs("outputHisto/ratio_pt_"+channel1 + "_" + channel2+".png")
	canv_pt.SaveAs("outputHisto/ratio_pt_"+channel1 + "_" + channel2+".pdf")
	canv_pt.SaveAs("outputHisto/ratio_pt_"+channel1 + "_" + channel2+".root")
	# eta
	canv_eta = ROOT.TCanvas("canv_eta", "canv_eta", 1024*2, 700*2)
	h_eta1 = f1.Get("h_eta")
	h_eta2 = f2.Get("h_eta")
	h_eta1.Scale(1./h_eta1.Integral())
	h_eta2.Scale(1./h_eta2.Integral())
	h_eta1.SetLineWidth(4);
	h_eta1.SetLineColor(ROOT.kOrange+8);
	h_eta1.SetLineStyle(1);
	h_eta2.SetLineWidth(4);
	h_eta2.SetLineColor(ROOT.kAzure+7);
	h_eta2.SetLineStyle(1);	
	ratioPlot_eta = ROOT.TRatioPlot(h_eta1, h_eta2)
	ratioPlot_eta.SetH1DrawOpt("hist")
	ratioPlot_eta.SetH2DrawOpt("hist")
	ratioPlot_eta.Draw("nohide")
	ratioPlot_eta.GetLowerRefYaxis().SetTitle("Ratio LO/NLO");
	ratioPlot_eta.SetLeftMargin(0.2)
	ratioPlot_eta.SetLowBottomMargin(0.4)
	# ratioPlot_eta.GetLowerRefYaxis().GetYaxis().SetTitleOffset(1.5);
	ratioPlot_eta.GetLowerRefGraph().SetMinimum(0)
	ratioPlot_eta.GetLowerRefGraph().SetMaximum(2.5)
	ratioPlot_eta.GetLowerRefYaxis().SetNdivisions(100)
	ratioPlot_eta.GetLowerRefYaxis().SetLabelSize(0.02)
	ratioPlot_eta.GetLowerRefYaxis().SetTitleOffset (1.2)
	ratioPlot_eta.SetSeparationMargin(0.0);
	# legend
	legend_eta = ROOT.TLegend(0.71,0.73,1.,0.9)
	legend_eta.SetHeader(channel["bosonName"]+ " Samples");
	legend_eta.SetBorderSize(0);
	legend_eta.SetFillStyle(0);
	legend_eta.AddEntry(h_eta1, "LO", "l");
	legend_eta.AddEntry(h_eta2, "NLO", "l");
	legend_eta.Draw();
	# ROOT.gPad.SetLeftMargin(0.3); 
	# ROOT.gPad.SetRightMargin(0.05); 
	# ROOT.gPad.SetTopMargin(0.08);
	# ROOT.gPad.SetBottomMargin(0.3);
	canv_eta.Update()
	canv_eta.SaveAs("outputHisto/ratio_eta_"+channel1 + "_" + channel2+".png")
	canv_eta.SaveAs("outputHisto/ratio_eta_"+channel1 + "_" + channel2+".pdf")
	canv_eta.SaveAs("outputHisto/ratio_eta_"+channel1 + "_" + channel2+".root")
	# close files
	f1.Close()
	f2.Close()



def drawEfficiency(channel):
	channel1 = channel["channel1"]
	channel2 = channel["channel2"]
	print "\n\n\n--> Making efficiency plots - Samples: "+ channel1 + " and " + channel2
	f1 = ROOT.TFile.Open("outputHisto/bosonsHisto_"+channel1+".root")
	f2 = ROOT.TFile.Open("outputHisto/bosonsHisto_"+channel2+".root")
	#output file
	sfFile = ROOT.TFile("outputHisto/bosonsSF_"+channel1 + "_" + channel2+".root", "RECREATE")

	# pT vs eta
	canv_eff = ROOT.TCanvas("canv_eff", "canv_eff", 1024*2, 700*2)
	# canv_eff.SetLeftMargin(0.5)
	# canv_eff.SetBottomMargin(2)
	h_ptEta1 = f1.Get("h_ptEta")
	h_ptEta2 = f2.Get("h_ptEta")
	h_ptEta1.Scale(1./h_ptEta1.Integral())
	h_ptEta2.Scale(1./h_ptEta2.Integral())
	# h_ptEta1.SetLineWidth(4);
	# h_ptEta1.SetLineColor(ROOT.kOrange+8);
	# h_ptEta1.SetLineStyle(1);
	# h_ptEta2.SetLineWidth(4);
	# h_ptEta2.SetLineColor(ROOT.kAzure+7);
	# h_ptEta2.SetLineStyle(1);	
	# canv_pt.SetLogy()
	h_ptEta2.Divide(h_ptEta1)
	# ratioPlot_pt.SetH1DrawOpt("hist")
	# ratioPlot_pt.SetH2DrawOpt("hist")
	h_ptEta2.Draw("COLZ")
	# effPlot.GetLowerRefYaxis().SetTitle("Ratio LO/NLO");
	# effPlot.SetLeftMargin(0.2)
	# effPlot.SetLowBottomMargin(0.4)
	# effPlot.GetLowerRefGraph().SetMinimum(0)
	# effPlot.GetLowerRefGraph().SetMaximum(4)
	# effPlot.GetLowerRefYaxis().SetNdivisions(100)
	# effPlot.GetLowerRefYaxis().SetLabelSize(0.02)
	# effPlot.GetLowerRefYaxis().SetTitleOffset (1.2)
	# effPlot.SetSeparationMargin(0.0);
	# # legend
	# legend_pt = ROOT.TLegend(0.68,0.73,0.97,0.9)
	# legend_pt.SetHeader(channel["bosonName"]+ " Samples");
	# legend_pt.SetBorderSize(0);
	# legend_pt.SetFillStyle(0);
	# legend_pt.AddEntry(h_ptEta1, "LO", "l");
	# legend_pt.AddEntry(h_pt2, "NLO", "l");
	# legend_pt.Draw();
	ROOT.gPad.SetLeftMargin(0.08); 
	ROOT.gPad.SetRightMargin(0.1); 
	ROOT.gPad.SetTopMargin(0.10);
	ROOT.gPad.SetBottomMargin(0.1);
	canv_eff.Update()
	canv_eff.SaveAs("outputHisto/sf_pt_eta_"+channel1 + "_" + channel2+".png")
	canv_eff.SaveAs("outputHisto/sf_pt_eta_"+channel1 + "_" + channel2+".pdf")
	canv_eff.SaveAs("outputHisto/sf_pt_eta_"+channel1 + "_" + channel2+".root")
	# close files
	h_ptEta2.SetDirectory(sfFile)
	sfFile.Write()
	sfFile.ls()
	sfFile.Close()
	f1.Close()
	f2.Close()

if __name__ == "__main__":
	# xSecs:
	# - Refs:  
	# -- https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt13TeV
	# -- https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
	# -- http://pdg.lbl.gov/2018/listings/rpp2018-list-z-boson.pdf
	# H_gg = 4.858E+01
	# H_vbf = 3.782E+00
	# H_w+ = 9.426E-02
	# H_w- = 5.983E-02	
	# H_ZH = 2.982E-02
	# H_tt = 5.071E-01
	# Z_M>50 =1921.8/3.3662*100

	# C O N F I G
	samples = [
		{
		"sampleName" : "ZToUpsilon1SG_LO",
		"isZ" : True,
		"xSec" : (1921.8/3.3662*100.),
		},
		# {
		# "sampleName" : "ZToUpsilon2SG_LO",
		# "isZ" : True,
		# "xSec" : 100.,
		# },
		# {
		# "sampleName" : "ZToUpsilon3SG_LO",
		# "isZ" : True,
		# "xSec" : 100.,
		# },
		# {
		# "sampleName" : "HToUpsilon1SG_LO",
		# "isZ" : False,
		# "xSec" : (4.858E+01+3.782E+00+9.426E-02+5.983E-02+2.982E-02+5.071E-01),
		# },
		# {
		# "sampleName" : "HToUpsilon2SG_LO",
		# "isZ" : False,
		# "xSec" : 100.,
		# },
		# {
		# "sampleName" : "HToUpsilon3SG_LO",
		# "isZ" : False,
		# "xSec" : 100.,
		# },
		{
		"sampleName" : "ZToUpsilon2SG_NLO",
		"isZ" : True,
		"xSec" : 1921.8/3.3662*100.,
		},
		# {
		# "sampleName" : "DYJetsToLL_NLO",
		# "isZ" : True,
		# "xSec" : 100.,
		# },
		# {
		# "sampleName" : "ggH_HToJPsiG_NLO",
		# "isZ" : False,
		# "xSec" : 4.858E+01,
		# },
		# {
		# "sampleName" : "VBFH_HToJPsiG_NLO",
		# "isZ" : False,
		# "xSec" : 3.782E+00,
		# },
		# {
		# "sampleName" : "ZH_HToJPsiG_NLO",
		# "isZ" : False,
		# "xSec" : 2.982E-02,
		# },
		# {
		# "sampleName" : "WpHJ_HToJPsiG_NLO",
		# "isZ" : False,
		# "xSec" : 9.426E-02,
		# },
		# {
		# "sampleName" : "WmHJ_HToJPsiG_NLO",
		# "isZ" : False,
		# "xSec" : 5.071E-01,
		# },       
		# {
		# "sampleName" : "ttH_HToJPsiG_NLO",
		# "isZ" : False,
		# "xSec" : 100.,
		# },      		    
	]

	# make the histos	
	for s in samples:
		makeHistos(s)

	# Merging Higgs histograms
	# os.system("hadd -f outputHisto/bosonsHisto_Higgs_NLO.root outputHisto/bosonsHisto*_HToJPsiG_NLO.root")

	# RATIO PLOTS
	channels = [
		{
			"channel1" : "ZToUpsilon1SG_LO",
			"channel2" : "ZToUpsilon2SG_NLO",
			"bosonName" : "Z",
		},
		# {
		# 	"channel1" : "HToUpsilon1SG_LO",
		# 	"channel2" : "Higgs_NLO",
		# 	"bosonName" : "Higgs",
		# },
	]


	for c in channels:
		drawRatio(c)
		drawEfficiency(c)


