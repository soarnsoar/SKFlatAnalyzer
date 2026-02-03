#ifndef DYbTruth_h
#define DYbTruth_h

#include "JHAnalyzerBase.h"

class DYbTruth : public JHAnalyzerBase {

public:


  void initializeAnalyzer() override;
  void TruthLoop() override;
  void EventLoop() override;
  bool FindBJet();
  void RunMuonInJet();
  void RunMuonInJet_v2405_1();
  void RunMuonInJet_v2405_2();
  void RunMuonInJet_v2405_3();
  void RunMuonInJet_v2503_1();
  void RunMuonInJet_v2503_2();
  
  void RunElectronInJet();
  void RunElectronInJet_v2405_1();
  void RunElectronInJet_v2405_2();
  void RunElectronInJet_v2405_3();
  void RunElectronInJet_v2503_1();
  void RunElectronInJet_v2503_2();
  
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

  DYbTruth();
  ~DYbTruth();

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

  TString LepCh;

  bool IsDiMuonChannel;
  bool IsDiElectronChannel;

  bool CheckIsDiElectronChannel(double min_mll,double max_mll);
  void SetElectron(const Electron& _l1, const Electron& _l2);
  bool CheckIsDiMuonChannel(double min_mll,double max_mll);
  void SetMuon(const Muon& _l1, const Muon& _l2);

  Muon mu1, mu2;
  Electron el1, el2;
  Lepton l1, l2;
  TLorentzVector vZ;


  double z_pt,z_eta,z_phi,z_mass,jet_pt,jet_eta,jet_phi,jet_mass;

  double z_rapidity,jet_rapidity,z_jet_rapidity,z_minus_jet_rapidity;
  double true_z_rapidity,true_b_rapidity,true_z_b_rapidity,true_z_minus_b_rapidity;
  
  double true_z_pt,true_z_eta,true_z_phi,true_z_mass;
  double true_b_pt,true_b_eta,true_b_phi,true_b_mass;
  double x_b,x_g;
  
  int n_mu,n_e;
  int n_mup,n_ep;
  int n_mum,n_em;
  bool is_cut_v2405_1;
  bool is_cut_v2405_2;
  bool is_cut_v2405_3;
  bool is_cut_v2503_1;
  bool is_cut_v2503_2;
  bool isTreeMode;
  bool lepveto;
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

