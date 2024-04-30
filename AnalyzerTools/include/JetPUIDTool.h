#ifndef JETPUIDTOOL_H
#define JETPUIDTOOL_H

#include <map>
#include <vector>
#include "TString.h"
#include "TH2.h"
#include "Jet.h"
class JetPUIDTool{

 public:
  JetPUIDTool(bool _isdata);
  ~JetPUIDTool();
  double arr_cut[4]={0,0,0,0};
  void SetEra(TString _era);
  void SetCut(TString _WP);
  vector<Jet> GetJetsPassPUID(vector<Jet> &jetcoll);
  double GetSF(double pt, double eta);
  double GetSF_err(double pt, double eta);
  void ReadHist(TString _datadir,TString _era, TString _WP);
  double GetCurrentSF();
  double GetCurrentSF_Up();
  double GetCurrentSF_Down();
  double SF,SF_up,SF_down;
  TH2* h;
  TH2* hsys;
  std::map<TString, TString> map_eraInHist;
  bool isdata;
  TString era;
};
#endif
