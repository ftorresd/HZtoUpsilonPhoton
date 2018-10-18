#include <iostream>
#include <algorithm>
#include <math.h>  

#include "TFile.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"

#include "TH1.h"
#include "TDirectory.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"
#include "TLatex.h"
#include "THStack.h"


#include "tdrstyle.C"


using namespace std;




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PLOTTER FUNCTIONS

void plotter_Pol_extremes(string analysisBranch, TH1D * h_PolNominal, TH1D * h_PolPlus, TH1D * h_PolMinus, string outputFilePath, bool isLogY = false, bool isLogX = false) {
	setTDRStyle();

	h_PolNominal->Scale(1.0/(h_PolNominal->Integral()));
	h_PolNominal->SetLineWidth(4);
	h_PolNominal->SetLineColor(kOrange+8);
	h_PolNominal->SetLineStyle(1);

	h_PolPlus->Scale(1.0/(h_PolPlus->Integral()));
	h_PolPlus->SetLineWidth(4);
	h_PolPlus->SetLineColor(kAzure+7);
	h_PolPlus->SetLineStyle(1);

	h_PolMinus->Scale(1.0/(h_PolMinus->Integral()));
	h_PolMinus->SetLineWidth(4);
	h_PolMinus->SetLineColor(kGray+2);
	h_PolMinus->SetLineStyle(1);

	auto c1 = new TCanvas("c1","c1",1050*2.0,750*2.0);	

	if (isLogY) c1->SetLogy();
	if (isLogX) c1->SetLogx();

	if (h_PolNominal->GetMaximum() > h_PolPlus->GetMaximum()) {
		h_PolNominal->SetMaximum(h_PolNominal->GetMaximum()*1.3);
		h_PolNominal->Draw("hist");	
		h_PolNominal->GetXaxis()->SetTitleSize(.08);
		h_PolNominal->GetYaxis()->SetTitle("a.u.");
		h_PolNominal->GetXaxis()->SetTitleOffset(1.0);
		h_PolNominal->GetYaxis()->SetTitleOffset(1.5);
		h_PolPlus->Draw("hist same");	
		h_PolMinus->Draw("hist same");	
	} else {
		h_PolPlus->SetMaximum(h_PolPlus->GetMaximum()*1.3);
		h_PolPlus->Draw("hist");	
		h_PolPlus->GetXaxis()->SetTitleSize(.08);
		h_PolPlus->GetYaxis()->SetTitle("a.u.");
		h_PolPlus->GetXaxis()->SetTitleOffset(1.0);
		h_PolPlus->GetYaxis()->SetTitleOffset(1.5);
		h_PolNominal->Draw("hist same");	
		h_PolMinus->Draw("hist same");			
	}
	

	// auto legend = new TLegend(0.1,0.7,0.48,0.9, "", "NB");
	// auto legend = new TLegend(0.67,0.76,0.96,0.93, "Z #rightarrow #Upsilon + #gamma #rightarrow #mu#mu + #gamma");
	auto legend = new TLegend(0.67,0.76,0.96,0.93);
	if (analysisBranch == "ZtoJPsi")
		legend->SetHeader("Z #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "HtoJPsi")
		legend->SetHeader("H #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "ZtoUpsilon")
		legend->SetHeader("Z #rightarrow #Upsilon + #gamma Analysis");
	if (analysisBranch == "HtoUpsilon")
		legend->SetHeader("H #rightarrow #Upsilon + #gamma Analysis");
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->AddEntry(h_PolNominal, "Unpolarized", "l");
	legend->AddEntry(h_PolPlus, "Transverse Polarization", "l");
	legend->AddEntry(h_PolMinus, "Longitudinal Polarization", "l");
	legend->Draw();

    auto latex = new TLatex();
    latex->SetNDC();
    latex->SetTextFont(61);
    latex->SetTextSize(0.05);
    latex->DrawLatex(.17, 0.96, "CMS");
    latex->SetTextFont(52);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(11);
    latex->DrawLatex(.25, 0.96, "Simulation");
    latex->SetTextFont(42);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.99, 0.96, "35.86 fb^{-1} (13 TeV, 2016) ");

	// h_MC->GetXaxis()->SetTitleSize(.08);
	// gPad->SetLeftMargin(0.17); 
	// gPad->SetRightMargin(0.05); 
	// gPad->SetTopMargin(0.08);
	gPad->SetBottomMargin(0.2);

	c1->Update();

	system(("mkdir -p  `dirname plotFiles/"+outputFilePath+".png`").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".png").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".pdf").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".root").c_str());

	delete c1;
	delete legend;
	delete latex;
}




