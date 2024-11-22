#ifndef TTsemiLepChargeScoreEfficiencyMeasurement_h
#define TTsemiLepChargeScoreEfficiencyMeasurement_h

#include "JHAnalyzerBase.h"

class TTsemiLepChargeScoreEfficiencyMeasurement : public JHAnalyzerBase {

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


  void Run();
  void RunPlots();

  void RunBJet(TString bjetname, int bjetidx);
  
  bool RunBJetMuon(TString bjetname, int bjetidx);
  bool Run_HasSoftMuon(int bjetidx);
  bool RunSLTMuonPassCutToMax();
  bool RunSLTMuonPassCutToMin();

  bool RunBJetElectron(TString bjetname, int bjetidx);
  bool Run_HasSoftElectron(int bjetidx);
  bool RunSLTElectronPassCutToMax();
  bool RunSLTElectronPassCutToMin();

  void RunBJetCharge(TString bjetname, int bjetidx);

  void FillHistAll(TString cutname);
  void FillHistTTLJ(TString cutname);

  void FillHist_bjetinfo(TString cutname, int i_bjet, TString name_bjet);
  void FillHist_bCand(TString cutname);
  void FillHist_bCand_bmuon(TString cutname);
  void FillHist_bCand_belectron(TString cutname);
  
  void FillHistBJet(TString cutname, int bjetidx);

  void FillHistBJetMuonMax(TString cutname, int bjetidx);
  void FillHistBJetMuonMin(TString cutname, int bjetidx);

  void FillHistBJetElectronMax(TString cutname, int bjetidx);
  void FillHistBJetElectronMin(TString cutname, int bjetidx);

  
  void SetTopAndW();
  TString LepCh;


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

  TTsemiLepChargeScoreEfficiencyMeasurement();
  ~TTsemiLepChargeScoreEfficiencyMeasurement();

  //flags
  bool noveto;
  bool HcbCR;
  //bool FlavourMatchBase;
  bool ForBinning;
  bool LeptonPt50;
  bool njet4;
  bool MuonChargeOnly;
  bool ElectronChargeOnly;
  bool JetChargeOnly;
  bool bpt100;

  bool TurnOnFillHist;

  int i_LightJet1,i_LightJet2;
  int iblep;
  int ibhad;
  int iq1;
  int iq2;
  int vz_fit;

  TLorentzVector Tlep_cand,Thad_cand,Wlep_cand,Whad_cand,neutrino_cand;
  
  //pair<int,bool> bLepCand_Charge,bHadCand_Charge;
  //tuple<int,bool,int> bLepCand_Charge_info,bHadCand_Charge_info;
  //int bLepCand_Charge,bHadCand_Charge;
  //bool bLepCand_NotUseOppositeCharge,bHadCand_NotUseOppositeCharge;
  //int bLepCand_iLep, bHadCand_iLep;

  int bCand_Charge;
  bool bCand_NotUseOppositeCharge;
  int bCand_im;
  int bCand_ie;
  double bCnad_ChargeScore;

  bjetvar current_bjetvar;
  bmuonvar current_bmuonvar;
  belectronvar current_belectronvar;
  TString current_bjetname;



  int current_im_max;
  double current_bmuon_score_max;
  double current_bmuon_charge_max;

  int current_im_min;
  double current_bmuon_score_min;
  double current_bmuon_charge_min;


  int current_ie_max;
  double current_belectron_score_max;
  double current_belectron_charge_max;

  int current_ie_min;
  double current_belectron_score_min;
  double current_belectron_charge_min;


  
};




#endif

