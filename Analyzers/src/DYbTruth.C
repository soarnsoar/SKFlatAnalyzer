#include "DYbTruth.h"
#include <map>
DYbTruth::DYbTruth(){
  //runSys=true;

  //JHAnalyzerBase::SetupDiLeptonChannel();  
}

DYbTruth::~DYbTruth(){
  //==== Destructor of this Analyzer
}

void DYbTruth::initializeAnalyzer(){


  //MuonID="NOCUT";
  //MuonID="POGLoose";
  //MuonMinPt=5;
  //DeltaR_Mu=0.1;
  
  //ElectronID="passVetoID";
  //ElectronID="NOCUT";
  //ElectronID="passVetoIDnoIso";
  //ElectronMinPt=5;
  //DeltaR_E=0.1;

  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupDiLeptonChannel();

  
  lepveto=false;
  if(HasFlag("lepveto")){
    lepveto=true;
    cout << "lepveto -> true" << endl;
  }




  cout << "[DYbTruth::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();


  jhchoi_newtree=new TTree("dyb_reco","dyb_reco");
  jhchoi_newtree->Branch("z_pt",&z_pt);
  jhchoi_newtree->Branch("z_eta",&z_eta);
  jhchoi_newtree->Branch("z_phi",&z_phi);
  jhchoi_newtree->Branch("z_mass",&z_mass);
  jhchoi_newtree->Branch("jet_pt",&jet_pt);
  jhchoi_newtree->Branch("jet_eta",&jet_eta);
  jhchoi_newtree->Branch("jet_phi",&jet_phi);
  jhchoi_newtree->Branch("jet_mass",&jet_mass);
  jhchoi_newtree->Branch("weight",&weight);
  jhchoi_newtree->Branch("x_b",&x_b);
  jhchoi_newtree->Branch("x_g",&x_g);
  jhchoi_newtree->Branch("x1",&genWeight_X1);
  jhchoi_newtree->Branch("x2",&genWeight_X2);

  jhchoi_newtree->Branch("z_rapidity",&z_rapidity);
  jhchoi_newtree->Branch("jet_rapidity",&jet_rapidity);
  jhchoi_newtree->Branch("z_jet_rapidity",&z_jet_rapidity);
  jhchoi_newtree->Branch("z_minus_jet_rapidity",&z_minus_jet_rapidity);

  
  jhchoi_newtree2=new TTree("dyb_truth","dyb_truth");
  jhchoi_newtree2->Branch("true_z_pt",&true_z_pt);
  jhchoi_newtree2->Branch("true_z_eta",&true_z_eta);
  jhchoi_newtree2->Branch("true_z_phi",&true_z_phi);
  jhchoi_newtree2->Branch("true_z_mass",&true_z_mass);

  jhchoi_newtree2->Branch("true_b_pt",&true_b_pt);
  jhchoi_newtree2->Branch("true_b_eta",&true_b_eta);
  jhchoi_newtree2->Branch("true_b_phi",&true_b_phi);
  jhchoi_newtree2->Branch("true_b_mass",&true_b_mass);

  jhchoi_newtree->Branch("true_z_rapidity",&true_z_rapidity);
  jhchoi_newtree->Branch("true_b_rapidity",&true_b_rapidity);
  jhchoi_newtree->Branch("true_z_b_rapidity",&true_z_b_rapidity);
  jhchoi_newtree->Branch("true_z_minus_b_rapidity",&true_z_minus_b_rapidity);


  
  jhchoi_newtree2->Branch("weight",&weight);
  jhchoi_newtree2->Branch("x_b",&x_b);
  jhchoi_newtree2->Branch("x_g",&x_g);

  jhchoi_newtree2->Branch("x1",&genWeight_X1);
  jhchoi_newtree2->Branch("x2",&genWeight_X2);

}


