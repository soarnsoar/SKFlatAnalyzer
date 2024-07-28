#include "TTSemiLepJetAssignment_ProduceTrainingTree.h"

TTSemiLepJetAssignment_ProduceTrainingTree::TTSemiLepJetAssignment_ProduceTrainingTree(){
  //runSys=true;
}

TTSemiLepJetAssignment_ProduceTrainingTree::~TTSemiLepJetAssignment_ProduceTrainingTree(){
  //==== Destructor of this Analyzer
}

void TTSemiLepJetAssignment_ProduceTrainingTree::initializeAnalyzer(){
  cout << "[TTSemiLepJetAssignment_ProduceTrainingTree::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupSingleLeptonChannel();
  noveto=false;
  if(HasFlag("noveto")){
    noveto=true;
  }

  doReduction=0;
  if(HasFlag("reduction_1M")){
    doReduction=1;
    if(DataEra=="2016preVFP"){
      sig_mod=5;
      bkg_mod=50;
    }
    else if(DataEra=="2016postVFP"){
      sig_mod=6;
      bkg_mod=60;
    }
    else if(DataEra=="2017"){
      sig_mod=16;
      bkg_mod=150;
    }
    else if(DataEra=="2018"){
      sig_mod=23;
      bkg_mod=220;
    }
    cout << "sig_mod=" << sig_mod << endl;
    cout << "bkg_mod=" << bkg_mod << endl;
  }


  //---Tree setup
  jhchoi_newtree=new TTree("sig","sig");
  jhchoi_newtree2=new TTree("bkg","bkg");
  SetBranches(jhchoi_newtree);
  SetBranches(jhchoi_newtree2);


}

void TTSemiLepJetAssignment_ProduceTrainingTree::SetBranches(TTree *this_Tree){
  //------
  this_Tree->Branch("event",&event);
  this_Tree->Branch("weight",&weight);

  this_Tree->Branch("met_pt",&met_pt);
  this_Tree->Branch("met_phi",&met_phi);

  this_Tree->Branch("lep_pt",&lep_pt);
  this_Tree->Branch("lep_eta",&lep_eta);
  this_Tree->Branch("lep_phi",&lep_phi);

  this_Tree->Branch("blep_pt",&blep_pt);
  this_Tree->Branch("blep_eta",&blep_eta);
  this_Tree->Branch("blep_phi",&blep_phi);
  this_Tree->Branch("blep_E",&blep_E);

  this_Tree->Branch("bhad_pt",&bhad_pt);
  this_Tree->Branch("bhad_eta",&bhad_eta);
  this_Tree->Branch("bhad_phi",&bhad_phi);
  this_Tree->Branch("bhad_E",&bhad_E);

  this_Tree->Branch("q1jet_pt",&q1jet_pt);
  this_Tree->Branch("q1jet_eta",&q1jet_eta);
  this_Tree->Branch("q1jet_phi",&q1jet_phi);
  this_Tree->Branch("q1jet_E",&q1jet_E);

  this_Tree->Branch("q2jet_pt",&q2jet_pt);
  this_Tree->Branch("q2jet_eta",&q2jet_eta);
  this_Tree->Branch("q2jet_phi",&q2jet_phi);
  this_Tree->Branch("q2jet_E",&q2jet_E);

  this_Tree->Branch("WhadCand_mass",&WhadCand_mass);
  this_Tree->Branch("ThadCand_mass",&ThadCand_mass);

  this_Tree->Branch("WlepCand_mt",&WlepCand_mt);
  this_Tree->Branch("TlepCand_mt",&TlepCand_mt);

}


void TTSemiLepJetAssignment_ProduceTrainingTree::SetMuon(const Muon& _l1){
  mu1=_l1;
}

bool TTSemiLepJetAssignment_ProduceTrainingTree::CheckIsMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  vector<Muon> v_muon=noveto ? GetSingleMuRecoNoVeto(TriggerSafeCut_muon1) : GetSingleMuReco(TriggerSafeCut_muon1);
  if( v_muon.size()!=1) return 0;
  SetMuon(v_muon[0]);

  return 1;
}  

void TTSemiLepJetAssignment_ProduceTrainingTree::SetElectron(const Electron& _l1){
  el1=_l1;
}


bool TTSemiLepJetAssignment_ProduceTrainingTree::CheckIsElectronChannel(){
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

void TTSemiLepJetAssignment_ProduceTrainingTree::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*btagsf;
  //Muon
  if(IsMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }
  
}

