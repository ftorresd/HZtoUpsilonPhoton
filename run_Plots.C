{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	
	gROOT->ProcessLine(".L plugins/getFilesList.C+");
	gROOT->ProcessLine(".L plots_ZtoUpsilonPhoton.C+"); 

	gStyle->SetOptStat(0);

	
	vector<string> ntuplesToPlotFilesData = {
						"outputFiles_BKP/outTree_ZtoUpsilonPhoton_Run2016B.root", 
						"outputFiles_BKP/outTree_ZtoUpsilonPhoton_Run2016E.root", 
						"outputFiles_BKP/outTree_ZtoUpsilonPhoton_Run2016G.root", 
						"outputFiles_BKP/outTree_ZtoUpsilonPhoton_Run2016C.root", 
						"outputFiles_BKP/outTree_ZtoUpsilonPhoton_Run2016F1.root", 
						"outputFiles_BKP/outTree_ZtoUpsilonPhoton_Run2016H2.root", 
						"outputFiles_BKP/outTree_ZtoUpsilonPhoton_Run2016D.root", 
						"outputFiles_BKP/outTree_ZtoUpsilonPhoton_Run2016F2.root", 
						"outputFiles_BKP/outTree_ZtoUpsilonPhoton_Run2016H3.root"
					};



	vector<string> ntuplesToPlotFilesMC = {
						"outputFiles_BKP/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root",
						// "outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root",
						// "outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"
					};




	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC, "MC", false); //MC
}

