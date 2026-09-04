#include "TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING.h"

TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING(){
  //runSys=true;
  //jetpog_etabins
  //jetpog_ptbins
}

TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::~TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING(){
  //==== Destructor of this Analyzer

}

void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::initializeAnalyzer(){
  cout << "[TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::initializeAnalyzer]" << endl;
  //TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING

  if(HasFlag("use_beff")){
    //----use this analyzer specific btag mc eff----//
    //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING_"+MCSample+".root");

  }
  if(HasFlag("use_beff_dasym")){
    //----use this analyzer specific btag mc eff----//
    //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING_"+MCSample+".root",true);
    use_dasym=true;
  }
  else{
    use_dasym=false;
  }
  JETPUID="";
  if(HasFlag("JETPUID_L")){
    JETPUID="L";
    cout << "Use JETPUID=L " << endl;
  }

  RunBasicObjectOnly=HasFlag("RunBasicObjectOnly");
  
  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupSingleLeptonChannel();
  noveto=false;
  if(HasFlag("noveto")){
    noveto=true;
  }
  newlepveto=false;
  if(HasFlag("newlepveto")){
    newlepveto=true;
    noveto=true;
  }
  
  //TopMassWindow=HasFlag("TopMassWindow");
  chi2kincut=HasFlag("chi2kincut");
  ApplyBtagSF=HasFlag("ApplyBtagSF");

  //NoJetVeto
  NoJetVeto=HasFlag("NoJetVeto");
  //Jet Assignment Tool
  InitJetAssigenChi2Fitter();
  //
  jetlepveto=HasFlag("jetlepveto");
  jetidtight="tight";
  if(jetlepveto) jetidtight="tightLepVeto";





}


void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::SetMuon(const Muon& _l1){
  mu1=_l1;  
}





bool TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::CheckIsMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;

  //vector<Muon> v_muon;
  vector<int> v_muonidx;

  //v_muon=noveto ? GetSingleMuRecoNoVeto(TriggerSafeCut_muon1) : GetSingleMuReco(TriggerSafeCut_muon1);
  v_muonidx=noveto ? GetSingleMuRecoNoVetoIdx(TriggerSafeCut_muon1) : GetSingleMuRecoIdx(TriggerSafeCut_muon1);
  //vector<Electron> JHAnalyzerBase::GetSingleElReco(double ptmin, double etacut, double ptveto, double ptveto2, double etacut2){//ptveto2 and etacut2 -->for add. muon

  //if( v_muon.size() < 1) return 0;
  if( v_muonidx.size() < 1) return 0;
  //SetMuon(v_muon[0]);
  v_tightmuonidx={v_muonidx[0]};
  SetMuon(AllMuons[v_muonidx[0]]);

  return 1;
}  

void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::SetElectron(const Electron& _l1){
  el1=_l1;
}



bool TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::CheckIsElectronChannel(){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  //vector<Electron> v_electron;
  vector<int> v_electronidx;
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  
  //v_electron=noveto ? GetSingleElRecoNoVeto(TriggerSafeCut_electron1) : GetSingleElReco(TriggerSafeCut_electron1);
  v_electronidx=noveto ? GetSingleElRecoNoVetoIdx(TriggerSafeCut_electron1) : GetSingleElRecoIdx(TriggerSafeCut_electron1);
  
  //if( v_electron.size() < 1) return 0;
  if( v_electronidx.size() < 1) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  //SetElectron(v_electron[0]);
  v_tightelectronidx={v_electronidx[0]};
  SetElectron(AllElectrons[v_electronidx[0]]);
  return 1;
}  

void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  if(measure_btageff||measure_btageff_tight) btagsf=1;
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  //Muon
  if(IsMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];//im goona use r_
  }
  else if(IsElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }
  
}

