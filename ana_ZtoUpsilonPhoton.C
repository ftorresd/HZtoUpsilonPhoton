// ######################################################
// Z --> Upsilon + Photon
// ######################################################
// Analysis Code
// Description:  - Read the ggNtuples
//               - Apply corrections           
//               - Produces a ntuple ready for plotting  
// ######################################################


#define IS_MC 1



#include <iostream>
#include <algorithm>
#include <math.h>  



#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "TRandom3.h"
#include "TROOT.h"
#include "TObjString.h"
#include "TDirectory.h"



#include "plugins/ggNtuplesFilesReader.h"
#include "plugins/roccor2016/RoccoR.cc"
#include "plugins/deltaR_deltaPhi.h"
#include "plugins/anaObjects.h"
#include "plugins/puWeight.h"
#include "plugins/upsilonPolarizationAngle.h"
#include "plugins/getSF.h"
#include "plugins/getR9Transform.h"
#include "plugins/getMeanVariance.h"
#include "plugins/translShapeSyst.h"


#ifdef __CINT__
#pragma link C++ class anaMuon+;
#pragma link C++ class anaPhoton+;
#pragma link C++ class anaGenPart+;
#endif

using namespace std;


void ana_ZtoUpsilonPhoton(vector<string> ggNtuplesFiles, int nFiles = -1, string outFileAppend = "", bool isMC = false, string puFile = "", string shapeSystMask = "default")  
{
	
	// output tree
	// TFile outFile("outTree_ZtoUpsilonPhoton.root","RECREATE","ZtoUpsilonPhoton output analysis tree");
	string outputFileName = "outputFiles/outTree_ZtoUpsilonPhoton_"+ outFileAppend + "_" + shapeSystMask+".root";
	// string outputFileName = "outputFiles/outTree_ZtoUpsilonPhoton_"+ outFileAppend + "_shapeSystMask_" + shapeSystMask + ".root";
	TFile * outFile  = new TFile(outputFileName.c_str(),"RECREATE","ZtoUpsilonPhoton output analysis tree");
	// TFile * outFile  = new TFile(outputFileName.c_str(),"UPDATE","ZtoUpsilonPhoton output analysis tree");
	TDirectory * shapeSystDirectory = outFile->mkdir(shapeSystMask.c_str());
	shapeSystDirectory->cd();
	TTree * outTree = new TTree("outTree_ZtoUpsilonPhoton","ZtoUpsilonPhoton output analysis tree");

	// loads the ggNtuples 
	if (nFiles > 0) {
		ggNtuplesFiles.resize(nFiles);	
	}
	TTreeReader * dataReader = ggNtuplesFilesReader( ggNtuplesFiles, "ggNtuplizer/EventTree" );
	TTree * dataTree = dataReader->GetTree();
	dataTree->AddFriend("muonsRands", ("data/muonsRands/muonsRands_"+outFileAppend+".root").c_str());

	////////////////////////////////////////////////////////////////////
	// define readers
	// event
	// TTreeReaderValue< int > run(*dataReader, "run");
	TTreeReaderValue< ULong64_t > HLTEleMuX(*dataReader, "HLTEleMuX");


	// muons
	TTreeReaderValue< int > nMu(*dataReader, "nMu");
	TTreeReaderArray< float > muPt(*dataReader, "muPt");
	TTreeReaderArray< float > muEta(*dataReader, "muEta");
	TTreeReaderArray< float > muPhi(*dataReader, "muPhi");
	TTreeReaderArray< int > muCharge(*dataReader, "muCharge");
	TTreeReaderArray< int > muType(*dataReader, "muType");
	TTreeReaderArray< double > rand1(*dataReader, "rand1");
	TTreeReaderArray< double > rand2(*dataReader, "rand2");
 	// Types of muons
	// REF: https://github.com/cms-sw/cmssw/blob/master/DataFormats/MuonReco/interface/Muon.h
	// muon type - type of the algorithm that reconstructed this muon
	// multiple algorithms can reconstruct the same muon
	const unsigned int GlobalMuon     =  1<<1;
	const unsigned int TrackerMuon    =  1<<2;
	const unsigned int StandAloneMuon =  1<<3;
	const unsigned int CaloMuon =  1<<4;
	const unsigned int PFMuon =  1<<5;
	const unsigned int RPCMuon =  1<<6; 
	const unsigned int GEMMuon =  1<<7;
	const unsigned int ME0Muon =  1<<8;
	TTreeReaderArray< unsigned short > muIDbit(*dataReader, "muIDbit");
	TTreeReaderArray< int > muMatches(*dataReader, "muMatches");
	// TTreeReaderArray< unsigned int > muFiredTrgs(*dataReader, "muFiredTrgs");
	TTreeReaderArray< int > muTrkLayers(*dataReader, "muTrkLayers");
	TTreeReaderArray< float > muD0(*dataReader, "muD0");
	TTreeReaderArray< float > muDz(*dataReader, "muDz");
	TTreeReaderArray< int > muBestTrkType(*dataReader, "muBestTrkType");
	TTreeReaderArray< float > muBestTrkPt(*dataReader, "muBestTrkPt");
	TTreeReaderArray< float > muBestTrkPtError(*dataReader, "muBestTrkPtError");
	TTreeReaderArray< float > muSIP(*dataReader, "muSIP");
	TTreeReaderArray< int > muPixelHits(*dataReader, "muPixelHits");
	TTreeReaderArray< int > muPixelLayers(*dataReader, "muPixelLayers");
	TTreeReaderArray< float > muPFChIso03(*dataReader, "muPFChIso03");
	TTreeReaderArray< float > muPFPhoIso03(*dataReader, "muPFPhoIso03");
	TTreeReaderArray< float > muPFNeuIso03(*dataReader, "muPFNeuIso03");
	TTreeReaderArray< float > muPFPUIso03(*dataReader, "muPFPUIso03");

	
	// photons
	TTreeReaderValue< int > nPho(*dataReader, "nPho");
	TTreeReaderArray< float > phoEt(*dataReader, "phoEt");
	TTreeReaderArray< float > phoCalibEt(*dataReader, "phoCalibEt");
	TTreeReaderArray< float > phoEta(*dataReader, "phoEta");
	TTreeReaderArray< float > phoSCEta(*dataReader, "phoSCEta");
	TTreeReaderArray< float > phoPhi(*dataReader, "phoPhi");
	TTreeReaderArray< float > phoIDMVA(*dataReader, "phoIDMVA");
	TTreeReaderArray< float > phoR9(*dataReader, "phoR9");
	TTreeReaderArray< unsigned short > phoIDbit(*dataReader, "phoIDbit");
	TTreeReaderArray< int > phoEleVeto(*dataReader, "phoEleVeto");

	TTreeReaderArray< float > phoScale_stat_up(*dataReader, "phoScale_stat_up");
	TTreeReaderArray< float > phoScale_stat_dn(*dataReader, "phoScale_stat_dn");
	TTreeReaderArray< float > phoScale_syst_up(*dataReader, "phoScale_syst_up");
	TTreeReaderArray< float > phoScale_syst_dn(*dataReader, "phoScale_syst_dn");
	TTreeReaderArray< float > phoScale_gain_up(*dataReader, "phoScale_gain_up");
	TTreeReaderArray< float > phoScale_gain_dn(*dataReader, "phoScale_gain_dn");
	TTreeReaderArray< float > phoResol_rho_up(*dataReader, "phoResol_rho_up");
	TTreeReaderArray< float > phoResol_rho_dn(*dataReader, "phoResol_rho_dn");
	TTreeReaderArray< float > phoResol_phi_up(*dataReader, "phoResol_phi_up");
	TTreeReaderArray< float > phoResol_phi_dn(*dataReader, "phoResol_phi_dn");


	//MC info
	#ifdef IS_MC
		TTreeReaderArray< float > puTrue(*dataReader, "puTrue");
		TTreeReaderValue< int > nMC(*dataReader, "nMC");
		TTreeReaderArray< int > mcPID(*dataReader, "mcPID");
		TTreeReaderArray< int > mcMomPID(*dataReader, "mcMomPID");
		TTreeReaderArray< int > mcGMomPID(*dataReader, "mcGMomPID");
		TTreeReaderArray< float > mcPt(*dataReader, "mcPt");
		TTreeReaderArray< float > mcEta(*dataReader, "mcEta");
		TTreeReaderArray< float > mcPhi(*dataReader, "mcPhi");
	#endif 

	auto * puInfo = new puWeight(isMC, puFile);
	auto * sfMVAIDFile = new TFile("data/SFs/egammaEffi.txt_EGM2D.root"); // photon MVA ID scale factor
	auto * sfMuonIDFile = new TFile("data/SFs/final_HZZ_Moriond17Preliminary_v4.root"); // photon MVA ID scale factor
	auto * sfTriggerFile = new TFile("data/SFs/TrigEff_HZZID_FinalVersion.root"); // trigger scale factor
	
	////////////////////////////////////////////////////////////////////
	//xSec
	TObjString sampleSource(outFileAppend.c_str());
	outTree->Branch("sampleSource", &sampleSource) ;

	//output objects - MUONS
	anaMuon leadingMuon = anaMuon();
	outTree->Branch("leadingMuon",&leadingMuon);

	anaMuon trailingMuon = anaMuon();
	outTree->Branch("trailingMuon",&trailingMuon);

	
	//output objects - PHOTONS
	anaPhoton leadingPhoton = anaPhoton();
	outTree->Branch("leadingPhoton",&leadingPhoton);

	//output objects - PHOTONS
	// TLorentzVector recoUpsilon = TLorentzVector();
	// outTree->Branch("recoUpsilon",&recoUpsilon);

	//output objects - PHOTONS
	// TLorentzVector recoZ = TLorentzVector();
	// outTree->Branch("recoZ",&recoZ);

	//output objects - isGoodEvent
	bool isGoodEvent = true;
	outTree->Branch("isGoodEvent",&isGoodEvent);

	//output objects - goodTriggerEvt
	bool goodTriggerEvt = true;
	outTree->Branch("goodTriggerEvt",&goodTriggerEvt);

	//output objects - goodMuonPairSel
	bool goodMuonPairSel = true;
	outTree->Branch("goodMuonPairSel",&goodMuonPairSel);

	//output objects - goodMuonPairSel
	bool goodMuonPairId = false;
	outTree->Branch("goodMuonPairId",&goodMuonPairId);
	

	//output objects - goodMuonPairPreSel
	bool goodMuonPairPreSel = true;
	outTree->Branch("goodMuonPairPreSel",&goodMuonPairPreSel);

	//output objects - goodPhotonSel
	bool goodPhotonSel = true;
	outTree->Branch("goodPhotonSel",&goodPhotonSel);

	//MC
	outTree->Branch("isMC",&isMC);

	//output objects -  PU weight
	double puWgt_nominal = 1.0;
	outTree->Branch("puWgt_nominal",&puWgt_nominal);	

	double puWgt_up = 1.0;
	outTree->Branch("puWgt_up",&puWgt_up);	
	
	double puWgt_down = 1.0;
	outTree->Branch("puWgt_down",&puWgt_down);	
	
	// double puWgtErr = 1.0;
	// outTree->Branch("puWgtErr",&puWgtErr);	

	//output objects -  gen particles
	anaGenPart genMuPlus = anaGenPart();
	outTree->Branch("genMuPlus",&genMuPlus);

	anaGenPart genMuMinus = anaGenPart();
	outTree->Branch("genMuMinus",&genMuMinus);

	anaGenPart genPhoton = anaGenPart();
	outTree->Branch("genPhoton",&genPhoton);

	//output objects -  polarization weight
	double polWgt_Nominal = 1.0;
	outTree->Branch("polWgt_Nominal",&polWgt_Nominal);	

	double polWgt_PLUS = 1.0;
	outTree->Branch("polWgt_PLUS",&polWgt_PLUS);	

	double polWgt_MINUS = 1.0;
	outTree->Branch("polWgt_MINUS",&polWgt_MINUS);	

	//output objects -  muonID SF
	pair<double,double> muonIDSF = {1.0, 0.0};
	outTree->Branch("muonIDSF",&muonIDSF);	

	//output objects -  photon MVA ID SF
	pair<double,double> photonMVAIDSF = {1.0, 0.0};
	outTree->Branch("photonMVAIDSF",&photonMVAIDSF);	

	//output objects -  photon electron veto
	pair<double,double> photonEleVetoSF = {1.0, 0.0};
	outTree->Branch("photonEleVetoSF",&photonEleVetoSF);

	//output objects -  trigger sf
	pair<double,double> triggerSF = {1.0, 0.0};
	outTree->Branch("triggerSF",&triggerSF);



	////////////////////////////////////////////////////////////////////
	// Rocherter Corrections
	// 	Example:
	// -------------------------------------------------------------------------------------
	// #include "RoccoR.cc"

	// RoccoR  rc("rcdata.2016.v3"); //directory path as input for now; initialize only once, contains all variations

	// //for each data muon in the loop, use this function to get a scale factor for its momentum:
	// double dataSF = rc.kScaleDT(charge, pt, eta, phi, s=0, m=0);

	// //for MC, if matched gen-level muon (genPt) is available, use this function
	// double mcSF = rc.kScaleFromGenMC(Q, pt, eta, phi, nl, genPt, u1, s=0, m=0);

	// //if not, then:
	// double mcSF = rc.kScaleAndSmearMC(Q, pt, eta, phi, nl, u1, u2, s=0, m=0);
	// -------------------------------------------------------------------------------------

	// Here: 
	// Q is charge
	// nl is trackerLayersWithMeasurement 
	// u1 and u2 are random numbers distributed uniformly between 0 and 1 (gRandom->Rndm());
	// s is error set (default is 0)
	// m is error member (default is 0)
	// For MC, when switching to different error sets/members for a given muon, random numbers (u1 and u2) should remain unchanged. 


	RoccoR  rc("plugins/roccor2016/rcdata.2016.v3"); // define corrections object


	////////////////////////////////////////////////////////////////////
	// numer of entries
	auto totalEvts = dataTree->GetEntries();
	// auto printEvery = 100000;
	auto printEvery = 10000;
	// auto printEvery = 1;
	if (!isMC) printEvery = 1000000;
	cout << "\nN. Entries (" << outFileAppend <<  "): " << totalEvts << endl;
	cout << "\nPrinting every: " << printEvery << " events" << endl;
	cout << "\nLooping over events... \n" << endl;

	// dataTree->Print();


	////////////////////////////////////////////////////////////////////
	// main loop
	auto iEvt = 0;
	while (dataReader->Next()) { // loop over events
		if (iEvt % printEvery == 0) cout << "----------------------------------------> Events read (" << outFileAppend <<  " - " << shapeSystMask << "): " << iEvt << " / " << totalEvts << " - ~"<< round(((float)iEvt/(float)totalEvts)*100) << "%"<< endl;
		iEvt++;

		////////////////////////////////////////////////////////////////////
		// clear output tree variables 
		leadingMuon.clear();
		trailingMuon.clear();
		leadingPhoton.clear();
		// recoUpsilon.SetPtEtaPhiM(-99,-99,-99,-99);
		// recoZ.SetPtEtaPhiM(-99,-99,-99,-99); 
		genMuPlus.clear();
		genMuMinus.clear();
		genPhoton.clear();
		puWgt_nominal = 1.0;
		puWgt_up = 1.0;
		puWgt_down = 1.0;
		polWgt_Nominal = 1.0;
		polWgt_PLUS = 1.0;
		polWgt_MINUS = 1.0;
		muonIDSF = {1.0, 0.0};
		photonMVAIDSF = {1.0, 0.0};
		photonEleVetoSF = {1.0, 0.0};

		////////////////////////////////////////////////////////////////////
		// MC stuff
		if (isMC){
			#ifdef IS_MC
			// PU reweighting
			puWgt_nominal = puInfo->getWeight_nominal(puTrue[1]); 
			puWgt_up = puInfo->getWeight_up(puTrue[1]); 
			puWgt_down = puInfo->getWeight_down(puTrue[1]); 
			// puWgtErr = puInfo->getWeightErr(puTrue[1]); 

			// ZToUpsilonGamma - Signal
			if (sampleSource.GetString() == "ZToUpsilon1SGamma" || sampleSource.GetString() == "ZToUpsilon3SGamma" || sampleSource.GetString() == "ZToUpsilon2SGamma") {
			// gen info
				for (int iPart = 0; iPart < *nMC; iPart++) {
					if (abs(mcPID[iPart]) == 13) {
						if (((mcMomPID[iPart]) == 553 || (mcMomPID[iPart]) == 100553 || (mcMomPID[iPart]) == 200553) && (mcGMomPID[iPart]) == 25) {
						// cout << "Muon!" << endl;
							if (mcPID[iPart] == 13) {
								// cout << "Muon +!" << endl;
								genMuPlus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuPlus.charge = 1;
								genMuPlus.partIndex = iPart;
								genMuPlus.pdgID = 13;
							} else if (mcPID[iPart] == -13) {
								// cout << "Muon -!" << endl;
								genMuMinus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuMinus.charge = -1;
								genMuMinus.partIndex = iPart;
								genMuMinus.pdgID = -13;
							} 
						}
					} else if ((mcPID[iPart]) == 22 && (mcMomPID[iPart]) == 25) {
						// cout << "Photon!" << endl;
						genPhoton.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 0);
						genPhoton.charge = 0;
						genPhoton.partIndex = iPart;
						genPhoton.pdgID = 22;
					}
				}
			}

			// ZToJPsiGamma - Signal
			if (sampleSource.GetString() == "ZToJPsiGamma") {
			// gen info
				for (int iPart = 0; iPart < *nMC; iPart++) {
					if (abs(mcPID[iPart]) == 13) {
						if (((mcMomPID[iPart]) == 443) && (mcGMomPID[iPart]) == 25) {
						// cout << "Muon!" << endl;
							if (mcPID[iPart] == 13) {
								// cout << "Muon +!" << endl;
								genMuPlus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuPlus.charge = 1;
								genMuPlus.partIndex = iPart;
								genMuPlus.pdgID = 13;
							} else if (mcPID[iPart] == -13) {
								// cout << "Muon -!" << endl;
								genMuMinus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuMinus.charge = -1;
								genMuMinus.partIndex = iPart;
								genMuMinus.pdgID = -13;
							} 
						}
					} else if ((mcPID[iPart]) == 22 && (mcMomPID[iPart]) == 25) {
						// cout << "Photon!" << endl;
						genPhoton.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 0);
						genPhoton.charge = 0;
						genPhoton.partIndex = iPart;
						genPhoton.pdgID = 22;
					}
				}
			}

			// for Z signal samples, exclude events with mass_Z < 50 GeV
			if (sampleSource.GetString() == "ZToUpsilon1SGamma" || sampleSource.GetString() == "ZToUpsilon3SGamma" || sampleSource.GetString() == "ZToUpsilon2SGamma" || sampleSource.GetString() == "ZToJPsiGamma") {
				// cout << "(genMuPlus+genMuMinus+genPhoton).M(): " << (genMuPlus+genMuMinus+genPhoton).M() << endl;
				if ((genMuPlus+genMuMinus+genPhoton).M() < 50.) continue;
				// if ((genMuPlus+genMuMinus+genPhoton).M() < 50.) cout << "Menor que 50 GeV!" << endl;
				// if ((genMuPlus+genMuMinus+genPhoton).M() > 50.) cout << "Maior que 50 GeV!" << endl;
			}			

			// ZToMuMuGamma - Background
			if (sampleSource.GetString() == "ZGTo2MuG_MMuMu-2To15") {
			// gen info
				for (int iPart = 0; iPart < *nMC; iPart++) {
					if (abs(mcPID[iPart]) == 13) {
						if ((mcMomPID[iPart]) == 23) {
						// cout << "Muon!" << endl;
							if (mcPID[iPart] == 13) {
								// cout << "Muon +!" << endl;
								genMuPlus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuPlus.charge = 1;
								genMuPlus.partIndex = iPart;
								genMuPlus.pdgID = 13;
							} else if (mcPID[iPart] == -13) {
								// cout << "Muon -!" << endl;
								genMuMinus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuMinus.charge = -1;
								genMuMinus.partIndex = iPart;
								genMuMinus.pdgID = -13;
							} else{
								// cout << "oi!" << endl;
							}
						}
					} else if ((mcPID[iPart]) == 22 && (mcMomPID[iPart] == 23) ) {
					// } else if ((mcPID[iPart]) == 22 ) {
						// cout << "Photon: " << mcMomPID[iPart] << endl;
						genPhoton.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 0);
						genPhoton.charge = 0;
						genPhoton.partIndex = iPart;
						genPhoton.pdgID = 22;
					}
				}
			// cout << "Gen Mu Plus: " << genMuPlus.Pt() << endl;
			// cout << "Gen Mu Minus: " << genMuMinus.Pt() << endl;
			// cout << "Gen Photon: " << genPhoton.Pt() << endl;
			// cout << "#############################################################" << endl;
			}


			// HToUpsilonGamma - Signal
			if (sampleSource.GetString() == "HToUpsilon1SGamma" || sampleSource.GetString() == "HToUpsilon2SGamma" || sampleSource.GetString() == "HToUpsilon3SGamma") {
			// gen info
				for (int iPart = 0; iPart < *nMC; iPart++) {
					if (abs(mcPID[iPart]) == 13) {
						if (((mcMomPID[iPart]) == 553 || (mcMomPID[iPart]) == 100553 || (mcMomPID[iPart]) == 200553) && (mcGMomPID[iPart]) == 25) {
						// cout << "Muon!" << endl;
							if (mcPID[iPart] == 13) {
								// cout << "Muon +!" << endl;
								genMuPlus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuPlus.charge = 1;
								genMuPlus.partIndex = iPart;
								genMuPlus.pdgID = 13;
							} else if (mcPID[iPart] == -13) {
								// cout << "Muon -!" << endl;
								genMuMinus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuMinus.charge = -1;
								genMuMinus.partIndex = iPart;
								genMuMinus.pdgID = -13;
							} 
						}
					} else if ((mcPID[iPart]) == 22 && (mcMomPID[iPart]) == 25) {
						// cout << "Photon!" << endl;
						genPhoton.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 0);
						genPhoton.charge = 0;
						genPhoton.partIndex = iPart;
						genPhoton.pdgID = 22;
					}
				}
			}

			// HToJPsiGamma - Signal
			if (sampleSource.GetString() == "HToJPsiGamma") {
			// gen info
				for (int iPart = 0; iPart < *nMC; iPart++) {
					if (abs(mcPID[iPart]) == 13) {
						if (((mcMomPID[iPart]) == 443) && (mcGMomPID[iPart]) == 25) {
						// cout << "Muon!" << endl;
							if (mcPID[iPart] == 13) {
								// cout << "Muon +!" << endl;
								genMuPlus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuPlus.charge = 1;
								genMuPlus.partIndex = iPart;
								genMuPlus.pdgID = 13;
							} else if (mcPID[iPart] == -13) {
								// cout << "Muon -!" << endl;
								genMuMinus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuMinus.charge = -1;
								genMuMinus.partIndex = iPart;
								genMuMinus.pdgID = -13;
							} 
						}
					} else if ((mcPID[iPart]) == 22 && (mcMomPID[iPart]) == 25) {
						// cout << "Photon!" << endl;
						genPhoton.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 0);
						genPhoton.charge = 0;
						genPhoton.partIndex = iPart;
						genPhoton.pdgID = 22;
					}
				}
			}

			// HDalitz - Background
			if (sampleSource.GetString() == "HDalitz") {
				// gen info
				// bool hasMuPlus = false;
				// bool hasMuMinus = false;
				// bool hasPhoton = false;
				for (int iPart = 0; iPart < *nMC; iPart++) {
					if (abs(mcPID[iPart]) == 13) {
						if ((mcMomPID[iPart]) == 25) {
						// cout << "Muon!" << endl;
							if (mcPID[iPart] == 13) {
								// cout << "Muon +!" << endl;
								// hasMuPlus = true;
								genMuPlus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuPlus.charge = 1;
								genMuPlus.partIndex = iPart;
								genMuPlus.pdgID = 13;
							} else if (mcPID[iPart] == -13) {
								// cout << "Muon -!" << endl;
								// hasMuMinus = true;
								genMuMinus.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 105.6583745/1000.0);
								genMuMinus.charge = -1;
								genMuMinus.partIndex = iPart;
								genMuMinus.pdgID = -13;
							} 
						}
					} else if ((mcPID[iPart]) == 22 && (mcMomPID[iPart]) == 25) {
						// cout << "Photon!" << endl;
						// hasPhoton = true;
						genPhoton.SetPtEtaPhiM(mcPt[iPart], mcEta[iPart], mcPhi[iPart], 0);
						genPhoton.charge = 0;
						genPhoton.partIndex = iPart;
						genPhoton.pdgID = 22;
					}
				}
				// cout << "hasMuPlus: " << hasMuPlus << endl;
				// cout << "hasMuMinus: " << hasMuMinus << endl;
				// cout << "hasPhoton: " << hasPhoton << endl;

			}

			// polarization weight
			auto cosAngle = upsilonPolarizationAngle(genMuPlus, genMuMinus);
			polWgt_Nominal = 1.0; // unpolarized
			polWgt_PLUS = (3./4.)*(1.+pow(cosAngle,2)); // transverse 
			polWgt_MINUS = (3./2.)*(1.-pow(cosAngle,2)); // longitudinal
			// cout << "polWgt: " << polWgt << endl;
			#endif
			// puWeight = puInfo->getWeight(999); 
			// if (iEvt % printEvery == 0) cout << puWgt << endl;
		}

		////////////////////////////////////////////////////////////////////
		// trigger test 
		// auto goodTriggerEvt = true;
		goodTriggerEvt = (((*HLTEleMuX >> 8) & 1) == 1) ? true : false; // HLT_Mu17_Photon30_CaloIdL_L1ISO_v*
		// goodTriggerEvt = ((((*HLTEleMuX >> 51) & 1) == 1) || (((*HLTEleMuX >> 52) & 1) == 1)) ? true : false; // HLT_Dimuon13_Upsilon_v* OR HLT_Dimuon8_Upsilon_Barrel_v*
		// if (goodTriggerEvt == false) continue;
		// cout << "Pass HLT!" << endl;

		////////////////////////////////////////////////////////////////////
		// muons analysis  
		vector< anaMuon > muonsCandCollection;
		// vector < vector< anaMuon > > muonsCandCollection = {{}, {}, {}, {}, {}, {}, {}, {}, {}};
		for (int iMuon = 0; iMuon < *nMu; iMuon++) { //loop over muons
			////////////////////////////////////////////////////////////////////
			// apply rochester corrections and get the corrected muons candidates collection
			// get RocCor SF
			// TRandom *rand3 = new TRandom3();
			// unique_ptr<TRandom3> rand3(new TRandom3);

			unique_ptr<std::map<int, double>> rocCorSF(new std::map<int, double>());
			(*rocCorSF)[translRocCor("default")] = 1.0;
			// (*rocCorSF)[translRocCor("statRocCorError_UP")] = 0.0;
			// (*rocCorSF)[translRocCor("statRocCorError_DOWN")] = 0.0;
			// (*rocCorSF)[translRocCor("refRocCorError_UP")] = 0.0;
			// (*rocCorSF)[translRocCor("refRocCorError_DOWN")] = 0.0;
			// (*rocCorSF)[translRocCor("profMassRocCorError_UP")] = 0.0;
			// (*rocCorSF)[translRocCor("profMassRocCorError_DOWN")] = 0.0;
			// (*rocCorSF)[translRocCor("fitMassRocCorError_UP")] = 0.0;
			// (*rocCorSF)[translRocCor("fitMassRocCorError_DOWN")] = 0.0;
			(*rocCorSF)[translRocCor("RocCorError_UP")] = 0.0;
			(*rocCorSF)[translRocCor("RocCorError_DOWN")] = 0.0;

			////////////////////////////////////////////////////////////////////////////////////////
			// Get the many scales/Smear for MC/DATA muons
			if (isMC) {
				// auto getRocCorRandom1 = rand3->Rndm();
				auto getRocCorRandom1 = rand1[iMuon];
				// auto getRocCorRandom2 = rand3->Rndm();
				auto getRocCorRandom2 = rand2[iMuon];

				// Default
				double rocCorDefault = rc.kScaleAndSmearMC(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], muTrkLayers[iMuon], getRocCorRandom1, getRocCorRandom2, 0, 0);

				// statistical uncert
				vector< double > statRocCor;
				for (int i = 0; i < 100; i++) {
					statRocCor.push_back(rc.kScaleAndSmearMC(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], muTrkLayers[iMuon], getRocCorRandom1, getRocCorRandom2, 1, i));
				}
				double statRocCorError = sqrt(getMeanVariance(statRocCor).second);

				// correction without reweighting reference to data
				double refRocCorError = fabs(rc.kScaleAndSmearMC(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], muTrkLayers[iMuon], getRocCorRandom1, getRocCorRandom2, 2, 0) - rocCorDefault);

				// profiled mass window
				vector< double > profRocCor;
				for (int i = 0; i < 5; i++) {
					profRocCor.push_back(fabs(rocCorDefault - rc.kScaleAndSmearMC(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], muTrkLayers[iMuon], getRocCorRandom1, getRocCorRandom2, 4, i)));
				}
				double profMassRocCorError = *max_element(std::begin(profRocCor), std::end(profRocCor));

				// fitting mass window
				vector< double > fitRocCor;
				for (int i = 0; i < 5; i++) {
					fitRocCor.push_back(fabs(rocCorDefault - rc.kScaleAndSmearMC(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], muTrkLayers[iMuon], getRocCorRandom1, getRocCorRandom2, 5, i)));
				}
				double fitMassRocCorError = *max_element(std::begin(fitRocCor), std::end(fitRocCor));

				// update rocCorSF map
				(*rocCorSF)[translRocCor("default")] = rocCorDefault;
				// (*rocCorSF)[translRocCor("statRocCorError_UP")] = statRocCorError;
				// (*rocCorSF)[translRocCor("statRocCorError_DOWN")] = (-1.0)*statRocCorError;
				// (*rocCorSF)[translRocCor("refRocCorError_UP")] = refRocCorError;
				// (*rocCorSF)[translRocCor("refRocCorError_DOWN")] = (-1.0)*refRocCorError;
				// (*rocCorSF)[translRocCor("profMassRocCorError_UP")] = profMassRocCorError;
				// (*rocCorSF)[translRocCor("profMassRocCorError_DOWN")] = (-1.0)*profMassRocCorError;
				// (*rocCorSF)[translRocCor("fitMassRocCorError_UP")] = fitMassRocCorError;
				// (*rocCorSF)[translRocCor("fitMassRocCorError_DOWN")] = (-1.0)*fitMassRocCorError;
				(*rocCorSF)[translRocCor("RocCorError_UP")] = (sqrt(pow(statRocCorError,2)+pow(refRocCorError,2)+pow(profMassRocCorError,2)+pow(fitMassRocCorError,2)));
				(*rocCorSF)[translRocCor("RocCorError_DOWN")] = (-1.0)*(sqrt(pow(statRocCorError,2)+pow(refRocCorError,2)+pow(profMassRocCorError,2)+pow(fitMassRocCorError,2)));
				// if (muPt[iMuon] > 30.) 
				// 	cout << "---> RocCor uncert: " << (sqrt(pow(statRocCorError,2)+pow(refRocCorError,2)+pow(profMassRocCorError,2)+pow(fitMassRocCorError,2)))/(rocCorDefault)*100. << endl;		

			} else {
				// update rocCorSF map
				(*rocCorSF)[translRocCor("default")] = rc.kScaleDT(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], 0, 0);
			}	

			
			// <END> Get the many scales/Smear for MC/DATA muons
			////////////////////////////////////////////////////////////////////////////////////////
			

			// if (isMC) rocCorSF = rc.kScaleAndSmearMC(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], muTrkLayers[iMuon], getRocCorRandom1, getRocCorRandom2, 0, 0);
			// else rocCorSF = rc.kScaleDT(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], 0, 0);

			// apply the corrections save muon candidate
			// anaMuon * muonCand = new anaMuon(muPt[iMuon]*rocCorSF, muEta[iMuon], muPhi[iMuon], muCharge[iMuon], iMuon);
			// unique_ptr<anaMuon> muonCand(new anaMuon(muPt[iMuon]*rocCorSF["default"], muEta[iMuon], muPhi[iMuon], muCharge[iMuon], iMuon));
			// unique_ptr<vector <anaMuon> > muonCand(new vector<anaMuon>());

			double rocCorError = 0.0;
			// if (shapeSystMask == "statRocCorError_UP" ||  shapeSystMask == "statRocCorError_DOWN" ||  shapeSystMask == "refRocCorError_UP" ||  shapeSystMask == "refRocCorError_DOWN" ||  shapeSystMask == "profMassRocCorError_UP" ||  shapeSystMask == "profMassRocCorError_DOWN" ||  shapeSystMask == "fitMassRocCorError_UP" ||  shapeSystMask == "fitMassRocCorError_DOWN") {
			if (shapeSystMask == "RocCorError_UP" ||  shapeSystMask == "RocCorError_UP") {
				rocCorError = (*rocCorSF)[translRocCor(shapeSystMask)];
			}

			muonsCandCollection.push_back(anaMuon(muPt[iMuon], muPt[iMuon]*((*rocCorSF)[translRocCor("default")]+rocCorError), muEta[iMuon], muPhi[iMuon], muCharge[iMuon], iMuon));
		}
		sort(muonsCandCollection.begin(), muonsCandCollection.end(),greater<anaMuon>()); // re-sort muon collection
		
		////////////////////////////////////////////////////////////////////
		// muons pre-selection
		// sort(muonsCandCollection.begin(), muonsCandCollection.end(),greater<anaMuon>()); // re-sort muon collection
		goodMuonPairPreSel = true; // muon pair pre-selection
		if (muonsCandCollection.size() >= 2) {
			// cout << "n: " << goodMuonPairPreSel << endl;
			goodMuonPairPreSel *= (muonsCandCollection[0].Pt() > 20.) ? true : false; // leading muon pT > 20.0 GeV
			// goodMuonPairPreSel *= (muonsCandCollection[0].Pt() > 10.) ? true : false; // leading muon pT > 20.0 GeV
			goodMuonPairPreSel *= (fabs(muonsCandCollection[0].Eta()) < 2.4) ? true : false; // leading muon abs(eta) < 2.4 
			// cout << "eta lead: " << goodMuonPairPreSel << endl;
			goodMuonPairPreSel *= (muonsCandCollection[1].Pt() > 4.) ? true : false; // trailing muon pT > 4.0 GeV
			// cout << "pt trail: " << goodMuonPairPreSel << endl;
			goodMuonPairPreSel *= (fabs(muonsCandCollection[1].Eta()) < 2.4) ? true : false; // trailing muon abs(eta) < 2.4
			// cout << "eta trail: " << goodMuonPairPreSel << endl; 
		} else {
			goodMuonPairPreSel = false;
		}



		//////////////////////////////////////////////////////////////////////
		// muons ID
		// https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsZZ4l2017#Muons
		for (unsigned int iCandMuon = 0; iCandMuon < muonsCandCollection.size(); iCandMuon++) { //loop over muons
			auto muIndex = muonsCandCollection[iCandMuon].muonIndex; //get event muon index

			// global muon: muType[] = 1 ; ((muType[] >> 1) &1) = 1 -> global muon
			// tracker muon: muType[] = 2 ; ((muType[] >> 2) &1) = 1 -> tracker muon
			// PF muon: muType[] = 5 ; ((muType[] >> 5) &1) = 1 -> PF muon


			// loose ID
			auto isMuonLooseID = false; //candidate muon loose id
			// if ((muType[muIndex] & GlobalMuon) || ( (muType[muIndex] & TrackerMuon) && (muMatches[muIndex] > 0) )) {
			if ( (((muType[muIndex] >> 1) & 1) == 1) || ( (((muType[muIndex] >> 2) & 1) == 1) && (muMatches[muIndex] > 0) )) {
				if (muBestTrkType[muIndex] != 2) {
					if ((fabs(muD0[muIndex]) < 0.5) && (fabs(muDz[muIndex]) < 1.0)) {
						if (muSIP[muIndex] < 4) {
							if ((muonsCandCollection[iCandMuon].Pt() > 4.0) && (fabs(muonsCandCollection[iCandMuon].Eta()) < 2.4)) {
								isMuonLooseID = true;
							}
						}
					}
				}
			}
			// isMuonLooseID *= (muonsCandCollection[iCandMuon].Pt() > 4.0) ? true : false; // pT > 4.0 GeV
		 // 	isMuonLooseID *= (fabs(muonsCandCollection[iCandMuon].Eta()) < 2.4) ? true : false;  //abs(eta) < 2.4
		 	// isMuonLooseID *= (fabs(muD0[muIndex]) < 0.5) ? true : false;  //dxy < 2.4
		 	// isMuonLooseID *= (fabs(muDz[muIndex]) < 1.0) ? true : false;  //dz < 1.0
		 	// isMuonLooseID *= (muBestTrkType[muIndex] != 2) ? true : false;  //muBestTrkType != 2
		 	// isMuonLooseID *= (muMatches[muIndex] > 0 ) ? true : false;
		 	// isMuonLooseID *= ( (muType[muIndex] & GlobalMuon) || (muType[muIndex] & TrackerMuon) ) ? true : false;
		 	// isMuonLooseID *= (muSIP[muIndex]) < 4 ? true : false;  //muon |SIP| < 4
		 	muonsCandCollection[iCandMuon].muonIsLooseID = isMuonLooseID; // set loose ID flag

		 	//tightID
		 	auto isMuonTightID = false;
		 	if (muonsCandCollection[iCandMuon].muonIsLooseID) {
		 		if (muPt[iCandMuon] < 200.0) {
		 			// if (muType[muIndex] & PFMuon) {
		 			if (((muType[muIndex] >> 5) & 1) == 1) {
		 				isMuonTightID = true;
		 			}
		 		} else {
		 			auto isTrackerHighPtID = false;
		 			// if (muType[muIndex] & TrackerMuon) {
		 			if (((muType[muIndex] >> 2) & 1) == 1) {
		 				if (muMatches[muIndex] >= 2) {
		 					if (muBestTrkPtError[muIndex]/muBestTrkPt[muIndex]  < 0.3) {
		 						if ((fabs(muD0[muIndex]) < 0.2) && (fabs(muDz[muIndex]) < 0.5)) {
		 							if ((muPixelHits[muIndex] >= 1) && (muTrkLayers[muIndex] >= 6)) {
		 								isTrackerHighPtID = true;
		 							}
		 						}
		 					}
		 				}
		 			}
		 			// if ( (muType[muIndex] & PFMuon) || isTrackerHighPtID) {
		 			if ( (((muType[muIndex] >> 5) & 1) == 1) || isTrackerHighPtID) {
		 				isMuonTightID = true;
		 			}
		 		}
		 	}


			// auto isMuonTightID = isMuonLooseID; //candidate muon tight id
			// if (muonsCandCollection[iCandMuon].Pt() < 200.0) { //pT below 200 GeV
			// 	isMuonTightID *= ( (muType[muIndex] & PFMuon) ) ? true : false; //is PF muon
			// } else {
			// 	auto isTrackerHighPtID = true; //candidate muon tight id
			// 	isTrackerHighPtID *= (muMatches[muIndex] >= 2) ? true : false;  // number of matches in the muon stations > 2
			// 	isTrackerHighPtID *= (muBestTrkPtError[muIndex]/muBestTrkPt[muIndex]  < 0.3) ? true : false;  // good pT measurement	
			// 	isTrackerHighPtID *= (fabs(muD0[muIndex]) < 0.2) ? true : false;  //dxy < 0.2
	 	// 		isTrackerHighPtID *= (fabs(muDz[muIndex]) < 0.5) ? true : false;  //dz < 0.5	
	 	// 		isTrackerHighPtID *= (muPixelHits[muIndex] >= 1) ? true : false;  // at least one pixel hit	
	 	// 		isTrackerHighPtID *= (muTrkLayers[muIndex] >= 6) ? true : false;  // at least 6 tracker layer hits

			// 	isMuonTightID *= ( (muType[muIndex] & PFMuon) || isTrackerHighPtID ) ? true : false; //is PF muon OR tracker high pT ID
			// }
			muonsCandCollection[iCandMuon].muonIsTightID = isMuonTightID; // set tight ID flag
			// muonsCandCollection[iCandMuon].muonIsTightID = true; // set tight ID flag

			// // Relative PF Iso
			// auto isMuonISO = true;
			// auto relPFIsoLeadingMuon =(muPFChIso03[muIndex] + max((muPFNeuIso03[muIndex]+muPFPhoIso03[muIndex]-0.5*muPFPUIso03[muIndex]),0.0))/(muPt[iCandMuon]);
			// isMuonISO *= (relPFIsoLeadingMuon < 0.35) ? true : false;  //Relative PF Iso < 0.35
			// muonsCandCollection[iCandMuon].muonIsISO = isMuonISO; 

			// clean muon collection 
			// if (!(muonsCandCollection[iCandMuon].muonIsLooseID) || !(muonsCandCollection[iCandMuon].muonIsTightID) || !(fabs(muonsCandCollection[iCandMuon].Eta()) < 2.4) || !(muonsCandCollection[iCandMuon].Pt() > 4.0)) {
			if ( !(muonsCandCollection[iCandMuon].muonIsTightID) ) {
				muonsCandCollection.erase(muonsCandCollection.begin() + iCandMuon);
			}
		}

		////////////////////////////////////////////////////////////////////
		// muons selection
		// sort(muonsCandCollection.begin(), muonsCandCollection.end(),greater<anaMuon>()); // re-sort muon collection
		int indexLeadCand = -99;
		int indexTrailCand = -99;
		goodMuonPairSel = true; // muon pair pre-selection
		vector< pair < int, int > > dimuonCandCollection = {};
		goodMuonPairId = false;
		if (muonsCandCollection.size() >= 2) {
			goodMuonPairId = true;
			// make dimuon pair
			for (unsigned int iLeadMuon = 0; iLeadMuon < (muonsCandCollection.size() - 1); iLeadMuon++) {
				for (unsigned int iTrailMuon = iLeadMuon+1; iTrailMuon < muonsCandCollection.size(); iTrailMuon++) {
					if ((muonsCandCollection[iLeadMuon].Pt() >= 20.) && (muonsCandCollection[iTrailMuon].Pt() >= 4.)) { //pT cut
						if ((fabs(muonsCandCollection[iLeadMuon].Eta()) < 2.4) && (fabs(muonsCandCollection[iTrailMuon].Eta()) < 2.4)) { // eta cut
							if ((muonsCandCollection[iLeadMuon].charge * muonsCandCollection[iTrailMuon].charge) < 0.0) { // opposite charges
								dimuonCandCollection.push_back({iLeadMuon, iTrailMuon});
							}
						}
					}
				}
			}
			// look for dimuon pairs
			// if (dimuonCandCollection.size() > 1) cout << "----> dimuonCandCollection.size(): " << dimuonCandCollection.size() << endl;
			if (dimuonCandCollection.size() > 0) {
				for (unsigned int iDimuon = 0; iDimuon < dimuonCandCollection.size(); iDimuon++) {
					auto isLeadIso = false;
					auto isTrailIso = false;
					auto relPFIsoMuon = 99999.9;
					if (deltaR(muonsCandCollection[dimuonCandCollection[iDimuon].first].Eta(), muonsCandCollection[dimuonCandCollection[iDimuon].first].Phi(), muonsCandCollection[dimuonCandCollection[iDimuon].second].Eta(), muonsCandCollection[dimuonCandCollection[iDimuon].second].Phi()) > 0.3) {
						// lead muon
						relPFIsoMuon = (muPFChIso03[dimuonCandCollection[iDimuon].first] + max((muPFNeuIso03[dimuonCandCollection[iDimuon].first]+muPFPhoIso03[dimuonCandCollection[iDimuon].first]-0.5*muPFPUIso03[dimuonCandCollection[iDimuon].first]),0.0))/(muPt[dimuonCandCollection[iDimuon].first]);
						isLeadIso = (relPFIsoMuon < 0.35) ? true : false;  //Relative PF Iso < 0.35
						muonsCandCollection[dimuonCandCollection[iDimuon].first].muonIsISO = isLeadIso; 
						// cout << "isLeadIso: " << isLeadIso << endl;

						// trail muon
						relPFIsoMuon = (muPFChIso03[dimuonCandCollection[iDimuon].second] + max((muPFNeuIso03[dimuonCandCollection[iDimuon].second]+muPFPhoIso03[dimuonCandCollection[iDimuon].second]-0.5*muPFPUIso03[dimuonCandCollection[iDimuon].second]),0.0))/(muPt[dimuonCandCollection[iDimuon].second]);
						isTrailIso = (relPFIsoMuon < 0.35) ? true : false;  //Relative PF Iso < 0.35
						// muonsCandCollection[dimuonCandCollection[iDimuon].second].muonIsISO = isTrailIso; 
						muonsCandCollection[dimuonCandCollection[iDimuon].second].muonIsISO = true; 
						// cout << "isTrailIso: " << isTrailIso << endl;
					} else {
						// lead muon
						// relPFIsoMuon = (muPFChIso03[dimuonCandCollection[iDimuon].first] + max((muPFNeuIso03[dimuonCandCollection[iDimuon].first]+muPFPhoIso03[dimuonCandCollection[iDimuon].first]-0.5*muPFPUIso03[dimuonCandCollection[iDimuon].first]),0.0) - muPt[dimuonCandCollection[iDimuon].second])/(muPt[dimuonCandCollection[iDimuon].first]);
						relPFIsoMuon = (muPFChIso03[dimuonCandCollection[iDimuon].first] + max((muPFNeuIso03[dimuonCandCollection[iDimuon].first]+muPFPhoIso03[dimuonCandCollection[iDimuon].first]-0.5*muPFPUIso03[dimuonCandCollection[iDimuon].first]),0.0))/(muPt[dimuonCandCollection[iDimuon].first]);
						isLeadIso *= (relPFIsoMuon < 0.35) ? true : false;  //Relative PF Iso < 0.35
						muonsCandCollection[dimuonCandCollection[iDimuon].first].muonIsISO = isLeadIso; 

						// trail muon
						muonsCandCollection[dimuonCandCollection[iDimuon].second].muonIsISO = true; 
					}
				}
				int goodPairIndex = -99;
				double maxPt = 0.0;
				for (unsigned int iDimuon = 0; iDimuon < dimuonCandCollection.size(); iDimuon++) {
					// cout << "Foi!" << endl;
					if ((muonsCandCollection[dimuonCandCollection[iDimuon].first].muonIsISO == true) && (muonsCandCollection[dimuonCandCollection[iDimuon].second].muonIsISO == true)) {
						// cout << "Vai!" << endl;
						if ((muonsCandCollection[dimuonCandCollection[iDimuon].first]+muonsCandCollection[dimuonCandCollection[iDimuon].second]).Pt() > maxPt) {
							goodPairIndex = iDimuon;
							maxPt = (muonsCandCollection[dimuonCandCollection[iDimuon].first]+muonsCandCollection[dimuonCandCollection[iDimuon].second]).Pt();
							// if (dimuonCandCollection.size() > 1) cout << "---> maxPt: " << maxPt << endl;
						}
					}
				}
				if (goodPairIndex != -99) {
					indexLeadCand = dimuonCandCollection[goodPairIndex].first;
					indexTrailCand = dimuonCandCollection[goodPairIndex].second;
				}
			}

		} else {
			goodMuonPairSel = false;
		}

		if (indexLeadCand != -99 && indexTrailCand != -99) {
			goodMuonPairSel = true;
			leadingMuon = muonsCandCollection[indexLeadCand];
			trailingMuon = muonsCandCollection[indexTrailCand];
		} else {
			goodMuonPairSel = false;
		}

		// if (muonsCandCollection.size() >= 2) {
		// 	for (unsigned int iLeadMuon = 0; iLeadMuon < muonsCandCollection.size(); iLeadMuon++) {
		// 		if (muonsCandCollection[iLeadMuon].muonIsISO && muonsCandCollection[iLeadMuon].Pt() >= 20.0) {
		// 		// if (muonsCandCollection[iLeadMuon].muonIsISO && muonsCandCollection[iLeadMuon].Pt() > 10.0) {
		// 			indexLeadCand = iLeadMuon;
		// 			break;
		// 		}
		// 		// goodMuonPairSel *= (muonsCandCollection[iLeadMuon].muonIsISO) ? true : false; // leading muon is ISO
		// 		// goodMuonPairSel *= (muonsCandCollection[iLeadMuon].Pt() > 20.) ? true : false; // leading muon pT > 20.0 GeV
		// 		// goodMuonPairSel *= (fabs(muonsCandCollection[0].Eta()) < 2.4) ? true : false; // leading muon abs(eta) < 2.4 
		// 		// for (unsigned int iTrailMuon == 1; muonsCandCollection.size(); iTrailMuon++) {
		// 		// 	if ((muonsCandCollection[iTrailMuon].charge * muonsCandCollection[0].charge) < 1.0){
		// 		// 	}
		// 		// }
		// 	}
		// 	if (indexLeadCand != -99) {
		// 		for (unsigned int iTrailMuon = indexLeadCand+1; iTrailMuon < muonsCandCollection.size(); iTrailMuon++) {
		// 			if ((muonsCandCollection[iTrailMuon].charge * muonsCandCollection[indexLeadCand].charge) < 0){ //oposite charge
		// 				indexTrailCand = iTrailMuon;
		// 				break;
		// 			}
		// 		}
		// 	}
		// 	// goodMuonPairSel *= (muonsCandCollection[1].Pt() > 4.) ? true : false; // trailing muon pT > 4.0 GeV
		// 	// goodMuonPairSel *= (fabs(muonsCandCollection[1].Eta()) < 2.4) ? true : false; // trailing muon abs(eta) < 2.4 
		// } else {
		// 	goodMuonPairSel = false;
		// }

		// if (indexLeadCand != -99 && indexTrailCand != -99) {
		// 	goodMuonPairSel = true;
		// 	leadingMuon = muonsCandCollection[indexLeadCand];
		// 	trailingMuon = muonsCandCollection[indexTrailCand];
		// } else {
		// 	goodMuonPairSel = false;
		// }


		////////////////////////////////////////////////////////////////////
		// photon selection  
		vector< anaPhoton > photonsCandCollection;
		double photonCalibEnergy = 0.0;
		TRandom3 * rgen_ = new TRandom3(0);
		for (int iPhoton = 0; iPhoton < *nPho; iPhoton++) { //loop over muons
			// apply the calibrations save photon candidate
			// https://twiki.cern.ch/twiki/bin/viewauth/CMS/EGMSmearer
			// https://twiki.cern.ch/twiki/bin/viewauth/CMS/Egamma2017DataRecommendations#Energy_Scale_and_Smearing_System
			// https://github.com/cmkuo/ggAnalysis/blob/master/ggNtuplizer/plugins/ggNtuplizer_photons.cc
			if (shapeSystMask == "phoScale_stat_UP") photonCalibEnergy =  phoEt[iPhoton] * phoScale_stat_up[iPhoton];
			else if (shapeSystMask == "phoScale_stat_DOWN") photonCalibEnergy =  phoEt[iPhoton] * phoScale_stat_dn[iPhoton];
			
			else if (shapeSystMask == "phoScale_syst_UP") photonCalibEnergy =  phoEt[iPhoton] * phoScale_syst_up[iPhoton];
			else if (shapeSystMask == "phoScale_syst_DOWN") photonCalibEnergy =  phoEt[iPhoton] * phoScale_syst_dn[iPhoton];
			
			else if (shapeSystMask == "phoScale_gain_UP") photonCalibEnergy =  phoEt[iPhoton] * phoScale_gain_up[iPhoton];
			else if (shapeSystMask == "phoScale_gain_DOWN") photonCalibEnergy =  phoEt[iPhoton] * phoScale_gain_dn[iPhoton];
			
			else if (shapeSystMask == "phoResol_rho_UP") photonCalibEnergy =  phoEt[iPhoton]*(rgen_->Gaus(1, phoResol_rho_up[iPhoton]));
			else if (shapeSystMask == "phoResol_rho_DOWN") photonCalibEnergy =  phoEt[iPhoton]*(rgen_->Gaus(1, phoResol_rho_dn[iPhoton]));
			
			else if (shapeSystMask == "phoResol_phi_UP") photonCalibEnergy =  phoEt[iPhoton]*(rgen_->Gaus(1, phoResol_phi_up[iPhoton]));
			else if (shapeSystMask == "phoResol_phi_DOWN") photonCalibEnergy =  phoEt[iPhoton]*(rgen_->Gaus(1, phoResol_phi_dn[iPhoton]));
			
			// else photonCalibEnergy =  phoCalibEt[iPhoton];
			else photonCalibEnergy =  phoEt[iPhoton];

			// cout << "#################################" << endl;
			// cout << "shapeSystMask: " << shapeSystMask << endl;
			// cout << "photonCalibEnergy: " << photonCalibEnergy << endl;


			unique_ptr<anaPhoton> photonCand(new anaPhoton(phoEt[iPhoton], photonCalibEnergy, phoEta[iPhoton], phoPhi[iPhoton], iPhoton));
			photonsCandCollection.push_back(*photonCand);
		}
		sort(photonsCandCollection.begin(), photonsCandCollection.end(),greater<anaPhoton>()); // re-sort photon collection


		for (int iCandPhoton = 0; iCandPhoton < *nPho; iCandPhoton++) { //loop over muons
			auto phoIndex = photonsCandCollection[iCandPhoton].photonIndex; //get global photon index
			auto goodPhoton = true;
			goodPhoton *= (fabs(phoSCEta[phoIndex]) < 2.5) ? true : false; 
			goodPhoton *= (!(fabs(phoSCEta[phoIndex]) > 1.4442 && fabs(phoSCEta[phoIndex]) < 1.566)) ? true : false;
			goodPhoton *= (phoEleVeto[phoIndex] != 0) ? true : false; 
			goodPhoton *= (phoIDMVA[phoIndex] > 0.2) ? true : false;
			// photonsCandCollection[iCandPhoton].photonR9 = phoR9[phoIndex];
			photonsCandCollection[iCandPhoton].photonR9 = getR9Transform(isMC, phoR9[phoIndex], phoSCEta[phoIndex]);
			photonsCandCollection[iCandPhoton].photonSCEta = phoSCEta[phoIndex];
			
			// clean photon collection 
			if (!goodPhoton) {
				photonsCandCollection.erase(photonsCandCollection.begin() + iCandPhoton);
			}
		}

		// photon selection
		sort(photonsCandCollection.begin(), photonsCandCollection.end(),greater<anaPhoton>()); // re-sort photon collection
		goodPhotonSel = true; 
		if (photonsCandCollection.size() >= 1) {
			goodPhotonSel *= (photonsCandCollection[0].Pt() > 33.) ? true : false; // photon Et > 33.0 GeV
			// goodPhotonSel *= (photonsCandCollection[0].Pt() > 20.) ? true : false; // photon Et > 33.0 GeV
		} else {
			goodPhotonSel = false;
		}
		if (goodPhotonSel == true) {
			leadingPhoton = photonsCandCollection[0];
		}

		//////////////////////////////////////////////////////////////////////
		// reconstructed UpsilonSetPtEtaPhiM
		// if (goodMuonPairSel && goodPhotonSel) recoUpsilon.SetPtEtaPhiM((leadingMuon + trailingMuon).Pt(), (leadingMuon + trailingMuon).Eta(), (leadingMuon + trailingMuon).Phi(), (leadingMuon + trailingMuon).M());
		// auto goodUpsilon = ( (recoUpsilon.M() > 7.0) && (recoUpsilon.M() < 12.0) ) ? true : false;

		//////////////////////////////////////////////////////////////////////
		// reconstructed Z
		// if (goodMuonPairSel && goodPhotonSel) recoZ.SetPtEtaPhiM((recoUpsilon + leadingPhoton).Pt(), (recoUpsilon + leadingPhoton).Eta(), (recoUpsilon + leadingPhoton).Phi(), (recoUpsilon + leadingPhoton).M());
		// auto goodZ = ( (recoZ.M() > 7) && (recoZ.M() < 12.0) ) ? true : false;


		// if (goodTriggerEvt && goodMuonPairSel && goodPhotonSel) {
		// 	TLorentzVector recoZ = leadingPhoton + leadingMuon + trailingMuon;
		// 	cout << "##########################" << endl;
		// 	cout << "leadingPhoton: " << leadingPhoton.Pt() << endl;
		// 	// cout << "muonsCandCollection[indexTrailCand]: " << muonsCandCollection[0].Pt() << endl;
		// 	cout << "leadingMuon: " << leadingMuon.Pt() << endl;
		// 	cout << "trailingMuon: " << trailingMuon.Pt() << endl;
		// 	cout << "recoZ - pT: " << recoZ.Pt() << endl;
		// 	cout << "recoZ - Mass: " << recoZ.M() << endl;
		// }

		





		// filling the outTree
		isGoodEvent = true;
		isGoodEvent *= goodTriggerEvt;
		isGoodEvent *= goodMuonPairSel;
		isGoodEvent *= goodPhotonSel;
		if (isGoodEvent) {
			// get the SFs
			muonIDSF = getMuonIDSF(isMC, leadingMuon, sfMuonIDFile); // muon ID
			// cout << "muonIDSF: " << muonIDSF.first << endl;
			photonMVAIDSF = getPhotonMVAIDSF(isMC, leadingPhoton, sfMVAIDFile); // photon MVA ID
			// cout << "photonMVAIDSF: " << photonMVAIDSF.first << endl;
			photonEleVetoSF = getPhotonEleVetoSF(isMC, leadingPhoton); // photon electron veto
			// cout << "photonEleVetoSF: " << photonEleVetoSF.first << endl;
			triggerSF = getTriggerSF(isMC, leadingMuon, leadingPhoton, sfTriggerFile); // photon electron veto
			// triggerSF = {1.,0.}; // photon electron veto
			// cout << "triggerSF: " << triggerSF.first << endl;
		}
		// fill the tree
		outTree->Fill();


		// delete pt; 

    } // end loop over events

    // post-processing 
    cout << "\n\n\nWriting output file... (" << outFileAppend <<  ")"  << endl;
    // outTree->Print();
    outFile->Write();
    outFile->Close();
    cout << "\nDone  (" << outFileAppend <<  ")" << "!\n\n\n\n\n" << endl;

} //end ana_ZtoUpsilonPhoton


