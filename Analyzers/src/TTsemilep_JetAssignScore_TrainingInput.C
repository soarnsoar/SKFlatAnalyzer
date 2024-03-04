#include "TTsemilep_JetAssignScore_TrainingInput.h"
#include <stdlib.h>
#include <stdio.h>

TTsemilep_JetAssignScore_TrainingInput::TTsemilep_JetAssignScore_TrainingInput(){//
  
  //doReduction=false;
  doDebug=false;
  DNNcut=0.5;



}
TTsemilep_JetAssignScore_TrainingInput::~TTsemilep_JetAssignScore_TrainingInput(){

  //==== Destructor of this Analyzer
  cout << "nevt=" << nevt << endl;
  cout << "nevt_samebb=" << nevt_samebb << endl;
}


void TTsemilep_JetAssignScore_TrainingInput::InitValues(){
  
  //-----Variables to Store for Machine Learning------//
  /*
    ->met pt,phi
    ->lep pt,eta,phi(e/mu)
    ->bjet pt,eta,phi
    ->b~jet pt,eta,phi
    ->light q jet pt,eta,phi
    ->light q' jet pt,eta,phi
  */

  met_pt=0,met_phi=0;
  electron_pt=0,electron_phi=0,electron_eta=0;
  muon_pt=0,muon_phi=0,muon_eta=0;
  blep_pt=0,blep_phi=0,blep_eta=0,blep_E=0;
  bhad_pt=0,bhad_phi=0,bhad_eta=0,bhad_E=0;
  //q1,q2 -> pt order
  q1jet_pt=0,q1jet_eta=0, q1jet_phi=0, q1jet_E=0;
  q2jet_pt=0,q2jet_eta=0, q2jet_phi=0, q2jet_E=0;

  //masses
  WhadCand_mass=0;
  ThadCand_mass=0;
  //
  IsSig=0;
  IsBkg=0;
}



