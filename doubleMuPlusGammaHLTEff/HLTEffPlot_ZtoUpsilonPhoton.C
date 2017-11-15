// ######################################################
// Z --> Upsilon + Photon
// ######################################################
// HLT Eff Plotter



#include <iostream>
#include <algorithm>
#include <math.h>  
#include <stdlib.h>

#include "../plugins/tdrstyle.C"

#include "TFile.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "TH1.h"
#include "TEfficiency.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"

using namespace std;

const auto muonMass = 105.6583745/1000.0; //GeV



TTreeReader * filesReader(vector<string> ntuplesFiles, int nFiles)  
{
	TChain * chain = new TChain("outTree_HLTTnPEff_ZtoUpsilonPhoton");

	for(unsigned int i = 0; i < ntuplesFiles.size(); i++) {
		chain->AddFile( ntuplesFiles[i].c_str() );
	}
	// chain->Print();
	TTreeReader * reader = new TTreeReader(chain);
	return reader;
}


void HLTEffPlot_ZtoUpsilonPhoton(vector<string> ntuplesFiles, int nFiles = -1)  
{
  	setTDRStyle();

	////////////////////////////////////////////////////////////////////
	// loads the ntuples
	if (nFiles > 0) {
		ntuplesFiles.resize(nFiles);	
	}
	TTreeReader * dataReader = filesReader( ntuplesFiles, nFiles );
	TTree * dataTree = dataReader->GetTree();

	////////////////////////////////////////////////////////////////////
	// define readers
	// tag muons
	TTreeReaderValue< TLorentzVector > tagMuon(*dataReader, "tagMuon");
	TTreeReaderValue< int > tagMuonType(*dataReader, "tagMuonType");
	TTreeReaderValue< unsigned short > tagMuonIDbit(*dataReader, "tagMuonIDbit");
	TTreeReaderValue< int > tagMuonMatches(*dataReader, "tagMuonMatches");
	TTreeReaderValue< ULong64_t > tagMuonFiredTrgs(*dataReader, "tagMuonFiredTrgs");

	// probe muons
	TTreeReaderValue< TLorentzVector > probeMuon(*dataReader, "probeMuon");
	TTreeReaderValue< int > probeMuonMatches(*dataReader, "probeMuonMatches");
	TTreeReaderValue< ULong64_t > probeMuonFiredTrgs(*dataReader, "probeMuonFiredTrgs");

	// photons
	TTreeReaderValue< TLorentzVector > photon(*dataReader, "photon");
	TTreeReaderValue< float > photonIDMVA(*dataReader, "photonIDMVA");
	TTreeReaderValue< float > photonR9(*dataReader, "photonR9");
	TTreeReaderValue< unsigned short > photonIDbit(*dataReader, "photonIDbit");

	////////////////////////////////////////////////////////////////////
	//define histos
	// pT
	// Float_t ptBins[] = { 2, 2.5, 2.75, 3, 3.25, 3.5, 3.75, 4, 4.5, 5, 6, 8, 10, 15, 20, 25, 30, 40, 50, 60, 120, 200 };
	// Float_t ptBins[] = { 2, 2.5, 2.75, 3, 3.25, 3.5, 3.75, 4, 4.5, 5, 6, 8, 10, 15, 20, 25, 30, 40, 50, 60, 120, 200, 300, 500, 700, 1200 };
	Float_t ptBins[] = { 0, 5, 7, 10, 12, 14, 16, 18, 20, 22, 25, 28, 32, 38, 42, 50, 60 };
	Int_t  ptBinnum = sizeof(ptBins)/sizeof(Float_t) - 1;
	auto h_numPt = new TH1F("h_numPt","h_numPt", ptBinnum, ptBins);
	auto h_denPt = (TH1F*)h_numPt->Clone("h_denPt");

  

	////////////////////////////////////////////////////////////////////
	// numer of entries
	auto totalPairs = dataTree->GetEntries();
	auto printEvery = 1000;
	cout << "\nN. Entries: " << totalPairs << endl;
	cout << "\nPrinting every: " << printEvery << " TnP pairs" << endl;
	cout << "\nLooping over pairs... \n" << endl;

	// data->Print();

	////////////////////////////////////////////////////////////////////
	// main loop
	auto iPair = 0;
	while (dataReader->Next()) { // loop over pairs
		if (iPair % printEvery == 0) cout << "----------------------------------------> Events read: " << iPair << " / " << totalPairs << " - ~"<< round(((float)iPair/(float)totalPairs)*100) << "%"<< endl;
		iPair++;

		// photon conditions
		auto goodPhoton = true;
		goodPhoton *= (photon->Pt() > 35.0) ? true : false;
		goodPhoton *= (((*photonIDbit >> 2) & 1) == 1) ? true : false; // isTightPhoton

		// tag conditions
		auto goodTag = true;
		goodTag *= (tagMuon->Pt() > 26.0) ? true : false;
		goodTag *= (((*tagMuonIDbit >> 2) & 1) == 1) ? true : false; // isTightMuon
		// if (((*tagMuonIDbit >> 1) & 1) != 1){
		// 	cout << "tagMuonIDbit: " << *tagMuonIDbit << endl ;
		// } else {
		// cout << "ui" << endl; // isTightMuon
		// }
		goodTag *= (((*tagMuonFiredTrgs >> 30) & 1) == 1) ? true : false; // HLT_IsoMu24
		// if (((*tagMuonFiredTrgs >> 1) & 1) != 1){
		// 	// cout << "tagMuonFiredTrgs: " << *tagMuonFiredTrgs << endl ;
		// } else {
		// // cout << "ui" << endl; // isTightMuon
		// }


		if (goodTag && goodPhoton) {
			h_denPt->Fill(probeMuon->Pt());
			// probe conditions
			auto goodProbe = true;
			goodProbe *= (probeMuon->Pt() > 2.0) ? true : false;
			// goodProbe *= (((*probeMuonFiredTrgs >> 29) & 1) == 1) ? true : false; // HLT_DoubleMu20_7...
			goodProbe *= (((*probeMuonFiredTrgs >> 29) & 1) == 1) ? true : false; // HLT_Mu17_IsoPhoton...
			if (goodProbe) h_numPt->Fill(probeMuon->Pt());
		}


		// for (auto iPair = 0; iPair < totalPairs; iPair++) { //loop over tag muons candidates
		// 	TLorentzVector * tagMuonCand = new TLorentzVector();
		// 	tagMuonCand->SetPtEtaPhiM(muPt[iMuon], muEta[iMuon], muPhi[iMuon], muonMass);
		// 		for (int jMuon = 0; jMuon < *nMu; jMuon++) { //loop over probe muons candidates
		// 			TLorentzVector * probeMuonCand = new TLorentzVector();
		// 			probeMuonCand->SetPtEtaPhiM(muPt[jMuon], muEta[jMuon], muPhi[jMuon], muonMass);
		// 			if (((*tagMuonCand+*probeMuonCand).M() > 2.95 && (*tagMuonCand+*probeMuonCand).M() < 3.30) && (muCharge[iMuon]*muCharge[jMuon] < 0) && (iMuon != jMuon)) {
		// 				// Good TnP pair!
		// 				tagMuon = *tagMuonCand;
		// 				probeMuon = *probeMuonCand;

		// 				if (*nPho > 0) {
		// 				// photons
		// 				auto maxEtResult =  max_element(phoEt.begin(), phoEt.end()); // get max Et
		// 				auto indexMaxPt = distance(phoEt.begin(), maxEtResult); // get max Et index
		// 				photon.SetPtEtaPhiM(phoEt[indexMaxPt], phoEta[indexMaxPt], phoPhi[indexMaxPt], 0.);
		// 				photonIDMVA = phoIDMVA[indexMaxPt];
		// 				photonR9 = phoR9[indexMaxPt];
		// 				photonIDbit = phoIDbit[indexMaxPt];

		// 			    //save tnp pair the tree
		// 				// outTree->Fill(); 
		// 			}
		// 		}
		// 	}	
		// }
    } // end loop over events

    // post-processing 
	auto h_effPt = new TEfficiency(*h_numPt, *h_denPt);
	h_effPt->SetTitle("; Muon p_{T} (GeV); Efficiency");
	auto c1 = new TCanvas("c1","c1",200,10,1050,750);	
	h_effPt->Draw("AP");
	c1->Update();
	h_effPt->GetPaintedGraph()->GetYaxis()->SetRangeUser(0., 1.3);

    c1->cd();
    auto leg = new TLegend(0.37, 0.8, 0.75, 0.9);
    leg->SetHeader("HLT_DoubleMu20_7_Mass0to30_Photon23_v*");
    // header = leg.GetListOfPrimitives();
    // header.SetTextColor(1)
    // header.SetTextFont(43)
    // header.SetTextSize(20)
    leg->AddEntry(h_effPt, "Data", "LP");
    leg->SetBorderSize(0);
    leg->SetTextFont(43);
    leg->SetTextSize(20);
    leg->Draw();

    auto latex = new TLatex();
    latex->SetNDC();
    latex->SetTextFont(61);
    latex->SetTextSize(0.06);
    latex->DrawLatex(.2, 0.85, "CMS");
    latex->SetTextFont(52);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(11);
    latex->DrawLatex(.2, 0.8, "Preliminary");
    latex->SetTextFont(42);
    latex->SetTextSize(0.038);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.97, 0.96, "10.6 fb^{-1} (13 TeV, Run2017F) ");
    

	c1->Update();
	system("rm -fr plotFiles; mkdir plotFiles");
	c1->SaveAs("plotFiles/h_effPt.png");
	c1->SaveAs("plotFiles/h_effPt.pdf");
	c1->SaveAs("plotFiles/h_effPt.root");



} //end ana_ZtoUpsilonPhoton


