#include "BBbar_Analyzer.h"


BBbar_Analyzer::BBbar_Analyzer(){//FYI : bottomness = -nb
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
}



void BBbar_Analyzer::initializeAnalyzer(){
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
  cout << "[BBbar_Analyzer::initializeAnalyzer] RunSyst = " << RunSyst << endl;

  if(IsDATA){
    //ProcessName=DataStream;    
    ProcessName="Data";
  }
  else{
    ProcessName=MCSample;
  }
  cout << "[BBbar_Analyzer::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;


  //==== (Example) Year-dependent variables
  //==== I defined "TString IsoMuTriggerName;" and "double TriggerSafePtCut;" in Analyzers/include/BBbar_Analyzer.h 
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
  cout << "[BBbar_Analyzer::initializeAnalyzer] RunNewPDF = " << RunNewPDF << endl;
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
  cout << "[BBbar_Analyzer::initializeAnalyzer] RunXSecSyst = " << RunXSecSyst << endl;

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
  if(1 != myLHE.nparton_outgoing) return false;
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
    if(myRECO.vBmatchedJet.Pt()){
      BmatJet20Event=true;
    }
    else{
      BmatJet20Event=false;
    }
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
  for(unsigned int i = 0; i < myLHE.LHEsize ; i++){
    status=LHEs[i].Status();
    pid=LHEs[i].ID();
    if(status==-1){
      myLHE.incoming_parton_pid.push_back(pid);
    }
  }

  myLHE.x_b=-1;
  myLHE.x_g=-1;
  myLHE.Q2=-1;
  if(abs(myLHE.incoming_parton_pid[0])==5){//1st parton is b
    myLHE.x_b=genWeight_X1;
  }
  else if (myLHE.incoming_parton_pid[0]==21){//1st parton is g
    myLHE.x_g=genWeight_X1;
  }
  else if(abs(myLHE.incoming_parton_pid[1])==5){//1st parton is b
    myLHE.x_b=genWeight_X2;
  }
  else if (myLHE.incoming_parton_pid[1]==21){//1st parton is g
    myLHE.x_g=genWeight_X2;
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
void BBbar_Analyzer::RunProtoType(){
  TString ProtoTypeEventTag="ProtoType__"+EventTag;
  
  std::vector<int> v_bmuonidx;
  for(unsigned int i=0; i < muonsize; i++){
    if(i==myRECO.idx_Zmuon1) continue;
    if(i==myRECO.idx_Zmuon2) continue;
    FillHist(ProtoTypeEventTag+"_Muon/NotZmuonCut/"+ProcessName, 0, weight, 2, -1., 1.);
    double ptwrtbjet=AllMuons[i].P()*sin(AllMuons[i].Angle(AllJets[myRECO.ij_B].Vect()));
    int muon_charge=AllMuons[i].Charge();
    if ( muon_charge > 0){
      FillHist(ProtoTypeEventTag+"_Muon/muonp_ptwrtbjet/"+ProcessName, ptwrtbjet, weight, 100, 0., 10.);
    }
    else{
      FillHist(ProtoTypeEventTag+"_Muon/muonn_ptwrtbjet/"+ProcessName, ptwrtbjet, weight, 100, 0., 10.);
    }
    if(ptwrtbjet <0.6) continue;
    if(AllMuons[i].TrkIso()/AllMuons[i].Pt() <0.05) continue; // original, 0.1
    if(fabs(AllMuons[i].IP3D())/AllMuons[i].IP3Derr() <2.) continue; // original, 2.5
    if(AllJets[myRECO.ij_B].DeltaR(AllMuons[i])>0.4) continue; 
    v_bmuonidx.push_back(i);
  }
 
  if(v_bmuonidx.size()>0){
    unsigned int i_bmuon=v_bmuonidx[0];
    //--check only muon channel!
    FillHist(ProtoTypeEventTag+"_AtLeast1MuonInBmatjet/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
    FillHist(ProtoTypeEventTag+"_AtLeast1MuonInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
    FillHist(ProtoTypeEventTag+"_AtLeast1MuonInBmatjet/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);

    if(v_bmuonidx.size()==1){
      FillHist(ProtoTypeEventTag+"_Only1MuonInBmatjet/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
      FillHist(ProtoTypeEventTag+"_Only1MuonInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
      FillHist(ProtoTypeEventTag+"_Only1MuonInBmatjet/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);
    }//[END] #muon==1
  }//[END] # muon>0
}

void BBbar_Analyzer::RunLeptonCutStudy(){
  TString CutStudyEventTag=EventTag;
  CutStudyEventTag="CutStudy__"+CutStudyEventTag;
  std::vector<int> v_bmuonidx;
  std::vector<int> v_nocut_bmuonidx;
  for(unsigned int i=0; i < muonsize; i++){
    if(i==myRECO.idx_Zmuon1) continue;
    if(i==myRECO.idx_Zmuon2) continue;
    v_nocut_bmuonidx.push_back(i);
    //---Boost muon to jet restframe
    TLorentzVector vl(AllMuons[i]);
    vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
    double muon_p_jetrestf=vl.P();
    double dR_mu_j=AllJets[myRECO.ij_B].DeltaR(AllMuons[i]);
    int muon_charge=AllMuons[i].Charge();
    FillHist(CutStudyEventTag+"_Muon/NotZmuonCut/"+ProcessName, 0, weight, 2, -1., 1.);
    if ( muon_charge > 0){
      FillHist(CutStudyEventTag+"_Muon/muonp_P_jetrestf/"+ProcessName, muon_p_jetrestf, weight, 200, 0., 10.);
      FillHist(CutStudyEventTag+"_Muon/muonp_dRbmatj/"+ProcessName, dR_mu_j, weight, 200, 0., 5.);
    }
    else{
      FillHist(CutStudyEventTag+"_Muon/muonn_P_jetrestf/"+ProcessName, muon_p_jetrestf, weight, 200, 0., 10.);
      FillHist(CutStudyEventTag+"_Muon/muonn_dRbmatj/"+ProcessName, dR_mu_j, weight, 200, 0., 5.);
    }

    if(dR_mu_j<0.5){
      if ( muon_charge > 0){
	FillHist(CutStudyEventTag+"_MuonInBmatjet0p5/muonp_P_jetrestf/"+ProcessName, muon_p_jetrestf, weight, 200, 0., 10.);
      }
      else{
	FillHist(CutStudyEventTag+"_MuonInBmatjet0p5/muonn_P_jetrestf/"+ProcessName, muon_p_jetrestf, weight, 200, 0., 10.);
      }
    }
    if( (muon_p_jetrestf > 0.7)  && (muon_p_jetrestf < 2.5) ){
      if ( muon_charge > 0){
        FillHist(CutStudyEventTag+"_MuonPjetrestf_0p7_2p5/muonp_dRbmatj/"+ProcessName, dR_mu_j, weight, 200, 0., 5.);
      }
      else{
        FillHist(CutStudyEventTag+"_MuonPjetrestf_0p7_2p5/muonn_dRbmatj/"+ProcessName, dR_mu_j, weight, 200, 0., 5.);
      }

    }

    if(  (dR_mu_j<0.5) && (muon_p_jetrestf > 0.7) && (muon_p_jetrestf < 2.5) ){ 
      v_bmuonidx.push_back(i);
    }
  }
 
  if(v_bmuonidx.size()>0){
    unsigned int i_bmuon=v_bmuonidx[0];
    //--check only muon channel!
    FillHist(CutStudyEventTag+"_AtLeast1MuonInBmatjet/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
    FillHist(CutStudyEventTag+"_AtLeast1MuonInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
    FillHist(CutStudyEventTag+"_AtLeast1MuonInBmatjet/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);

    if(v_bmuonidx.size()==1){
      FillHist(CutStudyEventTag+"_Only1MuonInBmatjet/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
      FillHist(CutStudyEventTag+"_Only1MuonInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
      FillHist(CutStudyEventTag+"_Only1MuonInBmatjet/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);
    }//[END] #muon==1
  }//[END] # muon >0
  if(v_nocut_bmuonidx.size()>0){
    unsigned int i_bmuon=v_nocut_bmuonidx[0];
    //--check only muon channel!
    FillHist("NoCutOnMuon__"+EventTag+"_AtLeast1MuonInBmatjet/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
    FillHist("NoCutOnMuon__"+EventTag+"_AtLeast1MuonInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
    FillHist("NoCutOnMuon__"+EventTag+"_AtLeast1MuonInBmatjet/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);
    
    if(v_nocut_bmuonidx.size()==1){
      FillHist("NoCutOnMuon__"+EventTag+"_Only1MuonInBmatjet/bmuon_charge/"+ProcessName, AllMuons[i_bmuon].Charge(), weight, 4, -2., 2.);
      FillHist("NoCutOnMuon__"+EventTag+"_Only1MuonInBmatjet/jet_charge/"+ProcessName, AllJets[myRECO.ij_B].Charge(), weight, 100, -2., 2.);
      FillHist("NoCutOnMuon__"+EventTag+"_Only1MuonInBmatjet/bmuon_bjet_chargesum/"+ProcessName, AllMuons[i_bmuon].Charge()+AllJets[myRECO.ij_B].Charge(), weight, 100, -3., 3.);
    }//[END] #muon==1
    
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
  if(myLHE.is_ee){
    EventTag+="_ee";
  }
  else if(myLHE.is_mumu){
    EventTag+="_mm";
  }

  //(1-2)For B hadron to lepton decay
  BBbar_Analyzer::RunProtoType();
  BBbar_Analyzer::RunLeptonCutStudy();
 

}

void BBbar_Analyzer::executeEvent(){
  EventTag="";
  doPrint=false;
  weight = 1.;//init event weight
  weight *= MCweight();

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
void BBbar_Analyzer::executeEventFromParameter(AnalyzerParameter param){
  


  //=============
  //==== No Cut
  //=============
  


  FillHist("NoCut/Events/"+ProcessName, 0., 1., 1, 0., 1.);

  //========================
  //==== MET Filter
  //========================

  if(!PassMETFilter()) return;

  Event ev = GetEvent();
  Particle METv = ev.GetMETVector();

  //==============
  //==== Trigger
  //==============
  if(! (ev.PassTrigger(IsoMuTriggerName) )) return;



  //======================
  //==== Copy AllObjects
  //======================

  vector<Muon> this_AllMuons = AllMuons;
  vector<Jet> this_AllJets = AllJets;

  //==== Then, for each systematic sources
  //==== 1) Smear or scale them
  //==== 2) Then apply ID selections
  //==== This order should be explicitly followed
  //==== Below are all variables for available systematic sources

  if(param.syst_ == AnalyzerParameter::Central){

  }
  else if(param.syst_ == AnalyzerParameter::JetResUp){
    this_AllJets = SmearJets( this_AllJets, +1 );
    //this_AllFatJets = SmearFatJets( this_AllFatJets, +1 );
  }
  else if(param.syst_ == AnalyzerParameter::JetResDown){
    this_AllJets = SmearJets( this_AllJets, -1 );
    //this_AllFatJets = SmearFatJets( this_AllFatJets, -1 );
  }
  else if(param.syst_ == AnalyzerParameter::JetEnUp){
    this_AllJets = ScaleJets( this_AllJets, +1 );
    //this_AllFatJets = ScaleFatJets( this_AllFatJets, +1 );
  }
  else if(param.syst_ == AnalyzerParameter::JetEnDown){
    this_AllJets = ScaleJets( this_AllJets, -1 );
    //this_AllFatJets = ScaleFatJets( this_AllFatJets, -1 );
  }
  else if(param.syst_ == AnalyzerParameter::MuonEnUp){
    this_AllMuons = ScaleMuons( this_AllMuons, +1 );
  }
  else if(param.syst_ == AnalyzerParameter::MuonEnDown){
    this_AllMuons = ScaleMuons( this_AllMuons, -1 );
  }
  else if(param.syst_ == AnalyzerParameter::ElectronResUp){
    //this_AllElectrons = SmearElectrons( this_AllElectrons, +1 );
  }
  else if(param.syst_ == AnalyzerParameter::ElectronResDown){
    //this_AllElectrons = SmearElectrons( this_AllElectrons, -1 );
  }
  else if(param.syst_ == AnalyzerParameter::ElectronEnUp){
    //this_AllElectrons = ScaleElectrons( this_AllElectrons, +1 );
  }
  else if(param.syst_ == AnalyzerParameter::ElectronEnDown){
    //this_AllElectrons = ScaleElectrons( this_AllElectrons, -1 );
  }
  else{
    cout << "[BBbar_Analyzer::executeEventFromParameter] Wrong syst" << endl;
    exit(EXIT_FAILURE);
  }

  //==================================================
  //==== Then, apply ID selections using this_AllXXX
  //==================================================

  vector<Muon> muons = SelectMuons(this_AllMuons, param.Muon_Tight_ID, 20., 2.4);
  vector<Jet> jets = SelectJets(this_AllJets, param.Jet_ID, 30., 2.4);

  //=======================
  //==== Sort in pt-order
  //=======================

  //==== 1) leptons : after scaling/smearing, pt ordring can differ from MINIAOD
  std::sort(muons.begin(), muons.end(), PtComparing);
  //==== 2) jets : similar, but also when applying new JEC, ordering is changes. This is important if you use leading jets
  std::sort(jets.begin(), jets.end(), PtComparing);

  int NBJets_NoSF(0), NBJets_WithSF_2a(0);
  JetTagging::Parameters jtp_DeepCSV_Medium = JetTagging::Parameters(JetTagging::DeepCSV,
                                                                     JetTagging::Medium,
                                                                     JetTagging::incl, JetTagging::comb);

  //==== b tagging

  //==== method 1a)
  //==== multiply "btagWeight" to the event weight
  double btagWeight = mcCorr->GetBTaggingReweight_1a(jets, jtp_DeepCSV_Medium);

  //==== method 2a)
  for(unsigned int ij = 0 ; ij < jets.size(); ij++){

    double this_discr = jets[ij].GetTaggerResult(JetTagging::DeepCSV);
    //==== No SF
    if( this_discr > mcCorr->GetJetTaggingCutValue(JetTagging::DeepCSV, JetTagging::Medium) ) NBJets_NoSF++;
    //==== 2a
    if( mcCorr->IsBTagged_2a(jtp_DeepCSV_Medium, jets[ij]) ) NBJets_WithSF_2a++;

  }

  
  //=========================
  //==== Event selections..
  //=========================

  //==== dimuon
  if(muons.size() != 2) return;

  //==== leading muon has trigger-safe pt
  if( muons.at(0).Pt() <= TriggerSafePtCut ) return;

  //==== On-Z
  Particle ZCand = muons.at(0) + muons.at(1);
  if(!IsOnZ(ZCand.M(), 15.)) return;

  //===================
  //==== Event weight
  //===================

  double weight = 1.;
  //==== If MC
  if(!IsDATA){

    //==== MCweight is normalized to 1 pb-1.
    weight *= MCweight();

    //==== you can pass trigger names to ev.GetTriggerLumi(), but if you are using unprescaled trigger, simply pass "Full"
    weight *= ev.GetTriggerLumi("Full");

    //==== L1Prefire reweight
    weight *= weight_Prefire;

    //==== Example of applying Muon scale factors
    for(unsigned int i=0; i<muons.size(); i++){

      double this_idsf = 1.;
      //double this_idsf  = mcCorr->MuonID_SF (param.Muon_ID_SF_Key,  muons[i].Eta(), muons[i].MiniAODPt());

      //==== If you have iso SF, do below. Here we don't.
      //double this_isosf = mcCorr->MuonISO_SF(param.Muon_ISO_SF_Key, muons[i].Eta(), muons[i].MiniAODPt());
      double this_isosf = 1.;

      weight *= this_idsf*this_isosf;

    }

  }

  //==========================
  //==== Now fill histograms
  //==========================

  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  FillHist("BasicCut/ZCand_Mass_Wide/"+ProcessName, ZCand.M(), weight, 180, 40., 400.); //nbin,xmin,xmax

}



