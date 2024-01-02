#include "LepJetChargeReliability_RECO_NoDNNcut_Tree.h"
#include <stdlib.h>
#include <stdio.h>

LepJetChargeReliability_RECO_NoDNNcut_Tree::LepJetChargeReliability_RECO_NoDNNcut_Tree(){//FYI : bottomness = -nb
  //Set Hadron PID vector with nb=+1
  SKFLAT_WD=getenv("SKFlat_WD");
  initTMVAmodel_muon();
  initTMVAmodel_electron();
  initTMVAmodel_jet();
  
  DNNcut=0.5;

  doDebug=false;

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

void LepJetChargeReliability_RECO_NoDNNcut_Tree::initTMVAmodel_muon(){
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
  //Float_t ret=myreader->EvaluateMVA("PyKeras::DNN");


  
}



void LepJetChargeReliability_RECO_NoDNNcut_Tree::initTMVAmodel_electron(){
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
  //Float_t ret=myreader->EvaluateMVA("PyKeras::DNN");


  
}


void LepJetChargeReliability_RECO_NoDNNcut_Tree::initTMVAmodel_jet(){
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
  //Float_t ret=myreader->EvaluateMVA("PyKeras::DNN");


  
}


void LepJetChargeReliability_RECO_NoDNNcut_Tree::InitValues(){
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
  nb_event=0.;
    
}



void LepJetChargeReliability_RECO_NoDNNcut_Tree::initializeAnalyzer(){
  //==== if you use "--userflags RunSyst" with SKFlat.py, HasFlag("RunSyst") will return "true"
  RunSyst = HasFlag("RunSyst");
  cout << "[LepJetChargeReliability_RECO_NoDNNcut_Tree::initializeAnalyzer] RunSyst = " << RunSyst << endl;

  if(IsDATA){
    //ProcessName=DataStream;    
    ProcessName="Data";
  }
  else{
    ProcessName=MCSample;
    if(ProcessName.Contains("DY")){
      ProcessName="DY";
    }
  }
  cout << "[LepJetChargeReliability_RECO_NoDNNcut_Tree::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;


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
    MuonTriggerName = "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v";
    ElectronTriggerName = "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v";
    TriggerSafeCut_muon1 = 20.;
    TriggerSafeCut_muon2 = 11.;
    TriggerSafeCut_electron1 = 26;
    TriggerSafeCut_electron2 = 15;
  }

}

LepJetChargeReliability_RECO_NoDNNcut_Tree::~LepJetChargeReliability_RECO_NoDNNcut_Tree(){
  //==== Destructor of this Analyzer
}

