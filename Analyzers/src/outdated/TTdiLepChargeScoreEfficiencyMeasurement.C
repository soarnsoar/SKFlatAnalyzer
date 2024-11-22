#include "TTdiLepChargeScoreEfficiencyMeasurement.h"
#include <map>
TTdiLepChargeScoreEfficiencyMeasurement::TTdiLepChargeScoreEfficiencyMeasurement(){
  //runSys=true;

  //JHAnalyzerBase::SetupDiLeptonChannel();  
}

TTdiLepChargeScoreEfficiencyMeasurement::~TTdiLepChargeScoreEfficiencyMeasurement(){
  //==== Destructor of this Analyzer
}

void TTdiLepChargeScoreEfficiencyMeasurement::initializeAnalyzer(){
  cout << "[TTdiLepChargeScoreEfficiencyMeasurement::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupDiLeptonChannel();
  IsDYSample=false;
  if(MCSample.Contains("DYJets")||MCSample.Contains("ZToEE")||MCSample.Contains("ZToMuMu")||MCSample.Contains(TRegexp("DY[0-9]Jets"))) IsDYSample=true;
  cout << "[IsDYSample]=" << IsDYSample << endl;
  lepveto=HasFlag("lepveto");


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
    cout << "[JETPUID] DEFAULT ==NOCUT" << endl;
    _JETPUID="";
  }


  TString v_muonScore="2405.4.3";
  TString v_electronScore="2405.4.3";
  TString v_jetScore="2405.4.3";
  bool apply_dnncut=true;
  LoadChargeScoreTool(v_muonScore,v_electronScore,v_jetScore,apply_dnncut);



}


void TTdiLepChargeScoreEfficiencyMeasurement::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;
  
}

bool TTdiLepChargeScoreEfficiencyMeasurement::CheckIsDiMuonChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  //vector<int> v_muonidx=GetIdxDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  vector<Muon> v_muon=lepveto ? GetDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2) : GetDiMuRecoNoVeto(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  if( v_muon.size()<2) return 0;
  double mll=(v_muon[0]+v_muon[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;

  SetMuon(v_muon[0],v_muon[1]);

  return 1;
}  

void TTdiLepChargeScoreEfficiencyMeasurement::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;
  
}


