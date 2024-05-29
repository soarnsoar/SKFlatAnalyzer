#ifndef EEMu_MuMuE_Method_h
#define EEMu_MuMuE_Method_h

#include "JHAnalyzerBase.h"

class EEMu_MuMuE_Method : public JHAnalyzerBase {

public:


  void initializeAnalyzer() override;
  void TruthLoop() override;
  void EventLoop() override;
  bool FindBJet();
  void RunMuonInJet();
  void RunMuonInJet_v2405_1();
  void RunMuonInJet_v2405_2();
  void RunMuonInJet_v2405_3();
  void RunElectronInJet();
  void RunElectronInJet_v2405_1();
  void RunElectronInJet_v2405_2();
  void RunElectronInJet_v2405_3();
  void FillHistMuon(TString cutname,Muon &muon);
  void FillHistElectron(TString cutname,Electron &electron);
  void FillHistBJet(TString cutname, Jet &jet);
  void FillHistNLepton(TString cutname);
  void CountEMuInJet(Jet &this_jet);
  void SetBranches(TTree *this_Tree);
  void FillTree_1bmuon();
  void FillTree_1belectron();
  void FillTree_0blepton();
  belectronvar Get_init_belectronvar();
  bmuonvar Get_init_bmuonvar();

  EEMu_MuMuE_Method();
  ~EEMu_MuMuE_Method();

  bool IsEE, IsMuMu;
  int idx_lhe_mu1, idx_lhe_mu2;
  int idx_lhe_e1, idx_lhe_e2;
  int idx_lhe_b;
  int pid_b;
  TString MuonID, ElectronID;
  double MuonMinPt, ElectronMinPt;
  double DeltaR_Mu, DeltaR_E;
  unsigned int nb, nbbar;
  double bcharge;
  TString bcharge_str, ll_str;
  int jetidx_b;

  int n_mu,n_e;
  int n_mup,n_ep;
  int n_mum,n_em;
  bool is_cut_v2405_1;
  bool is_cut_v2405_2;
  bool is_cut_v2405_3;
  bool isTreeMode;
  bool Has_bMuon;
  bool Has_bElectron;
  bmuonvar bmuon;
  belectronvar belectron;
  bjetvar bjet;
  int nbmuon, nbelectron;
  Muon current_bmuon;
  Electron current_belectron;
};




#endif

