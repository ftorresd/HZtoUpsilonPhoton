#!/usr/bin/env python

import json
from decimal import Decimal



###############################
# Print Final Yields
samplesBranchesFinalYields = {
		"ZtoUpsilon_Cat0":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat1":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat2":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoUpsilon_Cat3":["Data", "ZToUpsilon1SGamma", "ZToUpsilon2SGamma", "ZToUpsilon3SGamma", "ZToUpsilonGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat0":["Data", "ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat1":["Data", "ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat2":["Data", "ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"ZtoJPsi_Cat3":["Data", "ZToJPsiGamma", "ZGTo2MuG_MMuMu-2To15"],
		"HtoUpsilon_Cat0":["Data", "HToUpsilon1SGamma", "HToUpsilon2SGamma", "HToUpsilon3SGamma", "HToUpsilonGamma", "HDalitz"],
		"HtoJPsi_Cat0":["Data", "HToJPsiGamma", "HDalitz"]
		}

outputJSONFinalYields = {
				"ZtoUpsilon_Cat0":[],
				"ZtoUpsilon_Cat1":[],
				"ZtoUpsilon_Cat2":[],
				"ZtoUpsilon_Cat3":[],
				"ZtoJPsi_Cat0":[],
				"ZtoJPsi_Cat1":[],
				"ZtoJPsi_Cat2":[],
				"ZtoJPsi_Cat3":[],
				"HtoUpsilon_Cat0":[],
				"HtoJPsi_Cat0":[]
				}

for branch in samplesBranchesFinalYields:
	for sample in samplesBranchesFinalYields[branch]:
		f = open("evtsCountFiles/evtsCountFile_"+ sample +"_"+ branch +"_ZZZZZ.json","r")  
		counts = json.load(f)
		outputJSONFinalYields[branch].append({
			"Analysis Branch": counts["analysisBranch"]+"Photon",
			"Analysis Sample": counts["sample"],
			"Category": counts["selCategory"],
			"Total before selection": counts["total"],
			"Final Yield/Count": counts["hz_mass_cut"],
			})

		f.close()

def humanReadable(B, toInt = False):
   'Return the given number as a human friendly K, M, G, or T string'
   B = float(B)
   KB = float(1000)
   MB = float(KB ** 2) 
   GB = float(KB ** 3) 
   TB = float(KB ** 4) 

   if B < KB:
      return '{0} {1}'.format(int(B),'' if 0 == B > 1 else '')
   elif KB <= B < MB:
      return '{0:.2f} K'.format(B/KB)
   elif MB <= B < GB:
      return '{0:.2f} M'.format(B/MB)
   elif GB <= B < TB:
      return '{0:.2f} G'.format(B/GB)
   elif TB <= B:
      return '{0:.2f} T'.format(B/TB)

def latex_float(f):
    float_str = "{0:.3g}".format(f)
    if "e" in float_str:
        base, exponent = float_str.split("e")
        return r"${0} \times 10^{{{1}}}$".format(base, int(exponent))
    else:
        return float_str

def getValue(branch, selCategory, workingYield, workingSample, human = False):
	if (filter(lambda x: x.get("Analysis Sample") == workingSample,outputJSONFinalYields[branch+"_"+selCategory]) != []):
		if human:
			return str(humanReadable(filter(lambda x: x.get("Analysis Sample") == workingSample,outputJSONFinalYields[branch+"_"+selCategory])[0][workingYield]))
		else:
			return str(latex_float(filter(lambda x: x.get("Analysis Sample") == workingSample,outputJSONFinalYields[branch+"_"+selCategory])[0][workingYield]))
			# return ('%.2E \\times 10^\{' % Decimal(str(filter(lambda x: x.get("Analysis Sample") == workingSample,outputJSONFinalYields[branch+"_"+selCategory])[0][workingYield])))
	else:
		return "-"	  

