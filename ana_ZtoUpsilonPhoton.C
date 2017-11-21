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
#include <algorithm>
#include <math.h>  

#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "TRandom3.h"
// #include "TClassTable.h"
#include "TROOT.h"


#include "plugins/ggNtuplesFilesReader.h"
#include "plugins/roccor2016/RoccoR.cc"
#include "plugins/deltaR_deltaPhi.h"
#include "plugins/anaObjects.h"

#ifdef __CINT__
#pragma link C++ class anaMuon+;
#pragma link C++ class anaPhoton+;
#endif

using namespace std;


void ana_ZtoUpsilonPhoton(vector<string> ggNtuplesFiles, int nFiles = -1, string outFileAppend = "", bool isMC = false)  
{
	// output tree
	// TFile outFile("outTree_ZtoUpsilonPhoton.root","RECREATE","ZtoUpsilonPhoton output analysis tree");
	string outputFileName = "outTree_ZtoUpsilonPhoton_"+ outFileAppend + ".root";
	TFile * outFile  = new TFile(outputFileName.c_str(),"RECREATE","ZtoUpsilonPhoton output analysis tree");
	TTree * outTree = new TTree("outTree_ZtoUpsilonPhoton","ZtoUpsilonPhoton output analysis tree");

	// loads the ggNtuples 
	if (nFiles > 0) {
		ggNtuplesFiles.resize(nFiles);	
	}
	TTreeReader * dataReader = ggNtuplesFilesReader( ggNtuplesFiles, nFiles );
	TTree * dataTree = dataReader->GetTree();

	////////////////////////////////////////////////////////////////////
	// define readers
	// event
	TTreeReaderValue< int > run(*dataReader, "run");
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
	/// muon type - type of the algorithm that reconstructed this muon
	//  multiple algorithms can reconstruct the same muon
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
	TTreeReaderArray< unsigned int > muFiredTrgs(*dataReader, "muFiredTrgs");
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

	
	////////////////////////////////////////////////////////////////////
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
	// nl is trackerLayersWithMeasurement \\
	// u1 and u2 are random numbers distributed uniformly between 0 and 1 (gRandom->Rndm());
	// s is error set (default is 0)
	// m is error member (default is 0)
	// For MC, when switching to different error sets/members for a given muon, random numbers (u1 and u2) should remain unchanged. 


	RoccoR  rc("plugins/roccor2016/rcdata.2016.v3"); // define corrections object


	////////////////////////////////////////////////////////////////////
	// numer of entries
	auto totalEvts = dataTree->GetEntries();
	auto printEvery = 10000;
	cout << "\nN. Entries: " << totalEvts << endl;
	cout << "\nPrinting every: " << printEvery << " events" << endl;
	cout << "\nLooping over events... \n" << endl;

	// dataTree->Print();


	////////////////////////////////////////////////////////////////////
	// main loop
	auto iEvt = 0;
	while (dataReader->Next()) { // loop over events
		if (iEvt % printEvery == 0) cout << "----------------------------------------> Events read: " << iEvt << " / " << totalEvts << " - ~"<< round(((float)iEvt/(float)totalEvts)*100) << "%"<< endl;
		iEvt++;

		////////////////////////////////////////////////////////////////////
		// trigger test 
		auto goodEvt = true;
		goodEvt *= (((*HLTEleMuX >> 8) & 1) == 1) ? true : false; // HLT_Mu17_Photon30_CaloIdL_L1ISO_v*
		if (goodEvt == false) continue;
		// cout << "Pass HLT!" << endl;

		////////////////////////////////////////////////////////////////////
		// muons analysis  
		vector< anaMuon > muonsCandCollection;
		for (int iMuon = 0; iMuon < *nMu; iMuon++) { //loop over muons
			////////////////////////////////////////////////////////////////////
			// apply rochester corrections and get the corrected muons candidates collection
			// get RocCor SF
			TRandom *rand3 = new TRandom3();
			auto getRocCorRandom1 = rand3->Rndm();
			auto getRocCorRandom2 = rand3->Rndm();
			double rocCorSF = 1.0;
			if (isMC) rocCorSF = rc.kScaleAndSmearMC(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], muTrkLayers[iMuon], getRocCorRandom1, getRocCorRandom2, 0, 0);
			else rocCorSF = rc.kScaleDT(muCharge[iMuon], muPt[iMuon], muEta[iMuon], muPhi[iMuon], 0, 0);

			// apply the corrections save muon candidate
			anaMuon * muonCand = new anaMuon(muPt[iMuon]*rocCorSF, muEta[iMuon], muPhi[iMuon], muCharge[iMuon], iMuon);

			// cout << muonCand->Pt();
			muonsCandCollection.push_back(*muonCand);
		}
		sort(muonsCandCollection.begin(), muonsCandCollection.end(),greater<anaMuon>()); // re-sort muon collection

		//////////////////////////////////////////////////////////////////////
		// muons ID
		for (unsigned int iCandMuon = 0; iCandMuon < muonsCandCollection.size(); iCandMuon++) { //loop over muons
			auto muIndex = muonsCandCollection[iCandMuon].muonIndex; //get global muon index

			// loose ID
			auto isMuonLooseID = true; //candidate muon loose id
			isMuonLooseID *= (muonsCandCollection[iCandMuon].Pt() > 5.0) ? true : false; // pT > 4.0 GeV
		 	isMuonLooseID *= (fabs(muonsCandCollection[iCandMuon].Eta()) < 2.4) ? true : false;  //abs(eta) < 2.4
		 	isMuonLooseID *= (fabs(muD0[muIndex]) < 0.5) ? true : false;  //dxy < 2.4
		 	isMuonLooseID *= (fabs(muDz[muIndex]) < 1.0) ? true : false;  //dz < 1.0
		 	isMuonLooseID *= (muBestTrkType[muIndex] != 2) ? true : false;  //muBestTrkType != 2
		 	isMuonLooseID *= ( (muType[muIndex] & GlobalMuon) || ((muType[muIndex] & TrackerMuon) && (muMatches[muIndex] > 0)) ) ? true : false;
		 	isMuonLooseID *= (muSIP[muIndex] < 4) ? true : false;  //muon SIP < 4
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
			if (!(muonsCandCollection[iCandMuon].muonIsTightID) || !(fabs(muonsCandCollection[iCandMuon].Eta()) < 2.4)) {
				muonsCandCollection.erase(muonsCandCollection.begin() + iCandMuon);
			}
		}

		////////////////////////////////////////////////////////////////////
		// muons selection
		// sort(muonsCandCollection.begin(), muonsCandCollection.end(),greater<anaMuon>()); // re-sort muon collection
		auto goodMuonPairSel = true; // muon pair pre-selection
		if (muonsCandCollection.size() >= 2) {
			goodMuonPairSel *= (muonsCandCollection[0].muonIsISO) ? true : false; // leading muon is ISO
			goodMuonPairSel *= (muonsCandCollection[0].Pt() > 20.) ? true : false; // leading muon pT > 20.0 GeV
			// goodMuonPairSel *= (fabs(muonsCandCollection[0].Eta()) < 2.4) ? true : false; // leading muon abs(eta) < 2.4 
			goodMuonPairSel *= (muonsCandCollection[1].Pt() > 4.) ? true : false; // trailing muon pT > 4.0 GeV
			// goodMuonPairSel *= (fabs(muonsCandCollection[1].Eta()) < 2.4) ? true : false; // trailing muon abs(eta) < 2.4 
		} else {
			goodMuonPairSel = false;
		}
		if (goodMuonPairSel == true) {
			leadingMuon = muonsCandCollection[0];
			trailingMuon = muonsCandCollection[1];
		}


		////////////////////////////////////////////////////////////////////
		// photon analysis  
		vector< anaPhoton > photonsCandCollection;
		for (int iPhoton = 0; iPhoton < *nPho; iPhoton++) { //loop over muons
			// apply the calibrations save photon candidate
			anaPhoton * photonCand = new anaPhoton(phoCalibEt[iPhoton], phoEta[iPhoton], phoPhi[iPhoton], iPhoton);
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
			photonsCandCollection[iCandPhoton].photonR9 = phoR9[phoIndex];
			
			// clean photon collection 
			if (!goodPhoton) {
				photonsCandCollection.erase(photonsCandCollection.begin() + iCandPhoton);
			}
		}

		// photon selection
		sort(photonsCandCollection.begin(), photonsCandCollection.end(),greater<anaPhoton>()); // re-sort photon collection
		auto goodPhotonSel = true; 
		if (photonsCandCollection.size() >= 1) {
			goodPhotonSel *= (photonsCandCollection[0].Pt() > 33.) ? true : false; // photon Et > 33.0 GeV
		} else {
			goodPhotonSel = false;
		}
		if (goodPhotonSel == true) {
			leadingPhoton = photonsCandCollection[0];
		}

		//////////////////////////////////////////////////////////////////////
		// reconstructed Upsilon
		recoUpsilon = leadingMuon + trailingMuon

		//////////////////////////////////////////////////////////////////////
		// reconstructed Z
		recoZ = recoUpsilon + leadingPhoton

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
		auto isGoodEvent = true;
		if (isGoodEvent) {
			outTree->Fill();
			leadingMuon.clear();
			trailingMuon.clear();
			leadingPhoton.clear();
		}

    } // end loop over events

    // post-processing 
    cout << "\n\n\nWriting output file..." << endl;
    outTree->Print();
    outFile->Write();
    cout << "\nDone!\n\n" << endl;

} //end ana_ZtoUpsilonPhoton


