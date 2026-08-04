#include "TTsemiLepChargeScoreAccuracyMeasurement.h"

TTsemiLepChargeScoreAccuracyMeasurement::TTsemiLepChargeScoreAccuracyMeasurement(){
  //runSys=true;
  //jetpog_etabins
  //jetpog_ptbins
}

TTsemiLepChargeScoreAccuracyMeasurement::~TTsemiLepChargeScoreAccuracyMeasurement(){
  //==== Destructor of this Analyzer

}

void TTsemiLepChargeScoreAccuracyMeasurement::initializeAnalyzer(){
  cout << "[TTsemiLepChargeScoreAccuracyMeasurement::initializeAnalyzer]" << endl;
  //TTsemiLepChargeScoreAccuracyMeasurement

  if(HasFlag("use_beff")){
    //----use this analyzer specific btag mc eff----//
    //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    //if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("TTsemiLepChargeScoreAccuracyMeasurement_"+MCSample+".root");
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("");

  }
  if(HasFlag("use_beff_dasym")){
    //----use this analyzer specific btag mc eff----//
    //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("",true);
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
  }  
  splitcharge=HasFlag("splitcharge");
  //TopMassWindow=HasFlag("TopMassWindow");
  chi2kincut=HasFlag("chi2kincut");
  

  //NoJetVeto
  NoJetVeto=HasFlag("NoJetVeto");
  //Jet Assignment Tool

  //noetabin
  noetabin=HasFlag("noetabin");
  
  InitJetAssigenChi2Fitter();
  Setup_bChargeIDEff();


  if(HasFlag("bdt2512.5")){
    LoadChargeScoreTool("2512.5","2512.5","2512.5",true);

  }
  else{
    LoadChargeScoreTool("2512.5","2512.5","2512.5",true);
  }



}


void TTsemiLepChargeScoreAccuracyMeasurement::SetMuon(const Muon& _l1){
  mu1=_l1;
}

bool TTsemiLepChargeScoreAccuracyMeasurement::CheckIsMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;

  //vector<Muon> v_muon;
  vector<int> v_muonidx;

  //v_muon=noveto ? GetSingleMuRecoNoVeto(TriggerSafeCut_muon1) : GetSingleMuReco(TriggerSafeCut_muon1);
  //vector<Electron> JHAnalyzerBase::GetSingleElReco(double ptmin, double etacut, double ptveto, double ptveto2, double etacut2){//ptveto2 and etacut2 -->for add. muon

  v_muonidx=noveto ? GetSingleMuRecoNoVetoIdx(TriggerSafeCut_muon1) : GetSingleMuRecoIdx(TriggerSafeCut_muon1);
  
  if( v_muonidx.size()<1) return 0;
  SetMuon(AllMuons[v_muonidx[0]]);
  v_tightmuonidx={v_muonidx[0]};

  return 1;
}  

void TTsemiLepChargeScoreAccuracyMeasurement::SetElectron(const Electron& _l1){
  el1=_l1;
}


bool TTsemiLepChargeScoreAccuracyMeasurement::CheckIsElectronChannel(){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  //vector<Electron> v_electron;
  vector<int> v_electronidx;
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  
  //v_electron=noveto ? GetSingleElRecoNoVeto(TriggerSafeCut_electron1) : GetSingleElReco(TriggerSafeCut_electron1);
  v_electronidx=noveto ? GetSingleElRecoNoVetoIdx(TriggerSafeCut_electron1) : GetSingleElRecoIdx(TriggerSafeCut_electron1);
  
  if( v_electronidx.size()<1) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  //SetElectron(v_electron[0]);
  SetElectron(AllElectrons[v_electronidx[0]]);
  return 1;
}  

void TTsemiLepChargeScoreAccuracyMeasurement::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  //Muon
  if(IsMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];//im goona use r_
  }
  else if(IsElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }
  
}

