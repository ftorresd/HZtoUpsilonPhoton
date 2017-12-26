#include <iostream>
#include <algorithm>
#include <math.h>  
// #include <stdlib.h>

#include "TFile.h"
// #include "TMath.h"
// #include "TLorentzVector.h"
#include "TTree.h"
// #include "TTreeReader.h"
// #include "TTreeReaderValue.h"
// #include "TTreeReaderArray.h"
// #include "TRandom3.h"
// #include "TROOT.h"
#include "TH2.h"
// #include "TDirectory.h"
// #include "THStack.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"
#include "TLatex.h"


#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooChebychev.h"
#include "RooCBShape.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooProdPdf.h"
#include "RooBernstein.h"
#include "RooArgList.h"
#include "RooWorkspace.h"
#include "RooConstVar.h"


#include "RooDataSet.h"
// #include "RooPolynomial.h"
// #include "TAxis.h"
// #include "RooTrace.h"


#include "../plugins/tdrstyle.C"
// #include "plugins/tdrstyle.C"
#include "plugins/RooDCBShape/RooDCBShape.h"

#ifdef __CINT__
#pragma link C++ class RooDCBShape+;
#endif

using namespace RooFit;
using namespace std;



////////////////////////////////////////////////////////////////////////////////////
// 2D Fit
void DCBZPeakUpsilonfit2D() {

	setTDRStyle();

	TFile* _file0 = new TFile("../outputHistos/outHistos_ZtoUpsilonPhoton_Data.root","read");
	//	TFile* _file0 = new TFile("HaddHistos_ZtoUpsilonPhoton_ZToUpsilonGamma.root","read");

	TCanvas* c = new TCanvas("2DFits","2DFits",800,400) ;

	TH2* mass2DHist = (TH2D*)_file0->Get("outputHistos/withKinCutsHistos/h_withKin_Upsilon_Mass_Z_Mass");
	TString title="signal+bckg";



	// Upsilon Fit

	TString xtitle="m_{#mu^{-}#mu^{+}} [GeV/c^{2}]";
	TString ytitle="m_{#mu^{-}#mu^{+}+#gamma} [GeV/c^{2}]";
	const double M1S = 9.46;   //upsilon 1S pgd mass value
	const double M2S = 10.02;  //upsilon 2S pgd mass value
	const double M3S = 10.35; //upsilon 3S pgd mass value
	const double M4S = 10.579; //upsilon 4S pgd mass value

	double minMass=8.0;
	double maxMass=12.0;

	TH1 * Dimuon = mass2DHist->ProjectionX();//dimuon

	RooRealVar mass("mass",xtitle,minMass,maxMass);
	RooDataHist dimuonData("dimuonData","dimuonData",mass,Import(*Dimuon));

	RooRealVar mean("mass_mean","#Upsilon mean",M1S,M1S-0.5,M1S+0.5,"GeV");
	RooRealVar shift21("shift2","mass diff #Upsilon(1,2S)",M2S-M1S);
	RooRealVar shift31("shift3","mass diff #Upsilon(1,3S)",M3S-M1S);
	RooRealVar shift41("shift4","mass diff #Upsilon(1,4S)",M4S-M1S);

	RooRealVar mscale("mscale","mass scale factor",1.,1.0,1.0);
	mscale.setConstant(kTRUE); /* the def. parameter value is fixed in the fit */
	// double mscale = 1.0;//  check it for MC 

	RooFormulaVar mean1S("mean1S","@0",RooArgList(mean));
	RooFormulaVar mean2S("mean2S","@0+@1*@2",RooArgList(mean,mscale,shift21));
	RooFormulaVar mean3S("mean3S","@0+@1*@2",RooArgList(mean,mscale,shift31));
	RooFormulaVar mean4S("mean4S","@0+@1*@2",RooArgList(mean,mscale,shift41));


	RooRealVar sigma1("sigma1","Sigma_1",0.06,0.01,0.30);
	RooRealVar sigma2("sigma2","Sigma_2",0.10,0.01,0.30);

	/// to describe final state radiation tail on the left of the peaks
	RooRealVar alpha("alpha","tail shift",1.5,0.2,4);
	RooRealVar npow("npow","power order",2);
	npow.setConstant(kTRUE);
	alpha.setConstant(kTRUE);

	/// relative fraction of the two peak components 
	RooRealVar sigmaFraction("sigmaFraction","Sigma Fraction",0.3,0.,1.);

	/// Upsilon 1S
	RooGaussian gauss1S1("gauss1S1","1S Gaussian_1",mass,mean1S,sigma1);
	RooCBShape  gauss1S2("gauss1S2", "FSR cb 1s",mass,mean1S,sigma2,alpha,npow); 
	RooAddPdf sig1S("sig1S","1S mass pdf",RooArgList(gauss1S1,gauss1S2),sigmaFraction);

	/// Upsilon 2S
	RooGaussian gauss2S1("gauss2S1","2S Gaussian_1",mass,mean2S,sigma1);
	RooCBShape  gauss2S2("gauss2S2", "FSR cb 2s", mass,mean2S,sigma2,alpha,npow); 
	RooAddPdf sig2S("sig2S","2S mass pdf",RooArgList(gauss2S1,gauss2S2),sigmaFraction);

	/// Upsilon 3S
	RooGaussian gauss3S1("gauss3S1","3S Gaussian_1",mass,mean3S,sigma1);
	RooGaussian gauss3S2("gauss3S2","3S Gaussian_2",mass,mean3S,sigma2);
	RooAddPdf sig3S("sig3S","3S mass pdf",RooArgList(gauss3S1,gauss3S2),sigmaFraction);

	/// Upsilon 4S
	RooGaussian gauss4S1("gauss4S1","4S Gaussian_1",mass,mean4S,sigma1);
	RooGaussian gauss4S2("gauss4S2","4S Gaussian_2",mass,mean4S,sigma2);
	RooAddPdf sig4S("sig4S","4S mass pdf",RooArgList(gauss4S1,gauss4S2),sigmaFraction);


	/// Background
	RooRealVar *bkg_a1  = new RooRealVar("bkg_a1", "background a1", 0, -1, 1);
	RooRealVar *bkg_a2  = new RooRealVar("bkg_a2", "background a2", 0, -1, 1);
	RooAbsPdf  *bkgPdf  = new RooChebychev("bkg","linear background",mass, RooArgList(*bkg_a1,*bkg_a2));


	/// Combined pdf
	int nt = 30000;
	RooRealVar *nsig1 = new RooRealVar("nsig1","signal 1s yield",nt*0.25*0.6,0,10*nt); 
	RooRealVar *nsig2 = new RooRealVar("nsig2","signal 2s yield",nt*0.25*0.3,0,10*nt); 
	RooRealVar *nsig3 = new RooRealVar("nsig3","signal 3s yield",nt*0.25*0.1,0,10*nt); 
	RooRealVar *nsig4 = new RooRealVar("nsig4","signal 3s yield",nt*0.25*0.05,0,10*nt);
	RooRealVar *nbkgd = new RooRealVar("nbkgd","brackground yield",nt*0.75,0,10*nt); 
	RooAbsPdf  *pdf   = new RooAddPdf ("pdf","total signal+background pdf",RooArgList(sig1S,sig2S,sig3S,sig4S,*bkgPdf),RooArgList(*nsig1,*nsig2,*nsig3,*nsig4,*nbkgd));
	pdf->fitTo( dimuonData, Extended());

	RooPlot* frame = mass.frame(Title(title));
	dimuonData.plotOn(frame,Name("theData"),DataError(RooDataHist::SumW2));
	pdf->plotOn(frame,Name("thePdf"));
	pdf->plotOn(frame,Components("sig1S"),LineStyle(kDashed),LineColor(kGreen));
	pdf->plotOn(frame,Components("sig2S"),LineStyle(kDashed),LineColor(kMagenta));
	pdf->plotOn(frame,Components("sig3S"),LineStyle(kDashed),LineColor(kYellow));
	pdf->plotOn(frame,Components("sig4S"),LineStyle(kDashed),LineColor(kOrange)); 
	pdf->plotOn(frame,Components("bkg"),LineStyle(kDashed),LineColor(kRed));

	// Adding Dataset box and PDF parameters box 
	RooArgSet * dpars = pdf->getParameters(dimuonData);
	int dnfloatpars = dpars->selectByAttrib("Constant",kFALSE)->getSize();
	double dmychsq = frame->chiSquare("thePdf","theData", dnfloatpars);
	double dmyndof = Dimuon->GetNbinsX() - dnfloatpars;
	pdf->paramOn(frame,Layout(0.65,0.99,0.99),Format("NE"),Label(Form("#chi^{2}/ndf = %2.0f/%2.0f", dmyndof*dmychsq, dmyndof))
		);



	//////////////////////////////////////////
	//  DiMuons Gamma  Fit

	TH1 * DimuonGamma = mass2DHist->ProjectionY();// Boson Z
	RooRealVar dimuongamma("dimuongamma", ytitle, 70, 130);
	RooDataHist dimuonGammaData("dimuonGammaData","dimuonGammaData",dimuongamma,Import(*DimuonGamma));

	RooRealVar mean_dcb("mean_dcb", "Mean" ,91.1876,70,130) ;
	RooRealVar sigma_dcb("sigma_dcb", "Width" ,  2., 0.5, 4.) ;
	RooRealVar n1("n1","", 0.5, 0.1, 50.);//dCBPowerL
	RooRealVar n2("n2","", 1., 0.1, 50.);//dCBPowerR


	RooRealVar alpha1("alpha1","", 3., 0.1, 50.);//dCBCutL

	RooRealVar alpha2("alpha2","", 3., 0.1, 50.);//dCBCutR


	//RooRealVar lambda("lambda", "slope", -0.1, -5., 0.);
	//RooRealVar s_bw("signal_bw", "signal", 100, 0, 10000);
	RooRealVar s_dcb("signal_dcb", "signal", 100, 0, 10000);


	RooDCBShape cball("cball", "double crystal ball", dimuongamma, mean_dcb,sigma_dcb,alpha1,alpha2,n1,n2);

	//	RooExponential expo("expo", "exponential PDF", dimuongamma, lambda);


	//--------------------------------//
	// Background fit                 //
	// Using Bernstein 2nd polynomial //
	//                                //
	//--------------------------------//

	RooRealVar p0("p0", " ", 0, 1); // coefficient of x^0 term
	RooRealVar p1("p1", " ", 0, 1); // coefficient of x^1 term
	RooRealVar p2("p2", " ", 0, 1); // coefficient of x^2 term
	RooBernstein BkgPdf_2016("BkgPdf_2016", " ", dimuongamma, RooArgList(RooConst(1),p1,p2));
	RooRealVar b("BernsteinBackground", "background yield", 100, 0, 10000);


	//RooAddPdf sum("sum", "double crystal ball and exponential PDF", RooArgList(cball, expo), RooArgList(s_dcb, b));
	RooAddPdf sum("sum", "double crystal ball and Bernstein 2nd polynomial", RooArgList(cball, BkgPdf_2016), RooArgList(s_dcb, b));
    // RooAddPdf sum("sum", "double crystal ball and Bernstein 2nd polynomial", RooArgList(BkgPdf_2016), RooArgList(s_dcb, b));
	RooPlot * xFrame = dimuongamma.frame(Title("Z-peak")) ;

        // Z fiting and blind regions 
        //dimuongamma.setRange("blind_signal", 70, 120);
        //dimuongamma.setRange("blind_bck1", 80, 100);
        //dimuongamma.setRange("blind_bck2", 120, 135);


	sum.fitTo(dimuonGammaData, RooFit::Extended());  
	dimuonGammaData.plotOn(xFrame,DataError(RooDataHist::SumW2)) ;
	sum.plotOn(xFrame) ;

	//sum.plotOn(xFrame, RooFit::Components(expo),RooFit::LineStyle(kDashed),LineColor(kRed)) ;  
	sum.plotOn(xFrame, RooFit::Components(BkgPdf_2016),RooFit::LineStyle(kDashed),LineColor(kRed)) ; 
	sum.paramOn(xFrame,Layout(0.65), Format("NEU", AutoPrecision(1)), Parameters( RooArgList(s_dcb, b, mean_dcb,sigma_dcb )));

	// Adding Dataset box and PDF parameters box 
	RooArgSet * pars = sum.getParameters(dimuongamma);
	int nfloatpars = pars->selectByAttrib("Constant",kFALSE)->getSize();
	double mychsq = xFrame->chiSquare(nfloatpars);
	double myndof = DimuonGamma->GetNbinsX() - nfloatpars;
	sum.paramOn(xFrame,Layout(0.65,0.99,0.99),Format("NE"),Label(Form("#chi^{2}/ndf = %2.0f/%2.0f", myndof*mychsq, myndof))
		);


	////////////
	// Creating 2D fit using projection 
	///

	RooProdPdf sig2DpdfUSZ("sig2DpdfUZ", "2D Signal PDF Upsilon and Z boson", RooArgList(*pdf,sum));

	RooDataHist data2D("data2D","Th2D Dataset",RooArgList(mass,dimuongamma),mass2DHist);

	TH1* hmodel2d = sig2DpdfUSZ.createHistogram("hmodel2d",mass,Binning(50),YVar(dimuongamma,Binning(100))) ;

	// Z fiting and blind regions 
	//dimuongamma.setRange("blind_signal", 70, 120);
	dimuongamma.setRange("blind_bck1", 80, 100);
	dimuongamma.setRange("blind_bck2", 120, 135);	
	// Upsilon Region
	mass.setRange("blind_signal", 9., 11.);
	//mass.setRange("blind_bck", 8, 8.9);
	//mass.setRange("blind_bck", 11., 12.);


	sig2DpdfUSZ.fitTo(data2D,Save(kTRUE));
	//sig2DpdfUSZ.fitTo(data2D,Save(kTRUE),Range("blind_signal,blind_bck"));



	// Fit p.d.f to all data
	RooFitResult* r_full = sig2DpdfUSZ.fitTo(data2D,Save(kTRUE)) ;
	// Fit p.d.f only to data in "signal" range
	RooFitResult* r_sig = sig2DpdfUSZ.fitTo(data2D,Save(kTRUE),Range("blind_signal")) ;

	//  Fit p.d.f only to data in excluded region 80, 100 and 120, 135 for Z and  selection upsilon region 
	RooFitResult* r_Z = sig2DpdfUSZ.fitTo(data2D,Save(kTRUE),Range("blind_signal"),CutRange("blind_bck1,blind_bck2")) ;



	// --- Fit ---
	RooPlot* xyFrame = dimuongamma.frame() ;
	data2D.plotOn(xyFrame) ;
	sig2DpdfUSZ.plotOn(xyFrame) ;


	// Print fit results 
	cout << "result of fit on all data " << endl ;
	r_full->Print() ; 

	cout << "result of fit in in upsilon region (note increased error on signal fraction)" << endl ;
	r_sig->Print() ;

	cout << "result of fit in excluded region 80, 100 and 120, 135 for Z and  selection upsilon region   (note increased error on signal fraction)" << endl ;
	r_Z->Print() ;

	//-----------------------------------//


	/*
	// C r e a t e   w o r k s p a c e ,   i m p o r t   d a t a   a n d   m o d e l,
	// 2D fit
	*/      
	RooWorkspace *w = new RooWorkspace("w","workspace") ;   
	w->import(sig2DpdfUSZ); 
	w->import(data2D);
	w->Print();

	system(("mkdir -p  `dirname fitPlotFiles/DCBZPeakUpsilonfit2D/DCBZPeakUpsilonfit2D.root`"));
	w->writeToFile("fitPlotFiles/DCBZPeakUpsilonfit2D/workspace_DCBZPeakUpsilonfit2D.root"); 
	//gDirectory->Add(w) ;  

	// Draw the 'sigar'
	gStyle->SetCanvasPreferGL(true);
	gStyle->SetPalette(1);       
	// Draw all frames on a canvas
	//c->Divide(2,2) ;
	c->Divide(2,1);
	c->cd(1) ; gPad->SetLeftMargin(0.25) ; frame->GetYaxis()->SetTitleOffset(0.9) ;  frame->Draw() ; // dimuons
	//	c->cd(2) ; gPad->SetLeftMargin(0.25) ; xFrame->GetYaxis()->SetTitleOffset(0.9) ;  xFrame->Draw(); // dimuons + gamma 
	c->cd(2); hmodel2d->Draw("Surf3") ;

	system(("mkdir -p  `dirname fitPlotFiles/DCBZPeakUpsilonfit2D/UpsilonZ2Dfit.png`"));
	c->SaveAs("fitPlotFiles/DCBZPeakUpsilonfit2D/UpsilonZ2Dfit.png");
	c->SaveAs("fitPlotFiles/DCBZPeakUpsilonfit2D/UpsilonZ2Dfit.gif");
	c->SaveAs("fitPlotFiles/DCBZPeakUpsilonfit2D/UpsilonZ2Dfit.pdf");
	c->SaveAs("fitPlotFiles/DCBZPeakUpsilonfit2D/UpsilonZ2Dfit.root");
}

