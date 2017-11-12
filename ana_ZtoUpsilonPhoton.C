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

#include "plugins/ggNtuplesFilesReader.h"

using namespace std;


void ana_ZtoUpsilonPhoton(vector<string> ggNtuplesFiles, int nFiles = -1)  
{
	// output tree
	TFile outFile("outTree_ZtoUpsilonPhoton.root","RECREATE","ZtoUpsilonPhoton output analysis tree");
	TTree * outTree = new TTree("outTree_ZtoUpsilonPhoton","ZtoUpsilonPhoton output analysis tree");
	
	//output objects
	TLorentzVector * v2 = new TLorentzVector(1., 1., 1., 1.);
	outTree->Branch("v2",&v2);

	// loads the ggNtuples
	if (nFiles > 0) {
		ggNtuplesFiles.resize(nFiles);	
	}
	TTreeReader * dataReader = ggNtuplesFilesReader( ggNtuplesFiles, nFiles );
	TTree * dataTree = dataReader->GetTree();

	// define readers
	TTreeReaderValue< int > run(*dataReader, "run");
	TTreeReaderArray< float > phoE(*dataReader, "phoE");
	TTreeReaderArray< vector<float> > eleGSFEta(*dataReader, "eleGSFEta");  
	

	cout << "N. Entries: " << dataTree->GetEntries() << endl;
	// data->Print();

	while (dataReader->Next()) { // loop over events
		// cout << "Run: " << *run << endl;
		for (unsigned int i = 0; i < phoE.GetSize(); i++){
			// cout << "phoE: " << phoE[i] << endl;
		}
		// cout << "eleGSFEta: " << eleGSFEta.GetSize() << endl;
		// for (unsigned int i = 0; i < eleGSFEta.GetSize(); i++){
		// 	cout << "eleGSFEta: " << eleGSFEta[i].size() << endl;
		// }
    } // end loop over events

    // post-processing 
    outTree->Fill();
    outTree->Print();
    outFile.Write();

} //end ana_ZtoUpsilonPhoton


