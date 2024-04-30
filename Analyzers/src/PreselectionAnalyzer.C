#include "PreselectionAnalyzer.h"
#include <map>
PreselectionAnalyzer::PreselectionAnalyzer(){
  //runSys=true;

  //JHAnalyzerBase::SetupDiLeptonChannel();  
}

PreselectionAnalyzer::~PreselectionAnalyzer(){
  //==== Destructor of this Analyzer
}

void PreselectionAnalyzer::initializeAnalyzer(){
  cout << "[PreselectionAnalyzer::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupDiLeptonChannel();
  IsDYSample=false;
  if(MCSample.Contains("DYJets")||MCSample.Contains("ZToEE")||MCSample.Contains("ZToMuMu")||MCSample.Contains(TRegexp("DY[0-9]Jets"))) IsDYSample=true;
  cout << "[IsDYSample]=" << IsDYSample << endl;
  /*
  if(HasFlag("jetpuid_tight")){
    _JETPUID="T";
    cout << "[JETPUID] TIGHT" << endl;
  }
  else if(HasFlag("jetpuid_medium")){
    _JETPUID="M";
    cout << "[JETPUID] MEDIUM" << endl;
  }
  else if(HasFlag("jetpuid_loose")){
    cout << "[JETPUID] LOOSE" << endl;
    _JETPUID="L";
  }
  else{
    _JETPUID="";
  }
  */
  _JETPUID="T";
  
  check_tmva_input=false;
  if(HasFlag("check_tmva_input")){
    check_tmva_input=true;
    cout << "check_tmva_input -> true" << endl;
  }

  
}


void PreselectionAnalyzer::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;
  
}

bool PreselectionAnalyzer::CheckIsDiMuonChannel(double min_mll,double max_mll){
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

void PreselectionAnalyzer::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;
  
}


bool PreselectionAnalyzer::CheckIsDiElectronChannel(double min_mll,double max_mll){
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

void PreselectionAnalyzer::SetEventNormWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full");
}

void PreselectionAnalyzer::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  //----ZpT weight For DY
  //----DY WEAK NLO
  //---z0 weight
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  
  if(IsDiMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsDiElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }


}

void PreselectionAnalyzer::RunBasicZregion(){

  IsDiMuonChannel=false;
  IsDiElectronChannel=false;
  double min_mll = 60;
  double max_mll = 120;

  IsDiMuonChannel=CheckIsDiMuonChannel(min_mll,max_mll);
  if(!IsDiMuonChannel) IsDiElectronChannel=CheckIsDiElectronChannel(min_mll,max_mll);

  



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
  v_tightjet=GetTightJet(v_tightlep,30,2.4,"tight",_JETPUID);
  v_bjet=GetBJet(v_tightjet);

  njet=v_tightjet.size();
  nbjet=v_bjet.size();


  //--Now Objects are ready--//
  SetEventWeight();  


  //----Let's select and fillhist  
  if(nbjet!=1) return ;
  dphi_z_b= fabs(v_bjet[0].DeltaPhi(vZ));
  ptzb=(v_bjet[0]+vZ).Pt();
  if(!runSys)FillHistAllChannel("Only1bjet");
  if(PuppiMET.Pt() > 75.) return;
  if(!runSys)FillHistAllChannel("AfterMETUnder75");
  if(dphi_z_b < 1.6) return;
  if(!runSys)FillHistAllChannel("AfterMETUnder75__dphizbOver1p6__");
  if(vZ.Pt()<15.) return;
  if(!runSys)FillHistAllChannel("AfterMETUnder75__dphizbOver1p6__ptzOver15");
  if(ptzb>60.) return;
  FillHistAllChannel("AfterMETUnder75__dphizbOver1p6__ptzOver15__ptzbUnber60");

  ///---Let's look into leptons in bjet---//
  if(!check_tmva_input) return;
  for(auto& muon : AllMuons){
    if(muon.DeltaR(v_bjet[0]) < 0.4){
	bmuonvar this_bmuon=Get_bmuonvars(muon,v_bjet[0]);
	FillHistAll_bmuon(LepCh+"__Presel",this_bmuon);	
	FillHistAll_bmuon("ll__Presel",this_bmuon);	
      }
  }//[end muon for loop]

  for(auto& electron : AllElectrons){
    if(electron.DeltaR(v_bjet[0]) < 0.4){
	belectronvar this_belectron=Get_belectronvars(electron,v_bjet[0]);
	FillHistAll_belectron(LepCh+"__Presel",this_belectron);	
	FillHistAll_belectron("ll__Presel",this_belectron);	
      }
  }//[end electron for loop]

  bjetvar this_bjet=Get_bjetvars(v_bjet[0]);
  FillHistAll_bjet(LepCh+"__Presel",this_bjet);	
  FillHistAll_bjet("ll__Presel",this_bjet);	
}//[end]RunBasic Zregion




