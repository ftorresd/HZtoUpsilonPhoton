# ZtoUpsilonPhoton
ZtoUpsilonPhoton @ CMS

## Analysis Code
```
cmsrel CMSSW_8_0_26_patch1
cd CMSSW_8_0_26_patch1/src
git clone git@github.com:ftorresd/ZtoUpsilonPhoton.git
cd ZtoUpsilonPhoton/
git checkout 2017Data
```

## ggNtuples Code
https://github.com/cmkuo/ggAnalysis/tree/92X

### Recipe for ggNtuples Code
#### BRANCH: 92X (2017 Data)
```
cmsrel CMSSW_9_2_9

cd CMSSW_9_2_9/src 
cmsenv 
export CMSSW_GIT_REFERENCE=/cvmfs/cms.cern.ch/cmssw.git.daily 
git cms-init 

git cms-addpkg RecoEgamma/EgammaIsolationAlgos 
git cms-merge-topic rgoldouz:TrkIsoFix -u 
git clone https://github.com/cmkuo/HiggsAnalysis.git 
git clone -b 92X https://github.com/cmkuo/ggAnalysis.git 

scram b -j 20
```

Maybe one or two more ```scram b -j 20``` might be required in order to get clean compilation process.

## ggNtuples Code
https://github.com/cmkuo/ggAnalysis/tree/94X

### Recipe for ggNtuples Code
#### BRANCH: 94X (2017 Data)
```
cd CMSSW_9_4_4/src 
cmsenv 
git cms-init 
git cms-merge-topic lsoffi:CMSSW_9_4_0_pre3_TnP 
git cms-merge-topic guitargeek:ElectronID_MVA2017_940pre3 
scram b -j8 
cd $CMSSW_BASE/external/slc6_amd64_gcc630 
git clone https://github.com/lsoffi/RecoEgamma-PhotonIdentification.git data/RecoEgamma/PhotonIdentification/data 
cd data/RecoEgamma/PhotonIdentification/data 
git checkout CMSSW_9_4_0_pre3_TnP 
cd $CMSSW_BASE/external/slc6_amd64_gcc630/ 
git clone https://github.com/lsoffi/RecoEgamma-ElectronIdentification.git data/RecoEgamma/ElectronIdentification/data 
cd data/RecoEgamma/ElectronIdentification/data 
git checkout CMSSW_9_4_0_pre3_TnP 
cd $CMSSW_BASE/src 
git cms-merge-topic cms-egamma:EGM_94X_v1 
cd EgammaAnalysis/ElectronTools/data 
git clone https://github.com/ECALELFS/ScalesSmearings.git 
cd ScalesSmearings/ 
git checkout Run2017_17Nov2017_v1 
cd $CMSSW_BASE/src 
git clone https://github.com/cmkuo/HiggsAnalysis.git 
git clone -b 94X https://github.com/cmkuo/ggAnalysis.git 
scram b -j8 

```


## 2017 Samples
### MC 
- **CMS DAS:** 
**signal Z :** https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FZToUpsilon1SGamma-TuneCP5_13TeV-pythia8*%2F*%2FMINIAODSIM
** signal H :** https://cms-pdmv.cern.ch/mcm/requests?page=0&dataset_name=HToUpsilon*SG_ToMuMuG_allProdMode_M125_TuneCP5_13TeV_Pythia8
** bckg Z: ** https://cms-pdmv.cern.ch/mcm/requests?page=0&dataset_name=ZGTo2MuG_MMuMu-2To15_*&shown=274877907071
** bckg H: ** 

- **ggNutples:**:

| **Sample**         | **Location @ EOS**  |
| ------- |:-------|
| ```/ZToUpsilon1SGamma-TuneCP5_13TeV-pythia8/*/MINIAODSIM```   |	root://131.225.204.161:1094//store/user/eliza/ggNtuples2017/MC/ZToUpsilon1SGamma/ |
| ```/ZToUpsilon2SGamma-TuneCP5_13TeV-pythia8/*/MINIAODSIM```   |	TO BE PRODUCED |
| ```/ZToUpsilon3SGamma-TuneCP5_13TeV-pythia8/*/MINIAODSIM```   |root://131.225.204.161:1094//store/user/eliza/ggNtuples2017/MC/ZToUpsilon3SGamma/ |