bool LepJetChargeReliability_RECO_NoDNNcut_Tree::AnalyzeLHE(){
  LHEs=GetLHEs();
  LepJetChargeReliability_RECO_NoDNNcut_Tree::myLHE.LHEsize = LHEs.size();  
  myLHE.ngluon_incoming = 0;
  myLHE.nb_incoming = 0;
  myLHE.nb_outgoing = 0;
  myLHE.abs_nb_outgoing = 0;
  myLHE.nparton_outgoing = 0;
  myLHE.evt_nb = 0;
  myLHE.nincoming_b = 0;
  myLHE.nincoming_bbar = 0;

  //for LHE
  //We want event with
  //incoming : 1 g + 1 b
  //outgoing : 1 b , no other partons
  //double LHE_E;
  double LHE_status,LHE_id;
  unsigned int ntau = 0, nmu = 0, nele = 0;
  for(unsigned int i =0; i < myLHE.LHEsize ; i++){
    //LHE_E=LHEs[i].E();
    LHE_status=LHEs[i].Status();
    LHE_id=LHEs[i].ID();
    //LHE_index=LHEs[i].Index();
    //LHE_pt=LHEs[i].Pt();
    //LHE_eta=LHEs[i].Eta();
    //LHE_phi=LHEs[i].Phi();
    if (LHE_status==-1){//if incoming 
      if(LHE_id==5){//if incoming b
	myLHE.evt_nb += 1;
	myLHE.nb_incoming    += 1;
	myLHE.nincoming_b+=1;
      }
      else if(LHE_id==-5){//if bbar
	myLHE.evt_nb += -1;
	myLHE.nb_incoming    += 1;
	myLHE.nincoming_bbar+=1;
      }
      else if(LHE_id==21){//if gluon
	myLHE.ngluon_incoming += 1;
      }
    }//[END]if incoming
    else if (LHE_status==1){//if outgoing
      if (LHE_id==15){
	ntau += 1;
	myLHE.i_lepn = i; 
      }
      else if (LHE_id==-15){
	ntau += 1;
	myLHE.i_lepp = i; 
      }
      else if (LHE_id==13){
	nmu += 1;
	myLHE.i_lepn = i;
      }
      else if (LHE_id==-13){
	nmu += 1;
	myLHE.i_lepp = i;
      }
      else if (LHE_id==11){
	nele += 1;
	myLHE.i_lepn = i;
      }
      else if (LHE_id==-11){
	nele += 1;
	myLHE.i_lepp = i;
      }

      if (abs(LHE_id)==5){
	myLHE.nb_outgoing += 1;
	myLHE.vb=LHEs[i];
	myLHE.nparton_outgoing += 1;	
      }
      else if(
	 abs(LHE_id)>0 
	 &&
	 abs(LHE_id)<5
	 )
	{//if quark
	  myLHE.nparton_outgoing += 1;
	}
      else if (LHE_id == 21){//if gluon
	myLHE.nparton_outgoing += 1;
      }
    }//[END]if outgoing
  }//[END]for each LHE
  //Whether it's a tautau event

  if(myLHE.evt_nb==-1){
    //ProcessName="DY_gbToZbbar";
    IncomingPartonTag+="bbar";
  }
  else if(myLHE.evt_nb==1){
    //ProcessName="DY_gbToZb";
    IncomingPartonTag+="bevt";
  }
  else if(myLHE.nincoming_b==1 && myLHE.nincoming_bbar==1){
    //ProcessName="DY_others";
    IncomingPartonTag="bb";
  }
  else{
    IncomingPartonTag="others";
  }
  if(MCSample.Contains("DY")){
    ProcessName="DY_"+IncomingPartonTag;
  }

  myLHE.is_tautau= (ntau==2) ? true : false;
  myLHE.is_mumu= (nmu==2) ? true : false;
  myLHE.is_ee= (nele==2) ? true : false;

  //Check whether g+b scattering
  if(1 != myLHE.ngluon_incoming) return false;
  if(1 != myLHE.nb_incoming) return false;
  //Check whether only 1b among outgoing partons
  //<=> 1b outgoing && nparton outgoing=1
  if(1 != myLHE.nb_outgoing) return false;
  //if(1 != myLHE.nparton_outgoing) return false; // skip this. Only 1 b outgoing quark
  //else, it is one of the events we want.
  nb_event=myLHE.evt_nb;

  if(ProcessName=="DY"){
    cout << "myLHE.nincoming_b=" << myLHE.nincoming_b << endl;
    cout << "myLHE.nincoming_bbar=" << myLHE.nincoming_bbar << endl;
  }
  return true;

}//[END]Tag_gbToZb()




