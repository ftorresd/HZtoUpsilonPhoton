#include <iostream>
#include <algorithm>
#include <math.h>  
// #include <stdlib.h>

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
#include "TDirectory.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"
#include "TLatex.h"

 
// #include "plugins/tdrstyle.C"
#include "plugins/plotterTools.h"
// #include "plugins/ggNtuplesFilesReader.h"
// #include "plugins/roccor2016/RoccoR.cc"
// #include "plugins/deltaR_deltaPhi.h"
// #include "plugins/anaObjects.h"
// #include "plugins/puWeight.h"
// #include "plugins/upsilonPolarizationAngle.h"
// #include "plugins/getSF.h"


// #ifdef __CINT__
// #pragma link C++ class anaMuon+;
// #pragma link C++ class anaPhoton+;
// #pragma link C++ class anaGenPart+;
// // #pragma link C++ class TLorentzVector+;
// #endif
#include <regex>

// #include <boost/regex.hpp>
// using namespace boost;



using namespace std;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DOES THE ACTUAL PLOTTING
void plotter_HZtoUpsilonPhoton(string histoDataFilePath, string histoMCSignalFilePath, string histoMCBackgroundFilePath, string analysisBranch)  
{
	auto * histoDataFile = TFile::Open(histoDataFilePath.c_str());
	auto * histoMCSignalFile = TFile::Open(histoMCSignalFilePath.c_str());
	auto * histoMCBackgroundFile = TFile::Open(histoMCBackgroundFilePath.c_str());
	// auto * histoMCSignalFile = TFile::Open(histoDataFilePath.c_str());


	// plotter
	setTDRStyle();
	system("rm -fr plotFiles; mkdir plotFiles");

	//////////////////////////////////////////////////////////////////
	// GEN - UNPOLARIZED
	// gen unpolarized muons
	plotter_LeadingTrailing(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_LeadingMu_pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_TrailingMu_pt"), 
		"mc/unpolarized/h_Gen_Mu_pt",
		true
		); 
	plotter_LeadingTrailing(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_LeadingMu_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_TrailingMu_eta"), 
		"mc/unpolarized/h_Gen_Mu_eta",
		false
		); 
	plotter_LeadingTrailing(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_LeadingMu_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_TrailingMu_phi"), 
		"mc/unpolarized/h_Gen_Mu_phi",
		false
		); 

	// gen unpolarized photon
	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_Photon_pt"), 
		"mc/unpolarized/h_Gen_Photon_pt",
		"Photon",
		true
		); 
	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_Photon_eta"), 
		"mc/unpolarized/h_Gen_Photon_eta",
		"Photon",
		false
		); 
	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_Photon_phi"), 
		"mc/unpolarized/h_Gen_Photon_phi",
		"Photon",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_deltaR_Leading_Trailing"), 
		"mc/unpolarized/h_Gen_deltaR_Leading_Trailing",
		"",
		false
		); 

	plotter_LeadingTrailing(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_deltaR_Leading_Photon"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_deltaR_Trailing_Photon"), 
		"mc/unpolarized/h_Gen_deltaR_Mu_Photon",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_deltaR_Upsilon_Photon"), 
		"mc/unpolarized/h_Gen_deltaR_Upsilon_Photon",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_deltaPhi_Upsilon_Photon"), 
		"mc/unpolarized/h_Gen_deltaPhi_Upsilon_Photon",
		"",
		false
		); 
	
	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_Upsilon_Mass"), 
		"mc/unpolarized/h_Gen_Upsilon_Mass",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_Upsilon_Pt"), 
		"mc/unpolarized/h_Gen_Upsilon_Pt",
		"",
		true
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_Upsilon_eta"), 
		"mc/unpolarized/h_Gen_Upsilon_eta",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_Upsilon_phi"), 
		"mc/unpolarized/h_Gen_Upsilon_phi",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_Z_Mass"), 
		"mc/unpolarized/h_Gen_Z_Mass",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_Z_Pt"), 
		"mc/unpolarized/h_Gen_Z_Pt",
		"",
		true
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_Z_eta"), 
		"mc/unpolarized/h_Gen_Z_eta",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_Z_phi"), 
		"mc/unpolarized/h_Gen_Z_phi",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_upsilonPt_over_zMass"), 
		"mc/unpolarized/h_Gen_upsilonPt_over_zMass",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_photonPt_over_zMass"), 
		"mc/unpolarized/h_Gen_photonPt_over_zMass",
		"",
		false
		); 








	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// GEN - UNPOLARIZED
	// gen unpolarized muons
	plotter_LeadingTrailing(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_LeadingMu_pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_TrailingMu_pt"), 
		"mc/polarized/h_Gen_withPolWeight_Mu_pt",
		true
		); 
	plotter_LeadingTrailing(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_LeadingMu_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_TrailingMu_eta"), 
		"mc/polarized/h_Gen_withPolWeight_Mu_eta",
		false
		); 
	plotter_LeadingTrailing(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_LeadingMu_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_TrailingMu_phi"), 
		"mc/polarized/h_Gen_withPolWeight_Mu_phi",
		false
		); 

	// gen unpolarized photon
	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_Photon_pt"), 
		"mc/polarized/h_Gen_withPolWeight_Photon_pt",
		"Photon",
		true
		); 
	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_Photon_eta"), 
		"mc/polarized/h_Gen_withPolWeight_Photon_eta",
		"Photon",
		false
		); 
	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_Photon_phi"), 
		"mc/polarized/h_Gen_withPolWeight_Photon_phi",
		"Photon",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_deltaR_Leading_Trailing"), 
		"mc/polarized/h_Gen_withPolWeight_deltaR_Leading_Trailing",
		"",
		false
		); 

	plotter_LeadingTrailing(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_deltaR_Leading_Photon"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_deltaR_Trailing_Photon"), 
		"mc/polarized/h_Gen_withPolWeight_deltaR_Mu_Photon",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_deltaR_Upsilon_Photon"), 
		"mc/polarized/h_Gen_withPolWeight_deltaR_Upsilon_Photon",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_deltaPhi_Upsilon_Photon"), 
		"mc/polarized/h_Gen_withPolWeight_deltaPhi_Upsilon_Photon",
		"",
		false
		); 
	
	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_Upsilon_Mass"), 
		"mc/polarized/h_Gen_withPolWeight_Upsilon_Mass",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_Upsilon_Pt"), 
		"mc/polarized/h_Gen_withPolWeight_Upsilon_Pt",
		"",
		true
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_Upsilon_eta"), 
		"mc/polarized/h_Gen_withPolWeight_Upsilon_eta",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_Upsilon_phi"), 
		"mc/polarized/h_Gen_withPolWeight_Upsilon_phi",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_Z_Mass"), 
		"mc/polarized/h_Gen_withPolWeight_Z_Mass",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_Z_Pt"), 
		"mc/polarized/h_Gen_withPolWeight_Z_Pt",
		"",
		true
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_Z_eta"), 
		"mc/polarized/h_Gen_withPolWeight_Z_eta",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_Z_phi"), 
		"mc/polarized/h_Gen_withPolWeight_Z_phi",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_upsilonPt_over_zMass"), 
		"mc/polarized/h_Gen_withPolWeight_upsilonPt_over_zMass",
		"",
		false
		); 

	plotter_Single(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_withPolWeight_photonPt_over_zMass"), 
		"mc/polarized/h_Gen_withPolWeight_photonPt_over_zMass",
		"",
		false
		); 


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// RECO - NO KIN CUTS

	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_LeadingMu_pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_LeadingMu_pt"), 
		"data_x_mc/noKinCuts/h_noKin_LeadingMu_pt",
		true
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_LeadingMu_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_LeadingMu_eta"), 
		"data_x_mc/noKinCuts/h_noKin_LeadingMu_eta",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_LeadingMu_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_LeadingMu_phi"), 
		"data_x_mc/noKinCuts/h_noKin_LeadingMu_phi",
		false
		); 

	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_TrailingMu_pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_TrailingMu_pt"), 
		"data_x_mc/noKinCuts/h_noKin_TrailingMu_pt",
		true
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_TrailingMu_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_TrailingMu_eta"), 
		"data_x_mc/noKinCuts/h_noKin_TrailingMu_eta",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_TrailingMu_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_TrailingMu_phi"), 
		"data_x_mc/noKinCuts/h_noKin_TrailingMu_phi",
		false
		); 

	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Photon_pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Photon_pt"), 
		"data_x_mc/noKinCuts/h_noKin_Photon_pt",
		true
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Photon_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Photon_eta"), 
		"data_x_mc/noKinCuts/h_noKin_Photon_eta",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Photon_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Photon_phi"), 
		"data_x_mc/noKinCuts/h_noKin_Photon_phi",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_deltaR_Leading_Trailing"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_deltaR_Leading_Trailing"), 
		"data_x_mc/noKinCuts/h_noKin_deltaR_Leading_Trailing",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_deltaR_Leading_Photon"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_deltaR_Leading_Photon"), 
		"data_x_mc/noKinCuts/h_noKin_deltaR_Leading_Photon",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_deltaR_Trailing_Photon"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_deltaR_Trailing_Photon"), 
		"data_x_mc/noKinCuts/h_noKin_deltaR_Trailing_Photon",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_deltaR_Upsilon_Photon"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_deltaR_Upsilon_Photon"), 
		"data_x_mc/noKinCuts/h_noKin_deltaR_Upsilon_Photon",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_deltaPhi_Upsilon_Photon"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_deltaPhi_Upsilon_Photon"), 
		"data_x_mc/noKinCuts/h_noKin_deltaPhi_Upsilon_Photon",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Mass"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Mass"), 
		"data_x_mc/noKinCuts/h_noKin_Upsilon_Mass",
		false
		); 

 	plotter_DataMCSignalBackground(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Mass"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Mass"), 
		(TH1D*)histoMCBackgroundFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Mass"), 
		"data_x_mc/noKinCuts/h_noKin_Upsilon_Mass_Signal_and_Background",
		"#mu#mu Mass (GeV)",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Mass_LargeRange"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Mass_LargeRange"), 
		"data_x_mc/noKinCuts/h_noKin_Upsilon_Mass_LargeRange",
		false
		); 

 	plotter_DataMCSignalBackground(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Mass_LargeRange"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Mass_LargeRange"), 
		(TH1D*)histoMCBackgroundFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Mass_LargeRange"), 
		"data_x_mc/noKinCuts/h_noKin_Upsilon_Mass_Signal_and_Background_LargeRange",
		"#mu#mu Mass (GeV)",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_Pt"), 
		"data_x_mc/noKinCuts/h_noKin_Upsilon_Pt",
		true
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_eta"), 
		"data_x_mc/noKinCuts/h_noKin_Upsilon_eta",
		false
		); 
		
 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Upsilon_phi"), 
		"data_x_mc/noKinCuts/h_noKin_Upsilon_phi",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Z_Mass"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Z_Mass"), 
		"data_x_mc/noKinCuts/h_noKin_Z_Mass",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Z_Pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Z_Pt"), 
		"data_x_mc/noKinCuts/h_noKin_Z_Pt",
		true
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Z_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Z_eta"), 
		"data_x_mc/noKinCuts/h_noKin_Z_eta",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Z_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_Z_phi"), 
		"data_x_mc/noKinCuts/h_noKin_Z_phi",
		false
		); 
				 	
 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_upsilonPt_over_zMass"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_upsilonPt_over_zMass"), 
		"data_x_mc/noKinCuts/h_noKin_upsilonPt_over_zMass",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_photonPt_over_zMass"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/noKinCutsHistos/h_noKin_photonPt_over_zMass"), 
		"data_x_mc/noKinCuts/h_noKin_photonPt_over_zMass",
		false
		); 



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// RECO - WITH KIN CUTS
	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_LeadingMu_pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_LeadingMu_pt"), 
		"data_x_mc/withKinCuts/h_withKin_LeadingMu_pt",
		true
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_LeadingMu_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_LeadingMu_eta"), 
		"data_x_mc/withKinCuts/h_withKin_LeadingMu_eta",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_LeadingMu_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_LeadingMu_phi"), 
		"data_x_mc/withKinCuts/h_withKin_LeadingMu_phi",
		false
		); 

	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_TrailingMu_pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_TrailingMu_pt"), 
		"data_x_mc/withKinCuts/h_withKin_TrailingMu_pt",
		true
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_TrailingMu_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_TrailingMu_eta"), 
		"data_x_mc/withKinCuts/h_withKin_TrailingMu_eta",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_TrailingMu_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_TrailingMu_phi"), 
		"data_x_mc/withKinCuts/h_withKin_TrailingMu_phi",
		false
		); 

	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Photon_pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Photon_pt"), 
		"data_x_mc/withKinCuts/h_withKin_Photon_pt",
		true
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Photon_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Photon_eta"), 
		"data_x_mc/withKinCuts/h_withKin_Photon_eta",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Photon_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Photon_phi"), 
		"data_x_mc/withKinCuts/h_withKin_Photon_phi",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_deltaR_Leading_Trailing"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_deltaR_Leading_Trailing"), 
		"data_x_mc/withKinCuts/h_withKin_deltaR_Leading_Trailing",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_deltaR_Leading_Photon"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_deltaR_Leading_Photon"), 
		"data_x_mc/withKinCuts/h_withKin_deltaR_Leading_Photon",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_deltaR_Trailing_Photon"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_deltaR_Trailing_Photon"), 
		"data_x_mc/withKinCuts/h_withKin_deltaR_Trailing_Photon",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_deltaR_Upsilon_Photon"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_deltaR_Upsilon_Photon"), 
		"data_x_mc/withKinCuts/h_withKin_deltaR_Upsilon_Photon",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_deltaPhi_Upsilon_Photon"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_deltaPhi_Upsilon_Photon"), 
		"data_x_mc/withKinCuts/h_withKin_deltaPhi_Upsilon_Photon",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Mass"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Mass"), 
		"data_x_mc/withKinCuts/h_withKin_Upsilon_Mass",
		false
		); 

  	plotter_DataMCSignalBackground(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Mass"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Mass"), 
		(TH1D*)histoMCBackgroundFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Mass"), 
		"data_x_mc/withKinCuts/h_withKin_Upsilon_Mass_Signal_and_Background",
		"#mu#mu Mass (GeV)",
		false
		); 
  	
 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Mass_LargeRange"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Mass_LargeRange"), 
		"data_x_mc/withKinCuts/h_withKin_Upsilon_Mass_LargeRange",
		false
		); 

  	plotter_DataMCSignalBackground(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Mass_LargeRange"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Mass_LargeRange"), 
		(TH1D*)histoMCBackgroundFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Mass_LargeRange"), 
		"data_x_mc/withKinCuts/h_withKin_Upsilon_Mass_Signal_and_Background_LargeRange",
		"#mu#mu Mass (GeV)",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_Pt"), 
		"data_x_mc/withKinCuts/h_withKin_Upsilon_Pt",
		true
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_eta"), 
		"data_x_mc/withKinCuts/h_withKin_Upsilon_eta",
		false
		); 
		
 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Upsilon_phi"), 
		"data_x_mc/withKinCuts/h_withKin_Upsilon_phi",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Z_Mass"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Z_Mass"), 
		"data_x_mc/withKinCuts/h_withKin_Z_Mass",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Z_Pt"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Z_Pt"), 
		"data_x_mc/withKinCuts/h_withKin_Z_Pt",
		true
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Z_eta"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Z_eta"), 
		"data_x_mc/withKinCuts/h_withKin_Z_eta",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Z_phi"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_Z_phi"), 
		"data_x_mc/withKinCuts/h_withKin_Z_phi",
		false
		); 
				 	
 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_upsilonPt_over_zMass"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_upsilonPt_over_zMass"), 
		"data_x_mc/withKinCuts/h_withKin_upsilonPt_over_zMass",
		false
		); 

 	plotter_DataMC(analysisBranch,
		(TH1D*)histoDataFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_photonPt_over_zMass"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/withKinCutsHistos/h_withKin_photonPt_over_zMass"), 
		"data_x_mc/withKinCuts/h_withKin_photonPt_over_zMass",
		false
		); 

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// POLARIZATION
 	plotter_Pol(analysisBranch,
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genHistos/h_Gen_UnPol"), 
		(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_Pol"), 
		"mc/polarizatioReweight/h_Gen_COS_theta",
		false
		); 
  

	std::size_t found = histoMCSignalFilePath.find("JPsi");
	if(found == std::string::npos) {
	 	// get the other polarization files
	 	// Upsilon1SGamma
	 	// regex_replace(regex_replace(histoMCSignalFilePath, regex("UpsilonGamma_"), regex("Upsilon1SGamma_")
	 	// regex_replace(regex_replace(histoMCSignalFilePath, regex("Z.root"), "P.root"), regex("UpsilonGamma_"), "Upsilon1SGamma_")
	 	cout << regex_replace(regex_replace(histoMCSignalFilePath, regex("Z.root"), "M_default.root"), regex("UpsilonGamma_"), "Upsilon1SGamma_") << endl;
	 	auto * histoMCSignalFilePlus = TFile::Open(regex_replace(regex_replace(histoMCSignalFilePath, regex("Z.root"), "P_default.root"), regex("UpsilonGamma_"), "Upsilon1SGamma_").c_str());
	 	auto * histoMCSignalFileMinus = TFile::Open(regex_replace(regex_replace(histoMCSignalFilePath, regex("Z.root"), "M_default.root"), regex("UpsilonGamma_"), "Upsilon1SGamma_").c_str());

	 	plotter_Pol_extremes(analysisBranch,
			(TH1D*)histoMCSignalFile->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_Pol"), 
			(TH1D*)histoMCSignalFilePlus->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_Pol"), 
			(TH1D*)histoMCSignalFileMinus->Get("default/outputHistos/genwithPolWeightHistos/h_Gen_Pol"), 
			"mc/polarizatioReweight/h_Gen_COS_theta_extremes",
			false
			); 
	}

} //end plotter_ZtoUpsilonPhoton

   


