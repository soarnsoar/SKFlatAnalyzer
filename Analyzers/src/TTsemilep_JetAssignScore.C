#include "TTsemilep_JetAssignScore.h"
#include <stdlib.h>
#include <stdio.h>

TTsemilep_JetAssignScore::TTsemilep_JetAssignScore(){//
  
  doReduction=false;
  doDebug=false;
  DNNcut=0.5;



}
TTsemilep_JetAssignScore::~TTsemilep_JetAssignScore(){

  //==== Destructor of this Analyzer
  cout << "nevt=" << nevt << endl;
  cout << "nevt_samebb=" << nevt_samebb << endl;
}


void TTsemilep_JetAssignScore::initTMVAmodel_muon(){//TTsemilepJetAssign/2312/v1
  //TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/2312/v1//muon/TMVAClassification_DNN.weights.xml";//using only matched jets exist
  //TMVA/TTsemilepJetAssign/add_unmatchedjet_event/muon
  TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/add_unmatchedjet_event/muon/TMVAClassification_DNN.weights.xml";//add nonmatchedjet events
  cout << "define tmvareader"<< endl;
  myreader_muon=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_muon->AddVariable("met_pt",&met_pt);
  myreader_muon->AddVariable("met_phi",&met_phi);
  myreader_muon->AddVariable("muon_pt",&muon_pt);
  myreader_muon->AddVariable("muon_eta",&muon_eta);
  myreader_muon->AddVariable("muon_phi",&muon_phi);
  myreader_muon->AddVariable("blep_pt",&blep_pt);
  myreader_muon->AddVariable("blep_eta",&blep_eta);
  myreader_muon->AddVariable("blep_phi",&blep_phi);
  myreader_muon->AddVariable("blep_E",&blep_E);
  myreader_muon->AddVariable("bhad_pt",&bhad_pt);
  myreader_muon->AddVariable("bhad_eta",&bhad_eta);
  myreader_muon->AddVariable("bhad_phi",&bhad_phi);
  myreader_muon->AddVariable("bhad_E",&bhad_E);
  myreader_muon->AddVariable("q1jet_pt",&q1jet_pt);
  myreader_muon->AddVariable("q1jet_eta",&q1jet_eta);
  myreader_muon->AddVariable("q1jet_phi",&q1jet_phi);
  myreader_muon->AddVariable("q1jet_E",&q1jet_E);
  myreader_muon->AddVariable("q2jet_pt",&q2jet_pt);
  myreader_muon->AddVariable("q2jet_eta",&q2jet_eta);
  myreader_muon->AddVariable("q2jet_phi",&q2jet_phi);
  myreader_muon->AddVariable("q2jet_E",&q2jet_E);
  myreader_muon->AddVariable("WhadCand_mass",&WhadCand_mass);
  myreader_muon->AddVariable("ThadCand_mass",&ThadCand_mass);

  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_muon->BookMVA("PyKeras::DNN",xmlfile);
  cout << "[myreader_muon] Eval for Test" << endl;
  Float_t ret=myreader_muon->EvaluateMVA("PyKeras::DNN");
  cout << ret << endl;


}



