#include "HZZ_test.h"
#include <stdlib.h>
#include <stdio.h>

HZZ_test::HZZ_test(){//FYI : bottomness = -nb
  //Set Hadron PID vector with nb=+1
  
  DNNcut=0.5;

  doDebug=false;




}
//data/Run2UltraLegacy_v3/2017/TMVA

void HZZ_test::initializeAnalyzer(){

  if(IsDATA){
    //ProcessName=DataStream;    
    ProcessName="Data";
  }
  else{
    ProcessName=MCSample;
    //if(ProcessName.Contains("DY")){
    //  ProcessName="DY";
    //}
  }
  cout << "[HZZ_test::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;

  if(DataYear==2017){
  MuonTriggerName = "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v";
  ElectronTriggerName = "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v";
  TriggerSafeCut_muon1 = 20.;
  TriggerSafeCut_muon2 = 11.;
  TriggerSafeCut_electron1 = 26;
  TriggerSafeCut_electron2 = 15;
  }
  else if(DataYear==2018){
    MuonTriggerName = "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v";
    ElectronTriggerName = "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v";
    TriggerSafeCut_muon1 = 20.;
    TriggerSafeCut_muon2 = 11.;
    TriggerSafeCut_electron1 = 26;
    TriggerSafeCut_electron2 = 15;
  }
  else if(DataYear==2016){
    MuonTriggerName = "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v";
    ElectronTriggerName = "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v";
    TriggerSafeCut_muon1 = 20.;
    TriggerSafeCut_muon2 = 11.;
    TriggerSafeCut_electron1 = 26;
    TriggerSafeCut_electron2 = 15;
  }


}

HZZ_test::~HZZ_test(){
  //==== Destructor of this Analyzer
}