def makeLatex(yieldStr, HorZ):
	if (HorZ == "Z"):
		peakingBkgSample = "ZGTo2MuG_MMuMu-2To15"
	else:
		peakingBkgSample = "HDalitz"
	upsilonStates = ["1S", "2S", "3S"]
	for state in upsilonStates:
		yieldStr = yieldStr.replace("@@HZ_TOTAL_DATA@@", getValue(HorZ+"toUpsilon", "Cat0", "Total before selection", "Data", True) )
		yieldStr = yieldStr.replace("@@HZ_TOTAL_SIGNAL_"+state+"@@", getValue(HorZ+"toUpsilon", "Cat0", "Total before selection", HorZ+"ToUpsilon"+state+"Gamma") )
		yieldStr = yieldStr.replace("@@HZ_TOTAL_PEAKBKG@@", getValue(HorZ+"toUpsilon", "Cat0", "Total before selection", peakingBkgSample) )

		yieldStr = yieldStr.replace("@@HZ_FINAL_DATA_CAT0@@", getValue(HorZ+"toUpsilon", "Cat0", "Final Yield/Count", "Data", True) )
		yieldStr = yieldStr.replace("@@HZ_FINAL_SIGNAL_"+state+"_CAT0@@", getValue(HorZ+"toUpsilon", "Cat0", "Final Yield/Count", HorZ+"ToUpsilon"+state+"Gamma") )
		yieldStr = yieldStr.replace("@@HZ_FINAL_PEAKBKG_CAT0@@", getValue(HorZ+"toUpsilon", "Cat0", "Final Yield/Count", peakingBkgSample) )
		
		if (HorZ == "Z"):
			yieldStr = yieldStr.replace("@@HZ_FINAL_DATA_CAT1@@", getValue(HorZ+"toUpsilon", "Cat1", "Final Yield/Count", "Data", True) )
			yieldStr = yieldStr.replace("@@HZ_FINAL_SIGNAL_"+state+"_CAT1@@", getValue(HorZ+"toUpsilon", "Cat1", "Final Yield/Count", HorZ+"ToUpsilon"+state+"Gamma") )
			yieldStr = yieldStr.replace("@@HZ_FINAL_PEAKBKG_CAT1@@", getValue(HorZ+"toUpsilon", "Cat1", "Final Yield/Count", peakingBkgSample) )

			yieldStr = yieldStr.replace("@@HZ_FINAL_DATA_CAT2@@", getValue(HorZ+"toUpsilon", "Cat2", "Final Yield/Count", "Data", True) )
			yieldStr = yieldStr.replace("@@HZ_FINAL_SIGNAL_"+state+"_CAT2@@", getValue(HorZ+"toUpsilon", "Cat2", "Final Yield/Count", HorZ+"ToUpsilon"+state+"Gamma") )
			yieldStr = yieldStr.replace("@@HZ_FINAL_PEAKBKG_CAT2@@", getValue(HorZ+"toUpsilon", "Cat2", "Final Yield/Count", peakingBkgSample) )

			yieldStr = yieldStr.replace("@@HZ_FINAL_DATA_CAT3@@", getValue(HorZ+"toUpsilon", "Cat3", "Final Yield/Count", "Data", True) )
			yieldStr = yieldStr.replace("@@HZ_FINAL_SIGNAL_"+state+"_CAT3@@", getValue(HorZ+"toUpsilon", "Cat3", "Final Yield/Count", HorZ+"ToUpsilon"+state+"Gamma") )
			yieldStr = yieldStr.replace("@@HZ_FINAL_PEAKBKG_CAT3@@", getValue(HorZ+"toUpsilon", "Cat3", "Final Yield/Count", peakingBkgSample) )

	print "\n\n"+yieldStr+"\n\n"
	return yieldStr