void TTsemiLepChargeScoreAccuracyMeasurement::RunReco(){

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



  LepSign= l1.Charge() > 0 ? "Plus" : "Minus";
  //----Jet---//
  v_tightlep={l1};
  v_tightjet=GetTightJet(v_tightlep,30,jetetacut,"tight",JETPUID,!NoJetVeto);
  //vector<Jet> JHAnalyzerBase::GetTightJet(const vector<Lepton> &v_tightlep, double ptmin, double etacut, TString JetID, TString _JetPUID){
  //  vector<Jet> GetTightJet(const vector<Lepton> &TightLeptonCollection ,double ptmin, double etacut, TString JetID="tight", TString _JETPUID="");

  //btagsf=1;///Only for this analyzer. Unset the btag eff correction
  //250429 -> Other jets effdata/effmc effects will be cancelled. So, we dont have to remove charge indep. btagsf?

  
  
  v_bjetidx=GetBJetIdx(v_tightjet);
  nbjet=v_bjetidx.size();
  if(nbjet < 2) return;
  njet=v_tightjet.size();
  if(v_tightjet.size()<4) return;

  if(measure_bchargeeff){
    SetEventWeight();
    //vector<Jet> JHAnalyzerBase::GetBJet(const vector<Jet> &v_Tightjet){
    vector<Jet> v_bjet=GetBJet(v_tightjet);
    MeasureMC_bChargeIDEff(v_bjet);
    return;
  }


  if(measure_bchargeacc){
    SetEventWeight();
    vector<Jet> v_bjet=GetBJet(v_tightjet);
    MeasureMC_bChargeAcc(v_bjet);
    return;
  }

  
  //--Now Objects are ready--//
  SetEventWeight();

  

  Run();

}

void TTsemiLepChargeScoreAccuracyMeasurement::Run(){
  iblep=-1;
  ibhad=-1;
  iq1=-1;
  iq2=-1;
  vz_fit=0.0;
  ////Minimal Chi2 Method - kin fitter
  pair<vector<int>,double> v_jetidxset_and_vz_chi2=GetJetIndexSet_Chi2(l1, CurrentMET, v_tightjet, v_bjetidx,chi2kincut);
  //pair<vector<int>,double> JHAnalyzerBase::GetJetIndexSet_Chi2(Lepton &_l1, TLorentzVector &_met,vector<Jet> &_v_tightjet, vector<int> &_v_bjetidx, bool _kincut){


  //[0]=ib1 = bLep cand's v_bjet index
  //[1]=ib2 = bHad cand's v_bjet index
  //[2]=iq1 = one of light quark candiate v_tightjet index
  //[3]=iq2 = one of light quark candiate v_tightjet index
  //ret.first[0]=ib1; ret.first[1]=ib2; ret.first[2]=iq1, ret.first[3]=iq2;
  iblep=v_jetidxset_and_vz_chi2.first[0];
  ibhad=v_jetidxset_and_vz_chi2.first[1];
  iq1=v_jetidxset_and_vz_chi2.first[2];
  iq2=v_jetidxset_and_vz_chi2.first[3];
  vz_fit=v_jetidxset_and_vz_chi2.second;

  
  if(iblep<0) return;
  if(ibhad<0) return;
  if(iq1<0) return;
  if(iq2<0) return;




  //----
  neutrino_cand.SetPxPyPzE(CurrentMET.Px(),CurrentMET.Py(),vz_fit, sqrt(pow(CurrentMET.Pt(),2) + pow(vz_fit,2) ));
  SetTopAndW();

  ///--
  /// probe b is the blep or bhad which is not v_bjetidx[0]
  // 

  if(newlepveto){
    //TLorentzVector v_blep = v_tightjet[iblep];
    //TLorentzVector v_bhad = v_tightjet[ibhad];

    bool HasAddLep=HasVetoLepton_NotTightLeps_NotWithinJets(v_tightmuonidx,v_tightelectronidx ,&v_tightjet[iblep],&v_tightjet[ibhad]);
    //bool HasAddLep=HasVetoLepton_NotTightLeps_NotWithinJets(v_tightmuonidx,v_tightelectronidx ,{v_blep,v_bhad});
    //bool HasAddLep=HasVetoLepton_NotTightLeps_NotWithinJets(v_tightmuonidx,v_tightelectronidx ,{v_tightjet[iblep],v_tightjet[ibhad]});
    //  bool HasVetoLepton_NotTightLeps_NotWithinJets(const vector<int>& _v_tightmuonidx, const vector<int>& _v_tightelectronidx, const vector<TLorentzVector>& _v_jet);
    
    if(HasAddLep) return;
  }
  

  
  RunBJet("bJetLeptonicSide",iblep,-1,Tlep_cand);
  RunBJet("bJetHadronicSide",ibhad,-1,Thad_cand);


}




