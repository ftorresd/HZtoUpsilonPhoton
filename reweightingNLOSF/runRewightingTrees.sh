#!/bin/bash

# source plugins/setupCERT.sh

rm -rf logsTrees
mkdir logsTrees

rm -rf outputTrees
mkdir outputTrees

# ttH_HToJPsiG_NLO - excluded
for VAR in ZToUpsilon1SG_LO ZToUpsilon2SG_LO ZToUpsilon3SG_LO HToUpsilon1SG_LO HToUpsilon2SG_LO HToUpsilon3SG_LO ZToUpsilon2SG_NLO ggH_HToJPsiG_NLO VBFH_HToJPsiG_NLO ZH_HToJPsiG_NLO WpHJ_HToJPsiG_NLO WmHJ_HToJPsiG_NLO
# for VAR in ttH_HToJPsiG_NLO ZToUpsilon1SG_LO ZToUpsilon2SG_LO ZToUpsilon3SG_LO HToUpsilon1SG_LO HToUpsilon2SG_LO HToUpsilon3SG_LO ZToUpsilon2SG_NLO ggH_HToJPsiG_NLO VBFH_HToJPsiG_NLO ZH_HToJPsiG_NLO WpHJ_HToJPsiG_NLO WmHJ_HToJPsiG_NLO 
# for VAR in ttH_HToJPsiG_NLO
# for VAR in ZToUpsilon1SG_LO HToUpsilon1SG_LO ZToUpsilon2SG_NLO ggH_HToJPsiG_NLO VBFH_HToJPsiG_NLO ZH_HToJPsiG_NLO WpHJ_HToJPsiG_NLO WmHJ_HToJPsiG_NLO
do
	./reweightingNLOSFTrees.py $VAR  >> logsTrees/$VAR.log 2>&1 &
done


wait

tail -n 15 logsTrees/*.log



# for VAR in DYJetsToLL_NLO
# do
# 	./reweightingNLOSFTrees.py $VAR  >> logsTrees/$VAR.log 2>&1 &
# done


# wait

# tail -n 15 logsTrees/DYJetsToLL_NLO.log
