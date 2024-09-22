#include "TTsemiLepChargeScoreEfficiencyMeasurement.h"

TTsemiLepChargeScoreEfficiencyMeasurement::TTsemiLepChargeScoreEfficiencyMeasurement(){
  //runSys=true;
}

TTsemiLepChargeScoreEfficiencyMeasurement::~TTsemiLepChargeScoreEfficiencyMeasurement(){
  //==== Destructor of this Analyzer
}

void TTsemiLepChargeScoreEfficiencyMeasurement::initializeAnalyzer(){
  cout << "[TTsemiLepChargeScoreEfficiencyMeasurement::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupSingleLeptonChannel();
  noveto=false;
  if(HasFlag("noveto")){
    noveto=true;
  }
  HcbCR=false;
  if(HasFlag("HcbCR")){
    HcbCR=true;
  }

  FlavourMatchBase=false;
  if(HasFlag("FlavourMatchBase")){
    FlavourMatchBase=true;
  }

  LeptonPt50=false;
  if(HasFlag("LeptonPt50")){
    LeptonPt50=true;
  }

  njet4=false;
  if(HasFlag("njet4")){
    njet4=true;
  }

  //LoadTTSemilepJetAssignmentTool("1.0");
  //charge
  TString v_muonScore="2405.4.3";
  TString v_electronScore="2405.4.3";
  TString v_jetScore="2405.4.3";
  bool apply_dnncut=true;
  LoadChargeScoreTool(v_muonScore,v_electronScore,v_jetScore,apply_dnncut);

  ForBinning=false;
  if(HasFlag("ForBinning")){
    ForBinning=true;
  }


  ///------MuonChargeOnly
  //MuonChargeOnly=false;
  //if(HasFlag("MuonChargeOnly")){
  //  MuonChargeOnly=true;
  //}

}


void TTsemiLepChargeScoreEfficiencyMeasurement::SetMuon(const Muon& _l1){
  mu1=_l1;
}

bool TTsemiLepChargeScoreEfficiencyMeasurement::CheckIsMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;

  vector<Muon> v_muon;
  if(LeptonPt50){
    v_muon=noveto ? GetSingleMuRecoNoVeto(50.) : GetSingleMuReco(50.);
  }
  else{
    v_muon=noveto ? GetSingleMuRecoNoVeto(TriggerSafeCut_muon1) : GetSingleMuReco(TriggerSafeCut_muon1);
  }
  if( v_muon.size()!=1) return 0;
  SetMuon(v_muon[0]);

  return 1;
}  

void TTsemiLepChargeScoreEfficiencyMeasurement::SetElectron(const Electron& _l1){
  el1=_l1;
}


bool TTsemiLepChargeScoreEfficiencyMeasurement::CheckIsElectronChannel(){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  vector<Electron> v_electron;
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  if(LeptonPt50){
    v_electron=noveto ? GetSingleElRecoNoVeto(50.) : GetSingleElReco(50.);
  }
  else{
    v_electron=noveto ? GetSingleElRecoNoVeto(TriggerSafeCut_electron1) : GetSingleElReco(TriggerSafeCut_electron1);
  }
  if( v_electron.size()!=1) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  SetElectron(v_electron[0]);
  return 1;
}  