void TTsemiLepChargeScoreAccuracyMeasurement::RunBJet(TString bjetname, int bjetidx, int bgenidx, TLorentzVector &Tcand){
  
  ///---Let's Check matching OR not (if it is TTLJ sample <=> bgenidx>-1)---//
  int this_partonFlavour=-9999;
  int this_hadronFlavour=v_tightjet[bjetidx].hadronFlavour();

  TString hsuffix="__Hadron"+std::to_string(this_hadronFlavour);
  if(this_hadronFlavour==5){
    hsuffix="__HadronB";
  }
  else{
    hsuffix="__HadronOthers";
  }
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





  //
  cut_suffix=GetCutSuffix(v_tightjet[bjetidx].Pt(),v_tightjet[bjetidx].Eta(),noetabin);
  TString cut_suffix_all=GetCutSuffix(v_tightjet[bjetidx].Pt(),v_tightjet[bjetidx].Eta(),false);

  if(!runSys){
    if(!splitcharge){
    FillHistBJet("Lepton_"+bjetname,           bjetidx,bgenidx,Tcand);
    FillHistBJet("Lepton_"+bjetname+cut_suffix,bjetidx,bgenidx,Tcand);
    }else{
    FillHistBJet("Lepton"+LepSign+"_"+bjetname,           bjetidx,bgenidx,Tcand);
    FillHistBJet("Lepton"+LepSign+"_"+bjetname+cut_suffix,bjetidx,bgenidx,Tcand);
    }
  }//

  //Count SLT leptons//
  jetscore=-9999;
  jetcharge=-9999;
  //-----One of the followings is the charge that we gonna choose-----//
  //muH, muL
  //eH, eL
  //jetH
  //jetOthers
  //---Lepton Charge case --//
  Muon* muonHigh;
  Muon* muonLow;

  int n_muonHigh=0;
  int n_muonLow=0;

  double muonHigh_score=-999.;
  double muonLow_score=-999.;

  Electron* electronHigh;
  Electron* electronLow;

  int n_electronHigh=0;
  int n_electronLow=0;

  double electronHigh_score=-999.;
  double electronLow_score=-999.;

  //float measured_charge=0;

  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    if(muon.DeltaR(v_tightjet[bjetidx]) > 0.4) continue;
    if(muon.RelIso() > 10.) continue;
    if(muon.Chi2()>10) continue;
    if(muon.TrackerLayers()<1) continue;
    if(muon.MatchedStations() <1) continue;
    
    SetMuonChargeScore(muon,v_tightjet[bjetidx]);
    double this_muon_score=GetMuonChargeScore();
    int this_muon_coeff=GetMuonChargeScoreCoeff();// if pass HighCut -> +1 // if pass LowCut -> -1
    if(this_muon_coeff==1){
      muonHigh=&muon;
      n_muonHigh+=1;
      muonHigh_score=this_muon_score;
    }else if(this_muon_coeff==-1){
      muonLow=&muon;
      n_muonLow+=1;
      muonLow_score=this_muon_score;
    }

    
  }//[end muon for loop]

  for(auto& electron : AllElectrons){
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(electron.Pt() < 5.) continue;
    if(electron.DeltaR(v_tightjet[bjetidx]) > 0.4) continue;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    if(electron.RelIso() > 10.) continue;
    if(electron.NMissingHits() != 0) continue;
    
    
    SetElectronChargeScore(electron,v_tightjet[bjetidx]);
    double this_electron_score=GetElectronChargeScore();
    int this_electron_coeff=GetElectronChargeScoreCoeff();// if pass HighCut -> +1 // if pass LowCut -> -1
    if(this_electron_coeff==1){
      electronHigh=&electron;
      n_electronHigh+=1;
      electronHigh_score=this_electron_score;
    }else if(this_electron_coeff==-1){
      electronLow=&electron;
      n_electronLow+=1;
      electronLow_score=this_electron_score;
    }

  }//[end electron for loop]
  

  //void TTsemiLepChargeScoreAccuracyMeasurement::FillHistBJet(TString cutname, int bjetidx,int bgenidx, TLorentzVector& Tcand){
  ///
  double weight_SLT=1.;
  weight_SLT=Get_SLTEff_Corr({v_tightjet[bjetidx]},{n_muonHigh>0},{n_muonLow>0},{n_electronHigh>0},{n_electronLow>0});
  if(weight_SLT>0)weight*= weight_SLT;

  if(n_muonHigh==1 && n_muonLow==0 && n_electronHigh==0 && n_electronLow==0){
    int measured_charge=muonHigh->Charge();
    TString measured_charge_str= measured_charge > 0 ? "Plus" : measured_charge < 0 ? "Minus" : "Zero";
    measured_charge_str="_Measured"+measured_charge_str;
    //double JHAnalyzerBase::Get_SLTEff_Corr(vector<Jet> &_v_Jet, vector<bool> _v_Has_muH, vector<bool> _v_Has_muL, vector<bool> _v_Has_eH, vector<bool> _v_Has_eL){
    if(!splitcharge){
      FillHistBJet("Lepton_"+bjetname+"_1muHOnly"+measured_charge_str,bjetidx,bgenidx,Tcand);
      FillHistBJet("Lepton_"+bjetname+"_1muHOnly"+measured_charge_str+cut_suffix,bjetidx,bgenidx,Tcand);
    }else{
      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_1muHOnly"+measured_charge_str,           bjetidx,bgenidx,Tcand);
      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_1muHOnly"+measured_charge_str+cut_suffix,bjetidx,bgenidx,Tcand);
    }
  }
  else if(n_muonHigh==0 && n_muonLow==1 && n_electronHigh==0 && n_electronLow==0){
    int measured_charge= -muonLow->Charge();
    TString measured_charge_str= measured_charge > 0 ? "Plus" : measured_charge < 0 ? "Minus" : "Zero";
    measured_charge_str="_Measured"+measured_charge_str;
    if(!splitcharge){
      FillHistBJet("Lepton_"+bjetname+"_1muLOnly"+measured_charge_str,           bjetidx,bgenidx,Tcand);
      FillHistBJet("Lepton_"+bjetname+"_1muLOnly"+measured_charge_str+cut_suffix,bjetidx,bgenidx,Tcand);
    }else{
      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_1muLOnly"+measured_charge_str,           bjetidx,bgenidx,Tcand);
      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_1muLOnly"+measured_charge_str+cut_suffix,bjetidx,bgenidx,Tcand);
    }
  }
  else if(n_muonHigh==0 && n_muonLow==0 && n_electronHigh==1 && n_electronLow==0){
    int measured_charge= electronHigh->Charge();
    TString measured_charge_str= measured_charge > 0 ? "Plus" : measured_charge < 0 ? "Minus" : "Zero";
    measured_charge_str="_Measured"+measured_charge_str;    
    if(!splitcharge){
      FillHistBJet("Lepton_"+bjetname+"_1eHOnly"+measured_charge_str,           bjetidx,bgenidx,Tcand);
      FillHistBJet("Lepton_"+bjetname+"_1eHOnly"+measured_charge_str+cut_suffix,bjetidx,bgenidx,Tcand);
    }else{
      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_1eHOnly"+measured_charge_str,           bjetidx,bgenidx,Tcand);
      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_1eHOnly"+measured_charge_str+cut_suffix,bjetidx,bgenidx,Tcand);
    }
  }
  else if(n_muonHigh==0 && n_muonLow==0 && n_electronHigh==0 && n_electronLow==1){
    int measured_charge= -electronLow->Charge();
    TString measured_charge_str= measured_charge > 0 ? "Plus" : measured_charge < 0 ? "Minus" : "Zero";
    measured_charge_str="_Measured"+measured_charge_str;    
    if(!splitcharge){
      FillHistBJet("Lepton_"+bjetname+"_1eLOnly"+measured_charge_str,           bjetidx,bgenidx,Tcand);
      FillHistBJet("Lepton_"+bjetname+"_1eLOnly"+measured_charge_str+cut_suffix,bjetidx,bgenidx,Tcand);
    }else{
      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_1eLOnly"+measured_charge_str,           bjetidx,bgenidx,Tcand);
      FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_1eLOnly"+measured_charge_str+cut_suffix,bjetidx,bgenidx,Tcand);
    }
  }  
  if(n_muonHigh==0 && n_muonLow==0 && n_electronHigh==0 && n_electronLow==0){

    SetJetChargeScore(v_tightjet[bjetidx]);
    jetscore=GetJetChargeScore();
    jetcharge=v_tightjet[bjetidx].Charge();
    int measured_charge= jetcharge > 0 ? +1 : jetcharge < 0 ? -1 : 0 ;
    TString measured_charge_str= measured_charge > 0 ? "Plus" : measured_charge < 0 ? "Minus" : "Zero";
    measured_charge_str="_Measured"+measured_charge_str;

    int jetcharge_coeff=GetJetChargeScoreCoeff();
    double weight_HighScoreJet=Get_HighScoreChargeTagID_Eff_Corr({v_tightjet[bjetidx]},{jetcharge_coeff==1});
    weight*=weight_HighScoreJet;
    if(jetcharge_coeff==1){
      if(!splitcharge){
	FillHistBJet("Lepton_"+bjetname+"_NoSL_jH"+measured_charge_str,           bjetidx,bgenidx,Tcand);
	FillHistBJet("Lepton_"+bjetname+"_NoSL_jH"+measured_charge_str+cut_suffix_all,bjetidx,bgenidx,Tcand);
      }else{
	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_NoSL_jH"+measured_charge_str,           bjetidx,bgenidx,Tcand);
	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_NoSL_jH"+measured_charge_str+cut_suffix_all,bjetidx,bgenidx,Tcand);      
      }
    }
    else{
      if(!splitcharge){
	FillHistBJet("Lepton_"+bjetname+"_NoSL_jOthers"+measured_charge_str,           bjetidx,bgenidx,Tcand);
	FillHistBJet("Lepton_"+bjetname+"_NoSL_jOthers"+measured_charge_str+cut_suffix_all,bjetidx,bgenidx,Tcand);
      }else{
	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_NoSL_jOthers"+measured_charge_str,           bjetidx,bgenidx,Tcand);
	FillHistBJet("Lepton"+LepSign+"_"+bjetname+"_NoSL_jOthers"+measured_charge_str+cut_suffix_all,bjetidx,bgenidx,Tcand);      
      }
    }

    weight=weight/weight_HighScoreJet;
  }//[end] No SLT
  if(weight_SLT>0)weight= weight/weight_SLT;

}

