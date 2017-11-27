{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);


	
	gROOT->ProcessLine(".L plugins/getFilesList.C+");
	gROOT->ProcessLine(".L ana_ZtoUpsilonPhoton.C+"); 

	gStyle->SetOptStat(0);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Data
 	ana_ZtoUpsilonPhoton(getFilesList("filesLists/job_MuEG_Run2016B_FebReminiAOD.txt") , -1, "Run2016B");
 	ana_ZtoUpsilonPhoton(getFilesList("filesLists/job_MuEG_Run2016C_FebReminiAOD.txt"), -1, "Run2016C");
 	ana_ZtoUpsilonPhoton(getFilesList("filesLists/job_MuEG_Run2016D_FebReminiAOD.txt") , -1, "Run2016D");
 	ana_ZtoUpsilonPhoton(getFilesList("filesLists/job_MuEG_Run2016E_FebReminiAOD.txt"), -1, "Run2016E");
 	ana_ZtoUpsilonPhoton(getFilesList("filesLists/job_MuEG_Run2016F_FebReminiAOD1.txt"), -1, "Run2016F1");
 	ana_ZtoUpsilonPhoton(getFilesList("filesLists/job_MuEG_Run2016F_FebReminiAOD2.txt"), -1, "Run2016F2");
 	ana_ZtoUpsilonPhoton(getFilesList("filesLists/job_MuEG_Run2016G_SepRereco.txt"), -1, "Run2016G");
 	ana_ZtoUpsilonPhoton(getFilesList("filesLists/job_MuEG_Run2016H_PRv2.txt"), -1, "Run2016H2");
    ana_ZtoUpsilonPhoton(getFilesList("filesLists/job_MuEG_Run2016H_PRv3.txt"), -1, "Run2016H3");


  //   ana_ZtoUpsilonPhoton(getFilesList("filesLists/filesFromEOS/job_MuEG_Run2016B_FebReminiAOD.txt") , -1, "Run2016B");
 	// ana_ZtoUpsilonPhoton(getFilesList("filesLists/filesFromEOS/job_MuEG_Run2016C_FebReminiAOD.txt"), -1, "Run2016C");
 	// ana_ZtoUpsilonPhoton(getFilesList("filesLists/filesFromEOS/job_MuEG_Run2016D_FebReminiAOD.txt") , -1, "Run2016D");
 	// ana_ZtoUpsilonPhoton(getFilesList("filesLists/filesFromEOS/job_MuEG_Run2016E_FebReminiAOD.txt"), -1, "Run2016E");
 	// ana_ZtoUpsilonPhoton(getFilesList("filesLists/filesFromEOS/job_MuEG_Run2016F_FebReminiAOD1.txt"), -1, "Run2016F1");
 	// ana_ZtoUpsilonPhoton(getFilesList("filesLists/filesFromEOS/job_MuEG_Run2016F_FebReminiAOD2.txt"), -1, "Run2016F2");
 	// ana_ZtoUpsilonPhoton(getFilesList("filesLists/filesFromEOS/job_MuEG_Run2016G_SepRereco.txt"), -1, "Run2016G");
 	// ana_ZtoUpsilonPhoton(getFilesList("filesLists/filesFromEOS/job_MuEG_Run2016H_PRv2.txt"), -1, "Run2016H2");
  //   ana_ZtoUpsilonPhoton(getFilesList("filesLists/filesFromEOS/job_MuEG_Run2016H_PRv3.txt"), -1, "Run2016H3");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
 	// MC
 	// ana_ZtoUpsilonPhoton(getFilesList("filesLists/ZToUpsilon1SGamma_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV.txt"), -1, "ZToUpsilon1SGamma", true, "puWeight/puWeights_ZToUpsilon1SGamma.root");
 	// ana_ZtoUpsilonPhoton(getFilesList("filesLists/ZToUpsilon2SGamma_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV.txt"), -1, "ZToUpsilon2SGamma", true, "puWeight/puWeights_ZToUpsilon1SGamma.root");
 	// ana_ZtoUpsilonPhoton(getFilesList("filesLists/ZToUpsilon3SGamma_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV.txt"), -1, "ZToUpsilon3SGamma", true, "puWeight/puWeights_ZToUpsilon1SGamma.root");

}