#include "TTSemiLepJetAssignment.h"

TTSemiLepJetAssignment::TTSemiLepJetAssignment(){
  //runSys=true;
}

TTSemiLepJetAssignment::~TTSemiLepJetAssignment(){
  //==== Destructor of this Analyzer
}

void TTSemiLepJetAssignment::initializeAnalyzer(){
  cout << "[TTSemiLepJetAssignment::initializeAnalyzer]" << endl;
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

  LoadTTSemilepJetAssignmentTool("1.0");

}


void TTSemiLepJetAssignment::SetMuon(const Muon& _l1){
  mu1=_l1;
}

bool TTSemiLepJetAssignment::CheckIsMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  vector<Muon> v_muon=noveto ? GetSingleMuRecoNoVeto(TriggerSafeCut_muon1) : GetSingleMuReco(TriggerSafeCut_muon1);
  if( v_muon.size()!=1) return 0;
  SetMuon(v_muon[0]);

  return 1;
}  

void TTSemiLepJetAssignment::SetElectron(const Electron& _l1){
  el1=_l1;
}


bool TTSemiLepJetAssignment::CheckIsElectronChannel(){
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

void TTSemiLepJetAssignment::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  //weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*btagsf;
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf*jetpuidsf;  
  //Muon
  if(IsMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }
  
}

