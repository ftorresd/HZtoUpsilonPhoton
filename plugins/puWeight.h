#include "TH1.h"
#include "TFile.h"

class puWeight {
	public:
		bool isMC;
	  	TFile * puFile;
	    TH1D * puHisto;
	    puWeight(bool mc, string puFileName);
	    double getWeight(float mcPU);
	    double getWeightErr(float mcPU);
};

puWeight::puWeight (bool mc, string puFileName) {
	isMC = mc;
	if (isMC) {
		puFile = new TFile(puFileName.c_str());	
		puHisto = (TH1D*)puFile->Get("pileup"); 
	} else {
		puFile = nullptr;
		puHisto = nullptr;
	}
	
	
}

double puWeight::getWeight (float mcPU) {
	if (this->isMC) {
		return this->puHisto->GetBinContent(puHisto->FindBin(mcPU) );
	} else {
		return 1.0;
	}
}

double puWeight::getWeightErr (float mcPU) {
	if (this->isMC) {
		return this->puHisto->GetBinError(puHisto->FindBin(mcPU) );
	} else {
		return 1.0;
	}
}