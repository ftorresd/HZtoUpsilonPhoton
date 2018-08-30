#!/bin/bash

cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_2_1/
cmsenv
cd -

./reweightingNLOSFHistos.py
