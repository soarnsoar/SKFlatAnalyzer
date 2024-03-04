#ifndef TTsemilep_JetAssignScore_TrainingInput_h
#define TTsemilep_JetAssignScore_TrainingInput_h

#include "AnalyzerCore.h"
#include "TMVA/PyMethodBase.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include <set>
class TTsemilep_JetAssignScore_TrainingInput : public AnalyzerCore {

public:
  //temp
  double nevt;
  double nevt_samebb;

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



  double DNNscore;
  double MET;
  void initializeAnalyzer();
  bool TTbarMuReco();
  bool TTbarElReco();
  bool CheckJets();
  void CollectJets();
  TLorentzVector l1;
  unsigned int Nb =0, Nbbar=0;
  void FlavourAndDeltaR_Matching();
  bool Is_q1match,Is_q2match;
  unsigned int N_light_quark_jet,N_gluon_jet;
  void FlavourMatchingOnly();
  bool flavourmatch1,flavourmatch2;
  unsigned int N_flavour_match1,N_flavour_match2;
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
  double TriggerSafeCut_muon;
  double TriggerSafeCut_electron;


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
  void FillTreeValues_NotMatchCase();
  void AnalyzeRECO();
  void AnalyzeGEN();
  
  //For Histograms//
  //---leptons


  //For Categorize
  TString ChannelLep;
  TString bLeptonChannel;
  
  TTsemilep_JetAssignScore_TrainingInput();
  ~TTsemilep_JetAssignScore_TrainingInput();


  int nb_event;
  

  //---For Tree
  bool doFillTree;
  void InitValues();
  //-----Variables to Store for Machine Learning------//
  double met_pt,met_phi;
  double electron_pt,electron_phi,electron_eta;
  double muon_pt, muon_phi, muon_eta;
  double blep_pt,blep_phi,blep_eta,blep_E;
  double bhad_pt,bhad_phi,bhad_eta,bhad_E;
  double q1jet_pt,q1jet_phi,q1jet_eta,q1jet_E;
  double q2jet_pt,q2jet_phi,q2jet_eta,q2jet_E;
  double WhadCand_mass,ThadCand_mass;
};



#endif