void PreselectionAnalyzer::FillHistAll_bmuon(TString cutname,bmuonvar this_bmuon){
  FillHist(cutname+"/bmuon_P_jetrest",this_bmuon.P_jetrest,weight,10,0,10);
  FillHist(cutname+"/bmuon_ptwrtbjet",this_bmuon.ptwrtbjet,weight,10,0,10);
  FillHist(cutname+"/bmuon_dR_l_j",this_bmuon.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/bmuon_nsip3d",this_bmuon.nsip3d,weight,30,0,15);
  FillHist(cutname+"/bmuon_reltrkiso",this_bmuon.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/bmuon_reliso",this_bmuon.reliso,weight,150,0,15);
  FillHist(cutname+"/bmuon_charge",this_bmuon.charge,weight,3,-2,1);
}

void PreselectionAnalyzer::FillHistAll_belectron(TString cutname,belectronvar this_belectron){
  FillHist(cutname+"/belectron_P_jetrest",this_belectron.P_jetrest,weight,10,0,10);
  FillHist(cutname+"/belectron_ptwrtbjet",this_belectron.ptwrtbjet,weight,10,0,10);
  FillHist(cutname+"/belectron_dR_l_j",this_belectron.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/belectron_nsip3d",this_belectron.nsip3d,weight,30,0,15);
  FillHist(cutname+"/belectron_reltrkiso",this_belectron.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/belectron_reliso",this_belectron.reliso,weight,150,0,15);
  FillHist(cutname+"/belectron_charge",this_belectron.charge,weight,3,-2,1);
  FillHist(cutname+"/belectron_IsGsfCtfScPixChargeConsistent",this_belectron.IsGsfCtfScPixChargeConsistent,weight,3,-2,1);
}

void PreselectionAnalyzer::FillHistAll_bjet(TString cutname,bjetvar this_bjet){
  FillHist(cutname+"/bjet_pt",this_bjet.pt,weight,100,0,100);
  FillHist(cutname+"/bjet_aeta",this_bjet.aeta,weight,60,-3,3);
  FillHist(cutname+"/bjet_ChargedHadronEnergyFraction",this_bjet.ChargedHadronEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/bjet_NeutralHadronEnergyFraction",this_bjet.NeutralHadronEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/bjet_NeutralEmEnergyFraction",this_bjet.NeutralEmEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/bjet_ChargedEmEnergyFraction",this_bjet.ChargedEmEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/bjet_MuonEnergyFraction",this_bjet.MuonEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/bjet_charge",this_bjet.charge,weight,50,-1,1);
  FillHist(cutname+"/bjet_partonFlavour",this_bjet.partonFlavour,weight,27,-6,21);

}

void PreselectionAnalyzer::FillHistAllChannel(TString cutname){
  if(check_tmva_input) return;
  PreselectionAnalyzer::FillHistAll("ll__"+cutname);
  PreselectionAnalyzer::FillHistAll(LepCh+"__"+cutname);
}


void PreselectionAnalyzer::FillHistAll(TString cutname){

  FillHist(cutname+"/event",1,weight,1,0,1);
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

  FillHist(cutname+"/dphi_z_b",dphi_z_b,weight,80,0,4);
  FillHist(cutname+"/ptzb",ptzb,weight,60,0,120);
  FillHist(cutname+"/Zpt",vZ.Pt(),weight,100,0,200);

  
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
void PreselectionAnalyzer::FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max){
  JHAnalyzerBase::FillHist(histname,value,weight,n_bin,x_min,x_max);
  /*
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
  */

}
void PreselectionAnalyzer::EventLoop(){
  AnalyzerCore::FillHist("all/nmuons/"+ProcessName,AllMuons.size(),1,100,0.,100.);
  AnalyzerCore::FillHist("all/nelectrons/"+ProcessName,AllElectrons.size(),1,100,0.,100.);
  RunBasicZregion();
}  
  




