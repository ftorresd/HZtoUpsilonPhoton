#!/bin/bash

# time root -b -q -l run_Ana.C+

rm run_*temp*.C


run_Ana_template="{
	gSystem->AddIncludePath(\"-Iexternal\");
	gSystem->SetBuildDir(\"tmpdir\", kTRUE);
	gROOT->ProcessLine(\".L plugins/getFilesList.C+\");
	gROOT->ProcessLine(\".L ana_ZtoUpsilonPhoton.C+\"); 
	gStyle->SetOptStat(0);
 	___EXECSTRING___
}"

## DATA
totalEvts=-1
execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016B_FebReminiAOD.txt\") , 1, \"Run2016B\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp0.C 
# cat run_Ana_temp1.C 
root -b -q -l run_Ana_temp0.C+ 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016B_FebReminiAOD.txt\") , ${totalEvts}, \"Run2016B\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp1.C 
# cat run_Ana_temp1.C 
root -b -q -l run_Ana_temp1.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016C_FebReminiAOD.txt\"), ${totalEvts}, \"Run2016C\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp2.C  
# cat run_Ana_temp2.C 
root -b -q -l run_Ana_temp2.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016D_FebReminiAOD.txt\") , ${totalEvts}, \"Run2016D\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp3.C 
# cat run_Ana_temp3.C  
root -b -q -l run_Ana_temp3.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016E_FebReminiAOD.txt\"), ${totalEvts}, \"Run2016E\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp4.C 
# cat run_Ana_temp4.C  
root -b -q -l run_Ana_temp4.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016F_FebReminiAOD1.txt\"), ${totalEvts}, \"Run2016F1\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp5.C 
# cat run_Ana_temp5.C  
root -b -q -l run_Ana_temp5.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016F_FebReminiAOD2.txt\"), ${totalEvts}, \"Run2016F2\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp6.C 
# cat run_Ana_temp6.C  
root -b -q -l run_Ana_temp6.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016G_SepRereco.txt\"), ${totalEvts}, \"Run2016G\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp7.C  
# cat run_Ana_temp7.C 
root -b -q -l run_Ana_temp7.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016H_PRv2.txt\"), ${totalEvts}, \"Run2016H2\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp8.C 
# cat run_Ana_temp8.C 
root -b -q -l run_Ana_temp8.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/Data2016/job_MuEG_Run2016H_PRv3.txt\"), ${totalEvts}, \"Run2016H3\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp9.C  
# cat run_Ana_temp9.C 
root -b -q -l run_Ana_temp9.C+ & 
# sleep 1


# # MC
# # Z
# totalEvts=-1
# # execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon1SGamma.txt\"), 1, \"ZToUpsilon1SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon1SGamma.txt\"), 1, \"ZToUpsilon1SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
# echo "$run_Ana" > run_Ana_temp10.C  
# root -b -q -l run_Ana_temp10.C+ 

# # execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon1SGamma.txt\"), -1, \"ZToUpsilon1SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon1SGamma.txt\"), -1, \"ZToUpsilon1SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
# echo "$run_Ana" > run_Ana_temp11.C  
# root -b -q -l run_Ana_temp11.C+ & 

# # execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon2SGamma.txt\"), -1, \"ZToUpsilon2SGamma\", true, \"puWeight/puWeights_ZToUpsilon2SGamma.root\");"
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon2SGamma.txt\"), -1, \"ZToUpsilon2SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
# echo "$run_Ana" > run_Ana_temp12.C  
# root -b -q -l run_Ana_temp12.C+ & 

# # execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon3SGamma.txt\"), -1, \"ZToUpsilon3SGamma\", true, \"puWeight/puWeights_ZToUpsilon3SGamma.root\");"
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon3SGamma.txt\"), -1, \"ZToUpsilon3SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
# echo "$run_Ana" > run_Ana_temp13.C  
# root -b -q -l run_Ana_temp13.C+ & 


# # execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToJPsiGamma.txt.txt\"), -1, \"ZToJPsiGamma\", true, \"puWeight/puWeights_ZToJPsiGamma.root\");"
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToJPsiGamma.txt\"), -1, \"ZToJPsiGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
# echo "$run_Ana" > run_Ana_temp14.C  
# root -b -q -l run_Ana_temp14.C+ & 


# # Higgs
# # execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon1SGamma.txt\"), -1, \"HToUpsilon1SGamma\", true, \"puWeight/puWeights_HToUpsilon1SGamma.root\");"
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon1SGamma.txt\"), -1, \"HToUpsilon1SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
# echo "$run_Ana" > run_Ana_temp15.C  
# root -b -q -l run_Ana_temp15.C+ & 

# # execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon2SGamma.txt\"), -1, \"HToUpsilon2SGamma\", true, \"puWeight/puWeights_HToUpsilon2SGamma.root\");"
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon2SGamma.txt\"), -1, \"HToUpsilon2SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
# echo "$run_Ana" > run_Ana_temp16.C  
# root -b -q -l run_Ana_temp16.C+ & 

# # execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon3SGamma.txt\"), -1, \"HToUpsilon3SGamma\", true, \"puWeight/puWeights_HToUpsilon3SGamma.root\");"
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon3SGamma.txt\"), -1, \"HToUpsilon3SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
# echo "$run_Ana" > run_Ana_temp17.C  
# root -b -q -l run_Ana_temp17.C+ & 

# # execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToJPsiGamma.txt\"), -1, \"HToJPsiGamma\", true, \"puWeight/puWeights_HToJPsiGamma.root\");"
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToJPsiGamma.txt\"), -1, \"HToJPsiGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
# echo "$run_Ana" > run_Ana_temp18.C  
# root -b -q -l run_Ana_temp18.C+ & 


# # execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HDalitz.txt\"), -1, \"HDalitz\", true, \"puWeight/puWeights_HDalitz.root\");"
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HDalitz.txt\"), -1, \"HDalitz\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
# echo "$run_Ana" > run_Ana_temp19.C  
# root -b -q -l run_Ana_temp19.C+ & 

# # execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZGTo2MuG_MMuMu-2To15.txt\"), -1, \"ZGTo2MuG_MMuMu-2To15\", true, \"puWeight/puWeights_ZGTo2MuG_MMuMu-2To15.root\");"
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZGTo2MuG_MMuMu-2To15.txt\"), -1, \"ZGTo2MuG_MMuMu-2To15\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
# echo "$run_Ana" > run_Ana_temp20.C  
# root -b -q -l run_Ana_temp20.C+ & 





wait
rm run_Ana_temp*.C

echo "Done!"