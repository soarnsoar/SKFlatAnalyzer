#include "EEMu_MuMuE_Method.h"
#include <map>
EEMu_MuMuE_Method::EEMu_MuMuE_Method(){
  //runSys=true;

  //JHAnalyzerBase::SetupDiLeptonChannel();  
}

EEMu_MuMuE_Method::~EEMu_MuMuE_Method(){
  //==== Destructor of this Analyzer
}

void EEMu_MuMuE_Method::initializeAnalyzer(){


  MuonID="NOCUT";
  //MuonID="POGLoose";
  MuonMinPt=5;
  DeltaR_Mu=0.1;
  
  //ElectronID="passVetoID";
  ElectronID="NOCUT";
  //ElectronID="passVetoIDnoIso";
  ElectronMinPt=5;
  DeltaR_E=0.1;



    

  is_cut_v2405_1=false;
  if(HasFlag("cut_v2405.1")){
    is_cut_v2405_1=true;
  }


  is_cut_v2405_2=false;
  if(HasFlag("cut_v2405.2")){
    is_cut_v2405_2=true;
  }

  is_cut_v2405_3=false;
  if(HasFlag("cut_v2405.3")){
    is_cut_v2405_3=true;
    //rm ptcut and add id bits
    MuonMinPt=0.;//no ptcut
  }

  is_cut_v2503_1=false;
  if(HasFlag("cut_v2503.1")){
    is_cut_v2503_1=true;
    //rm ptcut and add id bits
    MuonMinPt=5.;//no ptcut
  }
  
  is_cut_v2503_2=false;
  if(HasFlag("cut_v2503.2")){
    is_cut_v2503_2=true;
    //rm ptcut and add id bits
    MuonMinPt=5.;//no ptcut
  }

  is_cut_v2608_1=false;
  if(HasFlag("cut_v2608.1")){
    is_cut_v2608_1=true;


  }

  
  isTreeMode=false;
  if(HasFlag("treemode")){
    isTreeMode=true;
  }
  if(isTreeMode && !is_cut_v2405_1 && !is_cut_v2405_2 && !is_cut_v2405_3 && !is_cut_v2503_1 && !is_cut_v2503_2 && !is_cut_v2608_1){
    cout << "!!!![EEMu_MuMuE_Method::initializeAnalyzer] In basic setup, treemode is not allowed!!!! EXIT!!!" << endl;
    exit(1);
  }

  cout << "[EEMu_MuMuE_Method::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  if(isTreeMode){
    jhchoi_newtree=new TTree("sig","sig");
    jhchoi_newtree2=new TTree("bkg","bkg");
    SetBranches(jhchoi_newtree);
    SetBranches(jhchoi_newtree2);
  }
}

void EEMu_MuMuE_Method::SetBranches(TTree *this_Tree){
  this_Tree->Branch("bmuon_P_jetrest",&bmuon.P_jetrest);
  this_Tree->Branch("bmuon_ptwrtbjet",&bmuon.ptwrtjet);
  this_Tree->Branch("bmuon_dR_l_j",&bmuon.dR_l_j);
  this_Tree->Branch("bmuon_nsip3d",&bmuon.nsip3d);
  this_Tree->Branch("bmuon_reltrkiso",&bmuon.reltrkiso);
  this_Tree->Branch("bmuon_reliso",&bmuon.reliso);
  this_Tree->Branch("bmuon_charge",&bmuon.charge);
  this_Tree->Branch("bmuon_palongjet",&bmuon.palongjet);
  this_Tree->Branch("bmuon_palongjetratio",&bmuon.palongjetratio);
  this_Tree->Branch("bmuon_pt",&bmuon.pt);
  this_Tree->Branch("bmuon_aeta",&bmuon.aeta);
  this_Tree->Branch("bmuon_normchi2",&bmuon.normchi2);
  this_Tree->Branch("bmuon_ntracklayers",&bmuon.ntracklayers);
  this_Tree->Branch("bmuon_ntrackhits",&bmuon.ntrackhits);
  this_Tree->Branch("bmuon_nvalidmuonhits",&bmuon.nvalidmuonhits);
  this_Tree->Branch("bmuon_nmatchedstations",&bmuon.nmatchedstations);
  //ID
  this_Tree->Branch("bmuon_isGlobalMuon",&bmuon.isGlobalMuon);
  this_Tree->Branch("bmuon_isTrackerMuon",&bmuon.isTrackerMuon);
  this_Tree->Branch("bmuon_isStandAloneMuon",&bmuon.isStandAloneMuon);
  this_Tree->Branch("bmuon_isCaloMuon",&bmuon.isCaloMuon);
  this_Tree->Branch("bmuon_isPFMuon",&bmuon.isPFMuon);
  this_Tree->Branch("bmuon_isRPCMuon",&bmuon.isRPCMuon);
  this_Tree->Branch("bmuon_isGEMMuon",&bmuon.isGEMMuon);
  this_Tree->Branch("bmuon_isME0Muon",&bmuon.isME0Muon);



  this_Tree->Branch("belectron_P_jetrest",&belectron.P_jetrest);
  this_Tree->Branch("belectron_ptwrtbjet",&belectron.ptwrtjet);
  this_Tree->Branch("belectron_dR_l_j",&belectron.dR_l_j);
  this_Tree->Branch("belectron_nsip3d",&belectron.nsip3d);
  this_Tree->Branch("belectron_reltrkiso",&belectron.reltrkiso);
  this_Tree->Branch("belectron_reliso",&belectron.reliso);
  this_Tree->Branch("belectron_charge",&belectron.charge);
  this_Tree->Branch("belectron_relecalPFClusterIso",&belectron.relecalPFClusterIso);
  this_Tree->Branch("belectron_IsGsfCtfScPixChargeConsistent",&belectron.IsGsfCtfScPixChargeConsistent);
  this_Tree->Branch("belectron_palongjet",&belectron.palongjet);
  this_Tree->Branch("belectron_palongjetratio",&belectron.palongjetratio);
  this_Tree->Branch("belectron_pt",&belectron.pt);
  this_Tree->Branch("belectron_aeta",&belectron.aeta);
  this_Tree->Branch("belectron_full5x5sigmaietaieta",&belectron.full5x5sigmaietaieta);
  this_Tree->Branch("belectron_detaseed",&belectron.detaseed);
  this_Tree->Branch("belectron_HoverE",&belectron.HoverE);
  this_Tree->Branch("belectron_InvEminusInvP",&belectron.InvEminusInvP);
  this_Tree->Branch("belectron_nmissinghits",&belectron.nmissinghits);


  this_Tree->Branch("bjet_pt",&bjet.pt);
  this_Tree->Branch("bjet_aeta",&bjet.aeta);
  this_Tree->Branch("bjet_ChargedHadronEnergyFraction",&bjet.ChargedHadronEnergyFraction);
  this_Tree->Branch("bjet_NeutralHadronEnergyFraction",&bjet.NeutralHadronEnergyFraction);
  this_Tree->Branch("bjet_NeutralEmEnergyFraction",&bjet.NeutralEmEnergyFraction);
  this_Tree->Branch("bjet_ChargedEmEnergyFraction",&bjet.ChargedEmEnergyFraction);
  this_Tree->Branch("bjet_MuonEnergyFraction",&bjet.MuonEnergyFraction);
  this_Tree->Branch("bjet_charge",&bjet.charge);
  this_Tree->Branch("bjet_partonFlavour",&bjet.partonFlavour);
  this_Tree->Branch("bjet_ChargedMultiplicity",&bjet.ChargedMultiplicity);
  this_Tree->Branch("bjet_NeutralMultiplicity",&bjet.NeutralMultiplicity);

  this_Tree->Branch("lhe_b_pdgid",&pid_b);
  this_Tree->Branch("lhe_bcharge",&bcharge);
  this_Tree->Branch("Has_bMuon",&Has_bMuon);
  this_Tree->Branch("Has_bElectron",&Has_bElectron);
  this_Tree->Branch("nbelectron",&nbelectron);
  this_Tree->Branch("nbmuon",&nbmuon);
  this_Tree->Branch("weight",&weight);

}

