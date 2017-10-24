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
- **CMS DAS:** https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FZToUpsilon*SGamma*%2F*%2FMINIAODSIM
- **ggNutples:**

| **Sample**         | **Location @ EOS**  |
| ------- |:-------|
| ```/ZToUpsilon1SGamma-TuneCUETP8M1_13TeV-pythia8/*/MINIAODSIM```   |	TO BE PRODUCED |
| ```/ZToUpsilon2SGamma-TuneCUETP8M1_13TeV-pythia8/*/MINIAODSIM```   |	TO BE PRODUCED |
| ```/ZToUpsilon3SGamma-TuneCUETP8M1_13TeV-pythia8/*/MINIAODSIM```   |		TO BE PRODUCED |

| **Sample**         | **xSec (pb)(*)**  | **Filter Efficiency(*)**  |  **Filter Efficiency Error(*)**  |
| ------ |:--------:|:-------:|:------:|
| ```ZToUpsilon1SGamma```   |	2.022 | 0.7222 | 0.03733 |
| ```ZToUpsilon2SGamma```   |	2.071 | 0.6667 | 0.04811 |
| ```ZToUpsilon3SGamma```   |	1.696 | 0.6146 | 0.04967 |

**(*)**: From McM (https://cms-pdmv.cern.ch/mcm/requests?prepid=SMP-RunIISummer15GS-00178&page=0&shown=127; https://cms-pdmv.cern.ch/mcm/requests?prepid=SMP-RunIISummer15GS-00179&page=0&shown=127; https://cms-pdmv.cern.ch/mcm/requests?prepid=SMP-RunIISummer15GS-00180&page=0&shown=127). 



## Data
- **CMS DAS:** https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FMuonEG%2FRun2017*PromptReco*%2FMINIAOD
- **JSON:** TBD
- **ggNutples:**

| **Sample**        | **Lumi (/fb)**  | **Location @ EOS**  |
| ------------- |:-------------:| :-----| 
| ```/MuonEG/Run2017A-PromptReco-v1/MINIAOD```  |	???? |	TO BE PRODUCED |
| ```/MuonEG/Run2017A-PromptReco-v2/MINIAOD```  |	???? |	TO BE PRODUCED |
| ```/MuonEG/Run2017A-PromptReco-v3/MINIAOD```  |	???? |	TO BE PRODUCED |
| ```/MuonEG/Run2017B-PromptReco-v1/MINIAOD```  |	???? |	TO BE PRODUCED |
| ```/MuonEG/Run2017B-PromptReco-v2/MINIAOD```  |	???? |	TO BE PRODUCED |
| ```/MuonEG/Run2017C-PromptReco-v1/MINIAOD```  |	???? |	TO BE PRODUCED |
| ```/MuonEG/Run2017C-PromptReco-v2/MINIAOD```  |	???? |	TO BE PRODUCED |
| ```/MuonEG/Run2017C-PromptReco-v3/MINIAOD```  |	???? |	TO BE PRODUCED |
| ```/MuonEG/Run2017D-PromptReco-v1/MINIAOD```  |	???? |	TO BE PRODUCED |
| ```/MuonEG/Run2017E-PromptReco-v1/MINIAOD```  |	???? |	TO BE PRODUCED |
| ```/MuonEG/Run2017F-PromptReco-v1/MINIAOD```  |	???? |	TO BE PRODUCED |
| **Total Recorded Lumi:**  |	???? /fb |	  |

- **ATTENTION: To be understood.**
  - **brilcalc command TO BE used:**
```brilcalc lumi -u /fb --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json -i [...]processedLumis.json```


- **Other ggNtuples versions:** https://docs.google.com/spreadsheets/d/1Fxy9KmV0Rirdl7Kjnc_KMNmqRhfwl9w1_5I0IWxaFYA/edit#gid=1329660137

