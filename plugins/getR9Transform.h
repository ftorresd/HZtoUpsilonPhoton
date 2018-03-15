#include "TGraph.h"
#include "TFile.h"

using namespace std;

double getR9Transform(bool isMC, double photonR9, double photonSCEta) {
	double newR9 = photonR9;

	// data
	if (!isMC) return newR9;

	// MC
	shared_ptr<TFile> r9TransformFile(new TFile("data/r9transformation.root")); 

	auto r9TransformGraphEB = (TGraph*)r9TransformFile->Get("transfnonfull5x5R9EB"); 	
	auto r9TransformGraphEE = (TGraph*)r9TransformFile->Get("transfnonfull5x5R9EE"); 

	if(fabs(photonSCEta) < 1.4442) newR9 = r9TransformGraphEB->Eval(photonR9);
	if(fabs(photonSCEta) > 1.566 && fabs(photonSCEta) < 2.5) newR9 = r9TransformGraphEB->Eval(photonR9);

	return newR9;
}
