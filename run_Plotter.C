{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	gROOT->ProcessLine(".L plotter_ZtoUpsilonPhoton.C+"); 
	gStyle->SetOptStat(0);

    // clear 
	system(("rm -rf outputPlots/*"));

	//////////////////////////////////////////////////////////////////
	// ZtoJPsi - Cat0
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoJPsi_Cat0_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToJPsiGamma_ZtoJPsi_Cat0_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoJPsi_Cat0_ZZZZZ.root",
		"ZtoJPsi"
		); 

	system(("mkdir -p outputPlots/ZtoJPsi_Cat0_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoJPsi_Cat0_ZZZZZ/."));
	system(("rm -rf plotFiles"));


	//////////////////////////////////////////////////////////////////
	// ZtoUpsilon - Cat0
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoUpsilon_Cat0_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat0_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoUpsilon_Cat0_ZZZZZ.root",
		"ZtoUpsilon"
		); 

	system(("mkdir -p outputPlots/ZtoUpsilon_Cat0_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoUpsilon_Cat0_ZZZZZ/."));
	system(("rm -rf plotFiles"));

	//////////////////////////////////////////////////////////////////
	// ZtoJPsi - Cat1
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoJPsi_Cat1_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToJPsiGamma_ZtoJPsi_Cat1_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoJPsi_Cat1_ZZZZZ.root",
		"ZtoJPsi"
		); 

	system(("mkdir -p outputPlots/ZtoJPsi_Cat1_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoJPsi_Cat1_ZZZZZ/."));
	system(("rm -rf plotFiles"));


	//////////////////////////////////////////////////////////////////
	// ZtoUpsilon - Cat1
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoUpsilon_Cat1_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat1_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoUpsilon_Cat1_ZZZZZ.root",
		"ZtoUpsilon"
		); 

	system(("mkdir -p outputPlots/ZtoUpsilon_Cat1_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoUpsilon_Cat1_ZZZZZ/."));
	system(("rm -rf plotFiles"));


	//////////////////////////////////////////////////////////////////
	// ZtoJPsi - Cat2
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoJPsi_Cat2_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToJPsiGamma_ZtoJPsi_Cat2_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoJPsi_Cat2_ZZZZZ.root",
		"ZtoJPsi"
		); 

	system(("mkdir -p outputPlots/ZtoJPsi_Cat2_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoJPsi_Cat2_ZZZZZ/."));
	system(("rm -rf plotFiles"));


	//////////////////////////////////////////////////////////////////
	// ZtoUpsilon - Cat2
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoUpsilon_Cat2_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat2_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoUpsilon_Cat2_ZZZZZ.root",
		"ZtoUpsilon"
		); 

	system(("mkdir -p outputPlots/ZtoUpsilon_Cat2_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoUpsilon_Cat2_ZZZZZ/."));
	system(("rm -rf plotFiles"));


	//////////////////////////////////////////////////////////////////
	// ZtoJPsi - Cat3
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoJPsi_Cat3_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToJPsiGamma_ZtoJPsi_Cat3_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoJPsi_Cat3_ZZZZZ.root",
		"ZtoJPsi"
		); 

	system(("mkdir -p outputPlots/ZtoJPsi_Cat3_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoJPsi_Cat3_ZZZZZ/."));
	system(("rm -rf plotFiles"));

	//////////////////////////////////////////////////////////////////
	// ZtoUpsilon - Cat3
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoUpsilon_Cat3_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat3_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoUpsilon_Cat3_ZZZZZ.root",
		"ZtoUpsilon"
		); 

	system(("mkdir -p outputPlots/ZtoUpsilon_Cat3_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoUpsilon_Cat3_ZZZZZ/."));
	system(("rm -rf plotFiles"));



	//////////////////////////////////////////////////////////////////
	// HtoJPsi
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_HtoJPsi_Cat0_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_HToJPsiGamma_HtoJPsi_Cat0_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_HDalitz_HtoJPsi_Cat0_ZZZZZ.root",
		"HtoJPsi"
		); 

	system(("mkdir -p outputPlots/HtoJPsi_Cat0_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/HtoJPsi_Cat0_ZZZZZ/."));
	system(("rm -rf plotFiles"));


	//////////////////////////////////////////////////////////////////
	// HtoUpsilon
	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_HtoUpsilon_Cat0_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon_Cat0_ZZZZZ.root",
		// "outputHistos/outHistos_ZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon_Cat0_ZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_HDalitz_HtoUpsilon_Cat0_ZZZZZ.root",
		"HtoUpsilon"
		); 

	system(("mkdir -p outputPlots/HtoUpsilon_Cat0_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/HtoUpsilon_Cat0_ZZZZZ/."));
	system(("rm -rf plotFiles"));

	

}
