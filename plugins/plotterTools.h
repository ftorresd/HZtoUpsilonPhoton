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

void plotter_Pol(TH1D * h_unPol, TH1D * h_Pol, string outputFilePath, bool isLogY = false, bool isLogX = false) {
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
		h_unPol->GetYaxis()->SetTitle("a.u.");
		h_unPol->GetXaxis()->SetTitleOffset(1.0);
		h_unPol->GetYaxis()->SetTitleOffset(1.5);
		h_Pol->Draw("hist same");	
	} else {
		h_Pol->SetMaximum(h_Pol->GetMaximum()*1.3);
		h_Pol->Draw("hist");	
		h_Pol->GetYaxis()->SetTitle("a.u.");
		h_Pol->GetXaxis()->SetTitleOffset(1.0);
		h_Pol->GetYaxis()->SetTitleOffset(1.5);
		h_unPol->Draw("hist same");			
	}
	

	// auto legend = new TLegend(0.1,0.7,0.48,0.9, "", "NB");
	auto legend = new TLegend(0.67,0.76,0.96,0.93, "Z #rightarrow #Upsilon + #gamma #rightarrow #mu#mu + #gamma");
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
    latex->DrawLatex(.25, 0.96, "Preliminary");
    latex->SetTextFont(42);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.99, 0.96, "35.86 fb^{-1} (13 TeV, 2016) ");

	c1->Update();

	system(("mkdir -p  `dirname plotFiles/"+outputFilePath+".png`").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".png").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".pdf").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".root").c_str());

	delete c1;
	delete legend;
	delete latex;
}

void plotter_Single(TH1D * h1, string outputFilePath, string legendEntry, bool isLogY = false, bool isLogX = false) {
	setTDRStyle();

	h1->Scale(1.0/(h1->Integral()));
	h1->SetLineWidth(4);
	h1->SetLineColor(kOrange+8);
	h1->SetLineStyle(1);

	auto c1 = new TCanvas("c1","c1",1050*2.0,750*2.0);	

	h1->SetMaximum(h1->GetMaximum()*1.3);
	h1->GetXaxis()->SetTitleOffset(1.0);
	h1->GetYaxis()->SetTitleOffset(1.5);
	h1->Draw("hist");	
	h1->GetYaxis()->SetTitle("a.u.");
	
	auto legend = new TLegend(0.74,0.76,1.03,0.93, "Z #rightarrow #Upsilon + #gamma #rightarrow #mu#mu + #gamma");
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
    latex->DrawLatex(.25, 0.96, "Preliminary");
    latex->SetTextFont(42);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.99, 0.96, "35.86 fb^{-1} (13 TeV, 2016) ");

	c1->Update();

	system(("mkdir -p  `dirname plotFiles/"+outputFilePath+".png`").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".png").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".pdf").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".root").c_str());

	delete c1;
	delete legend;
	delete latex;
}


void plotter_LeadingTrailing(TH1D * h_Lead, TH1D * h_Trail, string outputFilePath, bool isLogY = false, bool isLogX = false) {
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
		h_Lead->GetYaxis()->SetTitle("a.u.");
		h_Lead->GetXaxis()->SetTitleOffset(1.0);
		h_Lead->GetYaxis()->SetTitleOffset(1.5);
		h_Trail->Draw("hist same");	
	} else {
		h_Trail->SetMaximum(h_Trail->GetMaximum()*1.3);
		h_Trail->Draw("hist");	
		h_Trail->GetYaxis()->SetTitle("a.u.");
		h_Trail->GetXaxis()->SetTitleOffset(1.0);
		h_Trail->GetYaxis()->SetTitleOffset(1.5);
		h_Lead->Draw("hist same");			
	}
	

	// auto legend = new TLegend(0.1,0.7,0.48,0.9, "", "NB");
	auto legend = new TLegend(0.74,0.76,1.03,0.93, "Z #rightarrow #Upsilon + #gamma #rightarrow #mu#mu + #gamma");
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
    latex->DrawLatex(.25, 0.96, "Preliminary");
    latex->SetTextFont(42);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.99, 0.96, "35.86 fb^{-1} (13 TeV, 2016) ");

	c1->Update();

	system(("mkdir -p  `dirname plotFiles/"+outputFilePath+".png`").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".png").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".pdf").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".root").c_str());

	delete c1;
	delete legend;
	delete latex;
}

