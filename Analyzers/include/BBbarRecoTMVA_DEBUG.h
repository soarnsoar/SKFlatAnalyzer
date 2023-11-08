#ifndef BBbarRecoTMVA_DEBUG_h
#define BBbarRecoTMVA_DEBUG_h

#include "AnalyzerCore.h"
#include "TMVA/PyMethodBase.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include <set>
class BBbarRecoTMVA_DEBUG : public AnalyzerCore {

public:
  void print(TString a);
  int i_EVENT;
  Event ev;
  void initTMVAmodel_odd_pos();
  void initTMVAmodel_even_pos();
  void initTMVAmodel_odd_neg();
  void initTMVAmodel_even_neg();
  TMVA::Reader* myreader_odd_pos;
  TMVA::Reader* myreader_even_pos;
  TMVA::Reader* myreader_odd_neg;
  TMVA::Reader* myreader_even_neg;

  TGraph* tgr_odd_pos;
  TGraph* tgr_even_pos;
  TGraph* tgr_odd_neg;
  TGraph* tgr_even_neg;

  double CalcDNN();
  void initializeAnalyzer();
  bool ZmmReco();
  bool ZeeReco();
  bool Tag1bjet();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeExoticEvent();
  bool Tag_gbToZb();
  void Tag_B_Hadron();
  void Loop_genBMatchedRecoJet();
  void ParseReco();
  void HistConf();
  void RunProtoTypeMuon();
  void RunProtoTypeElectron();
  void RunLeptonCutStudyMuon();
  void RunLeptonCutStudyElectron();
  void FillHistMuonCharge(TString cutname);
  void FillHistMuon(TString cutname);
  void FillHistElectronCharge(TString cutname);
  void FillHistElectron(TString cutname);
  int Rank1n2Leptons(std::vector<int> &v_blep_idx, std::vector<double> &v_blep_value);
  int CheckIsBhadAndNb(int pid);
  int myevent;
  int isEvenEvent;
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

  double weight_Prefire;
  double weight;
  
  //
  TString ProcessName;
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

    double mZ;
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
  void AnalyzeGEN();
  void AnalyzeLHE();
  void AnalyzeJetInfos();

  vector<double> v_xscale_binning;
  vector<double> v_Q2scale_binning;
  double* xscale_binning;
  double* Q2scale_binning;
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
  TString Cat_b_bbar[10];
  TString Cat_Z_To_mm_ee[10];
  TString Cat_lepton_charge[10];
  TString Cat_1jet20[10];
  TString Cat_pTatJetRF2[10];
  unsigned int Cat_b_bbar_size;
  unsigned int Cat_Z_To_mm_ee_size;
  unsigned int Cat_lepton_charge_size;
  unsigned int Cat_1jet20_size;
  unsigned int Cat_pTatJetRF2_size;
  BBbarRecoTMVA_DEBUG();
  ~BBbarRecoTMVA_DEBUG();


  //---For Tree
  bool doFillTree;
  int i_bmuon1, i_bmuon2;
  void InitTreeValues();
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
  Float_t bmuon1_pt;
  Float_t bmuon1_eta;
  Float_t bmuon1_phi;
  Float_t bmuon1_ptwrtbjet;
  Float_t bmuon1_p_jetrestf;
  Float_t bmuon1_dR_l_j;
  Float_t bmuon1_nsip3d;
  Float_t bmuon1_reltrkiso;
  Float_t bmuon1_reliso;
  Int_t bmuon1_charge;
  Float_t bmuon1_charge_float;
  //subleading bmuon
  Float_t bmuon2_pt;
  Float_t bmuon2_eta;
  Float_t bmuon2_phi;
  Float_t bmuon2_ptwrtbjet;
  Float_t bmuon2_p_jetrestf;
  Float_t bmuon2_dR_l_j;
  Float_t bmuon2_nsip3d;
  Float_t bmuon2_reltrkiso;
  Float_t bmuon2_reliso;
  Int_t bmuon2_charge;
  Float_t bmuon2_charge_float;
  Int_t n_bmuon;
  Float_t n_bmuon_float;
  
  //leading belectron
  Float_t belectron1_pt;
  Float_t belectron1_eta;
  Float_t belectron1_phi;
  Float_t belectron1_ptwrtbjet;
  Float_t belectron1_p_jetrestf;
  Float_t belectron1_dR_l_j;
  Float_t belectron1_nsip3d;
  Float_t belectron1_reltrkiso;
  Float_t belectron1_elecalclusteriso;
  Int_t belectron1_IsGsfCtfScPixChargeConsistent;
  Float_t belectron1_IsGsfCtfScPixChargeConsistent_float;
  Float_t belectron1_reliso;
  Int_t belectron1_charge;
  Float_t belectron1_charge_float;
  //subleading belectron
  Float_t belectron2_pt;
  Float_t belectron2_eta;
  Float_t belectron2_phi;
  Float_t belectron2_ptwrtbjet;
  Float_t belectron2_p_jetrestf;
  Float_t belectron2_dR_l_j;
  Float_t belectron2_nsip3d;
  Float_t belectron2_reltrkiso;
  Float_t belectron2_elecalclusteriso;
  Int_t belectron2_IsGsfCtfScPixChargeConsistent;
  Float_t belectron2_IsGsfCtfScPixChargeConsistent_float;
  Float_t belectron2_reliso;
  Int_t belectron2_charge;
  Float_t belectron2_charge_float;
  Int_t n_belectron;
  Float_t n_belectron_float;
  //truth
  Int_t bjetPartonFlavourCharge;

  double DNN_odd_pos,DNN_even_pos,DNN_odd_neg,DNN_even_neg,DNN_b,DNN_s;
};



#endif

