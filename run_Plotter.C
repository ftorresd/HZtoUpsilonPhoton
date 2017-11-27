{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	gROOT->ProcessLine(".L plotter_ZtoUpsilonPhoton.C+"); 
	gStyle->SetOptStat(0);

	plotter_ZtoUpsilonPhoton("outputHistos/outHistos_ZtoUpsilonPhoton_Data.root", "outputHistos/outHistos_ZtoUpsilonPhoton_MC.root"); 

}