bool HZZ_test::AnalyzeLHE(){
  LHEs=GetLHEs();
  myLHE.LHEsize=LHEs.size();
  //cout << "LHE" << endl;
  //(1)Check Index of incoming parton
  //int status=-999;
  int pid=-999;
  //double pz=-999,E=-999;

  int N_mu=0;
  int N_e=0;
  for(unsigned int i = 0; i < myLHE.LHEsize ; i++){
    pid=LHEs[i].ID();
    //cout << pid << endl;
    if (abs(pid)==13) N_mu+=1;
    if (abs(pid)==11) N_e +=1;
  }
  if (N_mu!=2) return 0; 
  if (N_e !=2) return 0; 
  TLorentzVector Zmu;
  TLorentzVector Ze;
  Zmu.SetPxPyPzE(0,0,0,0);
  Ze.SetPxPyPzE(0,0,0,0);
  for(unsigned int i = 0; i < myLHE.LHEsize ; i++){
    //status=LHEs[i].Status();
    pid=LHEs[i].ID();
    //pz=LHEs[i].Pz();
    //E=LHEs[i].E();
    if(abs(pid)==11) Ze +=LHEs[i];
    if(abs(pid)==13) Zmu+=LHEs[i];
    
  }
  //cout << "-----" << endl;
  //cout << "Zmu.M()=" << Zmu.M() << endl; 
  //cout << "Ze.M()=" << Ze.M() << endl; 
  //cout << "(Zmu+Ze).M()=" << (Zmu+Ze).M() << endl;
  return 1;
}
bool HZZ_test::ZZmmmmReco(){
  vector<Muon> v_ZZmuon;

  vector<int> idx_ZZmuon_plus;
  vector<Muon> v_ZZmuon_plus;
  vector<int> idx_ZZmuon_minus;
  vector<Muon> v_ZZmuon_minus;
  //double this_leptonid_sf=1.;
  //double this_trigger_sf=1.;
  //double this_iso_sf=1.;
  //int i_l1=-1;

  //unsigned int N_plus=0;
  //unsigned int N_minus=0;
  //Because roch. corr. need to find leading pt muon again.
  double maxpt=-100.;
  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double pt=AllMuons[i].Pt();
    double eta=AllMuons[i].Eta();
    int charge=AllMuons[i].Charge();
    bool passID=AllMuons[i].PassID("POGMedium");
    bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    //double reliso=AllMuons[i].RelIso();
    if(fabs(eta) > 2.4) continue; 
    //if(pt <15.) continue;
    if (!passID) continue;
    if (!passISO) continue;
    if (pt < 5.)continue;
    if (pt > maxpt){
      maxpt=pt;
      //i_l1=i;
    }
    v_ZZmuon.push_back((AllMuons[i]));
    if(charge > 0){
      idx_ZZmuon_plus.push_back(i);
      v_ZZmuon_plus.push_back(AllMuons[i]);
    }
    else{
      idx_ZZmuon_minus.push_back(i);
      v_ZZmuon_minus.push_back(AllMuons[i]);
    }
  }//end of muon loop
  //unsigned int v_ZZmuonsize=v_ZZmuon.size();
  //if(v_ZZmuonsize<4) return 0;
  //TLorentzVector ZZ4l;
  //for(int i =0 ; i < 4 ; i++){
  //  ZZ4l+=v_ZZmuon[i];
  //}



  FillCutflow("cutflow/all/"+ProcessName,"4mu",weight);

  if (idx_ZZmuon_plus.size() !=2) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"2mu_plus",weight);
  if (idx_ZZmuon_minus.size() !=2) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"2mu_minus",weight);
  TLorentzVector ZZ4l;
  for(int i = 0 ; i < 2 ; i ++){
    ZZ4l+=v_ZZmuon_plus[i];
    ZZ4l+=v_ZZmuon_minus[i];
  }
  FillHist("4mu/4lmass/"+ProcessName,ZZ4l.M(),weight,170,0.,170.);
  TLorentzVector Z11,Z22;
  TLorentzVector Z12,Z21;
  Z11=v_ZZmuon_plus[0]+v_ZZmuon_minus[0];
  Z22=v_ZZmuon_plus[1]+v_ZZmuon_minus[1];
  Z12=v_ZZmuon_plus[0]+v_ZZmuon_minus[1];
  Z21=v_ZZmuon_plus[1]+v_ZZmuon_minus[0];

  if(Z11.M() < 4. ) return 0;
  if(Z22.M() < 4. ) return 0;
  if(Z12.M() < 4. ) return 0;
  if(Z21.M() < 4. ) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"all_mll_Over_4GeV",weight);

  double dm11=fabs(Z11.M()-91.);
  double dm22=fabs(Z22.M()-91.);
  double dm12=fabs(Z12.M()-91.);
  double dm21=fabs(Z21.M()-91.);
  vector<double> dmlist;
  dmlist.push_back(dm11);
  dmlist.push_back(dm22);
  dmlist.push_back(dm12);
  dmlist.push_back(dm21);
  double dm_min=1000000.;
  int imin=-1;
  for(unsigned int i = 0 ; i < 4; i++ ){
    double this_dm=dmlist[i];
    if(this_dm < dm_min){
      dm_min=this_dm;
      imin=i;
    }
  }
  bool Is1122=false;
  if(imin==0 || imin==1){
    Is1122=true;
  }
  TLorentzVector Z1,Z2;//Z1 :: MZ closer to 91.
  if(Is1122){
    if(imin==0){//11 is Z close
      Z1=Z11;
      Z2=Z22;
    }
    else{
      Z1=Z22;
      Z2=Z11;
    }    
  }
  else{
    if(imin==2){//12 is Z close
      Z1=Z12;
      Z2=Z21;
    }
    else{
      Z1=Z21;
      Z2=Z12;
    }
  }
  double MZ_window0=40,MZ_window1=130;
  if(  Z1.M() < MZ_window0) return 0;
  if(  Z1.M() > MZ_window1) return 0;
  if( Z2.M() < 12. ) return 0 ; 
  FillHist("4mu/4lmass_final/"+ProcessName,ZZ4l.M(),weight,170,0.,170.);
  FillHist("4l/4lmass_final/"+ProcessName,ZZ4l.M(),weight,170,0.,170.);



  return 1;


}