void TTsemilep_JetAssignScore::initTMVAmodel_electron(){
  //TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/2312/v1/electron/TMVAClassification_DNN.weights.xml";//training with only matchedjet events
  TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/add_unmatchedjet_event/electron/TMVAClassification_DNN.weights.xml";//add nonmatchedjet events
  cout << "define tmvareader"<< endl;
  myreader_electron=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_electron->AddVariable("met_pt",&met_pt);
  myreader_electron->AddVariable("met_phi",&met_phi);
  myreader_electron->AddVariable("electron_pt",&electron_pt);
  myreader_electron->AddVariable("electron_eta",&electron_eta);
  myreader_electron->AddVariable("electron_phi",&electron_phi);
  myreader_electron->AddVariable("blep_pt",&blep_pt);
  myreader_electron->AddVariable("blep_eta",&blep_eta);
  myreader_electron->AddVariable("blep_phi",&blep_phi);
  myreader_electron->AddVariable("blep_E",&blep_E);
  myreader_electron->AddVariable("bhad_pt",&bhad_pt);
  myreader_electron->AddVariable("bhad_eta",&bhad_eta);
  myreader_electron->AddVariable("bhad_phi",&bhad_phi);
  myreader_electron->AddVariable("bhad_E",&bhad_E);
  myreader_electron->AddVariable("q1jet_pt",&q1jet_pt);
  myreader_electron->AddVariable("q1jet_eta",&q1jet_eta);
  myreader_electron->AddVariable("q1jet_phi",&q1jet_phi);
  myreader_electron->AddVariable("q1jet_E",&q1jet_E);
  myreader_electron->AddVariable("q2jet_pt",&q2jet_pt);
  myreader_electron->AddVariable("q2jet_eta",&q2jet_eta);
  myreader_electron->AddVariable("q2jet_phi",&q2jet_phi);
  myreader_electron->AddVariable("q2jet_E",&q2jet_E);
  myreader_electron->AddVariable("WhadCand_mass",&WhadCand_mass);
  myreader_electron->AddVariable("ThadCand_mass",&ThadCand_mass);

  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_electron->BookMVA("PyKeras::DNN",xmlfile);
  cout << "[myreader_electron] Eval for Test" << endl;
  Float_t ret=myreader_electron->EvaluateMVA("PyKeras::DNN");
  cout << ret << endl;


}



