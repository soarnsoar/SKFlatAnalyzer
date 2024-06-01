#include "BasicTest.h"

BasicTest::BasicTest(){

}

void BasicTest::initializeAnalyzer(){

  //================================================================
  //====  Example 1
  //====  Dimuon Z-peak events with two muon IDs, with systematics
  //================================================================

  //==== if you use "--userflags RunSyst" with SKFlat.py, HasFlag("RunSyst") will return "true"
  RunSyst = HasFlag("RunSyst");
  cout << "[BasicTest::initializeAnalyzer] RunSyst = " << RunSyst << endl;

  //==== Dimuon Z-peak with two muon IDs
  //==== I defined "vector<TString> MuonIDs;" in Analyzers/include/BasicTest.h
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
  cout << "[BasicTest::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;

  //==== (Example) Year-dependent variables
  //==== I defined "TString IsoMuTriggerName;" and "double TriggerSafePtCut;" in Analyzers/include/BasicTest.h 
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

  cout << "[BasicTest::initializeAnalyzer] IsoMuTriggerName = " << IsoMuTriggerName << endl;
  cout << "[BasicTest::initializeAnalyzer TriggerSafePtCut = " << TriggerSafePtCut << endl;

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
  cout << "[BasicTest::initializeAnalyzer] RunNewPDF = " << RunNewPDF << endl;
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
  cout << "[BasicTest::initializeAnalyzer] RunXSecSyst = " << RunXSecSyst << endl;
  
  //TString xmlpath=(TString)getenv("DATA_DIR")+"/"+DataEra+"/TMVA/ChargeScore/v2405.2/muon/muon2017__3__50__100__0.1_DNN.weights.xml";
  //cout << xmlpath << endl;
  //TString xmlpath=(TString)getenv("DATA_DIR")+"2017/TMVA/old/LepJetChargeReliability/aMCatNLO/muon/TMVAClassification_DNN.weights.xml"
  //xmlfile test
  //  TMVATool *myScoreTool=new TMVATool(xmlpath);
  ChargeScoreTool *muonscoretool=new ChargeScoreTool("2405.2","muon",DataEra);

}

BasicTest::~BasicTest(){

  //==== Destructor of this Analyzer

}

