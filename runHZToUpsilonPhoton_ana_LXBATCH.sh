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
cp -r /afs/cern.ch/work/f/ftorresd/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/HZtoUpsilonPhoton .
	
echo "cmsenv..."
cmsenv
echo "scram b..."
scram b


cd HZtoUpsilonPhoton
echo "cleanning..."
rm -rf  tmpdir/*
rm -rf outputFiles/*

echo "running..."
./runHZToUpsilonPhoton_ana.py $1 $2 $3

# ./runZToUpsilonPhoton_plots.sh  

# ./runZToUpsilonPhoton_plotter.sh  

# ls

# echo "tar - BEGIN"
# # tar -zcvf outputFiles_LXBTACH.tar.gz outputFiles/ evtsCountFiles/ outputHistos/ outputPlots/
# tar -zcvf outputFiles_LXBTACH_$2_$3.tar.gz outputFiles/
# echo "tar - END"

# ls

echo "copy - BEGIN"
cp outputFiles/outTree_ZtoUpsilonPhoton_$2_$3.root /afs/cern.ch/work/f/ftorresd/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/.
# cp outputFiles_LXBTACH_$2_$3.tar.gz /afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/CMSSW_8_0_26_patch1/src/.
echo "copy - END"

ls /afs/cern.ch/work/f/ftorresd/private/HZUpsilonPhoton2016/Fit2D/CMSSW_8_0_26_patch1/src/outTree_ZtoUpsilonPhoton_$2_$3.root
echo "finishing..."
echo $1
echo $2
echo $3
date

exit 0