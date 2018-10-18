#!/bin/bash

cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_2_0_pre6/src
cmsenv
cd -

./reweightingNLOSFHistos.py
