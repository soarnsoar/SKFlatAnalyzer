#include "PreselectionAnalyzer.h"
#include <map>
PreselectionAnalyzer::PreselectionAnalyzer(){
  //runSys=true;

  //JHAnalyzerBase::SetupDiLeptonChannel();  
}

PreselectionAnalyzer::~PreselectionAnalyzer(){
  //==== Destructor of this Analyzer
}

void PreselectionAnalyzer::initializeAnalyzer(){

  if(HasFlag("use_beff")){
    //----use this analyzer specific btag mc eff----//
    //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("PreselectionAnalyzer_"+MCSample+".root");// with kincut
  }


  if(HasFlag("use_beffasym")){
    //----use this analyzer specific btag mc eff----//
    //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("PreselectionAnalyzer_"+MCSample+".root",true);// with kincut
  }
  
  
  cout << "[PreselectionAnalyzer::initializeAnalyzer]" << endl;
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
  
  jetvetotest=HasFlag("jetvetotest");
  kincutopt=HasFlag("kincutopt");
  bdtopt=HasFlag("bdtopt");
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
    jhchoi_newtree->Branch("zbjet_y",&zbjet_y);
    jhchoi_newtree->Branch("zbjet_m",&zbjet_m);
    
    jhchoi_newtree->Branch("x_b",&x_b);
    jhchoi_newtree->Branch("x_g",&x_g);
  }

  
  ///----For KinCut Optimization---//
  if(!runSys && kincutopt){
    jhchoi_newtree=new TTree("ll1b_dy1b","ll1b_dy1b");
    jhchoi_newtree->Branch("met",&met_pt);
    jhchoi_newtree->Branch("dphi_z_b",&dphi_z_b);
    jhchoi_newtree->Branch("ptzb",&ptzb);
    jhchoi_newtree->Branch("z_pt",&z_pt);
    jhchoi_newtree->Branch("weight",&weight);
    
    jhchoi_newtree2=new TTree("ll1b_dy_others","ll1b_dy_others");
    jhchoi_newtree2->Branch("met",&met_pt);
    jhchoi_newtree2->Branch("dphi_z_b",&dphi_z_b);
    jhchoi_newtree2->Branch("ptzb",&ptzb);
    jhchoi_newtree2->Branch("z_pt",&z_pt);
    jhchoi_newtree2->Branch("weight",&weight);
    
    jhchoi_newtree3=new TTree("ll1b_bkg","ll1b_bkg");
    jhchoi_newtree3->Branch("met",&met_pt);
    jhchoi_newtree3->Branch("dphi_z_b",&dphi_z_b);
    jhchoi_newtree3->Branch("ptzb",&ptzb);
    jhchoi_newtree3->Branch("z_pt",&z_pt);
    jhchoi_newtree3->Branch("weight",&weight);
    
    
    jhchoi_newtree4=new TTree("ll1b_data","ll1b_data");
    jhchoi_newtree4->Branch("met",&met_pt);
    jhchoi_newtree4->Branch("dphi_z_b",&dphi_z_b);
    jhchoi_newtree4->Branch("ptzb",&ptzb);
    jhchoi_newtree4->Branch("z_pt",&z_pt);
    jhchoi_newtree4->Branch("weight",&weight);

  }
  if(!runSys && bdtopt){
    jhchoi_newtree=new TTree("bdtopt","bdtopt");

    jhchoi_newtree->Branch("IsDYbplus",&IsDYbplus);
    jhchoi_newtree->Branch("IsDYbminus",&IsDYbminus);
    jhchoi_newtree->Branch("IsBKG",&IsBKG);
    jhchoi_newtree->Branch("IsDATA",&IsDATA);

    jhchoi_newtree->Branch("v_muonscore",&v_muonscore);
    jhchoi_newtree->Branch("v_muoncharge",&v_muoncharge);
    jhchoi_newtree->Branch("v_electronscore",&v_electronscore);
    jhchoi_newtree->Branch("v_electroncharge",&v_electroncharge);
    jhchoi_newtree->Branch("jetscore",&jetscore);
    jhchoi_newtree->Branch("jetcharge",&jetcharge);
    
    jhchoi_newtree->Branch("weight",&weight);
    


  }
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
  //----
  /*
  maxMET=70.0;
  min_dphi_z_b=-1;
  min_z_pt=5.0;
  max_ptzb=500.0;
  */
  //---newlepveto
  maxMET=75.0;
  min_dphi_z_b=-1;
  min_z_pt=5.0;
  max_ptzb=580.0;
  if(DataEra=="2016preVFP"){
    //m_score_region
    //e_score_region
    //j_score_region
    /*
    m_score_region.push_back(std::make_pair(-1,-0.4));
    m_score_region.push_back(std::make_pair(0.65,1));

    e_score_region.push_back(std::make_pair(0.4,1));
    e_score_region.push_back(std::make_pair(-0.3,-0.25));
    */
  }
  if(DataEra=="2016preVFP"){
    /*
    e_score_region.push_back(std::make_pair(0.5,0.6));
    e_score_region.push_back(std::make_pair(-1,-0.6));
    */
  }
  if(DataEra=="2017"){
    /*
    m_score_region.push_back(std::make_pair(-1,-0.5));
    e_score_region.push_back(std::make_pair(0.4,0.6));
    
    j_score_region.push_back(std::make_pair(0.2,0.3));
    */
  }
  if(DataEra=="2018"){
    /*
    m_score_region.push_back(std::make_pair(-1,-0.6));
    m_score_region.push_back(std::make_pair(0.8,1));

    e_score_region.push_back(std::make_pair(0.2,1));
    e_score_region.push_back(std::make_pair(-1,-0.5));
    
    j_score_region.push_back(std::make_pair(0.2,1));
    */
  }
}


