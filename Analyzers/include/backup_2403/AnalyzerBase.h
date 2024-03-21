#ifndef AnalyzerBase_h
#define AnalyzerBase_h

#include "AnalyzerCore.h"

class AnalyzerBase : public AnalyzerCore {

 public:

  void initializeAnalyzer();

  void executeEvent();
  //
  AnalyzerBase();
  ~AnalyzerBase();


  //--(1) Prepare Event--//
  void SetAllObjects();
  //SetAllObjects()
  //->This Mustbe done before start events.
  //->Read all objects and set systematic variations of momenta.
  void UpdateMET();
  //--(2) EventLoop--//
  virtual void EventLoop();//Some process you want to make histograms
  
  
};





#endif

