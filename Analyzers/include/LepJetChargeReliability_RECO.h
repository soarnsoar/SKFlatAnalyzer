#ifndef LepJetChargeReliability_RECO_h
#define LepJetChargeReliability_RECO_h

#include "AnalyzerCore.h"
#include "TMVA/PyMethodBase.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include <set>
class LepJetChargeReliability_RECO : public AnalyzerCore {

public:

  //Eff. SFs
  //**Trigger
  double trigsf;
  double mu_trigsf;
  double el_trigsf;
  //**ID
  double lep_idsf;
  double mu_idsf;
  double el_idsf;
  //**RECO
  double lep_recosf;
  double mu_recosf;
  double el_recosf;
  //**trackingSF
  double mu_trksf;

  double btagsf;
  double prefire_weight;
  double puweight;

  double DNNcut;
  double taged_bjet_score;
  TString SKFLAT_WD;
  Event ev;

  bool IsTreeMode;
  bool IsTrainingMode;

  void initTMVAmodel_muon();
  void initTMVAmodel_electron();
  void initTMVAmodel_jet();
  TMVA::Reader* myreader_muon;
  TMVA::Reader* myreader_electron;
  TMVA::Reader* myreader_jet;

  TString MuonTriggerName;
  TString ElectronTriggerName;
  
  double TriggerSafeCut_muon1;
  double TriggerSafeCut_muon2;
  double TriggerSafeCut_electron1;
  double TriggerSafeCut_electron2;

  void CategorizeEvent();

  double CalcDNN();
  double DNNscore;
  double MET;
  void initializeAnalyzer();
  bool ZmmReco();
  bool ZeeReco();
  bool Tag1bjet();
  bool AnalyzeLHE();
  void executeEventFromParameter(AnalyzerParameter param);
  void FillHists(TString cutname);
  bool AnalyzerLHE();
  void Tag_B_Hadron();
  bool ApplyEventKinematicCut();
  void Loop_genBMatchedRecoJet();
  void ParseReco();
  void HistConf();
  void RunProtoTypeMuon();
  void RunProtoTypeElectron();
  void RunBMuon();
  void RunBElectron();
  void SetBJetDNNInput();
  int Rank1n2Leptons(std::vector<int> &v_blep_idx, std::vector<double> &v_blep_value);
  int CheckIsBhadAndNb(int pid);
  int myevent;
  int isEvenEvent;
  double btag_cut, bveto_cut;
  JetTagging::Parameters jtp;
  JetTagging::Parameters jtp_loose;
  struct MuonCut{
    double P_JetRest_min;
    double P_JetRest_max;
    double dR_l_bj_min;
    double dR_l_bj_max;
    double reltrkiso_min;
    double reltrkiso_max;
    double nsip3d_min;
    double nsip3d_max;
  };
  MuonCut MuonCut_v1p0;
  MuonCut MuonCut_apply;
  
  struct ElectronCut{
    double P_JetRest_min;
    double P_JetRest_max;
    double dR_l_bj_min;
    double dR_l_bj_max;
    double reltrkiso_min;
    double reltrkiso_max;
    double nsip3d_min;
    double nsip3d_max;
    bool bool_IsGsfCtfScPixChargeConsistent;
  };
  ElectronCut ElectronCut_v1p0;
  ElectronCut ElectronCut_apply;

  bool ZTagCuts();
  void BmatjetTag();
  void AnalyzeLeptons();
  void AnalyzeBmatJet();

  void executeEvent();

  bool RunSyst;
  bool RunNewPDF;
  bool RunXSecSyst;

  bool allow_tautau;
  bool doDebug;

  TString IsoMuTriggerName;
  double TriggerSafePtCut;

  vector<TString> MuonIDs, MuonIDSFKeys;
  vector<Muon> AllMuons;
  unsigned int muonsize;
  vector<Electron> AllElectrons;
  unsigned int electronsize;
  vector<Jet> AllJets;
  unsigned int jetsize;
  vector<Jet> tightjets;
  unsigned int tightjetsize;


  double weight;
  double base_weight;

  
  //
  TString ProcessName;
  TString IncomingPartonTag;
  TString EventTag;
  TString EventTagJetParton;
  std::vector<Gen> GENs;
  std::vector<LHE> LHEs;
  //std::vector<int> BmesonPIDs;
  set<int> BhadronPIDs;
  set<int> BhadronPIDs2;
  set<int> BhadronPIDs3;

  bool doPrint;


  //container for LHE info
  struct LHEinfo{
    int evt_nb;
    unsigned int LHEsize;
    unsigned int ngluon_incoming;
    unsigned int nb_incoming;
    unsigned int nb_outgoing;
    unsigned int abs_nb_outgoing;
    unsigned int nparton_outgoing;
    bool is_gbToZb;
    bool is_tautau;
    bool is_mumu;
    bool is_ee;
    TLorentzVector vb;
    std::vector<int> incoming_parton_pid;

    double x_b;
    double x_g;
    double Q2;
    
