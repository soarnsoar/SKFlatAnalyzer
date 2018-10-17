#ifndef AnalyzerCore_h
#define AnalyzerCore_h

#include "TLorentzVector.h"
#include "TString.h"
#include "TMath.h"

#include "SKFlatNtuple.C"
#include "Event.h"
#include "Particle.h"
#include "Gen.h"
#include "Lepton.h"
#include "Muon.h"
#include "Electron.h"
#include "Photon.h"
#include "Jet.h"
#include "FatJet.h"

#include "AnalyzerParameter.h"
#include "MCCorrection.C"
#include "FakeBackgroundEstimator.C"
#include "CFBackgroundEstimator.C"

#define M_Z 91.1876
#define M_W 80.379

class AnalyzerCore: public SKFlatNtuple {

public:

  AnalyzerCore();
  ~AnalyzerCore();

  virtual void initializeAnalyzer(){

  };

  virtual void executeEvent(){

  };

  //==== Get objects

  Event GetEvent();

  std::vector<Muon> GetAllMuons();
  std::vector<Muon> GetMuons(TString id, double ptmin=-999., double fetamax=999.);

  std::vector<Electron> GetAllElectrons();
  std::vector<Electron> GetElectrons(TString id, double ptmin=-999., double fetamax=999.);

  std::vector<Photon> GetAllPhotons();
  std::vector<Photon> GetPhotons(TString id, double ptmin=-999., double fetamax=999.);
  
  std::vector<Lepton *> MakeLeptonPointerVector(std::vector<Muon>& muons, double TightIso=-999, bool UseMini=false);
  std::vector<Lepton *> MakeLeptonPointerVector(std::vector<Electron>& electrons, double TightIso=-999, bool UseMini=false);

  std::vector<Jet> GetAllJets();
  std::vector<Jet> GetJets(TString id, double ptmin=-999, double fetamax=999.);

  std::vector<FatJet> GetAllFatJets();
  std::vector<FatJet> GetFatJets(TString id, double ptmin=-999, double fetamax=999.);

  std::vector<Gen> GetGens();

  //==== Event Filters

  bool PassMETFilter();

  //============
  //==== Tools
  //============

  //===== Estimators

  MCCorrection mcCorr;
  FakeBackgroundEstimator fakeEst;
  CFBackgroundEstimator cfEst;

  //==== Functions

  bool IsOnZ(double m, double width);
  double MT(TLorentzVector a, TLorentzVector b);
  bool HasFlag(TString flag);
  std::vector<Muon> MuonWithoutGap(std::vector<Muon> muons);
  std::vector<Muon> MuonPromptOnly(std::vector<Muon> muons, std::vector<Gen> gens);
  std::vector<Muon> MuonUsePtCone(std::vector<Muon> muons);
  Muon MuonUsePtCone(Muon muon);
  Particle UpdateMET(Particle METv, std::vector<Muon> muons);
  std::vector<Muon> MuonApplyPtCut(std::vector<Muon> muons, double ptcut);
  std::vector<Electron> ElectronPromptOnly(std::vector<Electron> electrons, std::vector<Gen> gens);
  std::vector<Electron> ElectronUsePtCone(std::vector<Electron> electrons);
  Electron ElectronUsePtCone(Electron electron);
  std::vector<Electron> ElectronApplyPtCut(std::vector<Electron> electrons, double ptcut);
  std::vector<Jet> JetsAwayFromFatJet(std::vector<Jet> jets, std::vector<FatJet> fatjets, double mindr=1.0);
  std::vector<Jet> JetsVetoLeptonInside(std::vector<Jet> jets, std::vector<Electron> els, std::vector<Muon> mus);
  std::vector<Jet> JetsAwayFromPhoton(std::vector<Jet> jets, std::vector<Photon> photons, double mindr);
  Particle AddFatJetAndLepton(FatJet fatjet, Lepton lep);

  //==== GenMatching

  void PrintGen(std::vector<Gen> gens);
  Gen GetGenMatchedLepton(Lepton lep, std::vector<Gen> gens);
  Gen GetGenMathcedPhoton(Lepton lep, std::vector<Gen> gens);
  vector<int> TrackGenSelfHistory(Gen me, std::vector<Gen> gens);
  bool IsFromHadron(Gen me, std::vector<Gen> gens);
  int GetLeptonType(Lepton lep, std::vector<Gen> gens);
  int GetGenPhotonType(Gen genph, std::vector<Gen> gens);
  bool IsSignalPID(int pid);

  //==== Plotting

  std::map< TString, TH1D* > maphist_TH1D;
  std::map< TString, TH2D* > maphist_TH2D;

  TH1D* GetHist1D(TString histname);
  TH2D* GetHist2D(TString histname);

  void FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max);
  void FillHist(TString histname, double value, double weight, int n_bin, double *xbins);
  void FillHist(TString histname,
                double value_x, double value_y,
                double weight,
                int n_binx, double x_min, double x_max,
                int n_biny, double y_min, double y_max);
  void FillHist(TString histname,
                double value_x, double value_y,
                double weight,
                int n_binx, double *xbins,
                int n_biny, double *ybins);

  //==== JSFillHist : 1D
  std::map< TString, std::map<TString, TH1D*> > JSmaphist_TH1D;
  TH1D* JSGetHist1D(TString suffix, TString histname);
  void JSFillHist(TString suffix, TString histname, double value, double weight, int n_bin, double x_min, double x_max);
  //==== JSFillHist : 2D
  std::map< TString, std::map<TString, TH2D*> > JSmaphist_TH2D;
  TH2D* JSGetHist2D(TString suffix, TString histname);
  void JSFillHist(TString suffix, TString histname,
                  double value_x, double value_y,
                  double weight,
                  int n_binx, double x_min, double x_max,
                  int n_biny, double y_min, double y_max);
  void JSFillHist(TString suffix, TString histname,
                  double value_x, double value_y,
                  double weight,
                  int n_binx, double *xbins,
                  int n_biny, double *ybins);

  void WriteHist();

  //==== Quick Plotters
  void FillLeptonPlots(std::vector<Lepton *> leps, TString this_region, double weight);
  void FillJetPlots(std::vector<Jet> jets, std::vector<FatJet> fatjets, TString this_region, double weight);

  //==== Output rootfile

  TFile *outfile;
  void SetOutfilePath(TString outname){
    outfile = new TFile(outname,"RECREATE");
  };

};



#endif

