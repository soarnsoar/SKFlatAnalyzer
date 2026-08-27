#ifndef PreselectionAnalyzer_h
#define PreselectionAnalyzer_h

#include "JHAnalyzerBase.h"

class PreselectionAnalyzer : public JHAnalyzerBase {

public:
  //
  bool bdt_v2608_2=false;
  
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
  void FillHistAllChannel(TString cutname);
  void FillHistAllChannelWithSuffix(TString cutname);
  void FillHistAll_bmuon(TString cutname,bmuonvar this_bmuon);
  void FillHistAll_belectron(TString cutname,belectronvar this_belectron);
  void FillHistAll_bjet(TString cutname,bjetvar this_bjet);


  void FillBDTOptHistsMuE();
  void FillBDTOptHistsJet();
  void FillBDTOptHistsJetFin();
  void FillBDTOptHistsGivenCut(double cut_to_muon_high,double cut_to_muon_low,double cut_to_electron_high,double cut_to_electron_low);
  int GetMeasuredCharge(double cut_to_muon_high,double cut_to_muon_low,double cut_to_electron_high,double cut_to_electron_low);

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
  vector<int> v_tightmuonidx;
  vector<int> v_tightelectronidx;

  
  vector<int> v_jetidx;
  vector<int> v_bjetidx;

  vector<Jet> v_tightjet;
  vector<Jet> v_bjet;


  TString suffix_true_nb;
  int i_proc; //1:dyb 2:dyothers 3: bkg 0 :data
  PreselectionAnalyzer();
  ~PreselectionAnalyzer();

  std::map<TString,double> N_1_weightmap;
  double met_pt,z_pt;
  double dphi_z_b, ptzb;
  TString _JETPUID;
  bool check_tmva_input;
  bool lepveto;
  bool newlepveto;
  bool jetvetotest;
  bool kincutopt;
  bool bdtopt;
  bool bdtopt_mue;
  bool bdtopt_jet;
  bool bdtopt_jetfin;


  
  bool doxrange,xrangetree;
  bool bdtcut;
  double maxMET,min_dphi_z_b,min_z_pt,max_ptzb;

  double x_b,x_g;
  double bjet_y,bjet_eta,z_eta,z_y,zbjet_y,zbjet_m;
  vector<pair<double,double>> m_score_region;
  vector<pair<double,double>> e_score_region;
  vector<pair<double,double>> j_score_region; 
  //for optimization
  bool IsDYbplus,IsDYbminus,IsBKG;
  vector<double> v_muonscore;
  vector<double> v_muoncharge;
  vector<double> v_electronscore;
  vector<double> v_electroncharge;  
  double jetscore,jetcharge;

  vector<double> v_cut_to_muon_high;
  vector<double> v_cut_to_muon_low;
  vector<double> v_cut_to_electron_high;
  vector<double> v_cut_to_electron_low;
  //for bdtopt
  //double Measured_Q;
  //static const TString Arr_Measured_Q_Str[9];

  double opt_cut_to_muon_high,opt_cut_to_muon_low,opt_cut_to_electron_high,opt_cut_to_electron_low;
};




#endif

