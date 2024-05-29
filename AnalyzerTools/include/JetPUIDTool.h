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
  double GetEff_MC(double pt, double eta);
  double GetSF_Fail(double pt, double eta);
  double GetSF_Fail_Up(double pt, double eta);
  double GetSF_Fail_Down(double pt, double eta);
  void ReadHist(TString _datadir,TString _era, TString _WP);
  double GetCurrentSF();
  double GetCurrentSF_Up();
  double GetCurrentSF_Down();
  double SFtotal,SFtotal_up,SFtotal_down;
  TH2* h;
  TH2* heff;
  TH2* hsys;
  std::map<TString, TString> map_eraInHist;
  bool isdata;
  TString era;
};
#endif
