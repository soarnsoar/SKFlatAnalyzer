#include "ForNewJetCharge.h"


ForNewJetCharge::ForNewJetCharge(){//FYI : bottomness = -nb

  //Set Hadron PID vector with nb=+1
  BhadronPIDs={
    -511,-521,-10511,-10521,-513,-523,-10513,-10523,-20513,-20523,-515,-525,-531,-10531,-533,-10533,-20533,-535,-541,-10541,-543,-10543,-20543,-545,//MESON
    5122,5112,5212,5222,5114,5214,5224, //lambda and sigma baryon
    5332,5334,5342,5432,5434,5442,5444, //omega baryon
    5142,5242,5412,5422,5414,5424//some Xi
  };
  BhadronPIDs2={//with nb==2
    5132,5232,5312,5322,5314,5324,5512,5522,5514,5524,//some Xi
    5532,5534,5542,5544
  };
  BhadronPIDs3={//with nb==3
    5554
  };


  myRECO.dRcut_bmatj_lep=0.4;
  myRECO.dRcut_bmatj_muon=0.4;
  myRECO.dRcut_bmatj_electron=0.4;
  allow_tautau=false;
  doDebug=false;
  //---[arr for non uniform Binning]
  //(1) xscale
  for(int ie=-7; ie < 0 ; ie++){
    for(unsigned int ic=1; ic < 10 ; ic++){
      double _num=ic*pow(10,ie);
      v_xscale_binning.push_back(_num);
    }
  }
  v_xscale_binning.push_back(1);
  //array link to the vector 
  xscale_binning = &v_xscale_binning[0];
  

  //(2)Q2 scale
  
  for(unsigned int ie=0; ie < 6 ; ie++){
    for(unsigned int ic=1; ic < 10 ; ic++){
      double _num=ic*pow(10,ie);
      v_Q2scale_binning.push_back(_num);
    }
  }
  //array link to the vector 
  Q2scale_binning = &v_Q2scale_binning[0];


  //-- Event Category--//
  Cat_b_bbar[0]="";
  Cat_b_bbar[1]="_b";
  Cat_b_bbar[2]="_bbar";
  Cat_b_bbar_size = 3;

  Cat_Z_To_mm_ee[0]="";
  Cat_Z_To_mm_ee[1]="_mm";
  Cat_Z_To_mm_ee[2]="_ee";
  Cat_Z_To_mm_ee_size = 3;

  Cat_lepton_charge[0]="";
  Cat_lepton_charge[1]="_lepp";
  Cat_lepton_charge[2]="_lepn";
  Cat_lepton_charge_size = 3;

  Cat_1jet20[0] =""; //oneCleanJet20Event && BmatJet20Event
  //Cat_1jet20[1] ="_only1j20_bmat20";
  //Cat_1jet20_size = 2;
  Cat_1jet20_size = 1;

  Cat_pTatJetRF2[0] =""; //oneCleanJet20Event && BmatJet20Event
  Cat_pTatJetRF2[1] ="_pTatJetRF2";
  Cat_pTatJetRF2_size = 2;


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

  //---tree init---//
  jhchoi_newtree=new TTree("Tree_neg","Tree_neg");
  jhchoi_newtree2=new TTree("Tree_pos","Tree_pos");

  //tree#1 bevt
  jhchoi_newtree->Branch("bjet_charge",&bjet_charge);
  jhchoi_newtree->Branch("bjet_pt",&bjet_pt);
  jhchoi_newtree->Branch("bjet_eta",&bjet_eta);
  jhchoi_newtree->Branch("bjet_phi",&bjet_phi);
  jhchoi_newtree->Branch("bjet_DeepJet",&bjet_DeepJet);
  jhchoi_newtree->Branch("bjet_DeepJet_CvsL",&bjet_DeepJet_CvsL);
  jhchoi_newtree->Branch("bjet_DeepJet_CvsB",&bjet_DeepJet_CvsB);
  jhchoi_newtree->Branch("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  jhchoi_newtree->Branch("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  jhchoi_newtree->Branch("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  jhchoi_newtree->Branch("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  jhchoi_newtree->Branch("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  
  jhchoi_newtree->Branch("bmuon_pt",&bmuon_pt);
  jhchoi_newtree->Branch("bmuon_eta",&bmuon_eta);
  jhchoi_newtree->Branch("bmuon_phi",&bmuon_phi);
  jhchoi_newtree->Branch("bmuon_ptwrtbjet",&bmuon_ptwrtbjet);
  jhchoi_newtree->Branch("bmuon_p_jetrestf",&bmuon_p_jetrestf);
  jhchoi_newtree->Branch("bmuon_dR_l_j",&bmuon_dR_l_j);
  jhchoi_newtree->Branch("bmuon_nsip3d",&bmuon_nsip3d);
  jhchoi_newtree->Branch("bmuon_reltrkiso",&bmuon_reltrkiso);
  jhchoi_newtree->Branch("bmuon_reliso",&bmuon_reliso);
  jhchoi_newtree->Branch("bmuon_charge",&bmuon_charge);
  jhchoi_newtree->Branch("n_bmuon",&n_bmuon);
  //  belectron_elecalclusteriso=-10.;
  //belectron_IsGsfCtfScPixChargeConsistent=-10.;

  jhchoi_newtree->Branch("belectron_pt",&belectron_pt);
  jhchoi_newtree->Branch("belectron_eta",&belectron_eta);
  jhchoi_newtree->Branch("belectron_phi",&belectron_phi);
  jhchoi_newtree->Branch("belectron_ptwrtbjet",&belectron_ptwrtbjet);
  jhchoi_newtree->Branch("belectron_p_jetrestf",&belectron_p_jetrestf);
  jhchoi_newtree->Branch("belectron_dR_l_j",&belectron_dR_l_j);
  jhchoi_newtree->Branch("belectron_nsip3d",&belectron_nsip3d);
  jhchoi_newtree->Branch("belectron_reltrkiso",&belectron_reltrkiso);
  jhchoi_newtree->Branch("belectron_reliso",&belectron_reliso);
  jhchoi_newtree->Branch("belectron_charge",&belectron_charge);
  jhchoi_newtree->Branch("belectron_elecalclusteriso",&belectron_elecalclusteriso);
  jhchoi_newtree->Branch("belectron_IsGsfCtfScPixChargeConsistent",&belectron_IsGsfCtfScPixChargeConsistent);

  jhchoi_newtree->Branch("n_belectron",&n_belectron);

  //  belectron_elecalclusteriso=-10.;
  //belectron_IsGsfCtfScPixChargeConsistent=-10.;
  jhchoi_newtree->Branch("bjetPartonFlavourCharge",&bjetPartonFlavourCharge);
  jhchoi_newtree->Branch("weight",&weight);

  //tree#2(bbar)
  jhchoi_newtree2->Branch("bjet_charge",&bjet_charge);
  jhchoi_newtree2->Branch("bjet_pt",&bjet_pt);
  jhchoi_newtree2->Branch("bjet_eta",&bjet_eta);
  jhchoi_newtree2->Branch("bjet_phi",&bjet_phi);
  jhchoi_newtree2->Branch("bjet_DeepJet",&bjet_DeepJet);
  jhchoi_newtree2->Branch("bjet_DeepJet_CvsL",&bjet_DeepJet_CvsL);
  jhchoi_newtree2->Branch("bjet_DeepJet_CvsB",&bjet_DeepJet_CvsB);
  jhchoi_newtree2->Branch("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  jhchoi_newtree2->Branch("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  jhchoi_newtree2->Branch("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  jhchoi_newtree2->Branch("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  jhchoi_newtree2->Branch("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  
  jhchoi_newtree2->Branch("bmuon_pt",&bmuon_pt);
  jhchoi_newtree2->Branch("bmuon_eta",&bmuon_eta);
  jhchoi_newtree2->Branch("bmuon_phi",&bmuon_phi);
  jhchoi_newtree2->Branch("bmuon_ptwrtbjet",&bmuon_ptwrtbjet);
  jhchoi_newtree2->Branch("bmuon_p_jetrestf",&bmuon_p_jetrestf);
  jhchoi_newtree2->Branch("bmuon_dR_l_j",&bmuon_dR_l_j);
  jhchoi_newtree2->Branch("bmuon_nsip3d",&bmuon_nsip3d);
  jhchoi_newtree2->Branch("bmuon_reltrkiso",&bmuon_reltrkiso);
  jhchoi_newtree2->Branch("bmuon_reliso",&bmuon_reliso);
  jhchoi_newtree2->Branch("bmuon_charge",&bmuon_charge);
  jhchoi_newtree2->Branch("n_bmuon",&n_bmuon);

  jhchoi_newtree2->Branch("belectron_pt",&belectron_pt);
  jhchoi_newtree2->Branch("belectron_eta",&belectron_eta);
  jhchoi_newtree2->Branch("belectron_phi",&belectron_phi);
  jhchoi_newtree2->Branch("belectron_ptwrtbjet",&belectron_ptwrtbjet);
  jhchoi_newtree2->Branch("belectron_p_jetrestf",&belectron_p_jetrestf);
  jhchoi_newtree2->Branch("belectron_dR_l_j",&belectron_dR_l_j);
  jhchoi_newtree2->Branch("belectron_nsip3d",&belectron_nsip3d);
  jhchoi_newtree2->Branch("belectron_reltrkiso",&belectron_reltrkiso);
  jhchoi_newtree2->Branch("belectron_reliso",&belectron_reliso);
  jhchoi_newtree2->Branch("belectron_charge",&belectron_charge);
  jhchoi_newtree2->Branch("belectron_elecalclusteriso",&belectron_elecalclusteriso);
  jhchoi_newtree2->Branch("belectron_IsGsfCtfScPixChargeConsistent",&belectron_IsGsfCtfScPixChargeConsistent);

  jhchoi_newtree2->Branch("n_belectron",&n_belectron);

  jhchoi_newtree2->Branch("bjetPartonFlavourCharge",&bjetPartonFlavourCharge);
  jhchoi_newtree2->Branch("weight",&weight);
}

void ForNewJetCharge::InitTreeValues(){
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

  bmuon_pt.clear();
  bmuon_eta.clear();
  bmuon_phi.clear();
  bmuon_ptwrtbjet.clear();
  bmuon_p_jetrestf.clear();
  bmuon_dR_l_j.clear();
  bmuon_nsip3d.clear();
  bmuon_reltrkiso.clear();
  bmuon_reliso.clear();
  bmuon_charge.clear();
  n_bmuon=0;


  belectron_pt.clear();
  belectron_eta.clear();
  belectron_phi.clear();
  belectron_ptwrtbjet.clear();
  belectron_p_jetrestf.clear();
  belectron_dR_l_j.clear();
  belectron_nsip3d.clear();
  belectron_reltrkiso.clear();
  belectron_elecalclusteriso.clear();
  belectron_IsGsfCtfScPixChargeConsistent.clear();
  belectron_reliso.clear();
  belectron_charge.clear();

  n_belectron=0;
  //truth
  bjetPartonFlavourCharge=0;

}



void ForNewJetCharge::initializeAnalyzer(){
}

ForNewJetCharge::~ForNewJetCharge(){

  //==== Destructor of this Analyzer

}

bool ForNewJetCharge::Tag_gbToZb(){
  LHEs=GetLHEs();
  ForNewJetCharge::myLHE.LHEsize = LHEs.size();  
  myLHE.ngluon_incoming = 0;
  myLHE.nb_incoming = 0;
  myLHE.nb_outgoing = 0;
  myLHE.abs_nb_outgoing = 0;
  myLHE.nparton_outgoing = 0;
  myLHE.evt_nb = 0;

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

      }
      else if(LHE_id==-5){//if bbar
	myLHE.evt_nb += -1;
	myLHE.nb_incoming    += 1;
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
  return true;

}//[END]Tag_gbToZb()

int ForNewJetCharge::CheckIsBhadAndNb(int pid){
  //----if it is B hadron. return 0 if not B hadron
  //----return -1 if nbbar in hadron==1
  //----return +1 if nb in hadron==1

  //--(1) Check Hadron with 1 b
  auto it = BhadronPIDs.find(pid);
  if (it != BhadronPIDs.end()) {
    //if find
    myGEN.Bhad_pid=pid;
    return 1;
  }
  
  auto itm = BhadronPIDs.find(-pid);//whether anti hadron
  if (itm != BhadronPIDs.end()) {
    //if find
    myGEN.Bhad_pid=pid;
    return -1; // hadron with 1 bbar
  }
  
  //--(2) Check hadron with 2 b
  auto it2 = BhadronPIDs2.find(pid);
  if (it2 != BhadronPIDs2.end()) {
    myGEN.Bhad_pid=pid;
    return 2; // hadron with 2 b
  }
  //anti hadron
  auto itm2 = BhadronPIDs2.find(-pid);
  if (itm2 != BhadronPIDs2.end()) {
    myGEN.Bhad_pid=pid;
    return -2; // hadron with 2 b
  }
  auto it3 = BhadronPIDs3.find(pid);
  if (it3 != BhadronPIDs3.end()) {
    myGEN.Bhad_pid=pid;
    return 3;
  }

  auto itm3 = BhadronPIDs3.find(-pid);
  if (itm3 != BhadronPIDs3.end()) {
    myGEN.Bhad_pid=pid;
    return -3;
  }
  return 0;
}

void ForNewJetCharge::Tag_B_Hadron(){
  //init
  myGEN.HasBhadron = false;

  GENs=GetGens();
  myGEN.GENsize=GENs.size();
  int _nb = 0;
  
  double _Bhad_pt=1;
  //double GEN_status,GEN_eta,GEN_phi,GEN_m;
  double GEN_id,GEN_pt;
  myGEN.Bhad_idx=-1;
  for(unsigned int i =0; i < myGEN.GENsize ; i++){
    //GEN_index=GENs[i].Index();
    //GEN_px=GENs[i].Px();
    //GEN_py=GENs[i].Py();
    //GEN_pz=GENs[i].Pz();

    //GEN_status=GENs[i].Status();
    GEN_id=GENs[i].PID();
    GEN_pt=GENs[i].Pt();
    //GEN_eta=GENs[i].Eta();
    //GEN_phi=GENs[i].Phi();
    //GEN_m=GENs[i].M();    
    
    //CheckIsBhadAndNb(int pid)
    _nb=CheckIsBhadAndNb(GEN_id);
    if (_nb!=0){//is B hadron
      if (GEN_pt > _Bhad_pt){
	_Bhad_pt = GEN_pt;
	myGEN.Bhad_idx=i;
	myGEN.Bhad_nb=_nb;
      }
    }//[END] is B hadron 
  
  }//[END] for GEN particles
  if(myGEN.Bhad_idx>-1){ //HasBhadron
    myGEN.HasBhadron=true;
    myGEN.vBhad=GENs[myGEN.Bhad_idx];

  }//[END]HasBhadron
  
}//[END]Tag_B_Hadron()

void ForNewJetCharge::Loop_genBMatchedRecoJet(){
  //init

  myRECO.HasBmatchedRecoJet = false;
  myRECO.nBmatJet=0;
  AllJets = GetAllJets();
  jetsize=AllJets.size();
  //double _RECO_bj_pt=-999.;
  double _RECO_bj_pt=20.;
  myRECO.ij_B=-1;//Bmatched jet's jet idx
  double jet_pt=-999., jet_flavor= -100, jet_eta = -99;
  //double jet_eta=-999., jet_phi =-999, jet_m = -999, jet_E=-999;
  
  for( unsigned int ij = 0 ; ij < jetsize; ij++){
    jet_pt = AllJets[ij].Pt();
    jet_eta = AllJets[ij].Eta();
    //jet_phi = AllJets[ij].Phi();
    //jet_m = AllJets[ij].M();
    //jet_E = AllJets[ij].E();
    //jet_flavor = AllJets[ij].GenHFHadronMatcherFlavour();
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
    if(myRECO.vBmatchedJet.Pt()){
      BmatJet20Event=true;
    }
    else{
      BmatJet20Event=false;
    }
  }//[END] if there's Bhad matched jet
  
}//[END]ForNewJetCharge::Loop_genBMatchedRecoJet()

/////---Histogram Set---/////




void ForNewJetCharge::AnalyzeGEN(){
  //[TODO]
  //hadron pid by b or bbar
  //hadron nb(-bottomness) by b or bbar
  //kinematics of Bhad to LHE b
  FillHist("gbToZb/BhadPID/"+ProcessName, myGEN.Bhad_pid, weight, 10000, -5000., 5000.);
  FillHist("gbToZb/Bhad_nb/"+ProcessName, myGEN.Bhad_nb, weight, 8, -4., 4.);

  if(myLHE.evt_nb==1){
    FillHist("gbToZb_b/BhadPID/"+ProcessName, myGEN.Bhad_pid, weight, 10000, -5000., 5000.);
    FillHist("gbToZb_b/Bhad_nb/"+ProcessName, myGEN.Bhad_nb, weight, 8, -4., 4.);
  }
  else if(myLHE.evt_nb==-1){
    FillHist("gbToZb_bbar/BhadPID/"+ProcessName, myGEN.Bhad_pid, weight, 10000, -5000., 5000.);
    FillHist("gbToZb_bbar/Bhad_nb/"+ProcessName, myGEN.Bhad_nb, weight, 8, -4., 4.);
  //myGEN.Bhad_pid
  }
}
void ForNewJetCharge::AnalyzeLHE(){
  //[TODO]
  //bjorken scale of b , bbar
  //Q scale

  //(1)Check Index of incoming parton

  int status=-999, pid=-999;
  double pz=-999,E=-999;
  //cout << "genWeight_X1=" << genWeight_X1 << endl;
  //cout << "genWeight_X2=" << genWeight_X2 << endl;
  //cout << setw(4) << "i" << setw(4) << "pz" << setw(4) << "E" << setw(4) << endl; 
  for(unsigned int i = 0; i < myLHE.LHEsize ; i++){
    status=LHEs[i].Status();
    pid=LHEs[i].ID();
    pz=LHEs[i].Pz();
    E=LHEs[i].E();

    if(status==-1){
      myLHE.incoming_parton_pid.push_back(pid);
    }
    //cout << setw(4) << i << setw(4) << pz << setw(4) << E << setw(4) << endl; 
  }

  myLHE.x_b=-1;
  myLHE.x_g=-1;
  myLHE.Q2=-1;
  if(abs(myLHE.incoming_parton_pid[0])==5){//1st parton is b
    //myLHE.x_b=genWeight_X1;
    myLHE.x_b=LHEs[0].E()/65000.;
  }
  else if (myLHE.incoming_parton_pid[0]==21){//1st parton is g
    //myLHE.x_g=genWeight_X1;
    myLHE.x_g=LHEs[0].E()/65000.;
  }
  else if(abs(myLHE.incoming_parton_pid[1])==5){//1st parton is b
    //myLHE.x_b=genWeight_X2;
    myLHE.x_b=LHEs[1].E()/65000.;
  }
  else if (myLHE.incoming_parton_pid[1]==21){//1st parton is g
    myLHE.x_g=LHEs[0].E()/65000.;
    //myLHE.x_g=genWeight_X2;
  }
  myLHE.Q2=genWeight_Q*genWeight_Q;
  //genWeight_X1

  //Hist for all events
  /*
  int nbin_Q2scale = v_Q2scale_binning.size()-1;
  int nbin_xscale = v_xscale_binning.size()-1;
  FillHist("gbToZb/Q2/"+ProcessName, myLHE.Q2, weight, nbin_Q2scale, Q2scale_binning); //nbin,xmin,xmax
  FillHist("gbToZb/x_b/"+ProcessName, myLHE.x_b, weight, nbin_xscale, xscale_binning); //nbin,xmin,xmax
  FillHist("gbToZb/x_g/"+ProcessName, myLHE.x_g, weight, nbin_xscale, xscale_binning); //nbin,xmin,xmax
  //log scale
  FillHist("gbToZb/logQ2/"+ProcessName, log10(myLHE.Q2), weight, 100, 0, 5); //nbin,xmin,xmax
  FillHist("gbToZb/logx_b/"+ProcessName, log10(myLHE.x_b), weight, 100, -9, 0); //nbin,xmin,xmax
  FillHist("gbToZb/logx_g/"+ProcessName, log10(myLHE.x_g), weight, 100, -9, 0); //nbin,xmin,xmax
  if(myLHE.evt_nb==1){
    FillHist("gbToZb_b/Q2/"+ProcessName, myLHE.Q2, weight, nbin_Q2scale, Q2scale_binning); //nbin,xmin,xmax
    FillHist("gbToZb_b/x_b/"+ProcessName, myLHE.x_b, weight, nbin_xscale,xscale_binning); 
    FillHist("gbToZb_b/x_g/"+ProcessName, myLHE.x_g, weight, nbin_xscale,xscale_binning); //nbin,xmin,xmax

    FillHist("gbToZb_b/logQ2/"+ProcessName, log10(myLHE.Q2), weight, 100, 0, 5); //nbin,xmin,xmax
    FillHist("gbToZb_b/logx_b/"+ProcessName, log10(myLHE.x_b), weight, 100,-9, 0); 
    FillHist("gbToZb_b/logx_g/"+ProcessName, log10(myLHE.x_g), weight, 100,-9, 0); //nbin,xmin,xmax
  }

  else if(myLHE.evt_nb==-1){
    FillHist("gbToZb_bbar/Q2/"+ProcessName, myLHE.Q2, weight, nbin_Q2scale, Q2scale_binning); //nbin,xmin,xmax
    FillHist("gbToZb_bbar/x_b/"+ProcessName, myLHE.x_b, weight, nbin_xscale,xscale_binning); 
    FillHist("gbToZb_bbar/x_g/"+ProcessName, myLHE.x_g, weight, nbin_xscale,xscale_binning); //nbin,xmin,xmax

    FillHist("gbToZb_bbar/logQ2/"+ProcessName, log10(myLHE.Q2), weight, 100, 0, 5); //nbin,xmin,xmax
    FillHist("gbToZb_bbar/logx_b/"+ProcessName, log10(myLHE.x_b), weight, 100,-9, 0); 
    FillHist("gbToZb_bbar/logx_g/"+ProcessName, log10(myLHE.x_g), weight, 100,-9, 0); //nbin,xmin,xmax
  }
  */
}



bool ForNewJetCharge::ZTagCuts(){
  //[1]---Z -> ll tag--//

  //for mumu channel
  if(myLHE.is_mumu){
    unsigned int nzmuon=0;
    TLorentzVector v_Z;
    v_Z.SetPxPyPzE(0,0,0,0);
    myRECO.idx_Zmuon1=-1;
    myRECO.idx_Zmuon2=-1;
    std::vector<int> v_Zlepidx;
    for(unsigned int i=0; i < muonsize; i++){
      if(AllMuons[i].Pt() < 20) continue;
      if(fabs(AllMuons[i].Eta()) > 2.4) continue;
      
      v_Zlepidx.push_back(i);
      nzmuon+=1;
    }//[END electron loop]
    if(nzmuon<2) return 0;
    myRECO.idx_Zmuon1=v_Zlepidx[0];
    myRECO.idx_Zmuon2=v_Zlepidx[1];
    v_Z+=AllMuons[myRECO.idx_Zmuon1];
    v_Z+=AllMuons[myRECO.idx_Zmuon2];
    if(v_Z.M()<60.) return 0; 
    if(v_Z.M()>120.) return 0; 
    //cout << "ZTagCuts" <<endl;
    //cout << "myRECO.idx_Zmuon1=" << myRECO.idx_Zmuon1 << endl;
    //cout << "myRECO.idx_Zmuon2=" << myRECO.idx_Zmuon2 << endl;
    //cout << "myRECO.ij_B=" << myRECO.ij_B << endl;

    if(AllMuons[myRECO.idx_Zmuon1].DeltaR(AllJets[myRECO.ij_B]) < 0.4) return 0;
    if(AllMuons[myRECO.idx_Zmuon2].DeltaR(AllJets[myRECO.ij_B]) < 0.4) return 0;
  }//[END]mumu channel
  
  
  //for ee channel
  else if(myLHE.is_ee){
    unsigned int nzelectron=0;
    TLorentzVector v_Z;
    v_Z.SetPxPyPzE(0,0,0,0);
    myRECO.idx_Zelectron1=-1;
    myRECO.idx_Zelectron2=-1;
    std::vector<int> v_Zlepidx;
    for(unsigned int i=0; i < electronsize; i++){
      if(AllElectrons[i].Pt() < 20) continue;
      if(fabs(AllElectrons[i].Eta()) > 2.4) continue;
      v_Zlepidx.push_back(i);
      nzelectron+=1;
    }//[END electron loop]
    if(nzelectron<2) return 0;
    myRECO.idx_Zelectron1=v_Zlepidx[0];
    myRECO.idx_Zelectron2=v_Zlepidx[1];
    v_Z+=AllElectrons[myRECO.idx_Zelectron1];
    v_Z+=AllElectrons[myRECO.idx_Zelectron2];
    if(v_Z.M()<70.) return 0;
    if(v_Z.M()>110.) return 0;
    //cout << "ZTagCuts" <<endl;
    //cout << "myRECO.idx_Zelectron1=" << myRECO.idx_Zelectron1 << endl;
    //cout << "myRECO.idx_Zelectron2=" << myRECO.idx_Zelectron2 << endl;
    //cout << "myRECO.ij_B=" << myRECO.ij_B << endl;    
    if(AllElectrons[myRECO.idx_Zelectron1].DeltaR(AllJets[myRECO.ij_B]) < 0.4) return 0;
    if(AllElectrons[myRECO.idx_Zelectron2].DeltaR(AllJets[myRECO.ij_B]) < 0.4) return 0;
  }//[END]ee channel

  //--[END] Z->ll tag

  return 1;

}



//Sorting Leptons with P@j restframe , near 1.7
int ForNewJetCharge::Rank1n2Leptons(std::vector<int> &v_blep_idx, std::vector<double> &v_blep_value){
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


void ForNewJetCharge::FillHistMuon(TString cutname){
  FillHist(cutname+"/muon_P_jetrestf/"+ProcessName, p_jetrestf, weight, 200, 0., 10.);
  FillHist(cutname+"/muon_dRbmatj/"+ProcessName, dR_l_j, weight, 200, 0., 5.);
  FillHist(cutname+"/muon_ip3d/"+ProcessName, ip3d, weight, 100, -10., 10.);
  FillHist(cutname+"/muon_nsip3d/"+ProcessName, nsip3d, weight, 100, 0., 10.);
  FillHist(cutname+"/muon_logreliso/"+ProcessName, log10(reliso), weight, 100, -5., 2.);
  FillHist(cutname+"/muon_logreltrkiso/"+ProcessName, log10(reltrkiso), weight, 100, -5., 2.);
}

void ForNewJetCharge::FillHistMuonCharge(TString cutname){
  FillHist(cutname+"/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
  FillHist(cutname+"/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
  FillHist(cutname+"/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);


}

void ForNewJetCharge::RunLeptonCutStudyMuon(){
  TString CutStudyEventTag=EventTag;
  CutStudyEventTag="CutStudy__"+CutStudyEventTag;
  TString CutStudyEventTagJetParton=EventTagJetParton;
  CutStudyEventTagJetParton="CutStudy__"+CutStudyEventTagJetParton;
  std::vector<int> v_bmuonidx;
  std::vector<int> v_tmva_bmuonidx;
  std::vector<double> v_tmva_bmuon_p_jetrestf;
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
      v_tmva_bmuonidx.push_back(i);
      v_tmva_bmuon_p_jetrestf.push_back(p_jetrestf);
    }
  }
  if(v_tmva_bmuonidx.size()>0){
    SetTreeValuesMuon(v_tmva_bmuonidx);
  }
  
}
void ForNewJetCharge::SetTreeValuesMuon(vector<int> vmuonidx){
  doFillTree=true;
  unsigned int nbmuon=vmuonidx.size();
  for(int i=0; i < nbmuon; i++){
    //--p jetrestf
    int i_bmuon=vmuonidx[i];
    TLorentzVector vl(AllMuons[i_bmuon]);
    vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
    p_jetrestf=vl.P();//                                                                                                          
    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllMuons[i_bmuon]);
    //ip3d=AllMuons[i_bmuon].IP3D();
    nsip3d=fabs(AllMuons[i_bmuon].IP3D()/AllMuons[i_bmuon].IP3Derr());
    reliso=AllMuons[i_bmuon].RelIso();
    reltrkiso=AllMuons[i_bmuon].TrkIso()/AllMuons[i_bmuon].Pt();
    //pt wrt bjet
    double ptwrtbjet=AllMuons[i_bmuon].P()*sin(AllMuons[i_bmuon].Angle(AllJets[myRECO.ij_B].Vect()));
    
    
    //bmuon_pt=min(AllMuons[i_bmuon].Pt(),50.);
    bmuon_pt.push_back(AllMuons[i_bmuon].Pt());
    bmuon_eta.push_back(AllMuons[i_bmuon].Eta());
    bmuon_phi.push_back(AllMuons[i_bmuon].Phi());
    bmuon_ptwrtbjet.push_back(ptwrtbjet);
    bmuon_p_jetrestf.push_back(p_jetrestf);
    bmuon_dR_l_j.push_back(dR_l_j);
    //bmuon_nsip3d=min(nsip3d,5.);
    bmuon_nsip3d.push_back(nsip3d);
    //bmuon_reltrkiso=min(reltrkiso,15.);
    bmuon_reltrkiso.push_back(reltrkiso);
    //bmuon_reliso=min(reliso,15.);
    bmuon_reliso.push_back(reliso);
    bmuon_charge.push_back(AllMuons[i_bmuon].Charge());
  }//for bmuon loop
  n_bmuon=nbmuon;

  //jet
  bjet_charge=AllJets[myRECO.ij_B].Charge();
  //bjet_pt=min(AllJets[myRECO.ij_B].Pt(),250.);
  bjet_pt=AllJets[myRECO.ij_B].Pt();
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

  bjetPartonFlavourCharge=0.;
  if((AllJets[myRECO.ij_B].partonFlavour() == -5)  && (myLHE.evt_nb==-1)){
    bjetPartonFlavourCharge=1.;
  }
  else if((AllJets[myRECO.ij_B].partonFlavour() == 5) && (myLHE.evt_nb==1) ){
    bjetPartonFlavourCharge=-1.;
  }
  else{
    doFillTree=false;
  }

}





void ForNewJetCharge::FillHistElectron(TString cutname){
  FillHist(cutname+"/electron_P_jetrestf/"+ProcessName, p_jetrestf, weight, 200, 0., 10.);
  FillHist(cutname+"/electron_dRbmatj/"+ProcessName, dR_l_j, weight, 200, 0., 5.);
  FillHist(cutname+"/electron_ip3d/"+ProcessName, ip3d, weight, 100, -10., 10.);
  FillHist(cutname+"/electron_nsip3d/"+ProcessName, nsip3d, weight, 100, 0., 10.);
  FillHist(cutname+"/electron_logreliso/"+ProcessName, log10(reliso), weight, 100, -5., 2.);
  FillHist(cutname+"/electron_logreltrkiso/"+ProcessName, log10(reltrkiso), weight, 100, -5., 2.);
  FillHist(cutname+"/electron_logrelecalclusteriso/"+ProcessName, log10(relecalclusteriso), weight, 100, -5., 2.);
  FillHist(cutname+"/electron_IsGsfCtfScPixChargeConsistent/"+ProcessName, IsGsfCtfScPixChargeConsistent, weight, 4, -1., 3.);//
}

void ForNewJetCharge::FillHistElectronCharge(TString cutname){
  FillHist(cutname+"/belectron_charge/"+ProcessName, AllElectrons[i_belectron].Charge(), weight, 4, -2., 2.);
  FillHist(cutname+"/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
  FillHist(cutname+"/belectron_bjet_chargesum/"+ProcessName, AllElectrons[i_belectron].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);


}

void ForNewJetCharge::RunLeptonCutStudyElectron(){
  TString CutStudyEventTag=EventTag;
  CutStudyEventTag="CutStudy__"+CutStudyEventTag;
  TString CutStudyEventTagJetParton=EventTagJetParton;
  CutStudyEventTagJetParton="CutStudy__"+CutStudyEventTagJetParton;
  std::vector<int> v_belectronidx;
  std::vector<int> v_tmva_belectronidx;
  std::vector<double> v_tmva_belectron_p_jetrestf;

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
    relecalclusteriso=AllElectrons[i].ecalPFClusterIso()/AllElectrons[i].Pt();
    IsGsfCtfScPixChargeConsistent=AllElectrons[i].IsGsfCtfScPixChargeConsistent();

    int electron_charge=AllElectrons[i].Charge();



    if(dR_l_j<0.4){
      v_tmva_belectronidx.push_back(i);
      v_tmva_belectron_p_jetrestf.push_back(p_jetrestf);
    }
  }
  
  if(v_tmva_belectronidx.size()>0){
    SetTreeValuesElectron(v_tmva_belectronidx);
  }//end of if nocut belectron
  
  
}



void ForNewJetCharge::SetTreeValuesElectron(vector<int> velectronidx){
  doFillTree=true;
  unsigned int nbelectron=velectronidx.size();
  for(int i=0; i < nbelectron; i++){
    int i_belectron=velectronidx[i];
    //--p jetrestf
    TLorentzVector vl(AllElectrons[i_belectron]);
    vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
    p_jetrestf=vl.P();//                                                                                                          
    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllElectrons[i_belectron]);
    //ip3d=AllElectrons[i_belectron].IP3D();
    nsip3d=fabs(AllElectrons[i_belectron].IP3D()/AllElectrons[i_belectron].IP3Derr());
    reliso=AllElectrons[i_belectron].RelIso();
    reltrkiso=AllElectrons[i_belectron].TrkIso()/AllElectrons[i_belectron].Pt();
    //pt wrt bjet
    double ptwrtbjet=AllElectrons[i_belectron].P()*sin(AllElectrons[i_belectron].Angle(AllJets[myRECO.ij_B].Vect()));
    
    
    //belectron_pt=min(AllElectrons[i_belectron].Pt(),50.);
    belectron_pt.push_back(AllElectrons[i_belectron].Pt());
    belectron_eta.push_back(AllElectrons[i_belectron].Eta());
    belectron_phi.push_back(AllElectrons[i_belectron].Phi());
    belectron_ptwrtbjet.push_back(ptwrtbjet);
    belectron_p_jetrestf.push_back(p_jetrestf);
    belectron_dR_l_j.push_back(dR_l_j);
    //belectron_nsip3d=min(nsip3d,5.);
    belectron_nsip3d.push_back(nsip3d);
    //belectron_reltrkiso=min(reltrkiso,15.);
    belectron_reltrkiso.push_back(reltrkiso);
    //belectron_elecalclusteriso=min(AllElectrons[i_belectron].ecalPFClusterIso()/AllElectrons[i_belectron].Pt(),10.);
    belectron_elecalclusteriso.push_back(AllElectrons[i_belectron].ecalPFClusterIso()/AllElectrons[i_belectron].Pt());
    belectron_IsGsfCtfScPixChargeConsistent.push_back(AllElectrons[i_belectron].IsGsfCtfScPixChargeConsistent());
    //belectron_reliso=min(reliso,15.);
    belectron_reliso.push_back(reliso);
    belectron_charge.push_back(AllElectrons[i_belectron].Charge());
  }
  n_belectron=nbelectron;
  
  //jet
  bjet_charge=AllJets[myRECO.ij_B].Charge();
  //bjet_pt=min(AllJets[myRECO.ij_B].Pt(),250.);
  bjet_pt=AllJets[myRECO.ij_B].Pt();
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


  bjetPartonFlavourCharge=0.;
  if((AllJets[myRECO.ij_B].partonFlavour() == -5 ) && (myLHE.evt_nb==-1)){
    bjetPartonFlavourCharge=1.;
  }
  else if ((AllJets[myRECO.ij_B].partonFlavour() == 5) && (myLHE.evt_nb==1) ){
    bjetPartonFlavourCharge=-1.;
  }
  else{
    doFillTree=false;
    //discard this event if there's any ambiguity
  }

}







void ForNewJetCharge::AnalyzeRECO(){

  //call muon/electron
  AllMuons=GetAllMuons();
  muonsize = AllMuons.size();
  AllElectrons=GetAllElectrons();
  electronsize = AllElectrons.size();
  
  //(0) Apply some basic cuts
  bool isGoodZ=ForNewJetCharge::ZTagCuts();
  if(!isGoodZ) return;
  //->now Z is reconstructed
  //(1) Do Main Analysis
  //(1-1) Set EventTag
  if(myLHE.evt_nb==1){
    EventTag+="bevt";

  }
  else if(myLHE.evt_nb==-1){
    EventTag+="bbar";
  }
  //For partonFlavour-based EventTagJetParton
  //myRECO.ij_B
  if(AllJets[myRECO.ij_B].partonFlavour() ==5 ){
    EventTagJetParton="From_b";
  }
  else if(AllJets[myRECO.ij_B].partonFlavour() == -5 ){
    EventTagJetParton="From_bbar";
  }
  else{
    EventTagJetParton="From_OtherParton";
  }
  FillHist(EventTag+"/partonFlavour/"+ProcessName,AllJets[myRECO.ij_B].partonFlavour(),weight, 30, -5., 25.);
  FillHist(EventTagJetParton+"/evt_nb/"+ProcessName,myLHE.evt_nb,weight, 4, -2., 2.);
  if(myLHE.is_ee){
    EventTag+="_ee";
    EventTagJetParton+="_ee";
  }
  else if(myLHE.is_mumu){
    EventTag+="_mm";
    EventTagJetParton+="_mm";
  }
  
  //(1-2)For B hadron to lepton decay
  //ForNewJetCharge::RunProtoTypeMuon();
  //ForNewJetCharge::RunProtoTypeElectron();
  ForNewJetCharge::RunLeptonCutStudyMuon();
  ForNewJetCharge::RunLeptonCutStudyElectron();
  

}

void ForNewJetCharge::executeEvent(){
  EventTag="";
  EventTagJetParton="";
  doPrint=false;
  weight = 1.;//init event weight
  weight *= MCweight();

  //initialize//
  myLHE.incoming_parton_pid.clear();
  InitTreeValues();
  doFillTree=false;
  //(1)---Let's tag only events with following process..
  //         g      =====o----- b(or bbar)
  //                     |
  //                     |
  //   b(or bbar)   -----o======     Z
  //
  
  myLHE.is_gbToZb = ForNewJetCharge::Tag_gbToZb(); 
  if(!myLHE.is_gbToZb) return;
  if (!allow_tautau){
    if (myLHE.is_tautau) return;
  }
  FillHist("gbToZb/evt_nb_LHE/"+ProcessName,myLHE.evt_nb,weight, 4, -2., 2.);
  //->For LHE info, tag events with one gluon and one b(bbar)quark 
  // if b event : ForNewJetCharge::myLHE.evt_nb=1
  // if bbar event : ForNewJetCharge::myLHE.evt_nb=-1

  //(2)---Get the most energetic B-hadron info. in GEN
  ForNewJetCharge::Tag_B_Hadron();
  //->For GEN particles 
  //  -> Tag All B hadron and get the most energetic B-hadron info.
  
  //(3)---Check Jet matching to B-hadron
  ForNewJetCharge::Loop_genBMatchedRecoJet();


  //(4)---Now basic generator level info is set. do analysis//fill histograms
  ForNewJetCharge::AnalyzeLHE();
  ForNewJetCharge::AnalyzeGEN();
  if(!myRECO.HasBmatchedRecoJet) return; // if there's no bmatjet->return
  if(!(1==myRECO.nBmatJet)) return;
  ForNewJetCharge::AnalyzeRECO();
  //NowFillTree
  if(doFillTree){
    //cout<<"myLHE.evt_nb="<<myLHE.evt_nb<<endl;
    //cout<<"AllJets[myRECO.ij_B].partonFlavour()="<<AllJets[myRECO.ij_B].partonFlavour()<<endl;
    //cout << "bjetPartonFlavourCharge=" << bjetPartonFlavourCharge <<endl;
    if(bjetPartonFlavourCharge<0){//bevt
      jhchoi_newtree->Fill();
    }
    else if (bjetPartonFlavourCharge>0){//bbar

      jhchoi_newtree2->Fill();
    }
  }
  
  
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
