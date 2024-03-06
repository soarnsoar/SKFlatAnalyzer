#ifndef AnalyzerBase_h
#define AnalyzerBase_h

#include "AnalyzerCore.h"

class AnalyzerBase : public AnalyzerCore {

public:

  void initializeAnalyzer();

  void executeEvent();

  //
  TString ProcessName;
  AnalyzerBase();
  ~AnalyzerBase();

};



#endif