void TTsemilep_JetAssignScore_TrainingInput::initializeAnalyzer(){
  nevt=0., nevt_samebb=0.;
  cout << "[initialize DNN models]" << endl;
  SKFLAT_WD=getenv("SKFlat_WD");

  doReduction = HasFlag("doReduction");
  

  jhchoi_newtree=new TTree("ForMuon_Sig","ForMuon_Sig");
  jhchoi_newtree->Branch("event",&event);
  jhchoi_newtree->Branch("weight",&weight);

  jhchoi_newtree->Branch("met_pt",&met_pt);
  jhchoi_newtree->Branch("met_phi",&met_phi);

  jhchoi_newtree->Branch("electron_pt",&electron_pt);
  jhchoi_newtree->Branch("electron_eta",&electron_eta);
  jhchoi_newtree->Branch("electron_phi",&electron_phi);

  jhchoi_newtree->Branch("muon_pt",&muon_pt);
  jhchoi_newtree->Branch("muon_eta",&muon_eta);
  jhchoi_newtree->Branch("muon_phi",&muon_phi);

  jhchoi_newtree->Branch("blep_pt",&blep_pt);
  jhchoi_newtree->Branch("blep_eta",&blep_eta);
  jhchoi_newtree->Branch("blep_phi",&blep_phi);
  jhchoi_newtree->Branch("blep_E",&blep_E);

  jhchoi_newtree->Branch("bhad_pt",&bhad_pt);
  jhchoi_newtree->Branch("bhad_eta",&bhad_eta);
  jhchoi_newtree->Branch("bhad_phi",&bhad_phi);
  jhchoi_newtree->Branch("bhad_E",&bhad_E);

  jhchoi_newtree->Branch("q1jet_pt",&q1jet_pt);
  jhchoi_newtree->Branch("q1jet_eta",&q1jet_eta);
  jhchoi_newtree->Branch("q1jet_phi",&q1jet_phi);
  jhchoi_newtree->Branch("q1jet_E",&q1jet_E);

  jhchoi_newtree->Branch("q2jet_pt",&q2jet_pt);
  jhchoi_newtree->Branch("q2jet_eta",&q2jet_eta);
  jhchoi_newtree->Branch("q2jet_phi",&q2jet_phi);
  jhchoi_newtree->Branch("q2jet_E",&q2jet_E);

  jhchoi_newtree->Branch("WhadCand_mass",&WhadCand_mass);
  jhchoi_newtree->Branch("ThadCand_mass",&ThadCand_mass);



  jhchoi_newtree2=new TTree("ForMuon_Bkg","ForMuon_Bkg");
  jhchoi_newtree2->Branch("event",&event);
  jhchoi_newtree2->Branch("weight",&weight);

  jhchoi_newtree2->Branch("met_pt",&met_pt);
  jhchoi_newtree2->Branch("met_phi",&met_phi);

  jhchoi_newtree2->Branch("electron_pt",&electron_pt);
  jhchoi_newtree2->Branch("electron_eta",&electron_eta);
  jhchoi_newtree2->Branch("electron_phi",&electron_phi);

  jhchoi_newtree2->Branch("muon_pt",&muon_pt);
  jhchoi_newtree2->Branch("muon_eta",&muon_eta);
  jhchoi_newtree2->Branch("muon_phi",&muon_phi);

  jhchoi_newtree2->Branch("blep_pt",&blep_pt);
  jhchoi_newtree2->Branch("blep_eta",&blep_eta);
  jhchoi_newtree2->Branch("blep_phi",&blep_phi);
  jhchoi_newtree2->Branch("blep_E",&blep_E);

  jhchoi_newtree2->Branch("bhad_pt",&bhad_pt);
  jhchoi_newtree2->Branch("bhad_eta",&bhad_eta);
  jhchoi_newtree2->Branch("bhad_phi",&bhad_phi);
  jhchoi_newtree2->Branch("bhad_E",&bhad_E);

  jhchoi_newtree2->Branch("q1jet_pt",&q1jet_pt);
  jhchoi_newtree2->Branch("q1jet_eta",&q1jet_eta);
  jhchoi_newtree2->Branch("q1jet_phi",&q1jet_phi);
  jhchoi_newtree2->Branch("q1jet_E",&q1jet_E);

  jhchoi_newtree2->Branch("q2jet_pt",&q2jet_pt);
  jhchoi_newtree2->Branch("q2jet_eta",&q2jet_eta);
  jhchoi_newtree2->Branch("q2jet_phi",&q2jet_phi);
  jhchoi_newtree2->Branch("q2jet_E",&q2jet_E);

  jhchoi_newtree2->Branch("WhadCand_mass",&WhadCand_mass);
  jhchoi_newtree2->Branch("ThadCand_mass",&ThadCand_mass);




  jhchoi_newtree3=new TTree("ForElectron_Sig","ForMuon_Sig");
  jhchoi_newtree3->Branch("event",&event);
  jhchoi_newtree3->Branch("weight",&weight);

  jhchoi_newtree3->Branch("met_pt",&met_pt);
  jhchoi_newtree3->Branch("met_phi",&met_phi);

  jhchoi_newtree3->Branch("electron_pt",&electron_pt);
  jhchoi_newtree3->Branch("electron_eta",&electron_eta);
  jhchoi_newtree3->Branch("electron_phi",&electron_phi);

  jhchoi_newtree3->Branch("muon_pt",&muon_pt);
  jhchoi_newtree3->Branch("muon_eta",&muon_eta);
  jhchoi_newtree3->Branch("muon_phi",&muon_phi);

  jhchoi_newtree3->Branch("blep_pt",&blep_pt);
  jhchoi_newtree3->Branch("blep_eta",&blep_eta);
  jhchoi_newtree3->Branch("blep_phi",&blep_phi);
  jhchoi_newtree3->Branch("blep_E",&blep_E);

  jhchoi_newtree3->Branch("bhad_pt",&bhad_pt);
  jhchoi_newtree3->Branch("bhad_eta",&bhad_eta);
  jhchoi_newtree3->Branch("bhad_phi",&bhad_phi);
  jhchoi_newtree3->Branch("bhad_E",&bhad_E);

  jhchoi_newtree3->Branch("q1jet_pt",&q1jet_pt);
  jhchoi_newtree3->Branch("q1jet_eta",&q1jet_eta);
  jhchoi_newtree3->Branch("q1jet_phi",&q1jet_phi);
  jhchoi_newtree3->Branch("q1jet_E",&q1jet_E);

  jhchoi_newtree3->Branch("q2jet_pt",&q2jet_pt);
  jhchoi_newtree3->Branch("q2jet_eta",&q2jet_eta);
  jhchoi_newtree3->Branch("q2jet_phi",&q2jet_phi);
  jhchoi_newtree3->Branch("q2jet_E",&q2jet_E);

  jhchoi_newtree3->Branch("WhadCand_mass",&WhadCand_mass);
  jhchoi_newtree3->Branch("ThadCand_mass",&ThadCand_mass);


  jhchoi_newtree4=new TTree("ForElectron_Bkg","ForMuon_Bkg");
  jhchoi_newtree4->Branch("event",&event);
  jhchoi_newtree4->Branch("weight",&weight);

  jhchoi_newtree4->Branch("met_pt",&met_pt);
  jhchoi_newtree4->Branch("met_phi",&met_phi);

  jhchoi_newtree4->Branch("electron_pt",&electron_pt);
  jhchoi_newtree4->Branch("electron_eta",&electron_eta);
  jhchoi_newtree4->Branch("electron_phi",&electron_phi);

  jhchoi_newtree4->Branch("muon_pt",&muon_pt);
  jhchoi_newtree4->Branch("muon_eta",&muon_eta);
  jhchoi_newtree4->Branch("muon_phi",&muon_phi);

  jhchoi_newtree4->Branch("blep_pt",&blep_pt);
  jhchoi_newtree4->Branch("blep_eta",&blep_eta);
  jhchoi_newtree4->Branch("blep_phi",&blep_phi);
  jhchoi_newtree4->Branch("blep_E",&blep_E);

  jhchoi_newtree4->Branch("bhad_pt",&bhad_pt);
  jhchoi_newtree4->Branch("bhad_eta",&bhad_eta);
  jhchoi_newtree4->Branch("bhad_phi",&bhad_phi);
  jhchoi_newtree4->Branch("bhad_E",&bhad_E);

  jhchoi_newtree4->Branch("q1jet_pt",&q1jet_pt);
  jhchoi_newtree4->Branch("q1jet_eta",&q1jet_eta);
  jhchoi_newtree4->Branch("q1jet_phi",&q1jet_phi);
  jhchoi_newtree4->Branch("q1jet_E",&q1jet_E);

  jhchoi_newtree4->Branch("q2jet_pt",&q2jet_pt);
  jhchoi_newtree4->Branch("q2jet_eta",&q2jet_eta);
  jhchoi_newtree4->Branch("q2jet_phi",&q2jet_phi);
  jhchoi_newtree4->Branch("q2jet_E",&q2jet_E);

  jhchoi_newtree4->Branch("WhadCand_mass",&WhadCand_mass);
  jhchoi_newtree4->Branch("ThadCand_mass",&ThadCand_mass);


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
  cout << "[TTsemilep_JetAssignScore_TrainingInput::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;



  std::vector<JetTagging::Parameters> jtps;
  //==== If you want to use 1a or 2a method,
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Tight, JetTagging::incl, JetTagging::comb) );
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Loose, JetTagging::incl, JetTagging::comb) );
  //==== set
  mcCorr->SetJetTaggingParameters(jtps);
  jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  jtp_loose=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Loose,JetTagging::incl,JetTagging::comb);


  if(DataYear==2017){
    MuonTriggerNames = {"HLT_IsoMu24_v","HLT_IsoMu27_v"};
    MuonTriggerSFKeys={"IsoMu24_MediumID_trkIsoLoose","IsoMu27_MediumID_trkIsoLoose"};
    ElectronTriggerNames = {"HLT_Ele27_WPTight_Gsf_v","HLT_Ele32_WPTight_Gsf_v"};
    ElectronTriggerSFKeys = {"Ele27_MediumID","Ele32_MediumID"};
    TriggerSafeCut_muon = 30.;
    TriggerSafeCut_electron = 35.;

    MuonID="Muon_MediumID_trkIsoLoose";
    ElectronID="Electron_MediumID";

  }
  
}
void TTsemilep_JetAssignScore_TrainingInput::AnalyzeLHE(){
  
  // == init
  myLHE.IsMuonChannel=false;
  myLHE.IsElectronChannel=false;
  myLHE.IsTauChannel=false;
  myLHE.LeptonCharge=0;
  //=========
  int LHEsize = LHEs.size();
  //cout << "LHEsize=" << LHEsize << endl;
  
  int status=-999, pid=-999;
  //double pz=-999,E=-999, charge=-999;
  //cout << "i" << setw(15) << "pid" << setw(15) << "status"  << endl;
  int n_light_quark=0;
  //--Check Lepton--//
  for(int i = 0; i < LHEsize; i++) {
    status=LHEs[i].Status();
    pid=LHEs[i].ID();
    //pz=LHEs[i].Pz();
    //E=LHEs[i].E();
    //charge=LHEs[i].Charge();
    //cout << i << setw(15) << pid << setw(15) << status << endl;
    if(status==1){
      if(pid == 11){
	myLHE.LeptonCharge = -1; myLHE.IsElectronChannel=true; 
	break;
      }
      else if(pid == -11){
	myLHE.LeptonCharge = +1; myLHE.IsElectronChannel=true; 
	break;
      }
      else if(pid == 13){
	myLHE.LeptonCharge = -1; myLHE.IsMuonChannel=true;
	break;
      }
      else if(pid == -13){
	myLHE.LeptonCharge = 1; myLHE.IsMuonChannel=true;
	break;
      }
      else if(pid == 15){
	myLHE.LeptonCharge = -1; myLHE.IsTauChannel=true;
	break;
      }
      else if(pid == -15){
	myLHE.LeptonCharge = 1; myLHE.IsTauChannel=true;
	break;
      }
      if ( abs(pid)<5) n_light_quark+=1;
    }
  }

  myLHE.bLep_charge = -myLHE.LeptonCharge;
  //cout << "i" << setw(15) << "pid" << setw(15) << "status"  << endl;
  for(int i = 0; i < LHEsize; i++) {
    status=LHEs[i].Status();
    pid=LHEs[i].ID();
    //pz=LHEs[i].Pz();
    //E=LHEs[i].E();
    //charge=LHEs[i].Charge();
    //cout << i << setw(15) << pid << setw(15) << status << endl;
  }
}

