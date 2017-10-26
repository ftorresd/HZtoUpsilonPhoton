// #################################################
// reads the ggNtuples and loads then into a TChain
// #################################################

#include "TChain.h"
#include "TTreeReader.h"

using namespace std;

TTreeReader * ggNtuplesFilesReader(vector<string> ggNtuplesFiles, int nFiles)  
{
	TChain * chain = new TChain("ggNtuplizer/EventTree");

	for(unsigned int i = 0; i < ggNtuplesFiles.size(); i++) {
		chain->AddFile( ggNtuplesFiles[i].c_str() );
	}
	// chain->Print();
	TTreeReader * reader = new TTreeReader(chain);
	return reader;
}


