#include "bbbarAsymMeasurement.h"
#include <map>

//This is For Opimitzing the Max/Min scores of muon,electron,jets
bbbarAsymMeasurement::bbbarAsymMeasurement(){

}

bbbarAsymMeasurement::~bbbarAsymMeasurement(){
  //==== Destructor of this Analyzer
  if(apply_bchargeeff){
    DeleteBChargeEff();
  }
}

void bbbarAsymMeasurement::initializeAnalyzer(){

  if(HasFlag("use_beff_dasym")){
    //----use this analyzer specific btag mc eff----//
        //void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename)
    if(!IsDATA) AnalyzerCore::SetBTagMCEff_Filename("bbbarAsymMeasurement_"+MCSample+".root",true);
    use_dasym=true;
  }
  else{
    use_dasym=false;
  }


  
  cout << "[bbbarAsymMeasurement::initializeAnalyzer]" << endl;
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



  bool apply_dnncut=1;





  LoadChargeScoreTool(v_muonScore,v_electronScore,v_jetScore,apply_dnncut);

  apply_bchargeeff=false;
  if(HasFlag("apply_bchargeeff")){
    if(!IsDATA){
      initializeBChargeEff("bbbarAsymMeasurement_"+MCSample+".root");
      apply_bchargeeff=true;
    }
  }




}


void bbbarAsymMeasurement::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;
  
}

bool bbbarAsymMeasurement::CheckIsDiMuonChannel(double min_mll,double max_mll){
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

void bbbarAsymMeasurement::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;
  
}


bool bbbarAsymMeasurement::CheckIsDiElectronChannel(double min_mll,double max_mll){
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


void bbbarAsymMeasurement::SetEventWeight(){
  weight=1;
  if(IsDATA) return;

  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  
  if(IsDiMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsDiElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }


}

void bbbarAsymMeasurement::RunBasicZregion(){

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

  if(measure_btageff_partonFlavour_bonly){
    SetEventWeight();
    Measure_MCbtagEff_PartonFlavour_bonly();
    return;
  }


  
  //----Jet---//
  v_tightlep={l1,l2};
  v_tightjet=GetTightJet(v_tightlep,30,jetetacut,"tight",_JETPUID);
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



  if(measure_bchargeeff){
    Measure_MCbChargeIDEff(v_bjet[0]);
    return;
  }



  //Get bjet charges
  tuple<int,bool,int,int,double> bCand_Charge_info=GetBJetCharge_v2409_2(v_bjet[0],AllMuons,AllElectrons);

  int bCand_Charge=std::get<0>(bCand_Charge_info);
  bool bCand_NotUseOppositeCharge=std::get<1>(bCand_Charge_info);
  int bCand_im=std::get<2>(bCand_Charge_info);
  int bCand_ie=std::get<3>(bCand_Charge_info);
  double bCnad_ChargeScore=std::get<4>(bCand_Charge_info);

  int cat_id=0;

  //---bchargeID---//
  TString this_bchargeID="";
  if(fabs(bCand_Charge)==1){
    if(bCand_NotUseOppositeCharge){
      this_bchargeID="muH";
      cat_id=1;
    }
    else{
      this_bchargeID="muL";
      cat_id=2;
    }
  }
  else if(fabs(bCand_Charge)==2){
    if(bCand_NotUseOppositeCharge){
      this_bchargeID="eH";
      cat_id=3;
    }
    else{
      this_bchargeID="eL";
      cat_id=4;
    }
  }
  else if(fabs(bCand_Charge)==3){
    this_bchargeID="jG";
    cat_id=5;
    }
  else{
    this_bchargeID="jB";
    cat_id=6;
  }
  //---orig parton
  TString this_orig_parton=JHAnalyzerBase::Get_orig_parton_bChargeID(v_bjet[0]);
  
  if(apply_bchargeeff && !IsDATA){
    //---SF
    double SF_bChargeID=Get_bChargeID_SF(v_bjet[0].Pt(), this_bchargeID, this_orig_parton);
    weight*=SF_bChargeID;

  }

  FillHist("FinalCut/MeasuredCharge_Total", bCand_Charge,weight,9,-4.5,4.5);
  FillHist("FinalCut/abs_MeasuredCharge_Total", abs(bCand_Charge),weight,5,-0.5,4.5);
  FillHist("FinalCut/category", cat_id,weight,6,0.5,6.5);


  
}//[end]RunBasic Zregion


void bbbarAsymMeasurement::EventLoop(){
  RunBasicZregion();
}  
  


void bbbarAsymMeasurement::TruthLoop(){
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


