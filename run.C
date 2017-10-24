{
  gSystem->AddIncludePath("-Iexternal");
  gSystem->SetBuildDir("tmpdir", kTRUE);
  //gROOT->LoadMacro("xAna_Hjpsigamma_forData.C+");
  gROOT->ProcessLine(".L xAna_Zjpsigamma.C++");

  gStyle->SetOptStat(0);

  char inpath[200];
  //sprintf(inpath, "/data1/ggNtuples/V08_00_24_00/job_MuEG*/ggtree_data_*.root");
  //sprintf(inpath, "eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V08_00_26_01/job_MuEG*/ggtree_data_*.root");
  sprintf(inpath, "/data1/hjheng/FebReminiAOD/job_MuEG_Run2016*/ggtree_data_*.root");
  
  //TString outpath_1 = "output_tree/minitree_2016_RatioCuts_Data.root";
  //TString outpath_2 = "output_tree/minitree_2016_OrdinaryCuts_Data.root";

  //TString outpath_1 = "output_tree/minitree_2016_RatioCuts_dRdPhiCuts_Mmumu3to3p2_Data.root";
  //TString outpath_2 = "output_tree/minitree_2016_OrdinaryCuts_dRdPhiCuts_Mmumu3to3p2_Data.root";

  //TString outpath_1 = "output_tree/minitree_2016_RatioCuts_MuonMediumID_dRdPhiCuts_Mmumu3to3p2_Data.root";
  //TString outpath_2 = "output_tree/minitree_2016_OrdinaryCuts_MuonMediumID_dRdPhiCuts_Mmumu3to3p2_Data.root";

  TString outpath_1 = "output_tree/minitree_2016_Data.root";
  //TString outpath_2 = "output_tree/minitree_2016_OrdinaryCuts_MuonMediumID_dRdPhiCuts_Mmumu3to3p2_Data.root";
  
  float luminosity = 35.861;
  float Cross_section = 0.33551; // XS(Z->Jpsi+gamma->mumugamma)                                     
                                  // XS(pp->Z) = 59661.3526092 pb     
                                  // BR(Z->Jpsi+gamma) = 9.96*10^-8   
                                  // BR(Jpsi->mumu) = 0.059
  
  TString PU_hist = "PUweight_histogram/80X_36p0invfb/summer16/PU_histo_13TeV_GoldenJSON_69200nb.root";
  TString PU_hist_down = "PUweight_histogram/80X_36p0invfb/summer16/PU_histo_13TeV_GoldenJSON_65740nb.root";
  TString PU_hist_up = "PUweight_histogram/80X_36p0invfb/summer16/PU_histo_13TeV_GoldenJSON_72660nb.root";

  /*
  string outfile1 ("LimitSetting/Inputs/ZMass_signal_2016.txt");
  string outfile2 ("LimitSetting/Inputs_Jpsi/JpsiMass_signal_Rochcor_2016.txt");
  string outfile3 ("LimitSetting/Inputs/ZMass_signal_2016_NoWeight.txt");
  string outfile4 ("LimitSetting/Inputs_Jpsi/JpsiMass_signal_Rochcor_2016_NoWeight.txt");
  string outfile5 ("LimitSetting/Inputs/ZMass_2016.txt");
  string outfile6 ("cat_SingleMuon/fail_MuEGSelection_signal_2016.txt");
  string outfile7 ("cat_SingleMuon/fail_MuEGSelection_2016.txt");
  string outfile8 ("LimitSetting/Inputs/ZMass_40to200_2016.txt");
  */
  
  int Is_aMCatLNO = 0;

  //xAna_Zjpsigamma_2016(inpath, outpath_2, luminosity, Cross_section, Is_aMCatLNO, PU_hist, PU_hist_up, PU_hist_down, 0);
  xAna_Zjpsigamma_2016(inpath, outpath_1, luminosity, Cross_section, 0, PU_hist, PU_hist_up, PU_hist_down, 1, 0);
}