bool HZZ_test::ZZmmeeReco(){
  vector<Muon> v_ZZmuon;

  vector<int> idx_ZZmuon_plus;
  vector<Muon> v_ZZmuon_plus;
  vector<int> idx_ZZmuon_minus;
  vector<Muon> v_ZZmuon_minus;


  vector<Electron> v_ZZelectron;
  vector<int> idx_ZZelectron_plus;
  vector<Electron> v_ZZelectron_plus;
  vector<int> idx_ZZelectron_minus;
  vector<Electron> v_ZZelectron_minus;


  
  //int i_l1=-1;


  //Because roch. corr. need to find leading pt muon again.
  double maxpt=-100.;
  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double pt=AllMuons[i].Pt();
    double eta=AllMuons[i].Eta();
    int charge=AllMuons[i].Charge();
    bool passID=AllMuons[i].PassID("POGMedium");
    bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    //double reliso=AllMuons[i].RelIso();
    if(fabs(eta) > 2.4) continue; 
    //if(pt <15.) continue;
    if (!passID) continue;
    if (!passISO) continue;
    if (pt < 5.)continue;
    if (pt > maxpt){
      maxpt=pt;
      //i_l1=i;
    }
    v_ZZmuon.push_back((AllMuons[i]));
    if(charge > 0){
      idx_ZZmuon_plus.push_back(i);
      v_ZZmuon_plus.push_back(AllMuons[i]);
    }
    else{
      idx_ZZmuon_minus.push_back(i);
      v_ZZmuon_minus.push_back(AllMuons[i]);
    }
  }//end of muon loop
  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=AllElectrons[i].Pt();
    double eta=AllElectrons[i].Eta();
    bool passID=AllElectrons[i].PassID("passMediumID");
    int charge=AllElectrons[i].Charge();
    if(fabs(eta) > 2.4) continue; 
    if(pt < 7) continue;
    if (!passID) continue;

    v_ZZelectron.push_back(AllElectrons[i]);
    if(charge > 0){
      idx_ZZelectron_plus.push_back(i);
      v_ZZelectron_plus.push_back(AllElectrons[i]);
    }
    else{
      idx_ZZelectron_minus.push_back(i);
      v_ZZelectron_minus.push_back(AllElectrons[i]);
    }


  }//end of electron loop
  if (idx_ZZmuon_plus.size() !=1) return 0;
  if (idx_ZZmuon_minus.size() !=1) return 0;
  if (idx_ZZelectron_plus.size() !=1) return 0;
  if (idx_ZZelectron_minus.size() !=1) return 0;
  if(myRECO.passMuonTrigger){
    if (max(v_ZZmuon_plus[0].Pt(),v_ZZmuon_minus[0].Pt()) < TriggerSafeCut_muon1) return 0;
    if (min(v_ZZmuon_plus[0].Pt(),v_ZZmuon_minus[0].Pt()) < TriggerSafeCut_muon2) return 0;
  }
  else if(myRECO.passElectronTrigger){
    if (max(v_ZZelectron_plus[0].Pt(),v_ZZelectron_minus[0].Pt()) < TriggerSafeCut_electron1) return 0;
    if (min(v_ZZelectron_plus[0].Pt(),v_ZZelectron_minus[0].Pt()) < TriggerSafeCut_electron2) return 0;
    
  }

  TLorentzVector ZZ4l;
  ZZ4l=v_ZZmuon_plus[0]+v_ZZmuon_minus[0]+v_ZZelectron_plus[0]+v_ZZelectron_minus[0];
  TLorentzVector Zmm,Zee;
  Zmm=v_ZZmuon_plus[0]+v_ZZmuon_minus[0];
  Zee=v_ZZelectron_plus[0]+v_ZZelectron_minus[0];
  FillHist("mmee/4lmass/"+ProcessName,ZZ4l.M(),weight,170,0.,170.);

  if(Zmm.M() < 4. ) return 0;
  if(Zee.M() < 4. ) return 0;

  double dmee=fabs(Zee.M()-91.);
  double dmmm=fabs(Zmm.M()-91.);

  TLorentzVector Z1,Z2;//Z1 :: MZ closer to 91.
  if(dmee < dmmm){
      Z1=Zee;
      Z2=Zmm;
  }
  else{
    Z1=Zmm;
    Z2=Zee;
  }    
  

  double MZ_window0=40,MZ_window1=130;
  if(  Z1.M() < MZ_window0) return 0;
  if(  Z1.M() > MZ_window1) return 0;
  if( Z2.M() < 12. ) return 0 ; 
  FillHist("mmee/4lmass_final/"+ProcessName,ZZ4l.M(),weight,170,0.,170.);
  FillHist("4l/4lmass_final/"+ProcessName,ZZ4l.M(),weight,170,0.,170.);



  return 1;


}




