#ifndef Electron_h
#define Electron_h

#include "Lepton.h"
#include "TString.h"

class Electron: public Lepton{

public:

  Electron();
  ~Electron();

  void SetSC(double sceta, double scphi, double sce);
  inline double scEta() const { return j_scEta; }
  inline double scPhi() const { return j_scPhi; }
  inline double scE() const { return j_scE; }
  void SetMVA(double mvaiso, double mvanoiso);
  inline double MVAIso() const { return j_mvaiso; }
  inline double MVANoIso() const { return j_mvanoiso; }

  void SetUncorrE(double une){ j_EnergyUnCorr = une; }
  double UncorrE() const { return j_EnergyUnCorr; }
  double UncorrPt() const { return Pt() * j_EnergyUnCorr/E(); }

  inline void SetPassConversionVeto(bool b) { j_passConversionVeto = b; }
  inline int PassConversionVeto() const { return j_passConversionVeto; }
  inline void SetNMissingHits(int n) { j_NMissingHits = n; }
  inline int NMissingHits() const { return j_NMissingHits; };

  enum EtaRegion{
    IB, OB, GAP, EC
  };
  EtaRegion etaRegion(){
    double sceta = fabs(scEta());
    if( sceta < 0.8 ) return IB;
    else if( sceta < 1.444 ) return OB;
    else if( sceta < 1.566 ) return GAP;
    else return EC;
  }
  
  void SetCutBasedIDVariables(
    double full5x5_sigmaIetaIeta,
    double dEtaSeed,
    double dPhiIn,
    double HoverE,
    double InvEminusInvP
  ){
    j_full5x5_sigmaIetaIeta = full5x5_sigmaIetaIeta;
    j_dEtaSeed = dEtaSeed;
    j_dPhiIn = dPhiIn;
    j_HoverE = HoverE;
    j_InvEminusInvP = InvEminusInvP;
  }
  double full5x5_sigmaIetaIeta() const { return j_full5x5_sigmaIetaIeta; }
  double dEtaSeed() const { return j_dEtaSeed; }
  double dPhiIn() const { return j_dPhiIn; }
  double HoverE() const { return j_HoverE; }
  double InvEminusInvP() const { return j_InvEminusInvP; }

  void SetPOGIDs(std::vector<bool> bs);
  inline bool passVetoID() const {return j_passVetoID;}
  inline bool passLooseID() const {return j_passLooseID;}
  inline bool passMediumID() const {return j_passMediumID;}
  inline bool passTightID() const {return j_passTightID;}
  inline bool passMVAID_noIso_WP80() const {return j_passMVAID_noIso_WP80;}
  inline bool passMVAID_noIso_WP90() const {return j_passMVAID_noIso_WP90;}
  inline bool passMVAID_iso_WP80() const {return j_passMVAID_iso_WP80;}
  inline bool passMVAID_iso_WP90() const {return j_passMVAID_iso_WP90;}
  inline bool passHEEPID() const {return j_passHEEPID;}
  bool Pass_SUSYMVAWP(TString wp);
  bool Pass_SUSYTight();
  bool Pass_SUSYLoose();
  bool Pass_HNPairTight();
  bool Pass_HNPairLoose();
  bool Pass_HNPairLooseNoIP();
  bool Pass_HNPairVeto();
  bool Pass_HNWRTight();
  bool Pass_HNWRLoose();
  bool Pass_HNWRVeto();

  void SetRelPFIso_Rho(double r);
  double EA();

  //==== ID
  bool PassID(TString ID);
  bool Pass_TESTID();

  bool Pass_CutBasedLooseNoIso();
  bool Pass_CutBasedVetoNoIso();
  bool Pass_CutBasedLoose();
  bool Pass_CutBasedVeto();
  void SetRho(double r){ j_Rho = r; }
  double Rho() const { return j_Rho; }

private:

  double j_scEta,j_scPhi, j_scE;
  double j_mvaiso, j_mvanoiso;
  double j_EnergyUnCorr;
  bool j_passConversionVeto;
  int j_NMissingHits;
  double j_full5x5_sigmaIetaIeta, j_dEtaSeed, j_dPhiIn, j_HoverE, j_InvEminusInvP;
  bool j_passVetoID;
  bool j_passLooseID;
  bool j_passMediumID;
  bool j_passTightID;
  bool j_passMVAID_noIso_WP80;
  bool j_passMVAID_noIso_WP90;
  bool j_passMVAID_iso_WP80;
  bool j_passMVAID_iso_WP90;
  bool j_passHEEPID;

