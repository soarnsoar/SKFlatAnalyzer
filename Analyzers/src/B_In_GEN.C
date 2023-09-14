#include "B_In_GEN.h"

B_In_GEN::B_In_GEN(){

}

void B_In_GEN::initializeAnalyzer(){

  //================================================================
  //====  Example 1
  //====  Dimuon Z-peak events with two muon IDs, with systematics
  //================================================================

  //==== if you use "--userflags RunSyst" with SKFlat.py, HasFlag("RunSyst") will return "true"
  RunSyst = HasFlag("RunSyst");
  cout << "[B_In_GEN::initializeAnalyzer] RunSyst = " << RunSyst << endl;

  //==== Dimuon Z-peak with two muon IDs
  //==== I defined "vector<TString> MuonIDs;" in Analyzers/include/B_In_GEN.h
  MuonIDs = {
    //"POGMedium",
    "POGTight"
  };
  //==== corresponding Muon ID SF Keys for mcCorr->MuonID_SF()
  MuonIDSFKeys = {
    "NUM_MediumID_DEN_TrackerMuons",
    "NUM_TightID_DEN_TrackerMuons",
  };

  //==== At this point, sample informations (e.g., IsDATA, DataStream, MCSample, or DataYear) are all set
  //==== You can define sample-dependent or year-dependent variables here
  //----ProcessName-----//

  if(IsDATA){
    //ProcessName=DataStream;    
    ProcessName="Data";
  }
  else{
    ProcessName=MCSample;
  }
  cout << "[B_In_GEN::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;

  //==== (Example) Year-dependent variables
  //==== I defined "TString IsoMuTriggerName;" and "double TriggerSafePtCut;" in Analyzers/include/B_In_GEN.h 
  //==== IsoMuTriggerName is a year-dependent variable, and you don't want to do "if(Dataer==~~)" for every event (let's save cpu time).
  //==== Then, do it here, which only ran once for each macro

  if(DataYear==2016){
    IsoMuTriggerName = "HLT_IsoMu24_v";
    TriggerSafePtCut = 26.;
  }
  else if(DataYear==2017){
    IsoMuTriggerName = "HLT_IsoMu27_v";
    TriggerSafePtCut = 29.;
  }

  cout << "[B_In_GEN::initializeAnalyzer] IsoMuTriggerName = " << IsoMuTriggerName << endl;
  cout << "[B_In_GEN::initializeAnalyzer TriggerSafePtCut = " << TriggerSafePtCut << endl;

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
  cout << "[B_In_GEN::initializeAnalyzer] RunNewPDF = " << RunNewPDF << endl;
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
  cout << "[B_In_GEN::initializeAnalyzer] RunXSecSyst = " << RunXSecSyst << endl;

}

B_In_GEN::~B_In_GEN(){

  //==== Destructor of this Analyzer

}

