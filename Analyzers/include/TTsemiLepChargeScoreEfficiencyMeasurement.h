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


  void RunBJet(TString bjetname, int bjetidx, int bgenidx, TLorentzVector& Tcand);
  





  void FillHistOtherObject(TString cutname);

  void FillHistBJet(TString cutname, int bjetidx, int bgenidx, TLorentzVector &Tcand);
  TString GetCutSuffix(double this_bjet_pt, double this_bjet_eta,bool ignore_etabin=false);
  TString cut_suffix;

  
  void SetTopAndW();
  TString LepCh, LepSign;


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
  vector<int> v_tightmuonidx;
  vector<int> v_tightelectronidx;

  vector<int> v_jetidx;
  vector<int> v_bjetidx;

  vector<Jet> v_tightjet;
  vector<Jet> v_bjet;

  TTsemiLepChargeScoreEfficiencyMeasurement();
  ~TTsemiLepChargeScoreEfficiencyMeasurement();

  //flags
  bool noveto;
  bool HcbCR;
  bool newlepveto;
  //bool TopMassWindow;
  bool chi2kincut;
  //bool ApplyBtagSF;
  bool splitcharge;
  bool noetabin;
  bool HighJetOnly;
  bool RunBasicObjectOnly;
  bool NoJetVeto;
  bool use_dasym;
  //bool FlavourMatchBase;
  bool ForBinning;
  bool LeptonPt50;
  bool njet4;
  bool MuonChargeOnly;
  bool ElectronChargeOnly;
  bool JetChargeOnly;
  bool simplecat;
  bool ForMeasure;
  bool apply_bchargeideff;
  bool apply_bchargeeff_TT;
  TString JETPUID="";
  //bool TurnOnFillHist;

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
  double bCand_ChargeScore;


  TString current_bjetname;

  double jetscore,jetcharge;

  



  
};




#endif