void EEMu_MuMuE_Method::TruthLoop(){
  //---
  IsMuMu=0; IsEE=0;
  bcharge=0;
  nb=0;
  nbbar=0;
  idx_lhe_mu1=-1; idx_lhe_mu2=-1;//mu1=mu- , mu2=mu+
  idx_lhe_e1=-1; idx_lhe_e2=-1; //e1=e- , e2=e+
  idx_lhe_b=-1;
  pid_b=0;
  unsigned int nmuon=0;
  unsigned int nelectron=0;
  unsigned int ntau=0;
  unsigned int lhesize=lhes.size();
  for(unsigned int i = 0 ; i < lhesize; i++){
    int status=lhes[i].Status();
    int pid=lhes[i].ID();
    if(status==-1) continue;
    if(abs(pid)==15){//tau
      ntau+=1;
    }
    else if(abs(pid)==13){//muon
      nmuon+=1;
      if(pid>0){
	idx_lhe_mu1=i;
      }else{
	idx_lhe_mu2=i;
      }
    }else if(abs(pid)==11){//electron
      nelectron+=1;
      if(pid>0){
	idx_lhe_e1=i;	
      }
      else{
	idx_lhe_e2=i;
      }
    }//end if electron

    if(pid==5){
      nb+=1;
      idx_lhe_b=i;
      pid_b=5;
    }
    if(pid==-5){
      nbbar+=1;
      idx_lhe_b=i;
      pid_b=-5;
    }

  }



  if(ntau==2){
    IsMuMu=0; IsEE=0;
    idx_lhe_mu1=-1; idx_lhe_mu2=-1;
    idx_lhe_e1=-1; idx_lhe_e2=-1;
    return;
  }
  else if(nmuon==2){
    IsMuMu=1;
    ll_str="MuMu";
    return;
  }
  else if(nelectron==2){
    IsEE=1;
    ll_str="EE";
    return;
  }
  


}

void EEMu_MuMuE_Method::EventLoop(){
  weight=MCweight()*ev.GetTriggerLumi("Full");
  if(nb+nbbar!=1) return;

  if(nb==1){
    bcharge = -1.;
    bcharge_str="bMinus";
  }
  if(nbbar==1){
    bcharge = 1.;
    bcharge_str="bPlus";
  }

  //(0) apply minpt and ID//  std::vector<Muon> GetMuons(TString id, double ptmin, double fetamax);
  AllMuons=GetMuons(MuonID,MuonMinPt,2.4);
  AllElectrons=GetElectrons(ElectronID,ElectronMinPt,2.5);
  if(!FindBJet()) return;
  FillHistBJet(bcharge_str,AllJets[jetidx_b]);
  nbelectron=0; nbmuon=0;
  RunElectronInJet();
  RunMuonInJet();
  
  if(nbmuon==1 && nbelectron==0) FillTree_1bmuon();
  if(nbmuon==0 && nbelectron==1) FillTree_1belectron();
  if(nbmuon==0 && nbelectron==0) FillTree_0blepton();
}



