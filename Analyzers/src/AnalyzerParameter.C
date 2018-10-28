#include "AnalyzerParameter.h"

void AnalyzerParameter::Clear(){

  Name = "";

  MCCorrrectionIgnoreNoHist = false;

  Electron_Tight_ID = "";
  Electron_Loose_ID = "";
  Electron_Veto_ID = "";
  Electron_ID_SF_Key = "";
  Electron_FR_ID = "";
  Electron_FR_Key = "";
  Electron_CF_ID = "";
  Electron_CF_Key = "";
  Electron_Tight_RelIso = 999.;
  Electron_Loose_RelIso = 999.;
  Electron_Veto_RelIso = 999.;
  Electron_UseMini = false;
  Electron_UsePtCone = false;
  Electron_MinPt = 10.;

  Muon_Tight_ID = "";

  Muon_Loose_ID = "";
  Muon_Veto_ID = "";
  Muon_ID_SF_Key = "";
  Muon_ISO_SF_Key = "";
  Muon_Trigger_SF_Key = "";
  Muon_FR_ID = "";
  Muon_FR_Key = "";
  Muon_CF_ID = "";
  Muon_CF_Key = "";
  Muon_Tight_RelIso = 999.;
  Muon_Loose_RelIso = 999.;
  Muon_Veto_RelIso = 999.;
  Muon_UseMini = false;
  Muon_UsePtCone = false;
  Muon_UseTuneP = false;
  Muon_MinPt = 10.;

  Jet_ID = "";
  FatJet_ID = "";

}

AnalyzerParameter::AnalyzerParameter(){

  Name = "Default";

  MCCorrrectionIgnoreNoHist = false;

  Electron_Tight_ID = "passTightID";
  Electron_Loose_ID = "passLooseID";
  Electron_Veto_ID = "passVetoID";
  Electron_ID_SF_Key = "passTightID";

  Muon_Tight_ID = "POGTightWithTightIso";
  Muon_Loose_ID = "POGLoose";
  Muon_Veto_ID = "POGLoose";
  Muon_ID_SF_Key = "NUM_TightID_DEN_genTracks";
  Muon_ISO_SF_Key = "NUM_TightRelIso_DEN_TightIDandIPCut";
  Muon_Trigger_SF_Key = "POGTight";

  Jet_ID = "HN";
  FatJet_ID = "HN";

}

AnalyzerParameter::~AnalyzerParameter(){
}
