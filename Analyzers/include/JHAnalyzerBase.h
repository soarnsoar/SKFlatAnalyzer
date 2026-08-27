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

  //GetPDFSetIDCode
  int GetPDFSetIDCode();
  TString PDFalias;

  //Basic Global Object
  TString ProcessName;
  Event ev;
  //---flags
  bool runSys;
  bool runMomSys;
  bool runSysMom00;
  bool checksf;
  bool simple_lepscale;
  bool weightonly;
  bool pusysonly;
  bool measure_btageff=false;
  bool measure_btageff_partonFlavour=false;
  bool measure_btageff_partonFlavour_bonly=false;
  bool measure_bchargeeff=false;
  bool measure_bchargeacc=false;
  //--end flags
  //--flag for test
  bool muonscale00event;
  bool electronscale00event;
  bool nominalevent;

  bool nominal_LeptonMinus_bJetHadronicSide__PASS__PT30To50__Eta1p6To2;
  bool muonscale00_LeptonMinus_bJetHadronicSide__PASS__PT30To50__Eta1p6To2;
  
  bool nominal_LeptonPlus_bJetLeptonicSide__FAIL__PT100To140__Eta0To0p8;
  bool electronscale00_LeptonPlus_bJetLeptonicSide__FAIL__PT100To140__Eta0To0p8;

  bool nominal_LeptonPlus_bJetLeptonicSide__FAIL__PT30To50__Eta0To0p8;
  bool electronscale00_LeptonPlus_bJetLeptonicSide__FAIL__PT30To50__Eta0To0p8;


  bool nominal_LeptonPlus_bJetHadronicSide__FAIL__PT30To50__Eta0To0p8;
  bool electronscale00_LeptonPlus_bJetHadronicSide__FAIL__PT30To50__Eta0To0p8;
  
  bool scale00test;

  bool EvtToTest;
  //--

  double jetetacut;
  
  double weight;
  double btagcut;
  bool runWeightBase;
  //--(1) Prepare Event--//
  void SetJetEtacut();
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
  TLorentzVector CurrentMET_raw, CurrentMET_roch, CurrentMET; 
  //CurrentMET_roch -> correct_puppimet_by_rochcorr
  
  //--(2) Define EventLoop--//
  virtual void EventLoop(){};//main function making what you want
  virtual void TruthLoop(){};
  void FillHist(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHist(TString histname, double value, double this_weight, int n_bin, double *xbins);
  
  void FillHistUp(TString sysname, TString histname, double value, double this_weight, int n_bin,double x_min, double x_max);
  void FillHistUp(TString sysname, TString histname, double value, double this_weight, int n_bin, double *xbins);
  
  void FillHistDown(TString sysname, TString histname, double value, double this_weight, int n_bin,double x_min, double x_max);
  void FillHistDown(TString sysname, TString histname, double value, double this_weight, int n_bin, double *xbins);
  
  void FillHistIdx2(TString sysname, int idx1, int idx2, TString histname, double value, double this_weight,int n_bin, double x_min, double x_max);
  void FillHistIdx2(TString sysname, int idx1, int idx2, TString histname, double value, double this_weight,int n_bin, double *xbins);
  
  void FillHistIdx2(TString sysname, TString idx1, TString idx2, TString histname, double value, double this_weight,int n_bin, double x_min, double x_max);
  void FillHistIdx2(TString sysname, TString idx1, TString idx2, TString histname, double value, double this_weight,int n_bin, double *xbins);

  //--(3) RunVariations
  //void RunVariations();
  //void FillReservedHist();
  //void FillReservedHistWeightBase();
  //void ClearReserveHist();

  void FillHistPUSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistPUSys(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistPSSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistPSSys(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistPrefireSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistPrefireSys(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistElectronID(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistElectronID(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistElectronRECO(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistElectronRECO(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistElectronTrigger(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistElectronTrigger(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistMuonID(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistMuonID(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistMuonRECO(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistMuonRECO(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistMuonTrigger(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistMuonTrigger(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistMuonTrk(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistMuonTrk(TString histname, double value, double this_weight, int n_bin, double *xbins);
  

  void FillHistBtag(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistBtag(TString histname, double value, double this_weight, int n_bin, double *xbins);


  void FillHistBtagChargeAsym(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistBtagChargeAsym(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistChargeIDEff(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistChargeIDEff(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistChargeAcc(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistChargeAcc(TString histname, double value, double this_weight, int n_bin, double *xbins);  
  
  void FillHistZptWeight(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistZptWeight(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistTopPtReweight(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistTopPtReweight(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistJetPUID(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistJetPUID(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistPDF(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistPDF(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistScale(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistScale(TString histname, double value, double this_weight, int n_bin, double *xbins);

  void FillHistAlphaS(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistAlphaS(TString histname, double value, double this_weight, int n_bin, double *xbins);


  //void FillHistQCDXSEC(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  //void FillHistQCDXSEC(TString histname, double value, double this_weight, int n_bin, double *xbins);

  /*
  void FillHistalpsfact(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistalpsfact(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);

  void FillHistlargeptscales(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistq0(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHiststhw2(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  void FillHistkHtt(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max);
  */

  void FillHistWeightBase(TString histname,double value,double this_weight,int n_bin,double x_min,double x_max);
  void FillHistWeightBase(TString histname,double value,double this_weight,int n_bin,double *xbins);

  //void FillReservedHistMomentumVariations();
  //void FillReservedHistLeptonMomentumVariations();
  //--For Hist Reservation--//
  //struct ArgFillHist{
  //  TString histname;
  //  double value; double weight;
  //  int n_bin; double x_min;
  //  double x_max;
  //};
  //vector<ArgFillHist> vReserveHist;
  //vector<std::tuple<TString, double, double, int, double, double>> vReserveHist;
  //void ClearReservedHist();
  
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
  //vector<Muon> GetSingleMuReco(double ptmin, double etacut=2.4, double ptveto=10.);
  vector<Muon> GetSingleMuReco(double ptmin, double etacut=2.4, double ptveto=10, double ptveto2=15., double etacut2=2.5);//ptveto2,etacut2 == for electron
  vector<Muon> GetSingleMuRecoNoVeto(double ptmin, double etacut=2.4);

  vector<int> GetSingleMuRecoIdx(double ptmin, double etacut=2.4, double ptveto=10., double ptveto2=15., double etacut2=2.5);//
  vector<int> GetSingleMuRecoNoVetoIdx(double ptmin, double etacut=2.4);

  //vector<Lepton*> GetPointerSingleMuReco(double ptmin, double etacut=2.4, double ptveto=10.);
  //int GetIdxSingleElReco(double ptmin, double etacut=2.5, double ptveto=15.);
  //vector<Electron> GetSingleElReco(double ptmin, double etacut=2.5, double ptveto=15.);
  vector<Electron> GetSingleElReco(double ptmin, double etacut=2.5, double ptveto=15., double ptveto2=10., double etacut2=2.4);//ptveto2 and etacut2 -->for add. muon
  vector<Electron> GetSingleElRecoNoVeto(double ptmin, double etacut=2.5);
  
  vector<int> GetSingleElRecoIdx(double ptmin, double etacut=2.5, double ptveto=15., double ptveto2=10., double etacut2=2.4);//ptveto2 and etacut2 -->for add. muon
  vector<int> GetSingleElRecoNoVetoIdx(double ptmin, double etacut=2.5);

  //vector<Lepton*> GetPointerSingleElReco(double ptmin, double etacut=2.5, double ptveto=15.);
  //vector<int> GetIdxDiMuReco(double ptmin1, double ptmin2, double etacut=2.4, double ptveto=10. );
  vector<Muon> GetDiMuReco(double ptmin1, double ptmin2, double etacut=2.4, double ptveto=10., double ptveto2=15., double etacut2=2.5 );
  vector<int> GetDiMuRecoIdx(double ptmin1, double ptmin2, double etacut=2.4, double ptveto=10., double ptveto2=15., double etacut2=2.5 );
  vector<Muon> GetDiMuRecoNoVeto(double ptmin1, double ptmin2, double etacut=2.4);
  vector<int> GetDiMuRecoNoVetoIdx(double ptmin1, double ptmin2, double etacut=2.4);
  //vector<Lepton*> GetPointerDiMuReco(double ptmin1, double ptmin2, double etacut=2.4, double ptveto=10. );
  //vector<int> GetIdxDiElReco(double ptmin1, double ptmin2, double etacut=2.5, double ptveto=15. );
  vector<Electron> GetDiElReco(double ptmin1, double ptmin2, double etacut=2.5, double ptveto=15., double ptveto2=10., double etacut2=2.4 );
  vector<int> GetDiElRecoIdx(double ptmin1, double ptmin2, double etacut=2.5, double ptveto=15., double ptveto2=10., double etacut2=2.4 );
  vector<Electron> GetDiElRecoNoVeto(double ptmin1, double ptmin2, double etacut=2.5);
  vector<int> GetDiElRecoNoVetoIdx(double ptmin1, double ptmin2, double etacut=2.5);

  //vector<Lepton*> GetPointerDiElReco(double ptmin1, double ptmin2, double etacut=2.5, double ptveto=15. );
  void SetupSingleLeptonChannel();
  void SetupDiLeptonChannel();
  void SetIsDoubleLeptonTrigger();
  void PrintSFStructure();
  //vector<int> GetIdxTightJet(const vector<Lepton> &TightLeptonCollection ,double ptmin, double etacut, TString JetID="tight" );
  vector<Jet> GetTightJet(const vector<Lepton> &TightLeptonCollection ,double ptmin, double etacut, TString JetID="tight", TString _JETPUID="",bool apply_vetomap=true);
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
  //btag dasym variation
  //double r_ChargedAsymUp,r_ChargedAsymDown;
  enum PtBin { kPT30To50 = 0, kPT50To70, kPT70To100, kPT100To140, kPT140ToInf, nPtBin };
  enum EtaBin { kEta0To0p8 = 0, kEta0p8To1p6, kEta1p6To2, kEta2To2p5, nEtaBin};  
  
  double arr_r_ChargedAsymUp[nPtBin][nEtaBin];
  double arr_r_ChargedAsymDown[nPtBin][nEtaBin];

  //  static const char* PtBinName[nPtBin];

  //static const char* EtaBinName[nEtaBin];
  inline static const char* PtBinName[nPtBin] = {
    "PT30To50","PT50To70","PT70To100","PT100To140","PT140ToInf"
  };
  inline static const char* EtaBinName[nEtaBin] ={
    "Eta0To0p8",
    "Eta0p8To1p6",
    "Eta1p6To2",
    "Eta2To2p5"
  };



  
  //vector<double> v_r_ChargedAsymDown;
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
  //QCD xsec
  //doube r_QCDXSEC;
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
  double GetP_JetRestFrame(TLorentzVector &lep, const TLorentzVector &jet);
  double GetPt_wrt_Jet(TLorentzVector &lep, const TLorentzVector &jet);
  double GetP_along_Jet(TLorentzVector &lep, const TLorentzVector &jet);

  struct bmuonvar{
    float P_jetrest=0;
    float ptwrtjet=0;
    float dR_l_j=0;
    float nsip3d=0;
    float reltrkiso=0;
    float reliso=0;
    float log10_1_reliso=0;
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
    float log10_1_reliso=0;
    float charge=0;
    float relecalPFClusterIso=0;
    float IsGsfCtfScPixChargeConsistent=0;
    float PassConversionVeto=0;
    float pt=0;
    float aeta=0;
    float full5x5sigmaietaieta=0;
    float detaseed=0;
    float abs_detaseed=0;
    float dPhiIn=0;
    float abs_dPhiIn=0;
    float HoverE=0;
    float InvEminusInvP=0;
    float nmissinghits=0;
    float bjet_charge_dot_belectron_charge=0;
    bool passVetoID=0;
    bool passVetoIDnoIso=0;
    bool passLooseID=0;
    bool passMediumID=0;
    bool passTightID=0;
  };

  struct bjetvar{
    float pt=0;
    float aeta=0;
    float eta=0;
    float ChargedHadronEnergyFraction=0;
    float NeutralHadronEnergyFraction=0;
    float log_NeutralHadronEnergyFraction=-std::numeric_limits<float>::infinity();
    float NeutralEmEnergyFraction=0;
    float ChargedEmEnergyFraction=0;
    float MuonEnergyFraction=0;
    float log_MuonEnergyFraction=-std::numeric_limits<float>::infinity();
    float charge=0;
    float abs_charge=0;
    float partonFlavour=0;
    float hadronFlavour=0;
    float ChargedMultiplicity=0;
    float NeutralMultiplicity=0;
  };

  struct bmuonvar_cut{
    float P_jetrest[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float ptwrtjet[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float dR_l_j[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float nsip3d[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float reltrkiso[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float reliso[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float charge[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float palongjet[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float palongjetratio[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float pt[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float aeta[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float normchi2[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float ntracklayers[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float ntrackhits[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float nvalidmuonhits[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float nmatchedstations[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float bjet_charge_dot_bmuon_charge[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    
  };

  struct belectronvar_cut{
    float P_jetrest[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float ptwrtjet[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float palongjet[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float palongjetratio[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float dR_l_j[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float nsip3d[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float reltrkiso[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float reliso[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float charge[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float relecalPFClusterIso[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float IsGsfCtfScPixChargeConsistent[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float pt[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float aeta[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float full5x5sigmaietaieta[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float detaseed[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float abs_detaseed[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float HoverE[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float InvEminusInvP[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float nmissinghits[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float bjet_charge_dot_belectron_charge[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
  };

  struct bjetvar_cut{
    float pt[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float aeta[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float eta[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float ChargedHadronEnergyFraction[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float NeutralHadronEnergyFraction[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float NeutralEmEnergyFraction[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float ChargedEmEnergyFraction[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float MuonEnergyFraction[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float charge[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float abs_charge[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float partonFlavour[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float hadronFlavour[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float ChargedMultiplicity[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
    float NeutralMultiplicity[2]={-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
  };

  

  JHAnalyzerBase::bmuonvar Get_bmuonvar(Muon &this_muon,const Jet &this_jet);
  JHAnalyzerBase::belectronvar Get_belectronvar(Electron &this_electron, const Jet &this_jet);
  JHAnalyzerBase::bjetvar Get_bjetvar(const Jet &this_jet);
  /*
  enum class MuonScoreVer {
    v2409_2,
    v2512_3,
    v2512_4,
    
    v2512_5_2016preVFP,

    v2512_5_2016postVFP,
    v2512_5_2017,
    v2512_5_2018,

    others
  };
  enum class ElectronScoreVer {
    v2409_2,
    v2512_3,
    v2512_4,

    v2512_5_2016preVFP,
    v2512_5_2016postVFP,
    v2512_5_2017,
    v2512_5_2018,

    others
  };
  enum class JetScoreVer {
    v2409_2,
    v2512_3,
    v2512_4,

    v2512_5_2016preVFP,
    v2512_5_2016postVFP,
    v2512_5_2017,
    v2512_5_2018,

    others
  };
  */



  //void LoadChargeScoreTool(TString muon_version="2405.2",TString electron_version="2405.2", TString jet_version="2405.2", bool applycut=false);
  //void LoadChargeScoreTool(TString muon_version="2405.4.3",TString electron_version="2405.4.3", TString jet_version="2405.4.3", bool applycut=false);
  void LoadChargeScoreTool(TString muon_version="2512.4",TString electron_version="2512.4", TString jet_version="2512.4", bool applycut=false);
  void LoadChargeScoreTool_2409_2(bool applycut=false);
  void LoadChargeScoreTool_2512_3(bool applycut=false);
  void LoadChargeScoreTool_2512_4(bool applycut=false);
  void LoadChargeScoreTool_2512_5(bool applycut=false);
  void LoadChargeScoreTool_2608_2(bool applycut=false);
  
  void LoadChargeScoreTool_temp(TString muon_version="2409.2",TString electron_version="2409.2", TString jet_version="2409.2", bool applycut=false);
  bool IsChargeScoreToolOn=false;
  void DeleteChargeScoreTool();
  void SetChargeScoreCut(TString version);
  //void SetChargeScoreCut_2405_2();
  //void SetChargeScoreCut_2405_4();
  //void SetChargeScoreCut_2405_4_3();
  void SetChargeScoreCut_2409_2();
  void SetMuonChargeScore(Muon &_this_bmuon, const Jet &_this_bjet);
  void SetElectronChargeScore(Electron &_this_belectron, const Jet &_this_bjet);
  void SetJetChargeScore(const Jet &_this_bjet);
  double GetMuonChargeScore();
  double GetMuonChargeScoreCoeff();
  double GetElectronChargeScore();
  double GetElectronChargeScoreCoeff();
  double GetJetChargeScore();
  double GetJetChargeScoreCoeff();
  ChargeScoreTool *mChargeTool;
  bmuonvar bmuon_ChargeTool;
  bmuonvar_cut bmuon_ChargeTool_cut;
  ChargeScoreTool *eChargeTool;
  belectronvar belectron_ChargeTool;
  belectronvar_cut belectron_ChargeTool_cut;
  ChargeScoreTool *jChargeTool;
  bjetvar bjet_ChargeTool;
  bjetvar_cut bjet_ChargeTool_cut;




  //tuple<int,double,int,int,double,int> GetBJetMuonScore_v2405_4_3(Jet &_bjet, vector<Muon> &_muoncoll);
  //tuple<int,double,int,int,double,int> GetBJetElectronScore_v2405_4_3(Jet &_bjet, vector<Electron> &_electroncoll);
  //tuple<int,bool,int,int,double> GetBJetCharge_v2405_4_3(Jet &_bjet, vector<Muon> &_muoncoll, vector<Electron> &electroncoll);



  tuple<int,double,int,int,double,int> GetBJetMuonScore_v2409_2(Jet &_bjet, vector<Muon> &_muoncoll);
  tuple<int,double,int,int,double,int> GetBJetElectronScore_v2409_2(Jet &_bjet, vector<Electron> &_electroncoll);
  tuple<int,bool,int,int,double> GetBJetCharge_v2409_2(Jet &_bjet, vector<Muon> &_muoncoll, vector<Electron> &electroncoll);


  vector<int> GetMuonIdxInBJet(Jet &_bjet, vector<Muon> &_muoncoll);
  vector<int> GetElectronIdxInBJet(Jet &_bjet, vector<Electron> &_electroncoll);


  //---jet assignment
  //---input lins for TTSemilepJetAssignmentTool
  struct TTSemilepJetAssignmentToolvar{
    float met_pt=0;
    float met_phi=0;

    float lep_pt=0;
    float lep_eta=0;
    float lep_phi=0;

    float blep_pt=0;
    float blep_eta=0;
    float blep_phi=0;
    float blep_E=0;

    float bhad_pt=0;
    float bhad_eta=0;
    float bhad_phi=0;
    float bhad_E=0;

    float q1jet_pt=0;
    float q1jet_eta=0;
    float q1jet_phi=0;
    float q1jet_E=0;

    float q2jet_pt=0;
    float q2jet_eta=0;
    float q2jet_phi=0;
    float q2jet_E=0;
    
    float WhadCand_mass=0;
    float ThadCand_mass=0;

    float WlepCand_mt=0;
    float TlepCand_mt=0;

    
  };
  JHAnalyzerBase::TTSemilepJetAssignmentToolvar Get_JetAssignmentvar(TLorentzVector &_met, TLorentzVector &_lep, TLorentzVector &_blep, TLorentzVector &_bhad, TLorentzVector &_q1jet, TLorentzVector &_q2jet);

  TTSemilepJetAssignmentToolvar inputvar_TTSemilepJetAssignmentTool;
  void LoadTTSemilepJetAssignmentTool(TString version);
  TTSemilepJetAssignmentTool *TTLJJetAssignmentTool;
  bool IsTTLJJetAssignmentToolOn=false;
  double GetTTSemilepJetAssignmentScore();
  void SetTTSemilepJetAssignmentScore(TLorentzVector &_met, TLorentzVector &_lep, TLorentzVector &_blep, TLorentzVector &_bhad, TLorentzVector &_q1jet, TLorentzVector &_q2jet);
  static double Chi2TTSemiLep(double *x, double *par);
  void InitJetAssigenChi2Fitter();
  bool IsJetAssigenChi2FitterOn=false;
  void DeleteJetAssigenChi2Fitter();
  TF1 *f1;


  pair<vector<int>,double> GetJetIndexSet_Chi2(Lepton &_l1, TLorentzVector &_met,vector<Jet> &_v_tightjet, vector<int> &_v_bjetidx, bool _kincut);
  pair<vector<int>,double> GetJetIndexSet_Chi2_1b(Lepton &_l1, TLorentzVector &_met,vector<Jet> &_v_tightjet, int bjetidx, bool kincut=false);
  pair<vector<int>,double> GetJetIndexSet_Chi2_1b_AssignToLeptonicSide(Lepton &_l1, TLorentzVector &_met,vector<Jet> &_v_tightjet, int bjetidx, bool TopMassWindow=false);
  pair<vector<int>,double> GetJetIndexSet_Chi2_1b_AssignToHadronicSide(Lepton &_l1, TLorentzVector &_met,vector<Jet> &_v_tightjet, int bjetidx, bool TopMassWindow=false);
  pair<double,double> GetChi2_and_vz(TLorentzVector &_lep, TLorentzVector &_MET, TLorentzVector &_blep, TLorentzVector &_q1, TLorentzVector &_q2, TLorentzVector &_bhad);


  ///jet matching to gen ptl
  bool IsGENMatched_Flavour_dR(Jet& this_jet, int genidx);


  // mc btag eff
  void SetUpBtagEffMeasurement();
  void SetUpBtagEffMeasurementPartonFlavour();
  void SetUpBtagEffMeasurementPartonFlavour_bonly();
  void Measure_MCbtagEff();
  void Measure_MCbtagEff_PartonFlavour();
  void Measure_MCbtagEff_PartonFlavour_bonly();

  vector<string> TaggersToMeasure;
  vector<string> WPsToMeasure;
  vector<double> CutValuesToMeasure;

  //Use MET phi corr?
  bool UsePhiCorrMET=false;
  //UsePfMET
  bool UsePfMET=false;


  //JetPOG pt eta bin
  double jetpog_etabins[9] = {-2.5, -2., -1.6, -0.8, 0.0, 0.8, 1.6, 2., 2.5};
  const int njetpog_etabins=8;
  double jetpog_ptbins[10] = {20., 30., 50., 70., 100., 140., 200., 300., 600., 1000.};//PT bins used in POG SF measurements                                                                               
  const int njetpog_ptbins=9;

  //JetVetoMap//
  TFile* TFileJetVetoMap=NULL;
  TH2D* h_jetvetomap=NULL;
  void SetJetVetoMap();
  

  //--bChargeTagID--//
  //enum PtBin { kPT30To50 = 0, kPT50To70, kPT70To100, kPT100To140, kPT140ToInf, nPtBin };
  //enum EtaBin { kEta0To0p8 = 0, kEta0p8To1p6, kEta1p6To2, kEta2To2p5, nEtaBin};

  enum SLT { k_muH=0, k_muL, k_eH, k_eL, nSLT};
  enum JetOrigin{ k_bplus=0, k_bminus, nJetOrigin };
  enum SYSDIR{ k_central=0, k_uncorrUp, k_uncorrDown, k_corrUp, k_corrDown, nSYSDIR };

  inline static const char* SLTName[nSLT] ={
    "muH",
    "muL",
    "eH",
    "eL"
  };
  enum bChargeID{k_1muHOnly,k_1muLOnly,k_1eHOnly,k_1eLOnly,k_NoSL_jH,k_NoSL_jOthers};
  inline static const char* bChargeAccIDName[6]={
    "1muHOnly",
    "1muLOnly",
    "1eHOnly",
    "1eLOnly",
    "NoSL_jH",
    "NoSL_jOthers"
  };
  double SF_bChargeTagID_SLT[nJetOrigin][nSLT][nPtBin][nSYSDIR];
  double SF_bChargeTagID_Jet[nJetOrigin][nPtBin][nEtaBin][nSYSDIR];

  double SF_bChargeAcc_SLT[nJetOrigin][nSLT][nPtBin][nSYSDIR];
  double SF_bChargeAcc_Jet[nJetOrigin][2][nPtBin][nEtaBin][nSYSDIR];

  
  void Read_bChargeID_SF(bool readsltonly=false);
  void Read_bChargeAcc_SF();
  int getB(const std::string& s);
  int getLep(const std::string& s);
  int getIDAcc(const std::string& s);
  int getPT(const std::string& s);
  int getSysDir(const std::string& s);
  int getEta(const std::string& s);


  
  void Setup_bChargeIDEff(TString _bchargeid_mceff_filename="",bool readsltonly=false);
  void Setup_bChargeAcc(TString _bchargeacc_mc_filename="");
  bool Is_bChargeIDEffOn=false;
  bool Is_bChargeAccOn=false;
  void MeasureMC_bChargeIDEff(vector<Jet> vJets);
  void MeasureMC_bChargeAcc(vector<Jet> vJets);
  //void JHAnalyzerBase::MeasureMC_bChargeAcc(vector<Jet> vJets )
  vector<int> Count_SLT(const Jet& this_Jet);
  map<TString,TH2D*> map_effhist_bchargeID_mcjet;
  map<TString,TH2D*> map_acchist_bchargeID_mcjet;

  vector<double> Get_bChargeTagID_MCEffs_SLT( int partonFlavour, double JetPt);
  double Get_SLTEff_Corr_givenJet(const Jet& thisJet, const bool Has_muH, const bool Has_muL, const bool Has_eH, const bool Has_eL,
				  JHAnalyzerBase::SYSDIR SystDir=k_central, JHAnalyzerBase::PtBin SystPtBin=nPtBin, JHAnalyzerBase::SLT SystID=nSLT);
  
  double Get_bChargeTagID_MCEffs_jH(int partonFlavour, double JetPt, double JetEta);
  double Get_HighScoreChargeTagID_Eff_Corr_givenJet(const Jet& thisJet, const bool pass_jH,
						    JHAnalyzerBase::SYSDIR SystDir=k_central, JHAnalyzerBase::PtBin SystPtBin=nPtBin, JHAnalyzerBase::EtaBin SystEtaBin=nEtaBin);
  double Get_bChargeAcc_MC(int partonFlavour, int thisChargeID,double JetPt, double JetEta);
  ////-----bchargetagid----////
  //---Corrleated Component---//
  double arr_r_bChargeID_SLT_CorrUp[nSLT][nPtBin];
  double arr_r_bChargeID_SLT_CorrDown[nSLT][nPtBin];
  //---Uncorr. Component
  double arr_r_bChargeID_SLT_UnCorr_bPlusUp[nSLT][nPtBin];
  double arr_r_bChargeID_SLT_UnCorr_bPlusDown[nSLT][nPtBin];

  double arr_r_bChargeID_SLT_UnCorr_bMinusUp[nSLT][nPtBin];
  double arr_r_bChargeID_SLT_UnCorr_bMinusDown[nSLT][nPtBin];

  //---Corrleated Component--//
  double arr_r_bChargeID_Jet_CorrUp[nPtBin][nEtaBin];
  double arr_r_bChargeID_Jet_CorrDown[nPtBin][nEtaBin];
  //---Uncorr. Component
  double arr_r_bChargeID_Jet_UnCorr_bPlusUp[nPtBin][nEtaBin];
  double arr_r_bChargeID_Jet_UnCorr_bPlusDown[nPtBin][nEtaBin];

  double arr_r_bChargeID_Jet_UnCorr_bMinusUp[nPtBin][nEtaBin];
  double arr_r_bChargeID_Jet_UnCorr_bMinusDown[nPtBin][nEtaBin];


  ////-----bchargeacc----////
  //---Corrleated Component---//
  double arr_r_bChargeAcc_SLT_CorrUp[nSLT][nPtBin];
  double arr_r_bChargeAcc_SLT_CorrDown[nSLT][nPtBin];
  //---Uncorr. Component
  double arr_r_bChargeAcc_SLT_UnCorr_bPlusUp[nSLT][nPtBin];
  double arr_r_bChargeAcc_SLT_UnCorr_bPlusDown[nSLT][nPtBin];

  double arr_r_bChargeAcc_SLT_UnCorr_bMinusUp[nSLT][nPtBin];
  double arr_r_bChargeAcc_SLT_UnCorr_bMinusDown[nSLT][nPtBin];

  //---Corrleated Component--//
  double arr_r_bChargeAcc_Jet_CorrUp[2][nPtBin][nEtaBin];
  double arr_r_bChargeAcc_Jet_CorrDown[2][nPtBin][nEtaBin];
  //---Uncorr. Component
  double arr_r_bChargeAcc_Jet_UnCorr_bPlusUp[2][nPtBin][nEtaBin];
  double arr_r_bChargeAcc_Jet_UnCorr_bPlusDown[2][nPtBin][nEtaBin];

  double arr_r_bChargeAcc_Jet_UnCorr_bMinusUp[2][nPtBin][nEtaBin];
  double arr_r_bChargeAcc_Jet_UnCorr_bMinusDown[2][nPtBin][nEtaBin];  


  double Get_HighScoreChargeTagID_Eff_Corr(const vector<Jet> &_v_Jet, const vector<bool> _v_pass_jH);
  double Get_SLTEff_Corr(const vector<Jet> &_v_Jet, const vector<bool> _v_Has_muH, const vector<bool> _v_Has_muL, const vector<bool> _v_Has_eH, const vector<bool> _v_Has_eL);
  pair<int,int> GetMeasuredChargeAndID(const Jet& thisJet, bool ApplyAccCorr=true);
  double GetChargeAccCorr(const Jet& thisJet, int thisChargeID,int measured_charge);  

  //---new add. lepton veto
  bool HasVetoLepton_NotTightLeps_NotWithinJets(const vector<int>& _v_tightmuonidx, const vector<int>& _v_tightelectronidx,     const TLorentzVector* _jet1, const TLorentzVector* _jet2 = nullptr);


private:
  MomentumVar _CurrentSys;
  JetTagging::Parameters jtp;






};





#endif