# Z
finalYieldsZStr = r"""

\begin{tabular}{c|c|c|c|c|c}
%& \multicolumn{5}{c}{$Z \rightarrow \Upsilon(1S, 2S, 3S)+\gamma$}       \\
\hline
\hline

&  &  \multicolumn{3}{c|}{Signal} &    \\
\cline{3-5}
& Data & $Z \rightarrow \Upsilon(1S)+\gamma$ & $Z \rightarrow \Upsilon(2S)+\gamma$ & $Z \rightarrow \Upsilon(3S)+\gamma$ &  $Z \rightarrow \mu\mu\gamma$  \\
\hline
Total (before selection) & @@HZ_TOTAL_DATA@@ &  @@HZ_TOTAL_SIGNAL_1S@@ & @@HZ_TOTAL_SIGNAL_2S@@ & @@HZ_TOTAL_SIGNAL_3S@@ & @@HZ_TOTAL_PEAKBKG@@  \\
\hline\hline
Full Selection - Cat0 & @@HZ_FINAL_DATA_CAT0@@ &  @@HZ_FINAL_SIGNAL_1S_CAT0@@ &  @@HZ_FINAL_SIGNAL_2S_CAT0@@ &  @@HZ_FINAL_SIGNAL_3S_CAT0@@ &  @@HZ_FINAL_PEAKBKG_CAT0@@  \\
Full Selection - Cat1 & @@HZ_FINAL_DATA_CAT1@@ &  @@HZ_FINAL_SIGNAL_1S_CAT1@@ &  @@HZ_FINAL_SIGNAL_2S_CAT1@@ &  @@HZ_FINAL_SIGNAL_3S_CAT1@@ &  @@HZ_FINAL_PEAKBKG_CAT1@@  \\
Full Selection - Cat2 & @@HZ_FINAL_DATA_CAT2@@ &  @@HZ_FINAL_SIGNAL_1S_CAT2@@ &  @@HZ_FINAL_SIGNAL_2S_CAT2@@ &  @@HZ_FINAL_SIGNAL_3S_CAT2@@ &  @@HZ_FINAL_PEAKBKG_CAT2@@  \\
Full Selection - Cat3 & @@HZ_FINAL_DATA_CAT3@@ &  @@HZ_FINAL_SIGNAL_1S_CAT3@@ &  @@HZ_FINAL_SIGNAL_2S_CAT3@@ &  @@HZ_FINAL_SIGNAL_3S_CAT3@@ &  @@HZ_FINAL_PEAKBKG_CAT3@@ \\

\end{tabular}

"""

with open('evtsCountFiles/FinalZYieldsLatex.txt', 'w') as outputLATEXFinalYieldsFile:  
    outputLATEXFinalYieldsFile.write( makeLatex(finalYieldsZStr, "Z") )



# Higgs
finalYieldsHStr = r"""

\begin{tabular}{c|c|c|c|c|c}
%& \multicolumn{5}{c}{$H \rightarrow \Upsilon(1S, 2S, 3S)+\gamma$}       \\
\hline
\hline

&  &  \multicolumn{3}{c|}{Signal} &    \\
\cline{3-5}
& Data & $H \rightarrow \Upsilon(1S)+\gamma$ & $H \rightarrow \Upsilon(2S)+\gamma$ & $H \rightarrow \Upsilon(3S)+\gamma$ &  $H \rightarrow \gamma\gamma^{*}$  \\
\hline
Total (before selection) & @@HZ_TOTAL_DATA@@ &  @@HZ_TOTAL_SIGNAL_1S@@ & @@HZ_TOTAL_SIGNAL_2S@@ & @@HZ_TOTAL_SIGNAL_3S@@ & @@HZ_TOTAL_PEAKBKG@@  \\
\hline\hline
Full Selection - Cat0 & @@HZ_FINAL_DATA_CAT0@@ &  @@HZ_FINAL_SIGNAL_1S_CAT0@@ &  @@HZ_FINAL_SIGNAL_2S_CAT0@@ &  @@HZ_FINAL_SIGNAL_3S_CAT0@@ &  @@HZ_FINAL_PEAKBKG_CAT0@@  \\

\end{tabular}

"""

with open('evtsCountFiles/FinalHYieldsLatex.txt', 'w') as outputLATEXFinalYieldsFile:  
    outputLATEXFinalYieldsFile.write( makeLatex(finalYieldsHStr, "H") )











###############################
# Print Systematics
with open('evtsCountFiles/systErrorYields.json', 'r') as systJSON:
	systJSON = json.load(systJSON)

# print json.dumps(systJSON, sort_keys=True, indent=4)



def getSyst(branch, selCategory, workingSyst, workingSample):
	if (filter(lambda x: x.get("Analysis Sample") == workingSample,systJSON[branch+"_"+selCategory]) != []):
		return str(round(filter(lambda x: x.get("Analysis Sample") == workingSample,systJSON[branch+"_"+selCategory])[0][workingSyst], 2))
	else:
		return "-"	  

