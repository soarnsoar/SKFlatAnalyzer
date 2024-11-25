#include "TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch.h"

TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch(){
  //runSys=true;
  //jetpog_etabins
  //jetpog_ptbins
}

TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::~TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch(){
  //==== Destructor of this Analyzer

}

void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::initializeAnalyzer(){
  cout << "[TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::initializeAnalyzer]" << endl;
  //TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch
  if(HasFlag("use_beff")){
    //----use this analyzer specific btag mc eff----//
    //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch_"+MCSample+".root");
  }


  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupSingleLeptonChannel();
  noveto=false;
  if(HasFlag("noveto")){
    noveto=true;
  }
  HcbCR=false;
  if(HasFlag("HcbCR")){
    HcbCR=true;
  }

  //FlavourMatchBase=false;
  //if(HasFlag("FlavourMatchBase")){
  //  FlavourMatchBase=true;
  //}

  LeptonPt50=false;
  if(HasFlag("LeptonPt50")){
    LeptonPt50=true;
  }

  njet4=false;
  if(HasFlag("njet4")){
    njet4=true;
  }

  //LoadTTSemilepJetAssignmentTool("1.0");
  //charge
  TString v_muonScore="2409.2";
  TString v_electronScore="2409.2";
  TString v_jetScore="2409.2";
  bool apply_dnncut=true;
  LoadChargeScoreTool(v_muonScore,v_electronScore,v_jetScore,apply_dnncut);




  //Jet Assignment Tool
  InitJetAssigenChi2Fitter();



  //
  ForBinning=false;
  if(HasFlag("ForBinning")){
    ForBinning=true;
  }

  /*
  ///------MuonChargeOnly
  MuonChargeOnly=false;
  if(HasFlag("MuonChargeOnly")){
    MuonChargeOnly=true;
  }
  //-------Electron
  ElectronChargeOnly=false;
  if(HasFlag("ElectronChargeOnly")){
    ElectronChargeOnly=true;
  }
  //------Jet
  JetChargeOnly=false;
  if(HasFlag("JetChargeOnly")){
    JetChargeOnly=true;
  }
  
  */



  simplecat=false;
  if(HasFlag("simplecat")){
    simplecat=true;
  }


  ForMeasure=false;
  if(HasFlag("ForMeasure")){
    ForMeasure=true;
  }






  //TurnOnFillHist=1;




}


void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::SetMuon(const Muon& _l1){
  mu1=_l1;
}

bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::CheckIsMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;

  vector<Muon> v_muon;
  if(LeptonPt50){
    v_muon=noveto ? GetSingleMuRecoNoVeto(50.) : GetSingleMuReco(50.);
  }
  else{
    v_muon=noveto ? GetSingleMuRecoNoVeto(TriggerSafeCut_muon1) : GetSingleMuReco(TriggerSafeCut_muon1);
    //vector<Electron> JHAnalyzerBase::GetSingleElReco(double ptmin, double etacut, double ptveto, double ptveto2, double etacut2){//ptveto2 and etacut2 -->for add. muon
  }
  if( v_muon.size()!=1) return 0;
  SetMuon(v_muon[0]);

  return 1;
}  

void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::SetElectron(const Electron& _l1){
  el1=_l1;
}


bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::CheckIsElectronChannel(){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  vector<Electron> v_electron;
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  if(LeptonPt50){
    v_electron=noveto ? GetSingleElRecoNoVeto(50.) : GetSingleElReco(50.);
  }
  else{
    v_electron=noveto ? GetSingleElRecoNoVeto(TriggerSafeCut_electron1) : GetSingleElReco(TriggerSafeCut_electron1);
  }
  if( v_electron.size()!=1) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  SetElectron(v_electron[0]);
  return 1;
}  

void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  //Muon
  if(IsMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }
  
}

void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunReco(){

  IsMuonChannel=false;
  IsElectronChannel=false;


  IsMuonChannel=CheckIsMuonChannel();
  if(!IsMuonChannel) IsElectronChannel=CheckIsElectronChannel();





  LepCh="";
  if(IsMuonChannel){
    vtW=GetTransverseVector(mu1)+CurrentMET;
    LepCh="Muon";
    l1=mu1;
  }
  else if(IsElectronChannel){
    vtW=GetTransverseVector(el1)+CurrentMET;
    LepCh="Electron";
    l1=el1;
  }  

  else{
    return;
  }

  //---if this job is for btag mc eff measure, measure eff. before getjets
  if(measure_btageff){
    Measure_MCbtagEff();
    return;
  }



  LepSign= l1.Charge() > 0 ? "Plus" : "Minus";
  //----Jet---//
  v_tightlep={l1};
  v_tightjet=GetTightJet(v_tightlep,30,2.4);
  v_bjetidx=GetBJetIdx(v_tightjet);
  nbjet=v_bjetidx.size();
  if(nbjet != 2) return;
  njet=v_tightjet.size();
  if(v_tightjet.size()<4) return;
  if(njet4 && v_tightjet.size()!=4) return;
  //--Now Objects are ready--//
  SetEventWeight();


  Run();

}
void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::Run(){
  iblep=-1;
  ibhad=-1;
  iq1=-1;
  iq2=-1;
  vz_fit=0.0;
  ////Minimal Chi2 Method - kin fitter
  pair<vector<int>,double> v_jetidxset_and_vz_chi2=GetJetIndexSet_Chi2(l1, CurrentMET, v_tightjet, v_bjetidx, HcbCR);

  //vector<int> v_jetidxset_dnn=GetJetIndexSet_DNN();
  //[0]=ib1 = bLep cand's v_bjet index
  //[1]=ib2 = bHad cand's v_bjet index
  //[2]=iq1 = one of light quark candiate v_tightjet index
  //[3]=iq2 = one of light quark candiate v_tightjet index
  iblep=v_jetidxset_and_vz_chi2.first[0];
  ibhad=v_jetidxset_and_vz_chi2.first[1];
  iq1=v_jetidxset_and_vz_chi2.first[2];
  iq2=v_jetidxset_and_vz_chi2.first[3];
  vz_fit=v_jetidxset_and_vz_chi2.second;

  
  if(iblep<0) return;
  if(ibhad<0) return;
  if(iq1<0) return;
  if(iq2<0) return;

  neutrino_cand.SetPxPyPzE(CurrentMET.Px(),CurrentMET.Py(),vz_fit, sqrt(pow(CurrentMET.Pt(),2) + pow(vz_fit,2) ));
  SetTopAndW();  
  if(IsTTLJSample){
    RunBJet("bJetLeptonicSide",iblep,bLep_True_genidx,Tlep_cand);
    RunBJet("bJetHadronicSide",ibhad,bHad_True_genidx,Thad_cand);
  }
  else{
    RunBJet("bJetLeptonicSide",iblep,-1,Tlep_cand);
    RunBJet("bJetHadronicSide",ibhad,-1,Thad_cand);
  }




}