void PreselectionAnalyzer::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;
  
}

bool PreselectionAnalyzer::CheckIsDiMuonChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  //vector<int> v_muonidx=GetIdxDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  //vector<Muon> v_muon=lepveto ?  GetDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2) :  GetDiMuRecoNoVeto(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  vector<int> v_muonidx=lepveto ?  GetDiMuRecoIdx(TriggerSafeCut_muon1, TriggerSafeCut_muon2) :  GetDiMuRecoNoVetoIdx(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  if( v_muonidx.size()<2) return 0;
  //double mll=(v_muon[0]+v_muon[1]).M();
  double mll=(AllMuons[v_muonidx[0]] + AllMuons[v_muonidx[1]]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;

  //SetMuon(v_muon[0],v_muon[1]);
  SetMuon(AllMuons[v_muonidx[0]],AllMuons[v_muonidx[1]]);
  v_tightmuonidx={v_muonidx[0],v_muonidx[1]};
  return 1;
}  

void PreselectionAnalyzer::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;
  
}


bool PreselectionAnalyzer::CheckIsDiElectronChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  //vector<Electron> v_electron=lepveto ? GetDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2) :GetDiElRecoNoVeto(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  vector<int> v_electronidx=lepveto ? GetDiElRecoIdx(TriggerSafeCut_electron1, TriggerSafeCut_electron2) : GetDiElRecoNoVetoIdx(TriggerSafeCut_electron1, TriggerSafeCut_electron2); 
  if( v_electronidx.size()<2) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  
  double mll=(AllElectrons[v_electronidx[0]]+AllElectrons[v_electronidx[1]]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;
  SetElectron(AllElectrons[v_electronidx[0]],AllElectrons[v_electronidx[1]]);
  v_tightelectronidx={v_electronidx[0],v_electronidx[1]};
  return 1;
}  

void PreselectionAnalyzer::SetEventNormWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full");
}