def makeLatexSyst(systStr, HorZ):
	if (HorZ == "Z"):
		peakingBkgSample = "ZGTo2MuG_MMuMu-2To15"
	else:
		peakingBkgSample = "HDalitz"
	upsilonStates = ["1S", "2S", "3S", "PEAKBKG"]
	if (HorZ == "Z"):
		categories = ["Cat0", "Cat1", "Cat2", "Cat3"] 
	else:
		categories = ["Cat0"] 
	systematics = {
		"PU" : "Pileup",
		"ELECTRON-VETO" : "Electron Veto",
		"MUON-ID" : "Muon ID",
		"PHOTON-ID" : "Photon ID",
		"TRIGGER" : "Trigger",
		}

	# loop over systs
	for syst in systematics:
		for category in categories:
			for state in upsilonStates:
				if (state == "PEAKBKG"):
					systStr = systStr.replace("@@HZ-"+syst+"-"+state+"-"+category.upper()+"@@", getSyst(HorZ+"toUpsilon", category, systematics[syst], peakingBkgSample) )
				else:
					systStr = systStr.replace("@@HZ-"+syst+"-"+state+"-"+category.upper()+"@@", getSyst(HorZ+"toUpsilon", category, systematics[syst], HorZ+"ToUpsilon"+state+"Gamma") )
				
	print "\n\n"+systStr+"\n\n"
	return systStr