void plotter_DataMC(TH1D * h_Data, TH1D * h_MC, string outputFilePath, bool isLogY = false, bool isLogX = false) {
	setTDRStyle();

	h_Data->Sumw2();	
	h_MC->Sumw2();	

	h_Data->Scale(1.0/(h_Data->Integral()));
	// h_Data->SetLineWidth(0);
	// h_Data->SetLineColor(kOrange+8);
	// h_Data->SetLineStyle(0);
	h_Data->SetMarkerStyle(20);
	h_Data->SetMarkerSize(2);
	h_Data->SetMarkerColor(kBlack);


	h_MC->Scale(1.0/(h_MC->Integral()));
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
	h_MC->GetYaxis()->SetTitle("a.u.");
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
	auto legend = new TLegend(0.74,0.76,1.03,0.93);
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->AddEntry(h_Data, "Data", "lpe");
	legend->AddEntry(h_MC, "Signal", "f");
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

	system(("mkdir -p  `dirname plotFiles/"+outputFilePath+".png`").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".png").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".pdf").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".root").c_str());

	delete c1;
	delete legend;
	delete latex;
}

void plotter_DataMCSignalBackground(TH1D * h_Data, TH1D * h_MCSignal, TH1D * h_MCBackground, string outputFilePath, string xAxisTitle, bool isLogY = false, bool isLogX = false) {
	setTDRStyle();

	// gPad->SetLeftMargin(0.05); 
	gPad->SetRightMargin(0.05); 
	gPad->SetTopMargin(0.08);

	h_Data->Sumw2();	
	h_MCSignal->Sumw2();
	h_MCBackground->Sumw2();	

	h_Data->Scale(1.0/(h_Data->Integral()));
	h_Data->SetMarkerStyle(20);
	h_Data->SetMarkerSize(2);
	h_Data->SetMarkerColor(kBlack);


	// h_MCSignal->Scale(1.0/( (*h_MCSignal + *h_MCBackground).Integral() ));
	h_MCSignal->Scale(1.0/( h_MCSignal->Integral() ));
	h_MCSignal->SetLineWidth(0);
	h_MCSignal->SetLineStyle(0);
	h_MCSignal->SetFillColor(kAzure+7);
   	h_MCSignal->SetFillStyle(1001);

	// h_MCBackground->Scale(1.0/( (*h_MCSignal + *h_MCBackground).Integral() ));
	h_MCBackground->Scale(1.0/( h_MCBackground->Integral() ));
	h_MCBackground->SetLineWidth(0);
	h_MCBackground->SetLineStyle(0);
	h_MCBackground->SetFillColor(kGray);
   	h_MCBackground->SetFillStyle(1001);

   	THStack * h_MC = new THStack("h_MC","");
   	h_MC->Add(h_MCBackground);
   	h_MC->Add(h_MCSignal);

	auto c1 = new TCanvas("c1","c1",1050*2.0,750*2.0);	

	if (isLogY) c1->SetLogy();
	if (isLogX) c1->SetLogx();

	double histoMax = max(h_Data->GetMaximum(), h_MC->GetMaximum())*1.3;
	h_MC->SetMaximum(histoMax);
	h_MC->Draw("AXIS");	
	h_MC->GetXaxis()->SetTitle(xAxisTitle.c_str());
	h_MC->Draw("hist");	
	h_MC->GetYaxis()->SetTitle("a.u.");
	h_MC->GetXaxis()->SetTitleOffset(1.0);
	h_MC->GetYaxis()->SetTitleOffset(1.5);
	h_Data->Draw("E1 same");
	

	auto legend = new TLegend(0.71,0.76,1.0,0.93);
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->AddEntry(h_Data, "Data", "lpe");
	legend->AddEntry(h_MCSignal, "Signal", "f");
	legend->AddEntry(h_MCBackground, "Background", "f");
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

	system(("mkdir -p  `dirname plotFiles/"+outputFilePath+".png`").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".png").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".pdf").c_str());
	c1->SaveAs(("plotFiles/"+outputFilePath+".root").c_str());

	delete c1;
	delete legend;
	delete latex;
	delete h_MC;
}