void PreselectionAnalyzer::SetEventWeight(){
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

void PreselectionAnalyzer::RunBasicZregion(){
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
  //v_bjetidx=GetBJetIdx(v_tightjet);
  //v_bjet.clear();
  //for( const int ij : v_bjetidx){
  //  v_bjet.push_back(v_tightjet[ij]);
  //}
  njet=v_tightjet.size();
  nbjet=v_bjet.size();
  met_pt=CurrentMET.Pt();
  z_pt=vZ.Pt();
  //--Now Objects are ready--//
  SetEventWeight();  


  if(jetvetotest){
    for(auto& _jet : v_tightjet){
      
      AnalyzerCore::FillHist("jet_eta_phi",_jet.Eta(),_jet.Phi(),
	       weight,
	       82,-5.1910000,5.1910000,
	       72,-3.141592,3.141592);
    }
    
    return;
  }
  
  //----Let's select and fillhist
  if(!runSys)FillHistAllChannel("BasicDYSelection");
  if(nbjet!=1) return ;
  //  bool HasVetoLepton_NotTightLeps_NotWithinJets(const vector<int>& _v_tightmuonidx, const vector<int>& _v_tightelectronidx, const vector<TLorentzVector>& _v_jet);
  if(newlepveto){
    if (HasVetoLepton_NotTightLeps_NotWithinJets(v_tightmuonidx,v_tightelectronidx,&v_bjet[0])  ) return;
  }
  dphi_z_b= fabs(v_bjet[0].DeltaPhi(vZ));
  ptzb=(v_bjet[0]+vZ).Pt();

  if(!runSys && kincutopt){
    if(i_proc==1){
      jhchoi_newtree->Fill();
    }else if(i_proc==2){
      jhchoi_newtree2->Fill();
    }else if(i_proc==3){
      jhchoi_newtree3->Fill();
    }else{
      jhchoi_newtree4->Fill();
  }
  }
  if(!runSys)FillHistAllChannel("Only1bjet");
  //if(CurrentMET.Pt() > 75.) return;
  if(met_pt > maxMET) return;//updated 251222
  if(!runSys)FillHistAllChannel("After__maxMET");
  //if(dphi_z_b < 1.6) return;
  //if(dphi_z_b < min_dphi_z_b) return; // updated 251222
  //if(!runSys){
  //  FillHistAllChannel("After__maxMET__min_dphizb");
    
  //}
  //if(ptzb>60.) return;
  if(ptzb>max_ptzb) return;
  if(!runSys){
    
    //FillHistAllChannel("After__maxMET__min_dphizb__max_ptzb");
    FillHistAllChannel("After__maxMET__max_ptzb");
  }
  //if(vZ.Pt()<15.) return;
  if(z_pt<min_z_pt) return;
  
  //FillHistAllChannel("After__maxMET__min_dphizb__max_ptzb__min_z_pt");
  FillHistAllChannel("After__maxMET__max_ptzb__min_z_pt");


  if(measure_btageff){

    Measure_MCbtagEff();
    return;
  }

  if(IsDYbplus || IsDYbminus){
    if(xrangetree){
      bjet_y=v_bjet[0].Rapidity();
      bjet_eta=v_bjet[0].Eta();
      z_eta=vZ.Eta();
      z_y=vZ.Rapidity();
      zbjet_y=(vZ+v_bjet[0]).Rapidity();
      zbjet_m=(vZ+v_bjet[0]).M();
      jhchoi_newtree->Fill();
	
    }

  }
  ///---Let's look into leptons in bjet---//
  if(!check_tmva_input && !bdtopt) return;
  //---need to set bjet first---//
  
  //---for optimization----//

  v_muonscore.clear();
  v_muoncharge.clear();
  v_electronscore.clear();
  v_electroncharge.clear();
  jetscore=-9999;
  jetcharge=-9999;

  int nbmuon=0;
  int nbelectron=0;
  //bmuonvar this_bmuon;
  Muon* muon_1bmuon;
  Electron* electron_1belectron;
  for(auto& muon : AllMuons){
    if(muon.Pt() < 5.) continue;
    if(muon.DeltaR(v_bjet[0]) > 0.4) continue;
    /*
    if(muon.RelIso() > 10.) continue;
    if(muon.Chi2()>10) continue;
    if(muon.TrackerLayers()<1) continue;
    if(muon.MatchedStations() <1) continue;
    */
    bool isGlobalMuon__OR__isTrackerMuon= muon.IsType(Muon::GlobalMuon) || muon.IsType(Muon::TrackerMuon);
    if(!isGlobalMuon__OR__isTrackerMuon) continue;
    


    //this_bmuon=Get_bmuonvar(muon,v_bjet[0]);
    muon_1bmuon=&muon;
    nbmuon+=1;
    SetMuonChargeScore(muon,v_bjet[0]);

    v_muonscore.push_back(GetMuonChargeScore());
    v_muoncharge.push_back(muon.Charge());
    FillHist(LepCh+"__Presel/bmuon_chargescore",GetMuonChargeScore(),weight,240,-1.2,1.2);
    FillHist("ll__Presel/bmuon_chargescore",GetMuonChargeScore(),weight,240,-1.2,1.2);
    FillHist(LepCh+"__Presel/norm_bmuon_chargescore_dot_charge",(1+GetMuonChargeScore())/2*bmuon_ChargeTool.charge,weight,240,-1.2,1.2);
    FillHist("ll__Presel/norm_bmuon_chargescore_dot_charge",(1+GetMuonChargeScore())/2*bmuon_ChargeTool.charge,weight,240,-1.2,1.2);
    
    if(bdtopt) continue;
    
    FillHistAll_bmuon(LepCh+"__Presel",bmuon_ChargeTool);	
    FillHistAll_bmuon("ll__Presel",bmuon_ChargeTool);
    
    //FillHist(LepCh+"__Presel__Has_bmuon/bjet_charge",v_bjet[0].Charge(),weight,50,-1,1);
    //FillHist("ll__Presel__Has_bmuon/bjet_charge",v_bjet[0].Charge(),weight,50,-1,1);
    

  

  
  }//[end muon for loop]
  //belectronvar this_belectron;
  for(auto& electron : AllElectrons){
    if(electron.Pt() < 5.) continue;
    if(electron.DeltaR(v_bjet[0]) > 0.4) continue;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    //if(electron.RelIso() > 10.) continue;
    //if(electron.NMissingHits() != 0) continue;
    electron_1belectron=&electron;
    //this_belectron=Get_belectronvar(electron,v_bjet[0]);
    nbelectron+=1;    
    SetElectronChargeScore(electron,v_bjet[0]);
    v_electronscore.push_back(GetElectronChargeScore());
    v_electroncharge.push_back(electron.Charge());
    FillHist(LepCh+"__Presel/belectron_chargescore",GetElectronChargeScore(),weight,240,-1.2,1.2);
    FillHist("ll__Presel/belectron_chargescore",GetElectronChargeScore(),weight,240,-1.2,1.2);
    FillHist(LepCh+"__Presel/norm_belectron_chargescore_dot_charge",(1+GetElectronChargeScore())/2*belectron_ChargeTool.charge,weight,240,-1.2,1.2);
    FillHist("ll__Presel/norm_belectron_chargescore_dot_charge",(1+GetElectronChargeScore())/2*belectron_ChargeTool.charge,weight,240,-1.2,1.2);
    
    if(bdtopt) continue;



    FillHistAll_belectron(LepCh+"__Presel",belectron_ChargeTool);	
    FillHistAll_belectron("ll__Presel",belectron_ChargeTool);	
    
    //FillHist(LepCh+"__Presel__Has_belectron/bjet_charge",v_bjet[0].Charge(),weight,50,-1,1);
    //FillHist("ll__Presel__Has_belectron/bjet_charge",v_bjet[0].Charge(),weight,50,-1,1);    

    



    
  }//[end electron for loop]
  FillHist(LepCh+"__Presel/nblep",nbmuon+10*nbelectron,weight,100,0,100);
  FillHist("ll__Presel/nblep",nbmuon+10*nbelectron,weight,100,0,100);

  //bjetvar this_bjet=Get_bjetvar(v_bjet[0]);
  
  SetJetChargeScore(v_bjet[0]);
  jetscore=GetJetChargeScore();
  jetcharge=v_bjet[0].Charge();


  FillHist(LepCh+"__Presel/bjet_chargescore",GetJetChargeScore(),weight,240,-1.2,1.2);
  FillHist("ll__Presel/bjet_chargescore",GetJetChargeScore(),weight,240,-1.2,1.2);
  FillHist(LepCh+"__Presel/norm_bjet_chargescore_dot_charge",(1+GetJetChargeScore())*(bjet_ChargeTool.charge > 0 ? +1 : -1),weight,240,-1.2,1.2);
  FillHist("ll__Presel/norm_bjet_chargescore_dot_charge",GetJetChargeScore()*(bjet_ChargeTool.charge > 0 ? +1 : -1),weight,240,-1.2,1.2);
  

  FillHistAll_bjet(LepCh+"__Presel",bjet_ChargeTool);	
  FillHistAll_bjet("ll__Presel",bjet_ChargeTool);

  if(nbmuon==0 && nbelectron==0){
    FillHistAll_bjet(LepCh+"__Presel__No_bLep",bjet_ChargeTool);
    FillHistAll_bjet("ll__Presel__No_bLep",bjet_ChargeTool);
    
    FillHist(LepCh+"__Presel__No_bLep/bjet_chargescore",GetJetChargeScore(),weight,240,-1.2,1.2);
    FillHist("ll__Presel__No_bLep/bjet_chargescore",GetJetChargeScore(),weight,240,-1.2,1.2);
    FillHist(LepCh+"__Presel__No_bLep/norm_bjet_chargescore_dot_charge",(1+GetJetChargeScore())*(bjet_ChargeTool.charge > 0 ? +1 : -1),weight,240,-1.2,1.2);
    FillHist("ll__Presel__No_bLep/norm_bjet_chargescore_dot_charge",GetJetChargeScore()*(bjet_ChargeTool.charge > 0 ? +1 : -1),weight,240,-1.2,1.2);
    for(auto& cuts : j_score_region){
      double this_min=cuts.first;
      std::string this_min_str=std::to_string(this_min);
      double this_max=cuts.second;
      std::string this_max_str=std::to_string(this_max);
      
      TString this_cutname="__"+this_min_str+"__"+this_max_str;
      if(GetJetChargeScore() > this_min && GetJetChargeScore() < this_max){
	FillHistAll_bjet("ll__Presel__No_bLep"+this_cutname,bjet_ChargeTool);	
      }
    }
  }
  else if(nbmuon==1 && nbelectron==0){
    SetMuonChargeScore(*muon_1bmuon,v_bjet[0]);

    FillHistAll_bmuon(LepCh+"__Presel__1bmuon",bmuon_ChargeTool);
    FillHistAll_bmuon("ll__Presel__1bmuon",bmuon_ChargeTool);
    FillHistAll_bjet(LepCh+"__Presel__1bmuon",bjet_ChargeTool);
    FillHistAll_bjet("ll__Presel__1bmuon",bjet_ChargeTool);
    
    FillHist(LepCh+"__Presel__1bmuon/bmuon_chargescore",GetMuonChargeScore(),weight,240,-1.2,1.2);
    FillHist("ll__Presel__1bmuon/bmuon_chargescore",GetMuonChargeScore(),weight,240,-1.2,1.2);
    FillHist(LepCh+"__Presel__1bmuon/norm_bmuon_chargescore_dot_charge",(1+GetMuonChargeScore())/2*bmuon_ChargeTool.charge,weight,240,-1.2,1.2);
    FillHist("ll__Presel__1bmuon/norm_bmuon_chargescore_dot_charge",(1+GetMuonChargeScore())/2*bmuon_ChargeTool.charge,weight,240,-1.2,1.2);

    for(auto& cuts : m_score_region){
      double this_min=cuts.first;
      std::string this_min_str=std::to_string(this_min);
      double this_max=cuts.second;
      std::string this_max_str=std::to_string(this_max);
      
      TString this_cutname="__"+this_min_str+"__"+this_max_str;
      if(GetMuonChargeScore() > this_min && GetMuonChargeScore() < this_max){
	FillHistAll_bmuon("ll__Presel__1bmuon"+this_cutname,bmuon_ChargeTool);
	FillHistAll_bjet("ll__Presel__1bmuon"+this_cutname,bjet_ChargeTool);

      }
    }
    
  }
  else if(nbmuon==0 && nbelectron==1){
    SetElectronChargeScore(*electron_1belectron,v_bjet[0]);
    FillHistAll_belectron(LepCh+"__Presel__1belectron",belectron_ChargeTool);
    FillHistAll_belectron("ll__Presel__1belectron",belectron_ChargeTool);
    FillHistAll_bjet(LepCh+"__Presel__1belectron",bjet_ChargeTool);
    FillHistAll_bjet("ll__Presel__1belectron",bjet_ChargeTool);
    
    FillHist(LepCh+"__Presel__1belectron/belectron_chargescore",GetElectronChargeScore(),weight,240,-1.2,1.2);
    FillHist("ll__Presel__1belectron/belectron_chargescore",GetElectronChargeScore(),weight,240,-1.2,1.2);
    FillHist(LepCh+"__Presel__1belectron/norm_belectron_chargescore_dot_charge",(1+GetElectronChargeScore())/2*belectron_ChargeTool.charge,weight,240,-1.2,1.2);
    FillHist("ll__Presel__1belectron/norm_belectron_chargescore_dot_charge",(1+GetElectronChargeScore())/2*belectron_ChargeTool.charge,weight,240,-1.2,1.2);


    for(auto& cuts : e_score_region){
      double this_min=cuts.first;
      std::string this_min_str=std::to_string(this_min);
      double this_max=cuts.second;
      std::string this_max_str=std::to_string(this_max);

      TString this_cutname="__"+this_min_str+"__"+this_max_str;
      if(GetElectronChargeScore() > this_min && GetElectronChargeScore() < this_max){
	FillHistAll_belectron("ll__Presel__1belectron"+this_cutname,belectron_ChargeTool);
	FillHistAll_bjet("ll__Presel__1belectron"+this_cutname,bjet_ChargeTool);

      }
    }
  }

  if(bdtopt){
    jhchoi_newtree->Fill();
    return;
  }
  
}//[end]RunBasic Zregion




void PreselectionAnalyzer::FillHistAll_bmuon(TString cutname,bmuonvar this_bmuon){
  FillHist(cutname+"/bmuon_P_jetrest",this_bmuon.P_jetrest,weight,100,0,10);
  FillHist(cutname+"/bmuon_ptwrtjet",this_bmuon.ptwrtjet,weight,100,0,10);
  FillHist(cutname+"/bmuon_dR_l_j",this_bmuon.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/bmuon_nsip3d",this_bmuon.nsip3d,weight,100,0,10);
  FillHist(cutname+"/bmuon_reltrkiso",this_bmuon.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/bmuon_log_1_reltrkiso",log10(1+this_bmuon.reltrkiso),weight,100,0,2);
  FillHist(cutname+"/bmuon_reliso",this_bmuon.reliso,weight,100,0,10);
  FillHist(cutname+"/bmuon_log_1_reliso",log10(1+this_bmuon.reliso),weight,100,0,2);
  FillHist(cutname+"/bmuon_charge",this_bmuon.charge,weight,4,-2,2);
  

  FillHist(cutname+"/bmuon_palongjet",this_bmuon.palongjet,weight,200,0,50);
  FillHist(cutname+"/bmuon_palongjetratio",this_bmuon.palongjetratio,weight,50,0,1);
  //FillHist(cutname+"/bmuon_pt",this_bmuon.pt,weight,50,0,50);
  //FillHist(cutname+"/bmuon_aeta",this_bmuon.aeta,weight,40,-4,4);
  FillHist(cutname+"/bmuon_normchi2",this_bmuon.normchi2,weight,40,0,12);
  FillHist(cutname+"/bmuon_ntracklayers",this_bmuon.ntracklayers,weight,20,0,20);
  FillHist(cutname+"/bmuon_ntrackhits",this_bmuon.ntrackhits,weight,35,0,35);
  FillHist(cutname+"/bmuon_nvalidmuonhits",this_bmuon.nvalidmuonhits,weight,50,0,50);
  FillHist(cutname+"/bmuon_nmatchedstations",this_bmuon.nmatchedstations,weight,6,0,6);
  FillHist(cutname+"/bmuon_bjet_charge_dot_bmuon_charge",this_bmuon.bjet_charge_dot_bmuon_charge,weight,50,-1,1);
  //
  FillHist(cutname+"/bmuon_pt",this_bmuon.pt,weight,50,0,50);
  FillHist(cutname+"/bmuon_aeta",this_bmuon.aeta,weight,50,0,2.5);
}

void PreselectionAnalyzer::FillHistAll_belectron(TString cutname,belectronvar this_belectron){
  FillHist(cutname+"/belectron_P_jetrest",this_belectron.P_jetrest,weight,100,0,10);
  FillHist(cutname+"/belectron_ptwrtjet",this_belectron.ptwrtjet,weight,100,0,10);
  FillHist(cutname+"/belectron_dR_l_j",this_belectron.dR_l_j,weight,40,0,0.4);
  FillHist(cutname+"/belectron_nsip3d",this_belectron.nsip3d,weight,300,0,30);
  FillHist(cutname+"/belectron_reltrkiso",this_belectron.reltrkiso,weight,150,0,15);
  FillHist(cutname+"/belectron_log_1_reltrkiso",log10(1+this_belectron.reltrkiso),weight,100,0,2);
  FillHist(cutname+"/belectron_reliso",this_belectron.reliso,weight,100,0,10);
  FillHist(cutname+"/belectron_log_1_reliso",log10(1+this_belectron.reliso),weight,100,0,2);
  FillHist(cutname+"/belectron_charge",this_belectron.charge,weight,4,-2,2);
  FillHist(cutname+"/belectron_IsGsfCtfScPixChargeConsistent",this_belectron.IsGsfCtfScPixChargeConsistent,weight,4,-2,2);
  
  FillHist(cutname+"/belectron_full5x5sigmaietaieta",this_belectron.full5x5sigmaietaieta,weight,100,0,0.1);
  FillHist(cutname+"/belectron_log_1_full5x5sigmaietaieta",log10(1+this_belectron.full5x5sigmaietaieta),weight,100,0,0.5);
  FillHist(cutname+"/belectron_abs_detaseed",this_belectron.detaseed,weight,100,0,0.1);
  FillHist(cutname+"/belectron_HoverE",this_belectron.HoverE,weight,100,0,1);
  FillHist(cutname+"/belectron_InvEminusInvP",this_belectron.InvEminusInvP,weight,100,0,1);
  FillHist(cutname+"/belectron_nmissinghits",this_belectron.nmissinghits,weight,4,0,4);
  FillHist(cutname+"/belectron_bjet_charge_dot_belectron_charge",this_belectron.bjet_charge_dot_belectron_charge,weight,50,-1,1);

  FillHist(cutname+"/belectron_palongjet",this_belectron.palongjet,weight,200,0,100);
  FillHist(cutname+"/belectron_palongjetratio",this_belectron.palongjetratio,weight,50,0,1);
  

  FillHist(cutname+"/belectron_passVetoID",this_belectron.passVetoID,weight,3,-1,2);
  FillHist(cutname+"/belectron_passVetoIDnoIso",this_belectron.passVetoIDnoIso,weight,3,-1,2);
  FillHist(cutname+"/belectron_passLooseID",this_belectron.passLooseID,weight,3,-1,2);
  FillHist(cutname+"/belectron_passMediumID",this_belectron.passMediumID,weight,3,-1,2);
  FillHist(cutname+"/belectron_passTightID",this_belectron.passTightID,weight,3,-1,2);


  FillHist(cutname+"/belectron_pt",this_belectron.pt,weight,50,0,50);
  FillHist(cutname+"/belectron_aeta",this_belectron.aeta,weight,50,0,2.5);

  if(this_belectron.aeta<1.479){//ECAL BARREL
    FillHist(cutname+"_EB/belectron_full5x5sigmaietaieta",this_belectron.full5x5sigmaietaieta,weight,100,0,1);
    FillHist(cutname+"_EB/belectron_log_1_full5x5sigmaietaieta",log10(1+this_belectron.full5x5sigmaietaieta),weight,100,0,0.5);
    FillHist(cutname+"_EB/belectron_abs_detaseed",this_belectron.abs_detaseed,weight,100,0,1);
    FillHist(cutname+"_EB/belectron_log_abs_detaseed",log10(this_belectron.abs_detaseed),weight,100,-8,1);
    FillHist(cutname+"_EB/belectron_abs_dPhiIn",this_belectron.abs_dPhiIn,weight,100,0,1);
    FillHist(cutname+"_EB/belectron_log_abs_dPhiIn",log10(this_belectron.abs_dPhiIn),weight,100,-8,1);
    FillHist(cutname+"_EB/belectron_InvEminusInvP",this_belectron.InvEminusInvP,weight,100,0,1);
    FillHist(cutname+"_EB/belectron_log_InvEminusInvP",log10(this_belectron.InvEminusInvP),weight,100,-8,1);
    FillHist(cutname+"_EB/belectron_HoverE",this_belectron.HoverE,weight,100,0,1);
    FillHist(cutname+"_EB/belectron_log_0p0001_HoverE",log10(0.0001+this_belectron.HoverE),weight,100,-4,1);
    
  }else{//ECAL ENDCAP
    FillHist(cutname+"_EE/belectron_full5x5sigmaietaieta",this_belectron.full5x5sigmaietaieta,weight,100,0,1);
    FillHist(cutname+"_EE/belectron_log_1_full5x5sigmaietaieta",log10(1+this_belectron.full5x5sigmaietaieta),weight,100,0,0.5);
    FillHist(cutname+"_EE/belectron_abs_detaseed",this_belectron.abs_detaseed,weight,100,0,1);
    FillHist(cutname+"_EE/belectron_log_abs_detaseed",log10(this_belectron.abs_detaseed),weight,100,-8,1);
    FillHist(cutname+"_EE/belectron_abs_dPhiIn",this_belectron.abs_dPhiIn,weight,100,0,1);
    FillHist(cutname+"_EE/belectron_log_abs_dPhiIn",log10(this_belectron.abs_dPhiIn),weight,100,-8,1);
    FillHist(cutname+"_EE/belectron_InvEminusInvP",this_belectron.InvEminusInvP,weight,100,0,1);
    FillHist(cutname+"_EE/belectron_log_InvEminusInvP",log10(this_belectron.InvEminusInvP),weight,100,-8,1);
    FillHist(cutname+"_EE/belectron_HoverE",this_belectron.HoverE,weight,100,0,1);
    FillHist(cutname+"_EE/belectron_log_0p0001_HoverE",log10(0.0001+this_belectron.HoverE),weight,100,-4,1);
  }
  
}

void PreselectionAnalyzer::FillHistAll_bjet(TString cutname,bjetvar this_bjet){
  //FillHist(cutname+"/bjet_pt",this_bjet.pt,weight,100,0,100);
  //FillHist(cutname+"/bjet_aeta",this_bjet.aeta,weight,60,0,3);
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

void PreselectionAnalyzer::FillHistAllChannel(TString cutname){
  //FillHistAllChannelWithSuffix(cutname);
  if(check_tmva_input) return;
  PreselectionAnalyzer::FillHistAll("ll__"+cutname);
  PreselectionAnalyzer::FillHistAll(LepCh+"__"+cutname);
}
/*
void PreselectionAnalyzer::FillHistAllChannelWithSuffix(TString cutname){
  if(check_tmva_input) return;
  TString ProcessName_orig=ProcessName;
  ProcessName=ProcessName_orig+suffix_true_nb;
  PreselectionAnalyzer::FillHistAll("ll__"+cutname);
  PreselectionAnalyzer::FillHistAll(LepCh+"__"+cutname);
  ProcessName=ProcessName_orig;
}
*/

void PreselectionAnalyzer::FillHistAll(TString cutname){

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
    FillHist(cutname+"/ptzb",ptzb,weight,120,0,600);
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
void PreselectionAnalyzer::FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max){
  JHAnalyzerBase::FillHist(histname,value,weight,n_bin,x_min,x_max);
  if(check_tmva_input) return;
  if(bdtopt) return;
  if(!runSys ){
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
    N_1_weightmap["btagsf"]=btagsf ? 1/btagsf : 0;
    N_1_weightmap["jetpuidsf"]=jetpuidsf ? 1/jetpuidsf : 0;
    
    for(const auto& pair : N_1_weightmap){
      TString suffix="__No_"+pair.first;
      TString newhistname=histname+suffix;
      JHAnalyzerBase::FillHist("N-1__"+newhistname,value,weight*pair.second,n_bin,x_min,x_max);
    }
  
  }

}
void PreselectionAnalyzer::EventLoop(){
  AnalyzerCore::FillHist("all/nmuons/"+ProcessName,AllMuons.size(),1,100,0.,100.);
  AnalyzerCore::FillHist("all/nelectrons/"+ProcessName,AllElectrons.size(),1,100,0.,100.);
  RunBasicZregion();
}




void PreselectionAnalyzer::TruthLoop(){
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
   
  }//end of DYb
  else{
    suffix_true_nb="_others"; //dy others
    i_proc=2;
    IsBKG=1;
  }
  ProcessName=MCSample+suffix_true_nb;

}

  




