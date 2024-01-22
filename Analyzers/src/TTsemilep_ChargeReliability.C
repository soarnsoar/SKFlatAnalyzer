#include "TTsemilep_ChargeReliability.h"
#include <stdlib.h>
#include <stdio.h>

TTsemilep_ChargeReliability::TTsemilep_ChargeReliability(){//
  
  doDebug=false;
  DNNcut=0.5;
  doDrawDNNinputs=false;


}
TTsemilep_ChargeReliability::~TTsemilep_ChargeReliability(){

  //==== Destructor of this Analyzer
  cout << "nevt=" << nevt << endl;
  cout << "nevt_samebb=" << nevt_samebb << endl;
}


void TTsemilep_ChargeReliability::initChargeReliabilityModel_muon(){
  TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/LepJetChargeReliability/aMCatNLO/muon/TMVAClassification_DNN.weights.xml";
  cout << "define tmvareader"<< endl;
  myreader_ChReliab_muon=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_ChReliab_muon->AddVariable("bmuon_phi",&bmuon_phi);
  myreader_ChReliab_muon->AddVariable("bmuon_pt",&bmuon_pt);
  myreader_ChReliab_muon->AddVariable("bmuon_nsip3d",&bmuon_nsip3d);
  myreader_ChReliab_muon->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader_ChReliab_muon->AddVariable("bjet_pt",&bjet_pt);
  myreader_ChReliab_muon->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader_ChReliab_muon->AddVariable("bjet_phi",&bjet_phi);
  myreader_ChReliab_muon->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader_ChReliab_muon->AddVariable("bmuon_ptwrtbjet",&bmuon_ptwrtbjet);
  myreader_ChReliab_muon->AddVariable("bmuon_eta",&bmuon_eta);
  myreader_ChReliab_muon->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader_ChReliab_muon->AddVariable("bjet_eta",&bjet_eta);
  myreader_ChReliab_muon->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  myreader_ChReliab_muon->AddVariable("bmuon_p_jetrestf",&bmuon_p_jetrestf);
  myreader_ChReliab_muon->AddVariable("bmuon_reltrkiso",&bmuon_reltrkiso);
  myreader_ChReliab_muon->AddVariable("bmuon_dR_l_j",&bmuon_dR_l_j);
  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_ChReliab_muon->BookMVA("PyKeras::DNN",xmlfile);
  cout << "[myreader_ChReliab_muon] Eval for Test" << endl;
  Float_t ret=myreader_ChReliab_muon->EvaluateMVA("PyKeras::DNN");
  cout << ret << endl;


}

void TTsemilep_ChargeReliability::initChargeReliabilityModel_electron(){
  TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/LepJetChargeReliability/aMCatNLO/electron/TMVAClassification_DNN.weights.xml";
  cout << "define tmvareader"<< endl;
  myreader_ChReliab_electron=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_ChReliab_electron->AddVariable("belectron_dR_l_j",&belectron_dR_l_j);
  myreader_ChReliab_electron->AddVariable("belectron_nsip3d",&belectron_nsip3d);
  myreader_ChReliab_electron->AddVariable("belectron_p_jetrestf",&belectron_p_jetrestf);
  myreader_ChReliab_electron->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader_ChReliab_electron->AddVariable("bjet_pt",&bjet_pt);
  myreader_ChReliab_electron->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader_ChReliab_electron->AddVariable("bjet_phi",&bjet_phi);
  myreader_ChReliab_electron->AddVariable("belectron_phi",&belectron_phi);
  myreader_ChReliab_electron->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader_ChReliab_electron->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader_ChReliab_electron->AddVariable("belectron_pt",&belectron_pt);
  myreader_ChReliab_electron->AddVariable("belectron_ptwrtbjet",&belectron_ptwrtbjet);
  myreader_ChReliab_electron->AddVariable("bjet_eta",&bjet_eta);
  myreader_ChReliab_electron->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  myreader_ChReliab_electron->AddVariable("belectron_IsGsfCtfScPixChargeConsistent",&belectron_IsGsfCtfScPixChargeConsistent);
  myreader_ChReliab_electron->AddVariable("belectron_eta",&belectron_eta);
  myreader_ChReliab_electron->AddVariable("belectron_reltrkiso",&belectron_reltrkiso);
  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_ChReliab_electron->BookMVA("PyKeras::DNN",xmlfile);
  cout << "[myreader_ChReliab_electron] Eval for Test" << endl;
  Float_t ret=myreader_ChReliab_electron->EvaluateMVA("PyKeras::DNN");
  cout << ret << endl;


}

void TTsemilep_ChargeReliability::initChargeReliabilityModel_jet(){
  TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/LepJetChargeReliability/aMCatNLO/jet/TMVAClassification_DNN.weights.xml";
  cout << "define tmvareader"<< endl;
  myreader_ChReliab_jet=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_ChReliab_jet->AddVariable("bjet_eta",&bjet_eta);
  myreader_ChReliab_jet->AddVariable("bmuon_pt",&bmuon_pt);
  myreader_ChReliab_jet->AddVariable("belectron_p_jetrestf",&belectron_p_jetrestf);
  myreader_ChReliab_jet->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader_ChReliab_jet->AddVariable("belectron_reltrkiso",&belectron_reltrkiso);
  myreader_ChReliab_jet->AddVariable("belectron_pt",&belectron_pt);
  myreader_ChReliab_jet->AddVariable("belectron_nsip3d",&belectron_nsip3d);
  myreader_ChReliab_jet->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader_ChReliab_jet->AddVariable("belectron_phi",&belectron_phi);
  myreader_ChReliab_jet->AddVariable("bmuon_nsip3d",&bmuon_nsip3d);
  myreader_ChReliab_jet->AddVariable("belectron_ptwrtbjet",&belectron_ptwrtbjet);
  myreader_ChReliab_jet->AddVariable("bjet_phi",&bjet_phi);
  myreader_ChReliab_jet->AddVariable("bmuon_p_jetrestf",&bmuon_p_jetrestf);
  myreader_ChReliab_jet->AddVariable("belectron_eta",&belectron_eta);
  myreader_ChReliab_jet->AddVariable("belectron_dR_l_j",&belectron_dR_l_j);
  myreader_ChReliab_jet->AddVariable("bmuon_ptwrtbjet",&bmuon_ptwrtbjet);
  myreader_ChReliab_jet->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader_ChReliab_jet->AddVariable("bmuon_phi",&bmuon_phi);
  myreader_ChReliab_jet->AddVariable("belectron_IsGsfCtfScPixChargeConsistent",&belectron_IsGsfCtfScPixChargeConsistent);
  myreader_ChReliab_jet->AddVariable("bmuon_dR_l_j",&bmuon_dR_l_j);
  myreader_ChReliab_jet->AddVariable("bmuon_reltrkiso",&bmuon_reltrkiso);
  myreader_ChReliab_jet->AddVariable("bjet_pt",&bjet_pt);
  myreader_ChReliab_jet->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader_ChReliab_jet->AddVariable("bmuon_eta",&bmuon_eta);
  myreader_ChReliab_jet->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);

  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_ChReliab_jet->BookMVA("PyKeras::DNN",xmlfile);
  cout << "[myreader_ChReliab_jet] Eval for Test" << endl;
  Float_t ret=myreader_ChReliab_jet->EvaluateMVA("PyKeras::DNN");
  cout << ret << endl;


}



void TTsemilep_ChargeReliability::initJetAssignModel_muon(){//TTsemilepJetAssign/2312/v1
  //TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/2312/v1/muon/TMVAClassification_DNN.weights.xml";//training only using events with matched jets 
  TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/add_unmatchedjet_event/muon/TMVAClassification_DNN.weights.xml";//add nonmatchedjet events

  cout << "define tmvareader"<< endl;
  myreader_JetAssign_muon=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_JetAssign_muon->AddVariable("met_pt",&met_pt);
  myreader_JetAssign_muon->AddVariable("met_phi",&met_phi);
  myreader_JetAssign_muon->AddVariable("muon_pt",&muon_pt);
  myreader_JetAssign_muon->AddVariable("muon_eta",&muon_eta);
  myreader_JetAssign_muon->AddVariable("muon_phi",&muon_phi);
  myreader_JetAssign_muon->AddVariable("blep_pt",&blep_pt);
  myreader_JetAssign_muon->AddVariable("blep_eta",&blep_eta);
  myreader_JetAssign_muon->AddVariable("blep_phi",&blep_phi);
  myreader_JetAssign_muon->AddVariable("blep_E",&blep_E);
  myreader_JetAssign_muon->AddVariable("bhad_pt",&bhad_pt);
  myreader_JetAssign_muon->AddVariable("bhad_eta",&bhad_eta);
  myreader_JetAssign_muon->AddVariable("bhad_phi",&bhad_phi);
  myreader_JetAssign_muon->AddVariable("bhad_E",&bhad_E);
  myreader_JetAssign_muon->AddVariable("q1jet_pt",&q1jet_pt);
  myreader_JetAssign_muon->AddVariable("q1jet_eta",&q1jet_eta);
  myreader_JetAssign_muon->AddVariable("q1jet_phi",&q1jet_phi);
  myreader_JetAssign_muon->AddVariable("q1jet_E",&q1jet_E);
  myreader_JetAssign_muon->AddVariable("q2jet_pt",&q2jet_pt);
  myreader_JetAssign_muon->AddVariable("q2jet_eta",&q2jet_eta);
  myreader_JetAssign_muon->AddVariable("q2jet_phi",&q2jet_phi);
  myreader_JetAssign_muon->AddVariable("q2jet_E",&q2jet_E);
  myreader_JetAssign_muon->AddVariable("WhadCand_mass",&WhadCand_mass);
  myreader_JetAssign_muon->AddVariable("ThadCand_mass",&ThadCand_mass);

  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_JetAssign_muon->BookMVA("PyKeras::DNN",xmlfile);
  cout << "[myreader_JetAssign_muon] Eval for Test" << endl;
  Float_t ret=myreader_JetAssign_muon->EvaluateMVA("PyKeras::DNN");
  cout << ret << endl;


}



