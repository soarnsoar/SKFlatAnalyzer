#ifndef JHAnalyzerBase_h
#define JHAnalyzerBase_h

#include "AnalyzerCore.h"

class JHAnalyzerBase : public AnalyzerCore {

 public:
  static constexpr double MW_pdg=80.379;
  static constexpr double Width_W_pdg=2.085;
  static constexpr double MTop_pdg=172.5;
  static constexpr double Width_Top_pdg=1.42;


  void InitSystematicMomentumVariations();
  virtual void initializeAnalyzer();
  void InitClassVariablesPerEvent();
  void SetUpBtag();
  void SetSysStructure();
  void SetEventBaseSysWeight();
  void InitBtagSys();
  void executeEvent();
  //
  JHAnalyzerBase();
  ~JHAnalyzerBase();

  //Basic Global Object
  TString ProcessName;
  Event ev;
  //---flags
  bool runSys;
  bool checksf;
  bool simple_lepscale;
  //--end flags
  double weight;
  double btagcut;
  bool runWeightBase;
  //--(1) Prepare Event--//
  void InitAllObjects();
  //SetAllObjects()
  //->This Mustbe done before start events.
  //->Read all objects and set systematic variations of momenta.
  void InitMET();
  TLorentzVector UpdateMETByMuonRochCorr(const TLorentzVector &met, const vector<Muon> &muons);
  TLorentzVector UpdateMETByMuonElectronRochCorr(const TLorentzVector &met_orig, const vector<Muon> &muons,const vector<Electron> &electrons);
  TLorentzVector UpdateMETByMuonScale(const TLorentzVector &met, int sys);
  TLorentzVector UpdateMETByMuonScale(const TLorentzVector &met);
  TLorentzVector UpdateMETByElectronScale(const TLorentzVector &met, int sys);
  TLorentzVector UpdateMETByElectronScale(const TLorentzVector &met);
  TLorentzVector UpdateMETByJetScale(const TLorentzVector &met, int sys);
  TLorentzVector UpdateMETByJetSmear(const TLorentzVector &met, int sys);
  TLorentzVector GetShiftedMET(int sys);
  TLorentzVector PuppiMET_raw, PuppiMET_roch, PuppiMET; 
  //PuppiMET_roch -> correct_puppimet_by_rochcorr
  
  //--(2) Define EventLoop--//
  virtual void EventLoop(){};//main function making what you want
  virtual void TruthLoop(){};
  void FillHist(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistUp(TString sysname,TString histname,double value,double this_weight,int n_bin,double x_min, double x_max);
  void FillHistDown(TString sysname,TString histname,double value,double this_weight,int n_bin,double x_min, double x_max);
  void FillHistIdx2(TString sysname, int idx1, int idx2, TString histname,double value,double this_weight,int n_bin,double x_min, double x_max);
  void FillHistIdx2(TString sysname, TString idx1, TString idx2, TString histname,double value,double this_weight,int n_bin,double x_min, double x_max);
  //--(3) RunVariations
  void RunVariations();
  void FillReservedHist();
  void FillReservedHistWeightBase();
  void ClearReserveHist();

  void FillHistPUSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistPSSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistPrefireSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);

