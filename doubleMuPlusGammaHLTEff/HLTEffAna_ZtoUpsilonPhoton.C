// ######################################################
// Z --> Upsilon + Photon
// ######################################################
// HLT Eff Tree


#include <iostream>
#include <algorithm>
#include <math.h>  

#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"

#include "../plugins/ggNtuplesFilesReader.h"

using namespace std;

const auto muonMass = 105.6583745/1000.0; //GeV


void HLTEffAna_ZtoUpsilonPhoton(vector<string> ggNtuplesFiles, int nFiles = -1, string outFileAppend = "")  
{
	////////////////////////////////////////////////////////////////////
	// output tree
	// TFile * outFile  = new TFile("outTree_HLTTnPEff_ZtoUpsilonPhoton.root","RECREATE","ZtoUpsilonPhoton output analysis tree");
	string outputFileName = "outTree_HLTTnPEff_ZtoUpsilonPhoton_"+ outFileAppend + ".root";
	TFile * outFile  = new TFile(outputFileName.c_str(),"RECREATE","ZtoUpsilonPhoton output analysis tree");
	TTree * outTree = new TTree("outTree_HLTTnPEff_ZtoUpsilonPhoton","ZtoUpsilonPhoton output analysis tree");

	////////////////////////////////////////////////////////////////////
	// loads the ggNtuples
	if (nFiles > 0) {
		ggNtuplesFiles.resize(nFiles);	
	}
	TTreeReader * dataReader = ggNtuplesFilesReader( ggNtuplesFiles, nFiles );
	TTree * dataTree = dataReader->GetTree();

	////////////////////////////////////////////////////////////////////
	// define readers
	TTreeReaderValue< int > run(*dataReader, "run");

	// muons
	TTreeReaderValue< int > nMu(*dataReader, "nMu");
	TTreeReaderArray< float > muPt(*dataReader, "muPt");
	TTreeReaderArray< float > muEta(*dataReader, "muEta");
	TTreeReaderArray< float > muPhi(*dataReader, "muPhi");
	TTreeReaderArray< int > muCharge(*dataReader, "muCharge");
	TTreeReaderArray< int > muType(*dataReader, "muType");
	TTreeReaderArray< unsigned short > muIDbit(*dataReader, "muIDbit");
	TTreeReaderArray< int > muMatches(*dataReader, "muMatches");
	TTreeReaderArray< ULong64_t > muFiredTrgs(*dataReader, "muFiredTrgs");
	
	// photons
	TTreeReaderValue< int > nPho(*dataReader, "nPho");
	TTreeReaderArray< float > phoEt(*dataReader, "phoEt");
	TTreeReaderArray< float > phoEta(*dataReader, "phoEta");
	TTreeReaderArray< float > phoPhi(*dataReader, "phoPhi");
	TTreeReaderArray< float > phoIDMVA(*dataReader, "phoIDMVA");
	TTreeReaderArray< float > phoR9(*dataReader, "phoR9");
	TTreeReaderArray< unsigned short > phoIDbit(*dataReader, "phoIDbit");



	////////////////////////////////////////////////////////////////////
	//output objects - TAG
	TLorentzVector tagMuon;
	outTree->Branch("tagMuon",&tagMuon);

	int tagMuonType;
	outTree->Branch("tagMuonType",&tagMuonType);

	unsigned short tagMuonIDbit;
	outTree->Branch("tagMuonIDbit",&tagMuonIDbit);

	int tagMuonMatches;
	outTree->Branch("tagMuonMatches",&tagMuonMatches);

	ULong64_t tagMuonFiredTrgs;
	outTree->Branch("tagMuonFiredTrgs",&tagMuonFiredTrgs);

	//output objects - PROBE
	TLorentzVector probeMuon;
	outTree->Branch("probeMuon",&probeMuon);

	int probeMuonMatches;
	outTree->Branch("probeMuonMatches",&probeMuonMatches);

	ULong64_t probeMuonFiredTrgs;
	outTree->Branch("probeMuonFiredTrgs",&probeMuonFiredTrgs);
	

	//output objects - PHOTON
	TLorentzVector photon;
	outTree->Branch("photon",&photon);

	float photonIDMVA;
	outTree->Branch("photonIDMVA",&photonIDMVA);

	float photonR9;
	outTree->Branch("photonR9",&photonR9);

	unsigned short photonIDbit;
	outTree->Branch("photonIDbit",&photonIDbit);



	////////////////////////////////////////////////////////////////////
	// numer of entries
	auto totalEvts = dataTree->GetEntries();
	auto printEvery = 10000;
	cout << "\nN. Entries: " << totalEvts << endl;
	cout << "\nPrinting every: " << printEvery << " events" << endl;
	cout << "\nLooping over events... \n" << endl;

	// data->Print();

	////////////////////////////////////////////////////////////////////
	// main loop
	auto iEvt = 0;
	while (dataReader->Next()) { // loop over events
		if (iEvt % printEvery == 0) cout << "----------------------------------------> Events read: " << iEvt << " / " << totalEvts << " - ~"<< round(((float)iEvt/(float)totalEvts)*100) << "%"<< endl;
		iEvt++;
		for (int iMuon = 0; iMuon < *nMu; iMuon++) { //loop over tag muons candidates
			TLorentzVector * tagMuonCand = new TLorentzVector();
			tagMuonCand->SetPtEtaPhiM(muPt[iMuon], muEta[iMuon], muPhi[iMuon], muonMass);
				for (int jMuon = 0; jMuon < *nMu; jMuon++) { //loop over probe muons candidates
					TLorentzVector * probeMuonCand = new TLorentzVector();
					probeMuonCand->SetPtEtaPhiM(muPt[jMuon], muEta[jMuon], muPhi[jMuon], muonMass);
					if (((*tagMuonCand+*probeMuonCand).M() > 2.95 && (*tagMuonCand+*probeMuonCand).M() < 3.30) && (muCharge[iMuon]*muCharge[jMuon] < 0) && (iMuon != jMuon)) {
						// Good TnP pair!
						tagMuon = *tagMuonCand;
						probeMuon = *probeMuonCand;
						tagMuonType = muType[iMuon];
						tagMuonIDbit = muIDbit[iMuon];
						tagMuonMatches = muMatches[iMuon];
						probeMuonMatches = muMatches[jMuon];
						tagMuonFiredTrgs = muFiredTrgs[iMuon];
						probeMuonFiredTrgs = muFiredTrgs[jMuon];

						if (*nPho > 0) {
						// photons
						auto maxEtResult =  max_element(phoEt.begin(), phoEt.end()); // get max Et
						auto indexMaxPt = distance(phoEt.begin(), maxEtResult); // get max Et index
						photon.SetPtEtaPhiM(phoEt[indexMaxPt], phoEta[indexMaxPt], phoPhi[indexMaxPt], 0.);
						photonIDMVA = phoIDMVA[indexMaxPt];
						photonR9 = phoR9[indexMaxPt];
						photonIDbit = phoIDbit[indexMaxPt];

					    //save tnp pair the tree
						outTree->Fill(); 
					}
				}
			}	
		}
    } // end loop over events

    // post-processing 
    
    // outTree->Print();
    outFile->Write();

} //end ana_ZtoUpsilonPhoton


