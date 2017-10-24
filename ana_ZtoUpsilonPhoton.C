// ######################################################
// Z --> Upsilon + Photon
// ######################################################
// Analysis Code
// Description:  - Reads the ggNtuples
//               - Skim the sample
//               - Apply corrections and cuts           
//               - Produces a ntuple read for plotting  
// ######################################################



#include "plugins/untuplizer_v07.h"


void ana_ZtoUpsilonPhoton(const char* Inpath, TString outpath)  
{
    TreeReader data(Inpath);

}