void TTsemilep_JetAssignScore_TrainingInput::AnalyzeGEN(){
  GENs=GetGens();
  LightJetsTruePIDs.clear();
  unsigned int GENsize = GENs.size();
  int nlightquark_mother_not_status21=0;
  int idx_bquark=-1, idx_bbarquark=-1;
  //cout << "i" << setw(15) << "pid" << setw(15) << "status" << setw(15) << "mother" << setw(15) << "isHardProcess" << endl;
  vector<int> idx_lightquark;
  for(unsigned int i = 0 ; i < GENsize ; i++){
    int pid=GENs[i].PID();
    int status=GENs[i].Status();
    int mother=GENs[i].MotherIndex();
    int isHardProcess=GENs[i].isHardProcess();
    //if(isHardProcess) cout << i << setw(15) << pid << setw(15) << status << setw(15) << mother << setw(15) << isHardProcess << endl;
    if (isHardProcess && (status!=21) && GENs[mother].Status()!=21 && abs(pid)<5) {
      nlightquark_mother_not_status21+=1;
      idx_lightquark.push_back(i);
    }
    if (isHardProcess && (status!=21)){
      if(pid==5){
	idx_bquark=i;
      }
      else if(pid==-5){
	idx_bbarquark=i;
      }
    }

  }
  //    TLorentzVector vWhad;
  //  TLorentzVector vThad;

  myGEN.vWhad.SetPxPyPzE(0,0,0,0);
  myGEN.vThad.SetPxPyPzE(0,0,0,0);
  for(unsigned int i = 0 ; i < idx_lightquark.size(); i++){
    myGEN.vWhad+=GENs[idx_lightquark[i]];
    myGEN.vThad+=GENs[idx_lightquark[i]];
  }
  if(myLHE.bLep_charge>0){//b from THad_charge<0 -> bquark
    myGEN.vThad+=GENs[idx_bquark];
    //idx_bbarqurk
  }
  else{
    myGEN.vThad+=GENs[idx_bbarquark];
  }
  myGEN.Whad_q1_pid=GENs[idx_lightquark[0]].PID();
  myGEN.Whad_q2_pid=GENs[idx_lightquark[1]].PID();
  FillHist("Whad_quark_pid_GEN/all/"+ProcessName,myGEN.Whad_q1_pid, weight, 32, -7, 25);
  FillHist("Whad_quark_pid_GEN/all/"+ProcessName,myGEN.Whad_q2_pid, weight, 32, -7, 25);


  myGEN.Whad_q1_genidx=idx_lightquark[0];
  myGEN.Whad_q2_genidx=idx_lightquark[1];
  double mWhad_gen=myGEN.vWhad.M();
  double mThad_gen=myGEN.vThad.M();
  FillHist("M_Whad_GEN/all/"+ProcessName,mWhad_gen, weight, 150, 0, 150);
  FillHist("M_Thad_GEN/all/"+ProcessName,mThad_gen, weight, 300, 0, 300);
  FillHist("N_lightquark_GEN/all/"+ProcessName,nlightquark_mother_not_status21, weight, 10, 0, 10);

  //Check exception//
  if(nlightquark_mother_not_status21==2) return;
  FillHist("N_lightquark_GEN/nLightQuarkNotISR__not_2/"+ProcessName,nlightquark_mother_not_status21, weight, 10, 0, 10);
  //cout << "i" << setw(15) << "pid" << setw(15) << "status" << setw(15) << "mother" << setw(15) << "isHardProcess" << endl;
  //for(unsigned int i = 0 ; i < GENsize ; i++){
  //  int pid=GENs[i].PID();
  //  int status=GENs[i].Status();
  //  int mother=GENs[i].MotherIndex();
  // int isHardProcess=GENs[i].isHardProcess();
    //if(isHardProcess) cout << i << setw(15) << pid << setw(15) << status << setw(15) << mother << setw(15) << isHardProcess << endl;
  //}

}



bool TTsemilep_JetAssignScore_TrainingInput::TTbarMuReco(){

  //Tag only 1 muon 
  vector<int> idx_Tmuon;
  vector<Muon> v_Tmuon;
  //double this_leptonid_sf=1.;
  //double this_trigger_sf=1.;
  //double this_iso_sf=1.;

  //int i_l1=-1;

  //Because roch. corr. need to find leading pt muon again.
  double maxpt=-100.;
  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double pt=AllMuons[i].Pt();
    double eta=AllMuons[i].Eta();
    bool passID=AllMuons[i].PassID("POGLoose");
    bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    //double reliso=AllMuons[i].RelIso();
    if(fabs(eta) > 2.5) continue;
    if(pt <15) continue;
    if (!passID) continue;
    if (!passISO) continue;
    //if(reliso>0.15) continue;//reliso0.15
    if (pt > maxpt) {
      maxpt=pt;
      //i_l1=i;
    }

    idx_Tmuon.push_back(i);
    v_Tmuon.push_back(AllMuons[i]);

  }


  if (idx_Tmuon.size()!=1) return 0;
  if (!AllMuons[idx_Tmuon[0]].PassID("POGMedium")) return 0 ;
  if (maxpt < 20.) return 0;
  if(!IsDATA) {
    //this_leptonid_sf=1.;
    //this_iso_sf=1.;
    //this_trigger_sf=1.;
    vector<Lepton*> leps=MakeLeptonPointerVector(v_Tmuon);
    
    //mu_trigsf=GetLeptonTriggerORSF(ev, MuonTriggerNames, MuonTriggerSFKeys, leps,0,0,"");
    Lepton* _mu1=leps.at(0);
    mu_recosf=fEff->GetEfficiencySF("Muon_RECO",_mu1,0,0);
    mu_idsf=fEff->GetEfficiencySF("Muon_MediumID_trkIsoLoose",_mu1,0,0);
    mu_trksf=fEff->GetEfficiencySF("Muon_Tracking",_mu1,0,0);
  }
  //Now Muon is ready
  //PuppiMET_pt
  
  myRECO.idx_Tmuon=idx_Tmuon[0];
  return 1;

}

