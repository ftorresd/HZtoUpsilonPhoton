{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	
	gROOT->ProcessLine(".L plugins/getFilesList.C+");
	gROOT->ProcessLine(".L plots_ZtoUpsilonPhoton.C+"); 

	gStyle->SetOptStat(0);

	system("rm -fr evtsCountFiles; mkdir evtsCountFiles");
	
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
					
	// Data - Z
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon"); // Data
	// MC - Z
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root"}, "ZToUpsilon1SGamma", "ZtoUpsilon",false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root"}, "ZToUpsilon2SGamma", "ZtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"}, "ZToUpsilon3SGamma", "ZtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma.root"}, "ZToJPsiGamma", "ZtoJPsi", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", false); //MC


	// Data - H
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoJPsi"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoUpsilon"); // Data
	// MC - H
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon1SGamma.root"}, "HToUpsilon1SGamma", "HtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon2SGamma.root"}, "HToUpsilon2SGamma", "HtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon3SGamma.root"}, "HToUpsilon3SGamma", "HtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToJPsiGamma.root"}, "HToJPsiGamma", "HtoJPsi", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HDalitz.root"}, "HDalitz", "HtoJPsi", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HDalitz.root"}, "HDalitz", "HtoUpsilon", false); //MC
	// Merge Higgs Fit Tree
	system("hadd -f outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon.root outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon.root outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilon2SGamma_HtoUpsilon.root outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilon3SGamma_HtoUpsilon.root");
	system("hadd -f outputHistos/outTreeToFit_ZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon.root outputHistos/outTreeToFit_ZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon.root outputHistos/outTreeToFit_ZtoUpsilonPhoton_HToUpsilon2SGamma_HtoUpsilon.root outputHistos/outTreeToFit_ZtoUpsilonPhoton_HToUpsilon3SGamma_HtoUpsilon.root");


	// N_evts and yields
	system("cat evtsCountFiles/*.csv > evtsCountFiles/MERGED_evtsCountFiles.csv");


	
}
