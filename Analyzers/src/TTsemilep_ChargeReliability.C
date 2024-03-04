
///TODO : Add MET variation because i use met for jet assign dnn 
#include "TTsemilep_ChargeReliability.h"
#include <stdlib.h>
#include <stdio.h>

TTsemilep_ChargeReliability::TTsemilep_ChargeReliability(){//
  
  doDebug=false;
  DNNcut=0.5;
  doDrawDNNinputs=false;
  //SetSystematics();

}

TTsemilep_ChargeReliability::~TTsemilep_ChargeReliability(){

  //==== Destructor of this Analyzer

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
  //TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/add_unmatchedjet_event/muon/TMVAClassification_DNN.weights.xml";//add nonmatchedjet events
  TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/FullLearning/muon/TMVAClassification_DNN.weights.xml";//add nonmatchedjet events

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
  //TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/add_unmatchedjet_event/electron/TMVAClassification_DNN.weights.xml";//add nonmatchedjet events
  TString xmlfile=SKFLAT_WD+"/data/Run2UltraLegacy_v3/2017/TMVA/TTsemilepJetAssign/FullLearning/electron/TMVAClassification_DNN.weights.xml";//add nonmatchedjet events
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
  //--Systematics--//
  RunSyst = HasFlag("RunSyst");
  if(IsDATA) RunSyst=false;

  SkipRunSoftMuon = !HasFlag("RunSoftMuon");
  SkipRunSoftElectron = !HasFlag("RunSoftElectron");
  SkipRunJet = !HasFlag("RunJet");
  
  SkipRunHadronBJetSide = !HasFlag("RunHadronSide");
  SkipRunLeptonBJetSide = !HasFlag("RunLeptonSide");
  
  SkipMeasureReliab = !HasFlag("RunReliab");
  SkipMeasureChAcc = !HasFlag("RunChAcc");
  
  //--Systematics to Run--//
  if(RunSyst){
    SysToRun_w={
      "prefire",
      "pu",
      "pdf",
      "scale",
      "ps",
      "btaglfcorr",
      "btaglfuncorr",
      "btaghfcorr",
      "btaghfuncorr"
    };
    SysToRun_efftool={
      "muonreco",
      "muonid",
      "muontrk",
      "muontrigger",
      
      "electronreco",
      "electronid",
      "electrontrigger",
    };

  }
  else{
    SysToRun_w={};
    SysToRun_efftool={};

  }
  if(IsDATA){
    SysToRun_w={};
    SysToRun_efftool={};
  }
  
  
  cout << "[initialize DNN models]" << endl;
  SKFLAT_WD=getenv("SKFlat_WD");
  initJetAssignModel_muon();
  initJetAssignModel_electron();
  
  initChargeReliabilityModel_muon();
  initChargeReliabilityModel_electron();
  initChargeReliabilityModel_jet();

  if(IsDATA){
    ProcessName="Data";
  }
  else{
    ProcessName=MCSample;
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

    MuonID="Muon_MediumID_trkIsoLoose";
    ElectronID="Electron_MediumID";
    
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
  }
  //-----quarks pid from W->qq'----// 
  myGEN.Whad_q1_pid=GENs[idx_lightquark[0]].PID();
  myGEN.Whad_q2_pid=GENs[idx_lightquark[1]].PID();
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
    mu_idsf=fEff->GetEfficiencySF(MuonID,_mu1,0,0);
    mu_trksf=fEff->GetEfficiencySF("Muon_Tracking",_mu1,0,0);

    if(RunSyst && _run_weightbase ){
      if(syslist_efftool.count("muontrigger")) SetAllVar_syslist_efftool_muontrigger(mu_trigsf ,leps);
      if(syslist_efftool.count("muonreco")) SetAllVar_syslist_efftool(mu_recosf, _mu1, "muonreco", "Muon_RECO");
      if(syslist_efftool.count("muonid")) SetAllVar_syslist_efftool(mu_idsf, _mu1, "muonid", MuonID);
      if(syslist_efftool.count("muontrk")) SetAllVar_syslist_efftool(mu_trksf, _mu1, "muontrk", "Muon_Tracking");
    }
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
    el_idsf=fEff->GetEfficiencySF(ElectronID,_el1,0,0);

    if(RunSyst && _run_weightbase){
      if(syslist_efftool.count("electrontrigger")) SetAllVar_syslist_efftool_electrontrigger(el_trigsf ,leps);
      if(syslist_efftool.count("electronreco")) SetAllVar_syslist_efftool(el_recosf, _el1, "electronreco", "Electron_RECO");
      if(syslist_efftool.count("electronid")) SetAllVar_syslist_efftool(el_idsf, _el1, "electronid", ElectronID);
    }
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
    if(RunSyst && _run_weightbase){
      if(btagsf!=0){
	syslist_w["btaglfcorr"].push_back( mcCorr->GetBTaggingReweight_1a(alltightjets, jtp, "SystUpLTagCorr")/btagsf);
	syslist_w["btaglfcorr"].push_back( mcCorr->GetBTaggingReweight_1a(alltightjets, jtp, "SystDownLTagCorr")/btagsf);
	syslist_w["btaglfuncorr"].push_back( mcCorr->GetBTaggingReweight_1a(alltightjets, jtp, "SystUpLTagUnCorr")/btagsf);
	syslist_w["btaglfuncorr"].push_back( mcCorr->GetBTaggingReweight_1a(alltightjets, jtp, "SystDownLTagUnCorr")/btagsf);
	
	syslist_w["btaghfcorr"].push_back( mcCorr->GetBTaggingReweight_1a(alltightjets, jtp, "SystUpHTagCorr")/btagsf);
	syslist_w["btaghfcorr"].push_back( mcCorr->GetBTaggingReweight_1a(alltightjets, jtp, "SystDownHTagCorr")/btagsf);
	syslist_w["btaghfuncorr"].push_back( mcCorr->GetBTaggingReweight_1a(alltightjets, jtp, "SystUpHTagUnCorr")/btagsf);
	syslist_w["btaghfuncorr"].push_back( mcCorr->GetBTaggingReweight_1a(alltightjets, jtp, "SystDownHTagUnCorr")/btagsf);
      }
      else{
	syslist_w["btaglfcorr"].push_back(0);
	syslist_w["btaglfcorr"].push_back(0);
	syslist_w["btaglfuncorr"].push_back(0);
	syslist_w["btaglfuncorr"].push_back(0);
	
	syslist_w["btaghfcorr"].push_back(0);
	syslist_w["btaghfcorr"].push_back(0);
	syslist_w["btaghfuncorr"].push_back(0);
	syslist_w["btaghfuncorr"].push_back(0);
      }
    }
  }
  ReserveFillHist("AfterJetLoop/Nb/"+ProcessName,_Nb, weight, 10, 0, 10);
  if(_Nb!=2) return 0;
  //ReserveFillCutflow("cutflow/all/"+ProcessName,"exactly_2_bjets",weight);

  tightjetsize=tightjets.size();
  if (tightjetsize < 2) return 0;
  //ReserveFillCutflow("cutflow/all/"+ProcessName,"light_tightjet_size_over_2",weight);
  
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

  //--Set Some Booleans and values--//
  TString _bjettype="";
  bool _bmuon_Exist=false;
  int _bmuon_in_b_charge=0;
  bool _belectron_Exist=false;
  int _belectron_in_b_charge=0;
  bool _passJetDNN=false;
  double _bJetCharge=0;
  if(_Is_bHad){
    _bjettype="bHad";
    _bmuon_Exist=bmuon_in_bHad.IsExist;
    _bmuon_in_b_charge=bmuon_in_bHad.charge;

    _belectron_Exist=belectron_in_bHad.IsExist;
    _belectron_in_b_charge=belectron_in_bHad.charge;

    _passJetDNN=bHadJet.dnn > DNNcut;
    _bJetCharge=bHadJet.JetCharge;
  }else{
    _bjettype="bLep";    
    _bmuon_Exist=bmuon_in_bLep.IsExist;
    _bmuon_in_b_charge=bmuon_in_bLep.charge;

    _belectron_Exist=belectron_in_bLep.IsExist;
    _belectron_in_b_charge=belectron_in_bLep.charge;

    _passJetDNN=bLepJet.dnn > DNNcut;
    _bJetCharge=bLepJet.JetCharge;
  }
  //--[end] set some --//
  vector<TString> v_prefix;
  v_prefix.push_back("TTbarLep");
  //v_prefix.push_back(ChannelLep);
  
  for(unsigned int i = 0; i < v_prefix.size(); i++){
    
    TString prefix=v_prefix[i];
    TString suffix="";
    
    AddProcessTagTTLJ();
    suffix="";
    if(!SkipMeasureReliab) FillHist_bJet(prefix+suffix);
    //-----bMuon_in_b
    suffix="";
    if(!SkipRunSoftMuon){
      if(_bmuon_Exist){
	suffix= "__bMuonIn"+_bjettype+"Pass";
	FillHist_bmuon_in_b(prefix+suffix);
	FillHist_bJet(prefix+suffix);
	if(!SkipMeasureChAcc){
	  if(myRECO.TagLeptonCharge > 0){
	    suffix= "__bMuonIn"+_bjettype+"Pass__TagLepPlus";
	    FillHist_bmuon_in_b(prefix+suffix);
	    FillHist_bJet(prefix+suffix);
	    if(_bmuon_in_b_charge>0){
	      suffix="__bMuonIn"+_bjettype+"Pass__TagLepPlus__MeasuredPlus";
	      FillHist_bmuon_in_b(prefix+suffix);
	      FillHist_bJet(prefix+suffix);
	    }
	    else{
	      suffix="__bMuonIn"+_bjettype+"Pass__TagLepPlus__MeasuredMinus";
	      FillHist_bmuon_in_b(prefix+suffix);
	      FillHist_bJet(prefix+suffix);
	    }
	  }//[END]if TagLepPlus
	  else{// --if TagLepMinus
	    suffix="__bMuonIn"+_bjettype+"Pass__TagLepMinus";
	    FillHist_bmuon_in_b(prefix+suffix);
	    FillHist_bJet(prefix+suffix);
	    if(_bmuon_in_b_charge>0){
	      suffix="__bMuonIn"+_bjettype+"Pass__TagLepMinus__MeasuredPlus";
	      FillHist_bmuon_in_b(prefix+suffix);
	      FillHist_bJet(prefix+suffix);
	    }
	    else{
	      suffix="__bMuonIn"+_bjettype+"Pass__TagLepMinus__MeasuredMinus";
	      FillHist_bmuon_in_b(prefix+suffix);
	      FillHist_bJet(prefix+suffix);
	    }//[END]if Meausred Minus 
	  }//[End TagLepMinus]
	}//[END] !SkipMeasureChAcc
      }//[END]bmuon_in_b Exists
      else if(!SkipMeasureReliab){
	suffix= "__bMuonIn"+_bjettype+"Fail";
	FillHist_bJet(prefix+suffix);
      }
    }//[END]if not SkipRunSoftMuon
    if(_bmuon_Exist) continue;
    //-----bElectron_in_b
    if(!SkipRunSoftElectron){
      if(_belectron_Exist){
	suffix="__bElectronIn"+_bjettype+"Pass";
	FillHist_belectron_in_b(prefix+suffix);
	FillHist_bJet(prefix+suffix);
	if(!SkipMeasureChAcc){
	  if(myRECO.TagLeptonCharge > 0){
	    suffix="__bElectronIn"+_bjettype+"Pass__TagLepPlus";
	    FillHist_belectron_in_b(prefix+suffix);
	    FillHist_bJet(prefix+suffix);
	    if(_belectron_in_b_charge>0){
	      suffix="__bElectronIn"+_bjettype+"Pass__TagLepPlus__MeasuredPlus";
	      FillHist_belectron_in_b(prefix+suffix);
	      FillHist_bJet(prefix+suffix);
	    }
	    else{
	      suffix="__bElectronIn"+_bjettype+"Pass__TagLepPlus__MeasuredMinus";
	      FillHist_belectron_in_b(prefix+suffix);
	      FillHist_bJet(prefix+suffix);
	    }
	  }//[END]if TagLepPlus
	  else{// --if TagLepMinus
	    suffix="__bElectronIn"+_bjettype+"Pass__TagLepMinus";
	    FillHist_belectron_in_b(prefix+suffix);
	    FillHist_bJet(prefix+suffix);
	    if(_belectron_in_b_charge>0){
	      suffix="__bElectronIn"+_bjettype+"Pass__TagLepMinus__MeasuredPlus";
	      FillHist_belectron_in_b(prefix+suffix);
	      FillHist_bJet(prefix+suffix);
	    }
	    else{
	      suffix="__bElectronIn"+_bjettype+"Pass__TagLepMinus__MeasuredMinus";
	      FillHist_belectron_in_b(prefix+suffix);
	      FillHist_bJet(prefix+suffix);
	    }//[END]if Meausred Minus 
	  }//[End TagLepMinus]
	}//[END]SkipMeasureChAcc
      }//[END]belectron_in_b Exists
      else if(!SkipMeasureReliab){
	suffix="__bElectronIn"+_bjettype+"Fail";
	FillHist_bJet(prefix+suffix);
      }
    }//[END] if not SkipRunSoftElectron && not bmuon exist
    if(SkipRunJet) continue;
    if(_belectron_Exist) continue;
    if(_passJetDNN){
      suffix="__"+_bjettype+"Pass";
      FillHist_bJet(prefix+suffix);
      if(!SkipMeasureChAcc){
	if(myRECO.TagLeptonCharge>0){
	  suffix="__"+_bjettype+"Pass__TagLepPlus";
	  FillHist_bJet(prefix+suffix);
	  if(_bJetCharge>0){
	    suffix="__"+_bjettype+"Pass__TagLepPlus__MeasurePlus";
	    FillHist_bJet(prefix+suffix);
	  }//[END]_bJetCharge>0
	  else if(_bJetCharge<0){
	    suffix="__"+_bjettype+"Pass__TagLepPlus__MeasureMinus";
	    FillHist_bJet(prefix+suffix);
	  }//[END]_bJetCharge<0
	  else{
	    suffix="__"+_bjettype+"Pass__TagLepPlus__MeasureZero";
	    FillHist_bJet(prefix+suffix);
	  }
	}//[END] TagLeptonCharge>0
	else{// --TagLeptonCharge<0
	  suffix="__"+_bjettype+"Pass__TagLepMinus";
	  FillHist_bJet(prefix+suffix);
	  if(_bJetCharge>0){
	    suffix="__"+_bjettype+"Pass__TagLepMinus__MeasurePlus";
	    FillHist_bJet(prefix+suffix);
	  }//[END]bJet.JetCharge>0
	  else if(_bJetCharge<0){
	    suffix="__"+_bjettype+"Pass__TagLepMinus__MeasureMinus";
	    FillHist_bJet(prefix+suffix);
	  }//[END]bJet.JetCharge<0
	  else{
	    suffix="__"+_bjettype+"Pass__TagLepMinus__MeasureZero";
	    FillHist_bJet(prefix+suffix);
	  }
	}//[END] TagLeptonCharge<0
      }//[END]!SkipMeasureChAcc
    }// good bJet
    else{
      suffix="__"+_bjettype+"Fail";
      FillHist_bJet(prefix+suffix);
      if(!SkipMeasureChAcc){
	if(myRECO.TagLeptonCharge>0){
	  suffix="__"+_bjettype+"Fail__TagLepPlus";
	  FillHist_bJet(prefix+suffix);
	  if(_bJetCharge>0){
	    suffix="__"+_bjettype+"Fail__TagLepPlus__MeasurePlus";
	    FillHist_bJet(prefix+suffix);
	  }//[END]bJet.JetCharge>0
	  else if(_bJetCharge<0){//---bJetCharge<0
	    suffix="__"+_bjettype+"Fail__TagLepPlus__MeasureMinus";
	    FillHist_bJet(prefix+suffix);
	  }//[END]bJet.JetCharge<0
	  else{
	    suffix="__"+_bjettype+"Fail__TagLepPlus__MeasureZero";
	    FillHist_bJet(prefix+suffix);
	  }
	}//[END] TagLeptonCharge>0
	else{//--TagLeptonCharge<0
	  suffix="__"+_bjettype+"Fail__TagLepMinus";
	  FillHist_bJet(prefix+suffix);
	  if(_bJetCharge>0){
	    suffix="__"+_bjettype+"Fail__TagLepMinus__MeasurePlus";
	    FillHist_bJet(prefix+suffix);
	  }//[END]bJet.JetCharge>0
	  else if(_bJetCharge<0){
	    suffix="__"+_bjettype+"Fail__TagLepMinus__MeasureMinus";
	    FillHist_bJet(prefix+suffix);
	  }//[END]bJet.JetCharge<0
	  else{
	    suffix="__"+_bjettype+"Fail__TagLepMinus__MeasureZero";
	    FillHist_bJet(prefix+suffix);
	  }
	}//[END] TagLeptonCharge<0
      }//[END]!SkipMeasureChAcc
    }//[END] bad bJet
  } //[END] for prefix
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
  if(_Is_bHad){
  FillHist_bHadJet(cutname);
  FillHist_HadronicTopSide(cutname);
  }
  else{
    FillHist_bLepJet(cutname);
    FillHist_LeptonicTopSide(cutname);
  }
  
}


