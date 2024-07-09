#ifndef TMVATOOL_H
#define TMVATOOL_H

#include <map>
#include <vector>
#include "TString.h"
#include <TXMLEngine.h>
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
  std::map<TString, float*> map_InputVariables;
  std::vector<TString> vInputVariables;
  TString xmlfile;
  void ReadXML();
  void AddVariable(TString _formula, float *_this_var_address);
  void SetupTMVA();
  float GetScore();
  void SetScore();
  TMVA::Reader * reader;
  void SetMinCut(float _mincut);
  void SetMaxCut(float _maxcut);
  float GetCoefficient();
  float mincut,maxcut;
  float score;
};
#endif
