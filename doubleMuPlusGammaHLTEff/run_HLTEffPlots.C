{
  gSystem->AddIncludePath("-Iexternal");
  gSystem->SetBuildDir("tmpdir", kTRUE);

  gROOT->ProcessLine(".L HLTEffPlot_ZtoUpsilonPhoton.C++");

  gStyle->SetOptStat(0);

  vector<string> ggNtuplesFiles = {
    "file:outTree_HLTTnPEff_ZtoUpsilonPhoton_Run2017F.root",
    // "outTree_HLTTnPEff_ZtoUpsilonPhoton_BACKUP.root",
  };



  HLTEffPlot_ZtoUpsilonPhoton(ggNtuplesFiles, -1);

}