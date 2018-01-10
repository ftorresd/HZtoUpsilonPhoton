{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	gROOT->ProcessLine(".L plotter_ZtoUpsilonPhoton.C+"); 
	gStyle->SetOptStat(0);

    // clear 
	system(("rm -rf outputPlots/*"));

	//////////////////////////////////////////////////////////////////
	// ZtoJPsi
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_ZtoUpsilonPhoton_Data_ZtoJPsi.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_ZToJPsiGamma_ZtoJPsi.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoJPsi.root",
		"ZtoJPsi"
		); 

	system(("mkdir -p outputPlots/ZtoJPsi"));
	system(("mv plotFiles/* outputPlots/ZtoJPsi/."));
	system(("rm -rf plotFiles"));

	//////////////////////////////////////////////////////////////////
	// ZtoUpsilon
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_ZtoUpsilonPhoton_Data_ZtoUpsilon.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoUpsilon.root",
		"ZtoUpsilon"
		); 

	system(("mkdir -p outputPlots/ZtoUpsilon"));
	system(("mv plotFiles/* outputPlots/ZtoUpsilon/."));
	system(("rm -rf plotFiles"));



	//////////////////////////////////////////////////////////////////
	// HtoJPsi
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_ZtoUpsilonPhoton_Data_HtoJPsi.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_HToJPsiGamma_HtoJPsi.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_HDalitz_HtoJPsi.root",
		"HtoJPsi"
		); 

	system(("mkdir -p outputPlots/HtoJPsi"));
	system(("mv plotFiles/* outputPlots/HtoJPsi/."));
	system(("rm -rf plotFiles"));


	//////////////////////////////////////////////////////////////////
	// HtoUpsilon
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_ZtoUpsilonPhoton_Data_HtoUpsilon.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon.root",
		// "outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_HDalitz_HtoUpsilon.root",
		"HtoUpsilon"
		); 

	system(("mkdir -p outputPlots/HtoUpsilon"));
	system(("mv plotFiles/* outputPlots/HtoUpsilon/."));
	system(("rm -rf plotFiles"));

	

}
