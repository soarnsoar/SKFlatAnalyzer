#ifndef SkimTree_Dilepton_1DeepJetTightWP_h
#define SkimTree_Dilepton_1DeepJetTightWP_h

#include "AnalyzerCore.h"

class SkimTree_Dilepton_1DeepJetTightWP : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  SkimTree_Dilepton_1DeepJetTightWP();
  ~SkimTree_Dilepton_1DeepJetTightWP();

  TTree *newtree;

  vector<TString> double_triggers;
  vector<TString> single_muon_triggers;
  vector<TString> single_electron_triggers;
  void WriteHist();

};



#endif
