#include "OneBjet.h"

OneBjet::OneBjet(){
  //runSys=true;
}

OneBjet::~OneBjet(){
  //==== Destructor of this Analyzer
}

void OneBjet::initializeAnalyzer(){
  cout << "[OneBjet::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupSingleLeptonChannel();
  noveto=false;
  if(HasFlag("noveto")){
    noveto=true;
  }

  njet4=false;
  if(HasFlag("njet4")){
    njet4=true;
  }

  TString v_muonScore="2405.4.3";
  TString v_electronScore="2405.4.3";
  TString v_jetScore="2405.4.3";
  bool apply_dnncut=true;
  LoadChargeScoreTool(v_muonScore,v_electronScore,v_jetScore,apply_dnncut);




}


void OneBjet::SetMuon(const Muon& _l1){
  mu1=_l1;
}

bool OneBjet::CheckIsMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;

  vector<Muon> v_muon;
  v_muon=noveto ? GetSingleMuRecoNoVeto(TriggerSafeCut_muon1) : GetSingleMuReco(TriggerSafeCut_muon1);

  if( v_muon.size()!=1) return 0;
  SetMuon(v_muon[0]);

  return 1;
}  

void OneBjet::SetElectron(const Electron& _l1){
  el1=_l1;
}


bool OneBjet::CheckIsElectronChannel(){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  vector<Electron> v_electron;
  v_electron=noveto ? GetSingleElRecoNoVeto(TriggerSafeCut_electron1) : GetSingleElReco(TriggerSafeCut_electron1);
  
  if( v_electron.size()!=1) return 0;
  SetElectron(v_electron[0]);
  return 1;
}  