bool HZZ_test::ZZeeeeReco(){
  vector<Electron> v_ZZelectron;
  
  vector<int> idx_ZZelectron_plus;
  vector<Electron> v_ZZelectron_plus;
  vector<int> idx_ZZelectron_minus;
  vector<Electron> v_ZZelectron_minus;

  
  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=AllElectrons[i].Pt();
    double eta=AllElectrons[i].Eta();
    bool passID=AllElectrons[i].PassID("passMediumID");
    int charge=AllElectrons[i].Charge();
    if(fabs(eta) > 2.5) continue; 
    if(pt < 7.) continue;
    if (!passID) continue;

    v_ZZelectron.push_back((AllElectrons[i]));
    if(charge > 0){
      idx_ZZelectron_plus.push_back(i);
      v_ZZelectron_plus.push_back(AllElectrons[i]);
    }
    else{
      idx_ZZelectron_minus.push_back(i);
      v_ZZelectron_minus.push_back(AllElectrons[i]);
    }


  }

  //this_trigger_sf*=ElectronTrigger_SF(TString ID, "HLT_Ele35_WPTight_Gsf_v", v_Zelectron, 0);

  if (v_ZZelectron.size()<4) return 0;
  if (v_ZZelectron[0].Pt()< TriggerSafeCut_electron1) return 0;
  if (v_ZZelectron[1].Pt()< TriggerSafeCut_electron2) return 0;


  /*
  if(!IsDATA) {
    this_leptonreco_sf*=mcCorr->ElectronReco_SF (AllElectrons[i_l1].scEta(), AllElectrons[i_l1].Pt(),0);
    this_leptonreco_sf*=mcCorr->ElectronReco_SF (AllElectrons[i_l1].scEta(), AllElectrons[i_l2].Pt(),0);
    this_leptonid_sf*=mcCorr->ElectronID_SF ("passMediumID",  AllElectrons[i_l1].scEta(), AllElectrons[i_l1].Pt());
    this_leptonid_sf*=mcCorr->ElectronID_SF ("passMediumID",  AllElectrons[i_l2].scEta(), AllElectrons[i_l2].Pt());
    
    vector<Lepton*> leps=MakeLeptonPointerVector(v_Zelectron);
    Lepton* _el1=leps.at(0);
    Lepton* _el2=leps.at(1);
    el_trigsf=GetDileptonTriggerSF("Ele23Leg1_MediumID","Ele12Leg2_MediumID","",leps,0,0);
    el_recosf=fEff->GetEfficiencySF("Electron_RECO",_el1,0,0) * fEff->GetEfficiencySF("Electron_RECO",_el2,0,0);
    el_idsf=fEff->GetEfficiencySF("Electron_MediumID",_el1,0,0) * fEff->GetEfficiencySF("Electron_MediumID",_el2,0,0);
  }
  */

  
  ///
  if (idx_ZZelectron_plus.size() !=2) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"2e_plus",weight);
  if (idx_ZZelectron_minus.size() !=2) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"2e_minus",weight);
  TLorentzVector ZZ4l;
  for(int i = 0 ; i < 2 ; i ++){
    ZZ4l+=v_ZZelectron_plus[i];
    ZZ4l+=v_ZZelectron_minus[i];
  }
  FillHist("4e/4lmass/"+ProcessName,ZZ4l.M(),weight,1700,0.,170.);
  TLorentzVector Z11,Z22;
  TLorentzVector Z12,Z21;
  Z11=v_ZZelectron_plus[0]+v_ZZelectron_minus[0];
  Z22=v_ZZelectron_plus[1]+v_ZZelectron_minus[1];
  Z12=v_ZZelectron_plus[0]+v_ZZelectron_minus[1];
  Z21=v_ZZelectron_plus[1]+v_ZZelectron_minus[0];

  if(Z11.M() < 4. ) return 0;
  if(Z22.M() < 4. ) return 0;
  if(Z12.M() < 4. ) return 0;
  if(Z21.M() < 4. ) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"all_mll_Over_4GeV",weight);

  double dm11=fabs(Z11.M()-91.);
  double dm22=fabs(Z22.M()-91.);
  double dm12=fabs(Z12.M()-91.);
  double dm21=fabs(Z21.M()-91.);
  vector<double> dmlist;
  dmlist.push_back(dm11);
  dmlist.push_back(dm22);
  dmlist.push_back(dm12);
  dmlist.push_back(dm21);
  double dm_min=1000000.;
  int imin=-1;
  for(unsigned int i = 0 ; i < 4; i++ ){
    double this_dm=dmlist[i];
    if(this_dm < dm_min){
      dm_min=this_dm;
      imin=i;
    }
  }
  bool Is1122=false;
  if(imin==0 || imin==1){
    Is1122=true;
  }
  TLorentzVector Z1,Z2;//Z1 :: MZ closer to 91.
  if(Is1122){
    if(imin==0){//11 is Z close
      Z1=Z11;
      Z2=Z22;
    }
    else{
      Z1=Z22;
      Z2=Z11;
    }    
  }
  else{
    if(imin==2){//12 is Z close
      Z1=Z12;
      Z2=Z21;
    }
    else{
      Z1=Z21;
      Z2=Z12;
    }
  }
  double MZ_window0=40,MZ_window1=120;
  if(  Z1.M() < MZ_window0) return 0;
  if(  Z1.M() > MZ_window1) return 0;
  if( Z2.M() < 12. ) return 0 ; 
  FillHist("4e/4lmass_final/"+ProcessName,ZZ4l.M(),weight,170,0.,170.);
  FillHist("4l/4lmass_final/"+ProcessName,ZZ4l.M(),weight,170,0.,170.);


  return 1;



    

}