| **Sample**         | **xSec (pb)(*)**  | **Filter Efficiency(*)**  |  **Filter Efficiency Error(*)**  |
| ------ |:--------:|:-------:|:------:|
| ```ZToUpsilon1SGamma```   |	2.144  | 0.7056 | 0.01201 |
| ```ZToUpsilon2SGamma```   |	2.281 | 0.7118 | 0.1194 |
| ```ZToUpsilon3SGamma```   |	2.269 | 0.7389 | 0.1157 |

**(*)**: From McM (https://cms-pdmv.cern.ch/mcm/requests?prepid=SMP-RunIIFall17GS-00001&page=0; https://cms-pdmv.cern.ch/mcm/requests?prepid=SMP-RunIIFall17GS-00002&page=0; https://cms-pdmv.cern.ch/mcm/requests?prepid=SMP-RunIIFall17GS-00003&page=0). 



## Data
- **CMS DAS:** 
  - https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FMuonEG%2FRun2017*PromptReco*%2FMINIAOD
  - https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=%2FDoubleMuon%2FRun2017C-PromptReco*%2FMINIAOD
- **JSON ([Ref](https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/PromptReco/Cert_294927-305364_13TeV_PromptReco_Collisions17_JSON.txt
- **ggNutples:**  https://docs.google.com/spreadsheets/d/1H10ZsIrbIF2klhLOb3BSq9xft5KKiF2I0FT8t37fsuw/edit#gid=0

| **Sample**        | **Dataset Lumi (/fb)** | **Processed Lumi (/fb)**  |  Mu_Photon Trigger  |  DoubleMu_Photon Trigger  |**Location @ EOS**  |
| ------------- |:-------------:|:-------------:| :-------------:|:-------------:|:-----| 
| ```/MuonEG/Run2017A-PromptReco-v1/MINIAOD```  | ????| ???? |	**[x]** |	**[ ]**  |	 PRODUCED |
| ```/MuonEG/Run2017A-PromptReco-v2/MINIAOD```  | ????| ???? |	**[x]** |	**[ ]**  |	 PRODUCED |
| ```/MuonEG/Run2017A-PromptReco-v3/MINIAOD```  | ????| ???? |	**[x]** |	**[ ]**  |	 PRODUCED |
| ```/MuonEG/Run2017B-PromptReco-v1/MINIAOD```  | ????| ???? |	**[x]** |	**[ ]**  |	PRODUCED |
| ```/MuonEG/Run2017B-PromptReco-v2/MINIAOD```  | ????| ???? |	**[x]** |	**[ ]** |	 PRODUCED |
| ```/MuonEG/Run2017C-PromptReco-v1/MINIAOD```  | ????| ???? |	**[x]** |	**[ ]**  |	 PRODUCED |
| ```/MuonEG/Run2017C-PromptReco-v2/MINIAOD```  | ????| ???? |	**[x]** |	**[ ]**  |	 PRODUCED |
| ```/MuonEG/Run2017C-PromptReco-v3/MINIAOD```  | ????| ???? |	**[x]** |	**[ ]**  |	 PRODUCED |
| ```/DoubleMuon/Run2017C-PromptReco-v1/MINIAOD```  | ????| ???? |	**[ ]** |	**[x]**  |	PRODUCED |
| ```/DoubleMuon/Run2017C-PromptReco-v2/MINIAOD```  | ????| ???? |	**[ ]** |	**[x]**  |	 PRODUCED |
| ```/DoubleMuon/Run2017C-PromptReco-v3/MINIAOD```  | ????| ???? |	**[ ]** |	**[x]**  |	 PRODUCED |
| ```/MuonEG/Run2017D-PromptReco-v1/MINIAOD```  | ????| ???? |	**[x]** |	**[x]**  |	PRODUCED |
| ```/MuonEG/Run2017E-PromptReco-v1/MINIAOD```  | ????| ???? |	**[x]** |	**[x]** |	PRODUCED |
| ```/MuonEG/Run2017F-PromptReco-v1/MINIAOD```  | ????| ???? |	**[x]** |	**[x]**  |	 PRODUCED |
| **Total Recorded Lumi:**  |	???? /fb |	???? /fb |	  |

- **brilcalc command TO BE used:**
```brilcalc lumi -u /fb --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json -i [...]processedLumis.json```


- **Other ggNtuples versions:** https://docs.google.com/spreadsheets/d/1Fxy9KmV0Rirdl7Kjnc_KMNmqRhfwl9w1_5I0IWxaFYA/edit#gid=1329660137

