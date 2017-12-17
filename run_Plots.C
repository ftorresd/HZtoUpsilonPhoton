{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	
	gROOT->ProcessLine(".L plugins/getFilesList.C+");
	gROOT->ProcessLine(".L plots_ZtoUpsilonPhoton.C+"); 

	gStyle->SetOptStat(0);

	
	vector<string> ntuplesToPlotFilesData = {
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016B.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016E.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016G.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016C.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016D.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3.root"
					};
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data"); // Data



plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root"}, "ZToUpsilon1SGamma", false); //MC
plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root"}, "ZToUpsilon2SGamma", false); //MC
plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"}, "ZToUpsilon3SGamma", false); //MC
plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma.root"}, "ZToJPsiGamma", false); //MC
plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", false); //MC



plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon1SGamma.root"}, "HToUpsilon1SGamma", false); //MC
plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon2SGamma.root"}, "HToUpsilon2SGamma", false); //MC
plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon3SGamma.root"}, "HToUpsilon3SGamma", false); //MC
plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToJPsiGamma.root"}, "HToJPsiGamma", false); //MC
plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HDalitz.root"}, "HDalitz", false); //MC

	
}

