#include <iostream>
#include <algorithm>
#include <math.h> 
#include <fstream>
#include <string>
#include <iomanip>



#include "TFile.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
// #include "TRandom3.h"
// #include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TDirectory.h"
#include "TObjString.h"



#include "plugins/ggNtuplesFilesReader.h"
// #include "plugins/roccor2016/RoccoR.cc"
#include "plugins/deltaR_deltaPhi.h"
#include "plugins/anaObjects.h"
// #include "plugins/puWeight.h"
#include "plugins/upsilonPolarizationAngle.h"
// #include "plugins/getSF.h"


#ifdef __CINT__
#pragma link C++ class anaMuon+;
#pragma link C++ class anaPhoton+;
#pragma link C++ class anaGenPart+;
// #pragma link C++ class TLorentzVector+;
#endif

using namespace std;

void genFiller(bool plusIsLeading, TH1D * h_Gen_Leading, TH1D * h_Gen_Trailing, double plusVar, double minusVar, double weight = 1.0) {
	if (plusIsLeading) {
		h_Gen_Leading->Fill(plusVar, weight); 
		h_Gen_Trailing->Fill(minusVar, weight); 
	} else { 
		h_Gen_Leading->Fill(minusVar, weight); 
		h_Gen_Trailing->Fill(plusVar, weight); 
	}
}