# Z
finalSystZStr = r"""
% ADD TO HEADER:
%\usepackage{multirow} %multirow
%\usepackage[table]{xcolor}    % loads also colortbl
%\renewcommand{\familydefault}{\sfdefault}
%\rowcolors{0}{gray!25}{white}
\begin{tabular}{c|c|c|c|c}
\cline{1-5}
\multirow{3}{*}{Source} & \multicolumn{4}{c}{Uncertainty} \\
\cline{2-5}
& \multicolumn{3}{c|}{Signal} & Peaking Background   \\
\cline{2-5}
& $Z \rightarrow \Upsilon(1S)  \gamma$ & $Z \rightarrow \Upsilon(2S)  \gamma$ & $Z \rightarrow \Upsilon(3S)  \gamma$ & $Z \rightarrow \mu\mu\gamma$  \\
\hline\hline
Integrated luminosity & \multicolumn{4}{l}{} \\ \hline
All Categories & \multicolumn{4}{c}{2.5\%} \\
\hline\hline
SM Z boson $\sigma$ (scale) & \multicolumn{4}{l}{} \\ \hline
All Categories & \multicolumn{3}{c|}{3.5\%}  & \multicolumn{1}{c}{5.0\%} \\
\hline\hline
SM Z boson $\sigma$ (PDF + $\alpha_s$)  & \multicolumn{4}{l}{} \\ \hline
All Categories & \multicolumn{3}{c|}{1.73\%}  & \multicolumn{1}{c}{5.0\%} \\
\hline\hline
Pileup Reweighting  & \multicolumn{4}{l}{} \\ \hline
Cat0 & @@HZ-PU-1S-CAT0@@\% & @@HZ-PU-2S-CAT0@@\% & @@HZ-PU-3S-CAT0@@\% & @@HZ-PU-PEAKBKG-CAT0@@\% \\
Cat1 & @@HZ-PU-1S-CAT1@@\% & @@HZ-PU-2S-CAT1@@\% & @@HZ-PU-3S-CAT1@@\% & @@HZ-PU-PEAKBKG-CAT1@@\% \\
Cat2 & @@HZ-PU-1S-CAT2@@\% & @@HZ-PU-2S-CAT2@@\% & @@HZ-PU-3S-CAT2@@\% & @@HZ-PU-PEAKBKG-CAT2@@\% \\
Cat3 & @@HZ-PU-1S-CAT3@@\% & @@HZ-PU-2S-CAT3@@\% & @@HZ-PU-3S-CAT3@@\% & @@HZ-PU-PEAKBKG-CAT3@@\% \\
\hline\hline
Trigger  & \multicolumn{4}{l}{} \\ \hline
Cat0 & @@HZ-TRIGGER-1S-CAT0@@\% & @@HZ-TRIGGER-2S-CAT0@@\% & @@HZ-TRIGGER-3S-CAT0@@\% & @@HZ-TRIGGER-PEAKBKG-CAT0@@\% \\
Cat1 & @@HZ-TRIGGER-1S-CAT1@@\% & @@HZ-TRIGGER-2S-CAT1@@\% & @@HZ-TRIGGER-3S-CAT1@@\% & @@HZ-TRIGGER-PEAKBKG-CAT1@@\% \\
Cat2 & @@HZ-TRIGGER-1S-CAT2@@\% & @@HZ-TRIGGER-2S-CAT2@@\% & @@HZ-TRIGGER-3S-CAT2@@\% & @@HZ-TRIGGER-PEAKBKG-CAT2@@\% \\
Cat3 & @@HZ-TRIGGER-1S-CAT3@@\% & @@HZ-TRIGGER-2S-CAT3@@\% & @@HZ-TRIGGER-3S-CAT3@@\% & @@HZ-TRIGGER-PEAKBKG-CAT3@@\% \\
\hline\hline
Muon ID/Isolation & \multicolumn{4}{l}{} \\ \hline
Cat0 & @@HZ-MUON-ID-1S-CAT0@@\% & @@HZ-MUON-ID-2S-CAT0@@\% & @@HZ-MUON-ID-3S-CAT0@@\% & @@HZ-MUON-ID-PEAKBKG-CAT0@@\% \\
Cat1 & @@HZ-MUON-ID-1S-CAT1@@\% & @@HZ-MUON-ID-2S-CAT1@@\% & @@HZ-MUON-ID-3S-CAT1@@\% & @@HZ-MUON-ID-PEAKBKG-CAT1@@\% \\
Cat2 & @@HZ-MUON-ID-1S-CAT2@@\% & @@HZ-MUON-ID-2S-CAT2@@\% & @@HZ-MUON-ID-3S-CAT2@@\% & @@HZ-MUON-ID-PEAKBKG-CAT2@@\% \\
Cat3 & @@HZ-MUON-ID-1S-CAT3@@\% & @@HZ-MUON-ID-2S-CAT3@@\% & @@HZ-MUON-ID-3S-CAT3@@\% & @@HZ-MUON-ID-PEAKBKG-CAT3@@\% \\
\hline\hline
Photon ID  & \multicolumn{4}{l}{} \\ \hline
Cat0 & @@HZ-PHOTON-ID-1S-CAT0@@\% & @@HZ-PHOTON-ID-2S-CAT0@@\% & @@HZ-PHOTON-ID-3S-CAT0@@\% & @@HZ-PHOTON-ID-PEAKBKG-CAT0@@\% \\
Cat1 & @@HZ-PHOTON-ID-1S-CAT1@@\% & @@HZ-PHOTON-ID-2S-CAT1@@\% & @@HZ-PHOTON-ID-3S-CAT1@@\% & @@HZ-PHOTON-ID-PEAKBKG-CAT1@@\% \\
Cat2 & @@HZ-PHOTON-ID-1S-CAT2@@\% & @@HZ-PHOTON-ID-2S-CAT2@@\% & @@HZ-PHOTON-ID-3S-CAT2@@\% & @@HZ-PHOTON-ID-PEAKBKG-CAT2@@\% \\
Cat3 & @@HZ-PHOTON-ID-1S-CAT3@@\% & @@HZ-PHOTON-ID-2S-CAT3@@\% & @@HZ-PHOTON-ID-3S-CAT3@@\% & @@HZ-PHOTON-ID-PEAKBKG-CAT3@@\% \\
\hline\hline
Electron Veto  & \multicolumn{4}{l}{} \\ \hline
Cat0 & @@HZ-ELECTRON-VETO-1S-CAT0@@\% & @@HZ-ELECTRON-VETO-2S-CAT0@@\% & @@HZ-ELECTRON-VETO-3S-CAT0@@\% & @@HZ-ELECTRON-VETO-PEAKBKG-CAT0@@\% \\
Cat1 & @@HZ-ELECTRON-VETO-1S-CAT1@@\% & @@HZ-ELECTRON-VETO-2S-CAT1@@\% & @@HZ-ELECTRON-VETO-3S-CAT1@@\% & @@HZ-ELECTRON-VETO-PEAKBKG-CAT1@@\% \\
Cat2 & @@HZ-ELECTRON-VETO-1S-CAT2@@\% & @@HZ-ELECTRON-VETO-2S-CAT2@@\% & @@HZ-ELECTRON-VETO-3S-CAT2@@\% & @@HZ-ELECTRON-VETO-PEAKBKG-CAT2@@\% \\
Cat3 & @@HZ-ELECTRON-VETO-1S-CAT3@@\% & @@HZ-ELECTRON-VETO-2S-CAT3@@\% & @@HZ-ELECTRON-VETO-3S-CAT3@@\% & @@HZ-ELECTRON-VETO-PEAKBKG-CAT3@@\% \\
\hline\hline

\end{tabular}


"""

