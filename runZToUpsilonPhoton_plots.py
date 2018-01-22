#!/usr/bin/env python

fileHeader = '''
{
	gSystem->AddIncludePath("-Iexternal");
	gSystem->SetBuildDir("tmpdir", kTRUE);
	
	gROOT->ProcessLine(".L plugins/getFilesList.C+");
	gROOT->ProcessLine(".L plots_ZtoUpsilonPhoton.C+"); 

	gStyle->SetOptStat(0);

	// system("rm -fr evtsCountFiles; mkdir evtsCountFiles");
	
	vector<string> ntuplesToPlotFilesData = {
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016B.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016E.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016G.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016C.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016F1.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016H2.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016D.root", 
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016F2.root",  
						"outputFiles/outTree_ZtoUpsilonPhoton_Run2016H3.root"
					};
'''

fileBotton = '''
}

'''

h_Cat0 = '''
	// H - Cat0
	// // Data - H
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoJPsi", "Cat0"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "HtoUpsilon", "Cat0"); // Data
	// // MC - H
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon1SGamma.root"}, "HToUpsilon1SGamma", "HtoUpsilon", "Cat0", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon2SGamma.root"}, "HToUpsilon2SGamma", "HtoUpsilon", "Cat0", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToUpsilon3SGamma.root"}, "HToUpsilon3SGamma", "HtoUpsilon", "Cat0", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HToJPsiGamma.root"}, "HToJPsiGamma", "HtoJPsi", "Cat0", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HDalitz.root"}, "HDalitz", "HtoJPsi", "Cat0", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_HDalitz.root"}, "HDalitz", "HtoUpsilon", "Cat0", "ZZZZZ",  false); //MC

'''

z_Cat0 = '''
	// Z - Cat0				
	// Data - Z
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat0"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat0"); // Data
	// MC - Z
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root"}, "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat0", "ZZZZZ", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root"}, "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat0", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"}, "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat0", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma.root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat0", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat0", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat0", "ZZZZZ",  false); //MC

'''

z_Cat1 = '''
	// Z - Cat1			
	// Data - Z
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat1"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat1"); // Data
	// MC - Z
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root"}, "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat1", "ZZZZZ", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root"}, "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat1", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"}, "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat1", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma.root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat1", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat1", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat1", "ZZZZZ",  false); //MC

'''

z_Cat2 = '''
	// Z - Cat2				
	// Data - Z
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat2"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat2"); // Data
	// MC - Z
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root"}, "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat2", "ZZZZZ", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root"}, "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat2", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"}, "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat2", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma.root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat2", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat2", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat2", "ZZZZZ",  false); //MC

'''

z_Cat3 = '''
	// Z - Cat3			
	// Data - Z
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoJPsi", "Cat3"); // Data
	plots_ZtoUpsilonPhoton(ntuplesToPlotFilesData, "Data", "ZtoUpsilon", "Cat3"); // Data
	// MC - Z
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root"}, "ZToUpsilon1SGamma", "ZtoUpsilon", "Cat3", "ZZZZZ", false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon2SGamma.root"}, "ZToUpsilon2SGamma", "ZtoUpsilon", "Cat3", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToUpsilon3SGamma.root"}, "ZToUpsilon3SGamma", "ZtoUpsilon", "Cat3", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZToJPsiGamma.root"}, "ZToJPsiGamma", "ZtoJPsi", "Cat3", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoUpsilon", "Cat3", "ZZZZZ",  false); //MC
	plots_ZtoUpsilonPhoton({"outputFiles/outTree_ZtoUpsilonPhoton_ZGTo2MuG_MMuMu-2To15.root"}, "ZGTo2MuG_MMuMu-2To15", "ZtoJPsi", "Cat3", "ZZZZZ",  false); //MC

'''

# Dummy
with open( "run_Plots_Dummy.C", "w") as fileDummy:
    fileDummy.write(fileHeader+fileBotton)

# H - Cat0
with open( "run_Plots_H_Cat0.C", "w") as fileH_Cat0:
    fileH_Cat0.write(fileHeader+h_Cat0+fileBotton)

# Z - Cat0
with open( "run_Plots_Z_Cat0.C", "w") as fileZ_Cat0:
    fileZ_Cat0.write(fileHeader+z_Cat0+fileBotton)

# Z - Cat1
with open( "run_Plots_Z_Cat1.C", "w") as fileZ_Cat1:
    fileZ_Cat1.write(fileHeader+z_Cat1+fileBotton)

# Z - Cat2
with open( "run_Plots_Z_Cat2.C", "w") as fileZ_Cat2:
    fileZ_Cat2.write(fileHeader+z_Cat2+fileBotton)

# Z - Cat3
with open( "run_Plots_Z_Cat3.C", "w") as fileZ_Cat3:
    fileZ_Cat3.write(fileHeader+z_Cat3+fileBotton)