void plotter_Pol(string analysisBranch, TH1D * h_unPol, TH1D * h_Pol, string outputFilePath, bool isLogY = false, bool isLogX = false) {
	setTDRStyle();

	h_unPol->Scale(1.0/(h_unPol->Integral()));
	h_unPol->SetLineWidth(4);
	h_unPol->SetLineColor(kOrange+8);
	h_unPol->SetLineStyle(1);

	h_Pol->Scale(1.0/(h_Pol->Integral()));
	h_Pol->SetLineWidth(4);
	h_Pol->SetLineColor(kAzure+7);
	h_Pol->SetLineStyle(1);

	auto c1 = new TCanvas("c1","c1",1050*2.0,750*2.0);	

	if (isLogY) c1->SetLogy();
	if (isLogX) c1->SetLogx();

	if (h_unPol->GetMaximum() > h_Pol->GetMaximum()) {
		h_unPol->SetMaximum(h_unPol->GetMaximum()*1.3);
		h_unPol->Draw("hist");	
		h_unPol->GetXaxis()->SetTitleSize(.08);
		h_unPol->GetYaxis()->SetTitle("a.u.");
		h_unPol->GetXaxis()->SetTitleOffset(1.0);
		h_unPol->GetYaxis()->SetTitleOffset(1.5);
		h_Pol->Draw("hist same");	
	} else {
		h_Pol->SetMaximum(h_Pol->GetMaximum()*1.3);
		h_Pol->Draw("hist");	
		h_Pol->GetXaxis()->SetTitleSize(.08);
		h_Pol->GetYaxis()->SetTitle("a.u.");
		h_Pol->GetXaxis()->SetTitleOffset(1.0);
		h_Pol->GetYaxis()->SetTitleOffset(1.5);
		h_unPol->Draw("hist same");			
	}
	

	// auto legend = new TLegend(0.1,0.7,0.48,0.9, "", "NB");
	// auto legend = new TLegend(0.67,0.76,0.96,0.93, "Z #rightarrow #Upsilon + #gamma #rightarrow #mu#mu + #gamma");
	auto legend = new TLegend(0.67,0.76,0.96,0.93);
	if (analysisBranch == "ZtoJPsi")
		legend->SetHeader("Z #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "HtoJPsi")
		legend->SetHeader("H #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "ZtoUpsilon")
		legend->SetHeader("Z #rightarrow #Upsilon + #gamma Analysis");
	if (analysisBranch == "HtoUpsilon")
		legend->SetHeader("H #rightarrow #Upsilon + #gamma Analysis");
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->AddEntry(h_unPol, "w/o Polarization Reweighting", "l");
	legend->AddEntry(h_Pol, "w/ Polarization Reweighting", "l");
	legend->Draw();

    auto latex = new TLatex();
    latex->SetNDC();
    latex->SetTextFont(61);
    latex->SetTextSize(0.05);
    latex->DrawLatex(.17, 0.96, "CMS");
    latex->SetTextFont(52);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(11);
    // latex->DrawLatex(.25, 0.96, "Preliminary");
    latex->DrawLatex(.25, 0.96, "Simulation");
    latex->SetTextFont(42);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.99, 0.96, "35.86 fb^{-1} (13 TeV, 2016) ");

	// h_MC->GetXaxis()->SetTitleSize(.08);
	// gPad->SetLeftMargin(0.17); 
	// gPad->SetRightMargin(0.05); 
	// gPad->SetTopMargin(0.08);
	gPad->SetBottomMargin(0.2);

	c1->Update();

	system(("mkdir -p  `dirname plotFiles/"+outputFilePath+".png`").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".png").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".pdf").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".root").c_str());

	delete c1;
	delete legend;
	delete latex;
}

