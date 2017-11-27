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

# DATA
execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/job_MuEG_Run2016B_FebReminiAOD.txt\") , 1, \"Run2016B\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp0.C 
# cat run_Ana_temp1.C 
root -b -q -l run_Ana_temp0.C+ 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/job_MuEG_Run2016B_FebReminiAOD.txt\") , -1, \"Run2016B\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp1.C 
# cat run_Ana_temp1.C 
root -b -q -l run_Ana_temp1.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/job_MuEG_Run2016C_FebReminiAOD.txt\"), -1, \"Run2016C\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp2.C  
# cat run_Ana_temp2.C 
root -b -q -l run_Ana_temp2.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/job_MuEG_Run2016D_FebReminiAOD.txt\") , -1, \"Run2016D\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp3.C 
# cat run_Ana_temp3.C  
root -b -q -l run_Ana_temp3.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/job_MuEG_Run2016E_FebReminiAOD.txt\"), -1, \"Run2016E\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp4.C 
# cat run_Ana_temp4.C  
root -b -q -l run_Ana_temp4.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/job_MuEG_Run2016F_FebReminiAOD1.txt\"), -1, \"Run2016F1\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp5.C 
# cat run_Ana_temp5.C  
root -b -q -l run_Ana_temp5.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/job_MuEG_Run2016F_FebReminiAOD2.txt\"), -1, \"Run2016F2\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp6.C 
# cat run_Ana_temp6.C  
root -b -q -l run_Ana_temp6.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/job_MuEG_Run2016G_SepRereco.txt\"), -1, \"Run2016G\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp7.C  
# cat run_Ana_temp7.C 
root -b -q -l run_Ana_temp7.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/job_MuEG_Run2016H_PRv2.txt\"), -1, \"Run2016H2\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp8.C 
# cat run_Ana_temp8.C 
root -b -q -l run_Ana_temp8.C+ & 
# sleep 1

execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/job_MuEG_Run2016H_PRv3.txt\"), -1, \"Run2016H3\");"
run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" 
echo "$run_Ana" > run_Ana_temp9.C  
# cat run_Ana_temp9.C 
root -b -q -l run_Ana_temp9.C+ & 
# sleep 1


# MC
# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/ZToUpsilon1SGamma_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV.txt\"), -1, \"ZToUpsilon1SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" ; echo "$run_Ana" > run_Ana_temp.C ; root -b -q -l run_Ana_temp.C+ & ; sleep 1

# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/ZToUpsilon2SGamma_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV.txt\"), -1, \"ZToUpsilon2SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" ; echo "$run_Ana" > run_Ana_temp.C ; root -b -q -l run_Ana_temp.C+ & ; sleep 1

# execString="ana_ZtoUpsilonPhoton(getFilesList(\"filesLists/ZToUpsilon3SGamma_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV.txt\"), -1, \"ZToUpsilon3SGamma\", true, \"puWeight/puWeights_ZToUpsilon1SGamma.root\");"
# run_Ana="${run_Ana_template/___EXECSTRING___/$execString}" ; echo "$run_Ana" > run_Ana_temp.C ; root -b -q -l run_Ana_temp.C+ & ; sleep 1


wait
rm run_Ana_temp*.C

echo "Done!"