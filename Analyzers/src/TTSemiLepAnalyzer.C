#include "TTSemiLepAnalyzer.h"

TTSemiLepAnalyzer::TTSemiLepAnalyzer(){
  //runSys=true;
}

TTSemiLepAnalyzer::~TTSemiLepAnalyzer(){
  //==== Destructor of this Analyzer
}

void TTSemiLepAnalyzer::initializeAnalyzer(){
  cout << "[TTSemiLepAnalyzer::initializeAnalyzer]" << endl;
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

  //LoadTTSemilepJetAssignmentTool("1.0");

}


void TTSemiLepAnalyzer::SetMuon(const Muon& _l1){
  mu1=_l1;
}

bool TTSemiLepAnalyzer::CheckIsMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  vector<Muon> v_muon=noveto ? GetSingleMuRecoNoVeto(TriggerSafeCut_muon1) : GetSingleMuReco(TriggerSafeCut_muon1);
  if( v_muon.size()!=1) return 0;
  SetMuon(v_muon[0]);

  return 1;
}  

void TTSemiLepAnalyzer::SetElectron(const Electron& _l1){
  el1=_l1;
}


bool TTSemiLepAnalyzer::CheckIsElectronChannel(){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  
  //vector<int> v_electronidx=GetIdxDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  vector<Electron> v_electron=noveto ? GetSingleElRecoNoVeto(TriggerSafeCut_electron1) : GetSingleElReco(TriggerSafeCut_electron1);
  if( v_electron.size()!=1) return 0;
  //SetElectronIdx(v_electronidx[0],v_electronidx[1]);
  SetElectron(v_electron[0]);
  return 1;
}  

void TTSemiLepAnalyzer::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  //weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*btagsf;
  //Muon
  if(IsMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }
  
}

void TTSemiLepAnalyzer::RunReco(){

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
  //----Jet---//
  v_tightlep={l1};
  v_tightjet=GetTightJet(v_tightlep,30,2.4);
  v_bjetidx=GetBJetIdx(v_tightjet);

  njet=v_tightjet.size();
  nbjet=v_bjetidx.size();

  //--Now Objects are ready--//
  SetEventWeight();


  if(nbjet != 2) return;
  if(v_tightjet.size()<4) return;

  //FillHistAll(LepCh+"_beforeFit");
  //FillHistAll("AllLep_beforeFit");


  Run();

}
void TTSemiLepAnalyzer::Run(){
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

  //FillHistAll(LepCh+"_afterFit");
  //FillHistAll("AllLep_afterFit");
 
  RunPlots();
}

