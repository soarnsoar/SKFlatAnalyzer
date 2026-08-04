#include "PreselectionToBDTRegionAnalyzer.h"
#include <map>
PreselectionToBDTRegionAnalyzer::PreselectionToBDTRegionAnalyzer(){
  //runSys=true;

  //JHAnalyzerBase::SetupDiLeptonChannel();  
}

PreselectionToBDTRegionAnalyzer::~PreselectionToBDTRegionAnalyzer(){
  //==== Destructor of this Analyzer
}

void PreselectionToBDTRegionAnalyzer::initializeAnalyzer(){

  if(HasFlag("use_beff")){
    //----use this analyzer specific btag mc eff----//
    //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("PreselectionAnalyzer_"+MCSample+".root");// with kincut
  }


  if(HasFlag("use_beffasym")){
    //----use this analyzer specific btag mc eff----//
    //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    //if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("PreselectionAnalyzer_"+MCSample+".root",true);// with kincut
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("",true);// with kincut
    //use default mc eff
  }
  
  
  cout << "[PreselectionToBDTRegionAnalyzer::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupDiLeptonChannel();
  IsDYSample=false;
  if(MCSample.Contains("DYJets")||MCSample.Contains("ZToEE")||MCSample.Contains("ZToMuMu")||MCSample.Contains(TRegexp("DY[0-9]Jets"))) IsDYSample=true;
  cout << "[IsDYSample]=" << IsDYSample << endl;

  if(HasFlag("jetpuid_tight")){
    _JETPUID="T";
    cout << "[JETPUID] TIGHT" << endl;
  }
  else if(HasFlag("jetpuid_medium")){
    _JETPUID="M";
    cout << "[JETPUID] MEDIUM" << endl;
  }
  else if(HasFlag("jetpuid_loose")){
    cout << "[JETPUID] LOOSE" << endl;
    _JETPUID="L";
  }
  else if(HasFlag("nojetpuid")){
    cout << "[JETPUID] NOCUT" << endl;
    _JETPUID="";
  }
  else{
    cout << "[JETPUID] DEFAULT===>" << endl;
    _JETPUID="";
  }

  //_JETPUID="T";
  
  check_tmva_input=false;
  if(HasFlag("check_tmva_input")){
    check_tmva_input=true;
    cout << "check_tmva_input -> true" << endl;
  }
  //lepveto
  lepveto=false;
  if(HasFlag("lepveto")){
    lepveto=true;
    cout << "lepveto -> true" << endl;
  }

  newlepveto=false;
  if(HasFlag("newlepveto")){
    newlepveto=true;
    cout << "newlepveto -> true" << endl;
  }  


  //kincutopt=HasFlag("kincutopt");
  //bdtopt=HasFlag("bdtopt");
  doxrange=HasFlag("doxrange");
  xrangetree=HasFlag("xrangetree");
  bdtcut=HasFlag("bdtcut");//applying bdtcut
  //For x range study//
  if(xrangetree){
    jhchoi_newtree=new TTree("presel","presel");
    jhchoi_newtree->Branch("weight",&weight);
    jhchoi_newtree->Branch("bjet_eta",&bjet_eta);
    jhchoi_newtree->Branch("bjet_y",&bjet_y);
    jhchoi_newtree->Branch("z_eta",&z_eta);
    jhchoi_newtree->Branch("z_y",&z_y);
    jhchoi_newtree->Branch("x_b",&x_b);
    jhchoi_newtree->Branch("x_g",&x_g);
  }

  addxsuffix=HasFlag("addxsuffix");
  addregionsuffix=HasFlag("addregionsuffix");
  //charge
  cout << "[LoadChargeScoreTool]" << endl;
  //void LoadChargeScoreTool(TString muon_version="2512.4",TString electron_version="2512.4", TString jet_version="2512.4", bool applycut=false);




  if(HasFlag("bdt2512.5")){
    LoadChargeScoreTool("2512.5","2512.5","2512.5",bdtcut);

  }
  else if(HasFlag("bdt2512.4")){
    LoadChargeScoreTool("2512.4","2512.4","2512.4",0);
  }

  else if(HasFlag("bdt2512.3")){
    LoadChargeScoreTool("2512.3","2512.3","2512.3",0);
  }
  else{
    LoadChargeScoreTool("2512.3","2512.3","2512.3",0);
  }

  
  //--Set maxMET,min_dphi_z_b,min_z_pt,max_ptzb cuts
  /*
  if(DataEra=="2016preVFP"){
    maxMET=65.0;
    min_dphi_z_b=-1;
    min_z_pt=5.;
    max_ptzb=500.;
  }else if(DataEra=="2016postVFP"){
    maxMET=50.0;
    min_dphi_z_b=1.4;
    min_z_pt=15.;
    max_ptzb=360.0;
  }else if(DataEra=="2017"){
    maxMET=80.0;
    min_dphi_z_b=-1;
    min_z_pt=20.;
    max_ptzb=580.0;
  }else if(DataEra=="2018"){
    maxMET=75.0;
    min_dphi_z_b=-1;
    min_z_pt=5.;
    max_ptzb=600.0;
  }
  else{
    cout << "Not Valid DataEra-->" << DataEra << endl;
  }
  */
  maxMET=70.0;
  min_dphi_z_b=-1;
  min_z_pt=5.0;
  max_ptzb=500.0;

  apply_chargeid_eff_corr=HasFlag("apply_chargeid_eff_corr");
  if(apply_chargeid_eff_corr){
    cout << "apply_chargeid_eff_corr!!" << endl;
    //Setup_bChargeIDEff("PreselectionToBDTRegionAnalyzer_"+MCSample+".root");
    Setup_bChargeIDEff();
  }

  apply_chargeid_acc_corr=HasFlag("apply_chargeid_acc_corr");
  
  if(apply_chargeid_acc_corr){
    cout << "apply_chargeid_acc_corr!!" << endl;
    Setup_bChargeAcc();
  }
}


