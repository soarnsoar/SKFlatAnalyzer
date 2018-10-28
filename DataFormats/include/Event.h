#ifndef Event_h
#define Event_h

#include "Particle.h"
#include "TString.h"
#include "TObject.h"

class Event : public TObject {
public:

  Event();
  ~Event();

  void SetMCweight(double genw);
  inline double MCweight() const { return j_MCweight; }

  void SetnPV(double n);
  inline int nPV() const { return j_nPV; }

  void SetTrigger(vector<string> HLT_TriggerName, vector<bool> HLT_TriggerFired);
  bool PassTrigger(TString trig);
  bool PassTrigger(std::vector<TString> trigs);
  double GetTriggerLumi(TString trig);
  bool IsPDForTrigger(TString trig, TString PD);

  void SetMET(double pt, double px, double py);
  inline Particle GetMETVector() const {return j_METVector;}

  void SetDataYear(int y);
  inline int DataYear() const {return j_DataYear;}

private:
  double j_MCweight;
  int j_nPV;
  vector<string> j_HLT_TriggerName;
  vector<bool> j_HLT_TriggerFired;
  Particle j_METVector;
  int j_DataYear;

  ClassDef(Event,1)
};

#endif