void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunBJet(TString bjetname, int bjetidx, int bgenidx, TLorentzVector &Tcand){
  //----Before analyzing the current bjet (whose jetidx = bjetidx),
  // Add suffix to ProcessName if the bjet from b- OR b+ OR light parton
  
  bool isMatched=false;

  ///---Let's Check matching OR not (if it is TTLJ sample <=> bgenidx>-1)---//
  int this_partonFlavour=-9999;
  if(bgenidx>-1){//if TTLJ sample
    this_partonFlavour = v_tightjet[bjetidx].partonFlavour();

    bool FlavourMatched=false;
    bool dRMatched=false;
    if( v_tightjet[bjetidx].partonFlavour() == gens[bgenidx].PID() ) FlavourMatched=true;
    if( v_tightjet[bjetidx].DeltaR(gens[bgenidx]) < 0.4 ) dRMatched=true;
    isMatched=FlavourMatched&&dRMatched;
  }

  if(isMatched){
    TString bsuffix="";
    if(this_partonFlavour==5){
      bsuffix="Frombminus";
    }
    else if(this_partonFlavour==-5){
      bsuffix="Frombplus";
    }
    else{
      cout << "True Matched b-tagged jet cannot have flavour with->" << this_partonFlavour << endl;
      1/0;
    }
    ProcessName=MCSample+"_"+bsuffix;//ProcessName ===> ~Origin of the process
  }  //Add bjetname Suffix
  else{
    if(!IsDATA){
      this_partonFlavour = v_tightjet[bjetidx].partonFlavour();
      TString psuffix="From"+std::to_string(this_partonFlavour);
      ProcessName=MCSample+"_"+psuffix;
    }


  }  //Add bjetname Suffix


  //
  cut_suffix=GetCutSuffix(v_tightjet[bjetidx].Pt());

  //

  //TurnOnFillHist=1;
  bool IsSLTMuon=RunBJetMuon(bjetname, bjetidx, bgenidx,Tcand);
  if(IsSLTMuon) return;

  //if(MuonChargeOnly) return;

  //TurnOnFillHist=1;
  bool IsSLTElectron=RunBJetElectron(bjetname,bjetidx,bgenidx,Tcand);
  if(IsSLTElectron) return;
  
  //if(ElectronChargeOnly) return;

  //TurnOnFillHist=1;
  RunBJetCharge(bjetname,bjetidx,bgenidx,Tcand);
}
void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunBJetCharge(TString bjetname, int bjetidx, int bgenidx,TLorentzVector &Tcand){

  //--- use jetcharge
  bjetname+="TestJet";
  SetJetChargeScore(v_tightjet[bjetidx]);
  //TString cut_suffix=GetCutSuffix(v_tightjet[bjetidx].Pt());
  double bjet_score=GetJetChargeScore();
  ///------All TestJet region----///
  if(ForMeasure){
    FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+cut_suffix,Tcand);
  }
  else{
    if(!runSys){
      FillHistBJet("Lepton_"+bjetname,bjetidx,bgenidx,Tcand);
      FillHist("Lepton_"+bjetname+"/bjet_score", bjet_score,weight,100,0,1);
      
      FillHistBJet(LepCh+"_"+bjetname,bjetidx,bgenidx,Tcand);
      FillHist(LepCh+"_"+bjetname+"/bjet_score", bjet_score,weight,100,0,1);
      
      FillHistBJet("Lepton"+LepSign+"_"+bjetname,bjetidx,bgenidx,Tcand);
      FillHist("Lepton"+LepSign+"_"+bjetname+"/bjet_score", bjet_score,weight,100,0,1);
    }
    FillHistBJet(LepCh+LepSign+"_"+bjetname,bjetidx,bgenidx,Tcand);
    FillHist(LepCh+LepSign+"_"+bjetname+"/bjet_score", bjet_score,weight,100,0,1);
  }


  //-------Apply bjetCharge cut ----//
  //int bjet_charge=v_tightjet[bjetidx].Charge() > 0 ? +1 : -1;
  //---Good bjet---//
  if(bjet_score>jChargeTool->mincut){
    if(ForMeasure){
      FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+"_GoodBJet"+cut_suffix,Tcand);
    }
    else{
      if(!runSys){
	FillHistBJet("Lepton_"+bjetname+"_GoodBJet",bjetidx,bgenidx,Tcand);
	FillHist("Lepton_"+bjetname+"_GoodBJet"+"/bjet_score", bjet_score,weight,100,0,1);
	
	FillHistBJet(LepCh+"_"+bjetname+"_GoodBJet",bjetidx,bgenidx,Tcand);
	FillHist(LepCh+"_"+bjetname+"_GoodBJet"+"/bjet_score", bjet_score,weight,100,0,1);
	
	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_GoodBJet",bjetidx,bgenidx,Tcand);
	FillHist("Lepton"+LepSign+"_"+bjetname+"_GoodBJet"+"/bjet_score", bjet_score,weight,100,0,1);
      }
      FillHistBJet(LepCh+LepSign+"_"+bjetname+"_GoodBJet",bjetidx,bgenidx,Tcand);
      FillHist(LepCh+LepSign+"_"+bjetname+"_GoodBJet"+"/bjet_score", bjet_score,weight,100,0,1);
    }
  }
  //--------
  else{
    if(ForMeasure){
      FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+"_BadBJet"+cut_suffix,Tcand);
    }
    else{
      if(!runSys){
	FillHistBJet("Lepton_"+bjetname+"_BadBJet",bjetidx,bgenidx,Tcand);
	FillHist("Lepton_"+bjetname+"_BadBJet"+"/bjet_score", bjet_score,weight,100,0,1);
	
	FillHistBJet(LepCh+"_"+bjetname+"_BadBJet",bjetidx,bgenidx,Tcand);
	FillHist(LepCh+"_"+bjetname+"_BadBJet"+"/bjet_score", bjet_score,weight,100,0,1);
	
	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_BadBJet",bjetidx,bgenidx,Tcand);
	FillHist("Lepton"+LepSign+"_"+bjetname+"_BadBJet"+"/bjet_score", bjet_score,weight,100,0,1);
      }
      FillHistBJet(LepCh+LepSign+"_"+bjetname+"_BadBJet",bjetidx,bgenidx,Tcand);
      FillHist(LepCh+LepSign+"_"+bjetname+"_BadBJet"+"/bjet_score", bjet_score,weight,100,0,1);
    }//not simplecat
  }//bad jet

}



bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunBJetMuon(TString bjetname, int bjetidx,int bgenidx, TLorentzVector& Tcand){
  //if(ElectronChargeOnly) TurnOnFillHist=0;
  //if(JetChargeOnly) TurnOnFillHist=0;
  //TString cut_suffix=GetCutSuffix(v_tightjet[bjetidx].Pt());
  
  bjetname+="TestMuon";
  //FillHistBJet(TString cutname, int bjetidx)
  if(ForMeasure){
    FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+cut_suffix,Tcand);
  }
  else{
    if(!runSys){
      FillHistBJet("Lepton_"+bjetname,bjetidx,bgenidx,Tcand);
      FillHistBJet(LepCh+"_"+bjetname,bjetidx,bgenidx,Tcand);
      FillHistBJet("Lepton"+LepSign+"_"+bjetname,bjetidx,bgenidx,Tcand);
    }

    FillHistBJet(LepCh+LepSign+"_"+bjetname,bjetidx,bgenidx,Tcand);
  }
  

  //(1) Check if the bjet has basic softmuons.
  bool HasSoftMuon=Run_HasSoftMuon(bjetidx);
  if(!HasSoftMuon) return 0;
  if(ForMeasure){
    FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+"_HasSoftMuon"+cut_suffix,Tcand);
  }
  else{
    if(!runSys){
      FillHistBJet("Lepton_"+bjetname+"_HasSoftMuon",bjetidx,bgenidx,Tcand);
      FillHistBJetMuonMax("Lepton_"+bjetname+"_HasSoftMuon",bjetidx);
      FillHistBJetMuonMin("Lepton_"+bjetname+"_HasSoftMuon",bjetidx);

      FillHistBJet(LepCh+"_"+bjetname+"_HasSoftMuon",bjetidx,bgenidx,Tcand);
      FillHistBJetMuonMax(LepCh+"_"+bjetname+"_HasSoftMuon",bjetidx);
      FillHistBJetMuonMin(LepCh+"_"+bjetname+"_HasSoftMuon",bjetidx);


      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_HasSoftMuon",bjetidx,bgenidx,Tcand);
      FillHistBJetMuonMax("Lepton"+LepSign+"_"+bjetname+"_HasSoftMuon",bjetidx);
      FillHistBJetMuonMin("Lepton"+LepSign+"_"+bjetname+"_HasSoftMuon",bjetidx);
    }
    FillHistBJet(LepCh+LepSign+"_"+bjetname+"_HasSoftMuon",bjetidx,bgenidx,Tcand);
    FillHistBJetMuonMax(LepCh+LepSign+"_"+bjetname+"_HasSoftMuon",bjetidx);
    FillHistBJetMuonMin(LepCh+LepSign+"_"+bjetname+"_HasSoftMuon",bjetidx);
  }
  //(2) if there is soft muon, check whether the muon pass CutToMax OR CutToMin

  //(2-1) The Muon Has very HighScore
  bool SLTMuonPassCutToMax=RunSLTMuonPassCutToMax();

  if(SLTMuonPassCutToMax){
    if(ForMeasure){
      FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+"_HasSLTMuonHigh"+cut_suffix,Tcand);
    }
    else{
      if(!runSys){
	FillHistBJet("Lepton_"+bjetname+"_HasSLTMuonHigh",bjetidx,bgenidx,Tcand);
	FillHistBJetMuonMax("Lepton_"+bjetname+"_HasSLTMuonHigh",bjetidx);
	FillHistBJetMuonMin("Lepton_"+bjetname+"_HasSLTMuonHigh",bjetidx);

	FillHistBJet(LepCh+"_"+bjetname+"_HasSLTMuonHigh",bjetidx,bgenidx,Tcand);
	FillHistBJetMuonMax(LepCh+"_"+bjetname+"_HasSLTMuonHigh",bjetidx);
	FillHistBJetMuonMin(LepCh+"_"+bjetname+"_HasSLTMuonHigh",bjetidx);

	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_HasSLTMuonHigh",bjetidx,bgenidx,Tcand);
	FillHistBJetMuonMax("Lepton"+LepSign+"_"+bjetname+"_HasSLTMuonHigh",bjetidx);
	FillHistBJetMuonMin("Lepton"+LepSign+"_"+bjetname+"_HasSLTMuonHigh",bjetidx);
      }

      FillHistBJet(LepCh+LepSign+"_"+bjetname+"_HasSLTMuonHigh",bjetidx,bgenidx,Tcand);
      FillHistBJetMuonMax(LepCh+LepSign+"_"+bjetname+"_HasSLTMuonHigh",bjetidx);
      FillHistBJetMuonMin(LepCh+LepSign+"_"+bjetname+"_HasSLTMuonHigh",bjetidx);
    }
    return 1;
  }
  ///---Fail SLTMuonHigh
  if(ForMeasure){
    FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+"_FailSLTMuonHigh"+cut_suffix,Tcand);
  }
  else{
    if(!runSys){
      FillHistBJet("Lepton_"+bjetname+"_FailSLTMuonHigh",bjetidx,bgenidx,Tcand);
      FillHistBJetMuonMax("Lepton_"+bjetname+"_FailSLTMuonHigh",bjetidx);
      FillHistBJetMuonMin("Lepton_"+bjetname+"_FailSLTMuonHigh",bjetidx);

      FillHistBJet(LepCh+"_"+bjetname+"_FailSLTMuonHigh",bjetidx,bgenidx,Tcand);
      FillHistBJetMuonMax(LepCh+"_"+bjetname+"_FailSLTMuonHigh",bjetidx);
      FillHistBJetMuonMin(LepCh+"_"+bjetname+"_FailSLTMuonHigh",bjetidx);


      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_FailSLTMuonHigh",bjetidx,bgenidx,Tcand);
      FillHistBJetMuonMax("Lepton"+LepSign+"_"+bjetname+"_FailSLTMuonHigh",bjetidx);
      FillHistBJetMuonMin("Lepton"+LepSign+"_"+bjetname+"_FailSLTMuonHigh",bjetidx);
    }

    FillHistBJet(LepCh+LepSign+"_"+bjetname+"_FailSLTMuonHigh",bjetidx,bgenidx,Tcand);
    FillHistBJetMuonMax(LepCh+LepSign+"_"+bjetname+"_FailSLTMuonHigh",bjetidx);
    FillHistBJetMuonMin(LepCh+LepSign+"_"+bjetname+"_FailSLTMuonHigh",bjetidx);
  }
  //(2-2) The Muon Has very LowScore
  bool SLTMuonPassCutToMin=RunSLTMuonPassCutToMin();
  if(SLTMuonPassCutToMin){
    if(ForMeasure){
      FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+"_HasSLTMuonLow"+cut_suffix,Tcand);
    }
    else{
      if(!runSys){
	FillHistBJet("Lepton_"+bjetname+"_HasSLTMuonLow",bjetidx,bgenidx,Tcand);
	FillHistBJetMuonMax("Lepton_"+bjetname+"_HasSLTMuonLow",bjetidx);
	FillHistBJetMuonMin("Lepton_"+bjetname+"_HasSLTMuonLow",bjetidx);

	FillHistBJet(LepCh+"_"+bjetname+"_HasSLTMuonLow",bjetidx,bgenidx,Tcand);
	FillHistBJetMuonMax(LepCh+"_"+bjetname+"_HasSLTMuonLow",bjetidx);
	FillHistBJetMuonMin(LepCh+"_"+bjetname+"_HasSLTMuonLow",bjetidx);

	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_HasSLTMuonLow",bjetidx,bgenidx,Tcand);
	FillHistBJetMuonMax("Lepton"+LepSign+"_"+bjetname+"_HasSLTMuonLow",bjetidx);
	FillHistBJetMuonMin("Lepton"+LepSign+"_"+bjetname+"_HasSLTMuonLow",bjetidx);
      }
      FillHistBJet(LepCh+LepSign+"_"+bjetname+"_HasSLTMuonLow",bjetidx,bgenidx,Tcand);
      FillHistBJetMuonMax(LepCh+LepSign+"_"+bjetname+"_HasSLTMuonLow",bjetidx);
      FillHistBJetMuonMin(LepCh+LepSign+"_"+bjetname+"_HasSLTMuonLow",bjetidx);
    }
    return 1;
  }

  return 0;

}



bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::Run_HasSoftMuon(int bjetidx){
  tuple<int,double,double,int,double,double> ret=JHAnalyzerBase::GetBJetMuonScore_v2409_2(v_tightjet[bjetidx], AllMuons);
  //{im_max,bmuon_score_max,bmuon_charge_max,im_min,bmuon_score_min,bmuon_charge_min
  int im_max=std::get<0>(ret);
  double bmuon_score_max=std::get<1>(ret);
  double bmuon_charge_max=std::get<2>(ret);

  int im_min=std::get<3>(ret);
  double bmuon_score_min=std::get<4>(ret);
  double bmuon_charge_min=std::get<5>(ret);


  
  //denominator


  if(bmuon_charge_max==0) return 0; 

  //Set current info
  current_im_max=im_max;
  current_bmuon_score_max=bmuon_score_max;
  current_bmuon_charge_max=bmuon_charge_max;

  current_im_min=im_min;
  current_bmuon_score_min=bmuon_score_min;
  current_bmuon_charge_min=bmuon_charge_min;



  return 1;

}

bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunSLTMuonPassCutToMax(){
  if(current_bmuon_score_max > mChargeTool->mincut) return 1;
  return 0;
}

bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunSLTMuonPassCutToMin(){
  if(current_bmuon_score_min < mChargeTool->maxcut) return 1;
  return 0;
}


bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunBJetElectron(TString bjetname, int bjetidx,int bgenidx, TLorentzVector& Tcand){
  //if(MuonChargeOnly) TurnOnFillHist=0;
  //if(JetChargeOnly) TurnOnFillHist=0;
  //cut_suffix=GetCutSuffix(v_tightjet[bjetidx].Pt());
  bjetname+="TestElectron";
  //FillHistBJet(TString cutname, int bjetidx,Tcand)
  if(ForMeasure){
    FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+cut_suffix,Tcand);
  }
  else{
    if(!runSys){
      FillHistBJet("Lepton_"+bjetname,bjetidx,bgenidx,Tcand);
      FillHistBJet(LepCh+"_"+bjetname,bjetidx,bgenidx,Tcand);
      FillHistBJet("Lepton"+LepSign+"_"+bjetname,bjetidx,bgenidx,Tcand);
    }
    FillHistBJet(LepCh+LepSign+"_"+bjetname,bjetidx,bgenidx,Tcand);
  }
  //(1) Check if the bjet has basic softelectrons.
  bool HasSoftElectron=Run_HasSoftElectron(bjetidx);
  if(!HasSoftElectron) return 0;

  if(ForMeasure){
    FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+"_HasSoftElectron"+cut_suffix,Tcand);
  }
  else{
    if(!runSys){
      FillHistBJet("Lepton_"+bjetname+"_HasSoftElectron",bjetidx,bgenidx,Tcand);
      FillHistBJetElectronMax("Lepton_"+bjetname+"_HasSoftElectron",bjetidx);
      FillHistBJetElectronMin("Lepton_"+bjetname+"_HasSoftElectron",bjetidx);

      FillHistBJet(LepCh+"_"+bjetname+"_HasSoftElectron",bjetidx,bgenidx,Tcand);
      FillHistBJetElectronMax(LepCh+"_"+bjetname+"_HasSoftElectron",bjetidx);
      FillHistBJetElectronMin(LepCh+"_"+bjetname+"_HasSoftElectron",bjetidx);

      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_HasSoftElectron",bjetidx,bgenidx,Tcand);
      FillHistBJetElectronMax("Lepton"+LepSign+"_"+bjetname+"_HasSoftElectron",bjetidx);
      FillHistBJetElectronMin("Lepton"+LepSign+"_"+bjetname+"_HasSoftElectron",bjetidx);
    }
    
    FillHistBJet(LepCh+LepSign+"_"+bjetname+"_HasSoftElectron",bjetidx,bgenidx,Tcand);
    FillHistBJetElectronMax(LepCh+LepSign+"_"+bjetname+"_HasSoftElectron",bjetidx);
    FillHistBJetElectronMin(LepCh+LepSign+"_"+bjetname+"_HasSoftElectron",bjetidx);
  }
  
  //(2) if there is soft electron, check whether the electron pass CutToMax OR CutToMin
  
  //(2-1) The Electron Has very HighScore
  bool SLTElectronPassCutToMax=RunSLTElectronPassCutToMax();
  
  if(SLTElectronPassCutToMax){
    if(ForMeasure){
      FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+"_HasSLTElectronHigh"+cut_suffix,Tcand);
    }
    else{
      if(!runSys){
	FillHistBJet("Lepton_"+bjetname+"_HasSLTElectronHigh",bjetidx,bgenidx,Tcand);
	FillHistBJetElectronMax("Lepton_"+bjetname+"_HasSLTElectronHigh",bjetidx);
	FillHistBJetElectronMin("Lepton_"+bjetname+"_HasSLTElectronHigh",bjetidx);

	FillHistBJet(LepCh+"_"+bjetname+"_HasSLTElectronHigh",bjetidx,bgenidx,Tcand);
	FillHistBJetElectronMax(LepCh+"_"+bjetname+"_HasSLTElectronHigh",bjetidx);
	FillHistBJetElectronMin(LepCh+"_"+bjetname+"_HasSLTElectronHigh",bjetidx);

	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_HasSLTElectronHigh",bjetidx,bgenidx,Tcand);
	FillHistBJetElectronMax("Lepton"+LepSign+"_"+bjetname+"_HasSLTElectronHigh",bjetidx);
	FillHistBJetElectronMin("Lepton"+LepSign+"_"+bjetname+"_HasSLTElectronHigh",bjetidx);
	
      }
      
      FillHistBJet(LepCh+LepSign+"_"+bjetname+"_HasSLTElectronHigh",bjetidx,bgenidx,Tcand);
      FillHistBJetElectronMax(LepCh+LepSign+"_"+bjetname+"_HasSLTElectronHigh",bjetidx);
      FillHistBJetElectronMin(LepCh+LepSign+"_"+bjetname+"_HasSLTElectronHigh",bjetidx);
    }
    return 1;
  }

  if(ForMeasure){
    FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+"_FailSLTElectronHigh"+cut_suffix,Tcand);
  }
  else{
    if(!runSys){
      FillHistBJet("Lepton_"+bjetname+"_FailSLTElectronHigh",bjetidx,bgenidx,Tcand);
      FillHistBJetElectronMax("Lepton_"+bjetname+"_FailSLTElectronHigh",bjetidx);
      FillHistBJetElectronMin("Lepton_"+bjetname+"_FailSLTElectronHigh",bjetidx);

      FillHistBJet(LepCh+"_"+bjetname+"_FailSLTElectronHigh",bjetidx,bgenidx,Tcand);
      FillHistBJetElectronMax(LepCh+"_"+bjetname+"_FailSLTElectronHigh",bjetidx);
      FillHistBJetElectronMin(LepCh+"_"+bjetname+"_FailSLTElectronHigh",bjetidx);

      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_FailSLTElectronHigh",bjetidx,bgenidx,Tcand);
      FillHistBJetElectronMax("Lepton"+LepSign+"_"+bjetname+"_FailSLTElectronHigh",bjetidx);
      FillHistBJetElectronMin("Lepton"+LepSign+"_"+bjetname+"_FailSLTElectronHigh",bjetidx);
      
    }
    FillHistBJet(LepCh+LepSign+"_"+bjetname+"_FailSLTElectronHigh",bjetidx,bgenidx,Tcand);
    FillHistBJetElectronMax(LepCh+LepSign+"_"+bjetname+"_FailSLTElectronHigh",bjetidx);
    FillHistBJetElectronMin(LepCh+LepSign+"_"+bjetname+"_FailSLTElectronHigh",bjetidx);
  }
  //(2-2) The Electron Has very LowScore
  bool SLTElectronPassCutToMin=RunSLTElectronPassCutToMin();
  if(SLTElectronPassCutToMin){
    if(ForMeasure){
      FillHistBJetForMeasure("Lepton"+LepSign+"_"+bjetname+"_HasSLTElectronLow"+cut_suffix,Tcand);
    }
    else{
      if(!runSys){
	FillHistBJet("Lepton_"+bjetname+"_HasSLTElectronLow",bjetidx,bgenidx,Tcand);
	FillHistBJetElectronMax("Lepton_"+bjetname+"_HasSLTElectronLow",bjetidx);
	FillHistBJetElectronMin("Lepton_"+bjetname+"_HasSLTElectronLow",bjetidx);

	FillHistBJet(LepCh+"_"+bjetname+"_HasSLTElectronLow",bjetidx,bgenidx,Tcand);
	FillHistBJetElectronMax(LepCh+"_"+bjetname+"_HasSLTElectronLow",bjetidx);
	FillHistBJetElectronMin(LepCh+"_"+bjetname+"_HasSLTElectronLow",bjetidx);


	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_HasSLTElectronLow",bjetidx,bgenidx,Tcand);
	FillHistBJetElectronMax("Lepton"+LepSign+"_"+bjetname+"_HasSLTElectronLow",bjetidx);
	FillHistBJetElectronMin("Lepton"+LepSign+"_"+bjetname+"_HasSLTElectronLow",bjetidx);
	
      }
      FillHistBJet(LepCh+LepSign+"_"+bjetname+"_HasSLTElectronLow",bjetidx,bgenidx,Tcand);
      FillHistBJetElectronMax(LepCh+LepSign+"_"+bjetname+"_HasSLTElectronLow",bjetidx);
      FillHistBJetElectronMin(LepCh+LepSign+"_"+bjetname+"_HasSLTElectronLow",bjetidx);
    }
    return 1;
  }

  return 0;

}

bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunSLTElectronPassCutToMax(){
  if(current_belectron_score_max > eChargeTool->mincut) return 1; //mincut==CutToMax
  return 0;
}

bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunSLTElectronPassCutToMin(){
  if(current_belectron_score_min < eChargeTool->maxcut) return 1;//maxcut==CutToMin
  return 0;
}


bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::Run_HasSoftElectron(int bjetidx){
  tuple<int,double,double,int,double,double> ret=JHAnalyzerBase::GetBJetElectronScore_v2409_2(v_tightjet[bjetidx], AllElectrons);
  //{ie_max,belectron_score_max,belectron_charge_max,ie_min,belectron_score_min,belectron_charge_min
  int ie_max=std::get<0>(ret);
  double belectron_score_max=std::get<1>(ret);
  double belectron_charge_max=std::get<2>(ret);

  int ie_min=std::get<3>(ret);
  double belectron_score_min=std::get<4>(ret);
  double belectron_charge_min=std::get<5>(ret);


  
  //denominator


  if(belectron_charge_max==0) return 0; 

  //Set current info
  current_ie_max=ie_max;
  current_belectron_score_max=belectron_score_max;
  current_belectron_charge_max=belectron_charge_max;

  current_ie_min=ie_min;
  current_belectron_score_min=belectron_score_min;
  current_belectron_charge_min=belectron_charge_min;



  return 1;

}
TString TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::GetCutSuffix(double this_bjet_pt){
  //jetpog_ptbins={20., 30., 50., 70., 100., 140., 200., 300., 600., 1000.}
  TString ret="";
  if(this_bjet_pt>140.){
    ret="__PT140ToInf";    
  }
  else if(this_bjet_pt > 100.){
    ret="__PT100To140";
  }
  else if(this_bjet_pt > 70.){
    ret="__PT70To100";
  }
  else if(this_bjet_pt > 50.){
    ret="__PT50To70";
  }
  else if(this_bjet_pt > 30.){
    ret="__30To50";
  }
  else{
    ret="__0To30";
  }
  return ret;
}

void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHistBJetForMeasure(TString cutname, TLorentzVector& Tcand){
    FillHist(cutname+"/Tcand_mass", Tcand.M(),weight,70,50,350); 
    FillHist(cutname+"/Event", 0.5,weight,1,0,1); 
}
void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHistBJet(TString cutname, int bjetidx,int bgenidx, TLorentzVector& Tcand){
  //if(!TurnOnFillHist) return;
  FillHist(cutname+"/bjet_pt", v_tightjet[bjetidx].Pt(),weight,njetpog_ptbins,jetpog_ptbins);
  FillHist(cutname+"/bjet_eta", v_tightjet[bjetidx].Eta(),weight,njetpog_etabins,jetpog_etabins);
  
  FillHist(cutname+"/Tcand_mass", Tcand.M(),weight,200,0,400);  
  
  //FillHist(cutname+"/bjet_dR_l", v_tightjet[bjetidx].DeltaR(l1),weight,100,0,5);

}


void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHistBJetMuonMax(TString cutname, int bjetidx){
  //if(!TurnOnFillHist) return;
  //double JHAnalyzerBase::GetP_JetRestFrame(TLorentzVector &lep, TLorentzVector &jet)
  double ptAtJetRest=JHAnalyzerBase::GetP_JetRestFrame(AllMuons[current_im_max],v_tightjet[bjetidx]);
  //double JHAnalyzerBase::GetPt_wrt_Jet(TLorentzVector &lep, TLorentzVector &jet){
  double ptwrtjet=JHAnalyzerBase::GetPt_wrt_Jet(AllMuons[current_im_max],v_tightjet[bjetidx]);
  FillHist(cutname+"/muonmax_pt", AllMuons[current_im_max].Pt(),weight,100,0,100);
  //FillHist(cutname+"/muonmax_p", AllMuons[current_im_max].P(),weight,100,0,100);
  FillHist(cutname+"/muonmax_eta", AllMuons[current_im_max].Eta(),weight,50,-3,3);
  //FillHist(cutname+"/muonmax_ptwrtjet", ptwrtjet,weight,100,0,100);
  //FillHist(cutname+"/muonmax_ptAtJetRest", ptAtJetRest,weight,100,0,100);
  FillHist(cutname+"/muonmax_ptwrtjet_zoom", ptwrtjet,weight,100,0,10);
  FillHist(cutname+"/muonmax_ptAtJetRest_zoom", ptAtJetRest,weight,100,0,10);
  FillHist(cutname+"/muonmax_score", current_bmuon_score_max,weight,100,0,1);

}



void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHistBJetMuonMin(TString cutname, int bjetidx){
  //if(!TurnOnFillHist) return;
  //double JHAnalyzerBase::GetP_JetRestFrame(TLorentzVector &lep, TLorentzVector &jet)
  double ptAtJetRest=JHAnalyzerBase::GetP_JetRestFrame(AllMuons[current_im_min],v_tightjet[bjetidx]);
  //double JHAnalyzerBase::GetPt_wrt_Jet(TLorentzVector &lep, TLorentzVector &jet){
  double ptwrtjet=JHAnalyzerBase::GetPt_wrt_Jet(AllMuons[current_im_min],v_tightjet[bjetidx]);
  FillHist(cutname+"/muonmin_pt", AllMuons[current_im_min].Pt(),weight,100,0,100);
  //FillHist(cutname+"/muonmin_p", AllMuons[current_im_min].P(),weight,100,0,100);
  FillHist(cutname+"/muonmin_eta", AllMuons[current_im_min].Eta(),weight,50,-3,3);
  //FillHist(cutname+"/muonmin_ptwrtjet", ptwrtjet,weight,100,0,100);
  //FillHist(cutname+"/muonmin_ptAtJetRest", ptAtJetRest,weight,100,0,100);
  FillHist(cutname+"/muonmin_ptwrtjet_zoom", ptwrtjet,weight,100,0,10);
  FillHist(cutname+"/muonmin_ptAtJetRest_zoom", ptAtJetRest,weight,100,0,10);
  FillHist(cutname+"/muonmin_score", current_bmuon_score_min,weight,100,0,1);

}




void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHistBJetElectronMax(TString cutname, int bjetidx){
  //if(!TurnOnFillHist) return;
  //double JHAnalyzerBase::GetP_JetRestFrame(TLorentzVector &lep, TLorentzVector &jet)
  double ptAtJetRest=JHAnalyzerBase::GetP_JetRestFrame(AllElectrons[current_ie_max],v_tightjet[bjetidx]);
  //double JHAnalyzerBase::GetPt_wrt_Jet(TLorentzVector &lep, TLorentzVector &jet){
  double ptwrtjet=JHAnalyzerBase::GetPt_wrt_Jet(AllElectrons[current_ie_max],v_tightjet[bjetidx]);
  FillHist(cutname+"/electronmax_pt", AllElectrons[current_ie_max].Pt(),weight,100,0,100);
  //FillHist(cutname+"/electronmax_p", AllElectrons[current_ie_max].P(),weight,100,0,100);
  FillHist(cutname+"/electronmax_eta", AllElectrons[current_ie_max].Eta(),weight,50,-3,3);
  //FillHist(cutname+"/electronmax_ptwrtjet", ptwrtjet,weight,100,0,100);
  //FillHist(cutname+"/electronmax_ptAtJetRest", ptAtJetRest,weight,100,0,100);
  FillHist(cutname+"/electronmax_ptwrtjet_zoom", ptwrtjet,weight,100,0,10);
  FillHist(cutname+"/electronmax_ptAtJetRest_zoom", ptAtJetRest,weight,100,0,10);
  FillHist(cutname+"/electronmax_score", current_belectron_score_max,weight,100,0,1);

}