void EEMu_MuMuE_Method::FillTree_1bmuon(){
  Has_bMuon=true;
  Has_bElectron=false;
  bmuon=Get_bmuonvar(current_bmuon,AllJets[jetidx_b]);
  //cout << "bmuon.pt=" << bmuon.pt << endl;
  belectron=Get_init_belectronvar();
  bjet=Get_bjetvar(AllJets[jetidx_b]);
  bool isSig=false;
  bool isBkg=false;

  if(bmuon.charge*bcharge > 0) isSig=true;
  if(bmuon.charge*bcharge < 0) isBkg=true;

  if(isSig){
    jhchoi_newtree->Fill();
    if(IsEE)FillHist_1bmuon("Sig");
  }else if(isBkg){
    jhchoi_newtree2->Fill();
    if(IsEE)FillHist_1bmuon("Bkg");
  }
}
void EEMu_MuMuE_Method::FillHist_1bmuon(TString SigORBkg){
/*
  this_Tree->Branch("bmuon_P_jetrest",&bmuon.P_jetrest);
  this_Tree->Branch("bmuon_ptwrtbjet",&bmuon.ptwrtjet);
  this_Tree->Branch("bmuon_dR_l_j",&bmuon.dR_l_j);
  this_Tree->Branch("bmuon_nsip3d",&bmuon.nsip3d);
  this_Tree->Branch("bmuon_reltrkiso",&bmuon.reltrkiso);
  this_Tree->Branch("bmuon_reliso",&bmuon.reliso);
  this_Tree->Branch("bmuon_charge",&bmuon.charge);
  this_Tree->Branch("bmuon_palongjet",&bmuon.palongjet);
  this_Tree->Branch("bmuon_palongjetratio",&bmuon.palongjetratio);
  this_Tree->Branch("bmuon_pt",&bmuon.pt);
  this_Tree->Branch("bmuon_aeta",&bmuon.aeta);
  this_Tree->Branch("bmuon_normchi2",&bmuon.normchi2);
  this_Tree->Branch("bmuon_ntracklayers",&bmuon.ntracklayers);
  this_Tree->Branch("bmuon_ntrackhits",&bmuon.ntrackhits);
  this_Tree->Branch("bmuon_nvalidmuonhits",&bmuon.nvalidmuonhits);
  this_Tree->Branch("bmuon_nmatchedstations",&bmuon.nmatchedstations);
  //ID
  this_Tree->Branch("bmuon_isGlobalMuon",&bmuon.isGlobalMuon);
  this_Tree->Branch("bmuon_isTrackerMuon",&bmuon.isTrackerMuon);
  this_Tree->Branch("bmuon_isStandAloneMuon",&bmuon.isStandAloneMuon);
  this_Tree->Branch("bmuon_isCaloMuon",&bmuon.isCaloMuon);
  this_Tree->Branch("bmuon_isPFMuon",&bmuon.isPFMuon);
  this_Tree->Branch("bmuon_isRPCMuon",&bmuon.isRPCMuon);
  this_Tree->Branch("bmuon_isGEMMuon",&bmuon.isGEMMuon);
  this_Tree->Branch("bmuon_isME0Muon",&bmuon.isME0Muon);

 */
  FillHist(SigORBkg+"_1bmuon/muon_p_jetrestframe",bmuon.P_jetrest,weight,100,0,10);
  FillHist(SigORBkg+"_1bmuon/muon_ptwrtjet",bmuon.ptwrtjet,weight,100,0,10);
  FillHist(SigORBkg+"_1bmuon/muon_palongjet",bmuon.palongjet,weight,100,0,50);
  FillHist(SigORBkg+"_1bmuon/muon_palongjet_Over_Pjet",bmuon.palongjetratio,weight,100,0,1);
  FillHist(SigORBkg+"_1bmuon/muon_dR_j",bmuon.dR_l_j,weight,100,0,1);
  FillHist(SigORBkg+"_1bmuon/muon_reliso",bmuon.reliso,weight,100,0,10);
  FillHist(SigORBkg+"_1bmuon/muon_log_1_reliso",log10(1+bmuon.reliso),weight,100,0,2);
  FillHist(SigORBkg+"_1bmuon/muon_reltrkiso",bmuon.reltrkiso,weight,100,0,10);
  FillHist(SigORBkg+"_1bmuon/muon_log_1_reltrkiso",log10(1+bmuon.reltrkiso),weight,100,0,2);
  FillHist(SigORBkg+"_1bmuon/muon_nsip3d",fabs(bmuon.nsip3d),weight,100,0,10);


  //To Check ID                                                                                                                                                                                                                               
  FillHist(SigORBkg+"_1bmuon/muon_NormChi2",bmuon.normchi2,weight,40,0,20);
  FillHist(SigORBkg+"_1bmuon/muon_TrackerLayers",bmuon.ntracklayers,weight,20,0,20);
  FillHist(SigORBkg+"_1bmuon/muon_TrackerHits",bmuon.ntrackhits,weight,35,0,35);
  FillHist(SigORBkg+"_1bmuon/muon_ValidMuonHits",bmuon.nvalidmuonhits,weight,60,0,60);
  FillHist(SigORBkg+"_1bmuon/muon_MatchedStations",bmuon.nmatchedstations,weight,6,0,6);

  FillHist(SigORBkg+"_1bmuon/muon_isGlobalMuon",bmuon.isGlobalMuon,weight,2,0,2);
  FillHist(SigORBkg+"_1bmuon/muon_isTrackerMuon",bmuon.isTrackerMuon,weight,2,0,2);

  FillHist(SigORBkg+"_1bmuon/muon_isGlobalMuon_OR_isTrackerMuon",bmuon.isGlobalMuon||bmuon.isTrackerMuon,weight,2,0,2);
  FillHist(SigORBkg+"_1bmuon/muon_isGlobalMuon_OR_isTrackerMuon_OR_isStandAloneMuon",bmuon.isGlobalMuon||bmuon.isTrackerMuon||bmuon.isStandAloneMuon,weight,2,0,2);
  
  FillHist(SigORBkg+"_1bmuon/muon_isStandAloneMuon",bmuon.isStandAloneMuon,weight,2,0,2);
  FillHist(SigORBkg+"_1bmuon/muon_isCaloMuon",bmuon.isCaloMuon,weight,2,0,2);
  FillHist(SigORBkg+"_1bmuon/muon_isRPCMuon",bmuon.isRPCMuon,weight,2,0,2);
  FillHist(SigORBkg+"_1bmuon/muon_isGEMMuon",bmuon.isGEMMuon,weight,2,0,2);
  FillHist(SigORBkg+"_1bmuon/muon_isME0Muon",bmuon.isME0Muon,weight,2,0,2);
    
    /*
  this_Tree->Branch("bjet_pt",&bjet.pt);
  this_Tree->Branch("bjet_aeta",&bjet.aeta);
  this_Tree->Branch("bjet_ChargedHadronEnergyFraction",&bjet.ChargedHadronEnergyFraction);
  this_Tree->Branch("bjet_NeutralHadronEnergyFraction",&bjet.NeutralHadronEnergyFraction);
  this_Tree->Branch("bjet_NeutralEmEnergyFraction",&bjet.NeutralEmEnergyFraction);
  this_Tree->Branch("bjet_ChargedEmEnergyFraction",&bjet.ChargedEmEnergyFraction);
  this_Tree->Branch("bjet_MuonEnergyFraction",&bjet.MuonEnergyFraction);
  this_Tree->Branch("bjet_charge",&bjet.charge);
  this_Tree->Branch("bjet_partonFlavour",&bjet.partonFlavour);
  this_Tree->Branch("bjet_ChargedMultiplicity",&bjet.ChargedMultiplicity);
  this_Tree->Branch("bjet_NeutralMultiplicity",&bjet.NeutralMultiplicity);

   */
  FillHist(SigORBkg+"_1bmuon/bjet_ChargedHadronEnergyFraction",bjet.ChargedHadronEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1bmuon/bjet_logChargedHadronEnergyFraction",log10(bjet.ChargedHadronEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_1bmuon/bjet_NeutralHadronEnergyFraction",bjet.NeutralHadronEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1bmuon/bjet_log_NeutralHadronEnergyFraction",log10(bjet.NeutralHadronEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_1bmuon/bjet_NeutralEmEnergyFraction",bjet.NeutralEmEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1bmuon/bjet_logNeutralEmEnergyFraction",log10(bjet.NeutralEmEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_1bmuon/bjet_ChargedEmEnergyFraction",bjet.ChargedEmEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1bmuon/bjet_logChargedEmEnergyFraction",log10(bjet.ChargedEmEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_1bmuon/bjet_MuonEnergyFraction",bjet.MuonEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1bmuon/bjet_logMuonEnergyFraction",log10(bjet.MuonEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_1bmuon/bjet_charge",bjet.charge,weight,50,-1,1);
  FillHist(SigORBkg+"_1bmuon/bjet_charge_dot_muon_charge",bjet.charge*bmuon.charge,weight,50,-1,1);
  FillHist(SigORBkg+"_1bmuon/fabs(bjet_charge)",fabs(bjet.charge),weight,50,0,1);
  
  FillHist(SigORBkg+"_1bmuon/bjet_partonFlavour",bjet.partonFlavour,weight,27,-6,21);

  FillHist(SigORBkg+"_1bmuon/bjet_ChargedMultiplicity",bjet.ChargedMultiplicity,weight,60,0,60);
  FillHist(SigORBkg+"_1bmuon/bjet_NeutralMultiplicity",bjet.NeutralMultiplicity,weight,60,0,60);

  
}
void EEMu_MuMuE_Method::FillTree_1belectron(){
  Has_bMuon=false;
  Has_bElectron=true;
  belectron=Get_belectronvar(current_belectron,AllJets[jetidx_b]);
  bmuon=Get_init_bmuonvar();
  bjet=Get_bjetvar(AllJets[jetidx_b]);

  bool isSig=false;
  bool isBkg=false;
  if(belectron.charge*bcharge > 0) isSig=true;
  if(belectron.charge*bcharge < 0) isBkg=true;
  if(isSig){
    jhchoi_newtree->Fill();
    if(IsMuMu)FillHist_1belectron("Sig");
  }else if(isBkg){
    jhchoi_newtree2->Fill();
    if(IsMuMu)FillHist_1belectron("Bkg");
  }
}
void EEMu_MuMuE_Method::FillHist_1belectron(TString SigORBkg){
  /*
  this_Tree->Branch("belectron_P_jetrest",&belectron.P_jetrest);
  this_Tree->Branch("belectron_ptwrtbjet",&belectron.ptwrtjet);
  this_Tree->Branch("belectron_dR_l_j",&belectron.dR_l_j);
  this_Tree->Branch("belectron_nsip3d",&belectron.nsip3d);
  this_Tree->Branch("belectron_reltrkiso",&belectron.reltrkiso);
  this_Tree->Branch("belectron_reliso",&belectron.reliso);
  this_Tree->Branch("belectron_charge",&belectron.charge);
  this_Tree->Branch("belectron_relecalPFClusterIso",&belectron.relecalPFClusterIso);
  this_Tree->Branch("belectron_IsGsfCtfScPixChargeConsistent",&belectron.IsGsfCtfScPixChargeConsistent);
  this_Tree->Branch("belectron_palongjet",&belectron.palongjet);
  this_Tree->Branch("belectron_palongjetratio",&belectron.palongjetratio);
  this_Tree->Branch("belectron_pt",&belectron.pt);
  this_Tree->Branch("belectron_aeta",&belectron.aeta);
  this_Tree->Branch("belectron_full5x5sigmaietaieta",&belectron.full5x5sigmaietaieta);
  this_Tree->Branch("belectron_detaseed",&belectron.detaseed);
  this_Tree->Branch("belectron_HoverE",&belectron.HoverE);
  this_Tree->Branch("belectron_InvEminusInvP",&belectron.InvEminusInvP);
  this_Tree->Branch("belectron_nmissinghits",&belectron.nmissinghits);

   */
  FillHist(SigORBkg+"_1belectron/electron_p_jetrestframe",belectron.P_jetrest,weight,100,0,10);
  FillHist(SigORBkg+"_1belectron/electron_ptwrtjet",belectron.ptwrtjet,weight,100,0,10);
  FillHist(SigORBkg+"_1belectron/electron_palongjet",belectron.palongjet,weight,100,0,50);
  FillHist(SigORBkg+"_1belectron/electron_palongjet_Over_Pjet",belectron.palongjetratio,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/electron_dR_j",belectron.dR_l_j,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/electron_reliso",belectron.reliso,weight,100,0,10);
  FillHist(SigORBkg+"_1belectron/electron_log_1_reliso",log10(1+belectron.reliso),weight,100,0,2);
  FillHist(SigORBkg+"_1belectron/electron_reltrkiso",belectron.reltrkiso,weight,100,0,10);
  FillHist(SigORBkg+"_1belectron/electron_log_1_reltrkiso",log10(1+belectron.reltrkiso),weight,100,0,2);

  FillHist(SigORBkg+"_1belectron/electron_nsip3d",fabs(belectron.nsip3d),weight,100,0,10);

  FillHist(SigORBkg+"_1belectron/bjet_ChargedHadronEnergyFraction",bjet.ChargedHadronEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/bjet_logChargedHadronEnergyFraction",log10(bjet.ChargedHadronEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_1belectron/bjet_NeutralHadronEnergyFraction",bjet.NeutralHadronEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/bjet_log_NeutralHadronEnergyFraction",log10(bjet.NeutralHadronEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_1belectron/bjet_NeutralEmEnergyFraction",bjet.NeutralEmEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/bjet_logNeutralEmEnergyFraction",log10(bjet.NeutralEmEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_1belectron/bjet_ChargedEmEnergyFraction",bjet.ChargedEmEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/bjet_logChargedEmEnergyFraction",log10(bjet.ChargedEmEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_1belectron/bjet_MuonEnergyFraction",bjet.MuonEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/bjet_logMuonEnergyFraction",log10(bjet.MuonEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_1belectron/bjet_charge",bjet.charge,weight,50,-1,1);
  FillHist(SigORBkg+"_1belectron/bjet_charge_dot_electron_charge",bjet.charge*belectron.charge,weight,50,-1,1);
  FillHist(SigORBkg+"_1belectron/fabs(bjet_charge)",fabs(bjet.charge),weight,50,0,1);

  /*
  FillHist(SigORBkg+"_1belectron/bjet_ChargedHadronEnergyFraction",bjet.ChargedHadronEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/bjet_NeutralHadronEnergyFraction",bjet.NeutralHadronEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/bjet_NeutralEmEnergyFraction",bjet.NeutralEmEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/bjet_ChargedEmEnergyFraction",bjet.ChargedEmEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/bjet_logChargedEmEnergyFraction",log10(bjet.ChargedEmEnergyFraction),weight,100,-3,0);
  FillHist(SigORBkg+"_1belectron/bjet_MuonEnergyFraction",bjet.MuonEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_1belectron/bjet_logMuonEnergyFraction",log10(bjet.MuonEnergyFraction),weight,100,-3,0);
  FillHist(SigORBkg+"_1belectron/bjet_charge",bjet.charge,weight,50,-1,1);
  FillHist(SigORBkg+"_1belectron/fabs(bjet_charge)",fabs(bjet.charge),weight,50,0,1);
  FillHist(SigORBkg+"_1belectron/bjet_partonFlavour",bjet.partonFlavour,weight,27,-6,21);
  */
  FillHist(SigORBkg+"_1belectron/bjet_ChargedMultiplicity",bjet.ChargedMultiplicity,weight,60,0,60);
  FillHist(SigORBkg+"_1belectron/bjet_NeutralMultiplicity",bjet.NeutralMultiplicity,weight,60,0,60);
  
  //id related
  FillHist(SigORBkg+"_1belectron/electron_IsGsfCtfScPixChargeConsistent",belectron.IsGsfCtfScPixChargeConsistent,weight,2,0,2);
  FillHist(SigORBkg+"_1belectron/electron_PassConversionVeto",belectron.PassConversionVeto,weight,2,0,2);
  FillHist(SigORBkg+"_1belectron/electron_nmissinghits",belectron.nmissinghits,weight,20,0,20);
  FillHist(SigORBkg+"_1belectron/electron_passVetoID",belectron.passVetoID,weight,2,0,2);
  FillHist(SigORBkg+"_1belectron/electron_passVetoIDnoIso",belectron.passVetoIDnoIso,weight,2,0,2);
  FillHist(SigORBkg+"_1belectron/electron_passLooseID",belectron.passLooseID,weight,2,0,2);

  //id related // by eta region
  if(belectron.aeta < 1.479){ // ECAL BARREL
    FillHist(SigORBkg+"_1belectron_EB/electron_full5x5sigmaietaieta",belectron.full5x5sigmaietaieta,weight,100,0,1);
    FillHist(SigORBkg+"_1belectron_EB/electron_log_1_full5x5sigmaietaieta",log10(1+belectron.full5x5sigmaietaieta),weight,100,0,0.05);
    FillHist(SigORBkg+"_1belectron_EB/electron_abs_detaseed",belectron.abs_detaseed,weight,100,0,1);
    FillHist(SigORBkg+"_1belectron_EB/electron_log_abs_detaseed",log10(belectron.abs_detaseed),weight,100,-8,1);
    FillHist(SigORBkg+"_1belectron_EB/electron_abs_dPhiIn",belectron.abs_dPhiIn,weight,100,0,1);
    FillHist(SigORBkg+"_1belectron_EB/electron_log_abs_dPhiIn",log10(belectron.abs_dPhiIn),weight,100,-8,1);
    FillHist(SigORBkg+"_1belectron_EB/electron_InvEminusInvP",belectron.InvEminusInvP,weight,100,0,1);
    FillHist(SigORBkg+"_1belectron_EB/electron_log_InvEminusInvP",log10(belectron.InvEminusInvP),weight,100,-8,1);
    FillHist(SigORBkg+"_1belectron_EB/electron_HoverE",belectron.HoverE,weight,100,0,1);
    FillHist(SigORBkg+"_1belectron_EB/electron_log_0p0001_HoverE",log10(0.0001+belectron.HoverE),weight,100,-4,1);
    


  }// |eta|<1.479
  else{ // ECAL ENDCAP
    FillHist(SigORBkg+"_1belectron_EE/electron_full5x5sigmaietaieta",belectron.full5x5sigmaietaieta,weight,100,0,1);
    FillHist(SigORBkg+"_1belectron_EE/electron_log_1_full5x5sigmaietaieta",log10(1+belectron.full5x5sigmaietaieta),weight,100,0,0.05);
    FillHist(SigORBkg+"_1belectron_EE/electron_abs_detaseed",belectron.abs_detaseed,weight,100,0,1);
    FillHist(SigORBkg+"_1belectron_EE/electron_log_abs_detaseed",log10(belectron.abs_detaseed),weight,100,-8,1); 
    FillHist(SigORBkg+"_1belectron_EE/electron_abs_dPhiIn",belectron.abs_dPhiIn,weight,100,0,1);
    FillHist(SigORBkg+"_1belectron_EE/electron_log_abs_dPhiIn",log10(belectron.abs_dPhiIn),weight,100,-8,1);
    FillHist(SigORBkg+"_1belectron_EE/electron_InvEminusInvP",belectron.InvEminusInvP,weight,100,0,1);
    FillHist(SigORBkg+"_1belectron_EE/electron_log_InvEminusInvP",log10(belectron.InvEminusInvP),weight,100,-8,1);
    FillHist(SigORBkg+"_1belectron_EE/electron_HoverE",belectron.HoverE,weight,100,0,1);
    FillHist(SigORBkg+"_1belectron_EE/electron_log_0p0001_HoverE",log10(0.0001+belectron.HoverE),weight,100,-4,1);
  }//|eta|>1.479
}

