#ifndef ForLepJetChargeReliability_h
#define ForLepJetChargeReliability_h

#include "AnalyzerCore.h"
#include <set>
class ForLepJetChargeReliability : public AnalyzerCore {

public:
  bool isEventGroup1;
  bool isEventGroup2;
  void initializeAnalyzer();

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
  double dRToLHE,dRToBhad,ptratioToLHE,ptratioToBhad,charge_using_lep;

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
  ForLepJetChargeReliability();
  ~ForLepJetChargeReliability();


  //---For Tree
  bool doFillTree;
  void InitTreeValues();
  void SetTreeValuesMuon(vector<int> vmuonidx);
  void SetTreeValuesElectron(vector<int> velectronidx);
  //-----Variables to Store for Machine Learning------//
  double bjet_charge;
  double bjet_pt;
  double bjet_eta;
  double bjet_phi;
  double bjet_DeepJet;
  double bjet_DeepJet_CvsL;
  double bjet_DeepJet_CvsB;
  double bjet_chargedHadronEnergyFraction;
  double bjet_neutralHadronEnergyFraction;
  double bjet_neutralEmEnergyFraction;
  double bjet_chargedEmEnergyFraction;
  double bjet_muonEnergyFraction;

  double bmuon_pt;
  double bmuon_eta;
  double bmuon_phi;
  double bmuon_ptwrtbjet;
  double bmuon_p_jetrestf;
  double bmuon_dR_l_j;
  double bmuon_nsip3d;
  double bmuon_reltrkiso;
  double bmuon_reliso;
  int bmuon_charge;
  int n_bmuon;
  

  double belectron_pt;
  double belectron_eta;
  double belectron_phi;
  double belectron_ptwrtbjet;
  double belectron_p_jetrestf;
  double belectron_dR_l_j;
  double belectron_nsip3d;
  double belectron_reltrkiso;
  double belectron_elecalclusteriso;
  int belectron_IsGsfCtfScPixChargeConsistent;
  double belectron_reliso;
  int belectron_charge;
  int n_belectron;
  //truth
  int bjetPartonFlavourCharge;


};



#endif

