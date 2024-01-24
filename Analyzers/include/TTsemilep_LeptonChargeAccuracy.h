#ifndef TTsemilep_LeptonChargeAccuracy_h
#define TTsemilep_LeptonChargeAccuracy_h

#include "AnalyzerCore.h"
#include "TMVA/PyMethodBase.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include <set>
class TTsemilep_LeptonChargeAccuracy : public AnalyzerCore {

public:
  //temp
  double nevt;
  double nevt_samebb;

  //flags
  bool doDrawDNNinputs;

  double MW_pdg=80.379;
  double Width_W_pdg=2.085;
  double Width_Wqq_pdg=2.085*0.6741;
  double MTop_pdg=172.5;
  double Width_Top_pdg=1.42;
  double Width_Top_bqq_pdg=1.42*0.665;
  //

  //
  bool doReduction;
  //Eff. SFs
  //Triggers
  double trigsf;
  double mu_trigsf;
  double el_trigsf;
  //ID
  double lep_idsf;
  double mu_idsf;
  double el_idsf;
  //RECO
  double lep_recosf;
  double mu_recosf;
  double el_recosf;
  //trackingSF
  double mu_trksf;

  double btagsf;
  double prefire_weight;
  double puweight;

  double DNNcut;
  double taged_bjet_score;
  TString SKFLAT_WD;
  Event ev;


  vector<TString> MuonTriggerNames;
  vector<TString> MuonTriggerSFKeys;
  vector<TString> ElectronTriggerNames;
  vector<TString> ElectronTriggerSFKeys;
  
  double TriggerSafeCut_muon;
  double TriggerSafeCut_electron;


  double DNNscore;
  double MET;
  void initializeAnalyzer();

  ///DNN model for TTsemilep jet assignment
  void initJetAssignModel_muon();
  void initJetAssignModel_electron();
  TMVA::Reader* myreader_JetAssign_muon;
  TMVA::Reader* myreader_JetAssign_electron;
  ///DNN model for charge reliability
  void initChargeReliabilityModel_muon();
  void initChargeReliabilityModel_electron();
  void initChargeReliabilityModel_jet();
  TMVA::Reader* myreader_ChReliab_muon;
  TMVA::Reader* myreader_ChReliab_electron;
  TMVA::Reader* myreader_ChReliab_jet;
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

  //variable to handle 
  int bmuon1_idx,belectron1_idx;
  int bmuon1_charge,belectron1_charge;
  double bmuon1_DNN,belectron1_DNN;
  double bHadJet_DNN;
  double bLepJet_DNN;
  double p_jetrestf,dR_l_j,ip3d,nsip3d,reliso,reltrkiso;

  bool TTbarMuReco();
  bool TTbarElReco();
  bool CheckJets();
  void AnalyzeLHE();
  void executeEventFromParameter(AnalyzerParameter param);
  void FillHists(TString cutname);
  bool AnalyzerLHE();
  bool ApplyEventKinematicCut();
  void Check_bJet_Charge();

  
  void Set_bJet(bool Is_bHad);
  int _tightbjet_idx;
  bool _Is_bHad;
  void Check_bMuonScore();
  void Check_bElectronScore();
  TLorentzVector GetTransverseVector(TLorentzVector v);
  TLorentzVector GetTransverseVector(double pt, double phi);
  void FillHist_bJet(TString cutname);
  void FillHist_bHadJet(TString cutname);
  void FillHist_bLepJet(TString cutname);
  void FillHist_bmuon_in_bHad(TString cutname);
  void FillHist_bmuon_in_bLep(TString cutname);
  void FillHist_belectron_in_bHad(TString cutname);
  void FillHist_belectron_in_bLep(TString cutname);
 
  void FillHist_LeptonicTopSide(TString cutname);
  void FillHist_HadronicTopSide(TString cutname);
  JetTagging::Parameters jtp;
  JetTagging::Parameters jtp_loose;
  void executeEvent();

  bool RunSyst;
  bool RunNewPDF;
  bool RunXSecSyst;

  bool doDebug;

  TString IsoMuTriggerName;
  double TriggerSafePtCut;