with open('evtsCountFiles/FinalZSystLatex.txt', 'w') as outputLATEXFinalSystFile:  
    outputLATEXFinalSystFile.write( makeLatexSyst(finalSystZStr, "Z") )





# Higgs
finalSystHStr = r"""
% ADD TO HEADER:
%\usepackage{multirow} %multirow
%\usepackage[table]{xcolor}    % loads also colortbl
%\renewcommand{\familydefault}{\sfdefault}
%\rowcolors{0}{gray!25}{white}

\begin{tabular}{c|c|c|c|c}
\cline{1-5}
\multirow{3}{*}{Source} & \multicolumn{4}{c}{Uncertainty} \\
\cline{2-5}
& \multicolumn{3}{c|}{Signal} & Peaking Background   \\
\cline{2-5}
& $H \rightarrow \Upsilon(1S)  \gamma$ & $H \rightarrow \Upsilon(2S)  \gamma$ & $H \rightarrow \Upsilon(3S)  \gamma$ & $H \rightarrow \gamma\gamma^{*}$  \\
\hline\hline
Integrated luminosity & \multicolumn{4}{c}{2.5\%} \\
\hline
SM Z boson $\sigma$ (scale) & \multicolumn{4}{c}{+4.6\% / -6.7\%}  \\
\hline
SM Z boson $\sigma$ (PDF + $\alpha_s$) & \multicolumn{4}{c}{3.2\%}  \\
\hline
SM BR $H \rightarrow \gamma\gamma^{*}$  & \multicolumn{3}{c|}{-}  & \multicolumn{1}{c}{6.0\%} \\
\hline
Pileup Reweighting & @@HZ-PU-1S-CAT0@@\% & @@HZ-PU-2S-CAT0@@\% & @@HZ-PU-3S-CAT0@@\% & @@HZ-PU-PEAKBKG-CAT0@@\% \\
\hline
Trigger & @@HZ-TRIGGER-1S-CAT0@@\% & @@HZ-TRIGGER-2S-CAT0@@\% & @@HZ-TRIGGER-3S-CAT0@@\% & @@HZ-TRIGGER-PEAKBKG-CAT0@@\% \\
\hline
Muon ID/Isolation & @@HZ-MUON-ID-1S-CAT0@@\% & @@HZ-MUON-ID-2S-CAT0@@\% & @@HZ-MUON-ID-3S-CAT0@@\% & @@HZ-MUON-ID-PEAKBKG-CAT0@@\% \\
\hline
Photon ID  & @@HZ-PHOTON-ID-1S-CAT0@@\% & @@HZ-PHOTON-ID-2S-CAT0@@\% & @@HZ-PHOTON-ID-3S-CAT0@@\% & @@HZ-PHOTON-ID-PEAKBKG-CAT0@@\% \\
\hline
Electron Veto & @@HZ-ELECTRON-VETO-1S-CAT0@@\% & @@HZ-ELECTRON-VETO-2S-CAT0@@\% & @@HZ-ELECTRON-VETO-3S-CAT0@@\% & @@HZ-ELECTRON-VETO-PEAKBKG-CAT0@@\% \\
\hline
\end{tabular}
"""

with open('evtsCountFiles/FinalHSystLatex.txt', 'w') as outputLATEXFinalSystFile:  
    outputLATEXFinalSystFile.write( makeLatexSyst(finalSystHStr, "H") )