void TTsemilep_ChargeReliability::initJetAssignModel_electron(){//TTsemilepJetAssign/2312/v1
  //TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/2312/v1/electron/TMVAClassification_DNN.weights.xml";//training only using events with matched jets
  TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/add_unmatchedjet_event/electron/TMVAClassification_DNN.weights.xml";//add nonmatchedjet events
  cout << "define tmvareader"<< endl;
  myreader_JetAssign_electron=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_JetAssign_electron->AddVariable("met_pt",&met_pt);
  myreader_JetAssign_electron->AddVariable("met_phi",&met_phi);
  myreader_JetAssign_electron->AddVariable("electron_pt",&electron_pt);
  myreader_JetAssign_electron->AddVariable("electron_eta",&electron_eta);
  myreader_JetAssign_electron->AddVariable("electron_phi",&electron_phi);
  myreader_JetAssign_electron->AddVariable("blep_pt",&blep_pt);
  myreader_JetAssign_electron->AddVariable("blep_eta",&blep_eta);
  myreader_JetAssign_electron->AddVariable("blep_phi",&blep_phi);
  myreader_JetAssign_electron->AddVariable("blep_E",&blep_E);
  myreader_JetAssign_electron->AddVariable("bhad_pt",&bhad_pt);
  myreader_JetAssign_electron->AddVariable("bhad_eta",&bhad_eta);
  myreader_JetAssign_electron->AddVariable("bhad_phi",&bhad_phi);
  myreader_JetAssign_electron->AddVariable("bhad_E",&bhad_E);
  myreader_JetAssign_electron->AddVariable("q1jet_pt",&q1jet_pt);
  myreader_JetAssign_electron->AddVariable("q1jet_eta",&q1jet_eta);
  myreader_JetAssign_electron->AddVariable("q1jet_phi",&q1jet_phi);
  myreader_JetAssign_electron->AddVariable("q1jet_E",&q1jet_E);
  myreader_JetAssign_electron->AddVariable("q2jet_pt",&q2jet_pt);
  myreader_JetAssign_electron->AddVariable("q2jet_eta",&q2jet_eta);
  myreader_JetAssign_electron->AddVariable("q2jet_phi",&q2jet_phi);
  myreader_JetAssign_electron->AddVariable("q2jet_E",&q2jet_E);
  myreader_JetAssign_electron->AddVariable("WhadCand_mass",&WhadCand_mass);
  myreader_JetAssign_electron->AddVariable("ThadCand_mass",&ThadCand_mass);

  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_JetAssign_electron->BookMVA("PyKeras::DNN",xmlfile);
  cout << "[myreader_JetAssign_electron] Eval for Test" << endl;
  Float_t ret=myreader_JetAssign_electron->EvaluateMVA("PyKeras::DNN");
  cout << ret << endl;


}



void TTsemilep_ChargeReliability::InitValues(){
  
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



void TTsemilep_ChargeReliability::initializeAnalyzer(){
  

  nevt=0., nevt_samebb=0.;
  cout << "[initialize DNN models]" << endl;
  SKFLAT_WD=getenv("SKFlat_WD");
  initJetAssignModel_muon();
  initJetAssignModel_electron();

  initChargeReliabilityModel_muon();
  initChargeReliabilityModel_electron();
  initChargeReliabilityModel_jet();

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
  cout << "[TTsemilep_ChargeReliability::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;



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
void TTsemilep_ChargeReliability::AnalyzeLHE(){
  
  // == init
  myLHE.IsMuonChannel=false;
  myLHE.IsElectronChannel=false;
  myLHE.IsTauChannel=false;
  myLHE.LeptonCharge=0;
  //=========
  int LHEsize = LHEs.size();
  //cout << "LHEsize=" << LHEsize << endl;
  
  int status=-999, pid=-999;
  //double pz=-999;
  //double E=-999, charge=-999;
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

}

void TTsemilep_ChargeReliability::AnalyzeGEN(){
  GENs=GetGens();
  LightJetsTruePIDs.clear();//W->qq'
  unsigned int GENsize = GENs.size();
  int nlightquark_mother_not_status21=0;//isr's mother status==21(21:incoming parton)
  //int idx_bquark=-1, idx_bbarquark=-1;
  vector<int> idx_lightquark;
  for(unsigned int i = 0 ; i < GENsize ; i++){
    int pid=GENs[i].PID();
    int status=GENs[i].Status();
    int mother=GENs[i].MotherIndex();
    int isHardProcess=GENs[i].isHardProcess();
    if (isHardProcess && (status!=21) && GENs[mother].Status()!=21 && abs(pid)<5) {
      nlightquark_mother_not_status21+=1;
      idx_lightquark.push_back(i);
    }
    /*
    if (isHardProcess && (status!=21)){
      if(pid==5){
	idx_bquark=i;
      }
      else if(pid==-5){
	idx_bbarquark=i;
      }
    }
    */
  }
  //-----quarks pid from W->qq'----// 
  myGEN.Whad_q1_pid=GENs[idx_lightquark[0]].PID();
  myGEN.Whad_q2_pid=GENs[idx_lightquark[1]].PID();

  //----to check gen level info----//
  //--skip>>>
  /*
  myGEN.vWhad.SetPxPyPzE(0,0,0,0);
  myGEN.vThad.SetPxPyPzE(0,0,0,0);
  for(unsigned int i = 0 ; i < idx_lightquark.size(); i++){
    myGEN.vWhad+=GENs[idx_lightquark[i]];
    myGEN.vThad+=GENs[idx_lightquark[i]];
  }
  if(myLHE.bLep_charge>0){//b from THad_charge<0 -> bquark
    myGEN.vThad+=GENs[idx_bquark];
  }
  else{
    myGEN.vThad+=GENs[idx_bbarquark];
  }

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
  */
}



bool TTsemilep_ChargeReliability::TTbarMuReco(){
  //Tag only 1 muon 
  vector<int> idx_Tmuon;
  vector<Muon> v_Tmuon;
  
  double maxpt=-100.;
  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double pt=AllMuons[i].Pt();
    double eta=AllMuons[i].Eta();
    bool passID=AllMuons[i].PassID("POGLoose");
    bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    //double reliso=AllMuons[i].RelIso();
    if(fabs(eta) > 2.5) continue;
    if(pt < 10) continue;
    if (!passID) continue;
    if (!passISO) continue;
    if (pt > maxpt) {
      maxpt=pt;
    }
    idx_Tmuon.push_back(i);
    v_Tmuon.push_back(AllMuons[i]);
  }
  if (idx_Tmuon.size()!=1) return 0; // 2nd muon veto
  if (!AllMuons[idx_Tmuon[0]].PassID("POGMedium")) return 0 ;
  if (maxpt < TriggerSafeCut_muon) return 0;
  if(!IsDATA) {
    vector<Lepton*> leps=MakeLeptonPointerVector(v_Tmuon);
    mu_trigsf=GetLeptonTriggerORSF(ev, MuonTriggerNames, MuonTriggerSFKeys, leps,0,0,"");
    Lepton* _mu1=leps.at(0);
    mu_recosf=fEff->GetEfficiencySF("Muon_RECO",_mu1,0,0);
    mu_idsf=fEff->GetEfficiencySF("Muon_MediumID_trkIsoLoose",_mu1,0,0);
    mu_trksf=fEff->GetEfficiencySF("Muon_Tracking",_mu1,0,0);
  }
  myRECO.idx_Tmuon=idx_Tmuon[0];
  return 1;
}

bool TTsemilep_ChargeReliability::TTbarElReco(){
  //Tag only 1 electron 
  vector<int> idx_Telectron;
  vector<Electron> v_Telectron;
  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=AllElectrons[i].Pt();
    double eta=AllElectrons[i].Eta();
    bool passID=AllElectrons[i].PassID("passLooseID");
    if(fabs(eta) > 2.5) continue;
    if(pt < 10) continue;
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
  myRECO.idx_Telectron=idx_Telectron[0];
  return 1;
}


bool TTsemilep_ChargeReliability::CheckJets(){
  double btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
  //double bveto_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Loose);
  unsigned int _Nb=0;
  //unsigned int _Nbbar=0;

  tightjets.clear();
  tightbjets.clear();

  vector<Jet> alltightjets;//For btagSF
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
    else{
      tightjets.push_back(AllJets[i]);
    }
    alltightjets.push_back(AllJets[i]);
  }//end of jet loop

  if(!IsDATA){
    //https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods
    btagsf = mcCorr->GetBTaggingReweight_1a(alltightjets, jtp);
    weight*=btagsf;
  }
  FillHist("AfterJetLoop/Nb/"+ProcessName,_Nb, weight, 10, 0, 10);
  if(_Nb!=2) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"exactly_2_bjets",weight);

  tightjetsize=tightjets.size();
  if (tightjetsize < 2) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"light_tightjet_size_over_2",weight);
  
  //----Set input values of lep and met(NON-JET OBJS)---//
  met_pt=PuppiMET_pt,met_phi=PuppiMET_phi;
  if (myRECO.passMuonTriggerAndTTbarMu){//if single muon ttbar semilep
    muon_pt=l1.Pt();muon_eta=l1.Eta();muon_phi=l1.Phi();
  }
  else{//single electron ttbar semilep
    electron_pt=l1.Pt();electron_eta=l1.Eta();electron_phi=l1.Phi();
  }

  //----Set Member variables for DNN(Jet assignment)----//
  double _max_DNN=-100.;
  int idxset_dnn[4]={-1,-1,-1,-1};
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
	  if(tightjets[iq1].Pt()>tightjets[iq2].Pt()){//"q1jet pt > q2jet pt"
	    q1jet_pt=tightjets[iq1].Pt();
	    q1jet_eta=tightjets[iq1].Eta();
	    q1jet_phi=tightjets[iq1].Phi();
	    q1jet_E=tightjets[iq1].E();
	    q2jet_pt=tightjets[iq2].Pt();
	    q2jet_eta=tightjets[iq2].Eta();
	    q2jet_phi=tightjets[iq2].Phi();
	    q2jet_E=tightjets[iq2].E();
	  }
	  else{//"q1jet pt > q2jet pt must be "
	    q1jet_pt=tightjets[iq2].Pt();
	    q1jet_eta=tightjets[iq2].Eta();
	    q1jet_phi=tightjets[iq2].Phi();
	    q1jet_E=tightjets[iq2].E();
	    q2jet_pt=tightjets[iq1].Pt();
	    q2jet_eta=tightjets[iq1].Eta();
	    q2jet_phi=tightjets[iq1].Phi();
	    q2jet_E=tightjets[iq1].E();
	  }
	  //WhadCand_mass // ThadCand_mass
	  TLorentzVector _Whad,_Thad;
	  _Whad=tightjets[iq1]+tightjets[iq2];
	  _Thad=tightjets[iq1]+tightjets[iq2]+tightbjets[ib2];
	  WhadCand_mass=myRECO.Whad.M();
	  ThadCand_mass=myRECO.Thad.M();
	  //---dnn---//
	  double _score=-100;
	  //evaluate score
	  if(myRECO.passMuonTriggerAndTTbarMu){
	    _score=myreader_JetAssign_muon->EvaluateMVA("PyKeras::DNN");
	  }
	  else{
	    _score=myreader_JetAssign_electron->EvaluateMVA("PyKeras::DNN");
	  }
	  //--find maximum score
	  if(_score>_max_DNN){
	    _max_DNN=_score;
	    idxset_dnn[0]=ib1, idxset_dnn[1]=ib2, idxset_dnn[2]=iq1, idxset_dnn[3]=iq2;
	  }//[END] if score > maxscore
	}//[END]iq2 loop
      }//[END]iq1 loop
    }//[END]ib2loop
  }//[END]ib1loop
  //[END] all permutations
  //{ib1,ib2,iq1,iq2} ->ib1 : b from leptonic top decay // ib2 : b from hadronic top decay 

  //---DNN---
  TLorentzVector Whad_dnn,Thad_dnn;
  int ib1=idxset_dnn[0], ib2=idxset_dnn[1], iq1=idxset_dnn[2], iq2=idxset_dnn[3];
  Whad_dnn=tightjets[iq1]+tightjets[iq2];
  Thad_dnn=tightjets[iq1]+tightjets[iq2]+tightbjets[ib2];
  //FillHist("2b_over2j/Whad_M/"+ProcessName,Whad_dnn.M(), weight, 50, 0, 200);
  //FillHist("2b_over2j/Thad_M/"+ProcessName,Thad_dnn.M(), weight, 100, 0, 350);
  //-----set the indices of blep/bhad/q1/q2
  myRECO.tightbjet_idx_bLep=ib1;
  myRECO.tightbjet_idx_bHad=ib2;
  myRECO.tightjet_idx_q1=iq1;
  myRECO.tightjet_idx_q2=iq2;
  

  SetProcessTagTTLJ();
  
  /*
  if(!IsDATA){
    //bHadMatchName
    int reco_bHad_true_flavour=tightbjets[myRECO.tightbjet_idx_bHad].partonFlavour();
    if(reco_bHad_true_flavour==5){
      bHadMatchName="True_bHadJet";
    }
    else if(reco_bHad_true_flavour==-5){
      bHadMatchName="True_bbarHadJet";
    }
    else{
      bHadMatchName="Fail_bMatchHadJet";
    }

    int reco_bLep_true_flavour=tightbjets[myRECO.tightbjet_idx_bLep].partonFlavour();
    if(reco_bLep_true_flavour==5){
      bLepMatchName="True_bLepJet";
    }
    else if(reco_bLep_true_flavour==-5){
      bLepMatchName="True_bbarHadJet";
    }
    else{
      bLepMatchName="Fail_bMatchHadJet";
    }
  }
  */
  ///Set Leptonic Top Transverse momenta
  TLorentzVector vt_l=GetTransverseVector(l1);//---Make a Lepton 4-Vector whose pz is zero.
  TLorentzVector vt_met=GetTransverseVector(met_pt,met_phi);//---Make a met 4-Vector whose pz is zero.
  TLorentzVector vt_blep=GetTransverseVector(tightbjets[myRECO.tightbjet_idx_bHad]);//---Make a blep 4-Vector whose pz is zero.
  myRECO.vt_lep_top=(vt_l+vt_met+vt_blep);
  myRECO.vt_lep_W=vt_met+vt_l;
  return 1;
}

