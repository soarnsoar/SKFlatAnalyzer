#ifndef TTSemiLepJetAssignment_ProduceTrainingTree_h
#define TTSemiLepJetAssignment_ProduceTrainingTree_h

#include "JHAnalyzerBase.h"

class TTSemiLepJetAssignment_ProduceTrainingTree : public JHAnalyzerBase {

public:

  void initializeAnalyzer() override;
  void EventLoop() override;
  void TruthLoop() override;
  void RunLHEinfo();
  void RunGENinfo();

  bool doReduction;
  int sig_mod, bkg_mod;

  bool CheckIsMuonChannel();
  bool CheckIsElectronChannel();
  void SetIsMuonChannel();
  void SetIsElectronChannel();
  
  void SetMuon(const Muon& _l1);
  void SetElectron(const Electron& _l1);
  
  void RunReco();

  void FillHistAll(TString cutname);
  
  void SetBranches(TTree *this_Tree);


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
  void SetEventWeight();
  
  bool HasMatchedRecoJet(int genidx, double dRcut=0.4);
  


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

  TTSemiLepJetAssignment_ProduceTrainingTree();
  ~TTSemiLepJetAssignment_ProduceTrainingTree();


  bool noveto;


  //---input variable--//
  double met_pt,met_phi;
  double lep_pt, lep_eta, lep_phi;
  double blep_pt, blep_eta, blep_phi, blep_E;
  double bhad_pt, bhad_eta, bhad_phi, bhad_E;
  double q1jet_pt, q1jet_eta, q1jet_phi, q1jet_E;
  double q2jet_pt, q2jet_eta, q2jet_phi, q2jet_E;
  double WhadCand_mass, ThadCand_mass;
  double WlepCand_mt, TlepCand_mt;



};




#endif