//Sorting Leptons with P@j restframe , near 1.7
int LepJetChargeReliability_RECO_NoDNNcut_Tree::Rank1n2Leptons(std::vector<int> &v_blep_idx, std::vector<double> &v_blep_value){
  double center=1.7;
  unsigned int vsize=v_blep_idx.size();
  vector<double> v_diff;
  for(int i = 0 ; i < vsize ; i++){
    v_diff.push_back(fabs(v_blep_value[i]-center));
  }//v loop
  //----idx to return----//
  int idx_rank1=-1;
  int idx_rank2=-1;
  //////---/////

  //--Comparison--//
  for(int i = 0 ; i < vsize ; i++){
    double this_diff=v_diff[i];
    int this_rank=0;
    for(int j = 0 ; j < vsize ; j++){
      if(i==j) continue;
      if(this_diff == v_diff[j]){
	if(i>j) this_rank+=1;
      };
      if(this_diff > v_diff[j]){//if i is more far from center than j 
	this_rank+=1;
      }
      
    }//end of j loop
    if(this_rank==0){
      idx_rank1=v_blep_idx[i];//save mu or e idx
    }
    else if(this_rank==1){
      idx_rank2=v_blep_idx[i];//save mu or e idx
    }
  }//end of i loop
  //pair<int,int> _idxpair=make_pair(idx_rank1,idx_rank2);
  //return _idxpair;
  return idx_rank1+idx_rank2*100;
}


void LepJetChargeReliability_RECO_NoDNNcut_Tree::RunBMuon(){
  std::vector<int> v_tmva_bmuonidx;
  std::vector<double> v_tmva_bmuon_charge;
  std::vector<double> v_tmva_bmuon_dnn;
  for(unsigned int i=0; i < muonsize; i++){
    if(i==myRECO.idx_Zmuon1) continue;
    if(i==myRECO.idx_Zmuon2) continue;
    
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
      double bmuon_dnn=myreader_muon->EvaluateMVA("PyKeras::DNN");
      v_tmva_bmuon_dnn.push_back(bmuon_dnn);
      //Charge
      v_tmva_bmuon_charge.push_back(muon_charge);	
    }
  }//end of muon loop



  unsigned int bmuonsize=v_tmva_bmuonidx.size();
  n_bmuon=bmuonsize;

  //set rank
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




void LepJetChargeReliability_RECO_NoDNNcut_Tree::RunBElectron(){
  std::vector<int> v_tmva_belectronidx;
  std::vector<double> v_tmva_belectron_charge;
  std::vector<double> v_tmva_belectron_dnn;
  for(unsigned int i=0; i < electronsize; i++){
    if(i==myRECO.idx_Zelectron1) continue;
    if(i==myRECO.idx_Zelectron2) continue;
    
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
      double belectron_dnn=myreader_electron->EvaluateMVA("PyKeras::DNN");
      v_tmva_belectron_dnn.push_back(belectron_dnn);
      //Charge
      v_tmva_belectron_charge.push_back(electron_charge);	
    }
  }//end of electron loop



  unsigned int belectronsize=v_tmva_belectronidx.size();
  n_belectron=belectronsize;

  //set rank
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





