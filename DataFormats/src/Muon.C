#include "Muon.h"

ClassImp(Muon)

Muon::Muon() : Lepton() {
  j_isPOGTight = false;
  j_isPOGHighPt = false;
  j_isPOGMedium = false;
  j_isPOGLoose = false;
  j_chi2 = 999.;
  j_PFCH04 = -999.;
  j_PFNH04 = -999.;
  j_PFPH04 = -999.;
  j_PU04 = -999.;
  j_trkiso = -999.;
  this->SetLeptonFlavour(MUON);
  j_MiniAODPt = -999.;
  j_MomentumUp = -999.;
  j_MomentumDown = -999.;
  j_TunePPtError = -999.;
}

Muon::~Muon(){
}

void Muon::SetisPOGTight(bool b){
  j_isPOGTight = b;
}
void Muon::SetisPOGHighPt(bool b){
  j_isPOGHighPt = b;
}
void Muon::SetisPOGMedium(bool b){
  j_isPOGMedium = b;
}
void Muon::SetisPOGLoose(bool b){
  j_isPOGLoose = b;
}

void Muon::SetIso(double ch04, double nh04, double ph04, double pu04, double trkiso){
  j_PFCH04 = ch04;
  j_PFNH04 = nh04;
  j_PFPH04 = ph04;
  j_PU04 = pu04;
  j_trkiso = trkiso;
  CalcPFRelIso();
}

void Muon::SetChi2(double chi2){
  j_chi2 = chi2;
}

void Muon::CalcPFRelIso(){
  double absiso = j_PFCH04+std::max( 0., j_PFNH04 + j_PFPH04 - 0.5*j_PU04 );
  //cout << "[Muon::CalcPFRelIso] j_PFCH04 = " << j_PFCH04 << endl;
  //cout << "[Muon::CalcPFRelIso] j_PFNH04 = " << j_PFNH04 << endl;
  //cout << "[Muon::CalcPFRelIso] j_PFPH04 = " << j_PFPH04 << endl;
  //cout << "[Muon::CalcPFRelIso] j_PU04 = " << j_PU04 << endl;
  //cout << "[Muon::CalcPFRelIso] --> absiso = " << absiso << endl;
  this->SetRelIso(absiso/this->Pt());
}

double Muon::EA(){

  double eta = fabs(this->Eta());

  if     (eta<0.8000) return 0.0566;
  else if(eta<1.3000) return 0.0562;
  else if(eta<2.0000) return 0.0363;
  else if(eta<2.2000) return 0.0119;
  else if(eta<2.4000) return 0.0064;
  else return 0.0064;

}

void Muon::SetMiniAODPt(double d){
  j_MiniAODPt = d;
}
void Muon::SetMomentumUpDown(double up, double down){
  j_MomentumUp = up;
  j_MomentumDown = down;
}

void Muon::SetTuneP4(double pt, double pt_err, double eta, double phi){
  j_TuneP4.SetPtEtaPhiM(pt,eta,phi,M());
  j_TuneP4.SetCharge(Charge()); //FIXME later, used TuneP charge
  j_TunePPtError = pt_err;
}

bool Muon::PassID(TString ID){
  //==== POG
  if(ID=="POGTight") return isPOGTight();
  if(ID=="POGHighPt") return isPOGHighPt();
  if(ID=="POGMedium") return isPOGMedium();
  if(ID=="POGLoose") return isPOGLoose();
  if(ID=="POGTightWithTightIso") return Pass_POGTightWithTightIso();
  if(ID=="POGHighPtWithLooseTrkIso") return Pass_POGHighPtWithLooseTrkIso();
  //==== Customized
  if(ID=="HNPairTight") return Pass_HNPairTight();
  if(ID=="HNPairLoose") return Pass_HNPairLoose();
  if(ID=="HNPairVeto") return Pass_HNPairVeto();
  if(ID=="HNWRTight") return Pass_HNWRTight();
  if(ID=="HNWRLoose") return Pass_HNWRLoose();
  if(ID=="HNWRVeto") return Pass_HNWRVeto();
  if(ID=="TEST") return Pass_TESTID();

  cout << "[Electron::PassID] No id : " << ID << endl;
  exit(EXIT_FAILURE);

  return false;

}
bool Muon::Pass_POGTightWithTightIso(){
  if(!( isPOGTight() )) return false;
  if(!( RelIso()<0.15 ))  return false;
  return true;
}
bool Muon::Pass_POGHighPtWithLooseTrkIso(){
  if(!( isPOGHighPt() )) return false;
  if(!( TrkIso()/TuneP4().Pt()<0.1 )) return false;
  return true;
}

//==== HN Pair

bool Muon::Pass_HNPairTight(){
  if(! isPOGMedium() ) return false;
  if(! (MiniRelIso()<0.2) ) return false;
  if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1 && fabs(IP3D()/IP3Derr())<4.) ) return false;
  return true;
}
bool Muon::Pass_HNPairLoose(){
  if(! isPOGMedium() ) return false;
  if(! (MiniRelIso()<0.6) ) return false;
  return true;
}
bool Muon::Pass_HNPairVeto(){
  if(! isPOGLoose() ) return false;
  if(! (MiniRelIso()<0.6) ) return false;
  return true;
}

//==== HN WR

bool Muon::Pass_HNWRTight(){
  if(! isPOGMedium() ) return false;
  if(! (RelIso()<0.15) ) return false;
  if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1) ) return false;
  return true;
}
bool Muon::Pass_HNWRLoose(){
  if(! isPOGMedium() ) return false;
  if(! (RelIso()<0.6) ) return false;
  if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1) ) return false;
  return true;
}
bool Muon::Pass_HNWRVeto(){
  if(! isPOGLoose() ) return false;
  if(! (RelIso()<0.6) ) return false;
  return true;
}

//==== TEST ID

bool Muon::Pass_TESTID(){
  if(! isPOGLoose() ) return false;
  if(! (MiniRelIso()<0.6) ) return false;
  if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1 && fabs(IP3D()/IP3Derr())<4.) ) return false;
  return true;
}