void TTSemiLepJetAssignment::RunReco(){

  IsMuonChannel=false;
  IsElectronChannel=false;


  IsMuonChannel=CheckIsMuonChannel();
  if(!IsMuonChannel) IsElectronChannel=CheckIsElectronChannel();





  TString LepCh="";
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
  ///----light jets from W----//

  bool flavourmatch1=false;
  bool flavourmatch2=false;

  i_LightJet1=-1;
  i_LightJet2=-1;
  int i_jet=-1;

  for(auto &jet: v_tightjet){
    i_jet+=1;
    if(i_jet==v_bjetidx[0]){
      continue; //to skip bjet
    }
    if(i_jet==v_bjetidx[1]){
      continue; //to skip bjet
    }

    ///flavour matching
    bool this_flavourmatch1=jet.partonFlavour()==Whad_q1_pid;
    bool this_flavourmatch2=jet.partonFlavour()==Whad_q2_pid;
    if(!flavourmatch1){//if q1 is not matched yet 
      if(this_flavourmatch1){
	flavourmatch1=1;
	i_LightJet1=i_jet;
	continue; //take the hardest one
      }
    }

    if(!flavourmatch2){//if q1 is not matched yet 
      if(this_flavourmatch2){
	flavourmatch2=1;
	i_LightJet2=i_jet;
	continue; //take the hardest one
      }
    }
    

  }//[END OF tightjet loop]

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

  Run("Chi2");
  Run("DNN");
}
void TTSemiLepJetAssignment::Run(TString _type){
  int iblep=-1;
  int ibhad=-1;
  int iq1=-1;
  int iq2=-1;
  double vz_fit=0.0;
  ////Minimal Chi2 Method - kin fitter
  if (_type=="Chi2"){
    pair<vector<int>,double> v_jetidxset_and_vz_chi2=GetJetIndexSet_Chi2();
    
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
    
  }
  else if(_type=="DNN"){

    
    vector<int> v_jetidxset_dnn=GetJetIndexSet_DNN();
    //[0]=ib1 = bLep cand's v_bjet index
    //[1]=ib2 = bHad cand's v_bjet index
    //[2]=iq1 = one of light quark candiate v_tightjet index
    //[3]=iq2 = one of light quark candiate v_tightjet index
    iblep=v_jetidxset_dnn[0];
    ibhad=v_jetidxset_dnn[1];
    iq1=v_jetidxset_dnn[2];
    iq2=v_jetidxset_dnn[3];
  }
  else{
    cout << "No type for jet assignement->" << _type << endl;
  }

  
  if(iblep<0) return;
  if(ibhad<0) return;
  if(iq1<0) return;
  if(iq2<0) return;
  
  
  if (_type=="Chi2"){//check vz fit to truth
    FillHist(_type+"/all/vz_fit",vz_fit,weight,150,-300,300);
    FillHist(_type+"/all/vz_GEN",gens[i_neutrino_GEN].Pz(),weight,150,-300,300);
    if(gens[i_neutrino_GEN].Pz()!=0)FillHist(_type+"/all/vz_fit-vz_GEN_div_vz_GEN",(vz_fit-gens[i_neutrino_GEN].Pz())/gens[i_neutrino_GEN].Pz(),weight,200,-4,4);    
  }

  TLorentzVector Whad,Wlep,Thad,Tlep,neutrino;
  Whad=v_tightjet[iq1]+v_tightjet[iq2];
  Thad=Whad+v_tightjet[ibhad];
  neutrino.SetPxPyPzE(CurrentMET.Px(), CurrentMET.Py(), vz_fit, sqrt(pow(CurrentMET.Pt(),2)+pow(vz_fit,2)));
  Wlep=l1+neutrino;
  Tlep=Wlep+v_tightjet[iblep];

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

  //---Mass distribution shapes
  FillHist(_type+"/all/Wlep_M",Wlep.M(),weight,100,30,130);
  if(qq_FlavourMatched){
    FillHist(_type+"/WhadCand_FlavourMatched/Whad_M",Whad.M(),weight,100,30,130);
  }
  if(qq_Flavour_AND_dRMatched){
    FillHist(_type+"/WhadCand_FlavourMatched__dRMatched/Whad_M",Whad.M(),weight,100,30,130);
  }

  if(bLep_FlavourMatched){
    FillHist(_type+"/bLepCand_FlavourMatched/Tlep_M",Tlep.M(),weight,200,100,300);
  }
  if(bool(bLep_FlavourMatched*bLep_dRMatched)){
    FillHist(_type+"/bLepCand_FlavourMatched__dRMatched/Tlep_M",Tlep.M(),weight,200,100,300);
  }

  if(bool(bHad_FlavourMatched*qq_FlavourMatched)){
    FillHist(_type+"/ThadCand_FlavourMatched/Thad_M",Thad.M(),weight,200,100,300);
  }
  if(bool(bHad_FlavourMatched*qq_FlavourMatched*bHad_dRMatched)){
    FillHist(_type+"/ThadCand_FlavourMatched__dRMatched/Thad_M",Thad.M(),weight,200,100,300);
  }

  //---Booleans
  FillHist(_type+"/all/bHadCand_FlavourMatched",bHad_FlavourMatched,weight,4,-1,3);
  FillHist(_type+"/all/bHadCand_FlavourMatched_Opposite",bHad_FlavourMatched_Opposite,weight,4,-1,3);
  FillHist(_type+"/all/bHadCand_FlavourMatched__dRMatched",bHad_FlavourMatched*bHad_dRMatched,weight,4,-1,3);
  FillHist(_type+"/all/WhadCand_FlavourMatched",qq_FlavourMatched,weight,4,-1,3);
  FillHist(_type+"/all/WhadCand_FlavourMatched__dRMatched",qq_Flavour_AND_dRMatched,weight,4,-1,3);
  FillHist(_type+"/all/ThadCand_FlavourMatched",bHad_FlavourMatched*qq_FlavourMatched,weight,4,-1,3);
  FillHist(_type+"/all/ThadCand_FlavourMatched__dRMatched",bHad_FlavourMatched*bHad_dRMatched*qq_Flavour_AND_dRMatched,weight,4,-1,3);


  FillHist(_type+"/all/bLepCand_FlavourMatched",bLep_FlavourMatched,weight,4,-1,3);
  FillHist(_type+"/all/bLepCand_FlavourMatched_Opposite",bLep_FlavourMatched_Opposite,weight,4,-1,3);
  FillHist(_type+"/all/bLepCand_FlavourMatched__dRMatched",bLep_FlavourMatched*bLep_dRMatched,weight,4,-1,3);

  bool bHadGen_Has_dRMatchedJet=HasMatchedRecoJet(bHad_True_genidx);
  if(bHadGen_Has_dRMatchedJet){
    FillHist(_type+"/if_bHadGen_Has_dRMatchedJet/bHadCand_FlavourMatched",bHad_FlavourMatched,weight,4,-1,3);
    FillHist(_type+"/if_bHadGen_Has_dRMatchedJet/bHadCand_FlavourMatched_Opposite",bHad_FlavourMatched_Opposite,weight,4,-1,3);
    FillHist(_type+"/if_bHadGen_Has_dRMatchedJet/bHadCand_dRMatched",bHad_dRMatched,weight,4,-1,3);
    FillHist(_type+"/if_bHadGen_Has_dRMatchedJet/bHadCand_FlavourMatched__dRMatched",bHad_FlavourMatched*bHad_dRMatched,weight,4,-1,3);
    FillHist(_type+"/if_bHadGen_Has_dRMatchedJet/bHadCand_partonFlavour",v_tightjet[ibhad].partonFlavour(),weight,32,-6,25);
  }
  FillHist(_type+"/all/bHadGen_Has_dRMatchedJet",bHadGen_Has_dRMatchedJet,weight,4,-1,3);


  bool bHadGen_Has_FlavourMatchedJet=HasFlavourMatchedRecoJet(bHad_True_genidx);
  if(bHadGen_Has_FlavourMatchedJet){
    FillHist(_type+"/if_bHadGen_Has_FlavourMatchedJet/bHadCand_FlavourMatched",bHad_FlavourMatched,weight,4,-1,3);
    FillHist(_type+"/if_bHadGen_Has_FlavourMatchedJet/bHadCand_FlavourMatched_Opposite",bHad_FlavourMatched_Opposite,weight,4,-1,3);
    FillHist(_type+"/if_bHadGen_Has_FlavourMatchedJet/bHadCand_dRMatched",bHad_dRMatched,weight,4,-1,3);
    FillHist(_type+"/if_bHadGen_Has_FlavourMatchedJet/bHadCand_FlavourMatched__dRMatched",bHad_FlavourMatched*bHad_dRMatched,weight,4,-1,3);
    FillHist(_type+"/if_bHadGen_Has_FlavourMatchedJet/bHadCand_partonFlavour",v_tightjet[ibhad].partonFlavour(),weight,32,-6,25);

  }
  FillHist(_type+"/all/bHadGen_Has_FlavourMatchedJet",bHadGen_Has_FlavourMatchedJet,weight,4,-1,3);



  bool bLepGen_Has_dRMatchedJet=HasMatchedRecoJet(bLep_True_genidx);
  if(bLepGen_Has_dRMatchedJet){
    FillHist(_type+"/if_bLepGen_Has_dRMatchedJet/bLepCand_FlavourMatched",bLep_FlavourMatched,weight,4,-1,3);
    FillHist(_type+"/if_bLepGen_Has_dRMatchedJet/bLep_FlavourMatched_Opposite",bLep_FlavourMatched_Opposite,weight,4,-1,3);
    FillHist(_type+"/if_bLepGen_Has_dRMatchedJet/bLep_dRMatched",bLep_dRMatched,weight,4,-1,3);
    FillHist(_type+"/if_bLepGen_Has_dRMatchedJet/bLepCand_FlavourMatched__dRMatched",bLep_FlavourMatched*bLep_dRMatched,weight,4,-1,3);
    FillHist(_type+"/if_bLepGen_Has_dRMatchedJet/bLepCand_partonFlavour",v_tightjet[iblep].partonFlavour(),weight,32,-6,25);
  }
  FillHist(_type+"/all/bLepGen_Has_dRMatchedJet",bLepGen_Has_dRMatchedJet,weight,4,-1,3);

  bool bLepGen_Has_FlavourMatchedJet=HasFlavourMatchedRecoJet(bLep_True_genidx);
  if(bLepGen_Has_FlavourMatchedJet){
    FillHist(_type+"/if_bLepGen_Has_FlavourMatchedJet/bLepCand_FlavourMatched",bLep_FlavourMatched,weight,4,-1,3);
    FillHist(_type+"/if_bLepGen_Has_FlavourMatchedJet/bLep_FlavourMatched_Opposite",bLep_FlavourMatched_Opposite,weight,4,-1,3);
    FillHist(_type+"/if_bLepGen_Has_FlavourMatchedJet/bLep_dRMatched",bLep_dRMatched,weight,4,-1,3);
    FillHist(_type+"/if_bLepGen_Has_FlavourMatchedJet/bLepCand_FlavourMatched__dRMatched",bLep_FlavourMatched*bLep_dRMatched,weight,4,-1,3);
    FillHist(_type+"/if_bLepGen_Has_FlavourMatchedJet/bLepCand_partonFlavour",v_tightjet[iblep].partonFlavour(),weight,32,-6,25);
  }
  FillHist(_type+"/all/bLepGen_Has_FlavourMatchedJet",bLepGen_Has_FlavourMatchedJet,weight,4,-1,3);




  bool q1Gen_Has_dRMatchedJet=HasMatchedRecoJet(v_idx_lightquark_GEN[0]);
  bool q2Gen_Has_dRMatchedJet=HasMatchedRecoJet(v_idx_lightquark_GEN[1]);
  bool q1q2Gen_Has_dRMatchedJet=q1Gen_Has_dRMatchedJet&&q2Gen_Has_dRMatchedJet;
  if(q1q2Gen_Has_dRMatchedJet){
    FillHist(_type+"/if_q1q2Gen_Has_dRMatchedJet/qq_FlavourMatched",qq_FlavourMatched,weight,4,-1,3);
    FillHist(_type+"/if_q1q2Gen_Has_dRMatchedJet/qq_FlavourMatched__dRMatched",qq_Flavour_AND_dRMatched,weight,4,-1,3);
    
  }
  FillHist(_type+"/all/q1q2Gen_Has_dRMatchedJet",q1q2Gen_Has_dRMatchedJet,weight,4,-1,3);


  bool q1Gen_Has_FlavourMatchedJet=HasFlavourMatchedRecoJet(v_idx_lightquark_GEN[0]);
  bool q2Gen_Has_FlavourMatchedJet=HasFlavourMatchedRecoJet(v_idx_lightquark_GEN[1]);
  bool q1q2Gen_Has_FlavourMatchedJet=q1Gen_Has_FlavourMatchedJet&&q2Gen_Has_FlavourMatchedJet;
  if(q1q2Gen_Has_FlavourMatchedJet){
    FillHist(_type+"/if_q1q2Gen_Has_FlavourMatchedJet/qq_FlavourMatched",qq_FlavourMatched,weight,4,-1,3);
    FillHist(_type+"/if_q1q2Gen_Has_FlavourMatchedJet/qq_FlavourMatched__dRMatched",qq_Flavour_AND_dRMatched,weight,4,-1,3);
    
  }
  FillHist(_type+"/all/q1q2Gen_Has_FlavourMatchedJet",q1q2Gen_Has_FlavourMatchedJet,weight,4,-1,3);


  bool THad_Has_dRMatchedJet=q1q2Gen_Has_dRMatchedJet&&bHadGen_Has_dRMatchedJet;
  if(THad_Has_dRMatchedJet){
    FillHist(_type+"/if_THad_Has_dRMatchedJet/Thad_FlavourMatched",bHad_FlavourMatched*qq_FlavourMatched,weight,4,-1,3);
    FillHist(_type+"/if_THad_Has_dRMatchedJet/THad_FlavourMatched__dRMatched",bHad_FlavourMatched*bHad_dRMatched*qq_Flavour_AND_dRMatched,weight,4,-1,3);
  }
  FillHist(_type+"/all/THad_Has_dRMatchedJet",THad_Has_dRMatchedJet,weight,4,-1,3);


  bool THad_Has_FlavourMatchedJet=q1q2Gen_Has_FlavourMatchedJet&&bHadGen_Has_FlavourMatchedJet;
  if(THad_Has_FlavourMatchedJet){
    FillHist(_type+"/if_THad_Has_FlavourMatchedJet/Thad_FlavourMatched",bHad_FlavourMatched*qq_FlavourMatched,weight,4,-1,3);
    FillHist(_type+"/if_THad_Has_FlavourMatchedJet/THad_FlavourMatched__dRMatched",bHad_FlavourMatched*bHad_dRMatched*qq_Flavour_AND_dRMatched,weight,4,-1,3);
  }
  FillHist(_type+"/all/THad_Has_FlavourMatchedJet",THad_Has_FlavourMatchedJet,weight,4,-1,3);



}
bool TTSemiLepJetAssignment::HasMatchedRecoJet(int genidx,double dRcut){
  TLorentzVector this_genptl=gens[genidx];
  for(auto &jet : v_tightjet){
    if(this_genptl.DeltaR(jet) < dRcut) return 1;
  }
  return 0;
}


