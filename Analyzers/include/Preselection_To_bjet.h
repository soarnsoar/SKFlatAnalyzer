#ifndef Preselection_To_bjet_h
#define Preselection_To_bjet_h

#include "JHAnalyzerBase.h"

class Preselection_To_bjet : public JHAnalyzerBase {

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

  bool FindMuonInBJet();
  bool FindElectronInBJet();


  bool RunSLTMuon();
  bool RunSLTElectron();
  void RunBJet();

  bool isDYbbar,isDYb;
  int bgenidx;


  bool IsDiMuonChannel;
  bool IsDiElectronChannel;
  void SetEventWeight();
  TString LepCh;
  TString gen_suffix;
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

  Preselection_To_bjet();
  ~Preselection_To_bjet();

  std::map<TString,double> N_1_weightmap;
  
  double dphi_z_b, ptzb;
  TString _JETPUID;
  //--flag
  bool check_tmva_input;
  bool lepveto;
  bool MuonOnly;
  bool apply_bchargeeff;

  float cut_jetcharge_dot_dnn;



  void FillHist_bjet(TString cutname);
  void FillHist_Z(TString cutname);
  void FillHist_muonmax(TString cutname, int im, double score);
  void FillHist_muonmin(TString cutname, int im, double score);
  void FillHist_electronmax(TString cutname, int im, double score);
  void FillHist_electronmin(TString cutname, int im, double score);


  //-----ApplyBChargeIDSF
  void ApplyBChargeIDSF();
};




#endif