void TTsemiLepChargeScoreEfficiencyMeasurement::SetEventWeight(){
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

void TTsemiLepChargeScoreEfficiencyMeasurement::RunReco(){

  IsMuonChannel=false;
  IsElectronChannel=false;


  IsMuonChannel=CheckIsMuonChannel();
  if(!IsMuonChannel) IsElectronChannel=CheckIsElectronChannel();





  LepCh="";
  if(IsMuonChannel){
    vtW=GetTransverseVector(mu1)+PuppiMET;
    LepCh="Muon";
    l1=mu1;
  }
  else if(IsElectronChannel){
    vtW=GetTransverseVector(el1)+PuppiMET;
    LepCh="Electron";
    l1=el1;
  }  

  else{
    return;
  }
  //----Jet---//
  v_tightlep={l1};
  v_tightjet=GetTightJet(v_tightlep,30,2.4);
  v_bjetidx=GetBJetIdx(v_tightjet);
  nbjet=v_bjetidx.size();
  if(nbjet != 2) return;
  njet=v_tightjet.size();
  if(v_tightjet.size()<4) return;
  if(njet4 && v_tightjet.size()!=4) return;
  //--Now Objects are ready--//
  SetEventWeight();





  //FillHistAll(LepCh+"_beforeFit");
  //FillHistAll("AllLep_beforeFit");

  //return;
  Run();

}
void TTsemiLepChargeScoreEfficiencyMeasurement::Run(){
  iblep=-1;
  ibhad=-1;
  iq1=-1;
  iq2=-1;
  vz_fit=0.0;
  ////Minimal Chi2 Method - kin fitter
  pair<vector<int>,double> v_jetidxset_and_vz_chi2=GetJetIndexSet_Chi2(l1, PuppiMET, v_tightjet, v_bjetidx, HcbCR);

  //vector<int> v_jetidxset_dnn=GetJetIndexSet_DNN();
  //[0]=ib1 = bLep cand's v_bjet index
  //[1]=ib2 = bHad cand's v_bjet index
  //[2]=iq1 = one of light quark candiate v_tightjet index
  //[3]=iq2 = one of light quark candiate v_tightjet index
  iblep=v_jetidxset_and_vz_chi2.first[0];
  ibhad=v_jetidxset_and_vz_chi2.first[1];
  iq1=v_jetidxset_and_vz_chi2.first[2];
  iq2=v_jetidxset_and_vz_chi2.first[3];
  vz_fit=v_jetidxset_and_vz_chi2.second;

  
  if(iblep<0) return;
  if(ibhad<0) return;
  if(iq1<0) return;
  if(iq2<0) return;

  neutrino_cand.SetPxPyPzE(PuppiMET.Px(),PuppiMET.Py(),vz_fit, sqrt(pow(PuppiMET.Pt(),2) + pow(vz_fit,2) ));
  


  
  RunPlots();
}

void TTsemiLepChargeScoreEfficiencyMeasurement::RunPlots(){
  
  if(!IsDATA && FlavourMatchBase){
    bool isbLepFromb= abs(v_tightjet[iblep].hadronFlavour())==5;
    bool isbHadFromb= abs(v_tightjet[ibhad].hadronFlavour())==5;

    if(isbLepFromb&&isbHadFromb){
      ProcessName=MCSample+"_All_bjetFromb";
    }
    else if(isbHadFromb){
      ProcessName=MCSample+"_bHadCandFromb";
    }
    else if(isbLepFromb){
      ProcessName=MCSample+"_bLepCandFromb";
    }
    else{
      ProcessName=MCSample+"_NonFromb";
    }
  }

  else if(IsTTLJSample){
    bool isbLepMatched=0;
    bool isbHadMatched=0;
    /*
    //---bLep flavour match
    int bLep_FlavourMatched= v_tightjet[iblep].partonFlavour()==bLep_True_PID;
    int bLep_FlavourMatched_Opposite= v_tightjet[iblep].partonFlavour()==-bLep_True_PID;
    int bLep_dRMatched = v_tightjet[iblep].DeltaR(gens[bLep_True_genidx]) < 0.4;
    
    
    //---bHad flavour match
    int bHad_FlavourMatched= v_tightjet[ibhad].partonFlavour()==bHad_True_PID;
    int bHad_FlavourMatched_Opposite= v_tightjet[ibhad].partonFlavour()==-bHad_True_PID;
    int bHad_dRMatched = v_tightjet[ibhad].DeltaR(gens[bHad_True_genidx]) < 0.4;
    
    //--Whad, light quarks
    int q11_FlavourMatched=v_tightjet[iq1].partonFlavour()==Whad_q1_pid;
    int q22_FlavourMatched=v_tightjet[iq2].partonFlavour()==Whad_q2_pid;
    int q12_FlavourMatched=v_tightjet[iq1].partonFlavour()==Whad_q2_pid;
    int q21_FlavourMatched=v_tightjet[iq2].partonFlavour()==Whad_q1_pid;



    int q11_dRMatched=v_tightjet[iq1].DeltaR(gens[v_idx_lightquark_GEN[0]]) < 0.4;
    int q22_dRMatched=v_tightjet[iq2].DeltaR(gens[v_idx_lightquark_GEN[1]]) < 0.4;
    
    int q12_dRMatched=v_tightjet[iq1].DeltaR(gens[v_idx_lightquark_GEN[1]]) < 0.4;
    int q21_dRMatched=v_tightjet[iq2].DeltaR(gens[v_idx_lightquark_GEN[0]]) < 0.4;
    

    int qq_FlavourMatched= 0;
    if(q11_FlavourMatched && q22_FlavourMatched) qq_FlavourMatched=1;
    if(q21_FlavourMatched && q12_FlavourMatched) qq_FlavourMatched=1;
    
    int qq_Flavour_AND_dRMatched= 0;
    if(q11_FlavourMatched&&q11_dRMatched && q22_FlavourMatched&&q22_dRMatched) qq_Flavour_AND_dRMatched=1;
    if(q12_FlavourMatched&&q12_dRMatched && q21_FlavourMatched&&q21_dRMatched) qq_Flavour_AND_dRMatched=1;
    */
    //bool isbLepFlavourMatched= v_tightjet[iblep].partonFlavour()==bLep_True_PID;
    bool isbLepFlavourMatched= v_tightjet[iblep].hadronFlavour()==5;
    bool isbLepDeltaRMatched= v_tightjet[iblep].DeltaR(gens[bLep_True_genidx]) < 0.4;
    isbLepMatched=isbLepFlavourMatched&&isbLepDeltaRMatched;

    //bool isbHadFlavourMatched= v_tightjet[ibhad].partonFlavour()==bHad_True_PID;
    bool isbHadFlavourMatched= v_tightjet[ibhad].hadronFlavour()==5;
    bool isbHadDeltaRMatched= v_tightjet[ibhad].DeltaR(gens[bHad_True_genidx]) < 0.4;
    isbHadMatched=isbHadFlavourMatched&&isbHadDeltaRMatched;

    if(isbLepMatched && isbHadMatched){
      ProcessName=MCSample+"_AllMatched";
    }
    else if(isbLepMatched){
      ProcessName=MCSample+"_bLepMatchedOnly";
    }
    else if(isbHadMatched){
      ProcessName=MCSample+"_bHadMatchedOnly";
    }
    else{
      ProcessName=MCSample+"_Unmatched";
    }

  }//[END of TTLJ]

  SetTopAndW();
  



  //bLep infos
  FillHist_bjetinfo(LepCh+"_TTLJ",iblep,"bLep");
  return;  
  FillHist_bjetinfo("AllLep_TTLJ",iblep,"bLep");

 //bHad infos
  FillHist_bjetinfo(LepCh+"_TTLJ",ibhad,"bHad");
  FillHist_bjetinfo("AllLep_TTLJ",ibhad,"bHad");

  if(ForBinning)    return;
  if(runSys) return;
  //TTLJ infos
  FillHistTTLJ(LepCh+"_TTLJ");
  FillHistTTLJ("AllLep_TTLJ");



}
void TTsemiLepChargeScoreEfficiencyMeasurement::SetTopAndW(){

  Wlep_cand=l1+neutrino_cand;
  Whad_cand=v_tightjet[iq1]+v_tightjet[iq2];
  Tlep_cand=Wlep_cand+v_tightjet[iblep];
  Thad_cand=Whad_cand+v_tightjet[ibhad];
}
bool TTsemiLepChargeScoreEfficiencyMeasurement::HasMatchedRecoJet(int genidx,double dRcut){
  TLorentzVector this_genptl=gens[genidx];
  for(auto &jet : v_tightjet){
    if(this_genptl.DeltaR(jet) < dRcut) return 1;
  }
  return 0;
}


bool TTsemiLepChargeScoreEfficiencyMeasurement::HasFlavourMatchedRecoJet(int genidx){
  //TLorentzVector this_genptl=gens[genidx];
  int true_pid=gens[genidx].PID();
  for(auto &jet : v_tightjet){
    if(jet.partonFlavour() == true_pid) return 1;
  }
  return 0;
}




void TTsemiLepChargeScoreEfficiencyMeasurement::FillHistTTLJ(TString cutname){



  //---Top and W
  FillHist(cutname+"/Wlep_cand_pt",Wlep_cand.Pt(),weight,100,0,300);
  FillHist(cutname+"/Wlep_cand_eta",Wlep_cand.Eta(),weight,100,-5,5);
  FillHist(cutname+"/Wlep_cand_M",Wlep_cand.M(),weight,100,30,130);

  FillHist(cutname+"/Whad_cand_pt",Whad_cand.Pt(),weight,100,0,300);
  FillHist(cutname+"/Whad_cand_eta",Whad_cand.Eta(),weight,100,-5,5);
  FillHist(cutname+"/Whad_cand_M",Whad_cand.M(),weight,100,30,130);

  FillHist(cutname+"/Tlep_cand_pt",Tlep_cand.Pt(),weight,100,0,200);
  FillHist(cutname+"/Tlep_cand_eta",Tlep_cand.Eta(),weight,100,-5,5);
  FillHist(cutname+"/Tlep_cand_M",Tlep_cand.M(),weight,120,50,290);

  FillHist(cutname+"/Thad_cand_pt",Thad_cand.Pt(),weight,100,0,300);
  FillHist(cutname+"/Thad_cand_eta",Thad_cand.Eta(),weight,100,-5,5);
  FillHist(cutname+"/Thad_cand_M",Thad_cand.M(),weight,120,50,290);

  //---Decay products
  FillHist(cutname+"/neutrino_cand_pt",neutrino_cand.Pt(),weight,100,0,300);
  FillHist(cutname+"/neutrino_cand_eta",neutrino_cand.Eta(),weight,100,-5,5);
  FillHist(cutname+"/neutrino_cand_phi",neutrino_cand.Phi(),weight,100,-4,4);

  FillHist(cutname+"/q1_cand_pt",v_tightjet[iq1].Pt(),weight,100,0,300);
  FillHist(cutname+"/q1_cand_eta",v_tightjet[iq1].Eta(),weight,100,-5,5);
  FillHist(cutname+"/q1_cand_phi",v_tightjet[iq1].Phi(),weight,100,-4,4);

  FillHist(cutname+"/q2_cand_pt",v_tightjet[iq2].Pt(),weight,100,0,300);
  FillHist(cutname+"/q2_cand_eta",v_tightjet[iq2].Eta(),weight,100,-5,5);
  FillHist(cutname+"/q2_cand_phi",v_tightjet[iq2].Phi(),weight,100,-4,4);


  //v_tightjet[iblep],l1,
  double M_blep_l = (l1+v_tightjet[iblep]).M();
  FillHist(cutname+"/M_blep_l",M_blep_l,weight,100,0,400);
  double abs_dphi_Tlep_Thad=fabs(Tlep_cand.DeltaPhi(Thad_cand));
  FillHist(cutname+"/abs_dphi_Tlep_Thad",abs_dphi_Tlep_Thad,weight,100,0,4);

  FillHistAll(cutname);


}
void TTsemiLepChargeScoreEfficiencyMeasurement::FillHist_bjetinfo(TString cutname, int i_bjet, TString Name_bCand){
  //Charge of bjets
  //---Get Charge of bjets
  //pair<int,bool> JHAnalyzerBase::GetBJetCharge_v2405_4_3(Jet &_bjet, vector<Muon> &_muoncoll, vector<Electron> &electroncoll){
  //bLepCand_Charge_info=GetBJetCharge_v2405_4_3(v_tightjet[iblep],AllMuons,AllElectrons);
  //bHadCand_Charge_info=GetBJetCharge_v2405_4_3(v_tightjet[ibhad],AllMuons,AllElectrons);

  //Get bjet charges
  tuple<int,bool,int,int,double> bCand_Charge_info=GetBJetCharge_v2405_4_3(v_tightjet[i_bjet],AllMuons,AllElectrons);

  bCand_Charge=std::get<0>(bCand_Charge_info);
  bCand_NotUseOppositeCharge=std::get<1>(bCand_Charge_info);
  bCand_im=std::get<2>(bCand_Charge_info);
  bCand_ie=std::get<3>(bCand_Charge_info);
  bCnad_ChargeScore=std::get<4>(bCand_Charge_info);

  //bjetvar
  current_bjetname=Name_bCand;
  current_bjetvar=Get_bjetvar(v_tightjet[i_bjet]);
  //init bmuonvar 
  //current_bmuonvar=bmuonvar_init;
  //current_bmuonvar=Get_bmuonvar(AllMuons[bCand_im],v_tightjet[i_bjet]);
  //belectronvar
  //current_belectronvar=Get_belectronvar(AllElectrons[bCand_ie],v_tightjet[i_bjet]);

  
  FillHist(cutname+"/"+Name_bCand+"_Charge",bCand_Charge,weight,12,-6,6);
  if(bCand_NotUseOppositeCharge){//Not Opposite
    FillHist(cutname+"/"+Name_bCand+"_Charge_NotOpposite",bCand_Charge,weight,12,-6,6);
  }
  else{
    FillHist(cutname+"/"+Name_bCand+"_Charge_UseOpposite",bCand_Charge,weight,12,-6,6);
  }
  FillHist_bCand(cutname+"__"+Name_bCand);
  ///-----bjet's kin. by each bjetcharge----//
  //----bLep
  //(1)using softmuon
  if(abs(bCand_Charge)==1){//
    //read bmuonvar
    current_bmuonvar=Get_bmuonvar(AllMuons[bCand_im],v_tightjet[i_bjet]);
    FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftMuonCharge");
    FillHist_bCand_bmuon(cutname+"__"+Name_bCand+"UsingSoftMuonCharge");
    if(bCand_NotUseOppositeCharge){
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingSoftMuonChargeNotOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftMuonChargeNotOpposite");
      FillHist_bCand_bmuon(cutname+"__"+Name_bCand+"UsingSoftMuonChargeNotOpposite");
    }
    else{
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingSoftMuonChargeUseOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftMuonChargeUseOpposite");
      FillHist_bCand_bmuon(cutname+"__"+Name_bCand+"UsingSoftMuonChargeUseOpposite");

    }
  }
  else if(abs(bCand_Charge)==2){//using softelectron charge
    
    //read  belectronvar
    current_belectronvar=Get_belectronvar(AllElectrons[bCand_ie],v_tightjet[i_bjet]);
    //denominator
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon");
    //if(MuonChargeOnly) return;
    //(2)using softelectron
    FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftElectronCharge");
    FillHist_bCand_belectron(cutname+"__"+Name_bCand+"UsingSoftElectronCharge");
    if(bCand_NotUseOppositeCharge){
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingSoftElectronChargeNotOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftElectronChargeNotOpposite");
      FillHist_bCand_belectron(cutname+"__"+Name_bCand+"UsingSoftElectronChargeNotOpposite");
    }
    else{
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingSoftElectronChargeUseOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftElectronChargeUseOpposite");
      FillHist_bCand_belectron(cutname+"__"+Name_bCand+"UsingSoftElectronChargeUseOpposite");
    }
  }
    
    

  else if(abs(bCand_Charge)==3){//
    //denominators
    
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon");
    //if(MuonChargeOnly) return;
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon__FailSoftElectron");

    //(3)using goodjetcharge
    FillHist_bCand(cutname+"__"+Name_bCand+"UsingGoodJetCharge");
    if(bCand_NotUseOppositeCharge){
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingGoodJetChargeNotOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingGoodJetChargeNotOpposite");
    }
    else{
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingGoodJetChargeUseOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingGoodJetChargeUseOpposite");
    }
  }//(4)using poorjetcharge
  else{
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon");    
    //if(MuonChargeOnly) return;
    //FillHistTTLJ(cutname+"__"+Name_bCand+"_FailSoftMuon__FailSoftElectron__FailGoodBJet");
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon__FailSoftElectron");
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon__FailSoftElectron__FailGoodBJet");
  }
  
  

}

void TTsemiLepChargeScoreEfficiencyMeasurement::FillHist_bCand(TString cutname){
  //FillHist(cutname+"/"+bCandName+"_pt",v_tightjet[ibCand].Pt(),weight,100,0,300);
  //FillHist(cutname+"/"+bCandName+"_eta",v_tightjet[ibCand].Eta(),weight,100,-5,5);
  //FillHist(cutname+"/"+bCandName+"_phi",v_tightjet[ibCand].Phi(),weight,100,-4,4);


  if(ForBinning){
    if(current_bjetvar.pt < 40.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt30_40",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 50.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt40_50",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 60.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt50_60",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 70.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt60_70",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 80.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt70_80",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 90.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt80_90",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 100.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt90_100",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 110.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt100_110",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 120.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt110_120",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 130.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt120_130",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 140.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt130_140",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 150.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt140_150",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 160.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt150_160",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 170.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt160_170",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 180.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt170_180",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 190.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt180_190",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 200.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt190_200",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 210.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt200_210",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 220.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt210_220",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 230.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt220_230",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 240.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt230_240",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 250.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt240_250",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 260.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt250_260",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 270.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt260_270",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 280.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt270_280",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 290.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt280_290",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 300.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt290_300",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 400.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt300_400",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 500.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt400_500",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 600.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt500_600",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 700.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt600_700",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 800.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt700_800",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 900.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt800_900",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 1000.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt900_1000",current_bjetvar.eta,weight,30,-3,3);
    }



    return;

  }

  ///--DNN inputs
  //bjetvar this_bjetvar=Get_bjetvar(v_tightjet[ibCand]);
  FillHist(cutname+"/"+current_bjetname+"_pt",current_bjetvar.pt,weight,300,0,300);
  FillHist(cutname+"/"+current_bjetname+"_aeta",current_bjetvar.aeta,weight,60,0,3);
  FillHist(cutname+"/"+current_bjetname+"_eta",current_bjetvar.eta,weight,120,-3,3);
  if(runSys) return;
  FillHist(cutname+"/"+current_bjetname+"_ChargedHadronEnergyFraction",current_bjetvar.ChargedHadronEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/"+current_bjetname+"_NeutralHadronEnergyFraction",current_bjetvar.NeutralHadronEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/"+current_bjetname+"_NeutralEmEnergyFraction",current_bjetvar.NeutralEmEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/"+current_bjetname+"_ChargedEmEnergyFraction",current_bjetvar.ChargedEmEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/"+current_bjetname+"_MuonEnergyFraction",current_bjetvar.MuonEnergyFraction,weight,100,0,1);

  FillHist(cutname+"/"+current_bjetname+"_ChargedMultiplicity",current_bjetvar.ChargedMultiplicity,weight,60,0,60);
  FillHist(cutname+"/"+current_bjetname+"_NeutralMultiplicity",current_bjetvar.NeutralMultiplicity,weight,60,0,60);

  FillHist(cutname+"/"+current_bjetname+"_charge",current_bjetvar.charge,weight,50,-1,1);
  FillHist(cutname+"/"+current_bjetname+"_abs_charge",current_bjetvar.abs_charge,weight,50,0,1);
  FillHist(cutname+"/"+current_bjetname+"_int_charge",current_bjetvar.charge>0 ? 1 : -1 ,weight,4,-2,2);
  FillHist(cutname+"/"+current_bjetname+"_partonFlavour",current_bjetvar.partonFlavour,weight,27,-6,21);
  FillHist(cutname+"/"+current_bjetname+"_hadronFlavour",current_bjetvar.hadronFlavour,weight,6,0,6);

  FillHist(cutname+"/"+current_bjetname+"_ChargeScore",bCnad_ChargeScore,weight,100,0,1);

  FillHistTTLJ(cutname);


}
void TTsemiLepChargeScoreEfficiencyMeasurement::FillHist_bCand_bmuon(TString cutname){  

  if(runSys) return;
  if(ForBinning) return;
  //if the bjet has good softbmuon
  
  //bmuonvar this_bmuonvar=Get_bmuonvar(*MuonMax,v_bjet[0]);
  
  FillHist(cutname+"/"+current_bjetname+"_bmuon_P_jetrest",current_bmuonvar.P_jetrest,weight,10,0,10);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_ptwrtjet",current_bmuonvar.ptwrtjet,weight,10,0,10);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_dR_l_j",current_bmuonvar.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_nsip3d",current_bmuonvar.nsip3d,weight,30,0,15);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_reltrkiso",current_bmuonvar.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_reliso",current_bmuonvar.reliso,weight,150,0,15);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_charge",current_bmuonvar.charge,weight,4,-2,2);
}


