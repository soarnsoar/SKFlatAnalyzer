#ifndef TMVATOOL_H
#define TMVATOOL_H

#include <map>
#include <vector>
#include "TString.h"
#include <TXMLEngine.h>
//#include "TXMLEngine.h"
#include <TSystem.h>
#include <iostream>
#include "TMVA/PyMethodBase.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

class TMVATool{

 public:
  TMVATool(TString _xmlfile);
  ~TMVATool();
  struct VarSlot {
    float* addr;
    float min;
    float max;
};

  //std::map<TString, float*> map_InputVariables;
  std::map<TString, VarSlot> map_InputVariables;
  std::vector<TString> vInputVariables;
  
  void ReadXML();
  void AddVariable(TString _formula, float *_this_var_address,float min = -std::numeric_limits<float>::infinity(), float max = std::numeric_limits<float>::infinity());
  void SetupTMVA(TString type="BDT::BDT");//PyKeras::DNN
  float GetScore();
  void SetScore();
  TMVA::Reader * reader;
  void SetMinCut(float _mincut);
  void SetMaxCut(float _maxcut);
  float GetCoefficient();
  float mincut,maxcut;
  float score;
  int TotalCall=0;
  int TotalCallTime=0;
  TString Type;
private:
  TString this_xmlfile;
};
#endif