bool HZZ_test::ApplyEventKinematicCut(){
  FillHistEventBase("BeforeKinCut");
  //myRECO.vZ;
  //MET
  //(1) MET
  //if (MET > 75. ) return 0;
  if (PuppiMET_pt > 75. ) return 0;
  FillHistEventBase("After_MET_Cut");
  FillCutflow("cutflow/all/"+ProcessName,"MET_Cut",weight);
  //(2)dPhi(Z,b)
  dphi_z_b= fabs(AllJets[myRECO.ij_B].DeltaPhi(myRECO.vZ));
  if (dphi_z_b < 1.6 ) return 0;
  FillHistEventBase("After_MET_dPhi_Cut");
  FillCutflow("cutflow/all/"+ProcessName,"dPhi_Cut",weight);
  pt_z=myRECO.vZ.Pt();
  if (pt_z < 15.) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"ZpT_Cut",weight);
  FillHistEventBase("After_MET_dPhi_ZpT_Cut");
  pt_zb=(AllJets[myRECO.ij_B]+myRECO.vZ).Pt();
  if (pt_zb > 60.) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"pT_Zb_Cut",weight);
  FillHistEventBase("After_MET_dPhi_ZpT_pT_Zb_Cut");
  return 1;
}

void HZZ_test::CategorizeEvent(){
  if (n_bmuon > 0){
    FillHistBMuon("AtLeast1MuonInJet");
    FillHistBJet("AtLeast1MuonInJet");
  }
  if (n_belectron > 0){
    FillHistBElectron("AtLeast1ElectronInJet");
    FillHistBJet("AtLeast1ElectronInJet");
  }
  FillHistBJet("NoCategory");

  /////(1)BMuonChargeEvt
  if (n_bmuon>0 && bmuon1_DNN > DNNcut){
    evtcat_int=0;
    evtcat_str="BMuonChargeEvt";
    evtcharge=bmuon1_charge*bmuon1_DNN;
    evtscore=bmuon1_DNN;
  }////(2)BElectronChargeEvt 
  else if(n_belectron>0 && belectron1_DNN > DNNcut){
    evtcat_int=1;
    evtcat_str="BElectronChargeEvt";
    evtcharge=belectron1_charge*belectron1_DNN;
    evtscore=belectron1_DNN;
  }////(3)BJetChargeEvt
  else if(bjet_DNN > DNNcut){
    evtcat_int=2;
    evtcat_str="BJetChargeEvt";
    evtcharge=bjet_charge*bjet_DNN;
    evtscore=bjet_DNN;
  }////(4)Untagged
  else{
    evtcat_int=3;
    evtcat_str="UntaggedEvt";
    evtcharge=bjet_charge*bjet_DNN;
    evtscore=bjet_DNN;
  }

}

