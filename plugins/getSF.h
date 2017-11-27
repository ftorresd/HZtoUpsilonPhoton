#include "TH2.h"
#include "TFile.h"

using namespace std;

pair<double,double> getTriggerSF(bool isMC, anaMuon muon, anaPhoton photon, TFile * sfFile) {
	pair<double,double> sf = {1.0, 0.0};

	// data
	if (!isMC) return sf;

	// MC
	if(fabs(photon.photonSCEta) < 1.4442) {
		auto sfHisto = (TH2D*)sfFile->Get("hM_Eff_MuPtPhoEt_DataMCRatio_DYJetsToLL_aMCatNLO_PU_nominal_EB"); 	
		sf.first = sfHisto->GetBinContent(sfHisto->FindBin(muon.Pt(), photon.Pt()));
		sf.second = sfHisto->GetBinError(sfHisto->FindBin(muon.Pt(), photon.Pt()));
		//clean up memory
		delete sfHisto;
	} else {
		auto sfHisto = (TH2D*)sfFile->Get("hM_Eff_MuPtPhoEt_DataMCRatio_DYJetsToLL_aMCatNLO_PU_nominal_EE"); 	
		sf.first = sfHisto->GetBinContent(sfHisto->FindBin(muon.Pt(), photon.Pt()));
		sf.second = sfHisto->GetBinError(sfHisto->FindBin(muon.Pt(), photon.Pt()));
		//clean up memory
		delete sfHisto;
	}

	return sf;




}

pair<double,double> getMuonIDSF(bool isMC, anaMuon muon, TFile * sfFile) {
	pair<double,double> sf = {1.0, 0.0};

	// data
	if (!isMC) return sf;

	// MC
	auto sfHistoValue = (TH2D*)sfFile->Get("FINAL"); 	
	sf.first = sfHistoValue->GetBinContent(sfHistoValue->FindBin(muon.Eta(), muon.Pt()));
	auto sfHistoError = (TH2D*)sfFile->Get("ERROR"); 
	sf.second = sfHistoError->GetBinError(sfHistoError->FindBin(muon.Eta(), muon.Pt()));
	return sf;

	//clean up memory
	delete sfHistoValue;
	delete sfHistoError;
}

pair<double,double> getPhotonMVAIDSF(bool isMC, anaPhoton photon, TFile * sfFile) {
	pair<double,double> sf = {1.0, 0.0};

	// data
	if (!isMC) return sf;

	// MC
	auto sfHisto = (TH2D*)sfFile->Get("EGamma_SF2D"); 	
	sf.first = sfHisto->GetBinContent(sfHisto->FindBin(photon.photonSCEta, photon.Pt()));
	sf.second = sfHisto->GetBinError(sfHisto->FindBin(photon.photonSCEta, photon.Pt()));
	return sf;

	//clean up memory
	delete sfHisto;
}

pair<double,double> getPhotonEleVetoSF(bool isMC, anaPhoton photon) {
	pair<double,double> sf = {1.0, 0.0};

	// data
	if (!isMC) return sf;

	// MC
	if(fabs(photon.photonSCEta) < 1.4442) sf = {0.9938, 0.0119};
	if(fabs(photon.photonSCEta) > 1.566 && fabs(photon.photonSCEta) < 2.5) sf = {0.9875, 0.0044};
	return sf;
}