void TTsemilep_ChargeReliability::SetProcessTagTTLJ(){
  if(IsDATA) return;
  if(MCSample.Contains("TTLJ")){//if ttlj which is the main process    
    int reco_bHad_true_flavour=tightbjets[myRECO.tightbjet_idx_bHad].partonFlavour();
    if(reco_bHad_true_flavour==5){
      //ProcessName=MCSample+"_bHadJet_true_bmatch";
      bHadTrueMatchTag="_bHadJet_true_bmatch";
    }
    else if(reco_bHad_true_flavour==-5){
      //ProcessName=MCSample+"_bHadJet_true_bbarmatch";
      bHadTrueMatchTag="_bHadJet_true_bbarmatch";
    }
    else{
      //ProcessName=MCSample+"_bHadJet_Unmatched";
      bHadTrueMatchTag="_bHadJet_Unmatched";
    }

    ////
    int reco_bLep_true_flavour=tightbjets[myRECO.tightbjet_idx_bLep].partonFlavour();
    if(reco_bLep_true_flavour==5){
      //ProcessName=MCSample+"_bLepJet_true_bmatch";
      bLepTrueMatchTag="_bLepJet_true_bmatch";
    }
    else if(reco_bLep_true_flavour==-5){
      //ProcessName=MCSample+"_bLepJet_true_bbarmatch";
      bLepTrueMatchTag="_bLepJet_true_bbarmatch";
    }
    else{
      //ProcessName=MCSample+"_bLepJet_Unmatched";
      bLepTrueMatchTag="_bLepJet_Unmatched";
    }
  }
  else{
    bHadTrueMatchTag="";
    bLepTrueMatchTag="";
  }
}

void TTsemilep_ChargeReliability::AddProcessTagTTLJ(){
  if(IsDATA) return;
  if(_Is_bHad){
    ProcessName=MCSample+bHadTrueMatchTag;
  }else{
    ProcessName=MCSample+bLepTrueMatchTag;
  }
}