bool TTdiLepChargeScoreEfficiencyMeasurement::CheckIsDiElectronChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  vector<Electron> v_electron=lepveto ? GetDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2) : GetDiElRecoNoVeto(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  if( v_electron.size()<2) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  
  double mll=(v_electron[0]+v_electron[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;
  SetElectron(v_electron[0],v_electron[1]);
  return 1;
}  

void TTdiLepChargeScoreEfficiencyMeasurement::SetEventNormWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full");
}

void TTdiLepChargeScoreEfficiencyMeasurement::SetEventWeight(){
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

void TTdiLepChargeScoreEfficiencyMeasurement::RunReco(){

  IsDiMuonChannel=false;
  IsDiElectronChannel=false;
  double min_mll = 120.;
  double max_mll = 60.;

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
  v_tightjet=GetTightJet(v_tightlep,30,2.4,"tight",_JETPUID);
  v_bjetidx=GetBJetIdx(v_tightjet);

  njet=v_tightjet.size();
  nbjet=v_bjetidx.size();

  SetEventWeight();  


  if(nbjet != 2) return;
  if(v_tightjet.size()<4) return;


  if(!IsDATA){
    int ib1=v_bjetidx[0];
    int ib2=v_bjetidx[1];
    bool isLeadingBjetFromb= abs(v_tightjet[ib1].partonFlavour())==5;
    bool isSubleadingBjetFromb= abs(v_tightjet[ib2].partonFlavour())==5;
    if(isLeadingBjetFromb&&isSubleadingBjetFromb){
      ProcessName=MCSample+"_All_bjetFromb";
    }
    else if(isLeadingBjetFromb){
      ProcessName=MCSample+"_LeadingBjetFromb";
    }
    else if(isSubleadingBjetFromb){
      ProcessName=MCSample+"_SubleadingBjetFromb";
    }
    else{
      ProcessName=MCSample+"_NonFromb";
    }
    
    
  }

  FillHistAll("ll");
  FillHistAll(LepCh);

  
}




void TTdiLepChargeScoreEfficiencyMeasurement::FillHistAll(TString cutname){


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

  


  int ib1=v_bjetidx[0];
  int ib2=v_bjetidx[1];

    

  FillHist_bjetinfo(cutname, ib1,"leading_bjet");
  FillHist_bjetinfo(cutname, ib2,"subleading_bjet");





}


void TTdiLepChargeScoreEfficiencyMeasurement::FillHist_bjetinfo(TString cutname, int i_bjet, TString Name_bCand){



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
  FillHist(cutname+"/"+Name_bCand+"_Charge",bCand_Charge,weight,12,-6,6);
  if(bCand_NotUseOppositeCharge){//Not Opposite
    FillHist(cutname+"/"+Name_bCand+"_Charge_NotOpposite",bCand_Charge,weight,12,-6,6);
  }
  else{
    FillHist(cutname+"/"+Name_bCand+"_Charge_UseOpposite",bCand_Charge,weight,12,-6,6);
  }

  ///-----bjet's kin. by each bjetcharge----//
  //(1)using softmuon   
  if(abs(bCand_Charge)==1){//
    //read bmuonvar
    current_bmuonvar=Get_bmuonvar(AllMuons[bCand_im],v_tightjet[i_bjet]);
    FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftMuonCharge");
    FillHist_bCand_bmuon(cutname+"__"+Name_bCand+"UsingSoftMuonCharge");
    if(bCand_NotUseOppositeCharge){
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftMuonChargeNotOpposite");
      FillHist_bCand_bmuon(cutname+"__"+Name_bCand+"UsingSoftMuonChargeNotOpposite");
    }
    else{
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftMuonChargeUseOpposite");
      FillHist_bCand_bmuon(cutname+"__"+Name_bCand+"UsingSoftMuonChargeUseOpposite");

    }
  }
  else if(abs(bCand_Charge)==2){//using softelectron charge
    //read  belectronvar
    current_belectronvar=Get_belectronvar(AllElectrons[bCand_ie],v_tightjet[i_bjet]);
    //denominator
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon");

    //(2)using softelectron
    FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftElectronCharge");
    FillHist_bCand_belectron(cutname+"__"+Name_bCand+"UsingSoftElectronCharge");
    if(bCand_NotUseOppositeCharge){
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftElectronChargeNotOpposite");
      FillHist_bCand_belectron(cutname+"__"+Name_bCand+"UsingSoftElectronChargeNotOpposite");
    }
    else{
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftElectronChargeUseOpposite");
      FillHist_bCand_belectron(cutname+"__"+Name_bCand+"UsingSoftElectronChargeUseOpposite");
    }
  }



  else if(abs(bCand_Charge)==3){//
    //denominators
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon");
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon__FailSoftElectron");

    //(3)using goodjetcharge
    FillHist_bCand(cutname+"__"+Name_bCand+"UsingGoodJetCharge");
    if(bCand_NotUseOppositeCharge){
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingGoodJetChargeNotOpposite");
    }
    else{
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingGoodJetChargeUseOpposite");
    }
  }//(4)using poorjetcharge
  else{
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon");
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon__FailSoftElectron");
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon__FailSoftElectron__FailGoodBJet");
  }



}


void TTdiLepChargeScoreEfficiencyMeasurement::FillHist_bCand(TString cutname){
  ///--DNN inputs
  //bjetvar this_bjetvar=Get_bjetvar(v_tightjet[ibCand]);
  FillHist(cutname+"/"+current_bjetname+"_pt",current_bjetvar.pt,weight,300,0,300);
  FillHist(cutname+"/"+current_bjetname+"_aeta",current_bjetvar.aeta,weight,60,0,3);
  FillHist(cutname+"/"+current_bjetname+"_eta",current_bjetvar.eta,weight,120,-3,3);
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

  FillHist(cutname+"/"+current_bjetname+"_ChargeScore",bCnad_ChargeScore,weight,100,0,1);

}


void TTdiLepChargeScoreEfficiencyMeasurement::FillHist_bCand_bmuon(TString cutname){
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


void TTdiLepChargeScoreEfficiencyMeasurement::FillHist_bCand_belectron(TString cutname){
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



void TTdiLepChargeScoreEfficiencyMeasurement::EventLoop(){
  //AnalyzerCore::FillHist("all/nmuons/"+ProcessName,AllMuons.size(),1,100,0.,100.);
  //AnalyzerCore::FillHist("all/nelectrons/"+ProcessName,AllElectrons.size(),1,100,0.,100.);
  RunReco();
}  
  




