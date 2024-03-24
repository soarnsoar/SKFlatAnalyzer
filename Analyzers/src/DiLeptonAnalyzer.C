#include "DiLeptonAnalyzer.h"

DiLeptonAnalyzer::DiLeptonAnalyzer(){
  //runSys=true;

  //JHAnalyzerBase::SetupDiLeptonChannel();  
}

DiLeptonAnalyzer::~DiLeptonAnalyzer(){
  //==== Destructor of this Analyzer
}

void DiLeptonAnalyzer::initializeAnalyzer(){
  cout << "[DiLeptonAnalyzer::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupDiLeptonChannel();

}

void DiLeptonAnalyzer::SetMuonIdx(int _l1idx, int _l2idx){
  mu1idx=_l1idx;
  mu2idx=_l2idx;
  
}
void DiLeptonAnalyzer::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;
  
}

bool DiLeptonAnalyzer::CheckIsDiMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  cout << "Pass DiMuonTrigger!" << endl;
  //vector<int> v_muonidx=GetIdxDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  vector<Muon> v_muon=GetDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  if( v_muon.size()<2) return 0;
  SetMuon(v_muon[0],v_muon[1]);

  return 1;
}  
void DiLeptonAnalyzer::SetElectronIdx(int _l1idx, int _l2idx){
  el1idx=_l1idx;
  el2idx=_l2idx;  
  
}
void DiLeptonAnalyzer::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;
  
}


bool DiLeptonAnalyzer::CheckIsDiElectronChannel(){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  vector<Electron> v_electron=GetDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  if( v_electron.size()<2) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  SetElectron(v_electron[0],v_electron[1]);
  return 1;
}  

void DiLeptonAnalyzer::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0);
  //Muon
  if(IsDiMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsDiElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }
  
}

void DiLeptonAnalyzer::RunBasicZregion(){

  IsDiMuonChannel=false;
  IsDiElectronChannel=false;


  IsDiMuonChannel=CheckIsDiMuonChannel();
  if(!IsDiMuonChannel) IsDiElectronChannel=CheckIsDiElectronChannel();
  SetEventWeight();

  //--Now Objects are ready--//


  TString LepCh="";
  if(IsDiMuonChannel){
    //vZ=(*mu1)+(*mu2);
    vZ=mu1+mu2;
    LepCh="mm";
    l1=mu1;
    l2=mu2;
  }
  else if(IsDiElectronChannel){
    //vZ=GetDiElectronVector();
    vZ=el1+el2;
    LepCh="ee";
    //l1=AllElectrons[el1idx];
    //l2=AllElectrons[el2idx];
    l1=el1;
    l2=el2;
  }  

  else{
    return;
  }
  //----Jet---//
  v_tightlep={l1,l2};
  //v_jetidx=GetIdxTightJet(v_tightlep,30,2.4);
  //v_bjetidx=GetIdxBJet(v_jetidx);
  v_tightjet=GetTightJet(v_tightlep,30,2.4);
  v_bjet=GetBJet(v_tightjet);

  //njet=v_jetidx.size();
  //nbjet=v_bjetidx.size();
  njet=v_tightjet.size();
  nbjet=v_bjet.size();

  FillHistAll("ll");
  FillHistAll(LepCh);
  if(nbjet==1){
    FillHistAll("ll__1bjet");
    FillHistAll(LepCh+"__1bjet");
  }
  if(nbjet==2){
    FillHistAll("ll__2bjet");
    FillHistAll(LepCh+"__2bjet");
  }
  
}
void DiLeptonAnalyzer::FillHistAll(TString cutname){
  FillHist(cutname+"/M_ll",vZ.M(),weight,100,40,140);

  FillHist(cutname+"/pt_l1",l1.Pt(),weight,200,0,200);
  FillHist(cutname+"/pt_l2",l2.Pt(),weight,200,0,200);

  FillHist(cutname+"/eta_l1",l1.Eta(),weight,50,3,3);
  FillHist(cutname+"/eta_l2",l2.Eta(),weight,50,-3,3);

  FillHist(cutname+"/njet",njet,weight,10,0,10);
  FillHist(cutname+"/nbjet",nbjet,weight,10,0,10);

  FillHist(cutname+"/puppimet",PuppiMET.Pt(),weight,200,0,200);

  if(njet>0){
    FillHist(cutname+"/pt_j1",v_tightjet[0].Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_j1",v_tightjet[0].Eta(),weight,50,-3,3);
    if(njet>1){
      FillHist(cutname+"/pt_j2",v_tightjet[1].Pt(),weight,200,0,200);
      FillHist(cutname+"/eta_j2",v_tightjet[1].Eta(),weight,50,-3,3);
    }
  }
  
  
}


void DiLeptonAnalyzer::EventLoop(){
  RunBasicZregion();

}