bool LepJetChargeReliability_RECO_NoDNNcut_Tree::ZmmReco(){
  vector<int> idx_Zmuon;
  vector<Muon> v_Zmuon;
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
    bool passID=AllMuons[i].PassID("POGMedium");
    bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    //double reliso=AllMuons[i].RelIso();
    if(fabs(eta) > 2.4) continue; 
    if(pt <15.) continue;
    if (!passID) continue;
    if (!passISO) continue;
    //if(reliso>0.15) continue;//reliso0.15
    if (pt > maxpt) {
      maxpt=pt;
      i_l1=i;
    }

    idx_Zmuon.push_back(i);
    v_Zmuon.push_back(AllMuons[i]);

  }


  if (idx_Zmuon.size()<2) return 0;


  if(!IsDATA) {
    //this_leptonid_sf*=mcCorr->MuonID_SF("NUM_TightID_DEN_TrackerMuons",  eta, AllMuons[i].MiniAODPt());
    this_leptonid_sf=1.;
    //this_iso_sf = mcCorr->MuonISO_SF("NUM_TightRelIso_DEN_TightIDandIPCut", eta, AllMuons[i].MiniAODPt());
    this_iso_sf=1.;
    //this_trigger_sf*=mcCorr->MuonTrigger_SF("IsoMu27_POGTight", "HLT_IsoMu27_v", v_Zmuon, 0);
    this_trigger_sf=1.;
  }
  
  unsigned int SelectedMuonSize=idx_Zmuon.size();
  //int i_l1=idx_Zmuon[0];
  //int i_l2=idx_Zmuon[1];
  //--Find second leading muon
  double second_max_pt=-999;
  for(int i = 0 ; i <SelectedMuonSize ; i++){
    int idx=idx_Zmuon[i];
    double pt=AllMuons[idx].Pt();
    if(idx==i_l1)continue;//this is leading muon
    if(pt > second_max_pt){
      second_max_pt=pt;
      i_l2=idx;
    }
  }
  //--[DONE]Find second leading muon

  myRECO.vZ=AllMuons[i_l1]+AllMuons[i_l2];
  myRECO.mZ=myRECO.vZ.M();

  if(myRECO.mZ < 60) return 0;
  if(myRECO.mZ > 120) return 0;
  if (AllMuons[idx_Zmuon[0]].Pt()< TriggerSafeCut_muon1) return 0;
  if (AllMuons[idx_Zmuon[1]].Pt()< TriggerSafeCut_muon2) return 0;

  myRECO.idx_Zmuon1=i_l1;
  myRECO.idx_Zmuon2=i_l2;
  myRECO.goodZmm=true;
  weight*=this_leptonid_sf*this_trigger_sf;
  return 1;


}

bool LepJetChargeReliability_RECO_NoDNNcut_Tree::ZeeReco(){
  vector<int> idx_Zelectron;
  vector<Electron> v_Zelectron;
  double this_leptonid_sf=1.;
  double this_leptonreco_sf=1.;
  double this_trigger_sf=1.;
  for(int i = 0 ; i < electronsize; i++ ){
    double pt=AllElectrons[i].Pt();
    double eta=AllElectrons[i].Eta();
    bool passID=AllElectrons[i].PassID("passMediumID");
    if(fabs(eta) > 2.4) continue; 
    if(pt < TriggerSafeCut_electron2) continue;
    if (!passID) continue;
    idx_Zelectron.push_back(i);
    v_Zelectron.push_back(AllElectrons[i]);

  }

  //this_trigger_sf*=ElectronTrigger_SF(TString ID, "HLT_Ele35_WPTight_Gsf_v", v_Zelectron, 0);

  if (idx_Zelectron.size()<2) return 0;
  if (AllElectrons[idx_Zelectron[0]].Pt()< TriggerSafeCut_electron1) return 0;
  if (AllElectrons[idx_Zelectron[1]].Pt()< TriggerSafeCut_electron2) return 0;

  int i_l1=idx_Zelectron[0];
  int i_l2=idx_Zelectron[1];

  if(!IsDATA) {
    this_leptonreco_sf*=mcCorr->ElectronReco_SF (AllElectrons[i_l1].scEta(), AllElectrons[i_l1].Pt(),0);
    this_leptonreco_sf*=mcCorr->ElectronReco_SF (AllElectrons[i_l1].scEta(), AllElectrons[i_l2].Pt(),0);
    this_leptonid_sf*=mcCorr->ElectronID_SF ("passMediumID",  AllElectrons[i_l1].scEta(), AllElectrons[i_l1].Pt());
    this_leptonid_sf*=mcCorr->ElectronID_SF ("passMediumID",  AllElectrons[i_l2].scEta(), AllElectrons[i_l2].Pt());

    
    
  }

  myRECO.vZ=AllElectrons[i_l1]+AllElectrons[i_l2];
  myRECO.mZ=myRECO.vZ.M();
  
  
  if(myRECO.mZ < 60) return 0;
  if(myRECO.mZ > 120) return 0;
  weight*=this_leptonid_sf*this_leptonreco_sf;
  myRECO.idx_Zelectron1=i_l1;
  myRECO.idx_Zelectron2=i_l2;
  myRECO.goodZmm=true;
  return 1;



    

}


