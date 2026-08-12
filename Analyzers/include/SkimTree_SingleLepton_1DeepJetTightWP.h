#ifndef SkimTree_SingleLepton_1DeepJetTightWP_h
#define SkimTree_SingleLepton_1DeepJetTightWP_h

#include "AnalyzerCore.h"

class SkimTree_SingleLepton_1DeepJetTightWP : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  SkimTree_SingleLepton_1DeepJetTightWP();
  ~SkimTree_SingleLepton_1DeepJetTightWP();

  TTree *newtree;


  vector<TString> single_lepton_triggers;

  void WriteHist();

};



#endif
