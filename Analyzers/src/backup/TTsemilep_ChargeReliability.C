#include "TTsemilep_ChargeReliability.h"
#include <stdlib.h>
#include <stdio.h>

TTsemilep_ChargeReliability::TTsemilep_ChargeReliability(){//
  

  doDebug=false;
  DNNcut=0.5;



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
  double pz=-999,E=-999, charge=-999;
  //cout << "i" << setw(15) << "pid" << setw(15) << "status"  << endl;
  int n_light_quark=0;
  //--Check Lepton--//
  for(int i = 0; i < LHEsize; i++) {
    status=LHEs[i].Status();
    pid=LHEs[i].ID();
    pz=LHEs[i].Pz();
    E=LHEs[i].E();
    charge=LHEs[i].Charge();
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
    pz=LHEs[i].Pz();
    E=LHEs[i].E();
    charge=LHEs[i].Charge();
    //cout << i << setw(15) << pid << setw(15) << status << endl;
  }
}

void TTsemilep_ChargeReliability::AnalyzeGEN(){
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



bool TTsemilep_ChargeReliability::TTbarMuReco(){

  //Tag only 1 muon 
  vector<int> idx_Tmuon;
  vector<Muon> v_Tmuon;
  double this_leptonid_sf=1.;
  double this_trigger_sf=1.;
  double this_iso_sf=1.;

  int i_l1=-1;

  //Because roch. corr. need to find leading pt muon again.
  double maxpt=-100.;
  for(int i = 0 ; i < muonsize; i++ ){
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
      i_l1=i;
    }

    idx_Tmuon.push_back(i);
    v_Tmuon.push_back(AllMuons[i]);

  }


  if (idx_Tmuon.size()!=1) return 0;
  if (!AllMuons[idx_Tmuon[0]].PassID("POGMedium")) return 0 ;
  if (maxpt < TriggerSafeCut_muon) return 0;
  if(!IsDATA) {
    this_leptonid_sf=1.;
    this_iso_sf=1.;
    this_trigger_sf=1.;
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

bool TTsemilep_ChargeReliability::TTbarElReco(){

  //Tag only 1 electron 
  vector<int> idx_Telectron;
  vector<Electron> v_Telectron;
  double this_leptonid_sf=1.;
  double this_trigger_sf=1.;
  double this_iso_sf=1.;


  //Because roch. corr. need to find leading pt electron again.

  for(int i = 0 ; i < electronsize; i++ ){
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






bool TTsemilep_ChargeReliability::CheckJets(){

  double btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
  double bveto_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Loose);

  unsigned int _Nb=0;
  unsigned int _Nbbar=0;
  tightjets.clear();
  tightbjets.clear();
  vector<Jet> alltightjets;
  TLorentzVector l1;
  if(myRECO.passMuonTriggerAndTTbarMu){
    l1=AllMuons[myRECO.idx_Tmuon];
  }
  else if(myRECO.passElectronTriggerAndTTbarEl){
    l1=AllElectrons[myRECO.idx_Telectron];
  }
  //cout << "btag_cut=" << btag_cut << endl;
  for(int i = 0 ; i < jetsize; i ++){


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
  //if(_Nb!=1) return 0;
  //if(_Nbbar!=1) return 0;

  FillCutflow("cutflow/all/"+ProcessName,"exactly_2_bjets",weight);
  //Whad_q1_pid,Whad_q2_pid
  //Whad_q1_genidx,Whad_q2_genidx

  tightjetsize=tightjets.size();
  if (tightjetsize < 2) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"light_tightjet_size_over_2",weight);
  
  //cout << "<light jet flavour>" << endl;

  
  //----Set input values of lep and met(NON-JET OBJS)---//
  met_pt=PuppiMET_pt,met_phi=PuppiMET_phi;
  if (myRECO.passMuonTriggerAndTTbarMu){
    muon_pt=l1.Pt();muon_eta=l1.Eta();muon_phi=l1.Phi();
  }
  else{
    electron_pt=l1.Pt();electron_eta=l1.Eta();electron_phi=l1.Phi();
  }
  double _max_DNN=-100.;
  //double _min_chi2=1000000000000;
  int idxset_dnn[4]={-1,-1,-1,-1};
  //int idxset_chi2[4]={-1,-1,-1,-1};
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
	  WhadCand_mass=myRECO.Whad.M();
	  ThadCand_mass=myRECO.Thad.M();
	  
	  //---dnn---//
	  double _score=-100;
	  if(myRECO.passMuonTriggerAndTTbarMu){
	    _score=myreader_JetAssign_muon->EvaluateMVA("PyKeras::DNN");
	  }
	  else{
	    _score=myreader_JetAssign_electron->EvaluateMVA("PyKeras::DNN");
	  }
	  if(_score>_max_DNN){
	    _max_DNN=_score;
	    idxset_dnn[0]=ib1, idxset_dnn[1]=ib2, idxset_dnn[2]=iq1, idxset_dnn[3]=iq2;
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
  int ib1=idxset_dnn[0], ib2=idxset_dnn[1], iq1=idxset_dnn[2], iq2=idxset_dnn[3];
  Whad_dnn=tightjets[iq1]+tightjets[iq2];
  Thad_dnn=tightjets[iq1]+tightjets[iq2]+tightbjets[ib2];
  FillHist("2b_over2j/Whad_M/"+ProcessName,Whad_dnn.M(), weight, 50, 0, 200);
  FillHist("2b_over2j/Thad_M/"+ProcessName,Thad_dnn.M(), weight, 100, 0, 350);

  myRECO.tightbjet_idx_bLep=ib1;
  myRECO.tightbjet_idx_bHad=ib2;
  myRECO.tightjet_idx_q1=iq1;
  myRECO.tightjet_idx_q2=iq2;

  if(MCSample.Contains("TTLJ")){//if ttlj which is the main process    
    int reco_bHad_true_flavour=tightbjets[myRECO.tightbjet_idx_bHad].partonFlavour();
    //myLHE.bLep_charge
    if(reco_bHad_true_flavour==5){
      ProcessName=MCSample+"_bHadJet_true_bmatch";
    }
    else if(reco_bHad_true_flavour==-5){
      ProcessName=MCSample+"_bHadJet_true_bbarmatch";
    }
    else{
      ProcessName=MCSample+"_bHadJet_Unmatched";
    }
  }
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


  }
  ///Set Leptonic Top Transverse momenta
  TLorentzVector vt_l=GetTransverseVector(l1);
  TLorentzVector vt_met=GetTransverseVector(met_pt,met_phi);
  TLorentzVector vt_blep=GetTransverseVector(tightbjets[myRECO.tightbjet_idx_bHad]);
  myRECO.vt_lep_top=(vt_l+vt_met+vt_blep);
  myRECO.vt_lep_W=vt_met+vt_l;
  return 1;
}

void TTsemilep_ChargeReliability::Check_bHad_Charge(){
  //myRECO.tightbjet_idx_bHad
  TTsemilep_ChargeReliability::Set_bjet();
  


  TTsemilep_ChargeReliability::Check_bMuonScore();
  TTsemilep_ChargeReliability::Check_bElectronScore();
  //Eval DNN for jet charge reliability
  bjet_DNN=myreader_ChReliab_jet->EvaluateMVA("PyKeras::DNN");






  FillHist_bHadJet(ChannelLep);
  FillHist_bHadJet("AllLeptonChannel");
  FillHist_LeptonicTopSide("AllLeptonChannel");
  FillHist_LeptonicTopSide(ChannelLep);
  FillHist_HadronicTopSide("AllLeptonChannel");
  FillHist_HadronicTopSide(ChannelLep);
  if(bjet_DNN > 0.5){
    FillHist_bHadJet(ChannelLep+"_Pass_JetChargeReliability");
    FillHist_bHadJet("AllLeptonChannel_Pass_JetChargeReliability");
    FillHist_LeptonicTopSide(ChannelLep+"_Pass_JetChargeReliability");
    FillHist_LeptonicTopSide("AllLeptonChannel_Pass_JetChargeReliability");
    FillHist_HadronicTopSide(ChannelLep+"_Pass_JetChargeReliability");
    FillHist_HadronicTopSide("AllLeptonChannel_Pass_JetChargeReliability");
    ///-----jet charge +-----
    if(tightbjets[myRECO.tightbjet_idx_bHad].Charge() > 0){

    FillHist_bHadJet(ChannelLep+"_Pass_JetChargeReliability_JetChargePlus");
    FillHist_bHadJet("AllLeptonChannel_Pass_JetChargeReliability_JetChargePlus");
    FillHist_LeptonicTopSide(ChannelLep+"_Pass_JetChargeReliability_JetChargePlus");
    FillHist_LeptonicTopSide("AllLeptonChannel_Pass_JetChargeReliability_JetChargePlus");
    FillHist_HadronicTopSide(ChannelLep+"_Pass_JetChargeReliability_JetChargePlus");
    FillHist_HadronicTopSide("AllLeptonChannel_Pass_JetChargeReliability_JetChargePlus");

    }
    else{

      FillHist_bHadJet(ChannelLep+"_Pass_JetChargeReliability_JetChargeMinus");
      FillHist_bHadJet("AllLeptonChannel_Pass_JetChargeReliability_JetChargeMinus");
      FillHist_LeptonicTopSide(ChannelLep+"_Pass_JetChargeReliability_JetChargeMinus");
      FillHist_LeptonicTopSide("AllLeptonChannel_Pass_JetChargeReliability_JetChargeMinus");
      FillHist_HadronicTopSide(ChannelLep+"_Pass_JetChargeReliability_JetChargeMinus");
      FillHist_HadronicTopSide("AllLeptonChannel_Pass_JetChargeReliability_JetChargeMinus");
      
    }
    ///[END]-----jet charge +-----
  }
  else{//fail jetrelib
    FillHist_bHadJet(ChannelLep+"_Fail_JetChargeReliability");
    FillHist_bHadJet("AllLeptonChannel_Fail_JetChargeReliability");
    FillHist_LeptonicTopSide(ChannelLep+"_Fail_JetChargeReliability");
    FillHist_LeptonicTopSide("AllLeptonChannel_Fail_JetChargeReliability");
    FillHist_HadronicTopSide(ChannelLep+"_Fail_JetChargeReliability");
    FillHist_HadronicTopSide("AllLeptonChannel_Fail_JetChargeReliability");
  }
  if(bmuon1_idx > -1){
    FillHist_bmuon("AllLeptonChannel");
    FillHist_bmuon(ChannelLep);

 
    if(bmuon1_DNN>0.5){
      FillHist_bmuon(ChannelLep+"_Pass_MuonChargeReliability");
      FillHist_bmuon("AllLeptonChannel_Pass_MuonChargeReliability");
      FillHist_bHadJet(ChannelLep+"_Pass_MuonChargeReliability");
      FillHist_bHadJet("AllLeptonChannel_Pass_MuonChargeReliability");
      FillHist_LeptonicTopSide(ChannelLep+"_Pass_MuonChargeReliability");
      FillHist_LeptonicTopSide("AllLeptonChannel_Pass_MuonChargeReliability");
      FillHist_HadronicTopSide(ChannelLep+"_Pass_MuonChargeReliability");
      FillHist_HadronicTopSide("AllLeptonChannel_Pass_MuonChargeReliability");

      if(bmuon1_charge>0){
	FillHist_bmuon(ChannelLep+"_Pass_MuonChargeReliability_MuonChargePlus");
	FillHist_bmuon("AllLeptonChannel_Pass_MuonChargeReliability_MuonChargePlus");
	FillHist_bHadJet(ChannelLep+"_Pass_MuonChargeReliability_MuonChargePlus");
	FillHist_bHadJet("AllLeptonChannel_Pass_MuonChargeReliability_MuonChargePlus");
	FillHist_LeptonicTopSide(ChannelLep+"_Pass_MuonChargeReliability_MuonChargePlus");
	FillHist_LeptonicTopSide("AllLeptonChannel_Pass_MuonChargeReliability_MuonChargePlus");
	FillHist_HadronicTopSide(ChannelLep+"_Pass_MuonChargeReliability_MuonChargePlus");
	FillHist_HadronicTopSide("AllLeptonChannel_Pass_MuonChargeReliability_MuonChargePlus");
      }
      else{
	FillHist_bmuon(ChannelLep+"_Pass_MuonChargeReliability_MuonChargeMinus");
	FillHist_bmuon("AllLeptonChannel_Pass_MuonChargeReliability_MuonChargeMinus");
	FillHist_bHadJet(ChannelLep+"_Pass_MuonChargeReliability_MuonChargeMinus");
	FillHist_bHadJet("AllLeptonChannel_Pass_MuonChargeReliability_MuonChargeMinus");
	FillHist_LeptonicTopSide(ChannelLep+"_Pass_MuonChargeReliability_MuonChargeMinus");
	FillHist_LeptonicTopSide("AllLeptonChannel_Pass_MuonChargeReliability_MuonChargeMinus");
	FillHist_HadronicTopSide(ChannelLep+"_Pass_MuonChargeReliability_MuonChargeMinus");
	FillHist_HadronicTopSide("AllLeptonChannel_Pass_MuonChargeReliability_MuonChargeMinus");

      }

    }
    else{
      FillHist_bmuon(ChannelLep+"_Fail_MuonChargeReliability");
      FillHist_bmuon("AllLeptonChannel_Fail_MuonChargeReliability");
      FillHist_bHadJet(ChannelLep+"_Fail_MuonChargeReliability");
      FillHist_bHadJet("AllLeptonChannel_Fail_MuonChargeReliability");
      FillHist_LeptonicTopSide(ChannelLep+"_Fail_MuonChargeReliability");
      FillHist_LeptonicTopSide("AllLeptonChannel_Fail_MuonChargeReliability");
      FillHist_HadronicTopSide(ChannelLep+"_Fail_MuonChargeReliability");
      FillHist_HadronicTopSide("AllLeptonChannel_Fail_MuonChargeReliability");
    }
  }
  if(belectron1_idx > -1) {
    FillHist_belectron("AllLeptonChannel");
    FillHist_belectron(ChannelLep);
    if(belectron1_DNN>0.5){
      FillHist_belectron(ChannelLep+"_Pass_ElectronChargeReliability");
      FillHist_belectron("AllLeptonChannel_Pass_ElectronChargeReliability");
      FillHist_bHadJet(ChannelLep+"_Pass_ElectronChargeReliability");
      FillHist_bHadJet("AllLeptonChannel_Pass_ElectronChargeReliability");
      FillHist_LeptonicTopSide(ChannelLep+"_Pass_ElectronChargeReliability");
      FillHist_LeptonicTopSide("AllLeptonChannel_Pass_ElectronChargeReliability");
      FillHist_HadronicTopSide(ChannelLep+"_Pass_ElectronChargeReliability");
      FillHist_HadronicTopSide("AllLeptonChannel_Pass_ElectronChargeReliability");
      if(belectron1_charge>0){
	FillHist_belectron(ChannelLep+"_Pass_ElectronChargeReliability_ElectronChargePlus");
	FillHist_belectron("AllLeptonChannel_Pass_ElectronChargeReliability_ElectronChargePlus");
	FillHist_bHadJet(ChannelLep+"_Pass_ElectronChargeReliability_ElectronChargePlus");
	FillHist_bHadJet("AllLeptonChannel_Pass_ElectronChargeReliability_ElectronChargePlus");
	FillHist_LeptonicTopSide(ChannelLep+"_Pass_ElectronChargeReliability_ElectronChargePlus");
	FillHist_LeptonicTopSide("AllLeptonChannel_Pass_ElectronChargeReliability_ElectronChargePlus");
	FillHist_HadronicTopSide(ChannelLep+"_Pass_ElectronChargeReliability_ElectronChargePlus");
	FillHist_HadronicTopSide("AllLeptonChannel_Pass_ElectronChargeReliability_ElectronChargePlus");
      }
      else{
	FillHist_belectron(ChannelLep+"_Pass_ElectronChargeReliability_ElectronChargeMinus");
	FillHist_belectron("AllLeptonChannel_Pass_ElectronChargeReliability_ElectronChargeMinus");
	FillHist_bHadJet(ChannelLep+"_Pass_ElectronChargeReliability_ElectronChargeMinus");
	FillHist_bHadJet("AllLeptonChannel_Pass_ElectronChargeReliability_ElectronChargeMinus");
	FillHist_LeptonicTopSide(ChannelLep+"_Pass_ElectronChargeReliability_ElectronChargeMinus");
	FillHist_LeptonicTopSide("AllLeptonChannel_Pass_ElectronChargeReliability_ElectronChargeMinus");
	FillHist_HadronicTopSide(ChannelLep+"_Pass_ElectronChargeReliability_ElectronChargeMinus");
	FillHist_HadronicTopSide("AllLeptonChannel_Pass_ElectronChargeReliability_ElectronChargeMinus");

      }

    }
    else{
      FillHist_belectron(ChannelLep+"_Fail_ElectronChargeReliability");
      FillHist_belectron("AllLeptonChannel_Fail_ElectronChargeReliability");
      FillHist_bHadJet(ChannelLep+"_Fail_ElectronChargeReliability");
      FillHist_bHadJet("AllLeptonChannel_Fail_ElectronChargeReliability");
      FillHist_LeptonicTopSide(ChannelLep+"_Fail_ElectronChargeReliability");
      FillHist_LeptonicTopSide("AllLeptonChannel_Fail_ElectronChargeReliability");
      FillHist_HadronicTopSide(ChannelLep+"_Fail_ElectronChargeReliability");
      FillHist_HadronicTopSide("AllLeptonChannel_Fail_ElectronChargeReliability");
    }
  }


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

void TTsemilep_ChargeReliability::FillHist_LeptonicTopSide(TString cutname){


  if(myRECO.passMuonTriggerAndTTbarMu){
    //myRECO.idx_Tmuon
    FillHist(cutname+"/lepton_pt/"+ProcessName,AllMuons[myRECO.idx_Tmuon].Pt(), weight, 100, 0, 100.);
    FillHist(cutname+"/lepton_eta/"+ProcessName,AllMuons[myRECO.idx_Tmuon].Eta(), weight, 100, -3, 3.);
    FillHist(cutname+"/lepton_phi/"+ProcessName,AllMuons[myRECO.idx_Tmuon].Phi(), weight, 100, -4, 4.);

    FillHist(cutname+"/lepton_pt/"+bHadMatchName,AllMuons[myRECO.idx_Tmuon].Pt(), weight, 100, 0, 100.);
    FillHist(cutname+"/lepton_eta/"+bHadMatchName,AllMuons[myRECO.idx_Tmuon].Eta(), weight, 100, -3, 3.);
    FillHist(cutname+"/lepton_phi/"+bHadMatchName,AllMuons[myRECO.idx_Tmuon].Phi(), weight, 100, -4, 4.);

  }
  else{
    FillHist(cutname+"/lepton_pt/"+ProcessName,AllElectrons[myRECO.idx_Telectron].Pt(), weight, 100, 0, 100.);
    FillHist(cutname+"/lepton_eta/"+ProcessName,AllElectrons[myRECO.idx_Telectron].Eta(), weight, 50, -3, 3.);
    FillHist(cutname+"/lepton_phi/"+ProcessName,AllElectrons[myRECO.idx_Telectron].Phi(), weight, 50, -4, 4.);

    FillHist(cutname+"/lepton_pt/"+bHadMatchName,AllElectrons[myRECO.idx_Telectron].Pt(), weight, 100, 0, 100.);
    FillHist(cutname+"/lepton_eta/"+bHadMatchName,AllElectrons[myRECO.idx_Telectron].Eta(), weight, 50, -3, 3.);
    FillHist(cutname+"/lepton_phi/"+bHadMatchName,AllElectrons[myRECO.idx_Telectron].Phi(), weight, 50, -4, 4.);

  }

  FillHist(cutname+"/met_pt/"+ProcessName,met_pt, weight, 50, 0, 200.);
  FillHist(cutname+"/met_phi/"+ProcessName,met_phi, weight, 100, -4, 4.);

  FillHist(cutname+"/MT_LeptonicTop/"+ProcessName,myRECO.vt_lep_top.M(), weight, 50, 0, 400);
  FillHist(cutname+"/MT_LeptonicW/"+ProcessName,myRECO.vt_lep_W.M(), weight, 50, 0, 200);

  FillHist(cutname+"/bLep_pt/"+ProcessName,tightbjets[myRECO.tightbjet_idx_bLep].Pt(), weight, 50, 0, 200);
  FillHist(cutname+"/bLep_eta/"+ProcessName,tightbjets[myRECO.tightbjet_idx_bLep].Eta(), weight, 50, -3, 3);

  FillHist(cutname+"/met_pt/"+bHadMatchName,met_pt, weight, 50, 0, 200.);
  FillHist(cutname+"/met_phi/"+bHadMatchName,met_phi, weight, 100, -4, 4.);

  FillHist(cutname+"/MT_LeptonicTop/"+bHadMatchName,myRECO.vt_lep_top.M(), weight, 50, 0, 400);
  FillHist(cutname+"/MT_LeptonicW/"+bHadMatchName,myRECO.vt_lep_W.M(), weight, 50, 0, 200);

  FillHist(cutname+"/bLep_pt/"+bHadMatchName,tightbjets[myRECO.tightbjet_idx_bLep].Pt(), weight, 50, 0, 200);
  FillHist(cutname+"/bLep_eta/"+bHadMatchName,tightbjets[myRECO.tightbjet_idx_bLep].Eta(), weight, 50, -3, 3);



}
void TTsemilep_ChargeReliability::FillHist_HadronicTopSide(TString cutname){
  FillHist(cutname+"/Whad_M/"+ProcessName,(tightjets[myRECO.tightjet_idx_q1]+tightjets[myRECO.tightjet_idx_q2]).M(), weight, 50, 0, 200.);
  FillHist(cutname+"/Whad_M/"+bHadMatchName,(tightjets[myRECO.tightjet_idx_q1]+tightjets[myRECO.tightjet_idx_q2]).M(), weight, 100, 0, 200.);

  FillHist(cutname+"/Thad_M/"+ProcessName,(tightbjets[myRECO.tightbjet_idx_bHad]+tightjets[myRECO.tightjet_idx_q1]+tightjets[myRECO.tightjet_idx_q2]).M(), weight, 100, 0, 350.);
  FillHist(cutname+"/Thad_M/"+bHadMatchName,(tightbjets[myRECO.tightbjet_idx_bHad]+tightjets[myRECO.tightjet_idx_q1]+tightjets[myRECO.tightjet_idx_q2]).M(), weight, 100, 0, 350.);
}
void TTsemilep_ChargeReliability::FillHist_bHadJet(TString cutname){
  FillHist(cutname+"/bHad_dnn/"+ProcessName,bjet_DNN, weight, 50, 0, 1);
  FillHist(cutname+"/bHad_pt/"+ProcessName,tightbjets[myRECO.tightbjet_idx_bHad].Pt(), weight, 50, 0, 200);
  FillHist(cutname+"/bHad_eta/"+ProcessName,tightbjets[myRECO.tightbjet_idx_bHad].Eta(), weight, 50, -3, 3);
  FillHist(cutname+"/bHad_charge/"+ProcessName,tightbjets[myRECO.tightbjet_idx_bHad].Charge(), weight, 50, -1, 1);
  FillHist(cutname+"/bHad_chargedHadronEnergyFraction/"+ProcessName,bjet_chargedHadronEnergyFraction, weight, 50, 0, 1);
  FillHist(cutname+"/bHad_neutralHadronEnergyFraction/"+ProcessName,bjet_neutralHadronEnergyFraction, weight, 50, 0, 1);
  FillHist(cutname+"/bHad_neutralEmEnergyFraction/"+ProcessName,bjet_neutralEmEnergyFraction, weight, 50, 0, 1);
  FillHist(cutname+"/bHad_chargedEmEnergyFraction/"+ProcessName,bjet_chargedEmEnergyFraction, weight, 50, 0, 1);
  FillHist(cutname+"/bHad_muonEnergyFraction/"+ProcessName,bjet_muonEnergyFraction, weight, 50, 0, 1);

  FillHist(cutname+"/bHad_dnn/"+bHadMatchName,bjet_DNN, weight, 50, 0, 1);
  FillHist(cutname+"/bHad_pt/"+bHadMatchName,tightbjets[myRECO.tightbjet_idx_bHad].Pt(), weight, 50, 0, 200);
  FillHist(cutname+"/bHad_eta/"+bHadMatchName,tightbjets[myRECO.tightbjet_idx_bHad].Eta(), weight, 50, -3, 3);
  FillHist(cutname+"/bHad_charge/"+bHadMatchName,tightbjets[myRECO.tightbjet_idx_bHad].Charge(), weight, 50, -1, 1);
  FillHist(cutname+"/bHad_chargedHadronEnergyFraction/"+bHadMatchName,bjet_chargedHadronEnergyFraction, weight, 50, 0, 1);
  FillHist(cutname+"/bHad_neutralHadronEnergyFraction/"+bHadMatchName,bjet_neutralHadronEnergyFraction, weight, 50, 0, 1);
  FillHist(cutname+"/bHad_neutralEmEnergyFraction/"+bHadMatchName,bjet_neutralEmEnergyFraction, weight, 50, 0, 1);
  FillHist(cutname+"/bHad_chargedEmEnergyFraction/"+bHadMatchName,bjet_chargedEmEnergyFraction, weight, 50, 0, 1);
  FillHist(cutname+"/bHad_muonEnergyFraction/"+bHadMatchName,bjet_muonEnergyFraction, weight, 50, 0, 1);


}

void TTsemilep_ChargeReliability::FillHist_bmuon(TString cutname){
  FillHist(cutname+"/bmuon_dnn/"+ProcessName,bmuon1_DNN,weight,50,0.,1.);
  FillHist(cutname+"/bmuon_charge/"+ProcessName,bmuon1_charge,weight,50,-2.,2.);
  FillHist(cutname+"/bmuon_charge_weighted/"+ProcessName,bmuon1_charge*bmuon1_DNN,weight,50,-2.,2.);

  FillHist(cutname+"/bmuon_phi/"+ProcessName,bmuon_phi,weight,40,-4.,4.);
  FillHist(cutname+"/bmuon_pt/"+ProcessName,bmuon_pt,weight,50,0.,50.);
  FillHist(cutname+"/bmuon_nsip3d/"+ProcessName,bmuon_nsip3d,weight,15,0.,15.);
  FillHist(cutname+"/bmuon_ptwrtbjet/"+ProcessName,bmuon_ptwrtbjet,weight,20,0.,5.);
  FillHist(cutname+"/bmuon_eta/"+ProcessName,bmuon_eta,weight,40,-4.,4.);
  FillHist(cutname+"/bmuon_p_jetrestf/"+ProcessName,bmuon_p_jetrestf,weight,20,0.,5.);
  FillHist(cutname+"/bmuon_reltrkiso/"+ProcessName,bmuon_reltrkiso,weight,30,0.,15.);
  FillHist(cutname+"/bmuon_dR_l_j/"+ProcessName,bmuon_dR_l_j,weight,40,0.,0.4);

  FillHist(cutname+"/bmuon_dnn/"+bHadMatchName,bmuon1_DNN,weight,50,0.,1.);
  FillHist(cutname+"/bmuon_charge/"+bHadMatchName,bmuon1_charge,weight,50,-2.,2.);
  FillHist(cutname+"/bmuon_charge_weighted/"+bHadMatchName,bmuon1_charge*bmuon1_DNN,weight,50,-2.,2.);

  FillHist(cutname+"/bmuon_phi/"+bHadMatchName,bmuon_phi,weight,40,-4.,4.);
  FillHist(cutname+"/bmuon_pt/"+bHadMatchName,bmuon_pt,weight,50,0.,50.);
  FillHist(cutname+"/bmuon_nsip3d/"+bHadMatchName,bmuon_nsip3d,weight,15,0.,15.);
  FillHist(cutname+"/bmuon_ptwrtbjet/"+bHadMatchName,bmuon_ptwrtbjet,weight,20,0.,5.);
  FillHist(cutname+"/bmuon_eta/"+bHadMatchName,bmuon_eta,weight,40,-4.,4.);
  FillHist(cutname+"/bmuon_p_jetrestf/"+bHadMatchName,bmuon_p_jetrestf,weight,20,0.,5.);
  FillHist(cutname+"/bmuon_reltrkiso/"+bHadMatchName,bmuon_reltrkiso,weight,30,0.,15.);
  FillHist(cutname+"/bmuon_dR_l_j/"+bHadMatchName,bmuon_dR_l_j,weight,40,0.,0.4);

  
}
void TTsemilep_ChargeReliability::FillHist_belectron(TString cutname){
  FillHist(cutname+"/belectron_dnn/"+ProcessName,belectron1_DNN,weight,50,0.,1.);
  FillHist(cutname+"/belectron_charge/"+ProcessName,belectron1_charge,weight,50,-2.,2.);
  FillHist(cutname+"/belectron_charge_weighted/"+ProcessName,belectron1_charge*belectron1_DNN,weight,50,-2.,2.);

  FillHist(cutname+"/belectron_phi/"+ProcessName,belectron_phi,weight,40,-4.,4.);
  FillHist(cutname+"/belectron_pt/"+ProcessName,belectron_pt,weight,50,0.,50.);
  FillHist(cutname+"/belectron_nsip3d/"+ProcessName,belectron_nsip3d,weight,15,0.,15.);
  FillHist(cutname+"/belectron_ptwrtbjet/"+ProcessName,belectron_ptwrtbjet,weight,20,0.,5.);
  FillHist(cutname+"/belectron_eta/"+ProcessName,belectron_eta,weight,40,-4.,4.);
  FillHist(cutname+"/belectron_p_jetrestf/"+ProcessName,belectron_p_jetrestf,weight,20,0.,5.);
  FillHist(cutname+"/belectron_reltrkiso/"+ProcessName,belectron_reltrkiso,weight,30,0.,15.);
  FillHist(cutname+"/belectron_dR_l_j/"+ProcessName,belectron_dR_l_j,weight,40,0.,0.4);
  FillHist(cutname+"/belectron_IsGsfCtfScPixChargeConsistent/"+ProcessName,belectron_IsGsfCtfScPixChargeConsistent,weight,2,0.,2.);
  //
  FillHist(cutname+"/belectron_dnn/"+bHadMatchName,belectron1_DNN,weight,50,0.,1.);
  FillHist(cutname+"/belectron_charge/"+bHadMatchName,belectron1_charge,weight,50,-2.,2.);
  FillHist(cutname+"/belectron_charge_weighted/"+bHadMatchName,belectron1_charge*belectron1_DNN,weight,50,-2.,2.);

  FillHist(cutname+"/belectron_phi/"+bHadMatchName,belectron_phi,weight,40,-4.,4.);
  FillHist(cutname+"/belectron_pt/"+bHadMatchName,belectron_pt,weight,50,0.,50.);
  FillHist(cutname+"/belectron_nsip3d/"+bHadMatchName,belectron_nsip3d,weight,15,0.,15.);
  FillHist(cutname+"/belectron_ptwrtbjet/"+bHadMatchName,belectron_ptwrtbjet,weight,20,0.,5.);
  FillHist(cutname+"/belectron_eta/"+bHadMatchName,belectron_eta,weight,40,-4.,4.);
  FillHist(cutname+"/belectron_p_jetrestf/"+bHadMatchName,belectron_p_jetrestf,weight,20,0.,5.);
  FillHist(cutname+"/belectron_reltrkiso/"+bHadMatchName,belectron_reltrkiso,weight,30,0.,15.);
  FillHist(cutname+"/belectron_dR_l_j/"+bHadMatchName,belectron_dR_l_j,weight,40,0.,0.4);
  FillHist(cutname+"/belectron_IsGsfCtfScPixChargeConsistent/"+bHadMatchName,belectron_IsGsfCtfScPixChargeConsistent,weight,2,0.,2.);

}
void TTsemilep_ChargeReliability::Set_bjet(){

  bjet_charge=tightbjets[myRECO.tightbjet_idx_bHad].Charge();
  bjet_pt=min(tightbjets[myRECO.tightbjet_idx_bHad].Pt(),250.);
  bjet_eta=tightbjets[myRECO.tightbjet_idx_bHad].Eta();
  bjet_phi=tightbjets[myRECO.tightbjet_idx_bHad].Phi();
  bjet_DeepJet=tightbjets[myRECO.tightbjet_idx_bHad].GetTaggerResult(JetTagging::DeepJet);
  bjet_DeepJet_CvsL=tightbjets[myRECO.tightbjet_idx_bHad].GetTaggerResult(JetTagging::DeepJet_CvsL);
  bjet_DeepJet_CvsB=tightbjets[myRECO.tightbjet_idx_bHad].GetTaggerResult(JetTagging::DeepJet_CvsB);
  

  bjet_chargedHadronEnergyFraction=tightbjets[myRECO.tightbjet_idx_bHad].GetChargedHadronEnergyFraction();
  bjet_neutralHadronEnergyFraction=tightbjets[myRECO.tightbjet_idx_bHad].GetNeutralHadronEnergyFraction();
  bjet_neutralEmEnergyFraction=tightbjets[myRECO.tightbjet_idx_bHad].GetNeutralEmEnergyFraction();
  bjet_chargedEmEnergyFraction=tightbjets[myRECO.tightbjet_idx_bHad].GetChargedEmEnergyFraction();
  bjet_muonEnergyFraction=tightbjets[myRECO.tightbjet_idx_bHad].GetMuonEnergyFraction();
  
  
  
}
void TTsemilep_ChargeReliability::Check_bMuonScore(){
  Jet bHadJet=tightbjets[myRECO.tightbjet_idx_bHad];
  //--Check bMuon--
  std::vector<int> v_tmva_bmuonidx;
  std::vector<double> v_tmva_bmuon_charge;
  std::vector<double> v_tmva_bmuon_dnn;
  for(unsigned int i = 0 ; i < muonsize ; i++){
    if(i==myRECO.idx_Tmuon) continue;
    TLorentzVector vl(AllMuons[i]);
    vl.Boost(-tightbjets[myRECO.tightbjet_idx_bHad].BoostVector());
    p_jetrestf=vl.P();//
    dR_l_j=tightbjets[myRECO.tightbjet_idx_bHad].DeltaR(AllMuons[i]);//
    ip3d=AllMuons[i].IP3D();
    nsip3d=fabs(AllMuons[i].IP3D()/AllMuons[i].IP3Derr());
    reliso=AllMuons[i].RelIso();
    reltrkiso=AllMuons[i].TrkIso()/AllMuons[i].Pt();
    int muon_charge=AllMuons[i].Charge();

    if(dR_l_j<0.4){
      v_tmva_bmuonidx.push_back(i);
      ///DNN
      bmuon_phi=AllMuons[i].Phi();
      bmuon_pt=min(AllMuons[i].Pt(),50.);
      bmuon_nsip3d=min(nsip3d,15.);
      double ptwrtbjet=AllMuons[i].P()*sin(AllMuons[i].Angle(tightbjets[myRECO.tightbjet_idx_bHad].Vect()));
      bmuon_ptwrtbjet=min(ptwrtbjet,5.);
      bmuon_eta=AllMuons[i].Eta();
      bmuon_p_jetrestf=min(p_jetrestf,5.);
      bmuon_reltrkiso=min(reltrkiso,15.);
      bmuon_dR_l_j=dR_l_j;
      double bmuon_dnn=0.;
      bmuon_dnn=myreader_ChReliab_muon->EvaluateMVA("PyKeras::DNN");
      v_tmva_bmuon_dnn.push_back(bmuon_dnn);
      //Charge
      v_tmva_bmuon_charge.push_back(muon_charge);
    }
  }//end of muon loop


  unsigned int bmuonsize=v_tmva_bmuonidx.size();
  n_bmuon=bmuonsize;
  //set rank by score
  std::vector<int> v_tmva_bmuon_rank;
  for(unsigned int i=0; i < bmuonsize; i++){
    double _this_score=v_tmva_bmuon_dnn[i];
    unsigned int _this_rank=0;
    //compare with other muons
    for(unsigned int j=0; j < bmuonsize; j++){
      if(i==j) continue;
      if(_this_score < v_tmva_bmuon_dnn[j]){
	_this_rank+=1;
      }
      if(_this_score == v_tmva_bmuon_dnn[j]){
        if(j<i)_this_rank+=1;
      }

    }
    v_tmva_bmuon_rank.push_back(_this_rank);
  }

  bmuon1_idx=-1;
  //set vector wrt rank
  for(int i=0; i < bmuonsize; i++){//
    unsigned int target_rank=i;
    for(unsigned int j = 0 ; j < bmuonsize; j++){
      unsigned int _this_rank=v_tmva_bmuon_rank[j];
      if (target_rank==_this_rank){
        //bmuon_charges.push_back(v_tmva_bmuon_charge[j]);
        //bmuon_DNNs.push_back(v_tmva_bmuon_dnn[j]);
        if (target_rank==0){
          bmuon1_idx=v_tmva_bmuonidx[j];//leading bmuon
          bmuon1_DNN = v_tmva_bmuon_dnn[j];
          bmuon1_charge = v_tmva_bmuon_charge[j];
        }
      }

    }
  }
  if(bmuonsize > 0){//For bjet DNN score later, set 1st muon
    bmuon_phi=AllMuons[bmuon1_idx].Phi();
    bmuon_pt=min(AllMuons[bmuon1_idx].Pt(),50.);
    nsip3d=fabs(AllMuons[bmuon1_idx].IP3D()/AllMuons[bmuon1_idx].IP3Derr());
    bmuon_nsip3d=min(nsip3d,15.);
    double ptwrtbjet=AllMuons[bmuon1_idx].P()*sin(AllMuons[bmuon1_idx].Angle(tightbjets[myRECO.tightbjet_idx_bHad].Vect()));
    bmuon_ptwrtbjet=min(ptwrtbjet,5.);
    bmuon_eta=AllMuons[bmuon1_idx].Eta();

    TLorentzVector vl(AllMuons[bmuon1_idx]);
    vl.Boost(-tightbjets[myRECO.tightbjet_idx_bHad].BoostVector());
    //variables//
    p_jetrestf=vl.P();//
    bmuon_p_jetrestf=min(p_jetrestf,5.);

    reltrkiso=AllMuons[bmuon1_idx].TrkIso()/AllMuons[bmuon1_idx].Pt();
    bmuon_reltrkiso=min(reltrkiso,15.);
    
    dR_l_j=tightbjets[myRECO.tightbjet_idx_bHad].DeltaR(AllMuons[bmuon1_idx]);//
    bmuon_dR_l_j=dR_l_j;
 
  }
  
}

void TTsemilep_ChargeReliability::Check_bElectronScore(){
  std::vector<int> v_tmva_belectronidx;
  std::vector<double> v_tmva_belectron_charge;
  std::vector<double> v_tmva_belectron_dnn;
  for(unsigned int i=0; i < electronsize; i++){
    if(i==myRECO.idx_Telectron) continue;
    //---Boost electron to jet restframe
    TLorentzVector vl(AllElectrons[i]);
    vl.Boost(-tightbjets[myRECO.tightbjet_idx_bHad].BoostVector());
    //variables//
    p_jetrestf=vl.P();//
    dR_l_j=tightbjets[myRECO.tightbjet_idx_bHad].DeltaR(AllElectrons[i]);//
    ip3d=AllElectrons[i].IP3D();
    nsip3d=fabs(AllElectrons[i].IP3D()/AllElectrons[i].IP3Derr());
    reliso=AllElectrons[i].RelIso();
    reltrkiso=AllElectrons[i].TrkIso()/AllElectrons[i].Pt();

    int electron_charge=AllElectrons[i].Charge();
 
    if(dR_l_j<0.4){
      v_tmva_belectronidx.push_back(i);
      belectron_phi=AllElectrons[i].Phi();//
      belectron_pt=min(AllElectrons[i].Pt(),50.);//
      belectron_nsip3d=min(nsip3d,15.);//
      double ptwrtbjet=AllElectrons[i].P()*sin(AllElectrons[i].Angle(tightbjets[myRECO.tightbjet_idx_bHad].Vect()));
      belectron_ptwrtbjet=min(ptwrtbjet,5.);//
      belectron_eta=AllElectrons[i].Eta();//
      belectron_p_jetrestf=min(p_jetrestf,5.);//
      belectron_reltrkiso=min(reltrkiso,15.);//
      belectron_dR_l_j=dR_l_j;//
      belectron_IsGsfCtfScPixChargeConsistent=AllElectrons[i].IsGsfCtfScPixChargeConsistent();//

      double belectron_dnn=0.;
      belectron_dnn=myreader_ChReliab_electron->EvaluateMVA("PyKeras::DNN");
      v_tmva_belectron_dnn.push_back(belectron_dnn);
      //Charge
      v_tmva_belectron_charge.push_back(electron_charge);
    }
  }//end of electron loop
  unsigned int belectronsize=v_tmva_belectronidx.size();
  n_belectron=belectronsize;
  

  //set rank by score
  std::vector<int> v_tmva_belectron_rank;
  for(unsigned int i=0; i < belectronsize; i++){
    double _this_score=v_tmva_belectron_dnn[i];
    unsigned int _this_rank=0;
    for(unsigned int j=0; j < belectronsize; j++){
      if(i==j) continue;
      if(_this_score < v_tmva_belectron_dnn[j]){
	_this_rank+=1;
      }
      if(_this_score == v_tmva_belectron_dnn[j]){
        if(j<i)_this_rank+=1;
      }

    }
    v_tmva_belectron_rank.push_back(_this_rank);
  }
  belectron1_idx=-1;

  //set vector wrt rank
  for(int i=0; i < belectronsize; i++){//
    unsigned int target_rank=i;
    for(unsigned int j = 0 ; j < belectronsize; j++){
      unsigned int _this_rank=v_tmva_belectron_rank[j];
      if (target_rank==_this_rank){
        //belectron_charges.push_back(v_tmva_belectron_charge[j]);
        //belectron_DNNs.push_back(v_tmva_belectron_dnn[j]);
        if (target_rank==0){
          belectron1_idx=v_tmva_belectronidx[j];//leading belectron
          belectron1_DNN = v_tmva_belectron_dnn[j];
          belectron1_charge = v_tmva_belectron_charge[j];
	  
        }
      }
    }
  }
  
  
  if(belectronsize>0){
    
    belectron_phi=AllElectrons[belectron1_idx].Phi();
    belectron_pt=min(AllElectrons[belectron1_idx].Pt(),50.);
    nsip3d=fabs(AllElectrons[belectron1_idx].IP3D()/AllElectrons[belectron1_idx].IP3Derr());
    belectron_nsip3d=min(nsip3d,15.);
    double ptwrtbjet=AllElectrons[belectron1_idx].P()*sin(AllElectrons[belectron1_idx].Angle(tightbjets[myRECO.tightbjet_idx_bHad].Vect()));
    belectron_ptwrtbjet=min(ptwrtbjet,5.);
    belectron_eta=AllElectrons[belectron1_idx].Eta();

    TLorentzVector vl(AllElectrons[belectron1_idx]);
    vl.Boost(-tightbjets[myRECO.tightbjet_idx_bHad].BoostVector());
    //variables//
    p_jetrestf=vl.P();//
    belectron_p_jetrestf=min(p_jetrestf,5.);

    reltrkiso=AllElectrons[belectron1_idx].TrkIso()/AllElectrons[belectron1_idx].Pt();
    belectron_reltrkiso=min(reltrkiso,15.);

    dR_l_j=tightbjets[myRECO.tightbjet_idx_bHad].DeltaR(AllElectrons[belectron1_idx]);//
    belectron_dR_l_j=dR_l_j;
  }

}
void TTsemilep_ChargeReliability::AnalyzeRECO(){


  
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
  }
  else if(myRECO.passElectronTriggerAndTTbarEl){
    ChannelLep="TTbarEl";
    trigsf=el_trigsf;
    lep_recosf=el_recosf;
    lep_idsf=el_idsf;
    mu_trksf=1.;
    weight=weight*trigsf*lep_recosf*lep_idsf*mu_trksf;
  }
  




  ///--Check Jets--///
  if(!TTsemilep_ChargeReliability::CheckJets()) return;
  FillCutflow("cutflow/all/"+ProcessName,"After2b_and_Atleast2Jets",weight);

  //Now we have b jet from hadronic decay of top..
  TTsemilep_ChargeReliability::Check_bHad_Charge();

  
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
