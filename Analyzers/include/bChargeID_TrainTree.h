#ifndef bChargeID_TrainTree_h
#define bChargeID_TrainTree_h

#include "JHAnalyzerBase.h"

class bChargeID_TrainTree : public JHAnalyzerBase {

public:
  //--out tree--
  void InitOutputTree();
  void SetBranches(TTree *this_Tree);
  void SetTreeValue_bJet(Jet &jet);
  bool SetTreeValue_bMuon(Jet &jet);
  void Init_bMuonVars();
  bool SetTreeValue_bElectron(Jet &jet);
  void Init_bElectronVars();
  double GetP_JetRestFrame(TLorentzVector &lep, TLorentzVector &jet);
  double GetPt_wrt_Jet(TLorentzVector &lep, TLorentzVector &jet);
  //
  int Has_bMuon;
  int Has_bElectron;
  struct bmuonvar{
    double P_jetrest=0;
    double ptwrtbjet=0;
    double dR_l_j=0;
    double nsip3d=0;
    double reltrkiso=0;
    double reliso=0;
    double charge=0;
    
  };
  bmuonvar bmuon;
  struct belectronvar{
    double P_jetrest=0;
    double ptwrtbjet=0;
    double dR_l_j=0;
    double nsip3d=0;
    double reltrkiso=0;
    double reliso=0;
    double charge=0;
    double IsGsfCtfScPixChargeConsistent=0;
  };
  belectronvar belectron;
  struct bjetvar{
    double pt=0;
    double aeta=0;
    double ChargedHadronEnergyFraction=0;
    double NeutralHadronEnergyFraction=0;
    double NeutralEmEnergyFraction=0;
    double ChargedEmEnergyFraction=0;
    double MuonEnergyFraction=0;
    double charge=0;
    double partonFlavour=0;
  };
  bjetvar bjet;


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
  void FillHistAll(TString cutname);
  void FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max);



  bool IsDiMuonChannel;
  bool IsDiElectronChannel;
  void SetEventWeight();
  void SetEventNormWeight();
  TString LepCh;
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

  bChargeID_TrainTree();
  ~bChargeID_TrainTree();

  std::map<TString,double> N_1_weightmap;

  bool IsZbLHE;
  int lhe_b_pdgid;
};




#endif

