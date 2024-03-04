#include "TTsemilep_Btag.h"
#include <stdlib.h>
#include <stdio.h>

TTsemilep_Btag::TTsemilep_Btag(){//


  doDebug=false;
  DNNcut=0.5;



}

void TTsemilep_Btag::initTMVAmodel_muon(){
  TString xmlfile=SKFLAT_WD+"/external/TMVA/LepJetChargeReliability/aMCatNLO/muon/TMVAClassification_DNN.weights.xml";
  cout << "define tmvareader"<< endl;
  myreader_muon=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_muon->AddVariable("bmuon_phi",&bmuon_phi);
  myreader_muon->AddVariable("bmuon_pt",&bmuon_pt);
  myreader_muon->AddVariable("bmuon_nsip3d",&bmuon_nsip3d);
  myreader_muon->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader_muon->AddVariable("bjet_pt",&bjet_pt);
  myreader_muon->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader_muon->AddVariable("bjet_phi",&bjet_phi);
  myreader_muon->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader_muon->AddVariable("bmuon_ptwrtbjet",&bmuon_ptwrtbjet);
  myreader_muon->AddVariable("bmuon_eta",&bmuon_eta);
  myreader_muon->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader_muon->AddVariable("bjet_eta",&bjet_eta);
  myreader_muon->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  myreader_muon->AddVariable("bmuon_p_jetrestf",&bmuon_p_jetrestf);
  myreader_muon->AddVariable("bmuon_reltrkiso",&bmuon_reltrkiso);
  myreader_muon->AddVariable("bmuon_dR_l_j",&bmuon_dR_l_j);
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



void TTsemilep_Btag::initTMVAmodel_electron(){
  TString xmlfile=SKFLAT_WD+"/external/TMVA/LepJetChargeReliability/aMCatNLO/electron/TMVAClassification_DNN.weights.xml";
  cout << "define tmvareader"<< endl;
  myreader_electron=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_electron->AddVariable("belectron_dR_l_j",&belectron_dR_l_j);
  myreader_electron->AddVariable("belectron_nsip3d",&belectron_nsip3d);
  myreader_electron->AddVariable("belectron_p_jetrestf",&belectron_p_jetrestf);
  myreader_electron->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader_electron->AddVariable("bjet_pt",&bjet_pt);
  myreader_electron->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader_electron->AddVariable("bjet_phi",&bjet_phi);
  myreader_electron->AddVariable("belectron_phi",&belectron_phi);
  myreader_electron->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader_electron->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader_electron->AddVariable("belectron_pt",&belectron_pt);
  myreader_electron->AddVariable("belectron_ptwrtbjet",&belectron_ptwrtbjet);
  myreader_electron->AddVariable("bjet_eta",&bjet_eta);
  myreader_electron->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  myreader_electron->AddVariable("belectron_IsGsfCtfScPixChargeConsistent",&belectron_IsGsfCtfScPixChargeConsistent);
  myreader_electron->AddVariable("belectron_eta",&belectron_eta);
  myreader_electron->AddVariable("belectron_reltrkiso",&belectron_reltrkiso);
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


void TTsemilep_Btag::initTMVAmodel_jet(){
  TString xmlfile=SKFLAT_WD+"/external/TMVA/LepJetChargeReliability/aMCatNLO/jet/TMVAClassification_DNN.weights.xml";
  cout << "define tmvareader"<< endl;
  myreader_jet=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_jet->AddVariable("bjet_eta",&bjet_eta);
  myreader_jet->AddVariable("bmuon_pt",&bmuon_pt);
  myreader_jet->AddVariable("belectron_p_jetrestf",&belectron_p_jetrestf);
  myreader_jet->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader_jet->AddVariable("belectron_reltrkiso",&belectron_reltrkiso);
  myreader_jet->AddVariable("belectron_pt",&belectron_pt);
  myreader_jet->AddVariable("belectron_nsip3d",&belectron_nsip3d);
  myreader_jet->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader_jet->AddVariable("belectron_phi",&belectron_phi);
  myreader_jet->AddVariable("bmuon_nsip3d",&bmuon_nsip3d);
  myreader_jet->AddVariable("belectron_ptwrtbjet",&belectron_ptwrtbjet);
  myreader_jet->AddVariable("bjet_phi",&bjet_phi);
  myreader_jet->AddVariable("bmuon_p_jetrestf",&bmuon_p_jetrestf);
  myreader_jet->AddVariable("belectron_eta",&belectron_eta);
  myreader_jet->AddVariable("belectron_dR_l_j",&belectron_dR_l_j);
  myreader_jet->AddVariable("bmuon_ptwrtbjet",&bmuon_ptwrtbjet);
  myreader_jet->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader_jet->AddVariable("bmuon_phi",&bmuon_phi);
  myreader_jet->AddVariable("belectron_IsGsfCtfScPixChargeConsistent",&belectron_IsGsfCtfScPixChargeConsistent);
  myreader_jet->AddVariable("bmuon_dR_l_j",&bmuon_dR_l_j);
  myreader_jet->AddVariable("bmuon_reltrkiso",&bmuon_reltrkiso);
  myreader_jet->AddVariable("bjet_pt",&bjet_pt);
  myreader_jet->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader_jet->AddVariable("bmuon_eta",&bmuon_eta);
  myreader_jet->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);

  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_jet->BookMVA("PyKeras::DNN",xmlfile);

  cout << "[myreader_jet] Eval for Test" << endl;
  Float_t ret=myreader_jet->EvaluateMVA("PyKeras::DNN");
  cout << ret << endl;

  
}


void TTsemilep_Btag::InitValues(){
  //--global var--//
  bmuon1_idx=-1;  bmuon1_DNN=0;  bmuon1_charge=0;
  belectron1_idx=-1;  belectron1_DNN=0;  belectron1_charge=0;
  
  //-----Variables to Store for Machine Learning------//
  bjet_charge=0.;
  bjet_pt=0.;
  bjet_eta=0.;
  bjet_phi=0.;
  bjet_DeepJet=0.;
  bjet_DeepJet_CvsL=0.;
  bjet_DeepJet_CvsB=0.;
  bjet_chargedHadronEnergyFraction=0.;
  bjet_neutralHadronEnergyFraction=0.;
  bjet_neutralEmEnergyFraction=0.;
  bjet_chargedEmEnergyFraction=0.;
  bjet_muonEnergyFraction=0.;

  bmuon_pt=0.;
  bmuon_eta=0.;
  bmuon_phi=0.;
  bmuon_ptwrtbjet=0.;
  bmuon_p_jetrestf=0.;
  bmuon_dR_l_j=0.;
  bmuon_nsip3d=0.;
  bmuon_reltrkiso=0.;
  bmuon_reliso=0.;
  bmuon_charge=0.;

  n_bmuon=0;


  belectron_pt=0.;
  belectron_eta=0.;
  belectron_phi=0.;
  belectron_ptwrtbjet=0.;
  belectron_p_jetrestf=0.;
  belectron_dR_l_j=0.;
  belectron_nsip3d=0.;
  belectron_reltrkiso=0.;
  belectron_elecalclusteriso=0.;
  belectron_IsGsfCtfScPixChargeConsistent=0;
  belectron_reliso=0.;
  belectron_charge=0.;

  n_belectron=0;
  //truth
  bjetPartonFlavourCharge=0;

  //Variables ToStore
  bmuon_charges.clear();
  bmuon_DNNs.clear();
  belectron_charges.clear();
  belectron_DNNs.clear();
  bjet_DNN=0;
  bjet_charge=0;
  nb_event=0;
    
}



void TTsemilep_Btag::initializeAnalyzer(){

  IsTreeMode = HasFlag("TreeMode");//To store final events in tree
  IsTrainingMode = HasFlag("TrainingMode"); //Store training variables for DNN

  if(!IsTrainingMode){
    cout << "[initialize DNN models]" << endl;
    SKFLAT_WD=getenv("SKFlat_WD");
    initTMVAmodel_muon();
    initTMVAmodel_electron();
    initTMVAmodel_jet();
  } 
    

  if(IsTreeMode){
    cout << "[IsTreeMode]" << endl;
    jhchoi_newtree=new TTree("ForOpt","ForOpt");
    jhchoi_newtree->Branch("bmuon1_charge",&bmuon1_charge);
    jhchoi_newtree->Branch("bmuon1_DNN",&bmuon1_DNN);
    jhchoi_newtree->Branch("bjet_charge",&bjet_charge);
    jhchoi_newtree->Branch("bjet_DNN",&bjet_DNN);
    jhchoi_newtree->Branch("belectron1_charge",&belectron1_charge);
    jhchoi_newtree->Branch("belectron1_DNN",&belectron1_DNN);
    
    jhchoi_newtree->Branch("nb_event",&nb_event);
    jhchoi_newtree->Branch("weight",&weight);
    jhchoi_newtree->Branch("weight_PDF",&weight_PDF);
    jhchoi_newtree->Branch("weight_AlphaS",&weight_AlphaS);
    jhchoi_newtree->Branch("weight_Scale",&weight_Scale);
    
    jhchoi_newtree->Branch("genWeight_X1",&genWeight_X1);
    jhchoi_newtree->Branch("genWeight_X2",&genWeight_X2);
    jhchoi_newtree->Branch("genWeight_id1",&genWeight_id1);
    jhchoi_newtree->Branch("genWeight_id2",&genWeight_id2);
    jhchoi_newtree->Branch("genWeight_Q",&genWeight_Q);
  }
  

  if(IsTrainingMode){
    cout << "[IsTrainingMode]" << endl;
    jhchoi_newtree=new TTree("ForDNN","ForDNN");
    jhchoi_newtree->Branch("bjet_eta",&bjet_eta);
    jhchoi_newtree->Branch("bmuon_pt",&bmuon_pt);
    jhchoi_newtree->Branch("belectron_p_jetrestf",&belectron_p_jetrestf);
    jhchoi_newtree->Branch("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
    jhchoi_newtree->Branch("belectron_reltrkiso",&belectron_reltrkiso);
    jhchoi_newtree->Branch("belectron_pt",&belectron_pt);
    jhchoi_newtree->Branch("belectron_nsip3d",&belectron_nsip3d);
    jhchoi_newtree->Branch("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
    jhchoi_newtree->Branch("belectron_phi",&belectron_phi);
    jhchoi_newtree->Branch("bmuon_nsip3d",&bmuon_nsip3d);
    jhchoi_newtree->Branch("belectron_ptwrtbjet",&belectron_ptwrtbjet);
    jhchoi_newtree->Branch("bjet_phi",&bjet_phi);
    jhchoi_newtree->Branch("bmuon_p_jetrestf",&bmuon_p_jetrestf);
    jhchoi_newtree->Branch("belectron_eta",&belectron_eta);
    jhchoi_newtree->Branch("belectron_dR_l_j",&belectron_dR_l_j);
    jhchoi_newtree->Branch("bmuon_ptwrtbjet",&bmuon_ptwrtbjet);
    jhchoi_newtree->Branch("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
    jhchoi_newtree->Branch("bmuon_phi",&bmuon_phi);
    jhchoi_newtree->Branch("belectron_IsGsfCtfScPixChargeConsistent",&belectron_IsGsfCtfScPixChargeConsistent);
    jhchoi_newtree->Branch("bmuon_dR_l_j",&bmuon_dR_l_j);
    jhchoi_newtree->Branch("bmuon_reltrkiso",&bmuon_reltrkiso);
    jhchoi_newtree->Branch("bjet_pt",&bjet_pt);
    jhchoi_newtree->Branch("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
    jhchoi_newtree->Branch("bmuon_eta",&bmuon_eta);
    jhchoi_newtree->Branch("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);


    jhchoi_newtree->Branch("event",&event);
    jhchoi_newtree->Branch("n_bmuon",&n_bmuon);
    jhchoi_newtree->Branch("n_belectron",n_belectron);




  }


  //==== if you use "--userflags RunSyst" with SKFlat.py, HasFlag("RunSyst") will return "true"
  RunSyst = HasFlag("RunSyst");
  cout << "[TTsemilep_Btag::initializeAnalyzer] RunSyst = " << RunSyst << endl;

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
  cout << "[TTsemilep_Btag::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;


  std::vector<JetTagging::Parameters> jtps;
  //==== If you want to use 1a or 2a method,
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Tight, JetTagging::incl, JetTagging::comb) );
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Loose, JetTagging::incl, JetTagging::comb) );
  //==== set
  mcCorr->SetJetTaggingParameters(jtps);
  jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  jtp_loose=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Loose,JetTagging::incl,JetTagging::comb);
  //btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);

  //
  if(DataYear==2017){
    MuonTriggerNames = {"HLT_IsoMu24_v","HLT_IsoMu27_v"};
    MuonTriggerSFKeys={"IsoMu24_MediumID_trkIsoLoose","IsoMu27_MediumID_trkIsoLoose"};
    ElectronTriggerNames = {"HLT_Ele27_WPTight_Gsf_v","HLT_Ele32_WPTight_Gsf_v"};
    ElectronTriggerSFKeys = {"Ele27_MediumID","Ele32_MediumID"};

    TriggerSafeCut_muon = 30.;
    TriggerSafeCut_electron = 35.;

  }


}
bool TTsemilep_Btag::TTbarMuReco(){

  //Tag only 1 muon 
  vector<int> idx_Tmuon;
  vector<Muon> v_Tmuon;
  double this_leptonid_sf=1.;
  double this_trigger_sf=1.;
  double this_iso_sf=1.;

  int i_l1=-1;
  int i_l2=-1;
  //Because roch. corr. need to find leading pt muon again.
  double maxpt=-100.;
  for(int i = 0 ; i < muonsize; i++ ){
    double pt=AllMuons[i].Pt();
    double eta=AllMuons[i].Eta();
    bool passID=AllMuons[i].PassID("POGLoose");
    bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    //double reliso=AllMuons[i].RelIso();
    if(fabs(eta) > 2.4) continue;
    if(pt <TriggerSafeCut_muon) continue;
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

  if(!IsDATA) {
    this_leptonid_sf=1.;
    this_iso_sf=1.;
    this_trigger_sf=1.;
    vector<Lepton*> leps=MakeLeptonPointerVector(v_Tmuon);
    
    //mu_trigsf=GetLeptonTriggerORSF( MuonTriggerNames, MuonTriggerSFKeys, leps,0,0,"");
    Lepton* _mu1=leps.at(i_l1);
    mu_recosf=fEff->GetEfficiencySF("Muon_RECO",_mu1,0,0);
    mu_idsf=fEff->GetEfficiencySF("Muon_MediumID_trkIsoLoose",_mu1,0,0);
    mu_trksf=fEff->GetEfficiencySF("Muon_Tracking",_mu1,0,0);
  }
  //Now Muon is ready
  //PuppiMET_pt
  
  myRECO.idx_Tmuon=idx_Tmuon[0];
  return 1;

}

bool TTsemilep_Btag::TTbarElReco(){

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
    if(fabs(eta) > 2.4) continue;
    if(pt < TriggerSafeCut_electron) continue;
    if (!passID) continue;

    idx_Telectron.push_back(i);
    v_Telectron.push_back(AllElectrons[i]);

  }
  if (idx_Telectron.size()!=1) return 0;
  if (!AllElectrons[idx_Telectron[0]].PassID("POGMedium")) return 0 ;

  if(!IsDATA) {
    vector<Lepton*> leps=MakeLeptonPointerVector(v_Telectron);
    Lepton* _el1=leps.at(0);
    //el_trigsf=GetLeptonTriggerORSF(ElectronTriggerNames, ElectronTriggerSFKeys, leps,0,0,"");
    el_recosf=fEff->GetEfficiencySF("Electron_RECO",_el1,0,0);
    el_idsf=fEff->GetEfficiencySF("Electron_MediumID",_el1,0,0) ;

  }
  //Now Electron is ready
  //PuppiMET_pt
  
  myRECO.idx_Telectron=idx_Telectron[0];
  return 1;

}



void TTsemilep_Btag::RunBMuon(){
  std::vector<int> v_tmva_bmuonidx;
  std::vector<double> v_tmva_bmuon_charge;
  std::vector<double> v_tmva_bmuon_dnn;
  for(unsigned int i=0; i < muonsize; i++){
    if(i==myRECO.idx_Tmuon) continue;

    
    //---Boost muon to jet restframe
    TLorentzVector vl(AllMuons[i]);
    vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
    //variables//
    p_jetrestf=vl.P();//
    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllMuons[i]);//
    ip3d=AllMuons[i].IP3D();
    nsip3d=fabs(AllMuons[i].IP3D()/AllMuons[i].IP3Derr());
    reliso=AllMuons[i].RelIso();
    reltrkiso=AllMuons[i].TrkIso()/AllMuons[i].Pt();

    int muon_charge=AllMuons[i].Charge();



    if(dR_l_j<0.4){
      //FillHist("nTMVAmuon",1, weight, 1, 0, 2);
      v_tmva_bmuonidx.push_back(i);
      ///DNN
      bmuon_phi=AllMuons[i].Phi();
      bmuon_pt=min(AllMuons[i].Pt(),50.);
      bmuon_nsip3d=min(nsip3d,15.);
      double ptwrtbjet=AllMuons[i].P()*sin(AllMuons[i].Angle(AllJets[myRECO.ij_B].Vect()));
      bmuon_ptwrtbjet=min(ptwrtbjet,5.);
      bmuon_eta=AllMuons[i].Eta();
      bmuon_p_jetrestf=min(p_jetrestf,5.);
      bmuon_reltrkiso=min(reltrkiso,15.);
      bmuon_dR_l_j=dR_l_j;
      
      double bmuon_dnn=0.;
      if(IsTrainingMode){//no dnn score yet
	bmuon_dnn=i/100.;
      }
      else{
	bmuon_dnn=myreader_muon->EvaluateMVA("PyKeras::DNN");
      }
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
    //int _muonidx=v_tmva_bmuonidx[i];
    //eval muon dnn // muon charge //
    //double DNN_even_pos_raw=myreader_even_pos->EvaluateMVA("PyKeras::DNN");
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
	bmuon_charges.push_back(v_tmva_bmuon_charge[j]);
	bmuon_DNNs.push_back(v_tmva_bmuon_dnn[j]);
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
    double ptwrtbjet=AllMuons[bmuon1_idx].P()*sin(AllMuons[bmuon1_idx].Angle(AllJets[myRECO.ij_B].Vect()));
    bmuon_ptwrtbjet=min(ptwrtbjet,5.);
    bmuon_eta=AllMuons[bmuon1_idx].Eta();

    TLorentzVector vl(AllMuons[bmuon1_idx]);
    vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
    //variables//
    p_jetrestf=vl.P();//


    bmuon_p_jetrestf=min(p_jetrestf,5.);

    reltrkiso=AllMuons[bmuon1_idx].TrkIso()/AllMuons[bmuon1_idx].Pt();
    bmuon_reltrkiso=min(reltrkiso,15.);

    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllMuons[bmuon1_idx]);//
    bmuon_dR_l_j=dR_l_j;

  }

}//end RunBMuon