void TTsemiLepChargeScoreEfficiencyMeasurement::FillHist_bCand_belectron(TString cutname){  
  if(runSys) return;
  if(ForBinning) return;
  FillHist(cutname+"/"+current_bjetname+"_belectron_P_jetrest",current_belectronvar.P_jetrest,weight,10,0,10);
  FillHist(cutname+"/"+current_bjetname+"_belectron_ptwrtjet",current_belectronvar.ptwrtjet,weight,10,0,10);
  FillHist(cutname+"/"+current_bjetname+"_belectron_dR_l_j",current_belectronvar.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/"+current_bjetname+"_belectron_nsip3d",current_belectronvar.nsip3d,weight,30,0,15);
  FillHist(cutname+"/"+current_bjetname+"_belectron_reltrkiso",current_belectronvar.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/"+current_bjetname+"_belectron_reliso",current_belectronvar.reliso,weight,150,0,15);
  FillHist(cutname+"/"+current_bjetname+"_belectron_charge",current_belectronvar.charge,weight,4,-2,2);
  FillHist(cutname+"/"+current_bjetname+"_belectron_IsGsfCtfScPixChargeConsistent",current_belectronvar.IsGsfCtfScPixChargeConsistent,weight,4,-2,2);
  FillHist(cutname+"/"+current_bjetname+"_belectron_InvEminusInvP",current_belectronvar.InvEminusInvP,weight,50,0,0.3);
  FillHist(cutname+"/"+current_bjetname+"_belectron_palongjet",current_belectronvar.palongjet,weight,100,0,30);
  FillHist(cutname+"/"+current_bjetname+"_belectron_palongjetratio",current_belectronvar.palongjetratio,weight,100,0,2);

}


void TTsemiLepChargeScoreEfficiencyMeasurement::FillHistAll(TString cutname){
  if(ForBinning) return;
  FillHist(cutname+"/nPV",nPV,weight,100,0,100);

  FillHist(cutname+"/MT_lv",vtW.M(),weight,200,0,200);

  FillHist(cutname+"/pt_l1",l1.Pt(),weight,200,0,200);
  FillHist(cutname+"/eta_l1",l1.Eta(),weight,50,-3,3);

  FillHist(cutname+"/njet",njet,weight,10,0,10);
  FillHist(cutname+"/nbjet",nbjet,weight,10,0,10);

  FillHist(cutname+"/puppimet",PuppiMET.Pt(),weight,200,0,200);
  FillHist(cutname+"/dphi_l_met",PuppiMET.DeltaPhi(l1),weight,200,-4,4);

  if(njet>0){
    FillHist(cutname+"/pt_j1",v_tightjet[0].Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_j1",v_tightjet[0].Eta(),weight,50,-3,3);
    if(njet>1){
      FillHist(cutname+"/pt_j2",v_tightjet[1].Pt(),weight,200,0,200);
      FillHist(cutname+"/eta_j2",v_tightjet[1].Eta(),weight,50,-3,3);
    }
  }  


  
}


void TTsemiLepChargeScoreEfficiencyMeasurement::EventLoop(){
  RunReco();

}





void TTsemiLepChargeScoreEfficiencyMeasurement::TruthLoop(){
  //it must be TTLJ samples
  if (IsTTLJSample){
    TTsemiLepChargeScoreEfficiencyMeasurement::RunLHEinfo();
    TTsemiLepChargeScoreEfficiencyMeasurement::RunGENinfo();
  }

}

void TTsemiLepChargeScoreEfficiencyMeasurement::RunLHEinfo(){
  //
  //initialize
  int LHEsize = lhes.size();
  unsigned int n_light_quark=0;
  int LeptonCharge=0;
  IsElectronChannel_LHE =0;
  IsMuonChannel_LHE     =0;
  IsTauChannel_LHE      =0;

  for(int i = 0; i < LHEsize; i++) {
    int status=lhes[i].Status();
    int pid=lhes[i].ID();

    if(status==1){
      if(pid == 11){
        LeptonCharge = -1; IsElectronChannel_LHE=true;
        break;
      }
      else if(pid == -11){
        LeptonCharge = +1; IsElectronChannel_LHE=true;
        break;
      }
      else if(pid == 13){
        LeptonCharge = -1; IsMuonChannel_LHE=true;
        break;
      }
      else if(pid == -13){
        LeptonCharge = 1; IsMuonChannel_LHE=true;
        break;
      }

      else if(pid == 15){
        LeptonCharge = -1; IsTauChannel_LHE=true;
        break;
      }
      else if(pid == -15){
        LeptonCharge = 1; IsTauChannel_LHE=true;
        break;
      }

      if ( abs(pid)<5) n_light_quark+=1;
    }    
  }//[END] OF LHE LOOP
  bLepCharge_LHE=-LeptonCharge;
  bHadCharge_LHE=LeptonCharge;
  
}
void TTsemiLepChargeScoreEfficiencyMeasurement::RunGENinfo(){
  unsigned int gensize=gens.size();
  //status21 is incoming particle.
  //To find W decay daughters 

  idx_bquark_GEN=-1, idx_bbarquark_GEN=-1;
  v_idx_lightquark_GEN.clear();
  
  i_lepton_GEN=-1;
  i_neutrino_GEN=-1;
  for(unsigned int i = 0 ; i < gensize ; i++){
    int pid=gens[i].PID();
    int status=gens[i].Status();
    int mother=gens[i].MotherIndex();
    int isHardProcess=gens[i].isHardProcess();
    /// Outgoing HardProcess parton
    if(mother > -1){
      if (isHardProcess && (status!=21) && gens[mother].Status()!=21 && abs(pid)<5) {
	v_idx_lightquark_GEN.push_back(i);
      }
    }
    if (isHardProcess && (status!=21)){
      if(pid==5){
        idx_bquark_GEN=i;
      }
      else if(pid==-5){
        idx_bbarquark_GEN=i;
      }
      if(abs(pid)>10 && abs(pid)<17){
	if(abs(pid)==11 || abs(pid)==13 || abs(pid)==15){
	  i_lepton_GEN=i;
	}
	else{
	  i_neutrino_GEN=i;
	}
      }
    }


  }
  //----GEN-LEVEL W_had and T_had
  TLorentzVector vWhad,vThad,vWlep,vTlep;
  //---Add outgoing light quarks' momenta to whad,thad
  //for(unsigned int i = 0 ; i < v_idx_lightquark_GEN.size(); i++){
  for(auto& i_light : v_idx_lightquark_GEN){
    vWhad+=gens[i_light];
    vThad+=gens[i_light];
  }


  vWlep=gens[i_lepton_GEN]+gens[i_neutrino_GEN];
  vTlep=vWlep;

  //---add bquark momentum to Top
  if(bHadCharge_LHE>0){// bHadCharge >0 means bbar
    vThad+=gens[idx_bbarquark_GEN];
    vTlep+=gens[idx_bquark_GEN];
  }
  else{
    vThad+=gens[idx_bquark_GEN];
    vTlep+=gens[idx_bbarquark_GEN];
  }

  Whad_q1_pid=gens[v_idx_lightquark_GEN[0]].PID();
  Whad_q2_pid=gens[v_idx_lightquark_GEN[1]].PID();



  
  // FillHist("GEN/Whad_mass/"+ProcessName,vWhad.M(), weight, 80, 50, 130);
  //FillHist("GEN/Thad_mass/"+ProcessName,vThad.M(), weight, 60, 140, 200);

  //FillHist("GEN/Wlep_mass/"+ProcessName,vWlep.M(), weight, 80, 50, 130);
  //FillHist("GEN/Tlep_mass/"+ProcessName,vTlep.M(), weight, 60, 140, 200);


  //Hadronic b, and bjet
  bHad_True_PID=99999;
  bHad_True_genidx=-1;
  if(bHadCharge_LHE>0){//bbar
    bHad_True_PID=-5;
    bLep_True_PID=5;
    bHad_True_genidx=idx_bbarquark_GEN;
    bLep_True_genidx=idx_bquark_GEN;
  }
  else{//b
    bHad_True_PID=5;
    bLep_True_PID=-5;
    bHad_True_genidx=idx_bquark_GEN;
    bLep_True_genidx=idx_bbarquark_GEN;
  }
  

}


