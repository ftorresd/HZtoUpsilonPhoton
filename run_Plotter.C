{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	gROOT->ProcessLine(".L plotter_HZtoUpsilonPhoton.C+"); 
	gStyle->SetOptStat(0);

    // clear 
	system(("rm -rf outputPlots/*"));

	// //////////////////////////////////////////////////////////////////
	// // ZtoJPsi - Cat0
	// plotter_HZtoUpsilonPhoton(
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoJPsi_Cat0_ZZZZZZ.root",
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_ZToJPsiGamma_ZtoJPsi_Cat0_ZZZZZZ.root",
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoJPsi_Cat0_ZZZZZZ.root",
	// 	"ZtoJPsi"
	// 	); 

	// system(("mkdir -p outputPlots/ZtoJPsi_Cat0_ZZZZZ"));
	// system(("mv plotFiles/* outputPlots/ZtoJPsi_Cat0_ZZZZZ/."));
	// system(("rm -rf plotFiles"));


	//////////////////////////////////////////////////////////////////
	// ZtoUpsilon - Cat0
	plotter_HZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoUpsilon_Cat0_ZZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat0_ZZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoUpsilon_Cat0_ZZZZZZ.root",
		"ZtoUpsilon"
		); 

	system(("mkdir -p outputPlots/ZtoUpsilon_Cat0_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoUpsilon_Cat0_ZZZZZ/."));
	system(("rm -rf plotFiles"));

	// //////////////////////////////////////////////////////////////////
	// // ZtoJPsi - Cat1
	// plotter_HZtoUpsilonPhoton(
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoJPsi_Cat1_ZZZZZZ.root",
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_ZToJPsiGamma_ZtoJPsi_Cat1_ZZZZZZ.root",
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoJPsi_Cat1_ZZZZZZ.root",
	// 	"ZtoJPsi"
	// 	); 

	// system(("mkdir -p outputPlots/ZtoJPsi_Cat1_ZZZZZ"));
	// system(("mv plotFiles/* outputPlots/ZtoJPsi_Cat1_ZZZZZ/."));
	// system(("rm -rf plotFiles"));


	//////////////////////////////////////////////////////////////////
	// ZtoUpsilon - Cat1
	plotter_HZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoUpsilon_Cat1_ZZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat1_ZZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoUpsilon_Cat1_ZZZZZZ.root",
		"ZtoUpsilon"
		); 

	system(("mkdir -p outputPlots/ZtoUpsilon_Cat1_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoUpsilon_Cat1_ZZZZZ/."));
	system(("rm -rf plotFiles"));


	// //////////////////////////////////////////////////////////////////
	// // ZtoJPsi - Cat2
	// plotter_HZtoUpsilonPhoton(
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoJPsi_Cat2_ZZZZZZ.root",
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_ZToJPsiGamma_ZtoJPsi_Cat2_ZZZZZZ.root",
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoJPsi_Cat2_ZZZZZZ.root",
	// 	"ZtoJPsi"
	// 	); 

	// system(("mkdir -p outputPlots/ZtoJPsi_Cat2_ZZZZZ"));
	// system(("mv plotFiles/* outputPlots/ZtoJPsi_Cat2_ZZZZZ/."));
	// system(("rm -rf plotFiles"));


	//////////////////////////////////////////////////////////////////
	// ZtoUpsilon - Cat2
	plotter_HZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoUpsilon_Cat2_ZZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat2_ZZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoUpsilon_Cat2_ZZZZZZ.root",
		"ZtoUpsilon"
		); 

	system(("mkdir -p outputPlots/ZtoUpsilon_Cat2_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoUpsilon_Cat2_ZZZZZ/."));
	system(("rm -rf plotFiles"));


	// //////////////////////////////////////////////////////////////////
	// // ZtoJPsi - Cat3
	// plotter_HZtoUpsilonPhoton(
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoJPsi_Cat3_ZZZZZZ.root",
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_ZToJPsiGamma_ZtoJPsi_Cat3_ZZZZZZ.root",
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoJPsi_Cat3_ZZZZZZ.root",
	// 	"ZtoJPsi"
	// 	); 

	// system(("mkdir -p outputPlots/ZtoJPsi_Cat3_ZZZZZ"));
	// system(("mv plotFiles/* outputPlots/ZtoJPsi_Cat3_ZZZZZ/."));
	// system(("rm -rf plotFiles"));

	//////////////////////////////////////////////////////////////////
	// ZtoUpsilon - Cat3
	plotter_HZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_ZtoUpsilon_Cat3_ZZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat3_ZZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_ZtoUpsilon_Cat3_ZZZZZZ.root",
		"ZtoUpsilon"
		); 

	system(("mkdir -p outputPlots/ZtoUpsilon_Cat3_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/ZtoUpsilon_Cat3_ZZZZZ/."));
	system(("rm -rf plotFiles"));



	// //////////////////////////////////////////////////////////////////
	// // HtoJPsi
	// plotter_HZtoUpsilonPhoton(
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_Data_HtoJPsi_Cat0_ZZZZZZ.root",
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_HToJPsiGamma_HtoJPsi_Cat0_ZZZZZZ.root",
	// 	"outputHistos/outHistos_HZtoUpsilonPhoton_HDalitz_HtoJPsi_Cat0_ZZZZZZ.root",
	// 	"HtoJPsi"
	// 	); 

	// system(("mkdir -p outputPlots/HtoJPsi_Cat0_ZZZZZ"));
	// system(("mv plotFiles/* outputPlots/HtoJPsi_Cat0_ZZZZZ/."));
	// system(("rm -rf plotFiles"));


	//////////////////////////////////////////////////////////////////
	// HtoUpsilon
	plotter_HZtoUpsilonPhoton(
		"outputHistos/outHistos_HZtoUpsilonPhoton_Data_HtoUpsilon_Cat0_ZZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon_Cat0_ZZZZZZ.root",
		"outputHistos/outHistos_HZtoUpsilonPhoton_HDalitz_HtoUpsilon_Cat0_ZZZZZZ.root",
		"HtoUpsilon"
		); 

	system(("mkdir -p outputPlots/HtoUpsilon_Cat0_ZZZZZ"));
	system(("mv plotFiles/* outputPlots/HtoUpsilon_Cat0_ZZZZZ/."));
	system(("rm -rf plotFiles"));

	

}
