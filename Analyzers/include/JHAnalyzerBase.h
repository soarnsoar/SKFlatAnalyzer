#ifndef JHAnalyzerBase_h
#define JHAnalyzerBase_h

#include "AnalyzerCore.h"
#include <TStopwatch.h>

class JHAnalyzerBase : public AnalyzerCore {

 public:

  //--Timer--//
  TStopwatch timer_InitObj; int ncall_InitObj; double t_InitObj;
  TStopwatch timer_InitVariable; int ncall_InitVariable; double t_InitVariable;
  TStopwatch timer_EventLoop; int ncall_EventLoop; double t_EventLoop;
  TStopwatch timer_FillWeightBase; int ncall_FillWeightBase; double t_FillWeightBase;
  TStopwatch timer_FillMomentumBase; int ncall_FillMomentumBase; double t_FillMomentumBase;


  //Timer detail//
  TStopwatch timer_prefire; int ncall_prefire; double t_prefire;
  TStopwatch timer_pu; int ncall_pu; double t_pu;
  TStopwatch timer_ps; int ncall_ps; double t_ps;
  TStopwatch timer_btag; int ncall_btag; double t_btag;

  TStopwatch timer_ElectronID; int ncall_ElectronID; double t_ElectronID;
  TStopwatch timer_ElectronRECO; int ncall_ElectronRECO; double t_ElectronRECO;
  TStopwatch timer_ElectronTrigger; int ncall_ElectronTrigger; double t_ElectronTrigger;

  TStopwatch timer_MuonID; int ncall_MuonID; double t_MuonID;
  TStopwatch timer_MuonRECO; int ncall_MuonRECO; double t_MuonRECO;
  TStopwatch timer_MuonTrigger; int ncall_MuonTrigger; double t_MuonTrigger;
  TStopwatch timer_MuonTrk; int ncall_MuonTrk; double t_MuonTrk;
  
  //--[end]Timer//

  //void initializeAnalyzer();
  void InitSystematicMomentumVariations();
  void initializeAnalyzer();
  void InitClassVariablesPerEvent();
  void InitBtag();
  void SetSysStructure();
  void SetEventBaseSysWeight();
  void executeEvent();
  //
  JHAnalyzerBase();
  ~JHAnalyzerBase();

  //Basic Global Object
  TString ProcessName;
  Event ev;
  bool runSys;
  double weight;
  double btagcut;
  //--(1) Prepare Event--//
  void InitAllObjects();
  //SetAllObjects()
  //->This Mustbe done before start events.
  //->Read all objects and set systematic variations of momenta.
  void InitMET();
  TLorentzVector UpdateMETByMuonRochCorr(const TLorentzVector &met, const vector<Muon> &muons);
  TLorentzVector UpdateMETByMuonScale(const TLorentzVector &met, int sys);
  TLorentzVector UpdateMETByElectronScale(const TLorentzVector &met, int sys);
  TLorentzVector UpdateMETByJetScale(const TLorentzVector &met, int sys);
  TLorentzVector UpdateMETByJetSmear(const TLorentzVector &met, int sys);
  TLorentzVector GetShiftedMET(int sys);
  TLorentzVector PuppiMET_raw, PuppiMET_roch, PuppiMET; 
  //PuppiMET_roch -> correct_puppimet_by_rochcorr
  