bool LepJetChargeReliability_RECO_NoDNNcut_Tree::Tag1bjet(){
  //JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb
  //double MCCorrection::GetJetTaggingCutValue(JetTagging::Tagger tagger, JetTagging::WP wp){
  //myRECO.ij_B
  //vector<Jet> tightjets = SelectJets(AllJets, "tightLepVeto", 20., 2.4);
  unsigned int _Nb=0;
  unsigned int _Nb_loose=0;
  double _bjet_tagscore;
  tightjets.clear();
  //tightjets.push_back(AllJets[myRECO.ij_B]);
  //jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
  bveto_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Loose);
  TLorentzVector l1;
  TLorentzVector l2;
  if(myRECO.passMuonTriggerAndZmm){
    l1=AllMuons[myRECO.idx_Zmuon1];
    l2=AllMuons[myRECO.idx_Zmuon2];
  }
  else if(myRECO.passElectronTriggerAndZee){
    l1=AllElectrons[myRECO.idx_Zelectron1];
    l2=AllElectrons[myRECO.idx_Zelectron2];
  }
  //cout << "btag_cut=" << btag_cut << endl;
  for(int i = 0 ; i < jetsize; i ++){
    double btag_score=AllJets[i].GetTaggerResult(JetTagging::DeepJet);
    //cout << "btag_score=" << btag_score << endl;
    if(btag_score < bveto_cut) continue;
    if(AllJets[i].Pt() < 30.) continue;
    if(fabs(AllJets[i].Eta()) > 2.4) continue;
    if(AllJets[i].DeltaR(l1)<0.4) continue;
    if(AllJets[i].DeltaR(l2)<0.4) continue;
    if(!AllJets[i].PassID("tight")) continue;
    _Nb_loose+=1;
    myRECO.ij_B=i;
    if(btag_score>btag_cut) _Nb+=1;
    _bjet_tagscore=btag_score;
    tightjets.push_back(AllJets[i]);//for btagSF
  }
  if(_Nb_loose > 1) return 0;
  FillHist("Only1LooseBJet/cutflow/"+ProcessName,1, weight, 2, 0, 2);  
  if(_Nb!=1) return 0;
  FillHist("Only1TightBJet/cutflow/"+ProcessName,1, weight, 2, 0, 2);  

  

  if(!IsDATA){
    double btagWeight = mcCorr->GetBTaggingReweight_1a(tightjets, jtp);
    weight*=btagWeight;
  }
  return 1;
}


bool LepJetChargeReliability_RECO_NoDNNcut_Tree::ApplyEventKinematicCut(){
  FillHistEventBase("BeforeKinCut");
  //myRECO.vZ;
  //MET
  //(1) MET
  if (MET > 75. ) return 0;
  FillHistEventBase("After_MET_Cut");
  //(2)dPhi(Z,b)
  dphi_z_b= fabs(AllJets[myRECO.ij_B].DeltaPhi(myRECO.vZ));
  if (dphi_z_b < 1.6 ) return 0;
  FillHistEventBase("After_MET_dPhi_Cut");
  pt_z=myRECO.vZ.Pt();
  if (pt_z < 15.) return 0;
  FillHistEventBase("After_MET_dPhi_ZpT_Cut");
  pt_zb=(AllJets[myRECO.ij_B]+myRECO.vZ).Pt();
  if (pt_zb > 60.) return 0;
  FillHistEventBase("After_MET_dPhi_pT_Zb_Cut");
  return 1;
}

