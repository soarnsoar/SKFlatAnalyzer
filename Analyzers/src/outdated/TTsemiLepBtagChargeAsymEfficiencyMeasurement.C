#include "TTsemiLepBtagChargeAsymEfficiencyMeasurement.h"

TTsemiLepBtagChargeAsymEfficiencyMeasurement::TTsemiLepBtagChargeAsymEfficiencyMeasurement(){
  //runSys=true;
  //jetpog_etabins
  //jetpog_ptbins
}

TTsemiLepBtagChargeAsymEfficiencyMeasurement::~TTsemiLepBtagChargeAsymEfficiencyMeasurement(){
  //==== Destructor of this Analyzer
  if(apply_bchargeeff_TT){
    DeleteBChargeEff_TT();
  }
}

void TTsemiLepBtagChargeAsymEfficiencyMeasurement::initializeAnalyzer(){
  cout << "[TTsemiLepBtagChargeAsymEfficiencyMeasurement::initializeAnalyzer]" << endl;
  //TTsemiLepBtagChargeAsymEfficiencyMeasurement
  if(HasFlag("use_beff")){
    //----use this analyzer specific btag mc eff----//
    //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("TTsemiLepBtagChargeAsymEfficiencyMeasurement_"+MCSample+".root");
  }


  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupSingleLeptonChannel();
  noveto=false;
  if(HasFlag("noveto")){
    noveto=true;
  }
  TopMassWindow=HasFlag("TopMassWindow");
  ApplyBtagSF=HasFlag("ApplyBtagSF");


  //Jet Assignment Tool
  InitJetAssigenChi2Fitter();






}


void TTsemiLepBtagChargeAsymEfficiencyMeasurement::SetMuon(const Muon& _l1){
  mu1=_l1;
}

bool TTsemiLepBtagChargeAsymEfficiencyMeasurement::CheckIsMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;

  vector<Muon> v_muon;

  v_muon=noveto ? GetSingleMuRecoNoVeto(TriggerSafeCut_muon1) : GetSingleMuReco(TriggerSafeCut_muon1);
  //vector<Electron> JHAnalyzerBase::GetSingleElReco(double ptmin, double etacut, double ptveto, double ptveto2, double etacut2){//ptveto2 and etacut2 -->for add. muon

  if( v_muon.size()!=1) return 0;
  SetMuon(v_muon[0]);

  return 1;
}  

void TTsemiLepBtagChargeAsymEfficiencyMeasurement::SetElectron(const Electron& _l1){
  el1=_l1;
}


bool TTsemiLepBtagChargeAsymEfficiencyMeasurement::CheckIsElectronChannel(){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  vector<Electron> v_electron;
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  
  v_electron=noveto ? GetSingleElRecoNoVeto(TriggerSafeCut_electron1) : GetSingleElReco(TriggerSafeCut_electron1);
  
  if( v_electron.size()!=1) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  SetElectron(v_electron[0]);
  return 1;
}  

