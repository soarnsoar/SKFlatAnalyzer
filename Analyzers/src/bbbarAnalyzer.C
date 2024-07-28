#include "bbbarAnalyzer.h"
#include <map>
bbbarAnalyzer::bbbarAnalyzer(){

}

bbbarAnalyzer::~bbbarAnalyzer(){
  //==== Destructor of this Analyzer
}

void bbbarAnalyzer::initializeAnalyzer(){
  cout << "[bbbarAnalyzer::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupDiLeptonChannel();
  IsDYSample=false;
  if(MCSample.Contains("DYJets")||MCSample.Contains("ZToEE")||MCSample.Contains("ZToMuMu")||MCSample.Contains(TRegexp("DY[0-9]Jets"))) IsDYSample=true;
  cout << "[IsDYSample]=" << IsDYSample << endl;

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
  else if(HasFlag("nojetpuid")){
    cout << "[JETPUID] NOCUT" << endl;
    _JETPUID="";
  }
  else{
    cout << "[JETPUID] DEFAULT===>" << endl;
    _JETPUID="";
  }

  //_JETPUID="T";
  //lepveto
  lepveto=false;
  if(HasFlag("lepveto")){
    lepveto=true;
    cout << "lepveto -> true" << endl;
  }  


  //charge
  TString v_muonScore="2405.4.3";
  TString v_electronScore="2405.4.3";
  TString v_jetScore="2405.4.3";
  if(HasFlag("dnn_v2405.4")){
    v_muonScore="2405.4";
    v_electronScore="2405.4";
    v_jetScore="2405.2";
  }


  bool apply_dnncut=1;
  //if(HasFlag("apply_dnncut")){
  //  apply_dnncut=true;
  //}

  LoadChargeScoreTool(v_muonScore,v_electronScore,v_jetScore,apply_dnncut);



  jhchoi_newtree=new TTree("vars","vars");
  SetBranches(jhchoi_newtree);

}

void bbbarAnalyzer::SetBranches(TTree *this_Tree){
  this_Tree->Branch("bmuon_score_max",&bmuon_score_max);
  this_Tree->Branch("bmuon_charge_max",&bmuon_charge_max);
  
  this_Tree->Branch("bmuon_score_min",&bmuon_score_min);
  this_Tree->Branch("bmuon_charge_min",&bmuon_charge_min);

  this_Tree->Branch("belectron_score_max",&belectron_score_max);
  this_Tree->Branch("belectron_charge_max",&belectron_charge_max);

  this_Tree->Branch("belectron_score_min",&belectron_score_min);
  this_Tree->Branch("belectron_charge_min",&belectron_charge_min);

  this_Tree->Branch("bjet_score",&bjet_score);
  this_Tree->Branch("bjet_charge",&bjet_charge);

  this_Tree->Branch("isDYbbar",&isDYbbar);
  this_Tree->Branch("isDYb",&isDYb);

  this_Tree->Branch("weight",&weight);
  
}

void bbbarAnalyzer::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;
  
}

bool bbbarAnalyzer::CheckIsDiMuonChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  //vector<int> v_muonidx=GetIdxDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  vector<Muon> v_muon=lepveto ?  GetDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2) :  GetDiMuRecoNoVeto(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  if( v_muon.size()<2) return 0;
  double mll=(v_muon[0]+v_muon[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;

  SetMuon(v_muon[0],v_muon[1]);

  return 1;
}  

void bbbarAnalyzer::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;
  
}


