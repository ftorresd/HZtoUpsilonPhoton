#!/bin/bash


if [ $1 = "lxbatch" ]; then
	# cd ..
	# tar -cvf HZtoUpsilonPhoton.tar HZtoUpsilonPhoton/*
	# cd HZtoUpsilonPhoton

	for JOBS in H_Cat0_Data_JPsi H_Cat0_Data_Upsilon H_Cat0_MC Z_Cat0_Data_JPsi Z_Cat0_Data_Upsilon Z_Cat0_MC Z_Cat1_Data_JPsi Z_Cat1_Data_Upsilon Z_Cat1_MC Z_Cat2_Data_JPsi Z_Cat2_Data_Upsilon Z_Cat2_MC Z_Cat3_Data_JPsi Z_Cat3_Data_Upsilon Z_Cat3_MC
	do
		rm Plots_$JOBS.out Plots_$JOBS.err 
	done

	./runHZToUpsilonPhoton_plots.sh getSubmitCommands
	exit
fi


if [ $1 = "getSubmitCommands" ]; then
	# rm -rf ../outputHistos_FromLSF/*
	# rm -rf ../evtsCountFiles_FromLSF/*
	# for JOBS in H_Cat0_Data_JPsi H_Cat0_Data_Upsilon Z_Cat0_Data_JPsi Z_Cat0_Data_Upsilon Z_Cat1_Data_JPsi Z_Cat1_Data_Upsilon Z_Cat2_Data_JPsi Z_Cat2_Data_Upsilon Z_Cat3_Data_JPsi Z_Cat3_Data_Upsilon H_Cat0_MC Z_Cat0_MC Z_Cat1_MC Z_Cat2_MC Z_Cat3_MC
	for JOBS in H_Cat0_Data_Upsilon Z_Cat0_Data_Upsilon Z_Cat1_Data_Upsilon Z_Cat2_Data_Upsilon Z_Cat3_Data_Upsilon H_Cat0_MC Z_Cat0_MC Z_Cat1_MC Z_Cat2_MC Z_Cat3_MC
	do
		echo "bsub -R \"rusage[mem=32800]\" -R \"pool>30000\" -q 8nh -oo Plots_$JOBS.out -eo Plots_$JOBS.err -J Plots_$JOBS runHZToUpsilonPhoton_plots_LXBATCH.sh $JOBS"
	done
    exit
fi



if [ $1 = "check" ]; then
	cat Plots_*_Cat*_Data_*.out | grep "Writing output file"
    exit
fi
 