  double j_RelPFIso_Rho;

  double j_Rho;

};

Electron::Electron() : Lepton() {
  j_scEta = -999.;
  j_scPhi = -999.;
  j_scE = -999.;
  j_mvaiso = -999.;
  j_mvanoiso = -999.;
  j_EnergyUnCorr = -999.;
  j_passConversionVeto = false;
  j_NMissingHits = 0;
  j_passVetoID = false;
  j_passLooseID = false;
  j_passMediumID = false;
  j_passTightID = false;
  j_passMVAID_noIso_WP80 = false;
  j_passMVAID_noIso_WP90 = false;
  j_passMVAID_iso_WP80 = false;
  j_passMVAID_iso_WP90 = false;
  j_passHEEPID = false;
  j_Rho = -999.;
  this->SetLeptonFlavour(ELECTRON);
}

Electron::~Electron(){
}

void Electron::SetSC(double sceta, double scphi, double sce){
  j_scEta = sceta;
  j_scPhi = scphi;
  j_scE = sce;
}
void Electron::SetMVA(double mvaiso, double mvanoiso){
  j_mvaiso = mvaiso;
  j_mvanoiso = mvanoiso;
}

void Electron::SetPOGIDs(std::vector<bool> bs){
  j_passVetoID = bs.at(0);
  j_passLooseID = bs.at(1);
  j_passMediumID = bs.at(2);
  j_passTightID = bs.at(3);
  j_passMVAID_noIso_WP80 = bs.at(4);
  j_passMVAID_noIso_WP90 = bs.at(5);
  j_passMVAID_iso_WP80 = bs.at(6);
  j_passMVAID_iso_WP90 = bs.at(7);
  j_passHEEPID = bs.at(8);
}

void Electron::SetRelPFIso_Rho(double r){
  j_passTightID = r;
  this->SetRelIso(r);
}

double Electron::EA(){

  //==== RecoEgamma/ElectronIdentification/data/Fall17/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt
  
  double eta = fabs(this->scEta());

  if     (eta<1.000) return 0.1440;
  else if(eta<1.479) return 0.1562;
  else if(eta<2.000) return 0.1032;
  else if(eta<2.200) return 0.0859;
  else if(eta<2.300) return 0.1116;
  else if(eta<2.400) return 0.1321;
  else if(eta<2.500) return 0.1654;
  else return 0.1654;

}

bool Electron::PassID(TString ID){

  //==== XXX veto Gap Always
  if(etaRegion()==GAP) return false;

  //==== POG
  if(ID=="passVetoID") return passVetoID();
  if(ID=="passLooseID") return passLooseID();
  if(ID=="passMediumID") return passMediumID();
  if(ID=="passTightID") return passTightID();
  if(ID=="passMVAID_noIso_WP80") return passMVAID_noIso_WP80();
  if(ID=="passMVAID_noIso_WP90") return passMVAID_noIso_WP90();
  if(ID=="passMVAID_iso_WP80") return passMVAID_iso_WP80();
  if(ID=="passMVAID_iso_WP90") return passMVAID_iso_WP90();
  if(ID=="passHEEPID") return passHEEPID();
  //==== Customized
  if(ID=="SUSYTight") return Pass_SUSYTight();
  if(ID=="SUSYLoose") return Pass_SUSYLoose();
  if(ID=="HNPairTight") return Pass_HNPairTight();
  if(ID=="HNPairLoose") return Pass_HNPairLoose();
  if(ID=="HNPairLooseNoIP") return Pass_HNPairLooseNoIP();
  if(ID=="HNPairVeto") return Pass_HNPairVeto();
  if(ID=="HNWRTight") return Pass_HNWRTight();
  if(ID=="HNWRLoose") return Pass_HNWRLoose();
  if(ID=="HNWRVeto") return Pass_HNWRVeto();
  if(ID=="NOCUT") return true;
  if(ID=="TEST") return Pass_TESTID();

  cout << "[Electron::PassID] No id : " << ID << endl;
  exit(EXIT_FAILURE);

  return false;
}