bool bbbarAnalyzer::CheckIsDiElectronChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  vector<Electron> v_electron=lepveto ? GetDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2) :GetDiElRecoNoVeto(TriggerSafeCut_electron1, TriggerSafeCut_electron2); 
  if( v_electron.size()<2) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  
  double mll=(v_electron[0]+v_electron[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;
  SetElectron(v_electron[0],v_electron[1]);
  return 1;
}  


void bbbarAnalyzer::SetEventWeight(){
  weight=1;
  if(IsDATA) return;

  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  
  if(IsDiMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsDiElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }


}

void bbbarAnalyzer::RunBasicZregion(){

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
  if(PuppiMET.Pt() > 75.) return;
  if(dphi_z_b < 1.6) return;
  if(vZ.Pt()<15.) return;
  if(ptzb>60.) return;


  bjetvar this_bjet=Get_bjetvar(v_bjet[0]);
  SetJetChargeScore(v_bjet[0]);


  ///---Let's look into leptons in bjet---//
  bool HasMuon=0;
  bool HasElectron=0;
  HasMuon=bbbarAnalyzer::FindMuonInBJet();
  if(HasMuon) return;
  HasElectron=bbbarAnalyzer::FindElectronInBJet();
  if(HasElectron) return;
  
  bjet_score=GetJetChargeScore();
  bjet_charge=v_bjet[0].Charge();
  if(fabs(GetJetChargeScoreCoeff()>0)){
    FillHistAll_bjet(LepCh+"__HighScoreJetChannel",this_bjet);	
    FillHistAll_bjet("ll__HighScoreJetChannel",this_bjet);
  }else{
    FillHistAll_bjet(LepCh+"__LowScoreJetChannel",this_bjet);	
    FillHistAll_bjet("ll__LowScoreJetChannel",this_bjet);

  }
  //jhchoi_newtree->Fill();
  
}//[end]RunBasic Zregion


bool bbbarAnalyzer::FindMuonInBJet(){
  bool _HasMuon=0;
  bool IsMuonMax=0;
  bool IsMuonMin=0;
  bmuon_score_max=-999.;
  bmuon_charge_max=0;

  bmuon_score_min=999.;
  bmuon_charge_min=0;

  Muon *MuonMax=NULL;
  Muon *MuonMin=NULL;

  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    if(muon.DeltaR(v_bjet[0]) > 0.4) continue;
    if(muon.RelIso() > 10.) continue;
    if(muon.Chi2()>10) continue;
    if(muon.TrackerLayers()<1) continue;
    if(muon.MatchedStations() <1) continue;


    SetMuonChargeScore(muon,v_bjet[0]);
    if( fabs(GetMuonChargeScoreCoeff()) < 0.5 ) continue;//if this muon doesn't pass the score cut
    double this_muonscore=GetMuonChargeScore();



    if(this_muonscore>bmuon_charge_max){
      //BestMuon_max=&muon;
      MuonMax=&muon;
      bmuon_score_max=this_muonscore;
      bmuon_charge_max=muon.Charge();
      _HasMuon=1;
      IsMuonMax=1;
    }
    if(this_muonscore < bmuon_score_min ){
      MuonMin=&muon;
      bmuon_score_min=this_muonscore;
      bmuon_charge_min=muon.Charge();
      _HasMuon=1;
      IsMuonMin=1;
    }


  }//[end muon for loop]
  if(!_HasMuon) return false;
  if(IsMuonMax){
    FillHist("ll__bMuonChannel/bmuon_measured_charge_crosscheck", bmuon_charge_max,weight,5,-3,2);
    SetMuonChargeScore(*MuonMax,v_bjet[0]);
    bmuonvar this_bmuonvar=Get_bmuonvar(*MuonMax,v_bjet[0]);
    FillHistAll_bmuon(LepCh+"__bMuonChannel",this_bmuonvar);
    FillHistAll_bmuon("ll__bMuonChannel",this_bmuonvar);



  }
  else{
    FillHist("ll__bMuonChannel/bmuon_measured_charge_crosscheck", -1*bmuon_charge_min,weight,5,-3,2);
    SetMuonChargeScore(*MuonMin,v_bjet[0]);
    bmuonvar this_bmuonvar=Get_bmuonvar(*MuonMin,v_bjet[0]);
    FillHistAll_bmuon(LepCh+"__bMuonChannel",this_bmuonvar);
    FillHistAll_bmuon("ll__bMuonChannel",this_bmuonvar);
  }

  return _HasMuon;
}