void EEMu_MuMuE_Method::FillTree_0blepton(){
  Has_bMuon=false;
  Has_bElectron=false;
  bmuon=Get_init_bmuonvar();
  belectron=Get_init_belectronvar();
  bjet=Get_bjetvar(AllJets[jetidx_b]);

  bool isSig=false;
  bool isBkg=false;
  if(bjet.charge*bcharge > 0) isSig=true;
  if(bjet.charge*bcharge < 0) isBkg=true;
  if(isSig){
    jhchoi_newtree->Fill();
    FillHist_0blepton("Sig");
  }else if(isBkg){
    jhchoi_newtree2->Fill();
    FillHist_0blepton("Bkg");
  }

}

void EEMu_MuMuE_Method::FillHist_0blepton(TString SigORBkg){
  FillHist(SigORBkg+"_0blepton/bjet_ChargedHadronEnergyFraction",bjet.ChargedHadronEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_0blepton/bjet_logChargedHadronEnergyFraction",log10(bjet.ChargedHadronEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_0blepton/bjet_NeutralHadronEnergyFraction",bjet.NeutralHadronEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_0blepton/bjet_log_NeutralHadronEnergyFraction",log10(bjet.NeutralHadronEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_0blepton/bjet_NeutralEmEnergyFraction",bjet.NeutralEmEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_0blepton/bjet_logNeutralEmEnergyFraction",log10(bjet.NeutralEmEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_0blepton/bjet_ChargedEmEnergyFraction",bjet.ChargedEmEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_0blepton/bjet_logChargedEmEnergyFraction",log10(bjet.ChargedEmEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_0blepton/bjet_MuonEnergyFraction",bjet.MuonEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_0blepton/bjet_logMuonEnergyFraction",log10(bjet.MuonEnergyFraction),weight,100,-6,0);
  FillHist(SigORBkg+"_0blepton/bjet_charge",bjet.charge,weight,50,-1,1);
  FillHist(SigORBkg+"_0blepton/fabs(bjet_charge)",fabs(bjet.charge),weight,50,0,1);
  /*
  FillHist(SigORBkg+"_0blepton/bjet_ChargedHadronEnergyFraction",bjet.ChargedHadronEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_0blepton/bjet_NeutralHadronEnergyFraction",bjet.NeutralHadronEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_0blepton/bjet_NeutralEmEnergyFraction",bjet.NeutralEmEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_0blepton/bjet_ChargedEmEnergyFraction",bjet.ChargedEmEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_0blepton/bjet_logChargedEmEnergyFraction",log10(bjet.ChargedEmEnergyFraction),weight,100,-3,0);
  FillHist(SigORBkg+"_0blepton/bjet_MuonEnergyFraction",bjet.MuonEnergyFraction,weight,100,0,1);
  FillHist(SigORBkg+"_0blepton/bjet_logMuonEnergyFraction",log10(bjet.MuonEnergyFraction),weight,100,-3,0);
  FillHist(SigORBkg+"_0blepton/bjet_charge",bjet.charge,weight,50,-1,1);
  FillHist(SigORBkg+"_0blepton/fabs(bjet_charge)",fabs(bjet.charge),weight,50,0,1);
  FillHist(SigORBkg+"_0blepton/bjet_partonFlavour",bjet.partonFlavour,weight,27,-6,21);
  */
  FillHist(SigORBkg+"_0blepton/bjet_ChargedMultiplicity",bjet.ChargedMultiplicity,weight,60,0,60);
  FillHist(SigORBkg+"_0blepton/bjet_NeutralMultiplicity",bjet.NeutralMultiplicity,weight,60,0,60);

  

}

JHAnalyzerBase::belectronvar EEMu_MuMuE_Method::Get_init_belectronvar(){
  belectronvar init_var;
  return init_var;
}
JHAnalyzerBase::bmuonvar EEMu_MuMuE_Method::Get_init_bmuonvar(){
  bmuonvar init_var;
  return init_var;
}

void EEMu_MuMuE_Method::CountEMuInJet(Jet &this_jet){
  for(auto& electron : AllElectrons){
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(this_jet.DeltaR(electron)>0.4) continue;
    n_e+=1;
    if(electron.Charge()>0){
      n_ep+=1;
    }
    else{
      n_em+=1;
    }
  }
  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    if(this_jet.DeltaR(muon)>0.4) continue;
    n_mu+=1;
    if(muon.Charge()>0){
      n_mup+=1;
    }else{
      n_mum+=1;
    }
  }


}

