#ifndef B_In_GEN_h
#define B_In_GEN_h

#include "AnalyzerCore.h"

class B_In_GEN : public AnalyzerCore {

public:

  void initializeAnalyzer();

  void executeEventFromParameter(AnalyzerParameter param);
  void executeExoticEvent();
  void executeEvent();

  bool RunSyst;
  bool RunNewPDF;
  bool RunXSecSyst;

  TString IsoMuTriggerName;
  double TriggerSafePtCut;

  vector<TString> MuonIDs, MuonIDSFKeys;
  vector<Muon> AllMuons;
  vector<Jet> AllJets;

  double weight_Prefire;
  //
  TString ProcessName;
  std::vector<Gen> GENs;
  std::vector<LHE> LHEs;
  bool doPrint;
  B_In_GEN();
  ~B_In_GEN();

};



#endif

