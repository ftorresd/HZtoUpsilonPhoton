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
	
	/*
	vector<string> ntuplesToPlotFilesData = {
						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016B.root", 
						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016E.root", 
						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016G.root", 
						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016C.root", 
						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1.root", 
						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2.root", 
						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016D.root", 
						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2.root",  
						"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3.root"
					};
	*/
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
# Dummy
with open( "run_Plots_Dummy.C", "w") as fileDummy:
    fileDummy.write(fileHeader+fileBotton)


h_Cat0_Data_JPsi = '''
	// H - Cat0
	// Data - H
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoJPsi", "Cat0"); // Data
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoUpsilon", "Cat0"); // Data

'''
# H - Cat0
with open( "run_Plots_H_Cat0_Data_JPsi.C", "w") as fileH_Cat0_Data_JPsi:
    fileH_Cat0_Data_JPsi.write(fileHeader+h_Cat0_Data_JPsi+fileBotton)

h_Cat0_Data_Upsilon = '''
	// H - Cat0
	// Data - H
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoJPsi", "Cat0"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoUpsilon", "Cat0"); // Data

'''
# H - Cat0
with open( "run_Plots_H_Cat0_Data_Upsilon.C", "w") as fileH_Cat0_Data_Upsilon:
    fileH_Cat0_Data_Upsilon.write(fileHeader+h_Cat0_Data_Upsilon+fileBotton)

h_Cat0_MC = '''
	// H - Cat0

	// MC - H
	while(itShapeSystMask != shapeSystMask.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon1SGamma_"+*itShapeSystMask+".root"}, "HToUpsilon1SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon2SGamma_"+*itShapeSystMask+".root"}, "HToUpsilon2SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon3SGamma_"+*itShapeSystMask+".root"}, "HToUpsilon3SGamma", "HtoUpsilon", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_HToJPsiGamma_"+*itShapeSystMask+".root"}, "HToJPsiGamma", "HtoJPsi", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		itShapeSystMask++;
	}
	while(itShapeSystMaskDefault != shapeSystMaskDefault.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_HDalitz_"+*itShapeSystMaskDefault+".root"}, "HDalitz", "HtoJPsi", "Cat0", "ZZZZZZ",  false, false); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_HDalitz_"+*itShapeSystMaskDefault+".root"}, "HDalitz", "HtoUpsilon", "Cat0", "ZZZZZZ",  false, false); //MC
		itShapeSystMaskDefault++;
	}
'''
# H - Cat0
with open( "run_Plots_H_Cat0_MC.C", "w") as fileH_Cat0_MC:
    fileH_Cat0_MC.write(fileHeader+h_Cat0_MC+fileBotton)


z_Cat0_Data_JPsi = '''
	// Z - Cat0				
	// Data - Z
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat0"); // Data
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat0"); // Data

''' 

# Z - Cat0
with open( "run_Plots_Z_Cat0_Data_JPsi.C", "w") as fileZ_Cat0_Data_JPsi:
    fileZ_Cat0_Data_JPsi.write(fileHeader+z_Cat0_Data_JPsi+fileBotton)

z_Cat0_Data_Upsilon = '''
	// Z - Cat0				
	// Data - Z
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat0"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat0"); // Data

'''

# Z - Cat0
with open( "run_Plots_Z_Cat0_Data_Upsilon.C", "w") as fileZ_Cat0_Data_Upsilon:
    fileZ_Cat0_Data_Upsilon.write(fileHeader+z_Cat0_Data_Upsilon+fileBotton)


z_Cat0_MC = '''
	// Z - Cat0				

	// MC - Z
	while(itShapeSystMask != shapeSystMask.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ", false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma_"+*itShapeSystMask+".root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat0", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		itShapeSystMask++;
	}
	while(itShapeSystMaskDefault != shapeSystMaskDefault.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat0", "ZZZZZZ",  false, false); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat0", "ZZZZZZ",  false, false); //MC
		itShapeSystMaskDefault++;
	}
'''

# Z - Cat0
with open( "run_Plots_Z_Cat0_MC.C", "w") as fileZ_Cat0_MC:
    fileZ_Cat0_MC.write(fileHeader+z_Cat0_MC+fileBotton)

z_Cat1_Data_JPsi = '''
	// Z - Cat1			
	// Data - Z
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat1"); // Data
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat1"); // Data

'''

# Z - Cat1
with open( "run_Plots_Z_Cat1_Data_JPsi.C", "w") as fileZ_Cat1_Data_JPsi:
    fileZ_Cat1_Data_JPsi.write(fileHeader+z_Cat1_Data_JPsi+fileBotton)