    double i_lepn, i_lepp;
    int nincoming_b;
    int nincoming_bbar;
  };
  LHEinfo myLHE;
  //container for GEN info
  struct GENinfo{
    unsigned int GENsize;
    int Bhad_idx;
    int Bhad_nb;
    int Bhad_pid;
    bool HasBhadron;
    TLorentzVector vBhad;

  };
  GENinfo myGEN;
  //container for RECO info
  struct RECOinfo{
    bool passMuonTrigger;
    bool passElectronTrigger;
    bool goodZmm;
    bool goodZee;
    bool passMuonTriggerAndZmm;
    bool passElectronTriggerAndZee;

    double mZ;
    TLorentzVector vZ;
    int ij_B;
    bool HasBmatchedRecoJet;
    TLorentzVector vBmatchedJet;
    double dRcut_bmatj_lep;
    double dRcut_bmatj_muon;
    double dRcut_bmatj_electron;
    unsigned int nBmatJet;
    int idx_Zmuon1, idx_Zmuon2;
    int idx_Zelectron1, idx_Zelectron2;
  };
  RECOinfo myRECO;

  void AnalyzeRECO();
  //void AnalyzeGEN();
  
  void AnalyzeJetInfos();
  void FillHistEventBase(TString cutname);
  void FillHistBMuon(TString cutname);
  void FillHistBElectron(TString cutname);
  void FillHistBJet(TString cutname);
  vector<double> v_xscale_binning;
  vector<double> v_Q2scale_binning;
  double* xscale_binning;
  double* Q2scale_binning;

  double dphi_z_b,pt_z,pt_zb;
  //For Histograms//
  //---leptons
  bool IsNotLepton(int i);
  bool oneCleanJet20Event; 
  bool BmatJet20Event; 

  //global varibles for recolevel
  double reltrkiso,reliso,ip3d,nsip3d,relecalclusteriso,
    p_jetrestf;
  int IsGsfCtfScPixChargeConsistent;
  double  dR_l_j;  
  int i_bmuon;
  int i_belectron;

  //jet
  Float_t dRToLHE,dRToBhad,ptratioToLHE,ptratioToBhad,charge_using_lep;

  //For Categorize
  TString ZllChannel;
  TString bLeptonChannel;
  
  LepJetChargeReliability_RECO();
  ~LepJetChargeReliability_RECO();


  vector<double> bmuon_charges;
  vector<double> bmuon_DNNs;
  vector<double> belectron_charges;
  vector<double> belectron_DNNs;
  double bjet_DNN;
  int nb_event;
  int evtcat_int;
  TString evtcat_str;
  double evtcharge,evtscore;
  
  //---For Tree
  bool doFillTree;
  bool StoreEvent;
  int i_bmuon1, i_bmuon2;
  double bmuon1_idx,bmuon1_DNN,bmuon1_charge;
  double belectron1_idx,belectron1_DNN,belectron1_charge;
  void InitValues();
  void SetTreeValuesMuon(int i_bmuon1,int i_bmuon2,int nbmuon);
  void SetTreeValuesElectron(int i_electron1,int i_electron2,int nbelectron);
  //-----Variables to Store for Machine Learning------//
  Float_t bjet_charge;
  Float_t bjet_pt;
  Float_t bjet_eta;
  Float_t bjet_phi;
  Float_t bjet_DeepJet;
  Float_t bjet_DeepJet_CvsL;
  Float_t bjet_DeepJet_CvsB;
  Float_t bjet_chargedHadronEnergyFraction;
  Float_t bjet_neutralHadronEnergyFraction;
  Float_t bjet_neutralEmEnergyFraction;
  Float_t bjet_chargedEmEnergyFraction;
  Float_t bjet_muonEnergyFraction;
  //leading bmuon
  Float_t bmuon_pt;
  Float_t bmuon_eta;
  Float_t bmuon_phi;
  Float_t bmuon_ptwrtbjet;
  Float_t bmuon_p_jetrestf;
  Float_t bmuon_dR_l_j;
  Float_t bmuon_nsip3d;
  Float_t bmuon_reltrkiso;
  Float_t bmuon_reliso;
  Int_t bmuon_charge;
  Float_t bmuon_charge_float;
  Int_t n_bmuon;
  
  //leading belectron
  Float_t belectron_pt;
  Float_t belectron_eta;
  Float_t belectron_phi;
  Float_t belectron_ptwrtbjet;
  Float_t belectron_p_jetrestf;
  Float_t belectron_dR_l_j;
  Float_t belectron_nsip3d;
  Float_t belectron_reltrkiso;
  Float_t belectron_elecalclusteriso;
  Float_t belectron_IsGsfCtfScPixChargeConsistent;
  Float_t belectron_IsGsfCtfScPixChargeConsistent_float;
  Float_t belectron_reliso;
  Int_t belectron_charge;
  Float_t belectron_charge_float;

  Int_t n_belectron;
  Float_t n_belectron_float;
  //truth
  Int_t bjetPartonFlavourCharge;

  double DNN_odd_pos,DNN_even_pos,DNN_odd_neg,DNN_even_neg,DNN_b,DNN_s;
};



#endif

