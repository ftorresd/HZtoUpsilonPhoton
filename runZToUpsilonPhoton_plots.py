#!/usr/bin/env python

# MuonEG
fileHeader = '''
{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	
	gROOT->ProcessLine(".L plugins/getFilesList.C+");
	gROOT->ProcessLine(".L plots_ZtoUpsilonPhoton.C+"); 

	gStyle->SetOptStat(0);

	// system("rm -fr evtsCountFiles; mkdir evtsCountFiles");
	
	vector<string> ntuplesToPlotFilesData = {
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B_0.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B_1.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B_2.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B_3.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B_4.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B_5.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B_6.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B_7.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B_8.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B_9.root", 

					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E_0.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E_1.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E_2.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E_3.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E_4.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E_5.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E_6.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E_7.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E_8.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E_9.root",

					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G_0.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G_1.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G_2.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G_3.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G_4.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G_5.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G_6.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G_7.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G_8.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G_9.root", 

					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C_0.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C_1.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C_2.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C_3.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C_4.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C_5.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C_6.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C_7.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C_8.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C_9.root", 

					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1_0.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1_1.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1_2.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1_3.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1_4.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1_5.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1_6.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1_7.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1_8.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1_9.root", 

					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2_0.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2_1.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2_2.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2_3.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2_4.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2_5.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2_6.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2_7.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2_8.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2_9.root", 

					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D_0.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D_1.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D_2.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D_3.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D_4.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D_5.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D_6.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D_7.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D_8.root", 
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D_9.root", 
					
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2_0.root",  
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2_1.root",  
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2_2.root",  
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2_3.root",  
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2_4.root",  
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2_5.root",  
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2_6.root",  
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2_7.root",  
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2_8.root",  
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2_9.root",  
					
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3_0.root",
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3_1.root",
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3_2.root",
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3_3.root",
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3_4.root",
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3_5.root",
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3_6.root",
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3_7.root",
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3_8.root",
					"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3_9.root"
				};




	vector<string> shapeSystMaskDefault = {"default"};
	vector<string> shapeSystMask =  {
	 					"default",
	 					//"statRocCorError_UP",
	 					//"statRocCorError_DOWN",
	 					//"refRocCorError_UP",
	 					//"refRocCorError_DOWN",
	 					//"profMassRocCorError_UP",
	 					//"profMassRocCorError_DOWN",
	 					//"fitMassRocCorError_UP",
						//"fitMassRocCorError_DOWN",
						"RocCorError_UP",
						"RocCorError_DOWN",
						"phoScale_stat_UP",
	     				"phoScale_stat_DOWN",
				        "phoScale_syst_UP",
					    "phoScale_syst_DOWN",
					    "phoScale_gain_UP",
						"phoScale_gain_DOWN",
						"phoResol_rho_UP",
						"phoResol_rho_DOWN",
						"phoResol_phi_UP",
						"phoResol_phi_DOWN",
					};
	auto itShapeSystMaskDefault = shapeSystMaskDefault.begin();
	auto itShapeSystMask = shapeSystMask.begin();





	std::map<std::string, std::vector<std::string>>  ntuplesToPlotFilesMC_ZToUpsilon1SPhoton;
	std::map<std::string, std::vector<std::string>>  ntuplesToPlotFilesMC_ZToUpsilon2SPhoton;
	std::map<std::string, std::vector<std::string>>  ntuplesToPlotFilesMC_ZToUpsilon3SPhoton;

	itShapeSystMask = shapeSystMask.begin();
	while(itShapeSystMask != shapeSystMask.end()) {
		ntuplesToPlotFilesMC_ZToUpsilon1SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_ZToUpsilon2SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_ZToUpsilon3SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma_NLO_"+*itShapeSystMask+".root");
		itShapeSystMask++;
	}




	std::map<std::string, std::vector<std::string>>  ntuplesToPlotFilesMC_HToUpsilon1SPhoton;
	std::map<std::string, std::vector<std::string>>  ntuplesToPlotFilesMC_HToUpsilon2SPhoton;
	std::map<std::string, std::vector<std::string>>  ntuplesToPlotFilesMC_HToUpsilon3SPhoton;

	itShapeSystMask = shapeSystMask.begin();
	while(itShapeSystMask != shapeSystMask.end()) {
		ntuplesToPlotFilesMC_HToUpsilon1SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_VBFH_HToUps1SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon1SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_WmH_HToUps1SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon1SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_WpH_HToUps1SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon1SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZH_HToUps1SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon1SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ggH_HToUps1SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon1SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ttH_HToUps1SG_NLO_"+*itShapeSystMask+".root");
		
		ntuplesToPlotFilesMC_HToUpsilon2SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_VBFH_HToUps2SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon2SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_WmH_HToUps2SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon2SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_WpH_HToUps2SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon2SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZH_HToUps2SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon2SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ggH_HToUps2SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon2SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ttH_HToUps2SG_NLO_"+*itShapeSystMask+".root");
		
		ntuplesToPlotFilesMC_HToUpsilon3SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_VBFH_HToUps3SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon3SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_WmH_HToUps3SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon3SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_WpH_HToUps3SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon3SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZH_HToUps3SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon3SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ggH_HToUps3SG_NLO_"+*itShapeSystMask+".root");
		ntuplesToPlotFilesMC_HToUpsilon3SPhoton[*itShapeSystMask].push_back("/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ttH_HToUps3SG_NLO_"+*itShapeSystMask+".root");
		

		itShapeSystMask++;
	}


'''
# MuOnia
# fileHeader = '''
# {
# 	gSystem->AddIncludePath("-Iexternal");
# 	gSystem->SetBuildDir("tmpdir", kTRUE);
	