void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::RunReco(){

  IsMuonChannel=false;
  IsElectronChannel=false;
  v_tightmuonidx.clear();
  v_tightelectronidx.clear();

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
    SetEventWeight();
    Measure_MCbtagEff();
    return;
  }



  if(measure_btageff_partonFlavour){
    SetEventWeight();
    Measure_MCbtagEff_PartonFlavour();
    return;
  }

  if(measure_btageff_partonFlavour_bonly){
    SetEventWeight();
    Measure_MCbtagEff_PartonFlavour_bonly();
    return;
  }


  LepSign= l1.Charge() > 0 ? "Plus" : "Minus";
  //----Jet---//
  v_tightlep={l1};
  v_tightjet=GetTightJet(v_tightlep,30,jetetacut,jetidtight,JETPUID,!NoJetVeto);

  if(measure_btageff_tight){
    SetEventWeight();
    Measure_MCbtagEff_GivenJets(v_tightjet);
    return;
  }

  
  //vector<Jet> JHAnalyzerBase::GetTightJet(const vector<Lepton> &v_tightlep, double ptmin, double etacut, TString JetID, TString _JetPUID){
  //  vector<Jet> GetTightJet(const vector<Lepton> &TightLeptonCollection ,double ptmin, double etacut, TString JetID="tight", TString _JETPUID="");

  //btagsf=1;///Only for this analyzer. Unset the btag eff correction
  //250429 -> Other jets effdata/effmc effects will be cancelled. So, we dont have to remove charge indep. btagsf?

  if(!ApplyBtagSF) btagsf=1;
  
  v_bjetidx=GetBJetIdx(v_tightjet);
  nbjet=v_bjetidx.size();
  if(nbjet < 1) return;
  njet=v_tightjet.size();
  if(v_tightjet.size()<4) return;
  //--Now Objects are ready--//
  SetEventWeight();

  
  if(RunBasicObjectOnly){
    FillHistOtherObject("BaselineSelection");
    FillHistOtherObject("BaselineSelection__"+LepCh);
  }
  else if(!runSys){
    FillHistOtherObject("BaselineSelection");
    FillHistOtherObject("BaselineSelection__"+LepCh);
  }
  Run();

}
void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::Run(){
  iblep=-1;
  ibhad=-1;
  iq1=-1;
  iq2=-1;
  vz_fit=0.0;
  ////Minimal Chi2 Method - kin fitter
  pair<vector<int>,double> v_jetidxset_and_vz_chi2=GetJetIndexSet_Chi2_1b(l1, CurrentMET, v_tightjet, v_bjetidx[0],chi2kincut);
  //pair<vector<int>,double> JHAnalyzerBase::GetJetIndexSet_Chi2_1b(Lepton &_l1, TLorentzVector &_met,vector<Jet> &_v_tightjet, int bjetidx, bool chi2kincut){


  //for debug
  /*
  if(nominalevent || electronscale00event){
    cout << "[chi2 inputs -btagged jet info]" << endl;
    cout << "v_tightjet[v_bjetidx[0]].Pt()=" << v_tightjet[v_bjetidx[0]].Pt() << endl;
    cout << "v_tightjet[v_bjetidx[0]].Eta()=" << v_tightjet[v_bjetidx[0]].Eta() << endl;
    cout << "v_tightjet[v_bjetidx[0]].Phi()=" << v_tightjet[v_bjetidx[0]].Phi() << endl;
    cout << "v_tightjet[v_bjetidx[0]].GetTaggerResult(JetTagging::DeepJet)=" << v_tightjet[v_bjetidx[0]].GetTaggerResult(JetTagging::DeepJet) << endl;
    cout << "[chi2 inputs - others]" << endl;
    cout << "CurrentMET=" <<endl;
    cout << "CurrentMET.Pt()=" << CurrentMET.Pt() <<endl;
    cout << "CurrentMET.Phi()=" << CurrentMET.Phi() <<endl;
    cout << "CurrentMET.Px()=" << CurrentMET.Px() <<endl;
    cout << "CurrentMET.Py()=" << CurrentMET.Py() <<endl;
    cout << "[l1]PtEtaPhi=" << l1.Pt() << "," << l1.Eta() << "," << l1.Phi() << endl; 
    cout << "[TightJets]" << endl;
    for(auto& tj : v_tightjet){
      cout << "(Pt,Eta)=" << "(" <<tj.Pt() << "," << tj.Eta() << ")" << endl; 
    }

  }
  */

  //end for debug

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


  
  if(v_bjetidx[0]!=iblep && v_bjetidx[0]!=ibhad){
    cout << "tagged bjet is not assigned to blep OR bhad" << endl;
    cout << "v_bjetidx[0]=" << v_bjetidx[0] << endl;
    cout << "iblep=" << iblep << endl;
    cout << "ibhad=" << ibhad << endl;
    1/0;
  }
  if(RunBasicObjectOnly) {
    FillHistOtherObject("AfterChi2Fitter");
    FillHistOtherObject("AfterChi2Fitter__"+LepCh);
  } else if(!runSys){
    FillHistOtherObject("AfterChi2Fitter");
    FillHistOtherObject("AfterChi2Fitter__"+LepCh);
  }

  if(RunBasicObjectOnly) return;

  //----
  neutrino_cand.SetPxPyPzE(CurrentMET.Px(),CurrentMET.Py(),vz_fit, sqrt(pow(CurrentMET.Pt(),2) + pow(vz_fit,2) ));
  SetTopAndW();

  //----now iblep and ibhad are set.
  if(newlepveto){

    bool HasAddLep=HasVetoLepton_NotTightLeps_NotWithinJets(v_tightmuonidx,v_tightelectronidx ,&v_tightjet[iblep],&v_tightjet[ibhad]);
    //bool HasAddLep=HasVetoLepton_NotTightLeps_NotWithinJets(v_tightmuonidx,v_tightelectronidx ,&v_tightjet[iblep],&v_tightjet[ibhad]);
    //bool HasAddLep=HasVetoLepton_NotTightLeps_NotWithinJets(v_tightmuonidx,v_tightelectronidx ,{v_blep,v_bhad});
    //  bool HasVetoLepton_NotTightLeps_NotWithinJets(const vector<int>& _v_tightmuonidx, const vector<int>& _v_tightelectronidx, const vector<TLorentzVector>& _v_jet);

    
    if(HasAddLep) return;
  }
    

  ///--
  /// probe b is the blep or bhad which is not v_bjetidx[0]
  // 

  

  /*
  if(IsTTLJSample){
    if(v_bjetidx[0]==ibhad){//if tag b is bhad, probe is blep
      RunBJet("bJetLeptonicSide",iblep,bLep_True_genidx,Tlep_cand);
    }
    else{//if tag b is blep, probe is bhad
      RunBJet("bJetHadronicSide",ibhad,bHad_True_genidx,Thad_cand);
    }
  }
  else{
    if(v_bjetidx[0]==ibhad){//if tag b is bhad, probe is blep
      RunBJet("bJetLeptonicSide",iblep,-1,Tlep_cand);
    }
    else{//if tag b is blep, probe is bhad
      RunBJet("bJetHadronicSide",ibhad,-1,Thad_cand);
    }
  }
  */
  if(v_bjetidx[0]==ibhad){//if tag b is bhad, probe is blep
    RunBJet("bJetLeptonicSide",iblep,-1,Tlep_cand);
  }
  else{//if tag b is blep, probe is bhad
    RunBJet("bJetHadronicSide",ibhad,-1,Thad_cand);
  }


}




