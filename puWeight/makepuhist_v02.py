#! /usr/bin/env python

# Customized from: https://github.com/cmsb2g/B2GDAS/blob/master/test/makepu_fwlite.py
# More Info: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideCMSDataAnalysisSchoolLPC2017B2GTTbarExercise#Pileup_reweighting

# Usage:
  # pileupCalc.py -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt --calcMode true --minBiasXsec 69200 --maxPileupBin 200 --numPileupBins 1000 MyDataPileupHistogram_v02_NOMINAL.root
  # pileupCalc.py -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt --calcMode true --minBiasXsec 72383 --maxPileupBin 200 --numPileupBins 1000 MyDataPileupHistogram_v02_UP.root
  # pileupCalc.py -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt --calcMode true --minBiasXsec 66017 --maxPileupBin 200 --numPileupBins 1000 MyDataPileupHistogram_v02_DOWN.root

#   ./makepuhist.py --file_data MyDataPileupHistogram.root --file_ggNtuple_mc pu_ZToUpsilon1SGamma.root --file_out puWeights_ZToUpsilon1SGamma.root




## _________                _____.__                            __  .__               
## \_   ___ \  ____   _____/ ____\__| ____  __ ______________ _/  |_|__| ____   ____  
## /    \  \/ /  _ \ /    \   __\|  |/ ___\|  |  \_  __ \__  \\   __\  |/  _ \ /    \ 
## \     \___(  <_> )   |  \  |  |  / /_/  >  |  /|  | \// __ \|  | |  (  <_> )   |  \
##  \______  /\____/|___|  /__|  |__\___  /|____/ |__|  (____  /__| |__|\____/|___|  /
##         \/            \/        /_____/                   \/                    \/ 
import sys
from array import array
from optparse import OptionParser


def makepuhist(argv) : 
    parser = OptionParser()

    parser.add_option('--file_data_nominal', type='string', action='store',
                      dest='file_data_nominal',
                      help='Input file for data - nominal')

    parser.add_option('--file_data_up', type='string', action='store',
                      dest='file_data_up',
                      help='Input file for data - up')

    parser.add_option('--file_data_down', type='string', action='store',
                      dest='file_data_down',
                      help='Input file for data - down')

    parser.add_option('--file_ggNtuple_mc', type='string', action='store',
                      dest='file_mc',
                      help='Input ggNtuple for MC')

    parser.add_option('--file_out', type='string', action='store',
                      dest='file_out',
                      help='Output file')
    
    (options, args) = parser.parse_args(argv)
    argv = []

    print '===== Command line options ====='
    print options
    print '================================'

    import ROOT

    data_nominal = ROOT.TFile(options.file_data_nominal)
    data_up = ROOT.TFile(options.file_data_up)
    data_down = ROOT.TFile(options.file_data_down)
    
    with open(options.file_mc, 'r') as f:
      mc = ROOT.TFile(f.readline().strip())
    
    out = ROOT.TFile(options.file_out, "RECREATE")

    h_data_nominal = data_nominal.Get("pileup")
    h_data_up = data_up.Get("pileup")
    h_data_down = data_down.Get("pileup")

    h_data_nominal.SetName("pileup_nominal")
    h_data_up.SetName("pileup_up")
    h_data_down.SetName("pileup_down")

    h_mc = mc.Get("ggNtuplizer/hPUTrue")

    h_data_nominal.Sumw2()
    h_data_nominal.Scale(1.0 / h_data_nominal.Integral() )

    h_data_up.Sumw2()
    h_data_up.Scale(1.0 / h_data_up.Integral() )
    
    h_data_down.Sumw2()
    h_data_down.Scale(1.0 / h_data_down.Integral() )
    print h_data_down.GetSize()

    h_mc.Sumw2()
    h_mc.Scale(1.0 / h_mc.Integral() )
    # h_mc.Print("*")
    print h_mc.GetSize()


    h_data_nominal.Divide(h_mc)
    h_data_up.Divide(h_mc)
    h_data_down.Divide(h_mc)

    out.cd()
    h_data_nominal.Write()
    h_data_up.Write()
    h_data_down.Write()
    out.Close()



if __name__ == "__main__" :
    makepuhist(sys.argv)

