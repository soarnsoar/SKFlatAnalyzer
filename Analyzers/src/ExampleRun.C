#include "ExampleRun.h"

ExampleRun::ExampleRun(){

  hoe_max = -1.;

}
ExampleRun::~ExampleRun(){

}

void ExampleRun::executeEvent(){


  //==== AnalyzerParameter

  AnalyzerParameter param;

  param.Name = "POG";

  param.Electron_Tight_ID = "passMediumID";
  param.Muon_Tight_ID = "POGTightWithTightIso";


  executeEventFromParameter(param);

}

void ExampleRun::executeEventFromParameter(AnalyzerParameter param){

  Event ev = GetEvent();

  FillHist("MET", ev.GetMETVector().Pt(), 1., 200, 0., 200.);
  JSFillHist(param.Name, "MET_"+param.Name, ev.GetMETVector().Pt(), 1., 200, 0., 200.);

}



