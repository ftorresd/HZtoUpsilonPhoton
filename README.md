# ZtoUpsilonPhoton
ZtoUpsilonPhoton @ CMS

## Analysis Code

### Setup
```
cmsrel CMSSW_8_0_26_patch1
cd CMSSW_8_0_26_patch1/src
git clone git@github.com:ftorresd/HZtoUpsilonPhoton.git
cd HZtoUpsilonPhoton/
git checkout 2016Data
chmod +x setup.sh
./setup.sh
```

### Pushing
After ```git add``` and ```git commit -m```:
```
git push origin 2016Data
```

### Analysis Workflow
Produce HZToUpsilonGGNtuples (after propper configurarion for MC or Data):
```
./runZToUpsilonPhoton_ana.sh
```

Produce Histograms and TTres for fitting:
```
./runZToUpsilonPhoton_plots.sh
```

Produce plots:
```
./runZToUpsilonPhoton_plotter.sh
```

Fitting:
```
cd fits
./runHZToUpsilonPhoton_fitter.sh
```


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

Maybe one or two more ```scram b -j 20``` might be required in order to get clean compilation process.



## 2016 Samples
### MC 
- **CMS DAS:** https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FZToUpsilon*SGamma-TuneCUETP8M1_13TeV-pythia8*%2F*%2FMINIAODSIM
- **ggNutples:**

| **Sample**         | **Location @ EOS**  |
| ------- |:-------|
| ```/ZToUpsilon3SGamma-TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM```   |	```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/ZToUpsilon1SGamma_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_ggNtuples_V08_00_26_07_Upsilon_v06``` |
| ```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/ZToUpsilon2SGamma_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_ggNtuples_V08_00_26_07_Upsilon_v06```   |	```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/MuonEG_Run2016C-03Feb2017-v1_MINIAOD_ggNtuples_V08_00_26_07_v11/``` |
| ```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/ZToUpsilon3SGamma_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_ggNtuples_V08_00_26_07_Upsilon_v06```   |		```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/MuonEG_Run2016C-03Feb2017-v1_MINIAOD_ggNtuples_V08_00_26_07_v11/``` |

| **Sample**         | **xSec (pb)(*)**  | **Filter Efficiency(*)**  |  **Filter Efficiency Error(*)**  |
| ------ |:--------:|:-------:|:------:|
| ```ZToUpsilon1SGamma```   |	2.022 | 0.7222 | 0.03733 |
| ```ZToUpsilon2SGamma```   |	2.071 | 0.6667 | 0.04811 |
| ```ZToUpsilon3SGamma```   |	1.696 | 0.6146 | 0.04967 |

**(*)**: From McM (https://cms-pdmv.cern.ch/mcm/requests?prepid=SMP-RunIISummer15GS-00178&page=0&shown=127; https://cms-pdmv.cern.ch/mcm/requests?prepid=SMP-RunIISummer15GS-00179&page=0&shown=127; https://cms-pdmv.cern.ch/mcm/requests?prepid=SMP-RunIISummer15GS-00180&page=0&shown=127). 




## Data
- **CMS DAS:** https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FMuonEG%2FRun2016*-03Feb2017*%2FMINIAOD
- **JSON ([Ref](https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2016Analysis#Re_reco_datasets)):** https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt
- **ggNutples:**

| **Sample**      | **Dataset Lumi (/fb)** | **Processed Lumi (/fb)**   | **Location @ EOS**  |
| ------------- |:-------------:|:-------------:| :-----| 
| ```/MuonEG/Run2016B-03Feb2017_ver2-v2/MINIAOD```  | 6.133 |	2.925 |	```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/MuonEG_Run2016B-03Feb2017_ver2-v2_MINIAOD_ggNtuples_V08_00_26_07_v11/``` |
| ```/MuonEG/Run2016C-03Feb2017-v1/MINIAOD```  | 2.752 |	1.082 |	```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/MuonEG_Run2016C-03Feb2017-v1_MINIAOD_ggNtuples_V08_00_26_07_v11/``` |
| ```/MuonEG/Run2016D-03Feb2017-v1/MINIAOD```  | 4.395 |	1.436 |	```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/MuonEG_Run2016D-03Feb2017-v1_MINIAOD_ggNtuples_V08_00_26_07_v11/``` |
| ```/MuonEG/Run2016E-03Feb2017-v1/MINIAOD```  | 4.244 |	2.127 |	```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/MuonEG_Run2016E-03Feb2017-v1_MINIAOD_ggNtuples_V08_00_26_07_v11/``` |
| ```/MuonEG/Run2016F-03Feb2017-v1/MINIAOD```  | 3.180 |	1.161 |	```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/MuonEG_Run2016F-03Feb2017-v1_MINIAOD_ggNtuples_V08_00_26_07_v11/``` |
| ```/MuonEG/Run2016G-03Feb2017-v1/MINIAOD```  | 7.758 |	3.935 |	```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/MuonEG_Run2016G-03Feb2017-v1_MINIAOD_ggNtuples_V08_00_26_07_v11/``` |
| ```/MuonEG/Run2016H-03Feb2017_ver2-v1/MINIAOD```  | 8.777 |	4.528 |	```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/MuonEG_Run2016H-03Feb2017_ver2-v1_MINIAOD_ggNtuples_V08_00_26_07_v11/``` |
| ```/MuonEG/Run2016H-03Feb2017_ver3-v1/MINIAOD```  | 0.217 |	0.142 |	```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/MuonEG_Run2016H-03Feb2017_ver3-v1_MINIAOD_ggNtuples_V08_00_26_07_v11/``` |
| **Total Recorded Lumi:**  |	37.456 /fb |	17.336 /fb |	  |

- **ATTENTION: To be understood.**
  - **brilcalc command used:**
```brilcalc lumi -u /fb --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json -i [...]processedLumis.json```

  - **it should be ([ref](https://twiki.cern.ch/twiki/bin/view/CMS/TWikiLUM)):**
```brilcalc lumi -u /fb --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json -i [...]processedLumis.json```

- **ggNtuples Production Workspace Backup:** ```/eos/cms/store/user/ftorresd/ZtoUpsilonPhoton2016/ggNtuplizer_CMSSW_8_0_26_patch1_V08_00_26_07.tar.gz```

  
- **Other ggNtuples versions:** https://docs.google.com/spreadsheets/d/1Fxy9KmV0Rirdl7Kjnc_KMNmqRhfwl9w1_5I0IWxaFYA/edit#gid=1329660137