  vector<Muon> AllMuons;
  unsigned int muonsize;
  vector<Electron> AllElectrons;
  unsigned int electronsize;
  vector<Jet> AllJets;
  unsigned int jetsize;
  vector<Jet> tightjets;
  unsigned int tightjetsize;
  vector<Jet> tightbjets;
  unsigned int tightbjetsize;

  vector<int> LightJetsTruePIDs;

  double weight;
  double base_weight;

  int tightjetidx_q1_flav_match,tightjetidx_q2_flav_match;
  
  //
  TString ProcessName;
  TString bHadMatchName;
  TString bLepMatchName;
  TString IncomingPartonTag;
  TString EventTag;
  std::vector<Gen> GENs;
  std::vector<LHE> LHEs;

  bool doPrint;
  int IsSig,IsBkg;
  
  //container for LHE info
  struct LHEinfo{
    int evt_nb;
    unsigned int LHEsize;
    unsigned int ngluon_incoming;
    unsigned int nb_incoming;
    unsigned int nb_outgoing;
    unsigned int abs_nb_outgoing;
    unsigned int nparton_outgoing;
    TLorentzVector vb;
    std::vector<int> incoming_parton_pid;

    double x_b;
    double x_g;
    double Q2;
    
    double i_lepn, i_lepp;
    int nincoming_b;
    int nincoming_bbar;
    
    bool IsMuonChannel;
    bool IsElectronChannel;
    bool IsTauChannel;
    int LeptonCharge;
    int bLep_charge;
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
    TLorentzVector vWhad;
    TLorentzVector vThad;
    int Whad_q1_pid;
    int Whad_q2_pid;
    int Whad_q1_genidx;
    int Whad_q2_genidx;

  };
  GENinfo myGEN;
  //container for RECO info
  struct RECOinfo{
    bool passMuonTrigger;
    bool passElectronTrigger;
    bool goodTTbarMu;
    bool goodTTbarEl;
    bool passMuonTriggerAndTTbarMu;
    bool passElectronTriggerAndTTbarEl;


    int idx_Tmuon;
    int idx_Telectron;
    int tightbjet_idx_bHad;
    int tightbjet_idx_bLep;
    int tightjet_idx_q1;
    int tightjet_idx_q2;
    TLorentzVector vt_lep_top;
    TLorentzVector vt_lep_W;
    TLorentzVector Whad,Thad;
    int TagLeptonCharge;
  };
  RECOinfo myRECO;

  struct bLeptonInfo{
    int idx;
    int charge;
    double dnn;
    double phi;
    double pt;
    double nsip3d;
    double ptwrtbjet;
    double eta;
    double p_jetrestf;
    double reltrkiso;
    double dR_l_j;
    double IsGsfCtfScPixChargeConsistent;
    bool IsExist;
  };
  bLeptonInfo bmuon_in_bHad;
  bLeptonInfo bmuon_in_bLep;
  bLeptonInfo belectron_in_bHad;
  bLeptonInfo belectron_in_bLep;

  struct bJetInfo{
    double dnn;
    double pt;
    double eta;
    double phi;
    double JetCharge;
    double chargedHadronEnergyFraction;
    double neutralHadronEnergyFraction;
    double neutralEmEnergyFraction;
    double chargedEmEnergyFraction;
    double muonEnergyFraction;
  };
  bJetInfo bHadJet;
  bJetInfo bLepJet;

  void FillTreeValues();
  void AnalyzeRECO();
  void AnalyzeGEN();
  
  //For Histograms//
  //---leptons


  //For Categorize
  TString ChannelLep;

  
  TTsemilep_LeptonChargeAccuracy();
  ~TTsemilep_LeptonChargeAccuracy();


  int nb_event;
  

  //---For Tree
  bool doFillTree;
  void InitValues();
  //-----Variables to Store for Machine Learning------//
  Float_t met_pt,met_phi;
  Float_t electron_pt,electron_phi,electron_eta;
  Float_t muon_pt, muon_phi, muon_eta;
  Float_t blep_pt,blep_phi,blep_eta,blep_E;
  Float_t bhad_pt,bhad_phi,bhad_eta,bhad_E;
  Float_t q1jet_pt,q1jet_phi,q1jet_eta,q1jet_E;
  Float_t q2jet_pt,q2jet_phi,q2jet_eta,q2jet_E;
  Float_t WhadCand_mass,ThadCand_mass;


};



#endif

