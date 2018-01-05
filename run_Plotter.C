{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	gROOT->ProcessLine(".L plotter_ZtoUpsilonPhoton.C+"); 
	gStyle->SetOptStat(0);

    // clear 
	system(("rm -rf outputPlots"));


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

	// ZtoJpsi
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_ZtoUpsilonPhoton_Data_ZtoJpsi.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_ZToJPsiGamma_ZtoJpsi.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoJpsi.root",
		"ZtoJpsi"
		); 

	system(("mkdir -p outputPlots/ZtoJpsi"));
	system(("mv plotFiles/* outputPlots/ZtoJpsi/."));
	system(("rm -rf plotFiles"));

	// HtoJpsi
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_ZtoUpsilonPhoton_Data_HtoJpsi.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_HToJPsiGamma_HtoJpsi.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_HDalitz_HtoJpsi.root",
		"HtoJpsi"
		); 

	system(("mkdir -p outputPlots/HtoJpsi"));
	system(("mv plotFiles/* outputPlots/HtoJpsi/."));
	system(("rm -rf plotFiles"));


	// HtoUpsilon
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_ZtoUpsilonPhoton_Data_HtoUpsilon.root",
		// "outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_HDalitz_HtoUpsilon.root",
		"HtoUpsilon"
		); 

	system(("mkdir -p outputPlots/HtoUpsilon"));
	system(("mv plotFiles/* outputPlots/HtoUpsilon/."));
	system(("rm -rf plotFiles"));

}
