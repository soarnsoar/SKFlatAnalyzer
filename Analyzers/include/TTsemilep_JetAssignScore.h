#ifndef TTsemilep_JetAssignScore_h
#define TTsemilep_JetAssignScore_h

#include "AnalyzerCore.h"
#include "TMVA/PyMethodBase.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include <set>
class TTsemilep_JetAssignScore : public AnalyzerCore {

public:
  //temp
  double nevt;
  double nevt_samebb;

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


  double TriggerSafeCut_muon;
  double TriggerSafeCut_electron;



  double DNNscore;
  double MET;
  void initializeAnalyzer();
  void initTMVAmodel_muon();
  void initTMVAmodel_electron();
  TMVA::Reader* myreader_muon;
  TMVA::Reader* myreader_electron;

  


  bool TTbarMuReco();
  bool TTbarElReco();
  bool CheckJets();
  void AnalyzeLHE();
  void executeEventFromParameter(AnalyzerParameter param);
  void FillHists(TString cutname);
  bool AnalyzerLHE();
  bool ApplyEventKinematicCut();
  JetTagging::Parameters jtp;
  JetTagging::Parameters jtp_loose;
  void executeEvent();

  bool RunSyst;
  bool RunNewPDF;
  bool RunXSecSyst;

  bool doDebug;

  TString IsoMuTriggerName;
  double TriggerSafePtCut;


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

    int ij_B;
    bool HasBmatchedRecoJet;
    TLorentzVector vBmatchedJet;
    double dRcut_bmatj_lep;
    double dRcut_bmatj_muon;
    double dRcut_bmatj_electron;
    unsigned int nBmatJet;
    int idx_Tmuon;
    int idx_Telectron;
    int idx_bbarjet;
    int idx_bjet;
    
  };
  RECOinfo myRECO;
  void FillTreeValues();
  void AnalyzeRECO();
  void AnalyzeGEN();
  
  //For Histograms//
  //---leptons


  //For Categorize
  TString ChannelLep;
  TString bLeptonChannel;
  
  TTsemilep_JetAssignScore();
  ~TTsemilep_JetAssignScore();


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

