#ifndef SingleLeptonAnalyzer_h
#define SingleLeptonAnalyzer_h

#include "JHAnalyzerBase.h"

class SingleLeptonAnalyzer : public JHAnalyzerBase {

public:

  void initializeAnalyzer() override;
  void EventLoop() override;
  
  bool CheckIsMuonChannel();
  bool CheckIsElectronChannel();
  void SetIsMuonChannel();
  void SetIsElectronChannel();
  
  void SetMuon(const Muon& _l1);
  void SetElectron(const Electron& _l1);
  
  void RunBasicWregion();
  void FillHistAll(TString cutname);
  



  bool IsMuonChannel;
  bool IsElectronChannel;
  void SetEventWeight();
  
  Lepton mu1;
  Lepton el1;
  TLorentzVector vtW;
  Lepton l1;
  unsigned int njet, nbjet;
  vector<Lepton> v_tightlep;

  vector<int> v_jetidx;
  vector<int> v_bjetidx;

  vector<Jet> v_tightjet;
  vector<Jet> v_bjet;

  SingleLeptonAnalyzer();
  ~SingleLeptonAnalyzer();


  bool noveto;

};




#endif

