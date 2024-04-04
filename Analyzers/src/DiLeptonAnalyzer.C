#include "DiLeptonAnalyzer.h"
#include <map>
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


void DiLeptonAnalyzer::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;
  
}

bool DiLeptonAnalyzer::CheckIsDiMuonChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  //vector<int> v_muonidx=GetIdxDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  vector<Muon> v_muon=GetDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  if( v_muon.size()<2) return 0;
  double mll=(v_muon[0]+v_muon[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;

  SetMuon(v_muon[0],v_muon[1]);

  return 1;
}  

void DiLeptonAnalyzer::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;
  
}


bool DiLeptonAnalyzer::CheckIsDiElectronChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  vector<Electron> v_electron=GetDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  if( v_electron.size()<2) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  SetElectron(v_electron[0],v_electron[1]);
  double mll=(v_electron[0]+v_electron[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;

  return 1;
}  

void DiLeptonAnalyzer::SetEventNormWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full");
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
  double min_mll = 60;
  double max_mll = 120;

  IsDiMuonChannel=CheckIsDiMuonChannel(min_mll,max_mll);
  if(!IsDiMuonChannel) IsDiElectronChannel=CheckIsDiElectronChannel(min_mll,max_mll);
  //SetEventWeight();
  
  //--Now Objects are ready--//


  LepCh="";
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
  //---Because we loaded btag, need btagsf
  if(!IsDATA) weight*=btagsf;
  if(nbjet==0){
    FillHistAll("ll__0bjet");
    FillHistAll(LepCh+"__0bjet");
  }
  if(nbjet==1){
    FillHistAll("ll__1bjet");
    FillHistAll(LepCh+"__1bjet");
  }
  if(nbjet==2){
    FillHistAll("ll__2bjet");
    FillHistAll(LepCh+"__2bjet");
  }
  
}


