#include "JHAnalyzerBase.h"
#include "TStopwatch.h"
#include <limits>
#include <fstream>
#include <sstream>
#include <string>


JHAnalyzerBase::JHAnalyzerBase(){
  /*
  ///---define pt eta bin name----//
  const char* JHAnalyzerBase::PtBinName[JHAnalyzerBase::nPtBin] = {
    "PT30To50",
    "PT50To70",
    "PT70To100",
    "PT100To140",
    "PT140ToInf"
  };
  
  const char* JHAnalyzerBase::EtaBinName[JHAnalyzerBase::nEtaBin] = {
    "Eta0To0p8",
    "Eta0p8To1p6",
    "Eta1p6To2",
    "Eta2To2p5"
  };
  */
}
void JHAnalyzerBase::SetJetEtacut(){
  jetetacut=2.5;
  if(DataEra.Contains("2016")) jetetacut=2.4;
  cout << "[defualt jetetacut]=" << jetetacut << endl;
}
void JHAnalyzerBase::initializeAnalyzer(){
  cout << "[JHAnalyzerBase::initializeAnalyzer]DataEra->" << DataEra << endl;
  SetJetEtacut();
  IsDYSample=MCSample.Contains("DYJets")||MCSample.Contains("ZToEE")||MCSample.Contains("ZToMuMu")||MCSample.Contains(TRegexp("DY[0-9]Jets"));
  cout << "IsDYSample=" << IsDYSample <<endl;
  IsTTSample=MCSample.Contains(TRegexp("TT[LJ][LJ]"));
  cout << "IsTTSample=" << IsTTSample <<endl;
  IsTTLJSample=MCSample.Contains("TTLJ");
  IsQCDSample=MCSample.BeginsWith("QCD_");
  cout << "IsQCDSample=" << IsQCDSample <<endl;
  AnalyzerCore::SetupEfficiency();
  AnalyzerCore::SetupJetPUIDTool();
  AnalyzerCore::SetupRoccoR();
  if(IsDYSample)  AnalyzerCore::SetupZptWeight();
  InitSystematicMomentumVariations();
  runSys=HasFlag("runSys");
  //runSysMom00=HasFlag("runSysMom00");
  weightonly=HasFlag("weightonly");
  pusysonly=HasFlag("pusysonly");
  runMomSys=HasFlag("runMomSys");
  //scale00test=HasFlag("scale00test");
  simple_lepscale=HasFlag("simple_lepscale");
  checksf=HasFlag("checksf");
  measure_btageff=HasFlag("measure_btageff");
  measure_btageff_tight=HasFlag("measure_btageff_tight");
  measure_btageff_partonFlavour=HasFlag("measure_btageff_partonFlavour");
  measure_btageff_partonFlavour_bonly=HasFlag("measure_btageff_partonFlavour_bonly");
  measure_bchargeeff=HasFlag("measure_bchargeeff");
  measure_bchargeeff_v2=HasFlag("measure_bchargeeff_v2");
  measure_bchargeacc=HasFlag("measure_bchargeacc");
  UsePfMET=HasFlag("pfmet");
  if(UsePfMET){
    cout << "[jhchoi] UsePfMET!!" << endl;
  }
  UsePhiCorrMET=HasFlag("phicorrmet");
  if(UsePhiCorrMET){
    cout << "[jhchoi] UsePhiCorrMET!!" << endl;
  }
  SetUpBtag();
  if(IsDATA){
    ProcessName="Data";
  }
  else{
    ProcessName=MCSample;
  }
  cout << "[JHAnalyzerBase::initializeAnalyzer] runSys=" << runSys << endl;

  //------PDF sys setup-----//
  PDFalias="";
  int pdfidcode=GetPDFSetIDCode();
  //Note that e.g. 325300 (325500) and 306000 (320900) are considered equivalent at the SM regions. 
  //https://cms-pdmv.gitbook.io/project/mccontact/info-for-mc-production-for-ultra-legacy-campaigns-2016-2017-2018
  if(pdfidcode==306000 || pdfidcode==325300){
    PDFalias="NNPDF31_NNLO_5f";
  }
  else if(pdfidcode==325500){
    PDFalias="NNPDF31_NNLO_4f";
  }
  else{
    PDFalias="PDF";
  }
  cout << "PDFalias=" << PDFalias << endl;


  //---SetUp MC btag Eff Measurement--..
  if(measure_btageff) SetUpBtagEffMeasurement();
  if(measure_btageff_tight) SetUpBtagEffMeasurement();
  if(measure_btageff_partonFlavour) SetUpBtagEffMeasurementPartonFlavour();
  if(measure_btageff_partonFlavour_bonly) SetUpBtagEffMeasurementPartonFlavour_bonly();

  //---jet veto map(jetvetomap)
  TFileJetVetoMap=NULL;
  h_jetvetomap=NULL;
  SetJetVetoMap();

  //----bChargeID
  //Setup_bChargeIDEff();
}



void JHAnalyzerBase::SetJetVetoMap(){
 
  
  TString _datadir=getenv("DATA_DIR");
  TString _era=GetEra();
    
  TString vetofilepath=_datadir+"/"+_era+"/JetVetoMap/";
  TString vetohname="";
  if(_era.Contains("2016")){
    //vetofilepath+="hotjets-UL16.root";
    vetofilepath+="hotjets-UL16_add_mc.root";
    //vetohname="h2hot_ul16_plus_hbm2_hbp12_qie11";
    vetohname="h2hot_ul16_plus_hbm2_hbp12_qie11_plus_mc";
    
  }
  else if(_era.Contains("2017")){
    vetofilepath+="hotjets-UL17_v2.root";
    vetohname="h2hot_ul17_plus_hep17_plus_hbpw89";
  }else if(_era.Contains("2018")){
    vetofilepath+="hotjets-UL18.root";
    vetohname="h2hot_ul18_plus_hem1516_and_hbp2m1";
  }
  cout << "[JHAnalyzerBase::SetJetVetoMap] Open jet veto map file->" << vetofilepath << endl;
  cout << "histname=" << vetohname << endl;
  TFileJetVetoMap=TFile::Open(vetofilepath);
  h_jetvetomap=(TH2D*)TFileJetVetoMap->Get(vetohname)->Clone();
  if(!h_jetvetomap->InheritsFrom(TH2::Class())){
    cout << "!!!!veto map is not loaed properly!!!!" << endl;
    exit(ENODATA);

  }
  h_jetvetomap->SetDirectory(0);
  TFileJetVetoMap->Close();
  delete TFileJetVetoMap;
  TFileJetVetoMap=nullptr;
}




int JHAnalyzerBase::GetPDFSetIDCode(){
  //id=325500
  //NNPDF31_nnlo_as_0118_nf_4_mc_hessian
  if(MCSample.Contains("SingleTop_tch_antitop_Incl") || MCSample.Contains("SingleTop_tch_top_Incl") || MCSample.Contains("SingleTop_sch_Lep") ){
    return 325500;
  }
  //id=325300
  //NNPDF31_nnlo_as_0118_mc_hessian_pdfas
  else if(MCSample.Contains("WJets_MG")){
    return 325300;
  }
  //id=306000
  //NNPDF31_nnlo_hessian_pdfas
  else{
    return 306000;
  }
}


void JHAnalyzerBase::SetUpBtag(){
  std::vector<JetTagging::Parameters> jtps;
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Tight, JetTagging::incl, JetTagging::comb) );
  mcCorr->SetJetTaggingParameters(jtps);
  jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  mcCorr->MCCorrection::SetEra(DataEra);
  btagcut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
  cout << "[JHAnalyzerBase::SetUpBtag]btagcut=" << btagcut << endl;
}
void JHAnalyzerBase::InitSystematicMomentumVariations(){
  //--Define--//
  jesUp.jes=1;                         
  jesUp.name="jes"+DataEra;jesUp.dir="Up";

  jesDown.jes=-1;                      
  jesDown.name="jes"+DataEra;jesDown.dir="Down";   

  jerUp.jer=1;                         
  jerUp.name="jer"+DataEra;jerUp.dir="Up";

  jerDown.jer=-1;                      
  jerDown.name="jer"+DataEra;jerDown.dir="Down";   
  
  /*
  muonscaleUp.muonscale=1;       
  muonscaleUp.name="muonscale";muonscaleUp.dir="Up";

  muonscaleDown.muonscale=-1;    
  muonscaleDown.name="muonscale";muonscaleDown.dir="Down";

  electronscaleUp.electronscale=1;   
  electronscaleUp.name="electronscale"; electronscaleUp.dir="Up";

  electronscaleDown.electronscale=-1;
  electronscaleDown.name="electronscale"; electronscaleDown.dir="Down";
  */
  metUp.met=1;   
  metUp.name="met"+DataEra;   metUp.dir="Up";
  metDown.met=-1;
  metDown.name="met"+DataEra; metDown.dir="Down";
  //--Variation To Run--//
  //vMomentumVar={jesUp,jesDown,jerUp,jerDown,muonscaleUp,muonscaleDown,
  //		electronscaleUp,electronscaleDown,metUp,metDown};
  vMomentumVar={jesUp,jesDown,jerUp,jerDown,metUp,metDown};
  

  //--vMuonMomentumVar And ElectronMomentumVar
  const vector<int> nmem_mucorr={1,40,1,1,1,1};
  for(unsigned int idx1=0; idx1<nmem_mucorr.size();idx1++){
    int nmem=nmem_mucorr[idx1];
    vector<MuonMomentumVar> this_v;
    for(int idx2=0; idx2 < nmem;idx2++){
      MuonMomentumVar thisvar;
      thisvar.idx1=idx1; thisvar.idx2=idx2; thisvar.name="muonscale"+DataEra;
      this_v.push_back(thisvar);
    }
    vMuonMomentumVar.push_back(this_v);
  }


  const vector<int> nmem_elcorr={1,40,1,1,1,1,1,1,1};
  for(unsigned int idx1=0; idx1<nmem_elcorr.size();idx1++){
    int nmem=nmem_elcorr[idx1];
    vector<ElectronMomentumVar> this_v;
    for(int idx2=0; idx2 < nmem;idx2++){
      ElectronMomentumVar thisvar;
      thisvar.idx1=idx1; thisvar.idx2=idx2; thisvar.name="electronscale"+DataEra;
      this_v.push_back(thisvar);
    }
    vElectronMomentumVar.push_back(this_v);
  }
}

JHAnalyzerBase::~JHAnalyzerBase(){

  //==== Destructor of this Analyzer
  cout << printcurrunttime() << endl;
  cout << "DeleteChargeScoreTool" << endl;
  if(IsChargeScoreToolOn) DeleteChargeScoreTool();
  cout << printcurrunttime() << endl;
  cout << "delete TTLJJetAssignmentTool" << endl;
  if(IsTTLJJetAssignmentToolOn) delete TTLJJetAssignmentTool;
  cout << printcurrunttime() << endl;
  cout << "DeleteJetAssigenChi2Fitter" << endl;
  DeleteJetAssigenChi2Fitter();
  cout << printcurrunttime() << endl;
  cout << "[END]~JHAnalyzerBase" << endl;
  //---JetVetoMap

  
  //TFileJetVetoMap->Close();
  //delete TFileJetVetoMap;
  //TFileJetVetoMap=nullptr;
  //if(h_jetvetomap) delete h_jetvetomap;  


}

void JHAnalyzerBase::executeEvent(){  
  TStopwatch timer;


  //EvtToTest= (event==5721707 || event==20757 || event==9019092 || event==6568447 || event==294056 || event==15412219 || event==5574457);
  //EvtToTest=(event==25837934);
  //if(!EvtToTest) return;
  if(!PassMETFilter()) return;
  SetEventBaseSysWeight();//this should be done first due to gen info for rochcorr
  InitAllObjects();
  ev=GetEvent();
  //---Nominal and weight-base variations--//
  //--init variables--//
  runWeightBase=true;
  SetSysStructure();

  //cout << "[nominal & weightbase run]"<< endl;
  //timer.Start();

  InitClassVariablesPerEvent();
  InitBtagSys();
  TruthLoop();
  

    
  //muonscale00event=0;
  //electronscale00event=0;
  //nominalevent=1;
  EventLoop();
  //nominalevent=0;
  //cout << "weight=" << weight << endl;
  //timer.Stop();
  //std::cout << "[CPU time]: " << timer.CpuTime() << " s\n";
  //timer.Reset();
  
  //FillReservedHistWeightBase();
  //ClearReserveHist();

  //if(!runSys && !runMomSys && !scale00test) return;
  if(weightonly) return;
  if(pusysonly) return;
  if(!runSys && !runMomSys) return;  

  //---Momentum variations--//
  runWeightBase=false;
  SetSysStructure();//remove sysvariation weights

  //cout << "[JetMet scale run]" << endl;
  //timer.Start();

  for(const auto &sys : vMomentumVar){//jes/jer/met
    if(IsDATA) break; // jes/jer/met uncertainties of data are all propagated to MC
    //if(scale00test) break;
    //if(scale00test) break;
    SetSys(sys);
    InitClassVariablesPerEvent();
    InitBtagSys();
    EventLoop();
    //FillReservedHistMomentumVariations();
    //ClearReserveHist();
  }
  //timer.Stop();
  //std::cout << "[CPU time]: " << timer.CpuTime() << " s\n";
  //timer.Reset();


  
  if(simple_lepscale){
    //---Make muon/electron pt up/down collections 
    SetupSimpleMuonMomentumVar();
    SetupSimpleElectronMomentumVar();

    //--MuonScaleUp
    SetSysSimpleMuon(1);
    InitClassVariablesPerEvent();
    InitBtagSys();
    EventLoop();
    //--MuonScaleDown    
    SetSysSimpleMuon(-1);
    InitClassVariablesPerEvent();
    InitBtagSys();
    EventLoop();

    //--ElectronScaleUp
    SetSysSimpleElectron(1);
    InitClassVariablesPerEvent();
    InitBtagSys();
    EventLoop();
    //--ElectronScaleDown    
    SetSysSimpleElectron(-1);
    InitClassVariablesPerEvent();
    InitBtagSys();
    EventLoop();

  }
  else{//not simple_lepscale
    //cout << "[Muon Mom Scale Run]" << endl;
    //timer.Start();
	  
    for(const auto &_vsys : vMuonMomentumVar){
      for(const auto &sys : _vsys){
	SetSys(sys);
	InitClassVariablesPerEvent();
	InitBtagSys();
	/*
	if (sys.idx1 ==0 && sys.idx2==0){
	  muonscale00event=1;
	}else{
	  muonscale00event=0;
	  if(scale00test) continue;
	}
	*/
	EventLoop();
	//if (sys.idx1 ==0 && sys.idx2==0) cout << "weight=" << weight << endl;


	//FillReservedHistLeptonMomentumVariations();
	//ClearReserveHist();
      }
    }
    //timer.Stop();
    //std::cout << "[Func1] CPU time: " << timer.CpuTime() << " s\n";
    //timer.Reset();


    //cout << "[Ele Mom Scale Run]" << endl;
    //timer.Start();

    for(const auto &_vsys : vElectronMomentumVar){
      for(const auto &sys : _vsys){
	//if(scale00test) continue;
	SetSys(sys);
	InitClassVariablesPerEvent();
	InitBtagSys();
	/*
	if (sys.idx1 ==0 && sys.idx2==0){
	  electronscale00event=1;
	}else{
	  electronscale00event=0;
	  if(scale00test) continue;
	}
	*/
	EventLoop();
	//if (sys.idx1 ==0 && sys.idx2==0) cout << "weight=" << weight << endl;
	//FillReservedHistLeptonMomentumVariations();
	//ClearReserveHist();
      }
    }
    //timer.Stop();
    //std::cout << "[Func1] CPU time: " << timer.CpuTime() << " s\n";
    //timer.Reset();

  }//[END]not simple_lepscale
}
void JHAnalyzerBase::SetEventBaseSysWeight(){
  z0weight=1.; weakweight=1.;zptweight=1;topptweight=1.;
  if(IsDATA) return;
  //zptweight , weakweight, z0weight

  lhes=GetLHEs();
  gens=GetGens();

  if(IsDYSample){
    GetAFBLHEParticles(lhes,lhe_p0,lhe_p1,lhe_l0,lhe_l1,lhe_j0);
    GetAFBGenParticles(gens,gen_p0,gen_p1,gen_l0,gen_l1,3);//mode==3 -> before FSR
    GetAFBGenParticles(gens,gen_p0,gen_p1,gen_l0_dressed,gen_l1_dressed,1);//needed for ele rocc
    GetAFBGenParticles(gens,gen_p0,gen_p1,gen_l0_bare,gen_l1_bare,0);
    if(abs(lhe_l0.ID())==11||abs(lhe_l0.ID())==13){
      TLorentzVector genZ=(gen_l0+gen_l1);
      zptweight=GetZptWeight(genZ.M(),genZ.Rapidity(),genZ.Pt());
      weakweight=GetDYWeakWeight(genZ.M());

      //cout << "gen_l0_dressed is set" << gen_l0_dressed.Pt() << endl;
    }
    //cout << "---run=" << run << endl;
    //cout << "gen_l0_dressed is set" << gen_l0_dressed.Pt() << endl;
    //cout << "gen_l1_dressed is set" << gen_l1_dressed.Pt() << endl;
  }//[end] dysample
  z0weight=GetZ0Weight(vertex_Z);
  //[END]zptweight , weakweight, z0weight
  //topptweight
  if(IsTTSample)topptweight=mcCorr->GetTopPtReweight(gens);
  //cout << "topptweight=" << topptweight << endl;
  if(!runSys) return;

  //pu,prefire
  if(GetPileUpWeight(nPileUp,0)){
    r_PU={GetPileUpWeight(nPileUp,1)/GetPileUpWeight(nPileUp,0),GetPileUpWeight(nPileUp,-1)/GetPileUpWeight(nPileUp,0)};
  }
  else{
    r_PU={1.,1.};
  }
  //
  if(L1PrefireReweight_Central){
    r_Prefire={L1PrefireReweight_Up/L1PrefireReweight_Central, L1PrefireReweight_Down/L1PrefireReweight_Central };
  }
  else{
    r_Prefire={1.,1.};
  }


}
void JHAnalyzerBase::SetSysStructure(){
  //---WeightBase Systematic sources Only---//
  //if(runSys&&runWeightBase &&  !scale00test){
  if(runSys&&runWeightBase){
    //cout << "multiple variation of eff" << endl;
    w_ElectronID=fEff->GetStructure(ElectronIDSFKey);
    r_ElectronID=fEff->GetStructure(ElectronIDSFKey);
    w_ElectronRECO=fEff->GetStructure(ElectronRecoSFKey);
    r_ElectronRECO=fEff->GetStructure(ElectronRecoSFKey);
    w_ElectronTrigger=fEff->GetStructure(ElectronTriggerSFKeys[0]);
    r_ElectronTrigger=fEff->GetStructure(ElectronTriggerSFKeys[0]);
    
    w_MuonID=fEff->GetStructure(MuonIDSFKey);
    r_MuonID=fEff->GetStructure(MuonIDSFKey);
    w_MuonRECO=fEff->GetStructure(MuonRecoSFKey);
    r_MuonRECO=fEff->GetStructure(MuonRecoSFKey);
    w_MuonTrigger=fEff->GetStructure(MuonTriggerSFKeys[0]);
    r_MuonTrigger=fEff->GetStructure(MuonTriggerSFKeys[0]);
    w_MuonTrk=fEff->GetStructure(MuonTrkSFKey);
    r_MuonTrk=fEff->GetStructure(MuonTrkSFKey);

    //----below is to check # of sys histograms
    /*
    unsigned int n_efftool_var=0;
    for(unsigned int i =0 ; i < w_ElectronID.size(); i++){
      n_efftool_var+=w_ElectronID[i].size();
    }
    for(unsigned int i =0 ; i < w_ElectronRECO.size(); i++){
      n_efftool_var+=w_ElectronRECO[i].size();
    }
    for(unsigned int i =0 ; i < w_ElectronTrigger.size(); i++){
      n_efftool_var+=w_ElectronTrigger[i].size();
    }
    for(unsigned int i =0 ; i < w_MuonID.size(); i++){
      n_efftool_var+=w_MuonID[i].size();
    }
    for(unsigned int i =0 ; i < w_MuonRECO.size(); i++){
      n_efftool_var+=w_MuonRECO[i].size();
    }
    for(unsigned int i =0 ; i < w_MuonTrigger.size(); i++){
      n_efftool_var+=w_MuonTrigger[i].size();
    }
    for(unsigned int i =0 ; i < w_MuonTrk.size(); i++){
      n_efftool_var+=w_MuonTrk[i].size();
    }
    cout << "[n_efftool_var]=" << n_efftool_var << endl;
    */


  }

  else{//if not weightbase
    //cout << "no weight sys variations" << endl;
    //--Electron--//
    w_ElectronID.clear();
    r_ElectronID.clear();
    w_ElectronRECO.clear();
    r_ElectronRECO.clear();
    w_ElectronTrigger.clear();
    r_ElectronTrigger.clear();

    w_ElectronID.push_back({1.});
    r_ElectronID.push_back({1.});
    w_ElectronRECO.push_back({1.});
    r_ElectronRECO.push_back({1.});
    w_ElectronTrigger.push_back({1.});
    r_ElectronTrigger.push_back({1.});

    //---Muon--//
    w_MuonID.clear();
    r_MuonID.clear();
    w_MuonRECO.clear();
    r_MuonRECO.clear();
    w_MuonTrigger.clear();
    r_MuonTrigger.clear();
    w_MuonTrk.clear();
    r_MuonTrk.clear();

    w_MuonID.push_back({1.});
    r_MuonID.push_back({1.});
    w_MuonRECO.push_back({1.});
    r_MuonRECO.push_back({1.});
    w_MuonTrigger.push_back({1.});
    r_MuonTrigger.push_back({1.});
    w_MuonTrk.push_back({1.});
    r_MuonTrk.push_back({1.});

  }

}
void JHAnalyzerBase::InitBtagSys(){
  //---btagSF variations---//
  r_SystUpLTagCorr=1;r_SystDownLTagCorr=1;
  r_SystUpLTagUnCorr=1;r_SystDownLTagUnCorr=1;
  r_SystUpHTagCorr=1;r_SystDownHTagCorr=1;
  r_SystUpHTagUnCorr=1;r_SystDownHTagUnCorr=1;
  //r_ChargedAsymUp=1. ; r_ChargedAsymDown=1.;
  for (int ipt = 0; ipt < nPtBin; ++ipt) {
    for (int ieta = 0; ieta < nEtaBin; ++ieta) {
      arr_r_ChargedAsymUp[ipt][ieta]   = 1.0;
      arr_r_ChargedAsymDown[ipt][ieta] = 1.0;
    }
  }
}

void JHAnalyzerBase::InitClassVariablesPerEvent(){
  //--Event variables--//
  weight=1.;
  btagsf=1.;
  jetpuidsf=1.; jetpuidsf_up=1.; jetpuidsf_down=1.; r_jetpuidsf_up=1.;r_jetpuidsf_down=1.;
  //zptweight=1.;
  //z0weight=1.;
  //weakweight=1.;

  if(Is_bChargeIDEffOn){
    ///----bchargeID Efficiency syst---//
    for (int ipt = 0; ipt < nPtBin; ++ipt) {
      for (int islt = 0; islt < nSLT; ++islt) {
	arr_r_bChargeID_SLT_CorrUp[islt][ipt]   = 1.0;
	arr_r_bChargeID_SLT_CorrDown[islt][ipt] = 1.0;
	
	arr_r_bChargeID_SLT_UnCorr_bPlusUp[islt][ipt]   = 1.0;
	arr_r_bChargeID_SLT_UnCorr_bPlusDown[islt][ipt]   = 1.0;
	
	arr_r_bChargeID_SLT_UnCorr_bMinusUp[islt][ipt] = 1.0;
	arr_r_bChargeID_SLT_UnCorr_bMinusDown[islt][ipt] = 1.0;
      }
    }
    //---jH

    for (int ipt = 0; ipt < nPtBin; ++ipt) {
      for (int ieta = 0; ieta < nEtaBin; ++ieta) {
	arr_r_bChargeID_Jet_CorrUp[ipt][ieta]   = 1.0;
	arr_r_bChargeID_Jet_CorrDown[ipt][ieta] = 1.0;
	
	arr_r_bChargeID_Jet_UnCorr_bPlusUp[ipt][ieta]   = 1.0;
	arr_r_bChargeID_Jet_UnCorr_bPlusDown[ipt][ieta] = 1.0;
	
	arr_r_bChargeID_Jet_UnCorr_bMinusUp[ipt][ieta]   = 1.0;
	arr_r_bChargeID_Jet_UnCorr_bMinusDown[ipt][ieta] = 1.0;
	
	
      }
    }
  
  }

  if(Is_bChargeAccOn){
    /// -----charge accuracy syst----///
    for (int ipt = 0; ipt < nPtBin; ++ipt) {
      for (int islt = 0; islt < nSLT; ++islt) {
	arr_r_bChargeAcc_SLT_CorrUp[islt][ipt]   = 1.0;
	arr_r_bChargeAcc_SLT_CorrDown[islt][ipt] = 1.0;
	
	arr_r_bChargeAcc_SLT_UnCorr_bPlusUp[islt][ipt]   = 1.0;
	arr_r_bChargeAcc_SLT_UnCorr_bPlusDown[islt][ipt]   = 1.0;
	
	arr_r_bChargeAcc_SLT_UnCorr_bMinusUp[islt][ipt] = 1.0;
	arr_r_bChargeAcc_SLT_UnCorr_bMinusDown[islt][ipt] = 1.0;
      }
    }
    //---jH/jOthers                                                                                                                                                                                         
    for (int ipt = 0; ipt < nPtBin; ++ipt) {
      for (int ieta = 0; ieta < nEtaBin; ++ieta) {
	for (int ij =0 ; ij < 2; ++ij){
	  arr_r_bChargeAcc_Jet_CorrUp[ij][ipt][ieta]   = 1.0;
	  arr_r_bChargeAcc_Jet_CorrDown[ij][ipt][ieta] = 1.0;
	  
	  arr_r_bChargeAcc_Jet_UnCorr_bPlusUp[ij][ipt][ieta]   = 1.0;
	  arr_r_bChargeAcc_Jet_UnCorr_bPlusDown[ij][ipt][ieta] = 1.0;
	  
	  arr_r_bChargeAcc_Jet_UnCorr_bMinusUp[ij][ipt][ieta]   = 1.0;
	  arr_r_bChargeAcc_Jet_UnCorr_bMinusDown[ij][ipt][ieta] = 1.0;
	}
	
      }
    }
  }

  
  
}

void JHAnalyzerBase::FillHist(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //---ArgFillHist structure---//
  /*
  struct ArgFillHist{
    TString histname;
    double value; double weight;
    int n_bin; double x_min;
    double x_max;
  };

  */
  if(runWeightBase){
    FillHistWeightBase(histname,value,this_weight,n_bin,x_min,x_max);
  }  
  else{
    //TString histname="SYS/"+arg.histname+"/"+sysname_current+"/0/"+sysdir_current;
    TString newhistname="SYS/"+histname+"/"+sysname_current+"/"+sysidx1_current+"/"+sysidx2_current;
    AnalyzerCore::FillHist(newhistname+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
    //ArgFillHist this_arg={histname,value,this_weight,n_bin,x_min,x_max};
    //vReserveHist.push_back(this_arg);
  }
  //vReserveHist.push_back(make_tuple(histname,value,this_weight,n_bin,x_min,x_max));
}

void JHAnalyzerBase::FillHist(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //---ArgFillHist structure---//
  /*
  struct ArgFillHist{
    TString histname;
    double value; double weight;
    int n_bin; double x_min;
    double x_max;
  };

  */
  if(runWeightBase){
    FillHistWeightBase(histname,value,this_weight,n_bin,xbins);
  }  
  else{
    //TString histname="SYS/"+arg.histname+"/"+sysname_current+"/0/"+sysdir_current;
    TString newhistname="SYS/"+histname+"/"+sysname_current+"/"+sysidx1_current+"/"+sysidx2_current;
    AnalyzerCore::FillHist(newhistname+"/"+ProcessName,value,this_weight,n_bin,xbins);
    //ArgFillHist this_arg={histname,value,this_weight,n_bin,x_min,x_max};
    //vReserveHist.push_back(this_arg);
  }
  //vReserveHist.push_back(make_tuple(histname,value,this_weight,n_bin,x_min,x_max));
}




///----FillHistForSystematic---//
void JHAnalyzerBase::FillHistUp(TString sysname,TString histname,double value,double this_weight,int n_bin,double x_min, double x_max){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/0/Up/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistUp(TString sysname,TString histname,double value,double this_weight,int n_bin,double *xbins){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/0/Up/"+ProcessName,value,this_weight,n_bin,xbins);
}

void JHAnalyzerBase::FillHistDown(TString sysname,TString histname,double value,double this_weight,int n_bin,double x_min, double x_max){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/0/Down/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistDown(TString sysname,TString histname,double value,double this_weight,int n_bin,double *xbins){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/0/Down/"+ProcessName,value,this_weight,n_bin, xbins);
}


void JHAnalyzerBase::FillHistIdx2(TString sysname, int idx1, int idx2, TString histname,double value,double this_weight,int n_bin,double x_min, double x_max){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/"+std::to_string(idx1)+"/"+std::to_string(idx2)+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistIdx2(TString sysname, int idx1, int idx2, TString histname,double value,double this_weight,int n_bin,double *xbins){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/"+std::to_string(idx1)+"/"+std::to_string(idx2)+"/"+ProcessName,value,this_weight,n_bin, xbins);
}


void JHAnalyzerBase::FillHistIdx2(TString sysname, TString idx1, TString idx2, TString histname,double value,double this_weight,int n_bin,double x_min, double x_max){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/"+idx1+"/"+idx2+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistIdx2(TString sysname, TString idx1, TString idx2, TString histname,double value,double this_weight,int n_bin,double *xbins){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/"+idx1+"/"+idx2+"/"+ProcessName,value,this_weight,n_bin, xbins);
}


void JHAnalyzerBase::FillHistPUSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //PU weight//
  FillHistUp("pu"+DataEra,histname,value,this_weight*r_PU[0],n_bin,x_min,x_max);
  FillHistDown("pu"+DataEra,histname,value,this_weight*r_PU[1],n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistPUSys(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //PU weight//
  FillHistUp("pu"+DataEra,histname,value,this_weight*r_PU[0],n_bin,xbins);
  FillHistDown("pu"+DataEra,histname,value,this_weight*r_PU[1],n_bin,xbins);
}


void JHAnalyzerBase::FillHistZptWeight(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  double r_zptweight=zptweight ? zptweight : 1;
  FillHistUp("zptweight",histname,value,this_weight*r_zptweight,n_bin,x_min,x_max);
  //FillHistDown("zptweight",histname,value,this_weight,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistZptWeight(TString histname, double value, double this_weight, int n_bin, double *xbins){
  double r_zptweight=zptweight ? zptweight : 1;
  FillHistUp("zptweight",histname,value,this_weight*r_zptweight,n_bin,xbins);
  //FillHistDown("zptweight",histname,value,this_weight,n_bin,xbins);
}


void JHAnalyzerBase::FillHistTopPtReweight(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  double r_topptweight= topptweight ? 1/topptweight : 1;
  FillHistUp("topptweight",histname,value,this_weight*r_topptweight,n_bin,x_min,x_max);
  //FillHistDown("topptweight",histname,value,this_weight,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistTopPtReweight(TString histname, double value, double this_weight, int n_bin, double *xbins){
  double r_topptweight= topptweight ? 1/topptweight : 1;
  FillHistUp("topptweight",histname,value,this_weight*r_topptweight,n_bin,xbins);
  //FillHistDown("topptweight",histname,value,this_weight,n_bin,xbins);
}


void JHAnalyzerBase::FillHistPSSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //PS weight//
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/HowToPDF#Parton_shower_weights
  //"structure":{
  //   0:{"name":"fsrDown","type":"group","group":"fsr"},
  //   1:{"name":"fsrUp","type":"group","group":"fsr"},
  //   2:{"name":"isrDown","type":"group","group":"isr"},
  //   3:{"name":"isrUp","type":"group","group":"isr"},


  int idx=0;
  for(const auto& _pssyst : *weight_PSSyst){
    FillHistIdx2("ps",0,idx,histname,value,this_weight*_pssyst,n_bin,x_min,x_max);
    idx+=1;
  }

}
void JHAnalyzerBase::FillHistPSSys(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //PS weight//
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/HowToPDF#Parton_shower_weights
  //"structure":{
  //   0:{"name":"fsrDown","type":"group","group":"fsr"},
  //   1:{"name":"fsrUp","type":"group","group":"fsr"},
  //   2:{"name":"isrDown","type":"group","group":"isr"},
  //   3:{"name":"isrUp","type":"group","group":"isr"},


  int idx=0;
  for(const auto& _pssyst : *weight_PSSyst){
    FillHistIdx2("ps",0,idx,histname,value,this_weight*_pssyst,n_bin,xbins);
    idx+=1;
  }

}


void JHAnalyzerBase::FillHistPDF(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  int idx=0;
  int _size=weight_PDF->size();
  for(auto& _wsyst : *weight_PDF){
    if(std::isnan(_wsyst)) _wsyst=1;
    FillHistIdx2(PDFalias,_size,idx,histname,value,this_weight*_wsyst,n_bin,x_min,x_max);
    idx+=1;
  }
}
void JHAnalyzerBase::FillHistPDF(TString histname, double value, double this_weight, int n_bin, double *xbins){
  int idx=0;
  int _size=weight_PDF->size();
  for(auto& _wsyst : *weight_PDF){
    if(std::isnan(_wsyst)) _wsyst=1;
    FillHistIdx2(PDFalias,_size,idx,histname,value,this_weight*_wsyst,n_bin,xbins);
    idx+=1;
  }
}


void JHAnalyzerBase::FillHistScale(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  int idx=0;
  int _size=weight_Scale->size();
  for(const auto& _wsyst : *weight_Scale){
    FillHistIdx2("QCDScale",_size,idx,histname,value,this_weight*_wsyst,n_bin,x_min,x_max);
    idx+=1;
  }
}
void JHAnalyzerBase::FillHistScale(TString histname, double value, double this_weight, int n_bin, double *xbins){
  int idx=0;
  int _size=weight_Scale->size();
  for(const auto& _wsyst : *weight_Scale){
    FillHistIdx2("QCDScale",_size,idx,histname,value,this_weight*_wsyst,n_bin,xbins);
    idx+=1;
  }
}


void JHAnalyzerBase::FillHistAlphaS(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  int idx=0;
  int _size=weight_AlphaS->size();
  for(const auto& _wsyst : *weight_AlphaS){
    FillHistIdx2(PDFalias+"_AlphaS",_size,idx,histname,value,this_weight*_wsyst,n_bin,x_min,x_max);
    idx+=1;
  }
}
void JHAnalyzerBase::FillHistAlphaS(TString histname, double value, double this_weight, int n_bin, double *xbins){
  int idx=0;
  int _size=weight_AlphaS->size();
  for(const auto& _wsyst : *weight_AlphaS){
    FillHistIdx2(PDFalias+"_AlphaS",_size,idx,histname,value,this_weight*_wsyst,n_bin,xbins);
    idx+=1;
  }
}


void JHAnalyzerBase::FillHistPrefireSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //Prefire weight//
  FillHistUp("prefire"+DataEra,histname,value,this_weight*r_Prefire[0],n_bin,x_min,x_max);
  FillHistDown("prefire"+DataEra,histname,value,this_weight*r_Prefire[1],n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistPrefireSys(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //Prefire weight//
  FillHistUp("prefire"+DataEra,histname,value,this_weight*r_Prefire[0],n_bin,xbins);
  FillHistDown("prefire"+DataEra,histname,value,this_weight*r_Prefire[1],n_bin,xbins);
}

void JHAnalyzerBase::FillHistJetPUID(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //Prefire weight//
  FillHistUp("jetpuid",histname,value,this_weight*r_jetpuidsf_up,n_bin,x_min,x_max);
  FillHistDown("jetpuid",histname,value,this_weight*r_jetpuidsf_down,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistJetPUID(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //Prefire weight//
  FillHistUp("jetpuid",histname,value,this_weight*r_jetpuidsf_up,n_bin,xbins);
  FillHistDown("jetpuid",histname,value,this_weight*r_jetpuidsf_down,n_bin,xbins);
}


void JHAnalyzerBase::FillHistBtag(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //btag weight//  
  FillHistIdx2("btag","LTagCorr","Up",   histname, value,this_weight*r_SystUpLTagCorr,  n_bin,x_min,x_max);
  FillHistIdx2("btag","LTagCorr","Down", histname, value,this_weight*r_SystDownLTagCorr,n_bin,x_min,x_max);

  FillHistIdx2("btag","LTagUnCorr"+DataEra,"Up",  histname, value,this_weight*r_SystUpLTagUnCorr,  n_bin,x_min,x_max);
  FillHistIdx2("btag","LTagUnCorr"+DataEra,"Down",histname, value,this_weight*r_SystDownLTagUnCorr,n_bin,x_min,x_max);

  FillHistIdx2("btag","HTagCorr","Up",    histname, value,this_weight*r_SystUpHTagCorr,  n_bin,x_min,x_max);
  FillHistIdx2("btag","HTagCorr","Down",  histname, value,this_weight*r_SystDownHTagCorr,n_bin,x_min,x_max);

  FillHistIdx2("btag","HTagUnCorr"+DataEra,"Up",   histname, value,this_weight*r_SystUpHTagUnCorr,  n_bin,x_min,x_max);
  FillHistIdx2("btag","HTagUnCorr"+DataEra,"Down", histname, value,this_weight*r_SystDownHTagUnCorr,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistBtagChargeAsym(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  for (int ipt = 0; ipt < nPtBin; ++ipt) {
    for (int ieta = 0; ieta < nEtaBin; ++ieta) {
      FillHistUp("btagChargedAsym"+TString(PtBinName[ipt])+TString(EtaBinName[ieta])+DataEra,   histname, value,this_weight*arr_r_ChargedAsymUp[ipt][ieta],  n_bin,x_min,x_max);
      FillHistDown("btagChargedAsym"+TString(PtBinName[ipt])+TString(EtaBinName[ieta])+DataEra, histname, value,this_weight*arr_r_ChargedAsymDown[ipt][ieta],n_bin,x_min,x_max);
    }
  }
}
void JHAnalyzerBase::FillHistBtag(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //btag weight//  
  FillHistIdx2("btag","LTagCorr","Up",   histname, value,this_weight*r_SystUpLTagCorr,  n_bin,xbins);
  FillHistIdx2("btag","LTagCorr","Down", histname, value,this_weight*r_SystDownLTagCorr,n_bin,xbins);

  FillHistIdx2("btag","LTagUnCorr"+DataEra,"Up",  histname, value,this_weight*r_SystUpLTagUnCorr,  n_bin,xbins);
  FillHistIdx2("btag","LTagUnCorr"+DataEra,"Down",histname, value,this_weight*r_SystDownLTagUnCorr,n_bin,xbins);

  FillHistIdx2("btag","HTagCorr","Up",    histname, value,this_weight*r_SystUpHTagCorr,  n_bin,xbins);
  FillHistIdx2("btag","HTagCorr","Down",  histname, value,this_weight*r_SystDownHTagCorr,n_bin,xbins);

  FillHistIdx2("btag","HTagUnCorr"+DataEra,"Up",   histname, value,this_weight*r_SystUpHTagUnCorr,  n_bin,xbins);
  FillHistIdx2("btag","HTagUnCorr"+DataEra,"Down", histname, value,this_weight*r_SystDownHTagUnCorr,n_bin,xbins);
}
void JHAnalyzerBase::FillHistBtagChargeAsym(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //btag weight//    
  for (int ipt = 0; ipt < nPtBin; ++ipt) {
    for (int ieta = 0; ieta < nEtaBin; ++ieta) {
      FillHistUp("btagChargedAsym"+TString(PtBinName[ipt])+TString(EtaBinName[ieta])+DataEra,   histname, value,this_weight*arr_r_ChargedAsymUp[ipt][ieta],  n_bin,xbins);
      FillHistDown("btagChargedAsym"+TString(PtBinName[ipt])+TString(EtaBinName[ieta])+DataEra, histname, value,this_weight*arr_r_ChargedAsymDown[ipt][ieta],n_bin,xbins);
    }
  }
  
  //FillHistUp("btagChargedAsym"+DataEra,   histname, value,this_weight*r_ChargedAsymUp,   n_bin,xbins);
  //FillHistDown("btagChargedAsym"+DataEra  ,histname, value,this_weight*r_ChargedAsymDown,n_bin,xbins);
}


//--SLT Eff---//

void JHAnalyzerBase::FillHistChargeIDEff(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //---SLT n_bin,x_min,x_max
  //cout << "[JHAnalyzerBase::FillHistChargeIDEff]" << endl;
  for (int iPtBin = 0; iPtBin < nPtBin; ++iPtBin) {
    for (int iSLT = 0; iSLT < nSLT; ++iSLT) {
      //cout << "<" << PtBinName[iPtBin] << "  " << SLTName[iSLT] << ">" << endl;
      //cout << "arr_r_bChargeID_SLT_CorrUp[iSLT][iPtBin]=" << arr_r_bChargeID_SLT_CorrUp[iSLT][iPtBin] << endl;
      //cout << "arr_r_bChargeID_SLT_CorrDown[iSLT][iPtBin]=" << arr_r_bChargeID_SLT_CorrDown[iSLT][iPtBin] << endl;
      //cout << "arr_r_bChargeID_SLT_UnCorr_bPlusUp[iSLT][iPtBin]=" << arr_r_bChargeID_SLT_UnCorr_bPlusUp[iSLT][iPtBin] << endl;
      //cout << "arr_r_bChargeID_SLT_UnCorr_bPlusDown[iSLT][iPtBin]=" << arr_r_bChargeID_SLT_UnCorr_bPlusDown[iSLT][iPtBin] << endl;
      //cout << "arr_r_bChargeID_SLT_UnCorr_bMinusUp[iSLT][iPtBin]=" << arr_r_bChargeID_SLT_UnCorr_bMinusUp[iSLT][iPtBin] << endl;
      //cout << "arr_r_bChargeID_SLT_UnCorr_bMinusDown[iSLT][iPtBin]=" << arr_r_bChargeID_SLT_UnCorr_bMinusDown[iSLT][iPtBin] << endl;      
      
      //--Correlated--//                                                                                                                                                                                                                     
      FillHistUp("bChargeID_SLT_Corr_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_CorrUp[iSLT][iPtBin],  n_bin,x_min,x_max);
      FillHistDown("bChargeID_SLT_Corr_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_CorrDown[iSLT][iPtBin],  n_bin,x_min,x_max);
      //--UnCorr--//                                                                                                                                                                                                                          
      FillHistUp("bChargeID_SLT_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_UnCorr_bPlusUp[iSLT][iPtBin],  n_bin,x_min,x_max);
      FillHistDown("bChargeID_SLT_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_UnCorr_bPlusDown[iSLT][iPtBin],  n_bin,x_min,x_max);
      FillHistUp("bChargeID_SLT_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_UnCorr_bMinusUp[iSLT][iPtBin],  n_bin,x_min,x_max);
      FillHistDown("bChargeID_SLT_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_UnCorr_bMinusDown[iSLT][iPtBin],  n_bin,x_min,x_max);

    }//[end] SLT loop
    for (int iEtaBin = 0; iEtaBin < nEtaBin; ++iEtaBin){//    for(unsigned int iEtaBin;iEtaBin<nEtaBin;iEtaBin++){
      //--Correlated--//                                                                                                                                                                                                                     
      FillHistUp("bChargeID_Jet_Corr_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_CorrUp[iPtBin][iEtaBin],  n_bin,x_min,x_max);
      FillHistDown("bChargeID_Jet_Corr_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_CorrDown[iPtBin][iEtaBin],  n_bin,x_min,x_max);
      //--UnCorr--//
      FillHistUp("bChargeID_Jet_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_UnCorr_bPlusUp[iPtBin][iEtaBin],  n_bin,x_min,x_max);
      FillHistDown("bChargeID_Jet_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_UnCorr_bPlusDown[iPtBin][iEtaBin],  n_bin,x_min,x_max);
      FillHistUp("bChargeID_Jet_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_UnCorr_bMinusUp[iPtBin][iEtaBin],  n_bin,x_min,x_max);
      FillHistDown("bChargeID_Jet_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_UnCorr_bMinusDown[iPtBin][iEtaBin],  n_bin,x_min,x_max);


    }//[end] etabin loop
  }//[end] ptbin loop
}


void JHAnalyzerBase::FillHistChargeIDEff(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //---SLT n_bin,xbins

  for (int iPtBin = 0; iPtBin < nPtBin; ++iPtBin) {
    for (int iSLT = 0; iSLT < nSLT; ++iSLT) {
      
      //--Correlated--//
      FillHistUp("bChargeID_SLT_Corr_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_CorrUp[iSLT][iPtBin],  n_bin,xbins);
      FillHistDown("bChargeID_SLT_Corr_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_CorrDown[iSLT][iPtBin],  n_bin,xbins);
      //--UnCorr--//
      FillHistUp("bChargeID_SLT_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_UnCorr_bPlusUp[iSLT][iPtBin],  n_bin,xbins);
      FillHistDown("bChargeID_SLT_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_UnCorr_bPlusDown[iSLT][iPtBin],  n_bin,xbins);
      FillHistUp("bChargeID_SLT_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_UnCorr_bMinusUp[iSLT][iPtBin],  n_bin,xbins);
      FillHistDown("bChargeID_SLT_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(SLTName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeID_SLT_UnCorr_bMinusDown[iSLT][iPtBin],  n_bin,xbins);
    }//[end] SLT loop                                                                                                                                                                                                                         
    for (int iEtaBin = 0; iEtaBin < nEtaBin; ++iEtaBin){//    for(unsigned int iEtaBin;iEtaBin<nEtaBin;iEtaBin++){
      //--Correlated--//
      FillHistUp("bChargeID_Jet_Corr_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_CorrUp[iPtBin][iEtaBin],  n_bin,xbins);
      FillHistDown("bChargeID_Jet_Corr_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_CorrDown[iPtBin][iEtaBin],  n_bin,xbins);
      //--UnCorr--//
      FillHistUp("bChargeID_Jet_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_UnCorr_bPlusUp[iPtBin][iEtaBin],  n_bin,xbins);
      FillHistDown("bChargeID_Jet_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_UnCorr_bPlusDown[iPtBin][iEtaBin],  n_bin,xbins);
      FillHistUp("bChargeID_Jet_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_UnCorr_bMinusUp[iPtBin][iEtaBin],  n_bin,xbins);
      FillHistDown("bChargeID_Jet_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+DataEra,   histname, value,this_weight*arr_r_bChargeID_Jet_UnCorr_bMinusDown[iPtBin][iEtaBin],  n_bin,xbins);
    }//[end] etabin loop
  }//[end] ptbin loop
}

///acc

void JHAnalyzerBase::FillHistChargeAcc(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //---SLT n_bin,x_min,x_max
  //cout << "[JHAnalyzerBase::FillHistChargeAcc]" << endl;
  for (int iPtBin = 0; iPtBin < nPtBin; ++iPtBin) {
    for (int iSLT = 0; iSLT < nSLT; ++iSLT) {
      //--Correlated--//
      FillHistUp("bChargeAcc_SLT_Corr_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_CorrUp[iSLT][iPtBin],  n_bin,x_min,x_max);
      FillHistDown("bChargeAcc_SLT_Corr_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_CorrDown[iSLT][iPtBin],  n_bin,x_min,x_max);
      //--UnCorr--//
      FillHistUp("bChargeAcc_SLT_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_UnCorr_bPlusUp[iSLT][iPtBin],  n_bin,x_min,x_max);
      FillHistDown("bChargeAcc_SLT_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_UnCorr_bPlusDown[iSLT][iPtBin],  n_bin,x_min,x_max);
      FillHistUp("bChargeAcc_SLT_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_UnCorr_bMinusUp[iSLT][iPtBin],  n_bin,x_min,x_max);
      FillHistDown("bChargeAcc_SLT_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_UnCorr_bMinusDown[iSLT][iPtBin],  n_bin,x_min,x_max);

    }//[end] SLT loop
    for (int iEtaBin = 0; iEtaBin < nEtaBin; ++iEtaBin){//    for(unsigned int iEtaBin;iEtaBin<nEtaBin;iEtaBin++){
      for(int ij=0; ij < 2; ++ij){
	//--Correlated--//
	FillHistUp("bChargeAcc_Jet_Corr_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_CorrUp[ij][iPtBin][iEtaBin],  n_bin,x_min,x_max);
	FillHistDown("bChargeAcc_Jet_Corr_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_CorrDown[ij][iPtBin][iEtaBin],  n_bin,x_min,x_max);
	//--UnCorr--//
	FillHistUp("bChargeAcc_Jet_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_UnCorr_bPlusUp[ij][iPtBin][iEtaBin],  n_bin,x_min,x_max);
	FillHistDown("bChargeAcc_Jet_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_UnCorr_bPlusDown[ij][iPtBin][iEtaBin],  n_bin,x_min,x_max);
	FillHistUp("bChargeAcc_Jet_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_UnCorr_bMinusUp[ij][iPtBin][iEtaBin],  n_bin,x_min,x_max);
	FillHistDown("bChargeAcc_Jet_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_UnCorr_bMinusDown[ij][iPtBin][iEtaBin],  n_bin,x_min,x_max);
      }//[end]jetchargeid type 
      
    }//[end] etabin loop
  }//[end] ptbin loop
}


void JHAnalyzerBase::FillHistChargeAcc(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //---SLT n_bin,xbins

  for (int iPtBin = 0; iPtBin < nPtBin; ++iPtBin) {
    for (int iSLT = 0; iSLT < nSLT; ++iSLT) {
      
      //--Correlated--//
      FillHistUp("bChargeAcc_SLT_Corr_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_CorrUp[iSLT][iPtBin],  n_bin,xbins);
      FillHistDown("bChargeAcc_SLT_Corr_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_CorrDown[iSLT][iPtBin],  n_bin,xbins);
      //--UnCorr--//
      FillHistUp("bChargeAcc_SLT_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_UnCorr_bPlusUp[iSLT][iPtBin],  n_bin,xbins);
      FillHistDown("bChargeAcc_SLT_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_UnCorr_bPlusDown[iSLT][iPtBin],  n_bin,xbins);
      FillHistUp("bChargeAcc_SLT_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_UnCorr_bMinusUp[iSLT][iPtBin],  n_bin,xbins);
      FillHistDown("bChargeAcc_SLT_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(bChargeAccIDName[iSLT])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_SLT_UnCorr_bMinusDown[iSLT][iPtBin],  n_bin,xbins);
    }//[end] SLT loop
    for (int iEtaBin = 0; iEtaBin < nEtaBin; ++iEtaBin){//    for(unsigned int iEtaBin;iEtaBin<nEtaBin;iEtaBin++){
      for(int ij=0; ij < 2; ++ij){
	//--Correlated--//
	FillHistUp("bChargeAcc_Jet_Corr_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_CorrUp[ij][iPtBin][iEtaBin],  n_bin,xbins);
	FillHistDown("bChargeAcc_Jet_Corr_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_CorrDown[ij][iPtBin][iEtaBin],  n_bin,xbins);
	//--UnCorr--//
	FillHistUp("bChargeAcc_Jet_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_UnCorr_bPlusUp[ij][iPtBin][iEtaBin],  n_bin,xbins);
	FillHistDown("bChargeAcc_Jet_UnCorrPlus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_UnCorr_bPlusDown[ij][iPtBin][iEtaBin],  n_bin,xbins);
	FillHistUp("bChargeAcc_Jet_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_UnCorr_bMinusUp[ij][iPtBin][iEtaBin],  n_bin,xbins);
	FillHistDown("bChargeAcc_Jet_UnCorrMinus_"+TString(PtBinName[iPtBin])+TString(EtaBinName[iEtaBin])+TString(bChargeAccIDName[ij+4])+DataEra,   histname, value,this_weight*arr_r_bChargeAcc_Jet_UnCorr_bMinusDown[ij][iPtBin][iEtaBin],  n_bin,xbins);
      }//[end]jetchargeid type 
    }//[end] etabin loop
  }//[end] ptbin loop
}



//----EffTool----//
void JHAnalyzerBase::FillHistElectronID(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //ElectronID weight//
  //vector<vector<double>> w_ElectronID
  unsigned int setsize = w_ElectronID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("electronID"+DataEra,iset,imem,histname,value,this_weight*r_ElectronID[iset][imem],n_bin,x_min,x_max);
    }
  }
}
void JHAnalyzerBase::FillHistElectronID(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //ElectronID weight//
  //vector<vector<double>> w_ElectronID
  unsigned int setsize = w_ElectronID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("electronID"+DataEra,iset,imem,histname,value,this_weight*r_ElectronID[iset][imem],n_bin,xbins);
    }
  }
}

void JHAnalyzerBase::FillHistElectronRECO(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //ElectronRECO weight//
  //vector<vector<double>> w_ElectronRECO
  unsigned int setsize = w_ElectronRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("electronRECO"+DataEra,iset,imem,histname,value,this_weight*r_ElectronRECO[iset][imem],n_bin,x_min,x_max);
    }
  }
}
void JHAnalyzerBase::FillHistElectronRECO(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //ElectronRECO weight//
  //vector<vector<double>> w_ElectronRECO
  unsigned int setsize = w_ElectronRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("electronRECO"+DataEra,iset,imem,histname,value,this_weight*r_ElectronRECO[iset][imem],n_bin,xbins);
    }
  }
}


void JHAnalyzerBase::FillHistElectronTrigger(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //ElectronTrigger weight//
  //vector<vector<double>> w_ElectronTrigger
  unsigned int setsize = w_ElectronTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("electronTrigger"+DataEra,iset,imem,histname,value,this_weight*r_ElectronTrigger[iset][imem],n_bin,x_min,x_max);
    }
  }
}
void JHAnalyzerBase::FillHistElectronTrigger(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //ElectronTrigger weight//
  //vector<vector<double>> w_ElectronTrigger
  unsigned int setsize = w_ElectronTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("electronTrigger"+DataEra,iset,imem,histname,value,this_weight*r_ElectronTrigger[iset][imem],n_bin,xbins);
    }
  }
}


void JHAnalyzerBase::FillHistMuonID(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //MuonID weight//
  //vector<vector<double>> w_MuonID
  unsigned int setsize = w_MuonID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonID"+DataEra,iset,imem,histname,value,this_weight*r_MuonID[iset][imem],n_bin,x_min,x_max);
    }
  }
}
void JHAnalyzerBase::FillHistMuonID(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //MuonID weight//
  //vector<vector<double>> w_MuonID
  unsigned int setsize = w_MuonID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonID"+DataEra,iset,imem,histname,value,this_weight*r_MuonID[iset][imem],n_bin,xbins);
    }
  }
}



void JHAnalyzerBase::FillHistMuonRECO(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //MuonRECO weight//
  //vector<vector<double>> w_MuonRECO
  unsigned int setsize = w_MuonRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonRECO"+DataEra,iset,imem,histname,value,this_weight*r_MuonRECO[iset][imem],n_bin,x_min,x_max);
    }
  }
}
void JHAnalyzerBase::FillHistMuonRECO(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //MuonRECO weight//
  //vector<vector<double>> w_MuonRECO
  unsigned int setsize = w_MuonRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonRECO"+DataEra,iset,imem,histname,value,this_weight*r_MuonRECO[iset][imem],n_bin,xbins);
    }
  }
}

void JHAnalyzerBase::FillHistMuonTrigger(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //MuonTrigger weight//
  //vector<vector<double>> w_MuonTrigger
  unsigned int setsize = w_MuonTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonTrigger"+DataEra,iset,imem,histname,value,this_weight*r_MuonTrigger[iset][imem],n_bin,x_min,x_max);
    }
  }
}
void JHAnalyzerBase::FillHistMuonTrigger(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //MuonTrigger weight//
  //vector<vector<double>> w_MuonTrigger
  unsigned int setsize = w_MuonTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonTrigger"+DataEra,iset,imem,histname,value,this_weight*r_MuonTrigger[iset][imem],n_bin,xbins);
    }
  }
}

void JHAnalyzerBase::FillHistMuonTrk(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //MuonTrk weight//
  //vector<vector<double>> w_MuonTrk
  unsigned int setsize = w_MuonTrk.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrk[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonTrk"+DataEra,iset,imem,histname,value,this_weight*r_MuonTrk[iset][imem],n_bin,x_min,x_max);
    }
  }
}
void JHAnalyzerBase::FillHistMuonTrk(TString histname, double value, double this_weight, int n_bin, double *xbins){
  //MuonTrk weight//
  //vector<vector<double>> w_MuonTrk
  unsigned int setsize = w_MuonTrk.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrk[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonTrk"+DataEra,iset,imem,histname,value,this_weight*r_MuonTrk[iset][imem],n_bin,xbins);
    }
  }
}




void JHAnalyzerBase::FillHistWeightBase(TString histname,double value,double this_weight,int n_bin,double x_min,double x_max){
  //Nominal//
  AnalyzerCore::FillHist(histname+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
  
  if(IsDATA) return;
  if(!runSys) return;
  //if(scale00test) return;
  //if(scale00test) return;
  //-PU
  FillHistPUSys(histname,value,this_weight,n_bin,x_min,x_max);
  if(pusysonly) return;

  //-PartonShower
  FillHistPSSys(histname,value,this_weight,n_bin,x_min,x_max);
  //prefire//
  FillHistPrefireSys(histname,value,this_weight,n_bin,x_min,x_max);
  //btag
  FillHistBtag(histname,value,this_weight,n_bin,x_min,x_max);
  //btag charge asym factor
  if(mcCorr->use_dasym) FillHistBtagChargeAsym(histname,value,this_weight,n_bin,x_min,x_max);
  if(Is_bChargeIDEffOn) FillHistChargeIDEff(histname,value,this_weight,n_bin,x_min,x_max);
  if(Is_bChargeAccOn) FillHistChargeAcc(histname,value,this_weight,n_bin,x_min,x_max);
  //zptweight
  FillHistZptWeight(histname,value,this_weight,n_bin,x_min,x_max);
  //jetpuid
  FillHistJetPUID(histname,value,this_weight,n_bin,x_min,x_max);
  ///---EffTool--//
  //electronID//
  FillHistElectronID(histname,value,this_weight,n_bin,x_min,x_max);
  //electronRECO
  FillHistElectronRECO(histname,value,this_weight,n_bin,x_min,x_max);
  //electronTrigger
  FillHistElectronTrigger(histname,value,this_weight,n_bin,x_min,x_max);
  
  //muonID
  FillHistMuonID(histname,value,this_weight,n_bin,x_min,x_max);
  //muonRECO
  FillHistMuonRECO(histname,value,this_weight,n_bin,x_min,x_max);
  //MuonTrigger
  FillHistMuonTrigger(histname,value,this_weight,n_bin,x_min,x_max);
  //MuonTrk
  FillHistMuonTrk(histname,value,this_weight,n_bin,x_min,x_max);

  //PDF syst
  FillHistPDF(histname,value,this_weight,n_bin,x_min,x_max);
  //AlphaS
  FillHistAlphaS(histname,value,this_weight,n_bin,x_min,x_max);
  //muF,muR
  FillHistScale(histname,value,this_weight,n_bin,x_min,x_max);
  //topptweight
  FillHistTopPtReweight(histname,value,this_weight,n_bin,x_min,x_max);

}



void JHAnalyzerBase::FillHistWeightBase(TString histname,double value,double this_weight,int n_bin,double *xbins){
  //Nominal//
  AnalyzerCore::FillHist(histname+"/"+ProcessName,value,this_weight,n_bin,xbins);
  
  if(IsDATA) return;
  if(!runSys) return;
  //if(scale00test) return;
  //-PU
  FillHistPUSys(histname,value,this_weight,n_bin,xbins);
  if(pusysonly) return;

  //-PartonShower
  FillHistPSSys(histname,value,this_weight,n_bin,xbins);
  //prefire//
  FillHistPrefireSys(histname,value,this_weight,n_bin,xbins);
  //btag
  FillHistBtag(histname,value,this_weight,n_bin,xbins);
  //btag charge asym factor
  if(mcCorr->use_dasym) FillHistBtagChargeAsym(histname,value,this_weight,n_bin,xbins);
  //bChargeID
  if(Is_bChargeIDEffOn) FillHistChargeIDEff(histname,value,this_weight,n_bin,xbins);
  //zptweight
  FillHistZptWeight(histname,value,this_weight,n_bin,xbins);
  //jetpuid
  FillHistJetPUID(histname,value,this_weight,n_bin,xbins);
  ///---EffTool--//
  //electronID//
  FillHistElectronID(histname,value,this_weight,n_bin,xbins);
  //electronRECO
  FillHistElectronRECO(histname,value,this_weight,n_bin,xbins);
  //electronTrigger
  FillHistElectronTrigger(histname,value,this_weight,n_bin,xbins);
  
  //muonID
  FillHistMuonID(histname,value,this_weight,n_bin,xbins);
  //muonRECO
  FillHistMuonRECO(histname,value,this_weight,n_bin,xbins);
  //MuonTrigger
  FillHistMuonTrigger(histname,value,this_weight,n_bin,xbins);
  //MuonTrk
  FillHistMuonTrk(histname,value,this_weight,n_bin,xbins);

  //PDF syst
  FillHistPDF(histname,value,this_weight,n_bin,xbins);
  //AlphaS
  FillHistAlphaS(histname,value,this_weight,n_bin,xbins);
  //muF,muR
  FillHistScale(histname,value,this_weight,n_bin,xbins);
  //topptweight
  FillHistTopPtReweight(histname,value,this_weight,n_bin,xbins);

}




void JHAnalyzerBase::SetSysSimpleMuon(int direction){
  sysname_current="muonscale";
  sysidx1_current="0";
  if(direction>0){
    sysidx2_current="Up";
    AllMuons=AllMuons_plus;
    std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
  }
  else if(direction<0){
    sysidx2_current="Down";
    AllMuons=AllMuons_minus;
    std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);

  }
  else{
    cout << "[JHAnalyzerBase::SetSysSimpleMuon]wrong direction=" << direction << endl;
    exit(ENODATA);

  }
  std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
  AllElectrons=AllElectrons_roch;
  std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);  
  AllJets=AllJets_raw;
  std::sort(AllJets.begin(), AllJets.end(), PtComparing);  
  CurrentMET=UpdateMETByMuonScale(CurrentMET_roch);  
  
}

void JHAnalyzerBase::SetSysSimpleElectron(int direction){
  sysname_current="electronscale";
  sysidx1_current="0";
  if(direction>0){
    sysidx2_current="Up";
    AllElectrons=AllElectrons_plus;
    std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
  }
  else if(direction<0){
    sysidx2_current="Down";
    AllElectrons=AllElectrons_minus;
    std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
      
  }
  else{
    cout << "[JHAnalyzerBase::SetSysSimpleElectron]wrong direction=" << direction << endl;
    exit(ENODATA);

  }
  std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
  AllMuons=AllMuons_roch;
  std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
  AllJets=AllJets_raw;
  CurrentMET=UpdateMETByElectronScale(CurrentMET_roch);  
  
}
void JHAnalyzerBase::SetSys(MomentumVar _sys){
  sysname_current=_sys.name;

  //sysdir_current=_sys.dir;
  sysidx1_current="0";

  sysidx2_current=_sys.dir;

  if(_sys.jes!=0){
    //AllMuons=AllMuons_raw;
    AllMuons=AllMuons_roch;
    std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
    //AllElectrons=AllElectrons_raw;
    AllElectrons=AllElectrons_roch;
    std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
    AllJets=ScaleJets(AllJets_raw,_sys.jes);
    std::sort(AllJets.begin(), AllJets.end(), PtComparing);
    CurrentMET=UpdateMETByJetScale(CurrentMET_roch,_sys.jes); 
  }
  else if(_sys.jer!=0){
    //AllMuons=AllMuons_raw;
    AllMuons=AllMuons_roch;
    std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
    //AllElectrons=AllElectrons_raw;
    AllElectrons=AllElectrons_roch;
    std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
    AllJets=SmearJets(AllJets_raw,_sys.jer);
    std::sort(AllJets.begin(), AllJets.end(), PtComparing);
    CurrentMET=UpdateMETByJetSmear(CurrentMET_roch,_sys.jer);
  }
  else if(_sys.met!=0){
    //AllMuons=AllMuons_raw;
    AllMuons=AllMuons_roch;
    std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
    //AllElectrons=AllElectrons_raw;
    AllElectrons=AllElectrons_roch;
    std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
    AllJets=AllJets_raw;
    std::sort(AllJets.begin(), AllJets.end(), PtComparing);
    CurrentMET=GetShiftedMET(_sys.met);
  }
  else{
    cout << "[JHAnalyzerBase::SetSyst] No systematic shift for ->" << sysname_current << endl;
  }


}
//vMuonMomentumVar
void JHAnalyzerBase::SetupSimpleMuonMomentumVar(){
  AllMuons_plus=AllMuons_raw;
  AllMuons_minus=AllMuons_raw;
  unsigned int muonsize=AllMuons_raw.size();
  for(unsigned int i=0;i<muonsize;i++){
    double rc_nom= MuonMomentumCorrection(AllMuons_raw[i]);//nominal rochester corr
    double drc_stat=0.;
    double drc_sys_plus=0.;
    double drc_sys_minus=0.;
    //---For variations---//
    for(const auto& _vsys : vMuonMomentumVar){
      bool isStat=0;
      if(_vsys.size() > 10) isStat=1;
      if(isStat){
	double sum_rc=0;
	double sum_rc2=0;
	for(const auto &_sys : _vsys){//for replica elements
	  double this_rc = MuonMomentumCorrection(AllMuons_raw[i],_sys.idx1,_sys.idx2);
	  sum_rc+=this_rc;
	  sum_rc2+=pow(this_rc,2);
	}
	double mean_rc=sum_rc/_vsys.size();
	double mean_rc2=sum_rc2/_vsys.size();
	drc_stat=sqrt(mean_rc2-pow(mean_rc,2)); //standard deviation
      }else{
	for(const auto &_sys : _vsys){
	  double this_rc = MuonMomentumCorrection(AllMuons_raw[i],_sys.idx1,_sys.idx2);
	  if(this_rc>rc_nom){
	    drc_sys_plus=sqrt(pow(drc_sys_plus,2) + pow(rc_nom-this_rc,2));
	  }else{
	    drc_sys_minus=sqrt(pow(drc_sys_minus,2) + pow(rc_nom-this_rc,2));
	  }	  
	}//[END] for _sys
      }//[END] if not isStat
    }//[END]_vsys
    //---now drc_stat and drc_sys_plus,drc_sys_minus are set
    double drc_plus=sqrt( pow(drc_stat,2) + pow(drc_sys_plus,2));
    double drc_minus=sqrt( pow(drc_stat,2) + pow(drc_sys_minus,2));
    /*
    cout << "------muon----" << endl;
    cout << "pt=" << AllMuons_raw[i].MiniAODPt() << endl;
    cout << "drc_plus=" << drc_plus << endl;
    cout << "drc_minus=" << drc_minus << endl;
    cout << "drc_stat=" << drc_stat << endl;
    cout << "drc_sys_plus=" << drc_sys_plus << endl;
    cout << "drc_sys_minus=" << drc_sys_minus << endl;
    */
    /*
    void AnalyzerCore::FillHist(TString histname,
				double value_x, double value_y,
				double weight,
				int n_binx, double x_min, double x_max,
				int n_biny, double y_min, double y_max){
    */

    AnalyzerCore::FillHist((TString)"x_muonPt__y_rel_drc_plus",
	     AllMuons_raw[i].MiniAODPt(),drc_plus/rc_nom,1.,
	     100,0.,200.,
	     100,0.,2.);

    AnalyzerCore::FillHist((TString)"x_muonPt__y_rel_drc_minus",
	     AllMuons_raw[i].MiniAODPt(),drc_minus/rc_nom,1.,
	     100,0.,200.,
	     100,0.,2.);

    AllMuons_plus[i].SetPtEtaPhiM(AllMuons_raw[i].MiniAODPt()*(rc_nom+drc_plus), AllMuons_raw[i].Eta(), AllMuons_raw[i].Phi(),AllMuons_raw[i].M());
    AllMuons_minus[i].SetPtEtaPhiM(AllMuons_raw[i].MiniAODPt()*(max(0.,rc_nom-drc_minus)), AllMuons_raw[i].Eta(), AllMuons_raw[i].Phi(),AllMuons_raw[i].M());
  }//[END] for ith muon
  //std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
}


void JHAnalyzerBase::SetupSimpleElectronMomentumVar(){
  AllElectrons_plus=AllElectrons_raw;
  AllElectrons_minus=AllElectrons_raw;
  unsigned int electronsize=AllElectrons_raw.size();
  for(unsigned int i=0;i<electronsize;i++){
    double rc_nom= ElectronEnergyCorrection(AllElectrons_raw[i]);//nominal rochester corr
    double drc_stat=0.;
    double drc_sys_plus=0.;
    double drc_sys_minus=0.;
    //---For variations---//
    for(const auto& _vsys : vElectronMomentumVar){
      bool isStat=0;
      if(_vsys.size() > 10) isStat=1;
      if(isStat){
	double sum_rc=0;
	double sum_rc2=0;
	for(const auto &_sys : _vsys){//for replica elements
	  double this_rc = ElectronEnergyCorrection(AllElectrons_raw[i],_sys.idx1,_sys.idx2);
	  sum_rc+=this_rc;
	  sum_rc2+=pow(this_rc,2);
	}
	double mean_rc=sum_rc/_vsys.size();
	double mean_rc2=sum_rc2/_vsys.size();
	drc_stat=sqrt(mean_rc2-pow(mean_rc,2)); //standard deviation
      }else{
	for(const auto &_sys : _vsys){
	  double this_rc = ElectronEnergyCorrection(AllElectrons_raw[i],_sys.idx1,_sys.idx2);
	  if(this_rc>rc_nom){
	    drc_sys_plus=sqrt(pow(drc_sys_plus,2) + pow(rc_nom-this_rc,2));
	  }else{
	    drc_sys_minus=sqrt(pow(drc_sys_minus,2) + pow(rc_nom-this_rc,2));
	  }	  
	}//[END] for _sys
      }//[END] if not isStat
    }//[END]_vsys
    //---now drc_stat and drc_sys_plus,drc_sys_minus are set
    double drc_plus=sqrt( pow(drc_stat,2) + pow(drc_sys_plus,2));
    double drc_minus=sqrt( pow(drc_stat,2) + pow(drc_sys_minus,2));
    AllElectrons_plus[i]*=(rc_nom+drc_plus);
    AllElectrons_minus[i]*=(max(0.,rc_nom-drc_minus));
    /*
    cout << "------electron----" << endl;
    cout << "pt=" << AllElectrons_raw[i].UncorrPt() << endl;
    cout << "drc_plus=" << drc_plus << endl;
    cout << "drc_minus=" << drc_minus << endl;
    cout << "drc_stat=" << drc_stat << endl;
    cout << "drc_sys_plus=" << drc_sys_plus << endl;
    cout << "drc_sys_minus=" << drc_sys_minus << endl;
    */
    AnalyzerCore::FillHist("x_electronPt__y_rel_drc_plus",
	     AllElectrons_raw[i].UncorrPt(),drc_plus/rc_nom,1.,
	     100,0.,200.,
	     100,0.,2.);

    AnalyzerCore::FillHist("x_electronPt__y_rel_drc_minus",
	     AllElectrons_raw[i].UncorrPt(),drc_minus/rc_nom,1,
	     100,0,200,
	     100,0,2);

  }//[END] for ith electron
  //std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
}



void JHAnalyzerBase::SetSys(MuonMomentumVar _sys){
  sysname_current=_sys.name;

  
  AllMuons=MuonMomentumCorrection(AllMuons_raw,_sys.idx1,_sys.idx2);
  //std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
  AllElectrons=AllElectrons_roch;
  std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
  AllJets=AllJets_raw;
  std::sort(AllJets.begin(), AllJets.end(), PtComparing);
  CurrentMET=UpdateMETByMuonScale(CurrentMET_roch);
  sysidx1_current=std::to_string(_sys.idx1);
  sysidx2_current=std::to_string(_sys.idx2);
  /*
  //jhchoitemp
  if(!EvtToTest) return;
  if(_sys.idx1==0 && _sys.idx2==0){
    cout << "----Print muon for 0,0 Syst----" << endl;
    for(const auto& muon : AllMuons){
      cout << "muon.Pt()=" << muon.Pt() << endl;
      cout << "muon.Eta()=" << muon.Eta() << endl;
      cout << "muon.Phi()=" << muon.Phi() << endl;
    }
    cout << "CurrentMET=" << CurrentMET.Pt() << "CurrentMET_Phi=" << CurrentMET.Phi() << endl;
    for(const auto& jet : AllJets){
      cout << "jet.Pt()=" << jet.Pt() << endl;
      cout << "jet.Eta()=" << jet.Eta() << endl;
      cout << "jet.Phi()=" << jet.Phi() << endl;
    }
  }
  */
  
}

void JHAnalyzerBase::SetSys(ElectronMomentumVar _sys){
  sysname_current=_sys.name;
  //sysidx1_current=_sys.idx1;
  //sysidx2_current=_sys.idx2;

  AllMuons=AllMuons_roch;
  std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
  AllElectrons=ElectronEnergyCorrection(AllElectrons_raw,_sys.idx1,_sys.idx2);
  //std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);

  AllJets=AllJets_raw;
  std::sort(AllJets.begin(), AllJets.end(), PtComparing);
  CurrentMET=UpdateMETByElectronScale(CurrentMET_roch);
  sysidx1_current=std::to_string(_sys.idx1);
  sysidx2_current=std::to_string(_sys.idx2);

  /*
  //jhchoitemp
  if(!EvtToTest) return;
  if(_sys.idx1==0 && _sys.idx2==0){
    cout << "----Print muon for 0,0 Syst----" << endl;
    for(const auto& muon : AllMuons){
      cout << "muon.Pt()=" << muon.Pt() << endl;
      cout << "muon.Eta()=" << muon.Eta() << endl;
      cout << "muon.Phi()=" << muon.Phi() << endl;
    }                                                                                                                                                                             

    cout << "----Print electron for 0,0 Syst----" << endl;
    for(const auto& electron : AllElectrons){
      cout << "electron.Pt()=" << electron.Pt() << endl;
      cout << "electron.Eta()=" << electron.Eta() << endl;
      cout << "electron.Phi()=" << electron.Phi() << endl;
    }
    cout << "CurrentMET=" << CurrentMET.Pt() << "CurrentMET_Phi=" << CurrentMET.Phi() << endl;
    cout << "CurrentMET_roch=" << CurrentMET_roch.Pt() << "CurrentMET_Phi_roch=" << CurrentMET_roch.Phi() << endl;
    for(const auto& jet : AllJets){
      cout << "jet.Pt()=" << jet.Pt() << endl;
      cout << "jet.Eta()=" << jet.Eta() << endl;
      cout << "jet.Phi()=" << jet.Phi() << endl;
    }
  }
  */
  
}



void JHAnalyzerBase::InitAllObjects(){
  //cout << "[JHAnalyzerBase::InitAllObjects] init to nominal objects" << endl;
  AllMuons_raw=GetAllMuons();
  AllMuons_roch=MuonMomentumCorrection(AllMuons_raw);
  AllMuons=AllMuons_roch;
  //std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);//no need to sort again
  AllElectrons_raw=GetAllElectrons();
  AllElectrons_roch=ElectronEnergyCorrection(AllElectrons_raw);
  AllElectrons=AllElectrons_roch;
  //std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
  AllJets_raw=GetAllJets();
  AllJets=AllJets_raw;
  std::sort(AllJets.begin(), AllJets.end(), PtComparing);
  
  InitMET();
  /*
  if(!EvtToTest) return;
  //jhchoitemp
  cout << "---Nominal---" << endl;
  for(const auto& muon : AllMuons){
    cout << "muon.Pt()=" << muon.Pt() << endl;
    cout << "muon.Eta()=" << muon.Eta() << endl;
    cout << "muon.Phi()=" << muon.Phi() << endl;
  }
  for(const auto& electron : AllElectrons){
    cout << "electron.Pt()=" << electron.Pt() << endl;
    cout << "electron.Eta()=" << electron.Eta() << endl;
    cout << "electron.Phi()=" << electron.Phi() << endl;
  }

  cout << "CurrentMET=" << CurrentMET.Pt() << "CurrentMET_Phi=" << CurrentMET.Phi() << endl;
  for(const auto& jet : AllJets){
    cout << "jet.Pt()=" << jet.Pt() << endl;
    cout << "jet.Eta()=" << jet.Eta() << endl;
    cout << "jet.Phi()=" << jet.Phi() << endl;
  }
  */
}

void JHAnalyzerBase::InitMET(){

  //----JER smearing propation to all types of met
  InitMETSmeared();
  if(!IsDATA)UpdateMETBySmearNominal();

  
  TLorentzVector CurrentMET_raw;
  if(UsePfMET){
    if(UsePhiCorrMET){
      CurrentMET_raw.SetPtEtaPhiM(pfMET_Type1_PhiCor_JerSmear_pt,0.,pfMET_Type1_PhiCor_JerSmear_phi,0.);
    }
    else{
      CurrentMET_raw.SetPtEtaPhiM(pfMET_Type1_JerSmear_pt,0.,pfMET_Type1_JerSmear_phi,0.);
    }
  }
  else{
    if(UsePhiCorrMET){
      CurrentMET_raw.SetPtEtaPhiM(PuppiMET_Type1_PhiCor_JerSmear_pt,0.,PuppiMET_Type1_PhiCor_JerSmear_phi,0.);
    }else{
      CurrentMET_raw.SetPtEtaPhiM(PuppiMET_Type1_JerSmear_pt,0.,PuppiMET_Type1_JerSmear_phi,0.);
    }
  }
  CurrentMET_roch = UpdateMETByMuonRochCorr(CurrentMET_raw,AllMuons_raw);
  CurrentMET=CurrentMET_roch;
}




TLorentzVector JHAnalyzerBase::UpdateMETByMuonRochCorr(const TLorentzVector &met_orig, const vector<Muon> &muons){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& muon : muons){
    px_orig+= muon.MiniAODPt()*TMath::Cos(muon.Phi());
    py_orig+= muon.MiniAODPt()*TMath::Sin(muon.Phi());

    px_corrected += muon.Px();
    py_corrected += muon.Py();
    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}


TLorentzVector JHAnalyzerBase::UpdateMETByMuonElectronRochCorr(const TLorentzVector &met_orig, const vector<Muon> &muons,const vector<Electron> &electrons){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& muon : muons){
    px_orig+= muon.MiniAODPt()*TMath::Cos(muon.Phi());
    py_orig+= muon.MiniAODPt()*TMath::Sin(muon.Phi());

    px_corrected += muon.Px();
    py_corrected += muon.Py();
    
  }
  for(const auto& electron : electrons){
    px_orig+= electron.UncorrPt()*TMath::Cos(electron.Phi());
    py_orig+= electron.UncorrPt()*TMath::Sin(electron.Phi());

    px_corrected += electron.Px();
    py_corrected += electron.Py();
    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}


TLorentzVector JHAnalyzerBase::UpdateMETByMuonScale(const TLorentzVector &met_orig, int sys){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& muon : AllMuons_raw){
    px_orig+= muon.Px();
    py_orig+= muon.Py();

    px_corrected += muon.MomentumShift(sys)*TMath::Cos(muon.Phi());
    py_corrected += muon.MomentumShift(sys)*TMath::Sin(muon.Phi());
    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}

TLorentzVector JHAnalyzerBase::UpdateMETByMuonScale(const TLorentzVector &met_orig){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& muon : AllMuons_roch){//nominal rochcorr
    px_orig+= muon.Px();
    py_orig+= muon.Py();
  }
  for(const auto& muon : AllMuons){//after shift
    px_corrected += muon.Px();
    py_corrected += muon.Py();
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}


TLorentzVector JHAnalyzerBase::UpdateMETByElectronScale(const TLorentzVector &met_orig, int sys){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& electron : AllElectrons_raw){
    px_orig+= electron.Px();
    py_orig+= electron.Py();

    px_corrected += electron.Px()*electron.EnShift(sys);
    py_corrected += electron.Py()*electron.EnShift(sys);

    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}
TLorentzVector JHAnalyzerBase::UpdateMETByElectronScale(const TLorentzVector &met_orig){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& electron : AllElectrons_roch){
    px_orig+= electron.Px();
    py_orig+= electron.Py();
  }
  for(const auto& electron : AllElectrons){
    px_corrected += electron.Px();
    py_corrected += electron.Py();
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}


TLorentzVector JHAnalyzerBase::UpdateMETByJetScale(const TLorentzVector &met_orig, int sys){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& jet : AllJets_raw){
    px_orig+= jet.Px();
    py_orig+= jet.Py();

    px_corrected += jet.Px()*jet.EnShift(sys);
    py_corrected += jet.Py()*jet.EnShift(sys);

    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}

TLorentzVector JHAnalyzerBase::UpdateMETByJetSmear(const TLorentzVector &met_orig, int sys){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& jet : AllJets_raw){
    px_orig+= jet.Px();
    py_orig+= jet.Py();

    px_corrected += jet.Px()*jet.ResShift(sys);
    py_corrected += jet.Py()*jet.ResShift(sys);

    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}

TLorentzVector JHAnalyzerBase::GetShiftedMET(int sys){
  //MET shift by Uncluster part
  //UnclusteredEnUp=10, UnclusteredEnDown=11,
  int idx=-1;
  if(sys==1){
    idx=10;
  }
  else if (sys==-1){
    idx=11;
  }
  else{
    cout << "no MET shift for sys==" << sys << endl;
  }
  
  double pt=0;
  double phi=0;
  TLorentzVector this_met;  
  if(UsePfMET){
    if(UsePhiCorrMET){
      pt=pfMET_Type1_PhiCor_pt_shifts->at(idx);
      phi=pfMET_Type1_PhiCor_phi_shifts->at(idx);
      this_met.SetPtEtaPhiM(pt,0,phi,0);
    }
    else{
      pt=pfMET_Type1_pt_shifts->at(idx);
      phi=pfMET_Type1_phi_shifts->at(idx);
      this_met.SetPtEtaPhiM(pt,0,phi,0);
    }
  } 
  else{//puppi
    if(UsePhiCorrMET){
      //----No sys yet!!!
      pt=PuppiMET_Type1_PhiCor_pt;
      phi=PuppiMET_Type1_PhiCor_phi;
      this_met.SetPtEtaPhiM(pt,0,phi,0);
    }
    else{
      pt=PuppiMET_Type1_pt_shifts->at(idx);
      phi=PuppiMET_Type1_phi_shifts->at(idx);
      this_met.SetPtEtaPhiM(pt,0,phi,0);
      
    }
  }
  return this_met;


}



void JHAnalyzerBase::SetupSingleLeptonChannel(){

  //common setup
  MuonID="POGMedium";
  MuonRecoSFKey="Muon_RECO";
  MuonIDSFKey="Muon_MediumID_trkIsoLoose";
  MuonTrkSFKey="Muon_Tracking";
  MuonDZSFKey="";

  ElectronID="passMediumID";
  ElectronRecoSFKey="Electron_RECO";
  ElectronIDSFKey="Electron_MediumID";
  ElectronDZSFKey="";

  if(DataYear==2016){
    if (DataEra=="2016preVFP"){
      MuonID="POGMedium_hip";
    }
    MuonTriggerNames = {"HLT_IsoMu24_v","HLT_IsoTkMu24_v"};
    MuonTriggerSFKeys={"IsoMu24_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 27.;
    TriggerSafeCut_muon2 = -1.;


    ElectronTriggerNames = {"HLT_Ele27_WPTight_Gsf_v"};
    ElectronTriggerSFKeys = {"Ele27_MediumID"};
    TriggerSafeCut_electron1 = 30.;
    TriggerSafeCut_electron2 = -1.;


  }
  else if(DataYear==2017){
    MuonTriggerNames = {"HLT_IsoMu24_v","HLT_IsoMu27_v"};
    MuonTriggerSFKeys={"IsoMu24_MediumID_trkIsoLoose","IsoMu27_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 30.;
    TriggerSafeCut_muon2 = -1.;

    ElectronTriggerNames = {"HLT_Ele27_WPTight_Gsf_v","HLT_Ele32_WPTight_Gsf_v"};
    ElectronTriggerSFKeys = {"Ele27_MediumID","Ele32_MediumID"};
    TriggerSafeCut_electron1 = 35.;
    TriggerSafeCut_electron2 = -1.;

  }

  else if(DataYear==2018){
    MuonTriggerNames = {"HLT_IsoMu24_v"};
    MuonTriggerSFKeys={"IsoMu24_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 27.;
    TriggerSafeCut_muon2 = -1.;

    ElectronTriggerNames = {"HLT_Ele28_WPTight_Gsf_v","HLT_Ele32_WPTight_Gsf_v"};
    ElectronTriggerSFKeys = {"Ele28_MediumID","Ele32_MediumID"};
    TriggerSafeCut_electron1 = 35.;
    TriggerSafeCut_electron2 = -1.;


  }
  SetIsDoubleLeptonTrigger();
  PrintSFStructure();
}

void JHAnalyzerBase::SetupDiLeptonChannel(){
  cout << "[SetupDiLeptonChannel] " << DataYear << "  " << endl;
  cout << "[SetupDiLeptonChannel] " << GetEra() << "  " << endl;

  //common setup
  MuonID="POGMedium";
  MuonRecoSFKey="Muon_RECO";
  MuonIDSFKey="Muon_MediumID_trkIsoLoose";
  MuonTrkSFKey="Muon_Tracking";
  MuonDZSFKey="";

  ElectronID="passMediumID";
  ElectronRecoSFKey="Electron_RECO";
  ElectronIDSFKey="Electron_MediumID";
  ElectronDZSFKey="";


  if(DataYear==2016){
    ElectronDZSFKey="DZ_MediumID";
    if (DataEra=="2016preVFP"){
      MuonID="POGMedium_hip";
    }else{
      MuonDZSFKey="DZ_MediumID_trkIsoLoose";
    }
    MuonTriggerNames={"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v","HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v","HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"};
    MuonTriggerSFKeys={"Mu17Leg1_MediumID_trkIsoLoose","Mu8Leg2_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 20.;
    TriggerSafeCut_muon2 = 10.;
    


    ElectronTriggerNames = {"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"};
    ElectronTriggerSFKeys = {"Ele23Leg1_MediumID","Ele12Leg2_MediumID"};
    TriggerSafeCut_electron1 = 25.;
    TriggerSafeCut_electron2 = 15.;
    ElectronDZSFKey="DZ_MediumID";

  }
  else if(DataYear==2017){
    MuonTriggerNames = {"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v"};
    MuonTriggerSFKeys={"Mu17Leg1_MediumID_trkIsoLoose","Mu8Leg2_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 20.;
    TriggerSafeCut_muon2 = 10.;
    MuonDZSFKey="DZ_MediumID_trkIsoLoose";

    ElectronTriggerNames = {"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"};
    ElectronTriggerSFKeys = {"Ele23Leg1_MediumID","Ele12Leg2_MediumID"};
    TriggerSafeCut_electron1 = 25.;
    TriggerSafeCut_electron2 = 15.;

  }

  else if(DataYear==2018){
    MuonTriggerNames = {"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v"};
    MuonTriggerSFKeys={"Mu17Leg1_MediumID_trkIsoLoose","Mu8Leg2_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 20.;
    TriggerSafeCut_muon2 = 10.;
    MuonDZSFKey="DZ_MediumID_trkIsoLoose";

    ElectronTriggerNames = {"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"};
    ElectronTriggerSFKeys = {"Ele23Leg1_MediumID","Ele12Leg2_MediumID"};
    TriggerSafeCut_electron1 = 25.;
    TriggerSafeCut_electron2 = 15.;


  }

  SetIsDoubleLeptonTrigger();
  cout << "[SetupDiLeptonChannel] " << DataYear << "  " << endl;
  PrintSFStructure();

    
}

void JHAnalyzerBase::PrintSFStructure(){
  cout << "MuonRecoSFKey" << endl;
  fEff->PrintStructure(MuonRecoSFKey);
  cout << "MuonIDSFKey" << endl;
  fEff->PrintStructure(MuonIDSFKey);
  cout << "MuonTrkSFKey" << endl;
  fEff->PrintStructure(MuonTrkSFKey);
  cout << "MuonTriggerSFKeys[0]" << endl;
  fEff->PrintStructure(MuonTriggerSFKeys[0]);

  cout << "ElectronRecoSFKey" << endl;
  fEff->PrintStructure(ElectronRecoSFKey);
  cout << "ElectronIDSFKey" << endl;
  fEff->PrintStructure(ElectronIDSFKey);
  cout << "ElectronTriggerSFKeys[0]" << endl;
  fEff->PrintStructure(ElectronTriggerSFKeys[0]);
}

void JHAnalyzerBase::SetIsDoubleLeptonTrigger(){
  IsDoubleMuonTrigger=false;
  if( TriggerSafeCut_muon2 > 0. && TriggerSafeCut_muon1 > 0. ){
    IsDoubleMuonTrigger=true;
  }
  IsDoubleElectronTrigger=false;
  if( TriggerSafeCut_electron2 > 0. && TriggerSafeCut_electron1 >0. ){
    IsDoubleElectronTrigger=true;
  }
  cout << "IsDoubleMuonTrigger=" << IsDoubleMuonTrigger << endl; 
  cout << "IsDoubleElectronTrigger=" << IsDoubleElectronTrigger << endl; 

  cout << "---Use Following Muon triggerkeys ---" << endl;
  for (const auto& name : MuonTriggerSFKeys){
    cout << name << endl;
  }

  cout << "---Use Following Electron triggerkeys ---" << endl;
  for (const auto& name : ElectronTriggerSFKeys){
    cout << name << endl;
  }
  
  //----OR Trigger----//
  IsORMuonTrigger=false;
  if(!IsDoubleMuonTrigger){// SingleMuonTrigger
    if(MuonTriggerNames.size()==2  && MuonTriggerSFKeys.size()==2) IsORMuonTrigger=true;
  }
  
  IsORElectronTrigger=false;
  if(!IsDoubleElectronTrigger){// SingleMuonTrigger
    if(ElectronTriggerNames.size()==2  && ElectronTriggerSFKeys.size()==2) IsORElectronTrigger=true;
  }
  
  cout << "IsORMuonTrigger=" << IsORMuonTrigger << endl; 
  cout << "IsORElectronTrigger=" << IsORElectronTrigger << endl; 
}

//---Get Muon index-base. For SingleMuon Channel
/*
int JHAnalyzerBase::GetIdxSingleMuReco(double ptmin, double etacut, double ptveto){

  unsigned int muonsize = AllMuons.size();
  unsigned int nselected= 0;
  int muonidx=-1;
  //vector<Muon> _vmuons;
  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double eta=AllMuons[i].Eta();
    if(fabs(eta) > etacut) continue;
    double pt=AllMuons[i].Pt();
    if(pt < ptveto) continue;
    bool passLooseID=AllMuons[i].PassID("POGLoose");
    if (!passLooseID) continue;
    bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!passISO) continue;
    //----Loose ID Muon passing pt/eta/iso cut
    nselected+=1;
    if(nselected>1) return -1;
    //--For One selected as prompt lepton--//
    if(pt<ptmin) return -1;
    if(!AllMuons[i].PassID("POGMedium")) return -1;
    muonidx=i;
  }
  if (nselected==0) return -1;
  //---GetSF--//
  vector<int> v_muonidx={muonidx};
  SetMuonSFs(v_muonidx);
  return muonidx;

}
*/
//---Get Muon Object-Base. For SingleMuon Channel.
//https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2
vector<Muon> JHAnalyzerBase::GetSingleMuReco(double ptmin, double etacut, double ptveto, double ptveto2, double etacut2){//ptveto2,etacut2 == for electron 
  unsigned int nselected= 0;
  vector<Muon> _v_muons;

  //---Electron veto first
  for(const auto& electron : AllElectrons){
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto2) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut2) continue;
    //bool passID=AllElectrons[i].PassID("passLooseID");
    if(!electron.PassID("passVetoID")) continue;
    return {};
  }
  //unsigned int muonsize = AllMuons.size();

  //for(unsigned int i = 0 ; i < muonsize; i++ ){
  for(const auto &muon : AllMuons){
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    //double pt=AllMuons[i].Pt();
    if(muon.Pt() < ptveto) continue;
    //bool passLooseID=AllMuons[i].PassID("POGLoose");
    if (!muon.PassID("POGLoose")) continue;
    //bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //----Loose ID Muon passing pt/eta/iso cut
    nselected+=1;
    if(nselected>1) return {};
    //--For One selected as prompt lepton--//
    if(muon.Pt()<ptmin) return {};
    if(!muon.PassID(MuonID)) return {};
    //muonidx=i;
    _v_muons.push_back(muon);
  }
  if (nselected==0) return {};
  //---GetSF--//
  //vector<int> v_muonidx={muonidx};
  //SetMuonSFs(v_muonidx);
  SetMuonSFs({_v_muons[0]});
  return {_v_muons[0]};

}



vector<int> JHAnalyzerBase::GetSingleMuRecoIdx(double ptmin, double etacut, double ptveto, double ptveto2, double etacut2){//ptveto2,etacut2 == for electron 
  unsigned int nselected= 0;
  vector<Muon> _v_muons;
  vector<int> _v_muonidx;

  //---Electron veto first
  for(const auto& electron : AllElectrons){
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto2) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut2) continue;
    //bool passID=AllElectrons[i].PassID("passLooseID");
    if(!electron.PassID("passVetoID")) continue;
    return {};
  }
  //unsigned int muonsize = AllMuons.size();

  //for(unsigned int i = 0 ; i < muonsize; i++ ){
  int this_muonidx=-1;
  for(const auto &muon : AllMuons){
    this_muonidx+=1;
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    //double pt=AllMuons[i].Pt();
    if(muon.Pt() < ptveto) continue;
    //bool passLooseID=AllMuons[i].PassID("POGLoose");
    if (!muon.PassID("POGLoose")) continue;
    //bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //----Loose ID Muon passing pt/eta/iso cut
    nselected+=1;
    if(nselected>1) return {};
    //--For One selected as prompt lepton--//
    if(muon.Pt()<ptmin) return {};
    if(!muon.PassID(MuonID)) return {};
    //muonidx=i;
    _v_muons.push_back(muon);
    _v_muonidx.push_back(this_muonidx);
  }
  if (nselected==0) return {};
  //---GetSF--//
  //vector<int> v_muonidx={muonidx};
  //SetMuonSFs(v_muonidx);
  SetMuonSFs({_v_muons[0]});
  return {_v_muonidx[0]};

}






vector<Muon> JHAnalyzerBase::GetSingleMuRecoNoVeto(double ptmin, double etacut){

  //unsigned int muonsize = AllMuons.size();
  unsigned int nselected= 0;
  vector<Muon> _v_muons;
  //for(unsigned int i = 0 ; i < muonsize; i++ ){
  for(const auto &muon : AllMuons){
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    if(muon.Pt()<ptmin) continue;
    if(!muon.PassID(MuonID)) continue;
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    nselected+=1;
    _v_muons.push_back(muon);
  }
  if (nselected<1) return {};
  //---GetSF--//
  SetMuonSFs({_v_muons[0]});
  return {_v_muons[0]};

}


vector<int> JHAnalyzerBase::GetSingleMuRecoNoVetoIdx(double ptmin, double etacut){

  //unsigned int muonsize = AllMuons.size();
  unsigned int nselected= 0;
  vector<int> _v_muonidx;
  vector<Muon> _v_muons;
  //for(unsigned int i = 0 ; i < muonsize; i++ ){
  int this_muonidx=-1;
  for(const auto &muon : AllMuons){
    this_muonidx+=1;
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    if(muon.Pt()<ptmin) continue;
    if(!muon.PassID(MuonID)) continue;
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    nselected+=1;
    _v_muonidx.push_back(this_muonidx);
    _v_muons.push_back(muon);
  }
  if (nselected<1) return {};
  //---GetSF--//
  SetMuonSFs({_v_muons[0]});
  return {_v_muonidx[0]};

}

/*
//---Get Muon ObjectPointer-Base. For SingleMuon Channel.
vector<Lepton*> JHAnalyzerBase::GetPointerSingleMuReco(double ptmin, double etacut, double ptveto){

  //unsigned int muonsize = AllMuons.size();
  unsigned int nselected= 0;
  vector<Lepton*> _v_muons;
  //for(unsigned int i = 0 ; i < muonsize; i++ ){
  for(const auto &muon : AllMuons){
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    //double pt=AllMuons[i].Pt();
    if(muon.Pt() < ptveto) continue;
    //bool passLooseID=AllMuons[i].PassID("POGLoose");
    if (!muon.PassID("POGLoose")) continue;
    //bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //----Loose ID Muon passing pt/eta/iso cut
    nselected+=1;
    if(nselected>1) return {};
    //--For One selected as prompt lepton--//
    if(muon.Pt()<ptmin) return {};
    if(!muon.PassID("POGMedium")) return {};
    //muonidx=i;
    _v_muons.push_back((Lepton*)&muon);
  }
  if (nselected==0) return {};
  //---GetSF--//
  //vector<int> v_muonidx={muonidx};
  //SetMuonSFs(v_muonidx);
  SetMuonSFs(_v_muons);
  return _v_muons;

}
*/

/*
//---Get Muon index-base. For SingleMuon Channel
int JHAnalyzerBase::GetIdxSingleElReco(double ptmin, double etacut, double ptveto){
  unsigned int electronsize = AllElectrons.size();
  unsigned int nselected= 0;
  int electronidx=-1;
  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=AllElectrons[i].Pt();
    if(pt < ptveto) continue;
    double eta=AllElectrons[i].Eta();
    if(fabs(eta) > etacut) continue;
    bool passID=AllElectrons[i].PassID("passLooseID");
    if(!passID) continue;
    nselected+=1;
    if(nselected > 1) return -1;//if # of electron passing ptveto cut > 1, the event cannot pass the selection
    //Now Only 1 electron passing ptvetocut
    if(pt < ptmin) return -1; 
    if (!AllElectrons[i].PassID("passMediumID")) return -1;
    electronidx=i;
  }
  if (nselected==0) return -1;
  vector<int> v_electronidx= {electronidx};
  SetElectronSFs(v_electronidx);
  return electronidx;
}
*/
//---Get Muon Object-base. For SingleMuon Channel
vector<Electron> JHAnalyzerBase::GetSingleElReco(double ptmin, double etacut, double ptveto, double ptveto2, double etacut2){//ptveto2 and etacut2 -->for add. muon
  vector<Electron> _v_electrons;
  unsigned int nselected= 0;

  for(const auto &muon : AllMuons){
    if(fabs(muon.Eta()) > etacut2) continue;
    if(muon.Pt() < ptveto2) continue;
    if (!muon.PassID("POGLoose")) continue;
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //if at list one muon passing all of the above conditions, return empty  
    return {};
  }


  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  for(const auto& electron : AllElectrons){
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut) continue;
    //bool passID=AllElectrons[i].PassID("passLooseID");
    if(!electron.PassID("passVetoID")) continue;
    nselected+=1;
    if(nselected > 1) return {};//if # of electron passing ptveto cut > 1, the event cannot pass the selection
    //Now Only 1 electron passing ptvetocut
    if(electron.Pt() < ptmin) return {}; 
    //if (!AllElectrons[i].PassID("passMediumID")) return -1;
    if (!electron.PassID(ElectronID)) return {};
    _v_electrons.push_back(electron);
  }
  if (nselected==0) return {};

  SetElectronSFs({_v_electrons[0]});
  return {_v_electrons[0]};
}


vector<int> JHAnalyzerBase::GetSingleElRecoIdx(double ptmin, double etacut, double ptveto, double ptveto2, double etacut2){//ptveto2 and etacut2 -->for add. muon
  vector<Electron> _v_electrons;
  vector<int> _v_electronidx;
  unsigned int nselected= 0;
  
  for(const auto &muon : AllMuons){
    if(fabs(muon.Eta()) > etacut2) continue;
    if(muon.Pt() < ptveto2) continue;
    if (!muon.PassID("POGLoose")) continue;
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //if at list one muon passing all of the above conditions, return empty  
    return {};
  }


  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  int this_electronidx=-1;
  for(const auto& electron : AllElectrons){
    this_electronidx+=1;
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut) continue;
    //bool passID=AllElectrons[i].PassID("passLooseID");
    if(!electron.PassID("passVetoID")) continue;
    nselected+=1;
    if(nselected > 1) return {};//if # of electron passing ptveto cut > 1, the event cannot pass the selection
    //Now Only 1 electron passing ptvetocut
    if(electron.Pt() < ptmin) return {}; 
    //if (!AllElectrons[i].PassID("passMediumID")) return -1;
    if (!electron.PassID(ElectronID)) return {};
    _v_electrons.push_back(electron);
    _v_electronidx.push_back(this_electronidx);
  }
  if (nselected==0) return {};

  SetElectronSFs({_v_electrons[0]});
  return {_v_electronidx[0]};
}

vector<Electron> JHAnalyzerBase::GetSingleElRecoNoVeto(double ptmin, double etacut){
  vector<Electron> _v_electrons;
  unsigned int nselected= 0;
  for(const auto& electron : AllElectrons){
    if(electron.Pt() < ptmin) continue;
    if(fabs(electron.Eta()) > etacut) continue;
    if (!electron.PassID(ElectronID)) continue;
    nselected+=1;
    _v_electrons.push_back(electron);
  }
  if (nselected<1) return {};
  SetElectronSFs({_v_electrons[0]});
  return {_v_electrons[0]};
}


vector<int> JHAnalyzerBase::GetSingleElRecoNoVetoIdx(double ptmin, double etacut){
  vector<Electron> _v_electrons;
  vector<int> _v_electronidx;
  int this_electronidx=-1;
  unsigned int nselected= 0;
  for(const auto& electron : AllElectrons){
    this_electronidx+=1;
    if(electron.Pt() < ptmin) continue;
    if(fabs(electron.Eta()) > etacut) continue;
    if (!electron.PassID(ElectronID)) continue;
    nselected+=1;
    _v_electrons.push_back(electron);
    _v_electronidx.push_back(this_electronidx);
  }
  if (nselected<1) return {};
  SetElectronSFs({_v_electrons[0]});
  return {_v_electronidx[0]};
}

//---Get Muon ObjectPointer-base. For SingleElectron Channel
/*
vector<Lepton*> JHAnalyzerBase::GetPointerSingleElReco(double ptmin, double etacut, double ptveto){
  vector<Lepton*> _v_electrons;
  unsigned int nselected= 0;
  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  for(const auto& electron : AllElectrons){
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut) continue;
    //bool passID=AllElectrons[i].PassID("passLooseID");
    if(!electron.PassID("passLooseID")) continue;
    nselected+=1;
    if(nselected > 1) return {};//if # of electron passing ptveto cut > 1, the event cannot pass the selection
    //Now Only 1 electron passing ptvetocut
    if(electron.Pt() < ptmin) return {}; 
    //if (!AllElectrons[i].PassID("passMediumID")) return -1;
    if (electron.PassID("passMediumID")) return {};
    _v_electrons.push_back((Lepton*)&electron);
  }
  if (nselected==0) return {};

  SetElectronSFs(_v_electrons);
  return _v_electrons;
}
*/
/*
//Get Muons index-base. For DiMuonChannel
vector<int> JHAnalyzerBase::GetIdxDiMuReco(double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<int> v_muonidx;
  unsigned int muonsize = AllMuons.size();
  unsigned int npassveto=0;
  unsigned int npasstight=0;


  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double pt=AllMuons[i].Pt();
    if(pt < ptveto) continue;
    double eta=AllMuons[i].Eta();
    if(fabs(eta) > etacut) continue;
    bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!passISO) continue;
    bool passVetoID=AllMuons[i].PassID("POGLoose");
    if (!passVetoID) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    //Now only 2 muons passing ptveto cut
    bool passID=AllMuons[i].PassID("POGMedium");    
    if (!passID) continue; // the muons must pass ID
    npasstight+=1;
    v_muonidx.push_back(i);
    
  }
  if(npasstight<2) return {};
  if(AllMuons[v_muonidx[0]].Pt() < ptmin1) return {};
  if(AllMuons[v_muonidx[1]].Pt() < ptmin2) return {};
  SetMuonSFs(v_muonidx);
  return v_muonidx;
}
*/
//--GetMuons object-base For DiMuonChannel
vector<Muon> JHAnalyzerBase::GetDiMuReco(double ptmin1, double ptmin2, double etacut, double ptveto, double ptveto2, double etacut2 ){

  //---Electron veto first
  for(const auto& electron : AllElectrons){
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto2) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut2) continue;
    //bool passID=AllElectrons[i].PassID("passLooseID");
    if(!electron.PassID("passVetoID")) continue;
    return {};
  }

  
  vector<Muon> _v_muons;
  vector<int> _v_idx;
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  muon1_idx=-1;
  muon2_idx=-1;
  int _idx=-1;
  for(const auto& muon : AllMuons){
    _idx+=1;
    //double pt=AllMuons[i].Pt();
    if(muon.Pt() < ptveto) continue;
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    //bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //bool passVetoID=AllMuons[i].PassID("POGLoose");
    if (!muon.PassID("POGLoose")) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    //Now only 2 muons passing ptveto cut
    //bool passID=AllMuons[i].PassID("POGMedium");    
    if (!muon.PassID(MuonID)) continue; // the muons must pass ID for main selection
    npasstight+=1;
    _v_muons.push_back(muon);
    _v_idx.push_back(_idx);
  }

  if(npasstight<2) return {};
  if(_v_muons[0].Pt() < ptmin1) return {};
  if(_v_muons[1].Pt() < ptmin2) return {};

  /*
  for(const auto& muon : AllMuons){                                                                                                                          
    if(muon.Pt() < 25) continue;
    if(fabs(muon.Eta()) > etacut) continue;
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;                                                                                            
    if (!muon.PassID("POGMedium")) continue; // the muons must pass ID for main selection
    _v_muons.push_back(muon);
  }
  */
  muon1_idx=_v_idx[0];
  muon2_idx=_v_idx[1];
  SetMuonSFs({_v_muons[0],_v_muons[1]});
  return {_v_muons[0],{_v_muons[1]}};
}


vector<int> JHAnalyzerBase::GetDiMuRecoIdx(double ptmin1, double ptmin2, double etacut, double ptveto, double ptveto2, double etacut2 ){

  //---Electron veto first
  for(const auto& electron : AllElectrons){
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto2) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut2) continue;
    //bool passID=AllElectrons[i].PassID("passLooseID");
    if(!electron.PassID("passVetoID")) continue;
    return {};
  }

  
  vector<Muon> _v_muons;
  vector<int> _v_idx;
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  muon1_idx=-1;
  muon2_idx=-1;
  int _idx=-1;
  for(const auto& muon : AllMuons){
    _idx+=1;
    //double pt=AllMuons[i].Pt();
    if(muon.Pt() < ptveto) continue;
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    //bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //bool passVetoID=AllMuons[i].PassID("POGLoose");
    if (!muon.PassID("POGLoose")) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    //Now only 2 muons passing ptveto cut
    //bool passID=AllMuons[i].PassID("POGMedium");    
    if (!muon.PassID(MuonID)) continue; // the muons must pass ID for main selection
    npasstight+=1;
    _v_muons.push_back(muon);
    _v_idx.push_back(_idx);

  }

  if(npasstight<2) return {};
  if(_v_muons[0].Pt() < ptmin1) return {};
  if(_v_muons[1].Pt() < ptmin2) return {};

  /*
  for(const auto& muon : AllMuons){                                                                                                                          
    if(muon.Pt() < 25) continue;
    if(fabs(muon.Eta()) > etacut) continue;
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;                                                                                            
    if (!muon.PassID("POGMedium")) continue; // the muons must pass ID for main selection
    _v_muons.push_back(muon);
  }
  */
  muon1_idx=_v_idx[0];
  muon2_idx=_v_idx[1];
  SetMuonSFs({_v_muons[0],_v_muons[1]});
  return {muon1_idx,muon2_idx};
}



vector<Muon> JHAnalyzerBase::GetDiMuRecoNoVeto(double ptmin1, double ptmin2, double etacut){
  vector<Muon> _v_muons;
  vector<int> _v_idx;
  unsigned int npasstight=0;
  muon1_idx=-1;
  muon2_idx=-1;
  int _idx=-1;
  for(const auto& muon : AllMuons){
    _idx+=1;
    if(muon.Pt() < ptmin2) continue;
    if(fabs(muon.Eta()) > etacut) continue;
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    if (!muon.PassID(MuonID)) continue; // the muons must pass ID for main selection
    npasstight+=1;
    _v_muons.push_back(muon);
    _v_idx.push_back(_idx);
  }

  if(npasstight<2) return {};
  if(_v_muons[0].Pt() < ptmin1) return {};
  //if(_v_muons[1].Pt() < ptmin2) return {};

  muon1_idx=_v_idx[0];
  muon2_idx=_v_idx[1];
  SetMuonSFs({_v_muons[0],_v_muons[1]});
  return {_v_muons[0],_v_muons[1]};
}


vector<int> JHAnalyzerBase::GetDiMuRecoNoVetoIdx(double ptmin1, double ptmin2, double etacut){
  vector<Muon> _v_muons;
  vector<int> _v_idx;
  unsigned int npasstight=0;
  muon1_idx=-1;
  muon2_idx=-1;
  int _idx=-1;
  for(const auto& muon : AllMuons){
    _idx+=1;
    if(muon.Pt() < ptmin2) continue;
    if(fabs(muon.Eta()) > etacut) continue;
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    if (!muon.PassID(MuonID)) continue; // the muons must pass ID for main selection
    npasstight+=1;
    _v_muons.push_back(muon);
    _v_idx.push_back(_idx);
  }

  if(npasstight<2) return {};
  if(_v_muons[0].Pt() < ptmin1) return {};
  //if(_v_muons[1].Pt() < ptmin2) return {};

  muon1_idx=_v_idx[0];
  muon2_idx=_v_idx[1];
  SetMuonSFs({_v_muons[0],_v_muons[1]});
  return {muon1_idx,muon2_idx};
}



/*
//--GetMuons objectPointer-base For DiMuonChannel
vector<Lepton*> JHAnalyzerBase::GetPointerDiMuReco(double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<Lepton*> _v_muons;
  vector<int> _v_idx;
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  muon1_idx=-1;
  muon2_idx=-1;
    
  //for(unsigned int i = 0 ; i < muonsize; i++ ){
  for(const auto& muon : AllMuons){
    //double pt=AllMuons[i].Pt();
    if(muon.Pt() < ptveto) continue;
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    //bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //bool passVetoID=AllMuons[i].PassID("POGLoose");
    if (!muon.PassID("POGLoose")) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    //Now only 2 muons passing ptveto cut
    //bool passID=AllMuons[i].PassID("POGMedium");    
    if (!muon.PassID("POGMedium")) continue; // the muons must pass ID for main selection
    npasstight+=1;
    _v_muons.push_back((Lepton*)&muon);
    int _idx=std::distance(AllMuons.data(), &muon);
    _v_idx.push_back(_idx);    
  }
  if(npasstight<2) return {};
  if(_v_muons[0]->Pt() < ptmin1) return {};
  if(_v_muons[1]->Pt() < ptmin2) return {};
  muon1_idx=_v_idx[0];
  muon2_idx=_v_idx[1];
  SetMuonSFs(_v_muons);
  return _v_muons;
}
*/

/*
//Get Electrons index-base. For DiElectron Channel
vector<int> JHAnalyzerBase::GetIdxDiElReco(double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<int> v_electronidx;
  unsigned int electronsize = AllElectrons.size();
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=AllElectrons[i].Pt();
    if(pt < ptveto) continue;
    double eta=AllElectrons[i].Eta();
    if(fabs(eta) > etacut) continue;
    bool passVetoID=AllElectrons[i].PassID("passLooseID");
    if (!passVetoID) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    ///---Now we have only 2 electrons passing ptveto cut
    bool passID=AllElectrons[i].PassID("passMediumID");
    if (!passID) continue;
    npasstight+=1;
    v_electronidx.push_back(i);
  }
  if(npasstight<2) return {};
  if(AllElectrons[v_electronidx[0]].Pt() < ptmin1) return {};
  if(AllElectrons[v_electronidx[1]].Pt() < ptmin2) return {};
  SetElectronSFs(v_electronidx);
  return v_electronidx;
}
*/
//--Get Electrons Obejct-base. For DiElectron Channel
vector<Electron> JHAnalyzerBase::GetDiElReco(double ptmin1, double ptmin2, double etacut, double ptveto,double ptveto2, double etacut2  ){
  //muonveto first
  for(const auto &muon : AllMuons){
    if(fabs(muon.Eta()) > etacut2) continue;
    if(muon.Pt() < ptveto2) continue;
    if (!muon.PassID("POGLoose")) continue;
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //if at list one muon passing all of the above conditions, return empty
    return {};
  }

  
  vector<Electron> _v_electrons;
  vector<int> _v_idx;
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  electron1_idx=-1;
  electron2_idx=-1;
  int _idx=-1;
  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  for(const auto& electron : AllElectrons){
    _idx+=1;
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut) continue;
    //bool passVetoID=AllElectrons[i].PassID("passLooseID");
    if (!electron.PassID("passVetoID")) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    ///---Now we have only 2 electrons passing ptveto cut
    //bool passID=AllElectrons[i].PassID("passMediumID");
    if (!electron.PassID(ElectronID)) continue;
    npasstight+=1;
    _v_electrons.push_back(electron);
    _v_idx.push_back(_idx);
  }
  if(npasstight<2) return {};
  if(_v_electrons[0].Pt() < ptmin1) return {};
  if(_v_electrons[1].Pt() < ptmin2) return {};
  SetElectronSFs({_v_electrons[0],_v_electrons[1]});
  electron1_idx=_v_idx[0];
  electron2_idx=_v_idx[1];
  return {_v_electrons[0],_v_electrons[1]};
}


vector<int> JHAnalyzerBase::GetDiElRecoIdx(double ptmin1, double ptmin2, double etacut, double ptveto,double ptveto2, double etacut2 ){
  //muonveto first
  for(const auto &muon : AllMuons){
    if(fabs(muon.Eta()) > etacut2) continue;
    if(muon.Pt() < ptveto2) continue;
    if (!muon.PassID("POGLoose")) continue;
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //if at list one muon passing all of the above conditions, return empty                                                                                                                               
    return {};
  }
  
  vector<Electron> _v_electrons;
  vector<int> _v_idx;
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  electron1_idx=-1;
  electron2_idx=-1;
  int _idx=-1;
  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  for(const auto& electron : AllElectrons){
    _idx+=1;
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut) continue;
    //bool passVetoID=AllElectrons[i].PassID("passLooseID");
    if (!electron.PassID("passVetoID")) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    ///---Now we have only 2 electrons passing ptveto cut
    //bool passID=AllElectrons[i].PassID("passMediumID");
    if (!electron.PassID(ElectronID)) continue;
    npasstight+=1;
    _v_electrons.push_back(electron);
    _v_idx.push_back(_idx);
  }
  if(npasstight<2) return {};
  if(_v_electrons[0].Pt() < ptmin1) return {};
  if(_v_electrons[1].Pt() < ptmin2) return {};
  SetElectronSFs({_v_electrons[0],_v_electrons[1]});
  electron1_idx=_v_idx[0];
  electron2_idx=_v_idx[1];
  return {electron1_idx,electron2_idx};
}


vector<Electron> JHAnalyzerBase::GetDiElRecoNoVeto(double ptmin1, double ptmin2, double etacut){
  vector<Electron> _v_electrons;
  vector<int> _v_idx;
  unsigned int npasstight=0;
  electron1_idx=-1;
  electron2_idx=-1;
  int _idx=-1;
  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  for(const auto& electron : AllElectrons){
    _idx+=1;
    if(electron.Pt() < ptmin2) continue;
    if(fabs(electron.Eta()) > etacut) continue;
    if (!electron.PassID(ElectronID)) continue;
    npasstight+=1;
    _v_electrons.push_back(electron);
    _v_idx.push_back(_idx);
  }
  if(npasstight<2) return {};
  if(_v_electrons[0].Pt() < ptmin1) return {};
  SetElectronSFs({_v_electrons[0],_v_electrons[1]});
  electron1_idx=_v_idx[0];
  electron2_idx=_v_idx[1];
  return {_v_electrons[0],_v_electrons[1]};
}

vector<int> JHAnalyzerBase::GetDiElRecoNoVetoIdx(double ptmin1, double ptmin2, double etacut){
  vector<Electron> _v_electrons;
  vector<int> _v_idx;
  unsigned int npasstight=0;
  electron1_idx=-1;
  electron2_idx=-1;
  int _idx=-1;
  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  for(const auto& electron : AllElectrons){
    _idx+=1;
    if(electron.Pt() < ptmin2) continue;
    if(fabs(electron.Eta()) > etacut) continue;
    if (!electron.PassID(ElectronID)) continue;
    npasstight+=1;
    _v_electrons.push_back(electron);
    _v_idx.push_back(_idx);
  }
  if(npasstight<2) return {};
  if(_v_electrons[0].Pt() < ptmin1) return {};
  SetElectronSFs({_v_electrons[0],_v_electrons[1]});
  electron1_idx=_v_idx[0];
  electron2_idx=_v_idx[1];
  return {electron1_idx,electron2_idx};
}

/*
//--Get Electrons ObejctPointer-base. For DiElectron Channel
vector<Lepton*> JHAnalyzerBase::GetPointerDiElReco(double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<Lepton*> _v_electrons;
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  vector<int> _v_idx;
  electron1_idx=-1;
  electron2_idx=-1;
  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  for(const auto& electron : AllElectrons){
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut) continue;
    //bool passVetoID=AllElectrons[i].PassID("passLooseID");
    if (!electron.PassID("passLooseID")) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    ///---Now we have only 2 electrons passing ptveto cut
    //bool passID=AllElectrons[i].PassID("passMediumID");
    if (!electron.PassID("passMediumID")) continue;
    npasstight+=1;
    _v_electrons.push_back((Lepton*)&electron);
    int _idx=std::distance(AllMuons.data(), &electron);
    _v_idx.push_back(_idx);
  }
  if(npasstight<2) return {};
  if(_v_electrons[0]->Pt() < ptmin1) return {};
  if(_v_electrons[1]->Pt() < ptmin2) return {};
  SetElectronSFs(_v_electrons);
  electron1_idx=_v_idx[0];
  electron2_idx=_v_idx[1];
  return _v_electrons;
}
*/
//---GetTightJet index base
/*
vector<int> JHAnalyzerBase::GetIdxTightJet(const vector<Lepton> &v_tightlep, double ptmin, double etacut, TString JetID ){
  vector<int> v_jetidx;
  unsigned int jetsize = AllJets.size();
  for(unsigned int i=0; i < jetsize; i++){
    if(AllJets[i].Pt() < ptmin) continue;
    if(fabs(AllJets[i].Eta()) > etacut) continue;
    if(!AllJets[i].PassID(JetID)) continue;
    //--Lepton Cleaning--//
    bool HasCloseLep=false;
    for(const auto& lep : v_tightlep){
      if (AllJets[i].DeltaR(lep)<0.4){
	HasCloseLep=true;
	break;
      }
    }
    if(HasCloseLep)continue;
    //--end lepton cleaning--//
    v_jetidx.push_back(i);
  }
  SetBtagSF(v_jetidx);
  return v_jetidx;
}
*/
//---Get TightJet Object base
vector<Jet> JHAnalyzerBase::GetTightJet(const vector<Lepton> &v_tightlep, double ptmin, double etacut, TString JetID, TString _JetPUID,bool apply_vetomap){
  vector<Jet> v_tightjet;
  for(const auto& jet : AllJets){
    if(jet.Pt() < ptmin) continue;
    if(fabs(jet.Eta()) > etacut) continue;
    if(apply_vetomap){
      double this_eta=jet.Eta();
      double this_phi=jet.Phi();
      int this_bin=h_jetvetomap->FindBin(this_eta,this_phi);
      if(h_jetvetomap->GetBinContent(this_bin)>0) continue;
    }




    
    if(!jet.PassID(JetID)) continue;
    //--Lepton Cleaning--//
    bool HasCloseLep=false;
    for(const auto& lep : v_tightlep){
      if (jet.DeltaR(lep)<0.4){
	HasCloseLep=true;
	break;
      }
    }
    if(HasCloseLep) continue;
    //--end lepton cleaning--//
    v_tightjet.push_back(jet);
  }
  //--puid
  if(_JetPUID!=""){
    v_tightjet=map_jetpuid_tool[_JetPUID]->GetJetsPassPUID(v_tightjet);
    SetJetPUIDSF(_JetPUID);
    
  }
  SetBtagSF(v_tightjet);
  //cout << "jetpuidsf= " << endl;
  return v_tightjet;
}
/*
//---Get TightJet ObjectPointer base
vector<Jet*> JHAnalyzerBase::GetPointerTightJet(const vector<Lepton*> &v_tightlep, double ptmin, double etacut, TString JetID ){
  vector<Jet*> v_tightjet;
  vector<Jet> v_jetobj;
  for(const auto& jet : AllJets){
    if(jet.Pt() < ptmin) continue;
    if(fabs(jet.Eta()) > etacut) continue;
    if(!jet.PassID(JetID)) continue;
    //--Lepton Cleaning--//
    bool HasCloseLep=false;
    for(const auto& lep : v_tightlep){
      if (lep->DeltaR(jet)<0.4){
	HasCloseLep=true;
	break;
      }
    }
    if(HasCloseLep)continue;
    //--end lepton cleaning--//
    v_tightjet.push_back((Jet*)&jet);
    v_jetobj.push_back(jet);
  }
  SetBtagSF(v_jetobj);
  return v_tightjet;
}
*/


//--Get BJet index base
/*
vector<int> JHAnalyzerBase::GetIdxBJet(const vector<int> &v_TightjetIdx){
  vector<int> v_bjetidx;
  for(const auto& i : v_TightjetIdx){
    double btagscore=AllJets[i].GetTaggerResult(JetTagging::DeepJet);
    if(btagscore < btagcut) continue;
    v_bjetidx.push_back(i);
  }
  return v_bjetidx;
}
*/
//--Get BJet Object base
vector<Jet> JHAnalyzerBase::GetBJet(const vector<Jet> &v_Tightjet){
  vector<Jet> v_bjet;
  for(const auto& jet : v_Tightjet){
    double btagscore=jet.GetTaggerResult(JetTagging::DeepJet);
    if(btagscore < btagcut) continue;
    v_bjet.push_back(jet);
  }
  return v_bjet;
}

//--Get BJet Object base
vector<int> JHAnalyzerBase::GetBJetIdx(const vector<Jet> &v_Tightjet){
  vector<int> v_bjetidx;
  int bidx=-1;
  for(const auto& jet : v_Tightjet){
    bidx+=1;
    double btagscore=jet.GetTaggerResult(JetTagging::DeepJet);
    if(btagscore < btagcut) continue;
    v_bjetidx.push_back(bidx);
  }
  return v_bjetidx;
}

/*
//--Get BJet ObjectPointer base
vector<Jet*> JHAnalyzerBase::GetPointerBJet(const vector<Jet*> &v_Tightjet){
  vector<Jet*> v_bjet;
  for(const auto& jet : v_Tightjet){
    double btagscore=jet->GetTaggerResult(JetTagging::DeepJet);
    if(btagscore < btagcut) continue;
    v_bjet.push_back(jet);
  }
  return v_bjet;
}
*/
/*
void JHAnalyzerBase::SetBtagSF(const vector<int> &v_jetidx){
  //r_SystUpLTagUnCorr
  vector<Jet> v_tightjet;
  for(const auto& i : v_jetidx){
    v_tightjet.push_back(AllJets[i]);
  }
  btagsf = mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp);
  if(runSys){
    r_SystUpLTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpLTagCorr")/btagsf;
    r_SystDownLTagCorr   =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownLTagCorr")/btagsf;
    r_SystUpLTagUnCorr   =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpLTagUnCorr")/btagsf;
    r_SystDownLTagUnCorr =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownLTagUnCorr")/btagsf;
    r_SystUpHTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpHTagCorr")/btagsf;
    r_SystDownHTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownHTagCorr")/btagsf;
    r_SystUpHTagUnCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpHTagUnCorr")/btagsf;
    r_SystDownHTagUnCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownHTagUnCorr")/btagsf;
  }
}
*/
void JHAnalyzerBase::SetBtagSF(const vector<Jet> &v_tightjet){
  //cout << "[JHAnalyzerBase::SetBtagSF]" << endl;
  //cout << "mcCorr->use_dasym=" << mcCorr->use_dasym <<endl;
  btagsf = mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp, "central");
  
  if(runSys){
    r_SystUpLTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpLTagCorr")/btagsf;
    r_SystDownLTagCorr   =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownLTagCorr")/btagsf;
    r_SystUpLTagUnCorr   =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpLTagUnCorr")/btagsf;
    r_SystDownLTagUnCorr =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownLTagUnCorr")/btagsf;
    r_SystUpHTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpHTagCorr")/btagsf;
    r_SystDownHTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownHTagCorr")/btagsf;
    r_SystUpHTagUnCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpHTagUnCorr")/btagsf;
    r_SystDownHTagUnCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownHTagUnCorr")/btagsf;
    if(mcCorr->use_dasym){//if b+- btag asym factor is considered in MCCorr
      //global nuisance
      //r_ChargedAsymUp     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"dAsymUp")/btagsf;
      //r_ChargedAsymDown   =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"dAsymDown")/btagsf;

      //nuisance-split
      for (int ipt = 0; ipt < nPtBin; ++ipt) {
	for (int ieta = 0; ieta < nEtaBin; ++ieta) {
	  arr_r_ChargedAsymUp[ipt][ieta]=mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"dAsymUp",ipt,ieta)/btagsf;
	  arr_r_ChargedAsymDown[ipt][ieta]=mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"dAsymDown",ipt,ieta)/btagsf;
	}
      }
    }
  }
}

void JHAnalyzerBase::SetJetPUIDSF(TString _JetPUID){
  //cout << "[JHAnalyzerBase::SetJetPUIDSF] _JetPUID=" << _JetPUID << endl;
  jetpuidsf=map_jetpuid_tool[_JetPUID]->GetCurrentSF();
  if(runSys){
    jetpuidsf_up  =map_jetpuid_tool[_JetPUID]->GetCurrentSF_Up();
    jetpuidsf_down=map_jetpuid_tool[_JetPUID]->GetCurrentSF_Down();
    r_jetpuidsf_up= jetpuidsf ? jetpuidsf_up/jetpuidsf : 0;
    r_jetpuidsf_down= jetpuidsf ? jetpuidsf_down/jetpuidsf : 0;
  }
}

/*
void JHAnalyzerBase::SetMuonSFs(const vector<int> &v_muonidx){
  SetMuonRecoSF(v_muonidx);
  SetMuonIDSF(v_muonidx);
  SetMuonTrkSF(v_muonidx);
  SetMuonTriggerSF(v_muonidx);
}
*/
void JHAnalyzerBase::SetMuonSFs(const vector<Muon> &v_muon){
  vector<Lepton*> v_lepton;
  for(const auto& muon : v_muon){
    v_lepton.push_back((Lepton*)&muon);
  }
  SetMuonRecoSF(v_lepton);
  SetMuonIDSF(v_lepton);
  SetMuonTrkSF(v_lepton);
  SetMuonTriggerSF(v_lepton);
}

/*
void JHAnalyzerBase::SetMuonSFs(const vector<Lepton*> &v_lepton){
  SetMuonRecoSF(v_lepton);
  SetMuonIDSF(v_lepton);
  SetMuonTrkSF(v_lepton);
  SetMuonTriggerSF(v_lepton);
}
*/
/*
void JHAnalyzerBase::SetElectronSFs(const vector<int> &v_electronidx){
  SetElectronRecoSF(v_electronidx);
  SetElectronIDSF(v_electronidx);
  SetElectronTriggerSF(v_electronidx);
}
*/
void JHAnalyzerBase::SetElectronSFs(const vector<Electron> &v_electron){
  vector<Lepton*> v_lepton;
  for(const auto& electron : v_electron){
    v_lepton.push_back((Lepton*)&electron);
  }
  SetElectronRecoSF(v_lepton);
  SetElectronIDSF(v_lepton);
  SetElectronTriggerSF(v_lepton);
}
/*
void JHAnalyzerBase::SetElectronSFs(const vector<Lepton*> &v_lepton){
  SetElectronRecoSF(v_lepton);
  SetElectronIDSF(v_lepton);
  SetElectronTriggerSF(v_lepton);
}
*/
/*
void JHAnalyzerBase::SetMuonRecoSF(const vector<int> &v_muonidx){

  unsigned int setsize = w_MuonRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonRECO[iset][imem]=1;
      for(const auto& muonidx : v_muonidx){
	w_MuonRECO[iset][imem]*=fEff->GetEfficiencySF(MuonRecoSFKey,(Lepton *)&AllMuons[muonidx],iset,imem);
      }
      r_MuonRECO[iset][imem]= w_MuonRECO[0][0] ? w_MuonRECO[iset][imem]/w_MuonRECO[0][0] : 0;
    }
  }
}
*/
void JHAnalyzerBase::SetMuonRecoSF(const vector<Lepton*> &v_muon){

  unsigned int setsize = w_MuonRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonRECO[iset][imem]=1;
      for(const auto& muon : v_muon){
	w_MuonRECO[iset][imem]*=fEff->GetEfficiencySF(MuonRecoSFKey,(Lepton *)muon,iset,imem);
      }
      r_MuonRECO[iset][imem]= w_MuonRECO[0][0] ? w_MuonRECO[iset][imem]/w_MuonRECO[0][0] : 0;
    }
  }
}

/*
void JHAnalyzerBase::SetElectronRecoSF(const vector<int> &v_electronidx){
  unsigned int setsize = w_ElectronRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_ElectronRECO[iset][imem]=1;
      for(const auto& electronidx : v_electronidx){
	w_ElectronRECO[iset][imem]*=fEff->GetEfficiencySF(ElectronRecoSFKey,(Lepton *)&AllElectrons[electronidx],iset,imem);
      }
      r_ElectronRECO[iset][imem]= w_ElectronRECO[0][0] ? w_ElectronRECO[iset][imem]/w_ElectronRECO[0][0] : 0;
    }
  }
}
*/
void JHAnalyzerBase::SetElectronRecoSF(const vector<Lepton*> &v_electron){
  unsigned int setsize = w_ElectronRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_ElectronRECO[iset][imem]=1;
      for(const auto& electron : v_electron){
	w_ElectronRECO[iset][imem]*=fEff->GetEfficiencySF(ElectronRecoSFKey,(Lepton *)electron,iset,imem);
      }
      r_ElectronRECO[iset][imem]= w_ElectronRECO[0][0] ? w_ElectronRECO[iset][imem]/w_ElectronRECO[0][0] : 0;
    }
  }
}

/*
void JHAnalyzerBase::SetMuonIDSF(const vector<int> &v_muonidx){
  unsigned int setsize = w_MuonID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonID[iset][imem]=1;
      for(const auto& muonidx : v_muonidx){
	w_MuonID[iset][imem]*=fEff->GetEfficiencySF(MuonIDSFKey,(Lepton *)&AllMuons[muonidx],iset,imem);
      }
      r_MuonID[iset][imem]= w_MuonID[0][0] ? w_MuonID[iset][imem]/w_MuonID[0][0] : 0;
    }
  }
}
*/
void JHAnalyzerBase::SetMuonIDSF(const vector<Lepton*> &v_muon){
  unsigned int setsize = w_MuonID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonID[iset][imem]=1;
      for(const auto& muon : v_muon){
	w_MuonID[iset][imem]*=fEff->GetEfficiencySF(MuonIDSFKey,(Lepton *)muon,iset,imem);
      }
      r_MuonID[iset][imem]= w_MuonID[0][0] ? w_MuonID[iset][imem]/w_MuonID[0][0] : 0;
    }
  }
}

/*
void JHAnalyzerBase::SetElectronIDSF(const vector<int> &v_electronidx){
  unsigned int setsize = w_ElectronID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_ElectronID[iset][imem]=1;
      for(const auto& electronidx : v_electronidx){
	w_ElectronID[iset][imem]*=fEff->GetEfficiencySF(ElectronIDSFKey,(Lepton *)&AllElectrons[electronidx],iset,imem);
      }
      r_ElectronID[iset][imem]= w_ElectronID[0][0] ? w_ElectronID[iset][imem]/w_ElectronID[0][0] : 0;
    }
  }
}
*/

void JHAnalyzerBase::SetElectronIDSF(const vector<Lepton*> &v_electron){
  unsigned int setsize = w_ElectronID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_ElectronID[iset][imem]=1;
      for(const auto& electron : v_electron){
	w_ElectronID[iset][imem]*=fEff->GetEfficiencySF(ElectronIDSFKey,(Lepton *)electron,iset,imem);
      }
      r_ElectronID[iset][imem]= w_ElectronID[0][0] ? w_ElectronID[iset][imem]/w_ElectronID[0][0] : 0;
    }
  }
}
/*
void JHAnalyzerBase::SetMuonTrkSF(const vector<int> &v_muonidx){
  unsigned int setsize = w_MuonTrk.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrk[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonTrk[iset][imem]=1;
      for(const auto& muonidx : v_muonidx){
	w_MuonTrk[iset][imem]*=fEff->GetEfficiencySF(MuonTrkSFKey,(Lepton *)&AllMuons[muonidx],iset,imem);
      }
      r_MuonTrk[iset][imem]=w_MuonTrk[0][0] ? w_MuonTrk[iset][imem]/w_MuonTrk[0][0] : 0;
    }
  }
}
*/

void JHAnalyzerBase::SetMuonTrkSF(const vector<Lepton*> &v_muon){
  unsigned int setsize = w_MuonTrk.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrk[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonTrk[iset][imem]=1;
      for(const auto& muon : v_muon){
	w_MuonTrk[iset][imem]*=fEff->GetEfficiencySF(MuonTrkSFKey,(Lepton *)muon,iset,imem);
      }
      r_MuonTrk[iset][imem]=w_MuonTrk[0][0] ? w_MuonTrk[iset][imem]/w_MuonTrk[0][0] : 0;
    }
  }
}

/*
void JHAnalyzerBase::SetMuonTriggerSF(const vector<int> &v_muonidx){
  //---Make vector whose elements are Lepton pointers
  vector<Lepton*> _v_muons;
  for(const auto& muonidx : v_muonidx){
    _v_muons.push_back((Lepton*)&AllMuons[muonidx] );
  }

  if(!IsDoubleMuonTrigger){
    if(IsORMuonTrigger){
      SetSingleMuonTriggerORSF(_v_muons);
    }
    else{
      SetSingleMuonTriggerSF(_v_muons);
    }
  }
  else{
    SetDoubleMuonTriggerSF(_v_muons);
  }
  
}
*/
void JHAnalyzerBase::SetMuonTriggerSF(const vector<Lepton*> &v_muon){
  if(!IsDoubleMuonTrigger){
    if(IsORMuonTrigger){
      SetSingleMuonTriggerORSF(v_muon);
    }
    else{
      SetSingleMuonTriggerSF(v_muon);
    }
  }
  else{
    SetDoubleMuonTriggerSF(v_muon);
  }

}

void JHAnalyzerBase::SetSingleMuonTriggerSF(const vector<Lepton*> &v_muons){

  unsigned int setsize = w_MuonTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      if(IsORMuonTrigger){
	w_MuonTrigger[iset][imem]=AnalyzerCore::GetLeptonTriggerORSF(ev,MuonTriggerNames,MuonTriggerSFKeys,v_muons,iset,imem,"");
      }else{
	w_MuonTrigger[iset][imem]=AnalyzerCore::GetLeptonTriggerSF(MuonTriggerSFKeys[0],v_muons,iset,imem,"");
      }
      r_MuonTrigger[iset][imem]=w_MuonTrigger[0][0] ? w_MuonTrigger[iset][imem]/w_MuonTrigger[0][0] : 0;
    }
  }
}


void JHAnalyzerBase::SetSingleMuonTriggerORSF(const vector<Lepton*> &v_muons){

  unsigned int setsize = w_MuonTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonTrigger[iset][imem]=AnalyzerCore::GetLeptonTriggerORSF(ev,MuonTriggerNames,MuonTriggerSFKeys,v_muons,iset,imem,"");
      r_MuonTrigger[iset][imem]=w_MuonTrigger[0][0] ? w_MuonTrigger[iset][imem]/w_MuonTrigger[0][0] : 0;
    }
  }
}



void JHAnalyzerBase::SetDoubleMuonTriggerSF(const vector<Lepton*> &v_muons){

  unsigned int setsize = w_MuonTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      //double AnalyzerCore::GetDileptonTriggerSF(TString triggerSF_key0,TString triggerSF_key1,TString DZSF,const vector<Lepton*>& leps,int set,int mem)
      w_MuonTrigger[iset][imem]=AnalyzerCore::GetDileptonTriggerSF(MuonTriggerSFKeys[0],MuonTriggerSFKeys[1],MuonDZSFKey,v_muons,iset,imem);
      r_MuonTrigger[iset][imem]=w_MuonTrigger[0][0] ? w_MuonTrigger[iset][imem]/w_MuonTrigger[0][0] : 0;
    }
  }
}


//
/*
void JHAnalyzerBase::SetElectronTriggerSF(const vector<int> &v_electronidx){
  vector<Lepton*> _v_electrons;
  for(const auto& electronidx : v_electronidx){
    _v_electrons.push_back((Lepton*)&AllElectrons[electronidx] );
  }
  if(!IsDoubleElectronTrigger){
    if(IsORElectronTrigger){
      SetSingleElectronTriggerORSF(_v_electrons);
    }
    else{
      SetSingleElectronTriggerSF(_v_electrons);
    }
  }
  else{
    SetDoubleElectronTriggerSF(_v_electrons);
  }

}
*/

void JHAnalyzerBase::SetElectronTriggerSF(const vector<Lepton*> &v_electron){

  if(!IsDoubleElectronTrigger){
    if(IsORElectronTrigger){
      SetSingleElectronTriggerORSF(v_electron);
    }
    else{
      SetSingleElectronTriggerSF(v_electron);
    }
  }
  else{
    SetDoubleElectronTriggerSF(v_electron);
  }

}

void JHAnalyzerBase::SetSingleElectronTriggerSF(const vector<Lepton*> &v_electrons){

  unsigned int setsize = w_ElectronTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_ElectronTrigger[iset][imem]=AnalyzerCore::GetLeptonTriggerSF(ElectronTriggerSFKeys[0],v_electrons,iset,imem,"");
      r_ElectronTrigger[iset][imem]=w_ElectronTrigger[0][0] ? w_ElectronTrigger[iset][imem]/w_ElectronTrigger[0][0] : 0;
    }
  }
}



void JHAnalyzerBase::SetSingleElectronTriggerORSF(const vector<Lepton*> &v_electrons){

  unsigned int setsize = w_ElectronTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      
      w_ElectronTrigger[iset][imem]=AnalyzerCore::GetLeptonTriggerORSF(ev,ElectronTriggerNames,ElectronTriggerSFKeys,v_electrons,iset,imem,"");
      r_ElectronTrigger[iset][imem]=w_ElectronTrigger[0][0] ? w_ElectronTrigger[iset][imem]/w_ElectronTrigger[0][0] : 0;
    }
  }
}



void JHAnalyzerBase::SetDoubleElectronTriggerSF(const vector<Lepton*> &v_electrons){

  unsigned int setsize = w_ElectronTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      //double AnalyzerCore::GetDileptonTriggerSF(TString triggerSF_key0,TString triggerSF_key1,TString DZSF,const vector<Lepton*>& leps,int set,int mem)
      w_ElectronTrigger[iset][imem]=AnalyzerCore::GetDileptonTriggerSF(ElectronTriggerSFKeys[0],ElectronTriggerSFKeys[1],ElectronDZSFKey,v_electrons,iset,imem);
      r_ElectronTrigger[iset][imem]=w_ElectronTrigger[0][0] ? w_ElectronTrigger[iset][imem]/w_ElectronTrigger[0][0] : 0;
    }
  }
}




//---For Calc
TLorentzVector JHAnalyzerBase::GetTransverseVector(const TLorentzVector &v){
  // 2nd section of 
  //https://en.wikipedia.org/wiki/Transverse_mass
  //cout << "GetTransverseVector" << endl;
  double px=v.Px();
  double py=v.Py();
  double pz=0.;
  double m =v.M();
  double ee=sqrt(m*m+px*px+py*py);
  TLorentzVector ret;
  ret.SetPxPyPzE(px,py,pz,ee);
  return ret;
}

TLorentzVector JHAnalyzerBase::GetTransverseVector(double pt, double phi){
  //No mass
  double px=pt*cos(phi);
  double py=pt*sin(phi);
  double pz=0.;
  double ee=sqrt(px*px+py*py);
  TLorentzVector ret;
  ret.SetPxPyPzE(px,py,pz,ee);
  return ret;
}


//-----LHE check----//
bool JHAnalyzerBase::TagZbLHE(bool include_tautau){
  if(!IsDYSample) return 0;
  //init
  idx_outgoing_b=-1;
  unsigned int lhessize=lhes.size();
  unsigned int ngluon_incoming = 0;
  unsigned int nb_incoming = 0; // 5
  unsigned int nbbar_incoming = 0; // -5
  unsigned int nb_outgoing = 0;
  unsigned int nbbar_outgoing = 0;
  unsigned int nparton_outgoing = 0;
  
  //We want event with
  //incoming : 1 g + 1 b
  //outgoing : 1 b , no other partons
  
  unsigned int ntau = 0, nmu = 0, nele = 0;
  for(unsigned int i =0; i < lhessize ; i++){
    int status=lhes[i].Status();
    int pid=lhes[i].ID();
    
    if (status==-1){//if incoming
      if(pid==5){//if incoming b
        nb_incoming    += 1;
      }
      else if(pid==-5){//if bbar
        nbbar_incoming   += 1;
      }
      else if(pid==21){//if gluon
	ngluon_incoming += 1;
      }
    }//[END]if incoming
    else if (status==1){//if outgoing
      if (pid==15){
        ntau += 1;
      }
      else if (pid==-15){
        ntau += 1;
      }
      else if (pid==13){
        nmu += 1;
      }
      else if (pid==-13){
        nmu += 1;
      }
      else if (pid==11){
        nele += 1;
      }
      else if (pid==-11){
        nele += 1;
      }

      if (pid==5){
        nb_outgoing += 1;
	idx_outgoing_b=i;
        nparton_outgoing += 1;
      }
      else if (pid==-5){
        nbbar_outgoing += 1;
	idx_outgoing_b=i;
        nparton_outgoing += 1;
      }
      else if(abs(pid)<5){//if quark
          nparton_outgoing += 1;
      }
      else if (pid == 21){//if gluon
        nparton_outgoing += 1;
      }
    }//[END]if outgoing
  }//[END]for each LHE
  //Whether it's a tautau event
  bool is_tautau= (ntau==2) ? true : false;
  is_mumu_lhe= (nmu==2) ? true : false;
  is_ee_lhe= (nele==2) ? true : false;
  //Check whether g+b scattering
  if(!include_tautau && is_tautau) return false;
  if(1 != ngluon_incoming) return false;
  if(1 != (nb_incoming+nbbar_incoming)) return false;
  //Check whether only 1b among outgoing partons
  //<=> 1b outgoing && nparton outgoing=1
  if(1 != (nb_outgoing+nbbar_outgoing)) return false;
  //if(1 != nparton_outgoing) return false; // skip this. Only 1 b outgoing quark
  //else, it is one of the events we want.
  return true;

}

/*
bool JHAnalyzerBase::TagWbLHE(){
  if(ProcessName.Index("WJets")!=0) return 0 ;//samplename must start with "WJets"
  unsigned int lhessize=lhes.size();
  unsigned int ngluon_incoming = 0;
  unsigned int nu_incoming = 0; // 5
  unsigned int nc_incoming = 0; // -5
  unsigned int nb_outgoing = 0;
  unsigned int nbbar_outgoing = 0;
  unsigned int nparton_outgoing = 0;
  //We want event with
  //incoming : 1 g + 1 c/u
  //outgoing : 1 b , no other partons
  cout << "[JHAnalyzerBase::TagWbLHE]" << endl;
  cout << "pid" << setw(15) << "status" << endl;
  unsigned int ntau = 0, nmu = 0, nele = 0;
  for(unsigned int i =0; i < lhessize ; i++){
    int status=lhes[i].Status();
    int pid=lhes[i].ID();
    cout << pid << setw(15) << status << endl;
    if(status==-1){//incoming parton
      if(abs(pid)==2){//if up
	nu_incoming+=1;
      }
      else if(abs(pid)==4){
	nc_incoming+=1;
      }
      else if(pid==21){
	ngluon_incoming+=1;
      }
      
    }//[end] if incoming
    if(status==1){//if outgoing
      if(pid==5){
	nb_outgoing+=1;
      }
      else if(pid==-5){
	nbbar_outgoing+=1;
      }
      
      if(abs(pid)<6 || pid==21){//if parton
	nparton_outgoing+=1;
      }

    }//[end]if outgoing
  }
  cout << "nu_incoming=" << nu_incoming << endl;
  cout << "nc_incoming=" << nc_incoming << endl;
  cout << "ngluon_incoming=" << ngluon_incoming << endl;
  cout << "nb_outgoing=" << nb_outgoing << endl;
  cout << "nbbar_outgoing=" << nbbar_outgoing << endl;
  cout << "nparton_outgoing=" << nparton_outgoing << endl;
  //this_weight,n_bin,x_min,x_max
  if(nparton_outgoing!=1) return 0;
  if(nb_outgoing+nbbar_outgoing!=1) return 0;
  cout << "!! Wb event!!" << endl;
  AnalyzerCore::FillHist("Wb_LHE/nu_incoming/"+ProcessName, nu_incoming, 1., 2,0.,2.);
  AnalyzerCore::FillHist("Wb_LHE/nc_incoming/"+ProcessName, nc_incoming, 1., 2,0.,2.);
  AnalyzerCore::FillHist("Wb_LHE/ngluon_incoming/"+ProcessName, nc_incoming, 1., 2,0.,2.);

  return 1;
}

*/



double JHAnalyzerBase::GetP_JetRestFrame(TLorentzVector &lep, const TLorentzVector &jet){
  TLorentzVector vl_jetrest(lep);
  vl_jetrest.Boost(-jet.BoostVector());
  double pjetrest=vl_jetrest.P();
  if(TMath::IsNaN(pjetrest)) return -1.;
  return pjetrest;
}
double JHAnalyzerBase::GetPt_wrt_Jet(TLorentzVector &lep, const TLorentzVector &jet){
  double ptwrtjet=lep.P()*sin(lep.Angle(jet.Vect()));
  if(TMath::IsNaN(ptwrtjet)) return -1.;
  return ptwrtjet;
}

double JHAnalyzerBase::GetP_along_Jet(TLorentzVector &lep, const TLorentzVector &jet){
  double palongjet=lep.P()*cos(lep.Angle(jet.Vect()));
  if(TMath::IsNaN(palongjet)) return -1.;
  return palongjet;
}


JHAnalyzerBase::bmuonvar JHAnalyzerBase::Get_bmuonvar(Muon &this_muon,const Jet &this_jet){
  bmuonvar ret;
  ret.nsip3d=fabs(this_muon.IP3D()/this_muon.IP3Derr());
  ret.reliso=this_muon.RelIso();
  ret.log10_1_reliso=log10(1.+ret.reliso);
  ret.ptwrtjet=GetPt_wrt_Jet(this_muon,this_jet);
  ret.P_jetrest=GetP_JetRestFrame(this_muon,this_jet);
  ret.bjet_charge_dot_bmuon_charge=this_muon.Charge()*this_jet.Charge();
  ret.palongjet=GetP_along_Jet(this_muon,this_jet);
  ret.palongjetratio=ret.palongjet/this_jet.P();
  ret.charge=this_muon.Charge();
  ret.dR_l_j=this_muon.DeltaR(this_jet);
  ret.reltrkiso=this_muon.TrkIso()/this_muon.Pt();


  ret.pt=this_muon.Pt();
  ret.aeta=fabs(this_muon.Eta());
  ret.normchi2=this_muon.Chi2();
  ret.ntracklayers=this_muon.TrackerLayers();
  ret.ntrackhits=this_muon.TrackerHits();
  ret.nvalidmuonhits=this_muon.ValidMuonHits();
  ret.nmatchedstations=this_muon.MatchedStations();


  ret.isGlobalMuon=this_muon.IsType(Muon::GlobalMuon);
  ret.isTrackerMuon=this_muon.IsType(Muon::TrackerMuon);
  ret.isStandAloneMuon=this_muon.IsType(Muon::StandAloneMuon);
  ret.isCaloMuon=this_muon.IsType(Muon::CaloMuon);
  ret.isPFMuon=this_muon.IsType(Muon::PFMuon);
  ret.isRPCMuon=this_muon.IsType(Muon::RPCMuon);
  ret.isGEMMuon=this_muon.IsType(Muon::GEMMuon);
  ret.isME0Muon=this_muon.IsType(Muon::ME0Muon);

  return ret;


}
/*
JHAnalyzerBase::bmuonvar JHAnalyzerBase::Get_bmuonvar_2409_2(Muon &this_muon, Jet &this_jet){
  //bmuon=Get_bmuonvars(AllMuons[i],jet);
  //bmuon_var=["bmuon_nsip3d<10. ? bmuon_nsip3d : 10.","bmuon_reliso","bmuon_ptwrtbjet < 10. ? bmuon_ptwrtbjet : 10.","bmuon_P_jetrest < 10. ? bmuon_P_jetrest : 10.","bmuon_palongjet < 100. ? bmuon_palongjet: 100.", "bmuon_palongjetratio < 1. ? bmuon_palongjetratio : 1." , "bjet_charge*bmuon_charge", ]  
  bmuonvar ret;
  ret.nsip3d=fabs(this_muon.IP3D()/this_muon.IP3Derr());
  if(ret.nsip3d > 10) ret.nsip3d=10.;
  ret.reliso=this_muon.RelIso();
  if(ret.reliso > 10) ret.reliso=10.;
  ret.ptwrtjet=GetPt_wrt_Jet(this_muon,this_jet);
  if(ret.ptwrtjet >10) ret.ptwrtjet=10.;
  ret.P_jetrest=GetP_JetRestFrame(this_muon,this_jet);
  if(ret.P_jetrest>10) ret.P_jetrest=10.;
  ret.bjet_charge_dot_bmuon_charge=this_muon.Charge()*this_jet.Charge();
  ret.palongjet=GetP_along_Jet(this_muon,this_jet);
  if(ret.palongjet >100 ) ret.palongjet=100.;
  ret.palongjetratio=ret.palongjet/this_jet.P();
  if(ret.palongjetratio>1) ret.palongjetratio=1.;
  ret.charge=this_muon.Charge();




  //--remove 2409.2
  


  ret.dR_l_j=this_muon.DeltaR(this_jet);
  ret.reltrkiso=this_muon.TrkIso()/this_muon.Pt();


  ret.pt=this_muon.Pt();
  ret.aeta=fabs(this_muon.Eta());
  ret.normchi2=this_muon.Chi2();
  ret.ntracklayers=this_muon.TrackerLayers();
  ret.ntrackhits=this_muon.TrackerHits();
  ret.nvalidmuonhits=this_muon.ValidMuonHits();
  ret.nmatchedstations=this_muon.MatchedStations();


  ret.isGlobalMuon=this_muon.IsType(Muon::GlobalMuon);
  ret.isTrackerMuon=this_muon.IsType(Muon::TrackerMuon);
  ret.isStandAloneMuon=this_muon.IsType(Muon::StandAloneMuon);
  ret.isCaloMuon=this_muon.IsType(Muon::CaloMuon);
  ret.isPFMuon=this_muon.IsType(Muon::PFMuon);
  ret.isRPCMuon=this_muon.IsType(Muon::RPCMuon);
  ret.isGEMMuon=this_muon.IsType(Muon::GEMMuon);
  ret.isME0Muon=this_muon.IsType(Muon::ME0Muon);

  return ret;
}
*/


JHAnalyzerBase::belectronvar JHAnalyzerBase::Get_belectronvar(Electron &this_electron, const Jet &this_jet){

  belectronvar ret;
  ret.nsip3d=fabs(this_electron.IP3D()/this_electron.IP3Derr());
  ret.reliso=this_electron.RelIso();
  ret.log10_1_reliso=log10(1.+ret.reliso);

  ret.ptwrtjet=GetPt_wrt_Jet(this_electron,this_jet);
  ret.P_jetrest=GetP_JetRestFrame(this_electron,this_jet);
  ret.bjet_charge_dot_belectron_charge=this_electron.Charge()*this_jet.Charge();
  
  ret.palongjet=GetP_along_Jet(this_electron,this_jet);
  ret.palongjetratio=ret.palongjet/this_jet.P();
  ret.charge=this_electron.Charge();



  //  --rm for v2409.2

  ret.dR_l_j=this_electron.DeltaR(this_jet);  
  ret.reltrkiso=this_electron.TrkIso()/this_electron.Pt();                                                                                       
  ret.relecalPFClusterIso=this_electron.ecalPFClusterIso()/this_electron.Pt();
  ret.charge=this_electron.Charge();
  ret.IsGsfCtfScPixChargeConsistent=this_electron.IsGsfCtfScPixChargeConsistent();
  ret.PassConversionVeto=this_electron.PassConversionVeto();
  
  ret.pt=this_electron.Pt();
  ret.aeta=this_electron.Eta();
  ret.full5x5sigmaietaieta=this_electron.Full5x5_sigmaIetaIeta();
  ret.detaseed=this_electron.dEtaSeed();
  ret.abs_detaseed=fabs(ret.detaseed);
  ret.HoverE=this_electron.HoverE();
  ret.InvEminusInvP=fabs(this_electron.InvEminusInvP());
  ret.nmissinghits=this_electron.NMissingHits();
  ret.dPhiIn=this_electron.dPhiIn();
  ret.abs_dPhiIn=fabs(ret.dPhiIn);
  
  ret.passVetoID=this_electron.PassID("passVetoID");
  ret.passVetoIDnoIso=this_electron.PassID("passVetoIDnoIso");
  ret.passLooseID=this_electron.PassID("passLooseID");
  ret.passMediumID=this_electron.PassID("passMediumID");
  ret.passTightID=this_electron.PassID("passTightID");

  return ret;
}
/*

JHAnalyzerBase::belectronvar JHAnalyzerBase::Get_belectronvar_2409_2(Electron &this_electron, Jet &this_jet){
  //belectron=Get_belectronvars(AllElectrons[i],jet);
  //belectron_var=["belectron_nsip3d < 30. ? belectron_nsip3d : 30.","belectron_reliso","belectron_ptwrtbjet < 10. ? belectron_ptwrtbjet : 10.","belectron_P_jetrest < 10. ? belectron_P_jetrest : 10.","belectron_palongjet < 100. ? belectron_palongjet : 100.","belectron_palongjetratio < 1. ? belectron_palongjetratio : 1.","bjet_charge*belectron_charge"]  

  belectronvar ret;
  ret.nsip3d=fabs(this_electron.IP3D()/this_electron.IP3Derr());
  if(ret.nsip3d>30) ret.nsip3d=30.;
  ret.reliso=this_electron.RelIso();
  if(ret.reliso>10) ret.reliso=10.;
  ret.ptwrtjet=GetPt_wrt_Jet(this_electron,this_jet);
  if(ret.ptwrtjet>10) ret.ptwrtjet=10.;
  ret.P_jetrest=GetP_JetRestFrame(this_electron,this_jet);
  if(ret.P_jetrest>10) ret.P_jetrest=10.;
  ret.bjet_charge_dot_belectron_charge=this_electron.Charge()*this_jet.Charge();
  
  ret.palongjet=GetP_along_Jet(this_electron,this_jet);
  if(ret.palongjet>100) ret.palongjet=100;
  ret.palongjetratio=ret.palongjet/this_jet.P();
  ret.charge=this_electron.Charge();



  //  --rm for v2409.2

  ret.dR_l_j=this_electron.DeltaR(this_jet);  
  ret.reltrkiso=this_electron.TrkIso()/this_electron.Pt();                                                                                       
  ret.relecalPFClusterIso=this_electron.ecalPFClusterIso()/this_electron.Pt();
  ret.charge=this_electron.Charge();
  ret.IsGsfCtfScPixChargeConsistent=this_electron.IsGsfCtfScPixChargeConsistent();

  ret.pt=this_electron.Pt();
  ret.aeta=this_electron.Eta();
  ret.full5x5sigmaietaieta=this_electron.Full5x5_sigmaIetaIeta();
  ret.detaseed=this_electron.dEtaSeed();
  ret.abs_detaseed=fabs(ret.detaseed);
  ret.HoverE=this_electron.HoverE();
  ret.InvEminusInvP=fabs(this_electron.InvEminusInvP());
  ret.nmissinghits=this_electron.NMissingHits();



  return ret;
}
*/

JHAnalyzerBase::bjetvar JHAnalyzerBase::Get_bjetvar(const Jet &this_jet){
  bjetvar ret;

  ret.ChargedHadronEnergyFraction=this_jet.GetChargedHadronEnergyFraction();
  ret.NeutralHadronEnergyFraction=this_jet.GetNeutralHadronEnergyFraction();
  ret.log_NeutralHadronEnergyFraction=log(this_jet.GetNeutralHadronEnergyFraction());
  ret.NeutralEmEnergyFraction=this_jet.GetNeutralEmEnergyFraction();
  ret.ChargedEmEnergyFraction=this_jet.GetChargedEmEnergyFraction();
  ret.MuonEnergyFraction=this_jet.GetMuonEnergyFraction();
  ret.log_MuonEnergyFraction=log(this_jet.GetMuonEnergyFraction());
  ret.ChargedMultiplicity=this_jet.ChargedMultiplicity();
  ret.NeutralMultiplicity=this_jet.NeutralMultiplicity();
  ret.abs_charge=fabs(this_jet.Charge());
  ret.charge=this_jet.Charge();

  //skip for faster run

  ret.pt=this_jet.Pt();
  ret.aeta=fabs(this_jet.Eta());
  ret.eta=this_jet.Eta();



  ret.partonFlavour=this_jet.partonFlavour();//if is data -> 0
  ret.hadronFlavour=this_jet.hadronFlavour();//if is data -> 0

  
  return ret;
}

void JHAnalyzerBase::DeleteChargeScoreTool(){
  cout << "delete mChargeTool" << endl;
  if (mChargeTool){
    cout << "skip delete mChargeTool" << endl;
    //delete mChargeTool;
    //mChargeTool=nullptr;
  }
  
  cout << "delete eChargeTool" << endl;
  if (eChargeTool){
    cout << "skip delete eChargeTool" << endl;
    //delete eChargeTool;
    //eChargeTool=nullptr;
  }
  cout << "delete jChargeTool" << endl;
  if (jChargeTool){
    cout << "skip delete jChargeTool" << endl;
    //delete jChargeTool;
    //jChargeTool=nullptr;
  }
}
void JHAnalyzerBase::LoadChargeScoreTool(TString muon_version,TString electron_version, TString jet_version, bool applycut){
  //muon_score_version=muon_version;
  //electron_score_version=electron_version;
  //jet_score_version=jet_version;



  //bmuon_ChargeTool
  //belectron_ChargeTool
  //bjet_ChargeTool
  if(muon_version=="2608.2" && electron_version=="2608.2" && jet_version=="2608.2"){
    LoadChargeScoreTool_2608_2(applycut);
    return;    
  }
  else if(muon_version=="2409.2" && electron_version=="2409.2" && jet_version=="2409.2"){
    LoadChargeScoreTool_2409_2(applycut);
    return;
  }
  else if(muon_version=="2512.5" && electron_version=="2512.5" && jet_version=="2512.5"){    
    LoadChargeScoreTool_2512_5(applycut);
  }
  else if(muon_version=="2512.4" && electron_version=="2512.4" && jet_version=="2512.4"){    
    LoadChargeScoreTool_2512_4(applycut);
  }
  else if(muon_version=="2512.3" && electron_version=="2512.3" && jet_version=="2512.3"){    
    LoadChargeScoreTool_2512_3(applycut);
  }
  else{
    cout << "No Valid chargescore for the version" << endl;
  }
  return;
}



void JHAnalyzerBase::LoadChargeScoreTool_2608_2(bool applycut){
  IsChargeScoreToolOn=1;
  TString muon_version="2608.2";
  TString electron_version="2608.2";
  TString jet_version="2608.2";
  mChargeTool=new ChargeScoreTool("muon",muon_version,DataEra);
  eChargeTool=new ChargeScoreTool("electron",electron_version,DataEra);
  jChargeTool=new ChargeScoreTool("jet",jet_version,DataEra);
  //Link variables
  ///---Muon---//
  if(DataEra=="2016preVFP"){
    mChargeTool->AddVariable("bmuon_dR_l_j<0.05?0.05:bmuon_dR_l_j",&bmuon_ChargeTool.dR_l_j,0.05);
    mChargeTool->AddVariable("bmuon_nsip3d>10.?10.:bmuon_nsip3d",&bmuon_ChargeTool.nsip3d,0.,10.);
    mChargeTool->AddVariable("bmuon_P_jetrest<1.?1:bmuon_P_jetrest>3.?3.:bmuon_P_jetrest",&bmuon_ChargeTool.P_jetrest,1.,3.);
    mChargeTool->AddVariable("bmuon_palongjet>10.?10.:bmuon_palongjet",&bmuon_ChargeTool.palongjet,0.,10.);
    mChargeTool->AddVariable("bmuon_palongjetratio>0.4?0.4:bmuon_palongjetratio",&bmuon_ChargeTool.palongjetratio,0.,0.4);
    mChargeTool->AddVariable("bmuon_ptwrtbjet<0.5?0.5:bmuon_ptwrtbjet>3.?3.:bmuon_ptwrtbjet",&bmuon_ChargeTool.ptwrtjet,0.5,3.);
    mChargeTool->AddVariable("log10(1.+bmuon_reliso)>1.2?1.2:log10(1.+bmuon_reliso)",&bmuon_ChargeTool.log10_1_reliso,0.,1.2);
    mChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.1?0.1:bjet_ChargedHadronEnergyFraction>0.9?0.9:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.1,0.9);
    mChargeTool->AddVariable("bjet_ChargedMultiplicity>20?20:bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity,0.,20.);
    mChargeTool->AddVariable("bjet_MuonEnergyFraction<0.2?0.2:bjet_MuonEnergyFraction>0.5?0.5:bjet_MuonEnergyFraction",&bjet_ChargeTool.MuonEnergyFraction,0.2,0.5);
    mChargeTool->AddVariable("bjet_NeutralEmEnergyFraction<0.15?0.15:bjet_NeutralEmEnergyFraction>0.5?0.5:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.15,0.5);
    mChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction<0.15?0.15:bjet_NeutralHadronEnergyFraction>0.4?0.4:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.15,0.4);
    mChargeTool->AddVariable("bjet_NeutralMultiplicity>25?25:bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity,0.,25.);
    mChargeTool->AddVariable("bjet_charge*bmuon_charge<-0.4?-0.4:bjet_charge*bmuon_charge",&bmuon_ChargeTool.bjet_charge_dot_bmuon_charge,-0.4);
    mChargeTool->AddVariable("fabs(bjet_charge)",&bjet_ChargeTool.abs_charge);


  }
  else if(DataEra=="2016postVFP"){
    mChargeTool->AddVariable("bmuon_dR_l_j",&bmuon_ChargeTool.dR_l_j);
    mChargeTool->AddVariable("bmuon_nsip3d>10.?10.:bmuon_nsip3d",&bmuon_ChargeTool.nsip3d,0.,10.);
    mChargeTool->AddVariable("bmuon_P_jetrest>2.5?2.5:bmuon_P_jetrest",&bmuon_ChargeTool.P_jetrest,0.,2.5);
    mChargeTool->AddVariable("bmuon_palongjet>10.?10.:bmuon_palongjet",&bmuon_ChargeTool.palongjet,0.,10.);
    mChargeTool->AddVariable("bmuon_palongjetratio>0.4?0.4:bmuon_palongjetratio",&bmuon_ChargeTool.palongjetratio,0.,0.4);
    mChargeTool->AddVariable("bmuon_ptwrtbjet>3.?3.:bmuon_ptwrtbjet",&bmuon_ChargeTool.ptwrtjet,0.,3.);
    mChargeTool->AddVariable("log10(1.+bmuon_reliso)>1.2?1.2:log10(1.+bmuon_reliso)",&bmuon_ChargeTool.log10_1_reliso,0.,1.2);
    mChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.1?0.1:bjet_ChargedHadronEnergyFraction>0.9?0.9:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.1,0.9);
    mChargeTool->AddVariable("bjet_MuonEnergyFraction<0.2?0.2:bjet_MuonEnergyFraction>0.5?0.5:bjet_MuonEnergyFraction",&bjet_ChargeTool.MuonEnergyFraction,0.2,0.5);
    mChargeTool->AddVariable("bjet_NeutralEmEnergyFraction>0.5?0.5:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.,0.5);
    mChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction>0.3?0.3:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.,0.3);
    mChargeTool->AddVariable("bjet_NeutralMultiplicity>25?25:bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity,0.,25.);
    mChargeTool->AddVariable("bjet_charge*bmuon_charge<-0.4?-0.4:bjet_charge*bmuon_charge",&bmuon_ChargeTool.bjet_charge_dot_bmuon_charge,-0.4);
    mChargeTool->AddVariable("fabs(bjet_charge)>0.6?0.6:fabs(bjet_charge)",&bjet_ChargeTool.abs_charge,0.,0.6);



  }
  else if(DataEra=="2017"){
    mChargeTool->AddVariable("bmuon_dR_l_j",&bmuon_ChargeTool.dR_l_j);
    mChargeTool->AddVariable("bmuon_nsip3d>10.?10.:bmuon_nsip3d",&bmuon_ChargeTool.nsip3d,0.,10.);
    mChargeTool->AddVariable("bmuon_P_jetrest<1.?1.:bmuon_P_jetrest>4.?4.:bmuon_P_jetrest",&bmuon_ChargeTool.P_jetrest,1.,4.);
    mChargeTool->AddVariable("bmuon_palongjet>10.?10.:bmuon_palongjet",&bmuon_ChargeTool.palongjet,0.,10.);
    mChargeTool->AddVariable("bmuon_palongjetratio>0.4?0.4:bmuon_palongjetratio",&bmuon_ChargeTool.palongjetratio,0.,0.4);
    mChargeTool->AddVariable("bmuon_ptwrtbjet>3.?3.:bmuon_ptwrtbjet",&bmuon_ChargeTool.ptwrtjet,0.,3.);
    mChargeTool->AddVariable("log10(1.+bmuon_reliso)>1.2?1.2:log10(1.+bmuon_reliso)",&bmuon_ChargeTool.log10_1_reliso,0.,1.2);
    mChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.2?0.2:bjet_ChargedHadronEnergyFraction>0.9?0.9:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.2,0.9);
    mChargeTool->AddVariable("bjet_MuonEnergyFraction<0.2?0.2:bjet_MuonEnergyFraction>0.4?0.4:bjet_MuonEnergyFraction",&bjet_ChargeTool.MuonEnergyFraction,0.2,0.4);
    mChargeTool->AddVariable("bjet_NeutralEmEnergyFraction>0.5?0.5:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.,0.5);
    mChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction<0.1?0.1:bjet_NeutralHadronEnergyFraction>0.3?0.3:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.1,0.3);
    mChargeTool->AddVariable("bjet_NeutralMultiplicity>25?25:bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity,0.,25.);
    mChargeTool->AddVariable("bjet_charge*bmuon_charge<-0.3?-0.3:bjet_charge*bmuon_charge>0.5?0.5:bjet_charge*bmuon_charge",&bmuon_ChargeTool.bjet_charge_dot_bmuon_charge,-0.3,0.5);
    mChargeTool->AddVariable("fabs(bjet_charge)>0.5?0.5:fabs(bjet_charge)",&bjet_ChargeTool.abs_charge,0.,0.5);


  }
  else if(DataEra=="2018"){
    mChargeTool->AddVariable("bmuon_dR_l_j",&bmuon_ChargeTool.dR_l_j);
    mChargeTool->AddVariable("bmuon_nsip3d<0.1?0.1:bmuon_nsip3d>10.?10.:bmuon_nsip3d",&bmuon_ChargeTool.nsip3d,0.1,10.);
    mChargeTool->AddVariable("bmuon_P_jetrest<1.?1.:bmuon_P_jetrest>4.?4.:bmuon_P_jetrest",&bmuon_ChargeTool.P_jetrest,1.,4.);
    mChargeTool->AddVariable("bmuon_palongjet>10.?10.:bmuon_palongjet",&bmuon_ChargeTool.palongjet,0.,10.);
    mChargeTool->AddVariable("bmuon_palongjetratio>0.4?0.4:bmuon_palongjetratio",&bmuon_ChargeTool.palongjetratio,0.,0.4);
    mChargeTool->AddVariable("bmuon_ptwrtbjet<1.?1.:bmuon_ptwrtbjet>3.5?3.5:bmuon_ptwrtbjet",&bmuon_ChargeTool.ptwrtjet,1.,3.5);
    mChargeTool->AddVariable("log10(1.+bmuon_reliso)>1.2?1.2:log10(1.+bmuon_reliso)",&bmuon_ChargeTool.log10_1_reliso,0.,1.2);
    mChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.2?0.2:bjet_ChargedHadronEnergyFraction>0.9?0.9:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.2,0.9);
    mChargeTool->AddVariable("bjet_MuonEnergyFraction<0.2?0.2:bjet_MuonEnergyFraction>0.4?0.4:bjet_MuonEnergyFraction",&bjet_ChargeTool.MuonEnergyFraction,0.2,0.4);
    mChargeTool->AddVariable("bjet_NeutralEmEnergyFraction>0.5?0.5:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.,0.5);
    mChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction<0.1?0.1:bjet_NeutralHadronEnergyFraction>0.3?0.3:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.1,0.3);
    mChargeTool->AddVariable("bjet_NeutralMultiplicity>25?25:bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity,0.,25.);
    mChargeTool->AddVariable("bjet_charge*bmuon_charge<-0.3?-0.3:bjet_charge*bmuon_charge>0.5?0.5:bjet_charge*bmuon_charge",&bmuon_ChargeTool.bjet_charge_dot_bmuon_charge,-0.3,0.5);
    mChargeTool->AddVariable("fabs(bjet_charge)>0.5?0.5:fabs(bjet_charge)",&bjet_ChargeTool.abs_charge,0.,0.5);


  }
  mChargeTool->SetupTMVA();

  //---Electron---//
  if(DataEra=="2016preVFP"){
    eChargeTool->AddVariable("belectron_dR_l_j<0.13?0.13:belectron_dR_l_j",&belectron_ChargeTool.dR_l_j,0.13);
    eChargeTool->AddVariable("belectron_P_jetrest<0.8?0.8:belectron_P_jetrest>1.5?1.5:belectron_P_jetrest",&belectron_ChargeTool.P_jetrest,0.8,1.5);
    eChargeTool->AddVariable("belectron_palongjet>15.?15.:belectron_palongjet",&belectron_ChargeTool.palongjet,0.,15.);
    eChargeTool->AddVariable("belectron_palongjetratio>0.15?0.15:belectron_palongjetratio",&belectron_ChargeTool.palongjetratio,0.,0.15);
    eChargeTool->AddVariable("belectron_ptwrtbjet<0.8?0.8:belectron_ptwrtbjet>1.2?1.2:belectron_ptwrtbjet",&belectron_ChargeTool.ptwrtjet,0.8,1.2);
    eChargeTool->AddVariable("bjet_ChargedEmEnergyFraction>0.2?0.2:bjet_ChargedEmEnergyFraction",&bjet_ChargeTool.ChargedEmEnergyFraction,0.,0.2);
    eChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.3?0.3:bjet_ChargedHadronEnergyFraction>0.7?0.7:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.3,0.7);
    eChargeTool->AddVariable("bjet_NeutralEmEnergyFraction<0.2?0.2:bjet_NeutralEmEnergyFraction>0.6?0.6:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.2,0.6);
    eChargeTool->AddVariable("bjet_charge*belectron_charge<-0.4?-0.4:bjet_charge*belectron_charge>0.2?0.2:bjet_charge*belectron_charge",&belectron_ChargeTool.bjet_charge_dot_belectron_charge,-0.4,0.2);
    eChargeTool->AddVariable("fabs(bjet_charge)",&bjet_ChargeTool.abs_charge);

  }
  else if(DataEra=="2016postVFP"){
    eChargeTool->AddVariable("belectron_dR_l_j<0.13?0.13:belectron_dR_l_j",&belectron_ChargeTool.dR_l_j,0.13);
    eChargeTool->AddVariable("belectron_nsip3d>10.?10.:belectron_nsip3d",&belectron_ChargeTool.nsip3d,0.,10.);
    eChargeTool->AddVariable("belectron_P_jetrest>2.?2.:belectron_P_jetrest",&belectron_ChargeTool.P_jetrest,0.,2.);
    eChargeTool->AddVariable("belectron_palongjet>15.?15.:belectron_palongjet",&belectron_ChargeTool.palongjet,0.,15.);
    eChargeTool->AddVariable("belectron_palongjetratio>0.2?0.2:belectron_palongjetratio",&belectron_ChargeTool.palongjetratio,0.,0.2);
    eChargeTool->AddVariable("belectron_ptwrtbjet<0.5?0.5:belectron_ptwrtbjet>3.?3.:belectron_ptwrtbjet",&belectron_ChargeTool.ptwrtjet,0.5,3.);
    eChargeTool->AddVariable("log10(1.+belectron_reliso)>1.?1.:log10(1.+belectron_reliso)",&belectron_ChargeTool.log10_1_reliso,0.,1.);
    eChargeTool->AddVariable("bjet_ChargedEmEnergyFraction>0.2?0.2:bjet_ChargedEmEnergyFraction",&bjet_ChargeTool.ChargedEmEnergyFraction,0.,0.2);
    eChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.3?0.3:bjet_ChargedHadronEnergyFraction>0.8?0.8:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.3,0.8);
    eChargeTool->AddVariable("bjet_NeutralEmEnergyFraction<0.15?0.15:bjet_NeutralEmEnergyFraction>0.6?0.6:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.15,0.6);
    eChargeTool->AddVariable("bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity);
    eChargeTool->AddVariable("bjet_charge*belectron_charge<-0.4?-0.4:bjet_charge*belectron_charge>0.2?0.2:bjet_charge*belectron_charge",&belectron_ChargeTool.bjet_charge_dot_belectron_charge,-0.4,0.2);
    eChargeTool->AddVariable("fabs(bjet_charge)>0.35?0.35:fabs(bjet_charge)",&bjet_ChargeTool.abs_charge,0.,0.35);


  }
  else if(DataEra=="2017"){
    eChargeTool->AddVariable("belectron_dR_l_j<0.13?0.13:belectron_dR_l_j",&belectron_ChargeTool.dR_l_j,0.13);
    eChargeTool->AddVariable("belectron_nsip3d>10.?10.:belectron_nsip3d",&belectron_ChargeTool.nsip3d,0.,10.);
    eChargeTool->AddVariable("belectron_P_jetrest>2.?2.:belectron_P_jetrest",&belectron_ChargeTool.P_jetrest,0.,2.);
    eChargeTool->AddVariable("belectron_palongjet>15.?15.:belectron_palongjet",&belectron_ChargeTool.palongjet,0.,15.);
    eChargeTool->AddVariable("belectron_palongjetratio>0.2?0.2:belectron_palongjetratio",&belectron_ChargeTool.palongjetratio,0.,0.2);
    eChargeTool->AddVariable("belectron_ptwrtbjet>3.?3.:belectron_ptwrtbjet",&belectron_ChargeTool.ptwrtjet,0.,3.);
    eChargeTool->AddVariable("log10(1.+belectron_reliso)>1.1?1.1:log10(1.+belectron_reliso)<0.3?0.3:log10(1.+belectron_reliso)",&belectron_ChargeTool.log10_1_reliso,0.3,1.1);
    eChargeTool->AddVariable("bjet_ChargedEmEnergyFraction>0.2?0.2:bjet_ChargedEmEnergyFraction",&bjet_ChargeTool.ChargedEmEnergyFraction,0.,0.2);
    eChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.5?0.5:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.5);
    eChargeTool->AddVariable("bjet_NeutralEmEnergyFraction<0.15?0.15:bjet_NeutralEmEnergyFraction>0.6?0.6:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.15,0.6);
    eChargeTool->AddVariable("bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity);
    eChargeTool->AddVariable("bjet_charge*belectron_charge<-0.4?-0.4:bjet_charge*belectron_charge>0.2?0.2:bjet_charge*belectron_charge",&belectron_ChargeTool.bjet_charge_dot_belectron_charge,-0.4,0.2);
    eChargeTool->AddVariable("fabs(bjet_charge)>0.35?0.35:fabs(bjet_charge)",&bjet_ChargeTool.abs_charge,0.,0.35);


  }
  else if(DataEra=="2018"){
    eChargeTool->AddVariable("belectron_dR_l_j<0.1?0.1:belectron_dR_l_j",&belectron_ChargeTool.dR_l_j,0.1);
    eChargeTool->AddVariable("belectron_nsip3d>10.?10.:belectron_nsip3d",&belectron_ChargeTool.nsip3d,0.,10.);
    eChargeTool->AddVariable("belectron_P_jetrest>3.?3.:belectron_P_jetrest",&belectron_ChargeTool.P_jetrest,0.,3.);
    eChargeTool->AddVariable("belectron_palongjet>15.?15.:belectron_palongjet",&belectron_ChargeTool.palongjet,0.,15.);
    eChargeTool->AddVariable("belectron_palongjetratio>0.15?0.15:belectron_palongjetratio",&belectron_ChargeTool.palongjetratio,0.,0.15);
    eChargeTool->AddVariable("belectron_ptwrtbjet>3.?3.:belectron_ptwrtbjet",&belectron_ChargeTool.ptwrtjet,0.,3.);
    eChargeTool->AddVariable("log10(1.+belectron_reliso)>1.2?1.2:log10(1.+belectron_reliso)<0.3?0.3:log10(1.+belectron_reliso)",&belectron_ChargeTool.log10_1_reliso,0.3,1.2);
    eChargeTool->AddVariable("bjet_ChargedEmEnergyFraction>0.1?0.1:bjet_ChargedEmEnergyFraction",&bjet_ChargeTool.ChargedEmEnergyFraction,0.,0.1);
    eChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.5?0.5:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.5);
    eChargeTool->AddVariable("bjet_NeutralEmEnergyFraction<0.15?0.15:bjet_NeutralEmEnergyFraction>0.6?0.6:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.15,0.6);
    eChargeTool->AddVariable("bjet_charge*belectron_charge<-0.4?-0.4:bjet_charge*belectron_charge>0.2?0.2:bjet_charge*belectron_charge",&belectron_ChargeTool.bjet_charge_dot_belectron_charge,-0.4,0.2);
    eChargeTool->AddVariable("fabs(bjet_charge)>0.35?0.35:fabs(bjet_charge)",&bjet_ChargeTool.abs_charge,0.,0.35);

  }
  eChargeTool->SetupTMVA();
  //---Jet----//
  
  if(DataEra=="2016preVFP"){
    jChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.15?0.15:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.15);
    jChargeTool->AddVariable("bjet_ChargedMultiplicity>30?30:bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity,0.,30.);
    jChargeTool->AddVariable("bjet_NeutralEmEnergyFraction<0.1?0.1:bjet_NeutralEmEnergyFraction>0.7?0.7:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.1,0.7);
    jChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction<0.1?0.1:bjet_NeutralHadronEnergyFraction>0.4?0.4:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.1,0.4);
    jChargeTool->AddVariable("bjet_NeutralMultiplicity>30?30:bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity,0.,30.);
    jChargeTool->AddVariable("fabs(bjet_charge)",&bjet_ChargeTool.abs_charge);

  }
  else if(DataEra=="2016postVFP"){
    jChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.2?0.2:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.2);
    jChargeTool->AddVariable("bjet_NeutralEmEnergyFraction>0.7?0.7:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.,0.7);
    jChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction>0.4?0.4:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.,0.4);
    jChargeTool->AddVariable("bjet_NeutralMultiplicity>30?30:bjet_NeutralMultiplicity<5?5:bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity,5.,30.);
    jChargeTool->AddVariable("fabs(bjet_charge)",&bjet_ChargeTool.abs_charge);
  }
  else if(DataEra=="2017"){
    jChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.2?0.2:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.2);
    jChargeTool->AddVariable("bjet_NeutralEmEnergyFraction>0.7?0.7:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.,0.7);
    jChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction>0.4?0.4:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.,0.4);
    jChargeTool->AddVariable("bjet_NeutralMultiplicity>30?30:bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity,0.,30.);
    jChargeTool->AddVariable("fabs(bjet_charge)>0.4?0.4:fabs(bjet_charge)",&bjet_ChargeTool.abs_charge,0.,0.4);
  }
  else if(DataEra=="2018"){
    jChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.15?0.15:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.15);
    jChargeTool->AddVariable("bjet_NeutralEmEnergyFraction>0.7?0.7:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.,0.7);
    jChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction<0.05?0.05:bjet_NeutralHadronEnergyFraction>0.5?0.5:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.05,0.5);
    jChargeTool->AddVariable("bjet_NeutralMultiplicity>30?30:bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity,0.,30.);
    jChargeTool->AddVariable("fabs(bjet_charge)>0.4?0.4:fabs(bjet_charge)",&bjet_ChargeTool.abs_charge,0.,0.4);
  }

  jChargeTool->SetupTMVA();


  if (applycut){

    map<TString,float> map_muon_mincut;
    map_muon_mincut["2016preVFP"]=-0.05;  map_muon_mincut["2016postVFP"]=0.05;  map_muon_mincut["2017"]=0.05; map_muon_mincut["2018"]=0.05;
    map<TString,float> map_muon_maxcut;
    map_muon_maxcut["2016preVFP"]=-0.5;  map_muon_maxcut["2016postVFP"]=-0.55;  map_muon_maxcut["2017"]=-0.45; map_muon_maxcut["2018"]=-0.5;


    map<TString,float> map_electron_mincut;
    map_electron_mincut["2016preVFP"]=0.05;  map_electron_mincut["2016postVFP"]=0.05;  map_electron_mincut["2017"]=0.1; map_electron_mincut["2018"]=0.05;
    map<TString,float> map_electron_maxcut;
    map_electron_maxcut["2016preVFP"]=-0.45;  map_electron_maxcut["2016postVFP"]=-0.35;  map_electron_maxcut["2017"]=-0.45; map_electron_maxcut["2018"]=-0.4;
    map<TString,float> map_jet_mincut;
    map_jet_mincut["2016preVFP"]=0.01;  map_jet_mincut["2016postVFP"]=0.01;  map_jet_mincut["2017"]=0.02; map_jet_mincut["2018"]=0.03;
    map<TString,float> map_jet_maxcut;//Turn off this region                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
    map_jet_maxcut["2016preVFP"]=-1;  map_jet_maxcut["2016postVFP"]=-1;  map_jet_maxcut["2017"]=-1; map_jet_maxcut["2018"]=-1;


    cout << "[JHAnalyzerBase::SetChargeScoreCut_2409_2] " << endl;
    cout << "Muon" << endl;
    mChargeTool->SetMinCut(map_muon_mincut[DataEra]);
    mChargeTool->SetMaxCut(map_muon_maxcut[DataEra]);
    cout << "Electron" << endl;
    eChargeTool->SetMinCut(map_electron_mincut[DataEra]);
    eChargeTool->SetMaxCut(map_electron_maxcut[DataEra]);
    cout << "Jet" << endl;
    jChargeTool->SetMinCut(map_jet_mincut[DataEra]);
    jChargeTool->SetMaxCut(map_jet_maxcut[DataEra]);

  }
  for(int i = 0 ; i < 10 ; i++){
    cout << "i=" << i << endl;
    mChargeTool->SetScore();
    cout << "mChargeTool->GetScore()=" << mChargeTool->GetScore() << endl;
    eChargeTool->SetScore();
    cout << "eChargeTool->GetScore()=" << eChargeTool->GetScore() << endl;
    jChargeTool->SetScore();
    cout << "jChargeTool->GetScore()=" << jChargeTool->GetScore() << endl;
  }
}




void JHAnalyzerBase::LoadChargeScoreTool_2512_5(bool applycut){
  IsChargeScoreToolOn=1;
  TString muon_version="2512.5";
  TString electron_version="2512.5";
  TString jet_version="2512.5";
  mChargeTool=new ChargeScoreTool("muon",muon_version,DataEra);
  eChargeTool=new ChargeScoreTool("electron",electron_version,DataEra);
  jChargeTool=new ChargeScoreTool("jet",jet_version,DataEra);
  //Link variables
  //void TMVATool::AddVariable(TString _formula, float *_this_var_address)
  /*

  //bmuon_ChargeTool
  //belectron_ChargeTool
  //bjet_ChargeTool


   */
  ///---Muon---//
  if(DataEra=="2016preVFP"){

    mChargeTool->AddVariable("bmuon_dR_l_j<0.04?0.04:bmuon_dR_l_j",&bmuon_ChargeTool.dR_l_j,0.04);
    mChargeTool->AddVariable("(bmuon_P_jetrest<1.5)?1.5:(bmuon_P_jetrest>3.)?3.:bmuon_P_jetrest",&bmuon_ChargeTool.P_jetrest,1.5,3.);
    mChargeTool->AddVariable("bmuon_palongjet<25.?bmuon_palongjet:25.",&bmuon_ChargeTool.palongjet,0.,25.);
    mChargeTool->AddVariable("(bmuon_ptwrtbjet<1.)?1.:(bmuon_ptwrtbjet>3.)?3.:bmuon_ptwrtbjet",&bmuon_ChargeTool.ptwrtjet,1.,3.);
    mChargeTool->AddVariable("(bmuon_reliso<1.)?1:(bmuon_reliso>5.)?5.:bmuon_reliso",&bmuon_ChargeTool.reliso,1.,5.);
    mChargeTool->AddVariable("(bjet_ChargedHadronEnergyFraction<0.1)?0.1:(bjet_ChargedHadronEnergyFraction>0.6)?0.6:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.1,0.6);
    mChargeTool->AddVariable("(bjet_ChargedMultiplicity<2)?2:(bjet_ChargedMultiplicity>30)?30:bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity,2.,30.);
    mChargeTool->AddVariable("(bjet_MuonEnergyFraction<0.25)?0.25:(bjet_MuonEnergyFraction>0.5)?0.5:bjet_MuonEnergyFraction",&bjet_ChargeTool.MuonEnergyFraction,0.25,0.5);
    mChargeTool->AddVariable("(bjet_NeutralEmEnergyFraction<0.2)?0.2:(bjet_NeutralEmEnergyFraction>0.5)?0.5:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.2,0.5);
    mChargeTool->AddVariable("(bjet_NeutralHadronEnergyFraction<0.15)?0.15:(bjet_NeutralHadronEnergyFraction>0.4)?0.4:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.15,0.4);
    mChargeTool->AddVariable("(bjet_NeutralMultiplicity<6)?6:(bjet_NeutralMultiplicity>25)?25:bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity,6.,25.);
    mChargeTool->AddVariable("fabs(bjet_charge)",&bjet_ChargeTool.abs_charge);
    mChargeTool->AddVariable("(bjet_charge*bmuon_charge<-0.1)?-0.1:bjet_charge*bmuon_charge",&bmuon_ChargeTool.bjet_charge_dot_bmuon_charge,-0.1);

  }
  else if(DataEra=="2016postVFP"){
    mChargeTool->AddVariable("bmuon_dR_l_j<0.04?0.04:bmuon_dR_l_j",&bmuon_ChargeTool.dR_l_j,0.04);
    mChargeTool->AddVariable("bmuon_nsip3d<10.?bmuon_nsip3d:10.",&bmuon_ChargeTool.nsip3d,0.,10.);
    mChargeTool->AddVariable("(bmuon_P_jetrest<1.5)?1.5:(bmuon_P_jetrest>4.)?4.:bmuon_P_jetrest",&bmuon_ChargeTool.P_jetrest,1.5,4.);
    mChargeTool->AddVariable("bmuon_palongjet<30.?bmuon_palongjet:30.",&bmuon_ChargeTool.palongjet,0.,30.);
    mChargeTool->AddVariable("(bmuon_ptwrtbjet<1.)?1.:(bmuon_ptwrtbjet>3.)?3.:bmuon_ptwrtbjet",&bmuon_ChargeTool.ptwrtjet,1.,3.);
    mChargeTool->AddVariable("bmuon_reliso<6.?bmuon_reliso:6.",&bmuon_ChargeTool.reliso,0.,6.);
    mChargeTool->AddVariable("(bjet_ChargedHadronEnergyFraction<0.2)?0.2:(bjet_ChargedHadronEnergyFraction>0.8)?0.8:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.2,0.8);
    mChargeTool->AddVariable("(bjet_MuonEnergyFraction<0.25)?0.25:(bjet_MuonEnergyFraction>0.45)?0.45:bjet_MuonEnergyFraction",&bjet_ChargeTool.MuonEnergyFraction,0.25,0.45);
    mChargeTool->AddVariable("(bjet_NeutralEmEnergyFraction<0.4)?bjet_NeutralEmEnergyFraction:0.4",&bjet_ChargeTool.NeutralEmEnergyFraction,0.,0.4);
    mChargeTool->AddVariable("(bjet_NeutralHadronEnergyFraction<0.15)?0.15:(bjet_NeutralHadronEnergyFraction>0.4)?0.4:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.15,0.4);
    mChargeTool->AddVariable("(bjet_NeutralMultiplicity<25)?bjet_NeutralMultiplicity:25",&bjet_ChargeTool.NeutralMultiplicity,0.,25.);
    mChargeTool->AddVariable("fabs(bjet_charge)<0.5?fabs(bjet_charge):0.5",&bjet_ChargeTool.abs_charge,0.,0.5);
    mChargeTool->AddVariable("(bjet_charge*bmuon_charge<-0.5)?-0.5:(bjet_charge*bmuon_charge>0.6)?0.6:bjet_charge*bmuon_charge",&bmuon_ChargeTool.bjet_charge_dot_bmuon_charge,-0.5,0.6);
    

  }
  else if(DataEra=="2017"){
    mChargeTool->AddVariable("bmuon_dR_l_j<0.04?0.04:bmuon_dR_l_j",&bmuon_ChargeTool.dR_l_j,0.04);
    mChargeTool->AddVariable("(bmuon_nsip3d<3.)?3.:(bmuon_nsip3d>10.)?10.:bmuon_nsip3d",&bmuon_ChargeTool.nsip3d,3.,10.);
    mChargeTool->AddVariable("(bmuon_P_jetrest<1.5)?1.5:(bmuon_P_jetrest>5.)?5.:bmuon_P_jetrest",&bmuon_ChargeTool.P_jetrest,1.5,5.);
    mChargeTool->AddVariable("bmuon_palongjet<30.?bmuon_palongjet:30.",&bmuon_ChargeTool.palongjet,0.,30.);
    mChargeTool->AddVariable("(bmuon_ptwrtbjet<1.5)?1.5:(bmuon_ptwrtbjet>3.5)?3.5:bmuon_ptwrtbjet",&bmuon_ChargeTool.ptwrtjet,1.5,3.5);
    mChargeTool->AddVariable("bmuon_reliso<6.?bmuon_reliso:6.",&bmuon_ChargeTool.reliso,0.,6.);
    mChargeTool->AddVariable("(bjet_ChargedHadronEnergyFraction<0.35)?0.35:(bjet_ChargedHadronEnergyFraction>0.9)?0.9:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.35,0.9);
    mChargeTool->AddVariable("(bjet_MuonEnergyFraction<0.15)?0.15:(bjet_MuonEnergyFraction>0.45)?0.45:bjet_MuonEnergyFraction",&bjet_ChargeTool.MuonEnergyFraction,0.15,0.45);
    mChargeTool->AddVariable("bjet_NeutralEmEnergyFraction<0.5?bjet_NeutralEmEnergyFraction:0.5",&bjet_ChargeTool.NeutralEmEnergyFraction,0.,0.5);
    mChargeTool->AddVariable("(bjet_NeutralHadronEnergyFraction<0.1)?0.1:(bjet_NeutralHadronEnergyFraction>0.4)?0.4:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.1,0.4);
    mChargeTool->AddVariable("bjet_NeutralMultiplicity<30?bjet_NeutralMultiplicity:30",&bjet_ChargeTool.NeutralMultiplicity,0.,30.);
    mChargeTool->AddVariable("fabs(bjet_charge)<0.5?fabs(bjet_charge):0.5",&bjet_ChargeTool.abs_charge,0.,0.5);
    mChargeTool->AddVariable("(bjet_charge*bmuon_charge<-0.2)?-0.2:(bjet_charge*bmuon_charge>0.5)?0.5:bjet_charge*bmuon_charge",&bmuon_ChargeTool.bjet_charge_dot_bmuon_charge,-0.2,0.5);

  }
  else if(DataEra=="2018"){
    mChargeTool->AddVariable("bmuon_dR_l_j<0.04?0.04:bmuon_dR_l_j",&bmuon_ChargeTool.dR_l_j,0.04);
    mChargeTool->AddVariable("(bmuon_nsip3d<1.)?1.:(bmuon_nsip3d>10.)?10.:bmuon_nsip3d",&bmuon_ChargeTool.nsip3d,1.,10.);
    mChargeTool->AddVariable("(bmuon_P_jetrest<1.5)?1.5:(bmuon_P_jetrest>4.)?4.:bmuon_P_jetrest",&bmuon_ChargeTool.P_jetrest,1.5,4.);
    mChargeTool->AddVariable("bmuon_palongjet<30.?bmuon_palongjet:30.",&bmuon_ChargeTool.palongjet,0.,30.);
    mChargeTool->AddVariable("bmuon_ptwrtbjet<1.?1:bmuon_ptwrtbjet>3.5?3.5:bmuon_ptwrtbjet",&bmuon_ChargeTool.ptwrtjet,1.,3.5);
    mChargeTool->AddVariable("bmuon_reliso<4.?bmuon_reliso:4.",&bmuon_ChargeTool.reliso,0.,4.);
    mChargeTool->AddVariable("(bjet_ChargedHadronEnergyFraction<0.35)?0.35:(bjet_ChargedHadronEnergyFraction>0.9)?0.9:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.35,0.9);
    mChargeTool->AddVariable("(bjet_MuonEnergyFraction<0.15)?0.15:(bjet_MuonEnergyFraction>0.45)?0.45:bjet_MuonEnergyFraction",&bjet_ChargeTool.MuonEnergyFraction,0.15,0.45);
    mChargeTool->AddVariable("bjet_NeutralEmEnergyFraction<0.1?0.1:bjet_NeutralEmEnergyFraction>0.5?0.5:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.1,0.5);
    mChargeTool->AddVariable("(bjet_NeutralHadronEnergyFraction<0.1)?0.1:(bjet_NeutralHadronEnergyFraction>0.5)?0.5:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.1,0.5);
    mChargeTool->AddVariable("(bjet_NeutralMultiplicity<30)?bjet_NeutralMultiplicity:30",&bjet_ChargeTool.NeutralMultiplicity,0.,30.);
    mChargeTool->AddVariable("fabs(bjet_charge)<0.5?fabs(bjet_charge):0.5",&bjet_ChargeTool.abs_charge,0.,0.5);
    mChargeTool->AddVariable("bjet_charge*bmuon_charge<-0.6?-0.6:bjet_charge*bmuon_charge>0.5?0.5:bjet_charge*bmuon_charge",&bmuon_ChargeTool.bjet_charge_dot_bmuon_charge,-0.6,0.5);

  }
  mChargeTool->SetupTMVA();


  //---Electron---//
  if(DataEra=="2016preVFP"){
    eChargeTool->AddVariable("(belectron_dR_l_j<0.15)?0.15:belectron_dR_l_j",&belectron_ChargeTool.dR_l_j,0.15);
    eChargeTool->AddVariable("(belectron_P_jetrest<0.8)?0.8:(belectron_P_jetrest>1.5)?1.5:belectron_P_jetrest",&belectron_ChargeTool.P_jetrest,0.8,1.5);
    eChargeTool->AddVariable("(belectron_ptwrtbjet<0.5)?0.5:(belectron_ptwrtbjet>1.5)?1.5:belectron_ptwrtbjet",&belectron_ChargeTool.ptwrtjet,0.5,1.5);
    eChargeTool->AddVariable("bjet_ChargedEmEnergyFraction<0.2?bjet_ChargedEmEnergyFraction:0.2",&bjet_ChargeTool.ChargedEmEnergyFraction,0.,0.2);
    eChargeTool->AddVariable("(bjet_ChargedHadronEnergyFraction<0.2)?0.2:(bjet_ChargedHadronEnergyFraction>0.9)?0.9:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.2,0.9);
    eChargeTool->AddVariable("(bjet_NeutralEmEnergyFraction<0.4)?0.4:(bjet_NeutralEmEnergyFraction>0.7)?0.7:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.4,0.7);
    eChargeTool->AddVariable("(fabs(bjet_charge)<0.7)?fabs(bjet_charge):0.7",&bjet_ChargeTool.abs_charge,0.,0.7);
    eChargeTool->AddVariable("(bjet_charge*belectron_charge<-0.3)?-0.3:(bjet_charge*belectron_charge>0.3)?0.3:bjet_charge*belectron_charge",&belectron_ChargeTool.bjet_charge_dot_belectron_charge,-0.3,0.3);
  }
  else if(DataEra=="2016postVFP"){
    eChargeTool->AddVariable("belectron_dR_l_j<0.15?0.15:belectron_dR_l_j",&belectron_ChargeTool.dR_l_j,0.15);
    eChargeTool->AddVariable("(belectron_P_jetrest<1.)?1.:(belectron_P_jetrest>2.)?2.:belectron_P_jetrest",&belectron_ChargeTool.P_jetrest,1.,2.);
    eChargeTool->AddVariable("(belectron_ptwrtbjet<0.5)?0.5:(belectron_ptwrtbjet>3.)?3.:belectron_ptwrtbjet",&belectron_ChargeTool.ptwrtjet,0.5,3.);
    eChargeTool->AddVariable("bjet_ChargedEmEnergyFraction<0.2?bjet_ChargedEmEnergyFraction:0.2",&bjet_ChargeTool.ChargedEmEnergyFraction,0.,0.2);
    eChargeTool->AddVariable("(bjet_ChargedHadronEnergyFraction<0.5)?0.5:(bjet_ChargedHadronEnergyFraction>0.9)?0.9:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.5,0.9);
    eChargeTool->AddVariable("(bjet_NeutralEmEnergyFraction<0.25)?0.25:(bjet_NeutralEmEnergyFraction>0.7)?0.7:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.25,0.7);
    eChargeTool->AddVariable("fabs(bjet_charge)<0.3?fabs(bjet_charge):0.3",&bjet_ChargeTool.abs_charge,0.,0.3);
    eChargeTool->AddVariable("(bjet_charge*belectron_charge<-0.3)?-0.3:(bjet_charge*belectron_charge>0.3)?0.3:bjet_charge*belectron_charge",&belectron_ChargeTool.bjet_charge_dot_belectron_charge,-0.3,0.3);

  }
  else if(DataEra=="2017"){
    eChargeTool->AddVariable("belectron_dR_l_j<0.1?0.1:belectron_dR_l_j",&belectron_ChargeTool.dR_l_j,0.1);
    eChargeTool->AddVariable("belectron_nsip3d<6.?belectron_nsip3d:6.",&belectron_ChargeTool.nsip3d,0.,6.);
    eChargeTool->AddVariable("(belectron_P_jetrest<2.)?belectron_P_jetrest:2.",&belectron_ChargeTool.P_jetrest,0.,2.);
    eChargeTool->AddVariable("(belectron_ptwrtbjet<3.)?belectron_ptwrtbjet:3.",&belectron_ChargeTool.ptwrtjet,0.,3.);
    eChargeTool->AddVariable("bjet_ChargedEmEnergyFraction<0.2?bjet_ChargedEmEnergyFraction:0.2",&bjet_ChargeTool.ChargedEmEnergyFraction,0.,0.2);
    eChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.6?0.6:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.6);
    eChargeTool->AddVariable("(bjet_NeutralEmEnergyFraction<0.2)?0.2:(bjet_NeutralEmEnergyFraction>0.65)?0.65:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.2,0.65);
    eChargeTool->AddVariable("fabs(bjet_charge)<0.35?fabs(bjet_charge):0.35",&bjet_ChargeTool.abs_charge,0.,0.35);
    eChargeTool->AddVariable("(bjet_charge*belectron_charge<-0.4)?-0.4:(bjet_charge*belectron_charge>0.3)?0.3:bjet_charge*belectron_charge",&belectron_ChargeTool.bjet_charge_dot_belectron_charge,-0.4,0.3);

  }
  else if(DataEra=="2018"){
    eChargeTool->AddVariable("belectron_dR_l_j<0.15?0.15:belectron_dR_l_j",&belectron_ChargeTool.dR_l_j,0.15);
    eChargeTool->AddVariable("belectron_nsip3d<6.?belectron_nsip3d:6.",&belectron_ChargeTool.nsip3d,0.,6.);
    eChargeTool->AddVariable("belectron_P_jetrest<4.?belectron_P_jetrest:4.",&belectron_ChargeTool.P_jetrest,0.,4.);
    eChargeTool->AddVariable("(belectron_ptwrtbjet<3.)?3.:belectron_ptwrtbjet>5.?5.:belectron_ptwrtbjet",&belectron_ChargeTool.ptwrtjet,3.,5.);
    eChargeTool->AddVariable("bjet_ChargedEmEnergyFraction<0.15?bjet_ChargedEmEnergyFraction:0.15",&bjet_ChargeTool.ChargedEmEnergyFraction,0.,0.15);
    eChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.6?0.6:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.6);
    eChargeTool->AddVariable("(bjet_NeutralEmEnergyFraction<0.35)?0.35:(bjet_NeutralEmEnergyFraction>0.75)?0.75:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.35,0.75);
    eChargeTool->AddVariable("fabs(bjet_charge)<0.3?fabs(bjet_charge):0.3",&bjet_ChargeTool.abs_charge,0.,0.3);
    eChargeTool->AddVariable("(bjet_charge*belectron_charge<-0.2)?-0.2:(bjet_charge*belectron_charge>0.4)?0.4:bjet_charge*belectron_charge",&belectron_ChargeTool.bjet_charge_dot_belectron_charge,-0.2,0.4);
  }
  eChargeTool->SetupTMVA();
  //---Jet----//
  if(DataEra=="2016preVFP"){
    jChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction>0.15?bjet_ChargedHadronEnergyFraction:0.15",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.15);
    jChargeTool->AddVariable("(bjet_ChargedMultiplicity<30)?bjet_ChargedMultiplicity:30",&bjet_ChargeTool.ChargedMultiplicity,0.,30.);
    jChargeTool->AddVariable("(bjet_NeutralEmEnergyFraction<0.15)?0.15:(bjet_NeutralEmEnergyFraction>0.7)?0.7:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.15,0.7);
    jChargeTool->AddVariable("(bjet_NeutralHadronEnergyFraction<0.1)?0.1:(bjet_NeutralHadronEnergyFraction>0.4)?0.4:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.1,0.4);
    jChargeTool->AddVariable("(bjet_NeutralMultiplicity<30)?bjet_NeutralMultiplicity:30",&bjet_ChargeTool.NeutralMultiplicity,0.,30.);
    jChargeTool->AddVariable("(fabs(bjet_charge)<0.9)?fabs(bjet_charge):0.9",&bjet_ChargeTool.abs_charge,0.,0.9);
  }
  else if(DataEra=="2016postVFP"){
    jChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.15?0.15:(bjet_ChargedHadronEnergyFraction>0.7)?0.7:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.15,0.7);
    jChargeTool->AddVariable("(log(bjet_MuonEnergyFraction)<-3.5)?-3.5:(log(bjet_MuonEnergyFraction)>-1.5)?-1.5:log(bjet_MuonEnergyFraction)",&bjet_ChargeTool.log_MuonEnergyFraction,-3.5,-1.5);
    jChargeTool->AddVariable("bjet_NeutralEmEnergyFraction<0.7?bjet_NeutralEmEnergyFraction:0.7",&bjet_ChargeTool.NeutralEmEnergyFraction,0.,0.7);
    jChargeTool->AddVariable("(log(bjet_NeutralHadronEnergyFraction)<-4.5)?-4.5:(log(bjet_NeutralHadronEnergyFraction)>-0.5)?-0.5:log(bjet_NeutralHadronEnergyFraction)",&bjet_ChargeTool.log_NeutralHadronEnergyFraction,-4.5,-0.5);
    jChargeTool->AddVariable("(bjet_NeutralMultiplicity<5)?5:(bjet_NeutralMultiplicity>32)?32:bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity,5.,32.);
    jChargeTool->AddVariable("fabs(bjet_charge)<0.7?fabs(bjet_charge):0.7",&bjet_ChargeTool.abs_charge,0.,0.7);

  }
  else if(DataEra=="2017"){
    jChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction<0.3?0.3:bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.3);
    jChargeTool->AddVariable("bjet_NeutralEmEnergyFraction<0.05?0.05:bjet_NeutralEmEnergyFraction>0.7?0.7:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.05,0.7);
    jChargeTool->AddVariable("(log(bjet_NeutralHadronEnergyFraction)<-4)?-4:(log(bjet_NeutralHadronEnergyFraction)>-1)?-1:log(bjet_NeutralHadronEnergyFraction)",&bjet_ChargeTool.log_NeutralHadronEnergyFraction,-4.,-1.);
    jChargeTool->AddVariable("bjet_NeutralMultiplicity<30?bjet_NeutralMultiplicity:30",&bjet_ChargeTool.NeutralMultiplicity,0.,30.);
    jChargeTool->AddVariable("fabs(bjet_charge)<0.4?fabs(bjet_charge):0.4",&bjet_ChargeTool.abs_charge,0.,0.4);
  }
  else if(DataEra=="2018"){
    jChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction>0.2?bjet_ChargedHadronEnergyFraction:0.2",&bjet_ChargeTool.ChargedHadronEnergyFraction,0.,0.2);
    jChargeTool->AddVariable("bjet_NeutralEmEnergyFraction<0.05?0.05:bjet_NeutralEmEnergyFraction>0.75?0.75:bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction,0.05,0.75);
    jChargeTool->AddVariable("(bjet_NeutralHadronEnergyFraction<0.1)?0.1:(bjet_NeutralHadronEnergyFraction>0.6)?0.6:bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction,0.1,0.6);
    jChargeTool->AddVariable("bjet_NeutralMultiplicity<30?bjet_NeutralMultiplicity:30",&bjet_ChargeTool.NeutralMultiplicity,0.,30.);
    jChargeTool->AddVariable("fabs(bjet_charge)<0.4?fabs(bjet_charge):0.4",&bjet_ChargeTool.abs_charge,0.,0.4);
  }

  jChargeTool->SetupTMVA();


  if (applycut){

    map<TString,float> map_muon_mincut;
    map_muon_mincut["2016preVFP"]=0.0;  map_muon_mincut["2016postVFP"]=-0.05;  map_muon_mincut["2017"]=0.0; map_muon_mincut["2018"]=0.0;
    map<TString,float> map_muon_maxcut;
    map_muon_maxcut["2016preVFP"]=-0.6;  map_muon_maxcut["2016postVFP"]=-0.55;  map_muon_maxcut["2017"]=-0.55; map_muon_maxcut["2018"]=-0.55;

    
    map<TString,float> map_electron_mincut;
    map_electron_mincut["2016preVFP"]=0.05;  map_electron_mincut["2016postVFP"]=0.05;  map_electron_mincut["2017"]=0.05; map_electron_mincut["2018"]=0.05;
    map<TString,float> map_electron_maxcut;
    map_electron_maxcut["2016preVFP"]=-0.4;  map_electron_maxcut["2016postVFP"]=-0.4;  map_electron_maxcut["2017"]=-0.45; map_electron_maxcut["2018"]=-0.45;
    map<TString,float> map_jet_mincut;
    map_jet_mincut["2016preVFP"]=-0.06;  map_jet_mincut["2016postVFP"]=-0.04;  map_jet_mincut["2017"]=-0.08; map_jet_mincut["2018"]=-0.06;
    map<TString,float> map_jet_maxcut;//Turn off this region
    map_jet_maxcut["2016preVFP"]=-1;  map_jet_maxcut["2016postVFP"]=-1;  map_jet_maxcut["2017"]=-1; map_jet_maxcut["2018"]=-1;
    
    
    cout << "[JHAnalyzerBase::SetChargeScoreCut_2409_2] " << endl;
    cout << "Muon" << endl;
    mChargeTool->SetMinCut(map_muon_mincut[DataEra]);
    mChargeTool->SetMaxCut(map_muon_maxcut[DataEra]);
    cout << "Electron" << endl;
    eChargeTool->SetMinCut(map_electron_mincut[DataEra]);
    eChargeTool->SetMaxCut(map_electron_maxcut[DataEra]);
    cout << "Jet" << endl;
    jChargeTool->SetMinCut(map_jet_mincut[DataEra]);
    jChargeTool->SetMaxCut(map_jet_maxcut[DataEra]);
    
  }
  for(int i = 0 ; i < 10 ; i++){
    cout << "i=" << i << endl;
    mChargeTool->SetScore();
    cout << "mChargeTool->GetScore()=" << mChargeTool->GetScore() << endl;    
    eChargeTool->SetScore();
    cout << "eChargeTool->GetScore()=" << eChargeTool->GetScore() << endl;
    jChargeTool->SetScore();
    cout << "jChargeTool->GetScore()=" << jChargeTool->GetScore() << endl;
  }
}




void JHAnalyzerBase::LoadChargeScoreTool_2512_4(bool applycut){
  IsChargeScoreToolOn=1;
  TString muon_version="2512.4";
  TString electron_version="2512.4";
  TString jet_version="2512.4";
  mChargeTool=new ChargeScoreTool("muon",muon_version,DataEra);
  eChargeTool=new ChargeScoreTool("electron",electron_version,DataEra);
  jChargeTool=new ChargeScoreTool("jet",jet_version,DataEra);
  //Link variables
  //void TMVATool::AddVariable(TString _formula, float *_this_var_address)

  ///---Muon---//
  
  mChargeTool->AddVariable("bmuon_nsip3d<10.?bmuon_nsip3d:10.",&bmuon_ChargeTool.nsip3d);
  mChargeTool->AddVariable("bmuon_reliso<10.?bmuon_reliso:10.",&bmuon_ChargeTool.reliso);
  mChargeTool->AddVariable("bmuon_dR_l_j",&bmuon_ChargeTool.dR_l_j);
  mChargeTool->AddVariable("bmuon_ptwrtbjet<10.?bmuon_ptwrtbjet:10.",&bmuon_ChargeTool.ptwrtjet);
  mChargeTool->AddVariable("bmuon_P_jetrest<10.?bmuon_P_jetrest:10.",&bmuon_ChargeTool.P_jetrest);  
  mChargeTool->AddVariable("bmuon_palongjet<50.?bmuon_palongjet:50.",&bmuon_ChargeTool.palongjet);  
  mChargeTool->AddVariable("bjet_charge*bmuon_charge<0.6?bjet_charge*bmuon_charge:0.6",&bmuon_ChargeTool.bjet_charge_dot_bmuon_charge);


  mChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction>0.2?bjet_ChargedHadronEnergyFraction:0.2",&bjet_ChargeTool.ChargedHadronEnergyFraction);
  mChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction>0.06?bjet_NeutralHadronEnergyFraction:0.06",&bjet_ChargeTool.NeutralHadronEnergyFraction);
  mChargeTool->AddVariable("bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction);
  mChargeTool->AddVariable("bjet_MuonEnergyFraction>0.08?bjet_MuonEnergyFraction:0.08",&bjet_ChargeTool.MuonEnergyFraction);
  mChargeTool->AddVariable("(bjet_ChargedMultiplicity>19)?20:(bjet_ChargedMultiplicity<11)?11:bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity);
  mChargeTool->AddVariable("bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity);
  mChargeTool->AddVariable("fabs(bjet_charge)<0.6?fabs(bjet_charge):0.6",&bjet_ChargeTool.abs_charge);


  mChargeTool->SetupTMVA();


  //---Electron---//

  eChargeTool->AddVariable("belectron_nsip3d<10.?belectron_nsip3d:10.",&belectron_ChargeTool.nsip3d);
  eChargeTool->AddVariable("(belectron_reliso<1.)?1:(belectron_reliso>10)?10:belectron_reliso",&belectron_ChargeTool.reliso);
  eChargeTool->AddVariable("belectron_ptwrtbjet<10.?belectron_ptwrtbjet:10.",&belectron_ChargeTool.ptwrtjet);
  eChargeTool->AddVariable("belectron_P_jetrest<10.?belectron_P_jetrest:10.",&belectron_ChargeTool.P_jetrest);
  eChargeTool->AddVariable("bjet_charge*belectron_charge<0.4?bjet_charge*belectron_charge:0.4",&belectron_ChargeTool.bjet_charge_dot_belectron_charge);

  eChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction>0.35?bjet_ChargedHadronEnergyFraction:0.35",&bjet_ChargeTool.ChargedHadronEnergyFraction);
  eChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction>0.1?bjet_NeutralHadronEnergyFraction:0.1",&bjet_ChargeTool.NeutralHadronEnergyFraction);
  eChargeTool->AddVariable("bjet_NeutralEmEnergyFraction>0.1?bjet_NeutralEmEnergyFraction:0.1",&bjet_ChargeTool.NeutralEmEnergyFraction);
  eChargeTool->AddVariable("bjet_ChargedEmEnergyFraction<0.3?bjet_ChargedEmEnergyFraction:0.3",&bjet_ChargeTool.ChargedEmEnergyFraction);
  eChargeTool->AddVariable("(bjet_ChargedMultiplicity>20)?21:(bjet_ChargedMultiplicity<15)?14:bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity);
  eChargeTool->AddVariable("bjet_NeutralMultiplicity>9?bjet_NeutralMultiplicity:9",&bjet_ChargeTool.NeutralMultiplicity);  
  eChargeTool->AddVariable("fabs(bjet_charge)<0.5?fabs(bjet_charge):0.5",&bjet_ChargeTool.abs_charge);
  eChargeTool->SetupTMVA();

  //---Jet----//

  jChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction);
  jChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction);
  jChargeTool->AddVariable("bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction);
  jChargeTool->AddVariable("(bjet_ChargedMultiplicity>19)?20:(bjet_ChargedMultiplicity<12)?11:bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity);
  jChargeTool->AddVariable("bjet_NeutralMultiplicity>4?bjet_NeutralMultiplicity:4",&bjet_ChargeTool.NeutralMultiplicity);
  jChargeTool->AddVariable("fabs(bjet_charge)<0.5?fabs(bjet_charge):0.5",&bjet_ChargeTool.abs_charge);
			   

  jChargeTool->SetupTMVA();


  if (applycut)SetChargeScoreCut(muon_version);
  for(int i = 0 ; i < 10 ; i++){
    cout << "i=" << i << endl;
    mChargeTool->SetScore();
    cout << "mChargeTool->GetScore()=" << mChargeTool->GetScore() << endl;    
    eChargeTool->SetScore();
    cout << "eChargeTool->GetScore()=" << eChargeTool->GetScore() << endl;
    jChargeTool->SetScore();
    cout << "jChargeTool->GetScore()=" << jChargeTool->GetScore() << endl;
  }
}






void JHAnalyzerBase::LoadChargeScoreTool_2512_3(bool applycut){
  IsChargeScoreToolOn=1;
  TString muon_version="2512.3";
  TString electron_version="2512.3";
  TString jet_version="2512.3";
  mChargeTool=new ChargeScoreTool("muon",muon_version,DataEra);
  eChargeTool=new ChargeScoreTool("electron",electron_version,DataEra);
  jChargeTool=new ChargeScoreTool("jet",jet_version,DataEra);
  //Link variables
  //void TMVATool::AddVariable(TString _formula, float *_this_var_address)

  ///---Muon---//
  
  mChargeTool->AddVariable("bmuon_nsip3d<10.?bmuon_nsip3d:10.",&bmuon_ChargeTool.nsip3d);
  mChargeTool->AddVariable("bmuon_reliso<10.?bmuon_reliso:10.",&bmuon_ChargeTool.reliso);
  mChargeTool->AddVariable("bmuon_dR_l_j",&bmuon_ChargeTool.dR_l_j);
  mChargeTool->AddVariable("bmuon_ptwrtbjet<10.?bmuon_ptwrtbjet:10.",&bmuon_ChargeTool.ptwrtjet);
  mChargeTool->AddVariable("bmuon_P_jetrest<10.?bmuon_P_jetrest:10.",&bmuon_ChargeTool.P_jetrest);  
  mChargeTool->AddVariable("bmuon_palongjet<50.?bmuon_palongjet:50.",&bmuon_ChargeTool.palongjet);  
  mChargeTool->AddVariable("bjet_charge*bmuon_charge",&bmuon_ChargeTool.bjet_charge_dot_bmuon_charge);


  mChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction>0.2?bjet_ChargedHadronEnergyFraction:0.2",&bjet_ChargeTool.ChargedHadronEnergyFraction);
  mChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction>0.06?bjet_NeutralHadronEnergyFraction:0.06",&bjet_ChargeTool.NeutralHadronEnergyFraction);
  mChargeTool->AddVariable("bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction);
  mChargeTool->AddVariable("bjet_MuonEnergyFraction>0.08?bjet_MuonEnergyFraction:0.08",&bjet_ChargeTool.MuonEnergyFraction);
  mChargeTool->AddVariable("(bjet_ChargedMultiplicity>19)?20:(bjet_ChargedMultiplicity<11)?11:bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity);
  mChargeTool->AddVariable("bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity);
  mChargeTool->AddVariable("fabs(bjet_charge)",&bjet_ChargeTool.abs_charge);


  mChargeTool->SetupTMVA();


  //---Electron---//

  eChargeTool->AddVariable("belectron_nsip3d<10.?belectron_nsip3d:10.",&belectron_ChargeTool.nsip3d);
  eChargeTool->AddVariable("(belectron_reliso<1.)?1:(belectron_reliso>10)?10:belectron_reliso",&belectron_ChargeTool.reliso);
  eChargeTool->AddVariable("belectron_ptwrtbjet<10.?belectron_ptwrtbjet:10.",&belectron_ChargeTool.ptwrtjet);
  eChargeTool->AddVariable("belectron_P_jetrest<10.?belectron_P_jetrest:10.",&belectron_ChargeTool.P_jetrest);
  eChargeTool->AddVariable("bjet_charge*belectron_charge",&belectron_ChargeTool.bjet_charge_dot_belectron_charge);

  eChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction>0.35?bjet_ChargedHadronEnergyFraction:0.35",&bjet_ChargeTool.ChargedHadronEnergyFraction);
  eChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction>0.1?bjet_NeutralHadronEnergyFraction:0.1",&bjet_ChargeTool.NeutralHadronEnergyFraction);
  eChargeTool->AddVariable("bjet_NeutralEmEnergyFraction>0.1?bjet_NeutralEmEnergyFraction:0.1",&bjet_ChargeTool.NeutralEmEnergyFraction);
  eChargeTool->AddVariable("bjet_ChargedEmEnergyFraction<0.3?bjet_ChargedEmEnergyFraction:0.3",&bjet_ChargeTool.ChargedEmEnergyFraction);
  eChargeTool->AddVariable("(bjet_ChargedMultiplicity>20)?21:(bjet_ChargedMultiplicity<15)?14:bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity);
  eChargeTool->AddVariable("bjet_NeutralMultiplicity>9?bjet_NeutralMultiplicity:9",&bjet_ChargeTool.NeutralMultiplicity);  
  eChargeTool->AddVariable("fabs(bjet_charge)",&bjet_ChargeTool.abs_charge);
  eChargeTool->SetupTMVA();

  //---Jet----//

  jChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction);
  jChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction);
  jChargeTool->AddVariable("bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction);
  jChargeTool->AddVariable("(bjet_ChargedMultiplicity>19)?20:(bjet_ChargedMultiplicity<12)?11:bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity);
  jChargeTool->AddVariable("bjet_NeutralMultiplicity>4?bjet_NeutralMultiplicity:4",&bjet_ChargeTool.NeutralMultiplicity);
  jChargeTool->AddVariable("fabs(bjet_charge)",&bjet_ChargeTool.abs_charge);
			   

  jChargeTool->SetupTMVA();


  if (applycut)SetChargeScoreCut(muon_version);
  for(int i = 0 ; i < 10 ; i++){
    cout << "i=" << i << endl;
    mChargeTool->SetScore();
    cout << "mChargeTool->GetScore()=" << mChargeTool->GetScore() << endl;    
    eChargeTool->SetScore();
    cout << "eChargeTool->GetScore()=" << eChargeTool->GetScore() << endl;
    jChargeTool->SetScore();
    cout << "jChargeTool->GetScore()=" << jChargeTool->GetScore() << endl;
  }
}





void JHAnalyzerBase::LoadChargeScoreTool_2409_2(bool applycut){
  IsChargeScoreToolOn=1;
  TString muon_version="2409.2";
  TString electron_version="2409.2";
  TString jet_version="2409.2";
  mChargeTool=new ChargeScoreTool("muon",muon_version,DataEra);
  eChargeTool=new ChargeScoreTool("electron",electron_version,DataEra);
  jChargeTool=new ChargeScoreTool("jet",jet_version,DataEra);
  //Link variables
  //void TMVATool::AddVariable(TString _formula, float *_this_var_address)
  
  //bmuon_var=["bmuon_nsip3d<10. ? bmuon_nsip3d : 10.","bmuon_reliso","bmuon_ptwrtbjet < 10. ? bmuon_ptwrtbjet : 10.","bmuon_P_jetrest < 10. ? bmuon_P_jetrest : 10.","bmuon_palongjet < 100. ? bmuon_palongjet: 100.", "bmuon_palongjetratio < 1. ? bmuon_palongjetratio : 1." , "bjet_charge*bmuon_charge", ]  
  //bjet_var=["bjet_ChargedHadronEnergyFraction","bjet_NeutralHadronEnergyFraction","bjet_NeutralEmEnergyFraction","bjet_ChargedEmEnergyFraction","bjet_MuonEnergyFraction","bjet_ChargedMultiplicity","bjet_NeutralMultiplicity","fabs(bjet_charge)"]

  ///---Muon---//
  

  mChargeTool->AddVariable("bmuon_nsip3d<10.?bmuon_nsip3d:10.",&bmuon_ChargeTool.nsip3d);
  mChargeTool->AddVariable("bmuon_reliso",&bmuon_ChargeTool.reliso);
  mChargeTool->AddVariable("bmuon_ptwrtbjet<10.?bmuon_ptwrtbjet:10.",&bmuon_ChargeTool.ptwrtjet);
  mChargeTool->AddVariable("bmuon_P_jetrest<10.?bmuon_P_jetrest:10.",&bmuon_ChargeTool.P_jetrest);  
  mChargeTool->AddVariable("bmuon_palongjet<100.?bmuon_palongjet:100.",&bmuon_ChargeTool.palongjet);
  mChargeTool->AddVariable("bmuon_palongjetratio<1.?bmuon_palongjetratio:1.",&bmuon_ChargeTool.palongjetratio);
  mChargeTool->AddVariable("bjet_charge*bmuon_charge",&bmuon_ChargeTool.bjet_charge_dot_bmuon_charge);
  //mChargeTool->AddVariable("bmuon_dR_l_j",&bmuon_ChargeTool.dR_l_j);



  mChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction);
  mChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction);
  mChargeTool->AddVariable("bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction);
  mChargeTool->AddVariable("bjet_ChargedEmEnergyFraction",&bjet_ChargeTool.ChargedEmEnergyFraction);
  mChargeTool->AddVariable("bjet_MuonEnergyFraction",&bjet_ChargeTool.MuonEnergyFraction);
  mChargeTool->AddVariable("fabs(bjet_charge)",&bjet_ChargeTool.abs_charge);
  mChargeTool->AddVariable("bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity);
  mChargeTool->AddVariable("bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity);
  mChargeTool->SetupTMVA();


  //---Electron---//
  //belectron_var=["belectron_nsip3d < 30. ? belectron_nsip3d : 30.","belectron_reliso","belectron_ptwrtbjet < 10. ? belectron_ptwrtbjet : 10.","belectron_P_jetrest < 10. ? belectron_P_jetrest : 10.","belectron_palongjet < 100. ? belectron_palongjet : 100.","belectron_palongjetratio < 1. ? belectron_palongjetratio : 1.","bjet_charge*belectron_charge"]
  //bjet_var=["bjet_ChargedHadronEnergyFraction","bjet_NeutralHadronEnergyFraction","bjet_NeutralEmEnergyFraction","bjet_ChargedEmEnergyFraction","bjet_MuonEnergyFraction","bjet_ChargedMultiplicity","bjet_NeutralMultiplicity","fabs(bjet_charge)"]  
  eChargeTool->AddVariable("belectron_nsip3d<30.?belectron_nsip3d:30.",&belectron_ChargeTool.nsip3d);
  eChargeTool->AddVariable("belectron_reliso",&belectron_ChargeTool.reliso);
eChargeTool->AddVariable("belectron_ptwrtbjet<10.?belectron_ptwrtbjet:10.",&belectron_ChargeTool.ptwrtjet);
 eChargeTool->AddVariable("belectron_P_jetrest<10.?belectron_P_jetrest:10.",&belectron_ChargeTool.P_jetrest);
 eChargeTool->AddVariable("belectron_palongjet<100.?belectron_palongjet:100.",&belectron_ChargeTool.palongjet);
 eChargeTool->AddVariable("belectron_palongjetratio<1.?belectron_palongjetratio:1.",&belectron_ChargeTool.palongjetratio);
 //eChargeTool->AddVariable("belectron_dR_l_j",&belectron_ChargeTool.dR_l_j);
 eChargeTool->AddVariable("bjet_charge*belectron_charge",&belectron_ChargeTool.bjet_charge_dot_belectron_charge);
 
 eChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction);
 eChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction);
 eChargeTool->AddVariable("bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction);
 eChargeTool->AddVariable("bjet_ChargedEmEnergyFraction",&bjet_ChargeTool.ChargedEmEnergyFraction);
 eChargeTool->AddVariable("bjet_MuonEnergyFraction",&bjet_ChargeTool.MuonEnergyFraction);
 eChargeTool->AddVariable("bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity);
 eChargeTool->AddVariable("bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity);
 eChargeTool->AddVariable("fabs(bjet_charge)",&bjet_ChargeTool.abs_charge);
 eChargeTool->SetupTMVA();

  //---Jet----//
  //bjet_var=["bjet_ChargedHadronEnergyFraction","bjet_NeutralHadronEnergyFraction","bjet_NeutralEmEnergyFraction","bjet_ChargedEmEnergyFraction","bjet_MuonEnergyFraction","bjet_ChargedMultiplicity","bjet_NeutralMultiplicity","fabs(bjet_charge)"]  
  jChargeTool->AddVariable("bjet_ChargedHadronEnergyFraction",&bjet_ChargeTool.ChargedHadronEnergyFraction);
  jChargeTool->AddVariable("bjet_NeutralHadronEnergyFraction",&bjet_ChargeTool.NeutralHadronEnergyFraction);
  jChargeTool->AddVariable("bjet_NeutralEmEnergyFraction",&bjet_ChargeTool.NeutralEmEnergyFraction);
  jChargeTool->AddVariable("bjet_ChargedEmEnergyFraction",&bjet_ChargeTool.ChargedEmEnergyFraction);
  jChargeTool->AddVariable("bjet_MuonEnergyFraction",&bjet_ChargeTool.MuonEnergyFraction);
  jChargeTool->AddVariable("bjet_ChargedMultiplicity",&bjet_ChargeTool.ChargedMultiplicity);
  jChargeTool->AddVariable("bjet_NeutralMultiplicity",&bjet_ChargeTool.NeutralMultiplicity);
  jChargeTool->AddVariable("fabs(bjet_charge)",&bjet_ChargeTool.abs_charge);
  jChargeTool->SetupTMVA();


  if (applycut)SetChargeScoreCut(muon_version);
  for(int i = 0 ; i < 10 ; i++){
    cout << "i=" << i << endl;
    mChargeTool->SetScore();
    cout << "mChargeTool->GetScore()=" << mChargeTool->GetScore() << endl;    
    eChargeTool->SetScore();
    cout << "eChargeTool->GetScore()=" << eChargeTool->GetScore() << endl;
    jChargeTool->SetScore();
    cout << "jChargeTool->GetScore()=" << jChargeTool->GetScore() << endl;
  }
}


void JHAnalyzerBase::SetChargeScoreCut(TString version){
  if(version=="2409.2"){
    SetChargeScoreCut_2409_2();
  }
  else{
    cout << "[JHAnalyzerBase::SetChargeScoreCut]No version->" << version << endl;
    exit(1);
  }

}

void JHAnalyzerBase::SetChargeScoreCut_2409_2(){
  map<TString,float> map_muon_mincut;
  map_muon_mincut["2016preVFP"]=0.49;  map_muon_mincut["2016postVFP"]=0.55;  map_muon_mincut["2017"]=0.49; map_muon_mincut["2018"]=0.52;
  map<TString,float> map_muon_maxcut;
  map_muon_maxcut["2016preVFP"]=0.22;  map_muon_maxcut["2016postVFP"]=0.15;  map_muon_maxcut["2017"]=0.19; map_muon_maxcut["2018"]=0.21;
  map<TString,float> map_electron_mincut;
  map_electron_mincut["2016preVFP"]=0.48;  map_electron_mincut["2016postVFP"]=0.51;  map_electron_mincut["2017"]=0.53; map_electron_mincut["2018"]=0.48;
  map<TString,float> map_electron_maxcut;
  map_electron_maxcut["2016preVFP"]=0.22;  map_electron_maxcut["2016postVFP"]=0.25;  map_electron_maxcut["2017"]=0.22; map_electron_maxcut["2018"]=0.22;
  map<TString,float> map_jet_mincut;
  map_jet_mincut["2016preVFP"]=0.5;  map_jet_mincut["2016postVFP"]=0.48;  map_jet_mincut["2017"]=0.38; map_jet_mincut["2018"]=0.45;
  map<TString,float> map_jet_maxcut;//Turn off this region
  map_jet_maxcut["2016preVFP"]=0.0;  map_jet_maxcut["2016postVFP"]=0.0;  map_jet_maxcut["2017"]=0.0; map_jet_maxcut["2018"]=0.0;


  cout << "[JHAnalyzerBase::SetChargeScoreCut_2409_2] " << endl;
  cout << "Muon" << endl;
  mChargeTool->SetMinCut(map_muon_mincut[DataEra]);
  mChargeTool->SetMaxCut(map_muon_maxcut[DataEra]);
  cout << "Electron" << endl;
  eChargeTool->SetMinCut(map_electron_mincut[DataEra]);
  eChargeTool->SetMaxCut(map_electron_maxcut[DataEra]);
  cout << "Jet" << endl;
  jChargeTool->SetMinCut(map_jet_mincut[DataEra]);
  jChargeTool->SetMaxCut(map_jet_maxcut[DataEra]);


}


void JHAnalyzerBase::SetMuonChargeScore(Muon &_this_bmuon, const Jet &_this_bjet){
  //cout << "JHAnalyzerBase::SetMuonChargeScore" << endl;
  bjet_ChargeTool=Get_bjetvar(_this_bjet);
  bmuon_ChargeTool=Get_bmuonvar(_this_bmuon,_this_bjet);//Change input variable value //set inputvariable
  
  mChargeTool->SetScore();
}
double JHAnalyzerBase::GetMuonChargeScore(){
  return mChargeTool->GetScore();
}
double JHAnalyzerBase::GetMuonChargeScoreCoeff(){
  return mChargeTool->GetCoefficient();
}


void JHAnalyzerBase::SetElectronChargeScore(Electron &_this_belectron, const Jet &_this_bjet){
  //cout << "JHAnalyzerBase::SetElectronChargeScore" << endl;
  bjet_ChargeTool=Get_bjetvar(_this_bjet);

  belectron_ChargeTool=Get_belectronvar(_this_belectron,_this_bjet);//Change input variable value //set inputvariable



  
  eChargeTool->SetScore();  
  //cout << "[END]JHAnalyzerBase::SetElectronChargeScore" << endl;
}
double JHAnalyzerBase::GetElectronChargeScore(){
  return eChargeTool->GetScore();
}
double JHAnalyzerBase::GetElectronChargeScoreCoeff(){
  return eChargeTool->GetCoefficient();
}


void JHAnalyzerBase::SetJetChargeScore(const Jet &_this_bjet){
  //cout << "JHAnalyzerBase::SetJetChargeScore" << endl;
  
  //jhchoitemp
  bjet_ChargeTool=Get_bjetvar(_this_bjet);//Change input variable value
  jChargeTool->SetScore();
  //cout << "[END]JHAnalyzerBase::SetJetChargeScore" << endl;
}
double JHAnalyzerBase::GetJetChargeScore(){
  return jChargeTool->GetScore();
}
double JHAnalyzerBase::GetJetChargeScoreCoeff(){
  return jChargeTool->GetCoefficient();
}
/*
tuple<int,double,int,int,double,int> JHAnalyzerBase::GetBJetMuonScore_v2405_4_3(Jet &_bjet, vector<Muon> &_muoncoll){
  ///return max and min of the muon charge score
  //{im_max,bmuon_score_max,bmuon_charge_max,im_min,bmuon_score_min,bmuon_charge_min
  bjet_ChargeTool=Get_bjetvar(_bjet);
  ///----Run Muon----//
  double bmuon_score_max=-999.;
  int bmuon_charge_max=0;

  double bmuon_score_min=999.;
  int bmuon_charge_min=0;
  int im=-1, im_min=-1,im_max=-1;

  for(auto& muon : _muoncoll){
    im+=1;
    if(muon.Pt() < 5.) continue;
    if(muon.DeltaR(_bjet) > 0.4) continue;
    if(muon.RelIso() > 10.) continue;
    if(muon.Chi2()>10) continue;
    if(muon.TrackerLayers()<1) continue;
    if(muon.MatchedStations() <1) continue;


    SetMuonChargeScore(muon,_bjet);
    double this_muonscore=GetMuonChargeScore();
    if(this_muonscore>bmuon_charge_max){
      //BestMuon_max=&muon;
      bmuon_score_max=this_muonscore;
      bmuon_charge_max=muon.Charge();
      im_max=im;
    }
    if(this_muonscore < bmuon_score_min ){

      bmuon_score_min=this_muonscore;
      bmuon_charge_min=muon.Charge();
      im_min=im;
    }


  }//[end muon for loop]
  return {im_max,bmuon_score_max,bmuon_charge_max,im_min,bmuon_score_min,bmuon_charge_min};
}

*/

vector<int> JHAnalyzerBase::GetMuonIdxInBJet(Jet &_bjet, vector<Muon> &_muoncoll){
  vector<int> ret;
  int im=-1;
  for(auto& muon : _muoncoll){
    im+=1;
    if(muon.Pt() < 5.) continue;
    if(muon.DeltaR(_bjet) > 0.4) continue;
    if(muon.RelIso() > 10.) continue;
    if(muon.Chi2()>10) continue;
    if(muon.TrackerLayers()<1) continue;
    if(muon.MatchedStations() <1) continue;
    ret.push_back(im);
  }
  return ret;
}

tuple<int,double,int,int,double,int> JHAnalyzerBase::GetBJetMuonScore_v2409_2(Jet &_bjet, vector<Muon> &_muoncoll){
  ///return max and min of the muon charge score
  //{im_max,bmuon_score_max,bmuon_charge_max,im_min,bmuon_score_min,bmuon_charge_min
  ///----Run Muon----//
  bjet_ChargeTool=Get_bjetvar(_bjet);

  double bmuon_score_max=-999.;
  int bmuon_charge_max=0;

  double bmuon_score_min=999.;
  int bmuon_charge_min=0;
  int im=-1, im_min=-1,im_max=-1;

  for(auto& muon : _muoncoll){
    im+=1;
    if(muon.Pt() < 5.) continue;
    if(muon.DeltaR(_bjet) > 0.4) continue;
    if(muon.RelIso() > 10.) continue;
    if(muon.Chi2()>10) continue;
    if(muon.TrackerLayers()<1) continue;
    if(muon.MatchedStations() <1) continue;


    SetMuonChargeScore(muon,_bjet);
    double this_muonscore=GetMuonChargeScore();
    if(this_muonscore>bmuon_charge_max){
      //BestMuon_max=&muon;
      bmuon_score_max=this_muonscore;
      bmuon_charge_max=muon.Charge();
      im_max=im;
    }
    if(this_muonscore < bmuon_score_min ){

      bmuon_score_min=this_muonscore;
      bmuon_charge_min=muon.Charge();
      im_min=im;
    }


  }//[end muon for loop]
  return {im_max,bmuon_score_max,bmuon_charge_max,im_min,bmuon_score_min,bmuon_charge_min};
}


/*
tuple<int,double,int,int,double,int> JHAnalyzerBase::GetBJetElectronScore_v2405_4_3(Jet &_bjet, vector<Electron> &_electroncoll){
  ///return max and min of the electron charge score
  //{ie_max,belectron_score_max,belectron_charge_max,ie_min,belectron_score_min,belectron_charge_min
  //----RunElectron
  bjet_ChargeTool=Get_bjetvar(_bjet);

  double belectron_score_max=-999.;
  double belectron_charge_max=0;

  double belectron_score_min=999.;
  double belectron_charge_min=0;

  int ie=-1,ie_min=-1,ie_max=-1;

  for(auto& electron : _electroncoll){
    ie+=1;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(electron.Pt() < 5.) continue;
    if(electron.DeltaR(_bjet) > 0.4) continue;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    if(electron.RelIso() > 10.) continue;
    if(electron.NMissingHits() != 0) continue;


    SetElectronChargeScore(electron,_bjet);
    double this_electronscore=GetElectronChargeScore();
    if(this_electronscore>belectron_score_max){
      belectron_score_max=this_electronscore;
      belectron_charge_max=electron.Charge();
      ie_max=ie;
    }
    if(this_electronscore<belectron_score_min){
      belectron_score_min=this_electronscore;
      belectron_charge_min=electron.Charge();
      ie_min=ie;
    }


  }//[end electron for loop]


  return {ie_max,belectron_score_max,belectron_charge_max,ie_min,belectron_score_min,belectron_charge_min};
}
*/

vector<int> JHAnalyzerBase::GetElectronIdxInBJet(Jet &_bjet, vector<Electron> &_electroncoll){
  vector<int> ret;
  int ie=-1;
  for(auto& electron : _electroncoll){
    ie+=1;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(electron.Pt() < 5.) continue;
    if(electron.DeltaR(_bjet) > 0.4) continue;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    if(electron.RelIso() > 10.) continue;
    if(electron.NMissingHits() != 0) continue;
    ret.push_back(ie);
  }
  return ret;
}


tuple<int,double,int,int,double,int> JHAnalyzerBase::GetBJetElectronScore_v2409_2(Jet &_bjet, vector<Electron> &_electroncoll){
  ///return max and min of the electron charge score
  //{ie_max,belectron_score_max,belectron_charge_max,ie_min,belectron_score_min,belectron_charge_min
  //----RunElectron
  bjet_ChargeTool=Get_bjetvar(_bjet);

  double belectron_score_max=-999.;
  double belectron_charge_max=0;

  double belectron_score_min=999.;
  double belectron_charge_min=0;

  int ie=-1,ie_min=-1,ie_max=-1;

  for(auto& electron : _electroncoll){
    ie+=1;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(electron.Pt() < 5.) continue;
    if(electron.DeltaR(_bjet) > 0.4) continue;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    if(electron.RelIso() > 10.) continue;
    if(electron.NMissingHits() != 0) continue;


    SetElectronChargeScore(electron,_bjet);
    double this_electronscore=GetElectronChargeScore();
    if(this_electronscore>belectron_score_max){
      belectron_score_max=this_electronscore;
      belectron_charge_max=electron.Charge();
      ie_max=ie;
    }
    if(this_electronscore<belectron_score_min){
      belectron_score_min=this_electronscore;
      belectron_charge_min=electron.Charge();
      ie_min=ie;
    }


  }//[end electron for loop]


  return {ie_max,belectron_score_max,belectron_charge_max,ie_min,belectron_score_min,belectron_charge_min};
}



//---Get Good SoftMuonJet/SoftElectronJet. JetWithGoodChargeScore. JetWithPoorChargeScore
/*
tuple<int,bool,int,int,double> JHAnalyzerBase::GetBJetCharge_v2405_4_3(Jet &_bjet, vector<Muon> &_muoncoll, vector<Electron> &_electroncoll){
  //pair<charge,IsNotOpposite,leptonidx>
  
  ///----Run Muon----//
  double bmuon_score_max=-999.;
  int bmuon_charge_max=0;

  double bmuon_score_min=999.;
  int bmuon_charge_min=0;
  int im_min=-1,im_max=-1;
  
  tuple<int,double,double,int,double,double> ret_muon=JHAnalyzerBase::GetBJetMuonScore_v2405_4_3(_bjet, _muoncoll);
  //{im_max,bmuon_score_max,bmuon_charge_max,im_min,bmuon_score_min,bmuon_charge_min};
  im_max=std::get<0>(ret_muon);
  bmuon_score_max=std::get<1>(ret_muon);
  bmuon_charge_max=std::get<2>(ret_muon);

  im_min=std::get<3>(ret_muon);
  bmuon_score_min=std::get<4>(ret_muon);
  bmuon_charge_min=std::get<5>(ret_muon);


  //---if a good muon exists, return charge
  if(bmuon_score_max > mChargeTool->mincut){ //mincut == CutToMax
    return {bmuon_charge_max,true,im_max,-1,bmuon_score_max};
  }
  else if(bmuon_score_min < mChargeTool->maxcut){ //maxcut == CutToMin
    return {-bmuon_charge_min,false,im_min,-1,bmuon_score_min};
  }

  ///[END RunMuon]

  //----RunElectron


  double belectron_score_max=-999.;
  double belectron_charge_max=0;

  double belectron_score_min=999.;
  double belectron_charge_min=0;

  int ie_min=-1,ie_max=-1;

  tuple<int,double,double,int,double,double> ret_electron=JHAnalyzerBase::GetBJetElectronScore_v2405_4_3(_bjet, _electroncoll);
  //{ie_max,belectron_score_max,belectron_charge_max,ie_min,belectron_score_min,belectron_charge_min};
  ie_max=std::get<0>(ret_electron);
  belectron_score_max=std::get<1>(ret_electron);
  belectron_charge_max=std::get<2>(ret_electron);

  ie_min=std::get<3>(ret_electron);
  belectron_score_min=std::get<4>(ret_electron);
  belectron_charge_min=std::get<5>(ret_electron);



  if(belectron_score_max > eChargeTool->mincut){ //mincut == CutToMax
    return {2*belectron_charge_max,true,-1,ie_max,belectron_score_max};
  }
  else if(belectron_score_min < eChargeTool->maxcut){ //maxcut == CutToMin
    return {-2*belectron_charge_min,false,-1,ie_min,belectron_score_min};
  }


  ///[END of RunElectron]

  //---now check good jet

  SetJetChargeScore(_bjet);
  double bjet_score=GetJetChargeScore();
  int bjet_charge=_bjet.Charge() > 0 ? +1 : -1;
  if(bjet_score>jChargeTool->mincut){
    return {3*bjet_charge,true,-1,-1,bjet_score}; 
  }
  else if(bjet_score < jChargeTool->maxcut){
    return {-3*bjet_charge,false,-1,-1,bjet_score};
  }
  //Now reminaings are bjets with poor scores.
  return {4*bjet_charge,true,-1,-1,bjet_score};

}

*/



//---Get Good SoftMuonJet/SoftElectronJet. JetWithGoodChargeScore. JetWithPoorChargeScore
tuple<int,bool,int,int,double> JHAnalyzerBase::GetBJetCharge_v2409_2(Jet &_bjet, vector<Muon> &_muoncoll, vector<Electron> &_electroncoll){
  //pair<charge,IsNotOpposite,leptonidx>
  
  ///----Run Muon----//
  double bmuon_score_max=-999.;
  int bmuon_charge_max=0;

  double bmuon_score_min=999.;
  int bmuon_charge_min=0;
  int im_min=-1,im_max=-1;
  
  tuple<int,double,double,int,double,double> ret_muon=JHAnalyzerBase::GetBJetMuonScore_v2409_2(_bjet, _muoncoll);
  //{im_max,bmuon_score_max,bmuon_charge_max,im_min,bmuon_score_min,bmuon_charge_min};
  im_max=std::get<0>(ret_muon);
  bmuon_score_max=std::get<1>(ret_muon);
  bmuon_charge_max=std::get<2>(ret_muon);

  im_min=std::get<3>(ret_muon);
  bmuon_score_min=std::get<4>(ret_muon);
  bmuon_charge_min=std::get<5>(ret_muon);


  //---if a good muon exists, return charge
  if(bmuon_score_max > mChargeTool->mincut){ //mincut == CutToMax
    return {bmuon_charge_max,true,im_max,-1,bmuon_score_max};
  }
  else if(bmuon_score_min < mChargeTool->maxcut){ //maxcut == CutToMin
    return {-bmuon_charge_min,false,im_min,-1,bmuon_score_min};
  }

  ///[END RunMuon]

  //----RunElectron


  double belectron_score_max=-999.;
  double belectron_charge_max=0;

  double belectron_score_min=999.;
  double belectron_charge_min=0;

  int ie_min=-1,ie_max=-1;

  tuple<int,double,double,int,double,double> ret_electron=JHAnalyzerBase::GetBJetElectronScore_v2409_2(_bjet, _electroncoll);
  //{ie_max,belectron_score_max,belectron_charge_max,ie_min,belectron_score_min,belectron_charge_min};
  ie_max=std::get<0>(ret_electron);
  belectron_score_max=std::get<1>(ret_electron);
  belectron_charge_max=std::get<2>(ret_electron);

  ie_min=std::get<3>(ret_electron);
  belectron_score_min=std::get<4>(ret_electron);
  belectron_charge_min=std::get<5>(ret_electron);



  if(belectron_score_max > eChargeTool->mincut){ //mincut == CutToMax
    return {2*belectron_charge_max,true,-1,ie_max,belectron_score_max};
  }
  else if(belectron_score_min < eChargeTool->maxcut){ //maxcut == CutToMin
    return {-2*belectron_charge_min,false,-1,ie_min,belectron_score_min};
  }


  ///[END of RunElectron]

  //---now check good jet

  SetJetChargeScore(_bjet);
  double bjet_score=GetJetChargeScore();
  int bjet_charge=_bjet.Charge() > 0 ? +1 : -1;
  if(bjet_score>jChargeTool->mincut){
    return {3*bjet_charge,true,-1,-1,bjet_score}; 
  }
  else if(bjet_score < jChargeTool->maxcut){
    return {-3*bjet_charge,false,-1,-1,bjet_score};
  }
  //Now reminaings are bjets with poor scores.
  return {4*bjet_charge,true,-1,-1,bjet_score};

}



///----TTSemilepJetAssignment Tool
void JHAnalyzerBase::LoadTTSemilepJetAssignmentTool(TString version){
  IsTTLJJetAssignmentToolOn=1;
  TTLJJetAssignmentTool=new TTSemilepJetAssignmentTool(version,DataEra);

  //Link variables
  //void TMVATool::AddVariable(TString _formula, float *_this_var_address)

  TTLJJetAssignmentTool->AddVariable("met_pt",&inputvar_TTSemilepJetAssignmentTool.met_pt);
  TTLJJetAssignmentTool->AddVariable("met_phi",&inputvar_TTSemilepJetAssignmentTool.met_phi);

  TTLJJetAssignmentTool->AddVariable("lep_pt",&inputvar_TTSemilepJetAssignmentTool.lep_pt);
  TTLJJetAssignmentTool->AddVariable("lep_eta",&inputvar_TTSemilepJetAssignmentTool.lep_eta);
  TTLJJetAssignmentTool->AddVariable("lep_phi",&inputvar_TTSemilepJetAssignmentTool.lep_phi);

  TTLJJetAssignmentTool->AddVariable("blep_pt",&inputvar_TTSemilepJetAssignmentTool.blep_pt);
  TTLJJetAssignmentTool->AddVariable("blep_eta",&inputvar_TTSemilepJetAssignmentTool.blep_eta);
  TTLJJetAssignmentTool->AddVariable("blep_phi",&inputvar_TTSemilepJetAssignmentTool.blep_phi);
  TTLJJetAssignmentTool->AddVariable("blep_E",&inputvar_TTSemilepJetAssignmentTool.blep_E);

  TTLJJetAssignmentTool->AddVariable("bhad_pt",&inputvar_TTSemilepJetAssignmentTool.bhad_pt);
  TTLJJetAssignmentTool->AddVariable("bhad_eta",&inputvar_TTSemilepJetAssignmentTool.bhad_eta);
  TTLJJetAssignmentTool->AddVariable("bhad_phi",&inputvar_TTSemilepJetAssignmentTool.bhad_phi);
  TTLJJetAssignmentTool->AddVariable("bhad_E",&inputvar_TTSemilepJetAssignmentTool.bhad_E);

  TTLJJetAssignmentTool->AddVariable("q1jet_pt",&inputvar_TTSemilepJetAssignmentTool.q1jet_pt);
  TTLJJetAssignmentTool->AddVariable("q1jet_eta",&inputvar_TTSemilepJetAssignmentTool.q1jet_eta);
  TTLJJetAssignmentTool->AddVariable("q1jet_phi",&inputvar_TTSemilepJetAssignmentTool.q1jet_phi);
  TTLJJetAssignmentTool->AddVariable("q1jet_E",&inputvar_TTSemilepJetAssignmentTool.q1jet_E);

  TTLJJetAssignmentTool->AddVariable("q2jet_pt",&inputvar_TTSemilepJetAssignmentTool.q2jet_pt);
  TTLJJetAssignmentTool->AddVariable("q2jet_eta",&inputvar_TTSemilepJetAssignmentTool.q2jet_eta);
  TTLJJetAssignmentTool->AddVariable("q2jet_phi",&inputvar_TTSemilepJetAssignmentTool.q2jet_phi);
  TTLJJetAssignmentTool->AddVariable("q2jet_E",&inputvar_TTSemilepJetAssignmentTool.q2jet_E);

  TTLJJetAssignmentTool->AddVariable("WhadCand_mass",&inputvar_TTSemilepJetAssignmentTool.WhadCand_mass);
  TTLJJetAssignmentTool->AddVariable("ThadCand_mass",&inputvar_TTSemilepJetAssignmentTool.ThadCand_mass);

  TTLJJetAssignmentTool->AddVariable("WlepCand_mt",&inputvar_TTSemilepJetAssignmentTool.WlepCand_mt);
  TTLJJetAssignmentTool->AddVariable("TlepCand_mt",&inputvar_TTSemilepJetAssignmentTool.TlepCand_mt);




  TTLJJetAssignmentTool->SetupTMVA();//set link

}


JHAnalyzerBase::TTSemilepJetAssignmentToolvar JHAnalyzerBase::Get_JetAssignmentvar(TLorentzVector &_met, TLorentzVector &_lep, TLorentzVector &_blep, TLorentzVector &_bhad, TLorentzVector &_q1jet, TLorentzVector &_q2jet){
  TTSemilepJetAssignmentToolvar ret;
  ret.met_pt=_met.Pt();
  ret.met_phi=_met.Phi();

  ret.lep_pt=_lep.Pt();
  ret.lep_eta=_lep.Eta();
  ret.lep_phi=_lep.Phi();
  
  ret.blep_pt=_blep.Pt();
  ret.blep_eta=_blep.Eta();
  ret.blep_phi=_blep.Phi();
  ret.blep_E=_blep.E();

  ret.bhad_pt=_bhad.Pt();
  ret.bhad_eta=_bhad.Eta();
  ret.bhad_phi=_bhad.Phi();
  ret.bhad_E=_bhad.E();

  ret.q1jet_pt=_q1jet.Pt();
  ret.q1jet_eta=_q1jet.Eta();
  ret.q1jet_phi=_q1jet.Phi();
  ret.q1jet_E=_q1jet.E();

  ret.q2jet_pt=_q2jet.Pt();
  ret.q2jet_eta=_q2jet.Eta();
  ret.q2jet_phi=_q2jet.Phi();
  ret.q2jet_E=_q2jet.E();

  ret.WhadCand_mass=(_q1jet+_q2jet).M();
  ret.ThadCand_mass=(_q1jet+_q2jet+_bhad).M();


  TLorentzVector vt_Wlep=GetTransverseVector(_lep)+_met;
  TLorentzVector vt_Tlep=vt_Wlep+GetTransverseVector(_blep);

  ret.WlepCand_mt=vt_Wlep.M();
  ret.TlepCand_mt=vt_Tlep.M();
  return ret;
}

void JHAnalyzerBase::SetTTSemilepJetAssignmentScore(TLorentzVector &_met, TLorentzVector &_lep, TLorentzVector &_blep, TLorentzVector &_bhad, TLorentzVector &_q1jet, TLorentzVector &_q2jet){
  inputvar_TTSemilepJetAssignmentTool=Get_JetAssignmentvar(_met, _lep, _blep, _bhad, _q1jet, _q2jet);//Change input variable value
  TTLJJetAssignmentTool->SetScore();
}

double JHAnalyzerBase::GetTTSemilepJetAssignmentScore(){
  return TTLJJetAssignmentTool->GetScore();
}

double JHAnalyzerBase::Chi2TTSemiLep(double *x, double *par){
  //set params
  double _lepx=par[0];
  double _lepy=par[1];
  double _lepz=par[2];
  double _lepE=par[3];

  double _blepx=par[4];
  double _blepy=par[5];
  double _blepz=par[6];
  double _blepE=par[7];

  double _metx=par[8];
  double _mety=par[9];

  double _q1x=par[10];
  double _q1y=par[11];
  double _q1z=par[12];
  double _q1E=par[13];

  double _q2x=par[14];
  double _q2y=par[15];
  double _q2z=par[16];
  double _q2E=par[17];

  double _bhadx=par[18];
  double _bhady=par[19];
  double _bhadz=par[20];
  double _bhadE=par[21];


  double vz = x[0];
  double E2_neutrino= pow(vz,2) + pow(_metx,2) + pow(_mety,2);
  double E_neutrino=sqrt(E2_neutrino);
  TLorentzVector neutrino;
  neutrino.SetPxPyPzE(_metx,_mety,vz, E_neutrino);
  //---Wlep part
  TLorentzVector _Wlep,_lep;
  _lep.SetPxPyPzE(_lepx,_lepy,_lepz,_lepE);
  _Wlep=neutrino+_lep;
  //---Whad part
  TLorentzVector _Whad, _q1, _q2;
  _q1.SetPxPyPzE(_q1x,_q1y,_q1z,_q1E);
  _q2.SetPxPyPzE(_q2x,_q2y,_q2z,_q2E);
  _Whad=_q1+_q2;
  //---bjets
  TLorentzVector _blep,_bhad;
  _blep.SetPxPyPzE(_blepx,_blepy,_blepz,_blepE);
  _bhad.SetPxPyPzE(_bhadx,_bhady,_bhadz,_bhadE);
  //---Toplep part
  TLorentzVector _Tlep;
  _Tlep=neutrino+_lep+_blep;
  //---Top_had part
  TLorentzVector _Thad;
  _Thad=_q1+_q2+_bhad;

  //chi2
  double ret= pow((MW_pdg-_Wlep.M())/Width_W_pdg,2) + pow((MW_pdg-_Whad.M())/Width_W_pdg,2) + pow((MTop_pdg-_Tlep.M())/Width_Top_pdg  ,2) + pow((MTop_pdg-_Thad.M())/Width_Top_pdg  ,2) ;
  return ret;


}


pair<vector<int>,double> JHAnalyzerBase::GetJetIndexSet_Chi2(Lepton &_l1, TLorentzVector &_met,vector<Jet> &_v_tightjet, vector<int> &_v_bjetidx, bool _kincut){
  unsigned int _v_tightjetsize=_v_tightjet.size();
  double minchi2=std::numeric_limits<double>::max();
  pair<vector<int>,double> ret({-1,-1,-1,-1},0.0);

  for(auto &ib1 : _v_bjetidx){
    for(auto &ib2 : _v_bjetidx){
      if(ib1==ib2)continue;
      for(unsigned int iq1=0; iq1 < _v_tightjetsize; iq1++){
        if(ib1==iq1) continue;
        if(ib2==iq1) continue;//skip bquark

        for(unsigned int iq2=0; iq2 < _v_tightjetsize; iq2++){
          if(iq1==iq2) continue;

          if(ib1==iq2) continue;
          if(ib2==iq2) continue;//skip bquark

          ///-----NOW we have ib1,ib2,iq1,iq2
          // let ib2 "bHad" candidate

          TLorentzVector this_Thad, this_Whad;
          this_Whad=_v_tightjet[iq1]+_v_tightjet[iq2];
          this_Thad=this_Whad+_v_tightjet[ib2];
          if(_kincut){
            ///1) ThadCand mass : [100,240]
            ///2) M(blep,l) < 170
            double this_Thad_mass=this_Thad.M();
            if(this_Thad_mass < 100.) continue;
            if(this_Thad_mass > 240.) continue;
            TLorentzVector this_blep_lep;
            this_blep_lep=_l1+_v_tightjet[ib1];
            double this_blep_lep_mass=this_blep_lep.M();
            if(this_blep_lep_mass > 170.) continue;
            //(3)|dphi(Tlep,Thad)|> 1.5 -> not applied
            //TLorentzVector this_Tlep, this_neutrino;
            //this_neutrino=_met;
            //this_Tlep=this_neutrino+_v_tightjet[ib1]+_l1;
            //this_Thad,this_Tlep
            //double this_dphi=this_Thad.DeltaPhi(this_Tlep);
            //if(fabs(this_dphi) < 1.5) continue;
          }
          pair<double,double> this_chi2ret=GetChi2_and_vz(_l1,_met,_v_tightjet[ib1],_v_tightjet[iq1],_v_tightjet[iq2],_v_tightjet[ib2]);
          double this_chi2=this_chi2ret.first;
          double this_vz=this_chi2ret.second;

          if(this_chi2 < minchi2){
            minchi2=this_chi2;
            ret.first[0]=ib1; ret.first[1]=ib2; ret.first[2]=iq1, ret.first[3]=iq2;
            ret.second=this_vz;
          }
        }//[END of iq2]
      }//[END of iq1]
    }//[END of ib2]
  }//[END of ib1 loop]
  return ret;
}






pair<vector<int>,double> JHAnalyzerBase::GetJetIndexSet_Chi2_1b(Lepton &_l1, TLorentzVector &_met,vector<Jet> &_v_tightjet, int bjetidx, bool kincut){
  //for debug
  /*
  if(EvtToTest && (nominalevent || electronscale00event)){
    cout << "[GetJetIndexSet_Chi2_1b]" << endl;
    cout << "_l1 pt,eta,phi=" << _l1.Pt() << "," << _l1.Eta() << "," << _l1.Phi() << endl;
    cout << "_met.Pt,Phi" << _met.Pt() << "," << _met.Phi() << endl;
    cout << "Printjet" << endl;
    for(auto&  _jet : _v_tightjet){
      cout << "pt,eta,phi" << _jet.Pt() << "," << _jet.Eta() << "," << _jet.Phi() << endl; 
    }
    cout << "bjetidx=" << bjetidx <<endl;
    cout << "TopMassWindow" << TopMassWindow << endl;
  }
  */
  //end of debug

  //
  /// 1b is determined
  // case1 ) 1b is blep
  // -> You should find bhad and q1,q2 from other jets
  // case2 ) 1b is bhad
  // -> You should find blep and q1,q2 from other jets
  // final return
  // {blep, bhad, q1,q2} , pz of neutrino

  unsigned int _v_tightjetsize=_v_tightjet.size();
  double minchi2=std::numeric_limits<double>::max();
  pair<vector<int>,double> ret({-1,-1,-1,-1},0.0);

  
  for(unsigned int iq1=0; iq1 < _v_tightjetsize; iq1++){
    if(iq1==bjetidx) continue;
    for(unsigned int iq2=0; iq2 < _v_tightjetsize; iq2++){
      if(iq2<=iq1) continue; // q1,q2's order is not important. we only care the combination.
      if(iq2==bjetidx) continue;      
      for(unsigned int ib2=0; ib2 < _v_tightjetsize; ib2++){
	if(ib2==iq1) continue;
	if(ib2==iq2) continue;
	if(ib2==bjetidx) continue;

	//---Now we have bjetidx, ib2, iq1,iq2
	//[case1] bjetidx==>iblep
	//then ib2==>ibhad
	
	pair<double,double> case1_chi2ret=GetChi2_and_vz(_l1,_met,_v_tightjet[bjetidx],_v_tightjet[iq1],_v_tightjet[iq2],_v_tightjet[ib2]);
	double case1_chi2=case1_chi2ret.first;
	double case1_vz=case1_chi2ret.second;
	if(kincut){
	  //1.ThadCand mass : [100,240]
	  //2.M(blep,l) < 170    
	  TLorentzVector Tlep,Thad,neutrino;
	  neutrino.SetPxPyPzE(_met.Px(),_met.Py(),case1_vz, sqrt( pow(_met.Px(),2) + pow(_met.Py(),2) + pow(case1_vz,2) ));
	  //Tlep
	  Tlep=neutrino+_l1+_v_tightjet[bjetidx];
	  double M_Tlep=Tlep.M();
	  //Thad
	  Thad=_v_tightjet[iq1]+_v_tightjet[iq2]+_v_tightjet[ib2];
	  double M_Thad=Thad.M();
	  ////
	  //M(blep,l) < 170
	  double M_blep_l= (_v_tightjet[bjetidx] + _l1).M();

	  if(M_Tlep > 240. || M_Tlep < 100. || M_Thad > 240. || M_Thad < 100. || M_blep_l > 170.){
	    case1_chi2=std::numeric_limits<double>::max(); // skip this case
	  }
	  
	}
	
	if(case1_chi2 < minchi2){
	  minchi2=case1_chi2;
	  ret.first[0]=bjetidx; ret.first[1]=ib2; ret.first[2]=iq1, ret.first[3]=iq2;
	  ret.second=case1_vz;
	}

	
	//[case2] bjetidx==>ibhad
	//then ib2===>iblep
	pair<double,double> case2_chi2ret=GetChi2_and_vz(_l1,_met,_v_tightjet[ib2],_v_tightjet[iq1],_v_tightjet[iq2],_v_tightjet[bjetidx]);
	double case2_chi2=case2_chi2ret.first;
	double case2_vz=case2_chi2ret.second;


	if(kincut){
	  //1.ThadCand mass : [100,240]
	  //2.M(blep,l) < 170    
	  
	  TLorentzVector Tlep,Thad,neutrino;
	  neutrino.SetPxPyPzE(_met.Px(),_met.Py(),case2_vz, sqrt( pow(_met.Px(),2) + pow(_met.Py(),2) + pow(case2_vz,2) ));
	  //Tlep
	  Tlep=neutrino+_l1+_v_tightjet[ib2];
	  double M_Tlep=Tlep.M();
	  //Thad
	  Thad=_v_tightjet[iq1]+_v_tightjet[iq2]+_v_tightjet[bjetidx];
	  double M_Thad=Thad.M();
	  ////
          //M(blep,l) < 170
	  double M_blep_l= (_v_tightjet[ib2] + _l1).M();

	  if(M_Tlep > 240. || M_Tlep < 100. || M_Thad > 240. || M_Thad < 100. || M_blep_l > 170.){
	    case2_chi2=std::numeric_limits<double>::max(); // skip this case
	  }
	  
	}

	
	if(case2_chi2 < minchi2){
	  minchi2=case2_chi2;
	  ret.first[0]=ib2; ret.first[1]=bjetidx; ret.first[2]=iq1, ret.first[3]=iq2;
	  ret.second=case2_vz;
	}

	
      }
    }//[END] iq2 loop
  }//[END] iq1 loop

  ///for debug
  /*
  if(EvtToTest && (nominalevent || electronscale00event)){
    cout << "chi2 fitter ret" << endl;
    cout << "jetidx=" << ret.first[0] << "," << ret.first[1] << "," << ret.first[2] << "," << ret.first[3] << endl;
    cout << "vz=" << ret.second << endl;
    cout << "minchi2=" << minchi2 << endl;
  }
  */
  //[end]for debug
  return ret;

}


pair<vector<int>,double> JHAnalyzerBase::GetJetIndexSet_Chi2_1b_AssignToLeptonicSide(Lepton &_l1, TLorentzVector &_met,vector<Jet> &_v_tightjet, int bjetidx, bool TopMassWindow){
  //for debug                                                                                                                                          
  /*                                                                                                                                                   
  if(EvtToTest && (nominalevent || electronscale00event)){                                                                                             
    cout << "[GetJetIndexSet_Chi2_1b]" << endl;                                                                                                        
    cout << "_l1 pt,eta,phi=" << _l1.Pt() << "," << _l1.Eta() << "," << _l1.Phi() << endl;                                                             
    cout << "_met.Pt,Phi" << _met.Pt() << "," << _met.Phi() << endl;                                                                                   
    cout << "Printjet" << endl;                                                                                                                        
    for(auto&  _jet : _v_tightjet){                                                                                                                    
      cout << "pt,eta,phi" << _jet.Pt() << "," << _jet.Eta() << "," << _jet.Phi() << endl;                                                             
    }                                                                                                                                                  
    cout << "bjetidx=" << bjetidx <<endl;                                                                                                              
    cout << "TopMassWindow" << TopMassWindow << endl;                                                                                                  
  }                                                                                                                                                    
  */
  //end of debug                                                                                                                                       

  //                                                                                                                                                   
  /// 1b is determined                                                                                                                                 
  // case1 ) 1b is blep                                                                                                                                
  // -> You should find bhad and q1,q2 from other jets                                                                                                 
  // case2 ) 1b is bhad                                                                                                                                
  // -> You should find blep and q1,q2 from other jets                                                                                                 
  // final return                                                                                                                                      
  // {blep, bhad, q1,q2} , pz of neutrino                                                                                                              

  unsigned int _v_tightjetsize=_v_tightjet.size();
  double minchi2=std::numeric_limits<double>::max();
  pair<vector<int>,double> ret({-1,-1,-1,-1},0.0);


  for(unsigned int iq1=0; iq1 < _v_tightjetsize; iq1++){
    if(iq1==bjetidx) continue;
    for(unsigned int iq2=0; iq2 < _v_tightjetsize; iq2++){
      if(iq2<=iq1) continue; // q1,q2's order is not important. we only care the combination.                                                          
      if(iq2==bjetidx) continue;
      for(unsigned int ib2=0; ib2 < _v_tightjetsize; ib2++){
        if(ib2==iq1) continue;
        if(ib2==iq2) continue;
        if(ib2==bjetidx) continue;

        //---Now we have bjetidx, ib2, iq1,iq2                                                                                                         
        //[case1] bjetidx==>iblep                                                                                                                      
        //then ib2==>ibhad                                                                                                                             

        pair<double,double> case1_chi2ret=GetChi2_and_vz(_l1,_met,_v_tightjet[bjetidx],_v_tightjet[iq1],_v_tightjet[iq2],_v_tightjet[ib2]);
        double case1_chi2=case1_chi2ret.first;
        double case1_vz=case1_chi2ret.second;
        if(TopMassWindow){
          //ThadCand mass : [100,240]                                                                                                                  
          TLorentzVector Tlep,Thad,neutrino;
          neutrino.SetPxPyPzE(_met.Px(),_met.Py(),case1_vz, sqrt( pow(_met.Px(),2) + pow(_met.Py(),2) + pow(case1_vz,2) ));
          //Tlep                                                                                                                                       
          Tlep=neutrino+_l1+_v_tightjet[bjetidx];
          double M_Tlep=Tlep.M();
          //Thad                                                                                                                                       
          Thad=_v_tightjet[iq1]+_v_tightjet[iq2]+_v_tightjet[ib2];
          double M_Thad=Thad.M();
          ////                                                                                                                                         

          if(M_Tlep > 240. || M_Tlep < 100. || M_Thad > 240. || M_Thad < 100. ){
            case1_chi2=std::numeric_limits<double>::max(); // skip this case                                                                           
          }

        }

        if(case1_chi2 < minchi2){
          minchi2=case1_chi2;
          ret.first[0]=bjetidx; ret.first[1]=ib2; ret.first[2]=iq1, ret.first[3]=iq2;
          ret.second=case1_vz;
        }


      }
    }//[END] iq2 loop                                                                                                                                  
  }//[END] iq1 loop                                                                                                                                    

  ///for debug                                                                                                                                         
  /*                                                                                                                                                   
  if(EvtToTest && (nominalevent || electronscale00event)){                                                                                             
    cout << "chi2 fitter ret" << endl;                                                                                                                 
    cout << "jetidx=" << ret.first[0] << "," << ret.first[1] << "," << ret.first[2] << "," << ret.first[3] << endl;                                    
    cout << "vz=" << ret.second << endl;                                                                                                               
    cout << "minchi2=" << minchi2 << endl;                                                                                                             
  }                                                                                                                                                    
  */
  //[end]for debug                                                                                                                                     
  return ret;

}



pair<vector<int>,double> JHAnalyzerBase::GetJetIndexSet_Chi2_1b_AssignToHadronicSide(Lepton &_l1, TLorentzVector &_met,vector<Jet> &_v_tightjet, int bjetidx, bool TopMassWindow){
  //for debug                                                                                                                                          
  /*                                                                                                                                                   
  if(EvtToTest && (nominalevent || electronscale00event)){                                                                                             
    cout << "[GetJetIndexSet_Chi2_1b]" << endl;                                                                                                        
    cout << "_l1 pt,eta,phi=" << _l1.Pt() << "," << _l1.Eta() << "," << _l1.Phi() << endl;                                                             
    cout << "_met.Pt,Phi" << _met.Pt() << "," << _met.Phi() << endl;                                                                                   
    cout << "Printjet" << endl;                                                                                                                        
    for(auto&  _jet : _v_tightjet){                                                                                                                    
      cout << "pt,eta,phi" << _jet.Pt() << "," << _jet.Eta() << "," << _jet.Phi() << endl;                                                             
    }                                                                                                                                                  
    cout << "bjetidx=" << bjetidx <<endl;                                                                                                              
    cout << "TopMassWindow" << TopMassWindow << endl;                                                                                                  
  }                                                                                                                                                    
  */
  //end of debug                                                                                                                                       

  //                                                                                                                                                   
  /// 1b is determined                                                                                                                                 
  // case1 ) 1b is blep                                                                                                                                
  // -> You should find bhad and q1,q2 from other jets                                                                                                 
  // case2 ) 1b is bhad                                                                                                                                
  // -> You should find blep and q1,q2 from other jets                                                                                                 
  // final return                                                                                                                                      
  // {blep, bhad, q1,q2} , pz of neutrino                                                                                                              

  unsigned int _v_tightjetsize=_v_tightjet.size();
  double minchi2=std::numeric_limits<double>::max();
  pair<vector<int>,double> ret({-1,-1,-1,-1},0.0);


  for(unsigned int iq1=0; iq1 < _v_tightjetsize; iq1++){
    if(iq1==bjetidx) continue;
    for(unsigned int iq2=0; iq2 < _v_tightjetsize; iq2++){
      if(iq2<=iq1) continue; // q1,q2's order is not important. we only care the combination.                                                          
      if(iq2==bjetidx) continue;
      for(unsigned int ib2=0; ib2 < _v_tightjetsize; ib2++){
        if(ib2==iq1) continue;
        if(ib2==iq2) continue;
        if(ib2==bjetidx) continue;

        //---Now we have bjetidx, ib2, iq1,iq2                                                                                                         
        //[case1] bjetidx==>iblep                                                                                                                      
        //then ib2==>ibhad                                                                                                                             
	//-->skip


        //[case2] bjetidx==>ibhad                                                                                                                      
        //then ib2===>iblep                                                                                                                            
        pair<double,double> case2_chi2ret=GetChi2_and_vz(_l1,_met,_v_tightjet[ib2],_v_tightjet[iq1],_v_tightjet[iq2],_v_tightjet[bjetidx]);
        double case2_chi2=case2_chi2ret.first;
        double case2_vz=case2_chi2ret.second;


        if(TopMassWindow){
          //ThadCand mass : [100,240]                                                                                                                  
          TLorentzVector Tlep,Thad,neutrino;
          neutrino.SetPxPyPzE(_met.Px(),_met.Py(),case2_vz, sqrt( pow(_met.Px(),2) + pow(_met.Py(),2) + pow(case2_vz,2) ));
          //Tlep                                                                                                                                       
          Tlep=neutrino+_l1+_v_tightjet[ib2];
          double M_Tlep=Tlep.M();
          //Thad                                                                                                                                       
          Thad=_v_tightjet[iq1]+_v_tightjet[iq2]+_v_tightjet[bjetidx];
          double M_Thad=Thad.M();
          ////                                                                                                                                         

          if(M_Tlep > 240. || M_Tlep < 100. || M_Thad > 240. || M_Thad < 100. ){
            case2_chi2=std::numeric_limits<double>::max(); // skip this case                                                                           
          }

        }


        if(case2_chi2 < minchi2){
          minchi2=case2_chi2;
          ret.first[0]=ib2; ret.first[1]=bjetidx; ret.first[2]=iq1, ret.first[3]=iq2;
          ret.second=case2_vz;
        }


      }
    }//[END] iq2 loop                                                                                                                                  
  }//[END] iq1 loop                                                                                                                                    

  ///for debug                                                                                                                                         
  /*                                                                                                                                                   
  if(EvtToTest && (nominalevent || electronscale00event)){                                                                                             
    cout << "chi2 fitter ret" << endl;                                                                                                                 
    cout << "jetidx=" << ret.first[0] << "," << ret.first[1] << "," << ret.first[2] << "," << ret.first[3] << endl;                                    
    cout << "vz=" << ret.second << endl;                                                                                                               
    cout << "minchi2=" << minchi2 << endl;                                                                                                             
  }                                                                                                                                                    
  */
  //[end]for debug                                                                                                                                     
  return ret;

}



void JHAnalyzerBase::InitJetAssigenChi2Fitter(){
  //f1 = new TF1("f1", JHAnalyzerBase::Chi2TTSemiLep, -10000, 10000, 22);
  //f1 = new TF1("f1", JHAnalyzerBase::Chi2TTSemiLep, -500, 500, 22);//update 250719 by GEN/LEN Level vz dist.
  f1 = new TF1("f1", JHAnalyzerBase::Chi2TTSemiLep, -2000, 2000, 22);//update 250722 by GEN/LEN Level vz dist.
  //f1->SetNpx(1000);
  IsJetAssigenChi2FitterOn=1;

  
}

void JHAnalyzerBase::DeleteJetAssigenChi2Fitter(){
  if(IsJetAssigenChi2FitterOn){
    cout << "delete f1" << endl;
    if (f1){
      delete f1;
      f1=nullptr;
    }
  }
}

pair<double,double> JHAnalyzerBase::GetChi2_and_vz(TLorentzVector &_lep, TLorentzVector &_MET, TLorentzVector &_blep, TLorentzVector &_q1, TLorentzVector &_q2, TLorentzVector &_bhad){
  //cout << "-----GetChi2_and_vz" << endl;
  if(!f1){
    cout << "[JHAnalyzerBase::GetChi2_and_vz]f1 is not set yet!!" << endl;
    1/0;
  }
  //nparam=22
  //TF1 *f1 = new TF1("f1", JHAnalyzerBase::Chi2TTSemiLep, -10000, 10000, 22);//name, function, range,range,nparam
  //f1->SetDirectory(0);//add for avoid memory leakage(not sure)
  
  f1->SetParameter(0, _lep.Px());
  f1->SetParameter(1, _lep.Py());
  f1->SetParameter(2, _lep.Pz());
  f1->SetParameter(3, _lep.E());

  f1->SetParameter(4, _blep.Px());
  f1->SetParameter(5, _blep.Py());
  f1->SetParameter(6, _blep.Pz());
  f1->SetParameter(7, _blep.E());

  f1->SetParameter(8, _MET.Px());
  f1->SetParameter(9, _MET.Py());

  f1->SetParameter(10, _q1.Px());
  f1->SetParameter(11, _q1.Py());
  f1->SetParameter(12, _q1.Pz());
  f1->SetParameter(13, _q1.E());

  f1->SetParameter(14, _q2.Px());
  f1->SetParameter(15, _q2.Py());
  f1->SetParameter(16, _q2.Pz());
  f1->SetParameter(17, _q2.E());

  f1->SetParameter(18, _bhad.Px());
  f1->SetParameter(19, _bhad.Py());
  f1->SetParameter(20, _bhad.Pz());
  f1->SetParameter(21, _bhad.E());
  f1->Update();
  /*
  //f1->SetRange(-10000,10000); // for init update 250718
  //f1->SetMinimum();
  cout << "f1->GetNpx()" << f1->GetNpx() << endl;
  // Print 22 parameters
  for (int i = 0; i < 22; i++) {
    std::cout << "Parameter " << i << ": " << f1->GetParameter(i) << std::endl;
  }
  
  // Print x range
  std::cout << "X Range: [" << f1->GetXmin() << ", " << f1->GetXmax() << "]" << std::endl;
  
  */
  
  double min_vz = f1->GetMinimumX();
  double min_val = f1->Eval(min_vz);
  //cout << "f1->Eval(-4.2572)= " << f1->Eval(-4.2572) << endl;
  pair<double,double> ret;
  ret.first=min_val;
  ret.second=min_vz;

  //debug
  /*
  cout << "nominalevent=" << nominalevent << endl;
  cout << "muonscale00event=" << muonscale00event << endl;
  cout << "electronscale00event=" << electronscale00event << endl;
  cout << "minchi2 in fitter=" << ret.first << endl;
  cout << "min_vz in fitter=" << min_vz << endl;
  */
  //end debug
  return ret;
}



////----Jet to GEN ptl match----//


bool JHAnalyzerBase::IsGENMatched_Flavour_dR(Jet& this_jet, int genidx){
  if(genidx < 0) return 0;
  if( this_jet.partonFlavour() != gens[genidx].PID() ) return 0;
  if( this_jet.DeltaR(gens[genidx]) > 0.4 ) return 0;
  return 1;

}


//---btag eff mc ---//
void JHAnalyzerBase::SetUpBtagEffMeasurement(){
  TString datapath = getenv("DATA_DIR");
  TString btagpath = datapath+"/"+DataEra+"/BTag/";
  TaggersToMeasure.clear();
  WPsToMeasure.clear();
  CutValuesToMeasure.clear();
  ifstream in_tagger(btagpath+"/CutValues.txt");
  string btaggerline;
  while(getline(in_tagger,btaggerline)){
    std::istringstream is_tag( btaggerline );
    TString tstring_taggerline = btaggerline;
    if(tstring_taggerline.Contains("#")) continue;
    TString a;
    string b,c;
    float d;

    is_tag >> a; // ERA
    is_tag >> b; // TAGGER
    is_tag >> c; // WP
    is_tag >> d; // cut value

    if(a == DataEra){
      TaggersToMeasure.push_back(b);
      WPsToMeasure.push_back(c);
      CutValuesToMeasure.push_back(d);
    }
  }// end of taggermap loop

  cout << "[JHAnalyzerBase::SetUpBtagEffMeasurement] What to measure :" << endl;
  cout << "[JHAnalyzerBase::SetUpBtagEffMeasurement] Tagger\tWP\tCutValue" << endl;
  for(unsigned i_m=0; i_m<TaggersToMeasure.size(); i_m++){

    string Tagger = TaggersToMeasure.at(i_m);
    string WP = WPsToMeasure.at(i_m);
    double CutValue = CutValuesToMeasure.at(i_m);

    cout << "[JHAnalyzerBase::SetUpBtagEffMeasurement] " << Tagger << "\t" << WP << "\t" << CutValue << endl;
  }


}



void JHAnalyzerBase::SetUpBtagEffMeasurementPartonFlavour(){
  TString datapath = getenv("DATA_DIR");
  TString btagpath = datapath+"/"+DataEra+"/BTag/";
  TaggersToMeasure.clear();
  WPsToMeasure.clear();
  CutValuesToMeasure.clear();
  ifstream in_tagger(btagpath+"/CutValues.txt");
  string btaggerline;
  while(getline(in_tagger,btaggerline)){
    std::istringstream is_tag( btaggerline );
    TString tstring_taggerline = btaggerline;
    if(tstring_taggerline.Contains("#")) continue;
    TString a;
    string b,c;
    float d;

    is_tag >> a; // ERA
    is_tag >> b; // TAGGER
    is_tag >> c; // WP
    is_tag >> d; // cut value

    if(a == DataEra){
      TaggersToMeasure.push_back(b);
      WPsToMeasure.push_back(c);
      CutValuesToMeasure.push_back(d);
    }
  }// end of taggermap loop

  cout << "[JHAnalyzerBase::SetUpBtagEffMeasurement] What to measure :" << endl;
  cout << "[JHAnalyzerBase::SetUpBtagEffMeasurement] Tagger\tWP\tCutValue" << endl;
  for(unsigned i_m=0; i_m<TaggersToMeasure.size(); i_m++){

    string Tagger = TaggersToMeasure.at(i_m);
    string WP = WPsToMeasure.at(i_m);
    double CutValue = CutValuesToMeasure.at(i_m);

    cout << "[JHAnalyzerBase::SetUpBtagEffMeasurement] " << Tagger << "\t" << WP << "\t" << CutValue << endl;
  }


}



void JHAnalyzerBase::SetUpBtagEffMeasurementPartonFlavour_bonly(){
  TString datapath = getenv("DATA_DIR");
  TString btagpath = datapath+"/"+DataEra+"/BTag/";
  TaggersToMeasure.clear();
  WPsToMeasure.clear();
  CutValuesToMeasure.clear();
  ifstream in_tagger(btagpath+"/CutValues.txt");
  string btaggerline;
  while(getline(in_tagger,btaggerline)){
    std::istringstream is_tag( btaggerline );
    TString tstring_taggerline = btaggerline;
    if(tstring_taggerline.Contains("#")) continue;
    TString a;
    string b,c;
    float d;

    is_tag >> a; // ERA
    is_tag >> b; // TAGGER
    is_tag >> c; // WP
    is_tag >> d; // cut value

    if(a == DataEra){
      TaggersToMeasure.push_back(b);
      WPsToMeasure.push_back(c);
      CutValuesToMeasure.push_back(d);
    }
  }// end of taggermap loop

  cout << "[JHAnalyzerBase::SetUpBtagEffMeasurement] What to measure :" << endl;
  cout << "[JHAnalyzerBase::SetUpBtagEffMeasurement] Tagger\tWP\tCutValue" << endl;
  for(unsigned i_m=0; i_m<TaggersToMeasure.size(); i_m++){

    string Tagger = TaggersToMeasure.at(i_m);
    string WP = WPsToMeasure.at(i_m);
    double CutValue = CutValuesToMeasure.at(i_m);

    cout << "[JHAnalyzerBase::SetUpBtagEffMeasurement] " << Tagger << "\t" << WP << "\t" << CutValue << endl;
  }


}


void JHAnalyzerBase::Measure_MCbtagEff_GivenJets(vector<Jet> vJets){
  TString weight_sign_str= weight > 0 ? "_POS" : "_NEG";
  //AllJets_raw
  vector<double> vec_etabins = {0.0, 0.8, 1.6, 2., 2.5};
  vector<double> vec_ptbins = {20., 30., 50., 70., 100., 140., 200., 300., 600., 1000.};//PT bins used in POG SF measurements

  double PtMax = vec_ptbins.at( vec_ptbins.size()-1 );
  const int NEtaBin = vec_etabins.size()-1;
  const int NPtBin = vec_ptbins.size()-1;

  double etabins[NEtaBin+1];
  for(int i=0; i<NEtaBin+1; i++) etabins[i] = vec_etabins.at(i);
  double ptbins[NPtBin+1];
  for(int i=0; i<NPtBin+1; i++) ptbins[i] = vec_ptbins.at(i);
  //for(unsigned int ij = 0 ; ij < AllJets_raw.size(); ij++){
  for(auto& this_jet : vJets){
    TString flav= "B";
    if(fabs(this_jet.hadronFlavour()) == 4) flav= "C";
    if(fabs(this_jet.hadronFlavour()) == 0) flav= "Light";
    double this_Eta = fabs(this_jet.Eta());//POG recommendation is to use |eta|
    double this_Pt = this_jet.Pt()<PtMax ? this_jet.Pt() : PtMax-1; // put overflows in the last bin
    //==== First, fill the denominator
    /*
    if(weight>0){
      AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom", this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);
    }else{
      AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom_neg", this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);
    }
    */
    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom", this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);
    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom"+weight_sign_str, this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);
    

    //==== Now looping over (tagger,working point)
    for(unsigned i_m=0; i_m<TaggersToMeasure.size(); i_m++){

      string Tagger = TaggersToMeasure.at(i_m);
      string WP = WPsToMeasure.at(i_m);
      double CutValue = CutValuesToMeasure.at(i_m);

      double this_taggerresult = this_jet.GetTaggerResult( JetTagging::StringToTagger(Tagger) );

      if(this_taggerresult>CutValue){
	/*
	if(weight>0){
	  AnalyzerCore::FillHist("Jet_"+DataEra+"_"+Tagger+"_"+WP+"_eff_"+flav+"_num", this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);
	}else{
	  AnalyzerCore::FillHist("Jet_"+DataEra+"_"+Tagger+"_"+WP+"_eff_"+flav+"_num_neg", this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);
	}
	*/
	AnalyzerCore::FillHist("Jet_"+DataEra+"_"+Tagger+"_"+WP+"_eff_"+flav+"_num", this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);
	AnalyzerCore::FillHist("Jet_"+DataEra+"_"+Tagger+"_"+WP+"_eff_"+flav+"_num"+weight_sign_str, this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);

      }
    } // END Loop (tagger,working point)
  } // END Loop jet


}


void JHAnalyzerBase::Measure_MCbtagEff(){
  //AllJets_raw
  vector<double> vec_etabins = {0.0, 0.8, 1.6, 2., 2.5};
  vector<double> vec_ptbins = {20., 30., 50., 70., 100., 140., 200., 300., 600., 1000.};//PT bins used in POG SF measurements

  double PtMax = vec_ptbins.at( vec_ptbins.size()-1 );
  const int NEtaBin = vec_etabins.size()-1;
  const int NPtBin = vec_ptbins.size()-1;

  double etabins[NEtaBin+1];
  for(int i=0; i<NEtaBin+1; i++) etabins[i] = vec_etabins.at(i);
  double ptbins[NPtBin+1];
  for(int i=0; i<NPtBin+1; i++) ptbins[i] = vec_ptbins.at(i);
  for(unsigned int ij = 0 ; ij < AllJets_raw.size(); ij++){

    TString flav= "B";
    if(fabs(AllJets_raw.at(ij).hadronFlavour()) == 4) flav= "C";
    if(fabs(AllJets_raw.at(ij).hadronFlavour()) == 0) flav= "Light";
    double this_Eta = fabs(AllJets_raw.at(ij).Eta());//POG recommendation is to use |eta|
    double this_Pt = AllJets_raw.at(ij).Pt()<PtMax ? AllJets_raw.at(ij).Pt() : PtMax-1; // put overflows in the last bin
    //==== First, fill the denominator
    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom", this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);

    //==== Now looping over (tagger,working point)
    for(unsigned i_m=0; i_m<TaggersToMeasure.size(); i_m++){

      string Tagger = TaggersToMeasure.at(i_m);
      string WP = WPsToMeasure.at(i_m);
      double CutValue = CutValuesToMeasure.at(i_m);

      double this_taggerresult = AllJets_raw.at(ij).GetTaggerResult( JetTagging::StringToTagger(Tagger) );

      if(this_taggerresult>CutValue){
	AnalyzerCore::FillHist("Jet_"+DataEra+"_"+Tagger+"_"+WP+"_eff_"+flav+"_num", this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);
      }
    } // END Loop (tagger,working point)
  } // END Loop jet


}




//measure btageff by partonFlavour
void JHAnalyzerBase::Measure_MCbtagEff_PartonFlavour(){
  //AllJets_raw
  vector<double> vec_etabins = {0.0, 0.8, 1.6, 2., 2.5};
  vector<double> vec_ptbins = {20., 30., 50., 70., 100., 140., 200., 300., 600., 1000.};//PT bins used in POG SF measurements

  double PtMax = vec_ptbins.at( vec_ptbins.size()-1 );
  const int NEtaBin = vec_etabins.size()-1;
  const int NPtBin = vec_ptbins.size()-1;

  double etabins[NEtaBin+1];
  for(int i=0; i<NEtaBin+1; i++) etabins[i] = vec_etabins.at(i);
  double ptbins[NPtBin+1];
  for(int i=0; i<NPtBin+1; i++) ptbins[i] = vec_ptbins.at(i);
  for(unsigned int ij = 0 ; ij < AllJets_raw.size(); ij++){
    //TString str = std::to_string(value).c_str();
    TString flav= std::to_string(AllJets_raw.at(ij).partonFlavour()).c_str();
    double this_Eta = fabs(AllJets_raw.at(ij).Eta());//POG recommendation is to use |eta|
    double this_Pt = AllJets_raw.at(ij).Pt()<PtMax ? AllJets_raw.at(ij).Pt() : PtMax-1; // put overflows in the last bin
    //==== First, fill the denominator
    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom", this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);
    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom__ETA", this_Eta, weight, NEtaBin, etabins);
    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom__PT",  this_Pt, weight, NPtBin, ptbins);
    //  //    AnalyzerCore::FillHist(newhistname+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom__Overall",  0.5, weight, 1, 0,1);

    //==== Now looping over (tagger,working point)
    for(unsigned i_m=0; i_m<TaggersToMeasure.size(); i_m++){

      string Tagger = TaggersToMeasure.at(i_m);
      string WP = WPsToMeasure.at(i_m);
      double CutValue = CutValuesToMeasure.at(i_m);

      double this_taggerresult = AllJets_raw.at(ij).GetTaggerResult( JetTagging::StringToTagger(Tagger) );

      if(this_taggerresult>CutValue){
	AnalyzerCore::FillHist("Jet_"+DataEra+"_"+Tagger+"_"+WP+"_eff_"+flav+"_num", this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);
	AnalyzerCore::FillHist("Jet_"+DataEra+"_"+Tagger+"_"+WP+"_eff_"+flav+"_num__ETA", this_Eta,  weight, NEtaBin, etabins);
	AnalyzerCore::FillHist("Jet_"+DataEra+"_"+Tagger+"_"+WP+"_eff_"+flav+"_num__PT", this_Pt, weight, NPtBin, ptbins);

	AnalyzerCore::FillHist("Jet_"+DataEra+"_"+Tagger+"_"+WP+"_eff_"+flav+"_num__Overall", 0.5, weight, 1, 0,1);
      }
    } // END Loop (tagger,working point)
  } // END Loop jet


}

void JHAnalyzerBase::Measure_MCbtagEff_PartonFlavour_bonly(){
  //AllJets_raw
  vector<double> vec_etabins = {0.0, 0.8, 1.6, 2., 2.5};
  vector<double> vec_ptbins = {20., 30., 50., 70., 100., 140., 200., 300., 600., 1000.};//PT bins used in POG SF measurements

  double PtMax = vec_ptbins.at( vec_ptbins.size()-1 );
  const int NEtaBin = vec_etabins.size()-1;
  const int NPtBin = vec_ptbins.size()-1;

  double etabins[NEtaBin+1];
  for(int i=0; i<NEtaBin+1; i++) etabins[i] = vec_etabins.at(i);
  double ptbins[NPtBin+1];
  for(int i=0; i<NPtBin+1; i++) ptbins[i] = vec_ptbins.at(i);
  for(unsigned int ij = 0 ; ij < AllJets_raw.size(); ij++){

    TString flav= "B";
    if(fabs(AllJets_raw.at(ij).hadronFlavour()) == 5){
      int this_parton=AllJets_raw.at(ij).partonFlavour();
      if(this_parton==5){
	flav="Bminus";
      }else if(this_parton==-5){
	flav="Bplus";
      }
      else{
	flav="B";
      }
    }
    if(fabs(AllJets_raw.at(ij).hadronFlavour()) == 4) flav= "C";
    if(fabs(AllJets_raw.at(ij).hadronFlavour()) == 0) flav= "Light";
    double this_Eta = fabs(AllJets_raw.at(ij).Eta());//POG recommendation is to use |eta|
    double this_Pt = AllJets_raw.at(ij).Pt()<PtMax ? AllJets_raw.at(ij).Pt() : PtMax-1; // put overflows in the last bin
    //==== First, fill the denominator
    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom", this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);

    //==== Now looping over (tagger,working point)
    for(unsigned i_m=0; i_m<TaggersToMeasure.size(); i_m++){

      string Tagger = TaggersToMeasure.at(i_m);
      string WP = WPsToMeasure.at(i_m);
      double CutValue = CutValuesToMeasure.at(i_m);

      double this_taggerresult = AllJets_raw.at(ij).GetTaggerResult( JetTagging::StringToTagger(Tagger) );

      if(this_taggerresult>CutValue){
	AnalyzerCore::FillHist("Jet_"+DataEra+"_"+Tagger+"_"+WP+"_eff_"+flav+"_num", this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);
      }
    } // END Loop (tagger,working point)
  } // END Loop jet
}

int JHAnalyzerBase::getB(const std::string& s) {
    if (s == "bplus") return k_bplus;
    if (s == "bminus") return k_bminus;
    return -1;
}

int JHAnalyzerBase::getLep(const std::string& s) {
    if (s == "muH") return k_muH;
    if (s == "muL") return k_muL;
    if (s == "eH") return k_eH;
    if (s == "eL") return k_eL;
    return -1;
}

int JHAnalyzerBase::getIDAcc(const std::string& s) {
    if (s == "1muHOnly") return k_1muHOnly;
    if (s == "1muLOnly") return k_1muLOnly;
    if (s == "1eHOnly") return k_1eHOnly;
    if (s == "1eLOnly") return k_1eLOnly;
    if (s == "NoSL_jH") return k_NoSL_jH;
    if (s == "NoSL_jOthers") return k_NoSL_jOthers;    
    return -1;
}

int JHAnalyzerBase::getPT(const std::string& s) {
    if (s == "PT30To50") return kPT30To50;
    if (s == "PT50To70") return kPT50To70;
    if (s == "PT70To100") return kPT70To100;
    if (s == "PT100To140") return kPT100To140;
    if (s == "PT140ToInf") return kPT140ToInf;
    
    return -1;
}

int JHAnalyzerBase::getEta(const std::string& s) {
  if (s == "Eta0To0p8") return kEta0To0p8;
  if (s == "Eta0p8To1p6") return kEta0p8To1p6;
  if (s == "Eta1p6To2") return kEta1p6To2;
  if (s == "Eta2To2p5") return kEta2To2p5;
  
  
  return -1;
}


int JHAnalyzerBase::getSysDir(const std::string& s) {
    if (s == "central") return k_central;
    if (s == "uncorrUp") return k_uncorrUp;
    if (s == "uncorrDown") return k_uncorrDown;
    if (s == "corrUp") return k_corrUp;
    if (s == "corrDown") return k_corrDown;
    return -1;
}


void JHAnalyzerBase::Read_bChargeID_SF(bool readsltonly){
  //----SLT----//
  TString datapath=getenv("DATA_DIR");
  TString sltpath=datapath+"/"+DataEra+"/bChargeTagID/SF/SLT/SF_bChargeTag_SLT_"+DataEra+".txt";
  cout << "SLT Tagging Eff->" << sltpath << endl;
  std::ifstream sltfile(sltpath.Data());
  if (!sltfile.is_open()) {
    std::cerr << "file open failed: " << sltpath << std::endl;
    exit(ENODATA);
  }

  std::string _b, _lep, _pt, _sysdir;
  double _val;

  while (sltfile >> _b >> _lep >> _pt >> _sysdir >> _val) {
    int _ib = getB(_b);
    int _il = getLep(_lep);
    int _ip = getPT(_pt);
    int _is = getSysDir(_sysdir);
    
    if (_ib<0 || _il<0 || _ip<0 || _is<0) continue;
    
    SF_bChargeTagID_SLT[_ib][_il][_ip][_is] = _val;
  }

  ///----Print---//
  ///    SF_bChargeTagID_SLT[_ib][_il][_ip][_is] = _val;
  for(int ib = 0 ; ib < nJetOrigin; ++ib){
    JetOrigin this_jetorigin = static_cast<JetOrigin>(ib);
    for (int ip = 0; ip < nPtBin; ++ip) {
      PtBin this_ptbin = static_cast<PtBin>(ip);
      for(int il =0; il < nSLT; ++il){
	SLT this_SLT = static_cast<SLT>(il);
	for(int is = 0; is < nSYSDIR; ++is){ 
	  SYSDIR this_sysdir = static_cast<SYSDIR>(is);
	  cout << "[JetChargeTagIDEff]this_jetorigin=" << this_jetorigin << " this_ptbin="<< this_ptbin <<" this_SLT="<<this_SLT <<" this_sysdir="<<this_sysdir <<"->" <<SF_bChargeTagID_SLT[this_jetorigin][this_SLT][this_ptbin][this_sysdir] << endl;
	}//is
      }//ie
    }//ip
  }//ib
  //    SF_bChargeTagID_Jet[_ib][_ip][_ie][_is] = _val;

  if(readsltonly){
    for(int ib = 0 ; ib < nJetOrigin; ++ib){
      JetOrigin this_jetorigin = static_cast<JetOrigin>(ib);
      for (int ip = 0; ip < nPtBin; ++ip) {
	PtBin this_ptbin = static_cast<PtBin>(ip);
	for(int ie =0; ie < nEtaBin; ++ie){
	  EtaBin this_etabin = static_cast<EtaBin>(ie);
	  for(int is = 0; is < nSYSDIR; ++is){ 
	    SYSDIR this_sysdir = static_cast<SYSDIR>(is);
	    SF_bChargeTagID_Jet[this_jetorigin][this_ptbin][this_etabin][this_sysdir]=1.;
	    cout << "[JetChargeTagIDEff]this_jetorigin=" << this_jetorigin << " this_ptbin="<< this_ptbin <<" this_etabin="<<this_etabin <<" this_sysdir="<<this_sysdir<<"->" <<SF_bChargeTagID_Jet[this_jetorigin][this_ptbin][this_etabin][this_sysdir] << endl;
	  }//is
	}//ie
      }//ip
    }//ib
    
    
    return ;
  }
  
  //----jH----//
  TString jHpath=datapath+"/"+DataEra+"/bChargeTagID/SF/jH/SF_bChargeTag_jH_"+DataEra+".txt";
  cout << "jH Tagging Eff->" << jHpath << endl;
  std::ifstream jHfile(jHpath.Data());
  if (!jHfile.is_open()) {
    std::cerr << "file open failed: " << jHpath << std::endl;
    exit(ENODATA);
  }
  //std::string _b, _lep, _pt, _eta, _sysdir;
  double _val2;
  std::string _b2,  _pt2, _eta2, _sysdir2;
  
  while (jHfile >> _b2 >> _pt2 >> _eta2 >> _sysdir2 >> _val2) {
    cout << "_b2=" << _b2 << " _pt2=" << _pt2 << " _eta2=" << _eta2 << " _sysdir2=" << _sysdir2 << " _val2=" << _val2 << endl;
    int _ib2 = getB(_b2);
    int _ip2 = getPT(_pt2);
    int _ie2 = getEta(_eta2);
    int _is2 = getSysDir(_sysdir2);

    if (_ib2<0 || _ip2<0 || _ie2<0 || _is2<0){
      cout << "!!!! At least one of the index is not read " << endl;
      cout << "_ib2="<<_ib2<<" _ip2="<<_ip2<<" _ie2="<<_ie2<<" _is2="<<_is2<<endl;
      continue;
    }
    SF_bChargeTagID_Jet[_ib2][_ip2][_ie2][_is2] = _val2;


  }
  

  for(int ib = 0 ; ib < nJetOrigin; ++ib){
    JetOrigin this_jetorigin = static_cast<JetOrigin>(ib);
    for (int ip = 0; ip < nPtBin; ++ip) {
      PtBin this_ptbin = static_cast<PtBin>(ip);
      for(int ie =0; ie < nEtaBin; ++ie){
	EtaBin this_etabin = static_cast<EtaBin>(ie);
	for(int is = 0; is < nSYSDIR; ++is){ 
	  SYSDIR this_sysdir = static_cast<SYSDIR>(is);
	  cout << "[JetChargeTagIDEff]this_jetorigin=" << this_jetorigin << " this_ptbin="<< this_ptbin <<" this_etabin="<<this_etabin <<" this_sysdir="<<this_sysdir<<"->" <<SF_bChargeTagID_Jet[this_jetorigin][this_ptbin][this_etabin][this_sysdir] << endl;
	}//is
      }//ie
    }//ip
  }//ib




  
}


void JHAnalyzerBase::Read_bChargeAcc_SF(){
  //----SLT----//
  TString datapath=getenv("DATA_DIR");
  TString sltpath=datapath+"/"+DataEra+"/bChargeAcc/SF/SLT/SF_bChargeAcc_SLT_"+DataEra+".txt";
  cout << "SLT Charge Acc->" << sltpath << endl;
  std::ifstream sltfile(sltpath.Data());
  if (!sltfile.is_open()) {
    std::cerr << "file open failed: " << sltpath << std::endl;
    exit(ENODATA);
  }

  std::string _b, _lep, _pt, _sysdir;
  double _val;

  while (sltfile >> _b >> _lep >> _pt >> _sysdir >> _val) {
    int _ib = getB(_b);
    int _il = getIDAcc(_lep);
    int _ip = getPT(_pt);
    int _is = getSysDir(_sysdir);
    
    if (_ib<0 || _il<0 || _ip<0 || _is<0) continue;
    
    SF_bChargeAcc_SLT[_ib][_il][_ip][_is] = _val;
  }
  //----jH,jOthers----//
  TString NoSLpath=datapath+"/"+DataEra+"/bChargeAcc/SF/NoSL/SF_bChargeAcc_NoSL_"+DataEra+".txt";
  cout << "j Acc Eff->" << NoSLpath << endl;
  std::ifstream NoSLfile(NoSLpath.Data());
  if (!NoSLfile.is_open()) {
    std::cerr << "file open failed: " << NoSLpath << std::endl;
    exit(ENODATA);
  }
  //std::string _b, _lep, _pt, _eta, _sysdir;
  double _val2;
  std::string _b2, _jet2, _pt2, _eta2, _sysdir2;
  
  while (NoSLfile >> _b2 >> _jet2 >> _pt2 >> _eta2 >> _sysdir2 >> _val2) {
    cout << "_b2=" << _b2 << "_jet2" << _jet2 << " _pt2=" << _pt2 << " _eta2=" << _eta2 << " _sysdir2=" << _sysdir2 << " _val2=" << _val2 << endl;
    int _ib2 = getB(_b2);
    int _ij2 = getIDAcc(_jet2)-4;//idx_jetchargeid=idxID-4 
    int _ip2 = getPT(_pt2);
    int _ie2 = getEta(_eta2);
    int _is2 = getSysDir(_sysdir2);

    if (_ib2<0 || _ij2<0 || _ip2<0 || _ie2<0 || _is2<0){
      cout << "!!!! At least one of the index is not read " << endl;
      cout << "_ib2="<<_ib2<< "_ij2" << _ij2 << " _ip2="<<_ip2<<" _ie2="<<_ie2<<" _is2="<<_is2<<endl;
      continue;
    }
    SF_bChargeAcc_Jet[_ib2][_ij2][_ip2][_ie2][_is2] = _val2;


  }
  

  ///----Print---//

  for(int ib = 0 ; ib < nJetOrigin; ++ib){
    JetOrigin this_jetorigin = static_cast<JetOrigin>(ib);
    for (int ip = 0; ip < nPtBin; ++ip) {
      PtBin this_ptbin = static_cast<PtBin>(ip);
      for(int il =0; il < 4; ++il){
	bChargeID thisChargeID = static_cast<bChargeID>(il);
	for(int is = 0; is < nSYSDIR; ++is){ 
	  SYSDIR this_sysdir = static_cast<SYSDIR>(is);
	  cout << "[JetChargeAcc]this_jetorigin=" << this_jetorigin << " this_ptbin="<< this_ptbin <<" thisChargeID="<<thisChargeID <<" this_sysdir="<<this_sysdir <<"->" <<SF_bChargeAcc_SLT[this_jetorigin][thisChargeID][this_ptbin][this_sysdir] << endl;
	}//is
      }//ie
    }//ip
  }//ib
  //    SF_bChargeTagID_Jet[_ib][_ip][_ie][_is] = _val;
  for(int ib = 0 ; ib < nJetOrigin; ++ib){
    JetOrigin this_jetorigin = static_cast<JetOrigin>(ib);
    for(int ij =0; ij < 2; ++ij){
      //bChargeID thisChargeID = static_cast<bChargeID>(ij);
      for (int ip = 0; ip < nPtBin; ++ip) {
	PtBin this_ptbin = static_cast<PtBin>(ip);
	for(int ie =0; ie < nEtaBin; ++ie){
	  EtaBin this_etabin = static_cast<EtaBin>(ie);
	  for(int is = 0; is < nSYSDIR; ++is){ 
	    SYSDIR this_sysdir = static_cast<SYSDIR>(is);
	    cout << "[JetChargeAcc]this_jetorigin=" << this_jetorigin << " ij=" << ij << " this_ptbin="<< this_ptbin <<" this_etabin="<<this_etabin <<" this_sysdir="<<this_sysdir<<"->" <<SF_bChargeAcc_Jet[this_jetorigin][ij][this_ptbin][this_etabin][this_sysdir] << endl;
	  }//is
	}//ie
      }//ip
    }//ij
  }//i 

  
}

void JHAnalyzerBase::Setup_bChargeIDEff(TString _bchargeid_mceff_filename, bool readsltonly){
  Is_bChargeIDEffOn=true;
  Read_bChargeID_SF(readsltonly);




  
  ///Load MC Eff//
  //Setup_bChargeIDEff
  TString default_bchargeid_file="hadd_TTLJ_TTLL.root";
  TString datapath=getenv("DATA_DIR");
  if(_bchargeid_mceff_filename==""){
    cout << "[jhchoi]Use default bchargeid eff" << endl;
    _bchargeid_mceff_filename=default_bchargeid_file;
  }
  else{
    TString mcjetpath1=datapath+"/"+DataEra+"/bChargeTagID/"+_bchargeid_mceff_filename;
    cout << "[jhchoi]Use  btag mc eff-->" << mcjetpath1 << endl;
    ifstream fcheck1(mcjetpath1);
    if(!fcheck1.good()){
      cout << "[jhchoi]FAIL!!! to load  bchargeid mc eff-->" << mcjetpath1 << endl;
      cout << "Use default file" << endl;
      _bchargeid_mceff_filename=default_bchargeid_file;
    }
  }
  TString mcjetpath=datapath+"/"+DataEra+"/bChargeTagID/"+_bchargeid_mceff_filename;
  cout << "[JHAnalyzerBase::Setup_bChargeIDEff]mcjetpath----->" << mcjetpath << endl;
  ifstream fcheck(mcjetpath);
  if(!fcheck.good()){
    cout<<"[JHAnalyzerBase::Setup_bChargeIDEff] no "+mcjetpath<<endl;
    return;
  }
  TFile fmcjet(mcjetpath);
  // Denominator histogram setup first
  vector<TString> v_bsign = {"bplus","bminus"};
  vector<TString> v_bChargeID = {"muH","muL","eH","eL","jH"};
  for(unsigned int i=0; i<v_bsign.size(); i++){
    for(unsigned int j=0; j<v_bChargeID.size(); j++){
      //Jet_2018_Has_eH_eff_bminus_num
      //Jet_2018_eff_bplus_denom
      TString thisSign=v_bsign[i];
      TString thisID=v_bChargeID[j];
      TString hden="Jet_"+DataEra+"_eff_"+thisSign+"_denom";
      TString hnum="Jet_"+DataEra+"_Has_"+thisID+"_eff_"+thisSign+"_num";
      if(thisID=="jH"){
	//Jet_2018_eff_bplus_denom__NoSL
	hden="Jet_"+DataEra+"_eff_"+thisSign+"_denom__NoSL";
	//Jet_2018_jH_eff_bminus_num__NoSL
	hnum="Jet_"+DataEra+"_"+thisID+"_eff_"+thisSign+"_num__NoSL";
      }
      TH2D* this_hist=(TH2D*)fmcjet.Get(hnum)->Clone();      
      TH2D* this_hist_den=(TH2D*)fmcjet.Get(hden);
      this_hist->Divide(this_hist_den);
      this_hist->SetDirectory(0);
      map_effhist_bchargeID_mcjet[thisID+"__"+thisSign]=this_hist;
      
      cout<<"[JHAnalyzerBase::Setup_bChargeIDEff] setting "<< thisSign+"__"+thisID <<endl;
    }
  }
  
  //rSyst
  //---SLT
  for (int ipt = 0; ipt < nPtBin; ++ipt) {
    for (int islt = 0; islt < nSLT; ++islt) {
      arr_r_bChargeID_SLT_CorrUp[islt][ipt]   = 1.0;
      arr_r_bChargeID_SLT_CorrDown[islt][ipt] = 1.0;

      arr_r_bChargeID_SLT_UnCorr_bPlusUp[islt][ipt]   = 1.0;
      arr_r_bChargeID_SLT_UnCorr_bPlusDown[islt][ipt]   = 1.0;

      arr_r_bChargeID_SLT_UnCorr_bMinusUp[islt][ipt] = 1.0;
      arr_r_bChargeID_SLT_UnCorr_bMinusDown[islt][ipt] = 1.0;
    }
  }  
  //---jH
  for (int ipt = 0; ipt < nPtBin; ++ipt) {
    for (int ieta = 0; ieta < nEtaBin; ++ieta) {
      arr_r_bChargeID_Jet_CorrUp[ipt][ieta]   = 1.0;
      arr_r_bChargeID_Jet_CorrDown[ipt][ieta] = 1.0;

      arr_r_bChargeID_Jet_UnCorr_bPlusUp[ipt][ieta]   = 1.0;
      arr_r_bChargeID_Jet_UnCorr_bPlusDown[ipt][ieta] = 1.0;

      arr_r_bChargeID_Jet_UnCorr_bMinusUp[ipt][ieta]   = 1.0;
      arr_r_bChargeID_Jet_UnCorr_bMinusDown[ipt][ieta] = 1.0;


    }
  }

  

}


void JHAnalyzerBase::Setup_bChargeAcc(TString _bchargeacc_mc_filename){
  Is_bChargeAccOn=true;
  Read_bChargeAcc_SF();




  
  ///Load MC Eff//
  //Setup_bChargeAcc
  TString default_bchargeacc_file="hadd_TTLJ_TTLL.root";
  TString datapath=getenv("DATA_DIR");
  if(_bchargeacc_mc_filename==""){
    cout << "[jhchoi]Use default bchargeacc eff" << endl;
    _bchargeacc_mc_filename=default_bchargeacc_file;
  }
  else{
    TString mcjetpath1=datapath+"/"+DataEra+"/bChargeAcc/"+_bchargeacc_mc_filename;
    cout << "[jhchoi]Use  bcharge acc mc eff-->" << mcjetpath1 << endl;
    ifstream fcheck1(mcjetpath1);
    if(!fcheck1.good()){
      cout << "[jhchoi]FAIL!!! to load  bcharge acc mc-->" << mcjetpath1 << endl;
      cout << "Use default file" << endl;
      _bchargeacc_mc_filename=default_bchargeacc_file;
    }
  }
  TString mcjetpath=datapath+"/"+DataEra+"/bChargeAcc/"+_bchargeacc_mc_filename;
  cout << "[JHAnalyzerBase::Setup_bChargeAcc]mcjetpath----->" << mcjetpath << endl;
  ifstream fcheck(mcjetpath);
  if(!fcheck.good()){
    cout<<"[JHAnalyzerBase::Setup_bChargeAcc] no "+mcjetpath<<endl;
    return;
  }
  TFile fmcjet(mcjetpath);
  // Denominator histogram setup first
  vector<TString> v_bsign = {"bplus","bminus"};
  vector<TString> v_bChargeID = {"1muHOnly","1muLOnly","1eHOnly","1eLOnly","NoSL_jH","NoSL_jOthers"};
  for(unsigned int i=0; i<v_bsign.size(); i++){
    for(unsigned int j=0; j<v_bChargeID.size(); j++){

      //Jet_2018_Has_eH_eff_bminus_num
      //Jet_2018_eff_bplus_denom
      TString thisSign=v_bsign[i];
      TString thisID=v_bChargeID[j];
      cout<<"[JHAnalyzerBase::Setup_bChargeAcc] setting "<< thisSign+"__"+thisID <<endl;
      TString hden="Jet_"+DataEra+"_acc_"+thisSign+"_chargeid"+std::to_string(j)+"_denom";
      TString hnum="Jet_"+DataEra+"_acc_"+thisSign+"_chargeid"+to_string(j)+"_num";

      TH2D* this_hist=(TH2D*)fmcjet.Get(hnum)->Clone();      
      TH2D* this_hist_den=(TH2D*)fmcjet.Get(hden);
      this_hist->Divide(this_hist_den);
      this_hist->SetDirectory(0);
      map_acchist_bchargeID_mcjet[thisID+"__"+thisSign]=this_hist;
      

    }
  }
  
  //rSyst
  //---SLT
  for (int ipt = 0; ipt < nPtBin; ++ipt) {
    for (int islt = 0; islt < nSLT; ++islt) {
      arr_r_bChargeAcc_SLT_CorrUp[islt][ipt]   = 1.0;
      arr_r_bChargeAcc_SLT_CorrDown[islt][ipt] = 1.0;

      arr_r_bChargeAcc_SLT_UnCorr_bPlusUp[islt][ipt]   = 1.0;
      arr_r_bChargeAcc_SLT_UnCorr_bPlusDown[islt][ipt]   = 1.0;

      arr_r_bChargeAcc_SLT_UnCorr_bMinusUp[islt][ipt] = 1.0;
      arr_r_bChargeAcc_SLT_UnCorr_bMinusDown[islt][ipt] = 1.0;
    }
  }  
  //---jH/jOthers
  for (int ipt = 0; ipt < nPtBin; ++ipt) {
    for (int ieta = 0; ieta < nEtaBin; ++ieta) {
      for (int ij =0 ; ij < 2; ++ij){
	arr_r_bChargeAcc_Jet_CorrUp[ij][ipt][ieta]   = 1.0;
	arr_r_bChargeAcc_Jet_CorrDown[ij][ipt][ieta] = 1.0;
	
	arr_r_bChargeAcc_Jet_UnCorr_bPlusUp[ij][ipt][ieta]   = 1.0;
	arr_r_bChargeAcc_Jet_UnCorr_bPlusDown[ij][ipt][ieta] = 1.0;
	
	arr_r_bChargeAcc_Jet_UnCorr_bMinusUp[ij][ipt][ieta]   = 1.0;
	arr_r_bChargeAcc_Jet_UnCorr_bMinusDown[ij][ipt][ieta] = 1.0;
      }

    }
  }

  

}



void JHAnalyzerBase::MeasureMC_bChargeIDEff(vector<Jet> vJets ){
  TString weight_sign_str= weight > 0 ? "_POS" : "_NEG";

  vector<double> vec_etabins = {0.0, 0.8, 1.6, 2., 2.5};
  vector<double> vec_ptbins = {20., 30., 50., 70., 100., 140.};
  double etabins[5]= {0.0, 0.8, 1.6, 2., 2.5};
  double etabins_all[2]= {0.0, 2.5};
  double ptbins[6]= {30.,50.,70.,100.,140.,1000.};
  const int NEtaBin = 4;
  const int NEtaBinAll = 1;
  const int NPtBin = 5;

  for(auto& this_jet : vJets){
    if(fabs(this_jet.partonFlavour())!=5) continue;
    if(this_jet.hadronFlavour()!=5) continue;
    TString flav= this_jet.partonFlavour() > 0 ? "bminus" : "bplus";
    double this_Eta = fabs(this_jet.Eta());
    double this_Pt = this_jet.Pt()>1000. ? 999. : this_jet.Pt();

    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);

    std::vector<int> v_nSLT=Count_SLT(this_jet);
    int n_muH=v_nSLT[0];
    int n_muL=v_nSLT[1];
    int n_eH=v_nSLT[2];
    int n_eL=v_nSLT[3];

    if(n_muH>0){
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_muH_eff_"+flav+"_num", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_muH_eff_"+flav+"_num"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);
    }
    if(n_muL>0){
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_muL_eff_"+flav+"_num", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_muL_eff_"+flav+"_num"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);
    }
    if(n_eH>0){
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_eH_eff_"+flav+"_num", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_eH_eff_"+flav+"_num"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);
    }
    if(n_eL>0){
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_eL_eff_"+flav+"_num", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_eL_eff_"+flav+"_num"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);
    }
    if(n_muH==0 && n_muL==0 && n_eH==0 && n_eL==0){
      //do not need to apply SLT tag eff corr because for given jet/pt/eta/origin, the same weight is multiplied to deno and nume both.So it is canceled out.  
      AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom__NoSL", this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom__NoSL"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);

      SetJetChargeScore(this_jet);      
      int jetcharge_coeff=GetJetChargeScoreCoeff();
      if(jetcharge_coeff==1){//_NoSL_jH
	AnalyzerCore::FillHist("Jet_"+DataEra+"_jH_eff_"+flav+"_num__NoSL", this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);
	AnalyzerCore::FillHist("Jet_"+DataEra+"_jH_eff_"+flav+"_num__NoSL"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);
      }
    }
  }


}





void JHAnalyzerBase::MeasureMC_bChargeIDEff_test_v2(vector<Jet> vJets ){
  TString weight_sign_str= weight > 0 ? "_POS" : "_NEG";

  vector<double> vec_etabins = {0.0, 0.8, 1.6, 2., 2.5};
  vector<double> vec_ptbins = {20., 30., 50., 70., 100., 140.};
  double etabins[5]= {0.0, 0.8, 1.6, 2., 2.5};
  double etabins_all[2]= {0.0, 2.5};
  double ptbins[6]= {30.,50.,70.,100.,140.,1000.};
  const int NEtaBin = 4;
  const int NEtaBinAll = 1;
  const int NPtBin = 5;

  for(auto& this_jet : vJets){
    if(fabs(this_jet.partonFlavour())!=5) continue;
    if(this_jet.hadronFlavour()!=5) continue;
    TString flav= this_jet.partonFlavour() > 0 ? "bminus" : "bplus";
    double this_Eta = fabs(this_jet.Eta());
    double this_Pt = this_jet.Pt()>1000. ? 999. : this_jet.Pt();

    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
    AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);

    std::vector<int> v_nSLT=Count_SLT_test_v2(this_jet);
    int n_muH=v_nSLT[0];
    int n_muL=v_nSLT[1];
    int n_eH=v_nSLT[2];
    int n_eL=v_nSLT[3];

    if(n_muH>0){
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_muH_eff_"+flav+"_num", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_muH_eff_"+flav+"_num"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);
    }
    if(n_muL>0){
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_muL_eff_"+flav+"_num", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_muL_eff_"+flav+"_num"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);
    }
    if(n_eH>0){
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_eH_eff_"+flav+"_num", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_eH_eff_"+flav+"_num"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);
    }
    if(n_eL>0){
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_eL_eff_"+flav+"_num", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_Has_eL_eff_"+flav+"_num"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);
    }
    if(n_muH==0 && n_muL==0 && n_eH==0 && n_eL==0){
      //do not need to apply SLT tag eff corr because for given jet/pt/eta/origin, the same weight is multiplied to deno and nume both.So it is canceled out.  
      AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom__NoSL", this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_eff_"+flav+"_denom__NoSL"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);

      SetJetChargeScore(this_jet);      
      int jetcharge_coeff=GetJetChargeScoreCoeff();
      if(jetcharge_coeff==1){//_NoSL_jH
	AnalyzerCore::FillHist("Jet_"+DataEra+"_jH_eff_"+flav+"_num__NoSL", this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);
	AnalyzerCore::FillHist("Jet_"+DataEra+"_jH_eff_"+flav+"_num__NoSL"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);
      }
    }
  }


}




void JHAnalyzerBase::MeasureMC_bChargeAcc(vector<Jet> vJets ){
  TString weight_sign_str= weight > 0 ? "_POS" : "_NEG";
  vector<double> vec_etabins = {0.0, 0.8, 1.6, 2., 2.5};
  vector<double> vec_ptbins = {20., 30., 50., 70., 100., 140.};
  double etabins[5]= {0.0, 0.8, 1.6, 2., 2.5};
  double etabins_all[2]= {0.0, 2.5};
  double ptbins[6]= {30.,50.,70.,100.,140.,1000.};
  const int NEtaBin = 4;
  const int NEtaBinAll = 1;
  const int NPtBin = 5;

  for(auto& this_jet : vJets){
    if(fabs(this_jet.partonFlavour())!=5) continue;
    if(this_jet.hadronFlavour()!=5) continue;
    TString flav= this_jet.partonFlavour() > 0 ? "bminus" : "bplus";
    double this_Eta = fabs(this_jet.Eta());
    double this_Pt = this_jet.Pt()>1000. ? 999. : this_jet.Pt();

    auto this_charge_and_id =GetMeasuredChargeAndID(this_jet,false);
    int this_charge=this_charge_and_id.first;
    int this_chargeid=this_charge_and_id.second;
    if(this_chargeid<0) continue;
    bool isMeasuredCorrect=false;
    if(this_jet.partonFlavour()*this_charge <0) isMeasuredCorrect=true; 
    
   
    if(this_chargeid<4){//SLT
      AnalyzerCore::FillHist("Jet_"+DataEra+"_acc_"+flav+"_chargeid"+std::to_string(this_chargeid)+"_denom", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_acc_"+flav+"_chargeid"+std::to_string(this_chargeid)+"_denom"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);
      if(isMeasuredCorrect){
	AnalyzerCore::FillHist("Jet_"+DataEra+"_acc_"+flav+"_chargeid"+std::to_string(this_chargeid)+"_num", this_Eta, this_Pt, fabs(weight), NEtaBinAll, etabins_all, NPtBin, ptbins);
	AnalyzerCore::FillHist("Jet_"+DataEra+"_acc_"+flav+"_chargeid"+std::to_string(this_chargeid)+"_num"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBinAll, etabins_all, NPtBin, ptbins);
      }
    }else{
      AnalyzerCore::FillHist("Jet_"+DataEra+"_acc_"+flav+"_chargeid"+std::to_string(this_chargeid)+"_denom", this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);
      AnalyzerCore::FillHist("Jet_"+DataEra+"_acc_"+flav+"_chargeid"+std::to_string(this_chargeid)+"_denom"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);
      if(isMeasuredCorrect){
	AnalyzerCore::FillHist("Jet_"+DataEra+"_acc_"+flav+"_chargeid"+std::to_string(this_chargeid)+"_num", this_Eta, this_Pt, fabs(weight), NEtaBin, etabins, NPtBin, ptbins);
	AnalyzerCore::FillHist("Jet_"+DataEra+"_acc_"+flav+"_chargeid"+std::to_string(this_chargeid)+"_num"+weight_sign_str, this_Eta, this_Pt, weight, NEtaBin, etabins, NPtBin, ptbins);
      }
    }
  }


}




vector<int> JHAnalyzerBase::Count_SLT(const Jet& this_Jet){
  int n_muonHigh=0;
  int n_muonLow=0;
  int n_electronHigh=0;
  int n_electronLow=0;
  int last_measured_charge=0;

  
  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    if(muon.DeltaR(this_Jet) > 0.4) continue;
    //if(muon.RelIso() > 10.) continue;
    //if(muon.Chi2()>10) continue;
    //if(muon.TrackerLayers()<1) continue;
    //if(muon.MatchedStations() <1) continue;
    //---v2608.2
    bool isGlobalMuon__OR__isTrackerMuon= muon.IsType(Muon::GlobalMuon) || muon.IsType(Muon::TrackerMuon);
    if(!isGlobalMuon__OR__isTrackerMuon) continue;

    SetMuonChargeScore(muon,this_Jet);
    int this_muon_coeff=GetMuonChargeScoreCoeff();// if pass HighCut -> +1 // if pass LowCut -> -1
    if(this_muon_coeff==1){
      n_muonHigh+=1;
      last_measured_charge=muon.Charge();
    }else if(this_muon_coeff==-1){
      n_muonLow+=1;
      last_measured_charge=-muon.Charge();
    }

  }//[end muon for loop]
  
  for(auto& electron : AllElectrons){
    if(electron.Pt() < 5.) continue;
    if(electron.DeltaR(this_Jet) > 0.4) continue;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    
    if(electron.NMissingHits() > 1) continue;//2608.2


    SetElectronChargeScore(electron,this_Jet);
    int this_electron_coeff=GetElectronChargeScoreCoeff();// if pass HighCut -> +1 // if pass LowCut -> -1
    if(this_electron_coeff==1){
      n_electronHigh+=1;
      last_measured_charge=electron.Charge();
    }else if(this_electron_coeff==-1){
      n_electronLow+=1;
      last_measured_charge=-electron.Charge();
    }

  }//[end electron for loop]

  vector<int> ret;
  ret.clear();
  ret.push_back(n_muonHigh);
  ret.push_back(n_muonLow);
  ret.push_back(n_electronHigh);
  ret.push_back(n_electronLow);
  ret.push_back(last_measured_charge);
  return ret;
}




vector<int> JHAnalyzerBase::Count_SLT_test_v2(const Jet& this_Jet){
  int n_muonHigh=0;
  int n_muonLow=0;
  int n_electronHigh=0;
  int n_electronLow=0;
  int last_measured_charge=0;

  
  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    if(muon.DeltaR(this_Jet) > 0.4) continue;
    //if(muon.RelIso() > 10.) continue;
    //if(muon.Chi2()>10) continue;
    //if(muon.TrackerLayers()<1) continue;
    //if(muon.MatchedStations() <1) continue;
    //---v2608.2
    bool isGlobalMuon__OR__isTrackerMuon= muon.IsType(Muon::GlobalMuon) || muon.IsType(Muon::TrackerMuon);
    if(!isGlobalMuon__OR__isTrackerMuon) continue;
    //---test v2
    if(muon.TrkIso()/muon.Pt()<0.1) continue;
    if(GetPt_wrt_Jet(muon,this_Jet)>4) continue;
    
    SetMuonChargeScore(muon,this_Jet);
    int this_muon_coeff=GetMuonChargeScoreCoeff();// if pass HighCut -> +1 // if pass LowCut -> -1
    if(this_muon_coeff==1){
      n_muonHigh+=1;
      last_measured_charge=muon.Charge();
    }else if(this_muon_coeff==-1){
      n_muonLow+=1;
      last_measured_charge=-muon.Charge();
    }

  }//[end muon for loop]
  
  for(auto& electron : AllElectrons){
    if(electron.Pt() < 5.) continue;
    if(electron.DeltaR(this_Jet) > 0.4) continue;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    
    if(electron.NMissingHits() > 1) continue;//2608.2

    //--testv2
    if(electron.TrkIso()/electron.Pt()<0.1) continue;
    if(GetPt_wrt_Jet(electron,this_Jet)>4) continue;

    SetElectronChargeScore(electron,this_Jet);
    int this_electron_coeff=GetElectronChargeScoreCoeff();// if pass HighCut -> +1 // if pass LowCut -> -1
    if(this_electron_coeff==1){
      n_electronHigh+=1;
      last_measured_charge=electron.Charge();
    }else if(this_electron_coeff==-1){
      n_electronLow+=1;
      last_measured_charge=-electron.Charge();
    }

  }//[end electron for loop]

  vector<int> ret;
  ret.clear();
  ret.push_back(n_muonHigh);
  ret.push_back(n_muonLow);
  ret.push_back(n_electronHigh);
  ret.push_back(n_electronLow);
  ret.push_back(last_measured_charge);
  return ret;
}




vector<double> JHAnalyzerBase::Get_bChargeTagID_MCEffs_SLT( int partonFlavour, double JetPt){
  
  if(IsDATA) return {1.,1.,1.,1.};
  if(abs(partonFlavour)!=5) return {1.,1.,1.,1.}; 
  if(JetPt<30) JetPt = 30.;
  if(JetPt>=140.) JetPt = 141.;
  double JetEta=1.;
  
  TString bsign= partonFlavour > 0 ? "bminus" : "bplus";
  vector<double> ret;
  ret.clear();
  
  //Jet_2018_Has_eH_eff_bplus_num
  //Jet_2018_eff_bplus_denom
  for (auto thisID : {"muH","muL","eH","eL"}) {    
    TString this_key = TString(thisID) + "__" + bsign;
    TH2D* this_hist=map_effhist_bchargeID_mcjet[this_key];
    int this_bin = this_hist->FindBin(fabs(JetEta),JetPt);
    double this_eff=1.;
    this_eff=this_hist->GetBinContent(this_bin);
    if(this_eff<=0.) this_eff = 1E-10;
    if(this_eff>=1.) this_eff = 1.-1E-10;
    ret.push_back(this_eff);
  }
  return ret;  
}

double JHAnalyzerBase::Get_SLTEff_Corr(const vector<Jet> &_v_Jet, const vector<bool> _v_Has_muH, const vector<bool> _v_Has_muL, const vector<bool> _v_Has_eH, const vector<bool> _v_Has_eL){
  //cout << "[JHAnalyzerBase::Get_SLTEff_Corr]" << endl;
  if(IsDATA) return 1.;
  unsigned int _nJet=_v_Jet.size();
  double ret=1.;
  for(unsigned int i=0;i<_nJet;i++){
    ret*=Get_SLTEff_Corr_givenJet(_v_Jet[i], _v_Has_muH[i], _v_Has_muL[i], _v_Has_eH[i], _v_Has_eL[i]);
  }
  if(!runSys) return ret;
  if(!runWeightBase) return ret;
  //cout << "central=" << ret << endl;
  //cout << "[JHAnalyzerBase::Get_SLTEff_Corr] runSys " << endl;
  //[!!Setup Syst!!]//
  //  enum SYSDIR{ k_central=0, k_uncorrUp, k_uncorrDown, k_corrUp, k_corrDown, nSYSDIR };
  
  for(int iPtBin=0;iPtBin<nPtBin;iPtBin++){
    for(int iSLT=0;iSLT<nSLT;iSLT++){
      //cout << "iPtBin=" << iPtBin << " iSLT=" << iSLT << endl;
      double this_ptslt_corrUp=1.;
      double this_ptslt_corrDown=1.;

      double this_ptslt_uncorr_bPlusUp=1.;
      double this_ptslt_uncorr_bPlusDown=1.;

      double this_ptslt_uncorr_bMinusUp=1.;
      double this_ptslt_uncorr_bMinusDown=1.;

      for(int i=0;i<_nJet;i++){
	//double JHAnalyzerBase::Get_SLTEff_Corr_givenJet(Jet& thisJet, bool Has_muH, bool Has_muL, bool Has_eH,bool Has_eL,
	//                                               JHAnalyzerBase::SYSDIR SystDir, JHAnalyzerBase::PtBin SystPtBin, JHAnalyzerBase::SLT SystID){
	if( abs(_v_Jet[i].partonFlavour()) !=5  ) continue;
	if( _v_Jet[i].hadronFlavour() !=5  ) continue;
	double this_central_givenJet=Get_SLTEff_Corr_givenJet(_v_Jet[i], _v_Has_muH[i], _v_Has_muL[i], _v_Has_eH[i], _v_Has_eL[i]);
        this_ptslt_corrUp*=Get_SLTEff_Corr_givenJet(_v_Jet[i], _v_Has_muH[i], _v_Has_muL[i], _v_Has_eH[i], _v_Has_eL[i], k_corrUp, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::SLT)iSLT);
	this_ptslt_corrDown*=Get_SLTEff_Corr_givenJet(_v_Jet[i], _v_Has_muH[i], _v_Has_muL[i], _v_Has_eH[i], _v_Has_eL[i], k_corrDown, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::SLT)iSLT);
        if( _v_Jet[i].partonFlavour()< 0){//var only for bplus
	  //cout << "[this is bplus] " << endl;
          this_ptslt_uncorr_bPlusUp*=Get_SLTEff_Corr_givenJet(_v_Jet[i], _v_Has_muH[i], _v_Has_muL[i], _v_Has_eH[i], _v_Has_eL[i], k_uncorrUp, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::SLT)iSLT);
	  this_ptslt_uncorr_bPlusDown*=Get_SLTEff_Corr_givenJet(_v_Jet[i], _v_Has_muH[i], _v_Has_muL[i], _v_Has_eH[i], _v_Has_eL[i], k_uncorrDown, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::SLT)iSLT);
	  //cout << "this_ptslt_uncorr_bPlusUp=" << this_ptslt_uncorr_bPlusUp << endl;
	  //cout << "this_ptslt_uncorr_bPlusDown=" << this_ptslt_uncorr_bPlusDown << endl;
	  this_ptslt_uncorr_bMinusUp*=this_central_givenJet;
	  this_ptslt_uncorr_bMinusDown*=this_central_givenJet;
        }else if( _v_Jet[i].partonFlavour() > 0){//var only for bminus
	  //cout << "[this is bminus] " << endl;
	  this_ptslt_uncorr_bMinusUp*=Get_SLTEff_Corr_givenJet(_v_Jet[i], _v_Has_muH[i], _v_Has_muL[i], _v_Has_eH[i], _v_Has_eL[i], k_uncorrUp, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::SLT)iSLT);
	  this_ptslt_uncorr_bMinusDown*=Get_SLTEff_Corr_givenJet(_v_Jet[i], _v_Has_muH[i], _v_Has_muL[i], _v_Has_eH[i], _v_Has_eL[i], k_uncorrDown, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::SLT)iSLT);
	  //cout << "this_ptslt_uncorr_bMinusUp=" << this_ptslt_uncorr_bMinusUp << endl;
	  //cout << "this_ptslt_uncorr_bMinusDown=" << this_ptslt_uncorr_bMinusDown << endl;
	  this_ptslt_uncorr_bPlusUp*=this_central_givenJet; // if bminus, no variation by bPlus-sourced syst
	  this_ptslt_uncorr_bPlusDown*=this_central_givenJet;
        }
      }//[end] jet loop
      if(ret>0){
        arr_r_bChargeID_SLT_CorrUp[iSLT][iPtBin]=this_ptslt_corrUp/ret;
        arr_r_bChargeID_SLT_CorrDown[iSLT][iPtBin]=this_ptslt_corrDown/ret;

	arr_r_bChargeID_SLT_UnCorr_bPlusUp[iSLT][iPtBin]=this_ptslt_uncorr_bPlusUp/ret;
	arr_r_bChargeID_SLT_UnCorr_bPlusDown[iSLT][iPtBin]=this_ptslt_uncorr_bPlusDown/ret;

        arr_r_bChargeID_SLT_UnCorr_bMinusUp[iSLT][iPtBin]=this_ptslt_uncorr_bMinusUp/ret;
        arr_r_bChargeID_SLT_UnCorr_bMinusDown[iSLT][iPtBin]=this_ptslt_uncorr_bMinusDown/ret;
      }else{

        arr_r_bChargeID_SLT_CorrUp[iSLT][iPtBin]=1.;
        arr_r_bChargeID_SLT_CorrDown[iSLT][iPtBin]=1.;

        arr_r_bChargeID_SLT_UnCorr_bPlusUp[iSLT][iPtBin]=1.;
        arr_r_bChargeID_SLT_UnCorr_bPlusDown[iSLT][iPtBin]=1.;

        arr_r_bChargeID_SLT_UnCorr_bMinusUp[iSLT][iPtBin]=1.;
        arr_r_bChargeID_SLT_UnCorr_bMinusDown[iSLT][iPtBin]=1.;

      }
    }
  }//[end]arr_r_bChargeID_Jet_CorrUp/Down
  return ret;

  

  
}


double JHAnalyzerBase::Get_SLTEff_Corr_givenJet(const Jet& thisJet, const bool Has_muH, const bool Has_muL, const bool Has_eH, const bool Has_eL,
						JHAnalyzerBase::SYSDIR SystDir, JHAnalyzerBase::PtBin SystPtBin, JHAnalyzerBase::SLT SystID){
  //cout << "[JHAnalyzerBase::Get_SLTEff_Corr_givenJet]" << endl;
  if(IsDATA) return 1.;
  int this_partonFlavour=thisJet.partonFlavour();
  if(abs(this_partonFlavour)!=5) return 1.;
  if(thisJet.hadronFlavour()!=5) return 1.;

  //----Get ptbin----//
  double thisJetPt= thisJet.Pt();
  JHAnalyzerBase::PtBin thisJetPtBin=nPtBin;
  if(thisJetPt<50.){
    thisJetPtBin=kPT30To50;
  }else if(thisJetPt<70.){
    thisJetPtBin=kPT50To70;
  }else if(thisJetPt<100.){
    thisJetPtBin=kPT70To100;
  }else if(thisJetPt<140.){
    thisJetPtBin=kPT100To140;
  }else{
    thisJetPtBin=kPT140ToInf;
  }
  vector<double> v_mceff_slt = JHAnalyzerBase::Get_bChargeTagID_MCEffs_SLT(this_partonFlavour, thisJetPt);
  //vector<int> JHAnalyzerBase::Count_SLT(Jet& this_Jet){


  JetOrigin this_origin = (this_partonFlavour > 0) ? k_bminus : k_bplus;
  /*
  ///---TEST---//
  cout <<" -----TEST----" << endl;
  cout << "SystDir=" << SystDir << endl;
  cout << "SystPtBin=" << SystPtBin << endl;
  cout << "SystID=" << SystID << endl;
  cout << "thisJet.partonFlavour()="<<thisJet.partonFlavour()<<endl;
  cout << "thisJetPt=" << thisJetPt << endl;
  cout << "this_origin(0=k_plus OR 1=k_minus)=>" <<this_origin<<endl;
  cout << "Has_muH,Has_muL,Has_eH,Has_eL=" << Has_muH<<Has_muL<<Has_eH<<Has_eL << endl;
  */
  //final corr = data/mc = corr/mc 
  double nume=1.;//product of all corrected eff
  double deno=1.;//product of all mc eff
  
  //SF_bChargeTagID_SLT[k_bminus][k_eL][kPT140ToInf][k_corrDown]=0.9447710677457404;

  vector<bool> v_slt={Has_muH,Has_muL,Has_eH,Has_eL};
  for(int i_slt=0;i_slt<4;i_slt++){
    bool this_SLT = v_slt[i_slt];
    if(this_SLT){// multiplying SF only
      //cout << "apply iSLT=" << i_slt << " -> Has this SLT" << endl;
      nume *= SF_bChargeTagID_SLT[this_origin][i_slt][thisJetPtBin][k_central];
    }else{// 1- eff
      //cout << "apply iSLT=" << i_slt << " -> No this SLT" << endl;
      nume *= (1.- SF_bChargeTagID_SLT[this_origin][i_slt][thisJetPtBin][k_central]*v_mceff_slt[i_slt]);
      deno *= (1.- v_mceff_slt[i_slt]);    
    }
  }

  double ret=(deno > 0 && nume >= 0)  ? nume/deno : 1.;
  if(SystDir==k_central) return ret; // central value
  if(SystPtBin!=thisJetPtBin) return ret; // not varied by this nuisance->return central value
  
  //----variation by Syst----//  
  //double corr_syst =1.;
  //double corr_central =1.;
  
  //  enum SYSDIR{ k_central=0, k_uncorrUp, k_uncorrDown, k_corrUp, k_corrDown, nSYSDIR };
  //cout << "SF syst , SF centerl ->" << SF_bChargeTagID_SLT[this_origin][SystID][thisJetPtBin][SystDir] << "," << SF_bChargeTagID_SLT[this_origin][SystID][thisJetPtBin][k_central] << endl;
  //cout << "SF syst / SF centerl ->" << SF_bChargeTagID_SLT[this_origin][SystID][thisJetPtBin][SystDir]/SF_bChargeTagID_SLT[this_origin][SystID][thisJetPtBin][k_central] << endl;
  if(v_slt[SystID]){//has this syst slt
    //cout << "syst var, has this  syst slt -> " << SystID << endl; 
    double this_nume=SF_bChargeTagID_SLT[this_origin][SystID][thisJetPtBin][SystDir];
    if(this_nume<= 0.) return ret;      
    double this_deno= SF_bChargeTagID_SLT[this_origin][SystID][thisJetPtBin][k_central];
    if(this_deno <= 0.) return ret;
    
    return ret*this_nume/this_deno;  
  }else{// not having this syst slt -> variation of untagged prob.
    //cout << "syst var, No this  syst slt -> " << SystID << endl;
    //corr_syst    = (1.-SF_bChargeTagID_SLT[this_origin][SystID][thisJetPtBin][SystDir]*v_mceff_slt[SystID])/(1.-v_mceff_slt[SystID]);
    double this_nume=1.-SF_bChargeTagID_SLT[this_origin][SystID][thisJetPtBin][SystDir]*v_mceff_slt[SystID];
    if(this_nume <= 0.) return ret;
    //corr_central = (1.-SF_bChargeTagID_SLT[this_origin][SystID][thisJetPtBin][k_central]*v_mceff_slt[SystID])/(1.-v_mceff_slt[SystID]);
    double this_deno = 1.-SF_bChargeTagID_SLT[this_origin][SystID][thisJetPtBin][k_central]*v_mceff_slt[SystID];
    if(this_deno <= 0.) return ret;
    
    return ret*this_nume/this_deno;
  }
    
  
  return ret;

  //  enum SLT { k_muH=0, k_muL, k_eH, k_eL, nSLT};

}


//



double JHAnalyzerBase::Get_bChargeTagID_MCEffs_jH(int partonFlavour, double JetPt, double JetEta){

  if(IsDATA) return 1.;
  if(abs(partonFlavour)!=5) return 1.;
  if(JetPt<30) JetPt = 30.;
  if(JetPt>=140.) JetPt = 141.;
  JetEta=fabs(JetEta);
  if(JetEta>2.5) return 1.;
  TString bsign= partonFlavour > 0 ? "bminus" : "bplus";


  //Jet_2018_Has_eH_eff_bplus_num
  //Jet_2018_eff_bplus_denom
  TString this_key = "jH__" + bsign;
  TH2D* this_hist=map_effhist_bchargeID_mcjet[this_key];
  int this_bin = this_hist->FindBin(JetEta,JetPt);
  double this_eff=1.;
  this_eff=this_hist->GetBinContent(this_bin);
  if(this_eff<=0.) this_eff = 1E-10;
  if(this_eff>=1.) this_eff = 1.-1E-10;
  
  
  return this_eff;

}
double JHAnalyzerBase::Get_HighScoreChargeTagID_Eff_Corr(const vector<Jet> &_v_Jet, const vector<bool> _v_pass_jH){
  if(IsDATA) return 1.;
  unsigned int _nJet=_v_Jet.size();
  double ret=1.;
  for(unsigned int i=0;i<_nJet;i++){
    ret*=Get_HighScoreChargeTagID_Eff_Corr_givenJet(_v_Jet[i], _v_pass_jH[i]);
  }
  if(!runSys) return ret;
  if(!runWeightBase) return ret;
  //[!!Setup Syst!!]//
  
  //----arr_r_bChargeID_Jet_CorrUp/Down--// arr_r_bChargeID_Jet_CorrUp[nPtBin][nEtaBin]
  //----arr_r_bChargeID_Jet_UnCorr_bPlusUp/Down---// 
  //----arr_r_bChargeID_Jet_UnCorr_bMinusUp/Down---//
  
  //  enum SYSDIR{ k_central=0, k_uncorrUp, k_uncorrDown, k_corrUp, k_corrDown, nSYSDIR };

  for(unsigned int iPtBin=0;iPtBin<nPtBin;iPtBin++){
    for(unsigned int iEtaBin=0;iEtaBin<nEtaBin;iEtaBin++){
      double this_pteta_corrUp=1.;
      double this_pteta_corrDown=1.;

      double this_pteta_uncorr_bPlusUp=1.;
      double this_pteta_uncorr_bPlusDown=1.;

      double this_pteta_uncorr_bMinusUp=1.;
      double this_pteta_uncorr_bMinusDown=1.;
      
      for(unsigned int i=0;i<_nJet;i++){
        double this_central_givenJet=Get_HighScoreChargeTagID_Eff_Corr_givenJet(_v_Jet[i], _v_pass_jH[i]);
	
	
	this_pteta_corrUp*=Get_HighScoreChargeTagID_Eff_Corr_givenJet(_v_Jet[i], _v_pass_jH[i], k_corrUp, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::EtaBin)iEtaBin);
	this_pteta_corrDown*=Get_HighScoreChargeTagID_Eff_Corr_givenJet(_v_Jet[i], _v_pass_jH[i], k_corrDown, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::EtaBin)iEtaBin);

	if( _v_Jet[i].partonFlavour() < 0){//bplus
	  this_pteta_uncorr_bPlusUp*=Get_HighScoreChargeTagID_Eff_Corr_givenJet(_v_Jet[i], _v_pass_jH[i], k_uncorrUp, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::EtaBin)iEtaBin);
	  this_pteta_uncorr_bPlusDown*=Get_HighScoreChargeTagID_Eff_Corr_givenJet(_v_Jet[i], _v_pass_jH[i], k_uncorrDown, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::EtaBin)iEtaBin);
	  this_pteta_uncorr_bMinusUp=this_central_givenJet;
	  this_pteta_uncorr_bMinusDown=this_central_givenJet;
	}else{//bminus
	  this_pteta_uncorr_bMinusUp*=Get_HighScoreChargeTagID_Eff_Corr_givenJet(_v_Jet[i], _v_pass_jH[i], k_corrUp, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::EtaBin)iEtaBin);
	  this_pteta_uncorr_bMinusDown*=Get_HighScoreChargeTagID_Eff_Corr_givenJet(_v_Jet[i], _v_pass_jH[i], k_corrDown, (JHAnalyzerBase::PtBin)iPtBin, (JHAnalyzerBase::EtaBin)iEtaBin);
	  this_pteta_uncorr_bPlusUp=this_central_givenJet;
	  this_pteta_uncorr_bPlusDown=this_central_givenJet;
	}
      }
      if(ret>0){
	arr_r_bChargeID_Jet_CorrUp[iPtBin][iEtaBin]=this_pteta_corrUp/ret;
	arr_r_bChargeID_Jet_CorrDown[iPtBin][iEtaBin]=this_pteta_corrDown/ret;

	arr_r_bChargeID_Jet_UnCorr_bPlusUp[iPtBin][iEtaBin]=this_pteta_uncorr_bPlusUp/ret;
	arr_r_bChargeID_Jet_UnCorr_bPlusDown[iPtBin][iEtaBin]=this_pteta_uncorr_bPlusDown/ret;

	arr_r_bChargeID_Jet_UnCorr_bMinusUp[iPtBin][iEtaBin]=this_pteta_uncorr_bMinusUp/ret;
	arr_r_bChargeID_Jet_UnCorr_bMinusDown[iPtBin][iEtaBin]=this_pteta_uncorr_bMinusDown/ret;	
      }else{

	arr_r_bChargeID_Jet_CorrUp[iPtBin][iEtaBin]=1.;
	arr_r_bChargeID_Jet_CorrDown[iPtBin][iEtaBin]=1.;

	arr_r_bChargeID_Jet_UnCorr_bPlusUp[iPtBin][iEtaBin]=1.;
	arr_r_bChargeID_Jet_UnCorr_bPlusDown[iPtBin][iEtaBin]=1.;

	arr_r_bChargeID_Jet_UnCorr_bMinusUp[iPtBin][iEtaBin]=1.;
	arr_r_bChargeID_Jet_UnCorr_bMinusDown[iPtBin][iEtaBin]=1.;
	
      }
    }
  }//[end]arr_r_bChargeID_Jet_CorrUp/Down

  return ret;
  

  
}///[end]
//JHAnalyzerBase::Get_HighScoreChargeTagID_Eff_Corr

double JHAnalyzerBase::Get_HighScoreChargeTagID_Eff_Corr_givenJet(const Jet& thisJet, const bool pass_jH,
								  JHAnalyzerBase::SYSDIR SystDir, JHAnalyzerBase::PtBin SystPtBin, JHAnalyzerBase::EtaBin SystEtaBin){
  if(IsDATA) return 1.;
  int this_partonFlavour=thisJet.partonFlavour();
  if(abs(this_partonFlavour)!=5) return 1.;
  if(thisJet.hadronFlavour()!=5) return 1.;
  JetOrigin this_origin = (this_partonFlavour > 0) ? k_bminus : k_bplus;
  
  double thisJetPt= thisJet.Pt();
  double thisJetEta= fabs(thisJet.Eta());
  JHAnalyzerBase::PtBin thisJetPtBin=nPtBin;
  if(thisJetPt<50.){
    thisJetPtBin=kPT30To50;
  }else if(thisJetPt<70.){
    thisJetPtBin=kPT50To70;
  }else if(thisJetPt<100.){
    thisJetPtBin=kPT70To100;
  }else if(thisJetPt<140.){
    thisJetPtBin=kPT100To140;
  }else{
    thisJetPtBin=kPT140ToInf;
  }
  JHAnalyzerBase::EtaBin thisJetEtaBin=nEtaBin;
  if(thisJetEta<0.8){
    thisJetEtaBin=kEta0To0p8;
  }else if(thisJetEta<1.6){
    thisJetEtaBin=kEta0p8To1p6;
  }else if(thisJetEta<2.0){
    thisJetEtaBin=kEta1p6To2;
  }else if(thisJetEta<2.5){
    thisJetEtaBin=kEta2To2p5;
  }else{
    return 1.;
  }
  double ret=1.;

  JHAnalyzerBase::SYSDIR this_DIR=SystDir;
  if(SystPtBin!=thisJetPtBin) this_DIR=k_central;
  if(SystEtaBin!=thisJetEtaBin) this_DIR=k_central;

  
  if(pass_jH){
    //SF_bChargeTagID_Jet[k_bminus][kPT140ToInf][kEta2To2p5][k_corrDown]=1.015160887182364;
    ret=SF_bChargeTagID_Jet[this_origin][thisJetPtBin][thisJetEtaBin][this_DIR];
  }else{// 1- eff
    double this_mceff=Get_bChargeTagID_MCEffs_jH(this_partonFlavour,thisJetPt,thisJetEta);
    double nume = 1.- SF_bChargeTagID_Jet[this_origin][thisJetPtBin][thisJetEtaBin][this_DIR]*this_mceff;
    double deno = 1.- this_mceff;
    ret= (deno > 0. && nume >=0) ? nume/deno : 1.;
  }
  return ret;

}


pair<int,int> JHAnalyzerBase::GetMeasuredChargeAndID(const Jet& thisJet, bool ApplyAccCorr){
  int thisChargeID=-1;
  ////(1) Count SLT
  std::vector<int> v_nSLT=Count_SLT(thisJet);
  int n_muH=v_nSLT[0];
  int n_muL=v_nSLT[1];
  int n_eH=v_nSLT[2];
  int n_eL=v_nSLT[3];
  int measured_charge=v_nSLT[4];
  ////(2) Apply SLT Eff and jH Eff Corr
  double weight_SLT=Get_SLTEff_Corr({thisJet},{n_muH>0},{n_muL>0},{n_eH>0},{n_eL>0});
  weight*=weight_SLT;

  ////(3) Get measuredCharge
  if(n_muH==1 && n_muL==0 && n_eH==0 && n_eL==0){
    thisChargeID=0;
  }
  else if(n_muH==0 && n_muL==1 && n_eH==0 && n_eL==0){
    thisChargeID=1;
  }
  else if(n_muH==0 && n_muL==0 && n_eH==1 && n_eL==0){
    thisChargeID=2;
  }
  else if(n_muH==0 && n_muL==0 && n_eH==0 && n_eL==1){
    thisChargeID=3;
  }
  else if(n_muH==0 && n_muL==0 && n_eH==0 && n_eL==0){//jH or jOthers
    SetJetChargeScore(thisJet);
    double jetscore=GetJetChargeScore();
    double jetcharge_float=thisJet.Charge();
    measured_charge=(jetcharge_float>0) ? +1 : (jetcharge_float < 0) ? -1 : 0;
    int jetcharge_coeff=GetJetChargeScoreCoeff();
    thisChargeID = (jetcharge_coeff==1) ? 4 : 5;
    double weight_HighScoreJet=Get_HighScoreChargeTagID_Eff_Corr({thisJet},{jetcharge_coeff==1});
    weight*=weight_HighScoreJet;    
  }else{
    return {0,0};
  }
  if(ApplyAccCorr) weight*=GetChargeAccCorr(thisJet,thisChargeID,measured_charge);
  return {measured_charge,thisChargeID};
  
  
}

double JHAnalyzerBase::GetChargeAccCorr(const Jet& thisJet, int thisChargeID, int measured_charge){
  if(IsDATA) return 1.;
  int this_partonFlavour=thisJet.partonFlavour();
  if(abs(this_partonFlavour)!=5) return 1.;
  if(thisJet.hadronFlavour()!=5) return 1.;
  if(measured_charge==0) return 1.;
  bool IsMeasuredCorrectly=false;
  if(this_partonFlavour *measured_charge <0 ) IsMeasuredCorrectly = true;
  JetOrigin thisJetOrigin= (this_partonFlavour < 0) ? k_bplus : k_bminus;

  double ret=1.;
  double thisJetPt=thisJet.Pt();
  JHAnalyzerBase::PtBin thisJetPtBin=nPtBin;
  if(thisJetPt<50.){
    thisJetPtBin=kPT30To50;
  }else if(thisJetPt<70.){
    thisJetPtBin=kPT50To70;
  }else if(thisJetPt<100.){
    thisJetPtBin=kPT70To100;
  }else if(thisJetPt<140.){
    thisJetPtBin=kPT100To140;
  }else{
    thisJetPtBin=kPT140ToInf;
  }

  double mc_acc=Get_bChargeAcc_MC(this_partonFlavour,thisChargeID,thisJet.Pt(),thisJet.Eta());
  if(mc_acc<0) return 1.;
  if(mc_acc>1) return 0.;      

  double SF_acc=1.;

  //------SLT-----//
  if(thisChargeID<4){ //SLT//
    //SF_bChargeAcc_SLT[_ib][_il][_ip][_is]
    //SF_bChargeAcc_Jet[_ib2][_ij2][_ip2][_ie2][_is2] 
    SF_acc= SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_central];
    if(SF_acc*mc_acc>1) return 1.;
    if(SF_acc*mc_acc<0) return 1.;

    if(IsMeasuredCorrectly){
      ret*=SF_acc;
      if(runSys && runWeightBase){
	arr_r_bChargeAcc_SLT_CorrUp[thisChargeID][thisJetPtBin] *= SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_corrUp]/SF_acc;
	arr_r_bChargeAcc_SLT_CorrDown[thisChargeID][thisJetPtBin] *= SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_corrDown]/SF_acc;
	if(this_partonFlavour<0){
	  arr_r_bChargeAcc_SLT_UnCorr_bPlusUp[thisChargeID][thisJetPtBin] *= SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_uncorrUp]/SF_acc;
	  arr_r_bChargeAcc_SLT_UnCorr_bPlusDown[thisChargeID][thisJetPtBin] *= SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_uncorrDown]/SF_acc;
	}else{
	  arr_r_bChargeAcc_SLT_UnCorr_bMinusUp[thisChargeID][thisJetPtBin] *= SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_uncorrUp]/SF_acc;
	  arr_r_bChargeAcc_SLT_UnCorr_bMinusDown[thisChargeID][thisJetPtBin] *= SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_uncorrDown]/SF_acc;
	}
      }//if sys
      
    }//measured correctly
    else{
      ret *= (1-mc_acc*SF_acc)/(1-mc_acc);
      if(runSys && runWeightBase){
	arr_r_bChargeAcc_SLT_CorrUp[thisChargeID][thisJetPtBin] *= (1-mc_acc*SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_corrUp])/(1-mc_acc*SF_acc);
	arr_r_bChargeAcc_SLT_CorrDown[thisChargeID][thisJetPtBin] *= (1-mc_acc*SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_corrDown])/(1-mc_acc*SF_acc);
	if(this_partonFlavour<0){
	  arr_r_bChargeAcc_SLT_UnCorr_bPlusUp[thisChargeID][thisJetPtBin] *= (1-mc_acc*SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_uncorrUp])/(1-mc_acc*SF_acc);
	  arr_r_bChargeAcc_SLT_UnCorr_bPlusDown[thisChargeID][thisJetPtBin] *= (1-mc_acc*SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_uncorrDown])/(1-mc_acc*SF_acc);
	}else{
	  arr_r_bChargeAcc_SLT_UnCorr_bMinusUp[thisChargeID][thisJetPtBin] *= (1-mc_acc*SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_uncorrUp])/(1-mc_acc*SF_acc);
	  arr_r_bChargeAcc_SLT_UnCorr_bMinusDown[thisChargeID][thisJetPtBin] *= (1-mc_acc*SF_bChargeAcc_SLT[thisJetOrigin][thisChargeID][thisJetPtBin][k_uncorrDown])/(1-mc_acc*SF_acc);
	}
      }//if sys
    }//if measured oppositely

    ///-----Jet Charge Type -----//
  }else{//Jet Charge
    double thisJetEta=fabs(thisJet.Eta());
    JHAnalyzerBase::EtaBin thisJetEtaBin=nEtaBin;
    if(thisJetEta<0.8){
      thisJetEtaBin=kEta0To0p8;
    }else if(thisJetEta<1.6){
      thisJetEtaBin=kEta0p8To1p6;
    }else if(thisJetEta<2.0){
      thisJetEtaBin=kEta1p6To2;
    }else if(thisJetEta<2.5){
      thisJetEtaBin=kEta2To2p5;
    }
    SF_acc= SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_central];
    if(SF_acc*mc_acc>1) return 1.;
    if(SF_acc*mc_acc<0) return 1.;

    if(IsMeasuredCorrectly){
      ret*=SF_acc;
      if(runSys && runWeightBase){
        arr_r_bChargeAcc_Jet_CorrUp[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_corrUp]/SF_acc;
        arr_r_bChargeAcc_Jet_CorrDown[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_corrDown]/SF_acc;
        if(this_partonFlavour<0){
          arr_r_bChargeAcc_Jet_UnCorr_bPlusUp[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_uncorrUp]/SF_acc;
          arr_r_bChargeAcc_Jet_UnCorr_bPlusDown[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_uncorrDown]/SF_acc;
        }else{
          arr_r_bChargeAcc_Jet_UnCorr_bMinusUp[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_uncorrUp]/SF_acc;
          arr_r_bChargeAcc_Jet_UnCorr_bMinusDown[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_uncorrDown]/SF_acc;
        }
      }//if sys
      
    }//IsMeasuredCorrectly
    else{
      ret *= (1-mc_acc*SF_acc)/(1-mc_acc);

      if(runSys && runWeightBase){
	
	arr_r_bChargeAcc_Jet_CorrUp[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= (1-mc_acc*SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_corrUp])/(1-mc_acc*SF_acc);
	arr_r_bChargeAcc_Jet_CorrDown[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= (1-mc_acc*SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_corrDown])/(1-mc_acc*SF_acc);
	if(this_partonFlavour<0){
	  arr_r_bChargeAcc_Jet_UnCorr_bPlusUp[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= (1-mc_acc*SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_uncorrUp])/(1-mc_acc*SF_acc);
	  arr_r_bChargeAcc_Jet_UnCorr_bPlusDown[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= (1-mc_acc*SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_uncorrDown])/(1-mc_acc*SF_acc);
	}else{
	  arr_r_bChargeAcc_Jet_UnCorr_bMinusUp[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= (1-mc_acc*SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_uncorrUp])/(1-mc_acc*SF_acc);
	  arr_r_bChargeAcc_Jet_UnCorr_bMinusDown[thisChargeID-4][thisJetPtBin][thisJetEtaBin] *= (1-mc_acc*SF_bChargeAcc_Jet[thisJetOrigin][thisChargeID-4][thisJetPtBin][thisJetEtaBin][k_uncorrDown])/(1-mc_acc*SF_acc);
	}
      }//if sys
      
    }//not IsMeasuredCorrectly
    
  }

    
  return ret;
}
///for new lepton veto
double JHAnalyzerBase::Get_bChargeAcc_MC(int partonFlavour, int thisChargeID,double JetPt, double JetEta){
  if(IsDATA) return 1.;
  if(abs(partonFlavour)!=5) return 1.;
  if(JetPt<30) JetPt = 30.;
  if(JetPt>=140.) JetPt = 141.;
  JetEta=fabs(JetEta);
  if(JetEta>2.5) return 1.;
  TString bsign= partonFlavour > 0 ? "bminus" : "bplus";
  TString ChargeAccID=bChargeAccIDName[thisChargeID];
  TString this_key = ChargeAccID + "__" + bsign;
  TH2D* this_hist=map_acchist_bchargeID_mcjet[this_key];
  int this_bin = this_hist->FindBin(JetEta,JetPt);
  double this_acc=1.;
  this_acc=this_hist->GetBinContent(this_bin);
  if(this_acc<=0.) this_acc = 1E-10;
  if(this_acc>=1.) this_acc = 1.-1E-10;
  return this_acc;


}


bool JHAnalyzerBase::HasVetoLepton_NotTightLeps_NotWithinJets(const vector<int>& _v_tightmuonidx, const vector<int>& _v_tightelectronidx, const TLorentzVector* _jet1, const TLorentzVector* _jet2){
  //bool HasVetoLep=false;
  double ptcut_muveto=10.;
  double etacut_muveto=2.4;
  double ptcut_elveto=15.;
  double etacut_elveto=2.5;



  //---Veto Electron first
  int this_elidx=-1;
  for(const auto& electron : AllElectrons){
    this_elidx+=1;
    //pass pt cut
    if(electron.Pt() < ptcut_elveto) continue;
    //pass eta cut
    if(fabs(electron.Eta()) > etacut_elveto) continue;
    //pass vetoid
    if(!electron.PassID("passVetoID")) continue;
    //not tight electron
    bool is_tight=false;
    for(const int this_tightelectronidx : _v_tightelectronidx){
      if(this_tightelectronidx == this_elidx){
	is_tight=true;
	break;
      }
    }
    if(is_tight) continue;


    //not in selected jets
    if(_jet1->DeltaR(electron) < 0.4) continue;
    if(_jet2 != nullptr && _jet2->DeltaR(electron) < 0.4) continue;
    
    return true;
  }//end of electron loop
  //if(HasVetoLep) return true;

  //---Next, Veto Muon
  int this_muidx=-1;
  for(const auto& muon : AllMuons){
    this_muidx+=1;
    //pass pt cut
    if(muon.Pt() < ptcut_muveto) continue;
    //pass eta cut
    if(fabs(muon.Eta()) > etacut_muveto) continue;
    //pass loose id
    if (!muon.PassID("POGLoose")) continue;
    //pass trkiso loose
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //not tight muon
    bool is_tight=false;
    for(const int this_tightmuonidx : _v_tightmuonidx){
      if(this_tightmuonidx == this_muidx){
	is_tight=true;
	break;
      }
    }
    if(is_tight) continue;


    //not in selected jets
    
    //not in selected jets
    if(_jet1->DeltaR(muon) < 0.4) continue;
    if(_jet2 != nullptr && _jet2->DeltaR(muon) < 0.4) continue;

  
    
    
    //if the muon survives applying all conditions ->additional lepton...->veto
    //HasVetoLep=true;
    return true;
  }//end of muon loop
  //if(HasVetoLep) return true;
  
  return false;
}