bool TTsemilep_JetAssignScore_TrainingInput::TTbarElReco(){

  //Tag only 1 electron 
  vector<int> idx_Telectron;
  vector<Electron> v_Telectron;
  //double this_leptonid_sf=1.;
  //double this_trigger_sf=1.;
  //double this_iso_sf=1.;


  //Because roch. corr. need to find leading pt electron again.

  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=AllElectrons[i].Pt();
    double eta=AllElectrons[i].Eta();
    bool passID=AllElectrons[i].PassID("passLooseID");
    //double reliso=AllElectrons[i].RelIso();
    if(fabs(eta) > 2.5) continue;
    if(pt < 15) continue;
    if (!passID) continue;

    idx_Telectron.push_back(i);
    v_Telectron.push_back(AllElectrons[i]);

  }
  if (idx_Telectron.size()!=1) return 0;
  if (!AllElectrons[idx_Telectron[0]].PassID("passMediumID")) return 0 ;
  if (AllElectrons[idx_Telectron[0]].Pt() < 20) return 0;
  if(!IsDATA) {
    vector<Lepton*> leps=MakeLeptonPointerVector(v_Telectron);
    Lepton* _el1=leps.at(0);
    //el_trigsf=GetLeptonTriggerORSF(ev,ElectronTriggerNames, ElectronTriggerSFKeys, leps,0,0,"");
    el_recosf=fEff->GetEfficiencySF("Electron_RECO",_el1,0,0);
    el_idsf=fEff->GetEfficiencySF("Electron_MediumID",_el1,0,0) ;

  }
  //Now Electron is ready
  //PuppiMET_pt
  
  myRECO.idx_Telectron=idx_Telectron[0];
  return 1;

}




void TTsemilep_JetAssignScore_TrainingInput::CollectJets(){
  //cout << "<CollectJets>" << endl;
  double btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
  //double bveto_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Loose);
  Nb=0;
  Nbbar=0;
  tightjets.clear();
  myRECO.idx_bjet=-1;
  myRECO.idx_bbarjet=-1;
  
  l1.SetPxPyPzE(0,0,0,0);
  //TLorentzVector l1;
  if(myLHE.IsMuonChannel){
    l1=AllMuons[myRECO.idx_Tmuon];
  }
  else if(myLHE.IsElectronChannel){
    l1=AllElectrons[myRECO.idx_Telectron];
  }
  else{
    return;
  }
  //cout << "jetsize=" << jetsize << endl;
  // -- collect tight jets//
  for(unsigned int i = 0 ; i < jetsize; i ++){
    if(AllJets[i].Pt() < 30.) continue;
    if(fabs(AllJets[i].Eta()) > 2.4) continue;
    if(AllJets[i].DeltaR(l1)<0.4) continue;
    if(!AllJets[i].PassID("tightLepVeto")) continue; //old : tight
    double btag_score=AllJets[i].GetTaggerResult(JetTagging::DeepJet);    
    if(AllJets[i].partonFlavour()==5 && btag_score>btag_cut){
      Nb+=1;
      myRECO.idx_bjet=i;
    }
    else if(AllJets[i].partonFlavour()==-5 && btag_score>btag_cut){
      Nbbar+=1;
      myRECO.idx_bbarjet=i;
    }
    else if( abs(AllJets[i].partonFlavour()) !=5 && btag_score<btag_cut){
      tightjets.push_back(AllJets[i]);
    }
  }//end of jet loop
  tightjetsize=tightjets.size();
  //cout << "tightjetsize=" << tightjetsize << endl;
}

  
void TTsemilep_JetAssignScore_TrainingInput::FlavourAndDeltaR_Matching(){

  Is_q1match=false;
  Is_q2match=false;
  int tightjetidx_q1_match=-1;
  int tightjetidx_q2_match=-1;

  N_light_quark_jet=0;
  N_gluon_jet=0;

  int N_q1match=0;
  int N_q2match=0;


  for(unsigned int i = 0 ; i < tightjetsize ; i ++){
    if(fabs(tightjets[i].partonFlavour()) < 5) N_light_quark_jet+=1;
    if(tightjets[i].partonFlavour() == 21) N_gluon_jet+=1;
    //dR1,flavour1 matching


    double _dR1=tightjets[i].DeltaR(GENs[myGEN.Whad_q1_genidx]);
    bool _flavourmatch1=(tightjets[i].partonFlavour()==myGEN.Whad_q1_pid);
    if(_flavourmatch1 && (_dR1<0.4)) N_q1match+=1;
    double _dR2=tightjets[i].DeltaR(GENs[myGEN.Whad_q2_genidx]);
    bool _flavourmatch2=(tightjets[i].partonFlavour()==myGEN.Whad_q2_pid);
    if(_flavourmatch2 && (_dR2<0.4)) N_q2match+=1;


    if(!Is_q1match){
      if(_flavourmatch1 && (_dR1<0.4)) {
	Is_q1match=true;
	tightjetidx_q1_match=i;
      }
      if(Is_q1match) continue;
    }
    if(!Is_q2match){

      if(_flavourmatch2 && (_dR2<0.4)){
	Is_q2match=true;
	tightjetidx_q2_match=i;
      }
      if(Is_q2match) continue;
    }

    
  }//end of tightljetloop
  FillHist("Event_with_b1_b2/N_q1match_10_N_q2match/"+ProcessName,N_q1match+10*N_q2match, weight, 50, 0, 50);


  if(tightjetidx_q1_match!=-1 && tightjetidx_q2_match!=-1){
    FillCutflow("cutflow/"+ProcessName,"Flavour_dR_Match_Whad_q1q2",weight);
    TLorentzVector Whad, Thad;
    Whad=tightjets[tightjetidx_q1_match] + tightjets[tightjetidx_q2_match];
    if(myLHE.bLep_charge>0){//bHad_charge<0  ---> idx_bjet
      Thad=Whad+AllJets[myRECO.idx_bjet];
    }
    else{
      Thad=Whad+AllJets[myRECO.idx_bbarjet];
    }

    FillHist("Event_with_b1_b2/Whad_mass_q1q2_flav_dR_match/"+ProcessName,Whad.M(), weight, 100, 0, 200);
    FillHist("Event_with_b1_b2/Thad_mass_q1q2_flav_dR_match/"+ProcessName,Thad.M(), weight, 100, 0, 300);
    FillHist("Event_with_b1_b2/Whad_genmass_q1q2_flav_dR_match/"+ProcessName,myGEN.vWhad.M(), weight, 100, 0, 200);
    FillHist("Event_with_b1_b2/Thad_genmass_q1q2_flav_dR_match/"+ProcessName,myGEN.vThad.M(), weight, 100, 0, 300);
    if((fabs(GENs[myGEN.Whad_q1_genidx].Eta())<2.4 && GENs[myGEN.Whad_q1_genidx].Pt()>30) &&
       ((fabs(GENs[myGEN.Whad_q2_genidx].Eta())<2.4 && GENs[myGEN.Whad_q2_genidx].Pt()>30))){
      FillCutflow("cutflow/"+ProcessName,"GEN_eta_ptcut_Flavour_Match_Whad_q1q2",weight);
      FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/Whad_mass_q1q2_flav_dR_match/"+ProcessName,Whad.M(), weight, 100, 0, 200);
      FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/Thad_mass_q1q2_flav_dR_match/"+ProcessName,Thad.M(), weight, 100, 0, 300);
      FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/Whad_genmass_q1q2_flav_dR_match/"+ProcessName,myGEN.vWhad.M(), weight, 100, 0, 200);
      FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/Thad_genmass_q1q2_flav_dR_match/"+ProcessName,myGEN.vThad.M(), weight, 100, 0, 300);
    }
      
  }//if all matched

}

