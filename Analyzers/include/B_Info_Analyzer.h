#ifndef B_Info_Analyzer_h
#define B_Info_Analyzer_h

#include "AnalyzerCore.h"
#include <set>
class B_Info_Analyzer : public AnalyzerCore {

public:

  void initializeAnalyzer();

  void executeEventFromParameter(AnalyzerParameter param);
  void executeExoticEvent();
  bool Tag_gbToZb();
  void Tag_B_Hadron();
  void Loop_genBMatchedRecoJet();
  void ParseReco();
  void HistConf();

  int CheckIsBhadAndNb(int pid);

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

  };
  RECOinfo myRECO;

  void AnalyzeRECO();
  void AnalyzeGEN();
  void AnalyzeLHE();

  vector<double> v_xscale_binning;
  vector<double> v_Q2scale_binning;
  double* xscale_binning;
  double* Q2scale_binning;
  //For Histograms//
  //---leptons
  void FillHistRecoMuon(TString cutname);
  void FillHistSetRecoMuon(TString cutname);
  void FillHistReco_nMuon();
  void FillHistRecoElectron(TString cutname);
  void FillHistSetRecoElectron(TString cutname);
  void FillHistReco_nElectron();

  void FillHistReco_nLepton();


  void FillHistBmatJet(TString cutname);
  void FillHistJet(TString cutname, unsigned int jidx);
  //global varibles for recolevel
  double muon_pt,muon_eta,muon_phi,muon_dxy,muon_dz,
    muon_charge,muon_ip3d,muon_reliso,muon_jetptratio,
    muon_jetptrel,muon_dR_bmatj;
  unsigned int nmuon,nmuon_InBmatjet, nmuon_OutOfBmatjet;
  unsigned int nmuon_p,nmuon_p_InBmatjet, nmuon_p_OutOfBmatjet;
  unsigned int nmuon_n,nmuon_n_InBmatjet, nmuon_n_OutOfBmatjet;
  TLorentzVector v_muon;
  
  double electron_pt,electron_eta,electron_phi,electron_dxy,electron_dz,
    electron_charge,electron_ip3d,electron_reliso,electron_jetptratio,
    electron_jetptrel,electron_dR_bmatj;
  unsigned int nelectron,nelectron_InBmatjet, nelectron_OutOfBmatjet;
  unsigned int nelectron_p,nelectron_p_InBmatjet, nelectron_p_OutOfBmatjet;
  unsigned int nelectron_n,nelectron_n_InBmatjet, nelectron_n_OutOfBmatjet;
  TLorentzVector v_electron;


  double dRToLHE,dRToBhad,ptratioToLHE,ptratioToBhad;

  //For Categorize
  TString Cat_b_bbar[10];
  TString Cat_Z_To_mm_ee[10];
  TString Cat_lepton_charge[10];
  unsigned int Cat_b_bbar_size;
  unsigned int Cat_Z_To_mm_ee_size;
  unsigned int Cat_lepton_charge_size;
  
  B_Info_Analyzer();
  ~B_Info_Analyzer();
  
};



#endif