void TTsemilep_Btag::RunBElectron(){
  std::vector<int> v_tmva_belectronidx;
  std::vector<double> v_tmva_belectron_charge;
  std::vector<double> v_tmva_belectron_dnn;
  for(unsigned int i=0; i < electronsize; i++){
    if(i==myRECO.idx_Telectron) continue;
    
    
    //---Boost electron to jet restframe
    TLorentzVector vl(AllElectrons[i]);
    vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
    //variables//
    p_jetrestf=vl.P();//
    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllElectrons[i]);//
    ip3d=AllElectrons[i].IP3D();
    nsip3d=fabs(AllElectrons[i].IP3D()/AllElectrons[i].IP3Derr());
    reliso=AllElectrons[i].RelIso();
    reltrkiso=AllElectrons[i].TrkIso()/AllElectrons[i].Pt();

    int electron_charge=AllElectrons[i].Charge();



    if(dR_l_j<0.4){
      //FillHist("nTMVAelectron",1, weight, 1, 0, 2);
      v_tmva_belectronidx.push_back(i);
      ///DNN
      belectron_phi=AllElectrons[i].Phi();//
      belectron_pt=min(AllElectrons[i].Pt(),50.);//
      belectron_nsip3d=min(nsip3d,15.);//
      double ptwrtbjet=AllElectrons[i].P()*sin(AllElectrons[i].Angle(AllJets[myRECO.ij_B].Vect()));
      belectron_ptwrtbjet=min(ptwrtbjet,5.);//
      belectron_eta=AllElectrons[i].Eta();//
      belectron_p_jetrestf=min(p_jetrestf,5.);//
      belectron_reltrkiso=min(reltrkiso,15.);//
      belectron_dR_l_j=dR_l_j;//
      belectron_IsGsfCtfScPixChargeConsistent=AllElectrons[i].IsGsfCtfScPixChargeConsistent();//

      double belectron_dnn=0.;
      if(IsTrainingMode){//no dnn score yet
        belectron_dnn=i/100.;
      }
      else{
	belectron_dnn=myreader_electron->EvaluateMVA("PyKeras::DNN");
      }
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
    //int _electronidx=v_tmva_belectronidx[i];
    //eval electron dnn // electron charge //
    //double DNN_even_pos_raw=myreader_even_pos->EvaluateMVA("PyKeras::DNN");
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
	belectron_charges.push_back(v_tmva_belectron_charge[j]);
	belectron_DNNs.push_back(v_tmva_belectron_dnn[j]);
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
    double ptwrtbjet=AllElectrons[belectron1_idx].P()*sin(AllElectrons[belectron1_idx].Angle(AllJets[myRECO.ij_B].Vect()));
    belectron_ptwrtbjet=min(ptwrtbjet,5.);
    belectron_eta=AllElectrons[belectron1_idx].Eta();

    TLorentzVector vl(AllElectrons[belectron1_idx]);
    vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
    //variables//
    p_jetrestf=vl.P();//


    belectron_p_jetrestf=min(p_jetrestf,5.);

    reltrkiso=AllElectrons[belectron1_idx].TrkIso()/AllElectrons[belectron1_idx].Pt();
    belectron_reltrkiso=min(reltrkiso,15.);

    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllElectrons[belectron1_idx]);//
    belectron_dR_l_j=dR_l_j;
  }
}//end RunBElectron