void OneBjet::SetEventWeight(){
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

void OneBjet::RunReco(){

  IsMuonChannel=false;
  IsElectronChannel=false;


  IsMuonChannel=CheckIsMuonChannel();
  if(!IsMuonChannel) IsElectronChannel=CheckIsElectronChannel();





  LepCh="";
  if(IsMuonChannel){
    //vtW=GetTransverseVector(mu1)+CurrentMET;
    LepCh="Muon";
    l1=mu1;
  }
  else if(IsElectronChannel){
    //vtW=GetTransverseVector(el1)+CurrentMET;
    LepCh="Electron";
    l1=el1;
  }  

  else{
    return;
  }
  //----Jet---//
  v_tightlep={l1};
  v_tightjet=GetTightJet(v_tightlep,30,2.4);
  v_bjetidx=GetBJetIdx(v_tightjet);
  nbjet=v_bjetidx.size();
  if(nbjet != 1) return;
  njet=v_tightjet.size();
  //if(v_tightjet.size()<4) return;
  if(njet4 && v_tightjet.size()!=4) return;
  //--Now Objects are ready--//
  SetEventWeight();

  for(auto &i_bjet : v_bjetidx){
    /*
    tuple<int,bool,int,int,double> bCand_Charge_info=GetBJetCharge_v2405_4_3(v_tightjet[i_bjet],AllMuons,AllElectrons);
    int bCand_Charge=std::get<0>(bCand_Charge_info);
    bool bCand_NotUseOppositeCharge=std::get<1>(bCand_Charge_info);
    int bCand_im=std::get<2>(bCand_Charge_info);
    int bCand_ie=std::get<3>(bCand_Charge_info);
    double bCnad_ChargeScore=std::get<4>(bCand_Charge_info);

    v_tightjet[i_bjet].SetBCharge(bCand_Charge);
    v_tightjet[i_bjet].SetNotUsingOppositeCharge(bCand_NotUseOppositeCharge);
    v_tightjet[i_bjet].SetMuonIdxInBjet(bCand_im);
    v_tightjet[i_bjet].SetElectronIdxInBjet(bCand_ie);
    v_tightjet[i_bjet].SetBChargeScore(bCnad_ChargeScore);
    */

    FillHist("AllLep/pt_b",v_tightjet[i_bjet].Pt(),weight,100,0,300);
    FillHist("AllLep/eta_b",v_tightjet[i_bjet].Eta(),weight,50,-3,3);
    //---Has SoftMuon
    tuple<int,double,double,int,double,double> ret=JHAnalyzerBase::GetBJetMuonScore_v2409_2(v_tightjet[i_bjet], AllMuons);
    //{im_max,bmuon_score_max,bmuon_charge_max,im_min,bmuon_score_min,bmuon_charge_min
    int im_max=std::get<0>(ret);
    double bmuon_score_max=std::get<1>(ret);
    double bmuon_charge_max=std::get<2>(ret);

    int im_min=std::get<3>(ret);
    double bmuon_score_min=std::get<4>(ret);
    double bmuon_charge_min=std::get<5>(ret);


    bool HasSoftMuon=false;

    if(bmuon_charge_max!=0)      HasSoftMuon=true;
    //---SLTMuonPassCutToMax
    bool SLTMuonPassCutToMax=false;
    if(bmuon_score_max > mChargeTool->mincut) SLTMuonPassCutToMax=true;
    //--SLTMuonPassCutToMin
    bool SLTMuonPassCutToMin=false;


  }
  RunPlots();

}

void OneBjet::RunPlots(){
  FillHistCommon(LepCh);
  FillHistCommon("AllLep");
  
  


}


void OneBjet::FillHistCommon(TString cutname){
  FillHist(cutname+"/pt_l1",l1.Pt(),weight,200,0,200);
  FillHist(cutname+"/eta_l1",l1.Eta(),weight,50,-3,3);

  FillHist(cutname+"/met",CurrentMET.Pt(),weight,150,0,300);
  FillHist(cutname+"/njet",njet,weight,10,0,10);
  FillHist(cutname+"/nbjet",nbjet,weight,10,0,10);
  
  FillHistAllB(cutname);
}
void OneBjet::FillHistAllB(TString cutname){
  for(auto &i_bjet : v_bjetidx){
    int BCharge=v_tightjet[i_bjet].GetBCharge(); // if abs ==1 : muon / abs==2 : electron / abs==3:goodbjet / abs==4:badbjet
    bool NotUsingOppositeCharge=v_tightjet[i_bjet].GetNotUsingOppositeCharge();
    //int MuonIdxInBjet=v_tightjet[i_bjet].GetMuonIdxInBjet();
    //int ElectronIdxInBjet=v_tightjet[i_bjet].GetElectronIdxInBjet();
    //double BChargeScore=v_tightjet[i_bjet].GetBChargeScore();

    ///--SetProcessName//
    if(!IsDATA){
      if(abs(v_tightjet[i_bjet].partonFlavour())==5  ){
	ProcessName=MCSample+"_Flavour5";
      }
      else{
	ProcessName=MCSample+"_FlavourOthers";
      }
    }
    FillHistBInfo(cutname, i_bjet);

    if(abs(BCharge)==1){
      FillHistBInfo(cutname+"__UseMuonCharge", i_bjet);
      if(NotUsingOppositeCharge){
	FillHistBInfo(cutname+"__UseMuonChargeSame", i_bjet);
      }
      else{
	FillHistBInfo(cutname+"__UseMuonChargeOpposite", i_bjet);
      }

    }// [END] if using muoncharge
    else if(abs(BCharge)==2){
      FillHistBInfo(cutname+"__UseElectronCharge", i_bjet);
      if(NotUsingOppositeCharge){
	FillHistBInfo(cutname+"__UseElectronChargeSame", i_bjet);
      }
      else{
	FillHistBInfo(cutname+"__UseElectronChargeOpposite", i_bjet);
      }
    }//[END] if using electroncharge

    else if(abs(BCharge)==3){
      FillHistBInfo(cutname+"__UseJetChargeGood", i_bjet);
    }//[END]  using good bjet charge
    else{
      FillHistBInfo(cutname+"__UseJetChargeBad", i_bjet);
    }
  }




}

void OneBjet::FillHistBInfo(TString cutname, int i_bjet){
  FillHist(cutname+"/pt_b",v_tightjet[i_bjet].Pt(),weight,150,0,300);
  FillHist(cutname+"/eta_b",v_tightjet[i_bjet].Eta(),weight,60,-3,3);

  FillHist(cutname+"/partonFlavour",v_tightjet[i_bjet].partonFlavour(),weight,27,-6,27);
  FillHist(cutname+"/BChargeScore",v_tightjet[i_bjet].GetBChargeScore(),weight,100,0,1);



}
void OneBjet::EventLoop(){
  RunReco();

}





