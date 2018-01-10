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
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJpsi"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoJpsi"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoUpsilon"); // Data



	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root"}, "ZToUpsilon1SGamma", "ZtoUpsilon",false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root"}, "ZToUpsilon2SGamma", "ZtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"}, "ZToUpsilon3SGamma", "ZtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma.root"}, "ZToJPsiGamma", "ZtoJpsi", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", false); //MC



	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon1SGamma.root"}, "HToUpsilon1SGamma", "HtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon2SGamma.root"}, "HToUpsilon2SGamma", "HtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon3SGamma.root"}, "HToUpsilon3SGamma", "HtoUpsilon", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToJPsiGamma.root"}, "HToJPsiGamma", "HtoJpsi", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HDalitz.root"}, "HDalitz", "HtoJPsi", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HDalitz.root"}, "HDalitz", "HtoUpsilon", false); //MC


	system("hadd -f outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon.root outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon.root outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilon2SGamma_HtoUpsilon.root outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilon3SGamma_HtoUpsilon.root");
	system("hadd -f outputHistos/outTreeToFit_ZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon.root outputHistos/outTreeToFit_ZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon.root outputHistos/outTreeToFit_ZtoUpsilonPhoton_HToUpsilon2SGamma_HtoUpsilon.root outputHistos/outTreeToFit_ZtoUpsilonPhoton_HToUpsilon3SGamma_HtoUpsilon.root");

	system("cat evtsCountFiles/*.csv > evtsCountFiles/MERGED_evtsCountFiles.csv");


	
}