void DYbTruth::TruthLoop(){
  //
  true_b_pt=0;true_b_eta=0;true_b_phi=0;true_b_mass=0;
  true_z_pt=0;true_z_eta=0;true_z_phi=0;true_z_mass=0;
  TLorentzVector vz_true;
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
      vz_true+=lhes[i];
    }
    else if(abs(pid)==13){//muon
      nmuon+=1;
      if(pid>0){
	idx_lhe_mu1=i;
      }else{
	idx_lhe_mu2=i;
      }
      vz_true+=lhes[i];
    }else if(abs(pid)==11){//electron
      nelectron+=1;
      if(pid>0){
	idx_lhe_e1=i;	
      }
      else{
	idx_lhe_e2=i;
      }
      vz_true+=lhes[i];
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

  if(nb+nbbar==1){
    true_z_pt=vz_true.Pt();
    true_z_eta=vz_true.Eta();
    true_z_phi=vz_true.Phi();
    true_z_mass=vz_true.M();

    true_b_pt=lhes[idx_lhe_b].Pt();
    true_b_eta=lhes[idx_lhe_b].Eta();
    true_b_phi=lhes[idx_lhe_b].Phi();
    true_b_mass=lhes[idx_lhe_b].M();

    true_z_rapidity=vz_true.Rapidity();
    true_b_rapidity=lhes[idx_lhe_b].Rapidity();
    true_z_b_rapidity=(vz_true + lhes[idx_lhe_b]).Rapidity();
    true_z_minus_b_rapidity=(vz_true - lhes[idx_lhe_b]).Rapidity();
    
    weight=MCweight()*ev.GetTriggerLumi("Full");

    if(abs(genWeight_id1)==5){
      x_b=genWeight_X1;
      x_g=genWeight_X2;
    }

    if(abs(genWeight_id2)==5){
      x_b=genWeight_X2;
      x_g=genWeight_X1;
    }
    jhchoi_newtree2->Fill();
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


  if(nb+nbbar==1){
    FillHist("truth/nb_nbbar_sum_one",1,weight,2,0,2);
    if(abs(genWeight_id1)==5){
      FillHist("truth/non_b_incoming_parton_pid",genWeight_id2,weight,60,-30,30);
    }
    if(abs(genWeight_id2)==5){
      FillHist("truth/non_b_incoming_parton_pid",genWeight_id1,weight,60,-30,30);
    }

  }


}

void DYbTruth::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;

}