if [ $1 = "run_local" ]; then
	rm -rf evtsCountFiles/*
	rm -rf outputHistos/*

	rm run_Plots_Dummy.C
	rm run_Plots_H_Cat0_Data_JPsi.C
	rm run_Plots_H_Cat0_Data_Upsilon.C
	rm run_Plots_H_Cat0_MC.C

	rm run_Plots_Z_Cat0_Data_JPsi.C
	rm run_Plots_Z_Cat0_Data_Upsilon.C
	rm run_Plots_Z_Cat0_MC.C

	rm run_Plots_Z_Cat1_Data_JPsi.C
	rm run_Plots_Z_Cat1_Data_Upsilon.C
	rm run_Plots_Z_Cat1_MC.C

	rm run_Plots_Z_Cat2_Data_JPsi.C
	rm run_Plots_Z_Cat2_Data_Upsilon.C
	rm run_Plots_Z_Cat2_MC.C

	rm run_Plots_Z_Cat3_Data_JPsi.C
	rm run_Plots_Z_Cat3_Data_Upsilon.C
	rm run_Plots_Z_Cat3_MC.C



	python runZToUpsilonPhoton_plots.py

	root -b -q -l run_Plots_Dummy.C+ 

	# root -b -q -l run_Plots_Z_Cat0_MC.C+
	# root -b -q -l run_Plots_H_Cat0_MC.C+
	# root -b -q -l run_Plots_H_Cat0_Data_Upsilon.C+

	# root -b -q -l run_Plots_H_Cat0_Data_JPsi.C+ > Plots_H_Cat0_Data_JPsi.out 2> Plots_H_Cat0_Data_JPsi.err &
	# root -b -q -l run_Plots_H_Cat0_Data_Upsilon.C+ > Plots_H_Cat0_Data_Upsilon.out 2> Plots_H_Cat0_Data_Upsilon.err &
	# time wait
	root -b -q -l run_Plots_H_Cat0_MC.C+ > Plots_H_Cat0_MC.out 2> Plots_H_Cat0_MC.err 
 
	# root -b -q -l run_Plots_Z_Cat0_Data_JPsi.C+ > Plots_Z_Cat0_Data_JPsi.out 2> Plots_Z_Cat0_Data_JPsi.err &
	# root -b -q -l run_Plots_Z_Cat0_Data_Upsilon.C+ > Plots_Z_Cat0_Data_Upsilon.out 2> Plots_Z_Cat0_Data_Upsilon.err &
	# time wait
	# root -b -q -l run_Plots_Z_Cat0_MC.C+ > Plots_Z_Cat0_MC.out 2> Plots_Z_Cat0_MC.err &

	# root -b -q -l run_Plots_Z_Cat1_Data_JPsi.C+ > Plots_Z_Cat1_Data_JPsi.out 2> Plots_Z_Cat1_Data_JPsi.err &
	# root -b -q -l run_Plots_Z_Cat1_Data_Upsilon.C+ > Plots_Z_Cat1_Data_Upsilon.out 2> Plots_Z_Cat1_Data_Upsilon.err &
	# time wait
	# root -b -q -l run_Plots_Z_Cat1_MC.C+ > Plots_Z_Cat1_MC.out 2> Plots_Z_Cat1_MC.err &

	# root -b -q -l run_Plots_Z_Cat2_Data_JPsi.C+ > Plots_Z_Cat2_Data_JPsi.out 2> Plots_Z_Cat2_Data_JPsi.err &
	# root -b -q -l run_Plots_Z_Cat2_Data_Upsilon.C+ > Plots_Z_Cat2_Data_Upsilon.out 2> Plots_Z_Cat2_Data_Upsilon.err &
	# time wait
	# root -b -q -l run_Plots_Z_Cat2_MC.C+ > Plots_Z_Cat2_MC.out 2> Plots_Z_Cat2_MC.err &

	# root -b -q -l run_Plots_Z_Cat3_Data_JPsi.C+ > Plots_Z_Cat3_Data_JPsi.out 2> Plots_Z_Cat3_Data_JPsi.err &
	# root -b -q -l run_Plots_Z_Cat3_Data_Upsilon.C+ > Plots_Z_Cat3_Data_Upsilon.out 2> Plots_Z_Cat3_Data_Upsilon.err &
	# time wait
	# root -b -q -l run_Plots_Z_Cat3_MC.C+ > Plots_Z_Cat3_MC.out 2> Plots_Z_Cat3_MC.err &
	# time wait

	# root -b -q -l run_Plots_Dummy.C+ 
	# root -b -q -l run_Plots_H_Cat0_Data_JPsi.C+ &
	# root -b -q -l run_Plots_H_Cat0_Data_Upsilon.C+ &
	# root -b -q -l run_Plots_H_Cat0_MC.C+  &

	# root -b -q -l run_Plots_Z_Cat0_Data_JPsi.C+  &
	# root -b -q -l run_Plots_Z_Cat0_Data_Upsilon.C+  &
	# root -b -q -l run_Plots_Z_Cat0_MC.C+  &

	# root -b -q -l run_Plots_Z_Cat1_Data_JPsi.C+  &
	# root -b -q -l run_Plots_Z_Cat1_Data_Upsilon.C+  &
	# root -b -q -l run_Plots_Z_Cat1_MC.C+  &

	# root -b -q -l run_Plots_Z_Cat2_Data_JPsi.C+  &
	# root -b -q -l run_Plots_Z_Cat2_Data_Upsilon.C+  &
	# root -b -q -l run_Plots_Z_Cat2_MC.C+  &

	# root -b -q -l run_Plots_Z_Cat3_Data_JPsi.C+  &
	# root -b -q -l run_Plots_Z_Cat3_Data_Upsilon.C+  &
	# root -b -q -l run_Plots_Z_Cat3_MC.C+  &


	rm run_Plots_Dummy.C  
	rm run_Plots_H_Cat0_Data_JPsi.C
	rm run_Plots_H_Cat0_Data_Upsilon.C
	rm run_Plots_H_Cat0_MC.C

	rm run_Plots_Z_Cat0_Data_JPsi.C
	rm run_Plots_Z_Cat0_Data_Upsilon.C
	rm run_Plots_Z_Cat0_MC.C

	rm run_Plots_Z_Cat1_Data_JPsi.C
	rm run_Plots_Z_Cat1_Data_Upsilon.C
	rm run_Plots_Z_Cat1_MC.C

	rm run_Plots_Z_Cat2_Data_JPsi.C
	rm run_Plots_Z_Cat2_Data_Upsilon.C
	rm run_Plots_Z_Cat2_MC.C

	rm run_Plots_Z_Cat3_Data_JPsi.C
	rm run_Plots_Z_Cat3_Data_Upsilon.C
	rm run_Plots_Z_Cat3_MC.C
    exit
fi 


if [ $1 = "collect" ]; then
	cp -r ../outputHistos_FromLSF/* outputHistos/.
	cp -r ../evtsCountFiles_FromLSF/* evtsCountFiles/.
    exit
fi


if [ $1 = "merge" ]; then
	eval "$( ./plotsToMerge.py )"

	# Merge Z Fit Trees and Histograms
	echo "Merging ZtoUpsilon_Cat0..."
	hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root
	hadd -f outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat0_ZZZZZZ.root
	echo "Merging ZtoUpsilon_Cat1..."
	hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root
	hadd -f outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat1_ZZZZZZ.root
	echo "Merging ZtoUpsilon_Cat2..."
	hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root
	hadd -f outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat2_ZZZZZZ.root
	echo "Merging ZtoUpsilon_Cat3..."
	hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root
	hadd -f outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilonGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon2SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_ZToUpsilon3SGamma_ZtoUpsilon_Cat3_ZZZZZZ.root


	# Merge Higgs Fit Trees and Histograms
	echo "Merging HtoUpsilon_Cat0..."
	hadd -f outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilon2SGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outHistos_HZtoUpsilonPhoton_HToUpsilon3SGamma_HtoUpsilon_Cat0_ZZZZZZ.root
	hadd -f outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilonGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilon1SGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilon2SGamma_HtoUpsilon_Cat0_ZZZZZZ.root outputHistos/outTreeToFit_HZtoUpsilonPhoton_HToUpsilon3SGamma_HtoUpsilon_Cat0_ZZZZZZ.root
	
	python systematicsYields_HZtoUpsilonPhoton.py

	python dumpEvtCountsAndSyst_HZtoUpsilonPhoton.py
    exit
fi