bool TTSemiLepJetAssignment::HasFlavourMatchedRecoJet(int genidx){
  //TLorentzVector this_genptl=gens[genidx];
  int true_pid=gens[genidx].PID();
  for(auto &jet : v_tightjet){
    if(jet.partonFlavour() == true_pid) return 1;
  }
  return 0;
}



pair<vector<int>,double> TTSemiLepJetAssignment::GetJetIndexSet_Chi2(){
  unsigned int v_tightjetsize=v_tightjet.size();
  double minchi2=99999999999999.;
  pair<vector<int>,double> ret({-1,-1,-1,-1},0.0);
  

  for(auto &ib1 : v_bjetidx){
    for(auto &ib2 : v_bjetidx){
      if(ib1==ib2)continue;
      for(unsigned int iq1=0; iq1 < v_tightjetsize; iq1++){
	if(ib1==iq1) continue;
	if(ib2==iq1) continue;//skip bquark
	for(unsigned int iq2=0; iq2 < v_tightjetsize; iq2++){
	  if(iq1==iq2) continue;
	 
	  if(ib1==iq2) continue;
	  if(ib2==iq2) continue;//skip bquark
	  
	  ///-----NOW we have ib1,ib2,iq1,iq2
	  // let ib2 "bHad" candidate
	  //TLorentzVector this_Whad, this_Thad;
	  //this_Whad=v_tightjet[iq1]+v_tightjet[iq2];
	  //this_Thad=this_Whad+v_tightjet[ib2];
	  //double this_Whad_mass=this_Whad.M();
	  //double this_Thad_mass=this_Thad.M();

	  //double this_chi2 = pow((this_Whad_mass - MW_pdg)/Width_W_pdg,2) + pow((this_Thad_mass - MTop_pdg)/Width_Top_pdg,2);
	  //double TTSemiLepJetAssignment::Chi2TTSemiLep(double *x, TLorentzVector _lep, TLorentzVector _MET, TLorentzVector _blep, TLorentzVector _q1, TLorentzVector _q2, TLorentzVector _bhad){
	  //pair<doube,double> TTSemiLepJetAssignment::GetChi2_and_vz(TLorentzVector _lep, TLorentzVector _MET, TLorentzVector _blep, TLorentzVector _q1, TLorentzVector _q2, TLorentzVector _bhad){
	  TLorentzVector this_Thad, this_Whad;
	  this_Whad=v_tightjet[iq1]+v_tightjet[iq2];
	  this_Thad=this_Whad+v_tightjet[ib2];
	  if(HcbCR){
	    ///1) ThadCand mass : [100,240]
	    ///2) M(blep,l) < 170

	    double this_Thad_mass=this_Thad.M();
	    if(this_Thad_mass < 100.) continue;
	    if(this_Thad_mass > 240.) continue;
	    TLorentzVector this_blep_lep;
	    this_blep_lep=l1+v_tightjet[ib1];
	    double this_blep_lep_mass=this_blep_lep.M();
	    if(this_blep_lep_mass > 170.) continue;
	  }

	  pair<double,double> this_chi2ret=GetChi2_and_vz(l1,CurrentMET,v_tightjet[ib1],v_tightjet[iq1],v_tightjet[iq2],v_tightjet[ib2]);
	  double this_chi2=this_chi2ret.first;
	  double this_vz=this_chi2ret.second;
	  if(HcbCR){
	    //(3)|dphi(Tlep,Thad)|> 1.5
	    TLorentzVector this_Tlep, this_neutrino;
	    double this_Ev2= pow(CurrentMET.Pt(),2) + pow(this_vz,2);
	    double this_Ev=sqrt(this_Ev2);
	    this_neutrino.SetPxPyPzE(CurrentMET.Px(),CurrentMET.Py(),this_vz,this_Ev);
	    this_Tlep=this_neutrino+v_tightjet[ib1]+l1;
	    
	    //this_Thad,this_Tlep
	    double this_dphi=this_Thad.DeltaPhi(this_Tlep);
	    
	    if(fabs(this_dphi) < 1.5) continue;
	  }


	  if(this_chi2 < minchi2){
	    minchi2=this_chi2;
	    ret.first[0]=ib1; ret.first[1]=ib2; ret.first[2]=iq1, ret.first[3]=iq2;
	    ret.second=this_vz;

	  }
	}//[END of iq2]
      }//[END of iq1]
    }//[END of ib2]

  }//[END of ib1 loop]
  return ret;
}