void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHistBJetElectronMin(TString cutname, int bjetidx){
  //if(!TurnOnFillHist) return;
  //double JHAnalyzerBase::GetP_JetRestFrame(TLorentzVector &lep, TLorentzVector &jet)
  double ptAtJetRest=JHAnalyzerBase::GetP_JetRestFrame(AllElectrons[current_ie_min],v_tightjet[bjetidx]);
  //double JHAnalyzerBase::GetPt_wrt_Jet(TLorentzVector &lep, TLorentzVector &jet){
  double ptwrtjet=JHAnalyzerBase::GetPt_wrt_Jet(AllElectrons[current_ie_min],v_tightjet[bjetidx]);
  FillHist(cutname+"/electronmin_pt", AllElectrons[current_ie_min].Pt(),weight,100,0,100);
  //FillHist(cutname+"/electronmin_p", AllElectrons[current_ie_min].Pt(),weight,100,0,100);
  FillHist(cutname+"/electronmin_eta", AllElectrons[current_ie_min].Eta(),weight,50,-3,3);
  //FillHist(cutname+"/electronmin_ptwrtjet", ptwrtjet,weight,100,0,100);
  //FillHist(cutname+"/electronmin_ptAtJetRest", ptAtJetRest,weight,100,0,100);
  FillHist(cutname+"/electronmin_ptwrtjet_zoom", ptwrtjet,weight,100,0,10);
  FillHist(cutname+"/electronmin_ptAtJetRest_zoom", ptAtJetRest,weight,100,0,10);
  FillHist(cutname+"/electronmin_score", current_belectron_score_min,weight,100,0,1);
}

void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::SetTopAndW(){

  Wlep_cand=l1+neutrino_cand;
  Whad_cand=v_tightjet[iq1]+v_tightjet[iq2];
  Tlep_cand=Wlep_cand+v_tightjet[iblep];
  Thad_cand=Whad_cand+v_tightjet[ibhad];
}

///----OLD---///
void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunPlots(){
  
  if(!IsDATA){
    bool isbLepFromb= abs(v_tightjet[iblep].hadronFlavour())==5;
    bool isbHadFromb= abs(v_tightjet[ibhad].hadronFlavour())==5;

    if(isbLepFromb&&isbHadFromb){
      ProcessName=MCSample+"_All_bjetFromb";
    }
    else if(isbHadFromb){
      ProcessName=MCSample+"_bHadCandFromb";
    }
    else if(isbLepFromb){
      ProcessName=MCSample+"_bLepCandFromb";
    }
    else{
      ProcessName=MCSample+"_NonFromb";
    }
  }

  SetTopAndW();
  



  //bLep infos
  FillHist_bjetinfo(LepCh+"_TTLJ",iblep,"bLep");
  return;  
  FillHist_bjetinfo("AllLep_TTLJ",iblep,"bLep");

 //bHad infos
  FillHist_bjetinfo(LepCh+"_TTLJ",ibhad,"bHad");
  FillHist_bjetinfo("AllLep_TTLJ",ibhad,"bHad");

  if(ForBinning)    return;
  if(runSys) return;
  //TTLJ infos
  FillHistTTLJ(LepCh+"_TTLJ");
  FillHistTTLJ("AllLep_TTLJ");



}

bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::HasMatchedRecoJet(int genidx,double dRcut){
  TLorentzVector this_genptl=gens[genidx];
  for(auto &jet : v_tightjet){
    if(this_genptl.DeltaR(jet) < dRcut) return 1;
  }
  return 0;
}


bool TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::HasFlavourMatchedRecoJet(int genidx){
  //TLorentzVector this_genptl=gens[genidx];
  int true_pid=gens[genidx].PID();
  for(auto &jet : v_tightjet){
    if(jet.partonFlavour() == true_pid) return 1;
  }
  return 0;
}




void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHistTTLJ(TString cutname){



  //---Top and W
  FillHist(cutname+"/Wlep_cand_pt",Wlep_cand.Pt(),weight,100,0,300);
  FillHist(cutname+"/Wlep_cand_eta",Wlep_cand.Eta(),weight,100,-5,5);
  FillHist(cutname+"/Wlep_cand_M",Wlep_cand.M(),weight,100,30,130);

  FillHist(cutname+"/Whad_cand_pt",Whad_cand.Pt(),weight,100,0,300);
  FillHist(cutname+"/Whad_cand_eta",Whad_cand.Eta(),weight,100,-5,5);
  FillHist(cutname+"/Whad_cand_M",Whad_cand.M(),weight,100,30,130);

  FillHist(cutname+"/Tlep_cand_pt",Tlep_cand.Pt(),weight,100,0,200);
  FillHist(cutname+"/Tlep_cand_eta",Tlep_cand.Eta(),weight,100,-5,5);
  FillHist(cutname+"/Tlep_cand_M",Tlep_cand.M(),weight,120,50,290);

  FillHist(cutname+"/Thad_cand_pt",Thad_cand.Pt(),weight,100,0,300);
  FillHist(cutname+"/Thad_cand_eta",Thad_cand.Eta(),weight,100,-5,5);
  FillHist(cutname+"/Thad_cand_M",Thad_cand.M(),weight,120,50,290);

  //---Decay products
  FillHist(cutname+"/neutrino_cand_pt",neutrino_cand.Pt(),weight,100,0,300);
  FillHist(cutname+"/neutrino_cand_eta",neutrino_cand.Eta(),weight,100,-5,5);
  FillHist(cutname+"/neutrino_cand_phi",neutrino_cand.Phi(),weight,100,-4,4);

  FillHist(cutname+"/q1_cand_pt",v_tightjet[iq1].Pt(),weight,100,0,300);
  FillHist(cutname+"/q1_cand_eta",v_tightjet[iq1].Eta(),weight,100,-5,5);
  FillHist(cutname+"/q1_cand_phi",v_tightjet[iq1].Phi(),weight,100,-4,4);

  FillHist(cutname+"/q2_cand_pt",v_tightjet[iq2].Pt(),weight,100,0,300);
  FillHist(cutname+"/q2_cand_eta",v_tightjet[iq2].Eta(),weight,100,-5,5);
  FillHist(cutname+"/q2_cand_phi",v_tightjet[iq2].Phi(),weight,100,-4,4);


  //v_tightjet[iblep],l1,
  double M_blep_l = (l1+v_tightjet[iblep]).M();
  FillHist(cutname+"/M_blep_l",M_blep_l,weight,100,0,400);
  double abs_dphi_Tlep_Thad=fabs(Tlep_cand.DeltaPhi(Thad_cand));
  FillHist(cutname+"/abs_dphi_Tlep_Thad",abs_dphi_Tlep_Thad,weight,100,0,4);

  FillHistAll(cutname);


}
void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHist_bjetinfo(TString cutname, int i_bjet, TString Name_bCand){
  //Charge of bjets
  //---Get Charge of bjets
  //pair<int,bool> JHAnalyzerBase::GetBJetCharge_v2409_2(Jet &_bjet, vector<Muon> &_muoncoll, vector<Electron> &electroncoll){
  //bLepCand_Charge_info=GetBJetCharge_v2409_2(v_tightjet[iblep],AllMuons,AllElectrons);
  //bHadCand_Charge_info=GetBJetCharge_v2409_2(v_tightjet[ibhad],AllMuons,AllElectrons);

  //Get bjet charges
  tuple<int,bool,int,int,double> bCand_Charge_info=GetBJetCharge_v2409_2(v_tightjet[i_bjet],AllMuons,AllElectrons);

  bCand_Charge=std::get<0>(bCand_Charge_info);
  bCand_NotUseOppositeCharge=std::get<1>(bCand_Charge_info);
  bCand_im=std::get<2>(bCand_Charge_info);
  bCand_ie=std::get<3>(bCand_Charge_info);
  bCnad_ChargeScore=std::get<4>(bCand_Charge_info);

  //bjetvar
  current_bjetname=Name_bCand;
  current_bjetvar=Get_bjetvar(v_tightjet[i_bjet]);
  //init bmuonvar 
  //current_bmuonvar=bmuonvar_init;
  //current_bmuonvar=Get_bmuonvar(AllMuons[bCand_im],v_tightjet[i_bjet]);
  //belectronvar
  //current_belectronvar=Get_belectronvar(AllElectrons[bCand_ie],v_tightjet[i_bjet]);

  
  FillHist(cutname+"/"+Name_bCand+"_Charge",bCand_Charge,weight,12,-6,6);
  if(bCand_NotUseOppositeCharge){//Not Opposite
    FillHist(cutname+"/"+Name_bCand+"_Charge_NotOpposite",bCand_Charge,weight,12,-6,6);
  }
  else{
    FillHist(cutname+"/"+Name_bCand+"_Charge_UseOpposite",bCand_Charge,weight,12,-6,6);
  }
  FillHist_bCand(cutname+"__"+Name_bCand);
  ///-----bjet's kin. by each bjetcharge----//
  //----bLep
  //(1)using softmuon
  if(abs(bCand_Charge)==1){//
    //read bmuonvar
    current_bmuonvar=Get_bmuonvar(AllMuons[bCand_im],v_tightjet[i_bjet]);
    FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftMuonCharge");
    FillHist_bCand_bmuon(cutname+"__"+Name_bCand+"UsingSoftMuonCharge");
    if(bCand_NotUseOppositeCharge){
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingSoftMuonChargeNotOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftMuonChargeNotOpposite");
      FillHist_bCand_bmuon(cutname+"__"+Name_bCand+"UsingSoftMuonChargeNotOpposite");
    }
    else{
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingSoftMuonChargeUseOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftMuonChargeUseOpposite");
      FillHist_bCand_bmuon(cutname+"__"+Name_bCand+"UsingSoftMuonChargeUseOpposite");

    }
  }
  else if(abs(bCand_Charge)==2){//using softelectron charge
    
    //read  belectronvar
    current_belectronvar=Get_belectronvar(AllElectrons[bCand_ie],v_tightjet[i_bjet]);
    //denominator
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon");
    //if(MuonChargeOnly) return;
    //(2)using softelectron
    FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftElectronCharge");
    FillHist_bCand_belectron(cutname+"__"+Name_bCand+"UsingSoftElectronCharge");
    if(bCand_NotUseOppositeCharge){
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingSoftElectronChargeNotOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftElectronChargeNotOpposite");
      FillHist_bCand_belectron(cutname+"__"+Name_bCand+"UsingSoftElectronChargeNotOpposite");
    }
    else{
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingSoftElectronChargeUseOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingSoftElectronChargeUseOpposite");
      FillHist_bCand_belectron(cutname+"__"+Name_bCand+"UsingSoftElectronChargeUseOpposite");
    }
  }
    
    

  else if(abs(bCand_Charge)==3){//
    //denominators
    
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon");
    //if(MuonChargeOnly) return;
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon__FailSoftElectron");

    //(3)using goodjetcharge
    FillHist_bCand(cutname+"__"+Name_bCand+"UsingGoodJetCharge");
    if(bCand_NotUseOppositeCharge){
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingGoodJetChargeNotOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingGoodJetChargeNotOpposite");
    }
    else{
      //FillHistTTLJ(cutname+"__"+Name_bCand+"UsingGoodJetChargeUseOpposite");
      FillHist_bCand(cutname+"__"+Name_bCand+"UsingGoodJetChargeUseOpposite");
    }
  }//(4)using poorjetcharge
  else{
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon");    
    //if(MuonChargeOnly) return;
    //FillHistTTLJ(cutname+"__"+Name_bCand+"_FailSoftMuon__FailSoftElectron__FailGoodBJet");
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon__FailSoftElectron");
    FillHist_bCand(cutname+"__"+Name_bCand+"_FailSoftMuon__FailSoftElectron__FailGoodBJet");
  }
  
  

}