bool EEMu_MuMuE_Method::FindBJet(){
  //---Add cut for LHE level b's pT
  n_mu=0; n_e=0;
  n_mup=0; n_ep=0;
  n_mum=0; n_em=0;
  if(lhes[idx_lhe_b].Pt() < 30.) return 0;
  unsigned int jetsize=AllJets.size();
  vector<int> v_idx;

  for(unsigned int i = 0; i < jetsize;i++){
    if(AllJets[i].DeltaR(lhes[idx_lhe_b]) > 0.4) continue;
    if(AllJets[i].partonFlavour() != pid_b) continue;
    if(AllJets[i].Pt() < 30.) continue;
    v_idx.push_back(i);
  }
  if(v_idx.size()==1){
    jetidx_b=v_idx[0];
    CountEMuInJet(AllJets[jetidx_b]);
    return 1;
  }
  else{
    return 0;
  }
}

void EEMu_MuMuE_Method::RunMuonInJet_v2405_1(){
  nbmuon=0;
  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    if(AllJets[jetidx_b].DeltaR(muon)>0.4) continue;
    if(muon.RelIso() > 10.) continue;
    if(muon.Chi2()>10) continue;
    if(muon.TrackerLayers()<1) continue;
    if(muon.MatchedStations() <2) continue;
    nbmuon+=1;
    current_bmuon=muon;
    if(muon.Charge() > 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonPlus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonPlus",muon);
    }
    if(muon.Charge() < 0){
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonMinus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonMinus",muon);
    }
  }
}