void HZZ_test::AnalyzeRECO(){


  
  //call muon/electron
  vector<Muon> AllMuons_raw=GetAllMuons();
  AllMuons=ScaleMuons(AllMuons_raw,0);
  muonsize = AllMuons.size();
  AllElectrons=GetAllElectrons();
  electronsize = AllElectrons.size();
  AllJets = GetAllJets();
  jetsize=AllJets.size();

  //(0) Apply some basic cuts

  myRECO.passMuonTrigger=ev.PassTrigger(MuonTriggerName);
  myRECO.passElectronTrigger=ev.PassTrigger(ElectronTriggerName);

  if(!myRECO.passMuonTrigger && !myRECO.passElectronTrigger) return;

  //FillHist("PassBothTrigger",myRECO.passMuonTrigger*myRECO.passElectronTrigger, weight, 2, 0, 2);



  myRECO.goodZZmmmm=ZZmmmmReco();
  if(!myRECO.goodZZmmmm) myRECO.goodZZeeee=ZZeeeeReco();
  if(!myRECO.goodZZeeee && !myRECO.goodZZmmmm) myRECO.goodZZmmee=ZZmmeeReco();
  //if(!myRECO.passMuonTrigger) return;
  //FillCutflow("cutflow/all/"+ProcessName,"Trigger",weight);

  //myRECO.passMuonTriggerAndZZmmmm=myRECO.passMuonTrigger && myRECO.goodZZmmmm;
  //myRECO.passElectronTriggerAndZZeeee=myRECO.passElectronTrigger && myRECO.goodZZeeee;
  //myRECO.passElectronTriggerAndZee= myRECO.passElectronTrigger && myRECO.goodZee;
  //if((!myRECO.passMuonTriggerAndZmm) && (!myRECO.passElectronTriggerAndZee)) return;
  //if(!myRECO.passMuonTriggerAndZZmmmm && !myRECO.passElectronTriggerAndZZeeee) return;
  FillCutflow("cutflow/all/"+ProcessName,"TriggerAndGood_mmmm",weight);
  
  //FillHist("4mu/HCand_mass/"+ProcessName,hcand.M(),weight,50,70.,170.);




}