void TTsemilep_ChargeReliability::FillHist_LeptonicTopSide(TString cutname){
  

  ReserveFillHist(cutname+"/MT_LeptonicTop/"+ProcessName,myRECO.vt_lep_top.M(), weight, 125, 0, 500);

  
  if(!RunSyst){   
    ReserveFillHist(cutname+"/MT_LeptonicW/"+ProcessName,myRECO.vt_lep_W.M(), weight, 50, 0, 200);
    if(myRECO.passMuonTriggerAndTTbarMu){
      //myRECO.idx_Tmuon
      ReserveFillHist(cutname+"/lepton_pt/"+ProcessName,AllMuons[myRECO.idx_Tmuon].Pt(), weight, 100, 0, 100.);
      ReserveFillHist(cutname+"/lepton_eta/"+ProcessName,AllMuons[myRECO.idx_Tmuon].Eta(), weight, 100, -3, 3.);
      ReserveFillHist(cutname+"/lepton_phi/"+ProcessName,AllMuons[myRECO.idx_Tmuon].Phi(), weight, 100, -4, 4.);
      
    }
    else{
      ReserveFillHist(cutname+"/lepton_pt/"+ProcessName,AllElectrons[myRECO.idx_Telectron].Pt(), weight, 100, 0, 100.);
      ReserveFillHist(cutname+"/lepton_eta/"+ProcessName,AllElectrons[myRECO.idx_Telectron].Eta(), weight, 50, -3, 3.);
      ReserveFillHist(cutname+"/lepton_phi/"+ProcessName,AllElectrons[myRECO.idx_Telectron].Phi(), weight, 50, -4, 4.);
      
    }
    
    ReserveFillHist(cutname+"/met_pt/"+ProcessName,met_pt, weight, 50, 0, 200.);
    ReserveFillHist(cutname+"/met_phi/"+ProcessName,met_phi, weight, 100, -4, 4.);
    
  }





}
void TTsemilep_ChargeReliability::FillHist_HadronicTopSide(TString cutname){
  ReserveFillHist(cutname+"/Thad_M/"+ProcessName,(tightbjets[myRECO.tightbjet_idx_bHad]+tightjets[myRECO.tightjet_idx_q1]+tightjets[myRECO.tightjet_idx_q2]).M(), weight, 200, 0, 800.);

  if(!RunSyst){
    ReserveFillHist(cutname+"/Whad_M/"+ProcessName,(tightjets[myRECO.tightjet_idx_q1]+tightjets[myRECO.tightjet_idx_q2]).M(), weight, 50, 0, 200.);
  }
  
}
void TTsemilep_ChargeReliability::FillHist_bHadJet(TString cutname){
  

  ReserveFillHist(cutname+"/bHad_pt/"+ProcessName,bHadJet.pt, weight, 50, 0, 200);
  ReserveFillHist(cutname+"/bHad_eta/"+ProcessName,bHadJet.eta, weight, 50, -3, 3);
  
  if(!RunSyst){
    ReserveFillHist(cutname+"/bHad_dnn/"+ProcessName,bHadJet.dnn, weight, 50, 0, 1);
    ReserveFillHist(cutname+"/bHad_charge/"+ProcessName,bHadJet.JetCharge, weight, 50, -1, 1);
    if(doDrawDNNinputs){
      ReserveFillHist(cutname+"/bHad_phi/"+ProcessName,bHadJet.phi, weight, 50, -3, 3);
      ReserveFillHist(cutname+"/bHad_chargedHadronEnergyFraction/"+ProcessName,bHadJet.chargedHadronEnergyFraction, weight, 50, 0, 1);
      ReserveFillHist(cutname+"/bHad_neutralHadronEnergyFraction/"+ProcessName,bHadJet.neutralHadronEnergyFraction,weight, 50, 0, 1);
      ReserveFillHist(cutname+"/bHad_neutralEmEnergyFraction/"+ProcessName,bHadJet.neutralEmEnergyFraction, weight, 50, 0, 1);
      ReserveFillHist(cutname+"/bHad_chargedEmEnergyFraction/"+ProcessName,bHadJet.chargedEmEnergyFraction, weight, 50, 0, 1);
      ReserveFillHist(cutname+"/bHad_muonEnergyFraction/"+ProcessName,bHadJet.muonEnergyFraction, weight, 50, 0, 1);
    }
  }
}