void EEMu_MuMuE_Method::RunMuonInJet_v2405_2(){
  //updated : matchedstats > 0
  nbmuon=0;
  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    if(AllJets[jetidx_b].DeltaR(muon)>0.4) continue;
    if(muon.RelIso() > 10.) continue;
    if(muon.Chi2()>10) continue;
    if(muon.TrackerLayers()<1) continue;
    if(muon.MatchedStations() <1) continue;
    nbmuon+=1;
    current_bmuon=muon;
    if(muon.Charge() > 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonPlus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonPlus",muon);
    }
    if(muon.Charge() < 0){
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonMinus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonMinus",muon);
    }
  }
}

void EEMu_MuMuE_Method::RunMuonInJet_v2405_3(){
  //updated : matchedstats > 0
  nbmuon=0;
  for(auto& muon : AllMuons){
    //if(muon.Pt() < 5.) continue;
    if(AllJets[jetidx_b].DeltaR(muon)>0.4) continue;
    //if(muon.RelIso() > 10.) continue;
    //if(muon.Chi2()>10) continue;
    //if(muon.TrackerLayers()<1) continue;
    //if(muon.MatchedStations() <1) continue;
    nbmuon+=1;
    current_bmuon=muon;
    if(muon.Charge() > 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonPlus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonPlus",muon);
    }
    if(muon.Charge() < 0){
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonMinus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonMinus",muon);
    }
  }
}


void EEMu_MuMuE_Method::RunMuonInJet_v2503_1(){
  //updated : matchedstats > 0
  nbmuon=0;
  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    if(AllJets[jetidx_b].DeltaR(muon)>0.4) continue;
    //if(muon.RelIso() > 10.) continue;
    //if(muon.Chi2()>10) continue;
    //if(muon.TrackerLayers()<1) continue;
    //if(muon.MatchedStations() <1) continue;
    nbmuon+=1;
    current_bmuon=muon;
    if(muon.Charge() > 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonPlus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonPlus",muon);
    }
    if(muon.Charge() < 0){
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonMinus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonMinus",muon);
    }
  }
  //cout << "nbmuon=" << nbmuon << endl;
}



void EEMu_MuMuE_Method::RunMuonInJet_v2608_1(){
  //updated : matchedstats > 0
  nbmuon=0;
  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    if(AllJets[jetidx_b].DeltaR(muon)>0.4) continue;
    //if(muon.RelIso() > 10.) continue;
    //if(muon.Chi2()>10) continue;
    //if(muon.TrackerLayers()<1) continue;
    //if(muon.MatchedStations() <1) continue;
    bool isGlobalMuon__OR__isTrackerMuon= muon.IsType(Muon::GlobalMuon) || muon.IsType(Muon::TrackerMuon);
    if(!isGlobalMuon__OR__isTrackerMuon) continue;


    nbmuon+=1;
    current_bmuon=muon;
    if(muon.Charge() > 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonPlus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonPlus",muon);
    }
    if(muon.Charge() < 0){
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonMinus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonMinus",muon);
    }
  }
  //cout << "nbmuon=" << nbmuon << endl;
}



void EEMu_MuMuE_Method::RunMuonInJet(){
  //FillHist by MuonCharge
  //ll_str,bcharge_str
  if(isTreeMode && !IsEE) return;
  if(is_cut_v2608_1){
    RunMuonInJet_v2608_1();
    return;
  }
  else if (is_cut_v2405_1){
    RunMuonInJet_v2405_1();
    return;
  }
  else if (is_cut_v2405_2){
    RunMuonInJet_v2405_2();
    return;
  }
 else if (is_cut_v2405_3){
    RunMuonInJet_v2405_3();
    return;
  }

 else if (is_cut_v2503_1){
   RunMuonInJet_v2503_1();
   return;
 }

 else if (is_cut_v2503_2){
   RunMuonInJet_v2503_2();
   return;
 }
  nbmuon=0;
  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    nbmuon+=1;
    current_bmuon=muon;

    if(muon.Charge() > 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonPlus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonPlus",muon);
      if(AllJets[jetidx_b].DeltaR(muon)<0.4){
	FillHistBJet(ll_str+"__"+bcharge_str+"__muonPlus_InBJet",AllJets[jetidx_b]);
	FillHistMuon(ll_str+"__"+bcharge_str+"__muonPlus_InBJet",muon);
      }
    }
    if(muon.Charge() < 0){
      FillHistBJet(ll_str+"__"+bcharge_str+"__muonMinus",AllJets[jetidx_b]);
      FillHistMuon(ll_str+"__"+bcharge_str+"__muonMinus",muon);
      if(AllJets[jetidx_b].DeltaR(muon)<0.4) {
	FillHistBJet(ll_str+"__"+bcharge_str+"__muonMinus_InBJet",AllJets[jetidx_b]);
	FillHistMuon(ll_str+"__"+bcharge_str+"__muonMinus_InBJet",muon);
      }
    }
  }


}

void EEMu_MuMuE_Method::RunElectronInJet_v2405_1(){
  //FillHist by ElectronCharge
  nbelectron=0;
  for(auto& electron : AllElectrons){
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    if(electron.RelIso() > 10.) continue;
    if(electron.NMissingHits() != 0) continue;
    if(AllJets[jetidx_b].DeltaR(electron)>0.4) continue;
    nbelectron+=1;
    current_belectron=electron;
    if(electron.Charge() > 0) {
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronPlus",electron);
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronPlus",AllJets[jetidx_b]);
    }
    if(electron.Charge() < 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronMinus",AllJets[jetidx_b]);
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronMinus",electron);
    }
  }
} 

void EEMu_MuMuE_Method::RunElectronInJet_v2405_2(){
  //FillHist by ElectronCharge
  nbelectron=0;
  for(auto& electron : AllElectrons){
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    if(electron.RelIso() > 10.) continue;
    if(electron.NMissingHits() != 0) continue;
    if(AllJets[jetidx_b].DeltaR(electron)>0.4) continue;
    nbelectron+=1;
    current_belectron=electron;
    if(electron.Charge() > 0) {
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronPlus",electron);
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronPlus",AllJets[jetidx_b]);
    }
    if(electron.Charge() < 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronMinus",AllJets[jetidx_b]);
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronMinus",electron);
    }
  }
}

void EEMu_MuMuE_Method::RunElectronInJet_v2503_1(){
  //FillHist by ElectronCharge
  nbelectron=0;
  for(auto& electron : AllElectrons){
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    //if(electron.RelIso() > 10.) continue;
    //if(electron.NMissingHits() != 0) continue;
    if(AllJets[jetidx_b].DeltaR(electron)>0.4) continue;
    nbelectron+=1;
    current_belectron=electron;
    if(electron.Charge() > 0) {
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronPlus",electron);
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronPlus",AllJets[jetidx_b]);
    }
    if(electron.Charge() < 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronMinus",AllJets[jetidx_b]);
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronMinus",electron);
    }
  }
}




void EEMu_MuMuE_Method::RunElectronInJet_v2608_1(){
  //FillHist by ElectronCharge
  nbelectron=0;
  for(auto& electron : AllElectrons){
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    if(AllJets[jetidx_b].DeltaR(electron)>0.4) continue;
    nbelectron+=1;
    current_belectron=electron;
    if(electron.Charge() > 0) {
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronPlus",electron);
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronPlus",AllJets[jetidx_b]);
    }
    if(electron.Charge() < 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronMinus",AllJets[jetidx_b]);
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronMinus",electron);
    }
  }
}