bool Electron::Pass_SUSYMVAWP(TString wp){

  double sceta = fabs(scEta());

    double cutA = 0.77;
    double cutB = 0.52;

  if(wp=="Tight"){
    if     (sceta<0.8)  { cutA = 0.77; cutB = 0.52; }
    else if(sceta<1.479){ cutA = 0.56; cutB = 0.11; } 
    else                { cutA = 0.48; cutB =-0.01; }
  }
  else if(wp=="Loose"){
    if     (sceta<0.8)  { cutA =-0.48; cutB =-0.85; }
    else if(sceta<1.479){ cutA =-0.67; cutB =-0.91; }
    else                { cutA =-0.49; cutB =-0.83; }
  }
  else{}

  double cutSlope = (cutB-cutA) / 10.;
  double cutFinal = std::min( cutA, std::max(cutB , cutA + cutSlope*(this->Pt()-15.) ) );

  //==== Using NoIso MVA, because we apply MiniIso later
  if(MVANoIso()>cutFinal) return true;
  else return false;

}

bool Electron::Pass_SUSYTight(){
  if(! Pass_SUSYMVAWP("Tight") ) return false;
  if(! (MiniRelIso()<0.1) ) return false;	
  if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1 && fabs(IP3D()/IP3Derr())<8.) ) return false;
  if(! PassConversionVeto() ) return false;
  if(! (NMissingHits()==0) ) return false;

  return true;
}

bool Electron::Pass_SUSYLoose(){
  if(! Pass_SUSYMVAWP("Loose") ) return false;
  if(! (MiniRelIso()<0.4) ) return false;
  if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1 && fabs(IP3D()/IP3Derr())<8.) ) return false;
  if(! PassConversionVeto() ) return false;
  if(! (NMissingHits()==0) ) return false;

  return true;
}

//==== HN Pair

bool Electron::Pass_HNPairTight(){
/*
  if(! Pass_SUSYMVAWP("Tight") ) return false;
  if(! (MiniRelIso()<0.1) ) return false;
  if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1 && fabs(IP3D()/IP3Derr())<8.) ) return false;
  if(! PassConversionVeto() ) return false;
  if(! (NMissingHits()<2) ) return false;
*/

  if(!Pass_CutBasedLooseNoIso()) return false;
  if(! (MiniRelIso()<0.1) ) return false;

  if( fabs(scEta()) <= 1.479 ){
    if(!( fabs(dXY())<0.05 )) return false;
    if(!( fabs(dZ()) <0.10 )) return false;
  }
  else{
    if(!( fabs(dXY())<0.10 )) return false;
    if(!( fabs(dZ()) <0.20 )) return false;
  }

  return true;
}

bool Electron::Pass_HNPairLoose(){
/*
  if(! Pass_SUSYMVAWP("Loose") ) return false;
  if(! (MiniRelIso()<0.4) ) return false;
  if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1 && fabs(IP3D()/IP3Derr())<8.) ) return false;
  if(! PassConversionVeto() ) return false;
  if(! (NMissingHits()<2) ) return false;
*/

  if(!Pass_CutBasedVetoNoIso()) return false;
  if(! (MiniRelIso()<0.6) ) return false;

  if( fabs(scEta()) <= 1.479 ){
    if(!( fabs(dXY())<0.05 )) return false;
    if(!( fabs(dZ()) <0.10 )) return false;
  }
  else{
    if(!( fabs(dXY())<0.10 )) return false;
    if(!( fabs(dZ()) <0.20 )) return false;
  }

  return true;

}

bool Electron::Pass_HNPairLooseNoIP(){
/*
  if(! Pass_SUSYMVAWP("Loose") ) return false;
  if(! (MiniRelIso()<0.4) ) return false;
  if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1 && fabs(IP3D()/IP3Derr())<8.) ) return false;
  if(! PassConversionVeto() ) return false;
  if(! (NMissingHits()<2) ) return false;
*/

  if(!Pass_CutBasedVetoNoIso()) return false;
  if(! (MiniRelIso()<0.6) ) return false;

  return true;

}

bool Electron::Pass_HNPairVeto(){
/*
  if(! Pass_SUSYMVAWP("Loose") ) return false;
  if(! (MiniRelIso()<0.4) ) return false;
*/

  if(!Pass_CutBasedVetoNoIso()) return false;
  if(! (MiniRelIso()<0.6) ) return false;
  
  return true;
}

//==== HN WR

bool Electron::Pass_HNWRTight(){

  if(!Pass_CutBasedLooseNoIso()) return false;
  if(! (RelIso()<0.15) ) return false;

  if( fabs(scEta()) <= 1.479 ){
    if(!( fabs(dXY())<0.05 )) return false;
    if(!( fabs(dZ()) <0.10 )) return false;
  }
  else{
    if(!( fabs(dXY())<0.10 )) return false;
    if(!( fabs(dZ()) <0.20 )) return false;
  }

  return true;
}