bool DYbTruth::CheckIsDiMuonChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  //vector<int> v_muonidx=GetIdxDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);                                                                                             
  vector<Muon> v_muon=lepveto ?  GetDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2) :  GetDiMuRecoNoVeto(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  if( v_muon.size()<2) return 0;
  double mll=(v_muon[0]+v_muon[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;

  SetMuon(v_muon[0],v_muon[1]);

  return 1;
}

void DYbTruth::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;

}


bool DYbTruth::CheckIsDiElectronChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count                                                                           

  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);                                                                                 
  vector<Electron> v_electron=lepveto ? GetDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2) :GetDiElRecoNoVeto(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  if( v_electron.size()<2) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  
  double mll=(v_electron[0]+v_electron[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;
  SetElectron(v_electron[0],v_electron[1]);
  return 1;
}






void DYbTruth::EventLoop(){
  weight=MCweight()*ev.GetTriggerLumi("Full");
  FillHist("cutflow/allevents",1,weight,2,0,2);

  if(nb+nbbar!=1) return;

  FillHist("cutflow/nb_nbbar_sum_one",1,weight,2,0,2);

  
  if(nb==1){
    bcharge = -1.;
    bcharge_str="bMinus";
  }
  if(nbbar==1){
    bcharge = 1.;
    bcharge_str="bPlus";
  }

  //(0) apply minpt and ID//  std::vector<Muon> GetMuons(TString id, double ptmin, double fetamax);
  //AllMuons=GetMuons(MuonID,MuonMinPt,2.4);
  //AllElectrons=GetElectrons(ElectronID,ElectronMinPt,2.5);


  IsDiMuonChannel=false;
  IsDiElectronChannel=false;
  double min_mll = 60;
  double max_mll = 120;

  IsDiMuonChannel=CheckIsDiMuonChannel(min_mll,max_mll);
  if(!IsDiMuonChannel) IsDiElectronChannel=CheckIsDiElectronChannel(min_mll,max_mll);





  LepCh="";
  if(IsDiMuonChannel){
    //vZ=(*mu1)+(*mu2);
    vZ=mu1+mu2;
    LepCh="mm";
    l1=mu1;
    l2=mu2;
   
  }
  else if(IsDiElectronChannel){
    //vZ=GetDiElectronVector();
    vZ=el1+el2;
    LepCh="ee";
    //l1=AllElectrons[el1idx];
    //l2=AllElectrons[el2idx];
    l1=el1;
    l2=el2;
   
  }
  else{
    return;
  }
  
  if(!FindBJet()) return;
  FillHist("cutflow/findbjet",1,weight,2,0,2);

  

  
  //jetidx_b
  //AllJets[jetidx_b]
  
  //--Get which parton is "b" in LHE
  x_b=-1.;x_g=-1;
  bool Is_gb_production=false;
  if(abs(genWeight_id1)==5 && genWeight_id2==21) Is_gb_production=true;
  if(abs(genWeight_id2)==5 && genWeight_id1==21) Is_gb_production=true;

  if(!Is_gb_production) return;
  FillHist("cutflow/Is_gb_production",1,weight,2,0,2);

  TString prod="";
  if(abs(genWeight_id1)==5){
    x_b=genWeight_X1;
    x_g=genWeight_X2;
    if(genWeight_id1>0){
      prod="gb";
    }
    else{
      prod="gbbar";
    }
  }
  if(abs(genWeight_id2)==5){
    x_b=genWeight_X2;
    x_g=genWeight_X1;
    if(genWeight_id2>0){
      prod="gb";
    }
    else{
      prod="gbbar";
    }
  }


  ///----

  jet_eta=AllJets[jetidx_b].Eta();
  jet_pt=AllJets[jetidx_b].Pt();
  jet_phi=AllJets[jetidx_b].Phi();
  jet_mass=AllJets[jetidx_b].M();
  z_eta=vZ.Eta();
  z_pt=vZ.Pt();
  z_phi=vZ.Phi();
  z_mass=vZ.M();
  double zb_eta=z_eta+jet_eta;
  double zb_boost=zb_eta/2;

  z_rapidity=vZ.Rapidity();
  jet_rapidity=AllJets[jetidx_b].Rapidity();
  z_jet_rapidity=(vZ+AllJets[jetidx_b]).Rapidity();
  z_minus_jet_rapidity=(vZ-AllJets[jetidx_b]).Rapidity();
  //void AnalyzerCore::FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max){


  // x1 - x2 = z_eta + jet_eta
  // if x1 > x2 :
  //  +z boosted z+b system
  
  TString jet_eta_str="";
  
  if(jet_eta<-2.5){
    jet_eta_str="Eta-InfTo-2.5";
  }else if(jet_eta < -2) {
    jet_eta_str="Eta-2.5To-2";
  }else if(jet_eta < -1.6){
    jet_eta_str="Eta-2To-1.6";
  }else if(jet_eta < -0.8){
    jet_eta_str="Eta-1.6To-0.8";
  }else if(jet_eta < 0){
    jet_eta_str="Eta-0.8To0";
  }else if(jet_eta < 0.8){
    jet_eta_str="Eta0To0.8";
  }else if(jet_eta<1.6){
    jet_eta_str="Eta0.8To1.6";
  }else if(jet_eta<2){
    jet_eta_str="Eta1.6To2";
  }else if(jet_eta<2.5){
    jet_eta_str="Eta2To2.5";
  }
  else{
    jet_eta_str="Eta2.5ToInf";
  }
  //-----

  //--boost test case1
  TString jetboosteta_str="";
  if(zb_eta<0 && jet_eta < 0){
    jetboosteta_str=jet_eta_str+"_high1";
  }
  else{
    jetboosteta_str=jet_eta_str+"_low1";
  }


  if(zb_eta>0 && jet_eta > 0){
    jetboosteta_str=jet_eta_str+"_high1";
  }
  else{
    jetboosteta_str=jet_eta_str+"_low1";
  }


  //test case2

  // x1----->   <-- x2
  // zb_boost -> (+)
  // if x1 =b , x2 =g,
  // bjet eta -->(+)

  // else if x1 =g, x2=b
  // bjet eta ---> (+)

  
  
  double jet_deta = jet_eta - zb_boost;
  double z_deta = z_eta - zb_boost;

  


  
  //cut/x/p
  FillHist("all/x_b/"+prod,x_b,weight,100,0,1);
  FillHist("all/log_x_b/"+prod,log(x_b),weight,100,-10,0);


  FillHist(jet_eta_str+"/x_b/"+prod,x_b,weight,100,0,1);
  FillHist(jet_eta_str+"/log_x_b/"+prod,log(x_b),weight,100,-10,0);

  FillHist(jetboosteta_str+"/x_b/"+prod,x_b,weight,100,0,1);
  FillHist(jetboosteta_str+"/log_x_b/"+prod,log(x_b),weight,100,-10,0);
  


  jhchoi_newtree->Fill();
  
  
  
}





bool DYbTruth::FindBJet(){

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
    
    return 1;
  }
  else{
    return 0;
  }
}