void TTsemilep_JetAssignScore_TrainingInput::FlavourMatchingOnly(){
  //cout << "<FlavourMatchingOnly>" << endl;
  flavourmatch1=false;
  flavourmatch2=false;
  tightjetidx_q1_flav_match= -1 ;
  tightjetidx_q2_flav_match= -1 ;
  //cout << "tightjetidx_q1_flav_match=" << tightjetidx_q1_flav_match << endl;
  N_flavour_match1=0;
  N_flavour_match2=0;
  for(unsigned int i = 0 ; i < tightjetsize ; i ++){
    //dR1,flavour1 matching
    bool _flavourmatch1=(tightjets[i].partonFlavour()==myGEN.Whad_q1_pid);
    bool _flavourmatch2=(tightjets[i].partonFlavour()==myGEN.Whad_q2_pid);
    if(_flavourmatch1) N_flavour_match1+=1;
    if(_flavourmatch2) N_flavour_match2+=1;
    if(!flavourmatch1){
      if(_flavourmatch1){
	flavourmatch1=true;
	tightjetidx_q1_flav_match=i;
	continue;
      }
    }

    if(!flavourmatch2){
     
      if(_flavourmatch2){
	flavourmatch2=true;
	tightjetidx_q2_flav_match=i;
	continue;
      }
    }
  }//---end of for loop

  
  if(tightjetidx_q1_flav_match!=-1 && tightjetidx_q2_flav_match!=-1){//Find all matched tightjet
    FillCutflow("cutflow/"+ProcessName,"Flavour_Match_Whad_q1q2",weight);
    TLorentzVector Whad, Thad;
    Whad=tightjets[tightjetidx_q1_flav_match] + tightjets[tightjetidx_q2_flav_match];
    if(myLHE.bLep_charge>0){//bHad_charge<0  ---> idx_bjet
      Thad=Whad+AllJets[myRECO.idx_bjet];
    }
    else{
      Thad=Whad+AllJets[myRECO.idx_bbarjet];
    }
    
    FillHist("Event_with_b1_b2/Whad_mass_q1q2_flavour_match/"+ProcessName,Whad.M(), weight, 100, 0, 200);
    FillHist("Event_with_b1_b2/Thad_mass_q1q2_flavour_match/"+ProcessName,Thad.M(), weight, 100, 0, 300);
    //myGEN.vWhad.M
    FillHist("Event_with_b1_b2/Whad_genmass_q1q2_flavour_match/"+ProcessName,myGEN.vWhad.M(), weight, 100, 0, 200);
    FillHist("Event_with_b1_b2/Thad_genmass_q1q2_flavour_match/"+ProcessName,myGEN.vThad.M(), weight, 100, 0, 300);
    if((fabs(GENs[myGEN.Whad_q1_genidx].Eta())<2.4 && GENs[myGEN.Whad_q1_genidx].Pt()>30) &&
       ((fabs(GENs[myGEN.Whad_q2_genidx].Eta())<2.4 && GENs[myGEN.Whad_q2_genidx].Pt()>30))){
      FillCutflow("cutflow/"+ProcessName,"GEN_eta_ptcut_Flavour_Match_Whad_q1q2",weight);
      FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/Whad_mass_q1q2_flavour_match/"+ProcessName,Whad.M(), weight, 100, 0, 200);
      FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/Thad_mass_q1q2_flavour_match/"+ProcessName,Thad.M(), weight, 100, 0, 300);

      FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/Whad_genmass_q1q2_flavour_match/"+ProcessName,myGEN.vWhad.M(), weight, 100, 0, 200);
      FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/Thad_genmass_q1q2_flavour_match/"+ProcessName,myGEN.vThad.M(), weight, 100, 0, 300);
    }
    
    
  }
  
}

bool TTsemilep_JetAssignScore_TrainingInput::CheckJets(){
  FillCutflow("cutflow/"+ProcessName,"Without_bMatch",weight);
  FillHist("Without_bMatch/Event/"+ProcessName,1, weight, 4, -1, 3);


  TTsemilep_JetAssignScore_TrainingInput::CollectJets();
  if(myRECO.idx_bjet < 0 || myRECO.idx_bbarjet < 0 ) {
    //cout << "No bjets!" << endl;
    return 0;
  }
  if(Nb!=1) return 0;
  if(Nbbar!=1) return 0;
  if (tightjetsize < 2) return 0;
  FillCutflow("cutflow/"+ProcessName,"light_tightjet_size_over_2",weight);
  //cout << " tightjetsize should over 1 = " << tightjetsize << endl;
  TTsemilep_JetAssignScore_TrainingInput::FlavourAndDeltaR_Matching();
  TTsemilep_JetAssignScore_TrainingInput::FlavourMatchingOnly();
  
  //cout << "[after flavour jet matching]]tightjetidx_q1_flav_match=" << tightjetidx_q1_flav_match << endl;
  
  FillHist("Event_with_b1_b2/N_flavour_match1_10_N_flavour_match2/"+ProcessName,N_flavour_match1+10*N_flavour_match2, weight, 50, 0, 50);
  FillHist("Event_with_b1_b2/Whad_q1_q2_match/"+ProcessName,Is_q1match*Is_q2match, weight, 4, -1, 3);
  FillHist("Event_with_b1_b2/Whad_q1_q2_match_flavour_only/"+ProcessName,flavourmatch1&&flavourmatch2, weight, 4, -1, 3);
  FillHist("Event_with_b1_b2/nTightJet/"+ProcessName,tightjetsize, weight, 10, 0, 10);
  FillHist("Event_with_b1_b2/N_light_quark_jet/"+ProcessName,N_light_quark_jet, weight, 10, 0, 10);
  FillHist("Event_with_b1_b2/N_gluon_jet/"+ProcessName,N_gluon_jet, weight, 10, 0, 10);
  if(flavourmatch1&&flavourmatch2){
    FillHist("Event_with_b1_b2/nTightJet_if_flavour_matched/"+ProcessName,tightjetsize, weight, 10, 0, 10);
  }
  
  if((fabs(GENs[myGEN.Whad_q1_genidx].Eta())<2.4 && GENs[myGEN.Whad_q1_genidx].Pt()>30) &&
     ((fabs(GENs[myGEN.Whad_q2_genidx].Eta())<2.4 && GENs[myGEN.Whad_q2_genidx].Pt()>30))){
    FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/Whad_q1_q2_match/"+ProcessName,Is_q1match*Is_q2match, weight, 4, -1, 3);
    FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/Whad_q1_q2_match_flavour_only/"+ProcessName,flavourmatch1&&flavourmatch2, weight, 4, -1, 3);
    FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/nTightJet/"+ProcessName,tightjetsize, weight, 10, 0, 10);
    FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/N_light_quark_jet/"+ProcessName,N_light_quark_jet, weight, 10, 0, 10);
    if(flavourmatch1&&flavourmatch2) FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/nTightJet_if_flavour_matched/"+ProcessName,tightjetsize, weight, 10, 0, 10);
    
    FillHist("Event_with_b1_b2_GEN_eta_2p4_pt30/N_gluon_jet/"+ProcessName,N_gluon_jet, weight, 10, 0, 10);
    
    
  }
  return 1;
}



