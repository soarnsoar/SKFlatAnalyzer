#include "B_In_LHE.h"

B_In_LHE::B_In_LHE(){

}

void B_In_LHE::initializeAnalyzer(){

  //================================================================
  //====  Example 1
  //====  Dimuon Z-peak events with two muon IDs, with systematics
  //================================================================

  //==== if you use "--userflags RunSyst" with SKFlat.py, HasFlag("RunSyst") will return "true"
  RunSyst = HasFlag("RunSyst");
  cout << "[B_In_LHE::initializeAnalyzer] RunSyst = " << RunSyst << endl;

  //==== Dimuon Z-peak with two muon IDs
  //==== I defined "vector<TString> MuonIDs;" in Analyzers/include/B_In_LHE.h
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
  cout << "[B_In_LHE::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;

  //==== (Example) Year-dependent variables
  //==== I defined "TString IsoMuTriggerName;" and "double TriggerSafePtCut;" in Analyzers/include/B_In_LHE.h 
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

  cout << "[B_In_LHE::initializeAnalyzer] IsoMuTriggerName = " << IsoMuTriggerName << endl;
  cout << "[B_In_LHE::initializeAnalyzer TriggerSafePtCut = " << TriggerSafePtCut << endl;

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
  cout << "[B_In_LHE::initializeAnalyzer] RunNewPDF = " << RunNewPDF << endl;
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
  cout << "[B_In_LHE::initializeAnalyzer] RunXSecSyst = " << RunXSecSyst << endl;

}

B_In_LHE::~B_In_LHE(){

  //==== Destructor of this Analyzer

}

