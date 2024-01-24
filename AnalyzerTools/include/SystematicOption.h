#ifndef SystematicOption_h//if contents of this header are not declared
#define SystematicOption_h//let's define them
#include <TString.h>
enum SysName{
  JES,
  JER,
  PU,
  Prefire,
  //
  MuonReco,
  MuonIso,
  MuonTrk,
  MuonID,
  //
  ElectronReco,
  ElectronIso,
  ElectronTrk,
  ElectronID,
  //
  muRmuF,
  PS,
  //
  btag,
  MuonRochCorr,
  ChRelib,
  ChDet,
  //
  MuonScale,
  ElectronScale,
  
};

class SystematicOption{
  bool IsWeight=false;
  bool IsMuonScale=false;
  bool IsElectronScale=false;
  bool IsJetScale=false;
  SysName name;
  TString EffKey="";

  SystematicOption();
  ~SystematicOption();

};


#endif // end of if not declared