# 	gROOT->ProcessLine(".L plugins/getFilesList.C+");
# 	gROOT->ProcessLine(".L plots_ZtoUpsilonPhoton.C+"); 

# 	gStyle->SetOptStat(0);

# 	// system("rm -fr evtsCountFiles; mkdir evtsCountFiles");
	
# 	vector<string> ntuplesToPlotFilesData = {
# 						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B.root", 
# 						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C.root", 
# 						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D.root", 
# 						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E.root", 
# 						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F.root", 
# 						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G.root", 
# 						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H.root"
# 					};
# '''

fileBotton = '''
}

'''
############################################################
############################################################
## DUMMY
############################################################
############################################################
with open( "run_Plots_Dummy.C", "w") as fileDummy:
    fileDummy.write(fileHeader+fileBotton)


############################################################
############################################################
## Higgs - Cat0
############################################################
############################################################

# H - Cat0 - Data - J/Psi
# h_Cat0_Data_JPsi = '''
# 	// H - Cat0
# 	// Data - H
# 	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoJPsi", "Cat0"); // Data
# 	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoUpsilon", "Cat0"); // Data

# '''

# with open( "run_Plots_H_Cat0_Data_JPsi.C", "w") as fileH_Cat0_Data_JPsi:
#     fileH_Cat0_Data_JPsi.write(fileHeader+h_Cat0_Data_JPsi+fileBotton)


# H - Cat0 - Data - Upsilon
h_Cat0_Data_Upsilon = '''
	// H - Cat0
	// Data - H
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoJPsi", "Cat0"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoUpsilon", "Cat0"); // Data

'''
# H - Cat0
with open( "run_Plots_H_Cat0_Data_Upsilon.C", "w") as fileH_Cat0_Data_Upsilon:
    fileH_Cat0_Data_Upsilon.write(fileHeader+h_Cat0_Data_Upsilon+fileBotton)


# H - Cat0 - MC
h_Cat0_MC = '''
	// H - Cat0

	// MC - H
	itShapeSystMask = shapeSystMask.begin();
	while(itShapeSystMask != shapeSystMask.end()) {
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_HToUpsilon1SPhoton[*itShapeSystMask], "HToUpsilon1SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_HToUpsilon2SPhoton[*itShapeSystMask], "HToUpsilon2SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_HToUpsilon3SPhoton[*itShapeSystMask], "HToUpsilon3SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		// plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_HToJPsiGamma_"+*itShapeSystMask+".root"}, "HToJPsiGamma", "HtoJPsi", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		itShapeSystMask++;
	}
	while(itShapeSystMaskDefault != shapeSystMaskDefault.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_HDalitzNLO_"+*itShapeSystMaskDefault+".root"}, "HDalitz", "HtoUpsilon", "Cat0", "ZZZZZZ",  false, false); //MC
		// plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_HDalitzNLO_"+*itShapeSystMaskDefault+".root"}, "HDalitz", "HtoJPsi", "Cat0", "ZZZZZZ",  false, false); //MC
		itShapeSystMaskDefault++;
	}
'''
# H - Cat0
with open( "run_Plots_H_Cat0_MC.C", "w") as fileH_Cat0_MC:
    fileH_Cat0_MC.write(fileHeader+h_Cat0_MC+fileBotton)


