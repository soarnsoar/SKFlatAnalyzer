#include "ForLepJetChargeReliabilityCoeff.h"


ForLepJetChargeReliabilityCoeff::ForLepJetChargeReliabilityCoeff(){//FYI : bottomness = -nb
  //Set Hadron PID vector with nb=+1
  initTMVAmodel_muon();
  initTMVAmodel_electron();
  initTMVAmodel_jet();
  


  doDebug=false;

  //-----Lepton Cut----//
  MuonCut_v1p0.P_JetRest_min=0.7;
  MuonCut_v1p0.P_JetRest_max=3;
  MuonCut_v1p0.dR_l_bj_min=-1;
  MuonCut_v1p0.dR_l_bj_max=0.4;
  MuonCut_v1p0.reltrkiso_min=-1;
  MuonCut_v1p0.reltrkiso_max=2.5;
  MuonCut_v1p0.nsip3d_min=-1;
  MuonCut_v1p0.nsip3d_max=3;

  ElectronCut_v1p0.P_JetRest_min=0.7;
  ElectronCut_v1p0.P_JetRest_max=3;
  ElectronCut_v1p0.dR_l_bj_min=-1;
  ElectronCut_v1p0.dR_l_bj_max=0.4;
  ElectronCut_v1p0.reltrkiso_min=-1;
  ElectronCut_v1p0.reltrkiso_max=2.5;
  ElectronCut_v1p0.nsip3d_min=-1;
  ElectronCut_v1p0.nsip3d_max=3;
  ElectronCut_v1p0.bool_IsGsfCtfScPixChargeConsistent=true;

  MuonCut_apply=MuonCut_v1p0;
  ElectronCut_apply=ElectronCut_v1p0;


  jhchoi_newtree=new TTree("ForOpt","ForOpt");
  //jhchoi_newtree2=new TTree("dummyTree2","dummyTree2");
  //jhchoi_newtree3=new TTree("dummyTree3","dummyTree3");
  //jhchoi_newtree4=new TTree("dummyTree4","dummyTree4");

  jhchoi_newtree->Branch("n_bmuon",&n_bmuon);
  jhchoi_newtree->Branch("bmuon_charges",&bmuon_charges);
  jhchoi_newtree->Branch("bmuon_DNNs",&bmuon_DNNs);
  jhchoi_newtree->Branch("bjet_charge",&bjet_charge);
  jhchoi_newtree->Branch("bjet_DNN",&bjet_DNN);
  jhchoi_newtree->Branch("n_belectron",&n_belectron);
  jhchoi_newtree->Branch("belectron_charges",&belectron_charges);
  jhchoi_newtree->Branch("belectron_DNNs",&belectron_DNNs);

  jhchoi_newtree->Branch("nb_event",&nb_event);
  jhchoi_newtree->Branch("weight",&weight);



}

