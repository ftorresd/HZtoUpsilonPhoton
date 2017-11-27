#include "TLorentzVector.h"
#include "TVector3.h"
// #include "plugins/anaObjects.h"


double upsilonPolarizationAngle(anaGenPart genMuPlus, anaGenPart genMuMinus) {
	TVector3 boostVector = -1*(genMuPlus + genMuMinus).BoostVector();  
  	TLorentzVector genMuPlusUpsilonFrame(genMuPlus);
  	genMuPlusUpsilonFrame.Boost(boostVector); 
  	return genMuPlusUpsilonFrame.Vect().Unit().Dot((genMuPlus + genMuMinus).Vect().Unit());
}