#ifndef DiLeptonAnalyzer_h
#define DiLeptonAnalyzer_h

#include "JHAnalyzerBase.h"

class DiLeptonAnalyzer : public JHAnalyzerBase {

public:

  void initializeAnalyzer() override;
  void EventLoop() override;
  
  bool CheckIsDiMuonChannel(double min_mll, double max_mll);
  bool CheckIsDiElectronChannel(double min_mll, double max_mll);
  void SetIsDimuonChannel();
  void SetIsDielectronChannel();
  
  void SetMuon(const Muon& _l1, const Muon& _l2);
  void SetElectron(const Electron& _l1, const Electron& _l2);
  TLorentzVector GetDiMuonVector();
  TLorentzVector GetDiElectronVector();
  
  void RunBasicZregion();
  void FillHistAll(TString cutname);
  //void FillHist(TString cutname,TString variablename,double value,double weight,int nbin,double xmin,double xmax);
  



  bool IsDiMuonChannel;
  bool IsDiElectronChannel;
  void SetEventWeight();
  int mu1idx,mu2idx,el1idx,el2idx;
  Lepton mu1, mu2;
  Lepton el1, el2;
  TLorentzVector vZ;
  Lepton l1, l2;
  unsigned int njet, nbjet;
  vector<Lepton> v_tightlep;

  vector<int> v_jetidx;
  vector<int> v_bjetidx;

  vector<Jet> v_tightjet;
  vector<Jet> v_bjet;

  DiLeptonAnalyzer();
  ~DiLeptonAnalyzer();


  

};




#endif

