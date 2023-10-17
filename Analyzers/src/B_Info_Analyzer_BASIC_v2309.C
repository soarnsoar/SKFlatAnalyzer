#include "B_Info_Analyzer_BASIC_v2309.h"


B_Info_Analyzer_BASIC_v2309::B_Info_Analyzer_BASIC_v2309(){//FYI : bottomness = -nb
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



void B_Info_Analyzer_BASIC_v2309::initializeAnalyzer(){
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
  cout << "[B_Info_Analyzer_BASIC_v2309::initializeAnalyzer] RunSyst = " << RunSyst << endl;

  if(IsDATA){
    //ProcessName=DataStream;    
    ProcessName="Data";
  }
  else{
    ProcessName=MCSample;
  }
  cout << "[B_Info_Analyzer_BASIC_v2309::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;


  //==== (Example) Year-dependent variables
  //==== I defined "TString IsoMuTriggerName;" and "double TriggerSafePtCut;" in Analyzers/include/B_Info_Analyzer_BASIC_v2309.h 
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
  cout << "[B_Info_Analyzer_BASIC_v2309::initializeAnalyzer] RunNewPDF = " << RunNewPDF << endl;
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
  cout << "[B_Info_Analyzer_BASIC_v2309::initializeAnalyzer] RunXSecSyst = " << RunXSecSyst << endl;

}

B_Info_Analyzer_BASIC_v2309::~B_Info_Analyzer_BASIC_v2309(){

  //==== Destructor of this Analyzer

}

bool B_Info_Analyzer_BASIC_v2309::Tag_gbToZb(){
  LHEs=GetLHEs();
  B_Info_Analyzer_BASIC_v2309::myLHE.LHEsize = LHEs.size();  
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
    //LHE_E=LHEs.at(i).E();
    LHE_status=LHEs[i].Status();
    LHE_id=LHEs[i].ID();
    //LHE_index=LHEs.at(i).Index();
    //LHE_pt=LHEs.at(i).Pt();
    //LHE_eta=LHEs.at(i).Eta();
    //LHE_phi=LHEs.at(i).Phi();
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

int B_Info_Analyzer_BASIC_v2309::CheckIsBhadAndNb(int pid){
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

void B_Info_Analyzer_BASIC_v2309::Tag_B_Hadron(){
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
    //GEN_index=GENs.at(i).Index();
    //GEN_px=GENs.at(i).Px();
    //GEN_py=GENs.at(i).Py();
    //GEN_pz=GENs.at(i).Pz();

    //GEN_status=GENs.at(i).Status();
    GEN_id=GENs[i].PID();
    GEN_pt=GENs[i].Pt();
    //GEN_eta=GENs.at(i).Eta();
    //GEN_phi=GENs.at(i).Phi();
    //GEN_m=GENs.at(i).M();    
    
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

void B_Info_Analyzer_BASIC_v2309::Loop_genBMatchedRecoJet(){
  //init

  myRECO.HasBmatchedRecoJet = false;
  myRECO.nBmatJet=0;
  AllJets = GetAllJets();
  jetsize=AllJets.size();
  //double _RECO_bj_pt=-999.;
  double _RECO_bj_pt=-20.;
  myRECO.ij_B=-1;//Bmatched jet's jet idx
  double jet_pt=-999., jet_flavor= -100, jet_eta = -99;
  //double jet_eta=-999., jet_phi =-999, jet_m = -999, jet_E=-999;
  
  for( unsigned int ij = 0 ; ij < jetsize; ij++){
    jet_pt = AllJets[ij].Pt();
    jet_eta = AllJets.at(ij).Eta();
    //jet_phi = AllJets.at(ij).Phi();
    //jet_m = AllJets.at(ij).M();
    //jet_E = AllJets.at(ij).E();
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
  
}//[END]B_Info_Analyzer_BASIC_v2309::Loop_genBMatchedRecoJet()

/////---Histogram Set---/////

void B_Info_Analyzer_BASIC_v2309::FillHistSetRecoMuon(TString cutname){
  TString this_suffix="";
  for(unsigned int i1 = 0 ; i1 < Cat_b_bbar_size; i1++){
    for(unsigned int i2 = 0 ; i2 < Cat_Z_To_mm_ee_size; i2++){
      for(unsigned int i3 = 0 ; i3 < Cat_lepton_charge_size; i3++){
	//for(unsigned int i4 = 0 ; i4 < Cat_1jet20_size; i4++){
	for(unsigned int i5 = 0 ; i5 < Cat_pTatJetRF2_size; i5++){
	  //this_suffix=Cat_b_bbar[i1]+Cat_Z_To_mm_ee[i2]+Cat_lepton_charge[i3]+Cat_1jet20[i4]+Cat_pTatJetRF2[i5];
	  this_suffix=Cat_b_bbar[i1]+Cat_Z_To_mm_ee[i2]+Cat_lepton_charge[i3]+Cat_pTatJetRF2[i5];
	  //--Check category condition
	  if((i1==1)&&(myLHE.evt_nb!=1)) continue; //if not bevent, skip
	  if((i1==2)&&(myLHE.evt_nb!=-1)) continue; //if not bbarevent, skip
	  
	  if((i2==1)&&(!myLHE.is_mumu)) continue; //if not mumu, skip
	  if((i2==2)&&(!myLHE.is_ee)) continue; //if not ee, skip
	  
	  if((i3==1)&&(muon_charge < 0)) continue; //if not positive muon, skip
	  if((i3==2)&&(muon_charge > 0)) continue; //if not negative muon, skip
	  
	  //if((i4==1)&&(!oneCleanJet20Event || !BmatJet20Event)) continue; //if not 1cleanjet20 OR not bmatjetpt>20
	  if((i5==1)&&(muon_p_jetrestf>2)) continue;
	  //--Fill
	  FillHistRecoMuon(cutname+this_suffix);
	  //}
	}
      }
    }
  } 
  
}

void B_Info_Analyzer_BASIC_v2309::FillHistRecoMuon(TString cutname){
  //muon
  FillHist(cutname+"/muon_pt/"+ProcessName, muon_pt, weight, 100, 0., 100.);
  FillHist(cutname+"/muon_eta/"+ProcessName, muon_eta, weight, 100, -5., 5.);
  FillHist(cutname+"/muon_phi/"+ProcessName, muon_phi, weight, 100, -4., 4.);

  FillHist(cutname+"/muon_dxy/"+ProcessName, muon_dxy, weight, 100, -2., 2.);
  FillHist(cutname+"/muon_dz/"+ProcessName, muon_dz, weight, 100, -40., 40.);
  FillHist(cutname+"/muon_ip3d/"+ProcessName, muon_ip3d, weight, 100, -40., 40.);
  FillHist(cutname+"/muon_nsip3d/"+ProcessName, muon_nsip3d, weight, 100, 0., 10.);
  FillHist(cutname+"/muon_reliso/"+ProcessName, muon_reliso, weight, 100, 0., 5.);
  FillHist(cutname+"/muon_reliso_zoom/"+ProcessName, muon_reliso, weight, 100, 0., 0.3);
  FillHist(cutname+"/muon_reltrkiso/"+ProcessName, muon_reltrkiso, weight, 100, 0., 1.);
  FillHist(cutname+"/muon_reltrkiso_zoom/"+ProcessName, muon_reltrkiso, weight, 100, 0., 0.3);
  FillHist(cutname+"/muon_charge/"+ProcessName, muon_charge, weight, 4, -2., 2.);

  FillHist(cutname+"/muon_psin_bmatj/"+ProcessName, muon_psin_bmatj, weight, 100, 0., 10.);
  FillHist(cutname+"/muon_p_jetrestf/"+ProcessName, muon_p_jetrestf, weight, 100, 0., 10.);

  FillHist(cutname+"/muon_dR_bmatj/"+ProcessName, muon_dR_bmatj, weight, 100, 0., 5.);
  FillHist(cutname+"/muon_ptratio_bmatj/"+ProcessName, muon_ptratio_bmatj, weight, 100, 0., 2.);

  

  //FillHist(cutname+"/muon_jetptratio/"+ProcessName, muon_jetptratio, weight, 100, 0., 2.);
  //FillHist(cutname+"/muon_jetptrel/"+ProcessName, muon_jetptrel, weight, 100, 0., 50.);

  //it is a lepton as well
  FillHist(cutname+"/lepton_pt/"+ProcessName, muon_pt, weight, 100, 0., 100.);
  FillHist(cutname+"/lepton_eta/"+ProcessName, muon_eta, weight, 100, -5., 5.);
  FillHist(cutname+"/lepton_phi/"+ProcessName, muon_phi, weight, 100, -4., 4.);

  FillHist(cutname+"/lepton_dxy/"+ProcessName, muon_dxy, weight, 100, -2., 2.);
  FillHist(cutname+"/lepton_dz/"+ProcessName, muon_dz, weight, 100, -40., 40.);
  FillHist(cutname+"/lepton_ip3d/"+ProcessName, muon_ip3d, weight, 100, -40., 40.);
  FillHist(cutname+"/lepton_nsip3d/"+ProcessName, muon_nsip3d, weight, 100, 0., 10.);
  FillHist(cutname+"/lepton_reliso/"+ProcessName, muon_reliso, weight, 100, 0., 5.);
  FillHist(cutname+"/lepton_reliso_zoom/"+ProcessName, muon_reliso, weight, 100, 0., 0.3);
  FillHist(cutname+"/lepton_charge/"+ProcessName, muon_charge, weight, 4, -2., 2.);
  
  FillHist(cutname+"/lepton_psin_bmatj/"+ProcessName, muon_psin_bmatj, weight, 100, 0., 10.);
  FillHist(cutname+"/lepton_dR_bmatj/"+ProcessName, muon_dR_bmatj, weight, 100, 0., 5.);
  FillHist(cutname+"/lepton_ptratio_bmatj/"+ProcessName, muon_ptratio_bmatj, weight, 100, 0., 2.);
  FillHist(cutname+"/lepton_p_jetrestf/"+ProcessName, muon_p_jetrestf, weight, 100, 0., 10.);

  //FillHist(cutname+"/lepton_jetptratio/"+ProcessName, muon_jetptratio, weight, 100, 0., 2.);
  //FillHist(cutname+"/lepton_jetptrel/"+ProcessName, muon_jetptrel, weight, 100, 0., 50.);

}
void B_Info_Analyzer_BASIC_v2309::FillHistReco_nMuon(){
  TString this_suffix="";
  for(unsigned int i1 = 0 ; i1 < Cat_b_bbar_size; i1++){
    for(unsigned int i2 = 0 ; i2 < Cat_Z_To_mm_ee_size; i2++){
      //for(unsigned int i4 = 0 ; i4 < Cat_1jet20_size; i4++){


      //this_suffix=Cat_b_bbar[i1]+Cat_Z_To_mm_ee[i2]+Cat_1jet20[i4];
      this_suffix=Cat_b_bbar[i1]+Cat_Z_To_mm_ee[i2];
	//--Check category condition
	if((i1==1)&&(myLHE.evt_nb!=1)) continue; //if not bevent, skip
	if((i1==2)&&(myLHE.evt_nb!=-1)) continue; //if not bbarevent, skip
	
	if((i2==1)&&(!myLHE.is_mumu)) continue; //if not mumu, skip
	if((i2==2)&&(!myLHE.is_ee)) continue; //if not ee, skip
	
	//if((i4==1)&&(!oneCleanJet20Event || !BmatJet20Event)) continue; //if not 1cleanjet20 OR not bmatjetpt>20
	
	//--Fill
	FillHist("Lepton"+this_suffix+"/nmuon/"+ProcessName, nmuon, weight, 10, 0., 10.);
	FillHist("LeptonInBmatJet"+this_suffix+"/nmuon/"+ProcessName, nmuon_InBmatjet, weight, 10, 0., 10.);
	FillHist("LeptonOutOfBmatJet"+this_suffix+"/nmuon/"+ProcessName, nmuon_OutOfBmatjet, weight, 10, 0., 10.);
	FillHist("LeptonpTatJetRF2"+this_suffix+"/nmuon/"+ProcessName, nmuon_p_jetrestf2, weight, 10, 0., 10.);
	FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/nmuon/"+ProcessName, nmuon_InBmatjet_p_jetrestf2, weight, 10, 0., 10.);
	
	FillHist("Lepton"+this_suffix+"/nmuon_p/"+ProcessName, nmuon_p, weight, 10, 0., 10.);
	FillHist("LeptonInBmatJet"+this_suffix+"/nmuon_p/"+ProcessName, nmuon_p_InBmatjet, weight, 10, 0., 10.);
	FillHist("LeptonOutOfBmatJet"+this_suffix+"/nmuon_p/"+ProcessName, nmuon_p_OutOfBmatjet, weight, 10, 0., 10.);
	FillHist("LeptonpTatJetRF2"+this_suffix+"/nmuon_p/"+ProcessName, nmuon_p_p_jetrestf2, weight, 10, 0., 10.);
	FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/nmuon_p/"+ProcessName, nmuon_p_InBmatjet_p_jetrestf2, weight, 10, 0., 10.);	

	FillHist("Lepton"+this_suffix+"/nmuon_n/"+ProcessName, nmuon_n, weight, 10, 0., 10.);
	FillHist("LeptonInBmatJet"+this_suffix+"/nmuon_n/"+ProcessName, nmuon_n_InBmatjet, weight, 10, 0., 10.);
	FillHist("LeptonOutOfBmatJet"+this_suffix+"/nmuon_n/"+ProcessName, nmuon_n_OutOfBmatjet, weight, 10, 0., 10.);
	FillHist("LeptonpTatJetRF2"+this_suffix+"/nmuon_n/"+ProcessName, nmuon_n_p_jetrestf2, weight, 10, 0., 10.);
	FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/nmuon_n/"+ProcessName, nmuon_n_InBmatjet_p_jetrestf2, weight, 10, 0., 10.);		
	//--muonchargesum
	FillHist("Lepton"+this_suffix+"/muon_chargesum/"+ProcessName, nmuon_p-nmuon_n, weight, 20, -10., 10.);
	FillHist("LeptonInBmatJet"+this_suffix+"/muon_chargesum/"+ProcessName, nmuon_p_InBmatjet-nmuon_n_InBmatjet, weight, 20, -10., 10.);
	FillHist("LeptonOutOfBmatJet"+this_suffix+"/nmuon_chargesum/"+ProcessName, nmuon_p_OutOfBmatjet-nmuon_n_OutOfBmatjet, weight, 20, -10., 10.);
	FillHist("LeptonpTatJetRF2"+this_suffix+"/nmuon_chargesum/"+ProcessName, nmuon_p_p_jetrestf2-nmuon_n_p_jetrestf2, weight, 20, -10., 10.);
	FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/nmuon_chargesum/"+ProcessName, nmuon_p_InBmatjet_p_jetrestf2-nmuon_n_InBmatjet_p_jetrestf2, weight, 20, -10., 10.);
	
	// } //[END]loop 1cleanjet event 1 bmatjet event             
    }//[END]loop cat_ztommee
  }//[END]loop cat bbbar
}

void B_Info_Analyzer_BASIC_v2309::FillHistSetRecoElectron(TString cutname){
  TString this_suffix="";
  for(unsigned int i1 = 0 ; i1 < Cat_b_bbar_size; i1++){
    for(unsigned int i2 = 0 ; i2 < Cat_Z_To_mm_ee_size; i2++){
      for(unsigned int i3 = 0 ; i3 < Cat_lepton_charge_size; i3++){
	//for(unsigned int i4 = 0 ; i4 < Cat_1jet20_size; i4++){
	  for(unsigned int i5 = 0 ; i5 < Cat_pTatJetRF2_size; i5++){
	    //this_suffix=Cat_b_bbar[i1]+Cat_Z_To_mm_ee[i2]+Cat_lepton_charge[i3]+Cat_1jet20[i4]+Cat_pTatJetRF2[i5];
	    this_suffix=Cat_b_bbar[i1]+Cat_Z_To_mm_ee[i2]+Cat_lepton_charge[i3]+Cat_pTatJetRF2[i5];
	    //--Check category condition
	    if((i1==1)&&(myLHE.evt_nb!=1)) continue; //if not bevent, skip
	    if((i1==2)&&(myLHE.evt_nb!=-1)) continue; //if not bbarevent, skip
	    
	    if((i2==1)&&(!myLHE.is_mumu)) continue; //if not mumu, skip
	    if((i2==2)&&(!myLHE.is_ee)) continue; //if not ee, skip
	    
	    if((i3==1)&&(electron_charge < 0)) continue; //if not positive electron, skip
	    if((i3==2)&&(electron_charge > 0)) continue; //if not negative electron, skip
	    
	    //if((i4==1)&&(!oneCleanJet20Event || !BmatJet20Event)) continue; //if not 1cleanjet20 OR not bmatjetpt>20
	    if((i5==1)&&(electron_p_jetrestf>2)) continue;
	    //--Fill
	    FillHistRecoElectron(cutname+this_suffix);
	    //}
	}
      }
    }
  } 
  
}


void B_Info_Analyzer_BASIC_v2309::FillHistRecoElectron(TString cutname){
  //cout << "electron_dR_bmatj" << electron_dR_bmatj << endl;
  //electron
  FillHist(cutname+"/electron_pt/"+ProcessName, electron_pt, weight, 100, 0., 100.);
  FillHist(cutname+"/electron_eta/"+ProcessName, electron_eta, weight, 100, -5., 5.);
  FillHist(cutname+"/electron_phi/"+ProcessName, electron_phi, weight, 100, -4., 4.);

  FillHist(cutname+"/electron_dxy/"+ProcessName, electron_dxy, weight, 100, -2., 2.);
  FillHist(cutname+"/electron_dz/"+ProcessName, electron_dz, weight, 100, -40., 40.);
  FillHist(cutname+"/electron_ip3d/"+ProcessName, electron_ip3d, weight, 100, -40., 40.);
  FillHist(cutname+"/electron_nsip3d/"+ProcessName, electron_nsip3d, weight, 100, 0., 10.);
  FillHist(cutname+"/electron_reliso/"+ProcessName, electron_reliso, weight, 100, 0., 5.);
  FillHist(cutname+"/electron_reliso_zoom/"+ProcessName, electron_reliso, weight, 100, 0., 0.3);
  FillHist(cutname+"/electron_relecalPFClusterIso/"+ProcessName, electron_relecalPFClusterIso, weight, 100, 0., 5);
  FillHist(cutname+"/electron_relecalPFClusterIso_zoom/"+ProcessName, electron_relecalPFClusterIso, weight, 100, 0., 0.5);
  FillHist(cutname+"/electron_charge/"+ProcessName, electron_charge, weight, 4, -2., 2.);

  FillHist(cutname+"/electron_dR_bmatj/"+ProcessName, electron_dR_bmatj, weight, 100, 0., 5.);
  FillHist(cutname+"/electron_psin_bmatj/"+ProcessName, electron_psin_bmatj, weight, 100, 0., 10.);
  FillHist(cutname+"/electron_p_jetrestf/"+ProcessName, electron_p_jetrestf, weight, 100, 0., 10.);
  FillHist(cutname+"/electron_ptratio_bmatj/"+ProcessName, electron_ptratio_bmatj, weight, 100, 0., 2.);
  //FillHist(cutname+"/electron_jetptratio/"+ProcessName, electron_jetptratio, weight, 100, 0., 2.);
  //FillHist(cutname+"/electron_jetptrel/"+ProcessName, electron_jetptrel, weight, 100, 0., 50.);

  FillHist(cutname+"/electron_IsGsfCtfScPixChargeConsistent/"+ProcessName, electron_IsGsfCtfScPixChargeConsistent, weight, 4, -1., 3.);

  //it is a lepton as well
  FillHist(cutname+"/lepton_pt/"+ProcessName, electron_pt, weight, 100, 0., 100.);
  FillHist(cutname+"/lepton_eta/"+ProcessName, electron_eta, weight, 100, -5., 5.);
  FillHist(cutname+"/lepton_phi/"+ProcessName, electron_phi, weight, 100, -4., 4.);

  FillHist(cutname+"/lepton_dxy/"+ProcessName, electron_dxy, weight, 100, -2., 2.);
  FillHist(cutname+"/lepton_dz/"+ProcessName, electron_dz, weight, 100, -40., 40.);
  FillHist(cutname+"/lepton_ip3d/"+ProcessName, electron_ip3d, weight, 100, -40., 40.);
  FillHist(cutname+"/lepton_nsip3d/"+ProcessName, electron_nsip3d, weight, 100, 0., 10.);
  FillHist(cutname+"/lepton_reliso/"+ProcessName, electron_reliso, weight, 100, 0., 5.);
  FillHist(cutname+"/lepton_reliso_zoom/"+ProcessName, electron_reliso, weight, 100, 0., 0.3);
  FillHist(cutname+"/lepton_charge/"+ProcessName, electron_charge, weight, 4, -2., 2.);

  FillHist(cutname+"/lepton_psin_bmatj/"+ProcessName, electron_psin_bmatj, weight, 100, 0., 10.);
  FillHist(cutname+"/lepton_dR_bmatj/"+ProcessName, electron_dR_bmatj, weight, 100, 0., 5.);
  FillHist(cutname+"/lepton_ptratio_bmatj/"+ProcessName, electron_ptratio_bmatj, weight, 100, 0., 2.);
  FillHist(cutname+"/lepton_p_jetrestf/"+ProcessName, electron_p_jetrestf, weight, 100, 0., 10.);

  //FillHist(cutname+"/lepton_jetptratio/"+ProcessName, electron_jetptratio, weight, 100, 0., 2.);
  //FillHist(cutname+"/lepton_jetptrel/"+ProcessName, electron_jetptrel, weight, 100, 0., 50.);

}

void B_Info_Analyzer_BASIC_v2309::FillHistReco_nElectron(){
  TString this_suffix="";
  for(unsigned int i1 = 0 ; i1 < Cat_b_bbar_size; i1++){
    for(unsigned int i2 = 0 ; i2 < Cat_Z_To_mm_ee_size; i2++){
      //for(unsigned int i4 = 0 ; i4 < Cat_1jet20_size; i4++){
      //this_suffix=Cat_b_bbar[i1]+Cat_Z_To_mm_ee[i2]+Cat_1jet20[i4];
      this_suffix=Cat_b_bbar[i1]+Cat_Z_To_mm_ee[i2];
	//--Check category condition
	if((i1==1)&&(myLHE.evt_nb!=1)) continue; //if not bevent, skip
	if((i1==2)&&(myLHE.evt_nb!=-1)) continue; //if not bbarevent, skip
	
	if((i2==1)&&(!myLHE.is_mumu)) continue; //if not mumu, skip
	if((i2==2)&&(!myLHE.is_ee)) continue; //if not ee, skip
	
	//if((i4==1)&&(!oneCleanJet20Event || !BmatJet20Event)) continue; //if not 1cleanjet20 OR not bmatjetpt>20
	


	//--Fill
        FillHist("Lepton"+this_suffix+"/nelectron/"+ProcessName, nelectron, weight, 10, 0., 10.);
        FillHist("LeptonInBmatJet"+this_suffix+"/nelectron/"+ProcessName, nelectron_InBmatjet, weight, 10, 0., 10.);
        FillHist("LeptonOutOfBmatJet"+this_suffix+"/nelectron/"+ProcessName, nelectron_OutOfBmatjet, weight, 10, 0., 10.);
        FillHist("LeptonpTatJetRF2"+this_suffix+"/nelectron/"+ProcessName, nelectron_p_jetrestf2, weight, 10, 0., 10.);
        FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/nelectron/"+ProcessName, nelectron_InBmatjet_p_jetrestf2, weight, 10, 0., 10.);

        FillHist("Lepton"+this_suffix+"/nelectron_p/"+ProcessName, nelectron_p, weight, 10, 0., 10.);
        FillHist("LeptonInBmatJet"+this_suffix+"/nelectron_p/"+ProcessName, nelectron_p_InBmatjet, weight, 10, 0., 10.);
        FillHist("LeptonOutOfBmatJet"+this_suffix+"/nelectron_p/"+ProcessName, nelectron_p_OutOfBmatjet, weight, 10, 0., 10.);
        FillHist("LeptonpTatJetRF2"+this_suffix+"/nelectron_p/"+ProcessName, nelectron_p_p_jetrestf2, weight, 10, 0., 10.);
        FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/nelectron_p/"+ProcessName, nelectron_p_InBmatjet_p_jetrestf2, weight, 10, 0., 10.);

        FillHist("Lepton"+this_suffix+"/nelectron_n/"+ProcessName, nelectron_n, weight, 10, 0., 10.);
        FillHist("LeptonInBmatJet"+this_suffix+"/nelectron_n/"+ProcessName, nelectron_n_InBmatjet, weight, 10, 0., 10.);
        FillHist("LeptonOutOfBmatJet"+this_suffix+"/nelectron_n/"+ProcessName, nelectron_n_OutOfBmatjet, weight, 10, 0., 10.);
        FillHist("LeptonpTatJetRF2"+this_suffix+"/nelectron_n/"+ProcessName, nelectron_n_p_jetrestf2, weight, 10, 0., 10.);
        FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/nelectron_n/"+ProcessName, nelectron_n_InBmatjet_p_jetrestf2, weight, 10, 0., 10.);
        //--electronchargesum                                                                                                                                     
        FillHist("Lepton"+this_suffix+"/electron_chargesum/"+ProcessName, nelectron_p-nelectron_n, weight, 20, -10., 10.);
        FillHist("LeptonInBmatJet"+this_suffix+"/electron_chargesum/"+ProcessName, nelectron_p_InBmatjet-nelectron_n_InBmatjet, weight, 20, -10., 10.);
        FillHist("LeptonOutOfBmatJet"+this_suffix+"/nelectron_chargesum/"+ProcessName, nelectron_p_OutOfBmatjet-nelectron_n_OutOfBmatjet, weight, 20, -10., 10.);
        FillHist("LeptonpTatJetRF2"+this_suffix+"/nelectron_chargesum/"+ProcessName, nelectron_p_p_jetrestf2-nelectron_n_p_jetrestf2, weight, 20, -10., 10.);
        FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/nelectron_chargesum/"+ProcessName, nelectron_p_InBmatjet_p_jetrestf2-nelectron_n_InBmatjet_p_jetrestf2, weight , 20, -10., 10.);

	
	//}//[END] 1cleanjet event 1bmatjet
      
    }//[END]loop cat_ztoee mm
  }//[END]loop cat bbbar
}


void B_Info_Analyzer_BASIC_v2309::FillHistReco_nLepton(){
  TString this_suffix="";
  for(unsigned int i1 = 0 ; i1 < Cat_b_bbar_size; i1++){
    for(unsigned int i2 = 0 ; i2 < Cat_Z_To_mm_ee_size; i2++){
      //for(unsigned int i4 = 0 ; i4 < Cat_1jet20_size; i4++){
	
      //this_suffix=Cat_b_bbar[i1]+Cat_Z_To_mm_ee[i2]+Cat_1jet20[i4];
      this_suffix=Cat_b_bbar[i1]+Cat_Z_To_mm_ee[i2];
	//--Check category condition
	if((i1==1)&&(myLHE.evt_nb!=1)) continue; //if not bevent, skip
	if((i1==2)&&(myLHE.evt_nb!=-1)) continue; //if not bbarevent, skip
	
	if((i2==1)&&(!myLHE.is_mumu)) continue; //if not mumu, skip
	if((i2==2)&&(!myLHE.is_ee)) continue; //if not ee, skip
	
	//if((i4==1)&&(!oneCleanJet20Event || !BmatJet20Event)) continue; //if not 1cleanjet20 OR not bmatjetpt>20
	//--Fill
	FillHist("Lepton"+this_suffix+"/nlepton/"+ProcessName, nelectron+nmuon, weight, 10, 0., 10.);
	FillHist("LeptonInBmatJet"+this_suffix+"/nlepton/"+ProcessName, nelectron_InBmatjet+nmuon_InBmatjet, weight, 10, 0., 10.);
	FillHist("LeptonOutOfBmatJet"+this_suffix+"/nlepton/"+ProcessName, nelectron_OutOfBmatjet+nmuon_OutOfBmatjet, weight, 10, 0., 10.);
        FillHist("LeptonpTatJetRF2"+this_suffix+"/nlepton/"+ProcessName, nelectron_p_jetrestf2+nmuon_p_jetrestf2, weight, 10, 0., 10.);
        FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/nlepton/"+ProcessName, nelectron_InBmatjet_p_jetrestf2+nmuon_InBmatjet_p_jetrestf2, weight, 10, 0., 10.);


	
	FillHist("Lepton"+this_suffix+"/nlepton_p/"+ProcessName, nelectron_p+nmuon_p, weight, 10, 0., 10.);
	FillHist("LeptonInBmatJet"+this_suffix+"/nlepton_p/"+ProcessName, nelectron_p_InBmatjet+nmuon_p_InBmatjet, weight, 10, 0., 10.);
	FillHist("LeptonOutOfBmatJet"+this_suffix+"/nlepton_p/"+ProcessName, nelectron_p_OutOfBmatjet+nmuon_p_OutOfBmatjet, weight, 10, 0., 10.);
        FillHist("LeptonpTatJetRF2"+this_suffix+"/nlepton_p/"+ProcessName, nelectron_p_p_jetrestf2+nmuon_p_p_jetrestf2, weight, 10, 0., 10.);
        FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/nlepton_p/"+ProcessName, nelectron_p_InBmatjet_p_jetrestf2+nmuon_p_InBmatjet_p_jetrestf2, weight, 10, 0., 10.);
	
	FillHist("Lepton"+this_suffix+"/nlepton_n/"+ProcessName, nelectron_n+nmuon_n, weight, 10, 0., 10.);
	FillHist("LeptonInBmatJet"+this_suffix+"/nlepton_n/"+ProcessName, nelectron_n_InBmatjet+nmuon_n_InBmatjet, weight, 10, 0., 10.);
	FillHist("LeptonOutOfBmatJet"+this_suffix+"/nlepton_n/"+ProcessName, nelectron_n_OutOfBmatjet+nmuon_n_OutOfBmatjet, weight, 10, 0., 10.);
        FillHist("LeptonpTatJetRF2"+this_suffix+"/nlepton_n/"+ProcessName, nelectron_n_p_jetrestf2+nmuon_n_p_jetrestf2, weight, 10, 0., 10.);
        FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/nlepton_n/"+ProcessName, nelectron_n_InBmatjet_p_jetrestf2+nmuon_n_InBmatjet_p_jetrestf2, weight, 10, 0., 10.);
	
	//lepton_chargesum
	FillHist("Lepton"+this_suffix+"/lepton_chargesum/"+ProcessName, nelectron_p+nmuon_p-(nelectron_n+nmuon_n), weight, 20, -10., 10.);
	FillHist("LeptonInBmatJet"+this_suffix+"/lepton_chargesum/"+ProcessName, nelectron_p_InBmatjet+nmuon_p_InBmatjet-(nelectron_n_InBmatjet+nmuon_n_InBmatjet), weight, 20, -10., 10.);
	FillHist("LeptonOutOfBmatJet"+this_suffix+"/lepton_chargesum/"+ProcessName, nelectron_p_OutOfBmatjet+nmuon_p_OutOfBmatjet-(nelectron_n_OutOfBmatjet+nmuon_n_OutOfBmatjet), weight, 20, -10., 10.);
        FillHist("LeptonpTatJetRF2"+this_suffix+"/lepton_chargesum/"+ProcessName, nelectron_p_p_jetrestf2+nmuon_p_p_jetrestf2-(nelectron_n_p_jetrestf2+nmuon_n_p_jetrestf2), weight, 20, -10., 10.);
        FillHist("LeptonInBmatJetpTatJetRF2"+this_suffix+"/lepton_chargesum/"+ProcessName, nelectron_p_InBmatjet_p_jetrestf2+nmuon_p_InBmatjet_p_jetrestf2-(nelectron_n_InBmatjet_p_jetrestf2+nmuon_n_InBmatjet_p_jetrestf2), weight, 20, -10., 10.);

	if (nelectron_InBmatjet_p_jetrestf2+nmuon_InBmatjet_p_jetrestf2>0){
	  FillHist("LeptonInBmatJetpTatJetRF2AtLeastOneLep"+this_suffix+"/lepton_chargesum/"+ProcessName, nelectron_p_InBmatjet_p_jetrestf2+nmuon_p_InBmatjet_p_jetrestf2-(nelectron_n_InBmatjet_p_jetrestf2+nmuon_n_InBmatjet_p_jetrestf2), weight, 20, -10., 10.);

	  FillHist("LeptonInBmatJetpTatJetRF2AtLeastOneLep"+this_suffix+"/lepton_charge_rfptweighted/"+ProcessName, 
		   muon_charge_rfptweighted+electron_charge_rfptweighted,
		   weight, 1000, -100., 100.);

	  FillHist("LeptonInBmatJetpTatJetRF2AtLeastOneLep"+this_suffix+"/lepton_charge_rfpt_dr_weighted/"+ProcessName, 
		   muon_charge_rfpt_dr_weighted+electron_charge_rfpt_dr_weighted,
		   weight, 1000, -100., 100.);
	}
	if (muon_charge_rfpt13weighted+electron_charge_rfpt13weighted!=0){
	  FillHist("LeptonInBmatJetpTatJetRF2AtLeastOneLep"+this_suffix+"/lepton_charge_rfpt13weighted/"+ProcessName, 
		   muon_charge_rfpt13weighted+electron_charge_rfpt13weighted,
		   weight, 1000, -100., 100.);

	  FillHist("LeptonInBmatJetpTatJetRF2AtLeastOneLep"+this_suffix+"/lepton_charge_rfpt13_dr_weighted/"+ProcessName, 
		   muon_charge_rfpt13_dr_weighted+electron_charge_rfpt13_dr_weighted,
		   weight, 1000, -100., 100.);

	  
	}
	//}	//[END] 1cleanjet20_1bmatjet
    }//[END] ztommee cat
  }//[END] cat bbbar cat   
}//[END]function FillHistReco_nLepton







/////---[END]Histogram Sets---/////


void B_Info_Analyzer_BASIC_v2309::AnalyzeLeptons(){


  //(A) muon 



  //---For Muon--//
  nmuon=0,nmuon_InBmatjet=0, nmuon_OutOfBmatjet=0, nmuon_p_jetrestf2=0,nmuon_InBmatjet_p_jetrestf2=0;
  nmuon_p=0,nmuon_p_InBmatjet=0, nmuon_p_OutOfBmatjet=0,nmuon_p_p_jetrestf2=0,nmuon_p_InBmatjet_p_jetrestf2=0;
  nmuon_n=0,nmuon_n_InBmatjet=0, nmuon_n_OutOfBmatjet=0,nmuon_n_p_jetrestf2=0,nmuon_n_InBmatjet_p_jetrestf2=0;
  muon_charge_rfptweighted=0,muon_charge_rfpt_dr_weighted=0;
  muon_charge_rfpt13weighted=0,muon_charge_rfpt13_dr_weighted=0;
  //weighted charge// pt@jetRF*(leptoncharge)

  for(unsigned int i=0; i < muonsize; i++){
    nmuon+=1;
    muon_pt=AllMuons[i].Pt();
    muon_eta=AllMuons[i].Eta();
    muon_phi=AllMuons[i].Phi();

    muon_dxy=AllMuons[i].dXY();
    muon_dz=AllMuons[i].dZ();
    muon_ip3d=AllMuons[i].IP3D();
    muon_nsip3d=fabs(muon_ip3d/AllMuons[i].IP3Derr());
    muon_reliso=AllMuons[i].RelIso();
    muon_reltrkiso=AllMuons[i].TrkIso()/AllMuons[i].Pt(); 
    muon_charge=AllMuons[i].Charge();

    muon_psin_bmatj=AllMuons[i].P()*sin(AllMuons[i].Angle(AllJets[myRECO.ij_B].Vect()));
    //---lepton momentum @ jet rest frame
    TLorentzVector vl(AllMuons[i]);
    vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
    muon_p_jetrestf=vl.P();


    muon_charge>0 ? nmuon_p+=1 : nmuon_n+=1; // count muon+ muon-

    //muon_jetptratio=muon_jetPtRatio->at(i);
    //muon_jetptrel=muon_jetPtRel->at(i);
    muon_dR_bmatj=AllMuons[i].DeltaR(myRECO.vBmatchedJet);   
    muon_ptratio_bmatj=muon_pt/myRECO.vBmatchedJet.Pt();
    //(1)b/bbar event info
    FillHistSetRecoMuon("Lepton");

    //(2) leptons in BmatJet
    if(muon_dR_bmatj<myRECO.dRcut_bmatj_muon){
      FillHistSetRecoMuon("LeptonInBmatJet");
      nmuon_InBmatjet+=1;
      muon_charge>0 ? nmuon_p_InBmatjet+=1 : nmuon_n_InBmatjet+=1; // count muon+ muon-
      if(muon_p_jetrestf<2){//nmuon_p_jetrestf2
	nmuon_InBmatjet_p_jetrestf2+=1;
	if(muon_charge>0){
	  nmuon_p_InBmatjet_p_jetrestf2+=1;
	  muon_charge_rfptweighted+=muon_p_jetrestf;
	  muon_charge_rfpt_dr_weighted+=muon_p_jetrestf/fabs(0.1-muon_dR_bmatj);
	}
	else{
	  nmuon_n_InBmatjet_p_jetrestf2+=1; // count muon+ muon-
	  muon_charge_rfptweighted+= -muon_p_jetrestf;
	  muon_charge_rfpt_dr_weighted+= -muon_p_jetrestf/fabs(0.1-muon_dR_bmatj);
	}
      }// [END]ptatjetrf<2
      if((muon_p_jetrestf<3) && (muon_p_jetrestf>1)){//nmuon_p_jetrestf2
        if(muon_charge>0){
	  muon_charge_rfpt13weighted+=muon_p_jetrestf;
          muon_charge_rfpt13_dr_weighted+=muon_p_jetrestf/fabs(0.1-muon_dR_bmatj);
        }
        else{
          muon_charge_rfptweighted+= -muon_p_jetrestf;
          muon_charge_rfpt_dr_weighted+= -muon_p_jetrestf/fabs(0.1-muon_dR_bmatj);
        }
      
      }//[END]1<ptatjetrf<3
    }//[END if muon in bmatjet]
    //(3) leptons outof BmatJet
    else{
      FillHistSetRecoMuon("LeptonOutOfBmatJet");
      nmuon_OutOfBmatjet+=1;
      muon_charge>0 ? nmuon_p_OutOfBmatjet+=1 : nmuon_n_OutOfBmatjet+=1; // count muon+ muon-
    }//[END if muon in bmatjet]
    if(muon_p_jetrestf<2){//nmuon_p_jetrestf2
      nmuon_p_jetrestf2+=1;
      muon_charge>0 ? nmuon_p_p_jetrestf2+=1 : nmuon_n_p_jetrestf2+=1; // count muon+ muon-
    }
  }//[END] muon loop
  //FillHist For event
  FillHistReco_nMuon();
  
  
  

  

  //(B) electron
  //---For Electron--//
  nelectron=0,nelectron_InBmatjet=0, nelectron_OutOfBmatjet=0,nelectron_p_jetrestf2=0,nelectron_InBmatjet_p_jetrestf2=0;
  nelectron_p=0,nelectron_p_InBmatjet=0, nelectron_p_OutOfBmatjet=0,nelectron_p_p_jetrestf2=0,nelectron_p_InBmatjet_p_jetrestf2=0;
  nelectron_n=0,nelectron_n_InBmatjet=0, nelectron_n_OutOfBmatjet=0,nelectron_n_p_jetrestf2=0,nelectron_n_InBmatjet_p_jetrestf2=0;
  electron_charge_rfptweighted=0,electron_charge_rfpt_dr_weighted=0;
  electron_charge_rfpt13weighted=0,electron_charge_rfpt13_dr_weighted=0;
  for(unsigned int i=0; i < electronsize; i++){
    nelectron+=1;
    electron_pt=AllElectrons[i].Pt();
    electron_eta=AllElectrons[i].Eta();
    electron_phi=AllElectrons[i].Phi();

    electron_dxy=AllElectrons[i].dXY();
    electron_dz=AllElectrons[i].dZ();
    electron_ip3d=AllElectrons[i].IP3D();
    electron_nsip3d=electron_ip3d/AllElectrons[i].IP3Derr();
    electron_reliso=AllElectrons[i].RelIso();
    electron_charge=AllElectrons[i].Charge();

    electron_IsGsfCtfScPixChargeConsistent=AllElectrons[i].IsGsfCtfScPixChargeConsistent();
    electron_psin_bmatj=AllElectrons[i].P()*sin(AllElectrons[i].Angle(AllJets[myRECO.ij_B].Vect()));
    electron_relecalPFClusterIso=AllElectrons[i].ecalPFClusterIso()/electron_pt;

    electron_charge>0 ? nelectron_p+=1 : nelectron_n+=1; // count electron+ electron-

    //electron_jetptratio=electron_jetPtRatio->at(i);
    //electron_jetptrel=electron_jetPtRel->at(i);
    electron_dR_bmatj=AllElectrons[i].DeltaR(myRECO.vBmatchedJet);   
    electron_ptratio_bmatj=electron_pt/myRECO.vBmatchedJet.Pt();
    TLorentzVector vl(AllElectrons[i]);
    vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
    electron_p_jetrestf=vl.P();


    //(1)b/bbar event info
    FillHistSetRecoElectron("Lepton");

    //(2) leptons in BmatJet
    if(electron_dR_bmatj<myRECO.dRcut_bmatj_electron){
      FillHistSetRecoElectron("LeptonInBmatJet");
      nelectron_InBmatjet+=1;
      electron_charge>0 ? nelectron_p_InBmatjet+=1 : nelectron_n_InBmatjet+=1; // count electron+ electron-
      if(electron_p_jetrestf<2){//nelectron_p_jetrestf2
        nelectron_InBmatjet_p_jetrestf2+=1;
        if(electron_charge>0){
	  nelectron_p_InBmatjet_p_jetrestf2+=1;
	  electron_charge_rfptweighted+= electron_p_jetrestf;
	  electron_charge_rfpt_dr_weighted+= electron_p_jetrestf/fabs(1.-electron_dR_bmatj);
	}
	else{
	  nelectron_n_InBmatjet_p_jetrestf2+=1;
	  electron_charge_rfptweighted+= -electron_p_jetrestf;
	  electron_charge_rfpt_dr_weighted+= -electron_p_jetrestf/fabs(1.-electron_dR_bmatj);
	} // count electron+ electron-
      }//[END] pt@restframe<2  
      if((electron_p_jetrestf>1)&&(electron_p_jetrestf<3)){//nelectron_p_jetrestf2
	if(electron_charge>0){
	  electron_charge_rfpt13weighted+= electron_p_jetrestf;
	  electron_charge_rfpt13_dr_weighted+= electron_p_jetrestf/fabs(1.-electron_dR_bmatj);
	}
	else{
	  electron_charge_rfpt13weighted+= -electron_p_jetrestf;
	  electron_charge_rfpt13_dr_weighted+= -electron_p_jetrestf/fabs(1.-electron_dR_bmatj);
	} // count electron+ electron-
      }//[END] pt@restframe 1-3
      
    }//[END if electron in bmatjet]
    //(3) leptons outof BmatJet
    else{
      FillHistSetRecoElectron("LeptonOutOfBmatJet");
      nelectron_OutOfBmatjet+=1;
      electron_charge>0 ? nelectron_p_OutOfBmatjet+=1 : nelectron_n_OutOfBmatjet+=1; // count electron+ electron-
    }//[END if electron outof bmatjet]
    if(electron_p_jetrestf<2){//nelectron_p_jetrestf2
      nelectron_p_jetrestf2+=1;
      electron_charge>0 ? nelectron_p_p_jetrestf2+=1 : nelectron_n_p_jetrestf2+=1; // count electron+ electron-
    }
    
  }//[END] electron loop
  //FillHist For event
  FillHistReco_nElectron();
  
  
  //FillHist For event --lepton
  FillHistReco_nLepton();
}//[END]AnalyzeLeptons
  
  



void B_Info_Analyzer_BASIC_v2309::AnalyzeGEN(){
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
void B_Info_Analyzer_BASIC_v2309::AnalyzeLHE(){
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


void B_Info_Analyzer_BASIC_v2309::FillHistBmatJet(TString cutname){
  FillHist(cutname+"/dRToLHE/"+ProcessName,dRToLHE, weight, 100, 0., 3.);
  FillHist(cutname+"/dRToBhad/"+ProcessName,dRToBhad, weight, 100, 0., 3.);
  FillHist(cutname+"/ptratioToLHE/"+ProcessName,ptratioToLHE, weight, 100, 0., 3.);
  FillHist(cutname+"/ptratioToBhad/"+ProcessName,ptratioToBhad, weight, 100, 0., 3.);
  FillHist(cutname+"/charge_using_lep/"+ProcessName,charge_using_lep, weight, 100, -3., 3.);
  //FillHist(cutname+"/BmatchJet_charge/"+ProcessName,jet_charge->at(myRECO.ij_B), weight, 4, -2., 2.);

}
void B_Info_Analyzer_BASIC_v2309::FillHistJet(TString cutname, unsigned int jidx){
  FillHist(cutname+"/jet_chargedMultiplicity/"+ProcessName,(*jet_chargedMultiplicity)[jidx], weight, 30, 0., 30.);
  FillHist(cutname+"/jet_neutralMultiplicity/"+ProcessName,(*jet_neutralMultiplicity)[jidx], weight, 30, 0., 30.);
  FillHist(cutname+"/jet_pt/"+ProcessName,AllJets[jidx].Pt(), weight, 100, 0., 100.);
  FillHist(cutname+"/jet_eta/"+ProcessName,AllJets[jidx].Eta(), weight, 100, -5., 5.);
  FillHist(cutname+"/jet_charge/"+ProcessName,(*jet_charge)[jidx], weight, 100, -2., 2.);
  FillHist(cutname+"/jet_chargedHadronEnergyFraction/"+ProcessName,(*jet_chargedHadronEnergyFraction)[jidx], weight, 10000, 0., 1.);
  FillHist(cutname+"/jet_neutralHadronEnergyFraction/"+ProcessName,(*jet_neutralHadronEnergyFraction)[jidx], weight, 10000, 0., 1.);
  FillHist(cutname+"/jet_neutralEmEnergyFraction/"+ProcessName,(*jet_neutralEmEnergyFraction)[jidx], weight, 10000, 0., 1.);
  FillHist(cutname+"/jet_chargedEmEnergyFraction/"+ProcessName,(*jet_chargedEmEnergyFraction)[jidx], weight, 10000, 0., 1.);
  FillHist(cutname+"/jet_muonEnergyFraction/"+ProcessName,(*jet_muonEnergyFraction)[jidx], weight, 10000, 0., 1.);

  FillHist(cutname+"/jet_chargedHadronEnergyFraction_zoom/"+ProcessName,(*jet_chargedHadronEnergyFraction)[jidx], weight, 10000, 0., 0.0001);
  FillHist(cutname+"/jet_neutralHadronEnergyFraction_zoom/"+ProcessName,(*jet_neutralHadronEnergyFraction)[jidx], weight, 10000, 0., 0.0001);
  FillHist(cutname+"/jet_neutralEmEnergyFraction_zoom/"+ProcessName,(*jet_neutralEmEnergyFraction)[jidx], weight, 10000, 0., 0.0001);
  FillHist(cutname+"/jet_chargedEmEnergyFraction_zoom/"+ProcessName,(*jet_chargedEmEnergyFraction)[jidx], weight, 10000, 0., 0.0001);
  FillHist(cutname+"/jet_muonEnergyFraction_zoom/"+ProcessName,(*jet_muonEnergyFraction)[jidx], weight, 10000, 0., 0.0001);
  //deep jet
  FillHist(cutname+"/jet_DeepJet/"+ProcessName,(*jet_DeepJet)[jidx], weight, 100, 0., 1.);
  FillHist(cutname+"/jet_DeepJet_CvsL/"+ProcessName,(*jet_DeepJet_CvsL)[jidx], weight, 100, 0., 1.);
  FillHist(cutname+"/jet_DeepJet_CvsB/"+ProcessName,(*jet_DeepJet_CvsB)[jidx], weight, 100, 0., 1.);

  FillHist(cutname+"/jet_DeepCSV/"+ProcessName,(*jet_DeepCSV)[jidx], weight, 100, 0., 1.);
  FillHist(cutname+"/jet_DeepCSV_CvsL/"+ProcessName,(*jet_DeepCSV_CvsL)[jidx], weight, 100, 0., 1.);
  FillHist(cutname+"/jet_DeepCSV_CvsB/"+ProcessName,(*jet_DeepCSV_CvsB)[jidx], weight, 100, 0., 1.);

  //jet gen info
  //jet_partonFlavour
  FillHist(cutname+"/jet_partonFlavour/"+ProcessName,(*jet_partonFlavour)[jidx], weight, 27, -6., 21.);
  //AllJets[ij].GenHFHadronMatcherFlavour()
  FillHist(cutname+"/GenHFHadronMatcherFlavour/"+ProcessName,AllJets[jidx].GenHFHadronMatcherFlavour(), weight, 27, -6., 21.);  
}

void B_Info_Analyzer_BASIC_v2309::AnalyzeBmatJet(){
  //pT ratio /dR between BmatJet and Bhadron || LHE b 
  //for(unsigned int i = 0 ; i < jetsize ; i++){ 
  //  AllJets.at(i).Pt();
  //}
  
  dRToLHE = myRECO.vBmatchedJet.DeltaR(myLHE.vb);
  dRToBhad = myRECO.vBmatchedJet.DeltaR(myGEN.vBhad);
  ptratioToLHE = myRECO.vBmatchedJet.Pt()/myLHE.vb.Pt();
  ptratioToBhad = myRECO.vBmatchedJet.Pt()/myGEN.vBhad.Pt();
  charge_using_lep = (*jet_charge)[myRECO.ij_B];
  if(nmuon_InBmatjet>0){
    charge_using_lep+=(nmuon_p-nmuon_n);
  }
  else if(nelectron_InBmatjet>0){
    charge_using_lep+=(nelectron_p-nelectron_n);
  }
  //[TODO]jet charge/multiplicity...
  
  for(int ij = 0; ij < jetsize; ij++){
    //jet_chargedMultiplicity->at(i), jet_neutralMultiplicity->at(i)
    if(ij==myRECO.ij_B){
      FillHistJet("BmatJet",ij);
      FillHistBmatJet("BmatJet");
      if(oneCleanJet20Event && BmatJet20Event){
	FillHistJet("BmatJet_only1j20_bmat20",ij);
	FillHistBmatJet("BmatJet_only1j20_bmat20");
      }
      //mu/e
      if(myLHE.is_mumu){
	FillHistJet("BmatJet_mm",ij);
	FillHistBmatJet("BmatJet_mm");
	if(oneCleanJet20Event && BmatJet20Event){
	  FillHistJet("BmatJet_mm_only1j20_bmat20",ij);
	  FillHistBmatJet("BmatJet_mm_only1j20_bmat20");
	}
      }
      else if(myLHE.is_ee){
	FillHistJet("BmatJet_ee",ij);
	FillHistBmatJet("BmatJet_ee");
	if(oneCleanJet20Event && BmatJet20Event){
	  FillHistJet("BmatJet_ee_only1j20_bmat20",ij);
	  FillHistBmatJet("BmatJet_ee_only1j20_bmat20");
	}
      }
      //[end] mu/e

      //b event
      if(myLHE.evt_nb==1){
	FillHistJet("BmatJet_b",ij);
	FillHistBmatJet("BmatJet_b");
	if(oneCleanJet20Event && BmatJet20Event){
	  FillHistJet("BmatJet_b_only1j20_bmat20",ij);
	  FillHistBmatJet("BmatJet_b_only1j20_bmat20");
	}
	if(myLHE.is_mumu){
	  FillHistJet("BmatJet_b_mm",ij);
	  FillHistBmatJet("BmatJet_b_mm");
	  if(oneCleanJet20Event && BmatJet20Event){
	    FillHistJet("BmatJet_b_mm_only1j20_bmat20",ij);
	    FillHistBmatJet("BmatJet_b_mm_only1j20_bmat20");
	  }
	}
	else if(myLHE.is_ee){
	  FillHistJet("BmatJet_b_ee",ij);
	  FillHistBmatJet("BmatJet_b_ee");
	  if(oneCleanJet20Event && BmatJet20Event){
	    FillHistJet("BmatJet_b_ee_only1j20_bmat20",ij);
	    FillHistBmatJet("BmatJet_b_ee_only1j20_bmat20");
	  }
	}

      }//[end] b event

      //bbar event
      else if(myLHE.evt_nb==-1){
        FillHistJet("BmatJet_bbar",ij);
        FillHistBmatJet("BmatJet_bbar");
	if(oneCleanJet20Event && BmatJet20Event){
	  FillHistJet("BmatJet_bbar_only1j20_bmat20",ij);
	  FillHistBmatJet("BmatJet_bbar_only1j20_bmat20");
	}
        if(myLHE.is_mumu){
          FillHistJet("BmatJet_bbar_mm",ij);
          FillHistBmatJet("BmatJet_bbar_mm");
	  if(oneCleanJet20Event && BmatJet20Event){
	    FillHistJet("BmatJet_bbar_mm_only1j20_bmat20",ij);
	    FillHistBmatJet("BmatJet_bbar_mm_only1j20_bmat20");
	  }
        }
        else if(myLHE.is_ee){
          FillHistJet("BmatJet_bbar_ee",ij);
          FillHistBmatJet("BmatJet_bbar_ee");
	  if(oneCleanJet20Event && BmatJet20Event){
	    FillHistJet("BmatJet_bbar_ee_only1j20_bmat20",ij);
	    FillHistBmatJet("BmatJet_bbar_ee_only1j20_bmat20");
	  }
        }
	
      }

    }
    else{//other jets
      FillHistJet("NotBmatJet",ij);
      if(oneCleanJet20Event){
	FillHistJet("NotBmatJet_only1j20_bmat20",ij);
      }
      if(myLHE.is_mumu){
	FillHistJet("NotBmatJet_mm",ij);
	FillHistBmatJet("NotBmatJet_mm");
	if(oneCleanJet20Event){
	  FillHistJet("NotBmatJet_mm_only1j20_bmat20",ij);
	}
      }
      else if(myLHE.is_ee){
	FillHistJet("NotBmatJet_ee",ij);
	FillHistBmatJet("NotBmatJet_ee");
	if(oneCleanJet20Event){
	  FillHistJet("NotBmatJet_ee_only1j20_bmat20",ij);
	}
      }

    }
  }//[END for all jets]

}

bool B_Info_Analyzer_BASIC_v2309::IsNotLepton(int i){
  //(1) not matched to LHE lepton
  double dR = 9999.; 
  dR = AllJets[i].DeltaR(LHEs[myLHE.i_lepn]);
  if (dR < 0.4) return false;
  dR = AllJets[i].DeltaR(LHEs[myLHE.i_lepp]);
  if (dR < 0.4) return false;
  
  //(2) not near the most energetic leptons
  if(myLHE.is_mumu && (muonsize>1)){
    dR = AllJets[i].DeltaR(AllMuons[0]);
    if (dR < 0.4) return false;
    dR = AllJets[i].DeltaR(AllMuons[1]);
    if (dR < 0.4) return false;
  }
  if(myLHE.is_ee && (electronsize>1)){
    dR = AllJets[i].DeltaR(AllElectrons[0]);
    if (dR < 0.4) return false;
    dR = AllJets[i].DeltaR(AllElectrons[1]);
    if (dR < 0.4) return false;
  }
  return true;
}

void B_Info_Analyzer_BASIC_v2309::AnalyzeJetInfos(){
  //AllJets
  FillHist("gbToZb/jetsize/"+ProcessName,jetsize,weight, 4, -2., 2.);

  //--Check njets
  int njet20=0;
  int ncleanjet20=0;
  for(unsigned int i = 0; i < jetsize; i++){
    double jetpt=AllJets[i].Pt();
    
    if(jetpt < 20) continue;
    njet20+=1;
    if (!IsNotLepton(i)) continue;//using outgoing LHE lepton and energetic lepton info
    ncleanjet20+=1;

  }
  if (ncleanjet20==1){
    oneCleanJet20Event=true;
  }
  else{
    oneCleanJet20Event=false;
  }

}


void B_Info_Analyzer_BASIC_v2309::AnalyzeRECO(){

  //call muon/electron
  AllMuons=GetAllMuons();
  muonsize = AllMuons.size();
  AllElectrons=GetAllElectrons();
  electronsize = AllElectrons.size();

  //(1) Leptons of bOrbbar event || in BmatJet
  B_Info_Analyzer_BASIC_v2309::AnalyzeLeptons();
  //(2) Bmatjet's pt ratio / dR(Bhadron) / dR(LHE b) 
  B_Info_Analyzer_BASIC_v2309::AnalyzeBmatJet();
  //(3) Additional Jetinfo
  B_Info_Analyzer_BASIC_v2309::AnalyzeJetInfos();
}

void B_Info_Analyzer_BASIC_v2309::executeEvent(){
  doPrint=false;
  weight = 1.;//init event weight
  weight *= MCweight();

  //(1)---Let's tag only events with following process..
  //         g      =====o----- b(or bbar)
  //                     |
  //                     |
  //   b(or bbar)   -----o======     Z
  //
  //[TO DO : using LHE, tag the process]
  myLHE.is_gbToZb = B_Info_Analyzer_BASIC_v2309::Tag_gbToZb(); 
  if(!myLHE.is_gbToZb) return;
  if (!allow_tautau){
    if (myLHE.is_tautau) return;
  }
  FillHist("gbToZb/evt_nb_LHE/"+ProcessName,myLHE.evt_nb,weight, 4, -2., 2.);
  //->For LHE info, tag events with one gluon and one b(bbar)quark 
  // if b event : B_Info_Analyzer_BASIC_v2309::myLHE.evt_nb=1
  // if bbar event : B_Info_Analyzer_BASIC_v2309::myLHE.evt_nb=-1

  //(2)---Get the most energetic B-hadron info. in GEN
  B_Info_Analyzer_BASIC_v2309::Tag_B_Hadron();
  //->For GEN particles 
  //  -> Tag All B hadron and get the most energetic B-hadron info.
  
  //(3)---Check Jet matching to B-hadron
  B_Info_Analyzer_BASIC_v2309::Loop_genBMatchedRecoJet();
  //------DEBUG AREA----//
  if(doDebug){
    //[For Check and Debug]
    cout << "[DEBUG]LHE" << endl;
    for(unsigned int i = 0; i < myLHE.LHEsize;i++){
      cout << setw(5) << i << setw(15) << LHEs.at(i).ID() << setw(15) << LHEs.at(i).Status() << setw(15) << LHEs.at(i).Pt() << setw(15) << LHEs.at(i).Eta() << endl; 
  }
    cout << "[DEBUG]GEN" << endl;
    for(unsigned int i = 0 ; i < myGEN.GENsize;i++){
      cout << setw(5) << i << setw(15) << GENs.at(i).PID() << setw(15) << GENs.at(i).Status() << setw(15) << GENs.at(i).Pt() << setw(15) << GENs.at(i).Eta() << endl; 
    }
    cout << "-Tagged B hadron" << endl;
    if (myGEN.HasBhadron){
      cout << ">Bhad_nb" << setw(15) << myGEN.Bhad_nb << endl;
      cout << ">Bhad_pid" << setw(15) << myGEN.Bhad_pid << endl;
      cout << ">myGEN.Bhad_idx" << setw(15) << myGEN.Bhad_idx << endl;
      int ib= myGEN.Bhad_idx;
      cout << ib << setw(15) << GENs.at(ib).PID() << setw(15) << GENs.at(ib).Status() << setw(15) << GENs.at(ib).Pt() << setw(15) << GENs.at(ib).Eta() << endl;
    }
    else{
      cout << "No B hadron" << endl;
    }
    cout << "[DEBUG]RECOjet" << endl;
    for(unsigned int i = 0; i < jetsize;i++){
      cout << setw(5) << i << setw(15) << AllJets.at(i).Pt() << setw(15) << AllJets.at(i).Eta() << setw(15) << AllJets.at(i).Phi() << setw(15) << endl;
    }
    cout << "-BMatched jet" << endl;
    if (myRECO.HasBmatchedRecoJet){
      cout << "myRECO.ij_B=" << myRECO.ij_B << endl;
      int ib = myRECO.ij_B;
      cout << setw(5) << ib << setw(15) << AllJets.at(ib).Pt() << setw(15) << AllJets.at(ib).Eta() << setw(15) << AllJets.at(ib).Phi() << setw(15) << endl;
    }
    else{
      cout << " No B matched jet" << endl;
    }
  }
  //--[END]DEBUG--
  B_Info_Analyzer_BASIC_v2309::AnalyzeLHE();
  B_Info_Analyzer_BASIC_v2309::AnalyzeGEN();
  if(!myRECO.HasBmatchedRecoJet) return; // if there's no bmatjet->return
  if(!(1==myRECO.nBmatJet)) return;
  B_Info_Analyzer_BASIC_v2309::AnalyzeRECO();


  
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
void B_Info_Analyzer_BASIC_v2309::executeEventFromParameter(AnalyzerParameter param){
  


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
    cout << "[B_Info_Analyzer_BASIC_v2309::executeEventFromParameter] Wrong syst" << endl;
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

    double this_discr = jets.at(ij).GetTaggerResult(JetTagging::DeepCSV);
    //==== No SF
    if( this_discr > mcCorr->GetJetTaggingCutValue(JetTagging::DeepCSV, JetTagging::Medium) ) NBJets_NoSF++;
    //==== 2a
    if( mcCorr->IsBTagged_2a(jtp_DeepCSV_Medium, jets.at(ij)) ) NBJets_WithSF_2a++;

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
      //double this_idsf  = mcCorr->MuonID_SF (param.Muon_ID_SF_Key,  muons.at(i).Eta(), muons.at(i).MiniAODPt());

      //==== If you have iso SF, do below. Here we don't.
      //double this_isosf = mcCorr->MuonISO_SF(param.Muon_ISO_SF_Key, muons.at(i).Eta(), muons.at(i).MiniAODPt());
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