void B_In_GEN::executeEvent(){
  doPrint=false;
  double weight = 1.;
  weight *= MCweight();

  //---GEN info---//
  //GetGens
  GENs=GetGens();
  unsigned int GENsize=GENs.size();
  double GEN_px,GEN_py,GEN_pz,GEN_E,GEN_status,GEN_id,GEN_index, GEN_pt,GEN_eta, GEN_phi, GEN_mother, GEN_isLastCopy, GEN_Virtuality;

  unsigned int nb_GEN=0;
  if(doPrint) cout << "========[Start]====" << endl;

  LHEs=GetLHEs();
  unsigned int LHEsize=LHEs.size();
  
  double LHE_px,LHE_py,LHE_pz,LHE_E,LHE_status,LHE_id,LHE_index, LHE_pt,LHE_eta, LHE_phi;
  

  bool doStore = false;
  bool isExotic = false;
  unsigned int nb_LHE=0;
  //-----To Store----//
  double LHE_b_pt, LHE_b_eta,LHE_b_phi, LHE_b_E, LHE_b_pid;
  double GEN_b_pt=-999, GEN_b_eta=-999,GEN_b_phi=-999, GEN_b_E=-999;
  double GEN_B_pt=-999, GEN_B_eta=-999,GEN_B_phi=-999, GEN_B_E=-999, GEN_B_pid=-999;
  double RECO_bj_pt=-999, RECO_bj_eta=-999,RECO_bj_phi=-999, RECO_bj_E=-999,RECO_bj_m=-999, RECO_bj_pid=-999;
  //---[END]To Store---//
  TLorentzVector vb;
  if(doPrint) cout << "LHE_index" << setw(15) << "LHE_id" << setw(15) << "LHE_status" << setw(15) << "LHE_pt" << setw(15) << "LHE_eta" << setw(15) << "LHE_phi" << endl;
  for(unsigned int i =0; i < LHEsize ; i++){
    //LHE_px=LHEs.at(i).Px();
    //LHE_py=LHEs.at(i).Py();
    //LHE_pz=LHEs.at(i).Pz();
    LHE_E=LHEs.at(i).E();
    LHE_status=LHEs.at(i).Status();
    LHE_id=LHEs.at(i).ID();
    //LHE_index=LHEs.at(i).Index();
    LHE_pt=LHEs.at(i).Pt();
    LHE_eta=LHEs.at(i).Eta();
    LHE_phi=LHEs.at(i).Phi();
    

    if(doPrint) cout << i << setw(15) << LHE_id << setw(15) << LHE_status << setw(15) << LHE_pt << setw(15) << LHE_eta << setw(15) << LHE_phi << endl;
    
    if( (1==LHE_status)  && (5==abs(LHE_id))  ){//if outgoing b or bbar
      doStore = true;
      LHE_b_pt = LHE_pt;
      LHE_b_eta = LHE_eta;
      LHE_b_phi = LHE_phi;
      LHE_b_E = LHE_E;
      LHE_b_pid = LHE_id;
      nb_LHE=nb_LHE+1;
    }
  }
  double _dR=10000;
  if(!doStore) return;

  vb.SetPtEtaPhiE(LHE_b_pt,LHE_b_eta,LHE_b_phi,LHE_b_E);
  if(doPrint) cout << "[Print near LHE outgoing b quarkd R<0.4 " << endl;
  double _dRcut=0.8;
  std::vector<int> bquark_index;
  unsigned int nstatus1=0;
  if(doPrint) cout << "GEN_index" << setw(15) << "GEN_id" << setw(15) << "GEN_status" << setw(15) << "GEN_mother" << setw(15) << "GEN_isLastCopy" << setw(15) << "GEN_Virtuality" << setw(15)<< "GEN_pt" << setw(15) << "GEN_eta" << setw(15) << "GEN_phi" << endl;
  for(unsigned int i =0; i < GENsize ; i++){
    _dR=10000;
    GEN_index=GENs.at(i).Index();
    GEN_px=GENs.at(i).Px();
    GEN_py=GENs.at(i).Py();
    GEN_pz=GENs.at(i).Pz();
    GEN_E=GENs.at(i).E();
    GEN_status=GENs.at(i).Status();
    GEN_id=GENs.at(i).PID();
    GEN_mother=GENs.at(i).MotherIndex();
    GEN_isLastCopy=GENs.at(i).isLastCopy();
    GEN_Virtuality = GEN_E*GEN_E - GEN_px*GEN_px - GEN_py*GEN_py - GEN_pz*GEN_pz; 
    //GEN_index=GENs.at(i).Index();
    GEN_eta=GENs.at(i).Eta();
    GEN_phi=GENs.at(i).Phi();
    GEN_pt=GENs.at(i).Pt();
    //if ( (GEN_status == -1) && (abs(GEN_id) == 5)  ){
    //  //doPrint=true;
    //  nb_GEN=nb_GEN+1;
    //}
    _dR = GENs.at(i).DeltaR(vb);

    if(GEN_id==LHE_b_pid){
      GEN_b_pt=GEN_pt;
      GEN_b_eta=GEN_eta;
      GEN_b_phi=GEN_phi;
      GEN_b_E=GEN_E;
    }
    if(
       (GEN_id>500)
       &&
       (GEN_id<600)
       &&
       (GEN_pt>GEN_B_pt)
       ){
      GEN_B_pt=GEN_pt;
      GEN_B_eta=GEN_eta;
      GEN_B_phi=GEN_phi;
      GEN_B_E=GEN_E;
    }
  }//for genparticles
  AllJets = GetAllJets();

  //all recojet
  unsigned int jetsize=AllJets.size();
  double jet_pt=-999., jet_eta=-999., jet_phi =-999, jet_m = -999, jet_E=-999, jet_flavor= -100;
  for( unsigned int ij = 0 ; ij < jetsize; ij++){
    jet_pt = AllJets.at(ij).Pt();
    jet_eta = AllJets.at(ij).Eta();
    jet_phi = AllJets.at(ij).Phi();
    jet_m = AllJets.at(ij).M();
    jet_E = AllJets.at(ij).E();
    jet_flavor = AllJets.at(ij).GenHFHadronMatcherFlavour();
    if(doPrint) cout << ij << setw(15) << jet_pt << setw(15) << jet_eta << setw(15) << jet_phi << setw(15) <<jet_m << setw(15) << jet_flavor << endl;
    if (  (jet_flavor==5)  &&  
	  (RECO_bj_pt>RECO_bj_pt)
	  )
      {
	RECO_bj_pt=jet_pt;
	RECO_bj_eta=jet_eta;
	RECO_bj_phi=jet_phi;
      RECO_bj_m=jet_m;
      RECO_bj_E=jet_E;
      }
  }
  

  //---FillHist--
  FillHist("Nocut/LHE_b_pt/"+ProcessName, LHE_b_pt, weight, 300, 0., 300.); //nbin,xmin,xmax
  FillHist("Nocut/LHE_b_eta/"+ProcessName, LHE_b_eta, weight, 100, -5., 5.); //nbin,xmin,xmax
  FillHist("Nocut/LHE_b_phi/"+ProcessName, LHE_b_phi, weight, 80, -4., 4.); //nbin,xmin,xmax
  FillHist("Nocut/LHE_b_E/"+ProcessName, LHE_b_E, weight, 500, 0., 1000.); //nbin,xmin,xmax

  //set v_genb
  TLorentzVector v_genb;
  v_genb.SetPtEtaPhiE(GEN_b_pt,GEN_b_eta,GEN_b_phi,GEN_b_E);
  double dR_GEN_b=vb.DeltaR(v_genb);


  FillHist("Nocut/dR_GEN_b/"+ProcessName, dR_GEN_b, weight, 100, -1., 3.); //nbin,xmin,xmax
  FillHist("Nocut/GEN_b_pt/"+ProcessName, GEN_b_pt, weight, 300, 0., 300.); //nbin,xmin,xmax
  FillHist("Nocut/GEN_b_pt_over_LHE/"+ProcessName, GEN_b_pt/LHE_b_pt, weight, 50, -1., 2.); //nbin,xmin,xmax
  FillHist("Nocut/GEN_b_eta/"+ProcessName, GEN_b_eta, weight, 100, -5., 5.); //nbin,xmin,xmax
  FillHist("Nocut/GEN_b_phi/"+ProcessName, GEN_b_phi, weight, 80, -4., 4.); //nbin,xmin,xmax
  FillHist("Nocut/GEN_b_E/"+ProcessName, GEN_b_E, weight, 500, 0., 1000.); //nbin,xmin,xmax

  //set v_genB
  TLorentzVector v_genB;
  v_genB.SetPtEtaPhiE(GEN_B_pt,GEN_B_eta,GEN_B_phi,GEN_B_E);
  double dR_GEN_b_GEN_B=-1;
  double dR_GEN_B=-1;
  if (GEN_B_pt>0){
    dR_GEN_B = vb.DeltaR(v_genB);
    dR_GEN_b_GEN_B = v_genb.DeltaR(v_genB);
  }
  FillHist("Nocut/dR_GEN_B/"+ProcessName, dR_GEN_B, weight, 100, -1., 3.); //nbin,xmin,xmax
  FillHist("Nocut/GEN_B_pt/"+ProcessName, GEN_B_pt, weight, 300, 0., 300.); //nbin,xmin,xmax
  FillHist("Nocut/GEN_B_pt_over_LHE/"+ProcessName, GEN_B_pt/LHE_b_pt, weight, 50, -1., 2.); //nbin,xmin,xmax
  FillHist("Nocut/GEN_B_eta/"+ProcessName, GEN_B_eta, weight, 100, -5., 5.); //nbin,xmin,xmax
  FillHist("Nocut/GEN_B_phi/"+ProcessName, GEN_B_phi, weight, 80, -4., 4.); //nbin,xmin,xmax
  FillHist("Nocut/GEN_B_E/"+ProcessName, GEN_B_E, weight, 500, 0., 1000.); //nbin,xmin,xmax

  //set v_recobj
  TLorentzVector v_recobj;
  v_recobj.SetPtEtaPhiE(RECO_bj_pt,RECO_bj_eta,RECO_bj_phi,RECO_bj_E);
  double dR_RECO_bj=-1;
  double dR_RECO_bj_GEN_b=-1;
  double dR_RECO_bj_GEN_B=-1;
  if (RECO_bj_pt>0){
    dR_RECO_bj=vb.DeltaR(v_recobj);
    dR_RECO_bj_GEN_b=v_genb.DeltaR(v_recobj);
    dR_RECO_bj_GEN_B=v_genB.DeltaR(v_recobj);
  }



  FillHist("Nocut/dR_RECO_bj/"+ProcessName, dR_RECO_bj, weight, 100, 0., 3.); //nbin,xmin,xmax
  FillHist("Nocut/RECO_bj_pt/"+ProcessName, RECO_bj_pt, weight, 300, 0., 300.); //nbin,xmin,xmax
  FillHist("Nocut/RECO_bj_pt_over_LHE/"+ProcessName, RECO_bj_pt/LHE_b_pt, weight, 50, -1., 2.); //nbin,xmin,xmax
  FillHist("Nocut/RECO_bj_pt_over_GEN_B/"+ProcessName, RECO_bj_pt/GEN_B_pt, weight, 50, -1., 2.); //nbin,xmin,xmax
  FillHist("Nocut/RECO_bj_eta/"+ProcessName, RECO_bj_eta, weight, 100, -5., 5.); //nbin,xmin,xmax
  FillHist("Nocut/RECO_bj_phi/"+ProcessName, RECO_bj_phi, weight, 80, -4., 4.); //nbin,xmin,xmax
  FillHist("Nocut/RECO_bj_E/"+ProcessName, RECO_bj_E, weight, 500, 0., 1000.); //nbin,xmin,xmax


    /*
    if (
        ((_dR < _dRcut)  && (  (GEN_status==1)  ) )
	){
      nstatus1=nstatus1+1;
    }
    if 	(LHE_b_pid==GEN_id) {
      bquark_index.push_back(GEN_index);
    }
    if (  
	((_dR < _dRcut)  && (  (GEN_status==1) || (GEN_status==2)  ) )
	||
	(LHE_b_pid==GEN_id)
	||
	(std::find(bquark_index.begin(), bquark_index.end(), GEN_mother) != bquark_index.end() )
	  ) 
      {
	if(doPrint) cout << GEN_index << setw(15) << GEN_id << setw(15) << GEN_status << setw(15) << GEN_mother << setw(15) << GEN_isLastCopy << setw(15) << GEN_Virtuality << setw(15)<< GEN_pt << setw(15) << GEN_eta << setw(15) << GEN_phi << endl;
      }
  }

  if (0==nstatus1){// exotic case
    if(doPrint) cout << "[Exotic Case!!!]" << endl;
    isExotic= true;
    for(unsigned int i =0; i < GENsize ; i++){
      _dR=10000;
      GEN_index=GENs.at(i).Index();
      GEN_px=GENs.at(i).Px();
      GEN_py=GENs.at(i).Py();
      GEN_pz=GENs.at(i).Pz();
      GEN_E=GENs.at(i).E();
      GEN_status=GENs.at(i).Status();
      GEN_id=GENs.at(i).PID();
      GEN_mother=GENs.at(i).MotherIndex();
      GEN_isLastCopy=GENs.at(i).isLastCopy();
      GEN_Virtuality = GEN_E*GEN_E - GEN_px*GEN_px - GEN_py*GEN_py - GEN_pz*GEN_pz;
      //GEN_index=GENs.at(i).Index();
      GEN_eta=GENs.at(i).Eta();
      GEN_phi=GENs.at(i).Phi();
      GEN_pt=GENs.at(i).Pt();
      if(doPrint) cout << GEN_index << setw(15) << GEN_id << setw(15) << GEN_status << setw(15) << GEN_mother << setw(15) << GEN_isLastCopy << setw(15) << GEN_Virtuality << setw(15)<< GEN_pt << setw(15) << GEN_eta << setw(15) << GEN_phi << endl;      
    }
  }
  if(doPrint) cout << "========[End]====" << endl;
  isExotic=true;
  if (isExotic){
    if(doPrint) cout << "[looking into recojet]" << endl;
    B_In_GEN::executeExoticEvent();
    
  }
    */
  
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
void B_In_GEN::executeExoticEvent(){
  AllJets = GetAllJets();
  //vector<Jet> AllJets = AllJets;
  unsigned int jetsize=AllJets.size();
  if(doPrint) cout << "[NJets]=" << jetsize << endl;
  double jet_pt=-999., jet_eta=-999., jet_phi =-999, jet_m = -999, jet_flavor= -100;
  if(doPrint) cout << "ij" << setw(15) << "jet_pt" << setw(15) << "jet_eta" << setw(15) << "jet_phi" << setw(15) <<"jet_m" << setw(15) << "jet_flavor" << endl;
  for( unsigned int ij = 0 ; ij < jetsize; ij++){
    jet_pt = AllJets.at(ij).Pt();
    jet_eta = AllJets.at(ij).Eta();
    jet_phi = AllJets.at(ij).Phi();
    
    jet_m = AllJets.at(ij).M();
    jet_flavor = AllJets.at(ij).GenHFHadronMatcherFlavour();
    if(doPrint) cout << ij << setw(15) << jet_pt << setw(15) << jet_eta << setw(15) << jet_phi << setw(15) <<jet_m << setw(15) << jet_flavor << endl;
  }
  //GenHFHadronMatcherFlavour
  

}
void B_In_GEN::executeEventFromParameter(AnalyzerParameter param){
  


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
    cout << "[B_In_GEN::executeEventFromParameter] Wrong syst" << endl;
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



