#include "TH1.h"
#include "TFile.h"

class puWeight {
	public:
		bool isMC;
	  	TFile * puFile;
	    TH1D * puHisto_nominal;
	    TH1D * puHisto_up;
	    TH1D * puHisto_down;
	    puWeight(bool mc, string puFileName);
	    double getWeight_nominal(float mcPU);
	    double getWeight_up(float mcPU);
	    double getWeight_down(float mcPU);
	    // double getWeightErr(float mcPU);
};

puWeight::puWeight (bool mc, string puFileName) {
	isMC = mc;
	if (isMC) {
		puFile = new TFile(puFileName.c_str());	
		puHisto_nominal = (TH1D*)puFile->Get("pileup_nominal"); 
		puHisto_up = (TH1D*)puFile->Get("pileup_up"); 
		puHisto_down = (TH1D*)puFile->Get("pileup_down"); 
	} else {
		puFile = nullptr;
		puHisto_nominal = nullptr;
		puHisto_up = nullptr;
		puHisto_down = nullptr;
	}
	
	
}

double puWeight::getWeight_nominal (float mcPU) {
	if (this->isMC) {
		return this->puHisto_nominal->GetBinContent(puHisto_nominal->FindBin(mcPU) );
	} else {
		return 1.0;
	}
}

double puWeight::getWeight_up (float mcPU) {
	if (this->isMC) {
		return this->puHisto_up->GetBinContent(puHisto_up->FindBin(mcPU) );
	} else {
		return 1.0;
	}
}

double puWeight::getWeight_down (float mcPU) {
	if (this->isMC) {
		return this->puHisto_down->GetBinContent(puHisto_down->FindBin(mcPU) );
	} else {
		return 1.0;
	}
}


// double puWeight::getWeightErr (float mcPU) {
// 	if (this->isMC) {
// 		return this->puHisto->GetBinError(puHisto->FindBin(mcPU) );
// 	} else {
// 		return 1.0;
// 	}
// }