void TTSemiLepJetAssignment_ProduceTrainingTree::RunReco(){

  IsMuonChannel=false;
  IsElectronChannel=false;


  IsMuonChannel=CheckIsMuonChannel();
  if(!IsMuonChannel) IsElectronChannel=CheckIsElectronChannel();





  TString LepCh="";
  if(IsMuonChannel){
    vtW=GetTransverseVector(mu1)+PuppiMET;
    LepCh="Muon";
    l1=mu1;
  }
  else if(IsElectronChannel){
    vtW=GetTransverseVector(el1)+PuppiMET;
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

  int i_LightJet1=-1;
  int i_LightJet2=-1;
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


  



  ///-----Let's check combinatorial of jets---//

  unsigned int v_tightjetsize=v_tightjet.size();

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
	  TLorentzVector this_Whad, this_Thad;
	  this_Whad=v_tightjet[iq1]+v_tightjet[iq2];
	  this_Thad=this_Whad+v_tightjet[ib2];


	  //---Setting tree inputs
	  met_pt=PuppiMET.Pt();
	  met_phi=PuppiMET.Phi();

	  lep_pt=l1.Pt();
	  lep_eta=l1.Eta();
	  lep_phi=l1.Phi();
	  
	  blep_pt=v_tightjet[ib1].Pt();
	  blep_eta=v_tightjet[ib1].Eta();
	  blep_phi=v_tightjet[ib1].Phi();
	  blep_E=v_tightjet[ib1].E();

	  bhad_pt=v_tightjet[ib2].Pt();
	  bhad_eta=v_tightjet[ib2].Eta();
	  bhad_phi=v_tightjet[ib2].Phi();
	  bhad_E=v_tightjet[ib2].E();

	  q1jet_pt=v_tightjet[iq1].Pt();
	  q1jet_eta=v_tightjet[iq1].Eta();
	  q1jet_phi=v_tightjet[iq1].Phi();
	  q1jet_E=v_tightjet[iq1].E();

	  q2jet_pt=v_tightjet[iq2].Pt();
	  q2jet_eta=v_tightjet[iq2].Eta();
	  q2jet_phi=v_tightjet[iq2].Phi();
	  q2jet_E=v_tightjet[iq2].E();

	  WhadCand_mass=this_Whad.M();
	  ThadCand_mass=this_Thad.M();

	  TLorentzVector vt_Wlep=GetTransverseVector(l1)+PuppiMET;
	  TLorentzVector vt_Tlep=GetTransverseVector(l1)+PuppiMET+GetTransverseVector(v_tightjet[ib1]);
	  
	  WlepCand_mt=vt_Wlep.M();
	  TlepCand_mt=vt_Tlep.M();

	  bool blep_flavour_match=v_tightjet[ib1].partonFlavour()==bLep_True_PID;
	  bool bhad_flavour_match=v_tightjet[ib2].partonFlavour()==bHad_True_PID;
	  bool whad_flavour_match=false;
	  
	  if(i_LightJet1==iq1 && i_LightJet2==iq2) whad_flavour_match=true;
	  if(i_LightJet2==iq1 && i_LightJet1==iq2) whad_flavour_match=true;
	  
	  bool isSig=blep_flavour_match && bhad_flavour_match && whad_flavour_match;
	  if(isSig){
	    if(doReduction && (event%sig_mod)!=0) continue;
	    jhchoi_newtree->Fill();
	  }
	  else{
	    if(doReduction && (event%bkg_mod)!=0) continue;
	    jhchoi_newtree2->Fill();
	  }


	  
	}//[END of iq2]
      }//[END of iq1]
    }//[END of ib2]

  }//[END of ib1 loop]

}

void TTSemiLepJetAssignment_ProduceTrainingTree::EventLoop(){
  RunReco();
}





void TTSemiLepJetAssignment_ProduceTrainingTree::TruthLoop(){
  //it must be TTLJ samples
  TTSemiLepJetAssignment_ProduceTrainingTree::RunLHEinfo();
  TTSemiLepJetAssignment_ProduceTrainingTree::RunGENinfo();
  

}

void TTSemiLepJetAssignment_ProduceTrainingTree::RunLHEinfo(){
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
void TTSemiLepJetAssignment_ProduceTrainingTree::RunGENinfo(){
  unsigned int gensize=gens.size();
  //status21 is incoming particle.
  //To find W decay daughters 

  idx_bquark_GEN=-1, idx_bbarquark_GEN=-1;
  v_idx_lightquark_GEN.clear();
  
  
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
    }
  }
  //----GEN-LEVEL W_had and T_had
  TLorentzVector vWhad,vThad;
  //---Add outgoing light quarks' momenta to whad,thad
  //for(unsigned int i = 0 ; i < v_idx_lightquark_GEN.size(); i++){
  for(auto& i_light : v_idx_lightquark_GEN){
    vWhad+=gens[i_light];
    vThad+=gens[i_light];
  }
  //---add bquark momentum to Top(had)
  if(bHadCharge_LHE>0){// bHadCharge >0 means bbar
    vThad+=gens[idx_bbarquark_GEN];
  }
  else{
    vThad+=gens[idx_bquark_GEN];
  }

  Whad_q1_pid=gens[v_idx_lightquark_GEN[0]].PID();
  Whad_q2_pid=gens[v_idx_lightquark_GEN[1]].PID();
  FillHist("Whad_quark_pid_GEN/all/"+ProcessName,Whad_q1_pid, weight, 32, -7, 25);
  FillHist("Whad_quark_pid_GEN/all/"+ProcessName,Whad_q2_pid, weight, 32, -7, 25);





  

}
