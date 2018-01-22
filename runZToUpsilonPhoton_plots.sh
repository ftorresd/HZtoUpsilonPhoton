#!/bin/bash

rm -fr evtsCountFiles; mkdir evtsCountFiles
rm -rf outputHistos/*

rm run_Plots_Dummy.C
rm run_Plots_H_Cat0.C
rm run_Plots_Z_Cat0.C
rm run_Plots_Z_Cat1.C
rm run_Plots_Z_Cat2.C
rm run_Plots_Z_Cat3.C



python runZToUpsilonPhoton_plots.py



root -b -q -l run_Plots_Dummy.C+ 
root -b -q -l run_Plots_H_Cat0.C+ &
root -b -q -l run_Plots_Z_Cat0.C+ &
root -b -q -l run_Plots_Z_Cat1.C+ &
root -b -q -l run_Plots_Z_Cat2.C+ &
root -b -q -l run_Plots_Z_Cat3.C+ &

time wait

 # Merge Higgs Fit Trees adn Histograms
hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon_Cat0_ZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon_Cat0_ZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilon2SGamma_HtoUpsilon_Cat0_ZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilon3SGamma_HtoUpsilon_Cat0_ZZZZZ.root
hadd -f outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon_Cat0_ZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon_Cat0_ZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilon2SGamma_HtoUpsilon_Cat0_ZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilon3SGamma_HtoUpsilon_Cat0_ZZZZZ.root

rm outputHistos/*_PZZZZ.root
rm outputHistos/*_MZZZZ.root
rm outputHistos/*_ZPZZZ.root
rm outputHistos/*_ZMZZZ.root
rm outputHistos/*_ZZPZZ.root
rm outputHistos/*_ZZMZZ.root
rm outputHistos/*_ZZZPZ.root
rm outputHistos/*_ZZZMZ.root
rm outputHistos/*_ZZZZP.root
rm outputHistos/*_ZZZZM.root

rm run_Plots_Dummy.C
rm run_Plots_H_Cat0.C
rm run_Plots_Z_Cat0.C
rm run_Plots_Z_Cat1.C
rm run_Plots_Z_Cat2.C
rm run_Plots_Z_Cat3.C



python systematicsYields_HZtoUpsilonPhoton.py


# rm evtsCountFiles/*_PZZZZ.json
# rm evtsCountFiles/*_MZZZZ.json
# rm evtsCountFiles/*_ZPZZZ.json
# rm evtsCountFiles/*_ZMZZZ.json
# rm evtsCountFiles/*_ZZPZZ.json
# rm evtsCountFiles/*_ZZMZZ.json
# rm evtsCountFiles/*_ZZZPZ.json
# rm evtsCountFiles/*_ZZZMZ.json
# rm evtsCountFiles/*_ZZZZP.json
# rm evtsCountFiles/*_ZZZZM.json


