#ifndef SMP_Validation_h
#define SMP_Validation_h

#include "AnalyzerCore.h"

class SMP_Validation : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(TString channelname,Event* ev);
  void executeEvent();
  void FillGenHists(TString pre,TString suf,TLorentzVector genl0,TLorentzVector genl1,TLorentzVector genfsr,double w);
  void FillBasicHists(TString pre,TString suf,const vector<Lepton*>& leps,double weight);
  void FillSystematicHists(TString pre,TString suf,const vector<Lepton*>& leps,map<TString,double> map_systematic);
  double GetZPtWeight(double zpt,double zrap,Lepton::Flavour flavour);
  double DileptonTrigger_SF(TString SFhistkey0,TString SFhistkey1,const vector<Lepton*>& leps,int sys);
  void PrintGens(const vector<Gen>& gens);
  double GetBinContentUser(TH2* hist,double valx,double valy,int sys);

  static const int zptcor_nptbin=46;
  const double zptcor_ptbin[zptcor_nptbin+1]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,22,24,26,28,30,32,34,36,38,40,44,48,52,56,60,70,80,90,100,120,140,160,180,200,250,400};
  static const int zptcor_nybin=3;
  const double zptcor_ybin[zptcor_nybin+1]={0,0.5,1,3};

  TH2D *hzpt_muon,*hzpt_electron,*hzpt_norm_muon,*hzpt_norm_electron;
  TString prefix;
  double zptcor;

  SMP_Validation();
  ~SMP_Validation();

};



#endif

