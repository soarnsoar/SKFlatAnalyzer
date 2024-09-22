#ifndef TTdiLepChargeScoreEfficiencyMeasurement_h
#define TTdiLepChargeScoreEfficiencyMeasurement_h

#include "JHAnalyzerBase.h"

class TTdiLepChargeScoreEfficiencyMeasurement : public JHAnalyzerBase {

public:


  void initializeAnalyzer() override;
  void EventLoop() override;
  
  bool CheckIsDiMuonChannel(double min_mll=0., double max_mll=999999999.);
  bool CheckIsDiElectronChannel(double min_mll=0., double max_mll=999999999.);
  void SetIsDimuonChannel();
  void SetIsDielectronChannel();
  
  void SetMuon(const Muon& _l1, const Muon& _l2);
  void SetElectron(const Electron& _l1, const Electron& _l2);
  TLorentzVector GetDiMuonVector();
  TLorentzVector GetDiElectronVector();
  
  void RunReco();

  void FillHistAll(TString cutname);
  void FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max);
  void FillHist_bjetinfo(TString cutname, int i_bjet, TString Name_bCand);
  TString current_bjetname;
  bjetvar current_bjetvar;
  bmuonvar current_bmuonvar;
  belectronvar current_belectronvar;


  void FillHist_bCand(TString cutname);
  void FillHist_bCand_bmuon(TString cutname);
  void FillHist_bCand_belectron(TString cutname);

  bool bCand_NotUseOppositeCharge;
  int bCand_im;
  int bCand_ie;
  double bCnad_ChargeScore;
  int bCand_Charge;

  bool IsDiMuonChannel;
  bool IsDiElectronChannel;
  void SetEventWeight();
  void SetEventNormWeight();
  TString LepCh;
  int mu1idx,mu2idx,el1idx,el2idx;
  Muon mu1, mu2;
  Electron el1, el2;
  TLorentzVector vZ;
  Lepton l1, l2;
  TLorentzVector l1_uncorr, l2_uncorr;
  unsigned int njet, nbjet;
  vector<Lepton> v_tightlep;

  vector<int> v_jetidx;
  vector<int> v_bjetidx;

  vector<Jet> v_tightjet;
  vector<Jet> v_bjet;

  TTdiLepChargeScoreEfficiencyMeasurement();
  ~TTdiLepChargeScoreEfficiencyMeasurement();

  std::map<TString,double> N_1_weightmap;


  bool lepveto;
  TString _JETPUID;
};




#endif