vector<int> TTSemiLepJetAssignment::GetJetIndexSet_DNN(){
  unsigned int v_tightjetsize=v_tightjet.size();
  double maxdnn=-1;
  vector<int> ret ={-1,-1,-1,-1};
  

  for(auto &ib1 : v_bjetidx){
    for(auto &ib2 : v_bjetidx){
      if(ib1==ib2)continue;
      for(unsigned int iq1=0; iq1 < v_tightjetsize; iq1++){
	if(ib1==iq1) continue;
	if(ib2==iq1) continue;//skip bquark
	for(unsigned int iq2=0; iq2 < v_tightjetsize; iq2++){
	  if(iq1==iq2) continue;
	 
	  if(ib1==iq2) continue;
	  if(ib2==iq2) continue;//skip bquark
	  
	  ///-----NOW we have ib1,ib2,iq1,iq2
	  // let ib2 "bHad" candidate
	  //TLorentzVector this_Whad, this_Thad;
	  //this_Whad=v_tightjet[iq1]+v_tightjet[iq2];
	  //this_Thad=this_Whad+v_tightjet[ib2];
	  //double this_Whad_mass=this_Whad.M();
	  //double this_Thad_mass=this_Thad.M();


	  TLorentzVector this_Thad, this_Whad;
	  this_Whad=v_tightjet[iq1]+v_tightjet[iq2];
	  this_Thad=this_Whad+v_tightjet[ib2];
	  if(HcbCR){
	    ///1) ThadCand mass : [100,240]
	    ///2) M(blep,l) < 170

	    double this_Thad_mass=this_Thad.M();
	    if(this_Thad_mass < 100.) continue;
	    if(this_Thad_mass > 240.) continue;
	    TLorentzVector this_blep_lep;
	    this_blep_lep=l1+v_tightjet[ib1];
	    double this_blep_lep_mass=this_blep_lep.M();
	    if(this_blep_lep_mass > 170.) continue;
	  }

	  double this_dnn=GetDNN(l1,CurrentMET,v_tightjet[ib1],v_tightjet[iq1],v_tightjet[iq2],v_tightjet[ib2]);
	  if(HcbCR){
	    //(3)|dphi(Tlep,Thad)|> 1.5
	    TLorentzVector this_Tlep, this_neutrino;
	    this_neutrino.SetPxPyPzE(CurrentMET.Px(),CurrentMET.Py(),0,CurrentMET.Pt());
	    this_Tlep=this_neutrino+v_tightjet[ib1]+l1;
	    
	    //this_Thad,this_Tlep
	    double this_dphi=this_Thad.DeltaPhi(this_Tlep);
	    
	    if(fabs(this_dphi) < 1.5) continue;
	  }


	  if(this_dnn > maxdnn){
	    maxdnn=this_dnn;
	    ret[0]=ib1; ret[1]=ib2; ret[2]=iq1, ret[3]=iq2;
	  }
	}//[END of iq2]
      }//[END of iq1]
    }//[END of ib2]

  }//[END of ib1 loop]
  return ret;
}