void B_In_LHE::executeEvent(){

  double weight = 1.;
  weight *= MCweight();

  //---LHE info---//
  LHEs=GetLHEs();
  unsigned int LHEsize=LHEs.size();
  double LHE_px,LHE_py,LHE_pz,LHE_E,LHE_status,LHE_id, LHE_pt,LHE_eta, LHE_phi;
  //int LHE_id, LHE_status;
  bool doStore = false;
  unsigned int nb_LHE=0;
  for(unsigned int i =0; i < LHEsize ; i++){
    LHE_px=LHEs.at(i).Px();
    LHE_py=LHEs.at(i).Py();
    LHE_pz=LHEs.at(i).Pz();
    LHE_E=LHEs.at(i).E();
    LHE_status=LHEs.at(i).Status();
    LHE_id=LHEs.at(i).ID();
    //LHE_index=LHEs.at(i).Index();
    LHE_eta=LHEs.at(i).Eta();
    LHE_phi=LHEs.at(i).Phi();
    if ( (LHE_status == -1) && (abs(LHE_id) == 5)  ){
      //doPrint=true;
      nb_LHE=nb_LHE+1;
    }
      
  }
  if (nb_LHE==1) doStore=true;
  if (doStore){  
    
    //Event Info.
    FillHist("Nocut/Qsclae/"+ProcessName, genWeight_Q, weight, 100, 0., 700.); //nbin,xmin,xmax
    FillHist("Nocut/X1scale/"+ProcessName, genWeight_X1, weight, 500, 0., 1.); //nbin,xmin,xmax
    FillHist("Nocut/X2sclae/"+ProcessName, genWeight_X2, weight, 500, 0., 1.); //nbin,xmin,xmax
    double Q=genWeight_Q;
    double x_b=-1;
    double x_bbar=-1;
    double x_allb=-1;
    double x_g=-1;

    //cout << "=========================" << endl;
    //cout << "index" << setw(15)<< "id" << setw(15)<< "status" << setw(15)<< "px" << setw(15)<< "py" << setw(15)<< "pz" << setw(15)<< "E" << setw(15)<< "eta" << setw(15)<< "phi" << endl;
    // count incoming parton
    unsigned int i_incoming=0;
    for(unsigned int i =0; i < LHEsize ; i++){
      //LHE_px=LHEs.at(i).Px();
      //LHE_py=LHEs.at(i).Py();
      //LHE_pz=LHEs.at(i).Pz();
      //LHE_E=LHEs.at(i).E();
      LHE_status=LHEs.at(i).Status();
      LHE_id=LHEs.at(i).ID();
      //LHE_index=LHEs.at(i).Index();
      LHE_pt=LHEs.at(i).Pt();
      LHE_eta=LHEs.at(i).Eta();
      //LHE_phi=LHEs.at(i).Phi();

      if (LHE_status==-1){//##--incoming parton
	if (LHE_id==5){
	  if (i_incoming==0){
	    FillHist("Nocut/b_Xscale/"+ProcessName, genWeight_X1, weight, 500, 0., 1.); //nbin,xmin,xmax
	    x_b=genWeight_X1;
	    x_allb=genWeight_X1;
	  }
	  else{
	    FillHist("Nocut/b_Xscale/"+ProcessName, genWeight_X2, weight, 500, 0., 1.);
	    x_b=genWeight_X2;
	    x_allb=genWeight_X2;
	  }
	}
	else if (LHE_id==-5){
	  if (i_incoming==0){
	    FillHist("Nocut/bbar_Xscale/"+ProcessName, genWeight_X1, weight, 500, 0., 1.); //nbin,xmin,xmax
	    x_bbar=genWeight_X1;
	    x_allb=genWeight_X1;
	  }
	  else{
	    FillHist("Nocut/bbar_Xscale/"+ProcessName, genWeight_X2, weight, 500, 0., 1.);
	    x_bbar=genWeight_X2;
	    x_allb=genWeight_X2;
	  }
	  
	}
	else if (LHE_id==4){
	  if (i_incoming==0){
	    FillHist("Nocut/c_Xscale/"+ProcessName, genWeight_X1, weight, 500, 0., 1.); //nbin,xmin,xmax
	  }
	  else{
	    FillHist("Nocut/c_Xscale/"+ProcessName, genWeight_X2, weight, 500, 0., 1.);
	  }
	  
	}

	else if (LHE_id==-4){
	  if (i_incoming==0){
	    FillHist("Nocut/cbar_Xscale/"+ProcessName, genWeight_X1, weight, 500, 0., 1.); //nbin,xmin,xmax
	  }
	  else{
	    FillHist("Nocut/cbar_Xscale/"+ProcessName, genWeight_X2, weight, 500, 0., 1.);
	  }
	  
	}
	
	else if (LHE_id==3){
	  if (i_incoming==0){
	    FillHist("Nocut/s_Xscale/"+ProcessName, genWeight_X1, weight, 500, 0., 1.); //nbin,xmin,xmax
	  }
	  else{
	    FillHist("Nocut/s_Xscale/"+ProcessName, genWeight_X2, weight, 500, 0., 1.);
	  }
	}
	else if (LHE_id==-3){
	  if (i_incoming==0){
	    FillHist("Nocut/sbar_Xscale/"+ProcessName, genWeight_X1, weight, 500, 0., 1.); //nbin,xmin,xmax
	  }
	  else{
	    FillHist("Nocut/sbar_Xscale/"+ProcessName, genWeight_X2, weight, 500, 0., 1.);
	  }
	}
	
	else if (LHE_id==2){
	  if (i_incoming==0){
	    FillHist("Nocut/u_Xscale/"+ProcessName, genWeight_X1, weight, 500, 0., 1.); //nbin,xmin,xmax
	  }
	  else{
	    FillHist("Nocut/u_Xscale/"+ProcessName, genWeight_X2, weight, 500, 0., 1.);
	  }
	}
	
	else if (LHE_id==-1){
	  if (i_incoming==0){
	    FillHist("Nocut/dbar_Xscale/"+ProcessName, genWeight_X1, weight, 500, 0., 1.); //nbin,xmin,xmax
	  }
	  else{
	    FillHist("Nocut/dbar_Xscale/"+ProcessName, genWeight_X2, weight, 500, 0., 1.);
	  }
	}
	
	
	else if (LHE_id==1){
	  if (i_incoming==0){
	    FillHist("Nocut/d_Xscale/"+ProcessName, genWeight_X1, weight, 500, 0., 1.); //nbin,xmin,xmax
	  }
	  else{
	    FillHist("Nocut/d_Xscale/"+ProcessName, genWeight_X2, weight, 500, 0., 1.);
	  }
	}

	else if (LHE_id==21){
	  if (i_incoming==0){
	    FillHist("Nocut/g_Xscale/"+ProcessName, genWeight_X1, weight, 500, 0., 1.); //nbin,xmin,xmax
            x_g=genWeight_X1;
	  }
	  else{
	    FillHist("Nocut/g_Xscale/"+ProcessName, genWeight_X2, weight, 500, 0., 1.);
            x_g=genWeight_X2;
	  }
	}
      }
      //cout << LHE_index << setw(15)<< LHE_id << setw(15)<< LHE_status << setw(15)<< LHE_px << setw(15)<< LHE_py << setw(15)<< LHE_pz << setw(15)<< LHE_E << setw(15)<< LHE_eta << setw(15)<< LHE_phi << endl;


      if( (LHE_status==1) && (LHE_id==5) ){
	///--b outgoing
	FillHist("Nocut/b_LHE_pt/"+ProcessName, LHE_pt, weight, 300, 0., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/b_LHE_eta/"+ProcessName, LHE_eta, weight, 100, -5., 5.); //nbin,xmin,xmax        
	FillHist("Nocut/b_LHE_phi/"+ProcessName, LHE_phi, weight, 80, -4., 4.); //nbin,xmin,xmax        
	FillHist("Nocut/b_LHE_px/"+ProcessName, LHE_px, weight, 300, -300., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/b_LHE_py/"+ProcessName, LHE_py, weight, 300, -300., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/b_LHE_pz/"+ProcessName, LHE_pz, weight, 500, -1000., 1000.); //nbin,xmin,xmax        
	FillHist("Nocut/b_LHE_E/"+ProcessName, LHE_E, weight, 500, 0., 1000.); //nbin,xmin,xmax        


	FillHist("Nocut/allb_LHE_pt/"+ProcessName, LHE_pt, weight, 300, 0., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_eta/"+ProcessName, LHE_eta, weight, 100, -5., 5.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_phi/"+ProcessName, LHE_phi, weight, 80, -4., 4.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_px/"+ProcessName, LHE_px, weight, 300, -300., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_py/"+ProcessName, LHE_py, weight, 300, -300., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_pz/"+ProcessName, LHE_pz, weight, 500, -1000., 1000.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_E/"+ProcessName, LHE_E, weight, 500, 0., 1000.); //nbin,xmin,xmax        
	//xb vs b_pt
	FillHist("Nocut/xb_vs_bpt/"+ProcessName, x_b, LHE_pt,  weight, 100, 0, 1 ,100, 0., 1000.); //nbin,xmin,xmax        
	//xb vs b_eta
	FillHist("Nocut/xb_vs_beta/"+ProcessName, x_b, LHE_eta,  weight, 100, 0, 1 ,100, -5., 5.); //nbin,xmin,xmax        

	//xb vs b_pt
	FillHist("Nocut/xallb_vs_bpt/"+ProcessName, x_allb, LHE_pt,  weight, 100, 0, 1 ,100, 0., 1000.); //nbin,xmin,xmax        
	//xb vs b_eta
	FillHist("Nocut/xallb_vs_beta/"+ProcessName, x_allb, LHE_eta,  weight, 100, 0, 1 ,100, -5., 5.); //nbin,xmin,xmax        
	//xb vs xg
	FillHist("Nocut/xallb_vs_xg/"+ProcessName, x_allb, x_g,  weight, 100, 0, 1 ,100, 0., 1.); //nbin,xmin,xmax        

	//Q vs b_pt
	FillHist("Nocut/Q_vs_bpt/"+ProcessName, Q, LHE_pt,  weight, 100, 0, 1000 ,100, 0., 1000.); //nbin,xmin,xmax        
	//Q vs b_eta
	FillHist("Nocut/Q_vs_beta/"+ProcessName, Q, LHE_eta,  weight, 100, 1000, 1 ,100, -5., 5.); //nbin,xmin,xmax        
	//Q vs xg
	FillHist("Nocut/Q_vs_xg/"+ProcessName, Q, x_g,  weight, 100, 0, 1 ,1000, 0., 1.); //nbin,xmin,xmax        

	//Q vs b_pt
	FillHist("Nocut/Q_vs_allbpt/"+ProcessName, Q, LHE_pt,  weight, 100, 0, 1000 ,100, 0., 1000.); //nbin,xmin,xmax        
	//Q vs b_eta
	FillHist("Nocut/Q_vs_allbeta/"+ProcessName, Q, LHE_eta,  weight, 100, 1000, 1 ,100, -5., 5.); //nbin,xmin,xmax        

      }
      if((LHE_status==1) && (LHE_id==-5) ){
      	///--b outgoing
	FillHist("Nocut/bbar_LHE_pt/"+ProcessName, LHE_pt, weight, 300, 0., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/bbar_LHE_eta/"+ProcessName, LHE_eta, weight, 100, -5., 5.); //nbin,xmin,xmax        
	FillHist("Nocut/bbar_LHE_phi/"+ProcessName, LHE_phi, weight, 80, -4., 4.); //nbin,xmin,xmax        
	FillHist("Nocut/bbar_LHE_px/"+ProcessName, LHE_px, weight, 300, -300., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/bbar_LHE_py/"+ProcessName, LHE_py, weight, 300, -300., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/bbar_LHE_pz/"+ProcessName, LHE_pz, weight, 500, -1000., 1000.); //nbin,xmin,xmax        
	FillHist("Nocut/bbar_LHE_E/"+ProcessName, LHE_E, weight, 500, 0., 1000.); //nbin,xmin,xmax        

	FillHist("Nocut/allb_LHE_pt/"+ProcessName, LHE_pt, weight, 300, 0., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_eta/"+ProcessName, LHE_eta, weight, 100, -5., 5.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_phi/"+ProcessName, LHE_phi, weight, 80, -4., 4.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_px/"+ProcessName, LHE_px, weight, 300, -300., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_py/"+ProcessName, LHE_py, weight, 300, -300., 300.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_pz/"+ProcessName, LHE_pz, weight, 500, -1000., 1000.); //nbin,xmin,xmax        
	FillHist("Nocut/allb_LHE_E/"+ProcessName, LHE_E, weight, 500, 0., 1000.); //nbin,xmin,xmax        

	//xbbar vs b_pt
	FillHist("Nocut/xbbar_vs_bbarpt/"+ProcessName, x_bbar, LHE_pt,  weight, 100, 0, 1 ,100, 0., 1000.); //nbin,xmin,xmax        
	//xbbar vs b_eta
	FillHist("Nocut/xbbar_vs_bbareta/"+ProcessName, x_bbar, LHE_eta,  weight, 100, 0, 1 ,100, -5., 5.); //nbin,xmin,xmax        

	//xb vs b_pt
	FillHist("Nocut/xallb_vs_allbpt/"+ProcessName, x_allb, LHE_pt,  weight, 100, 0, 1 ,100, 0., 1000.); //nbin,xmin,xmax        
	//xb vs b_eta
	FillHist("Nocut/xallb_vs_allbeta/"+ProcessName, x_allb, LHE_eta,  weight, 100, 0, 1 ,100, -5., 5.); //nbin,xmin,xmax        
	//xb vs xg
	FillHist("Nocut/xallb_vs_xg/"+ProcessName, x_allb, x_g,  weight, 100, 0, 1 ,100, 0., 1.); //nbin,xmin,xmax        

	//Q vs b_pt
	FillHist("Nocut/Q_vs_bbarpt/"+ProcessName, Q, LHE_pt,  weight, 100, 0, 1000 ,100, 0., 1000.); //nbin,xmin,xmax        
	//Q vs b_eta
	FillHist("Nocut/Q_vs_bbareta/"+ProcessName, Q, LHE_eta,  weight, 100, 0, 1000 ,100, -5., 5.); //nbin,xmin,xmax        
	//Q vs xg
	FillHist("Nocut/Q_vs_xg/"+ProcessName, Q, x_g,  weight, 100, 0, 1000 ,100, 0., 1.); //nbin,xmin,xmax        

	//Q vs b_pt
	FillHist("Nocut/Q_vs_allbpt/"+ProcessName, Q, LHE_pt,  weight, 100, 0, 1000 ,100, 0., 1000.); //nbin,xmin,xmax        
	//Q vs b_eta
	FillHist("Nocut/Q_vs_allbeta/"+ProcessName, Q, LHE_eta,  weight, 100, 0, 1000 ,100, -5., 5.); //nbin,xmin,xmax        

      }
      i_incoming=i_incoming+1;
    }
  }




  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);


}

void B_In_LHE::executeEventFromParameter(AnalyzerParameter param){
  


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
    cout << "[B_In_LHE::executeEventFromParameter] Wrong syst" << endl;
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
  //double btagWeight = mcCorr->GetBTaggingReweight_1a(jets, jtp_DeepCSV_Medium);

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