void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::RunBJet(TString bjetname, int bjetidx, int bgenidx, TLorentzVector &Tcand){
  //----Before analyzing the current bjet (whose jetidx = bjetidx),
  // Add suffix to ProcessName if the bjet from b- OR b+ OR light parton

  //This is "probe" jet
  //probe pass is
  //double btagscore=jet.GetTaggerResult(JetTagging::DeepJet);
  // btagscore < btagcut

  bool isMatched=false;

  ///---Let's Check matching OR not (if it is TTLJ sample <=> bgenidx>-1)---//
  int this_partonFlavour=-9999;
  int this_hadronFlavour=v_tightjet[bjetidx].hadronFlavour();
  //TString hsuffix="__Hadron"+std::to_string(this_hadronFlavour);
  
  TString hsuffix="__Hadron"+std::to_string(this_hadronFlavour);
  if(this_hadronFlavour==5){
    hsuffix="__HadronB";
  }
  else{
    hsuffix="__HadronOthers";
  }
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
    ProcessName=MCSample+"_"+bsuffix+hsuffix;//ProcessName ===> ~Origin of the process
  }  //Add bjetname Suffix
  else{
    if(!IsDATA){
      this_partonFlavour = v_tightjet[bjetidx].partonFlavour();
      TString psuffix="From"+std::to_string(this_partonFlavour);
      if(this_partonFlavour==5){
	psuffix="Frombminus";
      }
      else if(this_partonFlavour==-5){
	psuffix="Frombplus";
      }
      else{
	psuffix="FromOthers";
      }
      ProcessName=MCSample+"_"+psuffix+hsuffix;
    }


  }  //Add bjetname Suffix


  //
  cut_suffix=GetCutSuffix(v_tightjet[bjetidx].Pt(),v_tightjet[bjetidx].Eta());


  if(!runSys){
    FillHistBJet("Lepton"+LepSign+"_"+bjetname,           bjetidx,bgenidx,Tcand);
    FillHistBJet("Lepton"+LepSign+"_"+bjetname+cut_suffix,bjetidx,bgenidx,Tcand);
    if(isMatched){
      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_MATCHED",           bjetidx,bgenidx,Tcand);
      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_MATCHED"+cut_suffix,bjetidx,bgenidx,Tcand);
    }
  }//
  //FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__"+cut_suffix,bjetidx,bgenidx,Tcand);


  //double btagscore=jet.GetTaggerResult(JetTagging::DeepJet);
  // btagscore < btagcut
  double btagscore=v_tightjet[bjetidx].GetTaggerResult(JetTagging::DeepJet);

  //for debug
  /*
  if(nominalevent || electronscale00event){
    cout << "btagscore=" << btagscore << endl;
    cout << "btagcut=" << btagcut <<endl;
    cout << "v_tightjet[bjetidx].Pt()=" << v_tightjet[bjetidx].Pt() << endl;
    cout << "v_tightjet[bjetidx].Eta()=" << v_tightjet[bjetidx].Eta() << endl;
    cout << "v_tightjet[bjetidx].Phi()=" << v_tightjet[bjetidx].Phi() << endl;
  }

  if(nominalevent) nominal_LeptonPlus_bJetHadronicSide__FAIL__PT30To50__Eta0To0p8=0;
  if(electronscale00event) electronscale00_LeptonPlus_bJetHadronicSide__FAIL__PT30To50__Eta0To0p8=0;
  */
  //end for debug
  if(btagscore > btagcut){//probe pass
    FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__PASS"+cut_suffix,bjetidx,bgenidx,Tcand);
    FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__PASS",bjetidx,bgenidx,Tcand);
    /* For debug
    if(LepSign=="Minus" && bjetname=="bJetHadronicSide" && cut_suffix=="__PT30To50__Eta1p6To2"){
      if(nominalevent ) {
	nominal_LeptonMinus_bJetHadronicSide__PASS__PT30To50__Eta1p6To2=1;
	cout << "[nominal]LeptonMinus_bJetHadronicSide__PASS__PT30To50__Eta1p6To2" << endl;
      }
      if(muonscale00event){
	cout << "[scale00]LeptonMinus_bJetHadronicSide__PASS__PT30To50__Eta1p6To2" << endl;
	if(nominal_LeptonMinus_bJetHadronicSide__PASS__PT30To50__Eta1p6To2){
	  true;
	}
	else{
	  cout << "!!! This event is failed for nominal / but muonscale00 passes!!" << endl;
	  //cout << "fChain->GetReadEntry()=" << fChain->GetReadEntry() << endl;
	  cout << "event=" << event << endl;
	}
      }
    }
    */
    //[end]For debug



    
    //FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__"+cut_suffix+"__PASS",bjetidx,bgenidx,Tcand);
    if(!runSys) {
      
      if(isMatched){
	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_MATCHED__PASS",           bjetidx,bgenidx,Tcand);
	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_MATCHED__PASS"+cut_suffix,bjetidx,bgenidx,Tcand);
      }

    }
  }
  else{//probe fail
    FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__FAIL"+cut_suffix,bjetidx,bgenidx,Tcand);
    FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__FAIL",bjetidx,bgenidx,Tcand);
    //FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__"+cut_suffix+"__FAIL",bjetidx,bgenidx,Tcand);
    if(!runSys) {

      if(isMatched){
	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_MATCHED__FAIL",           bjetidx,bgenidx,Tcand);
	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_MATCHED__FAIL"+cut_suffix,bjetidx,bgenidx,Tcand);
      }
    }
    /*
    //For debug2//
    if(LepSign=="Plus" && bjetname=="bJetHadronicSide" && cut_suffix=="__PT30To50__Eta0To0p8"){
      if(nominalevent ) {
	nominal_LeptonPlus_bJetHadronicSide__FAIL__PT30To50__Eta0To0p8=1;
      }
      if(electronscale00event){
	electronscale00_LeptonPlus_bJetHadronicSide__FAIL__PT30To50__Eta0To0p8=1;
      }
    }
    //[middle end]For debug2//
    */
  }//end of probe pass/fail





  
  //For debug2
  /*
  if(electronscale00event){
    if(nominal_LeptonPlus_bJetHadronicSide__FAIL__PT30To50__Eta0To0p8!=electronscale00_LeptonPlus_bJetHadronicSide__FAIL__PT30To50__Eta0To0p8){
      cout << "!!! This event is different for nominal / but electronscale00 passes!!" << endl;
      cout << "nominal=" << nominal_LeptonPlus_bJetHadronicSide__FAIL__PT30To50__Eta0To0p8 << endl;
      cout << "electron00=" << electronscale00_LeptonPlus_bJetHadronicSide__FAIL__PT30To50__Eta0To0p8  << endl;
      cout << "event=" << event << endl;
      
    }
  }
  */
  //end of debug2
}