bool bbbarAnalyzer::FindElectronInBJet(){
  bool _HasElectron=0;
  bool IsElectronMax=0;
  bool IsElectronMin=0;

  belectron_score_max=-999.;
  belectron_charge_max=0;

  belectron_score_min=999.;
  belectron_charge_min=0;

  Electron *ElectronMax=NULL;
  Electron *ElectronMin=NULL;

  //Electron *BestElectron=NULL;
  for(auto& electron : AllElectrons){
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(electron.Pt() < 5.) continue;
    if(electron.DeltaR(v_bjet[0]) > 0.4) continue;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    if(electron.RelIso() > 10.) continue;
    if(electron.NMissingHits() != 0) continue;

    
    SetElectronChargeScore(electron,v_bjet[0]);
    if( fabs(GetElectronChargeScoreCoeff()) < 0.5 ) continue;
    double this_electronscore=GetElectronChargeScore();
    if(this_electronscore>belectron_score_max){
      ElectronMax=&electron;
      belectron_score_max=this_electronscore;
      belectron_charge_max=electron.Charge();
      _HasElectron=1;
      IsElectronMax=1;
    }
    if(this_electronscore<belectron_score_min){
      ElectronMin=&electron;
      belectron_score_min=this_electronscore;
      belectron_charge_min=electron.Charge();
      _HasElectron=1;
      IsElectronMin=1;

    }


  }//[end electron for loop]
  if(!_HasElectron) return false;
  if(IsElectronMax){
    FillHist("ll__bElectronChannel/belectron_measured_charge_crosscheck", belectron_charge_max,weight,5,-3,2);
    SetElectronChargeScore(*ElectronMax,v_bjet[0]);
    belectronvar this_belectronvar=Get_belectronvar(*ElectronMax,v_bjet[0]);
    FillHistAll_belectron(LepCh+"__bElectronChannel",this_belectronvar);
    FillHistAll_belectron("ll__bElectronChannel",this_belectronvar);



  }
  else{
    FillHist("ll__bElectronChannel/belectron_measured_charge_crosscheck", -1*belectron_charge_min,weight,5,-3,2);
    SetElectronChargeScore(*ElectronMin,v_bjet[0]);
    belectronvar this_belectronvar=Get_belectronvar(*ElectronMin,v_bjet[0]);
    FillHistAll_belectron(LepCh+"__bElectronChannel",this_belectronvar);
    FillHistAll_belectron("ll__bElectronChannel",this_belectronvar);
  }


  return _HasElectron;

}