void LepJetChargeReliability_RECO_NoDNNcut_Tree::CategorizeEvent(){
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

void LepJetChargeReliability_RECO_NoDNNcut_Tree::AnalyzeRECO(){


  
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



  //FillHist("PassBothTrigger",myRECO.passMuonTrigger*myRECO.passElectronTrigger, weight, 2, 0, 2);




  myRECO.goodZee=ZeeReco();
  myRECO.goodZmm=ZmmReco();


  myRECO.passMuonTriggerAndZmm=myRECO.passMuonTrigger && myRECO.goodZmm;
  myRECO.passElectronTriggerAndZee= myRECO.passElectronTrigger && myRECO.goodZee;
  if((!myRECO.passMuonTriggerAndZmm) && (!myRECO.passElectronTriggerAndZee)) return;
  FillHist("TriggerAndGoodZ/cutflow/"+ProcessName,1, weight, 2, 0, 2);  


  if(myRECO.passMuonTriggerAndZmm){ 
    ZllChannel="Zmm";
  }
  else if(myRECO.passElectronTriggerAndZee){
    ZllChannel="Zee";
  }
  
  FillHist("PassTrigger__and__GoodZ",1, weight, 2, 0, 2);
  FillHist("PassTrigger_and_GoodZ/mZ/"+ProcessName, myRECO.mZ, weight, 200, 60., 120.);


  if(!LepJetChargeReliability_RECO_NoDNNcut_Tree::Tag1bjet()) return;
  //If Z event, Let's store
  
  FillHist("Tag1bjet/cutflow/"+ProcessName,1, weight, 2, 0, 2);  

  //FillHist("Pass1bjet",1, weight, 1, 0, 2);

  //Give Event Kinematic cut
  if(!LepJetChargeReliability_RECO_NoDNNcut_Tree::ApplyEventKinematicCut()) return;
  FillHist("PassKinCut/cutflow/"+ProcessName,1, weight, 2, 0, 2);  
  StoreEvent=true;

  LepJetChargeReliability_RECO_NoDNNcut_Tree::SetBJetDNNInput();
  //->now Z is reconstructed
  //(1) Do Main Analysis
  //(1-1) Set EventTag
  //(1-2)For B hadron to lepton decay
  //LepJetChargeReliability_RECO_NoDNNcut_Tree::RunProtoTypeMuon();
  //LepJetChargeReliability_RECO_NoDNNcut_Tree::RunProtoTypeElectron();
  LepJetChargeReliability_RECO_NoDNNcut_Tree::RunBMuon();
  //FillHist("PassRunLeptonCutStudyMuon",1, weight, 1, 0, 2);
  LepJetChargeReliability_RECO_NoDNNcut_Tree::RunBElectron();
  //FillHist("PassRunLeptonCutStudyElectron",1, weight, 1, 0, 2);

  //Calc bjet dnn
  
  bjet_DNN=myreader_jet->EvaluateMVA("PyKeras::DNN");

  CategorizeEvent();

  //  FillHist("event_start",1, weight, 1, 0, 1);
  //c.v.p
  FillHist(evtcat_str+"/BJetWeightedCharge/"+ProcessName,evtcharge,weight,100,-1.,1.);
  FillHist("FinalSelection/BJetWeightedCharge/"+ProcessName,evtcharge,weight,100,-1.,1.);
  FillHistEventBase(evtcat_str);
  FillHistBJet(evtcat_str);  
  FillHistBJet("FinalSelection");
  FillHistBMuon("FinalSelection");
  FillHistBElectron("FinalSelection");
  if(nPV<10){
    FillHistEventBase("nPV_under_10");
    FillHistBJet("nPV_under_10");
  }
  if(nPV>50){
    FillHistEventBase("nPV_over_50");
    FillHistBJet("nPV_over_50"); 
  }
  //10% up DY bbar 
  if(myLHE.nincoming_bbar==1 && ProcessName.Contains("DY")){
    FillHist(evtcat_str+"/BJetCharge_1p1_dybbar/"+ProcessName,evtcharge,weight*1.1,100,-1.,1.);
  }
  else{
    FillHist(evtcat_str+"/BJetCharge_1p1_dybbar/"+ProcessName,evtcharge,weight,100,-1.,1.);
  }

  //10% up DY bevt 
  if(myLHE.nincoming_b==1 && ProcessName.Contains("DY")){
    FillHist(evtcat_str+"/BJetCharge_1p1_dybevt/"+ProcessName,evtcharge,weight*1.1,100,-1.,1.);
  }
  else{
    FillHist(evtcat_str+"/BJetCharge_1p1_dybevt/"+ProcessName,evtcharge,weight,100,-1.,1.);
  }



  if(evtcat_int==0){
    FillHistBMuon(evtcat_str);
  }
  else if(evtcat_int==1){
    FillHistBElectron(evtcat_str);
  }
  //--For Tree--//
  jhchoi_newtree->Fill();
}

void LepJetChargeReliability_RECO_NoDNNcut_Tree::FillHistEventBase(TString cutname){

  FillHist(cutname+"/nPV/"+ProcessName,nPV,weight,75,0.,150.);
  FillHist(cutname+"/MET/"+ProcessName,MET,weight,75,0.,150.);
  FillHist(cutname+"/dPhi_Z_b/"+ProcessName,dphi_z_b,weight,35,0.,3.15);
  FillHist(cutname+"/pT_Z/"+ProcessName,pt_z,weight,50,0.,100.);
  FillHist(cutname+"/pT_Z_b/"+ProcessName,pt_zb,weight,50,0.,100.);
  FillHist(cutname+"/M_Z/"+ProcessName,myRECO.mZ,weight,30,60.,120.);


}


void LepJetChargeReliability_RECO_NoDNNcut_Tree::FillHistBMuon(TString cutname){
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


void LepJetChargeReliability_RECO_NoDNNcut_Tree::FillHistBElectron(TString cutname){
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



void LepJetChargeReliability_RECO_NoDNNcut_Tree::FillHistBJet(TString cutname){

  FillHist(cutname+"/bjet_charge/"+ProcessName,bjet_charge,weight,100,-1.,1.);
  FillHist(cutname+"/bjet_charge_weighed/"+ProcessName,bjet_charge*bjet_DNN,weight,100,-1.,1.);

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
 
void LepJetChargeReliability_RECO_NoDNNcut_Tree::SetBJetDNNInput(){
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





void LepJetChargeReliability_RECO_NoDNNcut_Tree::executeEvent(){
  ev = GetEvent();
  //FillHist("event_start",1, weight, 1, 0, 1);
  isEvenEvent=((event%2)==0);
  //---initialize--//
  //EventTag="";
  //EventTagJetParton="";
  ZllChannel="";
  IncomingPartonTag="";
  doPrint=false;
  weight = 1.;//init event weight
  myRECO.idx_Zmuon1=-1;
  myRECO.idx_Zmuon2=-1;
  myRECO.idx_Zelectron1=-1;
  myRECO.idx_Zelectron2=-1;
  myRECO.goodZmm=false;
  myRECO.goodZee=false;
  DNNscore=-999.;

  MET = ev.GetMETVector().Pt();

  //nPV
  weight*=GetPrefireWeight(0);
  weight*=GetPileUpWeight(nPileUp,0);
  if(!IsDATA){
    weight *= MCweight();
    weight *= ev.GetTriggerLumi("Full");
  }
  //initialize//
  myLHE.incoming_parton_pid.clear();
  InitValues();
  //doFillTree=false;
  StoreEvent=false;
  
  if(!IsDATA){
    myLHE.is_gbToZb = LepJetChargeReliability_RECO_NoDNNcut_Tree::AnalyzeLHE(); 
  }
  FillHist("event_start/cutflow/"+ProcessName,1, weight, 2, 0, 2);
  LepJetChargeReliability_RECO_NoDNNcut_Tree::AnalyzeRECO();
      
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
