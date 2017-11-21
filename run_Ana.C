{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);


	
	gROOT->ProcessLine(".L plugins/getFilesList.C+");
	gROOT->ProcessLine(".L ana_ZtoUpsilonPhoton.C+");

	gStyle->SetOptStat(0);





 	vector<string> ggNtuplesFiles = getFilesList("filesLists/MuonEG_Run2016B_Ming.txt"); //Run2016B - Ming

 	ana_ZtoUpsilonPhoton(ggNtuplesFiles, 100, "Run2016B");
}