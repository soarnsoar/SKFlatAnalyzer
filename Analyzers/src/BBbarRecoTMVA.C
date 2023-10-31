#include "BBbarRecoTMVA.h"


BBbarRecoTMVA::BBbarRecoTMVA(){//FYI : bottomness = -nb
  //Set Hadron PID vector with nb=+1
  initTMVAmodel();
  initTMVAmodel2();
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
  jhchoi_newtree=new TTree("TreeForTMVA_neg_Train","TreeForTMVA_neg_Train");
  jhchoi_newtree2=new TTree("TreeForTMVA_pos_Train","TreeForTMVA_pos_Train");
  jhchoi_newtree3=new TTree("TreeForTMVA_neg_Test","TreeForTMVA_neg_Test");
  jhchoi_newtree4=new TTree("TreeForTMVA_pos_Test","TreeForTMVA_pos_Test");

  //tree#1 bevt Train
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
  
  jhchoi_newtree->Branch("bmuon1_pt",&bmuon1_pt);
  jhchoi_newtree->Branch("bmuon1_eta",&bmuon1_eta);
  jhchoi_newtree->Branch("bmuon1_phi",&bmuon1_phi);
  jhchoi_newtree->Branch("bmuon1_ptwrtbjet",&bmuon1_ptwrtbjet);
  jhchoi_newtree->Branch("bmuon1_p_jetrestf",&bmuon1_p_jetrestf);
  jhchoi_newtree->Branch("bmuon1_dR_l_j",&bmuon1_dR_l_j);
  jhchoi_newtree->Branch("bmuon1_nsip3d",&bmuon1_nsip3d);
  jhchoi_newtree->Branch("bmuon1_reltrkiso",&bmuon1_reltrkiso);
  jhchoi_newtree->Branch("bmuon1_reliso",&bmuon1_reliso);
  jhchoi_newtree->Branch("bmuon1_charge",&bmuon1_charge);
  jhchoi_newtree->Branch("bmuon2_pt",&bmuon2_pt);
  jhchoi_newtree->Branch("bmuon2_eta",&bmuon2_eta);
  jhchoi_newtree->Branch("bmuon2_phi",&bmuon2_phi);
  jhchoi_newtree->Branch("bmuon2_ptwrtbjet",&bmuon2_ptwrtbjet);
  jhchoi_newtree->Branch("bmuon2_p_jetrestf",&bmuon2_p_jetrestf);
  jhchoi_newtree->Branch("bmuon2_dR_l_j",&bmuon2_dR_l_j);
  jhchoi_newtree->Branch("bmuon2_nsip3d",&bmuon2_nsip3d);
  jhchoi_newtree->Branch("bmuon2_reltrkiso",&bmuon2_reltrkiso);
  jhchoi_newtree->Branch("bmuon2_reliso",&bmuon2_reliso);
  jhchoi_newtree->Branch("bmuon2_charge",&bmuon2_charge);
  jhchoi_newtree->Branch("n_bmuon",&n_bmuon);
  //  belectron1_elecalclusteriso=-10.;
  //belectron1_IsGsfCtfScPixChargeConsistent=-10.;

  jhchoi_newtree->Branch("belectron1_pt",&belectron1_pt);
  jhchoi_newtree->Branch("belectron1_eta",&belectron1_eta);
  jhchoi_newtree->Branch("belectron1_phi",&belectron1_phi);
  jhchoi_newtree->Branch("belectron1_ptwrtbjet",&belectron1_ptwrtbjet);
  jhchoi_newtree->Branch("belectron1_p_jetrestf",&belectron1_p_jetrestf);
  jhchoi_newtree->Branch("belectron1_dR_l_j",&belectron1_dR_l_j);
  jhchoi_newtree->Branch("belectron1_nsip3d",&belectron1_nsip3d);
  jhchoi_newtree->Branch("belectron1_reltrkiso",&belectron1_reltrkiso);
  jhchoi_newtree->Branch("belectron1_reliso",&belectron1_reliso);
  jhchoi_newtree->Branch("belectron1_charge",&belectron1_charge);
  jhchoi_newtree->Branch("belectron1_elecalclusteriso",&belectron1_elecalclusteriso);
  jhchoi_newtree->Branch("belectron1_IsGsfCtfScPixChargeConsistent",&belectron1_IsGsfCtfScPixChargeConsistent);

  jhchoi_newtree->Branch("belectron2_pt",&belectron2_pt);
  jhchoi_newtree->Branch("belectron2_eta",&belectron2_eta);
  jhchoi_newtree->Branch("belectron2_phi",&belectron2_phi);
  jhchoi_newtree->Branch("belectron2_ptwrtbjet",&belectron2_ptwrtbjet);
  jhchoi_newtree->Branch("belectron2_p_jetrestf",&belectron2_p_jetrestf);
  jhchoi_newtree->Branch("belectron2_dR_l_j",&belectron2_dR_l_j);
  jhchoi_newtree->Branch("belectron2_nsip3d",&belectron2_nsip3d);
  jhchoi_newtree->Branch("belectron2_reltrkiso",&belectron2_reltrkiso);
  jhchoi_newtree->Branch("belectron2_reliso",&belectron2_reliso);
  jhchoi_newtree->Branch("belectron2_charge",&belectron2_charge);
  jhchoi_newtree->Branch("belectron2_elecalclusteriso",&belectron2_elecalclusteriso);
  jhchoi_newtree->Branch("belectron2_IsGsfCtfScPixChargeConsistent",&belectron2_IsGsfCtfScPixChargeConsistent);

  jhchoi_newtree->Branch("n_belectron",&n_belectron);

  //  belectron1_elecalclusteriso=-10.;
  //belectron1_IsGsfCtfScPixChargeConsistent=-10.;
  jhchoi_newtree->Branch("bjetPartonFlavourCharge",&bjetPartonFlavourCharge);
  jhchoi_newtree->Branch("weight",&weight);
  jhchoi_newtree->Branch("isEvenEvent",&isEvenEvent);
  jhchoi_newtree->Branch("DNN1",&DNN1);
  jhchoi_newtree->Branch("DNN2",&DNN2);
  jhchoi_newtree->Branch("DNN_Final",&DNN_Final);

  //tree#2(bbar Train)
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
  
  jhchoi_newtree2->Branch("bmuon1_pt",&bmuon1_pt);
  jhchoi_newtree2->Branch("bmuon1_eta",&bmuon1_eta);
  jhchoi_newtree2->Branch("bmuon1_phi",&bmuon1_phi);
  jhchoi_newtree2->Branch("bmuon1_ptwrtbjet",&bmuon1_ptwrtbjet);
  jhchoi_newtree2->Branch("bmuon1_p_jetrestf",&bmuon1_p_jetrestf);
  jhchoi_newtree2->Branch("bmuon1_dR_l_j",&bmuon1_dR_l_j);
  jhchoi_newtree2->Branch("bmuon1_nsip3d",&bmuon1_nsip3d);
  jhchoi_newtree2->Branch("bmuon1_reltrkiso",&bmuon1_reltrkiso);
  jhchoi_newtree2->Branch("bmuon1_reliso",&bmuon1_reliso);
  jhchoi_newtree2->Branch("bmuon1_charge",&bmuon1_charge);
  jhchoi_newtree2->Branch("bmuon2_pt",&bmuon2_pt);
  jhchoi_newtree2->Branch("bmuon2_eta",&bmuon2_eta);
  jhchoi_newtree2->Branch("bmuon2_phi",&bmuon2_phi);
  jhchoi_newtree2->Branch("bmuon2_ptwrtbjet",&bmuon2_ptwrtbjet);
  jhchoi_newtree2->Branch("bmuon2_p_jetrestf",&bmuon2_p_jetrestf);
  jhchoi_newtree2->Branch("bmuon2_dR_l_j",&bmuon2_dR_l_j);
  jhchoi_newtree2->Branch("bmuon2_nsip3d",&bmuon2_nsip3d);
  jhchoi_newtree2->Branch("bmuon2_reltrkiso",&bmuon2_reltrkiso);
  jhchoi_newtree2->Branch("bmuon2_reliso",&bmuon2_reliso);
  jhchoi_newtree2->Branch("bmuon2_charge",&bmuon2_charge);
  jhchoi_newtree2->Branch("n_bmuon",&n_bmuon);

  jhchoi_newtree2->Branch("belectron1_pt",&belectron1_pt);
  jhchoi_newtree2->Branch("belectron1_eta",&belectron1_eta);
  jhchoi_newtree2->Branch("belectron1_phi",&belectron1_phi);
  jhchoi_newtree2->Branch("belectron1_ptwrtbjet",&belectron1_ptwrtbjet);
  jhchoi_newtree2->Branch("belectron1_p_jetrestf",&belectron1_p_jetrestf);
  jhchoi_newtree2->Branch("belectron1_dR_l_j",&belectron1_dR_l_j);
  jhchoi_newtree2->Branch("belectron1_nsip3d",&belectron1_nsip3d);
  jhchoi_newtree2->Branch("belectron1_reltrkiso",&belectron1_reltrkiso);
  jhchoi_newtree2->Branch("belectron1_reliso",&belectron1_reliso);
  jhchoi_newtree2->Branch("belectron1_charge",&belectron1_charge);
  jhchoi_newtree2->Branch("belectron1_elecalclusteriso",&belectron1_elecalclusteriso);
  jhchoi_newtree2->Branch("belectron1_IsGsfCtfScPixChargeConsistent",&belectron1_IsGsfCtfScPixChargeConsistent);



  jhchoi_newtree2->Branch("belectron2_pt",&belectron2_pt);
  jhchoi_newtree2->Branch("belectron2_eta",&belectron2_eta);
  jhchoi_newtree2->Branch("belectron2_phi",&belectron2_phi);
  jhchoi_newtree2->Branch("belectron2_ptwrtbjet",&belectron2_ptwrtbjet);
  jhchoi_newtree2->Branch("belectron2_p_jetrestf",&belectron2_p_jetrestf);
  jhchoi_newtree2->Branch("belectron2_dR_l_j",&belectron2_dR_l_j);
  jhchoi_newtree2->Branch("belectron2_nsip3d",&belectron2_nsip3d);
  jhchoi_newtree2->Branch("belectron2_reltrkiso",&belectron2_reltrkiso);
  jhchoi_newtree2->Branch("belectron2_reliso",&belectron2_reliso);
  jhchoi_newtree2->Branch("belectron2_charge",&belectron2_charge);
  jhchoi_newtree2->Branch("belectron2_elecalclusteriso",&belectron2_elecalclusteriso);
  jhchoi_newtree2->Branch("belectron2_IsGsfCtfScPixChargeConsistent",&belectron2_IsGsfCtfScPixChargeConsistent);


  jhchoi_newtree2->Branch("n_belectron",&n_belectron);

  jhchoi_newtree2->Branch("bjetPartonFlavourCharge",&bjetPartonFlavourCharge);
  jhchoi_newtree2->Branch("weight",&weight);
  jhchoi_newtree2->Branch("isEvenEvent",&isEvenEvent);
  jhchoi_newtree2->Branch("DNN1",&DNN1);
  jhchoi_newtree2->Branch("DNN2",&DNN2);
  jhchoi_newtree2->Branch("DNN_Final",&DNN_Final);
  //tree#3 bevt Test
  jhchoi_newtree3->Branch("bjet_charge",&bjet_charge);
  jhchoi_newtree3->Branch("bjet_pt",&bjet_pt);
  jhchoi_newtree3->Branch("bjet_eta",&bjet_eta);
  jhchoi_newtree3->Branch("bjet_phi",&bjet_phi);
  jhchoi_newtree3->Branch("bjet_DeepJet",&bjet_DeepJet);
  jhchoi_newtree3->Branch("bjet_DeepJet_CvsL",&bjet_DeepJet_CvsL);
  jhchoi_newtree3->Branch("bjet_DeepJet_CvsB",&bjet_DeepJet_CvsB);
  jhchoi_newtree3->Branch("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  jhchoi_newtree3->Branch("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  jhchoi_newtree3->Branch("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  jhchoi_newtree3->Branch("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  jhchoi_newtree3->Branch("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  
  jhchoi_newtree3->Branch("bmuon1_pt",&bmuon1_pt);
  jhchoi_newtree3->Branch("bmuon1_eta",&bmuon1_eta);
  jhchoi_newtree3->Branch("bmuon1_phi",&bmuon1_phi);
  jhchoi_newtree3->Branch("bmuon1_ptwrtbjet",&bmuon1_ptwrtbjet);
  jhchoi_newtree3->Branch("bmuon1_p_jetrestf",&bmuon1_p_jetrestf);
  jhchoi_newtree3->Branch("bmuon1_dR_l_j",&bmuon1_dR_l_j);
  jhchoi_newtree3->Branch("bmuon1_nsip3d",&bmuon1_nsip3d);
  jhchoi_newtree3->Branch("bmuon1_reltrkiso",&bmuon1_reltrkiso);
  jhchoi_newtree3->Branch("bmuon1_reliso",&bmuon1_reliso);
  jhchoi_newtree3->Branch("bmuon1_charge",&bmuon1_charge);
  jhchoi_newtree3->Branch("bmuon2_pt",&bmuon2_pt);
  jhchoi_newtree3->Branch("bmuon2_eta",&bmuon2_eta);
  jhchoi_newtree3->Branch("bmuon2_phi",&bmuon2_phi);
  jhchoi_newtree3->Branch("bmuon2_ptwrtbjet",&bmuon2_ptwrtbjet);
  jhchoi_newtree3->Branch("bmuon2_p_jetrestf",&bmuon2_p_jetrestf);
  jhchoi_newtree3->Branch("bmuon2_dR_l_j",&bmuon2_dR_l_j);
  jhchoi_newtree3->Branch("bmuon2_nsip3d",&bmuon2_nsip3d);
  jhchoi_newtree3->Branch("bmuon2_reltrkiso",&bmuon2_reltrkiso);
  jhchoi_newtree3->Branch("bmuon2_reliso",&bmuon2_reliso);
  jhchoi_newtree3->Branch("bmuon2_charge",&bmuon2_charge);
  jhchoi_newtree3->Branch("n_bmuon",&n_bmuon);
  //  belectron1_elecalclusteriso=-10.;
  //belectron1_IsGsfCtfScPixChargeConsistent=-10.;

  jhchoi_newtree3->Branch("belectron1_pt",&belectron1_pt);
  jhchoi_newtree3->Branch("belectron1_eta",&belectron1_eta);
  jhchoi_newtree3->Branch("belectron1_phi",&belectron1_phi);
  jhchoi_newtree3->Branch("belectron1_ptwrtbjet",&belectron1_ptwrtbjet);
  jhchoi_newtree3->Branch("belectron1_p_jetrestf",&belectron1_p_jetrestf);
  jhchoi_newtree3->Branch("belectron1_dR_l_j",&belectron1_dR_l_j);
  jhchoi_newtree3->Branch("belectron1_nsip3d",&belectron1_nsip3d);
  jhchoi_newtree3->Branch("belectron1_reltrkiso",&belectron1_reltrkiso);
  jhchoi_newtree3->Branch("belectron1_reliso",&belectron1_reliso);
  jhchoi_newtree3->Branch("belectron1_charge",&belectron1_charge);
  jhchoi_newtree3->Branch("belectron1_elecalclusteriso",&belectron1_elecalclusteriso);
  jhchoi_newtree3->Branch("belectron1_IsGsfCtfScPixChargeConsistent",&belectron1_IsGsfCtfScPixChargeConsistent);

  jhchoi_newtree3->Branch("belectron2_pt",&belectron2_pt);
  jhchoi_newtree3->Branch("belectron2_eta",&belectron2_eta);
  jhchoi_newtree3->Branch("belectron2_phi",&belectron2_phi);
  jhchoi_newtree3->Branch("belectron2_ptwrtbjet",&belectron2_ptwrtbjet);
  jhchoi_newtree3->Branch("belectron2_p_jetrestf",&belectron2_p_jetrestf);
  jhchoi_newtree3->Branch("belectron2_dR_l_j",&belectron2_dR_l_j);
  jhchoi_newtree3->Branch("belectron2_nsip3d",&belectron2_nsip3d);
  jhchoi_newtree3->Branch("belectron2_reltrkiso",&belectron2_reltrkiso);
  jhchoi_newtree3->Branch("belectron2_reliso",&belectron2_reliso);
  jhchoi_newtree3->Branch("belectron2_charge",&belectron2_charge);
  jhchoi_newtree3->Branch("belectron2_elecalclusteriso",&belectron2_elecalclusteriso);
  jhchoi_newtree3->Branch("belectron2_IsGsfCtfScPixChargeConsistent",&belectron2_IsGsfCtfScPixChargeConsistent);

  jhchoi_newtree3->Branch("n_belectron",&n_belectron);

  //  belectron1_elecalclusteriso=-10.;
  //belectron1_IsGsfCtfScPixChargeConsistent=-10.;
  jhchoi_newtree3->Branch("bjetPartonFlavourCharge",&bjetPartonFlavourCharge);
  jhchoi_newtree3->Branch("weight",&weight);
  jhchoi_newtree3->Branch("isEvenEvent",&isEvenEvent);
  jhchoi_newtree3->Branch("DNN1",&DNN1);
  jhchoi_newtree3->Branch("DNN2",&DNN2);
  jhchoi_newtree3->Branch("DNN_Final",&DNN_Final);
  //tree#4(bbar Test)
  jhchoi_newtree4->Branch("bjet_charge",&bjet_charge);
  jhchoi_newtree4->Branch("bjet_pt",&bjet_pt);
  jhchoi_newtree4->Branch("bjet_eta",&bjet_eta);
  jhchoi_newtree4->Branch("bjet_phi",&bjet_phi);
  jhchoi_newtree4->Branch("bjet_DeepJet",&bjet_DeepJet);
  jhchoi_newtree4->Branch("bjet_DeepJet_CvsL",&bjet_DeepJet_CvsL);
  jhchoi_newtree4->Branch("bjet_DeepJet_CvsB",&bjet_DeepJet_CvsB);
  jhchoi_newtree4->Branch("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  jhchoi_newtree4->Branch("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  jhchoi_newtree4->Branch("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  jhchoi_newtree4->Branch("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  jhchoi_newtree4->Branch("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  
  jhchoi_newtree4->Branch("bmuon1_pt",&bmuon1_pt);
  jhchoi_newtree4->Branch("bmuon1_eta",&bmuon1_eta);
  jhchoi_newtree4->Branch("bmuon1_phi",&bmuon1_phi);
  jhchoi_newtree4->Branch("bmuon1_ptwrtbjet",&bmuon1_ptwrtbjet);
  jhchoi_newtree4->Branch("bmuon1_p_jetrestf",&bmuon1_p_jetrestf);
  jhchoi_newtree4->Branch("bmuon1_dR_l_j",&bmuon1_dR_l_j);
  jhchoi_newtree4->Branch("bmuon1_nsip3d",&bmuon1_nsip3d);
  jhchoi_newtree4->Branch("bmuon1_reltrkiso",&bmuon1_reltrkiso);
  jhchoi_newtree4->Branch("bmuon1_reliso",&bmuon1_reliso);
  jhchoi_newtree4->Branch("bmuon1_charge",&bmuon1_charge);
  jhchoi_newtree4->Branch("bmuon2_pt",&bmuon2_pt);
  jhchoi_newtree4->Branch("bmuon2_eta",&bmuon2_eta);
  jhchoi_newtree4->Branch("bmuon2_phi",&bmuon2_phi);
  jhchoi_newtree4->Branch("bmuon2_ptwrtbjet",&bmuon2_ptwrtbjet);
  jhchoi_newtree4->Branch("bmuon2_p_jetrestf",&bmuon2_p_jetrestf);
  jhchoi_newtree4->Branch("bmuon2_dR_l_j",&bmuon2_dR_l_j);
  jhchoi_newtree4->Branch("bmuon2_nsip3d",&bmuon2_nsip3d);
  jhchoi_newtree4->Branch("bmuon2_reltrkiso",&bmuon2_reltrkiso);
  jhchoi_newtree4->Branch("bmuon2_reliso",&bmuon2_reliso);
  jhchoi_newtree4->Branch("bmuon2_charge",&bmuon2_charge);
  jhchoi_newtree4->Branch("n_bmuon",&n_bmuon);

  jhchoi_newtree4->Branch("belectron1_pt",&belectron1_pt);
  jhchoi_newtree4->Branch("belectron1_eta",&belectron1_eta);
  jhchoi_newtree4->Branch("belectron1_phi",&belectron1_phi);
  jhchoi_newtree4->Branch("belectron1_ptwrtbjet",&belectron1_ptwrtbjet);
  jhchoi_newtree4->Branch("belectron1_p_jetrestf",&belectron1_p_jetrestf);
  jhchoi_newtree4->Branch("belectron1_dR_l_j",&belectron1_dR_l_j);
  jhchoi_newtree4->Branch("belectron1_nsip3d",&belectron1_nsip3d);
  jhchoi_newtree4->Branch("belectron1_reltrkiso",&belectron1_reltrkiso);
  jhchoi_newtree4->Branch("belectron1_reliso",&belectron1_reliso);
  jhchoi_newtree4->Branch("belectron1_charge",&belectron1_charge);
  jhchoi_newtree4->Branch("belectron1_elecalclusteriso",&belectron1_elecalclusteriso);
  jhchoi_newtree4->Branch("belectron1_IsGsfCtfScPixChargeConsistent",&belectron1_IsGsfCtfScPixChargeConsistent);



  jhchoi_newtree4->Branch("belectron2_pt",&belectron2_pt);
  jhchoi_newtree4->Branch("belectron2_eta",&belectron2_eta);
  jhchoi_newtree4->Branch("belectron2_phi",&belectron2_phi);
  jhchoi_newtree4->Branch("belectron2_ptwrtbjet",&belectron2_ptwrtbjet);
  jhchoi_newtree4->Branch("belectron2_p_jetrestf",&belectron2_p_jetrestf);
  jhchoi_newtree4->Branch("belectron2_dR_l_j",&belectron2_dR_l_j);
  jhchoi_newtree4->Branch("belectron2_nsip3d",&belectron2_nsip3d);
  jhchoi_newtree4->Branch("belectron2_reltrkiso",&belectron2_reltrkiso);
  jhchoi_newtree4->Branch("belectron2_reliso",&belectron2_reliso);
  jhchoi_newtree4->Branch("belectron2_charge",&belectron2_charge);
  jhchoi_newtree4->Branch("belectron2_elecalclusteriso",&belectron2_elecalclusteriso);
  jhchoi_newtree4->Branch("belectron2_IsGsfCtfScPixChargeConsistent",&belectron2_IsGsfCtfScPixChargeConsistent);


  jhchoi_newtree4->Branch("n_belectron",&n_belectron);

  jhchoi_newtree4->Branch("bjetPartonFlavourCharge",&bjetPartonFlavourCharge);
  jhchoi_newtree4->Branch("weight",&weight);
  jhchoi_newtree4->Branch("isEvenEvent",&isEvenEvent);
  jhchoi_newtree4->Branch("DNN1",&DNN1);
  jhchoi_newtree4->Branch("DNN2",&DNN2);
  jhchoi_newtree4->Branch("DNN_Final",&DNN_Final);
}

void BBbarRecoTMVA::initTMVAmodel(){
  TString xmlfile="/data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/nominal_odd_evt/TMVAClassification_DNN.weights.xml";
  ///data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/switch_even_evt
  cout << "define tmvareader"<< endl;
  myreader=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader->AddVariable("belectron2_nsip3d",&belectron2_nsip3d);
  myreader->AddVariable("belectron2_p_jetrestf",&belectron2_p_jetrestf);
  myreader->AddVariable("bjet_eta",&bjet_eta);
  myreader->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader->AddVariable("bmuon1_charge",&bmuon1_charge_float);
  myreader->AddVariable("belectron2_IsGsfCtfScPixChargeConsistent",&belectron2_IsGsfCtfScPixChargeConsistent_float);
  myreader->AddVariable("bmuon2_reliso",&bmuon2_reliso);
  myreader->AddVariable("bmuon2_nsip3d",&bmuon2_nsip3d);
  myreader->AddVariable("belectron1_pt",&belectron1_pt);
  myreader->AddVariable("n_bmuon",&n_bmuon_float);
  myreader->AddVariable("belectron2_pt",&belectron2_pt);
  myreader->AddVariable("bmuon1_dR_l_j",&bmuon1_dR_l_j);
  myreader->AddVariable("belectron2_dR_l_j",&belectron2_dR_l_j);
  myreader->AddVariable("belectron1_p_jetrestf",&belectron1_p_jetrestf);
  myreader->AddVariable("bjet_DeepJet_CvsB",&bjet_DeepJet_CvsB);
  myreader->AddVariable("belectron1_ptwrtbjet",&belectron1_ptwrtbjet);
  myreader->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader->AddVariable("bjet_DeepJet_CvsL",&bjet_DeepJet_CvsL);
  myreader->AddVariable("bmuon2_ptwrtbjet",&bmuon2_ptwrtbjet);
  myreader->AddVariable("belectron1_dR_l_j",&belectron1_dR_l_j);
  myreader->AddVariable("belectron1_reltrkiso",&belectron1_reltrkiso);
  myreader->AddVariable("belectron2_charge",&belectron2_charge_float);
  myreader->AddVariable("bmuon2_phi",&bmuon2_phi);
  myreader->AddVariable("bjet_phi",&bjet_phi);
  myreader->AddVariable("belectron2_ptwrtbjet",&belectron2_ptwrtbjet);
  myreader->AddVariable("belectron2_elecalclusteriso",&belectron2_elecalclusteriso);
  myreader->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader->AddVariable("belectron1_nsip3d",&belectron1_nsip3d);
  myreader->AddVariable("belectron1_reliso",&belectron1_reliso);
  myreader->AddVariable("bjet_charge",&bjet_charge);
  myreader->AddVariable("bmuon1_p_jetrestf",&bmuon1_p_jetrestf);
  myreader->AddVariable("bmuon2_charge",&bmuon2_charge_float);
  myreader->AddVariable("bmuon1_reltrkiso",&bmuon1_reltrkiso);
  myreader->AddVariable("bmuon1_reliso",&bmuon1_reliso);
  myreader->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  myreader->AddVariable("belectron1_charge",&belectron1_charge_float);
  myreader->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader->AddVariable("bjet_DeepJet",&bjet_DeepJet);
  myreader->AddVariable("bmuon1_pt",&bmuon1_pt);
  myreader->AddVariable("bmuon2_reltrkiso",&bmuon2_reltrkiso);
  myreader->AddVariable("bmuon2_p_jetrestf",&bmuon2_p_jetrestf);
  myreader->AddVariable("belectron2_reliso",&belectron2_reliso);
  myreader->AddVariable("belectron1_IsGsfCtfScPixChargeConsistent",&belectron1_IsGsfCtfScPixChargeConsistent_float);
  myreader->AddVariable("belectron2_reltrkiso",&belectron2_reltrkiso);
  myreader->AddVariable("bmuon2_pt",&bmuon2_pt);
  myreader->AddVariable("bjet_pt",&bjet_pt);
  myreader->AddVariable("bmuon1_phi",&bmuon1_phi);
  myreader->AddVariable("belectron1_phi",&belectron1_phi);
  myreader->AddVariable("n_belectron",&n_belectron_float);
  myreader->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader->AddVariable("belectron2_phi",&belectron2_phi);
  myreader->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader->AddVariable("bmuon1_ptwrtbjet",&bmuon1_ptwrtbjet);
  myreader->AddVariable("bmuon1_nsip3d",&bmuon1_nsip3d);
  myreader->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader->AddVariable("belectron1_elecalclusteriso",&belectron1_elecalclusteriso);  
  myreader->AddVariable("bmuon2_dR_l_j",&bmuon2_dR_l_j);
  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader->BookMVA("PyKeras::DNN",xmlfile);
  //Float_t ret=myreader->EvaluateMVA("PyKeras::DNN");


  
}


void BBbarRecoTMVA::initTMVAmodel2(){
  //TString xmlfile="/data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/nominal_odd_evt/TMVAClassification_DNN.weights.xml";
  TString xmlfile ="/data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/switch_even_evt/TMVAClassification_DNN.weights.xml";
  cout << "define tmvareader2"<< endl;
  myreader2=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader2->AddVariable("belectron2_nsip3d",&belectron2_nsip3d);
  myreader2->AddVariable("belectron2_p_jetrestf",&belectron2_p_jetrestf);
  myreader2->AddVariable("bjet_eta",&bjet_eta);
  myreader2->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader2->AddVariable("bmuon1_charge",&bmuon1_charge_float);
  myreader2->AddVariable("belectron2_IsGsfCtfScPixChargeConsistent",&belectron2_IsGsfCtfScPixChargeConsistent_float);
  myreader2->AddVariable("bmuon2_reliso",&bmuon2_reliso);
  myreader2->AddVariable("bmuon2_nsip3d",&bmuon2_nsip3d);
  myreader2->AddVariable("belectron1_pt",&belectron1_pt);
  myreader2->AddVariable("n_bmuon",&n_bmuon_float);
  myreader2->AddVariable("belectron2_pt",&belectron2_pt);
  myreader2->AddVariable("bmuon1_dR_l_j",&bmuon1_dR_l_j);
  myreader2->AddVariable("belectron2_dR_l_j",&belectron2_dR_l_j);
  myreader2->AddVariable("belectron1_p_jetrestf",&belectron1_p_jetrestf);
  myreader2->AddVariable("bjet_DeepJet_CvsB",&bjet_DeepJet_CvsB);
  myreader2->AddVariable("belectron1_ptwrtbjet",&belectron1_ptwrtbjet);
  myreader2->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader2->AddVariable("bjet_DeepJet_CvsL",&bjet_DeepJet_CvsL);
  myreader2->AddVariable("bmuon2_ptwrtbjet",&bmuon2_ptwrtbjet);
  myreader2->AddVariable("belectron1_dR_l_j",&belectron1_dR_l_j);
  myreader2->AddVariable("belectron1_reltrkiso",&belectron1_reltrkiso);
  myreader2->AddVariable("belectron2_charge",&belectron2_charge_float);
  myreader2->AddVariable("bmuon2_phi",&bmuon2_phi);
  myreader2->AddVariable("bjet_phi",&bjet_phi);
  myreader2->AddVariable("belectron2_ptwrtbjet",&belectron2_ptwrtbjet);
  myreader2->AddVariable("belectron2_elecalclusteriso",&belectron2_elecalclusteriso);
  myreader2->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader2->AddVariable("belectron1_nsip3d",&belectron1_nsip3d);
  myreader2->AddVariable("belectron1_reliso",&belectron1_reliso);
  myreader2->AddVariable("bjet_charge",&bjet_charge);
  myreader2->AddVariable("bmuon1_p_jetrestf",&bmuon1_p_jetrestf);
  myreader2->AddVariable("bmuon2_charge",&bmuon2_charge_float);
  myreader2->AddVariable("bmuon1_reltrkiso",&bmuon1_reltrkiso);
  myreader2->AddVariable("bmuon1_reliso",&bmuon1_reliso);
  myreader2->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  myreader2->AddVariable("belectron1_charge",&belectron1_charge_float);
  myreader2->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader2->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader2->AddVariable("bjet_DeepJet",&bjet_DeepJet);
  myreader2->AddVariable("bmuon1_pt",&bmuon1_pt);
  myreader2->AddVariable("bmuon2_reltrkiso",&bmuon2_reltrkiso);
  myreader2->AddVariable("bmuon2_p_jetrestf",&bmuon2_p_jetrestf);
  myreader2->AddVariable("belectron2_reliso",&belectron2_reliso);
  myreader2->AddVariable("belectron1_IsGsfCtfScPixChargeConsistent",&belectron1_IsGsfCtfScPixChargeConsistent_float);
  myreader2->AddVariable("belectron2_reltrkiso",&belectron2_reltrkiso);
  myreader2->AddVariable("bmuon2_pt",&bmuon2_pt);
  myreader2->AddVariable("bjet_pt",&bjet_pt);
  myreader2->AddVariable("bmuon1_phi",&bmuon1_phi);
  myreader2->AddVariable("belectron1_phi",&belectron1_phi);
  myreader2->AddVariable("n_belectron",&n_belectron_float);
  myreader2->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader2->AddVariable("belectron2_phi",&belectron2_phi);
  myreader2->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader2->AddVariable("bmuon1_ptwrtbjet",&bmuon1_ptwrtbjet);
  myreader2->AddVariable("bmuon1_nsip3d",&bmuon1_nsip3d);
  myreader2->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader2->AddVariable("belectron1_elecalclusteriso",&belectron1_elecalclusteriso);  
  myreader2->AddVariable("bmuon2_dR_l_j",&bmuon2_dR_l_j);
  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader2->BookMVA("PyKeras::DNN",xmlfile);
  //Float_t ret=myreader->EvaluateMVA("PyKeras::DNN");


  
}

void BBbarRecoTMVA::InitTreeValues(){
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
  //leading bmuon
  bmuon1_pt=0.;
  bmuon1_eta=0.;
  bmuon1_phi=0.;
  bmuon1_ptwrtbjet=0.;
  bmuon1_p_jetrestf=0.;
  bmuon1_dR_l_j=0.;
  bmuon1_nsip3d=0.;
  bmuon1_reltrkiso=0.;
  bmuon1_reliso=0.;
  bmuon1_charge=0.;
  //subleading bmuon
  bmuon2_pt=0.;
  bmuon2_eta=0.;
  bmuon2_phi=0.;
  bmuon2_ptwrtbjet=0.;
  bmuon2_p_jetrestf=0.;
  bmuon2_dR_l_j=0.;
  bmuon2_nsip3d=0.;
  bmuon2_reltrkiso=0.;
  bmuon2_reliso=0.;
  bmuon2_charge=0.;

  n_bmuon=0;
  //leading belectron
  belectron1_pt=0.;
  belectron1_eta=0.;
  belectron1_phi=0.;
  belectron1_ptwrtbjet=0.;
  belectron1_p_jetrestf=0.;
  belectron1_dR_l_j=0.;
  belectron1_nsip3d=0.;
  belectron1_reltrkiso=0.;
  belectron1_elecalclusteriso=0.;
  belectron1_IsGsfCtfScPixChargeConsistent=0;
  belectron1_reliso=0.;
  belectron1_charge=0.;
  //subleading belectron
  belectron2_pt=0.;
  belectron2_eta=0.;
  belectron2_phi=0.;
  belectron2_ptwrtbjet=0.;
  belectron2_p_jetrestf=0.;
  belectron2_dR_l_j=0.;
  belectron2_nsip3d=0.;
  belectron2_reltrkiso=0.;
  belectron2_elecalclusteriso=0.;
  belectron2_IsGsfCtfScPixChargeConsistent=0;
  belectron2_reliso=0.;
  belectron2_charge=0.;
  n_belectron=0;
  //truth
  bjetPartonFlavourCharge=0;

  DNN1=0;
  DNN2=0;
  DNN_Final=0;
}



void BBbarRecoTMVA::initializeAnalyzer(){
  /*
  double prenum,curnum;
  prenum=xscale_binning[0];
  for(int i = 1 ; i < 64 ; i++){
    curnum=xscale_binning[i];
    if( prenum >= curnum){
      cout << "!!!!!" << "prenum=" << prenum << "   curnum=" << curnum << endl; 
    }
  }

  prenum=Q2scale_binning[0];
  for(int i = 1 ; i < 53 ; i++){
    curnum=Q2scale_binning[i];
    if( prenum >= curnum){
      cout << "!!!!!" << "prenum=" << prenum << "   curnum=" << curnum << endl; 
    }
  }
  */
  //================================================================
  //====  Example 1
  //====  Dimuon Z-peak events with two muon IDs, with systematics
  //================================================================

  //==== if you use "--userflags RunSyst" with SKFlat.py, HasFlag("RunSyst") will return "true"
  RunSyst = HasFlag("RunSyst");
  cout << "[BBbarRecoTMVA::initializeAnalyzer] RunSyst = " << RunSyst << endl;

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
  cout << "[BBbarRecoTMVA::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;


  //==== (Example) Year-dependent variables
  //==== I defined "TString IsoMuTriggerName;" and "double TriggerSafePtCut;" in Analyzers/include/BBbarRecoTMVA.h 
  //==== IsoMuTriggerName is a year-dependent variable, and you don't want to do "if(Dataer==~~)" for every event (let's save cpu time).
  //==== Then, do it here, which only ran once for each macro
  //==== B-Tagging
  //==== add taggers and WP that you want to use in analysis
  std::vector<JetTagging::Parameters> jtps;
  //==== If you want to use 1a or 2a method,
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepCSV, JetTagging::Medium, JetTagging::incl, JetTagging::comb) );
  //==== set
  mcCorr->SetJetTaggingParameters(jtps);

  //================================
  //==== Example 2
  //==== Using new PDF
  //==== It consumes so much time, so only being actiavted with --userflags RunNewPDF
  //================================

  RunNewPDF = HasFlag("RunNewPDF");
  cout << "[BBbarRecoTMVA::initializeAnalyzer] RunNewPDF = " << RunNewPDF << endl;
  if(RunNewPDF && !IsDATA){

    LHAPDFHandler LHAPDFHandler_Prod;
    LHAPDFHandler_Prod.CentralPDFName = "NNPDF31_nnlo_hessian_pdfas";
    LHAPDFHandler_Prod.init();

    LHAPDFHandler LHAPDFHandler_New;
    LHAPDFHandler_New.CentralPDFName = "NNPDF31_nlo_hessian_pdfas";
    LHAPDFHandler_New.ErrorSetMember_Start = 1; 
    LHAPDFHandler_New.ErrorSetMember_End = 100; 
    LHAPDFHandler_New.AlphaSMember_Down = 101; 
    LHAPDFHandler_New.AlphaSMember_Up = 102; 
    LHAPDFHandler_New.init();

    pdfReweight->SetProdPDF( LHAPDFHandler_Prod.PDFCentral );
    pdfReweight->SetNewPDF( LHAPDFHandler_New.PDFCentral );
    pdfReweight->SetNewPDFErrorSet( LHAPDFHandler_New.PDFErrorSet );
    pdfReweight->SetNewPDFAlphaS( LHAPDFHandler_New.PDFAlphaSDown, LHAPDFHandler_New.PDFAlphaSUp );

  }

  //================================================
  //==== Example 3
  //==== How to estimate xsec errors (PDF & Scale)
  //==== For example, MET
  //================================================

  RunXSecSyst = HasFlag("RunXSecSyst");
  cout << "[BBbarRecoTMVA::initializeAnalyzer] RunXSecSyst = " << RunXSecSyst << endl;

}

BBbarRecoTMVA::~BBbarRecoTMVA(){

  //==== Destructor of this Analyzer

}

bool BBbarRecoTMVA::Tag_gbToZb(){
  LHEs=GetLHEs();
  BBbarRecoTMVA::myLHE.LHEsize = LHEs.size();  
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

int BBbarRecoTMVA::CheckIsBhadAndNb(int pid){
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

void BBbarRecoTMVA::Tag_B_Hadron(){
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

void BBbarRecoTMVA::Loop_genBMatchedRecoJet(){
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
  
}//[END]BBbarRecoTMVA::Loop_genBMatchedRecoJet()

/////---Histogram Set---/////




void BBbarRecoTMVA::AnalyzeGEN(){
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
void BBbarRecoTMVA::AnalyzeLHE(){
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

}



bool BBbarRecoTMVA::ZTagCuts(){
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
int BBbarRecoTMVA::Rank1n2Leptons(std::vector<int> &v_blep_idx, std::vector<double> &v_blep_value){
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


void BBbarRecoTMVA::FillHistMuon(TString cutname){
  FillHist(cutname+"/muon_P_jetrestf/"+ProcessName, p_jetrestf, weight, 200, 0., 10.);
  FillHist(cutname+"/muon_dRbmatj/"+ProcessName, dR_l_j, weight, 200, 0., 5.);
  FillHist(cutname+"/muon_ip3d/"+ProcessName, ip3d, weight, 100, -10., 10.);
  FillHist(cutname+"/muon_nsip3d/"+ProcessName, nsip3d, weight, 100, 0., 10.);
  FillHist(cutname+"/muon_logreliso/"+ProcessName, log10(reliso), weight, 100, -5., 2.);
  FillHist(cutname+"/muon_logreltrkiso/"+ProcessName, log10(reltrkiso), weight, 100, -5., 2.);
}

void BBbarRecoTMVA::FillHistMuonCharge(TString cutname){
  FillHist(cutname+"/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
  FillHist(cutname+"/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
  FillHist(cutname+"/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);


}

void BBbarRecoTMVA::RunLeptonCutStudyMuon(){
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
    FillHist(CutStudyEventTag+"_Muon/NotZmuonCut/"+ProcessName, 0, weight, 2, -1., 1.);
    FillHist(CutStudyEventTagJetParton+"_Muon/NotZmuonCut/"+ProcessName, 0, weight, 2, -1., 1.);
    if ( muon_charge > 0){
      FillHistMuon(CutStudyEventTag+"_MuonPlus");
      FillHistMuon(CutStudyEventTagJetParton+"_MuonPlus");
    }
    else{
      FillHistMuon(CutStudyEventTag+"_MuonMinus");
      FillHistMuon(CutStudyEventTagJetParton+"_MuonMinus");
    }
    
    if(p_jetrestf > 0.7){
      if(p_jetrestf < 3){
	if ( muon_charge > 0){
	  FillHistMuon(CutStudyEventTag+"_MuonPlus__Pjetrest__0p7_3");
	  FillHistMuon(CutStudyEventTagJetParton+"_MuonPlus__Pjetrest__0p7_3");
	}
	else{
	  FillHistMuon(CutStudyEventTag+"_MuonMinus__Pjetrest__0p7_3");
	  FillHistMuon(CutStudyEventTagJetParton+"_MuonMinus__Pjetrest__0p7_3");
	}
      }
    }


    if((dR_l_j<0.4) && (p_jetrestf>0.7) && (p_jetrestf<3)){
      v_tmva_bmuonidx.push_back(i);
      v_tmva_bmuon_p_jetrestf.push_back(p_jetrestf);
      if ( muon_charge > 0){
	FillHistMuon(CutStudyEventTag+"_MuonPlus__TMVA");
	FillHistMuon(CutStudyEventTagJetParton+"_MuonPlus__TMVA");
      }
      else{
	FillHistMuon(CutStudyEventTag+"_MuonMinus__TMVA");
	FillHistMuon(CutStudyEventTagJetParton+"_MuonMinus__TMVA");
      }
    }

    if(  (dR_l_j< MuonCut_apply.dR_l_bj_max) && (p_jetrestf > MuonCut_apply.P_JetRest_min) && (p_jetrestf < MuonCut_apply.P_JetRest_max) && (nsip3d < MuonCut_apply.nsip3d_max) ){
      if ( muon_charge > 0){
	FillHistMuon(CutStudyEventTag+"_MuonPlus__v1p0");
	FillHistMuon(CutStudyEventTagJetParton+"_MuonPlus__v1p0");
      }
      else{
	FillHistMuon(CutStudyEventTag+"_MuonMinus__v1p0");
	FillHistMuon(CutStudyEventTagJetParton+"_MuonMinus__v1p0");
      }
      v_bmuonidx.push_back(i);
    }
  }
 
  if(v_bmuonidx.size()>0){
    i_bmuon=v_bmuonidx[0];
    //--check only muon channel!
    FillHistMuonCharge(CutStudyEventTag+"__AtLeast1MuonInBmatjet__v1p0");
    FillHistMuonCharge(CutStudyEventTagJetParton+"__AtLeast1MuonInBmatjet__v1p0");

    if(v_bmuonidx.size()==1){
    FillHistMuonCharge(CutStudyEventTag+"__Only1MuonInBmatjet__v1p0");
    FillHistMuonCharge(CutStudyEventTagJetParton+"__Only1MuonInBmatjet__v1p0");
    }//[END] #muon==1
  }//[END] # muon >0
  if(v_tmva_bmuonidx.size()>0){
    i_bmuon=v_tmva_bmuonidx[0];
    //--check only muon channel!
    FillHistMuonCharge("TMVALepton__"+EventTag+"__AtLeast1MuonInBmatjet");
    FillHistMuonCharge("TMVALepton__"+EventTagJetParton+"__AtLeast1MuonInBmatjet");
    if(v_tmva_bmuonidx.size()==1){
      FillHistMuonCharge("TMVALepton__"+EventTag+"__Only1MuonInBmatjet");
      FillHistMuonCharge("TMVALepton__"+EventTagJetParton+"__Only1MuonInBmatjet");
      SetTreeValuesMuon(i_bmuon,-1,1);
    }//[END] #muon==1
    else{
      int idxIn100=Rank1n2Leptons(v_tmva_bmuonidx,v_tmva_bmuon_p_jetrestf);
      int i_bmuon1=idxIn100%100;
      int i_bmuon2=idxIn100/100;
      SetTreeValuesMuon(i_bmuon1,i_bmuon2,v_tmva_bmuonidx.size());
    }
  }

}
void BBbarRecoTMVA::SetTreeValuesMuon(int i_bmuon1,int i_bmuon2,int nbmuon){
  doFillTree=true;
  //--p jetrestf
  TLorentzVector vl(AllMuons[i_bmuon1]);
  vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
  p_jetrestf=vl.P();//                                                                                                          
  dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllMuons[i_bmuon1]);
  //ip3d=AllMuons[i_bmuon1].IP3D();
  nsip3d=fabs(AllMuons[i_bmuon1].IP3D()/AllMuons[i_bmuon1].IP3Derr());
  reliso=AllMuons[i_bmuon1].RelIso();
  reltrkiso=AllMuons[i_bmuon1].TrkIso()/AllMuons[i_bmuon1].Pt();
  //pt wrt bjet
  double ptwrtbjet=AllMuons[i_bmuon1].P()*sin(AllMuons[i_bmuon1].Angle(AllJets[myRECO.ij_B].Vect()));


  bmuon1_pt=min(AllMuons[i_bmuon1].Pt(),50.);
  bmuon1_eta=AllMuons[i_bmuon1].Eta();
  bmuon1_phi=AllMuons[i_bmuon1].Phi();
  bmuon1_ptwrtbjet=ptwrtbjet;
  bmuon1_p_jetrestf=p_jetrestf;
  bmuon1_dR_l_j=dR_l_j;
  
  bmuon1_nsip3d=min(nsip3d,5.);
  bmuon1_reltrkiso=min(reltrkiso,15.);
  bmuon1_reliso=min(reliso,15.);
  bmuon1_charge=AllMuons[i_bmuon1].Charge();
  bmuon1_charge_float=bmuon1_charge;
  if(i_bmuon2<0){
    bmuon2_pt=0.;
    bmuon2_eta=0.;
    bmuon2_phi=0.;
    bmuon2_ptwrtbjet=0.;
    bmuon2_p_jetrestf=0.;
    bmuon2_dR_l_j=0.;
    bmuon2_nsip3d=0.;
    bmuon2_reltrkiso=0.;
    bmuon2_reliso=0.;
    bmuon2_charge=0.;
    bmuon2_charge_float=0.;
  }
  else{
    //--p jetrestf
    TLorentzVector vl2(AllMuons[i_bmuon2]);
    vl2.Boost(-AllJets[myRECO.ij_B].BoostVector());
    p_jetrestf=vl2.P();//
    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllMuons[i_bmuon2]);
    //ip3d=AllMuons[i_bmuon2].IP3D();
    nsip3d=fabs(AllMuons[i_bmuon2].IP3D()/AllMuons[i_bmuon2].IP3Derr());
    reliso=AllMuons[i_bmuon2].RelIso();
    reltrkiso=AllMuons[i_bmuon2].TrkIso()/AllMuons[i_bmuon2].Pt();
    //pt wrt bjet
    ptwrtbjet=AllMuons[i_bmuon2].P()*sin(AllMuons[i_bmuon2].Angle(AllJets[myRECO.ij_B].Vect()));
   

    bmuon2_pt=min(AllMuons[i_bmuon2].Pt(),50.);
    bmuon2_eta=AllMuons[i_bmuon2].Eta();
    bmuon2_phi=AllMuons[i_bmuon2].Phi();
    bmuon2_ptwrtbjet=ptwrtbjet;
    bmuon2_p_jetrestf=p_jetrestf;
    bmuon2_dR_l_j=dR_l_j;
    bmuon2_nsip3d=min(nsip3d,5.);
    bmuon2_reltrkiso=min(reltrkiso,15.);
    bmuon2_reliso=min(reliso,15.);
    bmuon2_charge=AllMuons[i_bmuon2].Charge(); 
    bmuon2_charge_float=bmuon2_charge;
  }
  n_bmuon=nbmuon;
  n_bmuon_float=n_bmuon;
  //jet
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





void BBbarRecoTMVA::FillHistElectron(TString cutname){
  FillHist(cutname+"/electron_P_jetrestf/"+ProcessName, p_jetrestf, weight, 200, 0., 10.);
  FillHist(cutname+"/electron_dRbmatj/"+ProcessName, dR_l_j, weight, 200, 0., 5.);
  FillHist(cutname+"/electron_ip3d/"+ProcessName, ip3d, weight, 100, -10., 10.);
  FillHist(cutname+"/electron_nsip3d/"+ProcessName, nsip3d, weight, 100, 0., 10.);
  FillHist(cutname+"/electron_logreliso/"+ProcessName, log10(reliso), weight, 100, -5., 2.);
  FillHist(cutname+"/electron_logreltrkiso/"+ProcessName, log10(reltrkiso), weight, 100, -5., 2.);
  FillHist(cutname+"/electron_logrelecalclusteriso/"+ProcessName, log10(relecalclusteriso), weight, 100, -5., 2.);
  FillHist(cutname+"/electron_IsGsfCtfScPixChargeConsistent/"+ProcessName, IsGsfCtfScPixChargeConsistent, weight, 4, -1., 3.);//
}

void BBbarRecoTMVA::FillHistElectronCharge(TString cutname){
  FillHist(cutname+"/belectron_charge/"+ProcessName, AllElectrons[i_belectron].Charge(), weight, 4, -2., 2.);
  FillHist(cutname+"/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
  FillHist(cutname+"/belectron_bjet_chargesum/"+ProcessName, AllElectrons[i_belectron].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);


}

void BBbarRecoTMVA::RunLeptonCutStudyElectron(){
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
    FillHist(CutStudyEventTag+"_Electron/NotZelectronCut/"+ProcessName, 0, weight, 2, -1., 1.);
    FillHist(CutStudyEventTagJetParton+"_Electron/NotZelectronCut/"+ProcessName, 0, weight, 2, -1., 1.);
    if ( electron_charge > 0){
      FillHistElectron(CutStudyEventTag+"_ElectronPlus");
      FillHistElectron(CutStudyEventTagJetParton+"_ElectronPlus");
    }
    else{
      FillHistElectron(CutStudyEventTag+"_ElectronMinus");
      FillHistElectron(CutStudyEventTagJetParton+"_ElectronMinus");
    }
    
    if(p_jetrestf > 0.7){
      if(p_jetrestf < 3){
	if ( electron_charge > 0){
	  FillHistElectron(CutStudyEventTag+"_ElectronPlus__Pjetrest__0p7_3");
	  FillHistElectron(CutStudyEventTagJetParton+"_ElectronPlus__Pjetrest__0p7_3");
	}
	else{
	  FillHistElectron(CutStudyEventTag+"_ElectronMinus__Pjetrest__0p7_3");
	  FillHistElectron(CutStudyEventTagJetParton+"_ElectronMinus__Pjetrest__0p7_3");
	}
      }
    }


    //if(dR_l_j<0.4){
    if((dR_l_j<0.4) && (p_jetrestf>0.7) && (p_jetrestf<3) && (IsGsfCtfScPixChargeConsistent)){
      v_tmva_belectronidx.push_back(i);
      v_tmva_belectron_p_jetrestf.push_back(p_jetrestf);
      if ( electron_charge > 0){
	FillHistElectron(CutStudyEventTag+"_ElectronPlus__TMVA");
	FillHistElectron(CutStudyEventTagJetParton+"_ElectronPlus__TMVA");
      }
      else{
	FillHistElectron(CutStudyEventTag+"_ElectronMinus__TMVA");
	FillHistElectron(CutStudyEventTagJetParton+"_ElectronMinus__TMVA");
      }
    }

    if(  (dR_l_j<ElectronCut_apply.dR_l_bj_max) && (p_jetrestf > ElectronCut_apply.P_JetRest_min) && (p_jetrestf < ElectronCut_apply.P_JetRest_max) && (reltrkiso < ElectronCut_apply.reltrkiso_max) && (nsip3d < ElectronCut_apply.nsip3d_max) && (IsGsfCtfScPixChargeConsistent==ElectronCut_apply.bool_IsGsfCtfScPixChargeConsistent)){
      if ( electron_charge > 0){
	FillHistElectron(CutStudyEventTag+"_ElectronPlus__v1p0");
	FillHistElectron(CutStudyEventTagJetParton+"_ElectronPlus__v1p0");
      }
      else{
	FillHistElectron(CutStudyEventTag+"_ElectronMinus__v1p0");
	FillHistElectron(CutStudyEventTagJetParton+"_ElectronMinus__v1p0");
      }
      v_belectronidx.push_back(i);
    }
  }
 
  if(v_belectronidx.size()>0){
    i_belectron=v_belectronidx[0];
    //--check only electron channel!
    FillHistElectronCharge(CutStudyEventTag+"__AtLeast1ElectronInBmatjet__v1p0");
    FillHistElectronCharge(CutStudyEventTagJetParton+"__AtLeast1ElectronInBmatjet__v1p0");

    if(v_belectronidx.size()==1){
    FillHistElectronCharge(CutStudyEventTag+"__Only1ElectronInBmatjet__v1p0");
    FillHistElectronCharge(CutStudyEventTagJetParton+"__Only1ElectronInBmatjet__v1p0");
    }//[END] #electron==1
  }//[END] # electron >0
  if(v_tmva_belectronidx.size()>0){
    i_belectron=v_tmva_belectronidx[0];
    //--check only electron channel!
    FillHistElectronCharge("TMVALepton__"+EventTag+"__AtLeast1ElectronInBmatjet");
    FillHistElectronCharge("TMVALepton__"+EventTagJetParton+"__AtLeast1ElectronInBmatjet");
    if(v_tmva_belectronidx.size()==1){
      FillHistElectronCharge("TMVALepton__"+EventTag+"__Only1ElectronInBmatjet");
      FillHistElectronCharge("TMVALepton__"+EventTagJetParton+"__Only1ElectronInBmatjet");
      SetTreeValuesElectron(i_belectron,-1,1);
    }//[END] #electron==1
    else{
      int idxIn100=Rank1n2Leptons(v_tmva_belectronidx,v_tmva_belectron_p_jetrestf);
      int i_belectron1=idxIn100%100;
      int i_belectron2=idxIn100/100;
      SetTreeValuesElectron(i_belectron1,i_belectron2,v_tmva_belectronidx.size());
    }
  }//end of if tmva belectron


}



void BBbarRecoTMVA::SetTreeValuesElectron(int i_belectron1,int i_belectron2,int nbelectron){
  doFillTree=true;
  //--p jetrestf
  TLorentzVector vl(AllElectrons[i_belectron1]);
  vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
  p_jetrestf=vl.P();//                                                                                                          
  dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllElectrons[i_belectron1]);
  //ip3d=AllElectrons[i_belectron1].IP3D();
  nsip3d=fabs(AllElectrons[i_belectron1].IP3D()/AllElectrons[i_belectron1].IP3Derr());
  reliso=AllElectrons[i_belectron1].RelIso();
  reltrkiso=AllElectrons[i_belectron1].TrkIso()/AllElectrons[i_belectron1].Pt();
  //pt wrt bjet
  double ptwrtbjet=AllElectrons[i_belectron1].P()*sin(AllElectrons[i_belectron1].Angle(AllJets[myRECO.ij_B].Vect()));


  belectron1_pt=min(AllElectrons[i_belectron1].Pt(),50.);
  belectron1_eta=AllElectrons[i_belectron1].Eta();
  belectron1_phi=AllElectrons[i_belectron1].Phi();
  belectron1_ptwrtbjet=ptwrtbjet;
  belectron1_p_jetrestf=p_jetrestf;
  belectron1_dR_l_j=dR_l_j;
  belectron1_nsip3d=min(nsip3d,5.);
  belectron1_reltrkiso=min(reltrkiso,15.);
  belectron1_elecalclusteriso=min(AllElectrons[i_belectron1].ecalPFClusterIso()/AllElectrons[i_belectron1].Pt(),10.);
  belectron1_IsGsfCtfScPixChargeConsistent=AllElectrons[i_belectron1].IsGsfCtfScPixChargeConsistent();
  belectron1_IsGsfCtfScPixChargeConsistent_float=belectron1_IsGsfCtfScPixChargeConsistent;
  belectron1_reliso=min(reliso,15.);
  belectron1_charge=AllElectrons[i_belectron1].Charge();
  belectron1_charge_float=belectron1_charge;
  if(i_belectron2<0){
    belectron2_pt=0.;
    belectron2_eta=0.;
    belectron2_phi=0.;
    belectron2_ptwrtbjet=0.;
    belectron2_p_jetrestf=0.;
    belectron2_dR_l_j=0.;
    belectron2_nsip3d=0.;
    belectron2_reltrkiso=0.;
    belectron2_reliso=0.;
    belectron2_charge=0.;
    belectron2_elecalclusteriso=0.;
    belectron2_IsGsfCtfScPixChargeConsistent=0;
    belectron2_IsGsfCtfScPixChargeConsistent_float=0.;
  }
  else{
    //--p jetrestf
    TLorentzVector vl2(AllElectrons[i_belectron2]);
    vl2.Boost(-AllJets[myRECO.ij_B].BoostVector());
    p_jetrestf=vl2.P();//
    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllElectrons[i_belectron2]);
    //ip3d=AllElectrons[i_belectron2].IP3D();
    nsip3d=fabs(AllElectrons[i_belectron2].IP3D()/AllElectrons[i_belectron2].IP3Derr());
    reliso=AllElectrons[i_belectron2].RelIso();
    reltrkiso=AllElectrons[i_belectron2].TrkIso()/AllElectrons[i_belectron2].Pt();
    //pt wrt bjet
    ptwrtbjet=AllElectrons[i_belectron2].P()*sin(AllElectrons[i_belectron2].Angle(AllJets[myRECO.ij_B].Vect()));
   

    belectron2_pt=min(AllElectrons[i_belectron2].Pt(),50.);
    belectron2_eta=AllElectrons[i_belectron2].Eta();
    belectron2_phi=AllElectrons[i_belectron2].Phi();
    belectron2_ptwrtbjet=ptwrtbjet;
    belectron2_p_jetrestf=p_jetrestf;
    belectron2_dR_l_j=dR_l_j;
    belectron2_nsip3d=min(nsip3d,5.);
    belectron2_reltrkiso=min(reltrkiso,15.);
    belectron2_reliso=min(reliso,15.);
    belectron2_elecalclusteriso=min(AllElectrons[i_belectron2].ecalPFClusterIso()/AllElectrons[i_belectron2].Pt(),10.);
    belectron2_IsGsfCtfScPixChargeConsistent=AllElectrons[i_belectron2].IsGsfCtfScPixChargeConsistent();
    belectron2_IsGsfCtfScPixChargeConsistent_float=belectron2_IsGsfCtfScPixChargeConsistent;
    belectron2_charge=AllElectrons[i_belectron2].Charge(); 
    belectron2_charge_float=belectron2_charge;
  }
  n_belectron=nbelectron;
  n_belectron_float=n_belectron;
  //jet
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







void BBbarRecoTMVA::AnalyzeRECO(){

  //call muon/electron
  AllMuons=GetAllMuons();
  muonsize = AllMuons.size();
  AllElectrons=GetAllElectrons();
  electronsize = AllElectrons.size();
  
  //(0) Apply some basic cuts
  bool isGoodZ=BBbarRecoTMVA::ZTagCuts();
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
  //BBbarRecoTMVA::RunProtoTypeMuon();
  //BBbarRecoTMVA::RunProtoTypeElectron();
  BBbarRecoTMVA::RunLeptonCutStudyMuon();
  BBbarRecoTMVA::RunLeptonCutStudyElectron();
  

}

void BBbarRecoTMVA::executeEvent(){
  isEvenEvent=((event%2)==0);

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
  
  myLHE.is_gbToZb = BBbarRecoTMVA::Tag_gbToZb(); 
  if(!myLHE.is_gbToZb) return;
  if (!allow_tautau){
    if (myLHE.is_tautau) return;
  }
  FillHist("gbToZb/evt_nb_LHE/"+ProcessName,myLHE.evt_nb,weight, 4, -2., 2.);
  //->For LHE info, tag events with one gluon and one b(bbar)quark 
  // if b event : BBbarRecoTMVA::myLHE.evt_nb=1
  // if bbar event : BBbarRecoTMVA::myLHE.evt_nb=-1

  //(2)---Get the most energetic B-hadron info. in GEN
  BBbarRecoTMVA::Tag_B_Hadron();
  //->For GEN particles 
  //  -> Tag All B hadron and get the most energetic B-hadron info.
  
  //(3)---Check Jet matching to B-hadron
  BBbarRecoTMVA::Loop_genBMatchedRecoJet();


  //(4)---Now basic generator level info is set. do analysis//fill histograms
  BBbarRecoTMVA::AnalyzeLHE();
  BBbarRecoTMVA::AnalyzeGEN();
  if(!myRECO.HasBmatchedRecoJet) return; // if there's no bmatjet->return
  if(!(1==myRECO.nBmatJet)) return;
  BBbarRecoTMVA::AnalyzeRECO();
  //NowFillTree
  if(doFillTree){
    double DNN1_raw=myreader->EvaluateMVA("PyKeras::DNN");
    DNN1=(DNN1_raw>=0&& DNN1_raw<0.414289119617)*((0.1)/(0.414289119617-0)*(DNN1_raw-0)+-1.0)+(DNN1_raw>=0.414289119617&& DNN1_raw<0.439458691961)*((0.1)/(0.439458691961-0.414289119617)*(DNN1_raw-0.414289119617)+-0.9)+(DNN1_raw>=0.439458691961&& DNN1_raw<0.448793102896)*((0.1)/(0.448793102896-0.439458691961)*(DNN1_raw-0.439458691961)+-0.8)+(DNN1_raw>=0.448793102896&& DNN1_raw<0.460169416224)*((0.1)/(0.460169416224-0.448793102896)*(DNN1_raw-0.448793102896)+-0.7)+(DNN1_raw>=0.460169416224&& DNN1_raw<0.469462155682)*((0.1)/(0.469462155682-0.460169416224)*(DNN1_raw-0.460169416224)+-0.6)+(DNN1_raw>=0.469462155682&& DNN1_raw<0.479921696507)*((0.1)/(0.479921696507-0.469462155682)*(DNN1_raw-0.469462155682)+-0.5)+(DNN1_raw>=0.479921696507&& DNN1_raw<0.486047403683)*((0.1)/(0.486047403683-0.479921696507)*(DNN1_raw-0.479921696507)+-0.4)+(DNN1_raw>=0.486047403683&& DNN1_raw<0.492673168588)*((0.1)/(0.492673168588-0.486047403683)*(DNN1_raw-0.486047403683)+-0.3)+(DNN1_raw>=0.492673168588&& DNN1_raw<0.496215244166)*((0.1)/(0.496215244166-0.492673168588)*(DNN1_raw-0.492673168588)+-0.2)+(DNN1_raw>=0.496215244166&& DNN1_raw<0.502132593956)*((0.1)/(0.502132593956-0.496215244166)*(DNN1_raw-0.496215244166)+-0.1)+(DNN1_raw>=0.502132593956&& DNN1_raw<0.508049943745)*((0.1)/(0.508049943745-0.502132593956)*(DNN1_raw-0.502132593956)+0)+(DNN1_raw>=0.508049943745&& DNN1_raw<0.511383661936)*((0.1)/(0.511383661936-0.508049943745)*(DNN1_raw-0.508049943745)+0.1)+(DNN1_raw>=0.511383661936&& DNN1_raw<0.517926083887)*((0.1)/(0.517926083887-0.511383661936)*(DNN1_raw-0.511383661936)+0.2)+(DNN1_raw>=0.517926083887&& DNN1_raw<0.524510177314)*((0.1)/(0.524510177314-0.517926083887)*(DNN1_raw-0.517926083887)+0.3)+(DNN1_raw>=0.524510177314&& DNN1_raw<0.536469891325)*((0.1)/(0.536469891325-0.524510177314)*(DNN1_raw-0.524510177314)+0.4)+(DNN1_raw>=0.536469891325&& DNN1_raw<0.547137789537)*((0.1)/(0.547137789537-0.536469891325)*(DNN1_raw-0.536469891325)+0.5)+(DNN1_raw>=0.547137789537&& DNN1_raw<0.558972489116)*((0.1)/(0.558972489116-0.547137789537)*(DNN1_raw-0.547137789537)+0.6)+(DNN1_raw>=0.558972489116&& DNN1_raw<0.570098773579)*((0.1)/(0.570098773579-0.558972489116)*(DNN1_raw-0.558972489116)+0.7)+(DNN1_raw>=0.570098773579&& DNN1_raw<0.599643851049)*((0.1)/(0.599643851049-0.570098773579)*(DNN1_raw-0.570098773579)+0.8)+(DNN1_raw>=0.599643851049&& DNN1_raw<1)*((0.1)/(1-0.599643851049)*(DNN1_raw-0.599643851049)+0.9);

    FillHist("DNN/DNN1",DNN1,weight,100,-1.2,1.2);
    FillHist("DNN/DNN1_raw",DNN1_raw,weight,100,0.,1.);

    double DNN2_raw=myreader2->EvaluateMVA("PyKeras::DNN");
    DNN2=((DNN2_raw>=0&& DNN2_raw<0.440702643171)*((0.1)/(0.440702643171-0)*(DNN2_raw-0)+-1.0)+(DNN2_raw>=0.440702643171&& DNN2_raw<0.451453571147)*((0.1)/(0.451453571147-0.440702643171)*(DNN2_raw-0.440702643171)+-0.9)+(DNN2_raw>=0.451453571147&& DNN2_raw<0.454519425133)*((0.1)/(0.454519425133-0.451453571147)*(DNN2_raw-0.451453571147)+-0.8)+(DNN2_raw>=0.454519425133&& DNN2_raw<0.457912303543)*((0.1)/(0.457912303543-0.454519425133)*(DNN2_raw-0.454519425133)+-0.7)+(DNN2_raw>=0.457912303543&& DNN2_raw<0.460651133104)*((0.1)/(0.460651133104-0.457912303543)*(DNN2_raw-0.457912303543)+-0.6)+(DNN2_raw>=0.460651133104&& DNN2_raw<0.463757865143)*((0.1)/(0.463757865143-0.460651133104)*(DNN2_raw-0.460651133104)+-0.5)+(DNN2_raw>=0.463757865143&& DNN2_raw<0.465311231162)*((0.1)/(0.465311231162-0.463757865143)*(DNN2_raw-0.463757865143)+-0.4)+(DNN2_raw>=0.465311231162&& DNN2_raw<0.466987231341)*((0.1)/(0.466987231341-0.465311231162)*(DNN2_raw-0.465311231162)+-0.3)+(DNN2_raw>=0.466987231341&& DNN2_raw<0.467723036297)*((0.1)/(0.467723036297-0.466987231341)*(DNN2_raw-0.466987231341)+-0.2)+(DNN2_raw>=0.467723036297&& DNN2_raw<0.470298353645)*((0.1)/(0.470298353645-0.467723036297)*(DNN2_raw-0.467723036297)+-0.1)+(DNN2_raw>=0.470298353645&& DNN2_raw<0.472873670993)*((0.1)/(0.472873670993-0.470298353645)*(DNN2_raw-0.470298353645)+0)+(DNN2_raw>=0.472873670993&& DNN2_raw<0.474059134534)*((0.1)/(0.474059134534-0.472873670993)*(DNN2_raw-0.472873670993)+0.1)+(DNN2_raw>=0.474059134534&& DNN2_raw<0.476593573829)*((0.1)/(0.476593573829-0.474059134534)*(DNN2_raw-0.474059134534)+0.2)+(DNN2_raw>=0.476593573829&& DNN2_raw<0.478923622858)*((0.1)/(0.478923622858-0.476593573829)*(DNN2_raw-0.476593573829)+0.3)+(DNN2_raw>=0.478923622858&& DNN2_raw<0.48350196481)*((0.1)/(0.48350196481-0.478923622858)*(DNN2_raw-0.478923622858)+0.4)+(DNN2_raw>=0.48350196481&& DNN2_raw<0.488121184815)*((0.1)/(0.488121184815-0.48350196481)*(DNN2_raw-0.48350196481)+0.5)+(DNN2_raw>=0.488121184815&& DNN2_raw<0.494334648893)*((0.1)/(0.494334648893-0.488121184815)*(DNN2_raw-0.488121184815)+0.6)+(DNN2_raw>=0.494334648893&& DNN2_raw<0.500875137395)*((0.1)/(0.500875137395-0.494334648893)*(DNN2_raw-0.494334648893)+0.7)+(DNN2_raw>=0.500875137395&& DNN2_raw<0.536439043628)*((0.1)/(0.536439043628-0.500875137395)*(DNN2_raw-0.500875137395)+0.8)+(DNN2_raw>=0.536439043628&& DNN2_raw<1)*((0.1)/(1-0.536439043628)*(DNN2_raw-0.536439043628)+0.9));


    FillHist("DNN/DNN2",DNN2,weight,100,-1.2,1.2);
    FillHist("DNN/DNN2_raw",DNN2_raw,weight,100,0.,1.);
    //cout<<"myLHE.evt_nb="<<myLHE.evt_nb<<endl;
    //cout<<"AllJets[myRECO.ij_B].partonFlavour()="<<AllJets[myRECO.ij_B].partonFlavour()<<endl;
    //cout << "bjetPartonFlavourCharge=" << bjetPartonFlavourCharge <<endl;
    if(bjetPartonFlavourCharge<0){//bevt
      if(event%2==0){
	DNN_Final=DNN2;
	jhchoi_newtree->Fill();
	FillHist("DNN/neg_event/DNN2_raw",DNN2_raw,weight,100,0,1);
	FillHist("DNN/neg_event/DNN2",DNN2,weight,100,-1.2,1.2);
	FillHist("DNN/neg_event/DNN_final",DNN2,weight,100,-1.2,1.2);
	FillHist("DNN/all_event/DNN_final",DNN2,weight,100,-1.2,1.2);

      }
      else{
	DNN_Final=DNN1;
	jhchoi_newtree3->Fill();
	FillHist("DNN/neg_event/DNN1_raw",DNN1_raw,weight,100,0,1);
	FillHist("DNN/neg_event/DNN1",DNN1,weight,100,-1.2,1.2);
	FillHist("DNN/neg_event/DNN_final",DNN1,weight,100,-1.2,1.2);
	FillHist("DNN/all_event/DNN_final",DNN1,weight,100,-1.2,1.2);
      }
    }
    else if (bjetPartonFlavourCharge>0){//bbar
      if(event%2==0){
	DNN_Final=DNN2;
	jhchoi_newtree2->Fill();
	FillHist("DNN/pos_event/DNN2_raw",DNN2_raw,weight,100,0.,1.);
	FillHist("DNN/pos_event/DNN2",DNN2,weight,100,-1.2,1.2);
	FillHist("DNN/pos_event/DNN_final",DNN2,weight,100,-1.2,1.2);
	FillHist("DNN/all_event/DNN_final",DNN2,weight,100,-1.2,1.2);
      }
      else{
	DNN_Final=DNN1;
	jhchoi_newtree4->Fill();
	FillHist("DNN/pos_event/DNN1_raw",DNN1_raw,weight,100,0.,1.);
	FillHist("DNN/pos_event/DNN1",DNN1,weight,100,-1.2,1.2);
	FillHist("DNN/pos_event/DNN_final",DNN1,weight,100,-1.2,1.2);
	FillHist("DNN/all_event/DNN_final",DNN1,weight,100,-1.2,1.2);
      }
    }
  }

  
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
