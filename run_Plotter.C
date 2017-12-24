{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	gROOT->ProcessLine(".L plotter_ZtoUpsilonPhoton.C+"); 
	gStyle->SetOptStat(0);

	plotter_ZtoUpsilonPhoton(
		"outputHistos/outHistos_ZtoUpsilonPhoton_Data.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root",
		// "outputHistos/outHistos_ZtoUpsilonPhoton_ZToJPsiGamma.root",
		"outputHistos/outHistos_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"
		); 

}