TString TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::GetCutSuffix(double this_bjet_pt,double this_bjet_eta){
  //jetpog_ptbins={20., 30., 50., 70., 100., 140., 200., 300., 600., 1000.}
  TString ret="";
  /*
  if(this_bjet_pt>1000.){
    ret="__PT1000ToInf";
  }
  else if(this_bjet_pt>600.){
    ret="__PT600To1000";
  }
  else if(this_bjet_pt>300.){
    ret="__PT300To600";
  }
  else if(this_bjet_pt>200.){
    ret="__PT200To300";
  }
  else if(this_bjet_pt>140.){
  */
  
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
    ret="__PT30To50";
  }
  else{
    ret="__PT0To30";
  }

  //{0.0, 0.8, 1.6, 2., 2.5};

  double this_bjet_aeta=fabs(this_bjet_eta);

  if(this_bjet_aeta > 2.){
    ret+="__Eta2To2p5";
  }
  else if(this_bjet_aeta > 1.6){
    ret+="__Eta1p6To2";
  }
  else if(this_bjet_aeta > 0.8){
    ret+="__Eta0p8To1p6";
  }
  else{
    ret+="__Eta0To0p8";
  }
  
  return ret;
  
}
//---For AN Object section, add MET lep jet bjet distributions are needed.