void TTSemiLepJetAssignment::FillHistAll(TString cutname){
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


void TTSemiLepJetAssignment::EventLoop(){
  RunReco();

}





void TTSemiLepJetAssignment::TruthLoop(){
  //it must be TTLJ samples
  TTSemiLepJetAssignment::RunLHEinfo();
  TTSemiLepJetAssignment::RunGENinfo();
  

}

void TTSemiLepJetAssignment::RunLHEinfo(){
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
void TTSemiLepJetAssignment::RunGENinfo(){
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



  
  FillHist("GEN/Whad_mass/"+ProcessName,vWhad.M(), weight, 80, 50, 130);
  FillHist("GEN/Thad_mass/"+ProcessName,vThad.M(), weight, 60, 140, 200);

  FillHist("GEN/Wlep_mass/"+ProcessName,vWlep.M(), weight, 80, 50, 130);
  FillHist("GEN/Tlep_mass/"+ProcessName,vTlep.M(), weight, 60, 140, 200);



  

}

double TTSemiLepJetAssignment::GetDNN(TLorentzVector &_lep, TLorentzVector &_MET, TLorentzVector &_blep, TLorentzVector &_q1, TLorentzVector &_q2, TLorentzVector &_bhad){
  SetTTSemilepJetAssignmentScore(_lep,_MET,_blep,_bhad,_q1,_q2);
  return TTLJJetAssignmentTool->GetScore();
}

pair<double,double> TTSemiLepJetAssignment::GetChi2_and_vz(TLorentzVector &_lep, TLorentzVector &_MET, TLorentzVector &_blep, TLorentzVector &_q1, TLorentzVector &_q2, TLorentzVector &_bhad){
  /*
double JHAnalyzerBase::Chi2TTSemiLep(double *x, double _lepx, double _lepy, double _lepz, double _lepE,
                                     double _blepx, double _blepy, double _blepz, double _blepE,
                                     double _metx, double _mety,
                                     double _q1x, double _q1y, double _q1z, double _q1E,
                                     double _q2x, double _q2y, double _q2z, double _q2E,
                                     double _bhadx, double _bhady, double _bhadz, double _bhadE){

   */
  //nparam=22
  
  TF1 *f1 = new TF1("f1", JHAnalyzerBase::Chi2TTSemiLep, -10000, 10000, 22);//name, function, range,range,nparam
  f1->SetParameter(0, _lep.Px());
  f1->SetParameter(1, _lep.Py());
  f1->SetParameter(2, _lep.Pz());
  f1->SetParameter(3, _lep.E());

  f1->SetParameter(4, _blep.Px());
  f1->SetParameter(5, _blep.Py());
  f1->SetParameter(6, _blep.Pz());
  f1->SetParameter(7, _blep.E());

  f1->SetParameter(8, _MET.Px());
  f1->SetParameter(9, _MET.Py());

  f1->SetParameter(10, _q1.Px());
  f1->SetParameter(11, _q1.Py());
  f1->SetParameter(12, _q1.Pz());
  f1->SetParameter(13, _q1.E());

  f1->SetParameter(14, _q2.Px());
  f1->SetParameter(15, _q2.Py());
  f1->SetParameter(16, _q2.Pz());
  f1->SetParameter(17, _q2.E());

  f1->SetParameter(18, _bhad.Px());
  f1->SetParameter(19, _bhad.Py());
  f1->SetParameter(20, _bhad.Pz());
  f1->SetParameter(21, _bhad.E());

  f1->SetMinimum();

  double min_vz = f1->GetMinimumX();
  double min_val = f1->Eval(min_vz);

  pair<double,double> ret;
  ret.first=min_val;
  ret.second=min_vz;
  delete f1;
  return ret;
}
