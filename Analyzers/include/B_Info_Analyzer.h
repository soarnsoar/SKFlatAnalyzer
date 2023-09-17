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

  //For Histograms//
  void FillHistRecoMuon(TString cutname);
  void FillHistRecoElectron(TString cutname);
  void FillHistBmatJet(TString cutname);

  //global varibles for recolevel
  double muon_pt,muon_eta,muon_phi,muon_dxy,muon_dz,
    muon_charge,muon_ip3d,muon_reliso,muon_jetptratio,
    muon_jetptrel,muon_dR_bmatj;
  TLorentzVector v_muon;
  
  double electron_pt,electron_eta,electron_phi,electron_dxy,electron_dz,
    electron_charge,electron_ip3d,electron_reliso,electron_jetptratio,
    electron_jetptrel,electron_dR_bmatj;
  TLorentzVector v_electron;


  double dRToLHE,dRToBhad,ptratioToLHE,ptratioToBhad;


  B_Info_Analyzer();
  ~B_Info_Analyzer();
  
};



#endif

