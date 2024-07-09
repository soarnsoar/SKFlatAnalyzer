#ifndef DNNOptimizer_h
#define DNNOptimizer_h

#include "JHAnalyzerBase.h"

class DNNOptimizer : public JHAnalyzerBase {

public:


  void initializeAnalyzer() override;
  void EventLoop() override;
  void TruthLoop() override;
  bool CheckIsDiMuonChannel(double min_mll=0., double max_mll=999999999.);
  bool CheckIsDiElectronChannel(double min_mll=0., double max_mll=999999999.);
  void SetIsDimuonChannel();
  void SetIsDielectronChannel();
  
  void SetMuon(const Muon& _l1, const Muon& _l2);
  void SetElectron(const Electron& _l1, const Electron& _l2);
  TLorentzVector GetDiMuonVector();
  TLorentzVector GetDiElectronVector();
  
  void RunBasicZregion();
  void RunBasicZregion_CheckSF();
  void FillHistAll(TString cutname);
  void FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max);
  void FillHistAllChannel(TString cutname);
  void FillHistAll_bmuon(TString cutname,bmuonvar this_bmuon);
  void FillHistAll_belectron(TString cutname,belectronvar this_belectron);
  void FillHistAll_bjet(TString cutname,bjetvar this_bjet);


  void SetBranches(TTree *this_Tree);
  double bmuon_score_max, bmuon_score_min;
  int bmuon_charge_max, bmuon_charge_min;

  double belectron_score_max, belectron_score_min;
  int belectron_charge_max, belectron_charge_min;

  double bjet_score, bjet_charge;

  bool isDYbbar,isDYb;

  bool IsDiMuonChannel;
  bool IsDiElectronChannel;
  void SetEventWeight();
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

  DNNOptimizer();
  ~DNNOptimizer();

  std::map<TString,double> N_1_weightmap;
  
  double dphi_z_b, ptzb;
  TString _JETPUID;
  bool check_tmva_input;
  bool lepveto;

  float cut_jetcharge_dot_dnn;
};




#endif