////////////////////////////////////////////////////////////////////////////////////
// 2D Fit
void ZToUpsilonPhotonSignalAndBackgroundFit() {
	setTDRStyle();

	//////////////////////////////////////////////////////////////////////////////////////
	// LOAD DATA

	// DATA
	// auto * outTreeToFitFile = TFile::Open("../outputHistos/outTreeToFit_ZtoUpsilonPhoton_Data_ZtoJPsi.root");
	auto * outTreeToFitFileData = TFile::Open("../outputHistos/outTreeToFit_ZtoUpsilonPhoton_Data_ZtoUpsilon.root");
	auto * outTreeToFitData = (TTree*)outTreeToFitFileData->Get("outTree_ZtoUpsilonPhoton");
	RooRealVar mHZData("mHZ", "mHZ", 70, 120, "GeV") ;
	RooRealVar weightsData("mHZWeight", "mHZWeight", -100, 100, "");
	RooDataSet data("data", "", RooArgSet(mHZData), Import(*outTreeToFitData)); 
	data.Print();


	// SIGNAL HISTO
	auto * outHistoSignalFile = TFile::Open("../outputHistos/outHistos_ZtoUpsilonPhoton_ZToUpsilon1SGamma.root");
	auto * outHistoSignal = (TH1D*)outHistoSignalFile->Get("outputHistos/withKinCutsHistos/h_withKin_Z_Mass");


	// SIGNAL
	auto * outTreeToFitFileSignal = TFile::Open("../outputHistos/outTreeToFit_ZtoUpsilonPhoton_ZToJPsiGamma_ZtoJpsi.root");
	// auto * outTreeToFitFileSignal = TFile::Open("../outputHistos/outTreeToFit_ZtoUpsilonPhoton_ZToUpsilon1SGamma_ZtoUpsilon.root");
	auto * outTreeToFitSignal = (TTree*)outTreeToFitFileSignal->Get("outTree_ZtoUpsilonPhoton");
	RooRealVar mHZSignal("mHZ", "mHZ", 70, 120, "GeV") ;
	RooRealVar weightsSignal("mHZWeight", "mHZWeight", -100, 100, "");
	RooDataSet signal("signal", " ", RooArgSet(mHZSignal, weightsSignal), Import(*outTreeToFitSignal), WeightVar(weightsSignal));
	signal.Print();


	////////////////////////////////////////////////////////////////////////////////////
	// BACKGROUND MODEL
	RooRealVar p0("p0", " ", 0, 1); // coefficient of x^0 term
	RooRealVar p1("p1", " ", 0, 1); // coefficient of x^1 term
	RooRealVar p2("p2", " ", 0, 1); // coefficient of x^2 term
	RooRealVar p3("p3", " ", 0, 1); // coefficient of x^3 term
	RooBernstein Bernstein("Bernstein", " ", mHZData, RooArgList(RooConst(1), p1, p2, p3));
	// RooRealVar b("BernsteinBackground", "", 100, 0, 10000);

	cout << "\n\n---------> Begin Background Fit\n\n" << endl;
	RooFitResult * fitResultBackground = Bernstein.fitTo(data, Save(kTRUE));
	fitResultBackground->Print();
	cout << "\n\n---------> End Background Fit\n\n" << endl;



  	////////////////////////////////////////////////////////////////////////////////////
  	// BAKCGROUND PLOT 
	auto c1 = new TCanvas("c1","c1",1050*2.0,750*2.0);
	gPad->SetLeftMargin(0.17); 
	gPad->SetRightMargin(0.05); 
	gPad->SetTopMargin(0.08);

	mHZData.setRange("leftSide",70,80) ;
	mHZData.setRange("rightSide",100,120);
	RooPlot* xframe1 = mHZData.frame(Title("M_{#mu#mu#gamma}")) ;
	data.plotOn(xframe1,Binning(20),CutRange("leftSide"),RooFit::Name("data"), MarkerSize(3)) ; 
	data.plotOn(xframe1,Binning(20),CutRange("rightSide"), MarkerSize(3)) ;
	Bernstein.plotOn(xframe1,RooFit::Name("Bernstein"),VisualizeError(*fitResultBackground,2),FillColor(kYellow)) ;
	Bernstein.plotOn(xframe1,RooFit::Name("Bernstein"),VisualizeError(*fitResultBackground,1),FillColor(kGreen)) ;
	Bernstein.plotOn(xframe1,RooFit::Name("Bernstein"),LineColor(kAzure+7));
	// Bernstein.paramOn(xframe1,Layout(0.65,0.92,0.89));
	data.plotOn(xframe1,Binning(20),CutRange("leftSide"),RooFit::Name("data"), MarkerSize(3)) ; 
	data.plotOn(xframe1,Binning(20),CutRange("rightSide"), MarkerSize(3)) ;
	xframe1->SetMinimum(0.00001);
	xframe1->GetXaxis()->SetTitle("M_{#mu#mu#gamma} (GeV)");
	xframe1->GetXaxis()->SetLabelOffset(0.02);
	xframe1->Draw();


	//signal yield
	outHistoSignal->SetLineWidth(3);
	outHistoSignal->SetLineColor(kOrange+8);
	outHistoSignal->SetLineStyle(1);
	outHistoSignal->Scale(30.0/(outHistoSignal->Integral()));
	outHistoSignal->Rebin(5);
	outHistoSignal->Draw("hist same");

	// legend
	auto legend = new TLegend(0.6,0.7,0.9,0.87);
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->AddEntry(xframe1->findObject("data"), "Data", "lpe");
	legend->AddEntry(xframe1->findObject("Bernstein"), "Background Model", "l");
	legend->AddEntry(outHistoSignal, "Expected Signal (#times 30)", "l");

	legend->Draw();

	// CMS decoration
    auto latex = new TLatex();
    latex->SetNDC();
    latex->SetTextFont(61);
    latex->SetTextSize(0.05);
    latex->DrawLatex(.17, 0.93, "CMS");
    latex->SetTextFont(52);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(11);
    latex->DrawLatex(.25, 0.93, "Preliminary");
    latex->SetTextFont(42);
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.96, 0.93, "35.86 fb^{-1} (13 TeV, 2016) ");

 	system(("mkdir -p  `dirname fitPlotFiles/ZToUpsilonPhotonSignalAndBackgroundFit/ZToUpsilonPhotonSignalAndBackgroundFit_Data.png`"));
 	c1->SaveAs("fitPlotFiles/ZToUpsilonPhotonSignalAndBackgroundFit/ZToUpsilonPhotonSignalAndBackgroundFit_Data.root");
 	c1->SaveAs("fitPlotFiles/ZToUpsilonPhotonSignalAndBackgroundFit/ZToUpsilonPhotonSignalAndBackgroundFit_Data.png");
 	c1->SaveAs("fitPlotFiles/ZToUpsilonPhotonSignalAndBackgroundFit/ZToUpsilonPhotonSignalAndBackgroundFit_Data.pdf");


	////////////////////////////////////////////////////////////////////////////////////
	// SIGNAL MODEL
	RooRealVar mean_dcb("mean_dcb", "Mean" ,91.1876,70,120) ;
	RooRealVar sigma_dcb("sigma_dcb", "Width" ,  2., 0.5, 4.) ;
	RooRealVar n1("n1","", 0.5, 0.1, 50.);//dCBPowerL
	// RooRealVar n2("n2","", 1., 0.1, 50.);//dCBPowerR
	RooRealVar n2("n2","", 0.5, 0.1, 50.);//dCBPowerR
	RooRealVar alpha1("alpha1","", 3., 0.1, 50.);//dCBCutL
	RooRealVar alpha2("alpha2","", 3., 0.1, 50.);//dCBCutR
	// RooRealVar s_dcb("signal_dcb", "signal", 100, 0, 10000);


	RooDCBShape dcball("dcball", "double sided crystal ball", mHZSignal, mean_dcb,sigma_dcb,alpha1,alpha2,n1,n2);

	cout << "\n\n---------> Begin Signal Fit\n\n" << endl;
	RooFitResult * fitResultSignal = dcball.fitTo(signal, Save(kTRUE), SumW2Error(kTRUE) ) ;
	// RooFitResult * fitResultSignal = dcball.fitTo(signal, Save(kTRUE), SumW2Error(kFALSE) ) ;
	fitResultSignal->Print();
	cout << "\n\n---------> End Signal Fit\n\n" << endl;


  	////////////////////////////////////////////////////////////////////////////////////
  	// SIGNAL PLOT
	auto cSignal = new TCanvas("c2","c2",1050*2.0,750*2.0);
	gPad->SetLeftMargin(0.17); 
	gPad->SetRightMargin(0.05); 
	gPad->SetTopMargin(0.08);
	RooPlot* xframeSignal = mHZSignal.frame(Title("M_{#mu#mu#gamma}")) ;
	signal.plotOn(xframeSignal,Binning(40),RooFit::Name("signal"), MarkerSize(3), DataError(RooAbsData::SumW2)) ; 
	// dcball.plotOn(xframeSignal,RooFit::Name("dcball"),LineColor(kAzure+7));
	dcball.plotOn(xframeSignal,RooFit::Name("dcball"),LineColor(kOrange+8));
	// dcball.paramOn(xframeSignal,Layout(0.65,0.92,0.89));

	xframeSignal->SetMinimum(0.00001);
	xframeSignal->GetXaxis()->SetTitle("M_{#mu#mu#gamma} (GeV)");
	xframeSignal->GetXaxis()->SetLabelOffset(0.02);
	xframeSignal->Draw();

	// legend
	auto legendSignal = new TLegend(0.6,0.7,0.9,0.87);
	legendSignal->SetBorderSize(0);
	legendSignal->SetFillStyle(0);
	legendSignal->AddEntry(xframeSignal->findObject("signal"), "Signal MC", "lpe");
	legendSignal->AddEntry(xframeSignal->findObject("dcball"), "Signal Model", "l");
	// legendSignal->AddEntry(outHistoSignal, "Expected Signal (#times 30)", "l");
	legendSignal->Draw();

	// CMS decoration
    auto latexSignal = new TLatex();
    latexSignal->SetNDC();
    latexSignal->SetTextFont(61);
    latexSignal->SetTextSize(0.05);
    latexSignal->DrawLatex(.17, 0.93, "CMS");
    latexSignal->SetTextFont(52);
    latexSignal->SetTextSize(0.04);
    latexSignal->SetTextAlign(11);
    latexSignal->DrawLatex(.25, 0.93, "Preliminary");
    latexSignal->SetTextFont(42);
    latexSignal->SetTextSize(0.04);
    latexSignal->SetTextAlign(31);
    latexSignal->DrawLatex(0.96, 0.93, "35.86 fb^{-1} (13 TeV, 2016) ");

 	system(("mkdir -p  `dirname fitPlotFiles/ZToUpsilonPhotonSignalAndBackgroundFit/ZToUpsilonPhotonSignalAndBackgroundFit_Signal.png`"));
 	cSignal->SaveAs("fitPlotFiles/ZToUpsilonPhotonSignalAndBackgroundFit/ZToUpsilonPhotonSignalAndBackgroundFit_Signal.root");
 	cSignal->SaveAs("fitPlotFiles/ZToUpsilonPhotonSignalAndBackgroundFit/ZToUpsilonPhotonSignalAndBackgroundFit_Signal.png");
 	cSignal->SaveAs("fitPlotFiles/ZToUpsilonPhotonSignalAndBackgroundFit/ZToUpsilonPhotonSignalAndBackgroundFit_Signal.pdf");


	////////////////////////////////////////////////////////////////////////////////////
	// C r e a t e   w o r k s p a c e ,   i m p o r t   d a t a   a n d   m o d e l 
	RooWorkspace *w = new RooWorkspace("w","workspace") ;  
	w->import(mHZData);
	w->import(data,Rename("data_obs"));
	w->import(Bernstein);
	w->Print();
	system(("mkdir -p  `dirname fitPlotFiles/ZToUpsilonPhotonSignalAndBackgroundFit/ZToUpsilonPhotonSignalAndBackgroundFit.root`"));
	w->writeToFile("fitPlotFiles/ZToUpsilonPhotonSignalAndBackgroundFit/ZToUpsilonPhotonSignalAndBackgroundFit_workspace.root"); 

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DOES THE ACTUAL FITTING
// void fitter_HZtoUpsilonPhoton(string histoDataFilePath, string histoMCSignalFilePath, string histoMCBackgroundFilePath)  
void fitter_HZtoUpsilonPhoton()  
{
	// auto * histoDataFile = TFile::Open(histoDataFilePath.c_str());
	// auto * histoMCSignalFile = TFile::Open(histoMCSignalFilePath.c_str());
	// auto * histoMCBackgroundFile = TFile::Open(histoMCBackgroundFilePath.c_str());
	// auto * histoMCSignalFile = TFile::Open(histoDataFilePath.c_str());


	// plotter
	setTDRStyle();
	system("rm -fr fitPlotFiles; mkdir fitPlotFiles");

	// DCBZPeakUpsilonfit2D();
	ZToUpsilonPhotonSignalAndBackgroundFit();



} //end plotter_ZtoUpsilonPhoton