############################################################
############################################################
## Z - Cat0
############################################################
############################################################

# Z - Cat0 - Data - J/Psi
# z_Cat0_Data_JPsi = '''
# 	// Z - Cat0				
# 	// Data - Z
# 	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat0"); // Data
# 	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat0"); // Data

# ''' 

# with open( "run_Plots_Z_Cat0_Data_JPsi.C", "w") as fileZ_Cat0_Data_JPsi:
#     fileZ_Cat0_Data_JPsi.write(fileHeader+z_Cat0_Data_JPsi+fileBotton)


# Z - Cat0 - Data - Upsilon
z_Cat0_Data_Upsilon = '''
	// Z - Cat0				
	// Data - Z
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat0"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat0"); // Data

'''


with open( "run_Plots_Z_Cat0_Data_Upsilon.C", "w") as fileZ_Cat0_Data_Upsilon:
    fileZ_Cat0_Data_Upsilon.write(fileHeader+z_Cat0_Data_Upsilon+fileBotton)

# Z - Cat0 - MC
z_Cat0_MC = '''
	// Z - Cat0				

	// MC - Z
	itShapeSystMask = shapeSystMask.begin();
	while(itShapeSystMask != shapeSystMask.end()) {
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon1SPhoton[*itShapeSystMask], "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ", false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon2SPhoton[*itShapeSystMask], "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon3SPhoton[*itShapeSystMask], "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		// plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma_"+*itShapeSystMask+".root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		itShapeSystMask++;
	}
	while(itShapeSystMaskDefault != shapeSystMaskDefault.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat0", "ZZZZZZ",  false, false); //MC
		// plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat0", "ZZZZZZ",  false, false); //MC
		itShapeSystMaskDefault++;
	}
'''

with open( "run_Plots_Z_Cat0_MC.C", "w") as fileZ_Cat0_MC:
    fileZ_Cat0_MC.write(fileHeader+z_Cat0_MC+fileBotton)


############################################################
############################################################
## Z - Cat1
############################################################
############################################################

# Z - Cat1 - Data - P/Psi
# z_Cat1_Data_JPsi = '''
# 	// Z - Cat1			
# 	// Data - Z
# 	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat1"); // Data
# 	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat1"); // Data

# '''


# with open( "run_Plots_Z_Cat1_Data_JPsi.C", "w") as fileZ_Cat1_Data_JPsi:
#     fileZ_Cat1_Data_JPsi.write(fileHeader+z_Cat1_Data_JPsi+fileBotton)


# Z - Cat1 - Data - Upsilon
z_Cat1_Data_Upsilon = '''
	// Z - Cat1			
	// Data - Z
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat1"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat1"); // Data

'''

with open( "run_Plots_Z_Cat1_Data_Upsilon.C", "w") as fileZ_Cat1_Data_Upsilon:
    fileZ_Cat1_Data_Upsilon.write(fileHeader+z_Cat1_Data_Upsilon+fileBotton)

# Z - Cat1 - mC
z_Cat1_MC = '''

	// Z - Cat1

	// MC - Z
	itShapeSystMask = shapeSystMask.begin();
	while(itShapeSystMask != shapeSystMask.end()) {
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon1SPhoton[*itShapeSystMask], "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ", false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon2SPhoton[*itShapeSystMask], "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon3SPhoton[*itShapeSystMask], "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		// plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma_"+*itShapeSystMask+".root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat1", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		itShapeSystMask++;
	}
	while(itShapeSystMaskDefault != shapeSystMaskDefault.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat1", "ZZZZZZ",  false, false); //MC
		// plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat1", "ZZZZZZ",  false, false); //MC
		itShapeSystMaskDefault++;
	}
'''

