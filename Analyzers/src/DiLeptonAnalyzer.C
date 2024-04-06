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
  zptweight=1.;
  weakweight=1.;
  z0weight=1.;
  if(IsDATA) return;
  //----ZpT weight For DY
  //----DY WEAK NLO
  //---z0 weight

  lhes=GetLHEs();
  gens=GetGens();
  if(IsDYSample){
    GetAFBLHEParticles(lhes,lhe_p0,lhe_p1,lhe_l0,lhe_l1,lhe_j0);
    GetAFBGenParticles(gens,gen_p0,gen_p1,gen_l0,gen_l1,3);//mode==3 -> before FSR
    //GetAFBGenParticles(gens,gen_p0,gen_p1,gen_l0_dressed,gen_l1_dressed,1);
    //GetAFBGenParticles(gens,gen_p0,gen_p1,gen_l0_bare,gen_l1_bare,0);
    if(abs(lhe_l0.ID())==11||abs(lhe_l0.ID())==13){
      TLorentzVector genZ=(gen_l0+gen_l1);
      zptweight=GetZptWeight(genZ.M(),genZ.Rapidity(),genZ.Pt());
      weakweight=GetDYWeakWeight(genZ.M());
    }
    //
    
  }//[end] dysample
  z0weight=GetZ0Weight(vertex_Z);
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight;
  //weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0);
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
  SetEventWeight();
  
  //--Now Objects are ready--//


  LepCh="";
  if(IsDiMuonChannel){
    //vZ=(*mu1)+(*mu2);
    vZ=mu1+mu2;
    LepCh="mm";
    l1=mu1;
    l2=mu2;
    l1_uncorr=TLorentzVector(mu1);
    l1_uncorr.SetPtEtaPhiM(mu1.MiniAODPt(), mu1.Eta(), mu1.Phi(), mu1.M()  );
    l2_uncorr=TLorentzVector(mu2);
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
    l1_uncorr=TLorentzVector(el1);
    l1_uncorr.SetPtEtaPhiM(el1.UncorrPt(), el1.Eta(), el1.Phi(), el1.M()  );
    l2_uncorr=TLorentzVector(el2);
    l2_uncorr.SetPtEtaPhiM(el2.UncorrPt(), el2.Eta(), el2.Phi(), el2.M()  );
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



void DiLeptonAnalyzer::FillHistAll(TString cutname){

  FillHist(cutname+"/nPV",nPV,weight,100,0,100);
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
    if(njet>1){
      FillHist(cutname+"/pt_j2",v_tightjet[1].Pt(),weight,200,0,200);
      FillHist(cutname+"/eta_j2",v_tightjet[1].Eta(),weight,50,-3,3);
    }
  }
  
}
void DiLeptonAnalyzer::EventLoop(){
  RunBasicZregion();
}  
  