void TTsemilep_JetAssignScore::InitValues(){
  
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



void TTsemilep_JetAssignScore::initializeAnalyzer(){
  

  nevt=0., nevt_samebb=0.;
  cout << "[initialize DNN models]" << endl;
  SKFLAT_WD=getenv("SKFlat_WD");
  initTMVAmodel_muon();
  initTMVAmodel_electron();


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
  cout << "[TTsemilep_JetAssignScore::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;



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
    
  }

  
}
void TTsemilep_JetAssignScore::AnalyzeLHE(){
  
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

void TTsemilep_JetAssignScore::AnalyzeGEN(){
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



bool TTsemilep_JetAssignScore::TTbarMuReco(){

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
  if (maxpt < TriggerSafeCut_muon) return 0;
  if(!IsDATA) {
    //this_leptonid_sf=1.;
    //this_iso_sf=1.;
    //this_trigger_sf=1.;
    vector<Lepton*> leps=MakeLeptonPointerVector(v_Tmuon);
    
    mu_trigsf=GetLeptonTriggerORSF(ev, MuonTriggerNames, MuonTriggerSFKeys, leps,0,0,"");
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

bool TTsemilep_JetAssignScore::TTbarElReco(){

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
  if (AllElectrons[idx_Telectron[0]].Pt() < TriggerSafeCut_electron) return 0;
  if(!IsDATA) {
    vector<Lepton*> leps=MakeLeptonPointerVector(v_Telectron);
    Lepton* _el1=leps.at(0);
    el_trigsf=GetLeptonTriggerORSF(ev,ElectronTriggerNames, ElectronTriggerSFKeys, leps,0,0,"");
    el_recosf=fEff->GetEfficiencySF("Electron_RECO",_el1,0,0);
    el_idsf=fEff->GetEfficiencySF("Electron_MediumID",_el1,0,0) ;

  }
  //Now Electron is ready
  //PuppiMET_pt
  
  myRECO.idx_Telectron=idx_Telectron[0];
  return 1;

}






bool TTsemilep_JetAssignScore::CheckJets(){
  FillCutflow("cutflow/"+ProcessName,"Without_bMatch",weight);
  FillHist("Without_bMatch/Event/"+ProcessName,1, weight, 4, -1, 3);
  double btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
  //double bveto_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Loose);
  //JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb
  //double MCCorrection::GetJetTaggingCutValue(JetTagging::Tagger tagger, JetTagging::WP wp){
  //myRECO.ij_B
  //vector<Jet> tightjets = SelectJets(AllJets, "tightLepVeto", 20., 2.4);
  unsigned int _Nb=0;
  //unsigned int _Nbbar=0;
  tightjets.clear();
  tightbjets.clear();
  //myRECO.idx_bjet=-1;
  //myRECO.idx_bbarjet=-1;
  //tightjets.push_back(AllJets[myRECO.ij_B]);
  //jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  //btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
  //bveto_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Loose);
  TLorentzVector l1;
  if(myRECO.passMuonTriggerAndTTbarMu){
    l1=AllMuons[myRECO.idx_Tmuon];
  }
  else if(myRECO.passElectronTriggerAndTTbarEl){
    l1=AllElectrons[myRECO.idx_Telectron];
  }
  //cout << "btag_cut=" << btag_cut << endl;
  for(unsigned int i = 0 ; i < jetsize; i ++){


    if(AllJets[i].Pt() < 30.) continue;
    if(fabs(AllJets[i].Eta()) > 2.4) continue;
    if(AllJets[i].DeltaR(l1)<0.4) continue;
    if(!AllJets[i].PassID("tightLepVeto")) continue; //old : tight
    double btag_score=AllJets[i].GetTaggerResult(JetTagging::DeepJet);
    //if(AllJets[i].partonFlavour()==5 && btag_score>btag_cut){
    if(btag_score>btag_cut){
      _Nb+=1;
      tightbjets.push_back(AllJets[i]);
    }
    //else if(AllJets[i].partonFlavour()==-5 && btag_score>btag_cut){
    //else if(btag_score>btag_cut){
    //  _Nbbar+=1;
    //  myRECO.idx_bbarjet=i;
    //}
    //else if( abs(AllJets[i].partonFlavour()) !=5 && btag_score<btag_cut){
    else{
      tightjets.push_back(AllJets[i]);
    }
  }
  
  /*
  if(!IsDATA){
    btagsf = mcCorr->GetBTaggingReweight_1a(tightbjets, jtp);
    weight*=btagsf;

  }
  */

  if(_Nb!=2) return 0;
  //if(_Nb!=1) return 0;
  //if(_Nbbar!=1) return 0;


  //Whad_q1_pid,Whad_q2_pid
  //Whad_q1_genidx,Whad_q2_genidx

  tightjetsize=tightjets.size();
  if (tightjetsize < 2) return 0;
  FillCutflow("cutflow/"+ProcessName,"light_tightjet_size_over_2",weight);
  
  //cout << "<light jet flavour>" << endl;

  //------Truth Infos-----//
  ///---Let's check jets whose flavours are  matched to q1/q2 
  bool flavourmatch1=false;
  bool flavourmatch2=false;
  tightjetidx_q1_flav_match=-1;
  tightjetidx_q2_flav_match=-1;

  int N_flavour_match1=0;
  int N_flavour_match2=0;
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
	//cout << "<!!myGEN.Whad_q1_pid matched!!>" <<endl;
	//cout << "tightjets[i].partonFlavour()=" << tightjets[i].partonFlavour() << endl;
	continue;
      }
    }

    if(!flavourmatch2){
     
      if(_flavourmatch2){
	flavourmatch2=true;
	tightjetidx_q2_flav_match=i;
	//cout << "<!!myGEN.Whad_q2_pid matched!!>" <<endl;
	//cout << "tightjets[i].partonFlavour()=" << tightjets[i].partonFlavour() << endl;
	continue;
      }
    }
    
    //cout << i << "th light jets=" << tightjets[i].partonFlavour() << endl;
  }//---end of for loop


  if(tightjetidx_q1_flav_match!=-1 && tightjetidx_q2_flav_match!=-1){//Find all matched tightjet    


  }
  int bHad_true_pid=-999;
  ///---bjet's index---///
  if(myLHE.bLep_charge > 0 ){ //bhad_charge < 0 <=> bhad is b 
    bHad_true_pid=5;
  }
  else{
    bHad_true_pid=-5;
  }
  int tightbjetidx_bHad_flav_match=-1;
  for(unsigned int ib=0;ib<2;ib++){
    if(tightbjets[ib].partonFlavour()==bHad_true_pid){
      tightbjetidx_bHad_flav_match=ib;
      break;
    }
  }
  
  
  //----Set input values of lep and met(NON-JET OBJS)---//
  met_pt=PuppiMET_pt,met_phi=PuppiMET_phi;
  if (myRECO.passMuonTriggerAndTTbarMu){
    muon_pt=l1.Pt();muon_eta=l1.Eta();muon_phi=l1.Phi();
  }
  else{
    electron_pt=l1.Pt();electron_eta=l1.Eta();electron_phi=l1.Phi();
  }
  double _max_DNN=-100.;
  double _min_chi2=1000000000000;
  int idxset_dnn[4]={-1,-1,-1,-1};
  int idxset_chi2[4]={-1,-1,-1,-1};
  for(unsigned int ib1 =0 ; ib1 < 2 ; ib1++){//permutation for bjet
    for(unsigned int ib2 = 0 ; ib2 < 2; ib2++){
      if(ib1==ib2)continue;
      blep_pt=tightbjets[ib1].Pt();       
      blep_eta=tightbjets[ib1].Eta();       
      blep_phi=tightbjets[ib1].Phi();
      blep_E=tightbjets[ib1].E();

      bhad_pt=tightbjets[ib2].Pt();       
      bhad_eta=tightbjets[ib2].Eta();       
      bhad_phi=tightbjets[ib2].Phi();
      bhad_E=tightbjets[ib2].E();

      ///q1/q2
      for(unsigned int iq1=0; iq1 < tightjetsize; iq1++){
	for(unsigned int iq2=iq1; iq2 < tightjetsize; iq2++){//select 2 jets
	  if(iq1==iq2) continue;
	  if(tightjets[iq1].Pt()>tightjets[iq2].Pt()){
	    q1jet_pt=tightjets[iq1].Pt();
	    q1jet_eta=tightjets[iq1].Eta();
	    q1jet_phi=tightjets[iq1].Phi();
	    q1jet_E=tightjets[iq1].E();
	    q2jet_pt=tightjets[iq2].Pt();
	    q2jet_eta=tightjets[iq2].Eta();
	    q2jet_phi=tightjets[iq2].Phi();
	    q2jet_E=tightjets[iq2].E();
	  }
	  else{
	    q1jet_pt=tightjets[iq2].Pt();
	    q1jet_eta=tightjets[iq2].Eta();
	    q1jet_phi=tightjets[iq2].Phi();
	    q1jet_E=tightjets[iq2].E();
	    q2jet_pt=tightjets[iq1].Pt();
	    q2jet_eta=tightjets[iq1].Eta();
	    q2jet_phi=tightjets[iq1].Phi();
	    q2jet_E=tightjets[iq1].E();
	  }
	  //WhadCand_mass / ThadCand_mass
	  TLorentzVector _Whad,_Thad;
	  _Whad=tightjets[iq1]+tightjets[iq2];
	  _Thad=tightjets[iq1]+tightjets[iq2]+tightbjets[ib2];
	  WhadCand_mass=_Whad.M();
	  ThadCand_mass=_Thad.M();
	  
	  //---dnn---//
	  double _score=-100;
	  if(myRECO.passMuonTriggerAndTTbarMu){
	    _score=myreader_muon->EvaluateMVA("PyKeras::DNN");
	  }
	  else{
	    _score=myreader_electron->EvaluateMVA("PyKeras::DNN");
	  }
	  if(_score>_max_DNN){
	    _max_DNN=_score;
	    idxset_dnn[0]=ib1, idxset_dnn[1]=ib2, idxset_dnn[2]=iq1, idxset_dnn[3]=iq2;
	  }
	  //--chi2--//
	  double _chi2 = pow((WhadCand_mass - MW_pdg)/Width_Wqq_pdg,2) + pow((ThadCand_mass - MTop_pdg)/Width_Top_bqq_pdg,2);
	  if(_chi2<_min_chi2){
	    idxset_chi2[0]=ib1, idxset_chi2[1]=ib2, idxset_chi2[2]=iq1, idxset_chi2[3]=iq2;
	  }
	}
      }

    }
  }//for all permutations
  //{ib1,ib2,iq1,iq2} ->ib1 : b from leptonic top decay // ib2 : b from hadronic top decay 
  //idxset_dnn
  //idxset_chi2
  //---DNN---
  TLorentzVector Whad_dnn,Thad_dnn;
  //int ib1=idxset_dnn[0], ib2=idxset_dnn[1], iq1=idxset_dnn[2], iq2=idxset_dnn[3];
  int ib2=idxset_dnn[1], iq1=idxset_dnn[2], iq2=idxset_dnn[3];
  Whad_dnn=tightjets[iq1]+tightjets[iq2];
  Thad_dnn=tightjets[iq1]+tightjets[iq2]+tightbjets[ib2];
  FillHist("2b_over2j/Whad_dnn/"+ProcessName,Whad_dnn.M(), weight, 100, 0, 200);
  FillHist("2b_over2j/Thad_dnn/"+ProcessName,Thad_dnn.M(), weight, 175, 0, 350);
  bool bjet_flavour_matched_dnn=false;
  bool qq_flavour_matched_dnn=false;
  if(bHad_true_pid==tightbjets[ib2].partonFlavour()) bjet_flavour_matched_dnn=true;
  if(iq1==tightjetidx_q1_flav_match && iq2==tightjetidx_q2_flav_match) qq_flavour_matched_dnn = true;
  if(iq2==tightjetidx_q1_flav_match && iq1==tightjetidx_q2_flav_match) qq_flavour_matched_dnn = true;
  FillHist("2b_over2j/qqb_flavour_matched_dnn/"+ProcessName,bjet_flavour_matched_dnn*qq_flavour_matched_dnn, weight, 4, -1, 3);
  FillHist("2b_over2j/b_flavour_matched_dnn/"+ProcessName,bjet_flavour_matched_dnn, weight, 4, -1, 3);
  FillHist("2b_over2j/qq_flavour_matched_dnn/"+ProcessName,qq_flavour_matched_dnn, weight, 4, -1, 3);
  if(tightjetidx_q1_flav_match!=-1 && tightjetidx_q2_flav_match!=-1 && tightbjetidx_bHad_flav_match!=-1){//Find all matched tightjet
    FillHist("2b_over2j_all_matched_jet_exist/qqb_flavour_matched_dnn/"+ProcessName,bjet_flavour_matched_dnn*qq_flavour_matched_dnn, weight, 4, -1, 3);
    FillHist("2b_over2j_all_matched_jet_exist/b_flavour_matched_dnn/"+ProcessName,bjet_flavour_matched_dnn, weight, 4, -1, 3);
    FillHist("2b_over2j_all_matched_jet_exist/qq_flavour_matched_dnn/"+ProcessName,qq_flavour_matched_dnn, weight, 4, -1, 3);
    FillHist("2b_over2j_all_matched_jet_exist/Whad_dnn/"+ProcessName,Whad_dnn.M(), weight, 100, 0, 200);
    FillHist("2b_over2j_all_matched_jet_exist/Thad_dnn/"+ProcessName,Thad_dnn.M(), weight, 175, 0, 350);

  }

  //--chi2--
  TLorentzVector Whad_chi2,Thad_chi2;
  //ib1=idxset_chi2[0]; 
  ib2=idxset_chi2[1], iq1=idxset_chi2[2], iq2=idxset_chi2[3];
  Whad_chi2=tightjets[iq1]+tightjets[iq2];
  Thad_chi2=tightjets[iq1]+tightjets[iq2]+tightbjets[ib2];
  FillHist("2b_over2j/Whad_chi2/"+ProcessName,Whad_chi2.M(), weight, 100, 0, 200);
  FillHist("2b_over2j/Thad_chi2/"+ProcessName,Thad_chi2.M(), weight, 175, 0, 350);
  bool bjet_flavour_matched_chi2=false;
  bool qq_flavour_matched_chi2=false;
  if(bHad_true_pid==tightbjets[ib2].partonFlavour()) bjet_flavour_matched_chi2=true;
  if(iq1==tightjetidx_q1_flav_match && iq2==tightjetidx_q2_flav_match) qq_flavour_matched_chi2 = true;
  if(iq2==tightjetidx_q1_flav_match && iq1==tightjetidx_q2_flav_match) qq_flavour_matched_chi2 = true;
  FillHist("2b_over2j/qqb_flavour_matched_chi2/"+ProcessName,bjet_flavour_matched_chi2*qq_flavour_matched_chi2, weight, 4, -1, 3);
  FillHist("2b_over2j/b_flavour_matched_chi2/"+ProcessName,bjet_flavour_matched_chi2, weight, 4, -1, 3);
  FillHist("2b_over2j/qq_flavour_matched_chi2/"+ProcessName,qq_flavour_matched_chi2, weight, 4, -1, 3);
  if(tightjetidx_q1_flav_match!=-1 && tightjetidx_q2_flav_match!=-1 && tightbjetidx_bHad_flav_match!=-1){//Find all matched tightjet
    FillHist("2b_over2j_all_matched_jet_exist/qqb_flavour_matched_chi2/"+ProcessName,bjet_flavour_matched_chi2*qq_flavour_matched_chi2, weight, 4, -1, 3);
    FillHist("2b_over2j_all_matched_jet_exist/b_flavour_matched_chi2/"+ProcessName,bjet_flavour_matched_chi2, weight, 4, -1, 3);
    FillHist("2b_over2j_all_matched_jet_exist/qq_flavour_matched_chi2/"+ProcessName,qq_flavour_matched_chi2, weight, 4, -1, 3);
    FillHist("2b_over2j_all_matched_jet_exist/Whad_chi2/"+ProcessName,Whad_chi2.M(), weight, 100, 0, 200);
    FillHist("2b_over2j_all_matched_jet_exist/Thad_chi2/"+ProcessName,Thad_chi2.M(), weight, 175, 0, 350);
  }


  //FillHist("TagBjet/cutflow/"+ProcessName,1, weight, 2, 0, 2);

  return 1;
}



void TTsemilep_JetAssignScore::AnalyzeRECO(){


  
  //call muon/electron
  vector<Muon> AllMuons_raw=GetAllMuons();
  AllMuons=ScaleMuons(AllMuons_raw,0);
  muonsize = AllMuons.size();
  AllElectrons=GetAllElectrons();
  electronsize = AllElectrons.size();
  AllJets = GetAllJets();
  jetsize=AllJets.size();

  //(0) Apply some basic cuts

  myRECO.passMuonTrigger=ev.PassTrigger(MuonTriggerNames);
  myRECO.passElectronTrigger=ev.PassTrigger(ElectronTriggerNames);

  myRECO.goodTTbarMu=TTbarMuReco();
  
  myRECO.goodTTbarEl=TTbarElReco();
  


  myRECO.passMuonTriggerAndTTbarMu=myRECO.passMuonTrigger && myRECO.goodTTbarMu;
  myRECO.passElectronTriggerAndTTbarEl= myRECO.passElectronTrigger && myRECO.goodTTbarEl;
  if((!myRECO.passMuonTriggerAndTTbarMu) && (!myRECO.passElectronTriggerAndTTbarEl)) return;
  //if( (!(myRECO.goodTTbarMu&&myLHE.IsMuonChannel)) && (!(myRECO.goodTTbarEl&&myLHE.IsElectronChannel)) ) return;


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
  if(!TTsemilep_JetAssignScore::CheckJets()) return;

  //If Z event, Let's store
  //FillCutflow("cutflow/all/"+ProcessName,"TagBjet",weight);
  FillHist("TagBjet/cutflow/"+ProcessName,1, weight, 2, 0, 2);  
  
  //FillHist("Pass1bjet",1, weight, 1, 0, 2);
  
}





void TTsemilep_JetAssignScore::FillTreeValues(){
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



void TTsemilep_JetAssignScore::executeEvent(){
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
  TTsemilep_JetAssignScore::AnalyzeLHE();
  if (myLHE.IsTauChannel) return; // not caring tau channel
  if(ProcessName.Contains("TTLJ"))TTsemilep_JetAssignScore::AnalyzeGEN();
  //FillCutflow("cutflow/all/"+ProcessName,"event_start",weight);
  FillHist("event_start/cutflow/"+ProcessName,1, weight, 2, 0, 2);
  TTsemilep_JetAssignScore::AnalyzeRECO();

  
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
