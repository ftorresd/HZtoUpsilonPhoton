# ZtoUpsilonPhoton
ZtoUpsilonPhoton @ CMS

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



## 2017 Samples
### MC 
- **CMS DAS:** https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FZToUpsilon1SGamma-TuneCP5_13TeV-pythia8*%2F*%2FMINIAODSIM
- **ggNutples:**

| **Sample**         | **Location @ EOS**  |
| ------- |:-------|
| ```/ZToUpsilon1SGamma-TuneCP5_13TeV-pythia8/*/MINIAODSIM```   |	TO BE PRODUCED |
| ```/ZToUpsilon2SGamma-TuneCP5_13TeV-pythia8/*/MINIAODSIM```   |	TO BE PRODUCED |
| ```/ZToUpsilon3SGamma-TuneCP5_13TeV-pythia8/*/MINIAODSIM```   |		TO BE PRODUCED |

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
- **JSON ([Ref](https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2017Analysis)):** https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/PromptReco/Cert_294927-303825_13TeV_PromptReco_Collisions17_JSON.txt
- **ggNutples:**

| **Sample**        | **Dataset Lumi (/fb)** | **Processed Lumi (/fb)**  |  Mu_Photon Trigger  |  DoubleMu_Photon Trigger  |**Location @ EOS**  |
| ------------- |:-------------:|:-------------:| :-------------:|:-------------:|:-----| 
| ```/MuonEG/Run2017A-PromptReco-v1/MINIAOD```  | ????| ???? |	[x] |	[ ]  |	TO BE PRODUCED |
| ```/MuonEG/Run2017A-PromptReco-v2/MINIAOD```  | ????| ???? |	[x] |	[ ]  |	TO BE PRODUCED |
| ```/MuonEG/Run2017A-PromptReco-v3/MINIAOD```  | ????| ???? |	[x] |	[ ]  |	TO BE PRODUCED |
| ```/MuonEG/Run2017B-PromptReco-v1/MINIAOD```  | ????| ???? |	[x] |	[ ]  |	TO BE PRODUCED |
| ```/MuonEG/Run2017B-PromptReco-v2/MINIAOD```  | ????| ???? |	[x] |	[ ] |	TO BE PRODUCED |
| ```/MuonEG/Run2017C-PromptReco-v1/MINIAOD```  | ????| ???? |	[x] |	[ ]  |	TO BE PRODUCED |
| ```/MuonEG/Run2017C-PromptReco-v2/MINIAOD```  | ????| ???? |	[x] |	[ ]  |	TO BE PRODUCED |
| ```/MuonEG/Run2017C-PromptReco-v3/MINIAOD```  | ????| ???? |	[x] |	[ ]  |	TO BE PRODUCED |
| ```/DoubleMuon/Run2017C-PromptReco-v1/MINIAOD```  | ????| ???? |	[ ] |	[x]  |	TO BE PRODUCED |
| ```/DoubleMuon/Run2017C-PromptReco-v2/MINIAOD```  | ????| ???? |	[ ] |	[x]  |	TO BE PRODUCED |
| ```/DoubleMuon/Run2017C-PromptReco-v3/MINIAOD```  | ????| ???? |	[ ] |	[x]  |	TO BE PRODUCED |
| ```/MuonEG/Run2017D-PromptReco-v1/MINIAOD```  | ????| ???? |	[x] |	[x]  |	TO BE PRODUCED |
| ```/MuonEG/Run2017E-PromptReco-v1/MINIAOD```  | ????| ???? |	[x] |	[x] |	TO BE PRODUCED |
| ```/MuonEG/Run2017F-PromptReco-v1/MINIAOD```  | ????| ???? |	[x] |	[x]  |	TO BE PRODUCED |
| **Total Recorded Lumi:**  |	???? /fb |	???? /fb |	  |

- **brilcalc command TO BE used:**
```brilcalc lumi -u /fb --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json -i [...]processedLumis.json```


- **Other ggNtuples versions:** https://docs.google.com/spreadsheets/d/1Fxy9KmV0Rirdl7Kjnc_KMNmqRhfwl9w1_5I0IWxaFYA/edit#gid=1329660137