void TTsemilep_JetAssignScore_TrainingInput::AnalyzeRECO(){


  
  //call muon/electron
  vector<Muon> AllMuons_raw=GetAllMuons();
  AllMuons=ScaleMuons(AllMuons_raw,0);
  muonsize = AllMuons.size();
  AllElectrons=GetAllElectrons();
  electronsize = AllElectrons.size();
  AllJets = GetAllJets();
  jetsize=AllJets.size();

  //(0) Apply some basic cuts

  //myRECO.passMuonTrigger=ev.PassTrigger(MuonTriggerNames);
  //myRECO.passElectronTrigger=ev.PassTrigger(ElectronTriggerNames);

  myRECO.goodTTbarMu=TTbarMuReco();
  
  myRECO.goodTTbarEl=TTbarElReco();
  


  //myRECO.passMuonTriggerAndTTbarMu=myRECO.passMuonTrigger && myRECO.goodTTbarMu;
  //myRECO.passElectronTriggerAndTTbarEl= myRECO.passElectronTrigger && myRECO.goodTTbarEl;
  //  if((!myRECO.passMuonTriggerAndTTbarMu) && (!myRECO.passElectronTriggerAndTTbarEl)) return;
  if( (!(myRECO.goodTTbarMu&&myLHE.IsMuonChannel)) && (!(myRECO.goodTTbarEl&&myLHE.IsElectronChannel)) ) return;


  if(myRECO.passMuonTriggerAndTTbarMu){ 
    ChannelLep="TTbarMu";
    trigsf=mu_trigsf;
    lep_recosf=mu_recosf;
    lep_idsf=mu_idsf;
    weight=weight*trigsf*lep_recosf*lep_idsf*mu_trksf;
  }
  else if(myRECO.passElectronTriggerAndTTbarEl){
    ChannelLep="TTbarEl";
    trigsf=el_trigsf;
    lep_recosf=el_recosf;
    lep_idsf=el_idsf;
    mu_trksf=1.;
    weight=weight*trigsf*lep_recosf*lep_idsf*mu_trksf;
  }
  




  ///--Using btag score--//
  if(!TTsemilep_JetAssignScore_TrainingInput::CheckJets()) return;
  //if(tightjetidx_q1_flav_match!=-1 && tightjetidx_q2_flav_match!=-1)doFillTree=true;
  //If Z event, Let's store
  //FillCutflow("cutflow/all/"+ProcessName,"TagBjet",weight);
  FillHist("TagBjet/cutflow/"+ProcessName,1, weight, 2, 0, 2);  
  
  //FillHist("Pass1bjet",1, weight, 1, 0, 2);
  
}





