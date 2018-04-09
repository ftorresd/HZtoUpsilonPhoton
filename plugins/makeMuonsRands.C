#include <iostream>
#include <algorithm>
#include <math.h>  

#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "TRandom3.h"
#include "TROOT.h"

#include "TChain.h"


// #include "plugins/ggNtuplesFilesReader.h"


using namespace std;


void makeMuonsRands(vector<string> ggNtuplesFiles, string outFileAppend = "") {
	string outputFileName = "data/muonsRands/muonsRands_"+ outFileAppend + ".root";
	TFile * outFile  = new TFile(outputFileName.c_str(),"RECREATE","");
	TTree * outTree = new TTree("muonsRands", "Muons Randon Numbers");


	TChain * chain = new TChain("ggNtuplizer/EventTree");
	
	for(unsigned int i = 0; i < ggNtuplesFiles.size(); i++) {
		// chain->AddFile( ggNtuplesFiles[i].c_str() );
		chain->Add( ggNtuplesFiles[i].c_str() );
	}
	TTreeReader * dataReader  = new TTreeReader(chain);
	TTree * dataTree = dataReader->GetTree();
	chain->SetBranchStatus("*", 0);
	chain->SetBranchStatus("nMu", 1);
	TTreeReaderValue< int > nMu(*dataReader, "nMu");


	//output objects 
	vector<double> rand1;
	outTree->Branch("rand1",&rand1);

	vector<double> rand2;
	outTree->Branch("rand2",&rand2);

	unique_ptr<TRandom3> rand3(new TRandom3);

	////////////////////////////////////////////////////////////////////
	// numer of entries
	auto totalEvts = dataTree->GetEntries();
	auto printEvery = 100000;
	cout << "\nN. Entries (" << outFileAppend <<  "): " << totalEvts << endl;
	cout << "\nPrinting every: " << printEvery << " events" << endl;
	cout << "\nLooping over events... \n" << endl;

	auto iEvt = 0;
	while (dataReader->Next()) { // loop over events
		if (iEvt % printEvery == 0) cout << "----------------------------------------> (makeMuonsRands) Events read (" << outFileAppend << "): " << iEvt << " / " << totalEvts << " - ~"<< round(((float)iEvt/(float)totalEvts)*100) << "%"<< endl;
		iEvt++;
		rand1.clear();
		rand2.clear();

		for (int iMuon = 0; iMuon < (*nMu)+1; iMuon++) { //loop over muons
			rand1.push_back(rand3->Rndm());	
			rand2.push_back(rand3->Rndm());
		}
		outTree->Fill();
	}
    outFile->Write();
    outFile->Close();

}
	