bool Electron::Pass_HNWRLoose(){

  if(!Pass_CutBasedVetoNoIso()) return false;
  if(! (RelIso()<0.6) ) return false;

  if( fabs(scEta()) <= 1.479 ){
    if(!( fabs(dXY())<0.05 )) return false;
    if(!( fabs(dZ()) <0.10 )) return false;
  }
  else{
    if(!( fabs(dXY())<0.10 )) return false;
    if(!( fabs(dZ()) <0.20 )) return false;
  }

  return true;

}

bool Electron::Pass_HNWRVeto(){

  if(!Pass_CutBasedVetoNoIso()) return false;
  if(! (RelIso()<0.6) ) return false;

  return true;
}

//==== TEST ID

bool Electron::Pass_TESTID(){
  return true;
}



bool Electron::Pass_CutBasedLooseNoIso(){

  if( fabs(scEta()) <= 1.479 ){

    if(! (full5x5_sigmaIetaIeta() < 0.0112) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00377) ) return false;
    if(! (fabs(dPhiIn()) < 0.0884) ) return false;
    if(! (HoverE() < 0.05 + 1.16/scE() + 0.0324*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.193) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }
  else{

    if(! (full5x5_sigmaIetaIeta() < 0.0425) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00674) ) return false;
    if(! (fabs(dPhiIn()) <  0.169 ) ) return false;
    if(! (HoverE() < 0.0441 + 2.54/scE() + 0.183*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.111) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }

}

bool Electron::Pass_CutBasedVetoNoIso(){
  
  if( fabs(scEta()) <= 1.479 ){
    
    if(! (full5x5_sigmaIetaIeta() < 0.0126 ) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00463 ) ) return false;
    if(! (fabs(dPhiIn()) < 0.148) ) return false;
    if(! (HoverE() < 0.05 + 1.16/scE() + 0.0324*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.209) ) return false;
    if(! (NMissingHits() <= 2) ) return false;
    if(! (PassConversionVeto()) ) return false;
    
    return true;
  
  }
  else{
    
    if(! (full5x5_sigmaIetaIeta() < 0.0457) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00814) ) return false;
    if(! (fabs(dPhiIn()) < 0.19) ) return false;
    if(! (HoverE() < 0.05 + 2.54/scE() + 0.183*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.132) ) return false;
    if(! (NMissingHits() <= 3) ) return false;
    if(! (PassConversionVeto()) ) return false;
    
    return true;
  
  }

}

bool Electron::Pass_CutBasedLoose(){

  if( fabs(scEta()) <= 1.479 ){

    if(! (full5x5_sigmaIetaIeta() < 0.0112) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00377) ) return false;
    if(! (fabs(dPhiIn()) < 0.0884) ) return false;
    if(! (HoverE() < 0.05 + 1.16/scE() + 0.0324*Rho()/scE()) ) return false;
    if(! (RelIso() < 0.112+0.506/UncorrPt()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.193) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }
  else{

    if(! (full5x5_sigmaIetaIeta() < 0.0425) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00674) ) return false;
    if(! (fabs(dPhiIn()) <  0.169 ) ) return false;
    if(! (HoverE() < 0.0441 + 2.54/scE() + 0.183*Rho()/scE()) ) return false;
    if(! (RelIso() < 0.108+0.963/UncorrPt()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.111) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }

}

bool Electron::Pass_CutBasedVeto(){

  if( fabs(scEta()) <= 1.479 ){

    if(! (full5x5_sigmaIetaIeta() < 0.0126 ) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00463 ) ) return false;
    if(! (fabs(dPhiIn()) < 0.148) ) return false;
    if(! (HoverE() < 0.05 + 1.16/scE() + 0.0324*Rho()/scE()) ) return false;
    if(! (RelIso() < 0.198+0.506/UncorrPt()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.209) ) return false;
    if(! (NMissingHits() <= 2) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }
  else{

    if(! (full5x5_sigmaIetaIeta() < 0.0457) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00814) ) return false;
    if(! (fabs(dPhiIn()) < 0.19) ) return false;
    if(! (HoverE() < 0.05 + 2.54/scE() + 0.183*Rho()/scE()) ) return false;
    if(! (RelIso() < 0.203+0.963/UncorrPt()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.132) ) return false;
    if(! (NMissingHits() <= 3) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }

}



#endif
