#include "Preselection_To_bjet.h"
#include <map>

//Based on bbbarAsymMeasurement 241031
Preselection_To_bjet::Preselection_To_bjet(){

}

Preselection_To_bjet::~Preselection_To_bjet(){
  //==== Destructor of this Analyzer
}

void Preselection_To_bjet::initializeAnalyzer(){
  cout << "[Preselection_To_bjet::initializeAnalyzer]" << endl;

  if(HasFlag("use_beff")){
    //----use this analyzer specific btag mc eff----//
    //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("Preselection_To_bjet_"+MCSample+".root");
  }

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

  MuonOnly=false;
  if(HasFlag("MuonOnly")){
    MuonOnly=true;
    cout << "MuonOnly -> true" << endl;
  }  
  //charge
  TString v_muonScore="2409.2";
  TString v_electronScore="2409.2";
  TString v_jetScore="2409.2";



  bool apply_dnncut=1;





  LoadChargeScoreTool(v_muonScore,v_electronScore,v_jetScore,apply_dnncut);


  apply_bchargeeff=false;
  if(HasFlag("apply_bchargeeff")){
    if(!IsDATA){
      initializeBChargeEff("bbbarAsymMeasurement_"+MCSample+".root");
      apply_bchargeeff=true;
    }
  }
  




}


void Preselection_To_bjet::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;
  
}

bool Preselection_To_bjet::CheckIsDiMuonChannel(double min_mll,double max_mll){
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

void Preselection_To_bjet::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;
  
}


