#ifndef TTSemiLepTrueBJetAnalyzer_h
#define TTSemiLepTrueBJetAnalyzer_h

#include "JHAnalyzerBase.h"

class TTSemiLepTrueBJetAnalyzer : public JHAnalyzerBase {

public:

  void initializeAnalyzer() override;
  void EventLoop() override;
  void TruthLoop() override;
  void RunLHEinfo();
  void RunGENinfo();


  
  void RunReco();


  void Run();

  //---EtaBinning--//
  vector<double> vEta;
  int nEta, nPt, nTotal;
  double Ptmax;
  int FindBinNumber(double this_eta);


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

  int GetBJet_TightJetIdx_dR_Flavour_Match(int i_GEN);
  pair<int,int> GetN_SLTMuon(Jet &_bjet, vector<Muon> &_muoncoll);
  int GetN_SLTElectron(Jet &_bjet, vector<Electron> &_electroncoll);
  void FillHist_this_bjet(Jet &_bjet, TString bjetname,int i_GEN);

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

  TTSemiLepTrueBJetAnalyzer();
  ~TTSemiLepTrueBJetAnalyzer();


  bool FlavourMatchOnly;

  int i_LightJet1,i_LightJet2;
  int iblep;
  int ibhad;
  int iq1;
  int iq2;
  int vz_fit;

  TLorentzVector Tlep_cand,Thad_cand,Wlep_cand,Whad_cand,neutrino_cand;

};




#endif

