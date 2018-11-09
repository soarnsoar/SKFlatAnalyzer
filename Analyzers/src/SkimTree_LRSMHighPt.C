#include "SkimTree_LRSMHighPt.h"

void SkimTree_LRSMHighPt::initializeAnalyzer(){

  newtree = fChain->CloneTree(0);

}

void SkimTree_LRSMHighPt::executeEvent(){

  Event ev;
  ev.SetTrigger(*HLT_TriggerName);

  vector<TString> triggers = {
    "HLT_Mu50_v",
    "HLT_oldMu100_v",
    "HLT_TkMu100_v",
    "HLT_Ele35_WPTight_Gsf_v",
    "HLT_DoublePhoton70_v",
  };

  if( ev.PassTrigger(triggers) ){
    newtree->Fill();
  }

}

void SkimTree_LRSMHighPt::executeEventFromParameter(AnalyzerParameter param){

}

SkimTree_LRSMHighPt::SkimTree_LRSMHighPt(){

}

SkimTree_LRSMHighPt::~SkimTree_LRSMHighPt(){

}

void SkimTree_LRSMHighPt::WriteHist(){

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree->Write();
  outfile->cd();

}