void EEMu_MuMuE_Method::RunElectronInJet_v2503_2(){
  //FillHist by ElectronCharge
  nbelectron=0;
  for(auto& electron : AllElectrons){
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    //if(electron.RelIso() > 10.) continue;
    //if(electron.NMissingHits() != 0) continue;
    if(AllJets[jetidx_b].DeltaR(electron)>0.4) continue;
    nbelectron+=1;
    current_belectron=electron;
    if(electron.Charge() > 0) {
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronPlus",electron);
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronPlus",AllJets[jetidx_b]);
    }
    if(electron.Charge() < 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronMinus",AllJets[jetidx_b]);
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronMinus",electron);
    }
  }
}



void EEMu_MuMuE_Method::RunElectronInJet_v2405_3(){
  RunElectronInJet_v2405_2();//variation only in muon
}


void EEMu_MuMuE_Method::RunElectronInJet(){
  if(isTreeMode && !IsMuMu) return;
  if(is_cut_v2608_1){
    RunElectronInJet_v2608_1();
    return;
  }
  else if(is_cut_v2405_1){
    RunElectronInJet_v2405_1();
    return;
  }  
  else if(is_cut_v2405_2){
    RunElectronInJet_v2405_2();
    return;
  }
  else if(is_cut_v2405_3){
    RunElectronInJet_v2405_3();
    return;
  }
  //FillHist by ElectronCharge
  nbelectron=0;
  for(auto& electron : AllElectrons){
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;    
    nbelectron+=1;
    current_belectron=electron;

    if(electron.Charge() > 0) {
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronPlus",electron);
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronPlus",AllJets[jetidx_b]);
      if(AllJets[jetidx_b].DeltaR(electron)<0.4){
	FillHistElectron(ll_str+"__"+bcharge_str+"__electronPlus_InBJet",electron);
	FillHistBJet(ll_str+"__"+bcharge_str+"__electronPlus_InBJet",AllJets[jetidx_b]);
      }
    }
    if(electron.Charge() < 0) {
      FillHistBJet(ll_str+"__"+bcharge_str+"__electronMinus",AllJets[jetidx_b]);
      FillHistElectron(ll_str+"__"+bcharge_str+"__electronMinus",electron);
      if(AllJets[jetidx_b].DeltaR(electron)<0.4) {
	FillHistBJet(ll_str+"__"+bcharge_str+"__electronMinus_InBJet",AllJets[jetidx_b]);
	FillHistElectron(ll_str+"__"+bcharge_str+"__electronMinus_InBJet",electron);
      }
    }
  }

}


void EEMu_MuMuE_Method::FillHistBJet(TString cutname, Jet &jet){
  if(isTreeMode) return;
  FillHist(cutname+"/bjet_pt",jet.Pt(),weight,100,0,200);
  FillHist(cutname+"/bjet_eta",jet.Eta(),weight,80,-4,4);
  FillHist(cutname+"/bjet_phi",jet.Phi(),weight,80,-4,4);
  FillHist(cutname+"/bjet_ChargedHadronEnergyFraction",jet.GetChargedHadronEnergyFraction(),weight,100,0,1);
  FillHist(cutname+"/bjet_NeutralHadronEnergyFraction",jet.GetNeutralHadronEnergyFraction(),weight,100,0,1);
  FillHist(cutname+"/bjet_NeutralEmEnergyFraction",jet.GetNeutralEmEnergyFraction(),weight,100,0,1);
  FillHist(cutname+"/bjet_ChargedEmEnergyFraction",jet.GetChargedEmEnergyFraction(),weight,100,0,1);
  FillHist(cutname+"/bjet_logChargedEmEnergyFraction",log10(jet.GetChargedEmEnergyFraction()),weight,100,-3,0);
  FillHist(cutname+"/bjet_MuonEnergyFraction",jet.GetMuonEnergyFraction(),weight,100,0,1);
  FillHist(cutname+"/bjet_logMuonEnergyFraction",log10(jet.GetMuonEnergyFraction()),weight,100,-3,0);
  FillHist(cutname+"/bjet_charge",jet.Charge(),weight,50,-1,1);
  FillHist(cutname+"/fabs(bjet_charge)",fabs(jet.Charge()),weight,50,0,1);
  FillHist(cutname+"/bjet_partonFlavour",jet.partonFlavour(),weight,27,-6,21);

  FillHist(cutname+"/bjet_ChargedMultiplicity",jet.ChargedMultiplicity(),weight,60,0,60);
  FillHist(cutname+"/bjet_NeutralMultiplicity",jet.NeutralMultiplicity(),weight,60,0,60);

  FillHistNLepton(cutname);
  if(n_mu+n_e>0) FillHistNLepton(cutname+"_nlepOver0");
  if(n_mu==1) FillHistNLepton(cutname+"_nmu1");
  if(n_mu>0) FillHistNLepton(cutname+"_nmuOver0");
  if(n_e==1) FillHistNLepton(cutname+"_ne1");
  if(n_e==1) FillHistNLepton(cutname+"_neOver0");
  //lep+
  if(n_mup+n_ep==1) FillHistNLepton(cutname+"_nlepp1");
  if(n_mup+n_ep>0) FillHistNLepton(cutname+"_nleppOver0");
  if(n_mup==1) FillHistNLepton(cutname+"_nmup1");
  if(n_mup>0) FillHistNLepton(cutname+"_nmupOver0");
  if(n_ep==1) FillHistNLepton(cutname+"_nep1");
  if(n_ep>0) FillHistNLepton(cutname+"_nepOver0");

  //lep-
  if(n_mum+n_em>0) FillHistNLepton(cutname+"_nlepmOver0");
  if(n_mum==1) FillHistNLepton(cutname+"_nmum1");
  if(n_mum>0) FillHistNLepton(cutname+"_nmumOver0");
  if(n_em==1) FillHistNLepton(cutname+"_nem1");
  if(n_em>0) FillHistNLepton(cutname+"_nemOver0");


}

void EEMu_MuMuE_Method::FillHistNLepton(TString cutname){
    FillHist(cutname+"/bjet_nlepton",n_mu+n_e,weight,10,0,10);
    FillHist(cutname+"/bjet_nmuon",n_mu,weight,10,0,10);
    FillHist(cutname+"/bjet_nelectron",n_e,weight,10,0,10);
    FillHist(cutname+"/bjet_nleptonPlus",n_mup+n_ep,weight,10,0,10);
    FillHist(cutname+"/bjet_nmuonPlus",n_mup,weight,10,0,10);
    FillHist(cutname+"/bjet_nelectronPlus",n_ep,weight,10,0,10);
    
    FillHist(cutname+"/bjet_nleptonMinus",n_mum+n_em,weight,10,0,10);
    FillHist(cutname+"/bjet_nmuonMinus",n_mum,weight,10,0,10);
    FillHist(cutname+"/bjet_nelectronMinus",n_em,weight,10,0,10);
}

