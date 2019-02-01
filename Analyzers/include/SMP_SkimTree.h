#ifndef SMP_SkimTree_h
#define SMP_SkimTree_h

#include "AnalyzerCore.h"

class SMP_SkimTree : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  SMP_SkimTree();
  ~SMP_SkimTree();

  TTree *newtree;

  vector<TString> triggers;
  void WriteHist();

};



#endif

