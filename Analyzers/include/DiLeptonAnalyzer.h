#ifndef DiLeptonAnalyzer_h
#define DiLeptonAnalyzer_h

#include "JHAnalyzerBase.h"

class DiLeptonAnalyzer : public JHAnalyzerBase {

public:


  void EventLoop() override;
  
  bool CheckIsDiMuonChannel();
  bool CheckIsDiElectronChannel();
  void SetIsDimuonChannel();
  void SetIsDielectronChannel();
  void SetMuonIdx(int _idx1,int _idx2);
  void SetElectronIdx(int _idx1,int _idx2);  
  TLorentzVector GetDiMuonVector();
  TLorentzVector GetDiElectronVector();
  
  void RunBasicZregion();
  void FillHistAll(TString cutname);
  void FillHist(TString cutname,TString variablename,double value,double weight,int nbin,double xmin,double xmax);
  



  bool IsDiMuonChannel;
  bool IsDiElectronChannel;
  void SetEventWeight();
  int mu1idx,mu2idx,el1idx,el2idx;
  TLorentzVector vZ;
  Lepton l1,l2;
  unsigned int njet, nbjet;
  vector<Lepton> v_tightlep;
  vector<int> v_jetidx;
  vector<int> v_bjetidx;

  DiLeptonAnalyzer();
  ~DiLeptonAnalyzer();


  

};




#endif

