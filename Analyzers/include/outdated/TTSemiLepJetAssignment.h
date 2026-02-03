#ifndef TTSemiLepJetAssignment_h
#define TTSemiLepJetAssignment_h

#include "JHAnalyzerBase.h"

class TTSemiLepJetAssignment : public JHAnalyzerBase {

public:

  void initializeAnalyzer() override;
  void EventLoop() override;
  void TruthLoop() override;
  void RunLHEinfo();
  void RunGENinfo();


  bool CheckIsMuonChannel();
  bool CheckIsElectronChannel();
  void SetIsMuonChannel();
  void SetIsElectronChannel();
  
  void SetMuon(const Muon& _l1);
  void SetElectron(const Electron& _l1);
  
  void RunReco();
  pair<vector<int>,double> GetJetIndexSet_Chi2();
  vector<int> GetJetIndexSet_DNN();
  pair<double,double> GetChi2_and_vz(TLorentzVector &_lep, TLorentzVector &_MET, TLorentzVector &_blep, TLorentzVector &_q1, TLorentzVector &_q2, TLorentzVector &_bhad);
  double GetDNN(TLorentzVector &_lep, TLorentzVector &_MET, TLorentzVector &_blep, TLorentzVector &_q1, TLorentzVector &_q2, TLorentzVector &_bhad);
  void Run(TString _type);
  void FillHistAll(TString cutname);
  



  bool IsMuonChannel;
  bool IsElectronChannel;

  //For truth level into
  bool IsTauChannel_LHE;
  bool IsMuonChannel_LHE;
  bool IsElectronChannel_LHE;
  int bLepCharge_LHE;
  int bLep_True_genidx;
  int bLep_True_PID;

  int bHadCharge_LHE;
  int bHad_True_genidx;
  int bHad_True_PID;


  int Whad_q1_pid, Whad_q2_pid;
  vector<int> v_idx_lightquark_GEN;
  int idx_bquark_GEN, idx_bbarquark_GEN;
  int i_lepton_GEN,i_neutrino_GEN;
  void SetEventWeight();
  
  bool HasMatchedRecoJet(int genidx, double dRcut=0.4);
  bool HasFlavourMatchedRecoJet(int genidx);


  Lepton mu1;
  Lepton el1;
  TLorentzVector vtW;
  Lepton l1;
  unsigned int njet, nbjet;
  vector<Lepton> v_tightlep;

  vector<int> v_jetidx;
  vector<int> v_bjetidx;

  vector<Jet> v_tightjet;
  vector<Jet> v_bjet;

  TTSemiLepJetAssignment();
  ~TTSemiLepJetAssignment();


  bool noveto;
  bool HcbCR;

  int i_LightJet1,i_LightJet2;

};




#endif

