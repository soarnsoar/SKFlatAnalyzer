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
  IsDYSample=false;
  if(MCSample.Contains("DYJets")||MCSample.Contains("ZToEE")||MCSample.Contains("ZToMuMu")||MCSample.Contains(TRegexp("DY[0-9]Jets"))) IsDYSample=true;
  cout << "[IsDYSample]=" << IsDYSample << endl;
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
  
  double mll=(v_electron[0]+v_electron[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;
  SetElectron(v_electron[0],v_electron[1]);
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
  //----ZpT weight For DY
  //----DY WEAK NLO
  //---z0 weight
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf;

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

  
  //--Now Objects are ready--//


  LepCh="";
  if(IsDiMuonChannel){
    //vZ=(*mu1)+(*mu2);
    vZ=mu1+mu2;
    LepCh="mm";
    l1=mu1;
    l2=mu2;
    l1_uncorr.SetPtEtaPhiM(mu1.MiniAODPt(), mu1.Eta(), mu1.Phi(), mu1.M()  );
    l2_uncorr.SetPtEtaPhiM(mu2.MiniAODPt(), mu2.Eta(), mu2.Phi(), mu2.M()  );
  }
  else if(IsDiElectronChannel){
    //vZ=GetDiElectronVector();
    vZ=el1+el2;
    LepCh="ee";
    //l1=AllElectrons[el1idx];
    //l2=AllElectrons[el2idx];
    l1=el1;
    l2=el2;
    l1_uncorr.SetPtEtaPhiM(el1.UncorrPt(), el1.Eta(), el1.Phi(), el1.M()  );
    l2_uncorr.SetPtEtaPhiM(el2.UncorrPt(), el2.Eta(), el2.Phi(), el2.M()  );
  }  
  else{
    return;
  }
  //----Jet---//
  v_tightlep={l1,l2};
  v_tightjet=GetTightJet(v_tightlep,30,2.4,"tight");
  v_bjet=GetBJet(v_tightjet);

  njet=v_tightjet.size();
  nbjet=v_bjet.size();

  SetEventWeight();  
  FillHistAll("ll");
  FillHistAll(LepCh);

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



void DiLeptonAnalyzer::FillHistAll(TString cutname){


  FillHist(cutname+"/nPV",nPV,weight,100,0,100);
  FillHist(cutname+"/vertex_Z",vertex_Z,weight,80,-20,20);
  FillHist(cutname+"/M_ll",vZ.M(),weight,60,60,120);
  FillHist(cutname+"/M_ll_uncorr",(l1_uncorr+l2_uncorr).M(),weight,60,60,120);



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
    if(!runSys){
      FillHist(cutname+"/dR_j1_l1",v_tightjet[0].DeltaR(l1),weight,40,0,4);
      FillHist(cutname+"/dR_j1_l2",v_tightjet[0].DeltaR(l2),weight,40,0,4);
      FillHist(cutname+"/dR_j1_Z",v_tightjet[0].DeltaR(vZ),weight,40,0,4);
    }
    if(njet>1){
      FillHist(cutname+"/pt_j2",v_tightjet[1].Pt(),weight,200,0,200);
      FillHist(cutname+"/eta_j2",v_tightjet[1].Eta(),weight,50,-3,3);
      if(!runSys){
	FillHist(cutname+"/dR_j2_l1",v_tightjet[1].DeltaR(l1),weight,40,0,4);
	FillHist(cutname+"/dR_j2_l2",v_tightjet[1].DeltaR(l2),weight,40,0,4);
	FillHist(cutname+"/dR_j2_Z",v_tightjet[1].DeltaR(vZ),weight,40,0,4);
      }
    }
  }
  if(nbjet>0){
    FillHist(cutname+"/pt_bj1",v_bjet[0].Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_bj1",v_bjet[0].Eta(),weight,50,-3,3);
    if(!runSys){
      FillHist(cutname+"/dR_bj1_l1",v_bjet[0].DeltaR(l1),weight,40,0,4);
      FillHist(cutname+"/dR_bj1_l2",v_bjet[0].DeltaR(l2),weight,40,0,4);
      FillHist(cutname+"/dR_bj1_Z",v_bjet[0].DeltaR(vZ),weight,40,0,4);
    }
    if(nbjet>1){
      FillHist(cutname+"/pt_bj2",v_bjet[1].Pt(),weight,200,0,200);
      FillHist(cutname+"/eta_bj2",v_bjet[1].Eta(),weight,50,-3,3);
      if(!runSys){
	FillHist(cutname+"/dR_bj2_l1",v_bjet[1].DeltaR(l1),weight,40,0,4);
	FillHist(cutname+"/dR_bj2_l2",v_bjet[1].DeltaR(l2),weight,40,0,4);
	FillHist(cutname+"/dR_bj2_Z",v_bjet[1].DeltaR(vZ),weight,40,0,4);
      }
    }
  }



  for( const auto& jet : v_tightjet){
    FillHist(cutname+"/pt_j",jet.Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_j",jet.Eta(),weight,50,-3,3);
    if(!runSys){
      FillHist(cutname+"/dR_j_l1",jet.DeltaR(l1),weight,40,0,4);
      FillHist(cutname+"/dR_j_l2",jet.DeltaR(l2),weight,40,0,4);
      FillHist(cutname+"/dR_j_Z",jet.DeltaR(vZ),weight,40,0,4);
    }
  }
  for( const auto& bjet : v_bjet){
    FillHist(cutname+"/pt_bj",bjet.Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_bj",bjet.Eta(),weight,50,-3,3);
    if(!runSys){
      FillHist(cutname+"/dR_bj_l1",bjet.DeltaR(l1),weight,40,0,4);
      FillHist(cutname+"/dR_bj_l2",bjet.DeltaR(l2),weight,40,0,4);
      FillHist(cutname+"/dR_bj_Z",bjet.DeltaR(vZ),weight,40,0,4);
    }
  }


}
void DiLeptonAnalyzer::FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max){
  JHAnalyzerBase::FillHist(histname,value,weight,n_bin,x_min,x_max);
  
  if(!runSys){
    N_1_weightmap["pu"]=GetPileUpWeight(nPileUp,0) ? 1/GetPileUpWeight(nPileUp,0) : 0;
    N_1_weightmap["prefire"]=GetPileUpWeight(nPileUp,0) ? 1/GetPileUpWeight(nPileUp,0) : 0;
    N_1_weightmap["zptweight"]=zptweight ? 1/zptweight : 0;
    N_1_weightmap["z0weight"]=z0weight ? 1/z0weight : 0;
    N_1_weightmap["weakweight"]=weakweight ? 1/weakweight : 0;
    N_1_weightmap["topptweight"]=topptweight ? 1/topptweight : 0;
    
    N_1_weightmap["w_MuonID"]=w_MuonID[0][0] ? 1/w_MuonID[0][0] : 0;
    N_1_weightmap["w_MuonRECO"]=w_MuonRECO[0][0] ? 1/w_MuonRECO[0][0] : 0;
    N_1_weightmap["w_MuonTrk"]=w_MuonTrk[0][0] ? 1/w_MuonTrk[0][0] : 0;
    N_1_weightmap["w_MuonTrigger"]=w_MuonTrigger[0][0] ? 1/w_MuonTrigger[0][0] : 0;
    
    N_1_weightmap["w_ElectronID"]=w_ElectronID[0][0] ? 1/w_ElectronID[0][0] : 0;
    N_1_weightmap["w_ElectronRECO"]=w_ElectronRECO[0][0] ? 1/w_ElectronRECO[0][0] : 0;
    N_1_weightmap["w_ElectronTrigger"]=w_ElectronTrigger[0][0] ? 1/w_ElectronTrigger[0][0] : 0;
    N_1_weightmap["btagsf"]=btagsf ? 1/btagsf : 0;
    
    
    for(const auto& pair : N_1_weightmap){
      TString suffix="__No_"+pair.first;
      TString newhistname=histname+suffix;
      JHAnalyzerBase::FillHist("N-1__"+newhistname,value,weight*pair.second,n_bin,x_min,x_max);
    }
  
  }


}
void DiLeptonAnalyzer::EventLoop(){
  AnalyzerCore::FillHist("all/nmuons/"+ProcessName,AllMuons.size(),1,100,0.,100.);
  AnalyzerCore::FillHist("all/nelectrons/"+ProcessName,AllElectrons.size(),1,100,0.,100.);
  RunBasicZregion();
}  
  