void TTsemiLepBtagChargeAsymEfficiencyMeasurement::SetEventWeight(){
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

void TTsemiLepBtagChargeAsymEfficiencyMeasurement::RunReco(){

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
  v_tightjet=GetTightJet(v_tightlep,30,jetetacut);

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



  Run();

}
void TTsemiLepBtagChargeAsymEfficiencyMeasurement::Run(){
  iblep=-1;
  ibhad=-1;
  iq1=-1;
  iq2=-1;
  vz_fit=0.0;
  ////Minimal Chi2 Method - kin fitter
  pair<vector<int>,double> v_jetidxset_and_vz_chi2=GetJetIndexSet_Chi2_1b(l1, CurrentMET, v_tightjet, v_bjetidx[0],TopMassWindow);


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
  

  //----
  neutrino_cand.SetPxPyPzE(CurrentMET.Px(),CurrentMET.Py(),vz_fit, sqrt(pow(CurrentMET.Pt(),2) + pow(vz_fit,2) ));
  SetTopAndW();

  ///--
  /// probe b is the blep or bhad which is not v_bjetidx[0]
  // 

  

  
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




}




void TTsemiLepBtagChargeAsymEfficiencyMeasurement::RunBJet(TString bjetname, int bjetidx, int bgenidx, TLorentzVector &Tcand){
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
    FillHistBJet("Lepton"+LepSign+"_"+bjetname,bjetidx,bgenidx,Tcand);
  }
  //FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__"+cut_suffix,bjetidx,bgenidx,Tcand);


  //double btagscore=jet.GetTaggerResult(JetTagging::DeepJet);
  // btagscore < btagcut
  double btagscore=v_tightjet[bjetidx].GetTaggerResult(JetTagging::DeepJet);
  //cout << "btagscore=" << btagscore << endl;
  //cout << "btagcut=" << btagcut <<endl;
  if(btagscore > btagcut){//probe pass
    FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__PASS",bjetidx,bgenidx,Tcand);
    //FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__"+cut_suffix+"__PASS",bjetidx,bgenidx,Tcand);
  }
  else{//probe fail
    FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__FAIL",bjetidx,bgenidx,Tcand);
    //FillHistBJet("Lepton"+LepSign+"_"+bjetname+"__"+cut_suffix+"__FAIL",bjetidx,bgenidx,Tcand);
  }
  

  
}

TString TTsemiLepBtagChargeAsymEfficiencyMeasurement::GetCutSuffix(double this_bjet_pt,double this_bjet_eta){
  //jetpog_ptbins={20., 30., 50., 70., 100., 140., 200., 300., 600., 1000.}
  TString ret="";
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
    ret="__PT140To200";    
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

  if(this_bjet_aeta<2.){
    ret+="__Eta2To2p5";
  }
  else if(this_bjet_aeta<1.6){
    ret+="__Eta1p6To2";
  }
  else if(this_bjet_aeta<0.8){
    ret+="__Eta0p8To1p6";
  }
  else{
    ret+="__Eta0To0p8";
  }
  
  return ret;
  
}


void TTsemiLepBtagChargeAsymEfficiencyMeasurement::FillHistBJet(TString cutname, int bjetidx,int bgenidx, TLorentzVector& Tcand){
  //if(!TurnOnFillHist) return;
  FillHist(cutname+"/Tcand_mass", Tcand.M(),weight,200,0,400);
  if(runSys) return;
  FillHist(cutname+"/bjet_pt", v_tightjet[bjetidx].Pt(),weight,njetpog_ptbins,jetpog_ptbins);
  FillHist(cutname+"/bjet_eta", v_tightjet[bjetidx].Eta(),weight,njetpog_etabins,jetpog_etabins);
  

  FillHist(cutname+"/Event", 0.5,weight,1,0,1);


  //FillHist(cutname+"/bjet_dR_l", v_tightjet[bjetidx].DeltaR(l1),weight,100,0,5);

}



void TTsemiLepBtagChargeAsymEfficiencyMeasurement::SetTopAndW(){

  Wlep_cand=l1+neutrino_cand;
  Whad_cand=v_tightjet[iq1]+v_tightjet[iq2];
  Tlep_cand=Wlep_cand+v_tightjet[iblep];
  Thad_cand=Whad_cand+v_tightjet[ibhad];
}

///----OLD---///


void TTsemiLepBtagChargeAsymEfficiencyMeasurement::EventLoop(){
  RunReco();

}





void TTsemiLepBtagChargeAsymEfficiencyMeasurement::TruthLoop(){
  //it must be TTLJ samples
  if (IsTTLJSample){
    TTsemiLepBtagChargeAsymEfficiencyMeasurement::RunLHEinfo();
    TTsemiLepBtagChargeAsymEfficiencyMeasurement::RunGENinfo();
  }

}

void TTsemiLepBtagChargeAsymEfficiencyMeasurement::RunLHEinfo(){
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
void TTsemiLepBtagChargeAsymEfficiencyMeasurement::RunGENinfo(){
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