void bbbarAnalyzer::FillHistAll_bmuon(TString cutname,bmuonvar this_bmuon){
  FillHist(cutname+"/bmuon_P_jetrest",this_bmuon.P_jetrest,weight,10,0,10);
  FillHist(cutname+"/bmuon_ptwrtjet",this_bmuon.ptwrtjet,weight,10,0,10);
  FillHist(cutname+"/bmuon_dR_l_j",this_bmuon.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/bmuon_nsip3d",this_bmuon.nsip3d,weight,30,0,15);
  FillHist(cutname+"/bmuon_reltrkiso",this_bmuon.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/bmuon_reliso",this_bmuon.reliso,weight,150,0,15);
  FillHist(cutname+"/bmuon_charge",this_bmuon.charge,weight,4,-2,2);
  FillHist(cutname+"/bmuon_chargescore",GetMuonChargeScore(),weight,70,-0.2,1.2);
  FillHist(cutname+"/bmuon_chargescore_coeff",GetMuonChargeScoreCoeff(),weight,5,-3,2);
  FillHist(cutname+"/bmuon_measured_charge",this_bmuon.charge*GetMuonChargeScoreCoeff(),weight,5,-3,2);

  FillHist(cutname+"/bmuon_palongjet",this_bmuon.palongjet,weight,100,0,30);
  FillHist(cutname+"/bmuon_palongjetratio",this_bmuon.palongjetratio,weight,100,0,2);
  FillHist(cutname+"/bmuon_bjet_charge_dot_bmuon_charge",this_bmuon.bjet_charge_dot_bmuon_charge,weight,100,-2,2);
  FillHist(cutname+"/bmuon_bjet_MuonEnergyFraction",v_bjet[0].GetMuonEnergyFraction(),weight,100,0,1);
  FillHist(cutname+"/bmuon_bjet_ChargedMultiplicity",v_bjet[0].ChargedMultiplicity(),weight,60,0,60);
  FillHist(cutname+"/bmuon_bjet_pt",v_bjet[0].Pt(),weight,100,0,100);
  FillHist(cutname+"/bmuon_bjet_aeta",fabs(v_bjet[0].Eta()),weight,60,-3,3);

  //bmuon_palongjetratio//bmuon_ptwrtbjet//bmuon_P_jetrest//bjet_charge*bmuon_charge//bjet_MuonEnergyFraction//bjet_ChargedMultiplicity//
  //bjet_pt//bjet_aeta//

}

void bbbarAnalyzer::FillHistAll_belectron(TString cutname,belectronvar this_belectron){
  FillHist(cutname+"/belectron_P_jetrest",this_belectron.P_jetrest,weight,10,0,10);
  FillHist(cutname+"/belectron_ptwrtjet",this_belectron.ptwrtjet,weight,10,0,10);
  FillHist(cutname+"/belectron_dR_l_j",this_belectron.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/belectron_nsip3d",this_belectron.nsip3d,weight,30,0,15);
  FillHist(cutname+"/belectron_reltrkiso",this_belectron.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/belectron_reliso",this_belectron.reliso,weight,150,0,15);
  FillHist(cutname+"/belectron_charge",this_belectron.charge,weight,4,-2,2);
  FillHist(cutname+"/belectron_IsGsfCtfScPixChargeConsistent",this_belectron.IsGsfCtfScPixChargeConsistent,weight,4,-2,2);

  FillHist(cutname+"/belectron_chargescore",GetElectronChargeScore(),weight,70,-0.2,1.2);
  FillHist(cutname+"/belectron_chargescore_coeff",GetElectronChargeScoreCoeff(),weight,5,-3,2);
  FillHist(cutname+"/belectron_measured_charge",this_belectron.charge*GetElectronChargeScoreCoeff(),weight,5,-3,2);

  FillHist(cutname+"/belectron_InvEminusInvP",this_belectron.InvEminusInvP,weight,50,0,0.3);
  FillHist(cutname+"/belectron_palongjet",this_belectron.palongjet,weight,100,0,30);
  FillHist(cutname+"/belectron_palongjetratio",this_belectron.palongjetratio,weight,100,0,2);
  FillHist(cutname+"/belectron_bjet_charge_dot_belectron_charge",this_belectron.bjet_charge_dot_belectron_charge,weight,100,-2,2);
  FillHist(cutname+"/belectron_bjet_MuonEnergyFraction",v_bjet[0].GetMuonEnergyFraction(),weight,100,0,1);
  FillHist(cutname+"/belectron_bjet_ChargedEmEnergyFraction",v_bjet[0].GetChargedEmEnergyFraction(),weight,100,0,1);
  FillHist(cutname+"/belectron_bjet_ChargedMultiplicity",v_bjet[0].ChargedMultiplicity(),weight,60,0,60);
  FillHist(cutname+"/belectron_bjet_pt",v_bjet[0].Pt(),weight,100,0,100);
  FillHist(cutname+"/belectron_bjet_aeta",fabs(v_bjet[0].Eta()),weight,60,-3,3);
}

void bbbarAnalyzer::FillHistAll_bjet(TString cutname,bjetvar this_bjet){
  FillHist(cutname+"/bjet_pt",this_bjet.pt,weight,100,0,100);
  FillHist(cutname+"/bjet_aeta",this_bjet.aeta,weight,60,0,3);
  FillHist(cutname+"/bjet_ChargedHadronEnergyFraction",this_bjet.ChargedHadronEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/bjet_NeutralHadronEnergyFraction",this_bjet.NeutralHadronEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/bjet_NeutralEmEnergyFraction",this_bjet.NeutralEmEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/bjet_ChargedEmEnergyFraction",this_bjet.ChargedEmEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/bjet_MuonEnergyFraction",this_bjet.MuonEnergyFraction,weight,100,0,1);

  FillHist(cutname+"/bjet_ChargedMultiplicity",this_bjet.ChargedMultiplicity,weight,60,0,60);
  FillHist(cutname+"/bjet_NeutralMultiplicity",this_bjet.NeutralMultiplicity,weight,60,0,60);
  
  FillHist(cutname+"/bjet_charge",this_bjet.charge,weight,50,-1,1);
  FillHist(cutname+"/bjet_abs_charge",this_bjet.abs_charge,weight,50,0,1);
  FillHist(cutname+"/bjet_int_charge",this_bjet.charge>0 ? 1 : -1 ,weight,4,-2,2);
  FillHist(cutname+"/bjet_partonFlavour",this_bjet.partonFlavour,weight,27,-6,21);

  FillHist(cutname+"/bjet_chargescore",GetJetChargeScore(),weight,70,-0.2,1.2);
  FillHist(cutname+"/bjet_chargescore_coeff",GetJetChargeScoreCoeff(),weight,5,-3,2);
  FillHist(cutname+"/bjet_measured_charge",this_bjet.charge*GetJetChargeScoreCoeff(),weight,120,-1.2,1.2);
  FillHist(cutname+"/bjet_measured_int_charge",this_bjet.charge*GetJetChargeScoreCoeff() > 0 ? 1 : -1,weight,4,-2,2);


}

void bbbarAnalyzer::FillHistAllChannel(TString cutname){
  if(check_tmva_input) return;
  bbbarAnalyzer::FillHistAll("ll__"+cutname);
  bbbarAnalyzer::FillHistAll(LepCh+"__"+cutname);
}


void bbbarAnalyzer::FillHistAll(TString cutname){

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
void bbbarAnalyzer::FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max){
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
void bbbarAnalyzer::EventLoop(){
  AnalyzerCore::FillHist("all/nmuons/"+ProcessName,AllMuons.size(),1,100,0.,100.);
  AnalyzerCore::FillHist("all/nelectrons/"+ProcessName,AllElectrons.size(),1,100,0.,100.);
  RunBasicZregion();
}  
  


void bbbarAnalyzer::TruthLoop(){
  isDYbbar=false;
  isDYb=false;




  if(!IsDYSample) return;
  
  unsigned int nb=0;
  unsigned int nbbar=0;
  int pid_b=0;
  unsigned int ntau=0;
  unsigned int lhesize=lhes.size();
  for(unsigned int i = 0 ; i < lhesize; i++){
    int status=lhes[i].Status();
    int pid=lhes[i].ID();
    if(status==-1) continue;
    if(abs(pid)==15){//tau
      ntau+=1;
    }
    if(pid==5){
      nb+=1;
      pid_b=5;
    }
    if(pid==-5){
      nbbar+=1;
      pid_b=-5;
    }

  }



  if(ntau==2){
    ProcessName="DY_tautau";
    return;
  }

  if(nb+nbbar==1){
    if(pid_b>0){ 
       ProcessName="DY_b";
       isDYb=true;
    }
    else{
      ProcessName="DY_bbar";
       isDYbbar=true;
    }
    return;
  }

  ProcessName="DY_others";


}