void TTsemilep_ChargeReliability::FillHist_bLepJet(TString cutname){


  ReserveFillHist(cutname+"/bLep_pt/"+ProcessName,bLepJet.pt, weight, 50, 0, 200);
  ReserveFillHist(cutname+"/bLep_eta/"+ProcessName,bLepJet.eta, weight, 50, -3, 3);
  if(!RunSyst){
    ReserveFillHist(cutname+"/bLep_dnn/"+ProcessName,bLepJet.dnn, weight, 50, 0, 1);
    ReserveFillHist(cutname+"/bLep_charge/"+ProcessName,bLepJet.JetCharge, weight, 50, -1, 1);
    if(doDrawDNNinputs){
      ReserveFillHist(cutname+"/bLep_phi/"+ProcessName,bLepJet.phi, weight, 50, -3, 3);
      ReserveFillHist(cutname+"/bLep_chargedHadronEnergyFraction/"+ProcessName,bLepJet.chargedHadronEnergyFraction, weight, 50, 0, 1);
      ReserveFillHist(cutname+"/bLep_neutralHadronEnergyFraction/"+ProcessName,bLepJet.neutralHadronEnergyFraction,weight, 50, 0, 1);
      ReserveFillHist(cutname+"/bLep_neutralEmEnergyFraction/"+ProcessName,bLepJet.neutralEmEnergyFraction, weight, 50, 0, 1);
      ReserveFillHist(cutname+"/bLep_chargedEmEnergyFraction/"+ProcessName,bLepJet.chargedEmEnergyFraction, weight, 50, 0, 1);
      ReserveFillHist(cutname+"/bLep_muonEnergyFraction/"+ProcessName,bLepJet.muonEnergyFraction, weight, 50, 0, 1);
    }
  }
}