void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHist_bCand(TString cutname){
  //FillHist(cutname+"/"+bCandName+"_pt",v_tightjet[ibCand].Pt(),weight,100,0,300);
  //FillHist(cutname+"/"+bCandName+"_eta",v_tightjet[ibCand].Eta(),weight,100,-5,5);
  //FillHist(cutname+"/"+bCandName+"_phi",v_tightjet[ibCand].Phi(),weight,100,-4,4);


  if(ForBinning){
    if(current_bjetvar.pt < 40.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt30_40",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 50.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt40_50",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 60.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt50_60",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 70.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt60_70",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 80.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt70_80",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 90.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt80_90",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 100.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt90_100",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 110.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt100_110",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 120.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt110_120",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 130.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt120_130",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 140.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt130_140",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 150.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt140_150",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 160.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt150_160",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 170.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt160_170",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 180.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt170_180",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 190.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt180_190",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 200.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt190_200",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 210.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt200_210",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 220.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt210_220",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 230.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt220_230",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 240.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt230_240",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 250.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt240_250",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 260.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt250_260",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 270.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt260_270",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 280.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt270_280",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 290.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt280_290",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 300.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt290_300",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 400.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt300_400",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 500.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt400_500",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 600.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt500_600",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 700.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt600_700",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 800.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt700_800",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 900.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt800_900",current_bjetvar.eta,weight,30,-3,3);
    }
    else if(current_bjetvar.pt < 1000.){
      FillHist(cutname+"/"+current_bjetname+"_eta__pt900_1000",current_bjetvar.eta,weight,30,-3,3);
    }



    return;

  }

  ///--DNN inputs
  //bjetvar this_bjetvar=Get_bjetvar(v_tightjet[ibCand]);
  FillHist(cutname+"/"+current_bjetname+"_pt",current_bjetvar.pt,weight,300,0,300);
  FillHist(cutname+"/"+current_bjetname+"_aeta",current_bjetvar.aeta,weight,60,0,3);
  FillHist(cutname+"/"+current_bjetname+"_eta",current_bjetvar.eta,weight,120,-3,3);
  if(runSys) return;
  FillHist(cutname+"/"+current_bjetname+"_ChargedHadronEnergyFraction",current_bjetvar.ChargedHadronEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/"+current_bjetname+"_NeutralHadronEnergyFraction",current_bjetvar.NeutralHadronEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/"+current_bjetname+"_NeutralEmEnergyFraction",current_bjetvar.NeutralEmEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/"+current_bjetname+"_ChargedEmEnergyFraction",current_bjetvar.ChargedEmEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/"+current_bjetname+"_MuonEnergyFraction",current_bjetvar.MuonEnergyFraction,weight,100,0,1);

  FillHist(cutname+"/"+current_bjetname+"_ChargedMultiplicity",current_bjetvar.ChargedMultiplicity,weight,60,0,60);
  FillHist(cutname+"/"+current_bjetname+"_NeutralMultiplicity",current_bjetvar.NeutralMultiplicity,weight,60,0,60);

  FillHist(cutname+"/"+current_bjetname+"_charge",current_bjetvar.charge,weight,50,-1,1);
  FillHist(cutname+"/"+current_bjetname+"_abs_charge",current_bjetvar.abs_charge,weight,50,0,1);
  FillHist(cutname+"/"+current_bjetname+"_int_charge",current_bjetvar.charge>0 ? 1 : -1 ,weight,4,-2,2);
  FillHist(cutname+"/"+current_bjetname+"_partonFlavour",current_bjetvar.partonFlavour,weight,27,-6,21);
  FillHist(cutname+"/"+current_bjetname+"_hadronFlavour",current_bjetvar.hadronFlavour,weight,6,0,6);

  FillHist(cutname+"/"+current_bjetname+"_ChargeScore",bCnad_ChargeScore,weight,100,0,1);

  FillHistTTLJ(cutname);


}
void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHist_bCand_bmuon(TString cutname){  

  if(runSys) return;
  if(ForBinning) return;
  //if the bjet has good softbmuon
  
  //bmuonvar this_bmuonvar=Get_bmuonvar(*MuonMax,v_bjet[0]);
  
  FillHist(cutname+"/"+current_bjetname+"_bmuon_P_jetrest",current_bmuonvar.P_jetrest,weight,10,0,10);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_ptwrtjet",current_bmuonvar.ptwrtjet,weight,10,0,10);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_dR_l_j",current_bmuonvar.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_nsip3d",current_bmuonvar.nsip3d,weight,30,0,15);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_reltrkiso",current_bmuonvar.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_reliso",current_bmuonvar.reliso,weight,150,0,15);
  FillHist(cutname+"/"+current_bjetname+"_bmuon_charge",current_bmuonvar.charge,weight,4,-2,2);
}


