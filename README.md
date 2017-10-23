# ZtoUpsilonPhoton
ZtoUpsilonPhoton @ CMS

## ggNtuples Code
https://github.com/cmkuo/ggAnalysis

### Recipe for ggNtuples Code
#### TAG: V08_00_26_07 (2016 Data)
```
cmsrel CMSSW_8_0_26_patch1
cd CMSSW_8_0_26_patch1/src 
cmsenv 
export CMSSW_GIT_REFERENCE=/cvmfs/cms.cern.ch/cmssw.git.daily 
git cms-init 
git remote add btv-cmssw https://github.com/cms-btv-pog/cmssw.git 
git fetch --tags btv-cmssw 
git cms-merge-topic -u cms-btv-pog:BoostedDoubleSVTaggerV4-WithWeightFiles-v1_from-CMSSW_8_0_21 
git cms-merge-topic rafaellopesdesa:RegressionCheckNegEnergy 
git cms-merge-topic cms-egamma:EGM_gain_v1 
cd EgammaAnalysis/ElectronTools/data 
git clone -b Moriond17_gainSwitch_unc https://github.com/ECALELFS/ScalesSmearings.git 
cd $CMSSW_BASE/src 
git cms-merge-topic cms-met:METRecipe_8020 -u 
git cms-merge-topic cms-met:METRecipe_80X_part2 -u 
git cms-merge-topic Sam-Harper:HEEPV70VID_8010_ReducedCheckout 
git cms-merge-topic Sam-Harper:PackedCandNoPuppi 
git cms-merge-topic ikrav:egm_id_80X_v2 
git cms-merge-topic ikrav:egm_id_80X_v3_photons 
git cms-merge-topic -u mverzett:DeepFlavour-from-CMSSW_8_0_21 
mkdir RecoBTag/DeepFlavour/data/ 
cd RecoBTag/DeepFlavour/data/ 
wget http://home.fnal.gov/~verzetti//DeepFlavour/training/DeepFlavourNoSL.json 
cd $CMSSW_BASE/src 
git clone https://github.com/cmkuo/HiggsAnalysis.git 
git clone -b V08_00_26_07 https://github.com/cmkuo/ggAnalysis.git 
scram b -j 20
```


#### TAG: V08_00_26_01 (2016 Data)
```
export SCRAM_ARCH=slc6_amd64_gcc530
cmsrel CMSSW_8_0_26_patch1
cd CMSSW_8_0_26_patch1/src 
cmsenv 


export CMSSW_GIT_REFERENCE="/cvmfs/cms.cern.ch/cmssw.git.daily"
git cms-init
git remote add btv-cmssw https://github.com/cms-btv-pog/cmssw.git
git fetch --tags btv-cmssw
git cms-merge-topic -u cms-btv-pog:BoostedDoubleSVTaggerV4-WithWeightFiles-v1_from-CMSSW_8_0_21



git cms-merge-topic rafaellopesdesa:EgammaAnalysis80_EGMSmearer_Moriond17_23Jan 
cd EgammaAnalysis/ElectronTools/data 
git clone git@github.com:ECALELFS/ScalesSmearings.git 
cd ../../../ 
git cms-merge-topic cms-met:METRecipe_8020 -u 
git cms-merge-topic cms-met:METRecipe_80X_part2 -u 

git cms-merge-topic Sam-Harper:HEEPV70VID_8010_ReducedCheckout #error


git cms-merge-topic Sam-Harper:PackedCandNoPuppi 
git cms-merge-topic ikrav:egm_id_80X_v2 
git cms-merge-topic ikrav:egm_id_80X_v3_photons 

git clone https://github.com/cmkuo/HiggsAnalysis.git 

git clone -b V08_00_26_01 https://github.com/cmkuo/ggAnalysis.git 

scram b -j 10 
```




## 2016 Samples
### MC 
- DAS: https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FZToUpsilon*SGamma-TuneCUETP8M1_13TeV-pythia8*%2F*%2FMINIAODSIM
- ggNutples: ???

## Data
- DAS: https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FMuonEG%2FRun2016*-03Feb2017*%2FMINIAOD
- ggNutples: /eos/cms/store/user/ftorresd/ggNtuples/13TeV/data/V08_00_26_06/
- More Info: https://docs.google.com/spreadsheets/d/1Fxy9KmV0Rirdl7Kjnc_KMNmqRhfwl9w1_5I0IWxaFYA/edit#gid=1329660137

| Sample       | NJobs           | Lumi (/fb)  | Location @ EOS  |
| ------------- |:-------------:| -----:| -----:|
| /MuonEG/Run2016B-03Feb2017_ver2-v2/MINIAOD |	1317 |	5.784 |	/eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V08_00_26_01/job_MuEG_Run2016B_FebReminiAOD |
| /MuonEG/Run2016C-03Feb2017-v1/MINIAOD |		435 |	2.573 |	/eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V08_00_26_01/job_MuEG_Run2016C_FebReminiAOD |
| /MuonEG/Run2016D-03Feb2017-v1/MINIAOD |	729 |	4.248 |	/eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V08_00_26_01/job_MuEG_Run2016D_FebReminiAOD |
| /MuonEG/Run2016E-03Feb2017-v1/MINIAOD |	620 |	4.009 |	/eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V08_00_26_01/job_MuEG_Run2016E_FebReminiAOD |
| /MuonEG/Run2016F-03Feb2017-v1/MINIAOD |	392 |	2.704 |	/eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V08_00_26_01/job_MuEG_Run2016F_FebReminiAOD1 |
| /MuonEG/Run2016F-03Feb2017-v1/MINIAOD |	61 |	0.397 |	/eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V08_00_26_01/job_MuEG_Run2016F_FebReminiAOD2 |
| /MuonEG/Run2016G-03Feb2017-v1/MINIAOD |	1068 |	7.54 |	/eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V08_00_26_01/job_MuEG_Run2016G_FebReminiAOD |
| /MuonEG/Run2016H-03Feb2017_ver2-v1/MINIAOD |	1156 |	8.391 |	/eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V08_00_26_01/job_MuEG_Run2016H_FebReminiAODv2 |
| /MuonEG/Run2016H-03Feb2017_ver3-v1/MINIAOD |	31 |	0.215 |	/eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V08_00_26_01/job_MuEG_Run2016H_FebReminiAODv3 |