void TTsemilep_ChargeReliability::FillHist_bmuon_in_b(TString cutname){
  if(_Is_bHad){
    FillHist_bmuon_in_bHad(cutname);
  }
  else{
    FillHist_bmuon_in_bLep(cutname);
  }
}
void TTsemilep_ChargeReliability::FillHist_bmuon_in_bHad(TString cutname){

  ReserveFillHist(cutname+"/bmuon_in_bHad_pt/"+ProcessName,bmuon_in_bHad.pt,weight,50,0.,50.);
  ReserveFillHist(cutname+"/bmuon_in_bHad_eta/"+ProcessName,bmuon_in_bHad.eta,weight,40,-4.,4.);
  if(!RunSyst){
    ReserveFillHist(cutname+"/bmuon_in_bHad_dnn/"+ProcessName,bmuon_in_bHad.dnn,weight,50,0.,1.);
    ReserveFillHist(cutname+"/bmuon_in_bHad_charge/"+ProcessName,bmuon_in_bHad.charge,weight,50,-2.,2.);
    if(doDrawDNNinputs){
      ReserveFillHist(cutname+"/bmuon_in_bHad_phi/"+ProcessName,bmuon_in_bHad.phi,weight,40,-4.,4.);
      ReserveFillHist(cutname+"/bmuon_in_bHad_charge_weighted/"+ProcessName,bmuon_in_bHad.charge*bmuon_in_bHad.dnn,weight,50,-2.,2.);
      ReserveFillHist(cutname+"/bmuon_in_bHad_nsip3d/"+ProcessName,bmuon_in_bHad.nsip3d,weight,15,0.,15.);
      ReserveFillHist(cutname+"/bmuon_in_bHad_ptwrtbjet/"+ProcessName,bmuon_in_bHad.ptwrtbjet,weight,20,0.,5.);
      ReserveFillHist(cutname+"/bmuon_in_bHad_p_jetrestf/"+ProcessName,bmuon_in_bHad.p_jetrestf,weight,20,0.,5.);
      ReserveFillHist(cutname+"/bmuon_in_bHad_reltrkiso/"+ProcessName,bmuon_in_bHad.reltrkiso,weight,30,0.,15.);
      ReserveFillHist(cutname+"/bmuon_in_bHad_dR_l_j/"+ProcessName,bmuon_in_bHad.dR_l_j,weight,40,0.,0.4);
    }
  }
}
void TTsemilep_ChargeReliability::FillHist_bmuon_in_bLep(TString cutname){


  ReserveFillHist(cutname+"/bmuon_in_bLep_pt/"+ProcessName,bmuon_in_bLep.pt,weight,50,0.,50.);
  ReserveFillHist(cutname+"/bmuon_in_bLep_eta/"+ProcessName,bmuon_in_bLep.eta,weight,40,-4.,4.);
  if(!RunSyst){
    ReserveFillHist(cutname+"/bmuon_in_bLep_dnn/"+ProcessName,bmuon_in_bLep.dnn,weight,50,0.,1.);
    ReserveFillHist(cutname+"/bmuon_in_bLep_charge/"+ProcessName,bmuon_in_bLep.charge,weight,50,-2.,2.);
    if(doDrawDNNinputs){
      ReserveFillHist(cutname+"/bmuon_in_bLep_phi/"+ProcessName,bmuon_in_bLep.phi,weight,40,-4.,4.);
      ReserveFillHist(cutname+"/bmuon_in_bLep_charge_weighted/"+ProcessName,bmuon_in_bLep.charge*bmuon_in_bLep.dnn,weight,50,-2.,2.);
      ReserveFillHist(cutname+"/bmuon_in_bLep_nsip3d/"+ProcessName,bmuon_in_bLep.nsip3d,weight,15,0.,15.);
      ReserveFillHist(cutname+"/bmuon_in_bLep_ptwrtbjet/"+ProcessName,bmuon_in_bLep.ptwrtbjet,weight,20,0.,5.);
      ReserveFillHist(cutname+"/bmuon_in_bLep_p_jetrestf/"+ProcessName,bmuon_in_bLep.p_jetrestf,weight,20,0.,5.);
      ReserveFillHist(cutname+"/bmuon_in_bLep_reltrkiso/"+ProcessName,bmuon_in_bLep.reltrkiso,weight,30,0.,15.);
      ReserveFillHist(cutname+"/bmuon_in_bLep_dR_l_j/"+ProcessName,bmuon_in_bLep.dR_l_j,weight,40,0.,0.4);
    }
  }
}
void TTsemilep_ChargeReliability::FillHist_belectron_in_b(TString cutname){
  if(_Is_bHad){
    FillHist_belectron_in_bHad(cutname);
  }
  else{
    FillHist_belectron_in_bLep(cutname);
  }
}
void TTsemilep_ChargeReliability::FillHist_belectron_in_bHad(TString cutname){
  
  ReserveFillHist(cutname+"/belectron_in_bHad_pt/"+ProcessName,belectron_in_bHad.pt,weight,50,0.,50.);  
  ReserveFillHist(cutname+"/belectron_in_bHad_eta/"+ProcessName,belectron_in_bHad.eta,weight,40,-4.,4.);
  if(!RunSyst){
    ReserveFillHist(cutname+"/belectron_in_bHad_dnn/"+ProcessName,belectron_in_bHad.dnn,weight,50,0.,1.);
    ReserveFillHist(cutname+"/belectron_in_bHad_charge/"+ProcessName,belectron_in_bHad.charge,weight,50,-2.,2.);
    if(doDrawDNNinputs){
      ReserveFillHist(cutname+"/belectron_in_bHad_phi/"+ProcessName,belectron_in_bHad.phi,weight,40,-4.,4.);
      ReserveFillHist(cutname+"/belectron_in_bHad_charge_weighted/"+ProcessName,belectron_in_bHad.charge*belectron_in_bHad.dnn,weight,50,-2.,2.);
      ReserveFillHist(cutname+"/belectron_in_bHad_nsip3d/"+ProcessName,belectron_in_bHad.nsip3d,weight,15,0.,15.);
      ReserveFillHist(cutname+"/belectron_in_bHad_ptwrtbjet/"+ProcessName,belectron_in_bHad.ptwrtbjet,weight,20,0.,5.);
      ReserveFillHist(cutname+"/belectron_in_bHad_p_jetrestf/"+ProcessName,belectron_in_bHad.p_jetrestf,weight,20,0.,5.);
      ReserveFillHist(cutname+"/belectron_in_bHad_reltrkiso/"+ProcessName,belectron_in_bHad.reltrkiso,weight,30,0.,15.);
      ReserveFillHist(cutname+"/belectron_in_bHad_dR_l_j/"+ProcessName,belectron_in_bHad.dR_l_j,weight,40,0.,0.4);
      ReserveFillHist(cutname+"/belectron_in_bHad_IsGsfCtfScPixChargeConsistent/"+ProcessName,belectron_in_bHad.IsGsfCtfScPixChargeConsistent,weight,2,0.,2.);
    }
  }
}
void TTsemilep_ChargeReliability::FillHist_belectron_in_bLep(TString cutname){
  ReserveFillHist(cutname+"/belectron_in_bLep_pt/"+ProcessName,belectron_in_bLep.pt,weight,50,0.,50.);
  ReserveFillHist(cutname+"/belectron_in_bLep_eta/"+ProcessName,belectron_in_bLep.eta,weight,40,-4.,4.);
  if(!RunSyst){
    ReserveFillHist(cutname+"/belectron_in_bLep_dnn/"+ProcessName,belectron_in_bLep.dnn,weight,50,0.,1.);
    ReserveFillHist(cutname+"/belectron_in_bLep_charge/"+ProcessName,belectron_in_bLep.charge,weight,50,-2.,2.);
    if(doDrawDNNinputs){
      ReserveFillHist(cutname+"/belectron_in_bLep_phi/"+ProcessName,belectron_in_bLep.phi,weight,40,-4.,4.);
      ReserveFillHist(cutname+"/belectron_in_bLep_charge_weighted/"+ProcessName,belectron_in_bLep.charge*belectron_in_bLep.dnn,weight,50,-2.,2.);
      ReserveFillHist(cutname+"/belectron_in_bLep_nsip3d/"+ProcessName,belectron_in_bLep.nsip3d,weight,15,0.,15.);
      ReserveFillHist(cutname+"/belectron_in_bLep_ptwrtbjet/"+ProcessName,belectron_in_bLep.ptwrtbjet,weight,20,0.,5.);
      ReserveFillHist(cutname+"/belectron_in_bLep_p_jetrestf/"+ProcessName,belectron_in_bLep.p_jetrestf,weight,20,0.,5.);
      ReserveFillHist(cutname+"/belectron_in_bLep_reltrkiso/"+ProcessName,belectron_in_bLep.reltrkiso,weight,30,0.,15.);
      ReserveFillHist(cutname+"/belectron_in_bLep_dR_l_j/"+ProcessName,belectron_in_bLep.dR_l_j,weight,40,0.,0.4);
      ReserveFillHist(cutname+"/belectron_in_bLep_IsGsfCtfScPixChargeConsistent/"+ProcessName,belectron_in_bLep.IsGsfCtfScPixChargeConsistent,weight,2,0.,2.);
    }
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
  

  AllMuons=ScaleMuons(AllMuons_raw,_var_muonscale);//roch. corr.
  AllElectrons=ScaleElectrons(AllElectrons_raw,_var_electronscale);
  // cout << "_JESsource->" << _JESsource << endl;
  //AllJets = ScaleJetsIndividualSource(AllJets_raw,_var_jes,_JESsource);
  if(_var_jes){
    AllJets = ScaleJets(AllJets_raw,_var_jes);
  }
  else if(_var_jer){
    AllJets = SmearJets(AllJets_raw,_var_jer);
  }
  else{
    AllJets = ScaleJets(AllJets_raw,_var_jes);
  }
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

  //FillCutflow("cutflow/all/"+ProcessName,"BeforeTrigger",weight);
  myRECO.passMuonTriggerAndTTbarMu=myRECO.passMuonTrigger && myRECO.goodTTbarMu;
  myRECO.passElectronTriggerAndTTbarEl= myRECO.passElectronTrigger && myRECO.goodTTbarEl;
  if((!myRECO.passMuonTriggerAndTTbarMu) && (!myRECO.passElectronTriggerAndTTbarEl)) return;
  //if( (!(myRECO.goodTTbarMu&&myLHE.IsMuonChannel)) && (!(myRECO.goodTTbarEl&&myLHE.IsElectronChannel)) ) return;
  //FillCutflow("cutflow/all/"+ProcessName,"AfterTriggerAnd1TightLep",weight);

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
  //FillCutflow("cutflow/all/"+ProcessName,"After2b_and_Atleast2Jets",weight);
  //Now we have b jet from hadronic decay of top..
  //--bHad
  if(!SkipRunHadronBJetSide){
    TTsemilep_ChargeReliability::Set_bJet(true);//set target bjet to bHad and eval relibilities
    TTsemilep_ChargeReliability::Check_bJet_Charge();
  }
  //--bLep
  if(!SkipRunLeptonBJetSide){
    TTsemilep_ChargeReliability::Set_bJet(false);//set target bjet to bLep and eval relibilities
    TTsemilep_ChargeReliability::Check_bJet_Charge();
  }
}





void TTsemilep_ChargeReliability::GetAllObject(){
  AllMuons_raw=GetAllMuons();
  muonsize=AllMuons_raw.size();
  AllElectrons_raw=GetAllElectrons();
  electronsize=AllElectrons_raw.size();
  AllJets_raw=GetAllJets();
  jetsize=AllJets_raw.size();
  //cout << "jetsize=" << jetsize << endl;

}

void TTsemilep_ChargeReliability::executeEvent(){//this function is only for 
  //----GetAll Muons/Electrons/Jets
  GetAllObject();
  InitSysVar();
  SetRunWeightBase(true);
  if(!RunSyst){//OR IsData
    if(!IsDATA){
      LHEs=GetLHEs();
      if(ProcessName.Contains("TTLJ"))TTsemilep_ChargeReliability::AnalyzeLHE();
      //if (myLHE.IsTauChannel) return; // not caring tau channel
      if(ProcessName.Contains("TTLJ"))TTsemilep_ChargeReliability::AnalyzeGEN();
      //FillCutflow("cutflow/all/"+ProcessName,"event_start",weight);
    }
    executeEventWithCurrentSet();
  } 
  else{//---
    //--Systematics
    InitSysVar();
    SetRunWeightBase(true);
    executeEventWithCurrentSet();

    //--Scales
    SetRunWeightBase(false);
    //---muonscale--//
    InitSysVar();
    _var_muonscale=+1;
    syssuffix="muonscale";
    sysdir="Up";
    executeEventWithCurrentSet();

    InitSysVar();
    _var_muonscale=-1;
    syssuffix="muonscale";
    sysdir="Down";
    executeEventWithCurrentSet();


    //--electronscale--//

    InitSysVar();
    _var_electronscale=+1;
    syssuffix="electronscale";
    sysdir="Up";
    executeEventWithCurrentSet();

    InitSysVar();
    _var_electronscale=-1;
    syssuffix="electronscale";
    sysdir="Down";
    executeEventWithCurrentSet();


   //--jes--//


    InitSysVar();
    _var_jes=+1;
    _JESsource="Total";
    syssuffix="jesTotal";
    sysdir="Up";
    executeEventWithCurrentSet();

    InitSysVar();
    _var_jes=-1;
    _JESsource="Total";
    syssuffix="jesTotal";
    sysdir="Down";
    executeEventWithCurrentSet();

    //--jer--//
    InitSysVar();
    _var_jer=+1;
    syssuffix="jer";
    sysdir="Up";
    executeEventWithCurrentSet();

    InitSysVar();
    _var_jer=-1;
    syssuffix="jer";
    sysdir="Down";
    executeEventWithCurrentSet();


  }


}
void TTsemilep_ChargeReliability::executeEventWithCurrentSet(){
  //jhchoi//
  ev = GetEvent();
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




  
  
  if(!IsDATA){
    prefire_weight=L1PrefireReweight_Central;
    weight*=prefire_weight;
    //nPV
    puweight=GetPileUpWeight(nPileUp,0);
    weight*=puweight;

    base_weight*=MCweight();
    base_weight*=ev.GetTriggerLumi("Full");
    weight *= MCweight();
    weight *= ev.GetTriggerLumi("Full");
    if(RunSyst && _run_weightbase){
      if(syslist_w.count("prefire")) {
	if(L1PrefireReweight_Central==0.){ 
	  syslist_w["prefire"].push_back(0.);
	  syslist_w["prefire"].push_back(0.);
	}
	else{
	  syslist_w["prefire"].push_back(L1PrefireReweight_Up/L1PrefireReweight_Central);//direct read prefire weight
	  syslist_w["prefire"].push_back(L1PrefireReweight_Down/L1PrefireReweight_Central);
	}
      }
      if(syslist_w.count("pu")) {
	if(puweight==0.){
	  syslist_w["pu"].push_back(0.);
	  syslist_w["pu"].push_back(0.);
	}
	else{
	  syslist_w["pu"].push_back(GetPileUpWeight(nPileUp,1)/puweight);
	  syslist_w["pu"].push_back(GetPileUpWeight(nPileUp,-1)/puweight);;
	}
      }
      if(syslist_w.count("ps")) {
	for(const auto& _pssyst : *weight_PSSyst){ //PS systematics
	  syslist_w["ps"].push_back(_pssyst);
	}
      }
    }
  }
  //initialize//
  myLHE.incoming_parton_pid.clear();
  _tightbjet_idx=-1;
  InitValues();
  //doFillTree=false;

  TTsemilep_ChargeReliability::AnalyzeRECO();
  
  FillReservedHist();
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