z_Cat1_Data_Upsilon = '''
	// Z - Cat1			
	// Data - Z
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat1"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat1"); // Data

'''

# Z - Cat1
with open( "run_Plots_Z_Cat1_Data_Upsilon.C", "w") as fileZ_Cat1_Data_Upsilon:
    fileZ_Cat1_Data_Upsilon.write(fileHeader+z_Cat1_Data_Upsilon+fileBotton)


z_Cat1_MC = '''
	// Z - Cat1			

	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat1"); // Data
	// MC - Z
	while(itShapeSystMask != shapeSystMask.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ", false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat1", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma_"+*itShapeSystMask+".root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat1", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		itShapeSystMask++;
	}
	while(itShapeSystMaskDefault != shapeSystMaskDefault.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat1", "ZZZZZZ",  false, false); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat1", "ZZZZZZ",  false, false); //MC
		itShapeSystMaskDefault++;
	}
'''

# Z - Cat1
with open( "run_Plots_Z_Cat1_MC.C", "w") as fileZ_Cat1_MC:
    fileZ_Cat1_MC.write(fileHeader+z_Cat1_MC+fileBotton)

z_Cat2_Data_JPsi = '''
	// Z - Cat2				
	// Data - Z
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat2"); // Data
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat2"); // Data

'''

# Z - Cat2
with open( "run_Plots_Z_Cat2_Data_JPsi.C", "w") as fileZ_Cat2_Data_JPsi:
    fileZ_Cat2_Data_JPsi.write(fileHeader+z_Cat2_Data_JPsi+fileBotton)


z_Cat2_Data_Upsilon = '''
	// Z - Cat2				
	// Data - Z
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat2"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat2"); // Data

'''

# Z - Cat2
with open( "run_Plots_Z_Cat2_Data_Upsilon.C", "w") as fileZ_Cat2_Data_Upsilon:
    fileZ_Cat2_Data_Upsilon.write(fileHeader+z_Cat2_Data_Upsilon+fileBotton)


z_Cat2_MC = '''
	// Z - Cat2				

	// MC - Z
	while(itShapeSystMask != shapeSystMask.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ", false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat2", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma_"+*itShapeSystMask+".root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat2", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		itShapeSystMask++;
	}
	while(itShapeSystMaskDefault != shapeSystMaskDefault.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat2", "ZZZZZZ",  false, false); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat2", "ZZZZZZ",  false, false); //MC
		itShapeSystMaskDefault++;
	}
'''

# Z - Cat2
with open( "run_Plots_Z_Cat2_MC.C", "w") as fileZ_Cat2_MC:
    fileZ_Cat2_MC.write(fileHeader+z_Cat2_MC+fileBotton)


z_Cat3_Data_JPsi = '''
	// Z - Cat3			
	// Data - Z
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat3"); // Data
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat3"); // Data

'''

# Z - Cat3
with open( "run_Plots_Z_Cat3_Data_JPsi.C", "w") as fileZ_Cat3_Data_JPsi:
    fileZ_Cat3_Data_JPsi.write(fileHeader+z_Cat3_Data_JPsi+fileBotton)

z_Cat3_Data_Upsilon = '''
	// Z - Cat3			
	// Data - Z
	//plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat3"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat3"); // Data

'''

# Z - Cat3
with open( "run_Plots_Z_Cat3_Data_Upsilon.C", "w") as fileZ_Cat3_Data_Upsilon:
    fileZ_Cat3_Data_Upsilon.write(fileHeader+z_Cat3_Data_Upsilon+fileBotton)


z_Cat3_MC = '''
	// Z - Cat3			
	while(itShapeSystMask != shapeSystMask.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ", false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma_"+*itShapeSystMask+".root"}, "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat3", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma_"+*itShapeSystMask+".root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat3", "ZZZZZZ",  false, true, *itShapeSystMask); //MC
		itShapeSystMask++;
	}
	while(itShapeSystMaskDefault != shapeSystMaskDefault.end()) {
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat3", "ZZZZZZ",  false, false); //MC
		plots_ZtoUpsilonPhoton({"/afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton/outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15_"+*itShapeSystMaskDefault+".root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat3", "ZZZZZZ",  false, false); //MC
		itShapeSystMaskDefault++;
	}
'''

# Z - Cat3
with open( "run_Plots_Z_Cat3_MC.C", "w") as fileZ_Cat3_MC:
    fileZ_Cat3_MC.write(fileHeader+z_Cat3_MC+fileBotton)

