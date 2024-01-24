#ifndef SysTemplate_h
#define SysTemplate_h

#include "AnalyzerCore.h"

class SysTemplate : public AnalyzerCore {

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

  SysTemplate();
  ~SysTemplate();

};



#endif