void plotter_Single(string analysisBranch, TH1D * h1, string outputFilePath, string legendEntry, bool isLogY = false, bool isLogX = false) {
	setTDRStyle();

	h1->Scale(1.0/(h1->Integral()));
	h1->SetLineWidth(4);
	h1->SetLineColor(kOrange+8);
	h1->SetLineStyle(1);

	auto c1 = new TCanvas("c1","c1",1050*2.0,750*2.0);	

	if (isLogY) c1->SetLogy();
	if (isLogX) c1->SetLogx();


	h1->SetMaximum(h1->GetMaximum()*1.3);
	h1->GetXaxis()->SetTitleOffset(1.0);
	h1->GetYaxis()->SetTitleOffset(1.5);
	h1->Draw("hist");	
	h1->GetXaxis()->SetTitleSize(.08);
	h1->GetYaxis()->SetTitle("a.u.");
	
	// auto legend = new TLegend(0.74,0.76,1.03,0.93, "Z #rightarrow #Upsilon + #gamma #rightarrow #mu#mu + #gamma");
	auto legend = new TLegend(0.74,0.76,1.03,0.93);
	if (analysisBranch == "ZtoJPsi")
		legend->SetHeader("Z #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "HtoJPsi")
		legend->SetHeader("H #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "ZtoUpsilon")
		legend->SetHeader("Z #rightarrow #Upsilon + #gamma Analysis");
	if (analysisBranch == "HtoUpsilon")
		legend->SetHeader("H #rightarrow #Upsilon + #gamma Analysis");
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	if (legendEntry != "") legend->AddEntry(h1, legendEntry.c_str(), "l");
	legend->Draw();

    auto latex = new TLatex();
    latex->SetNDC();
    latex->SetTextFont(61);
    latex->SetTextSize(0.05);
    latex->DrawLatex(.17, 0.96, "CMS");
    latex->SetTextFont(52);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(11);
    // latex->DrawLatex(.25, 0.96, "Preliminary");
    latex->DrawLatex(.25, 0.96, "Simulation");
    latex->SetTextFont(42);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.99, 0.96, "35.86 fb^{-1} (13 TeV, 2016) ");

	// h_MC->GetXaxis()->SetTitleSize(.08);
	// gPad->SetLeftMargin(0.17); 
	// gPad->SetRightMargin(0.05); 
	// gPad->SetTopMargin(0.08);
	gPad->SetBottomMargin(0.2);

	c1->Update();

	system(("mkdir -p  `dirname plotFiles/"+outputFilePath+".png`").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".png").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".pdf").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".root").c_str());

	delete c1;
	delete legend;
	delete latex;
}


