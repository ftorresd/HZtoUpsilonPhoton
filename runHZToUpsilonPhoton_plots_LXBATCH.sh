#!/bin/sh
echo "starting..."
date
user=`whoami`
# echo "mounting uerjpower..."
# sshfs uerjpowerp100:/storage1/ftorresd /afs/cern.ch/user/f/ftorresd/workSpace/public/UERJPower_Storage1/

echo "setuping CMSSW env..."
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc530
 
echo "cmsrel..."
cmsrel CMSSW_8_0_26_patch1
cd CMSSW_8_0_26_patch1/src
echo "copying from AFS..."
# cp -rv /afs/cern.ch/user/${user:0:1}/$user/workSpace/private/HZUpsilonPhoton2016/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton .
# rsync -av /afs/cern.ch/user/${user:0:1}/$user/workSpace/private/HZUpsilonPhoton2016/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton . --exclude outputFiles
rsync -av /afs/cern.ch/user/${user:0:1}/$user/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton . --exclude outputFiles


echo "cmsenv..."
cmsenv
echo "scram b..."
scram b


cd HZtoUpsilonPhoton
echo "cleanning..."
rm -rf  tmpdir/*
rm -rf evtsCountFiles/*
rm -rf outputHistos/*

echo "running..."
rm -rf evtsCountFiles/*
rm -rf outputHistos/*

rm run_Plots_Dummy.C
rm run_Plots_H_Cat0_Data_JPsi.C
rm run_Plots_H_Cat0_Data_Upsilon.C
rm run_Plots_H_Cat0_MC.C

rm run_Plots_Z_Cat0_Data_JPsi.C
rm run_Plots_Z_Cat0_Data_Upsilon.C
rm run_Plots_Z_Cat0_MC.C

rm run_Plots_Z_Cat1_Data_JPsi.C
rm run_Plots_Z_Cat1_Data_Upsilon.C
rm run_Plots_Z_Cat1_MC.C

rm run_Plots_Z_Cat2_Data_JPsi.C
rm run_Plots_Z_Cat2_Data_Upsilon.C
rm run_Plots_Z_Cat2_MC.C

rm run_Plots_Z_Cat3_Data_JPsi.C
rm run_Plots_Z_Cat3_Data_Upsilon.C
rm run_Plots_Z_Cat3_MC.C



python runZToUpsilonPhoton_plots.py


root -b -q -l run_Plots_Dummy.C+ 

root -b -q -l run_Plots_$1.C+


echo "copy - BEGIN"
# cp -r outputHistos/* /afs/cern.ch/user/${user:0:1}/$user/workSpace/private/HZUpsilonPhoton2016/CMSSW_8_0_26_patch1/src/outputHistos_FromLSF/.
cp -r outputHistos/* /afs/cern.ch/user/${user:0:1}/$user/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/outputHistos_FromLSF/.
# cp -r evtsCountFiles/* /afs/cern.ch/user/${user:0:1}/$user/workSpace/private/HZUpsilonPhoton2016/CMSSW_8_0_26_patch1/src/evtsCountFiles_FromLSF/.
cp -r evtsCountFiles/* /afs/cern.ch/user/${user:0:1}/$user/workSpace/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/evtsCountFiles_FromLSF/.
echo "copy - END"

# ls /afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/CMSSW_8_0_26_patch1/src/outTree_ZtoUpsilonPhoton_$2_$3.root
echo "finishing..."

date

exit 0