# How to get the PU weights

 ```
 pileupCalc.py -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt --calcMode true --minBiasXsec 69200 --maxPileupBin 200 --numPileupBins 1000 MyDataPileupHistogram_v02_NOMINAL.root &
 
 pileupCalc.py -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt --calcMode true --minBiasXsec 72383 --maxPileupBin 200 --numPileupBins 1000 MyDataPileupHistogram_v02_UP.root &
 
 pileupCalc.py -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt --calcMode true --minBiasXsec 66017 --maxPileupBin 200 --numPileupBins 1000 MyDataPileupHistogram_v02_DOWN.root &


wait




./makepuhist_v02.py --file_data_nominal MyDataPileupHistogram_v02_NOMINAL.root --file_data_up MyDataPileupHistogram_v02_UP.root --file_data_down MyDataPileupHistogram_v02_DOWN.root --file_ggNtuple_mc ../filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToJPsiGamma.txt --file_out pu_ZToJPsiGamma.root &

./makepuhist_v02.py --file_data_nominal MyDataPileupHistogram_v02_NOMINAL.root --file_data_up MyDataPileupHistogram_v02_UP.root --file_data_down MyDataPileupHistogram_v02_DOWN.root --file_ggNtuple_mc ../filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon1SGamma.txt --file_out pu_ZToUpsilon1SGamma.root &


./makepuhist_v02.py --file_data_nominal MyDataPileupHistogram_v02_NOMINAL.root --file_data_up MyDataPileupHistogram_v02_UP.root --file_data_down MyDataPileupHistogram_v02_DOWN.root --file_ggNtuple_mc ../filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon2SGamma.txt --file_out pu_ZToUpsilon2SGamma.root &

./makepuhist_v02.py --file_data_nominal MyDataPileupHistogram_v02_NOMINAL.root --file_data_up MyDataPileupHistogram_v02_UP.root --file_data_down MyDataPileupHistogram_v02_DOWN.root --file_ggNtuple_mc ../filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZToUpsilon3SGamma.txt --file_out pu_ZToUpsilon3SGamma.root &
     
./makepuhist_v02.py --file_data_nominal MyDataPileupHistogram_v02_NOMINAL.root --file_data_up MyDataPileupHistogram_v02_UP.root --file_data_down MyDataPileupHistogram_v02_DOWN.root --file_ggNtuple_mc ../filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/ZGTo2MuG_MMuMu-2To15.txt --file_out pu_ZGTo2MuG_MMuMu-2To15.root &









./makepuhist_v02.py --file_data_nominal MyDataPileupHistogram_v02_NOMINAL.root --file_data_up MyDataPileupHistogram_v02_UP.root --file_data_down MyDataPileupHistogram_v02_DOWN.root --file_ggNtuple_mc ../filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToJPsiGamma.txt --file_out pu_HToJPsiGamma.root &

./makepuhist_v02.py --file_data_nominal MyDataPileupHistogram_v02_NOMINAL.root --file_data_up MyDataPileupHistogram_v02_UP.root --file_data_down MyDataPileupHistogram_v02_DOWN.root --file_ggNtuple_mc ../filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon1SGamma.txt --file_out pu_HToUpsilon1SGamma.root &


./makepuhist_v02.py --file_data_nominal MyDataPileupHistogram_v02_NOMINAL.root --file_data_up MyDataPileupHistogram_v02_UP.root --file_data_down MyDataPileupHistogram_v02_DOWN.root --file_ggNtuple_mc ../filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon2SGamma.txt --file_out pu_HToUpsilon2SGamma.root &

./makepuhist_v02.py --file_data_nominal MyDataPileupHistogram_v02_NOMINAL.root --file_data_up MyDataPileupHistogram_v02_UP.root --file_data_down MyDataPileupHistogram_v02_DOWN.root --file_ggNtuple_mc ../filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HToUpsilon3SGamma.txt --file_out pu_HToUpsilon3SGamma.root &
     
./makepuhist_v02.py --file_data_nominal MyDataPileupHistogram_v02_NOMINAL.root --file_data_up MyDataPileupHistogram_v02_UP.root --file_data_down MyDataPileupHistogram_v02_DOWN.root --file_ggNtuple_mc ../filesLists/filesFromUERJPOWER/HZtoUpsilonPlusPhotonSamples2016_withGhostCleanning/HDalitz.txt --file_out pu_HDalitz.root &

wait


echo "Done!"

```



#########################################

```

comando = '''
./makepuhist_v02.py \
--file_data_nominal MyDataPileupHistogram_v02_NOMINAL.root \
--file_data_up MyDataPileupHistogram_v02_UP.root \
--file_data_down MyDataPileupHistogram_v02_DOWN.root \
--file_ggNtuple_mc ../filesLists/filesListsOniaTriggers/fromEOS/MC_@@SAMPLE@@.txt \
--file_out pu_@@SAMPLE@@_MuOniaTriggers.root &
'''

filesMC = [
	"filesLists/filesListsOniaTriggers/fromEOS/MC_HToJPsiGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_HToUpsilon1SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_HToUpsilon2SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_HToUpsilon3SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_ZGTo2MuG_MMuMu-2To15.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_ZToJPsiGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_ZToUpsilon1SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_ZToUpsilon2SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_ZToUpsilon3SGamma.txt",
	"filesLists/filesListsOniaTriggers/fromEOS/MC_HDalitz.txt",
	]

for file in filesMC:
	sampleString = file.replace("filesLists/filesListsOniaTriggers/fromEOS/MC_", "").replace(".txt", "")
	print comando.replace("@@SAMPLE@@", sampleString)
```