void plotter_LeadingTrailing(string analysisBranch, TH1D * h_Lead, TH1D * h_Trail, string outputFilePath, bool isLogY = false, bool isLogX = false) {
	setTDRStyle();

	h_Lead->Scale(1.0/(h_Lead->Integral()));
	h_Lead->SetLineWidth(4);
	h_Lead->SetLineColor(kOrange+8);
	h_Lead->SetLineStyle(1);

	h_Trail->Scale(1.0/(h_Trail->Integral()));
	h_Trail->SetLineWidth(4);
	h_Trail->SetLineColor(kAzure+7);
	h_Trail->SetLineStyle(1);

	auto c1 = new TCanvas("c1","c1",1050*2.0,750*2.0);	

	if (isLogY) c1->SetLogy();
	if (isLogX) c1->SetLogx();

	if (h_Lead->GetMaximum() > h_Trail->GetMaximum()) {
		h_Lead->SetMaximum(h_Lead->GetMaximum()*1.3);
		h_Lead->Draw("hist");	
		h_Lead->GetXaxis()->SetTitleSize(.08);
		h_Lead->GetYaxis()->SetTitle("a.u.");
		h_Lead->GetXaxis()->SetTitleOffset(1.0);
		h_Lead->GetYaxis()->SetTitleOffset(1.5);
		h_Trail->Draw("hist same");	
	} else {
		h_Trail->SetMaximum(h_Trail->GetMaximum()*1.3);
		h_Trail->Draw("hist");	
		h_Trail->GetXaxis()->SetTitleSize(.08);
		h_Trail->GetYaxis()->SetTitle("a.u.");
		h_Trail->GetXaxis()->SetTitleOffset(1.0);
		h_Trail->GetYaxis()->SetTitleOffset(1.5);
		h_Lead->Draw("hist same");			
	}
	

	// auto legend = new TLegend(0.1,0.7,0.48,0.9, "", "NB");
	// auto legend = new TLegend(0.74,0.76,1.03,0.93, "Z #rightarrow #Upsilon + #gamma #rightarrow #mu#mu + #gamma");
	auto legend = new TLegend(0.74,0.76,1.03,0.93);
	if (analysisBranch == "ZtoJPsi")
		legend->SetHeader("Z #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "HtoJPsi")
		legend->SetHeader("H #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "ZtoUpsilon")
		legend->SetHeader("Z #rightarrow #Upsilon + #gamma Analysis");
	if (analysisBranch == "HtoUpsilon")
		legend->SetHeader("H #rightarrow #Upsilon + #gamma Analysis");
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->AddEntry(h_Lead, "Leading Muon", "l");
	legend->AddEntry(h_Trail, "Trailing Muon", "l");
	legend->Draw();

    auto latex = new TLatex();
    latex->SetNDC();
    latex->SetTextFont(61);
    latex->SetTextSize(0.05);
    latex->DrawLatex(.17, 0.96, "CMS");
    latex->SetTextFont(52);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(11);
    // latex->DrawLatex(.25, 0.96, "Preliminary");
    latex->DrawLatex(.25, 0.96, "Simulation");
    latex->SetTextFont(42);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.99, 0.96, "35.86 fb^{-1} (13 TeV, 2016) ");

    // h_MC->GetXaxis()->SetTitleSize(.08);
	// gPad->SetLeftMargin(0.17); 
	// gPad->SetRightMargin(0.05); 
	// gPad->SetTopMargin(0.08);
	gPad->SetBottomMargin(0.2);

	c1->Update();

	system(("mkdir -p  `dirname plotFiles/"+outputFilePath+".png`").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".png").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".pdf").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".root").c_str());

	delete c1;
	delete legend;
	delete latex;
}

