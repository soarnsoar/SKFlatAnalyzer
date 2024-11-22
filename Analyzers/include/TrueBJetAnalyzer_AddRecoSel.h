#ifndef TrueBJetAnalyzer_AddRecoSel_h
#define TrueBJetAnalyzer_AddRecoSel_h

#include "JHAnalyzerBase.h"

class TrueBJetAnalyzer_AddRecoSel : public JHAnalyzerBase {

public:

  void initializeAnalyzer() override;
  void EventLoop() override;
  void TruthLoop() override;
  void RunLHEinfo();
  void RunGENinfo();


  
  void RunReco();


  void Run(int i_GEN);

  bool UseSingleLepSel;

  //---EtaBinning--//
  vector<double> vEta;
  int nEta, nPt, nTotal;
  double Ptmax;
  int FindBinNumber(double this_eta);

  //For truth level into
  TString ll_str;
  bool IsE, IsMu, IsTau;
  int nE,nMu,nTau;

  int idx_lhe_mu1, idx_lhe_mu2;
  int idx_lhe_e1, idx_lhe_e2;
  int idx_lhe_b;
  int pid_b;
  unsigned int nb;

  vector<int> v_idx_bquark_GEN,v_idx_bbarquark_GEN;

  void SetEventWeight();
  
  bool HasMatchedRecoJet(int genidx, double dRcut=0.4);
  bool HasFlavourMatchedRecoJet(int genidx);

  int GetBJet_TightJetIdx_dR_Flavour_Match(int i_GEN);
  pair<int,int> GetN_SLTMuon(Jet &_bjet, vector<Muon> &_muoncoll);
  int GetN_SLTElectron(Jet &_bjet, vector<Electron> &_electroncoll);
  void FillHist_this_bjet(Jet &_bjet,TString bjetname, int i_GEN);

  Lepton mu1,mu2;
  Lepton el1,el2;
  TLorentzVector vtW;
  Lepton l1,l2;
  unsigned int njet, nbjet;
  vector<Lepton> v_tightlep;

  vector<int> v_jetidx;
  vector<int> v_bjetidx;

  vector<Jet> v_tightjet;
  vector<Jet> v_bjet;

  TrueBJetAnalyzer_AddRecoSel();
  ~TrueBJetAnalyzer_AddRecoSel();

  //flags
  bool FlavourMatchOnly;
  bool AddRecoSel;


  TLorentzVector Tlep_cand,Thad_cand,Wlep_cand,Whad_cand,neutrino_cand;

  //--reco

  void SetElectron(const Electron& _l1);
  void SetMuon(const Muon& _l1);
  bool CheckIsSingleMuonChannel();
  bool CheckIsSingleElectronChannel();
  bool PassSingleLeptonCut();
  void SetMuon(const Muon& _l1, const Muon& _l2);
  bool CheckIsDiMuonChannel(double min_mll,double max_mll);
  void SetElectron(const Electron& _l1, const Electron& _l2);
  bool CheckIsDiElectronChannel(double min_mll,double max_mll);
  bool PassDiLeptonCut();
  bool PassPresel();


};




#endif

