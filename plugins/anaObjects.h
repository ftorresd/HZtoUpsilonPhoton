#include "TLorentzVector.h"

using namespace std;

const auto muonMass = 105.6583745/1000.0; //GeV


///////////////////////////////////////////////////
// muons
class anaMuon: public TLorentzVector {
	public:
  	int charge;
    int muonIndex;
    bool muonIsLooseID;
    bool muonIsTightID;
    bool muonIsISO;
    anaMuon();
    anaMuon(float, float, float, int, int, float);
    void clear();
    bool operator > (const anaMuon& compMuon) const
    {
        return (this->Pt() > compMuon.Pt());
    }
    ClassDef(anaMuon, 1)
};



anaMuon::anaMuon () {
  this->SetPtEtaPhiM(-99, -99, -99, muonMass);
  charge = -99;
  muonIndex = -99;
  muonIsLooseID = false;
  muonIsTightID = false;
  muonIsISO = false;
}

anaMuon::anaMuon (float pt, float eta, float phi , int c, int i, float mass = muonMass) {
  this->SetPtEtaPhiM(pt, eta, phi, mass);
  charge = c;
  muonIndex = i;
  muonIsLooseID = false;
  muonIsTightID = false;
  muonIsISO = false;
}

void anaMuon::clear () {
  this->SetPtEtaPhiM(-99, -99, -99, muonMass);
  charge = -99;
  muonIndex = -99;
  muonIsLooseID = false;
  muonIsTightID = false;
  muonIsISO = false;
}


///////////////////////////////////////////////////
// photons
class anaPhoton: public TLorentzVector {
  public:
    int photonIndex;
    float photonR9;
    float photonSCEta;
    anaPhoton();
    anaPhoton(float, float, float, int, float);
    void clear();
    bool operator > (const anaPhoton& compPhoton) const
    {
        return (this->Pt() > compPhoton.Pt());
    }
    ClassDef(anaPhoton, 1)
};



anaPhoton::anaPhoton () {
  this->SetPtEtaPhiM(-99, -99, -99, 0.);
  photonIndex = -99;
  photonR9 = -99;
  photonSCEta = -99;
}

anaPhoton::anaPhoton (float pt, float eta, float phi, int i, float mass = 0.0) {
  this->SetPtEtaPhiM(pt, eta, phi, mass);
  photonIndex = i;
  photonR9 = -99;
  photonSCEta = -99;
}

void anaPhoton::clear () {
  this->SetPtEtaPhiM(-99, -99, -99, 0.);
  photonIndex = -99;
  photonR9 = -99;
  photonSCEta = -99;
}


///////////////////////////////////////////////////
// gen Particles
class anaGenPart: public TLorentzVector {
  public:
    int charge;
    int partIndex;
    int pdgID;
    anaGenPart();
    anaGenPart(float pt, float eta, float phi , int c, int i, int pdg, float mass);
    void clear();
    bool operator > (const anaGenPart& compPart) const
    {
        return (this->Pt() > compPart.Pt());
    }
    ClassDef(anaGenPart, 1)
};

anaGenPart::anaGenPart () {
  this->SetPtEtaPhiM(-99, -99, -99, -99);
  charge = -99;
  partIndex = -99;
  pdgID = -99;
}

anaGenPart::anaGenPart (float pt, float eta, float phi , int c, int i, int pdg, float mass) {
  this->SetPtEtaPhiM(pt, eta, phi, mass);
  charge = c;
  partIndex = i;
  partIndex = pdg;
  pdgID = -99;
}

void anaGenPart::clear () {
  this->SetPtEtaPhiM(-99, -99, -99, -99);
  charge = -99;
  partIndex = -99;
  pdgID = -99;
}



#if !defined(__CINT__)
ClassImp(anaPhoton);
#endif