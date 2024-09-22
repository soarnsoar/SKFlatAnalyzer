#ifndef TwoBjets_h
#define TwoBjets_h

#include "JHAnalyzerBase.h"

class TwoBjets : public JHAnalyzerBase {

public:

  void initializeAnalyzer() override;
  void EventLoop() override;



  bool CheckIsMuonChannel();
  bool CheckIsElectronChannel();
  void SetIsMuonChannel();
  void SetIsElectronChannel();
  
  void SetMuon(const Muon& _l1);
  void SetElectron(const Electron& _l1);
  
  void RunReco();


  void Run();
  void RunPlots();
  void FillHistCommon(TString cutname);
  void FillHistBInfo(TString cutname, int i_bjet);
  void FillHistAllB(TString cutname);
  

  TString LepCh;


  bool IsMuonChannel;
  bool IsElectronChannel;

  //For truth level into



  void SetEventWeight();
  
  bool HasMatchedRecoJet(int genidx, double dRcut=0.4);
  bool HasFlavourMatchedRecoJet(int genidx);


  Lepton mu1;
  Lepton el1;
  Lepton l1;
  unsigned int njet, nbjet;
  vector<Lepton> v_tightlep;

  vector<int> v_jetidx;
  vector<int> v_bjetidx;

  vector<Jet> v_tightjet;
  vector<Jet> v_bjet;

  TwoBjets();
  ~TwoBjets();

  //flags
  bool noveto;
  bool njet4;
  //bool MuonChargeOnly;




  


};




#endif

