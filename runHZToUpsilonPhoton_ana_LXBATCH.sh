#!/bin/sh

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc530

cmsrel CMSSW_8_0_26_patch1
cd CMSSW_8_0_26_patch1/src
cp -r /afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/CMSSW_8_0_26_patch1/src/* .

cmsenv

scram b

cd HZtoUpsilonPhoton

./runHZToUpsilonPhoton_ana.py  >> /dev/null 2>&1

./runZToUpsilonPhoton_plots.sh  >> /dev/null 2>&1

./runZToUpsilonPhoton_plotter.sh  >> /dev/null 2>&1

ls

tar -zcvf outputFiles_LXBTACH.tar.gz outputFiles/ evtsCountFiles/ outputHistos/ outputPlots/

echo "tar..."
ls

echo "copy..."
cp outputFiles_LXBTACH.tar.gz /afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/CMSSW_8_0_26_patch1/src/outputFiles_LXBTACH_MuOnia_Nominal.tar.gz

ls /afs/cern.ch/user/f/ftorresd/workSpace/private/HZUpsilonPhoton2016/CMSSW_8_0_26_patch1/src/outputFiles_LXBTACH_MuOnia_Nominal.tar.gz