void TTsemilep_JetAssignScore_TrainingInput::FillTreeValues(){
  TLorentzVector _v_Thad,_v_Whad;
  
  met_pt=PuppiMET_pt,met_phi=PuppiMET_phi;
  if(myRECO.goodTTbarEl&&myLHE.IsElectronChannel) {
    muon_pt=0, muon_phi=0, muon_eta=0;
    electron_pt=AllElectrons[myRECO.idx_Telectron].Pt(),electron_phi=AllElectrons[myRECO.idx_Telectron].Phi(),electron_eta=AllElectrons[myRECO.idx_Telectron].Eta();

  }
  if(myRECO.goodTTbarMu&&myLHE.IsMuonChannel){
    muon_pt=AllMuons[myRECO.idx_Tmuon].Pt(),muon_phi=AllMuons[myRECO.idx_Tmuon].Phi(),muon_eta=AllMuons[myRECO.idx_Tmuon].Eta();
    electron_pt=0,electron_phi=0,electron_eta=0;
    
  }
  //TODO : set muon,electron pt
  
  //----signal_evt---//
  IsSig=1;
  IsBkg=0;
  int idx_blep=-1;
  int idx_bhad=-1;
  if(myLHE.bLep_charge>0){//bHad_charge<0  ---> idx_bjet
    idx_blep=myRECO.idx_bbarjet;
    idx_bhad=myRECO.idx_bjet;    
  }
  else{// bLep charge <0 -> bhad charge > 0 ->bbarjet
    idx_blep=myRECO.idx_bjet;
    idx_bhad=myRECO.idx_bbarjet;    
  }
  
  blep_pt=AllJets[idx_blep].Pt(), blep_eta=AllJets[idx_blep].Eta(), blep_phi=AllJets[idx_blep].Phi(), blep_E=AllJets[idx_blep].E();
  bhad_pt=AllJets[idx_bhad].Pt(), bhad_eta=AllJets[idx_bhad].Eta(), bhad_phi=AllJets[idx_bhad].Phi(), bhad_E=AllJets[idx_bhad].E();

  


  //q1,q2 from Whad... pT ordered
  if(tightjets[tightjetidx_q1_flav_match].Pt() > tightjets[tightjetidx_q2_flav_match].Pt()  ){
  
    q1jet_pt=tightjets[tightjetidx_q1_flav_match].Pt(),q1jet_eta=tightjets[tightjetidx_q1_flav_match].Eta(), q1jet_phi=tightjets[tightjetidx_q1_flav_match].Phi(), q1jet_E=tightjets[tightjetidx_q1_flav_match].E();
    q2jet_pt=tightjets[tightjetidx_q2_flav_match].Pt(),q2jet_eta=tightjets[tightjetidx_q2_flav_match].Eta(), q2jet_phi=tightjets[tightjetidx_q2_flav_match].Phi(),q2jet_E=tightjets[tightjetidx_q2_flav_match].E();
    
  }
  else{
    
    q1jet_pt=tightjets[tightjetidx_q2_flav_match].Pt(),q1jet_eta=tightjets[tightjetidx_q2_flav_match].Eta(), q1jet_phi=tightjets[tightjetidx_q2_flav_match].Phi(),q1jet_E=tightjets[tightjetidx_q2_flav_match].E();
    q2jet_pt=tightjets[tightjetidx_q1_flav_match].Pt(),q2jet_eta=tightjets[tightjetidx_q1_flav_match].Eta(), q2jet_phi=tightjets[tightjetidx_q1_flav_match].Phi(),q2jet_E=tightjets[tightjetidx_q1_flav_match].E();
    
  }

  _v_Whad=tightjets[tightjetidx_q1_flav_match] + tightjets[tightjetidx_q2_flav_match];
  _v_Thad=tightjets[tightjetidx_q1_flav_match] + tightjets[tightjetidx_q2_flav_match] + AllJets[idx_bhad];

  WhadCand_mass=_v_Whad.M();
  ThadCand_mass=_v_Thad.M();

  if(myRECO.goodTTbarMu&&myLHE.IsMuonChannel) jhchoi_newtree->Fill();  
  if(myRECO.goodTTbarEl&&myLHE.IsElectronChannel) jhchoi_newtree3->Fill();
  
  //---bkg evt wrong light quark assigned---//  
  IsSig=0;
  IsBkg=1;
  
  for(unsigned int i=0; i < tightjetsize; i++ ){
    
    for(unsigned int j=i+1; j < tightjetsize; j++ ){
      //exclude signal events
      
      if( (int)i==tightjetidx_q1_flav_match && (int)j==tightjetidx_q2_flav_match ) continue;
      if( (int)i==tightjetidx_q2_flav_match && (int)j==tightjetidx_q1_flav_match ) continue;
      if(tightjets[i].Pt() > tightjets[j].Pt()){
	q1jet_pt=tightjets[i].Pt(),q1jet_eta=tightjets[i].Eta(), q1jet_phi=tightjets[i].Phi(), q1jet_E=tightjets[i].E();
	q2jet_pt=tightjets[j].Pt(),q2jet_eta=tightjets[j].Eta(), q2jet_phi=tightjets[j].Phi(), q2jet_E=tightjets[j].E();
      }
      else{
	q1jet_pt=tightjets[j].Pt(),q1jet_eta=tightjets[j].Eta(), q1jet_phi=tightjets[j].Phi(),q1jet_E=tightjets[j].E();
	q2jet_pt=tightjets[i].Pt(),q2jet_eta=tightjets[i].Eta(), q2jet_phi=tightjets[i].Phi(),q2jet_E=tightjets[i].E();
      }

      _v_Whad=tightjets[i] + tightjets[j];
      _v_Thad=tightjets[i] + tightjets[j] + AllJets[idx_bhad];

      WhadCand_mass=_v_Whad.M();
      ThadCand_mass=_v_Thad.M();

      if(myRECO.goodTTbarMu&&myLHE.IsMuonChannel) jhchoi_newtree2->Fill();
      if(myRECO.goodTTbarEl&&myLHE.IsElectronChannel) jhchoi_newtree4->Fill();

    }
  }

  //--bkg evt all cases with wrong b/b~ assignment

  blep_pt=AllJets[idx_bhad].Pt(), blep_eta=AllJets[idx_bhad].Eta(), blep_phi=AllJets[idx_bhad].Phi(), blep_E=AllJets[idx_bhad].E();
  bhad_pt=AllJets[idx_blep].Pt(), bhad_eta=AllJets[idx_blep].Eta(), bhad_phi=AllJets[idx_blep].Phi(), bhad_E=AllJets[idx_blep].E();





  for(unsigned int i=0; i < tightjetsize; i++ ){
    for(unsigned int j=i+1; j < tightjetsize; j++ ){

      //if( i==tightjetidx_q1_flav_match && j==tightjetidx_q2_flav_match ) continue;
      //if( i==tightjetidx_q2_flav_match && j==tightjetidx_q1_flav_match ) continue;
      if(tightjets[i].Pt() > tightjets[j].Pt()){
        q1jet_pt=tightjets[i].Pt(),q1jet_eta=tightjets[i].Eta(), q1jet_phi=tightjets[i].Phi(),q1jet_E=tightjets[i].E();
        q2jet_pt=tightjets[j].Pt(),q2jet_eta=tightjets[j].Eta(), q2jet_phi=tightjets[j].Phi(),q2jet_E=tightjets[j].E();
      }
      else{
        q1jet_pt=tightjets[j].Pt(),q1jet_eta=tightjets[j].Eta(), q1jet_phi=tightjets[j].Phi(), q1jet_E=tightjets[j].E();
        q2jet_pt=tightjets[i].Pt(),q2jet_eta=tightjets[i].Eta(), q2jet_phi=tightjets[i].Phi(), q2jet_E=tightjets[i].E();
      }
      _v_Whad=tightjets[i]+tightjets[j];
      _v_Thad=tightjets[i]+tightjets[j]+AllJets[idx_blep];
      WhadCand_mass=_v_Whad.M();
      ThadCand_mass=_v_Thad.M();
      if(myRECO.goodTTbarMu&&myLHE.IsMuonChannel) jhchoi_newtree2->Fill();
      if(myRECO.goodTTbarEl&&myLHE.IsElectronChannel) jhchoi_newtree4->Fill();
      
    }
  }

}