void PreselectionToBDTRegionAnalyzer::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;
  
}

bool PreselectionToBDTRegionAnalyzer::CheckIsDiMuonChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  //vector<int> v_muonidx=GetIdxDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  //vector<Muon> v_muon=lepveto ?  GetDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2) :  GetDiMuRecoNoVeto(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  vector<int> v_muonidx=lepveto ?  GetDiMuRecoIdx(TriggerSafeCut_muon1, TriggerSafeCut_muon2) :  GetDiMuRecoNoVetoIdx(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  if( v_muonidx.size()<2) return 0;
  double mll=(AllMuons[v_muonidx[0]]+AllMuons[v_muonidx[1]]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;

  SetMuon(AllMuons[v_muonidx[0]],AllMuons[v_muonidx[1]]);
  v_tightmuonidx={v_muonidx[0],v_muonidx[1]};
  return 1;
}  

void PreselectionToBDTRegionAnalyzer::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;
  
}


bool PreselectionToBDTRegionAnalyzer::CheckIsDiElectronChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  //vector<Electron> v_electron=lepveto ? GetDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2) :GetDiElRecoNoVeto(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  vector<int> v_electronidx=lepveto ? GetDiElRecoIdx(TriggerSafeCut_electron1, TriggerSafeCut_electron2) :GetDiElRecoNoVetoIdx(TriggerSafeCut_electron1, TriggerSafeCut_electron2); 
  if( v_electronidx.size()<2) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  
  double mll=(AllElectrons[v_electronidx[0]]+AllElectrons[v_electronidx[1]]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;
  SetElectron(AllElectrons[v_electronidx[0]],AllElectrons[v_electronidx[1]]);
  v_tightelectronidx={v_electronidx[0],v_electronidx[1]};  
  return 1;
}  

void PreselectionToBDTRegionAnalyzer::SetEventNormWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full");
}

void PreselectionToBDTRegionAnalyzer::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  //----ZpT weight For DY
  //----DY WEAK NLO
  //---z0 weight
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  
  if(IsDiMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsDiElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }


}