  void FillHistElectronID(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistElectronRECO(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistElectronTrigger(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);

  void FillHistMuonID(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistMuonRECO(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistMuonTrigger(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistMuonTrk(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  

  void FillHistBtag(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistZptWeight(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistJetPUID(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);

  void FillHistWeightBase(TString histname,double value,double this_weight,int n_bin,double x_min,double x_max);
  void FillReservedHistMomentumVariations();
  void FillReservedHistLeptonMomentumVariations();
  //--For Hist Reservation--//
  struct ArgFillHist{
    TString histname;
    double value; double weight;
    int n_bin; double x_min;
    double x_max;
  };
  vector<ArgFillHist> vReserveHist;
  //vector<std::tuple<TString, double, double, int, double, double>> vReserveHist;
  void ClearReservedHist();
  
  //syst
  struct MomentumVar{
    TString name="nominal";
    TString dir="0";
    int jes=0,jer=0,muonscale=0,electronscale=0,met=0;
  };
  MomentumVar nominal, 
    jesUp, jesDown, 
    jerUp, jerDown, 
    muonscaleUp, muonscaleDown, 
    electronscaleUp, electronscaleDown, 
    metUp,metDown;
  vector<MomentumVar> vMomentumVar;
  //LeptonMomentumVar
  struct MuonMomentumVar{
    TString name="muonscale";
    int idx1=0;
    int idx2=0;
  };
  vector<vector<MuonMomentumVar>> vMuonMomentumVar;
  struct ElectronMomentumVar{
    TString name="electronscale";
    int idx1=0;
    int idx2=0;
  };
  vector<vector<ElectronMomentumVar>> vElectronMomentumVar;

  TString sysname_current,sysdir_current;
  TString sysidx1_current,sysidx2_current;
  void SetCurrentSys(MomentumVar sys);
  MomentumVar GetCurrentSys();
  TString GetCurrentSysDir();
  TString GetCurrentSysName();
  void SetSys(MomentumVar _sys);
  void SetSys(MuonMomentumVar _sys);
  void SetSys(ElectronMomentumVar _sys);

  void SetSysSimpleMuon(int direction);
  void SetSysSimpleElectron(int direction);
  void SetupSimpleMuonMomentumVar();
  void SetupSimpleElectronMomentumVar();


  //--modules and their variables--//
  int GetIdxSingleMuReco(double ptmin, double etacut=2.4, double ptveto=10.);
  vector<Muon> GetSingleMuReco(double ptmin, double etacut=2.4, double ptveto=10.);
  vector<Muon> GetSingleMuRecoNoVeto(double ptmin, double etacut=2.4);
  //vector<Lepton*> GetPointerSingleMuReco(double ptmin, double etacut=2.4, double ptveto=10.);
  int GetIdxSingleElReco(double ptmin, double etacut=2.5, double ptveto=15.);
  vector<Electron> GetSingleElReco(double ptmin, double etacut=2.5, double ptveto=15.);
  vector<Electron> GetSingleElRecoNoVeto(double ptmin, double etacut=2.5);
  //vector<Lepton*> GetPointerSingleElReco(double ptmin, double etacut=2.5, double ptveto=15.);
  //vector<int> GetIdxDiMuReco(double ptmin1, double ptmin2, double etacut=2.4, double ptveto=10. );
  vector<Muon> GetDiMuReco(double ptmin1, double ptmin2, double etacut=2.4, double ptveto=10. );
  vector<Muon> GetDiMuRecoNoVeto(double ptmin1, double ptmin2, double etacut=2.4);
  //vector<Lepton*> GetPointerDiMuReco(double ptmin1, double ptmin2, double etacut=2.4, double ptveto=10. );
  //vector<int> GetIdxDiElReco(double ptmin1, double ptmin2, double etacut=2.5, double ptveto=15. );
  vector<Electron> GetDiElReco(double ptmin1, double ptmin2, double etacut=2.5, double ptveto=15. );
  vector<Electron> GetDiElRecoNoVeto(double ptmin1, double ptmin2, double etacut=2.5);
  //vector<Lepton*> GetPointerDiElReco(double ptmin1, double ptmin2, double etacut=2.5, double ptveto=15. );
  void SetupSingleLeptonChannel();
  void SetupDiLeptonChannel();
  void SetIsDoubleLeptonTrigger();
  void PrintSFStructure();
  //vector<int> GetIdxTightJet(const vector<Lepton> &TightLeptonCollection ,double ptmin, double etacut, TString JetID="tight" );
  vector<Jet> GetTightJet(const vector<Lepton> &TightLeptonCollection ,double ptmin, double etacut, TString JetID="tight", TString _JETPUID="" );
  //vector<Jet*> GetPointerTightJet(const vector<Lepton*> &TightLeptonCollection ,double ptmin, double etacut, TString JetID="tight" );
  //vector<int> GetIdxBJet(const vector<int> &v_TightjetIdx);
  vector<Jet> GetBJet(const vector<Jet> &v_Tightjet);
  vector<int> GetBJetIdx(const vector<Jet> &v_Tightjet);
  //vector<Jet*> GetPointerBJet(const vector<Jet*> &v_Tightjet);
  //void SetBtagSF(const vector<int> &v_jetidx);
  void SetBtagSF(const vector<Jet> &v_jet);
  void SetJetPUIDSF(TString _JetPUID);
  
  double TriggerSafeCut_muon1, TriggerSafeCut_muon2;
  double TriggerSafeCut_electron1, TriggerSafeCut_electron2;
  vector<TString> MuonTriggerNames;
  bool IsDoubleMuonTrigger;
  bool IsORMuonTrigger;
  vector<TString> MuonTriggerSFKeys;
  vector<TString> ElectronTriggerNames;
  bool IsDoubleElectronTrigger;
  bool IsORElectronTrigger;
  vector<TString> ElectronTriggerSFKeys;
  TString MuonRecoSFKey,MuonIDSFKey,MuonTrkSFKey,MuonDZSFKey;
  TString ElectronRecoSFKey,ElectronIDSFKey,ElectronDZSFKey;
  TString MuonID;
  TString ElectronID;

  //--For Calc.
  TLorentzVector GetTransverseVector(const TLorentzVector &v);
  TLorentzVector GetTransverseVector(double pt, double phi);

  //For eff.
  vector<vector<double>> w_ElectronID;
  vector<vector<double>> r_ElectronID;
  vector<vector<double>> w_ElectronRECO;
  vector<vector<double>> r_ElectronRECO;
  vector<vector<double>> w_ElectronTrigger;
  vector<vector<double>> r_ElectronTrigger;

  vector<vector<double>> w_MuonID;
  vector<vector<double>> r_MuonID;
  vector<vector<double>> w_MuonRECO;
  vector<vector<double>> r_MuonRECO;
  vector<vector<double>> w_MuonTrk;
  vector<vector<double>> r_MuonTrk;
  vector<vector<double>> w_MuonTrigger;
  vector<vector<double>> r_MuonTrigger;
  //For Other weight
  vector<double> r_PU;
  vector<double> r_Prefire;

  //eff scale Factor
  //void SetMuonSFs(const vector<int> &v_muonidx);
  void SetMuonSFs(const vector<Muon> &v_muon);
  //void SetMuonSFs(const vector<Lepton*> &v_muon);
  //void SetMuonRecoSF(const vector<int> &v_muonidx);
  void SetMuonRecoSF(const vector<Lepton*> &v_muon);
  //void SetMuonIDSF(const vector<int> &v_muonidx);
  void SetMuonIDSF(const vector<Lepton*> &v_muon);
  //void SetMuonTrkSF(const vector<int> &v_muonidx);
  void SetMuonTrkSF(const vector<Lepton*> &v_muon);
  //void SetMuonTriggerSF(const vector<int> &v_muonidx);
  void SetMuonTriggerSF(const vector<Lepton*> &_v_muons);
  void SetSingleMuonTriggerSF(const vector<Lepton*> &v_muon);
  void SetSingleMuonTriggerORSF(const vector<Lepton*> &v_muon);
  void SetDoubleMuonTriggerSF(const vector<Lepton*> &v_muon);

  //void SetElectronSFs(const vector<int> &v_electronidx);
  void SetElectronSFs(const vector<Electron> &v_electron);
  //void SetElectronSFs(const vector<Lepton*> &v_electron);
  //void SetElectronRecoSF(const vector<int> &v_electronidx);
  void SetElectronRecoSF(const vector<Lepton*> &v_electron);
  //void SetElectronIDSF(const vector<int> &v_electronidx);
  void SetElectronIDSF(const vector<Lepton*> &v_electron);
  //void SetElectronTriggerSF(const vector<int> &v_electronidx);
  void SetElectronTriggerSF(const vector<Lepton*> &v_electron);
  void SetSingleElectronTriggerSF(const vector<Lepton*> &v_electron);
  void SetSingleElectronTriggerORSF(const vector<Lepton*> &v_electron);
  void SetDoubleElectronTriggerSF(const vector<Lepton*> &v_electron);


  //btag variation
  double btagsf;
  double r_SystUpLTagCorr,r_SystDownLTagCorr;
  double r_SystUpLTagUnCorr,r_SystDownLTagUnCorr;
  double r_SystUpHTagCorr,r_SystDownHTagCorr;
  double r_SystUpHTagUnCorr,r_SystDownHTagUnCorr;
  //puidsf
  double jetpuidsf;
  double jetpuidsf_up, jetpuidsf_down;
  double r_jetpuidsf_up, r_jetpuidsf_down;
  //zptweight
  double zptweight;
  //z0weight
  double z0weight;
  //weakweight
  double weakweight;
  //toppt
  double topptweight;
  std::vector<Muon> AllMuons_raw;
  std::vector<Muon> AllMuons_roch;
  std::vector<Electron> AllElectrons_raw;
  std::vector<Electron> AllElectrons_roch;
  std::vector<Jet> AllJets_raw;

  std::vector<Muon> AllMuons;
  std::vector<Electron> AllElectrons;
  std::vector<Jet> AllJets;
  //for simple momentum
  std::vector<Muon> AllMuons_plus;
  std::vector<Muon> AllMuons_minus;  
  std::vector<Electron> AllElectrons_plus;
  std::vector<Electron> AllElectrons_minus;

  //lepton idx
  int muon1_idx, muon2_idx;
  int electron1_idx, electron2_idx;

  //----Truth Level---
  bool TagZbLHE(bool include_tautau=false);
  int idx_outgoing_b;
  bool is_mumu_lhe, is_ee_lhe;
  //bool TagWbLHE();
  //---functions for lep in bjet
  double GetP_JetRestFrame(TLorentzVector &lep, TLorentzVector &jet);
  double GetPt_wrt_Jet(TLorentzVector &lep, TLorentzVector &jet);
  double GetP_along_Jet(TLorentzVector &lep, TLorentzVector &jet);

  struct bmuonvar{
    float P_jetrest=0;
    float ptwrtjet=0;
    float dR_l_j=0;
    float nsip3d=0;
    float reltrkiso=0;
    float reliso=0;
    float charge=0;
    float palongjet=0;
    float palongjetratio=0;
    float pt=0;
    float aeta=0;
    float normchi2=0;
    float ntracklayers=0;
    float ntrackhits=0;
    float nvalidmuonhits=0;
    float nmatchedstations=0;
    float bjet_charge_dot_bmuon_charge=0;
    bool isGlobalMuon=0;
    bool isTrackerMuon=0;
    bool isStandAloneMuon=0;
    bool isCaloMuon=0;
    bool isPFMuon=0;
    bool isRPCMuon=0;
    bool isGEMMuon=0;
    bool isME0Muon=0;
  };

  struct belectronvar{
    float P_jetrest=0;
    float ptwrtjet=0;
    float palongjet=0;
    float palongjetratio=0;
    float dR_l_j=0;
    float nsip3d=0;
    float reltrkiso=0;
    float reliso=0;
    float charge=0;
    float relecalPFClusterIso=0;
    float IsGsfCtfScPixChargeConsistent=0;
    float pt=0;
    float aeta=0;
    float full5x5sigmaietaieta=0;
    float detaseed=0;
    float abs_detaseed=0;
    float HoverE=0;
    float InvEminusInvP=0;
    float nmissinghits=0;
    float bjet_charge_dot_belectron_charge=0;
  };

  struct bjetvar{
    float pt=0;
    float aeta=0;
    float ChargedHadronEnergyFraction=0;
    float NeutralHadronEnergyFraction=0;
    float NeutralEmEnergyFraction=0;
    float ChargedEmEnergyFraction=0;
    float MuonEnergyFraction=0;
    float charge=0;
    float abs_charge=0;
    float partonFlavour=0;
    float ChargedMultiplicity=0;
    float NeutralMultiplicity=0;
  };



  JHAnalyzerBase::bmuonvar Get_bmuonvar(Muon &this_muon, Jet &this_jet);
  JHAnalyzerBase::belectronvar Get_belectronvar(Electron &this_electron, Jet &this_jet);
  JHAnalyzerBase::bjetvar Get_bjetvar(Jet &this_jet);


  void LoadChargeScoreTool(TString muon_version="2405.2",TString electron_version="2405.2", TString jet_version="2405.2", bool applycut=false);
  void SetChargeScoreCut(TString version);
  void SetChargeScoreCut_2405_2();
  void SetChargeScoreCut_2405_4();
  void SetChargeScoreCut_2405_4_3();
  void SetMuonChargeScore(Muon &_this_bmuon, Jet &_this_bjet);
  void SetElectronChargeScore(Electron &_this_belectron, Jet &_this_bjet);
  void SetJetChargeScore(Jet &_this_bjet);
  double GetMuonChargeScore();
  double GetMuonChargeScoreCoeff();
  double GetElectronChargeScore();
  double GetElectronChargeScoreCoeff();
  double GetJetChargeScore();
  double GetJetChargeScoreCoeff();
  ChargeScoreTool *mChargeTool;
  bmuonvar bmuon_ChargeTool;
  ChargeScoreTool *eChargeTool;
  belectronvar belectron_ChargeTool;
  ChargeScoreTool *jChargeTool;
  bjetvar bjet_ChargeTool;

  //---jet assignment
  static double Chi2TTSemiLep(double *x, double *par);

 private:
  MomentumVar _CurrentSys;
  JetTagging::Parameters jtp;
};





#endif