  //--(2) Define EventLoop--//
  virtual void EventLoop(){};//main function making what you want
  void FillHist(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistUp(TString sysname,TString histname,double value,double this_weight,int n_bin,double x_min, double x_max);
  void FillHistDown(TString sysname,TString histname,double value,double this_weight,int n_bin,double x_min, double x_max);
  void FillHistIdx2(TString sysname, int idx1, int idx2, TString histname,double value,double this_weight,int n_bin,double x_min, double x_max);
  void FillHistIdx2(TString sysname, TString idx1, TString idx2, TString histname,double value,double this_weight,int n_bin,double x_min, double x_max);
  //--(3) RunVariations
  void RunVariations();
  void RunWeightVariations();
  void RunMomentumVariations();
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
  
  void FillReservedHistMomentumVariations();
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
  TString sysname_current,sysdir_current;
  void SetCurrentSys(MomentumVar sys);
  MomentumVar GetCurrentSys();
  TString GetCurrentSysDir();
  TString GetCurrentSysName();
  void SetSys(MomentumVar _sys);

  //--modules and their variables--//
  int GetIdxSingleMuReco(const vector<Muon> &MuonCollection, double ptmin, double etacut=2.4, double ptveto=10.);
  int GetIdxSingleElReco(const vector<Electron> &ElectronCollection, double ptmin, double etacut=2.5, double ptveto=15.);
  vector<int> GetIdxDiMuReco(const vector<Muon> &MuonCollection, double ptmin1, double ptmin2, double etacut=2.4, double ptveto=10. );
  vector<int> GetIdxDiElReco(const vector<Electron> &ElectronCollection, double ptmin1, double ptmin2, double etacut=2.5, double ptveto=15. );
  void SetupSingleLeptonChannel();
  void SetupDiLeptonChannel();
  void SetIsDoubleLeptonTrigger();

  vector<int> GetIdxTightJet(const vector<Jet> &JetCollection, const vector<Lepton> &TightLeptonCollection ,double ptmin, double etacut, TString JetID="tight" );
  vector<int> GetIdxBJet(const vector<int> &v_TightjetIdx);
  void SetBtagSF(const vector<int> &v_jetidx);


  double TriggerSafeCut_muon1, TriggerSafeCut_muon2;
  double TriggerSafeCut_electron1, TriggerSafeCut_electron2;
  vector<TString> MuonTriggerNames;
  bool IsDoubleMuonTrigger;
  vector<TString> MuonTriggerSFKeys;
  vector<TString> ElectronTriggerNames;
  bool IsDoubleElectronTrigger;
  vector<TString> ElectronTriggerSFKeys;
  TString MuonRecoSFKey,MuonIDSFKey,MuonTrkSFKey,MuonDZSFKey;
  TString ElectronRecoSFKey,ElectronIDSFKey,ElectronDZSFKey;
  TString MuonID;
  TString ElectronID;

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
  void SetMuonSFs(const vector<int> &v_muonidx);
  void SetMuonRecoSF(const vector<int> &v_muonidx);
  void SetMuonIDSF(const vector<int> &v_muonidx);
  void SetMuonTrkSF(const vector<int> &v_muonidx);
  void SetMuonTriggerSF(const vector<int> &v_muonidx);
  void SetSingleMuonTriggerSF(const vector<Lepton*> &v_muon);
  void SetDoubleMuonTriggerSF(const vector<Lepton*> &v_muon);

  void SetElectronSFs(const vector<int> &v_electronidx);
  void SetElectronRecoSF(const vector<int> &v_electronidx);
  void SetElectronIDSF(const vector<int> &v_electronidx);
  void SetElectronTriggerSF(const vector<int> &v_electronidx);
  void SetSingleElectronTriggerSF(const vector<Lepton*> &v_electron);
  void SetDoubleElectronTriggerSF(const vector<Lepton*> &v_electron);


  //btag variation
  double btagsf;
  double r_SystUpLTagCorr,r_SystDownLTagCorr;
  double r_SystUpLTagUnCorr,r_SystDownLTagUnCorr;
  double r_SystUpHTagCorr,r_SystDownHTagCorr;
  double r_SystUpHTagUnCorr,r_SystDownHTagUnCorr;



  std::vector<Muon> AllMuons_raw;
  std::vector<Electron> AllElectrons_raw;
  std::vector<Jet> AllJets_raw;

  std::vector<Muon> AllMuons;
  std::vector<Electron> AllElectrons;
  std::vector<Jet> AllJets;

  
 private:
  MomentumVar _CurrentSys;
  JetTagging::Parameters jtp;
};





#endif

