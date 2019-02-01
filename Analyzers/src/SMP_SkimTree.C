#include "SMP_SkimTree.h"

void SMP_SkimTree::initializeAnalyzer(){

  newtree = fChain->CloneTree(0);

  triggers.clear();
  if(DataYear==2016){
    triggers = {
    };
  }
  else if(DataYear==2017){
    triggers = {
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v",
      "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"
    };
  }

  cout << "[SMP_SkimTree::initializeAnalyzer] triggers to skim = " << endl;
  for(unsigned int i=0; i<triggers.size(); i++){
    cout << "[SMP_SkimTree::initializeAnalyzer]   " << triggers.at(i) << endl;
  }

}

void SMP_SkimTree::executeEvent(){

  Event ev;
  ev.SetTrigger(*HLT_TriggerName);

  if( ev.PassTrigger(triggers) ){
    newtree->Fill();
  }

}

void SMP_SkimTree::executeEventFromParameter(AnalyzerParameter param){

}

SMP_SkimTree::SMP_SkimTree(){

}

SMP_SkimTree::~SMP_SkimTree(){

}

void SMP_SkimTree::WriteHist(){

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree->Write();
  outfile->cd();

}