void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::FillHistOtherObject(TString cutname){
  //if(runSys) return;
  //v_bjetidx
  //l1
  //CurrentMET.Pt()
  //v_tightjet[bjetidx]
  for(auto& this_jet : v_tightjet){
    FillHist(cutname+"/jet_pt", this_jet.Pt(),weight,170,30,200);
    FillHist(cutname+"/jet_eta", this_jet.Eta(),weight,njetpog_etabins,jetpog_etabins);    
  }
  for(auto& this_ibjet : v_bjetidx){
    FillHist(cutname+"/bjet_pt", v_tightjet[this_ibjet].Pt(),weight,170,30,200);
    FillHist(cutname+"/bjet_eta", v_tightjet[this_ibjet].Eta(),weight,njetpog_etabins,jetpog_etabins);    
  }
  
  FillHist(cutname+"/lep_pt", l1.Pt(),weight,200,0,200);
  FillHist(cutname+"/lep_eta", l1.Eta(),weight,50,-2.5,2.5);

  FillHist(cutname+"/met", CurrentMET.Pt(),weight,50,0,200);

  FillHist(cutname+"/nPV",nPV,weight,100,0,100);
}

void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::FillHistBJet(TString cutname, int bjetidx,int bgenidx, TLorentzVector& Tcand){
  //if(!TurnOnFillHist) return;
  /*
  if(cutname.Contains("bJetLeptonicSide")){
    FillHist(cutname+"/Tcand_mass", Tcand.M(),weight,45,150,240);
  }
  else if(cutname.Contains("bJetHadronicSide")){
    FillHist(cutname+"/Tcand_mass", Tcand.M(),weight,70,100,240);
  }
  else{
     FillHist(cutname+"/Tcand_mass", Tcand.M(),weight,200,0,400);
  }
  */
  FillHist(cutname+"/Tcand_mass", Tcand.M(),weight,200,0,400);
  
  if(runSys) return;
  FillHist(cutname+"/Event", 0.5,weight,1,0,1);
  //if(scale00test) return;
  FillHist(cutname+"/bjet_pt", v_tightjet[bjetidx].Pt(),weight,njetpog_ptbins,jetpog_ptbins);
  FillHist(cutname+"/bjet_eta", v_tightjet[bjetidx].Eta(),weight,njetpog_etabins,jetpog_etabins);

  FillHist(cutname+"/bjet_pt_fine", v_tightjet[bjetidx].Pt(),weight,200,0,200);


  if(IsTTLJSample && (bgenidx > -1)){
    FillHist(cutname+"/bjet_pt_TTLJ_MATCH", v_tightjet[bjetidx].Pt(),weight,200,0,200);
    FillHist(cutname+"/true_b_pt_TTLJ_MATCH", gens[bgenidx].Pt(),weight,200,0,200);
    FillHist(cutname+"/bjet_pt__OVER__true_b_pt_TTLJ_MATCH", gens[bgenidx].Pt() ? v_tightjet[bjetidx].Pt()/gens[bgenidx].Pt() : 100. ,weight,200,0,4);

    //vz_fit
    //i_neutrino_GEN
    double vz_truth=gens[i_neutrino_GEN].Pz();
    FillHist(cutname+"/vz_fit__OVER__true_vz_TTLJ_MATCH", vz_truth ? vz_fit/vz_truth : 100. ,weight,400,-4,4);
    FillHist(cutname+"/vz_fit__TTLJ_MATCH", vz_fit ,weight,400,-400,400);
    FillHist(cutname+"/true_vz__TTLJ_MATCH", vz_truth ,weight,400,-400,400);

  }
  double M_blep_l = (v_tightjet[iblep] + l1 ).M();
  FillHist(cutname+"/M_blep_l", M_blep_l , weight , 300, 0, 300);
  FillHist(cutname+"/Tcand_mass_Wide", Tcand.M(),weight,200,0,400);

  //FillHist(cutname+"/bjet_dR_l", v_tightjet[bjetidx].DeltaR(l1),weight,100,0,5);

}



void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::SetTopAndW(){

  Wlep_cand=l1+neutrino_cand;
  Whad_cand=v_tightjet[iq1]+v_tightjet[iq2];
  Tlep_cand=Wlep_cand+v_tightjet[iblep];
  Thad_cand=Whad_cand+v_tightjet[ibhad];
}

///----OLD---///


void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::EventLoop(){
  RunReco();

}





void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::TruthLoop(){
  //it must be TTLJ samples
  if (IsTTLJSample){
    TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::RunLHEinfo();
    TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::RunGENinfo();
  }

}

void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::RunLHEinfo(){
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
void TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING::RunGENinfo(){
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