bool TTsemilep_Btag::TagBjet(){
  //JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb
  //double MCCorrection::GetJetTaggingCutValue(JetTagging::Tagger tagger, JetTagging::WP wp){
  //myRECO.ij_B
  //vector<Jet> tightjets = SelectJets(AllJets, "tightLepVeto", 20., 2.4);
  unsigned int _Nb=0;
  unsigned int _Nb_loose=0;
  double taged_bjet_score=0.;
  tightjets.clear();
  tightbjets.clear();
  //tightjets.push_back(AllJets[myRECO.ij_B]);
  //jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
  bveto_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Loose);
  TLorentzVector l1;
  if(myRECO.passMuonTriggerAndTTbarMu){
    l1=AllMuons[myRECO.idx_Tmuon];
  }
  else if(myRECO.passElectronTriggerAndTTbarEl){
    l1=AllElectrons[myRECO.idx_Telectron];
  }
  //cout << "btag_cut=" << btag_cut << endl;
  for(int i = 0 ; i < jetsize; i ++){
    double btag_score=AllJets[i].GetTaggerResult(JetTagging::DeepJet);
    //cout << "btag_score=" << btag_score << endl;
    
    if(AllJets[i].Pt() < 30.) continue;
    if(fabs(AllJets[i].Eta()) > 2.4) continue;
    if(AllJets[i].DeltaR(l1)<0.4) continue;
    if(!AllJets[i].PassID("tightLepVeto")) continue; //old : tight
    if(btag_score > bveto_cut) _Nb_loose+=1;
    if(btag_score > btag_cut){
      _Nb+=1;
      tightbjets.push_back(AllJets[i]);
    }
    else{
      tightjets.push_back(AllJets[i]);
    }
  }
  if(_Nb_loose > 2) return 0;
  FillCutflow("cutflow/all/"+ProcessName,"Only2LooseBJet",weight);
  FillHist("Only2LooseBJet/cutflow/"+ProcessName,1, weight, 2, 0, 2);
  if(_Nb!=2) return 0;

  FillHist("Only2TightBJet/cutflow/"+ProcessName,1, weight, 2, 0, 2);  
  FillHist("Only2TightBJet/btagscore_nobtagsf/"+ProcessName, tightbjets[0].GetTaggerResult(JetTagging::DeepJet), weight, 50, 0, 1);  
  FillHist("Only2TightBJet/btagscore_nobtagsf/"+ProcessName, tightbjets[1].GetTaggerResult(JetTagging::DeepJet), weight, 50, 0, 1);  
  

  if(!IsDATA){
    btagsf = mcCorr->GetBTaggingReweight_1a(tightbjets, jtp);
    weight*=btagsf;

  }
  FillHist("Only2TightBJet/btagscore_withsf/"+ProcessName, tightbjets[0].GetTaggerResult(JetTagging::DeepJet), weight, 50, 0, 1);  
  FillHist("Only2TightBJet/btagscore_withsf/"+ProcessName, tightbjets[1].GetTaggerResult(JetTagging::DeepJet), weight, 50, 0, 1);  
  FillCutflow("cutflow/all/"+ProcessName,"Only2TightBJet",weight);



  ///---For check ---//
  cout << "<btagged jet flavour>" << endl;
  //partonFlavour
  int  bjet1flavour=tightbjets[0].partonFlavour();
  int  bjet2flavour=tightbjets[1].partonFlavour();
  cout << "bjet1flavour=" << bjet1flavour << endl;
  cout << "bjet2flavour=" << bjet2flavour << endl;


  tightjetsize=tightjets.size();
  cout << "<light jet flavour>" << endl;
  for(unsigned int i = 0 ; i < tightjetsize ; i ++){
    cout << i << "th light jets" << tightjets[i].partonFlavour() << endl;
  }
  return 1;
}


