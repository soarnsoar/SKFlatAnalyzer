#ifndef DYbTrueBJetAnalyzer_h
#define DYbTrueBJetAnalyzer_h

#include "JHAnalyzerBase.h"

class DYbTrueBJetAnalyzer : public JHAnalyzerBase {

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
  TString ll_str;
  bool IsEE, IsMuMu;
  int idx_lhe_mu1, idx_lhe_mu2;
  int idx_lhe_e1, idx_lhe_e2;
  int idx_lhe_b;
  int pid_b;
  unsigned int nb, nbbar;

  int idx_bquark_GEN,idx_bbarquark_GEN;

  void SetEventWeight();
  
  bool HasMatchedRecoJet(int genidx, double dRcut=0.4);
  bool HasFlavourMatchedRecoJet(int genidx);

  int GetBJet_TightJetIdx_dR_Flavour_Match(int i_GEN);
  pair<int,int> GetN_SLTMuon(Jet &_bjet, vector<Muon> &_muoncoll);
  int GetN_SLTElectron(Jet &_bjet, vector<Electron> &_electroncoll);
  void FillHist_this_bjet(Jet &_bjet,TString bjetname, int i_GEN);

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

  DYbTrueBJetAnalyzer();
  ~DYbTrueBJetAnalyzer();


  bool FlavourMatchOnly;



  TLorentzVector Tlep_cand,Thad_cand,Wlep_cand,Whad_cand,neutrino_cand;

};




#endif