void ForLepJetChargeReliabilityCoeff::initTMVAmodel_muon(){
  TString xmlfile="/data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/LepJetChargeReliability/aMCatNLO/muon/TMVAClassification_DNN.weights.xml";
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



void ForLepJetChargeReliabilityCoeff::initTMVAmodel_electron(){
  TString xmlfile="/data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/LepJetChargeReliability/aMCatNLO/electron/TMVAClassification_DNN.weights.xml";
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


void ForLepJetChargeReliabilityCoeff::initTMVAmodel_jet(){
  TString xmlfile="/data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/LepJetChargeReliability/aMCatNLO/jet/TMVAClassification_DNN.weights.xml";
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






void ForLepJetChargeReliabilityCoeff::InitValues(){
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



void ForLepJetChargeReliabilityCoeff::initializeAnalyzer(){
  //==== if you use "--userflags RunSyst" with SKFlat.py, HasFlag("RunSyst") will return "true"
  RunSyst = HasFlag("RunSyst");
  cout << "[ForLepJetChargeReliabilityCoeff::initializeAnalyzer] RunSyst = " << RunSyst << endl;

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
  cout << "[ForLepJetChargeReliabilityCoeff::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;


  std::vector<JetTagging::Parameters> jtps;
  //==== If you want to use 1a or 2a method,
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Tight, JetTagging::incl, JetTagging::comb) );
  //==== set
  mcCorr->SetJetTaggingParameters(jtps);
  jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  //btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);


}

ForLepJetChargeReliabilityCoeff::~ForLepJetChargeReliabilityCoeff(){

  //==== Destructor of this Analyzer

}

bool ForLepJetChargeReliabilityCoeff::Tag_gbToZb(){
  LHEs=GetLHEs();
  ForLepJetChargeReliabilityCoeff::myLHE.LHEsize = LHEs.size();  
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

  if(myLHE.nincoming_bbar==1){
    //ProcessName="DY_gbToZbbar";
    IncomingPartonTag+="bbar";
  }
  if(myLHE.nincoming_b==1){
    //ProcessName="DY_gbToZb";
    IncomingPartonTag+="bevt";
  }
  if(myLHE.nincoming_b==0 && myLHE.nincoming_bbar==0){
    //ProcessName="DY_others";
    IncomingPartonTag="others";
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
  return true;

}//[END]Tag_gbToZb()




//Sorting Leptons with P@j restframe , near 1.7
int ForLepJetChargeReliabilityCoeff::Rank1n2Leptons(std::vector<int> &v_blep_idx, std::vector<double> &v_blep_value){
  double center=1.7;
  unsigned int vsize=v_blep_idx.size();
  vector<double> v_diff;
  for(unsigned int i = 0 ; i < vsize ; i++){
    v_diff.push_back(fabs(v_blep_value[i]-center));
  }//v loop
  //----idx to return----//
  int idx_rank1=-1;
  int idx_rank2=-1;
  //////---/////

  //--Comparison--//
  for(unsigned int i = 0 ; i < vsize ; i++){
    double this_diff=v_diff[i];
    int this_rank=0;
    for(unsigned int j = 0 ; j < vsize ; j++){
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


void ForLepJetChargeReliabilityCoeff::RunLeptonCutStudyMuon(){
  std::vector<int> v_tmva_bmuonidx;
  std::vector<double> v_tmva_bmuon_charge;
  std::vector<double> v_tmva_bmuon_dnn;
  for(unsigned int i=0; i < muonsize; i++){
    if((int)i==myRECO.idx_Zmuon1) continue;
    if((int)i==myRECO.idx_Zmuon2) continue;
    
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
  int bmuon1_idx=-1;
  //set vector wrt rank
  for(unsigned int i=0; i < bmuonsize; i++){//
    unsigned int target_rank=i;
    for(unsigned int j = 0 ; j < bmuonsize; j++){
      unsigned int _this_rank=v_tmva_bmuon_rank[j];
      if (target_rank==_this_rank){
	bmuon_charges.push_back(v_tmva_bmuon_charge[j]);
	bmuon_DNNs.push_back(v_tmva_bmuon_dnn[j]);
	if (target_rank==0){
	  bmuon1_idx=v_tmva_bmuonidx[j];//leading bmuon
	}
      }

    }
  }
  if(bmuonsize > 0){//For bjet DNN score later
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

}//end RunLeptonCutStudyMuon




void ForLepJetChargeReliabilityCoeff::RunLeptonCutStudyElectron(){
  std::vector<int> v_tmva_belectronidx;
  std::vector<double> v_tmva_belectron_charge;
  std::vector<double> v_tmva_belectron_dnn;
  for(unsigned int i=0; i < electronsize; i++){
    if((int)i==myRECO.idx_Zelectron1) continue;
    if((int)i==myRECO.idx_Zelectron2) continue;
    
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
  int belectron1_idx=-1;
  //set vector wrt rank
  for(unsigned int i=0; i < belectronsize; i++){//
    unsigned int target_rank=i;
    for(unsigned int j = 0 ; j < belectronsize; j++){
      unsigned int _this_rank=v_tmva_belectron_rank[j];
      if (target_rank==_this_rank){
	belectron_charges.push_back(v_tmva_belectron_charge[j]);
	belectron_DNNs.push_back(v_tmva_belectron_dnn[j]);
        if (target_rank==0){
          belectron1_idx=v_tmva_belectronidx[j];//leading belectron
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
}//end RunLeptonCutStudyElectron





bool ForLepJetChargeReliabilityCoeff::ZmmReco(){


  
  vector<int> idx_Zmuon;
  vector<Muon> v_Zmuon;
  double this_leptonid_sf=1.;
  double this_trigger_sf=1.;
  //double this_iso_sf=1.;
  double maxpt=-999.;
  int i_l1=-1;
  int i_l2=-1;
  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double pt=AllMuons[i].Pt();
    double eta=AllMuons[i].Eta();
    bool passID=AllMuons[i].PassID("POGTight");
    double reliso=AllMuons[i].RelIso();
    if(fabs(eta) > 2.4) continue; 
    if(pt <15.) continue;
    if (!passID) continue;
    if(reliso>0.15) continue;//reliso0.15

    idx_Zmuon.push_back(i);
    v_Zmuon.push_back(AllMuons[i]);
    if(!IsDATA) {
      this_leptonid_sf*=mcCorr->MuonID_SF("NUM_TightID_DEN_TrackerMuons",  eta, AllMuons[i].MiniAODPt());
      //this_iso_sf = mcCorr->MuonISO_SF("NUM_TightRelIso_DEN_TightIDandIPCut", eta, AllMuons[i].MiniAODPt());
    }
    if(pt > maxpt){
      maxpt = pt;
      i_l1 = i;
    }
  }

  this_trigger_sf*=mcCorr->MuonTrigger_SF("IsoMu27_POGTight", "HLT_IsoMu27_v", v_Zmuon, 0);
  if (idx_Zmuon.size()<2) return 0;
  if (maxpt<30.) return 0;
  
  unsigned int SelectedMuonSize=idx_Zmuon.size();
  //int i_l1=idx_Zmuon[0];
  //int i_l2=idx_Zmuon[1];
  double second_max_pt=-999;
  for(unsigned int i = 0 ; i <SelectedMuonSize ; i++){
    int idx=idx_Zmuon[i];
    double pt=AllMuons[idx].Pt();
    if(idx==i_l1)continue;
    if(pt > second_max_pt){
      second_max_pt=pt;
      i_l2=idx;
    }
  }


  myRECO.mZ=(AllMuons[i_l1]+AllMuons[i_l2]).M();
  double mZ=myRECO.mZ;
  if(mZ < 60) return 0;
  if(mZ > 120) return 0;


  myRECO.idx_Zmuon1=i_l1;
  myRECO.idx_Zmuon2=i_l2;
  myRECO.goodZmm=true;
  weight*=this_leptonid_sf*this_trigger_sf;
  return 1;


}

bool ForLepJetChargeReliabilityCoeff::ZeeReco(){
  vector<int> idx_Zelectron;
  vector<Electron> v_Zelectron;
  double this_leptonid_sf=1.;
  double this_leptonreco_sf=1.;
  //double this_trigger_sf=1.;
  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=AllElectrons[i].Pt();
    double eta=AllElectrons[i].Eta();
    bool passID=AllElectrons[i].PassID("passMediumID");
    if(fabs(eta) > 2.4) continue; 
    if(pt <15.) continue;
    if (!passID) continue;
    idx_Zelectron.push_back(i);
    v_Zelectron.push_back(AllElectrons[i]);
    if(!IsDATA) {
      this_leptonid_sf*=mcCorr->ElectronID_SF ("passMediumID",  AllElectrons[i].scEta(), pt);
      this_leptonreco_sf*=mcCorr->ElectronReco_SF (AllElectrons[i].scEta(), pt,0);

    }
  }

  //this_trigger_sf*=ElectronTrigger_SF(TString ID, "HLT_Ele35_WPTight_Gsf_v", v_Zelectron, 0);

  if (idx_Zelectron.size()<2) return 0;
  if (AllElectrons[idx_Zelectron[0]].Pt()<38) return 0;

  int i_l1=idx_Zelectron[0];
  int i_l2=idx_Zelectron[1];
  myRECO.mZ=(AllElectrons[i_l1]+AllElectrons[i_l2]).M();
  double mZ=myRECO.mZ;
  if(mZ < 60) return 0;
  if(mZ > 120) return 0;
  weight*=this_leptonid_sf*this_leptonreco_sf;
  myRECO.idx_Zelectron1=i_l1;
  myRECO.idx_Zelectron2=i_l2;
  myRECO.goodZmm=true;
  return 1;



    

}


bool ForLepJetChargeReliabilityCoeff::Tag1bjet(){
  //JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb
  //double MCCorrection::GetJetTaggingCutValue(JetTagging::Tagger tagger, JetTagging::WP wp){
  //myRECO.ij_B
  //vector<Jet> tightjets = SelectJets(AllJets, "tightLepVeto", 20., 2.4);
  unsigned int _Nb=0;
  tightjets.clear();
  //tightjets.push_back(AllJets[myRECO.ij_B]);
  //jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
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
  for(unsigned int i = 0 ; i < jetsize; i ++){
    double btag_score=AllJets[i].GetTaggerResult(JetTagging::DeepJet);
    //cout << "btag_score=" << btag_score << endl;
    if(btag_score < btag_cut) continue;
    if(AllJets[i].Pt() < 20) continue;
    if(fabs(AllJets[i].Eta()) > 2.4) continue;
    if(AllJets[i].DeltaR(l1)<0.4) continue;
    if(AllJets[i].DeltaR(l2)<0.4) continue;
    if(AllJets[i].PassID("tight")){
      _Nb+=1;
      myRECO.ij_B=i;
    }
    tightjets.push_back(AllJets[i]);
  }
  if(_Nb!=1) return 0;
  

  

  if(!IsDATA){
    double btagWeight = mcCorr->GetBTaggingReweight_1a(tightjets, jtp);
    weight*=btagWeight;
  }
  return 1;
}

void ForLepJetChargeReliabilityCoeff::AnalyzeRECO(){


  
  //call muon/electron
  vector<Muon> AllMuons_raw=GetAllMuons();
  AllMuons=ScaleMuons(AllMuons_raw,0);
  muonsize = AllMuons.size();
  AllElectrons=GetAllElectrons();
  electronsize = AllElectrons.size();
  AllJets = GetAllJets();
  jetsize=AllJets.size();

  //(0) Apply some basic cuts
  TString MuonTriggerName = "HLT_IsoMu27_v";
  TString ElectronTriggerName = "HLT_Ele35_WPTight_Gsf_v";
  myRECO.passMuonTrigger=ev.PassTrigger(MuonTriggerName);
  myRECO.passElectronTrigger=ev.PassTrigger(ElectronTriggerName);

  FillHist("PassBothTrigger",myRECO.passMuonTrigger*myRECO.passElectronTrigger, weight, 2, 0, 2);




  myRECO.goodZee=ZeeReco();
  myRECO.goodZmm=ZmmReco();

  bool passMuonTriggerAndZmm=myRECO.passMuonTrigger&&myRECO.goodZmm;
  bool passElectronTriggerAndZee=myRECO.passElectronTrigger&&myRECO.goodZee;
  
  if((!passMuonTriggerAndZmm) && (!passElectronTriggerAndZee)) return;
  
  myRECO.passMuonTriggerAndZmm=passMuonTriggerAndZmm;
  myRECO.passElectronTriggerAndZee=passElectronTriggerAndZee;

  if(passMuonTriggerAndZmm){ 
    ZllChannel="Zmm";
  }
  else if(passElectronTriggerAndZee){
    ZllChannel="Zee";
  }
  
  FillHist("PassTrigger__and__GoodZ",1, weight, 1, 0, 2);
  FillHist("PassTrigger_and_GoodZ/mZ/"+ProcessName, myRECO.mZ, weight, 200, 60., 120.);


  if(!ForLepJetChargeReliabilityCoeff::Tag1bjet()) return;
  //If Z event, Let's store
  StoreEvent=true;
  FillHist("Pass1bjet",1, weight, 1, 0, 2);
  ForLepJetChargeReliabilityCoeff::SetBJetKins();
  //->now Z is reconstructed
  //(1) Do Main Analysis
  //(1-1) Set EventTag
  //(1-2)For B hadron to lepton decay
  //ForLepJetChargeReliabilityCoeff::RunProtoTypeMuon();
  //ForLepJetChargeReliabilityCoeff::RunProtoTypeElectron();
  ForLepJetChargeReliabilityCoeff::RunLeptonCutStudyMuon();
  //FillHist("PassRunLeptonCutStudyMuon",1, weight, 1, 0, 2);
  ForLepJetChargeReliabilityCoeff::RunLeptonCutStudyElectron();
  //FillHist("PassRunLeptonCutStudyElectron",1, weight, 1, 0, 2);

  //Calc bjet dnn
  
  bjet_DNN=myreader_jet->EvaluateMVA("PyKeras::DNN");
}

void ForLepJetChargeReliabilityCoeff::SetBJetKins(){
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





void ForLepJetChargeReliabilityCoeff::executeEvent(){
  ev = GetEvent();
  FillHist("event_start",1, weight, 1, 0, 1);
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
  //(1)---Let's tag only events with following process..
  //         g      =====o----- b(or bbar)
  //                     |
  //                     |
  //   b(or bbar)   -----o======     Z
  //
  
  //if (MCSample.Contains("DY")){
  if(!IsDATA){
    myLHE.is_gbToZb = ForLepJetChargeReliabilityCoeff::Tag_gbToZb(); 
  }
  //ForLepJetChargeReliabilityCoeff::AnalyzeLHE();
  //}
  ForLepJetChargeReliabilityCoeff::AnalyzeRECO();
  //NowFillTree
  if(StoreEvent){
    jhchoi_newtree->Fill();
    

  }//end dofilltree
  
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
