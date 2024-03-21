#include "DiLeptonAnalyzer.h"

DiLeptonAnalyzer::DiLeptonAnalyzer(){
  runSys=true;
  JHAnalyzerBase::SetupDiLeptonChannel();  
}

DiLeptonAnalyzer::~DiLeptonAnalyzer(){
  //==== Destructor of this Analyzer
}


void DiLeptonAnalyzer::SetMuonIdx(int _l1idx, int _l2idx){
  mu1idx=_l1idx;
  mu2idx=_l2idx;
  
}
bool DiLeptonAnalyzer::CheckIsDiMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  vector<int> v_muonidx=GetIdxDiMuReco(AllMuons, TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  if( v_muonidx.size()<2) return 0;
  SetMuonIdx(v_muonidx[0],v_muonidx[1]);
  return 1;
}  
void DiLeptonAnalyzer::SetElectronIdx(int _l1idx, int _l2idx){
  el1idx=_l1idx;
  el2idx=_l2idx;  
}
TLorentzVector DiLeptonAnalyzer::GetDiMuonVector(){
  return AllMuons[mu1idx]+AllMuons[mu2idx];
}
TLorentzVector DiLeptonAnalyzer::GetDiElectronVector(){
  return AllElectrons[el1idx]+AllElectrons[el2idx];
}


bool DiLeptonAnalyzer::CheckIsDiElectronChannel(){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  vector<int> v_electronidx=GetIdxDiElReco(AllElectrons, TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  if( v_electronidx.size()<2) return 0;
  SetElectronIdx(v_electronidx[0],v_electronidx[1]);
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
  IsDiElectronChannel=CheckIsDiElectronChannel();

  
  if(!IsDiMuonChannel) IsDiElectronChannel=CheckIsDiElectronChannel();
  SetEventWeight();




  TString LepCh="ll";
  if(IsDiMuonChannel){
    vZ=GetDiMuonVector();
    LepCh="mm";
    l1=AllMuons[mu1idx];
    l2=AllMuons[mu2idx];
  }
  else if(IsDiElectronChannel){
    vZ=GetDiElectronVector();
    LepCh="ee";
    l1=AllElectrons[el1idx];
    l2=AllElectrons[el2idx];
  }  

  //----Jet---//
  v_tightlep={l1,l2};
  v_jetidx=GetIdxTightJet(AllJets,v_tightlep,30,2.4);    
  v_bjetidx=GetIdxBJet(v_jetidx);

  njet=v_jetidx.size();
  nbjet=v_bjetidx.size();

  //double PuppiMET_pt=PuppiMET.Pt();

  //
  FillHistAll("ll");
  FillHistAll(LepCh);
  if(nbjet==1){
    FillHistAll("ll__1bjet");
    FillHistAll(LepCh+"__1bjet");
  }
  if(nbjet==2){
    FillHistAll(LepCh+"__2bjet");
  }
  
}
void DiLeptonAnalyzer::FillHistAll(TString cutname){
  FillHist(cutname,"M_ll",vZ.M(),weight,100,40,140);
  FillHist(cutname,"pt_l1",l1.Pt(),weight,200,0,400);
  FillHist(cutname,"pt_l2",l2.Pt(),weight,200,0,400);

  FillHist(cutname,"eta_l1",l1.Eta(),weight,50,3,3);
  FillHist(cutname,"eta_l2",l2.Eta(),weight,50,-3,3);

  FillHist(cutname,"njet",njet,weight,10,0,10);
  FillHist(cutname,"nbjet",nbjet,weight,10,0,10);

  FillHist(cutname,"puppimet",PuppiMET.Pt(),weight,100,0,100);

  if(njet>0){
    FillHist(cutname,"pt_j1",AllJets[v_jetidx[0]].Pt(),weight,100,0,200);
    FillHist(cutname,"eta_j1",AllJets[v_jetidx[0]].Eta(),weight,50,-3,3);
    if(njet>1){
      FillHist(cutname,"pt_j2",AllJets[v_jetidx[1]].Pt(),weight,100,0,200);
      FillHist(cutname,"eta_j2",AllJets[v_jetidx[1]].Eta(),weight,50,-3,3);
    }
  }
  
  
}

void DiLeptonAnalyzer::FillHist(TString cutname,TString variablename,double value,double weight,int nbin,double xmin,double xmax){
  JHAnalyzerBase::FillHist(cutname+"/"+variablename,value,weight,nbin,xmin,xmax);
}


void DiLeptonAnalyzer::EventLoop(){
  RunBasicZregion();

}





