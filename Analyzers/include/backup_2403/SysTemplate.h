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
  double TriggerSafeCut_muon;
  double TriggerSafeCut_electron;
  vector<TString> MuonIDs, MuonIDSFKeys;

  double weight_Prefire;
  //
  TString ProcessName;
  std::vector<LHE> LHEs;

  SysTemplate();
  ~SysTemplate();

};



#endif