bool Preselection_To_bjet::CheckIsDiElectronChannel(double min_mll,double max_mll){
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


void Preselection_To_bjet::SetEventWeight(){
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

void Preselection_To_bjet::RunBasicZregion(){

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

  //---if this job is for btag mc eff measure, measure eff. before getjets
  if(measure_btageff){

    Measure_MCbtagEff();
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
  if(CurrentMET.Pt() > 75.) return;
  if(dphi_z_b < 1.6) return;
  if(vZ.Pt()<15.) return;
  if(ptzb>60.) return;



  //---Presl DONE---//
  if(apply_bchargeeff){
    ApplyBChargeIDSF();
  }


  if(bgenidx>-1){//if DYb || DYbbar
    //IsGENMatched_Flavour_dR(Jet& this_jet, int genidx)
    bool GENMatched=IsGENMatched_Flavour_dR(v_bjet[0],bgenidx);
    if(GENMatched){
      ProcessName=MCSample+gen_suffix+"_Matched";
    }
    else{
      ProcessName=MCSample+gen_suffix+"_UnMatched";
    }


  }//[END] if bgenidx>-1
  
  FillHist_bjet("ll");
  FillHist_bjet(LepCh);

  /*
  //---Check HasMuon
  //vector<int> JHAnalyzerBase::GetMuonIdxInBJet(Jet &_bjet, vector<Muon> &_muoncoll){
  vector<int> v_bmuonidx=GetMuonIdxInBJet(v_bjet[0],AllMuons);
  if(v_bmuonidx.size() > 0){//Has Muon in this bjet
    FillHist_bjet("ll__HasMuon");
    FillHist_bjet(LepCh+"__HasMuon");

  }



  vector<int> v_belectronidx=GetElectronIdxInBJet(v_bjet[0],AllElectrons);
  if(v_belectronidx.size() > 0){//Has Muon in this bjet
    FillHist_bjet("ll__HasElectron");
    FillHist_bjet(LepCh+"__HasElectron");

  }
  */







  //----SLT

  bool HasSLTMuon=RunSLTMuon();

  if(HasSLTMuon) return;
  if(MuonOnly) return;
  FillHist_bjet("ll__FailSLTMuon");
  FillHist_bjet(LepCh+"__FailSLTMuon");

  bool HasSLTElectron=RunSLTElectron();

  if(HasSLTElectron) return;


  FillHist_bjet("ll__FailSLTLepton");
  FillHist_bjet(LepCh+"__FailSLTLepton");

  RunBJet();
    

}



void Preselection_To_bjet::ApplyBChargeIDSF(){
  if(IsDATA) return;
  tuple<int,bool,int,int,double> bCand_Charge_info=GetBJetCharge_v2409_2(v_bjet[0],AllMuons,AllElectrons);

  int bCand_Charge=std::get<0>(bCand_Charge_info);
  bool bCand_NotUseOppositeCharge=std::get<1>(bCand_Charge_info);
  int bCand_im=std::get<2>(bCand_Charge_info);
  int bCand_ie=std::get<3>(bCand_Charge_info);
  double bCnad_ChargeScore=std::get<4>(bCand_Charge_info);

  int cat_id=0;

  //---bchargeID---//
  TString this_bchargeID="";
  if(fabs(bCand_Charge)==1){
    if(bCand_NotUseOppositeCharge){
      this_bchargeID="muH";
      cat_id=1;
    }
    else{
      this_bchargeID="muL";
      cat_id=2;
    }
  }
  else if(fabs(bCand_Charge)==2){
    if(bCand_NotUseOppositeCharge){
      this_bchargeID="eH";
      cat_id=3;
    }
    else{
      this_bchargeID="eL";
      cat_id=4;
    }
  }
  else if(fabs(bCand_Charge)==3){
    this_bchargeID="jG";
    cat_id=5;
  }
  else{
    this_bchargeID="jB";
    cat_id=6;
  }
  //---orig parton
  TString this_orig_parton=JHAnalyzerBase::Get_orig_parton_bChargeID(v_bjet[0]);
  
  if(apply_bchargeeff && !IsDATA){
    //---SF
    double SF_bChargeID=Get_bChargeID_SF(v_bjet[0].Pt(), this_bchargeID, this_orig_parton);
    weight*=SF_bChargeID;
  }
  
}

bool Preselection_To_bjet::RunSLTMuon(){
  //----Check HasSLTMuon
  tuple<int,double,double,int,double,double> ret=JHAnalyzerBase::GetBJetMuonScore_v2409_2(v_bjet[0], AllMuons);
  //{im_max,bmuon_score_max,bmuon_charge_max,im_min,bmuon_score_min,bmuon_charge_min
  int im_max=std::get<0>(ret);
  double bmuon_score_max=std::get<1>(ret);
  double bmuon_charge_max=std::get<2>(ret);
  int im_min=std::get<3>(ret);
  double bmuon_score_min=std::get<4>(ret);
  double bmuon_charge_min=std::get<5>(ret);
  if(bmuon_charge_max==0) return 0;  
  ///Has Muon w/o dnnscore cut
  FillHist_bjet("ll__HasSoftMuon");
  FillHist_bjet(LepCh+"__HasSoftMuon");
  FillHist_muonmax("ll__HasSoftMuon",im_max,bmuon_score_max);
  FillHist_muonmax(LepCh+"__HasSoftMuon",im_max,bmuon_score_max);
  FillHist_muonmin("ll__HasSoftMuon",im_min,bmuon_score_min);
  FillHist_muonmin(LepCh+"__HasSoftMuon",im_min,bmuon_score_min);


  if(bmuon_score_max > mChargeTool->mincut){
    FillHist_bjet("ll__HasSLTMuonHigh");
    FillHist_bjet(LepCh+"__HasSLTMuonHigh");
    FillHist_muonmax("ll__HasSLTMuonHigh",im_max,bmuon_score_max);
    FillHist_muonmax(LepCh+"__HasSLTMuonHigh",im_max,bmuon_score_max);
    FillHist_muonmin("ll__HasSLTMuonHigh",im_min,bmuon_score_min);
    FillHist_muonmin(LepCh+"__HasSLTMuonHigh",im_min,bmuon_score_min);
    return 1;
  }

  FillHist_bjet("ll__FailSLTMuonHigh");
  FillHist_bjet(LepCh+"__FailSLTMuonHigh");
  FillHist_muonmax("ll__FailSLTMuonHigh",im_max,bmuon_score_max);
  FillHist_muonmax(LepCh+"__FailSLTMuonHigh",im_max,bmuon_score_max);
  FillHist_muonmin("ll__FailSLTMuonHigh",im_min,bmuon_score_min);
  FillHist_muonmin(LepCh+"__FailSLTMuonHigh",im_min,bmuon_score_min);
  if(bmuon_score_min < mChargeTool->maxcut){
    FillHist_bjet("ll__HasSLTMuonLow");
    FillHist_bjet(LepCh+"__HasSLTMuonLow");
    FillHist_muonmax("ll__HasSLTMuonLow",im_max,bmuon_score_max);
    FillHist_muonmax(LepCh+"__HasSLTMuonLow",im_max,bmuon_score_max);
    FillHist_muonmin("ll__HasSLTMuonLow",im_min,bmuon_score_min);
    FillHist_muonmin(LepCh+"__HasSLTMuonLow",im_min,bmuon_score_min);
    return 1;
  }
  return 0;

}



bool Preselection_To_bjet::RunSLTElectron(){
  //----Check HasSLTElectron
  tuple<int,double,double,int,double,double> ret=JHAnalyzerBase::GetBJetElectronScore_v2409_2(v_bjet[0], AllElectrons);
  //{ie_max,belectron_score_max,belectron_charge_max,ie_min,belectron_score_min,belectron_charge_min
  int ie_max=std::get<0>(ret);
  double belectron_score_max=std::get<1>(ret);
  double belectron_charge_max=std::get<2>(ret);
  int ie_min=std::get<3>(ret);
  double belectron_score_min=std::get<4>(ret);
  double belectron_charge_min=std::get<5>(ret);
  if(belectron_charge_max==0) return 0;
  ///Has Electron w/o dnnscore cut
  FillHist_bjet("ll__HasSoftElectron");
  FillHist_bjet(LepCh+"__HasSoftElectron");
  FillHist_electronmax("ll__HasSoftElectron",ie_max,belectron_score_max);
  FillHist_electronmax(LepCh+"__HasSoftElectron",ie_max,belectron_score_max);
  FillHist_electronmin("ll__HasSoftElectron",ie_min,belectron_score_min);
  FillHist_electronmin(LepCh+"__HasSoftElectron",ie_min,belectron_score_min);


  if(belectron_score_max > eChargeTool->mincut){
    FillHist_bjet("ll__HasSLTElectronHigh");
    FillHist_bjet(LepCh+"__HasSLTElectronHigh");
    FillHist_electronmax("ll__HasSLTElectronHigh",ie_max,belectron_score_max);
    FillHist_electronmax(LepCh+"__HasSLTElectronHigh",ie_max,belectron_score_max);
    FillHist_electronmin("ll__HasSLTElectronHigh",ie_min,belectron_score_min);
    FillHist_electronmin(LepCh+"__HasSLTElectronHigh",ie_min,belectron_score_min);
    return 1;
  }

  FillHist_bjet("ll__FailSLTElectronHigh");
  FillHist_bjet(LepCh+"__FailSLTElectronHigh");
  FillHist_electronmax("ll__FailSLTElectronHigh",ie_max,belectron_score_max);
  FillHist_electronmax(LepCh+"__FailSLTElectronHigh",ie_max,belectron_score_max);
  FillHist_electronmin("ll__FailSLTElectronHigh",ie_min,belectron_score_min);
  FillHist_electronmin(LepCh+"__FailSLTElectronHigh",ie_min,belectron_score_min);

  if(belectron_score_min < eChargeTool->maxcut){
    FillHist_bjet("ll__HasSLTElectronLow");
    FillHist_bjet(LepCh+"__HasSLTElectronLow");
    FillHist_electronmax("ll__HasSLTElectronLow",ie_max,belectron_score_max);
    FillHist_electronmax(LepCh+"__HasSLTElectronLow",ie_max,belectron_score_max);
    FillHist_electronmin("ll__HasSLTElectronLow",ie_min,belectron_score_min);
    FillHist_electronmin(LepCh+"__HasSLTElectronLow",ie_min,belectron_score_min);
    return 1;
  }
  return 0;

}


void Preselection_To_bjet::RunBJet(){
  SetJetChargeScore(v_bjet[0]);
  double bjet_score=GetJetChargeScore();
  int bjet_charge=v_bjet[0].Charge() > 0 ? +1 : -1;

  if(bjet_score>jChargeTool->mincut){
    FillHist_bjet("ll__GoodBJet");
    FillHist("ll__GoodBJet/bjet_score", bjet_score,weight,100,0,1);
    FillHist_bjet(LepCh+"__GoodBJet");    
    FillHist(LepCh+"__GoodBJet/bjet_score", bjet_score,weight,100,0,1);
  }
  else{
    FillHist_bjet("ll__BadBJet");
    FillHist("ll__BadBJet/bjet_score", bjet_score,weight,100,0,1);
    FillHist_bjet(LepCh+"__BadBJet");    
    FillHist(LepCh+"__BadBJet/bjet_score", bjet_score,weight,100,0,1);
  }
      

}
  



void Preselection_To_bjet::FillHist_bjet(TString cutname){
  //bgenidx
  FillHist(cutname+"/bjet_pt",v_bjet[0].Pt(), weight, 100,0,200);
  if(bgenidx>-1) FillHist(cutname+"/true_bjet_pt",gens[bgenidx].Pt(), weight, 100,0,200);
  FillHist(cutname+"/bjet_eta",v_bjet[0].Eta(), weight, 50,-3,3);
  FillHist_Z(cutname);
}

void Preselection_To_bjet::FillHist_Z(TString cutname){
  //FillHist(cutname+"/Z_pt",vZ.Pt(), weight, 100,0,200);
  //FillHist(cutname+"/met_pt",CurrentMET.Pt(), weight, 100,0,200);
  //FillHist(cutname+"/met_phi",CurrentMET.Phi(), weight, 80,-4,4);
  //FillHist(cutname+"/Z_eta",vZ.Eta(), weight, 50,-3,3);
  FillHist(cutname+"/Z_M",vZ.M(), weight, 60,60,120);
}

void Preselection_To_bjet::FillHist_muonmax(TString cutname, int im, double score){
  FillHist(cutname+"/muonmax_pt",AllMuons[im].Pt(), weight, 100,0,100);
  //FillHist(cutname+"/muonmax_p",AllMuons[im].P(), weight, 100,0,100);
  FillHist(cutname+"/muonmax_eta",AllMuons[im].Eta(), weight, 50,-3,3);

  double ptAtJetRest=JHAnalyzerBase::GetP_JetRestFrame(AllMuons[im],v_bjet[0]);
  double ptwrtjet=JHAnalyzerBase::GetPt_wrt_Jet(AllMuons[im],v_bjet[0]);
  //FillHist(cutname+"/muonmax_ptwrtjet", ptwrtjet,weight,100,0,100);
  FillHist(cutname+"/muonmax_ptwrtjet_zoom", ptwrtjet,weight,100,0,10);
  //FillHist(cutname+"/muonmax_ptAtJetRest", ptAtJetRest,weight,100,0,100);
  FillHist(cutname+"/muonmax_ptAtJetRest_zoom", ptAtJetRest,weight,100,0,10);
  FillHist(cutname+"/muonmax_score", score,weight,100,0,1);


}

void Preselection_To_bjet::FillHist_muonmin(TString cutname, int im, double score){
  FillHist(cutname+"/muonmin_pt",AllMuons[im].Pt(), weight, 100,0,100);
  //FillHist(cutname+"/muonmin_p",AllMuons[im].P(), weight, 100,0,100);
  FillHist(cutname+"/muonmin_eta",AllMuons[im].Eta(), weight, 50,-3,3);

  double ptAtJetRest=JHAnalyzerBase::GetP_JetRestFrame(AllMuons[im],v_bjet[0]);
  double ptwrtjet=JHAnalyzerBase::GetPt_wrt_Jet(AllMuons[im],v_bjet[0]);
  //FillHist(cutname+"/muonmin_ptwrtjet", ptwrtjet,weight,100,0,100);
  FillHist(cutname+"/muonmin_ptwrtjet_zoom", ptwrtjet,weight,100,0,10);
  //FillHist(cutname+"/muonmin_ptAtJetRest", ptAtJetRest,weight,100,0,100);
  FillHist(cutname+"/muonmin_ptAtJetRest_zoom", ptAtJetRest,weight,100,0,10);
  FillHist(cutname+"/muonmin_score", score,weight,100,0,1);

}


void Preselection_To_bjet::FillHist_electronmax(TString cutname, int ie, double score){
  FillHist(cutname+"/electronmax_pt",AllElectrons[ie].Pt(), weight, 100,0,100);
  //FillHist(cutname+"/electronmax_p",AllElectrons[ie].Pt(), weight, 100,0,100);
  FillHist(cutname+"/electronmax_eta",AllElectrons[ie].Eta(), weight, 50,-3,3);

  double ptAtJetRest=JHAnalyzerBase::GetP_JetRestFrame(AllElectrons[ie],v_bjet[0]);
  double ptwrtjet=JHAnalyzerBase::GetPt_wrt_Jet(AllElectrons[ie],v_bjet[0]);
  //FillHist(cutname+"/electronmax_ptwrtjet", ptwrtjet,weight,100,0,100);
  //FillHist(cutname+"/electronmax_ptAtJetRest", ptAtJetRest,weight,100,0,100);

  FillHist(cutname+"/electronmax_ptwrtjet_zoom", ptwrtjet,weight,100,0,10);
  FillHist(cutname+"/electronmax_ptAtJetRest_zoom", ptAtJetRest,weight,100,0,10);

  FillHist(cutname+"/electronmax_score", score,weight,100,0,1);


}

void Preselection_To_bjet::FillHist_electronmin(TString cutname, int ie, double score){
  FillHist(cutname+"/electronmin_pt",AllElectrons[ie].Pt(), weight, 100,0,100);
  //FillHist(cutname+"/electronmin_p",AllElectrons[ie].Pt(), weight, 100,0,100);
  FillHist(cutname+"/electronmin_eta",AllElectrons[ie].Eta(), weight, 50,-3,3);

  double ptAtJetRest=JHAnalyzerBase::GetP_JetRestFrame(AllElectrons[ie],v_bjet[0]);
  double ptwrtjet=JHAnalyzerBase::GetPt_wrt_Jet(AllElectrons[ie],v_bjet[0]);
  //FillHist(cutname+"/electronmin_ptwrtjet", ptwrtjet,weight,100,0,100);
  //FillHist(cutname+"/electronmin_ptAtJetRest", ptAtJetRest,weight,100,0,100);

  FillHist(cutname+"/electronmin_ptwrtjet_zoom", ptwrtjet,weight,100,0,10);
  FillHist(cutname+"/electronmin_ptAtJetRest_zoom", ptAtJetRest,weight,100,0,10);
  FillHist(cutname+"/electronmin_score", score,weight,100,0,1);

}


void Preselection_To_bjet::EventLoop(){
  RunBasicZregion();
}  
  


void Preselection_To_bjet::TruthLoop(){
  bgenidx=-1;
  isDYbbar=false;
  isDYb=false;

  gen_suffix="";


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
    ProcessName=MCSample+"_tautau";
    gen_suffix="_tautau";
    return;
  }

  if(nb+nbbar==1){
    if(pid_b>0){ 
      ProcessName=MCSample+"_b";
      gen_suffix="_b";
      isDYb=true;
    }
    else{
      ProcessName=MCSample+"_bbar";
      gen_suffix="_bbar";
      isDYbbar=true;
    }
   
  }//only 1b
  else{
    ProcessName=MCSample+"_others";
    gen_suffix="_others";
    return; //only 1b
  }




  //--genlevel
  bgenidx=-1;
  unsigned int gensize=gens.size();
  for(unsigned int i = 0 ; i < gensize ; i++){
    int pid=gens[i].PID();
    int status=gens[i].Status();
    //int mother=gens[i].MotherIndex();
    int isHardProcess=gens[i].isHardProcess();

    /// Outgoing HardProcess parton
    
    if (isHardProcess && (status!=21)){//status21===incoming quark

      if(pid==pid_b){
        bgenidx=i;
      }

    }

    
  }//[END]gen loop
  
  
  

}