void EEMu_MuMuE_Method::FillHistElectron(TString cutname,Electron &electron){
  if(isTreeMode) return;
  FillHist(cutname+"/electron_p_jetrestframe",GetP_JetRestFrame(electron,AllJets[jetidx_b]),weight,100,0,20);
  FillHist(cutname+"/electron_ptwrtjet",GetPt_wrt_Jet(electron,AllJets[jetidx_b]),weight,100,0,20);
  FillHist(cutname+"/electron_palongjet",GetP_along_Jet(electron,AllJets[jetidx_b]),weight,100,0,50);
  FillHist(cutname+"/electron_palongjet_Over_Pjet",GetP_along_Jet(electron,AllJets[jetidx_b])/AllJets[jetidx_b].P(),weight,100,0,1);
  FillHist(cutname+"/electron_dR_j",electron.DeltaR(AllJets[jetidx_b]),weight,100,0,2);
  FillHist(cutname+"/electron_reliso",electron.RelIso(),weight,100,0,20);
  FillHist(cutname+"/electron_logreliso",log10(electron.RelIso()),weight,100,-2,1.5);
  FillHist(cutname+"/electron_reltrkiso",electron.TrkIso()/electron.Pt(),weight,100,0,20);
  FillHist(cutname+"/electron_logreltrkiso",log10(electron.TrkIso()/electron.Pt()),weight,100,-2,1.5);
  FillHist(cutname+"/electron_relecalPFClusterIso",electron.ecalPFClusterIso()/electron.Pt(),weight,100,0,20);
  FillHist(cutname+"/electron_logrelecalPFClusterIso",log10(electron.ecalPFClusterIso()/electron.Pt()),weight,100,-2,1.5);
  FillHist(cutname+"/electron_nsip3d",fabs(electron.IP3D()/electron.IP3Derr()),weight,100,0,10);

  FillHist(cutname+"/electron_pt",electron.Pt(),weight,100,0,100);
  FillHist(cutname+"/electron_eta",electron.Eta(),weight,80,-4,4);
  //To Check ID
  FillHist(cutname+"/electron_passVetoNoIso",electron.PassID("passVetoIDnoIso"),weight,4,-2,2);
  FillHist(cutname+"/electron_passVetoID",electron.PassID("passVetoID"),weight,4,-2,2);
  FillHist(cutname+"/electron_passLooseID",electron.PassID("passLooseID"),weight,4,-2,2);
  //To Check ID variables //https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2
  if (fabs(electron.scEta()) <= 1.479){
    FillHist(cutname+"_EB/electron_Full5x5_sigmaIetaIeta",electron.Full5x5_sigmaIetaIeta(),weight,100,0,0.1);
    FillHist(cutname+"_EB/electron_fabs_dEtaSeed",fabs(electron.dEtaSeed()),weight,100,0,0.01);
    FillHist(cutname+"_EB/electron_HoverE_Over_DENO",electron.HoverE()/(0.05 + 1.16/electron.scE() + 0.0324*electron.Rho()/electron.scE()) ,weight,100,0,10);
    FillHist(cutname+"_EB/electron_HoverE",electron.HoverE(),weight,100,0,10);
    FillHist(cutname+"_EB/electron_logHoverE",log10(electron.HoverE()),weight,100,-3,2);
    FillHist(cutname+"_EB/electron_fabs_InvEminusInvP",fabs(electron.InvEminusInvP()) ,weight,100,0,1);
    FillHist(cutname+"_EB/electron_logfabs_InvEminusInvP",log10(fabs(electron.InvEminusInvP())) ,weight,100,-3,0);
    FillHist(cutname+"_EB/electron_NMissingHits",electron.NMissingHits() ,weight,10,0,10);
    FillHist(cutname+"_EB/electron_PassConversionVeto",electron.PassConversionVeto() ,weight,4,-2,2);
  }
  else{
    FillHist(cutname+"_EE/electron_Full5x5_sigmaIetaIeta",electron.Full5x5_sigmaIetaIeta(),weight,100,0,0.1);
    FillHist(cutname+"_EE/electron_fabs_dEtaSeed",fabs(electron.dEtaSeed()),weight,100,0,0.02);
    FillHist(cutname+"_EE/electron_HoverE_Over_DENO",electron.HoverE()/(0.05 + 2.54/electron.scE() + 0.183*electron.Rho()/electron.scE()) ,weight,100,0,10);
    FillHist(cutname+"_EE/electron_HoverE",electron.HoverE(),weight,100,0,10);
    FillHist(cutname+"_EE/electron_logHoverE",log10(electron.HoverE()),weight,100,-3,2);
    FillHist(cutname+"_EE/electron_fabs_InvEminusInvP",fabs(electron.InvEminusInvP()) ,weight,100,0,1);
    FillHist(cutname+"_EE/electron_logfabs_InvEminusInvP",log10(fabs(electron.InvEminusInvP())) ,weight,100,-3,0);
    FillHist(cutname+"_EE/electron_NMissingHits",electron.NMissingHits() ,weight,10,0,10);
    FillHist(cutname+"_EE/electron_PassConversionVeto",electron.PassConversionVeto() ,weight,4,-2,2);
  }
}

void EEMu_MuMuE_Method::FillHistMuon(TString cutname,Muon &muon){
  if(isTreeMode) return;
  FillHist(cutname+"/muon_p_jetrestframe",GetP_JetRestFrame(muon,AllJets[jetidx_b]),weight,100,0,20);
  FillHist(cutname+"/muon_ptwrtjet",GetPt_wrt_Jet(muon,AllJets[jetidx_b]),weight,100,0,20);
  FillHist(cutname+"/muon_palongjet",GetP_along_Jet(muon,AllJets[jetidx_b]),weight,100,0,50);
  FillHist(cutname+"/muon_palongjet_Over_Pjet",GetP_along_Jet(muon,AllJets[jetidx_b])/AllJets[jetidx_b].P(),weight,100,0,1);
  FillHist(cutname+"/muon_dR_j",muon.DeltaR(AllJets[jetidx_b]),weight,100,0,2);
  FillHist(cutname+"/muon_reliso",muon.RelIso(),weight,100,0,20);
  FillHist(cutname+"/muon_logreliso",log10(muon.RelIso()),weight,100,-2,1.5);
  FillHist(cutname+"/muon_reltrkiso",muon.TrkIso()/muon.Pt(),weight,100,0,20);
  FillHist(cutname+"/muon_logreltrkiso",log10(muon.TrkIso()/muon.Pt()),weight,100,-2,1.5);
  FillHist(cutname+"/muon_nsip3d",fabs(muon.IP3D()/muon.IP3Derr()),weight,100,0,10);

  FillHist(cutname+"/muon_pt",muon.Pt(),weight,100,0,100);
  FillHist(cutname+"/muon_eta",muon.Eta(),weight,80,-4,4);

  //To Check ID
  FillHist(cutname+"/muon_passLoose",muon.PassID("POGLoose"),weight,4,-2,2);
  FillHist(cutname+"/muon_passMedium",muon.PassID("POGMedium"),weight,4,-2,2);
  FillHist(cutname+"/muon_passTight",muon.PassID("POGTight"),weight,4,-2,2);

  //Add some other variables to Check
  FillHist(cutname+"/muon_NormChi2",muon.Chi2(),weight,40,0,20);
  FillHist(cutname+"/muon_TrackerLayers",muon.TrackerLayers(),weight,20,0,20);
  FillHist(cutname+"/muon_TrackerHits",muon.TrackerHits(),weight,35,0,35);
  FillHist(cutname+"/muon_ValidMuonHits",muon.ValidMuonHits(),weight,60,0,60);
  FillHist(cutname+"/muon_MatchedStations",muon.MatchedStations(),weight,6,0,6);
  
}


