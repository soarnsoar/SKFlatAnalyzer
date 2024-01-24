#ifndef BBosillation_h
#define BBosillation_h

#include "AnalyzerCore.h"

class BBosillation : public AnalyzerCore {

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
  vector<Muon> AllMuons;
  vector<Jet> AllJets;

  double weight_Prefire;
  //
  TString ProcessName;
  std::vector<LHE> LHEs;

  BBosillation();
  ~BBosillation();

};



#endif