bool TTsemilep_Btag::ApplyEventKinematicCut(){
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

void TTsemilep_Btag::CategorizeEvent(){
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

void TTsemilep_Btag::AnalyzeRECO(){


  
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
  
  FillCutflow("cutflow/all/"+ProcessName,"TriggerAndGoodZ",weight);
  FillHist("TriggerAndGoodZ/cutflow/"+ProcessName,1, weight, 2, 0, 2);  


  if(myRECO.passMuonTriggerAndTTbarMu){ 
    ZllChannel="TTbarMu";
    trigsf=mu_trigsf;
    lep_recosf=mu_recosf;
    lep_idsf=mu_idsf;
    weight=weight*trigsf*lep_recosf*lep_idsf*mu_trksf;
  }
  else if(myRECO.passElectronTriggerAndTTbarEl){
    ZllChannel="TTbarEl";
    trigsf=el_trigsf;
    lep_recosf=el_recosf;
    lep_idsf=el_idsf;
    mu_trksf=1.;
    weight=weight*trigsf*lep_recosf*lep_idsf*mu_trksf;
  }
  
  FillHistEventBase("NoBtag");




  if(!TTsemilep_Btag::TagBjet()) return;
  //If Z event, Let's store
  FillCutflow("cutflow/all/"+ProcessName,"TagBjet",weight);
  FillHist("TagBjet/cutflow/"+ProcessName,1, weight, 2, 0, 2);  
  
  //FillHist("Pass1bjet",1, weight, 1, 0, 2);
  
}


void TTsemilep_Btag::Loop_genBMatchedRecoJet(){
  //init
  myRECO.HasBmatchedRecoJet = false;
  myRECO.nBmatJet=0;
  AllJets = GetAllJets();
  jetsize=AllJets.size();
  //double _RECO_bj_pt=-999.;
  double _RECO_bj_pt=30.;
  myRECO.ij_B=-1;//Bmatched jet's jet idx
  double jet_pt=-999., jet_flavor= -100, jet_eta = -99;
  for( unsigned int ij = 0 ; ij < jetsize; ij++){
    jet_pt = AllJets[ij].Pt();
    jet_eta = AllJets[ij].Eta();
    jet_flavor = AllJets[ij].hadronFlavour();

    if (
        (jet_flavor==5)  &&
        (jet_pt > _RECO_bj_pt) &&
        (fabs(jet_eta) < 2.4)
	)//if genB matched reco jet with the highest pt ever
      {
        myRECO.ij_B=ij;
        myRECO.nBmatJet+=1;
        _RECO_bj_pt=jet_pt;
      }
  }//[END] for all recojets
  if(myRECO.ij_B > -1 ){
    myRECO.HasBmatchedRecoJet=true;
    myRECO.vBmatchedJet.SetPtEtaPhiM(
				     AllJets[myRECO.ij_B].Pt(),
				     AllJets[myRECO.ij_B].Eta(),
				     AllJets[myRECO.ij_B].Phi(),
				     AllJets[myRECO.ij_B].M()
				     );
    
  }//[END] if there's Bhad matched jet
}//[END]ForLepJetChargeReliability::Loop_genBMatchedRecoJet()


void TTsemilep_Btag::FillHistEventBase(TString cutname){
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


void TTsemilep_Btag::FillHistBMuon(TString cutname){
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


void TTsemilep_Btag::FillHistBElectron(TString cutname){
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



void TTsemilep_Btag::FillHistBJet(TString cutname){
  if(IsTreeMode) return;
  FillHist(cutname+"/bjet_charge/"+ProcessName,bjet_charge,weight,100,-1.,1.);
  FillHist(cutname+"/bjet_charge_weighed/"+ProcessName,bjet_charge*bjet_DNN,weight,100,-1.,1.);
  FillHist(cutname+"/bjet_DNN/"+ProcessName,bjet_DNN,weight,100,-1.,1.);

  FillHist(cutname+"/bjet_pt/"+ProcessName,bjet_pt,weight,50,0.,250.);
  FillHist(cutname+"/bjet_eta/"+ProcessName,bjet_eta,weight,60,-3.,3.);
  FillHist(cutname+"/bjet_phi/"+ProcessName,bjet_phi,weight,40,-4.,4.);
  FillHist(cutname+"/bjet_DeepJet/"+ProcessName,bjet_DeepJet,weight,100,0.,1.);
  FillHist(cutname+"/bjet_chargedHadronEnergyFraction/"+ProcessName,bjet_chargedHadronEnergyFraction,weight,100,0.,1.);
  FillHist(cutname+"/bjet_neutralHadronEnergyFraction/"+ProcessName,bjet_neutralHadronEnergyFraction,weight,100,0.,1.);
  FillHist(cutname+"/bjet_neutralEmEnergyFraction/"+ProcessName,bjet_neutralEmEnergyFraction,weight,100,0.,1.);
  FillHist(cutname+"/bjet_chargedEmEnergyFraction/"+ProcessName,bjet_chargedEmEnergyFraction,weight,100,0.,1.);
  FillHist(cutname+"/bjet_muonEnergyFraction/"+ProcessName,bjet_muonEnergyFraction,weight,100,0.,1.);



}
 
void TTsemilep_Btag::SetBJetDNNInput(){
  bjet_charge=AllJets[myRECO.ij_B].Charge();
  bjet_pt=min(AllJets[myRECO.ij_B].Pt(),250.);
  bjet_eta=AllJets[myRECO.ij_B].Eta();
  bjet_phi=AllJets[myRECO.ij_B].Phi();
  bjet_DeepJet=(*jet_DeepJet)[myRECO.ij_B];
  bjet_DeepJet_CvsL=(*jet_DeepJet_CvsL)[myRECO.ij_B];
  bjet_DeepJet_CvsB=(*jet_DeepJet_CvsB)[myRECO.ij_B];
  bjet_chargedHadronEnergyFraction=(*jet_chargedHadronEnergyFraction)[myRECO.ij_B];
  bjet_neutralHadronEnergyFraction=(*jet_neutralHadronEnergyFraction)[myRECO.ij_B];
  bjet_neutralEmEnergyFraction=(*jet_neutralEmEnergyFraction)[myRECO.ij_B];
  bjet_chargedEmEnergyFraction=(*jet_chargedEmEnergyFraction)[myRECO.ij_B];
  bjet_muonEnergyFraction=(*jet_muonEnergyFraction)[myRECO.ij_B];
  
}





void TTsemilep_Btag::executeEvent(){
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
  myRECO.idx_Tmuon=-1;
  myRECO.idx_Telectron=-1;

  myRECO.goodTTbarMu=false;
  myRECO.goodTTbarEl=false;
  DNNscore=-999.;
  dphi_z_b=0.;
  pt_z=0.;
  pt_zb=0.;
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
  //doFillTree=false;
  StoreEvent=false;
  
  if(!IsDATA){
    myLHE.is_gbToZb = TTsemilep_Btag::AnalyzeLHE();
    
  }
  FillCutflow("cutflow/all/"+ProcessName,"event_start",weight);
  FillHist("event_start/cutflow/"+ProcessName,1, weight, 2, 0, 2);
  TTsemilep_Btag::AnalyzeRECO();
      
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