void DiLeptonAnalyzer::RunBasicZregion_CheckSF(){
  map<TString, double> weightMap;


  IsDiMuonChannel=false;
  IsDiElectronChannel=false;
  double min_mll = 60;
  double max_mll = 120;

  IsDiMuonChannel=CheckIsDiMuonChannel(min_mll,max_mll);
  if(!IsDiMuonChannel) IsDiElectronChannel=CheckIsDiElectronChannel(min_mll,max_mll);
  //SetEventWeight();
  SetEventNormWeight();
  //---weight map --//
  weightMap["pu"]=GetPileUpWeight(nPileUp,0);
  weightMap["prefire"]=GetPrefireWeight(0);

  weightMap["MuonRECO"]=w_MuonRECO[0][0];
  weightMap["MuonID"]=w_MuonID[0][0];
  weightMap["MuonTrk"]=w_MuonTrk[0][0];
  weightMap["MuonTrigger"]=w_MuonTrigger[0][0];

  weightMap["ElectronRECO"]=w_ElectronRECO[0][0];
  weightMap["ElectronID"]=w_ElectronID[0][0];
  weightMap["ElectronTrigger"]=w_ElectronTrigger[0][0];



  //--Now Objects are ready--//


  LepCh="";
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


  //---
  FillHistAllRegion("__nosf",weight,1);
  FillHistAllRegion("__puOnly",weight*weightMap["pu"],1);
  FillHistAllRegion("__prefireOnly",weight*weightMap["prefire"],1);
  FillHistAllRegion("__pu_prefire",weight*weightMap["prefire"]*weightMap["pu"],1);

  FillHistAllRegion("__MuonRECOOnly",weight*weightMap["MuonRECO"],1);
  FillHistAllRegion("__MuonRECO_MuonTrk",weight*weightMap["MuonRECO"]*weightMap["MuonTrk"],1);
  FillHistAllRegion("__MuonRECO_MuonTrk_MuonID",weight*weightMap["MuonRECO"]*weightMap["MuonTrk"]*weightMap["MuonID"],1);
  FillHistAllRegion("__MuonRECO_MuonTrk_MuonID_MuonTrigger",weight*weightMap["MuonRECO"]*weightMap["MuonTrk"]*weightMap["MuonID"]*weightMap["MuonTrigger"],1);
  FillHistAllRegion("__MuonRECO_MuonTrk_MuonID_MuonTrigger_btagsf",weight*weightMap["MuonRECO"]*weightMap["MuonTrk"]*weightMap["MuonID"]*weightMap["MuonTrigger"],btagsf);

  FillHistAllRegion("__pu_prefire_MuonRECO",weight*weightMap["pu"]*weightMap["prefire"]*weightMap["MuonRECO"],1);
  FillHistAllRegion("__pu_prefire_MuonRECO_MuonTrk",weight*weightMap["pu"]*weightMap["prefire"]*weightMap["MuonRECO"]*weightMap["MuonTrk"],1);
  FillHistAllRegion("__pu_prefire_MuonRECO_MuonTrk_MuonID",weight*weightMap["pu"]*weightMap["prefire"]*weightMap["MuonRECO"]*weightMap["MuonTrk"]*weightMap["MuonID"],1);
  FillHistAllRegion("__pu_prefire_MuonRECO_MuonTrk_MuonID_MuonTrigger",weight*weightMap["pu"]*weightMap["prefire"]*weightMap["MuonRECO"]*weightMap["MuonTrk"]*weightMap["MuonID"]*weightMap["MuonTrigger"],1);
  FillHistAllRegion("__pu_prefire_MuonRECO_MuonTrk_MuonID_MuonTrigger_btagsf",weight*weightMap["pu"]*weightMap["prefire"]*weightMap["MuonRECO"]*weightMap["MuonTrk"]*weightMap["MuonID"]*weightMap["MuonTrigger"],btagsf);



  FillHistAllRegion("__ElectronRECOOnly",weight*weightMap["ElectronRECO"],1);
  FillHistAllRegion("__ElectronRECO_ElectronID",weight*weightMap["ElectronRECO"]*weightMap["ElectronID"],1);
  FillHistAllRegion("__ElectronRECO_ElectronID_ElectronTrigger",weight*weightMap["ElectronRECO"]*weightMap["ElectronID"]*weightMap["ElectronTrigger"],1);
  FillHistAllRegion("__ElectronRECO_ElectronID_ElectronTrigger_btagsf",weight*weightMap["ElectronRECO"]*weightMap["ElectronID"]*weightMap["ElectronTrigger"],btagsf);

  FillHistAllRegion("__pu_prefire_ElectronRECO",weight*weightMap["pu"]*weightMap["prefire"]*weightMap["ElectronRECO"],1);
  FillHistAllRegion("__pu_prefire_ElectronRECO_ElectronID",weight*weightMap["pu"]*weightMap["prefire"]*weightMap["ElectronRECO"]*weightMap["ElectronID"],1);
  FillHistAllRegion("__pu_prefire_ElectronRECO_ElectronID_ElectronTrigger",weight*weightMap["pu"]*weightMap["prefire"]*weightMap["ElectronRECO"]*weightMap["ElectronID"]*weightMap["ElectronTrigger"],1);
  FillHistAllRegion("__pu_prefire_ElectronRECO_ElectronID_ElectronTrigger_btagsf",weight*weightMap["pu"]*weightMap["prefire"]*weightMap["ElectronRECO"]*weightMap["ElectronID"]*weightMap["ElectronTrigger"],btagsf);

  
}
void DiLeptonAnalyzer::FillHistAll(TString cutname){
  FillHist(cutname+"/nPV",nPV,weight,100,0,100);
  FillHist(cutname+"/M_ll",vZ.M(),weight,60,60,120);

  FillHist(cutname+"/pt_l1",l1.Pt(),weight,200,0,200);
  FillHist(cutname+"/pt_l2",l2.Pt(),weight,200,0,200);

  FillHist(cutname+"/pt_l",l1.Pt(),weight,200,0,200);
  FillHist(cutname+"/pt_l",l2.Pt(),weight,200,0,200);

  FillHist(cutname+"/eta_l1",l1.Eta(),weight,50,-3,3);
  FillHist(cutname+"/eta_l2",l2.Eta(),weight,50,-3,3);

  FillHist(cutname+"/eta_l",l1.Eta(),weight,50,-3,3);
  FillHist(cutname+"/eta_l",l2.Eta(),weight,50,-3,3);

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


void DiLeptonAnalyzer::FillHistAllRegion(TString suffix, double this_weight,double this_btagsf){
  FillHistAllX("ll"+suffix,this_weight);
  FillHistAllX(LepCh+suffix,this_weight);
  //---Because we loaded btagsf, need btagsf
  if(!IsDATA) this_weight*=this_btagsf;
  if(nbjet==0){
    FillHistAllX("ll__0bjet"+suffix,this_weight);
    FillHistAllX(LepCh+"__0bjet"+suffix,this_weight);
  }
  if(nbjet==1){
    FillHistAllX("ll__1bjet"+suffix,this_weight);
    FillHistAllX(LepCh+"__1bjet"+suffix,this_weight);
  }
  if(nbjet==2){
    FillHistAllX("ll__2bjet"+suffix,this_weight);
    FillHistAllX(LepCh+"__2bjet"+suffix,this_weight);
  }
}
void DiLeptonAnalyzer::FillHistAllX(TString cutname, double this_weight){
  
  FillHist(cutname+"/nPV",nPV,this_weight,100,0,100);
  FillHist(cutname+"/M_ll",vZ.M(),this_weight,60,60,120);

  FillHist(cutname+"/pt_l1",l1.Pt(),this_weight,200,0,200);
  FillHist(cutname+"/pt_l2",l2.Pt(),this_weight,200,0,200);

  FillHist(cutname+"/pt_l",l1.Pt(),this_weight,200,0,200);
  FillHist(cutname+"/pt_l",l2.Pt(),this_weight,200,0,200);

  FillHist(cutname+"/eta_l1",l1.Eta(),this_weight,50,-3,3);
  FillHist(cutname+"/eta_l2",l2.Eta(),this_weight,50,-3,3);

  FillHist(cutname+"/eta_l",l1.Eta(),this_weight,50,-3,3);
  FillHist(cutname+"/eta_l",l2.Eta(),this_weight,50,-3,3);

  FillHist(cutname+"/njet",njet,this_weight,10,0,10);
  FillHist(cutname+"/nbjet",nbjet,this_weight,10,0,10);

  FillHist(cutname+"/puppimet",PuppiMET.Pt(),this_weight,200,0,200);

  if(njet>0){
    FillHist(cutname+"/pt_j1",v_tightjet[0].Pt(),this_weight,200,0,200);
    FillHist(cutname+"/eta_j1",v_tightjet[0].Eta(),this_weight,50,-3,3);
    if(njet>1){
      FillHist(cutname+"/pt_j2",v_tightjet[1].Pt(),this_weight,200,0,200);
      FillHist(cutname+"/eta_j2",v_tightjet[1].Eta(),this_weight,50,-3,3);
    }
  }
  
  
}


void DiLeptonAnalyzer::EventLoop(){
  if(checksf){
    RunBasicZregion_CheckSF();
  }
  else{
    RunBasicZregion();
  }
}