TString TTsemiLepChargeScoreAccuracyMeasurement::GetCutSuffix(double this_bjet_pt,double this_bjet_eta,bool ignore_etabin){
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
  if(ignore_etabin){
    return ret;
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

void TTsemiLepChargeScoreAccuracyMeasurement::FillHistOtherObject(TString cutname){
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

void TTsemiLepChargeScoreAccuracyMeasurement::FillHistBJet(TString cutname, int bjetidx,int bgenidx, TLorentzVector& Tcand){

  FillHist(cutname+"/Tcand_mass", Tcand.M(),weight,70,100,240);
  FillHist(cutname+"/Event", 0.5,weight,1,0,1);  
  if(runSys) return;


  FillHist(cutname+"/bjet_pt", v_tightjet[bjetidx].Pt(),weight,njetpog_ptbins,jetpog_ptbins);
  FillHist(cutname+"/bjet_eta", v_tightjet[bjetidx].Eta(),weight,njetpog_etabins,jetpog_etabins);

  FillHist(cutname+"/bjet_pt_fine", v_tightjet[bjetidx].Pt(),weight,200,0,200);



  double M_blep_l = (v_tightjet[iblep] + l1 ).M();
  FillHist(cutname+"/M_blep_l", M_blep_l , weight , 300, 0, 300);
  FillHist(cutname+"/Tcand_mass_Wide", Tcand.M(),weight,200,0,400);



}



void TTsemiLepChargeScoreAccuracyMeasurement::SetTopAndW(){

  Wlep_cand=l1+neutrino_cand;
  Whad_cand=v_tightjet[iq1]+v_tightjet[iq2];
  Tlep_cand=Wlep_cand+v_tightjet[iblep];
  Thad_cand=Whad_cand+v_tightjet[ibhad];
}

///----OLD---///


void TTsemiLepChargeScoreAccuracyMeasurement::EventLoop(){
  RunReco();

}





void TTsemiLepChargeScoreAccuracyMeasurement::TruthLoop(){
  //it must be TTLJ samples
  if (IsTTLJSample){
    TTsemiLepChargeScoreAccuracyMeasurement::RunLHEinfo();
    TTsemiLepChargeScoreAccuracyMeasurement::RunGENinfo();
  }

}

void TTsemiLepChargeScoreAccuracyMeasurement::RunLHEinfo(){
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
void TTsemiLepChargeScoreAccuracyMeasurement::RunGENinfo(){
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


