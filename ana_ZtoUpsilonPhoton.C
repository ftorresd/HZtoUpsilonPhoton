// ######################################################
// Z --> Upsilon + Photon
// ######################################################
// Analysis Code
// Description:  - Read the ggNtuples
//               - Skim the sample
//               - Apply corrections and cuts           
//               - Produces a ntuple ready for plotting  
// ######################################################


// #define IS_MC 1



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
// #include "TH1.h"


#include "plugins/ggNtuplesFilesReader.h"
#include "plugins/roccor2016/RoccoR.cc"
#include "plugins/deltaR_deltaPhi.h"
#include "plugins/anaObjects.h"
#include "plugins/puWeight.h"
#include "plugins/upsilonPolarizationAngle.h"
#include "plugins/getSF.h"
#include "plugins/getR9Transform.h"


#ifdef __CINT__
#pragma link C++ class anaMuon+;
#pragma link C++ class anaPhoton+;
#pragma link C++ class anaGenPart+;
#endif

using namespace std;


void ana_ZtoUpsilonPhoton(vector<string> ggNtuplesFiles, int nFiles = -1, string outFileAppend = "", bool isMC = false, string puFile = "")  
{
	// output tree
	// TFile outFile("outTree_ZtoUpsilonPhoton.root","RECREATE","ZtoUpsilonPhoton output analysis tree");
	string outputFileName = "outputFiles/outTree_ZtoUpsilonPhoton_"+ outFileAppend + ".root";
	TFile * outFile  = new TFile(outputFileName.c_str(),"RECREATE","ZtoUpsilonPhoton output analysis tree");
	TTree * outTree = new TTree("outTree_ZtoUpsilonPhoton","ZtoUpsilonPhoton output analysis tree");

	// loads the ggNtuples 
	if (nFiles > 0) {
		ggNtuplesFiles.resize(nFiles);	
	}
	TTreeReader * dataReader = ggNtuplesFilesReader( ggNtuplesFiles, "ggNtuplizer/EventTree" );
	TTree * dataTree = dataReader->GetTree();

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
	TLorentzVector recoUpsilon = TLorentzVector();
	outTree->Branch("recoUpsilon",&recoUpsilon);

	//output objects - PHOTONS
	TLorentzVector recoZ = TLorentzVector();
	outTree->Branch("recoZ",&recoZ);

	//output objects - isGoodEvent
	bool isGoodEvent = true;
	outTree->Branch("isGoodEvent",&isGoodEvent);

	//output objects - goodTriggerEvt
	bool goodTriggerEvt = true;
	outTree->Branch("goodTriggerEvt",&goodTriggerEvt);

	//output objects - goodMuonPairSel
	bool goodMuonPairSel = true;
	outTree->Branch("goodMuonPairSel",&goodMuonPairSel);

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
	double polWgt = 1.0;
	outTree->Branch("polWgt",&polWgt);	

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
	if (!isMC) printEvery = 1000000;
	cout << "\nN. Entries (" << outFileAppend <<  "): " << totalEvts << endl;
	cout << "\nPrinting every: " << printEvery << " events" << endl;
	cout << "\nLooping over events... \n" << endl;

	// dataTree->Print();


	////////////////////////////////////////////////////////////////////
	// main loop
	auto iEvt = 0;
	while (dataReader->Next()) { // loop over events
		if (iEvt % printEvery == 0) cout << "----------------------------------------> Events read (" << outFileAppend <<  "): " << iEvt << " / " << totalEvts << " - ~"<< round(((float)iEvt/(float)totalEvts)*100) << "%"<< endl;
		iEvt++;

		////////////////////////////////////////////////////////////////////
		// clear output tree variables 
		leadingMuon.clear();
		trailingMuon.clear();
		leadingPhoton.clear();
		recoUpsilon.SetPtEtaPhiM(-99,-99,-99,-99);
		recoZ.SetPtEtaPhiM(-99,-99,-99,-99); 
		genMuPlus.clear();
		genMuMinus.clear();
		genPhoton.clear();
		puWgt_nominal = 1.0;
		puWgt_up = 1.0;
		puWgt_down = 1.0;
		polWgt = 1.0;
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
					} else if ((mcPID[iPart]) == 22 && (mcMomPID[iPart]) == 23) {
						// cout << "Photon!" << endl;
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
			polWgt = (3./4.)*(1.+pow(cosAngle,2));
			// cout << "polWgt: " << polWgt << endl;
			#endif
			// puWeight = puInfo->getWeight(999); 
			// if (iEvt % printEvery == 0) cout << puWgt << endl;
		}

		////////////////////////////////////////////////////////////////////
		// trigger test 
		// auto goodTriggerEvt = true;
		goodTriggerEvt = (((*HLTEleMuX >> 8) & 1) == 1) ? true : false; // HLT_Mu17_Photon30_CaloIdL_L1ISO_v*
		// if (goodTriggerEvt == false) continue;
		// cout << "Pass HLT!" << endl;

		////////////////////////////////////////////////////////////////////
		// muons analysis  
		vector< anaMuon > muonsCandCollection;
		for (int iMuon = 0; iMuon < *nMu; iMuon++) { //loop over muons
			////////////////////////////////////////////////////////////////////
			// apply rochester corrections and get the corrected muons candidates collection
			// get RocCor SF
			// TRandom *rand3 = new TRandom3();
			shared_ptr<TRandom3> rand3(new TRandom3);
			auto getRocCorRandom1 = rand3->Rndm();
			auto getRocCorRandom2 = rand3->Rndm();
			double rocCorSF = 1.0;
			if (isMC) rocCorSF = rc.kScaleAndSmearMC(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], muTrkLayers[iMuon], getRocCorRandom1, getRocCorRandom2, 0, 0);
			else rocCorSF = rc.kScaleDT(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], 0, 0);

			// apply the corrections save muon candidate
			// anaMuon * muonCand = new anaMuon(muPt[iMuon]*rocCorSF, muEta[iMuon], muPhi[iMuon], muCharge[iMuon], iMuon);
			shared_ptr<anaMuon> muonCand(new anaMuon(muPt[iMuon]*rocCorSF, muEta[iMuon], muPhi[iMuon], muCharge[iMuon], iMuon));


			// cout << muonCand->Pt();
			muonsCandCollection.push_back(*muonCand);
		}
		sort(muonsCandCollection.begin(), muonsCandCollection.end(),greater<anaMuon>()); // re-sort muon collection
		
		////////////////////////////////////////////////////////////////////
		// muons pre-selection
		// sort(muonsCandCollection.begin(), muonsCandCollection.end(),greater<anaMuon>()); // re-sort muon collection
		goodMuonPairPreSel = true; // muon pair pre-selection
		if (muonsCandCollection.size() >= 2) {
			goodMuonPairPreSel *= (muonsCandCollection[0].Pt() > 20.) ? true : false; // leading muon pT > 20.0 GeV
			goodMuonPairSel *= (fabs(muonsCandCollection[0].Eta()) < 2.4) ? true : false; // leading muon abs(eta) < 2.4 
			goodMuonPairPreSel *= (muonsCandCollection[1].Pt() > 4.) ? true : false; // trailing muon pT > 4.0 GeV
			goodMuonPairSel *= (fabs(muonsCandCollection[1].Eta()) < 2.4) ? true : false; // trailing muon abs(eta) < 2.4 
		} else {
			goodMuonPairPreSel = false;
		}

		//////////////////////////////////////////////////////////////////////
		// muons ID
		for (unsigned int iCandMuon = 0; iCandMuon < muonsCandCollection.size(); iCandMuon++) { //loop over muons
			auto muIndex = muonsCandCollection[iCandMuon].muonIndex; //get global muon index

			// loose ID
			auto isMuonLooseID = true; //candidate muon loose id
			isMuonLooseID *= (muonsCandCollection[iCandMuon].Pt() > 4.0) ? true : false; // pT > 4.0 GeV
		 	isMuonLooseID *= (fabs(muonsCandCollection[iCandMuon].Eta()) < 2.4) ? true : false;  //abs(eta) < 2.4
		 	isMuonLooseID *= (fabs(muD0[muIndex]) < 0.5) ? true : false;  //dxy < 2.4
		 	isMuonLooseID *= (fabs(muDz[muIndex]) < 1.0) ? true : false;  //dz < 1.0
		 	isMuonLooseID *= (muBestTrkType[muIndex] != 2) ? true : false;  //muBestTrkType != 2
		 	isMuonLooseID *= (muMatches[muIndex] > 0 ) ? true : false;
		 	isMuonLooseID *= ( (muType[muIndex] & GlobalMuon) || (muType[muIndex] & TrackerMuon) ) ? true : false;
		 	isMuonLooseID *= (muSIP[muIndex]) < 4 ? true : false;  //muon |SIP| < 4
		 	muonsCandCollection[iCandMuon].muonIsLooseID = isMuonLooseID; // set loose ID flag

		 	//tightID
			auto isMuonTightID = isMuonLooseID; //candidate muon tight id
			if (muonsCandCollection[iCandMuon].Pt() < 200.0) { //pT below 200 GeV
				isMuonTightID *= ( (muType[muIndex] & PFMuon) ) ? true : false; //is PF muon
			} else {
				auto isTrackerHighPtID = true; //candidate muon tight id
				isTrackerHighPtID *= (muMatches[muIndex] >= 2) ? true : false;  // number of matches in the muon stations > 2
				isTrackerHighPtID *= (muBestTrkPtError[muIndex]/muBestTrkPt[muIndex]  < 0.3) ? true : false;  // good pT measurement	
				isTrackerHighPtID *= (fabs(muD0[muIndex]) < 0.2) ? true : false;  //dxy < 0.2
	 			isTrackerHighPtID *= (fabs(muDz[muIndex]) < 0.5) ? true : false;  //dz < 0.5	
	 			isTrackerHighPtID *= (muPixelHits[muIndex] >= 1) ? true : false;  // at least one pixel hit	
	 			isTrackerHighPtID *= (muTrkLayers[muIndex] >= 6) ? true : false;  // at least 6 tracker layer hits

				isMuonTightID *= ( (muType[muIndex] & PFMuon) || isTrackerHighPtID ) ? true : false; //is PF muon OR tracker high pT ID
			}
			muonsCandCollection[iCandMuon].muonIsTightID = isMuonTightID; // set tight ID flag

			// Relative PF Iso
			auto isMuonISO = true;
			auto relPFIsoLeadingMuon =(muPFChIso03[muIndex] + max((muPFNeuIso03[muIndex]+muPFPhoIso03[muIndex]-0.5*muPFPUIso03[muIndex]),0.0))/(muonsCandCollection[iCandMuon].Pt());
			isMuonISO *= (relPFIsoLeadingMuon < 0.35) ? true : false;  //Relative PF Iso < 0.35
			muonsCandCollection[iCandMuon].muonIsISO = isMuonISO; 

			// clean muon collection 
			if (!(muonsCandCollection[iCandMuon].muonIsTightID) || !(fabs(muonsCandCollection[iCandMuon].Eta()) < 2.4) || !(muonsCandCollection[iCandMuon].Pt() > 4.0)) {
				muonsCandCollection.erase(muonsCandCollection.begin() + iCandMuon);
			}
		}

		////////////////////////////////////////////////////////////////////
		// muons selection
		// sort(muonsCandCollection.begin(), muonsCandCollection.end(),greater<anaMuon>()); // re-sort muon collection
		int indexLeadCand = -99;
		int indexTrailCand = -99;
		goodMuonPairSel = true; // muon pair pre-selection
		if (muonsCandCollection.size() >= 2) {
			for (unsigned int iLeadMuon = 0; iLeadMuon < muonsCandCollection.size(); iLeadMuon++) {
				if (muonsCandCollection[iLeadMuon].muonIsISO && muonsCandCollection[iLeadMuon].Pt() > 20.0) {
					indexLeadCand = iLeadMuon;
					break;
				}
				// goodMuonPairSel *= (muonsCandCollection[iLeadMuon].muonIsISO) ? true : false; // leading muon is ISO
				// goodMuonPairSel *= (muonsCandCollection[iLeadMuon].Pt() > 20.) ? true : false; // leading muon pT > 20.0 GeV
				// goodMuonPairSel *= (fabs(muonsCandCollection[0].Eta()) < 2.4) ? true : false; // leading muon abs(eta) < 2.4 
				// for (unsigned int iTrailMuon == 1; muonsCandCollection.size(); iTrailMuon++) {
				// 	if ((muonsCandCollection[iTrailMuon].charge * muonsCandCollection[0].charge) < 1.0){
				// 	}
				// }
			}
			if (indexLeadCand != -99) {
				for (unsigned int iTrailMuon = indexLeadCand+1; iTrailMuon < muonsCandCollection.size(); iTrailMuon++) {
					if ((muonsCandCollection[iTrailMuon].charge * muonsCandCollection[indexLeadCand].charge) < 0){ //oposite charge
						indexTrailCand = iTrailMuon;
						break;
					}
				}
			}
			// goodMuonPairSel *= (muonsCandCollection[1].Pt() > 4.) ? true : false; // trailing muon pT > 4.0 GeV
			// goodMuonPairSel *= (fabs(muonsCandCollection[1].Eta()) < 2.4) ? true : false; // trailing muon abs(eta) < 2.4 
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


		////////////////////////////////////////////////////////////////////
		// photon analysis  
		vector< anaPhoton > photonsCandCollection;
		for (int iPhoton = 0; iPhoton < *nPho; iPhoton++) { //loop over muons
			// apply the calibrations save photon candidate
			// anaPhoton * photonCand = new anaPhoton(phoCalibEt[iPhoton], phoEta[iPhoton], phoPhi[iPhoton], iPhoton);
			shared_ptr<anaPhoton> photonCand(new anaPhoton(phoCalibEt[iPhoton], phoEta[iPhoton], phoPhi[iPhoton], iPhoton));
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
		} else {
			goodPhotonSel = false;
		}
		if (goodPhotonSel == true) {
			leadingPhoton = photonsCandCollection[0];
		}

		//////////////////////////////////////////////////////////////////////
		// reconstructed UpsilonSetPtEtaPhiM
		if (goodMuonPairSel && goodPhotonSel) recoUpsilon.SetPtEtaPhiM((leadingMuon + trailingMuon).Pt(), (leadingMuon + trailingMuon).Eta(), (leadingMuon + trailingMuon).Phi(), (leadingMuon + trailingMuon).M());
		// auto goodUpsilon = ( (recoUpsilon.M() > 7.0) && (recoUpsilon.M() < 12.0) ) ? true : false;

		//////////////////////////////////////////////////////////////////////
		// reconstructed Z
		if (goodMuonPairSel && goodPhotonSel) recoZ.SetPtEtaPhiM((recoUpsilon + leadingPhoton).Pt(), (recoUpsilon + leadingPhoton).Eta(), (recoUpsilon + leadingPhoton).Phi(), (recoUpsilon + leadingPhoton).M());
		// auto goodZ = ( (recoZ.M() > 7) && (recoZ.M() < 12.0) ) ? true : false;

		//////////////////////////////////////////////////////////////////////
		// muons ghost cleaning
		// REF: https://github.com/cms-analysis/MuonAnalysis-MuonAssociators/blob/master/plugins/MuonCleanerBySegments.cc
		// for (unsigned int iCandMuon = 0; iCandMuon < muonsCandCollection.size(); iCandMuon++) { //loop over muons
		// 	auto iMuIndex = muonsCandCollection[iCandMuon].muonIndex; //get global muon index
		// 	// for (auto i = muPixelLayers[iMuIndex].begin(); i != muPixelLayers[iMuIndex].end(); ++i)
  //   			std::cout << muPixelLayers[iMuIndex] << ' ';		
		// 	if ( (muType[iMuIndex] & TrackerMuon)  && !(muType[iMuIndex] & GlobalMuon) ) {
		// 		for (unsigned int jCandMuon = iCandMuon+1; jCandMuon < muonsCandCollection.size(); jCandMuon++) { //loop over muons
		// 			auto jMuIndex = muonsCandCollection[jCandMuon].muonIndex; //get global muon index
		// 			if (iMuIndex != jMuIndex) { // not the same muon
		// 				if ( (muType[jMuIndex] & TrackerMuon)  && !(muType[jMuIndex] & GlobalMuon) ) {

		// 				}
		// 			}
		// 		}
		// 	}
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
    cout << "\nDone  (" << outFileAppend <<  ")" << "!\n\n\n\n\n" << endl;

} //end ana_ZtoUpsilonPhoton


