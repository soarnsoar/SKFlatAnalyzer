#include "BBbar_Analyzer.h"


BBbar_Analyzer::BBbar_Analyzer(){//FYI : bottomness = -nb
  //TMVA model
  overflow=3;


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


}




void BBbar_Analyzer::initializeAnalyzer(){

  //================================================================
  //====  Example 1
  //====  Dimuon Z-peak events with two muon IDs, with systematics
  //================================================================

  //==== if you use "--userflags RunSyst" with SKFlat.py, HasFlag("RunSyst") will return "true"
  RunSyst = HasFlag("RunSyst");
  cout << "[BBbar_Analyzer::initializeAnalyzer] RunSyst = " << RunSyst << endl;

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
  cout << "[BBbar_Analyzer::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;



}

BBbar_Analyzer::~BBbar_Analyzer(){

  //==== Destructor of this Analyzer

}

bool BBbar_Analyzer::Tag_gbToZb(){
  LHEs=GetLHEs();
  BBbar_Analyzer::myLHE.LHEsize = LHEs.size();  
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

int BBbar_Analyzer::CheckIsBhadAndNb(int pid){
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

void BBbar_Analyzer::Tag_B_Hadron(){
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

void BBbar_Analyzer::Loop_genBMatchedRecoJet(){
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
    
  }//[END] if there's Bhad matched jet
  
}//[END]BBbar_Analyzer::Loop_genBMatchedRecoJet()

/////---Histogram Set---/////




void BBbar_Analyzer::AnalyzeGEN(){
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
void BBbar_Analyzer::AnalyzeLHE(){
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



bool BBbar_Analyzer::ZTagCuts(){
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
    if(v_Z.M()<60.) return 0;
    if(v_Z.M()>120.) return 0;
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





void BBbar_Analyzer::RunProtoTypeMuon(){
  TString ProtoTypeEventTag="ProtoType__"+EventTag;
  TString ProtoTypeEventTagJetParton="ProtoType__"+EventTagJetParton;
  
  std::vector<int> v_bmuonidx;
  for(unsigned int i=0; i < muonsize; i++){
    if(i==myRECO.idx_Zmuon1) continue;
    if(i==myRECO.idx_Zmuon2) continue;
    FillHist(ProtoTypeEventTag+"_Muon/NotZmuonCut/"+ProcessName, 0, weight, 2, -1., 1.);
    FillHist(ProtoTypeEventTagJetParton+"_Muon/NotZmuonCut/"+ProcessName, 0, weight, 2, -1., 1.);
    double ptwrtbjet=AllMuons[i].P()*sin(AllMuons[i].Angle(AllJets[myRECO.ij_B].Vect()));
    int muon_charge=AllMuons[i].Charge();
    if ( muon_charge > 0){
      FillHist(ProtoTypeEventTag+"_MuonPlus/muon_ptwrtbjet/"+ProcessName, ptwrtbjet, weight, 100, 0., 10.);
      FillHist(ProtoTypeEventTagJetParton+"_MuonPlus/muon_ptwrtbjet/"+ProcessName, ptwrtbjet, weight, 100, 0., 10.);
    }
    else{
      FillHist(ProtoTypeEventTag+"_MuonMinus/muon_ptwrtbjet/"+ProcessName, ptwrtbjet, weight, 100, 0., 10.);      
      FillHist(ProtoTypeEventTagJetParton+"_MuonMinus/muon_ptwrtbjet/"+ProcessName, ptwrtbjet, weight, 100, 0., 10.);
    }
    if(ptwrtbjet <0.6) continue;
    if(AllMuons[i].TrkIso()/AllMuons[i].Pt() <0.05) continue; // original, 0.1
    if(fabs(AllMuons[i].IP3D()/AllMuons[i].IP3Derr()) <2.) continue; // original, 2.5
    if(AllJets[myRECO.ij_B].DeltaR(AllMuons[i])>0.4) continue; 
    v_bmuonidx.push_back(i);
  }
 
  if(v_bmuonidx.size()>0){
    i_bmuon=v_bmuonidx[0];
    //--check only muon channel!
    FillHist(ProtoTypeEventTag+"__AtLeast1MuonInBmatjet/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
    FillHist(ProtoTypeEventTag+"__AtLeast1MuonInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
    FillHist(ProtoTypeEventTag+"__AtLeast1MuonInBmatjet/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);
    FillHist(ProtoTypeEventTagJetParton+"__AtLeast1MuonInBmatjet/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
    FillHist(ProtoTypeEventTagJetParton+"__AtLeast1MuonInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
    FillHist(ProtoTypeEventTagJetParton+"__AtLeast1MuonInBmatjet/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);
    if(v_bmuonidx.size()==1){
      FillHist(ProtoTypeEventTag+"__Only1MuonInBmatjet/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
      FillHist(ProtoTypeEventTag+"__Only1MuonInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
      FillHist(ProtoTypeEventTag+"__Only1MuonInBmatjet/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);

      FillHist(ProtoTypeEventTagJetParton+"__Only1MuonInBmatjet/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
      FillHist(ProtoTypeEventTagJetParton+"__Only1MuonInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
      FillHist(ProtoTypeEventTagJetParton+"__Only1MuonInBmatjet/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);
    }//[END] #muon==1
  }//[END] # muon>0
}


void BBbar_Analyzer::RunProtoTypeElectron(){
  TString ProtoTypeEventTag="ProtoType__"+EventTag;
  TString ProtoTypeEventTagJetParton="ProtoType__"+EventTagJetParton;
  
  std::vector<int> v_belectronidx;
  for(unsigned int i=0; i < electronsize; i++){
    if(i==myRECO.idx_Zelectron1) continue;
    if(i==myRECO.idx_Zelectron2) continue;
    FillHist(ProtoTypeEventTag+"_Electron/NotZelectronCut/"+ProcessName, 0, weight, 2, -1., 1.);
    FillHist(ProtoTypeEventTagJetParton+"_Electron/NotZelectronCut/"+ProcessName, 0, weight, 2, -1., 1.);
    double ptwrtbjet=AllElectrons[i].P()*sin(AllElectrons[i].Angle(AllJets[myRECO.ij_B].Vect()));
    int electron_charge=AllElectrons[i].Charge();
    if ( electron_charge > 0){
      FillHist(ProtoTypeEventTag+"_ElectronPlus/electron_ptwrtbjet/"+ProcessName, ptwrtbjet, weight, 100, 0., 10.);
      FillHist(ProtoTypeEventTagJetParton+"_ElectronPlus/electron_ptwrtbjet/"+ProcessName, ptwrtbjet, weight, 100, 0., 10.);
    }
    else{
      FillHist(ProtoTypeEventTag+"_ElectronMinus/electron_ptwrtbjet/"+ProcessName, ptwrtbjet, weight, 100, 0., 10.);
      FillHist(ProtoTypeEventTagJetParton+"_ElectronMinus/electron_ptwrtbjet/"+ProcessName, ptwrtbjet, weight, 100, 0., 10.);
    }
    if(ptwrtbjet <0.6) continue;
    if(AllElectrons[i].ecalPFClusterIso()/AllElectrons[i].Pt() == 0.) continue;
    if(abs(AllElectrons[i].IP3D())/AllElectrons[i].IP3Derr() <2.0) continue;
    if(!AllElectrons[i].IsGsfCtfScPixChargeConsistent()) continue;
    v_belectronidx.push_back(i);
  }
 
  if(v_belectronidx.size()>0){
    i_belectron=v_belectronidx[0];
    //--check only electron channel!
    FillHist(ProtoTypeEventTag+"__AtLeast1ElectronInBmatjet/belectron_charge/"+ProcessName, AllElectrons[i_belectron].Charge(), weight, 4, -2., 2.);
    FillHist(ProtoTypeEventTag+"__AtLeast1ElectronInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
    FillHist(ProtoTypeEventTag+"__AtLeast1ElectronInBmatjet/belectron_bjet_chargesum/"+ProcessName, AllElectrons[i_belectron].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);

    FillHist(ProtoTypeEventTagJetParton+"__AtLeast1ElectronInBmatjet/belectron_charge/"+ProcessName, AllElectrons[i_belectron].Charge(), weight, 4, -2., 2.);
    FillHist(ProtoTypeEventTagJetParton+"__AtLeast1ElectronInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
    FillHist(ProtoTypeEventTagJetParton+"__AtLeast1ElectronInBmatjet/belectron_bjet_chargesum/"+ProcessName, AllElectrons[i_belectron].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);

    if(v_belectronidx.size()==1){
      FillHist(ProtoTypeEventTag+"__Only1ElectronInBmatjet/belectron_charge/"+ProcessName, AllElectrons[i_belectron].Charge(), weight, 4, -2., 2.);
      FillHist(ProtoTypeEventTag+"__Only1ElectronInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
      FillHist(ProtoTypeEventTag+"__Only1ElectronInBmatjet/belectron_bjet_chargesum/"+ProcessName, AllElectrons[i_belectron].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);

      FillHist(ProtoTypeEventTagJetParton+"__Only1ElectronInBmatjet/belectron_charge/"+ProcessName, AllElectrons[i_belectron].Charge(), weight, 4, -2., 2.);
      FillHist(ProtoTypeEventTagJetParton+"__Only1ElectronInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
      FillHist(ProtoTypeEventTagJetParton+"__Only1ElectronInBmatjet/belectron_bjet_chargesum/"+ProcessName, AllElectrons[i_belectron].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);
    }//[END] #electron==1
  }//[END] # electron>0
}

void BBbar_Analyzer::FillHistMuon(TString cutname){
  FillHistUnderAndOverFlow(cutname+"/muon_P_jetrestf/"+ProcessName, p_jetrestf, weight, 200, 0., 10.);
  FillHistUnderAndOverFlow(cutname+"/muon_dRbmatj/"+ProcessName, dR_l_j, weight, 200, 0., 5.);
  FillHistUnderAndOverFlow(cutname+"/muon_ip3d/"+ProcessName, ip3d, weight, 100, -10., 10.);
  FillHistUnderAndOverFlow(cutname+"/muon_nsip3d/"+ProcessName, nsip3d, weight, 100, 0., 100.);
  FillHistUnderAndOverFlow(cutname+"/muon_lognsip3d/"+ProcessName, log10(nsip3d), weight,100, -4, 2.);
  FillHistUnderAndOverFlow(cutname+"/muon_logreliso/"+ProcessName, log10(reliso), weight, 100, -5., 3.);
  FillHistUnderAndOverFlow(cutname+"/muon_logreltrkiso/"+ProcessName, log10(reltrkiso), weight, 100, -5., 3.);
  FillHistUnderAndOverFlow(cutname+"/muon_reltrkiso/"+ProcessName, reltrkiso, weight, 100, 0., 1.);

  FillHist(cutname+"/muon_P_jetrestf_noOF/"+ProcessName, p_jetrestf, weight, 200, 0., 10.);
  FillHist(cutname+"/muon_dRbmatj_noOF/"+ProcessName, dR_l_j, weight, 200, 0., 5.);
  FillHist(cutname+"/muon_ip3d_noOF/"+ProcessName, ip3d, weight, 100, -10., 10.);
  FillHist(cutname+"/muon_nsip3d_noOF/"+ProcessName, nsip3d, weight, 100, 0., 100.);
  FillHist(cutname+"/muon_lognsip3d_noOF/"+ProcessName, log10(nsip3d), weight,100, -4, 2.);
  FillHist(cutname+"/muon_logreliso_noOF/"+ProcessName, log10(reliso), weight, 100, -5., 3.);
  FillHist(cutname+"/muon_logreltrkiso_noOF/"+ProcessName, log10(reltrkiso), weight, 100, -5., 3.);
  FillHist(cutname+"/muon_reltrkiso_noOF/"+ProcessName, reltrkiso, weight, 100, 0., 1.);
}

void BBbar_Analyzer::FillHistMuonCharge(TString cutname){
  FillHist(cutname+"/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
  FillHist(cutname+"/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
  FillHist(cutname+"/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);


}

void BBbar_Analyzer::RunLeptonCutStudyMuon(){
  TString CutStudyEventTag=EventTag;
  CutStudyEventTag="CutStudy__"+CutStudyEventTag;
  TString CutStudyEventTagJetParton=EventTagJetParton;
  CutStudyEventTagJetParton="CutStudy__"+CutStudyEventTagJetParton;
  std::vector<int> v_bmuonidx;
  std::vector<int> v_nocut_bmuonidx;
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
    /*
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
    */

    if(dR_l_j<0.4){
      v_nocut_bmuonidx.push_back(i);
      if ( muon_charge > 0){
	FillHistMuon(CutStudyEventTag+"_MuonPlus__dR0p4");
	FillHistMuon(CutStudyEventTagJetParton+"_MuonPlus__dR0p4");
      }
      else{
	FillHistMuon(CutStudyEventTag+"_MuonMinus__dR0p4");
	FillHistMuon(CutStudyEventTagJetParton+"_MuonMinus__dR0p4");
      }
    }
    
    
  }
 

}






void BBbar_Analyzer::FillHistElectron(TString cutname){
  FillHistUnderAndOverFlow(cutname+"/electron_P_jetrestf/"+ProcessName, p_jetrestf, weight, 200, 0., 10.);
  FillHistUnderAndOverFlow(cutname+"/electron_dRbmatj/"+ProcessName, dR_l_j, weight, 200, 0., 5.);
  FillHistUnderAndOverFlow(cutname+"/electron_ip3d/"+ProcessName, ip3d, weight, 100, -10., 10.);
  FillHistUnderAndOverFlow(cutname+"/electron_nsip3d/"+ProcessName, nsip3d, weight, 100, 0., 100.);
  FillHistUnderAndOverFlow(cutname+"/electron_lognsip3d/"+ProcessName, log10(nsip3d), weight, 100,-4, 2.);
  FillHistUnderAndOverFlow(cutname+"/electron_logreliso/"+ProcessName, log10(reliso), weight, 100, -5., 3.);
  FillHistUnderAndOverFlow(cutname+"/electron_logreltrkiso/"+ProcessName, log10(reltrkiso), weight, 100, -5., 3.);
  FillHistUnderAndOverFlow(cutname+"/electron_reltrkiso/"+ProcessName, reltrkiso, weight, 100, 0., 1.);
  FillHistUnderAndOverFlow(cutname+"/electron_logrelecalclusteriso/"+ProcessName, log10(relecalclusteriso), weight, 100, -5., 2.);
  FillHistUnderAndOverFlow(cutname+"/electron_IsGsfCtfScPixChargeConsistent/"+ProcessName, IsGsfCtfScPixChargeConsistent, weight, 4, -1., 3.);//


  FillHist(cutname+"/electron_P_jetrestf_noOF/"+ProcessName, p_jetrestf, weight, 200, 0., 10.);
  FillHist(cutname+"/electron_dRbmatj_noOF/"+ProcessName, dR_l_j, weight, 200, 0., 5.);
  FillHist(cutname+"/electron_ip3d_noOF/"+ProcessName, ip3d, weight, 100, -10., 10.);
  FillHist(cutname+"/electron_nsip3d_noOF/"+ProcessName, nsip3d, weight, 100, 0., 100.);
  FillHist(cutname+"/electron_lognsip3d_noOF/"+ProcessName, log10(nsip3d), weight, 100,-4, 2.);
  FillHist(cutname+"/electron_logreliso_noOF/"+ProcessName, log10(reliso), weight, 100, -5., 3.);
  FillHist(cutname+"/electron_logreltrkiso_noOF/"+ProcessName, log10(reltrkiso), weight, 100, -5., 3.);
  FillHist(cutname+"/electron_reltrkiso_noOF/"+ProcessName, reltrkiso, weight, 100, 0., 1.);
  FillHist(cutname+"/electron_logrelecalclusteriso_noOF/"+ProcessName, log10(relecalclusteriso), weight, 100, -5., 2.);
  FillHist(cutname+"/electron_IsGsfCtfScPixChargeConsistent_noOF/"+ProcessName, IsGsfCtfScPixChargeConsistent, weight, 4, -1., 3.);//
}

void BBbar_Analyzer::FillHistElectronCharge(TString cutname){
  FillHist(cutname+"/belectron_charge/"+ProcessName, AllElectrons[i_belectron].Charge(), weight, 4, -2., 2.);
  FillHist(cutname+"/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
  FillHist(cutname+"/belectron_bjet_chargesum/"+ProcessName, AllElectrons[i_belectron].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);


}

void BBbar_Analyzer::RunLeptonCutStudyElectron(){
  TString CutStudyEventTag=EventTag;
  CutStudyEventTag="CutStudy__"+CutStudyEventTag;
  TString CutStudyEventTagJetParton=EventTagJetParton;
  CutStudyEventTagJetParton="CutStudy__"+CutStudyEventTagJetParton;
  std::vector<int> v_belectronidx;
  std::vector<int> v_nocut_belectronidx;
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
    if(dR_l_j<0.4){
      v_nocut_belectronidx.push_back(i);
      if ( electron_charge > 0){
	FillHistElectron(CutStudyEventTag+"_ElectronPlus__dR0p4");
	FillHistElectron(CutStudyEventTagJetParton+"_ElectronPlus__dR0p4");
      }
      else{
	FillHistElectron(CutStudyEventTag+"_ElectronMinus__dR0p4");
	FillHistElectron(CutStudyEventTagJetParton+"_ElectronMinus__dR0p4");
      }
    }


  }
  
  
}









void BBbar_Analyzer::AnalyzeRECO(){

  //call muon/electron
  AllMuons=GetAllMuons();
  muonsize = AllMuons.size();
  AllElectrons=GetAllElectrons();
  electronsize = AllElectrons.size();
  
  //(0) Apply some basic cuts
  bool isGoodZ=BBbar_Analyzer::ZTagCuts();
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

  BBbar_Analyzer::RunLeptonCutStudyMuon();
  BBbar_Analyzer::RunLeptonCutStudyElectron();
 

}

void BBbar_Analyzer::executeEvent(){
  EventTag="";
  EventTagJetParton="";
  doPrint=false;
  weight = 1.;//init event weight
  weight *= MCweight();

  //initialize//
  myLHE.incoming_parton_pid.clear();

  //(1)---Let's tag only events with following process..
  //         g      =====o----- b(or bbar)
  //                     |
  //                     |
  //   b(or bbar)   -----o======     Z
  //
  
  myLHE.is_gbToZb = BBbar_Analyzer::Tag_gbToZb(); 
  if(!myLHE.is_gbToZb) return;
  if (!allow_tautau){
    if (myLHE.is_tautau) return;
  }
  FillHist("gbToZb/evt_nb_LHE/"+ProcessName,myLHE.evt_nb,weight, 4, -2., 2.);
  //->For LHE info, tag events with one gluon and one b(bbar)quark 
  // if b event : BBbar_Analyzer::myLHE.evt_nb=1
  // if bbar event : BBbar_Analyzer::myLHE.evt_nb=-1

  //(2)---Get the most energetic B-hadron info. in GEN
  BBbar_Analyzer::Tag_B_Hadron();
  //->For GEN particles 
  //  -> Tag All B hadron and get the most energetic B-hadron info.
  
  //(3)---Check Jet matching to B-hadron
  BBbar_Analyzer::Loop_genBMatchedRecoJet();


  //(4)---Now basic generator level info is set. do analysis//fill histograms
  BBbar_Analyzer::AnalyzeLHE();
  BBbar_Analyzer::AnalyzeGEN();
  if(!myRECO.HasBmatchedRecoJet) return; // if there's no bmatjet->return
  if(!(1==myRECO.nBmatJet)) return;
  BBbar_Analyzer::AnalyzeRECO();


  
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
