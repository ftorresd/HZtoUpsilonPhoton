// ######################################################
// Z --> Upsilon + Photon
// ######################################################
// Analysis Code
// Description:  - Reads the ggNtuples
//               - Skim the sample
//               - Apply corrections and cuts           
//               - Produces a ntuple read for plotting  
// ######################################################


#include <iostream>
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"

#include "../plugins/ggNtuplesFilesReader.h"

using namespace std;

const auto muonMass = 105.6583745/1000.0; //GeV


void HLTEffAna_ZtoUpsilonPhoton(vector<string> ggNtuplesFiles, int nFiles = -1)  
{
	////////////////////////////////////////////////////////////////////
	// output tree
	TFile * outFile  = new TFile("outTree_HLTTnPEff_ZtoUpsilonPhoton.root","RECREATE","ZtoUpsilonPhoton output analysis tree");
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
	TTreeReaderArray< float > phoEt(*dataReader, "phoEt");
	TTreeReaderArray< float > phoIDMVA(*dataReader, "phoIDMVA");

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
	
	////////////////////////////////////////////////////////////////////
	// numer of entries
	cout << "\nN. Entries: " << dataTree->GetEntries() << endl;
	// data->Print();

	////////////////////////////////////////////////////////////////////
	// main loop
	while (dataReader->Next()) { // loop over events
		// cout << "nMu: " << *nMu << endl;
		for (int iMuon = 0; iMuon < *nMu; iMuon++) { //loop over tag muons candidates
			TLorentzVector * tagMuonCand = new TLorentzVector();
			tagMuonCand->SetPtEtaPhiM(muPt[iMuon], muEta[iMuon], muPhi[iMuon], muonMass);
				for (int jMuon = 0; jMuon < *nMu; jMuon++) { //loop over probe muons candidates
					TLorentzVector * probeMuonCand = new TLorentzVector();
					probeMuonCand->SetPtEtaPhiM(muPt[jMuon], muEta[jMuon], muPhi[jMuon], muonMass);
					if (((*tagMuonCand+*probeMuonCand).M() > 2.95 && (*tagMuonCand+*probeMuonCand).M() < 3.30) && (muCharge[iMuon]*muCharge[jMuon] < 0) && (iMuon != jMuon)) {
						// cout << "Good TnP pair!" << endl;
						tagMuon = *tagMuonCand;
						probeMuon = *probeMuonCand;


						outTree->Fill(); //save tnp pair the tree
					}
				}	
			}
    } // end loop over events

    // post-processing 
    
    outTree->Print();
    outFile->Write();

} //end ana_ZtoUpsilonPhoton