void plots_ZtoUpsilonPhoton(vector<string> ntuplesToPlotFilesData, string outHistoAppend, string analysisBranch, string selCategory, string systMaskYields = "ZZZZZ", bool isData = true)  
{
	// output tree
	// TFile outFile("outTree_ZtoUpsilonPhoton.root","RECREATE","ZtoUpsilonPhoton output analysis tree");
	string outputFileName = "outputHistos/outHistos_HZtoUpsilonPhoton_"+ outHistoAppend + "_" + analysisBranch + "_" + selCategory + "_" + systMaskYields + ".root";
	TFile * outFile  = new TFile(outputFileName.c_str(),"RECREATE","HZtoUpsilonPhoton output histos");


	////////////////////////////////////////////////////////
	// loads the ntuples 
	TTreeReader * dataReader = ggNtuplesFilesReader( ntuplesToPlotFilesData, "outTree_ZtoUpsilonPhoton" );
	TTree * dataTree = dataReader->GetTree();



	////////////////////////////////////////////////////////////////////
	// define readers

	TTreeReaderValue< TObjString > sampleSource(*dataReader, "sampleSource");


	TTreeReaderValue< anaGenPart > genMuPlus(*dataReader, "genMuPlus");
	TTreeReaderValue< anaGenPart > genMuMinus(*dataReader, "genMuMinus");
	TTreeReaderValue< anaGenPart > genPhoton(*dataReader, "genPhoton");

	TTreeReaderValue< anaMuon > leadingMuon(*dataReader, "leadingMuon");
	TTreeReaderValue< anaMuon > trailingMuon(*dataReader, "trailingMuon");
	TTreeReaderValue< anaPhoton > leadingPhoton(*dataReader, "leadingPhoton");


	// can't figure it ou t why TTreeReaderValue don't work for TLorentzVector
	// TTreeReaderValue< TLorentzVector > recoUpsilon(*dataReader, "recoUpsilon");
	// TTreeReaderValue< TLorentzVector > recoZ(*dataReader, "recoZ");

	// TLorentzVector * recoUpsilon;
	// dataTree->SetBranchAddress("recoUpsilon",&recoUpsilon);
	// TLorentzVector * recoZ;
	// dataTree->SetBranchAddress("recoZ",&recoZ);

	
	TTreeReaderValue< bool > isGoodEvent(*dataReader, "isGoodEvent");
	TTreeReaderValue< bool > goodTriggerEvt(*dataReader, "goodTriggerEvt");
	TTreeReaderValue< bool > goodMuonPairSel(*dataReader, "goodMuonPairSel");
	TTreeReaderValue< bool > goodMuonPairPreSel(*dataReader, "goodMuonPairPreSel");
	TTreeReaderValue< bool > goodPhotonSel(*dataReader, "goodPhotonSel");



	TTreeReaderValue< bool > isMC(*dataReader, "isMC");

	TTreeReaderValue< double > puWgt_nominal(*dataReader, "puWgt_nominal");
	TTreeReaderValue< double > puWgt_up(*dataReader, "puWgt_up");
	TTreeReaderValue< double > puWgt_down(*dataReader, "puWgt_down");
	TTreeReaderValue< double > polWgt(*dataReader, "polWgt");
	TTreeReaderValue< pair<double,double> > muonIDSF(*dataReader, "muonIDSF");
	TTreeReaderValue< pair<double,double> > photonMVAIDSF(*dataReader, "photonMVAIDSF");
	TTreeReaderValue< pair<double,double> > photonEleVetoSF(*dataReader, "photonEleVetoSF");
	TTreeReaderValue< pair<double,double> > triggerSF(*dataReader, "triggerSF");


	////////////////////////////////////////////////////////////////////
	// cuts setup
	double minUpsilonMassHistoRange = 1;
	double minUpsilonMass = 1;
	double maxUpsilonMass = 1;
	double maxUpsilonMassHistoRange = 1;
	int nBinsUpsilonMass = 1;

	double minHZMassLeft = 1;
	double maxHZMassLeft = 1;
	double minHZMassRight = 1;
	double maxHZMassRight = 1;
	int nBinsHZMass = 1;
	string dimuonLatexName = "";
	string mumugammaLatexName = "";

	// dimuon cut
	if (analysisBranch == "ZtoJPsi" || analysisBranch == "HtoJPsi") {
		minUpsilonMassHistoRange = 2.9;
		minUpsilonMass = 3.0;
		maxUpsilonMass = 3.2;
		maxUpsilonMassHistoRange = 3.3;
		nBinsUpsilonMass = 40;
		dimuonLatexName = "J/#Psi";
	}
	if (analysisBranch == "ZtoUpsilon") {
		minUpsilonMassHistoRange = 8.9;
		minUpsilonMass = 9.25;
		maxUpsilonMass = 9.67;
		maxUpsilonMassHistoRange = 9.9;
		nBinsUpsilonMass = 30;
		dimuonLatexName = "#Upsilon";
	}

	if (analysisBranch == "HtoUpsilon") {
		minUpsilonMassHistoRange = 8.4;
		minUpsilonMass = 8.5;
		maxUpsilonMass = 11.0;
		maxUpsilonMassHistoRange = 11.1;
		nBinsUpsilonMass = 50;
		dimuonLatexName = "#Upsilon";
	}

	// mumugamma cut 
	if (analysisBranch == "ZtoJPsi" || analysisBranch == "ZtoUpsilon") {
		minHZMassLeft = 70.;
		maxHZMassLeft = 80.;
		minHZMassRight = 100.;
		maxHZMassRight = 120.;
		nBinsHZMass = 20;
		mumugammaLatexName = "Z";
	}
	if (analysisBranch == "HtoJPsi" || analysisBranch == "HtoUpsilon") {
		minHZMassLeft = 100.;
		maxHZMassLeft = 115.;
		minHZMassRight = 135.;
		maxHZMassRight = 150.;
		nBinsHZMass = 25;
		mumugammaLatexName = "H";
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Categorization
	// setup
	double minPhotonAbsEta = 0.0;
	double maxPhotonAbsEta = 1E+125;
	double minPhotonR9 = 0.0;
	double maxPhotonR9 = 1.0;

	if (selCategory == "Cat0") {
		minPhotonAbsEta = 0.0;
		maxPhotonAbsEta = 2.5;
		minPhotonR9 = 0.0;
		maxPhotonR9 = 1.0;
	}
	if (selCategory == "Cat1") {
		minPhotonAbsEta = 0.0;
		maxPhotonAbsEta = 1.4442;
		minPhotonR9 = 0.94;
		maxPhotonR9 = 1.0;
	}
	if (selCategory == "Cat2") {
		minPhotonAbsEta = 0.0;
		maxPhotonAbsEta = 1.4442;
		minPhotonR9 = 0.0;
		maxPhotonR9 = 0.94;
	}

	if (selCategory == "Cat3") {
		minPhotonAbsEta = 1.4442;
		maxPhotonAbsEta = 2.5;
		minPhotonR9 = 0.0;
		maxPhotonR9 = 1.0;
	}


	////////////////////////////////////////////////////////////////////////////////////
	// define directories and histos
	TDirectory * rootDir = outFile->mkdir("outputHistos");
	rootDir->cd();    

	//GEN - no Polarization weight
	rootDir->cd(); 
	TDirectory * genDir = rootDir->mkdir("genHistos");
	genDir->cd();   
	auto * h_Gen_LeadingMu_pt = new TH1D("h_Gen_LeadingMu_pt", ";p_{T}^{#mu} (GeV);", 250, 0.0, 250.0);
	h_Gen_LeadingMu_pt->Sumw2();
	auto * h_Gen_LeadingMu_eta = new TH1D("h_Gen_LeadingMu_eta", ";#eta^{#mu};", 50, -2.5, 2.5);
	h_Gen_LeadingMu_eta->Sumw2();
	auto * h_Gen_LeadingMu_phi = new TH1D("h_Gen_LeadingMu_phi", ";#phi^{#mu};", 70, -3.2, 3.2);
	h_Gen_LeadingMu_phi->Sumw2();

	auto * h_Gen_TrailingMu_pt = new TH1D("h_Gen_TrailingMu_pt", ";p_{T}^{#mu} (GeV);", 250, 0.0, 250.0);
	h_Gen_TrailingMu_pt->Sumw2();
	auto * h_Gen_TrailingMu_eta = new TH1D("h_Gen_TrailingMu_eta", ";#eta^{#mu};", 50, -2.5, 2.5);
	h_Gen_TrailingMu_eta->Sumw2();
	auto * h_Gen_TrailingMu_phi = new TH1D("h_Gen_TrailingMu_phi", ";#phi^{#mu};", 70, -3.2, 3.2);
	h_Gen_TrailingMu_phi->Sumw2();

	auto * h_Gen_Photon_pt = new TH1D("h_Gen_Photon_pt", ";p_{T}^{#gamma} (GeV);", 250, 0.0, 250.0);
	h_Gen_Photon_pt->Sumw2();
	auto * h_Gen_Photon_eta = new TH1D("h_Gen_Photon_eta", ";#eta^{#gamma};", 50, -2.5, 2.5);
	h_Gen_Photon_eta->Sumw2();
	auto * h_Gen_Photon_phi = new TH1D("h_Gen_Photon_phi", ";#phi^{#gamma};", 70, -3.2, 3.2);
	h_Gen_Photon_phi->Sumw2();
	
	auto * h_Gen_deltaR_Leading_Trailing = new TH1D("h_Gen_deltaR_Leading_Trailing", ";#DeltaR(#mu_{Lead}, #mu_{Trail});", 100, 0.0, 1.0);
	h_Gen_deltaR_Leading_Trailing->Sumw2();
	auto * h_Gen_deltaR_Leading_Photon = new TH1D("h_Gen_deltaR_Leading_Photon", ";#DeltaR(#mu, #gamma);", 100, 0.0, 5.0);
	h_Gen_deltaR_Leading_Photon->Sumw2();
	auto * h_Gen_deltaR_Trailing_Photon = new TH1D("h_Gen_deltaR_Trailing_Photon", ";#DeltaR(#mu, #gamma);", 100, 0.0, 5.0);
	h_Gen_deltaR_Trailing_Photon->Sumw2();
	auto * h_Gen_deltaR_Upsilon_Photon = new TH1D("h_Gen_deltaR_Upsilon_Photon", (";#DeltaR("+dimuonLatexName+", #gamma);").c_str(), 100, 0.0, 5.0);
	h_Gen_deltaR_Upsilon_Photon->Sumw2();
	auto * h_Gen_deltaPhi_Upsilon_Photon = new TH1D("h_Gen_deltaPhi_Upsilon_Photon", (";|#Delta#phi("+dimuonLatexName+", #gamma)|;").c_str(), 100, 0.0, 4.0);
	h_Gen_deltaPhi_Upsilon_Photon->Sumw2();


	auto * h_Gen_Upsilon_Mass = new TH1D("h_Gen_Upsilon_Mass", (";"+dimuonLatexName+" Mass (GeV);").c_str(), nBinsUpsilonMass, minUpsilonMassHistoRange, maxUpsilonMassHistoRange);
	h_Gen_Upsilon_Mass->Sumw2();
	auto * h_Gen_Upsilon_Pt = new TH1D("h_Gen_Upsilon_Pt", (";p_{T}^{"+dimuonLatexName+"} (GeV);").c_str(), 250, 0.0, 250.0);
	h_Gen_Upsilon_Pt->Sumw2();
	auto * h_Gen_Upsilon_eta = new TH1D("h_Gen_Upsilon_eta", (";#eta^{"+dimuonLatexName+"};").c_str(), 50, -2.5, 2.5);
	h_Gen_Upsilon_eta->Sumw2();
	auto * h_Gen_Upsilon_phi = new TH1D("h_Gen_Upsilon_phi", (";#phi^{"+dimuonLatexName+"};").c_str(), 70, -3.2, 3.2);
	h_Gen_Upsilon_phi->Sumw2();

	auto * h_Gen_Z_Mass = new TH1D("h_Gen_Z_Mass", (";"+mumugammaLatexName+" Mass (GeV);").c_str(), nBinsHZMass, minHZMassLeft, maxHZMassRight);
	h_Gen_Z_Mass->Sumw2();
	auto * h_Gen_Z_Pt = new TH1D("h_Gen_Z_Pt", (";p_{T}^{"+mumugammaLatexName+"} (GeV);").c_str(), 250, 0.0, 250.0);
	h_Gen_Z_Pt->Sumw2();
	auto * h_Gen_Z_eta = new TH1D("h_Gen_Z_eta", (";#eta^{"+mumugammaLatexName+"};").c_str(), 50, -2.5, 2.5);
	h_Gen_Z_eta->Sumw2();
	auto * h_Gen_Z_phi = new TH1D("h_Gen_Z_phi", (";#phi^{"+mumugammaLatexName+"};").c_str(), 70, -3.2, 3.2);
	h_Gen_Z_phi->Sumw2();

	auto * h_Gen_upsilonPt_over_zMass = new TH1D("h_Gen_upsilonPt_over_zMass", (";p_{T}^{"+dimuonLatexName+"}/m_{"+mumugammaLatexName+"};").c_str(), 100, 0.0, 1.0);
	h_Gen_upsilonPt_over_zMass->Sumw2();
	auto * h_Gen_photonPt_over_zMass = new TH1D("h_Gen_photonPt_over_zMass", (";E_{T}^{"+dimuonLatexName+"}/m_{"+mumugammaLatexName+"};").c_str(), 100, 0.0, 1.0);
	h_Gen_photonPt_over_zMass->Sumw2();

	// polarization
	auto * h_Gen_UnPol = new TH1D("h_Gen_UnPol", (";cos("+dimuonLatexName+", #mu^{+});").c_str(), 100, -1.0, 1.0);
	h_Gen_UnPol->Sumw2();


	//GEN - with Polarization weight
	rootDir->cd(); 
	TDirectory * genwithPolWeightDir = rootDir->mkdir("genwithPolWeightHistos");
	genwithPolWeightDir->cd();   
	auto * h_Gen_withPolWeight_LeadingMu_pt = new TH1D("h_Gen_withPolWeight_LeadingMu_pt", ";p_{T}^{#mu} (GeV);", 250, 0.0, 250.0);
	h_Gen_withPolWeight_LeadingMu_pt->Sumw2();
	auto * h_Gen_withPolWeight_LeadingMu_eta = new TH1D("h_Gen_withPolWeight_LeadingMu_eta", ";#eta^{#mu};", 50, -2.5, 2.5);
	h_Gen_withPolWeight_LeadingMu_eta->Sumw2();
	auto * h_Gen_withPolWeight_LeadingMu_phi = new TH1D("h_Gen_withPolWeight_LeadingMu_phi", ";#phi^{#mu};", 70, -3.2, 3.2);
	h_Gen_withPolWeight_LeadingMu_phi->Sumw2();

	auto * h_Gen_withPolWeight_TrailingMu_pt = new TH1D("h_Gen_withPolWeight_TrailingMu_pt", ";p_{T}^{#mu} (GeV);", 250, 0.0, 250.0);
	h_Gen_withPolWeight_TrailingMu_pt->Sumw2();
	auto * h_Gen_withPolWeight_TrailingMu_eta = new TH1D("h_Gen_withPolWeight_TrailingMu_eta", ";#eta^{#mu};", 50, -2.5, 2.5);
	h_Gen_withPolWeight_TrailingMu_eta->Sumw2();
	auto * h_Gen_withPolWeight_TrailingMu_phi = new TH1D("h_Gen_withPolWeight_TrailingMu_phi", ";#phi^{#mu};", 70, -3.2, 3.2);
	h_Gen_withPolWeight_TrailingMu_phi->Sumw2();

	auto * h_Gen_withPolWeight_Photon_pt = new TH1D("h_Gen_withPolWeight_Photon_pt", ";p_{T}^{#gamma} (GeV);", 250, 0.0, 250.0);
	h_Gen_withPolWeight_Photon_pt->Sumw2();
	auto * h_Gen_withPolWeight_Photon_eta = new TH1D("h_Gen_withPolWeight_Photon_eta", ";#eta^{#gamma};", 50, -2.5, 2.5);
	h_Gen_withPolWeight_Photon_eta->Sumw2();
	auto * h_Gen_withPolWeight_Photon_phi = new TH1D("h_Gen_withPolWeight_Photon_phi", ";#phi^{#gamma};", 70, -3.2, 3.2);
	h_Gen_withPolWeight_Photon_phi->Sumw2();
	
	auto * h_Gen_withPolWeight_deltaR_Leading_Trailing = new TH1D("h_Gen_withPolWeight_deltaR_Leading_Trailing", ";#DeltaR(#mu_{Lead}, #mu_{Trail});", 100, 0.0, 1.0);
	h_Gen_withPolWeight_deltaR_Leading_Trailing->Sumw2();
	auto * h_Gen_withPolWeight_deltaR_Leading_Photon = new TH1D("h_Gen_withPolWeight_deltaR_Leading_Photon", ";#DeltaR(#mu, #gamma);", 100, 0.0, 5.0);
	h_Gen_withPolWeight_deltaR_Leading_Photon->Sumw2();
	auto * h_Gen_withPolWeight_deltaR_Trailing_Photon = new TH1D("h_Gen_withPolWeight_deltaR_Trailing_Photon", ";#DeltaR(#mu, #gamma);", 100, 0.0, 5.0);
	h_Gen_withPolWeight_deltaR_Trailing_Photon->Sumw2();
	auto * h_Gen_withPolWeight_deltaR_Upsilon_Photon = new TH1D("h_Gen_withPolWeight_deltaR_Upsilon_Photon", (";#DeltaR("+dimuonLatexName+", #gamma);").c_str(), 100, 0.0, 5.0);
	h_Gen_withPolWeight_deltaR_Upsilon_Photon->Sumw2();
	auto * h_Gen_withPolWeight_deltaPhi_Upsilon_Photon = new TH1D("h_Gen_withPolWeight_deltaPhi_Upsilon_Photon", (";|#Delta#phi("+dimuonLatexName+", #gamma)|;").c_str(), 100, 0.0, 4.0);
	h_Gen_withPolWeight_deltaPhi_Upsilon_Photon->Sumw2();

	auto * h_Gen_withPolWeight_Upsilon_Mass = new TH1D("h_Gen_withPolWeight_Upsilon_Mass", (";"+dimuonLatexName+" Mass (GeV);").c_str(), nBinsUpsilonMass, minUpsilonMassHistoRange, maxUpsilonMassHistoRange);
	h_Gen_withPolWeight_Upsilon_Mass->Sumw2();
	auto * h_Gen_withPolWeight_Upsilon_Pt = new TH1D("h_Gen_withPolWeight_Upsilon_Pt", (";p_{T}^{"+dimuonLatexName+"} (GeV);").c_str(), 250, 0.0, 250.0);
	h_Gen_withPolWeight_Upsilon_Pt->Sumw2();
	auto * h_Gen_withPolWeight_Upsilon_eta = new TH1D("h_Gen_withPolWeight_Upsilon_eta", (";#eta^{"+dimuonLatexName+"};").c_str(), 50, -2.5, 2.5);
	h_Gen_withPolWeight_Upsilon_eta->Sumw2();
	auto * h_Gen_withPolWeight_Upsilon_phi = new TH1D("h_Gen_withPolWeight_Upsilon_phi", (";#phi^{"+dimuonLatexName+"};").c_str(), 70, -3.2, 3.2);
	h_Gen_withPolWeight_Upsilon_phi->Sumw2();


	auto * h_Gen_withPolWeight_Z_Mass = new TH1D("h_Gen_withPolWeight_Z_Mass", (";"+mumugammaLatexName+" Mass (GeV);").c_str(), nBinsHZMass, minHZMassLeft, maxHZMassRight);
	h_Gen_withPolWeight_Z_Mass->Sumw2();
	auto * h_Gen_withPolWeight_Z_Pt = new TH1D("h_Gen_withPolWeight_Z_Pt", (";p_{T}^{"+mumugammaLatexName+"} (GeV);").c_str(), 250, 0.0, 250.0);
	h_Gen_withPolWeight_Z_Pt->Sumw2();
	auto * h_Gen_withPolWeight_Z_eta = new TH1D("h_Gen_withPolWeight_Z_eta", (";#eta^{"+mumugammaLatexName+"};").c_str(), 50, -2.5, 2.5);
	h_Gen_withPolWeight_Z_eta->Sumw2();
	auto * h_Gen_withPolWeight_Z_phi = new TH1D("h_Gen_withPolWeight_Z_phi", (";#phi^{"+mumugammaLatexName+"};").c_str(), 70, -3.2, 3.2);
	h_Gen_withPolWeight_Z_phi->Sumw2();

	auto * h_Gen_withPolWeight_upsilonPt_over_zMass = new TH1D("h_Gen_withPolWeight_upsilonPt_over_zMass", (";p_{T}^{"+dimuonLatexName+"}/m_{"+mumugammaLatexName+"};").c_str(), 100, 0.0, 1.0);
	h_Gen_withPolWeight_upsilonPt_over_zMass->Sumw2();
	auto * h_Gen_withPolWeight_photonPt_over_zMass = new TH1D("h_Gen_withPolWeight_photonPt_over_zMass", (";E_{T}^{#gamma}/m_{"+mumugammaLatexName+"};").c_str(), 100, 0.0, 1.0);
	h_Gen_withPolWeight_photonPt_over_zMass->Sumw2();

	// polarization
	auto * h_Gen_Pol = new TH1D("h_Gen_Pol", (";cos("+dimuonLatexName+", #mu^{+});").c_str(), 100, -1.0, 1.0);
	h_Gen_Pol->Sumw2();

	// no kinematical cuts
	rootDir->cd(); 
	TDirectory * noKinCutsDir = rootDir->mkdir("noKinCutsHistos");
	noKinCutsDir->cd();   
	auto * h_noKin_LeadingMu_pt = new TH1D("h_noKin_LeadingMu_pt", ";p_{T}^{#mu} (GeV)", 160, 0.0, 160.0);
	h_noKin_LeadingMu_pt->Sumw2();
	auto * h_noKin_LeadingMu_eta = new TH1D("h_noKin_LeadingMu_eta", ";#eta^{#mu}", 50, -2.5, 2.7);
	h_noKin_LeadingMu_eta->Sumw2();
	auto * h_noKin_LeadingMu_phi = new TH1D("h_noKin_LeadingMu_phi", ";#phi^{#mu}", 70, -3.2, 3.2);
	h_noKin_LeadingMu_phi->Sumw2();

	auto * h_noKin_TrailingMu_pt = new TH1D("h_noKin_TrailingMu_pt", ";p_{T}^{#mu}", 160, 0.0, 160.0);
	h_noKin_TrailingMu_pt->Sumw2();
	auto * h_noKin_TrailingMu_eta = new TH1D("h_noKin_TrailingMu_eta", ";#eta^{#mu}", 50, -2.5, 2.7);
	h_noKin_TrailingMu_eta->Sumw2();
	auto * h_noKin_TrailingMu_phi = new TH1D("h_noKin_TrailingMu_phi", ";#phi^{#mu}", 70, -3.2, 3.2);
	h_noKin_TrailingMu_phi->Sumw2();

	auto * h_noKin_Photon_pt = new TH1D("h_noKin_Photon_pt", ";E_{T}^{#gamma} (GeV)", 100, 0.0, 160.0);
	h_noKin_Photon_pt->Sumw2();
	auto * h_noKin_Photon_eta = new TH1D("h_noKin_Photon_eta", ";#eta_{SC}^{#gamma}", 50, -2.5, 2.7);
	h_noKin_Photon_eta->Sumw2();
	auto * h_noKin_Photon_phi = new TH1D("h_noKin_Photon_phi", ";#phi^{#gamma}", 70, -3.2, 3.2);
	h_noKin_Photon_phi->Sumw2();

	auto * h_noKin_deltaR_Leading_Trailing = new TH1D("h_noKin_deltaR_Leading_Trailing", ";#DeltaR(lead #mu, trail #mu);", 100, 0.0, 1.0);
	h_noKin_deltaR_Leading_Trailing->Sumw2();
	auto * h_noKin_deltaR_Leading_Photon = new TH1D("h_noKin_deltaR_Leading_Photon", ";#DeltaR(lead #mu, #gamma);", 100, 0.0, 5.0);
	h_noKin_deltaR_Leading_Photon->Sumw2();
	auto * h_noKin_deltaR_Trailing_Photon = new TH1D("h_noKin_deltaR_Trailing_Photon", ";#DeltaR(trail #mu, #gamma);", 100, 0.0, 5.0);
	h_noKin_deltaR_Trailing_Photon->Sumw2();
	auto * h_noKin_deltaR_Upsilon_Photon = new TH1D("h_noKin_deltaR_Upsilon_Photon", ";#DeltaR(#mu#mu, #gamma);", 100, 0.0, 5.0);
	h_noKin_deltaR_Upsilon_Photon->Sumw2();
	auto * h_noKin_deltaPhi_Upsilon_Photon = new TH1D("h_noKin_deltaPhi_Upsilon_Photon", ";|#Delta#phi(#mu#mu, #gamma)|;", 100, 0.0, 4.0);
	h_noKin_deltaPhi_Upsilon_Photon->Sumw2();

	auto * h_noKin_Upsilon_Mass_LargeRange = new TH1D("h_noKin_Upsilon_Mass_LargeRange", ";#mu#mu Mass (GeV);", 100, 0.0, 20.0);
	h_noKin_Upsilon_Mass_LargeRange->Sumw2();
	auto * h_noKin_Upsilon_Mass = new TH1D("h_noKin_Upsilon_Mass", ";#mu#mu Mass (GeV);", nBinsUpsilonMass, minUpsilonMassHistoRange, maxUpsilonMassHistoRange);
	h_noKin_Upsilon_Mass->Sumw2();
	auto * h_noKin_Upsilon_Pt = new TH1D("h_noKin_Upsilon_Pt", ";p_{T}^{#mu#mu} (GeV);", 160, 0.0, 160.0);
	h_noKin_Upsilon_Pt->Sumw2();
	auto * h_noKin_Upsilon_eta = new TH1D("h_noKin_Upsilon_eta", ";#eta^{#mu#mu};", 50, -2.5, 2.5);
	h_noKin_Upsilon_eta->Sumw2();
	auto * h_noKin_Upsilon_phi = new TH1D("h_noKin_Upsilon_phi", ";#phi^{#mu#mu};", 70, -3.2, 3.2);
	h_noKin_Upsilon_phi->Sumw2();



	auto * h_noKin_Z_Mass = new TH1D("h_noKin_Z_Mass", ";#mu#mu#gamma Mass (GeV);", nBinsHZMass, minHZMassLeft, maxHZMassRight);
	h_noKin_Z_Mass->Sumw2();
	auto * h_noKin_Z_Pt = new TH1D("h_noKin_Z_Pt", ";p_{T}^{#mu#mu#gamma} (GeV);", 160, 0.0, 160.0);
	h_noKin_Z_Pt->Sumw2();
	auto * h_noKin_Z_eta = new TH1D("h_noKin_Z_eta", ";#eta^{#mu#mu#gamma};", 50, -2.5, 2.5);
	h_noKin_Z_eta->Sumw2();
	auto * h_noKin_Z_phi = new TH1D("h_noKin_Z_phi", ";#phi^{#mu#mu#gamma};", 70, -3.2, 3.2);
	h_noKin_Z_phi->Sumw2();

	auto * h_noKin_upsilonPt_over_zMass = new TH1D("h_noKin_upsilonPt_over_zMass", ";p_{T}^{#mu#mu}/m_{#mu#mu#gamma};", 100, 0.0, 1.0);
	h_noKin_upsilonPt_over_zMass->Sumw2();
	auto * h_noKin_photonPt_over_zMass = new TH1D("h_noKin_photonPt_over_zMass", ";E_{T}^{#gamma}/m_{#mu#mu#gamma};", 100, 0.0, 1.0);
	h_noKin_photonPt_over_zMass->Sumw2();

	//2D masss plot
	auto * h_noKin_Upsilon_Mass_Z_Mass = new TH2D("h_noKin_Upsilon_Mass_Z_Mass", ";#mu#mu Mass (GeV); #mu#mu#gamma Mass (GeV)", nBinsUpsilonMass, minUpsilonMassHistoRange, maxUpsilonMassHistoRange, nBinsHZMass, minHZMassLeft, maxHZMassRight);
	h_noKin_Upsilon_Mass_Z_Mass->Sumw2();
	//3D masss plot
	auto * h_noKin_Upsilon_Mass_Z_Mass_Z_Pt = new TH3D("h_noKin_Upsilon_Mass_Z_Mass_Z_Pt", ";#mu#mu Mass (GeV); #mu#mu#gamma Mass (GeV); p_{T}^{#mu#mu#gamma} (GeV)", nBinsUpsilonMass, minUpsilonMassHistoRange, maxUpsilonMassHistoRange, nBinsHZMass, minHZMassLeft, maxHZMassRight, 160, 0.0, 160.0);
	h_noKin_Upsilon_Mass_Z_Mass_Z_Pt->Sumw2();



	// with kinematical cuts
	rootDir->cd(); 
	TDirectory * withKinCutsDir = rootDir->mkdir("withKinCutsHistos");
	withKinCutsDir->cd();   
	auto * h_withKin_LeadingMu_pt = new TH1D("h_withKin_LeadingMu_pt", ";p_{T}^{#mu} (GeV)", 160, 0.0, 160.0);
	h_withKin_LeadingMu_pt->Sumw2();
	auto * h_withKin_LeadingMu_eta = new TH1D("h_withKin_LeadingMu_eta", ";#eta^{#mu}", 50, -2.5, 2.7);
	h_withKin_LeadingMu_eta->Sumw2();
	auto * h_withKin_LeadingMu_phi = new TH1D("h_withKin_LeadingMu_phi", ";#phi^{#mu}", 70, -3.2, 3.2);
	h_withKin_LeadingMu_phi->Sumw2();

	auto * h_withKin_TrailingMu_pt = new TH1D("h_withKin_TrailingMu_pt", ";p_{T}^{#mu}", 160, 0.0, 160.0);
	h_withKin_TrailingMu_pt->Sumw2();
	auto * h_withKin_TrailingMu_eta = new TH1D("h_withKin_TrailingMu_eta", ";#eta^{#mu}", 50, -2.5, 2.7);
	h_withKin_TrailingMu_eta->Sumw2();
	auto * h_withKin_TrailingMu_phi = new TH1D("h_withKin_TrailingMu_phi", ";#phi^{#mu}", 70, -3.2, 3.2);
	h_withKin_TrailingMu_phi->Sumw2();

	auto * h_withKin_Photon_pt = new TH1D("h_withKin_Photon_pt", ";E_{T}^{#gamma} (GeV)", 100, 0.0, 160.0);
	h_withKin_Photon_pt->Sumw2();
	auto * h_withKin_Photon_eta = new TH1D("h_withKin_Photon_eta", ";#eta_{SC}^{#gamma}", 50, -2.5, 2.7);
	h_withKin_Photon_eta->Sumw2();
	auto * h_withKin_Photon_phi = new TH1D("h_withKin_Photon_phi", ";#phi^{#gamma}", 70, -3.2, 3.2);
	h_withKin_Photon_phi->Sumw2();

	auto * h_withKin_deltaR_Leading_Trailing = new TH1D("h_withKin_deltaR_Leading_Trailing", ";#DeltaR(lead #mu, trail #mu);", 100, 0.0, 1.0);
	h_withKin_deltaR_Leading_Trailing->Sumw2();
	auto * h_withKin_deltaR_Leading_Photon = new TH1D("h_withKin_deltaR_Leading_Photon", ";#DeltaR(lead #mu, #gamma);", 100, 0.0, 5.0);
	h_withKin_deltaR_Leading_Photon->Sumw2();
	auto * h_withKin_deltaR_Trailing_Photon = new TH1D("h_withKin_deltaR_Trailing_Photon", ";#DeltaR(trail #mu, #gamma);", 100, 0.0, 5.0);
	h_withKin_deltaR_Trailing_Photon->Sumw2();
	auto * h_withKin_deltaR_Upsilon_Photon = new TH1D("h_withKin_deltaR_Upsilon_Photon", ";#DeltaR(#mu#mu, #gamma);", 100, 0.0, 5.0);
	h_withKin_deltaR_Upsilon_Photon->Sumw2();
	auto * h_withKin_deltaPhi_Upsilon_Photon = new TH1D("h_withKin_deltaPhi_Upsilon_Photon", ";|#Delta#phi(#mu#mu, #gamma)|;", 100, 0.0, 4.0);
	h_withKin_deltaPhi_Upsilon_Photon->Sumw2();

	auto * h_withKin_Upsilon_Mass = new TH1D("h_withKin_Upsilon_Mass", ";#mu#mu Mass (GeV);", nBinsUpsilonMass, minUpsilonMassHistoRange, maxUpsilonMassHistoRange);
	h_withKin_Upsilon_Mass->Sumw2();
	auto * h_withKin_Upsilon_Mass_LargeRange = new TH1D("h_withKin_Upsilon_Mass_LargeRange", ";#mu#mu Mass (GeV);", 100, 0.0, 20.0);
	h_withKin_Upsilon_Mass_LargeRange->Sumw2();
	auto * h_withKin_Upsilon_Pt = new TH1D("h_withKin_Upsilon_Pt", ";p_{T}^{#mu#mu} (GeV);", 160, 0.0, 160.0);
	h_withKin_Upsilon_Pt->Sumw2();
	auto * h_withKin_Upsilon_eta = new TH1D("h_withKin_Upsilon_eta", ";#eta^{#mu#mu};", 50, -2.5, 2.5);
	h_withKin_Upsilon_eta->Sumw2();
	auto * h_withKin_Upsilon_phi = new TH1D("h_withKin_Upsilon_phi", ";#phi^{#mu#mu};", 70, -3.2, 3.2);
	h_withKin_Upsilon_phi->Sumw2();



	auto * h_withKin_Z_Mass = new TH1D("h_withKin_Z_Mass", ";#mu#mu#gamma Mass (GeV);", minHZMassLeft, minHZMassLeft, maxHZMassRight);
	h_withKin_Z_Mass->Sumw2();
	auto * h_withKin_Z_Pt = new TH1D("h_withKin_Z_Pt", ";p_{T}^{#mu#mu#gamma} (GeV);", 160, 0.0, 160.0);
	h_withKin_Z_Pt->Sumw2();
	auto * h_withKin_Z_eta = new TH1D("h_withKin_Z_eta", ";#eta^{#mu#mu#gamma};", 50, -2.5, 2.5);
	h_withKin_Z_eta->Sumw2();
	auto * h_withKin_Z_phi = new TH1D("h_withKin_Z_phi", ";#phi^{#mu#mu#gamma};", 70, -3.2, 3.2);
	h_withKin_Z_phi->Sumw2();

	auto * h_withKin_upsilonPt_over_zMass = new TH1D("h_withKin_upsilonPt_over_zMass", ";p_{T}^{#mu#mu}/m_{#mu#mu#gamma};", 100, 0.0, 1.0);
	h_withKin_upsilonPt_over_zMass->Sumw2();
	auto * h_withKin_photonPt_over_zMass = new TH1D("h_withKin_photonPt_over_zMass", ";E_{T}^{#gamma}/m_{#mu#mu#gamma};", 100, 0.0, 1.0);
	h_withKin_photonPt_over_zMass->Sumw2();

	//2D masss plot
	auto * h_withKin_Upsilon_Mass_Z_Mass = new TH2D("h_withKin_Upsilon_Mass_Z_Mass", ";#mu#mu Mass (GeV); #mu#mu#gamma Mass (GeV)", nBinsUpsilonMass, minUpsilonMassHistoRange, maxUpsilonMassHistoRange, minHZMassLeft, minHZMassLeft, maxHZMassRight);
	h_withKin_Upsilon_Mass_Z_Mass->Sumw2();
	//3D masss plot
	auto * h_withKin_Upsilon_Mass_Z_Mass_Z_Pt = new TH3D("h_withKin_Upsilon_Mass_Z_Mass_Z_Pt", ";#mu#mu Mass (GeV); #mu#mu#gamma Mass (GeV); p_{T}^{#mu#mu#gamma} (GeV)", nBinsUpsilonMass, minUpsilonMassHistoRange, maxUpsilonMassHistoRange, minHZMassLeft, minHZMassLeft, maxHZMassRight, 160, 0.0, 160.0);
	h_withKin_Upsilon_Mass_Z_Mass_Z_Pt->Sumw2();


	////////////////////////////////////////////////////////
	// ttree to fit
	string outputTreeName = "outputHistos/outTreeToFit_HZtoUpsilonPhoton_"+ outHistoAppend + "_" + analysisBranch + "_" + selCategory + "_" + systMaskYields + ".root";
	TFile * outputTreeFile  = new TFile(outputTreeName.c_str(),"RECREATE","ZtoUpsilonPhoton output analysis tree");
	TTree * outTree = new TTree("outTree_HZtoUpsilonPhoton","ZtoUpsilonPhoton output analysis tree");
	double mHZ = -99.0;
	outTree->Branch("mHZ", &mHZ) ;
	double mMuMNU = -99.0;
	outTree->Branch("mMuMNU", &mMuMNU) ;
	double mHZWeight = 1.;
	outTree->Branch("mHZWeight", &mHZWeight) ;

	////////////////////////////////////////////////////////////////////
	// events count
	// counter
	double countTotalEvts = 0.0;
	double countTrigger = 0.0;
	double countMuonPreSel = 0.0;
	double countMuonIDISO = 0.0;
	double countPhotonSel = 0.0;
	double countMuonToPhoton = 0.0;
	double countUpsilonToPhoton = 0.0;
	double countUpsilonMassCut = 0.0;
	double countRatioCuts = 0.0;
	double countZMassCut = 0.0;
    // booleans
	bool goodDeltaRLeadTrail = false;
	bool goodDeltaRMuonsPhoton = false;
	bool goodDeltaRPhiUpsilonPhoton  = false;
	bool goodUpsilonMassCut = false;
	bool goodRatioCuts = false;
	bool goodZMassCut = false;
	bool goodCategory = false;
	bool isTrailingMuonISO = false;
	bool goodKinCuts = true;


	////////////////////////////////////////////////////////////////////
	// numer of entries
	auto totalEvts = dataTree->GetEntries();
	auto printEvery = 100000;
	cout << "\nN. Entries: " << totalEvts << endl;
	cout << "\nPrinting every: " << printEvery << " events" << endl;
	cout << "\nLooping over events... \n" << endl;

	// // dataTree->Print();


	////////////////////////////////////////////////////////////////////
	// main loop
	auto iEvt = 0;
	while (dataReader->Next()) { // loop over events
		if (iEvt % printEvery == 0) cout << "----------------------------------------> Events read (" << outHistoAppend << " - " << analysisBranch << " - " << selCategory << " - " << systMaskYields << "): " << iEvt << " / " << totalEvts << " - ~"<< round(((float)iEvt/(float)totalEvts)*100) << "%"<< endl;
		// countTotalEvts = countTotalEvts + 1.0;
		// cout << "--------------------------> iEvt (" << outHistoAppend << " - " << analysisBranch << " - " << selCategory << " - " << systMaskYields << "): " << iEvt <<  endl;
		// cout << "--------------------------> countTotalEvts (" << outHistoAppend << " - " << analysisBranch << " - " << selCategory << " - " << systMaskYields << "): " << countTotalEvts << endl;
		iEvt++;

		// event weight
		// xSecs and BRs: https://docs.google.com/spreadsheets/d/1zP8P9kp-yFrkMu9bGt4fpIirKAKYlH-w2em_kVkYYKw/edit#gid=0
		double totalWeight = 1.0;
		// for systematics corrections
		double puWgt = (systMaskYields == "PZZZZ") ? *puWgt_up : *puWgt_nominal;
		puWgt = (systMaskYields == "MZZZZ") ? *puWgt_down : puWgt;
		double triggerWgt = (systMaskYields == "ZPZZZ") ? triggerSF->first + triggerSF->second : triggerSF->first;
		triggerWgt = (systMaskYields == "ZMZZZ") ? triggerSF->first - triggerSF->second : triggerWgt;
		double muonIDWgt = (systMaskYields == "ZZPZZ") ? muonIDSF->first + muonIDSF->second : muonIDSF->first;
		muonIDWgt = (systMaskYields == "ZZMZZ") ? muonIDSF->first - muonIDSF->second : muonIDWgt;
		double photonMVAIDWgt = (systMaskYields == "ZZZPZ") ? photonMVAIDSF->first + photonMVAIDSF->second : photonMVAIDSF->first;
		photonMVAIDWgt = (systMaskYields == "ZZZMZ") ? photonMVAIDSF->first - photonMVAIDSF->second : photonMVAIDWgt;
		double photonEleVetoWgt = (systMaskYields == "ZZZZP") ? photonEleVetoSF->first + photonEleVetoSF->second : photonEleVetoSF->first;
		photonEleVetoWgt = (systMaskYields == "ZZZZM") ? photonEleVetoSF->first - photonEleVetoSF->second : photonEleVetoWgt;
		
		if (sampleSource->GetString() == "ZToUpsilon1SGamma" && !isData) 
			totalWeight = (6.9806E-05*0.7222*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);

		if (sampleSource->GetString() == "ZToUpsilon2SGamma" && !isData) 
			totalWeight = (6.9806E-05*0.7222*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
		
		if (sampleSource->GetString() == "ZToUpsilon3SGamma" && !isData) 
			totalWeight = (6.9806E-05*0.7222*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
		
		if (sampleSource->GetString() == "ZToJPsiGamma" && !isData) 
			totalWeight = (3.3898E-04*0.7015*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
		
		if (sampleSource->GetString() == "ZGTo2MuG_MMuMu-2To15" && !isData) 
			totalWeight = (7.9260E-02*3.5860E+04/(double)totalEvts)*(puWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
		
		if (sampleSource->GetString() == "HToUpsilon1SGamma" && !isData) 
			// totalWeight = (8.4271E-10*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
			totalWeight = (6.3582E-09*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
		
		if (sampleSource->GetString() == "HToUpsilon2SGamma" && !isData) 
			// totalWeight = (2.1682E-09*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
			totalWeight = (2.5116E-09*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
		
		if (sampleSource->GetString() == "HToUpsilon3SGamma" && !isData) 
			// totalWeight = (2.9582E-09*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
			totalWeight = (2.5824E-09*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
		
		if (sampleSource->GetString() == "HToJPsiGamma" && !isData) 
			totalWeight = (9.2493E-06*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
			// totalWeight = (9.7797E-06*3.5860E+04/(double)totalEvts)*(puWgt)*(*polWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
		
		if (sampleSource->GetString() == "HDalitz" && !isData) 
			totalWeight = (1.8614E-03*3.5860E+04/(double)totalEvts)*(puWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt)*(triggerWgt);
		
		// MC
		if (!isData) { 
			// upsilon polarization
			h_Gen_UnPol->Fill(upsilonPolarizationAngle(*genMuPlus, *genMuMinus), 1.0);
			h_Gen_Pol->Fill(upsilonPolarizationAngle(*genMuPlus, *genMuMinus), *polWgt);


			auto plusIsLeading = (genMuPlus->Pt() > genMuMinus->Pt()) ? true : false; // who is the leading?
			
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			// GEN - no Polarization weight
			//muons
			genFiller(plusIsLeading, h_Gen_LeadingMu_pt, h_Gen_TrailingMu_pt, genMuPlus->Pt(), genMuMinus->Pt()) ;
			genFiller(plusIsLeading, h_Gen_LeadingMu_eta, h_Gen_TrailingMu_eta, genMuPlus->Eta(), genMuMinus->Eta()) ;
			genFiller(plusIsLeading, h_Gen_LeadingMu_phi, h_Gen_TrailingMu_phi, genMuPlus->Phi(), genMuMinus->Phi()) ;	
			// photon
			h_Gen_Photon_pt->Fill(genPhoton->Pt(), 1.0);
			h_Gen_Photon_eta->Fill(genPhoton->Eta(), 1.0);
			h_Gen_Photon_phi->Fill(genPhoton->Phi(), 1.0);
			//Upsilon
			TLorentzVector genUpsilon = *genMuPlus + *genMuMinus;
			h_Gen_Upsilon_Mass->Fill(genUpsilon.M(), 1.0);
			h_Gen_Upsilon_Pt->Fill(genUpsilon.Pt(), 1.0);
			h_Gen_Upsilon_eta->Fill(genUpsilon.Eta(), 1.0);
			h_Gen_Upsilon_phi->Fill(genUpsilon.Phi(), 1.0);
			// Z
			TLorentzVector genZ = genUpsilon + *genPhoton;
			h_Gen_Z_Mass->Fill(genZ.M(), 1.0);
			h_Gen_Z_Pt->Fill(genZ.Pt(), 1.0);
			h_Gen_Z_eta->Fill(genZ.Eta(), 1.0);
			h_Gen_Z_phi->Fill(genZ.Phi(), 1.0);
			// deltaR
			h_Gen_deltaR_Leading_Trailing->Fill(deltaR(genMuPlus->Eta(), genMuPlus->Phi(), genMuMinus->Eta(), genMuMinus->Phi()), 1.0);
			genFiller(plusIsLeading, h_Gen_deltaR_Leading_Photon, h_Gen_deltaR_Trailing_Photon, deltaR(genMuPlus->Eta(), genMuPlus->Phi(), genPhoton->Eta(), genPhoton->Phi()), deltaR(genMuMinus->Eta(), genMuMinus->Phi(), genPhoton->Eta(), genPhoton->Phi()), 1.0);
			h_Gen_deltaR_Upsilon_Photon->Fill(deltaR(genUpsilon.Eta(), genUpsilon.Phi(), genPhoton->Eta(), genPhoton->Phi()), 1.0);
			h_Gen_deltaPhi_Upsilon_Photon->Fill(fabs(deltaPhi(genUpsilon.Phi(), genPhoton->Phi())), 1.0);

			//energy ratios
			h_Gen_upsilonPt_over_zMass->Fill(genUpsilon.Pt()/genZ.M(), 1.0);
			h_Gen_photonPt_over_zMass->Fill(genPhoton->Pt()/genZ.M(), 1.0);
			
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			// GEN - with Polarization weight
			//muons
			genFiller(plusIsLeading, h_Gen_withPolWeight_LeadingMu_pt, h_Gen_withPolWeight_TrailingMu_pt, genMuPlus->Pt(), genMuMinus->Pt(), *polWgt) ;
			genFiller(plusIsLeading, h_Gen_withPolWeight_LeadingMu_eta, h_Gen_withPolWeight_TrailingMu_eta, genMuPlus->Eta(), genMuMinus->Eta(), *polWgt) ;
			genFiller(plusIsLeading, h_Gen_withPolWeight_LeadingMu_phi, h_Gen_withPolWeight_TrailingMu_phi, genMuPlus->Phi(), genMuMinus->Phi(), *polWgt) ;	
			// photon
			h_Gen_withPolWeight_Photon_pt->Fill(genPhoton->Pt(), *polWgt);
			h_Gen_withPolWeight_Photon_eta->Fill(genPhoton->Eta(), *polWgt);
			h_Gen_withPolWeight_Photon_phi->Fill(genPhoton->Phi(), *polWgt);
			//Upsilon
			// TLorentzVector genUpsilon = *genMuPlus + *genMuMinus;
			h_Gen_withPolWeight_Upsilon_Mass->Fill(genUpsilon.M(), *polWgt);
			h_Gen_withPolWeight_Upsilon_Pt->Fill(genUpsilon.Pt(), *polWgt);
			h_Gen_withPolWeight_Upsilon_eta->Fill(genUpsilon.Eta(), *polWgt);
			h_Gen_withPolWeight_Upsilon_phi->Fill(genUpsilon.Phi(), *polWgt);
			// Z
			// TLorentzVector genZ = genUpsilon + *genPhoton;
			h_Gen_withPolWeight_Z_Mass->Fill(genZ.M(), *polWgt);
			h_Gen_withPolWeight_Z_Pt->Fill(genZ.Pt(), *polWgt);
			h_Gen_withPolWeight_Z_eta->Fill(genZ.Eta(), *polWgt);
			h_Gen_withPolWeight_Z_phi->Fill(genZ.Phi(), *polWgt);
			// deltaR
			h_Gen_withPolWeight_deltaR_Leading_Trailing->Fill(deltaR(genMuPlus->Eta(), genMuPlus->Phi(), genMuMinus->Eta(), genMuMinus->Phi()), *polWgt);
			genFiller(plusIsLeading, h_Gen_withPolWeight_deltaR_Leading_Photon, h_Gen_withPolWeight_deltaR_Trailing_Photon, deltaR(genMuPlus->Eta(), genMuPlus->Phi(), genPhoton->Eta(), genPhoton->Phi()), deltaR(genMuMinus->Eta(), genMuMinus->Phi(), genPhoton->Eta(), genPhoton->Phi()), *polWgt) ;
			h_Gen_withPolWeight_deltaR_Upsilon_Photon->Fill(deltaR(genUpsilon.Eta(), genUpsilon.Phi(), genPhoton->Eta(), genPhoton->Phi()), *polWgt);
			h_Gen_withPolWeight_deltaPhi_Upsilon_Photon->Fill(fabs(deltaPhi(genUpsilon.Phi(), genPhoton->Phi())), *polWgt);

			//energy ratios
			h_Gen_withPolWeight_upsilonPt_over_zMass->Fill(genUpsilon.Pt()/genZ.M(), *polWgt);
			h_Gen_withPolWeight_photonPt_over_zMass->Fill(genPhoton->Pt()/genZ.M(), *polWgt);


		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		// no kinematical cuts
		if (*isGoodEvent) {
		// if (*goodTriggerEvt && *goodMuonPairSel) {
		// 	leadingPhoton->SetPtEtaPhiM(0,0,0,0);
			// reco objects
			TLorentzVector recoUpsilon = *leadingMuon + *trailingMuon;
			TLorentzVector recoZ = recoUpsilon + *leadingPhoton;

			h_noKin_LeadingMu_pt->Fill(leadingMuon->Pt(),totalWeight);
			h_noKin_LeadingMu_eta->Fill(leadingMuon->Eta(),totalWeight);
			h_noKin_LeadingMu_phi->Fill(leadingMuon->Phi(),totalWeight);

			h_noKin_TrailingMu_pt->Fill(trailingMuon->Pt(),totalWeight);
			h_noKin_TrailingMu_eta->Fill(trailingMuon->Eta(),totalWeight);
			h_noKin_TrailingMu_phi->Fill(trailingMuon->Phi(),totalWeight);

			h_noKin_Photon_pt->Fill(leadingPhoton->Et(),totalWeight);
			h_noKin_Photon_eta->Fill(leadingPhoton->photonSCEta,totalWeight);
			h_noKin_Photon_phi->Fill(leadingPhoton->Phi(),totalWeight);

			h_noKin_deltaR_Leading_Trailing->Fill(deltaR(leadingMuon->Eta(), leadingMuon->Phi(), trailingMuon->Eta(), trailingMuon->Phi()),totalWeight);
			h_noKin_deltaR_Leading_Photon->Fill(deltaR(leadingMuon->Eta(), leadingMuon->Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()),totalWeight);
			h_noKin_deltaR_Trailing_Photon->Fill(deltaR(trailingMuon->Eta(), trailingMuon->Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()),totalWeight);
			h_noKin_deltaR_Upsilon_Photon->Fill(deltaR(recoUpsilon.Eta(), recoUpsilon.Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()),totalWeight);
			h_noKin_deltaPhi_Upsilon_Photon->Fill(fabs(deltaPhi(recoUpsilon.Phi(), leadingPhoton->Phi())),totalWeight);

			h_noKin_Upsilon_Mass->Fill(recoUpsilon.M(),totalWeight);
			h_noKin_Upsilon_Mass_LargeRange->Fill(recoUpsilon.M(),totalWeight);
			h_noKin_Upsilon_Pt->Fill(recoUpsilon.Pt(),totalWeight);
			h_noKin_Upsilon_eta->Fill(recoUpsilon.Eta(),totalWeight);
			h_noKin_Upsilon_phi->Fill(recoUpsilon.Phi(),totalWeight);


			if (isData){
				if (recoZ.M() < maxHZMassLeft || recoZ.M() > minHZMassRight) h_noKin_Z_Mass->Fill(recoZ.M(),totalWeight);
			} else {
				h_noKin_Z_Mass->Fill(recoZ.M(),totalWeight);
			}

			h_noKin_Z_Pt->Fill(recoZ.Pt(),totalWeight);
			h_noKin_Z_eta->Fill(recoZ.Eta(),totalWeight);
			h_noKin_Z_phi->Fill(recoZ.Phi(),totalWeight);

			//energy ratios
			h_noKin_upsilonPt_over_zMass->Fill(recoUpsilon.Pt()/recoZ.M(),totalWeight);
			h_noKin_photonPt_over_zMass->Fill(leadingPhoton->Et()/recoZ.M(),totalWeight);

			//2D masss plot
			h_noKin_Upsilon_Mass_Z_Mass->Fill(recoUpsilon.M(), recoZ.M(),totalWeight);
			//3D masss plot
			h_noKin_Upsilon_Mass_Z_Mass_Z_Pt->Fill(recoUpsilon.M(), recoZ.M(), recoZ.Pt(),totalWeight);

			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			// with kinematical cuts
			// auto goodKinCuts = true;
			goodKinCuts = true;
			goodDeltaRMuonsPhoton = ( (deltaR(leadingMuon->Eta(), leadingMuon->Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()) > 1.0) && (deltaR(trailingMuon->Eta(), trailingMuon->Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()) > 1.0)) ? true : false;
			// goodKinCuts *= (deltaR(leadingMuon->Eta(), leadingMuon->Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()) > 1.0) ? true : false;
			// goodKinCuts *= (deltaR(trailingMuon->Eta(), trailingMuon->Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()) > 1.0) ? true : false;
			goodKinCuts *= goodDeltaRMuonsPhoton;
			goodDeltaRPhiUpsilonPhoton = ( (deltaR(recoUpsilon.Eta(), recoUpsilon.Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()) > 2.0) && (fabs(deltaPhi(recoUpsilon.Phi(), leadingPhoton->Phi())) > 1.5) ) ? true : false;
			// goodKinCuts *= (deltaR(recoUpsilon.Eta(), recoUpsilon.Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()) > 2.0) ? true : false;
			// goodKinCuts *= (fabs(deltaPhi(recoUpsilon.Phi(), leadingPhoton->Phi())) > 1.5) ? true : false;
			goodKinCuts *= goodDeltaRPhiUpsilonPhoton;
			// goodKinCuts *= (recoUpsilon.M() > 9.35 && recoUpsilon.M() < 9.55) ? true : false;
			goodUpsilonMassCut = ((recoUpsilon.M() > minUpsilonMass && recoUpsilon.M() < maxUpsilonMass)) ? true : false;
			// goodKinCuts *= (recoUpsilon.M() >minUpsilonMass && recoUpsilon.M() < maxUpsilonMass) ? true : false;
			goodKinCuts *= goodUpsilonMassCut;
			if (analysisBranch == "ZtoJPsi" || analysisBranch == "ZtoUpsilon" ) goodRatioCuts = ( (recoUpsilon.Pt()/recoZ.M() > (35.0/91.2)) && (leadingPhoton->Et()/recoZ.M() > (35.0/91.2))) ? true : false;
			if (analysisBranch == "HtoJPsi" || analysisBranch == "HtoUpsilon" ) goodRatioCuts = ( (recoUpsilon.Pt()/recoZ.M() > (35.0/125.0)) && (leadingPhoton->Et()/recoZ.M() > (35.0/125.0))) ? true : false;
			// goodKinCuts *= (recoUpsilon.Pt()/recoZ.M() > (35.0/91.2)) ? true : false;
			// goodKinCuts *= (leadingPhoton->Et()/recoZ.M() > (35.0/91.2)) ? true : false;
			goodKinCuts *= goodRatioCuts;

			// if (analysisBranch == "ZtoUpsilon" || analysisBranch == "HtoUpsilon" ) goodKinCuts *= (deltaR(leadingMuon->Eta(), leadingMuon->Phi(), trailingMuon->Eta(), trailingMuon->Phi()) > 0.25);
			// if (analysisBranch == "ZtoUpsilon" || analysisBranch == "HtoUpsilon" ) goodKinCuts *= ((deltaR(leadingMuon->Eta(), leadingMuon->Phi(), trailingMuon->Eta(), trailingMuon->Phi()) > 0.25) && (deltaR(leadingMuon->Eta(), leadingMuon->Phi(), trailingMuon->Eta(), trailingMuon->Phi()) < 0.95));


			goodZMassCut = (recoZ.M() > minHZMassLeft && recoZ.M() < maxHZMassRight) ? true : false;

			goodCategory = (leadingPhoton->photonR9 >= minPhotonR9 && leadingPhoton->photonR9 < maxPhotonR9 && fabs(leadingPhoton->photonSCEta) >= minPhotonAbsEta && fabs(leadingPhoton->photonSCEta) < maxPhotonAbsEta);
			goodKinCuts *= goodCategory;


			// goodDeltaRLeadTrail = (deltaR(leadingMuon->Eta(), leadingMuon->Phi(), trailingMuon->Eta(), trailingMuon->Phi()) > 2.3) ? true : false;
			// goodKinCuts *= goodDeltaRLeadTrail;

			// Trailing muon ISO
			// isTrailingMuonISO = trailingMuon->muonIsISO;
			// goodKinCuts *= isTrailingMuonISO;

			// // dimuon pT cut
			// goodKinCuts *= ( recoUpsilon.Pt() > 35.0 ) ? true : false;



			if (goodKinCuts) {
				h_withKin_LeadingMu_pt->Fill(leadingMuon->Pt(),totalWeight);
				h_withKin_LeadingMu_eta->Fill(leadingMuon->Eta(),totalWeight);
				h_withKin_LeadingMu_phi->Fill(leadingMuon->Phi(),totalWeight);

				h_withKin_TrailingMu_pt->Fill(trailingMuon->Pt(),totalWeight);
				h_withKin_TrailingMu_eta->Fill(trailingMuon->Eta(),totalWeight);
				h_withKin_TrailingMu_phi->Fill(trailingMuon->Phi(),totalWeight);

				h_withKin_Photon_pt->Fill(leadingPhoton->Et(),totalWeight);
				h_withKin_Photon_eta->Fill(leadingPhoton->photonSCEta,totalWeight);
				h_withKin_Photon_phi->Fill(leadingPhoton->Phi(),totalWeight);

				h_withKin_deltaR_Leading_Trailing->Fill(deltaR(leadingMuon->Eta(), leadingMuon->Phi(), trailingMuon->Eta(), trailingMuon->Phi()),totalWeight);
				h_withKin_deltaR_Leading_Photon->Fill(deltaR(leadingMuon->Eta(), leadingMuon->Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()),totalWeight);
				h_withKin_deltaR_Trailing_Photon->Fill(deltaR(trailingMuon->Eta(), trailingMuon->Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()),totalWeight);
				h_withKin_deltaR_Upsilon_Photon->Fill(deltaR(recoUpsilon.Eta(), recoUpsilon.Phi(), leadingPhoton->Eta(), leadingPhoton->Phi()),totalWeight);
				h_withKin_deltaPhi_Upsilon_Photon->Fill(fabs(deltaPhi(recoUpsilon.Phi(), leadingPhoton->Phi())),totalWeight);

				h_withKin_Upsilon_Mass->Fill(recoUpsilon.M(),totalWeight);
				h_withKin_Upsilon_Mass_LargeRange->Fill(recoUpsilon.M(),totalWeight);
				h_withKin_Upsilon_Pt->Fill(recoUpsilon.Pt(),totalWeight);
				h_withKin_Upsilon_eta->Fill(recoUpsilon.Eta(),totalWeight);
				h_withKin_Upsilon_phi->Fill(recoUpsilon.Phi(),totalWeight);

				mHZ = recoZ.M();
				mMuMNU = recoUpsilon.M();
				mHZWeight = totalWeight;
				if (isData){
					if (recoZ.M() < maxHZMassLeft || recoZ.M() > minHZMassRight) {
						h_withKin_Z_Mass->Fill(recoZ.M(),totalWeight);
						// outputTreeFile->cd();
						// cout << "mHZ: "<< mHZ << endl;
					}
					outTree->Fill();
					mHZ = -99.0;
					mHZWeight = 1.;
				} else {
					h_withKin_Z_Mass->Fill(recoZ.M(),totalWeight);
					outTree->Fill();
					mHZ = -99.0;
					mHZWeight = 1.;
				}
				// mHZ = recoZ.M();
				// mHZWeight = totalWeight;
				h_withKin_Z_Pt->Fill(recoZ.Pt(),totalWeight);
				h_withKin_Z_eta->Fill(recoZ.Eta(),totalWeight);
				h_withKin_Z_phi->Fill(recoZ.Phi(),totalWeight);

				//energy ratios
				h_withKin_upsilonPt_over_zMass->Fill(recoUpsilon.Pt()/recoZ.M(),totalWeight);
				h_withKin_photonPt_over_zMass->Fill(leadingPhoton->Et()/recoZ.M(),totalWeight);

				//2D masss plot
				h_withKin_Upsilon_Mass_Z_Mass->Fill(recoUpsilon.M(), recoZ.M(),totalWeight);
				//3D masss plot
				h_withKin_Upsilon_Mass_Z_Mass_Z_Pt->Fill(recoUpsilon.M(), recoZ.M(), recoZ.Pt(),totalWeight);

			}
		}
 

		// evts count
		// xSecs and BRs: https://docs.google.com/spreadsheets/d/1zP8P9kp-yFrkMu9bGt4fpIirKAKYlH-w2em_kVkYYKw/edit#gid=0
		double mcWeight = 1.0;
		if (sampleSource->GetString() == "ZToUpsilon1SGamma" && !isData) 
			mcWeight = (6.9806E-05*0.7222*3.5860E+04/(double)totalEvts)*(*polWgt);
			// countTotalEvts += 1.0*((!isData) ? (puWgt)*(*polWgt)*(6.9806E-05*0.7222*3.5860E+04/(double)totalEvts) : 1.0);

		if (sampleSource->GetString() == "ZToUpsilon2SGamma" && !isData) 
			mcWeight = (6.9806E-05*0.7222*3.5860E+04/(double)totalEvts)*(*polWgt); 
			// countTotalEvts += 1.0*((!isData) ? (puWgt)*(*polWgt)*(6.9806E-05*0.7222*3.5860E+04/(double)totalEvts) : 1.0);

		if (sampleSource->GetString() == "ZToUpsilon3SGamma" && !isData)  
			mcWeight = (6.9806E-05*0.7222*3.5860E+04/(double)totalEvts)*(*polWgt);
			// countTotalEvts += 1.0*((!isData) ? (puWgt)*(*polWgt)*(6.9806E-05*0.7222*3.5860E+04/(double)totalEvts) : 1.0);

		if (sampleSource->GetString() == "ZToJPsiGamma" && !isData)  
			mcWeight = (3.3898E-04*0.7015*3.5860E+04/(double)totalEvts)*(*polWgt);
			// countTotalEvts += 1.0*((!isData) ? (puWgt)*(*polWgt)*(3.3898E-04*0.7015*3.5860E+04/(double)totalEvts) : 1.0);

		if (sampleSource->GetString() == "ZGTo2MuG_MMuMu-2To15" && !isData)  
			mcWeight = (7.9260E-02*3.5860E+04/(double)totalEvts);
			// countTotalEvts += 1.0*((!isData) ? (puWgt)*(*polWgt)*(7.9260E-02*3.5860E+04/(double)totalEvts) : 1.0);

		if (sampleSource->GetString() == "HToUpsilon1SGamma" && !isData)  
			mcWeight = (6.3582E-09*3.5860E+04/(double)totalEvts)*(*polWgt);
			// mcWeight = (8.4271E-10*3.5860E+04/(double)totalEvts)*(*polWgt);
			// countTotalEvts += 1.0*((!isData) ? (puWgt)*(*polWgt)*(8.4271E-10*3.5860E+04/(double)totalEvts) : 1.0);

		if (sampleSource->GetString() == "HToUpsilon2SGamma" && !isData)  
			mcWeight = (2.5116E-09*3.5860E+04/(double)totalEvts)*(*polWgt);
			// mcWeight = (2.1682E-09*3.5860E+04/(double)totalEvts)*(*polWgt);
			// countTotalEvts += 1.0*((!isData) ? (puWgt)*(*polWgt)*(2.1682E-09*3.5860E+04/(double)totalEvts) : 1.0);

		if (sampleSource->GetString() == "HToUpsilon3SGamma" && !isData)   
			mcWeight = (2.5824E-09*3.5860E+04/(double)totalEvts)*(*polWgt);
			// mcWeight = (2.9582E-09*3.5860E+04/(double)totalEvts)*(*polWgt);
			// countTotalEvts += 1.0*((!isData) ? (puWgt)*(*polWgt)*(2.9582E-04*3.5860E+04/(double)totalEvts) : 1.0);
		
		if (sampleSource->GetString() == "HToJPsiGamma" && !isData)  
			mcWeight = (9.2493E-06*3.5860E+04/(double)totalEvts)*(*polWgt);
			// mcWeight = (9.7797E-06*3.5860E+04/(double)totalEvts)*(*polWgt);
			// countTotalEvts += 1.0*((!isData) ? (puWgt)*(*polWgt)*(9.2493E-06*3.5860E+04/(double)totalEvts) : 1.0);
		
		if (sampleSource->GetString() == "HDalitz" && !isData)  
			mcWeight = (1.8614E-03*3.5860E+04/(double)totalEvts);
			// countTotalEvts += 1.0*((!isData) ? (puWgt)*(*polWgt)*(1.8614E-03*3.5860E+04/(double)totalEvts) : 1.0);
		// if (isData) 

		// countTotalEvts += 1.0; 
		countTotalEvts += 1.0*((!isData) ? (mcWeight)*(puWgt) : 1.0);
		// countTotalEvts += 1.0;
		// cout << "isData: " << isData << endl;
		// cout << "--------------------------> iEvt (" << outHistoAppend << " - " << analysisBranch << " - " << selCategory << " - " << systMaskYields << "): " << iEvt <<  endl;
		// cout << "--------------------------> countTotalEvts (" << outHistoAppend << " - " << analysisBranch << " - " << selCategory << " - " << systMaskYields << "): " << countTotalEvts << endl;

		if (*goodTriggerEvt) countTrigger += 1.0*((!isData) ? (mcWeight)*(puWgt)*(triggerWgt) : 1.0);

		if (*goodTriggerEvt && *goodMuonPairPreSel) countMuonPreSel += 1.0*((!isData) ? (mcWeight)*(puWgt)*(triggerWgt) : 1.0);
		
		if (*goodTriggerEvt && *goodMuonPairPreSel && *goodMuonPairSel) countMuonIDISO += 1.0*((!isData) ? (mcWeight)*(puWgt)*(triggerWgt)*(muonIDWgt) : 1.0);
		
		if (*goodTriggerEvt && *goodMuonPairPreSel && *goodMuonPairSel && *goodPhotonSel) countPhotonSel += 1.0*((!isData) ? (mcWeight)*(puWgt)*(triggerWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt) : 1.0);
		
		if (*goodTriggerEvt && *goodMuonPairPreSel && *goodMuonPairSel && *goodPhotonSel && goodDeltaRMuonsPhoton) countMuonToPhoton += 1.0*((!isData) ? (mcWeight)*(puWgt)*(triggerWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt) : 1.0);
		
		if (*goodTriggerEvt && *goodMuonPairPreSel && *goodMuonPairSel && *goodPhotonSel && goodDeltaRMuonsPhoton && goodDeltaRPhiUpsilonPhoton) countUpsilonToPhoton += 1.0*((!isData) ? (mcWeight)*(puWgt)*(triggerWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt) : 1.0);
		
		if (*goodTriggerEvt && *goodMuonPairPreSel && *goodMuonPairSel && *goodPhotonSel && goodDeltaRMuonsPhoton && goodDeltaRPhiUpsilonPhoton && goodUpsilonMassCut) countUpsilonMassCut += 1.0*((!isData) ? (mcWeight)*(puWgt)*(triggerWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt) : 1.0);
		
		if (*goodTriggerEvt && *goodMuonPairPreSel && *goodMuonPairSel && *goodPhotonSel && goodDeltaRMuonsPhoton && goodDeltaRPhiUpsilonPhoton && goodUpsilonMassCut && goodRatioCuts) countRatioCuts += 1.0*((!isData) ? (mcWeight)*(puWgt)*(triggerWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt) : 1.0);
		
		if (*goodTriggerEvt && *goodMuonPairPreSel && *goodMuonPairSel && *goodPhotonSel && goodDeltaRMuonsPhoton && goodDeltaRPhiUpsilonPhoton && goodUpsilonMassCut && goodRatioCuts && goodZMassCut && goodCategory) countZMassCut += 1.0*((!isData) ? (mcWeight)*(puWgt)*(triggerWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt) : 1.0);
		// if (goodKinCuts) countZMassCut += 1.0*((!isData) ? (mcWeight)*(puWgt)*(triggerWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt) : 1.0);
		
		// if (*goodTriggerEvt && *goodMuonPairPreSel && *goodMuonPairSel && *goodPhotonSel && goodDeltaRMuonsPhoton && goodDeltaRPhiUpsilonPhoton && goodUpsilonMassCut && goodRatioCuts && goodZMassCut && goodCategory) countZMassCut += 1.0*((!isData) ? (mcWeight)*(puWgt)*(triggerWgt)*(muonIDWgt)*(photonMVAIDWgt)*(photonEleVetoWgt) : 1.0);


	} // end events loop

	// cout << "#####################################################################################" << endl;
	// cout << "(" << outHistoAppend << " - " << analysisBranch << " - " << selCategory << " - " << systMaskYields << ")" <<  endl;
	// cout << "-- totalEvts: " << totalEvts << endl;
	// cout << "-- iEvt: " << iEvt << endl;
	// cout << "-- countTotalEvts: " << std::setprecision(15) << countTotalEvts << endl;
	// cout << "-- countTotalEvts: " << (int)countTotalEvts << endl;
	// cout << "#####################################################################################" << endl;

    // post-processing 
	cout << "\n\n\nWriting output text file..." << endl;
	// evtsCount
	ofstream evtsCountFile;
	evtsCountFile.open ("evtsCountFiles/evtsCountFile_" + outHistoAppend + "_" + analysisBranch + "_" + selCategory + "_" + systMaskYields + ".json");
	evtsCountFile << "{" << endl;
	evtsCountFile << "\"sample\" : \"" + outHistoAppend + "\"," << endl;
	evtsCountFile << "\"analysisBranch\" : \"" + analysisBranch + "\"," << endl;
	evtsCountFile << "\"selCategory\" : \"" + selCategory + "\"," << endl;
	evtsCountFile << "\"systMaskYields\" : \"" + systMaskYields + "\"," << endl;
	evtsCountFile << "\"total\" : " << std::setprecision(15)  << countTotalEvts << "," << endl;
	evtsCountFile << "\"trigger\" : " << std::setprecision(15)  << countTrigger << "," << endl;
	evtsCountFile << "\"muon_presel\" : " << std::setprecision(15)  << countMuonPreSel << "," << endl;
	evtsCountFile << "\"muon_id\" : " << std::setprecision(15)  << countMuonIDISO << "," << endl;
	evtsCountFile << "\"photon_sel\" : " << std::setprecision(15)  << countPhotonSel << "," << endl;
	evtsCountFile << "\"deltaR_muon_to_photon\" : " << std::setprecision(15)  << countMuonToPhoton << "," << endl;
	evtsCountFile << "\"deltaRPhi_quarkonia_to_photon\" : " << std::setprecision(15)  << countUpsilonToPhoton << "," << endl;
	evtsCountFile << "\"quarkonia_mass_cut\" : " << std::setprecision(15)  << countUpsilonMassCut << "," << endl;
	evtsCountFile << "\"ratio_cuts\" : " << std::setprecision(15)  << countRatioCuts << "," << endl;
	evtsCountFile << "\"hz_mass_cut\" : " << std::setprecision(15)  << countZMassCut << endl;
	evtsCountFile << "}" << endl;
	evtsCountFile.close();



	cout << "\n\n\nWriting output file..." << endl;
	outFile->Write();
	outputTreeFile->Write();

	// recursive systematics
	if (systMaskYields == "ZZZZZ") {
		if (!isData) {
			//recursive calls
			// systMaskYields:
			// (PILE-UP, TRIGGER, MUON ID, PHOTON ID, PHOTON-ELECTRON VETO)
			// P -> plus 1 sigma
			// Z -> nominal value (zero sigmas)
			// M -> minus 1 sigma
			plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, outHistoAppend, analysisBranch, selCategory, "PZZZZ", isData) ;
			plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, outHistoAppend, analysisBranch, selCategory, "MZZZZ", isData) ;
			plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, outHistoAppend, analysisBranch, selCategory, "ZPZZZ", isData) ;
			plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, outHistoAppend, analysisBranch, selCategory, "ZMZZZ", isData) ;
			plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, outHistoAppend, analysisBranch, selCategory, "ZZPZZ", isData) ;
			plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, outHistoAppend, analysisBranch, selCategory, "ZZMZZ", isData) ;
			plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, outHistoAppend, analysisBranch, selCategory, "ZZZPZ", isData) ;
			plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, outHistoAppend, analysisBranch, selCategory, "ZZZMZ", isData) ;
			plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, outHistoAppend, analysisBranch, selCategory, "ZZZZP", isData) ;
			plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, outHistoAppend, analysisBranch, selCategory, "ZZZZM", isData) ;
		}
	}

	cout << "\nDone!\n\n\n\n\n" << endl;


} //end plots_ZtoUpsilonPhoton