void HZZ_test::FillHistEventBase(TString cutname){
  if(IsTreeMode) return;
  FillHist(cutname+"/nPV/"+ProcessName,nPV,weight,75,0.,150.);
  FillHist(cutname+"/pfMET/"+ProcessName,MET,weight,75,0.,150.);
  FillHist(cutname+"/PuppiMET/"+ProcessName,PuppiMET_pt,weight,75,0.,150.);
  FillHist(cutname+"/dPhi_Z_b/"+ProcessName,dphi_z_b,weight,35,0.,3.15);
  FillHist(cutname+"/pT_Z/"+ProcessName,pt_z,weight,50,0.,100.);
  FillHist(cutname+"/pT_Z_b/"+ProcessName,pt_zb,weight,50,0.,100.);
  FillHist(cutname+"/M_Z/"+ProcessName,myRECO.mZ,weight,30,60.,120.);

  if (ZllChannel!=""){
    
    FillHist(cutname+"_"+ZllChannel+"/M_Z_nosf/"+ProcessName,myRECO.mZ,base_weight,30,60.,120.);
    FillHist(cutname+"_"+ZllChannel+"/M_Z_after_PUW/"+ProcessName,myRECO.mZ,base_weight*puweight,30,60.,120.);
    FillHist(cutname+"_"+ZllChannel+"/M_Z_after_PREFIREW/"+ProcessName,myRECO.mZ,base_weight*puweight*prefire_weight,30,60.,120.);
    FillHist(cutname+"_"+ZllChannel+"/M_Z_after_TRIGSF/"+ProcessName,myRECO.mZ,base_weight*puweight*prefire_weight*trigsf,30,60.,120.);
    FillHist(cutname+"_"+ZllChannel+"/M_Z_after_TRKSF/"+ProcessName,myRECO.mZ,base_weight*puweight*prefire_weight*mu_trksf,30,60.,120.);
    FillHist(cutname+"_"+ZllChannel+"/M_Z_after_RECOSF/"+ProcessName,myRECO.mZ,base_weight*puweight*prefire_weight*mu_trksf*lep_recosf,30,60.,120.);
    FillHist(cutname+"_"+ZllChannel+"/M_Z_after_IDSF/"+ProcessName,myRECO.mZ,base_weight*puweight*prefire_weight*mu_trksf*lep_recosf*lep_idsf,30,60.,120.);

    FillHist(cutname+"_"+ZllChannel+"/M_Z_after_BTAGSF/"+ProcessName,myRECO.mZ,base_weight*puweight*prefire_weight*mu_trksf*lep_recosf*lep_idsf*btagsf,30,60.,120.);



  }

}


void HZZ_test::FillHistBMuon(TString cutname){
  if(IsTreeMode) return;
  FillHist(cutname+"/bmuon_dnn/"+ProcessName,bmuon1_DNN,weight,100,0.,1.);
  FillHist(cutname+"/bmuon_charge/"+ProcessName,bmuon1_charge,weight,100,-2.,2.);
  FillHist(cutname+"/bmuon_charge_weighted/"+ProcessName,bmuon1_charge*bmuon1_DNN,weight,100,-2.,2.);

  FillHist(cutname+"/bmuon_phi/"+ProcessName,bmuon_phi,weight,40,-4.,4.);
  FillHist(cutname+"/bmuon_pt/"+ProcessName,bmuon_pt,weight,50,0.,50.);
  FillHist(cutname+"/bmuon_nsip3d/"+ProcessName,bmuon_nsip3d,weight,15,0.,15.);
  FillHist(cutname+"/bmuon_ptwrtbjet/"+ProcessName,bmuon_ptwrtbjet,weight,20,0.,5.);
  FillHist(cutname+"/bmuon_eta/"+ProcessName,bmuon_eta,weight,40,-4.,4.);
  FillHist(cutname+"/bmuon_p_jetrestf/"+ProcessName,bmuon_p_jetrestf,weight,20,0.,5.);
  FillHist(cutname+"/bmuon_reltrkiso/"+ProcessName,bmuon_reltrkiso,weight,30,0.,15.);
  FillHist(cutname+"/bmuon_dR_l_j/"+ProcessName,bmuon_dR_l_j,weight,40,0.,0.4);
}