void TTsemilep_JetAssignScore_TrainingInput::FillTreeValues_NotMatchCase(){
  ///Anyway...this case is wrong... because some jet from Whad doesn't enter out ROI
  TLorentzVector _v_Thad,_v_Whad;
  met_pt=PuppiMET_pt,met_phi=PuppiMET_phi;
  if(myRECO.goodTTbarEl&&myLHE.IsElectronChannel) {
    muon_pt=0, muon_phi=0, muon_eta=0;
    electron_pt=AllElectrons[myRECO.idx_Telectron].Pt(),electron_phi=AllElectrons[myRECO.idx_Telectron].Phi(),electron_eta=AllElectrons[myRECO.idx_Telectron].Eta();

  }
  if(myRECO.goodTTbarMu&&myLHE.IsMuonChannel){
    muon_pt=AllMuons[myRECO.idx_Tmuon].Pt(),muon_phi=AllMuons[myRECO.idx_Tmuon].Phi(),muon_eta=AllMuons[myRECO.idx_Tmuon].Eta();
    electron_pt=0,electron_phi=0,electron_eta=0;
    
  }
  int idx_blep=-1;
  int idx_bhad=-1;
  if(myLHE.bLep_charge>0){//bHad_charge<0  ---> idx_bjet
    idx_blep=myRECO.idx_bbarjet;
    idx_bhad=myRECO.idx_bjet;
  }
  else{// bLep charge <0 -> bhad charge > 0 ->bbarjet
    idx_blep=myRECO.idx_bjet;
    idx_bhad=myRECO.idx_bbarjet;
  }
  blep_pt=AllJets[idx_blep].Pt(), blep_eta=AllJets[idx_blep].Eta(), blep_phi=AllJets[idx_blep].Phi(), blep_E=AllJets[idx_blep].E();
  bhad_pt=AllJets[idx_bhad].Pt(), bhad_eta=AllJets[idx_bhad].Eta(), bhad_phi=AllJets[idx_bhad].Phi(), bhad_E=AllJets[idx_bhad].E();

  ////----
  //---bkg evt wrong light quark assigned---//  
  IsSig=0;
  IsBkg=1;

  for(unsigned int i=0; i < tightjetsize; i++ ){
    
    for(unsigned int j=i+1; j < tightjetsize; j++ ){
      //exclude signal events
      //if( i==tightjetidx_q1_flav_match && j==tightjetidx_q2_flav_match ) continue;
      //if( i==tightjetidx_q2_flav_match && j==tightjetidx_q1_flav_match ) continue;
      if(tightjets[i].Pt() > tightjets[j].Pt()){
	q1jet_pt=tightjets[i].Pt(),q1jet_eta=tightjets[i].Eta(), q1jet_phi=tightjets[i].Phi(), q1jet_E=tightjets[i].E();
	q2jet_pt=tightjets[j].Pt(),q2jet_eta=tightjets[j].Eta(), q2jet_phi=tightjets[j].Phi(), q2jet_E=tightjets[j].E();
      }
      else{
	q1jet_pt=tightjets[j].Pt(),q1jet_eta=tightjets[j].Eta(), q1jet_phi=tightjets[j].Phi(),q1jet_E=tightjets[j].E();
	q2jet_pt=tightjets[i].Pt(),q2jet_eta=tightjets[i].Eta(), q2jet_phi=tightjets[i].Phi(),q2jet_E=tightjets[i].E();
      }

      _v_Whad=tightjets[i] + tightjets[j];
      _v_Thad=tightjets[i] + tightjets[j] + AllJets[idx_bhad];

      WhadCand_mass=_v_Whad.M();
      ThadCand_mass=_v_Thad.M();

      if(myRECO.goodTTbarMu&&myLHE.IsMuonChannel) jhchoi_newtree2->Fill();
      if(myRECO.goodTTbarEl&&myLHE.IsElectronChannel) jhchoi_newtree4->Fill();

    }
  }

  //--bkg evt all cases with wrong b/b~ assignment(b/b~ switched)

  blep_pt=AllJets[idx_bhad].Pt(), blep_eta=AllJets[idx_bhad].Eta(), blep_phi=AllJets[idx_bhad].Phi(), blep_E=AllJets[idx_bhad].E();
  bhad_pt=AllJets[idx_blep].Pt(), bhad_eta=AllJets[idx_blep].Eta(), bhad_phi=AllJets[idx_blep].Phi(), bhad_E=AllJets[idx_blep].E();





  for(unsigned int i=0; i < tightjetsize; i++ ){
    for(unsigned int j=i+1; j < tightjetsize; j++ ){

      //if( i==tightjetidx_q1_flav_match && j==tightjetidx_q2_flav_match ) continue;
      //if( i==tightjetidx_q2_flav_match && j==tightjetidx_q1_flav_match ) continue;
      if(tightjets[i].Pt() > tightjets[j].Pt()){
        q1jet_pt=tightjets[i].Pt(),q1jet_eta=tightjets[i].Eta(), q1jet_phi=tightjets[i].Phi(),q1jet_E=tightjets[i].E();
        q2jet_pt=tightjets[j].Pt(),q2jet_eta=tightjets[j].Eta(), q2jet_phi=tightjets[j].Phi(),q2jet_E=tightjets[j].E();
      }
      else{
        q1jet_pt=tightjets[j].Pt(),q1jet_eta=tightjets[j].Eta(), q1jet_phi=tightjets[j].Phi(), q1jet_E=tightjets[j].E();
        q2jet_pt=tightjets[i].Pt(),q2jet_eta=tightjets[i].Eta(), q2jet_phi=tightjets[i].Phi(), q2jet_E=tightjets[i].E();
      }
      _v_Whad=tightjets[i]+tightjets[j];
      _v_Thad=tightjets[i]+tightjets[j]+AllJets[idx_blep];
      WhadCand_mass=_v_Whad.M();
      ThadCand_mass=_v_Thad.M();
      if(myRECO.goodTTbarMu&&myLHE.IsMuonChannel) jhchoi_newtree2->Fill();
      if(myRECO.goodTTbarEl&&myLHE.IsElectronChannel) jhchoi_newtree4->Fill();
      
    }
  }

}

void TTsemilep_JetAssignScore_TrainingInput::executeEvent(){
  if(doReduction){
    if(event%60!=0) return;
  }
  //jhchoi//

  ev = GetEvent();
  //FillHist("event_start",1, weight, 1, 0, 1);
  //isEvenEvent=((event%2)==0);
  //---initialize--//
  //EventTag="";
  //EventTagJetParton="";
  ChannelLep="";
  IncomingPartonTag="";
  doPrint=false;
  weight=1.;//init event weight
  base_weight=1.;
  myRECO.idx_Tmuon=-1;
  myRECO.idx_Telectron=-1;

  myRECO.goodTTbarMu=false;
  myRECO.goodTTbarEl=false;
  DNNscore=-999.;
  
  taged_bjet_score=0.;
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

  //indices
  tightjetidx_q1_flav_match=-1, tightjetidx_q2_flav_match=-1;
  //checkjets
  Nb=0,Nbbar=0;
  if(!IsDATA){
    base_weight*=MCweight();
    base_weight*=ev.GetTriggerLumi("Full");
    weight *= MCweight();
    weight *= ev.GetTriggerLumi("Full");
  }
  //initialize//
  myLHE.incoming_parton_pid.clear();
  InitValues();
  doFillTree=false;

  LHEs=GetLHEs();
  TTsemilep_JetAssignScore_TrainingInput::AnalyzeLHE();
  if (myLHE.IsTauChannel) return; // not caring tau channel
  if(ProcessName.Contains("TTLJ"))TTsemilep_JetAssignScore_TrainingInput::AnalyzeGEN();
  //FillCutflow("cutflow/all/"+ProcessName,"event_start",weight);
  FillHist("event_start/cutflow/"+ProcessName,1, weight, 2, 0, 2);
  TTsemilep_JetAssignScore_TrainingInput::AnalyzeRECO();
  if(Nb==1 && Nbbar==1 && tightjetsize>1  ){
    if(tightjetidx_q1_flav_match!=-1 && tightjetidx_q2_flav_match!=-1) {
      TTsemilep_JetAssignScore_TrainingInput::FillTreeValues();
    }
    else{//not matched cases
      TTsemilep_JetAssignScore_TrainingInput::FillTreeValues_NotMatchCase();
    }
  }
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
