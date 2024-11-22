#include "bbbarAsymMeasurement_NoCat.h"
#include <map>

//This is For Opimitzing the Max/Min scores of muon,electron,jets
bbbarAsymMeasurement_NoCat::bbbarAsymMeasurement_NoCat(){

}

bbbarAsymMeasurement_NoCat::~bbbarAsymMeasurement_NoCat(){
  //==== Destructor of this Analyzer
}

void bbbarAsymMeasurement_NoCat::initializeAnalyzer(){
  cout << "[bbbarAsymMeasurement_NoCat::initializeAnalyzer]" << endl;
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
  //lepveto
  lepveto=false;
  if(HasFlag("lepveto")){
    lepveto=true;
    cout << "lepveto -> true" << endl;
  }  


  //charge
  TString v_muonScore="2409.2";
  TString v_electronScore="2409.2";
  TString v_jetScore="2409.2";
  if(HasFlag("dnn_v2405.4")){
    v_muonScore="2405.4";
    v_electronScore="2405.4";
    v_jetScore="2405.2";
  }


  if(HasFlag("dnn_v2405.4.3")){
    cout << "[jhchoi] Use v2405.4.3!!!" << endl;
    v_muonScore="2405.4.3";
    v_electronScore="2405.4.3";
    v_jetScore="2405.4.3";
  }


  bool apply_dnncut=0;





  LoadChargeScoreTool(v_muonScore,v_electronScore,v_jetScore,apply_dnncut);


  //map<TString,float> map_jet_mincut;
  map_jet_mincut["2016preVFP"]=0.5;  map_jet_mincut["2016postVFP"]=0.52;  map_jet_mincut["2017"]=0.39; map_jet_mincut["2018"]=0.46;

  cout << "DataEra=" << DataEra << endl;
  jet_mincut=map_jet_mincut[DataEra];


}


void bbbarAsymMeasurement_NoCat::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;
  
}

bool bbbarAsymMeasurement_NoCat::CheckIsDiMuonChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  //vector<int> v_muonidx=GetIdxDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  vector<Muon> v_muon=lepveto ?  GetDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2) :  GetDiMuRecoNoVeto(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  if( v_muon.size()<2) return 0;
  double mll=(v_muon[0]+v_muon[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;

  SetMuon(v_muon[0],v_muon[1]);

  return 1;
}  

void bbbarAsymMeasurement_NoCat::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;
  
}


bool bbbarAsymMeasurement_NoCat::CheckIsDiElectronChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  vector<Electron> v_electron=lepveto ? GetDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2) :GetDiElRecoNoVeto(TriggerSafeCut_electron1, TriggerSafeCut_electron2); 
  if( v_electron.size()<2) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  
  double mll=(v_electron[0]+v_electron[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;
  SetElectron(v_electron[0],v_electron[1]);
  return 1;
}  


void bbbarAsymMeasurement_NoCat::SetEventWeight(){
  weight=1;
  if(IsDATA) return;

  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  
  if(IsDiMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsDiElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }


}

void bbbarAsymMeasurement_NoCat::RunBasicZregion(){

  IsDiMuonChannel=false;
  IsDiElectronChannel=false;
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
  v_tightjet=GetTightJet(v_tightlep,30,2.4,"tight",_JETPUID);
  v_bjet=GetBJet(v_tightjet);

  njet=v_tightjet.size();
  nbjet=v_bjet.size();


  //--Now Objects are ready--//
  SetEventWeight();  


  //----Let's select and fillhist  
  if(nbjet!=1) return ;
  dphi_z_b= fabs(v_bjet[0].DeltaPhi(vZ));
  ptzb=(v_bjet[0]+vZ).Pt();
  if(CurrentMET.Pt() > 75.) return;
  if(dphi_z_b < 1.6) return;
  if(vZ.Pt()<15.) return;
  if(ptzb>60.) return;

  //Get bjet charges
  
  //tuple<int,bool,int,int,double> bCand_Charge_info=GetBJetCharge_v2409_2(v_bjet[0],AllMuons,AllElectrons);

  //int bCand_Charge=std::get<0>(bCand_Charge_info);
  //bool bCand_NotUseOppositeCharge=std::get<1>(bCand_Charge_info);
  //int bCand_im=std::get<2>(bCand_Charge_info);
  //int bCand_ie=std::get<3>(bCand_Charge_info);
  //double bCnad_ChargeScore=std::get<4>(bCand_Charge_info);
  SetJetChargeScore(v_bjet[0]);
  double bjet_score=GetJetChargeScore();
  int bjet_charge=v_bjet[0].Charge() > 0 ? +1 : -1;

  if (bjet_score<jet_mincut) bjet_charge=bjet_charge*2;


  FillHist("FinalCut/MeasuredCharge_Total", bjet_charge,weight,5,-2.5,2.5);

  
}//[end]RunBasic Zregion


void bbbarAsymMeasurement_NoCat::EventLoop(){
  RunBasicZregion();
}  
  


void bbbarAsymMeasurement_NoCat::TruthLoop(){
  isDYbbar=false;
  isDYb=false;




  if(!IsDYSample) return;
  
  unsigned int nb=0;
  unsigned int nbbar=0;
  int pid_b=0;
  unsigned int ntau=0;
  unsigned int lhesize=lhes.size();
  for(unsigned int i = 0 ; i < lhesize; i++){
    int status=lhes[i].Status();
    int pid=lhes[i].ID();
    if(status==-1) continue;
    if(abs(pid)==15){//tau
      ntau+=1;
    }
    if(pid==5){
      nb+=1;
      pid_b=5;
    }
    if(pid==-5){
      nbbar+=1;
      pid_b=-5;
    }

  }



  if(ntau==2){
    ProcessName="DY_tautau";
    return;
  }

  if(nb+nbbar==1){
    if(pid_b>0){ 
       ProcessName="DY_b";
       isDYb=true;
    }
    else{
      ProcessName="DY_bbar";
       isDYbbar=true;
    }
    return;
  }

  ProcessName="DY_others";


}