with open( "run_Plots_Z_Cat1_MC.C", "w") as fileZ_Cat1_MC:
    fileZ_Cat1_MC.write(fileHeader+z_Cat1_MC+fileBotton)


############################################################
############################################################
## Z - Cat2
############################################################
############################################################

# Z - Cat2 - Data - J/Psi
# z_Cat2_Data_JPsi = '''
# 	// Z - Cat2				
# 	// Data - Z
# 	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat2"); // Data
# 	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat2"); // Data

# '''

# with open( "run_Plots_Z_Cat2_Data_JPsi.C", "w") as fileZ_Cat2_Data_JPsi:
#     fileZ_Cat2_Data_JPsi.write(fileHeader+z_Cat2_Data_JPsi+fileBotton)

# Z - Cat2 - Data - Upsilon
z_Cat2_Data_Upsilon = '''
	// Z - Cat2				
	// Data - Z
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat2"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat2"); // Data

'''

with open( "run_Plots_Z_Cat2_Data_Upsilon.C", "w") as fileZ_Cat2_Data_Upsilon:
    fileZ_Cat2_Data_Upsilon.write(fileHeader+z_Cat2_Data_Upsilon+fileBotton)


# Z - Cat2 - MC
z_Cat2_MC = '''
	// Z - Cat2				

	// MC - Z
	itShapeSystMask = shapeSystMask.begin();
	while(itShapeSystMask != shapeSystMask.end()) {
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon1SPhoton[*itShapeSystMask], "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ", false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon2SPhoton[*itShapeSystMask], "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon3SPhoton[*itShapeSystMask], "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		// plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma_"+*itShapeSystMask+".root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat2", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		itShapeSystMask++;
	}
	while(itShapeSystMaskDefault != shapeSystMaskDefault.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat2", "ZZZZZZ",  false, false); //MC
		// plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat2", "ZZZZZZ",  false, false); //MC
		itShapeSystMaskDefault++;
	}
'''

with open( "run_Plots_Z_Cat2_MC.C", "w") as fileZ_Cat2_MC:
    fileZ_Cat2_MC.write(fileHeader+z_Cat2_MC+fileBotton)


############################################################
############################################################
## Z - Cat3
############################################################
############################################################
# Z - Cat3 - Data - J/Psi
# z_Cat3_Data_JPsi = '''
# 	// Z - Cat3			
# 	// Data - Z
# 	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat3"); // Data
# 	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat3"); // Data

# '''

# with open( "run_Plots_Z_Cat3_Data_JPsi.C", "w") as fileZ_Cat3_Data_JPsi:
#     fileZ_Cat3_Data_JPsi.write(fileHeader+z_Cat3_Data_JPsi+fileBotton)

# Z - Cat3 - Data - Upsilon
z_Cat3_Data_Upsilon = '''
	// Z - Cat3			
	// Data - Z
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat3"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat3"); // Data

'''

with open( "run_Plots_Z_Cat3_Data_Upsilon.C", "w") as fileZ_Cat3_Data_Upsilon:
    fileZ_Cat3_Data_Upsilon.write(fileHeader+z_Cat3_Data_Upsilon+fileBotton)

# Z - Cat3 - MC
z_Cat3_MC = '''
	// Z - Cat3		
	itShapeSystMask = shapeSystMask.begin();	
	while(itShapeSystMask != shapeSystMask.end()) {
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon1SPhoton[*itShapeSystMask], "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ", false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon2SPhoton[*itShapeSystMask], "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton(ntuplesToPlotFilesMC_ZToUpsilon3SPhoton[*itShapeSystMask], "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		// plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma_"+*itShapeSystMask+".root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat3", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		itShapeSystMask++;
	}
	while(itShapeSystMaskDefault != shapeSystMaskDefault.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat3", "ZZZZZZ",  false, false); //MC
		// plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat3", "ZZZZZZ",  false, false); //MC
		itShapeSystMaskDefault++;
	}
'''

with open( "run_Plots_Z_Cat3_MC.C", "w") as fileZ_Cat3_MC:
    fileZ_Cat3_MC.write(fileHeader+z_Cat3_MC+fileBotton)