void plotter_DataMC(string analysisBranch, TH1D * h_DataOriginal, TH1D * h_MCOriginal, string outputFilePath, bool isLogY = false, int mcScale = -1, bool isLogX = false) {
	setTDRStyle();

	// clone histos
	auto h_Data = (TH1D*)h_DataOriginal->Clone();
	auto h_MC = (TH1D*)h_MCOriginal->Clone();

	if (mcScale < 0) h_Data->Scale(1.0/(h_Data->Integral()));
	else h_Data->Scale(1.0);
	// h_Data->SetLineWidth(0);
	// h_Data->SetLineColor(kOrange+8);
	// h_Data->SetLineStyle(0);
	h_Data->SetMarkerStyle(20);
	h_Data->SetMarkerSize(2);
	h_Data->SetMarkerColor(kBlack);


	if (mcScale < 0) h_MC->Scale(1.0/(h_MC->Integral()));
	// else h_MC->Scale(mcScale/(h_MC->Integral()));
	else h_MC->Scale(mcScale);
	h_MC->SetLineWidth(0);
	// h_MC->SetLineColor(kAzure+7);
	h_MC->SetLineStyle(0);
	h_MC->SetFillColor(kAzure+7);
   	h_MC->SetFillStyle(1001);

	auto c1 = new TCanvas("c1","c1",1050*2.0,750*2.0);	

	if (isLogY) c1->SetLogy();
	if (isLogX) c1->SetLogx();

	double histoMax = max(h_Data->GetMaximum(), h_MC->GetMaximum())*1.3;
	h_MC->SetMaximum(histoMax);
	h_MC->Draw("hist");	
	h_MC->GetXaxis()->SetTitleSize(.08);



	if (mcScale < 0) h_MC->GetYaxis()->SetTitle("a.u.");
	else h_MC->GetYaxis()->SetTitle("Events (Data) / Yield (MC)");
	h_MC->GetXaxis()->SetTitleOffset(1.0);
	h_MC->GetYaxis()->SetTitleOffset(1.5);
	h_Data->Draw("E1 same");

	// if (h_Data->GetMaximum() > h_MC->GetMaximum()) {
	// 	h_Data->SetMaximum(h_Data->GetMaximum()*1.3);
	// 	h_Data->Draw("E1");	
	// 	h_Data->GetYaxis()->SetTitle("a.u.");
	// 	h_Data->GetXaxis()->SetTitleOffset(1.0);
	// 	h_Data->GetYaxis()->SetTitleOffset(1.5);
	// 	h_MC->Draw("hist same");	
	// } else {
	// 	h_MC->SetMaximum(h_MC->GetMaximum()*1.3);
	// 	h_MC->Draw("hist");	
	// 	h_MC->GetYaxis()->SetTitle("a.u.");
	// 	h_MC->GetXaxis()->SetTitleOffset(1.0);
	// 	h_MC->GetYaxis()->SetTitleOffset(1.5);
	// 	h_Data->Draw("E1 same");			
	// }
	

	// auto legend = new TLegend(0.1,0.7,0.48,0.9, "", "NB");
	auto legend = new TLegend(0.68,0.76,.97,0.93);
	if (analysisBranch == "ZtoJPsi")
		legend->SetHeader("Z #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "HtoJPsi")
		legend->SetHeader("H #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "ZtoUpsilon")
		legend->SetHeader("Z #rightarrow #Upsilon + #gamma Analysis");
	if (analysisBranch == "HtoUpsilon")
		legend->SetHeader("H #rightarrow #Upsilon + #gamma Analysis");
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->AddEntry(h_Data, "Data", "lpe");
	if (mcScale < 0) legend->AddEntry(h_MC, "Signal", "f");
	else legend->AddEntry(h_MC, ("Signal (#times " + to_string(mcScale) + ")").c_str(), "f");
	legend->Draw();

    auto latex = new TLatex();
    latex->SetNDC();
    latex->SetTextFont(61);
    latex->SetTextSize(0.05);
    latex->DrawLatex(.17, 0.96, "CMS");
    latex->SetTextFont(52);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(11);
    latex->DrawLatex(.25, 0.96, "Preliminary");
    latex->SetTextFont(42);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.99, 0.96, "35.86 fb^{-1} (13 TeV, 2016) ");
	
	// h_MC->GetXaxis()->SetTitleSize(.08);
	// gPad->SetLeftMargin(0.17); 
	// gPad->SetRightMargin(0.05); 
	// gPad->SetTopMargin(0.08);
	gPad->SetBottomMargin(0.2);

	c1->Update();

	if (mcScale < 0){ 
		system(("mkdir -p  `dirname plotFiles/au/"+outputFilePath+".png`").c_str());
		c1->SaveAs(("plotFiles/au/"+outputFilePath+".png").c_str());
		c1->SaveAs(("plotFiles/au/"+outputFilePath+".pdf").c_str());
		c1->SaveAs(("plotFiles/au/"+outputFilePath+".root").c_str());
	} else {
		system(("mkdir -p  `dirname plotFiles/nEvts/"+outputFilePath+".png`").c_str());
		c1->SaveAs(("plotFiles/nEvts/"+outputFilePath+".png").c_str());
		c1->SaveAs(("plotFiles/nEvts/"+outputFilePath+".pdf").c_str());
		c1->SaveAs(("plotFiles/nEvts/"+outputFilePath+".root").c_str());
	}

	delete c1;
	delete legend;
	delete latex;
	delete h_MC;
	delete h_Data;

	// break recursive function
	if (analysisBranch == "ZtoJPsi")
		if (mcScale < 0) plotter_DataMC(analysisBranch, h_DataOriginal, h_MCOriginal, outputFilePath, isLogY, 50 , isLogX);
	if (analysisBranch == "HtoJPsi")
		if (mcScale < 0) plotter_DataMC(analysisBranch, h_DataOriginal, h_MCOriginal, outputFilePath, isLogY, 1000 , isLogX);
	if (analysisBranch == "ZtoUpsilon")
		if (mcScale < 0) plotter_DataMC(analysisBranch, h_DataOriginal, h_MCOriginal, outputFilePath, isLogY, 100 , isLogX);
	if (analysisBranch == "HtoUpsilon")
		if (mcScale < 0) plotter_DataMC(analysisBranch, h_DataOriginal, h_MCOriginal, outputFilePath, isLogY, 600000 , isLogX);

	if (mcScale > 0) return;

}

void plotter_DataMCSignalBackground(string analysisBranch, TH1D * h_DataOriginal, TH1D * h_MCSignalOriginal, TH1D * h_MCBackgroundOriginal, string outputFilePath, string xAxisTitle, bool isLogY = false, int mcSignalScale = -1, int mcBackgroundScale = -1, bool isLogX = false) {
	setTDRStyle();


	// h_Data->Sumw2();	
	// h_MCSignal->Sumw2();
	// h_MCBackground->Sumw2();	

	// clone histos
	auto h_Data = (TH1D*)h_DataOriginal->Clone();
	auto h_MCSignal = (TH1D*)h_MCSignalOriginal->Clone();
	auto h_MCBackground = (TH1D*)h_MCBackgroundOriginal->Clone();


	if (mcSignalScale < 0) h_Data->Scale(1.0/(h_Data->Integral()));
	else h_Data->Scale(1.0);
	h_Data->SetMarkerStyle(20);
	h_Data->SetMarkerSize(2);
	h_Data->SetMarkerColor(kBlack);


	// h_MCSignal->Scale(1.0/( (*h_MCSignal + *h_MCBackground).Integral() ));
	if (mcSignalScale < 0) h_MCSignal->Scale(1.0/( h_MCSignal->Integral() ));
	else h_MCSignal->Scale(mcSignalScale);
	h_MCSignal->SetLineWidth(0);
	h_MCSignal->SetLineStyle(0);
	h_MCSignal->SetFillColor(kAzure+7);
   	h_MCSignal->SetFillStyle(1001);

	// h_MCBackground->Scale(1.0/( (*h_MCSignal + *h_MCBackground).Integral() ));
	if (mcSignalScale < 0) h_MCBackground->Scale(1.0/( h_MCBackground->Integral() ));
	else h_MCBackground->Scale(mcBackgroundScale);
	h_MCBackground->SetLineWidth(3);
	h_MCBackground->SetLineStyle(9);
	h_MCBackground->SetLineColor(kGray+1);
	// h_MCBackground->SetFillColor(kGray);
	// h_MCBackground->SetFillColor(kBlack);
   	h_MCBackground->SetFillStyle(1001);
   	h_MCBackground->SetFillColorAlpha(kGray, 0.60);
   	// h_MCBackground->SetFillStyle(3315);

   	THStack * h_MC = new THStack("h_MC","");
   	h_MC->Add(h_MCSignal);
   	h_MC->Add(h_MCBackground);

	auto c1 = new TCanvas("c1","c1",1050*2.0,750*2.0);	

	if (isLogY) c1->SetLogy();
	if (isLogX) c1->SetLogx();

	double histoMax = max(h_Data->GetMaximum(), h_MC->GetMaximum())*1.3;
	h_MC->SetMaximum(histoMax);
	h_MC->Draw("AXIS");	
	h_MC->GetXaxis()->SetTitle(xAxisTitle.c_str());
	h_MC->Draw("hist nostack");	
	h_MC->GetXaxis()->SetTitleSize(.08);

	// h_MC->GetYaxis()->SetTitle("a.u.");
	if (mcSignalScale < 0) h_MC->GetYaxis()->SetTitle("a.u.");
	else h_MC->GetYaxis()->SetTitle("Events (Data) / Yield (MC)");
	h_MC->GetXaxis()->SetTitleOffset(1.0);
	h_MC->GetYaxis()->SetTitleOffset(1.5);
	h_Data->Draw("E1 same");
	
	gPad->SetLeftMargin(0.17); 
	gPad->SetRightMargin(0.05); 
	gPad->SetTopMargin(0.08);
	gPad->SetBottomMargin(0.2);

	auto legend = new TLegend(0.66,0.74,0.95,0.91);
	if (analysisBranch == "ZtoJPsi")
		legend->SetHeader("Z #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "HtoJPsi")
		legend->SetHeader("H #rightarrow J/#Psi + #gamma Analysis");
	if (analysisBranch == "ZtoUpsilon")
		legend->SetHeader("Z #rightarrow #Upsilon + #gamma Analysis");
	if (analysisBranch == "HtoUpsilon")
		legend->SetHeader("H #rightarrow #Upsilon + #gamma Analysis");
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->AddEntry(h_Data, "Data", "lpe");
	if (mcSignalScale < 0) legend->AddEntry(h_MCSignal, "Signal", "f");
	else legend->AddEntry(h_MCSignal, ("Signal (#times " + to_string(mcSignalScale) + ")").c_str(), "f");
	if (mcSignalScale < 0) legend->AddEntry(h_MCBackground, "Background", "f");
	else legend->AddEntry(h_MCBackground, ("Background (#times " + to_string(mcBackgroundScale) + ")").c_str(), "f");
	// legend->AddEntry(h_MCSignal, "Signal", "f");
	// legend->AddEntry(h_MCBackground, "Background", "f");
	legend->Draw();

    auto latex = new TLatex();
    latex->SetNDC();
    latex->SetTextFont(61);
    latex->SetTextSize(0.05);
    latex->DrawLatex(.17, 0.96, "CMS");
    latex->SetTextFont(52);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(11);
    latex->DrawLatex(.25, 0.96, "Preliminary");
    latex->SetTextFont(42);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.99, 0.96, "35.86 fb^{-1} (13 TeV, 2016) ");

	c1->Update();



	if (mcSignalScale < 0){ 
		system(("mkdir -p  `dirname plotFiles/au/"+outputFilePath+".png`").c_str());
		c1->SaveAs(("plotFiles/au/"+outputFilePath+".png").c_str());
		c1->SaveAs(("plotFiles/au/"+outputFilePath+".pdf").c_str());
		c1->SaveAs(("plotFiles/au/"+outputFilePath+".root").c_str());
	} else {
		system(("mkdir -p  `dirname plotFiles/nEvts/"+outputFilePath+".png`").c_str());
		c1->SaveAs(("plotFiles/nEvts/"+outputFilePath+".png").c_str());
		c1->SaveAs(("plotFiles/nEvts/"+outputFilePath+".pdf").c_str());
		c1->SaveAs(("plotFiles/nEvts/"+outputFilePath+".root").c_str());
	}

	
	delete c1;
	delete legend;
	delete latex;
	delete h_MCSignal;
	delete h_MCBackground;
	delete h_Data;

	// break recursive function
	if (analysisBranch == "ZtoJPsi")
		if (mcSignalScale < 0) plotter_DataMCSignalBackground(analysisBranch, h_DataOriginal, h_MCSignalOriginal, h_MCBackgroundOriginal, outputFilePath, xAxisTitle, isLogY, 100, 60, isLogX);
	if (analysisBranch == "HtoJPsi")
		if (mcSignalScale < 0) plotter_DataMCSignalBackground(analysisBranch, h_DataOriginal, h_MCSignalOriginal, h_MCBackgroundOriginal, outputFilePath, xAxisTitle, isLogY, 1600, 400, isLogX);
	if (analysisBranch == "ZtoUpsilon")
		if (mcSignalScale < 0) plotter_DataMCSignalBackground(analysisBranch, h_DataOriginal, h_MCSignalOriginal, h_MCBackgroundOriginal, outputFilePath, xAxisTitle, isLogY, 100, 3, isLogX);
	if (analysisBranch == "HtoUpsilon")
		if (mcSignalScale < 0) plotter_DataMCSignalBackground(analysisBranch, h_DataOriginal, h_MCSignalOriginal, h_MCBackgroundOriginal, outputFilePath, xAxisTitle, isLogY, 600000, 400, isLogX);
	
	if (mcSignalScale > 0) return;


}











