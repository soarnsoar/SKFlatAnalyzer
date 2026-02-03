#include "SingleLeptonAnalyzer.h"

SingleLeptonAnalyzer::SingleLeptonAnalyzer(){
  //runSys=true;
}

SingleLeptonAnalyzer::~SingleLeptonAnalyzer(){
  //==== Destructor of this Analyzer
}

void SingleLeptonAnalyzer::initializeAnalyzer(){
  cout << "[SingleLeptonAnalyzer::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupSingleLeptonChannel();
  noveto=false;
  if(HasFlag("noveto")){
    noveto=true;
  }
}


void SingleLeptonAnalyzer::SetMuon(const Muon& _l1){
  mu1=_l1;
}

bool SingleLeptonAnalyzer::CheckIsMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  vector<Muon> v_muon=noveto ? GetSingleMuRecoNoVeto(TriggerSafeCut_muon1) : GetSingleMuReco(TriggerSafeCut_muon1);
  if( v_muon.size()!=1) return 0;
  SetMuon(v_muon[0]);

  return 1;
}  

void SingleLeptonAnalyzer::SetElectron(const Electron& _l1){
  el1=_l1;
}


bool SingleLeptonAnalyzer::CheckIsElectronChannel(){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  vector<Electron> v_electron=noveto ? GetSingleElRecoNoVeto(TriggerSafeCut_electron1) : GetSingleElReco(TriggerSafeCut_electron1);
  if( v_electron.size()!=1) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  SetElectron(v_electron[0]);
  return 1;
}  

void SingleLeptonAnalyzer::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  //Muon
  if(IsMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }
  
}

void SingleLeptonAnalyzer::RunBasicWregion(){

  IsMuonChannel=false;
  IsElectronChannel=false;


  IsMuonChannel=CheckIsMuonChannel();
  if(!IsMuonChannel) IsElectronChannel=CheckIsElectronChannel();





  TString LepCh="";
  if(IsMuonChannel){
    vtW=GetTransverseVector(mu1)+CurrentMET;
    LepCh="Muon";
    l1=mu1;
  }
  else if(IsElectronChannel){
    vtW=GetTransverseVector(el1)+CurrentMET;
    LepCh="Electron";
    l1=el1;
  }  

  else{
    return;
  }
  //----Jet---//
  v_tightlep={l1};
  v_tightjet=GetTightJet(v_tightlep,30,jetetacut);
  v_bjet=GetBJet(v_tightjet);

  njet=v_tightjet.size();
  nbjet=v_bjet.size();

  //--Now Objects are ready--//
  SetEventWeight();

  if(CurrentMET.Pt() < 30.) return;
  if(vtW.M() < 60. ) return;
  FillHistAll("Lepton");
  FillHistAll(LepCh);
  if(nbjet==1){
    FillHistAll("Lepton__1bjet");
    FillHistAll(LepCh+"__1bjet");
  }
  if(nbjet==2){
    FillHistAll("Lepton__2bjet");
    FillHistAll(LepCh+"__2bjet");
  }
  
}
void SingleLeptonAnalyzer::FillHistAll(TString cutname){
  FillHist(cutname+"/nPV",nPV,weight,100,0,100);

  FillHist(cutname+"/MT_lv",vtW.M(),weight,200,0,200);

  FillHist(cutname+"/pt_l1",l1.Pt(),weight,200,0,200);
  FillHist(cutname+"/eta_l1",l1.Eta(),weight,50,-3,3);

  FillHist(cutname+"/njet",njet,weight,10,0,10);
  FillHist(cutname+"/nbjet",nbjet,weight,10,0,10);

  FillHist(cutname+"/met",CurrentMET.Pt(),weight,200,0,200);
  FillHist(cutname+"/dphi_l_met",CurrentMET.DeltaPhi(l1),weight,200,-4,4);

  if(njet>0){
    FillHist(cutname+"/pt_j1",v_tightjet[0].Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_j1",v_tightjet[0].Eta(),weight,50,-3,3);
    if(njet>1){
      FillHist(cutname+"/pt_j2",v_tightjet[1].Pt(),weight,200,0,200);
      FillHist(cutname+"/eta_j2",v_tightjet[1].Eta(),weight,50,-3,3);
    }
  }

  if(nbjet>0){
    FillHist(cutname+"/pt_bj1",v_bjet[0].Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_bj1",v_bjet[0].Eta(),weight,50,-3,3);
    if(nbjet>1){
      FillHist(cutname+"/pt_bj2",v_bjet[1].Pt(),weight,200,0,200);
      FillHist(cutname+"/eta_bj2",v_bjet[1].Eta(),weight,50,-3,3);
    }
  }
  
  
}


void SingleLeptonAnalyzer::EventLoop(){
  RunBasicWregion();

}





