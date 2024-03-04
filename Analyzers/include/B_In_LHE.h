#ifndef B_In_LHE_h
#define B_In_LHE_h

#include "AnalyzerCore.h"

class B_In_LHE : public AnalyzerCore {

public:

  void initializeAnalyzer();

  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  bool RunSyst;
  bool RunNewPDF;
  bool RunXSecSyst;

  TString IsoMuTriggerName;
  double TriggerSafePtCut;

  vector<TString> MuonIDs, MuonIDSFKeys;
  //vector<Muon> AllMuons;
  //vector<Jet> AllJets;

  double weight_Prefire;
  //
  TString ProcessName;
  std::vector<LHE> LHEs;

  B_In_LHE();
  ~B_In_LHE();

};



#endif