void BasicTest::executeEvent(){
  /*
  vector<Electron> this_AllElectrons = GetAllElectrons();


  for(auto &electron : this_AllElectrons){
    cout << "---" << endl;
    cout << "electron.InvEminusInvP()=" << electron.InvEminusInvP() << endl;
    double scE=electron.scE();
    double E=electron.E();
    double P=electron.P();

    double uncorrE=electron.UncorrE();
    double uncorrP=electron.P()*uncorrE/E;
    double uncorrP_bySC=electron.P()*scE/E;
    TLorentzVector mygsf;
    //electron_gsfpt = 0;
    //electron_gsfEta = 0;
    //electron_gsfPhi
    
    cout << "1/E - 1/P=" << (P-E)/(E*P) << endl;
    cout << "1/E - 1/uncorrP_bySC=" << (uncorrP_bySC-E)/(E*uncorrP_bySC) << endl;
    cout << "1/E - 1/uncorrP=" << (uncorrP-E)/(E*uncorrP) << endl;


    cout << "1/uncorrE - 1/P=" << (P-uncorrE)/(uncorrE*P) << endl;
    cout << "1/uncorrE - 1/uncorrP=" << (uncorrP-uncorrE)/(uncorrE*uncorrP) << endl;
    cout << "1/uncorrE - 1/uncorrP_bySC=" << (uncorrP_bySC-uncorrE)/(uncorrE*uncorrP_bySC) << endl;

    cout << "1/scE - 1/uncorrP=" << (uncorrP-scE)/(scE*uncorrP) << endl;
    cout << "1/scE - 1/uncorrP_bySC=" << (uncorrP_bySC-scE)/(scE*uncorrP_bySC) << endl;
    cout << "1/scE - 1/P=" << (P-scE)/(scE*P) << endl;


  }
  */
  /*
  for(unsigned int i=0; i<electron_Energy->size(); i++){
    double InvEminusInvP=electron_InvEminusInvP->at(i);
    cout << "---" << endl;
    cout << "InvEminusInvP=" << InvEminusInvP << endl;

    double E=electron_Energy->at(i);
    TLorentzVector this_gsf;
    this_gsf.SetPtEtaPhiM(electron_gsfpt->at(i),electron_gsfEta->at(i),electron_gsfPhi->at(i),0);
    double Pgsf=this_gsf.P();

    TLorentzVector el;
    el.SetPtEtaPhiE(1., electron_eta->at(i), electron_phi->at(i), electron_Energy->at(i));
    double el_theta = el.Theta();
    double el_et = electron_Energy->at(i) * TMath::Sin( el_theta );
    double el_pt = sqrt(el_et*el_et - 0.512*0.512);
    el.SetPtEtaPhiE( el_pt, electron_eta->at(i), electron_phi->at(i), electron_Energy->at(i));

    double P=el.P();
    double scE=electron_scEnergy->at(i);
    double uncorrE=electron_EnergyUnCorr->at(i);
    double scRawEnergy=electron_scRawEnergy->at(i);
    TLorentzVector sc;
    sc.SetPtEtaPhiE(1,electron_scEta->at(i),electron_scPhi->at(i),scE);
    double scEt=electron_scEt->at(i);
    double scPt=sqrt(scEt*scEt - 0.512*0.512);
    sc.SetPtEtaPhiE(scPt,electron_scEta->at(i),electron_scPhi->at(i),scE);
    

    cout << "1/E-1/P=" << 1./E-1/P << endl;
    cout << "1/E-1/Pgsf=" << 1./E-1/Pgsf << endl;

    cout << "1/scE-1/P=" << 1./scE-1/P << endl;
    cout << "1/scE-1/Pgsf=" << 1./scE-1/Pgsf << endl;

    cout << "1/uncorrE-1/P=" << 1./uncorrE-1/P << endl;
    cout << "1/uncorrE-1/Pgsf=" << 1./uncorrE-1/Pgsf << endl;

    double eOverP=electron_eOverP->at(i);
    cout << "eOverP=" << eOverP << endl;
    cout << "E/P=" << E/P << endl;
    cout << "E/Pgsf=" << E/Pgsf << endl;
   
    cout << "scE/P=" << scE/P << endl;
    cout << "scE/Pgsf=" << scE/Pgsf << endl;

    cout << "uncorrE/P=" << uncorrE/P << endl;
    cout << "uncorrE/Pgsf=" << uncorrE/Pgsf << endl;

    //mimic cmssw //https://github.com/cms-sw/cmssw/blob/CMSSW_9_4_X/RecoEgamma/ElectronIdentification/plugins/cuts/GsfEleEInverseMinusPInverseCut.cc#L43-L45
    double inverse_E=1/E;
    double inverse_scRawEnergy=1/scRawEnergy;
    double inverse_scE=1/scE;
    double inverse_uncorrE=1/uncorrE;
    cout << "(1-eOverP)*inverse_E=" << (1.0-eOverP)*inverse_E << endl;
    cout << "(1-eOverP)*inverse_scE=" << (1.0-eOverP)*inverse_scE << endl;
    cout << "(1-eOverP)*inverse_scRawEnergy=" << (1.0-eOverP)*inverse_scRawEnergy << endl;
    cout << "(1-eOverP)*inverse_uncorrE=" << (1.0-eOverP)*inverse_uncorrE << endl;
    double diff = (1.0-eOverP)*inverse_scE - (1.0-eOverP)*inverse_uncorrE;
    double ratio=diff/((1-eOverP)*inverse_uncorrE);
    if (ratio > 0.3 && InvEminusInvP < 1000.){
      cout << "!!diff over 30%!!!!" << endl;
    } 
  }
  */

  //GetDileptonTriggerSF
  //double AnalyzerCore::GetDileptonTriggerSF(TString triggerSF_key0,TString triggerSF_key1,TString DZSF,const vector<Lepton*>& leps,int set,int mem,TString option)
  //MakeLeptonPointerVector()
  vector<Muon> AllMuons = GetAllMuons();
  if (AllMuons.size()<2) return;
  vector<Lepton*> leps=MakeLeptonPointerVector(AllMuons);
  //double triggersf=GetDileptonTriggerSF("Mu17Leg1_MediumID_trkIsoLoose","Mu8Leg2_MediumID_trkIsoLoose","DZ_MediumID_trkIsoLoose",leps,0,0);
  //cout << "triggersf=" << triggersf << endl;
  //---LHE info---//
  LHEs=GetLHEs();
  unsigned int LHEsize=LHEs.size();
  double LHE_px,LHE_py,LHE_pz,LHE_E,LHE_status,LHE_id,LHE_index, LHE_eta, LHE_phi;

  bool doPrint = false;
  unsigned int nb_LHE=0;
  for(unsigned int i =0; i < LHEsize ; i++){
    LHE_px=LHEs.at(i).Px();
    LHE_py=LHEs.at(i).Py();
    LHE_pz=LHEs.at(i).Pz();
    LHE_E=LHEs.at(i).E();
    LHE_status=LHEs.at(i).Status();
    LHE_id=LHEs.at(i).ID();
    LHE_index=LHEs.at(i).Index();
    LHE_eta=LHEs.at(i).Eta();
    LHE_phi=LHEs.at(i).Phi();
    if ( (LHE_status == -1) && (abs(LHE_id) == 5)  ){
      //doPrint=true;
      nb_LHE=nb_LHE+1;
    }
      
  }
  if (nb_LHE==1) doPrint=true;
  if (doPrint){  
    cout << "=========================" << endl;
    cout << "index" << setw(15)<< "id" << setw(15)<< "status" << setw(15)<< "px" << setw(15)<< "py" << setw(15)<< "pz" << setw(15)<< "E" << setw(15)<< "eta" << setw(15)<< "phi" << endl;
    for(unsigned int i =0; i < LHEsize ; i++){
      LHE_px=LHEs.at(i).Px();
      LHE_py=LHEs.at(i).Py();
      LHE_pz=LHEs.at(i).Pz();
      LHE_E=LHEs.at(i).E();
      LHE_status=LHEs.at(i).Status();
      LHE_id=LHEs.at(i).ID();
      LHE_index=LHEs.at(i).Index();
      LHE_eta=LHEs.at(i).Eta();
      LHE_phi=LHEs.at(i).Phi();
      cout << LHE_index << setw(15)<< LHE_id << setw(15)<< LHE_status << setw(15)<< LHE_px << setw(15)<< LHE_py << setw(15)<< LHE_pz << setw(15)<< LHE_E << setw(15)<< LHE_eta << setw(15)<< LHE_phi << endl;
    }
  }
  //================================================================
  //====  Example 1
  //====  Dimuon Z-peak events with two muon IDs, with systematics
  //================================================================

  //==== *IMPORTANT TO SAVE CPU TIME*
  //==== Every GetMuon() funtion first collect ALL MINIAOD muons with GetAllMuons(),
  //==== and then check ID booleans.
  //==== GetAllMuons not only loops over all MINIAOD muons, but also actually CONSTRUCT muon objects for each muons.
  //==== We are now running systematics, and you don't want to do this for every systematic sources
  //==== So, I defined "vector<Muon> AllMuons;" in Analyzers/include/BasicTest.h,
  //==== and save muons objects at the very beginning of executeEvent().
  //==== Later, do "SelectMuons(AllMuons, ID, pt, eta)" to get muons with ID cuts
  AllMuons = GetAllMuons();
  //=== Jets too
  vector<Jet> AllJets = GetAllJets();

  //==== Get L1Prefire reweight
  //==== If data, 1.;
  //==== If MC && DataYear > 2017, 1.;
  //==== If MC && DataYear <= 2017, we have to reweight the event with this value
  //==== I defined "double weight_Prefire;" in Analyzers/include/BasicTest.h
  weight_Prefire = GetPrefireWeight(0);

  //==== Declare AnalyzerParameter

  AnalyzerParameter param;

  //==== Loop over muon IDs

  for(unsigned int it_MuonID=0; it_MuonID<MuonIDs.size(); it_MuonID++){

    TString MuonID = MuonIDs.at(it_MuonID);
    TString MuonIDSFKey = MuonIDSFKeys.at(it_MuonID);

    //==== 1) First, let's run Central values of the systematics

    //==== clear parameter set
    param.Clear();

    //==== set which systematic sources you want to run this time
    //==== default syst_ is AnalyzerParameter::Central
    param.syst_ = AnalyzerParameter::Central;

    //==== set name of the parameter set
    //==== this will be used for the directory name of histograms
    param.Name = MuonID+"_"+"Central";

    //==== You can define lepton ID string here
    param.Muon_Tight_ID = MuonID;
    param.Muon_ID_SF_Key = MuonIDSFKey;

    //==== And, Jet ID
    param.Jet_ID = "tight";

    //==== Now, all parameters are set. Run executeEventFromParameter() with this parameter set
    executeEventFromParameter(param);

    //==== 2) Now, loop over systematic sources
    //==== without --userflag RunSyst, this will not be ran

    if(RunSyst){

      for(int it_syst=1; it_syst<AnalyzerParameter::NSyst; it_syst++){

        //==== Everything else remains same, but only change syst_ and parameter name

        param.syst_ = AnalyzerParameter::Syst(it_syst);
        param.Name = MuonID+"_"+"Syst_"+param.GetSystType();
        executeEventFromParameter(param);
      }

    }

  }

  //================================
  //==== Example 2
  //==== Using new PDF
  //================================

  if(RunNewPDF && !IsDATA){
    //cout << "[BasicTest::executeEvent] PDF reweight = " << GetPDFReweight() << endl;
    FillHist("NewPDF_PDFReweight", GetPDFReweight(), 1., 2000, 0.90, 1.10);
    //cout << "[BasicTest::executeEvent] PDF reweight for error set (NErrorSet = "<<pdfReweight->NErrorSet<< ") :" << endl;
    for(int i=0; i<pdfReweight->NErrorSet; i++){
      //cout << "[BasicTest::executeEvent]   " << GetPDFReweight(i) << endl;
      FillHist("NewPDF_PDFErrorSet/PDFReweight_Member_"+TString::Itoa(i,10), GetPDFReweight(i), 1., 2000, 0.90, 1.10);
    }
  }

  //================================================
  //==== Example 3
  //==== How to estimate xsec errors (PDF & Scale)
  //==== For example, MET
  //================================================

  if(RunXSecSyst && !IsDATA){

    Event ev = GetEvent();
    double MET = ev.GetMETVector().Pt();

    //==== 1) PDF Error
    //==== Obtain RMS of the distribution later
    for(unsigned int i=0; i<weight_PDF->size(); i++){
      FillHist("XSecError/MET_PDFError_"+TString::Itoa(i,10), MET, weight_PDF->at(i), 200, 0., 200.);
    }

    //==== 2) PDF AlphaS
    //==== Look for PDF4LHC paper..
    //==== https://arxiv.org/abs/1510.03865
    if(weight_AlphaS->size()==2){
      FillHist("XSecError/MET_PDFAlphaS_Down", MET, weight_AlphaS->at(0), 200, 0., 200.);
      FillHist("XSecError/MET_PDFAlphaS_Up", MET, weight_AlphaS->at(1), 200, 0., 200.);
    }

    //==== 3) Scale
    //==== Obtain the envelop of the distribution later
    for(unsigned int i=0; i<weight_Scale->size(); i++){
      //==== i=5 and 7 are unphysical
      if(i==5) continue;
      if(i==7) continue;
      FillHist("XSecError/MET_Scale_"+TString::Itoa(i,10), MET, weight_Scale->at(i), 200, 0., 200.);
    }

  }

}

void BasicTest::executeEventFromParameter(AnalyzerParameter param){
  


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
  vector<Jet> this_AllJets = AllJets;
  vector<Muon> this_AllMuons = AllMuons;

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
    cout << "[BasicTest::executeEventFromParameter] Wrong syst" << endl;
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