void PreselectionToBDTRegionAnalyzer::RunBasicZregion(){
  if(xrangetree){
    if(!IsDYbplus && !IsDYbminus){
      return;
    }
  }
  IsDiMuonChannel=false;
  IsDiElectronChannel=false;
  v_tightmuonidx.clear();
  v_tightelectronidx.clear();
  double min_mll = 60;
  double max_mll = 120;

  IsDiMuonChannel=CheckIsDiMuonChannel(min_mll,max_mll);
  if(!IsDiMuonChannel) IsDiElectronChannel=CheckIsDiElectronChannel(min_mll,max_mll);

  



  LepCh="";
  if(IsDiMuonChannel){
    //vZ=(*mu1)+(*mu2);
    vZ=mu1+mu2;
    LepCh="mm";
    l1=mu1;
    l2=mu2;
    l1_uncorr.SetPtEtaPhiM(mu1.MiniAODPt(), mu1.Eta(), mu1.Phi(), mu1.M()  );
    l2_uncorr.SetPtEtaPhiM(mu2.MiniAODPt(), mu2.Eta(), mu2.Phi(), mu2.M()  );
  }
  else if(IsDiElectronChannel){
    //vZ=GetDiElectronVector();
    vZ=el1+el2;
    LepCh="ee";
    //l1=AllElectrons[el1idx];
    //l2=AllElectrons[el2idx];
    l1=el1;
    l2=el2;
    l1_uncorr.SetPtEtaPhiM(el1.UncorrPt(), el1.Eta(), el1.Phi(), el1.M()  );
    l2_uncorr.SetPtEtaPhiM(el2.UncorrPt(), el2.Eta(), el2.Phi(), el2.M()  );
  }  
  else{
    return;
  }
  //----Jet---//
  v_tightlep={l1,l2};
  v_tightjet=GetTightJet(v_tightlep,30,jetetacut,"tight",_JETPUID);
  v_bjet=GetBJet(v_tightjet);


  njet=v_tightjet.size();
  nbjet=v_bjet.size();
  met_pt=CurrentMET.Pt();
  z_pt=vZ.Pt();
  //--Now Objects are ready--//
  SetEventWeight();  


  //----Let's select and fillhist
  
  if(nbjet!=1) return ;
  //  bool HasVetoLepton_NotTightLeps_NotWithinJets(const vector<int>& _v_tightmuonidx, const vector<int>& _v_tightelectronidx, const vector<TLorentzVector>& _v_jet);
  if(newlepveto){
    if (HasVetoLepton_NotTightLeps_NotWithinJets(v_tightmuonidx,v_tightelectronidx,&v_bjet[0])  ) return;
  }

  
  dphi_z_b= fabs(v_bjet[0].DeltaPhi(vZ));
  ptzb=(v_bjet[0]+vZ).Pt();  
  if(met_pt > maxMET) return;//updated 251222
  if(ptzb>max_ptzb) return;
  if(z_pt<min_z_pt) return;

  if(measure_btageff){

    Measure_MCbtagEff();
    return;
  }

  if(measure_bchargeeff){
    //vector<Jet> v_bjet=GetBJet(v_tightjet);
    MeasureMC_bChargeIDEff(v_bjet);
    return;
  }

  
  bjet_y=v_bjet[0].Rapidity();
  bjet_eta=v_bjet[0].Eta();
  z_eta=vZ.Eta();
  z_y=vZ.Rapidity();
  if(IsDYbplus || IsDYbminus){
    if(xrangetree){    
      jhchoi_newtree->Fill();	
    }
  }
  //-------xregion-----//
  TString suffix_rapidity_region="";
  int suffix_rapidity_region_idx=-1;
  if((bjet_y-z_y)*z_y>0 && fabs(bjet_y-z_y)>0.4){
    suffix_rapidity_region="low_peak";
    suffix_rapidity_region_idx=1;
  }else if((bjet_y-z_y)*z_y>0 && fabs(bjet_y-z_y)<0.4){
    suffix_rapidity_region="broad";
    suffix_rapidity_region_idx=4;
  }else if((bjet_y-z_y)*z_y<0 && fabs(z_y)>1.2){
    suffix_rapidity_region="high_peak";
    suffix_rapidity_region_idx=3;
  }else{
    suffix_rapidity_region="mid_peak";
    suffix_rapidity_region_idx=2;
  }
  suffix_rapidity_region="__"+suffix_rapidity_region;
  if(i_proc==1 && addregionsuffix) ProcessName+=suffix_rapidity_region;
  //addxsuffix
  //------


  v_muonscore.clear();
  v_muoncharge.clear();
  v_electronscore.clear();
  v_electroncharge.clear();
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

  float measured_charge=0;
  
  
  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    if(muon.DeltaR(v_bjet[0]) > 0.4) continue;
    if(muon.RelIso() > 10.) continue;
    if(muon.Chi2()>10) continue;
    if(muon.TrackerLayers()<1) continue;
    if(muon.MatchedStations() <1) continue;

    SetMuonChargeScore(muon,v_bjet[0]);
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
  //belectronvar this_belectron;
  for(auto& electron : AllElectrons){
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(electron.Pt() < 5.) continue;
    if(electron.DeltaR(v_bjet[0]) > 0.4) continue;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    if(electron.RelIso() > 10.) continue;
    if(electron.NMissingHits() != 0) continue;
    
    //this_belectron=Get_belectronvar(electron,v_bjet[0]);
    
    SetElectronChargeScore(electron,v_bjet[0]);
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

  
  SetJetChargeScore(v_bjet[0]);
  jetscore=GetJetChargeScore();
  jetcharge=v_bjet[0].Charge();

  ///----determine the type of this event---//
  if(n_muonHigh<10 && n_muonLow<10 && n_electronHigh<10 && n_electronLow<10){
    if(!runSys)FillHist("ll_1b/nSLT",n_muonHigh+n_muonLow*10+n_electronHigh*100+n_electronLow*1000,weight,10000,0,10000);
    if(!runSys)FillHist("ll_1b/HasSLT",(n_muonHigh>0)
			+(n_muonLow>0)*2
			+(n_electronHigh>0)*4
			+(n_electronLow>0)*8
			,weight,20,0,20);
    
  }

  if(apply_chargeid_eff_corr){
    //double JHAnalyzerBase::Get_SLTEff_Corr(vector<Jet> &_v_Jet, vector<bool> _v_Has_muH, vector<bool> _v_Has_muL, vector<bool> _v_Has_eH, vector<bool> _v_Has_eL){
    weight*=Get_SLTEff_Corr({v_bjet[0]},{n_muonHigh>0},{n_muonLow>0},{n_electronHigh>0},{n_electronLow>0});
  }

  TString bChargeType="NOTUSE";
  
  if(n_muonHigh==1 && n_muonLow==0 && n_electronHigh==0 && n_electronLow==0){
    //RunMuonHigh();
    //FillHistAll_bmuon(TString cutname,bmuonvar this_bmuon)
    //Get_bmuonvar(muon,v_bjet[0])
    //double JHAnalyzerBase::Get_SLTEff_Corr_givenJet(Jet& thisJet, bool Has_muH, bool Has_muL, bool Has_eH,bool Has_eL,
    //               JHAnalyzerBase::SYSDIR SystDir, JHAnalyzerBase::PtBin SystPtBin, JHAnalyzerBase::SLT SystID){


    bmuonvar this_bmuonvar=Get_bmuonvar(*muonHigh,v_bjet[0]);
    bjetvar this_bjetvar=Get_bjetvar(v_bjet[0]);
    measured_charge=muonHigh->Charge();


    if(apply_chargeid_acc_corr){
      weight*=GetChargeAccCorr(v_bjet[0],0,measured_charge);
    }
    FillHistAll_bmuon("ll__muonHigh",this_bmuonvar);
    FillHistAll_bjet("ll__muonHigh",this_bjetvar);
    FillHistAll2("ll__muonHigh");


    FillHist("ll__muonHigh/bmuon_chargescore",muonHigh_score,weight,240,-1.2,1.2);
    FillHist("ll__muonHigh/norm_bmuon_chargescore_dot_charge",(1+muonHigh_score)/2*muonHigh->Charge(),weight,240,-1.2,1.2);
    bChargeType="muH";
  }
  else if(n_muonHigh==0 && n_muonLow==1 && n_electronHigh==0 && n_electronLow==0){
    //RunMuonLow();
    bmuonvar this_bmuonvar=Get_bmuonvar(*muonLow,v_bjet[0]);
    bjetvar this_bjetvar=Get_bjetvar(v_bjet[0]);

    measured_charge=-2*muonLow->Charge();
    if(apply_chargeid_acc_corr){
      weight*=GetChargeAccCorr(v_bjet[0],1,measured_charge);
    }
    FillHistAll_bmuon("ll__muonLow",this_bmuonvar);
    FillHistAll_bjet("ll__muonLow",this_bjetvar);
    FillHistAll2("ll__muonLow");
    
    FillHist("ll__muonLow/bmuon_chargescore",muonLow_score,weight,240,-1.2,1.2);    
    FillHist("ll__muonLow/norm_bmuon_chargescore_dot_charge",(1+muonLow_score)/2*muonLow->Charge(),weight,240,-1.2,1.2);    
    bChargeType="muL";
  }
  else if(n_muonHigh==0 && n_muonLow==0 && n_electronHigh==1 && n_electronLow==0){
    //RunElectronHigh();
    belectronvar this_belectronvar=Get_belectronvar(*electronHigh,v_bjet[0]);
    bjetvar this_bjetvar=Get_bjetvar(v_bjet[0]);
    
    measured_charge=3*electronHigh->Charge();
    if(apply_chargeid_acc_corr){
      weight*=GetChargeAccCorr(v_bjet[0],2,measured_charge);
    }
    FillHistAll_belectron("ll__electronHigh",this_belectronvar);
    FillHistAll_bjet("ll__electronHigh",this_bjetvar);
    FillHistAll2("ll__electronHigh");
    FillHist("ll__electronHigh/belectron_chargescore",electronHigh_score,weight,240,-1.2,1.2);
    FillHist("ll__electronHigh/norm_belectron_chargescore_dot_charge",(1+electronHigh_score)/2*electronHigh->Charge(),weight,240,-1.2,1.2);    
    bChargeType="eH";
  }
  else if(n_muonHigh==0 && n_muonLow==0 && n_electronHigh==0 && n_electronLow==1){
    //RunElectronLow();
    belectronvar this_belectronvar=Get_belectronvar(*electronLow,v_bjet[0]);
    bjetvar this_bjetvar=Get_bjetvar(v_bjet[0]);

    measured_charge=-4*electronLow->Charge();
    if(apply_chargeid_acc_corr){
      weight*=GetChargeAccCorr(v_bjet[0],3,measured_charge);
    }
    FillHistAll_belectron("ll__electronLow",this_belectronvar);
    FillHistAll_bjet("ll__electronLow",this_bjetvar);
    FillHistAll2("ll__electronLow");
    FillHist("ll__electronLow/belectron_chargescore",electronLow_score,weight,240,-1.2,1.2);
    FillHist("ll__electronLow/norm_belectron_chargescore_dot_charge",(1+electronLow_score)/2*electronLow->Charge(),weight,240,-1.2,1.2);
    bChargeType="eL";
  }
  else if(n_muonHigh==0 && n_muonLow==0 && n_electronHigh==0 && n_electronLow==0){
    int jetcharge_coeff=GetJetChargeScoreCoeff();
    if(apply_chargeid_eff_corr) weight*=Get_HighScoreChargeTagID_Eff_Corr({v_bjet[0]},{jetcharge_coeff==1});
    FillHist("ll_1b_noSLT/jetHighPASS",(jetcharge_coeff==1),weight,2,0,2);
    if(jetcharge_coeff==1){
      //RunJetHigh();


      bjetvar this_bjetvar=Get_bjetvar(v_bjet[0]);

      measured_charge=5*(jetcharge>0 ? 1 : -1);
      if(apply_chargeid_acc_corr){
	weight*=GetChargeAccCorr(v_bjet[0],4,measured_charge);
      }
      FillHistAll_bjet("ll__jetHigh",this_bjetvar);
      FillHistAll2("ll__jetHigh");
      FillHist("ll__jetHigh/bjet_chargescore",jetscore,weight,240,-1.2,1.2);
      FillHist("ll__jetHigh/norm_bjet_chargescore_dot_charge",(1+jetscore)/2*(jetcharge > 0 ? 1 : -1),weight,240,-1.2,1.2);
      bChargeType="jH";   
    }
    else{
      //RunJetOthers();

      bjetvar this_bjetvar=Get_bjetvar(v_bjet[0]);

      measured_charge=6*(jetcharge>0 ? 1 : -1);
      if(apply_chargeid_acc_corr){
	weight*=GetChargeAccCorr(v_bjet[0],5,measured_charge);
      }
      FillHistAll_bjet("ll__jetOthers",this_bjetvar);
      FillHistAll2("ll__jetOthers");
      FillHist("ll__jetOthers/bjet_chargescore",jetscore,weight,240,-1.2,1.2);
      FillHist("ll__jetOthers/norm_bjet_chargescore_dot_charge",(1+jetscore)/2*(jetcharge > 0 ? 1 : -1),weight,240,-1.2,1.2);
      bChargeType="jOthers";
    }
  }
  if(!runSys){
    int jetcharge_coeff=GetJetChargeScoreCoeff();
    FillHist("ll_1b/jetHighPASS",(jetcharge_coeff==1),weight,2,0,2);
  }

  FillHistAll2("AllEvents");
  FillHist("AllEvents/measured_charge_all",measured_charge,weight,13,-6.5,6.5);
  if(measured_charge!=0)FillHist("AllEvents/measured_charge",measured_charge,weight,13,-6.5,6.5);

  FillHist("AllEvents/bChargeID_all",fabs(measured_charge),weight,7,-0.5,6.5);
  if(measured_charge!=0)FillHist("AllEvents/bChargeID",fabs(measured_charge),weight,7,-0.5,6.5);
  FillHist("AllEvents__"+bChargeType+suffix_rapidity_region+"/measured_charge",measured_charge>0? +1 : -1,weight,3,-1.5,1.5);

  if(addxsuffix || addregionsuffix){
    FillHist("AllEvents/xcat_region",suffix_rapidity_region_idx,weight,5,-0.5,4.5);
    FillHist("AllEvents"+suffix_rapidity_region+"/measured_charge_all",measured_charge,weight,13,-6.5,6.5);
    if(measured_charge!=0){

      FillHist("AllEvents"+suffix_rapidity_region+"/measured_charge",measured_charge,weight,13,-6.5,6.5);
      FillHist("AllEvents__"+bChargeType+suffix_rapidity_region+"/measured_charge",measured_charge>0? +1 : -1,weight,3,-1.5,1.5);
    }
    FillHist(bChargeType+"/xcat_region_dot_measured_charge",suffix_rapidity_region_idx*(measured_charge>0 ? +1 : -1),weight,9,-4.5,4.5);    
    
    FillHist("AllEvents"+suffix_rapidity_region+"/bChargeID_all",fabs(measured_charge),weight,7,-0.5,6.5);
    if(measured_charge!=0)FillHist("AllEvents"+suffix_rapidity_region+"/bChargeID",fabs(measured_charge),weight,7,-0.5,6.5);
    ///---if is DYb
    if(IsDYbplus || IsDYbminus){
      FillHist("AllEvents"+suffix_rapidity_region+"/log_x_b",log(x_b),weight,80,-8,0);
      FillHist("AllEvents/log_x_b",log(x_b),weight,80,-8,0);

      FillHist("AllEvents"+suffix_rapidity_region+"/Q",genWeight_Q,weight,200,0,200);
      FillHist("AllEvents/Q",genWeight_Q,weight,200,0,200);      
    }
  }//[end] if addsuffix


  
  
}//[end]RunBasic Zregion




void PreselectionToBDTRegionAnalyzer::FillHistAll_bmuon(TString cutname,bmuonvar this_bmuon){
  FillHist(cutname+"/bmuon_P_jetrest",this_bmuon.P_jetrest,weight,100,0,10);
  FillHist(cutname+"/bmuon_ptwrtjet",this_bmuon.ptwrtjet,weight,100,0,10);
  FillHist(cutname+"/bmuon_dR_l_j",this_bmuon.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/bmuon_nsip3d",this_bmuon.nsip3d,weight,100,0,10);
  FillHist(cutname+"/bmuon_reltrkiso",this_bmuon.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/bmuon_reliso",this_bmuon.reliso,weight,100,0,10);
  FillHist(cutname+"/bmuon_charge",this_bmuon.charge,weight,4,-2,2);
  

  FillHist(cutname+"/bmuon_palongjet",this_bmuon.palongjet,weight,200,0,50);
  FillHist(cutname+"/bmuon_palongjetratio",this_bmuon.palongjetratio,weight,50,0,1);
  FillHist(cutname+"/bmuon_pt",this_bmuon.pt,weight,50,0,50);
  FillHist(cutname+"/bmuon_aeta",this_bmuon.aeta,weight,40,-4,4);
  //FillHist(cutname+"/bmuon_normchi2",this_bmuon.normchi2,weight,40,0,12);
  //FillHist(cutname+"/bmuon_ntracklayers",this_bmuon.ntracklayers,weight,20,0,20);
  //FillHist(cutname+"/bmuon_ntrackhits",this_bmuon.ntrackhits,weight,35,0,35);
  //FillHist(cutname+"/bmuon_nvalidmuonhits",this_bmuon.nvalidmuonhits,weight,50,0,50);
  //FillHist(cutname+"/bmuon_nmatchedstations",this_bmuon.nmatchedstations,weight,6,0,6);
  FillHist(cutname+"/bmuon_bjet_charge_dot_bmuon_charge",this_bmuon.bjet_charge_dot_bmuon_charge,weight,50,-1,1);

}

void PreselectionToBDTRegionAnalyzer::FillHistAll_belectron(TString cutname,belectronvar this_belectron){
  FillHist(cutname+"/belectron_P_jetrest",this_belectron.P_jetrest,weight,100,0,10);
  FillHist(cutname+"/belectron_ptwrtjet",this_belectron.ptwrtjet,weight,100,0,10);
  FillHist(cutname+"/belectron_dR_l_j",this_belectron.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/belectron_nsip3d",this_belectron.nsip3d,weight,300,0,30);
  FillHist(cutname+"/belectron_reltrkiso",this_belectron.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/belectron_reliso",this_belectron.reliso,weight,100,0,10);
  FillHist(cutname+"/belectron_charge",this_belectron.charge,weight,4,-2,2);
  FillHist(cutname+"/belectron_IsGsfCtfScPixChargeConsistent",this_belectron.IsGsfCtfScPixChargeConsistent,weight,4,-2,2);
  FillHist(cutname+"/belectron_pt",this_belectron.pt,weight,50,0,50);
  FillHist(cutname+"/belectron_aeta",this_belectron.aeta,weight,40,-4,4);
  //FillHist(cutname+"/belectron_full5x5sigmaietaieta",this_belectron.full5x5sigmaietaieta,weight,100,0,0.1);
  //FillHist(cutname+"/belectron_abs_detaseed",this_belectron.detaseed,weight,100,0,0.1);
  //FillHist(cutname+"/belectron_HoverE",this_belectron.HoverE,weight,100,0,1);
  //FillHist(cutname+"/belectron_InvEminusInvP",this_belectron.InvEminusInvP,weight,100,0,1);
  //FillHist(cutname+"/belectron_nmissinghits",this_belectron.nmissinghits,weight,4,0,4);
  FillHist(cutname+"/belectron_bjet_charge_dot_belectron_charge",this_belectron.bjet_charge_dot_belectron_charge,weight,50,-1,1);

  FillHist(cutname+"/belectron_palongjet",this_belectron.palongjet,weight,200,0,100);
  FillHist(cutname+"/belectron_palongjetratio",this_belectron.palongjetratio,weight,50,0,1);
  

  //FillHist(cutname+"/belectron_passVetoID",this_belectron.passVetoID,weight,3,-1,2);
  //FillHist(cutname+"/belectron_passVetoIDnoIso",this_belectron.passVetoIDnoIso,weight,3,-1,2);
  //FillHist(cutname+"/belectron_passLooseID",this_belectron.passLooseID,weight,3,-1,2);
  //FillHist(cutname+"/belectron_passMediumID",this_belectron.passMediumID,weight,3,-1,2);
  //FillHist(cutname+"/belectron_passTightID",this_belectron.passTightID,weight,3,-1,2);


}

void PreselectionToBDTRegionAnalyzer::FillHistAll_bjet(TString cutname,bjetvar this_bjet){
  FillHist(cutname+"/bjet_pt",this_bjet.pt,weight,100,0,200);
  FillHist(cutname+"/bjet_aeta",this_bjet.aeta,weight,60,0,3);
  FillHist(cutname+"/bjet_ChargedHadronEnergyFraction",this_bjet.ChargedHadronEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/bjet_NeutralHadronEnergyFraction",this_bjet.NeutralHadronEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/log_bjet_NeutralHadronEnergyFraction",log(this_bjet.NeutralHadronEnergyFraction),weight,100,-10,0);
  FillHist(cutname+"/bjet_NeutralEmEnergyFraction",this_bjet.NeutralEmEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/bjet_ChargedEmEnergyFraction",this_bjet.ChargedEmEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/log_bjet_ChargedEmEnergyFraction",log(this_bjet.ChargedEmEnergyFraction),weight,100,-10,0);
  FillHist(cutname+"/bjet_MuonEnergyFraction",this_bjet.MuonEnergyFraction,weight,100,0,1);
  FillHist(cutname+"/log_bjet_MuonEnergyFraction",log(this_bjet.MuonEnergyFraction),weight,100,-10,0);
  FillHist(cutname+"/bjet_ChargedMultiplicity",this_bjet.ChargedMultiplicity,weight,60,0,60);
  FillHist(cutname+"/bjet_NeutralMultiplicity",this_bjet.NeutralMultiplicity,weight,60,0,60);
  FillHist(cutname+"/bjet_charge",this_bjet.charge,weight,50,-1,1);
  FillHist(cutname+"/bjet_abs_charge",this_bjet.abs_charge,weight,50,0,1);
  //FillHist(cutname+"/bjet_partonFlavour",this_bjet.partonFlavour,weight,27,-6,21);

}

void PreselectionToBDTRegionAnalyzer::FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max){
  JHAnalyzerBase::FillHist(histname,value,weight,n_bin,x_min,x_max);
  //if(check_tmva_input) return;
  //if(bdtopt) return;
  if(!runSys ){
    /*
    N_1_weightmap["pu"]=GetPileUpWeight(nPileUp,0) ? 1/GetPileUpWeight(nPileUp,0) : 0;
    N_1_weightmap["prefire"]=GetPileUpWeight(nPileUp,0) ? 1/GetPileUpWeight(nPileUp,0) : 0;
    //N_1_weightmap["zptweight"]=zptweight ? 1/zptweight : 0;                                                                                                                                               
    N_1_weightmap["z0weight"]=z0weight ? 1/z0weight : 0;
    N_1_weightmap["weakweight"]=weakweight ? 1/weakweight : 0;
    N_1_weightmap["topptweight"]=topptweight ? 1/topptweight : 0;

    N_1_weightmap["w_MuonID"]=w_MuonID[0][0] ? 1/w_MuonID[0][0] : 0;
    N_1_weightmap["w_MuonRECO"]=w_MuonRECO[0][0] ? 1/w_MuonRECO[0][0] : 0;
    N_1_weightmap["w_MuonTrk"]=w_MuonTrk[0][0] ? 1/w_MuonTrk[0][0] : 0;
    N_1_weightmap["w_MuonTrigger"]=w_MuonTrigger[0][0] ? 1/w_MuonTrigger[0][0] : 0;

    N_1_weightmap["w_ElectronID"]=w_ElectronID[0][0] ? 1/w_ElectronID[0][0] : 0;
    N_1_weightmap["w_ElectronRECO"]=w_ElectronRECO[0][0] ? 1/w_ElectronRECO[0][0] : 0;
    N_1_weightmap["w_ElectronTrigger"]=w_ElectronTrigger[0][0] ? 1/w_ElectronTrigger[0][0] : 0;
    */
    N_1_weightmap["btagsf"]=btagsf ? 1/btagsf : 0;
    //N_1_weightmap["jetpuidsf"]=jetpuidsf ? 1/jetpuidsf : 0;

    for(const auto& pair : N_1_weightmap){
      TString suffix="__No_"+pair.first;
      TString newhistname=histname+suffix;
      JHAnalyzerBase::FillHist("N-1__"+newhistname,value,weight*pair.second,n_bin,x_min,x_max);
    }

  }

}


void PreselectionToBDTRegionAnalyzer::FillHistAllChannel(TString cutname){
  //FillHistAllChannelWithSuffix(cutname);
  if(check_tmva_input) return;
  PreselectionToBDTRegionAnalyzer::FillHistAll("ll__"+cutname);
  PreselectionToBDTRegionAnalyzer::FillHistAll(LepCh+"__"+cutname);
}
/*
void PreselectionToBDTRegionAnalyzer::FillHistAllChannelWithSuffix(TString cutname){
  if(check_tmva_input) return;
  TString ProcessName_orig=ProcessName;
  ProcessName=ProcessName_orig+suffix_true_nb;
  PreselectionToBDTRegionAnalyzer::FillHistAll("ll__"+cutname);
  PreselectionToBDTRegionAnalyzer::FillHistAll(LepCh+"__"+cutname);
  ProcessName=ProcessName_orig;
}
*/

void PreselectionToBDTRegionAnalyzer::FillHistAll2(TString cutname){
    FillHist(cutname+"/M_ll",vZ.M(),weight,60,60,120);
    FillHist(cutname+"/Zpt",vZ.Pt(),weight,200,0,200);
    FillHist(cutname+"/Zy",z_y,weight,50,-3,3);
    FillHist(cutname+"/bjet_y",bjet_y,weight,50,-3,3);
    
    
}

void PreselectionToBDTRegionAnalyzer::FillHistAll(TString cutname){

  FillHist(cutname+"/event",1,weight,1,0,1);
  FillHist(cutname+"/nPV",nPV,weight,100,0,100);
  FillHist(cutname+"/vertex_Z",vertex_Z,weight,80,-20,20);
  FillHist(cutname+"/M_ll",vZ.M(),weight,60,60,120);
  FillHist(cutname+"/M_ll_uncorr",(l1_uncorr+l2_uncorr).M(),weight,60,60,120);



  FillHist(cutname+"/pt_l1",l1.Pt(),weight,200,0,200);
  FillHist(cutname+"/pt_l2",l2.Pt(),weight,200,0,200);

  FillHist(cutname+"/pt_l",l1.Pt(),weight,200,0,200);
  FillHist(cutname+"/pt_l",l2.Pt(),weight,200,0,200);

  FillHist(cutname+"/eta_l1",l1.Eta(),weight,50,-2.5,2.5);
  FillHist(cutname+"/eta_l2",l2.Eta(),weight,50,-2.5,2.5);

  FillHist(cutname+"/eta_l",l1.Eta(),weight,50,-2.5,2.5);
  FillHist(cutname+"/eta_l",l2.Eta(),weight,50,-2.5,2.5);

  FillHist(cutname+"/njet",njet,weight,10,0,10);
  FillHist(cutname+"/nbjet",nbjet,weight,10,0,10);

  if(!runSys){
    FillHist(cutname+"/met_wide",CurrentMET.Pt(),weight,40,0,200);
  }
  FillHist(cutname+"/met",CurrentMET.Pt(),weight,(int)maxMET,0,maxMET);
  if(nbjet>0){
    FillHist(cutname+"/dphi_z_b",dphi_z_b,weight,40,0,4);
    FillHist(cutname+"/ptzb",ptzb,weight,100,0,500);
    FillHist(cutname+"/Zpt",vZ.Pt(),weight,200,0,200);
  }
  
  if(njet>0){
    FillHist(cutname+"/pt_j1",v_tightjet[0].Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_j1",v_tightjet[0].Eta(),weight,60,-3,3);
    if(njet>1){
      FillHist(cutname+"/pt_j2",v_tightjet[1].Pt(),weight,200,0,200);
      FillHist(cutname+"/eta_j2",v_tightjet[1].Eta(),weight,60,-3,3);
    }
  }
  if(nbjet>0){

    FillHist(cutname+"/pt_bj1",v_bjet[0].Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_bj1",v_bjet[0].Eta(),weight,60,-3,3);
    if(nbjet>1){
      FillHist(cutname+"/pt_bj2",v_bjet[1].Pt(),weight,200,0,200);
      FillHist(cutname+"/eta_bj2",v_bjet[1].Eta(),weight,60,-3,3);
    }
  }



  for( const auto& jet : v_tightjet){
    FillHist(cutname+"/pt_j",jet.Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_j",jet.Eta(),weight,60,-3,3);
    if(!runSys){
      FillHist(cutname+"/dR_j_l1",jet.DeltaR(l1),weight,40,0,4);
      FillHist(cutname+"/dR_j_l2",jet.DeltaR(l2),weight,40,0,4);
      FillHist(cutname+"/dR_j_Z",jet.DeltaR(vZ),weight,40,0,4);
    }
  }
  for( const auto& bjet : v_bjet){
    FillHist(cutname+"/pt_bj",bjet.Pt(),weight,200,0,200);
    FillHist(cutname+"/eta_bj",bjet.Eta(),weight,60,-3,3);
    if(!runSys){
      FillHist(cutname+"/dR_bj_l1",bjet.DeltaR(l1),weight,40,0,4);
      FillHist(cutname+"/dR_bj_l2",bjet.DeltaR(l2),weight,40,0,4);
      FillHist(cutname+"/dR_bj_Z",bjet.DeltaR(vZ),weight,40,0,4);
    }
  }


}

void PreselectionToBDTRegionAnalyzer::EventLoop(){
  AnalyzerCore::FillHist("all/nmuons/"+ProcessName,AllMuons.size(),1,100,0.,100.);
  AnalyzerCore::FillHist("all/nelectrons/"+ProcessName,AllElectrons.size(),1,100,0.,100.);
  RunBasicZregion();
}




void PreselectionToBDTRegionAnalyzer::TruthLoop(){
  suffix_xscale="";
  IsDYbplus=0;
  IsDYbminus=0;
  IsBKG=0;
  x_b=100;
  x_g=100;
  suffix_true_nb="";

  //---IsDYSample
  if(IsDATA){
    i_proc=0; // data
    return;
  }
  if(!IsDYSample){
    i_proc=3;//non dy bkg
    IsBKG=1;
    return;
  }
  int bcharge=0;
  int nb=0;
  int nbbar=0;
  int idx_lhe_b=-1;
  int pid_b=0;

  unsigned int lhesize=lhes.size();
  for(unsigned int i = 0 ; i < lhesize; i++){
    int status=lhes[i].Status();
    int pid=lhes[i].ID();
    if(status==-1) continue;
    if(pid==5){
      nb+=1;
      idx_lhe_b=i;
      pid_b=5;
    }
    if(pid==-5){
      nbbar+=1;
      idx_lhe_b=i;
      pid_b=-5;
    }

  }

  if(nb+nbbar==1) {
    if(nb==1)suffix_true_nb="_b"; //dy+b
    if(nbbar==1)suffix_true_nb="_bbar";
    i_proc=1;
    if(nb==1){
      IsDYbminus=1;
    }else{
      IsDYbplus=1;
    }
    //-----in DYb
    if(abs(genWeight_id1)==5){
      x_b=genWeight_X1;
      x_g=genWeight_X2;
    }
    else if(abs(genWeight_id2)==5){
      x_b=genWeight_X2;
      x_g=genWeight_X1;
      
    }
    //suffix_xscale="";
    if(log(x_b)<-4.5){
      suffix_xscale="__logx_-InfTo-4.5";
    }else if(log(x_b)<-3.5){
      suffix_xscale="__logx_-4.5To-3.5";
    }else{
      suffix_xscale="__logx_-3.5To0";
    }
    
  }//end of DYb
  else{
    suffix_true_nb="_others"; //dy others
    i_proc=2;
    IsBKG=1;
  }
  ProcessName=MCSample+suffix_true_nb;
  if(addxsuffix) ProcessName+=suffix_xscale;
}

  




