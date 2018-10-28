#ifndef Muon_h
#define Muon_h

#include "Lepton.h"
#include "TString.h"

class Muon: public Lepton{

public:

  Muon();
  ~Muon();

  inline bool isPOGTight() const {return j_isPOGTight;}
  inline bool isPOGHighPt() const {return j_isPOGHighPt;}
  inline bool isPOGMedium() const {return j_isPOGMedium;}
  inline bool isPOGLoose() const {return j_isPOGLoose;}
  void SetisPOGTight(bool b);
  void SetisPOGHighPt(bool b);
  void SetisPOGMedium(bool b);
  void SetisPOGLoose(bool b);

  void SetIso(double ch04, double nh04, double ph04, double pu04, double trkiso);
  void CalcPFRelIso();
  inline double TrkIso() const {return j_trkiso;}
  double EA();

  void SetChi2(double chi2);
  inline double Chi2() const { return j_chi2; }

  void SetMiniAODPt(double d);
  inline double MiniAODPt() const {return j_MiniAODPt;}

  void SetMomentumUpDown(double up, double down);
  inline double MomentumUp() const {return j_MomentumUp;}
  inline double MomentumDown() const {return j_MomentumDown;}

  void SetTuneP4(double pt, double pt_err, double eta, double phi);
  inline Particle TuneP4() const {return j_TuneP4;}
  inline double TunePPtError() const {return j_TunePPtError;}

  //==== ID
  bool PassID(TString ID);
  bool Pass_POGTight();
  bool Pass_POGTightWithTightIso();
  bool Pass_POGHighPtWithLooseTrkIso();
  bool Pass_HNPairTight();
  bool Pass_HNPairLoose();
  bool Pass_HNPairVeto();
  bool Pass_HNWRTight();
  bool Pass_HNWRLoose();
  bool Pass_HNWRVeto();
  bool Pass_TESTID();

private:

  bool j_isPOGTight, j_isPOGHighPt, j_isPOGMedium, j_isPOGLoose;
  double j_chi2;
  double j_PFCH04, j_PFNH04, j_PFPH04, j_PU04, j_trkiso;
  double j_MiniAODPt, j_MomentumUp, j_MomentumDown;
  Particle j_TuneP4;
  double j_TunePPtError;

  ClassDef(Muon,1);
};

#endif