void HZZ_test::FillHistBElectron(TString cutname){
  if(IsTreeMode) return;
  FillHist(cutname+"/belectron_dnn/"+ProcessName,belectron1_DNN,weight,100,0.,1.);
  FillHist(cutname+"/belectron_charge/"+ProcessName,belectron1_charge,weight,100,-2.,2.);
  FillHist(cutname+"/belectron_charge_weighted/"+ProcessName,belectron1_charge*belectron1_DNN,weight,100,-2.,2.);

  FillHist(cutname+"/belectron_phi/"+ProcessName,belectron_phi,weight,40,-4.,4.);
  FillHist(cutname+"/belectron_pt/"+ProcessName,belectron_pt,weight,50,0.,50.);
  FillHist(cutname+"/belectron_nsip3d/"+ProcessName,belectron_nsip3d,weight,15,0.,15.);
  FillHist(cutname+"/belectron_ptwrtbjet/"+ProcessName,belectron_ptwrtbjet,weight,20,0.,5.);
  FillHist(cutname+"/belectron_eta/"+ProcessName,belectron_eta,weight,40,-4.,4.);
  FillHist(cutname+"/belectron_p_jetrestf/"+ProcessName,belectron_p_jetrestf,weight,20,0.,5.);
  FillHist(cutname+"/belectron_reltrkiso/"+ProcessName,belectron_reltrkiso,weight,30,0.,15.);
  FillHist(cutname+"/belectron_dR_l_j/"+ProcessName,belectron_dR_l_j,weight,40,0.,0.4);
  FillHist(cutname+"/belectron_IsGsfCtfScPixChargeConsistent/"+ProcessName,belectron_IsGsfCtfScPixChargeConsistent,weight,2,0.,2.);
}






void HZZ_test::executeEvent(){
  //jhchoi//

  ev = GetEvent();
  //FillHist("event_start",1, weight, 1, 0, 1);
  isEvenEvent=((event%2)==0);
  //---initialize--//
  //EventTag="";
  //EventTagJetParton="";
  ZllChannel="";
  IncomingPartonTag="";
  doPrint=false;
  weight=1.;//init event weight
  base_weight=1.;
  myRECO.goodZZmmmm=false;
  myRECO.goodZZmmee=false;
  myRECO.goodZZeeee=false;
  //SF
  trigsf=1.;
  mu_trigsf=1.;
  el_trigsf=1.;

  lep_recosf=1.;
  mu_recosf=1.;
  el_recosf=1.;

  lep_idsf=1.;
  mu_idsf=1.;
  el_idsf=1.;

  mu_trksf=1.;

  btagsf=1.;

  MET = ev.GetMETVector().Pt();


  prefire_weight=GetPrefireWeight(0);
  weight*=prefire_weight;
  //nPV
  puweight=GetPileUpWeight(nPileUp,0);
  weight*=puweight;
  if(!IsDATA){
    base_weight*=MCweight();
    base_weight*=ev.GetTriggerLumi("Full");
    weight *= MCweight();
    weight *= ev.GetTriggerLumi("Full");
  }
  //initialize//

  
  //doFillTree=false;
  StoreEvent=false;
  FillCutflow("cutflow/all/"+ProcessName,"event_start",weight);
  FillHist("event_start/cutflow/"+ProcessName,1, weight, 2, 0, 2);
  HZZ_test::AnalyzeLHE();
  HZZ_test::AnalyzeRECO();
      
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