void TTSemiLepAnalyzer::RunPlots(){
  
  if(IsTTLJSample){
    bool isbLepMatched=0;
    bool isbHadMatched=0;
    /*
    //---bLep flavour match
    int bLep_FlavourMatched= v_tightjet[iblep].partonFlavour()==bLep_True_PID;
    int bLep_FlavourMatched_Opposite= v_tightjet[iblep].partonFlavour()==-bLep_True_PID;
    int bLep_dRMatched = v_tightjet[iblep].DeltaR(gens[bLep_True_genidx]) < 0.4;
    
    
    //---bHad flavour match
    int bHad_FlavourMatched= v_tightjet[ibhad].partonFlavour()==bHad_True_PID;
    int bHad_FlavourMatched_Opposite= v_tightjet[ibhad].partonFlavour()==-bHad_True_PID;
    int bHad_dRMatched = v_tightjet[ibhad].DeltaR(gens[bHad_True_genidx]) < 0.4;
    
    //--Whad, light quarks
    int q11_FlavourMatched=v_tightjet[iq1].partonFlavour()==Whad_q1_pid;
    int q22_FlavourMatched=v_tightjet[iq2].partonFlavour()==Whad_q2_pid;
    int q12_FlavourMatched=v_tightjet[iq1].partonFlavour()==Whad_q2_pid;
    int q21_FlavourMatched=v_tightjet[iq2].partonFlavour()==Whad_q1_pid;



    int q11_dRMatched=v_tightjet[iq1].DeltaR(gens[v_idx_lightquark_GEN[0]]) < 0.4;
    int q22_dRMatched=v_tightjet[iq2].DeltaR(gens[v_idx_lightquark_GEN[1]]) < 0.4;
    
    int q12_dRMatched=v_tightjet[iq1].DeltaR(gens[v_idx_lightquark_GEN[1]]) < 0.4;
    int q21_dRMatched=v_tightjet[iq2].DeltaR(gens[v_idx_lightquark_GEN[0]]) < 0.4;
    

    int qq_FlavourMatched= 0;
    if(q11_FlavourMatched && q22_FlavourMatched) qq_FlavourMatched=1;
    if(q21_FlavourMatched && q12_FlavourMatched) qq_FlavourMatched=1;
    
    int qq_Flavour_AND_dRMatched= 0;
    if(q11_FlavourMatched&&q11_dRMatched && q22_FlavourMatched&&q22_dRMatched) qq_Flavour_AND_dRMatched=1;
    if(q12_FlavourMatched&&q12_dRMatched && q21_FlavourMatched&&q21_dRMatched) qq_Flavour_AND_dRMatched=1;
    */
    bool isbLepFlavourMatched= v_tightjet[iblep].partonFlavour()==bLep_True_PID;
    bool isbLepDeltaRMatched= v_tightjet[iblep].DeltaR(gens[bLep_True_genidx]) < 0.4;
    isbLepMatched=isbLepFlavourMatched&&isbLepDeltaRMatched;

    bool isbHadFlavourMatched= v_tightjet[ibhad].partonFlavour()==bHad_True_PID;
    bool isbHadDeltaRMatched= v_tightjet[ibhad].DeltaR(gens[bHad_True_genidx]) < 0.4;
    isbHadMatched=isbHadFlavourMatched&&isbHadDeltaRMatched;
    if(isbLepMatched && isbHadMatched){
      ProcessName=MCSample+"_AllMatched";
    }
    else if(isbLepMatched){
      ProcessName=MCSample+"_bLepMatchedOnly";
    }
    else if(isbHadMatched){
      ProcessName=MCSample+"_bHadMatchedOnly";
    }
    else{
      ProcessName=MCSample+"_Unmatched";
    }

  }//[END of TTLJ]
  SetTopAndW();
  

  //FillHistAll(LepCh+"_afterFit");
  //FillHistAll("AllLep_afterFit");

  FillHistTTLJ(LepCh+"_TTLJ");
  FillHistTTLJ("AllLep_TTLJ");
  

}
void TTSemiLepAnalyzer::SetTopAndW(){

  Wlep_cand=l1+neutrino_cand;
  Whad_cand=v_tightjet[iq1]+v_tightjet[iq2];
  Tlep_cand=Wlep_cand+v_tightjet[iblep];
  Thad_cand=Whad_cand+v_tightjet[ibhad];
}
bool TTSemiLepAnalyzer::HasMatchedRecoJet(int genidx,double dRcut){
  TLorentzVector this_genptl=gens[genidx];
  for(auto &jet : v_tightjet){
    if(this_genptl.DeltaR(jet) < dRcut) return 1;
  }
  return 0;
}


bool TTSemiLepAnalyzer::HasFlavourMatchedRecoJet(int genidx){
  //TLorentzVector this_genptl=gens[genidx];
  int true_pid=gens[genidx].PID();
  for(auto &jet : v_tightjet){
    if(jet.partonFlavour() == true_pid) return 1;
  }
  return 0;
}




void TTSemiLepAnalyzer::FillHistTTLJ(TString cutname){
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


  FillHist(cutname+"/bLep_cand_pt",v_tightjet[iblep].Pt(),weight,100,0,300);
  FillHist(cutname+"/bLep_cand_eta",v_tightjet[iblep].Eta(),weight,100,-5,5);
  FillHist(cutname+"/bLep_cand_phi",v_tightjet[iblep].Phi(),weight,100,-4,4);

  FillHist(cutname+"/bHad_cand_pt",v_tightjet[ibhad].Pt(),weight,100,0,300);
  FillHist(cutname+"/bHad_cand_eta",v_tightjet[ibhad].Eta(),weight,100,-5,5);
  FillHist(cutname+"/bHad_cand_phi",v_tightjet[ibhad].Phi(),weight,100,-4,4);





  

  //v_tightjet[iblep],l1,
  double M_blep_l = (l1+v_tightjet[iblep]).M();
  FillHist(cutname+"/M_blep_l",M_blep_l,weight,100,0,400);
  double abs_dphi_Tlep_Thad=fabs(Tlep_cand.DeltaPhi(Thad_cand));
  FillHist(cutname+"/abs_dphi_Tlep_Thad",abs_dphi_Tlep_Thad,weight,100,0,4);




  FillHistAll(cutname);
}
void TTSemiLepAnalyzer::FillHistAll(TString cutname){
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


void TTSemiLepAnalyzer::EventLoop(){
  RunReco();

}





void TTSemiLepAnalyzer::TruthLoop(){
  //it must be TTLJ samples
  if (IsTTLJSample){
    TTSemiLepAnalyzer::RunLHEinfo();
    TTSemiLepAnalyzer::RunGENinfo();
  }

}

void TTSemiLepAnalyzer::RunLHEinfo(){
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
void TTSemiLepAnalyzer::RunGENinfo(){
  unsigned int gensize=gens.size();
  //status21 is incoming particle.
  //To find W decay daughters 

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