void TTsemilep_ChargeReliability::Check_bJet_Charge(){
  //---bHadJet
  TTsemilep_ChargeReliability::Set_bJet(true);//set target bjet to bHad and eval relibilities
  //----bLepJet
  TTsemilep_ChargeReliability::Set_bJet(false);//set target bjet to bLep and eval relibilities
  //--Now bHad, Lepton in bHad, bLep, Leptons in bLep are set!!!
  //What histograms to Draw....??
  //what to measure => 
  //A. efficiency of charge reliability cut
  //B. accuracy of charge determination of given bjet.
  // ---- accuracy(real + charge bjet)
  //       =  [true +bjet meausred as +]/[true +bjet]
  
  //--- Think about categories---
  //(1) all event
  //(2) category by tag-lepton(prompt lepton)

  //----[ bHad side ]
  //** here, tag-lepton charge~==true charge
  //(3) Good bHad -----> [tag-lepton charge >0] ---->[Measured bJetCharge>0]  
  //                                           ----->[Meausred bJetCharge<0]
  //
  //                     [tag-lepton charge <0]----->[Meausred bJetCharge>0]
  //                                           ----->[Meausred bJetCharge<0]

  //(4) Bad  bHad -----> [tag-lepton charge >0] ---->[Measured bJetCharge>0]  
  //                                           ----->[Meausred bJetCharge<0]
  //
  //                     [tag-lepton charge <0]----->[Meausred bJetCharge>0]
  //                                           ----->[Meausred bJetCharge<0]

  //(5) Good  bMuon_in_bHad -----> [tag-lepton charge >0]----->[Measured bMuonCharge>0]  
  //                                                     ----->[Meausred bMuonCharge<0]
  //
  //                                [tag-lepton charge <0]----->[Meausred bMuonCharge>0]
  //                                                      ----->[Meausred bMuonCharge<0]

  //(6) Good  bElectron_in_bHad ----->[tag-lepton charge >0]----->[Measured bElectronCharge>0]  
  //                                                        ----->[Meausred bElectronCharge<0]
  //
  //                                  [tag-lepton charge <0]----->[Meausred bElectronCharge>0]
  //                                                        ----->[Meausred bElectronCharge<0]


  //----[ bLep side ]
  //(7) Good bLep -----> [tag-lepton charge >0] ---->[Measured bJetCharge>0]  
  //                                           ----->[Meausred bJetCharge<0]
  //
  //                     [tag-lepton charge <0]----->[Meausred bJetCharge>0]
  //                                           ----->[Meausred bJetCharge<0]

  //(8) Bad  bLep -----> [tag-lepton charge >0] ---->[Measured bJetCharge>0]  
  //                                           ----->[Meausred bJetCharge<0]
  //
  //                     [tag-lepton charge <0]----->[Meausred bJetCharge>0]
  //                                           ----->[Meausred bJetCharge<0]

  //(9) Good  bMuon_in_bLep -----> [tag-lepton charge >0]----->[Measured bMuonCharge>0]  
  //                                                     ----->[Meausred bMuonCharge<0]
  //
  //                                [tag-lepton charge <0]----->[Meausred bMuonCharge>0]
  //                                                      ----->[Meausred bMuonCharge<0]

  //(10) Good  bElectron_in_bLep ----->[tag-lepton charge >0]----->[Measured bElectronCharge>0]  
  //                                                        ----->[Meausred bElectronCharge<0]
  //
  //                                  [tag-lepton charge <0]----->[Meausred bElectronCharge>0]
  //                                                        ----->[Meausred bElectronCharge<0]



  vector<TString> v_prefix;
  v_prefix.push_back("TTbarLep");
  v_prefix.push_back(ChannelLep);

  for(unsigned int i = 0; i < 2; i++){
    TString prefix=v_prefix[i];
    TString suffix="";

    //----bHadJetSide----//
    _Is_bHad=true;
    AddProcessTagTTLJ();
    suffix="";
    FillHist_bJet(prefix+suffix);
    //-----bMuon_in_bHad
    suffix="";
    if(bmuon_in_bHad.IsExist){
      suffix="__bMuonInbHadPass";
      FillHist_bmuon_in_bHad(prefix+suffix);
      FillHist_bJet(prefix+suffix);
      if(myRECO.TagLeptonCharge > 0){
	suffix="__bMuonInbHadPass__TagLepPlus";
	FillHist_bmuon_in_bHad(prefix+suffix);
	FillHist_bJet(prefix+suffix);
	if(bmuon_in_bHad.charge>0){
	  suffix="__bMuonInbHadPass__TagLepPlus__MeasuredPlus";
	  FillHist_bmuon_in_bHad(prefix+suffix);
	  FillHist_bJet(prefix+suffix);
	}
	else{
	  suffix="__bMuonInbHadPass__TagLepPlus__MeasuredMinus";
	  FillHist_bmuon_in_bHad(prefix+suffix);
	  FillHist_bJet(prefix+suffix);
	}
      }//[END]if TagLepPlus
      else{// --if TagLepMinus
	suffix="__bMuonInbHadPass__TagLepMinus";
        FillHist_bmuon_in_bHad(prefix+suffix);
        FillHist_bJet(prefix+suffix);
	if(bmuon_in_bHad.charge>0){
          suffix="__bMuonInbHadPass__TagLepMinus__MeasuredPlus";
          FillHist_bmuon_in_bHad(prefix+suffix);
          FillHist_bJet(prefix+suffix);
	}
	else{
	  suffix="__bMuonInbHadPass__TagLepMinus__MeasuredMinus";
          FillHist_bmuon_in_bHad(prefix+suffix);
          FillHist_bJet(prefix+suffix);
	}//[END]if Meausred Minus 
      }//[End TagLepMinus]
    }//[END]bmuon_in_bHad Exists


    
    //-----bElectron_in_bHad
    else if(belectron_in_bHad.IsExist){
      suffix="__bElectronInbHadPass";
      FillHist_belectron_in_bHad(prefix+suffix);
      FillHist_bJet(prefix+suffix);
      if(myRECO.TagLeptonCharge > 0){
	suffix="__bElectronInbHadPass__TagLepPlus";
	FillHist_belectron_in_bHad(prefix+suffix);
	FillHist_bJet(prefix+suffix);
	if(belectron_in_bHad.charge>0){
	  suffix="__bElectronInbHadPass__TagLepPlus__MeasuredPlus";
	  FillHist_belectron_in_bHad(prefix+suffix);
	  FillHist_bJet(prefix+suffix);
	}
	else{
	  suffix="__bElectronInbHadPass__TagLepPlus__MeasuredMinus";
	  FillHist_belectron_in_bHad(prefix+suffix);
	  FillHist_bJet(prefix+suffix);
	}
      }//[END]if TagLepPlus
      else{// --if TagLepMinus
	suffix="__bElectronInbHadPass__TagLepMinus";
        FillHist_belectron_in_bHad(prefix+suffix);
        FillHist_bJet(prefix+suffix);
	if(belectron_in_bHad.charge>0){
          suffix="__bElectronInbHadPass__TagLepMinus__MeasuredPlus";
          FillHist_belectron_in_bHad(prefix+suffix);
          FillHist_bJet(prefix+suffix);
	}
	else{
	  suffix="__bElectronInbHadPass__TagLepMinus__MeasuredMinus";
          FillHist_belectron_in_bHad(prefix+suffix);
          FillHist_bJet(prefix+suffix);
	}//[END]if Meausred Minus 
      }//[End TagLepMinus]
    }//[END]belectron_in_bHad Exists

    else if(bHadJet.dnn > DNNcut){
      suffix="__bHadPass";
      FillHist_bJet(prefix+suffix);
      if(myRECO.TagLeptonCharge>0){
	suffix="__bHadPass__TagLepPlus";
	FillHist_bJet(prefix+suffix);
	if(bHadJet.JetCharge>0){
	  suffix="__bHadPass__TagLepPlus__MeasurePlus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bHadJet.JetCharge>0
	else if(bHadJet.JetCharge<0){
	  suffix="__bHadPass__TagLepPlus__MeasureMinus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bHadJet.JetCharge<0
	else{
	  suffix="__bHadPass__TagLepPlus__MeasureZero";
	  FillHist_bJet(prefix+suffix);
	}
      }//[END] TagLeptonCharge>0
      else{// --TagLeptonCharge<0
	suffix="__bHadPass__TagLepMinus";
	FillHist_bJet(prefix+suffix);
	if(bHadJet.JetCharge>0){
	  suffix="__bHadPass__TagLepMinus__MeasurePlus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bHadJet.JetCharge>0
	else if(bHadJet.JetCharge<0){
	  suffix="__bHadPass__TagLepMinus__MeasureMinus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bHadJet.JetCharge<0
	else{
	  suffix="__bHadPass__TagLepMinus__MeasureZero";
	  FillHist_bJet(prefix+suffix);
	}
      }//[END] TagLeptonCharge<0

    }//[END] good bHadJet
    else{
      suffix="__bHadFail";
      FillHist_bJet(prefix+suffix);
      if(myRECO.TagLeptonCharge>0){
	suffix="__bHadFail__TagLepPlus";
	FillHist_bJet(prefix+suffix);
	if(bHadJet.JetCharge>0){
	  suffix="__bHadFail__TagLepPlus__MeasurePlus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bHadJet.JetCharge>0
	else if(bHadJet.JetCharge<0){//---bHadJetCharge<0
	  suffix="__bHadFail__TagLepPlus__MeasureMinus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bHadJet.JetCharge<0
	else{
	  suffix="__bHadFail__TagLepPlus__MeasureZero";
	  FillHist_bJet(prefix+suffix);
	}
      }//[END] TagLeptonCharge>0
      else{//--TagLeptonCharge<0
	suffix="__bHadFail__TagLepMinus";
	FillHist_bJet(prefix+suffix);
	if(bHadJet.JetCharge>0){
	  suffix="__bHadFail__TagLepMinus__MeasurePlus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bHadJet.JetCharge>0
	else if(bHadJet.JetCharge<0){
	  suffix="__bHadFail__TagLepMinus__MeasureMinus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bHadJet.JetCharge<0
	else{
	  suffix="__bHadFail__TagLepMinus__MeasureZero";
	  FillHist_bJet(prefix+suffix);
	}
      }//[END] TagLeptonCharge<0
    }//[END] bad bHadJet
    


    //-----Copy hHad lines.....and replace bHad to bLep----//

    //----bLepJet----//
    _Is_bHad=false;
    AddProcessTagTTLJ();
    suffix="";
    FillHist_bJet(prefix+suffix);
    //-----bMuon_in_bLep
    suffix="";
    if(bmuon_in_bLep.IsExist){
      suffix="__bMuonInbLepPass";
      FillHist_bmuon_in_bLep(prefix+suffix);
      FillHist_bJet(prefix+suffix);
      if(myRECO.TagLeptonCharge > 0){
	suffix="__bMuonInbLepPass__TagLepPlus";
	FillHist_bmuon_in_bLep(prefix+suffix);
	FillHist_bJet(prefix+suffix);
	if(bmuon_in_bLep.charge>0){
	  suffix="__bMuonInbLepPass__TagLepPlus__MeasuredPlus";
	  FillHist_bmuon_in_bLep(prefix+suffix);
	  FillHist_bJet(prefix+suffix);
	}
	else{
	  suffix="__bMuonInbLepPass__TagLepPlus__MeasuredMinus";
	  FillHist_bmuon_in_bLep(prefix+suffix);
	  FillHist_bJet(prefix+suffix);
	}
      }//[END]if TagLepPlus
      else{// --if TagLepMinus
	suffix="__bMuonInbLepPass__TagLepMinus";
        FillHist_bmuon_in_bLep(prefix+suffix);
        FillHist_bJet(prefix+suffix);
	if(bmuon_in_bLep.charge>0){
          suffix="__bMuonInbLepPass__TagLepMinus__MeasuredPlus";
          FillHist_bmuon_in_bLep(prefix+suffix);
          FillHist_bJet(prefix+suffix);
	}
	else{
	  suffix="__bMuonInbLepPass__TagLepMinus__MeasuredMinus";
          FillHist_bmuon_in_bLep(prefix+suffix);
          FillHist_bJet(prefix+suffix);
	}//[END]if Meausred Minus 
      }//[End TagLepMinus]
    }//[END]bmuon_in_bLep Exists


    
    //-----bElectron_in_bLep
    else if(belectron_in_bLep.IsExist){
      suffix="__bElectronInbLepPass";
      FillHist_belectron_in_bLep(prefix+suffix);
      FillHist_bJet(prefix+suffix);
      if(myRECO.TagLeptonCharge > 0){
	suffix="__bElectronInbLepPass__TagLepPlus";
	FillHist_belectron_in_bLep(prefix+suffix);
	FillHist_bJet(prefix+suffix);
	if(belectron_in_bLep.charge>0){
	  suffix="__bElectronInbLepPass__TagLepPlus__MeasuredPlus";
	  FillHist_belectron_in_bLep(prefix+suffix);
	  FillHist_bJet(prefix+suffix);
	}
	else{
	  suffix="__bElectronInbLepPass__TagLepPlus__MeasuredMinus";
	  FillHist_belectron_in_bLep(prefix+suffix);
	  FillHist_bJet(prefix+suffix);
	}
      }//[END]if TagLepPlus
      else{// --if TagLepMinus
	suffix="__bElectronInbLepPass__TagLepMinus";
        FillHist_belectron_in_bLep(prefix+suffix);
        FillHist_bJet(prefix+suffix);
	if(belectron_in_bLep.charge>0){
          suffix="__bElectronInbLepPass__TagLepMinus__MeasuredPlus";
          FillHist_belectron_in_bLep(prefix+suffix);
          FillHist_bJet(prefix+suffix);
	}
	else{
	  suffix="__bElectronInbLepPass__TagLepMinus__MeasuredMinus";
          FillHist_belectron_in_bLep(prefix+suffix);
          FillHist_bJet(prefix+suffix);
	}//[END]if Meausred Minus 
      }//[End TagLepMinus]
    }//[END]belectron_in_bLep Exists

    else if(bLepJet.dnn > DNNcut){
      suffix="__bLepPass";
      FillHist_bJet(prefix+suffix);
      if(myRECO.TagLeptonCharge>0){
	suffix="__bLepPass__TagLepPlus";
	FillHist_bJet(prefix+suffix);
	if(bLepJet.JetCharge>0){
	  suffix="__bLepPass__TagLepPlus__MeasurePlus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bLepJet.JetCharge>0
	else if(bLepJet.JetCharge<0){
	  suffix="__bLepPass__TagLepPlus__MeasureMinus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bLepJet.JetCharge<0
	else{
	  suffix="__bLepPass__TagLepPlus__MeasureZero";
	  FillHist_bJet(prefix+suffix);
	}
      }//[END] TagLeptonCharge>0
      else{// --TagLeptonCharge<0
	suffix="__bLepPass__TagLepMinus";
	FillHist_bJet(prefix+suffix);
	if(bLepJet.JetCharge>0){
	  suffix="__bLepPass__TagLepMinus__MeasurePlus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bLepJet.JetCharge>0
	else if(bLepJet.JetCharge<0){
	  suffix="__bLepPass__TagLepMinus__MeasureMinus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bLepJet.JetCharge<0
	else{
	  suffix="__bLepPass__TagLepMinus__MeasureZero";
	  FillHist_bJet(prefix+suffix);
	}
      }//[END] TagLeptonCharge<0

    }//[END] good bLepJet
    else{
      suffix="__bLepFail";
      FillHist_bJet(prefix+suffix);
      if(myRECO.TagLeptonCharge>0){
	suffix="__bLepFail__TagLepPlus";
	FillHist_bJet(prefix+suffix);
	if(bLepJet.JetCharge>0){
	  suffix="__bLepFail__TagLepPlus__MeasurePlus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bLepJet.JetCharge>0
	else if(bLepJet.JetCharge<0){//---bLepJetCharge<0
	  suffix="__bLepFail__TagLepPlus__MeasureMinus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bLepJet.JetCharge<0
	else{
	  suffix="__bLepFail__TagLepPlus__MeasureZero";
	  FillHist_bJet(prefix+suffix);
	}
      }//[END] TagLeptonCharge>0
      else{//--TagLeptonCharge<0
	suffix="__bLepFail__TagLepMinus";
	FillHist_bJet(prefix+suffix);
	if(bLepJet.JetCharge>0){
	  suffix="__bLepFail__TagLepMinus__MeasurePlus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bLepJet.JetCharge>0
	else if(bLepJet.JetCharge<0){
	  suffix="__bLepFail__TagLepMinus__MeasureMinus";
	  FillHist_bJet(prefix+suffix);
	}//[END]bLepJet.JetCharge<0
	else{
	  suffix="__bLepFail__TagLepMinus__MeasureZero";
	  FillHist_bJet(prefix+suffix);
	}
      }//[END] TagLeptonCharge<0
    }//[END] bad bLepJet


    
  }//[END]Category on Prompt Lep















}
TLorentzVector TTsemilep_ChargeReliability::GetTransverseVector(TLorentzVector v){
  //cout << "GetTransverseVector" << endl;
  double px=v.Px();
  double py=v.Py();
  double pz=0.;
  double ee=sqrt(px*px+py*py);
  TLorentzVector ret;
  //cout << "before setpxpypze" << endl;
  ret.SetPxPyPzE(px,py,pz,ee);
  //cout << "[before return]GetTransverseVector" << endl;
  return ret;
}

TLorentzVector TTsemilep_ChargeReliability::GetTransverseVector(double pt, double phi){
  double px=pt*cos(phi);
  double py=pt*sin(phi);
  double pz=0.;
  double ee=sqrt(px*px+py*py);
  TLorentzVector ret;
  ret.SetPxPyPzE(px,py,pz,ee);
  return ret;
}

void TTsemilep_ChargeReliability::FillHist_bJet(TString cutname){
  FillHist_bHadJet(cutname);
  FillHist_bLepJet(cutname);
  FillHist_LeptonicTopSide(cutname);
  FillHist_HadronicTopSide(cutname);
  
}


void TTsemilep_ChargeReliability::FillHist_LeptonicTopSide(TString cutname){


  if(myRECO.passMuonTriggerAndTTbarMu){
    //myRECO.idx_Tmuon
    FillHist(cutname+"/lepton_pt/"+ProcessName,AllMuons[myRECO.idx_Tmuon].Pt(), weight, 100, 0, 100.);
    FillHist(cutname+"/lepton_eta/"+ProcessName,AllMuons[myRECO.idx_Tmuon].Eta(), weight, 100, -3, 3.);
    FillHist(cutname+"/lepton_phi/"+ProcessName,AllMuons[myRECO.idx_Tmuon].Phi(), weight, 100, -4, 4.);

  }
  else{
    FillHist(cutname+"/lepton_pt/"+ProcessName,AllElectrons[myRECO.idx_Telectron].Pt(), weight, 100, 0, 100.);
    FillHist(cutname+"/lepton_eta/"+ProcessName,AllElectrons[myRECO.idx_Telectron].Eta(), weight, 50, -3, 3.);
    FillHist(cutname+"/lepton_phi/"+ProcessName,AllElectrons[myRECO.idx_Telectron].Phi(), weight, 50, -4, 4.);

  }

  FillHist(cutname+"/met_pt/"+ProcessName,met_pt, weight, 50, 0, 200.);
  FillHist(cutname+"/met_phi/"+ProcessName,met_phi, weight, 100, -4, 4.);

  FillHist(cutname+"/MT_LeptonicTop/"+ProcessName,myRECO.vt_lep_top.M(), weight, 50, 0, 400);
  FillHist(cutname+"/MT_LeptonicW/"+ProcessName,myRECO.vt_lep_W.M(), weight, 50, 0, 200);

  FillHist(cutname+"/bLep_pt/"+ProcessName,tightbjets[myRECO.tightbjet_idx_bLep].Pt(), weight, 50, 0, 200);
  FillHist(cutname+"/bLep_eta/"+ProcessName,tightbjets[myRECO.tightbjet_idx_bLep].Eta(), weight, 50, -3, 3);


}
void TTsemilep_ChargeReliability::FillHist_HadronicTopSide(TString cutname){
  FillHist(cutname+"/Whad_M/"+ProcessName,(tightjets[myRECO.tightjet_idx_q1]+tightjets[myRECO.tightjet_idx_q2]).M(), weight, 50, 0, 200.);
  FillHist(cutname+"/Thad_M/"+ProcessName,(tightbjets[myRECO.tightbjet_idx_bHad]+tightjets[myRECO.tightjet_idx_q1]+tightjets[myRECO.tightjet_idx_q2]).M(), weight, 100, 0, 350.);
  
}
void TTsemilep_ChargeReliability::FillHist_bHadJet(TString cutname){
  FillHist(cutname+"/bHad_dnn/"+ProcessName,bHadJet.dnn, weight, 50, 0, 1);
  FillHist(cutname+"/bHad_pt/"+ProcessName,bHadJet.pt, weight, 50, 0, 200);
  FillHist(cutname+"/bHad_eta/"+ProcessName,bHadJet.eta, weight, 50, -3, 3);
  FillHist(cutname+"/bHad_charge/"+ProcessName,bHadJet.JetCharge, weight, 50, -1, 1);
  if(doDrawDNNinputs){
    FillHist(cutname+"/bHad_phi/"+ProcessName,bHadJet.phi, weight, 50, -3, 3);
    FillHist(cutname+"/bHad_chargedHadronEnergyFraction/"+ProcessName,bHadJet.chargedHadronEnergyFraction, weight, 50, 0, 1);
    FillHist(cutname+"/bHad_neutralHadronEnergyFraction/"+ProcessName,bHadJet.neutralHadronEnergyFraction,weight, 50, 0, 1);
    FillHist(cutname+"/bHad_neutralEmEnergyFraction/"+ProcessName,bHadJet.neutralEmEnergyFraction, weight, 50, 0, 1);
    FillHist(cutname+"/bHad_chargedEmEnergyFraction/"+ProcessName,bHadJet.chargedEmEnergyFraction, weight, 50, 0, 1);
    FillHist(cutname+"/bHad_muonEnergyFraction/"+ProcessName,bHadJet.muonEnergyFraction, weight, 50, 0, 1);
  }
}

void TTsemilep_ChargeReliability::FillHist_bLepJet(TString cutname){
  FillHist(cutname+"/bLep_dnn/"+ProcessName,bLepJet.dnn, weight, 50, 0, 1);
  FillHist(cutname+"/bLep_pt/"+ProcessName,bLepJet.pt, weight, 50, 0, 200);
  FillHist(cutname+"/bLep_eta/"+ProcessName,bLepJet.eta, weight, 50, -3, 3);
  FillHist(cutname+"/bLep_charge/"+ProcessName,bLepJet.JetCharge, weight, 50, -1, 1);
  if(doDrawDNNinputs){
    FillHist(cutname+"/bLep_phi/"+ProcessName,bLepJet.phi, weight, 50, -3, 3);
    FillHist(cutname+"/bLep_chargedHadronEnergyFraction/"+ProcessName,bLepJet.chargedHadronEnergyFraction, weight, 50, 0, 1);
    FillHist(cutname+"/bLep_neutralHadronEnergyFraction/"+ProcessName,bLepJet.neutralHadronEnergyFraction,weight, 50, 0, 1);
    FillHist(cutname+"/bLep_neutralEmEnergyFraction/"+ProcessName,bLepJet.neutralEmEnergyFraction, weight, 50, 0, 1);
    FillHist(cutname+"/bLep_chargedEmEnergyFraction/"+ProcessName,bLepJet.chargedEmEnergyFraction, weight, 50, 0, 1);
    FillHist(cutname+"/bLep_muonEnergyFraction/"+ProcessName,bLepJet.muonEnergyFraction, weight, 50, 0, 1);
  }
}


void TTsemilep_ChargeReliability::FillHist_bmuon_in_bHad(TString cutname){
  FillHist(cutname+"/bmuon_in_bHad_dnn/"+ProcessName,bmuon_in_bHad.dnn,weight,50,0.,1.);
  FillHist(cutname+"/bmuon_in_bHad_pt/"+ProcessName,bmuon_in_bHad.pt,weight,50,0.,50.);
  FillHist(cutname+"/bmuon_in_bHad_eta/"+ProcessName,bmuon_in_bHad.eta,weight,40,-4.,4.);  
  FillHist(cutname+"/bmuon_in_bHad_charge/"+ProcessName,bmuon_in_bHad.charge,weight,50,-2.,2.);
  if(doDrawDNNinputs){
    FillHist(cutname+"/bmuon_in_bHad_phi/"+ProcessName,bmuon_in_bHad.phi,weight,40,-4.,4.);
    FillHist(cutname+"/bmuon_in_bHad_charge_weighted/"+ProcessName,bmuon_in_bHad.charge*bmuon_in_bHad.dnn,weight,50,-2.,2.);
    FillHist(cutname+"/bmuon_in_bHad_nsip3d/"+ProcessName,bmuon_in_bHad.nsip3d,weight,15,0.,15.);
    FillHist(cutname+"/bmuon_in_bHad_ptwrtbjet/"+ProcessName,bmuon_in_bHad.ptwrtbjet,weight,20,0.,5.);
    FillHist(cutname+"/bmuon_in_bHad_p_jetrestf/"+ProcessName,bmuon_in_bHad.p_jetrestf,weight,20,0.,5.);
    FillHist(cutname+"/bmuon_in_bHad_reltrkiso/"+ProcessName,bmuon_in_bHad.reltrkiso,weight,30,0.,15.);
    FillHist(cutname+"/bmuon_in_bHad_dR_l_j/"+ProcessName,bmuon_in_bHad.dR_l_j,weight,40,0.,0.4);
  }
}
void TTsemilep_ChargeReliability::FillHist_bmuon_in_bLep(TString cutname){
  FillHist(cutname+"/bmuon_in_bLep_dnn/"+ProcessName,bmuon_in_bLep.dnn,weight,50,0.,1.);
  FillHist(cutname+"/bmuon_in_bLep_pt/"+ProcessName,bmuon_in_bLep.pt,weight,50,0.,50.);
  FillHist(cutname+"/bmuon_in_bLep_eta/"+ProcessName,bmuon_in_bLep.eta,weight,40,-4.,4.);
  FillHist(cutname+"/bmuon_in_bLep_charge/"+ProcessName,bmuon_in_bLep.charge,weight,50,-2.,2.);
  if(doDrawDNNinputs){
    FillHist(cutname+"/bmuon_in_bLep_phi/"+ProcessName,bmuon_in_bLep.phi,weight,40,-4.,4.);
    FillHist(cutname+"/bmuon_in_bLep_charge_weighted/"+ProcessName,bmuon_in_bLep.charge*bmuon_in_bLep.dnn,weight,50,-2.,2.);
    FillHist(cutname+"/bmuon_in_bLep_nsip3d/"+ProcessName,bmuon_in_bLep.nsip3d,weight,15,0.,15.);
    FillHist(cutname+"/bmuon_in_bLep_ptwrtbjet/"+ProcessName,bmuon_in_bLep.ptwrtbjet,weight,20,0.,5.);
    FillHist(cutname+"/bmuon_in_bLep_p_jetrestf/"+ProcessName,bmuon_in_bLep.p_jetrestf,weight,20,0.,5.);
    FillHist(cutname+"/bmuon_in_bLep_reltrkiso/"+ProcessName,bmuon_in_bLep.reltrkiso,weight,30,0.,15.);
    FillHist(cutname+"/bmuon_in_bLep_dR_l_j/"+ProcessName,bmuon_in_bLep.dR_l_j,weight,40,0.,0.4);
  }
}
void TTsemilep_ChargeReliability::FillHist_belectron_in_bHad(TString cutname){
  FillHist(cutname+"/belectron_in_bHad_dnn/"+ProcessName,belectron_in_bHad.dnn,weight,50,0.,1.);
  FillHist(cutname+"/belectron_in_bHad_pt/"+ProcessName,belectron_in_bHad.pt,weight,50,0.,50.);  
  FillHist(cutname+"/belectron_in_bHad_eta/"+ProcessName,belectron_in_bHad.eta,weight,40,-4.,4.);
  FillHist(cutname+"/belectron_in_bHad_charge/"+ProcessName,belectron_in_bHad.charge,weight,50,-2.,2.);
  if(doDrawDNNinputs){
    FillHist(cutname+"/belectron_in_bHad_phi/"+ProcessName,belectron_in_bHad.phi,weight,40,-4.,4.);
    FillHist(cutname+"/belectron_in_bHad_charge_weighted/"+ProcessName,belectron_in_bHad.charge*belectron_in_bHad.dnn,weight,50,-2.,2.);
    FillHist(cutname+"/belectron_in_bHad_nsip3d/"+ProcessName,belectron_in_bHad.nsip3d,weight,15,0.,15.);
    FillHist(cutname+"/belectron_in_bHad_ptwrtbjet/"+ProcessName,belectron_in_bHad.ptwrtbjet,weight,20,0.,5.);
    FillHist(cutname+"/belectron_in_bHad_p_jetrestf/"+ProcessName,belectron_in_bHad.p_jetrestf,weight,20,0.,5.);
    FillHist(cutname+"/belectron_in_bHad_reltrkiso/"+ProcessName,belectron_in_bHad.reltrkiso,weight,30,0.,15.);
    FillHist(cutname+"/belectron_in_bHad_dR_l_j/"+ProcessName,belectron_in_bHad.dR_l_j,weight,40,0.,0.4);
    FillHist(cutname+"/belectron_in_bHad_IsGsfCtfScPixChargeConsistent/"+ProcessName,belectron_in_bHad.IsGsfCtfScPixChargeConsistent,weight,2,0.,2.);
  }
}
void TTsemilep_ChargeReliability::FillHist_belectron_in_bLep(TString cutname){
  FillHist(cutname+"/belectron_in_bLep_dnn/"+ProcessName,belectron_in_bLep.dnn,weight,50,0.,1.);
  FillHist(cutname+"/belectron_in_bLep_pt/"+ProcessName,belectron_in_bLep.pt,weight,50,0.,50.);
  FillHist(cutname+"/belectron_in_bLep_eta/"+ProcessName,belectron_in_bLep.eta,weight,40,-4.,4.);
  FillHist(cutname+"/belectron_in_bLep_charge/"+ProcessName,belectron_in_bLep.charge,weight,50,-2.,2.);
  if(doDrawDNNinputs){
    FillHist(cutname+"/belectron_in_bLep_phi/"+ProcessName,belectron_in_bLep.phi,weight,40,-4.,4.);
    FillHist(cutname+"/belectron_in_bLep_charge_weighted/"+ProcessName,belectron_in_bLep.charge*belectron_in_bLep.dnn,weight,50,-2.,2.);
    FillHist(cutname+"/belectron_in_bLep_nsip3d/"+ProcessName,belectron_in_bLep.nsip3d,weight,15,0.,15.);
    FillHist(cutname+"/belectron_in_bLep_ptwrtbjet/"+ProcessName,belectron_in_bLep.ptwrtbjet,weight,20,0.,5.);
    FillHist(cutname+"/belectron_in_bLep_p_jetrestf/"+ProcessName,belectron_in_bLep.p_jetrestf,weight,20,0.,5.);
    FillHist(cutname+"/belectron_in_bLep_reltrkiso/"+ProcessName,belectron_in_bLep.reltrkiso,weight,30,0.,15.);
    FillHist(cutname+"/belectron_in_bLep_dR_l_j/"+ProcessName,belectron_in_bLep.dR_l_j,weight,40,0.,0.4);
    FillHist(cutname+"/belectron_in_bLep_IsGsfCtfScPixChargeConsistent/"+ProcessName,belectron_in_bLep.IsGsfCtfScPixChargeConsistent,weight,2,0.,2.);
  }
}

void TTsemilep_ChargeReliability::Set_bJet(bool Is_bHad){
  _Is_bHad=Is_bHad;//_Is_bHad : class member variable
  if(_Is_bHad){
    _tightbjet_idx=myRECO.tightbjet_idx_bHad;
    //init
    bmuon_in_bHad.IsExist=false;
    belectron_in_bHad.IsExist=false;
  }
  else{
    _tightbjet_idx=myRECO.tightbjet_idx_bLep;
    //init
    bmuon_in_bLep.IsExist=false;
    belectron_in_bLep.IsExist=false;
  }
  bjet_charge=tightbjets[_tightbjet_idx].Charge();
  bjet_pt=min(tightbjets[_tightbjet_idx].Pt(),250.);
  bjet_eta=tightbjets[_tightbjet_idx].Eta();
  bjet_phi=tightbjets[_tightbjet_idx].Phi();
  //bjet_DeepJet=tightbjets[_tightbjet_idx].GetTaggerResult(JetTagging::DeepJet);
  //bjet_DeepJet_CvsL=tightbjets[_tightbjet_idx].GetTaggerResult(JetTagging::DeepJet_CvsL);
  //bjet_DeepJet_CvsB=tightbjets[_tightbjet_idx].GetTaggerResult(JetTagging::DeepJet_CvsB);
  bjet_chargedHadronEnergyFraction=tightbjets[_tightbjet_idx].GetChargedHadronEnergyFraction();
  bjet_neutralHadronEnergyFraction=tightbjets[_tightbjet_idx].GetNeutralHadronEnergyFraction();
  bjet_neutralEmEnergyFraction=tightbjets[_tightbjet_idx].GetNeutralEmEnergyFraction();
  bjet_chargedEmEnergyFraction=tightbjets[_tightbjet_idx].GetChargedEmEnergyFraction();
  bjet_muonEnergyFraction=tightbjets[_tightbjet_idx].GetMuonEnergyFraction();


  //---After set bjet input, set bmuon input and eval relib. of bmuon charge 
  TTsemilep_ChargeReliability::Check_bMuonScore();
  //---After set bjet input, set belectron input and eval relib. of belectron charge 
  TTsemilep_ChargeReliability::Check_bElectronScore();
  
 
  //Eval DNN for jet charge reliability
  if(_Is_bHad){
    bHadJet.dnn=myreader_ChReliab_jet->EvaluateMVA("PyKeras::DNN");
    bHadJet.JetCharge=bjet_charge;
    bHadJet.pt = bjet_pt;
    bHadJet.eta = bjet_eta;
    bHadJet.phi = bjet_phi;
    bHadJet.chargedHadronEnergyFraction=bjet_chargedHadronEnergyFraction;
    bHadJet.neutralHadronEnergyFraction=bjet_neutralHadronEnergyFraction;
    bHadJet.neutralEmEnergyFraction=bjet_neutralEmEnergyFraction;
    bHadJet.chargedEmEnergyFraction=bjet_chargedEmEnergyFraction;
    bHadJet.muonEnergyFraction=bjet_muonEnergyFraction;
  }
  else{
    bLepJet.dnn=myreader_ChReliab_jet->EvaluateMVA("PyKeras::DNN");
    bLepJet.JetCharge=bjet_charge;
    bLepJet.pt = bjet_pt;
    bLepJet.eta = bjet_eta;
    bLepJet.phi = bjet_phi;
    bLepJet.chargedHadronEnergyFraction=bjet_chargedHadronEnergyFraction;
    bLepJet.neutralHadronEnergyFraction=bjet_neutralHadronEnergyFraction;
    bLepJet.neutralEmEnergyFraction=bjet_neutralEmEnergyFraction;
    bLepJet.chargedEmEnergyFraction=bjet_chargedEmEnergyFraction;
    bLepJet.muonEnergyFraction=bjet_muonEnergyFraction;
  }

}  


void TTsemilep_ChargeReliability::Check_bMuonScore(){
  //--Check bMuon--
  
  int bmuon1_idx = -999;
  int bmuon1_charge = -999;
  double bmuon1_dnn = -999;
  double bmuon1_phi = -999;
  double bmuon1_pt = -999;
  double bmuon1_nsip3d = -999;
  double bmuon1_ptwrtbjet = -999;
  double bmuon1_eta = -999;
  double bmuon1_p_jetrestf = -999;
  double bmuon1_reltrkiso = -999;
  double bmuon1_dR_l_j = -999;
  bool IsExist=false;

  double dnn_max=DNNcut;//at least over this cut
  std::vector<int> v_tmva_bmuonidx;
  std::vector<double> v_tmva_bmuon_charge;
  std::vector<double> v_tmva_bmuon_dnn;
  int muonsize_int = muonsize;
  for(int i = 0 ; i < muonsize_int ; i++){
    if(i==myRECO.idx_Tmuon) continue;//if Prompt muon, skip
    TLorentzVector vl(AllMuons[i]);
    vl.Boost(-tightbjets[_tightbjet_idx].BoostVector());
    p_jetrestf=vl.P();//
    dR_l_j=tightbjets[_tightbjet_idx].DeltaR(AllMuons[i]);//
    ip3d=AllMuons[i].IP3D();
    nsip3d=fabs(AllMuons[i].IP3D()/AllMuons[i].IP3Derr());
    reliso=AllMuons[i].RelIso();
    reltrkiso=AllMuons[i].TrkIso()/AllMuons[i].Pt();
    //int muon_charge=AllMuons[i].Charge();
    if(dR_l_j<0.4){
      ///set DNN inputs
      bmuon_phi=AllMuons[i].Phi();
      bmuon_pt=min(AllMuons[i].Pt(),50.);
      bmuon_nsip3d=min(nsip3d,15.);
      double ptwrtbjet=AllMuons[i].P()*sin(AllMuons[i].Angle(tightbjets[_tightbjet_idx].Vect()));
      bmuon_ptwrtbjet=min(ptwrtbjet,5.);
      bmuon_eta=AllMuons[i].Eta();
      bmuon_p_jetrestf=min(p_jetrestf,5.);
      bmuon_reltrkiso=min(reltrkiso,15.);
      bmuon_dR_l_j=dR_l_j;
      //--eval dnn score
      double bmuon_dnn=0.;
      bmuon_dnn=myreader_ChReliab_muon->EvaluateMVA("PyKeras::DNN");
      if(bmuon_dnn > dnn_max){
	bmuon1_idx = i;
	bmuon1_charge = AllMuons[i].Charge();
	bmuon1_dnn = bmuon_dnn;
	bmuon1_phi = bmuon_phi;
	bmuon1_pt  = bmuon_pt;
	bmuon1_nsip3d=bmuon_nsip3d;
	bmuon1_ptwrtbjet=bmuon_ptwrtbjet;
	bmuon1_eta = bmuon_eta;
	bmuon1_p_jetrestf = bmuon_p_jetrestf;
	bmuon1_reltrkiso=bmuon_reltrkiso;
	bmuon1_dR_l_j=bmuon_dR_l_j;
	IsExist=true;
      }
    }
  }//end of muon loop
  if(_Is_bHad){
    bmuon_in_bHad.IsExist=IsExist;
    bmuon_in_bHad.idx=bmuon1_idx;
    bmuon_in_bHad.charge=bmuon1_charge;
    bmuon_in_bHad.dnn=bmuon1_dnn;
    bmuon_in_bHad.phi=bmuon1_phi;
    bmuon_in_bHad.pt=bmuon1_pt;
    bmuon_in_bHad.nsip3d=bmuon1_nsip3d;
    bmuon_in_bHad.ptwrtbjet=bmuon1_ptwrtbjet;
    bmuon_in_bHad.eta=bmuon1_eta;
    bmuon_in_bHad.p_jetrestf=bmuon1_p_jetrestf;
    bmuon_in_bHad.reltrkiso=bmuon1_reltrkiso;
    bmuon_in_bHad.dR_l_j=bmuon1_dR_l_j;
  }
  else{
    bmuon_in_bLep.IsExist=IsExist;
    bmuon_in_bLep.idx=bmuon1_idx;
    bmuon_in_bLep.charge=bmuon1_charge;
    bmuon_in_bLep.dnn=bmuon1_dnn;
    bmuon_in_bLep.phi=bmuon1_phi;
    bmuon_in_bLep.pt=bmuon1_pt;
    bmuon_in_bLep.nsip3d=bmuon1_nsip3d;
    bmuon_in_bLep.ptwrtbjet=bmuon1_ptwrtbjet;
    bmuon_in_bLep.eta=bmuon1_eta;
    bmuon_in_bLep.p_jetrestf=bmuon1_p_jetrestf;
    bmuon_in_bLep.reltrkiso=bmuon1_reltrkiso;
    bmuon_in_bLep.dR_l_j=bmuon1_dR_l_j;

  }
  
}

void TTsemilep_ChargeReliability::Check_bElectronScore(){
  //--Check bElectron--
  bool IsExist=false;
  int belectron1_idx = -999;
  int belectron1_charge = -999;
  double belectron1_dnn = -999;
  double belectron1_phi = -999;
  double belectron1_pt = -999;
  double belectron1_nsip3d = -999;
  double belectron1_ptwrtbjet = -999;
  double belectron1_eta = -999;
  double belectron1_p_jetrestf = -999;
  double belectron1_reltrkiso = -999;
  double belectron1_dR_l_j = -999;
  double belectron1_IsGsfCtfScPixChargeConsistent = -999;
  double dnn_max=DNNcut;//at least over this cut
  int electronsize_int=electronsize;
  for(int i=0; i < electronsize_int; i++){
    if(i==myRECO.idx_Telectron) continue;
    //---Boost electron to jet restframe
    TLorentzVector vl(AllElectrons[i]);
    vl.Boost(-tightbjets[_tightbjet_idx].BoostVector());//_tightbjet_idx
    //variables//
    p_jetrestf=vl.P();//
    dR_l_j=tightbjets[_tightbjet_idx].DeltaR(AllElectrons[i]);//
    ip3d=AllElectrons[i].IP3D();
    nsip3d=fabs(AllElectrons[i].IP3D()/AllElectrons[i].IP3Derr());
    reliso=AllElectrons[i].RelIso();
    reltrkiso=AllElectrons[i].TrkIso()/AllElectrons[i].Pt();
    if(dR_l_j<0.4){

      belectron_phi=AllElectrons[i].Phi();//
      belectron_pt=min(AllElectrons[i].Pt(),50.);//
      belectron_nsip3d=min(nsip3d,15.);//
      double ptwrtbjet=AllElectrons[i].P()*sin(AllElectrons[i].Angle(tightbjets[_tightbjet_idx].Vect()));
      belectron_ptwrtbjet=min(ptwrtbjet,5.);//
      belectron_eta=AllElectrons[i].Eta();//
      belectron_p_jetrestf=min(p_jetrestf,5.);//
      belectron_reltrkiso=min(reltrkiso,15.);//
      belectron_dR_l_j=dR_l_j;//
      belectron_IsGsfCtfScPixChargeConsistent=AllElectrons[i].IsGsfCtfScPixChargeConsistent();//
      double belectron_dnn=0.;
      belectron_dnn=myreader_ChReliab_electron->EvaluateMVA("PyKeras::DNN");
      if (belectron_dnn > dnn_max){
	belectron1_idx = i;
	belectron1_charge = AllElectrons[i].Charge();
	belectron1_dnn = belectron_dnn;
	belectron1_phi = belectron_phi;
	belectron1_pt  = belectron_pt;
	belectron1_nsip3d=belectron_nsip3d;
	belectron1_ptwrtbjet=belectron_ptwrtbjet;
	belectron1_eta = belectron_eta;
	belectron1_p_jetrestf = belectron_p_jetrestf;
	belectron1_reltrkiso=belectron_reltrkiso;
	belectron1_dR_l_j=belectron_dR_l_j;
	belectron1_IsGsfCtfScPixChargeConsistent=belectron_IsGsfCtfScPixChargeConsistent;
	IsExist=true;
      } 

    }
  }//end of electron loop
  if(_Is_bHad){
    belectron_in_bHad.IsExist=IsExist;
    belectron_in_bHad.idx=belectron1_idx;
    belectron_in_bHad.charge=belectron1_charge;
    belectron_in_bHad.dnn=belectron1_dnn;
    belectron_in_bHad.phi=belectron1_phi;
    belectron_in_bHad.pt=belectron1_pt;
    belectron_in_bHad.nsip3d=belectron1_nsip3d;
    belectron_in_bHad.ptwrtbjet=belectron1_ptwrtbjet;
    belectron_in_bHad.eta=belectron1_eta;
    belectron_in_bHad.p_jetrestf=belectron1_p_jetrestf;
    belectron_in_bHad.reltrkiso=belectron1_reltrkiso;
    belectron_in_bHad.dR_l_j=belectron1_dR_l_j;
    belectron_in_bHad.IsGsfCtfScPixChargeConsistent=belectron1_IsGsfCtfScPixChargeConsistent;
  }
  else{
    belectron_in_bLep.IsExist=IsExist;
    belectron_in_bLep.idx=belectron1_idx;
    belectron_in_bLep.charge=belectron1_charge;
    belectron_in_bLep.dnn=belectron1_dnn;
    belectron_in_bLep.phi=belectron1_phi;
    belectron_in_bLep.pt=belectron1_pt;
    belectron_in_bLep.nsip3d=belectron1_nsip3d;
    belectron_in_bLep.ptwrtbjet=belectron1_ptwrtbjet;
    belectron_in_bLep.eta=belectron1_eta;
    belectron_in_bLep.p_jetrestf=belectron1_p_jetrestf;
    belectron_in_bLep.reltrkiso=belectron1_reltrkiso;
    belectron_in_bLep.dR_l_j=belectron1_dR_l_j;
    belectron_in_bLep.IsGsfCtfScPixChargeConsistent=belectron1_IsGsfCtfScPixChargeConsistent;
  }

}
void TTsemilep_ChargeReliability::AnalyzeRECO(){
  //call muon/electron
  vector<Muon> AllMuons_raw=GetAllMuons();
  AllMuons=ScaleMuons(AllMuons_raw,0);//roch. corr.
  muonsize = AllMuons.size();
  AllElectrons=GetAllElectrons();
  electronsize = AllElectrons.size();
  AllJets = GetAllJets();
  jetsize=AllJets.size();

  //(0) Apply some basic cuts
  myRECO.passMuonTrigger=ev.PassTrigger(MuonTriggerNames);
  myRECO.passElectronTrigger=ev.PassTrigger(ElectronTriggerNames);
  //--avoid double-count--//
  if(IsDATA){
    if(DataStream.Contains("Electron") || DataStream.Contains("EG")){
      if(myRECO.passMuonTrigger) return;
    }
  }
  //Check Leptons in Leptonic Top side
  myRECO.goodTTbarMu=TTbarMuReco();
  myRECO.goodTTbarEl=TTbarElReco();

  FillCutflow("cutflow/all/"+ProcessName,"BeforeTrigger",weight);
  myRECO.passMuonTriggerAndTTbarMu=myRECO.passMuonTrigger && myRECO.goodTTbarMu;
  myRECO.passElectronTriggerAndTTbarEl= myRECO.passElectronTrigger && myRECO.goodTTbarEl;
  if((!myRECO.passMuonTriggerAndTTbarMu) && (!myRECO.passElectronTriggerAndTTbarEl)) return;
  //if( (!(myRECO.goodTTbarMu&&myLHE.IsMuonChannel)) && (!(myRECO.goodTTbarEl&&myLHE.IsElectronChannel)) ) return;
  FillCutflow("cutflow/all/"+ProcessName,"AfterTriggerAnd1TightLep",weight);

  if(myRECO.passMuonTriggerAndTTbarMu){ 
    ChannelLep="TTbarMu";
    trigsf=mu_trigsf;
    lep_recosf=mu_recosf;
    lep_idsf=mu_idsf;
    weight=weight*trigsf*lep_recosf*lep_idsf*mu_trksf;
    myRECO.TagLeptonCharge=AllMuons[myRECO.idx_Tmuon].Charge();
  }
  else if(myRECO.passElectronTriggerAndTTbarEl){
    ChannelLep="TTbarEl";
    trigsf=el_trigsf;
    lep_recosf=el_recosf;
    lep_idsf=el_idsf;
    mu_trksf=1.;
    weight=weight*trigsf*lep_recosf*lep_idsf*mu_trksf;
    myRECO.TagLeptonCharge=AllElectrons[myRECO.idx_Telectron].Charge();
  }
  




  ///--Check Jets--///
  if(!TTsemilep_ChargeReliability::CheckJets()) return;
  FillCutflow("cutflow/all/"+ProcessName,"After2b_and_Atleast2Jets",weight);
  //Now we have b jet from hadronic decay of top..
  TTsemilep_ChargeReliability::Check_bJet_Charge();

  
}







void TTsemilep_ChargeReliability::executeEvent(){

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
  _tightbjet_idx=-1;
  InitValues();
  doFillTree=false;

  LHEs=GetLHEs();
  if(ProcessName.Contains("TTLJ"))TTsemilep_ChargeReliability::AnalyzeLHE();
  //if (myLHE.IsTauChannel) return; // not caring tau channel
  if(ProcessName.Contains("TTLJ"))TTsemilep_ChargeReliability::AnalyzeGEN();
  //FillCutflow("cutflow/all/"+ProcessName,"event_start",weight);
  
  TTsemilep_ChargeReliability::AnalyzeRECO();
  
  
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