void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHist_bCand_belectron(TString cutname){  
  if(runSys) return;
  if(ForBinning) return;
  FillHist(cutname+"/"+current_bjetname+"_belectron_P_jetrest",current_belectronvar.P_jetrest,weight,10,0,10);
  FillHist(cutname+"/"+current_bjetname+"_belectron_ptwrtjet",current_belectronvar.ptwrtjet,weight,10,0,10);
  FillHist(cutname+"/"+current_bjetname+"_belectron_dR_l_j",current_belectronvar.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/"+current_bjetname+"_belectron_nsip3d",current_belectronvar.nsip3d,weight,30,0,15);
  FillHist(cutname+"/"+current_bjetname+"_belectron_reltrkiso",current_belectronvar.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/"+current_bjetname+"_belectron_reliso",current_belectronvar.reliso,weight,150,0,15);
  FillHist(cutname+"/"+current_bjetname+"_belectron_charge",current_belectronvar.charge,weight,4,-2,2);
  FillHist(cutname+"/"+current_bjetname+"_belectron_IsGsfCtfScPixChargeConsistent",current_belectronvar.IsGsfCtfScPixChargeConsistent,weight,4,-2,2);
  FillHist(cutname+"/"+current_bjetname+"_belectron_InvEminusInvP",current_belectronvar.InvEminusInvP,weight,50,0,0.3);
  FillHist(cutname+"/"+current_bjetname+"_belectron_palongjet",current_belectronvar.palongjet,weight,100,0,30);
  FillHist(cutname+"/"+current_bjetname+"_belectron_palongjetratio",current_belectronvar.palongjetratio,weight,100,0,2);

}


void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::FillHistAll(TString cutname){
  if(ForBinning) return;
  FillHist(cutname+"/nPV",nPV,weight,100,0,100);

  FillHist(cutname+"/MT_lv",vtW.M(),weight,200,0,200);

  FillHist(cutname+"/pt_l1",l1.Pt(),weight,200,0,200);
  FillHist(cutname+"/eta_l1",l1.Eta(),weight,50,-3,3);

  FillHist(cutname+"/njet",njet,weight,10,0,10);
  FillHist(cutname+"/nbjet",nbjet,weight,10,0,10);

  FillHist(cutname+"/met",CurrentMET.Pt(),weight,200,0,200);
  FillHist(cutname+"/dphi_l_met",CurrentMET.DeltaPhi(l1),weight,200,-4,4);

  if(njet>0){
    FillHist(cutname+"/pt_j1",v_tightjet[0].Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_j1",v_tightjet[0].Eta(),weight,50,-3,3);
    if(njet>1){
      FillHist(cutname+"/pt_j2",v_tightjet[1].Pt(),weight,200,0,200);
      FillHist(cutname+"/eta_j2",v_tightjet[1].Eta(),weight,50,-3,3);
    }
  }  


  
}


void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::EventLoop(){
  RunReco();

}





void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::TruthLoop(){
  //it must be TTLJ samples
  if (IsTTLJSample){
    TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunLHEinfo();
    TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunGENinfo();
  }

}

void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunLHEinfo(){
  //
  //initialize
  int LHEsize = lhes.size();
  unsigned int n_light_quark=0;
  int LeptonCharge=0;
  IsElectronChannel_LHE =0;
  IsMuonChannel_LHE     =0;
  IsTauChannel_LHE      =0;

  for(int i = 0; i < LHEsize; i++) {
    int status=lhes[i].Status();
    int pid=lhes[i].ID();

    if(status==1){
      if(pid == 11){
        LeptonCharge = -1; IsElectronChannel_LHE=true;
        break;
      }
      else if(pid == -11){
        LeptonCharge = +1; IsElectronChannel_LHE=true;
        break;
      }
      else if(pid == 13){
        LeptonCharge = -1; IsMuonChannel_LHE=true;
        break;
      }
      else if(pid == -13){
        LeptonCharge = 1; IsMuonChannel_LHE=true;
        break;
      }

      else if(pid == 15){
        LeptonCharge = -1; IsTauChannel_LHE=true;
        break;
      }
      else if(pid == -15){
        LeptonCharge = 1; IsTauChannel_LHE=true;
        break;
      }

      if ( abs(pid)<5) n_light_quark+=1;
    }    
  }//[END] OF LHE LOOP
  bLepCharge_LHE=-LeptonCharge;
  bHadCharge_LHE=LeptonCharge;
  
}
void TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch::RunGENinfo(){
  unsigned int gensize=gens.size();
  //status21 is incoming particle.
  //To find W decay daughters 

  bLep_True_genidx=-1; bHad_True_genidx=-1;

  idx_bquark_GEN=-1, idx_bbarquark_GEN=-1;
  v_idx_lightquark_GEN.clear();
  
  i_lepton_GEN=-1;
  i_neutrino_GEN=-1;
  for(unsigned int i = 0 ; i < gensize ; i++){
    int pid=gens[i].PID();
    int status=gens[i].Status();
    int mother=gens[i].MotherIndex();
    int isHardProcess=gens[i].isHardProcess();
    /// Outgoing HardProcess parton
    if(mother > -1){
      if (isHardProcess && (status!=21) && gens[mother].Status()!=21 && abs(pid)<5) {
	v_idx_lightquark_GEN.push_back(i);
      }
    }
    if (isHardProcess && (status!=21)){
      if(pid==5){
        idx_bquark_GEN=i;
      }
      else if(pid==-5){
        idx_bbarquark_GEN=i;
      }
      if(abs(pid)>10 && abs(pid)<17){
	if(abs(pid)==11 || abs(pid)==13 || abs(pid)==15){
	  i_lepton_GEN=i;
	}
	else{
	  i_neutrino_GEN=i;
	}
      }
    }


  }
  //----GEN-LEVEL W_had and T_had
  TLorentzVector vWhad,vThad,vWlep,vTlep;
  //---Add outgoing light quarks' momenta to whad,thad
  //for(unsigned int i = 0 ; i < v_idx_lightquark_GEN.size(); i++){
  for(auto& i_light : v_idx_lightquark_GEN){
    vWhad+=gens[i_light];
    vThad+=gens[i_light];
  }


  vWlep=gens[i_lepton_GEN]+gens[i_neutrino_GEN];
  vTlep=vWlep;

  //---add bquark momentum to Top
  if(bHadCharge_LHE>0){// bHadCharge >0 means bbar
    vThad+=gens[idx_bbarquark_GEN];
    vTlep+=gens[idx_bquark_GEN];
  }
  else{
    vThad+=gens[idx_bquark_GEN];
    vTlep+=gens[idx_bbarquark_GEN];
  }

  Whad_q1_pid=gens[v_idx_lightquark_GEN[0]].PID();
  Whad_q2_pid=gens[v_idx_lightquark_GEN[1]].PID();



  
  // FillHist("GEN/Whad_mass/"+ProcessName,vWhad.M(), weight, 80, 50, 130);
  //FillHist("GEN/Thad_mass/"+ProcessName,vThad.M(), weight, 60, 140, 200);

  //FillHist("GEN/Wlep_mass/"+ProcessName,vWlep.M(), weight, 80, 50, 130);
  //FillHist("GEN/Tlep_mass/"+ProcessName,vTlep.M(), weight, 60, 140, 200);


  //Hadronic b, and bjet
  bHad_True_PID=99999;
  bHad_True_genidx=-1;
  if(bHadCharge_LHE>0){//bbar
    bHad_True_PID=-5;
    bLep_True_PID=5;
    bHad_True_genidx=idx_bbarquark_GEN;
    bLep_True_genidx=idx_bquark_GEN;
  }
  else{//b
    bHad_True_PID=5;
    bLep_True_PID=-5;
    bHad_True_genidx=idx_bquark_GEN;
    bLep_True_genidx=idx_bbarquark_GEN;
  }
  

}


