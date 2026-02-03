#include "bChargeID_TrainTree.h"
#include <map>
bChargeID_TrainTree::bChargeID_TrainTree(){
  //runSys=true;

  //JHAnalyzerBase::SetupDiLeptonChannel();  
}

bChargeID_TrainTree::~bChargeID_TrainTree(){
  //==== Destructor of this Analyzer
}

void bChargeID_TrainTree::initializeAnalyzer(){
  cout << "[bChargeID_TrainTree::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  JHAnalyzerBase::SetupDiLeptonChannel();
  InitOutputTree();
  IsDYSample=false;
  if(MCSample.Contains("DYJets")||MCSample.Contains("ZToEE")||MCSample.Contains("ZToMuMu")||MCSample.Contains(TRegexp("DY[0-9]Jets"))) IsDYSample=true;
  cout << "[IsDYSample]=" << IsDYSample << endl;

  is_cut_v2405_1=false;
  if(HasFlag("cut_v2405.1")){
    is_cut_v2405_1=true;
  }


}
void bChargeID_TrainTree::InitOutputTree(){
  jhchoi_newtree=new TTree("sig","sig");
  jhchoi_newtree2=new TTree("bkg","bkg");
  SetBranches(jhchoi_newtree);
  SetBranches(jhchoi_newtree2);
}
void bChargeID_TrainTree::SetBranches(TTree *this_Tree){
  this_Tree->Branch("bmuon_P_jetrest",&bmuon.P_jetrest);
  this_Tree->Branch("bmuon_ptwrtbjet",&bmuon.ptwrtjet);
  this_Tree->Branch("bmuon_dR_l_j",&bmuon.dR_l_j);
  this_Tree->Branch("bmuon_nsip3d",&bmuon.nsip3d);
  this_Tree->Branch("bmuon_reltrkiso",&bmuon.reltrkiso);
  this_Tree->Branch("bmuon_reliso",&bmuon.reliso);
  this_Tree->Branch("bmuon_charge",&bmuon.charge);
  this_Tree->Branch("bmuon_palongjet",&bmuon.palongjet);
  this_Tree->Branch("bmuon_palongjetratio",&bmuon.palongjetratio);
  this_Tree->Branch("bmuon_pt",&bmuon.pt);
  this_Tree->Branch("bmuon_aeta",&bmuon.aeta);
  this_Tree->Branch("bmuon_normchi2",&bmuon.normchi2);
  this_Tree->Branch("bmuon_ntracklayers",&bmuon.ntracklayers);
  this_Tree->Branch("bmuon_ntrackhits",&bmuon.ntrackhits);
  this_Tree->Branch("bmuon_nvalidmuonhits",&bmuon.nvalidmuonhits);
  this_Tree->Branch("bmuon_nmatchedstations",&bmuon.nmatchedstations);



  this_Tree->Branch("belectron_P_jetrest",&belectron.P_jetrest);
  this_Tree->Branch("belectron_ptwrtbjet",&belectron.ptwrtjet);
  this_Tree->Branch("belectron_dR_l_j",&belectron.dR_l_j);
  this_Tree->Branch("belectron_nsip3d",&belectron.nsip3d);
  this_Tree->Branch("belectron_reltrkiso",&belectron.reltrkiso);
  this_Tree->Branch("belectron_reliso",&belectron.reliso);
  this_Tree->Branch("belectron_charge",&belectron.charge);
  this_Tree->Branch("belectron_relecalPFClusterIso",&belectron.relecalPFClusterIso);
  this_Tree->Branch("belectron_IsGsfCtfScPixChargeConsistent",&belectron.IsGsfCtfScPixChargeConsistent);
  this_Tree->Branch("belectron_palongjet",&belectron.palongjet);
  this_Tree->Branch("belectron_palongjetratio",&belectron.palongjetratio);
  this_Tree->Branch("belectron_pt",&belectron.pt);
  this_Tree->Branch("belectron_aeta",&belectron.aeta);
  this_Tree->Branch("belectron_full5x5sigmaietaieta",&belectron.full5x5sigmaietaieta);
  this_Tree->Branch("belectron_detaseed",&belectron.detaseed);
  this_Tree->Branch("belectron_HoverE",&belectron.HoverE);
  this_Tree->Branch("belectron_InvEminusInvP",&belectron.InvEminusInvP);
  this_Tree->Branch("belectron_nmissinghits",&belectron.nmissinghits);


  this_Tree->Branch("bjet_pt",&bjet.pt);
  this_Tree->Branch("bjet_aeta",&bjet.aeta);
  this_Tree->Branch("bjet_ChargedHadronEnergyFraction",&bjet.ChargedHadronEnergyFraction);
  this_Tree->Branch("bjet_NeutralHadronEnergyFraction",&bjet.NeutralHadronEnergyFraction);
  this_Tree->Branch("bjet_NeutralEmEnergyFraction",&bjet.NeutralEmEnergyFraction);
  this_Tree->Branch("bjet_ChargedEmEnergyFraction",&bjet.ChargedEmEnergyFraction);
  this_Tree->Branch("bjet_MuonEnergyFraction",&bjet.MuonEnergyFraction);
  this_Tree->Branch("bjet_charge",&bjet.charge);
  this_Tree->Branch("bjet_partonFlavour",&bjet.partonFlavour);
  this_Tree->Branch("bjet_ChargedMultiplicity",&bjet.ChargedMultiplicity);
  this_Tree->Branch("bjet_NeutralMultiplicity",&bjet.NeutralMultiplicity);

  this_Tree->Branch("lhe_b_pdgid",&lhe_b_pdgid);
  this_Tree->Branch("Has_bMuon",&Has_bMuon);
  this_Tree->Branch("Has_bElectron",&Has_bElectron);
  this_Tree->Branch("weight",&weight);
}

void bChargeID_TrainTree::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;
  
}

bool bChargeID_TrainTree::CheckIsDiMuonChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  vector<Muon> v_muon=GetDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  if( v_muon.size()<2) return 0;
  double mll=(v_muon[0]+v_muon[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;

  SetMuon(v_muon[0],v_muon[1]);

  return 1;
}  

void bChargeID_TrainTree::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;
  
}


bool bChargeID_TrainTree::CheckIsDiElectronChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  
  vector<Electron> v_electron=GetDiElReco(TriggerSafeCut_electron1, TriggerSafeCut_electron2);
  if( v_electron.size()<2) return 0;
  
  double mll=(v_electron[0]+v_electron[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;
  SetElectron(v_electron[0],v_electron[1]);
  return 1;
}  



void bChargeID_TrainTree::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  //----ZpT weight For DY
  //----DY WEAK NLO
  //---z0 weight
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf*jetpuidsf;

  if(IsDiMuonChannel){
    weight*=w_MuonID[0][0]*w_MuonRECO[0][0]*w_MuonTrk[0][0]*w_MuonTrigger[0][0];
  }
  else if(IsDiElectronChannel){
    weight*=w_ElectronID[0][0]*w_ElectronRECO[0][0]*w_ElectronTrigger[0][0];
  }


}

void bChargeID_TrainTree::RunBasicZregion(){

  IsDiMuonChannel=false;
  IsDiElectronChannel=false;
  double min_mll = 60.;
  double max_mll = 120.;

  IsDiMuonChannel=CheckIsDiMuonChannel(min_mll,max_mll);
  if(!IsDiMuonChannel) IsDiElectronChannel=CheckIsDiElectronChannel(min_mll,max_mll);

  
  //--Now Objects are ready--//


  LepCh="";
  if(IsDiMuonChannel){
    //vZ=(*mu1)+(*mu2);
    vZ=mu1+mu2;
    LepCh="mm";
    l1=mu1;
    l2=mu2;
  }
  else if(IsDiElectronChannel){
    //vZ=GetDiElectronVector();
    vZ=el1+el2;
    LepCh="ee";
    //l1=AllElectrons[el1idx];
    //l2=AllElectrons[el2idx];
    l1=el1;
    l2=el2;
  }  

  //else{
  //  return;
  //}
  //----Jet---//
  //v_tightlep={l1,l2};
  v_tightlep={};
  v_tightjet=GetTightJet(v_tightlep,30,jetetacut,"tight");
  v_bjet=GetBJet(v_tightjet);

  njet=v_tightjet.size();
  nbjet=v_bjet.size();

  SetEventWeight();  
  //---Now event is ready
  AnalyzerCore::FillHist("Mll_1btag/event/"+ProcessName,1,1,2,0,2);
  if(nbjet!=1) return;
  int bjet_parton_pdgid=v_bjet[0].partonFlavour();
  lhe_b_pdgid=lhes[idx_outgoing_b].ID();
  if(bjet_parton_pdgid!=lhe_b_pdgid) return; 
  AnalyzerCore::FillHist("Mll_1btag_matching_flavour/event/"+ProcessName,1,1,2,0,2);

  ///----candiates of variables----//
  //pT of jet
  //|eta| of jet

  //Energy Fraction variables of jet
  //pt wrt jet 
  //|P_3Dvector| at jet rest frame
  //dR(l,bjet)
  //Isolation of leptons
  //lep_nsip3d
  SetTreeValue_bJet(v_bjet[0]);
  Has_bMuon=SetTreeValue_bMuon(v_bjet[0]);
  Has_bElectron=SetTreeValue_bElectron(v_bjet[0]);
  jhchoi_newtree->Fill();
  jhchoi_newtree2->Fill();
}
void bChargeID_TrainTree::SetTreeValue_bJet(Jet &jet){
  bjet=Get_bjetvar(jet);
  //bjet.pt=jet.Pt();
  //bjet.aeta=jet.Eta();
  //bjet.ChargedHadronEnergyFraction=jet.GetChargedHadronEnergyFraction();
  //bjet.NeutralHadronEnergyFraction=jet.GetNeutralHadronEnergyFraction();
  //bjet.NeutralEmEnergyFraction=jet.GetNeutralEmEnergyFraction();
  //bjet.ChargedEmEnergyFraction=jet.GetChargedEmEnergyFraction();
  //bjet.MuonEnergyFraction=jet.GetMuonEnergyFraction();
  //bjet.charge=jet.Charge();
  //bjet.partonFlavour=jet.partonFlavour();
}
bool bChargeID_TrainTree::SetTreeValue_bMuon(Jet &jet){
  Init_bMuonVars();
  unsigned int muonsize=AllMuons.size();
  unsigned int nbmuon=0;
  for(unsigned int i = 0 ; i < muonsize ; i++){
    if((int)i==muon1_idx) continue;
    if((int)i==muon2_idx) continue;
    if(AllMuons[i].Pt() < 5.) continue;
    if(!AllMuons[i].PassID("POGLoose")) continue;    
    double dR=jet.DeltaR(AllMuons[i]);
    if(dR < 0.4){      
      nbmuon+=1;
      bmuon=Get_bmuonvar(AllMuons[i],jet);
      //bmuon.P_jetrest=min(GetP_JetRestFrame(AllMuons[i],jet),10.);
      //bmuon.ptwrtjet=min(GetPt_wrt_Jet(AllElectrons[i],jet),10.);
      //bmuon.dR_l_j=dR;
      //bmuon.nsip3d=min(fabs(AllMuons[i].IP3D()/AllMuons[i].IP3Derr()),15.);
      //bmuon.reltrkiso=min(AllMuons[i].TrkIso()/AllMuons[i].Pt(),15.);
      //bmuon.reliso=min(AllMuons[i].RelIso(),15.);
      //bmuon.charge=AllMuons[i].Charge();
    }
    if(nbmuon>1) return false;
    
  }
  if(nbmuon==1) return true;
  return false;
}
void bChargeID_TrainTree::Init_bMuonVars(){
  bmuon.P_jetrest=0;
  bmuon.ptwrtjet=0;
  bmuon.dR_l_j=0;
  bmuon.nsip3d=0;
  bmuon.reltrkiso=0;
  bmuon.reliso=0;
  bmuon.charge=0;
}

bool bChargeID_TrainTree::SetTreeValue_bElectron(Jet &jet){
  Init_bElectronVars();
  unsigned int electronsize=AllElectrons.size();
  //int belectronidx=-1;
  unsigned int nbelectron=0;
  for(unsigned int i = 0 ; i < electronsize ; i++){
    if((int)i==electron1_idx) continue;
    if((int)i==electron2_idx) continue;
    if(AllElectrons[i].Pt() < 5) continue;
    if(!AllElectrons[i].IsGsfCtfScPixChargeConsistent()) continue;
    if(!AllElectrons[i].PassID("passVetoID")) continue;
    double dR=jet.DeltaR(AllElectrons[i]);
    if(dR < 0.4){      
      nbelectron+=1;
      belectron=Get_belectronvar(AllElectrons[i],jet);
      //belectron.P_jetrest=min(GetP_JetRestFrame(AllElectrons[i],jet),10.);
      //belectron.ptwrtjet=min(GetPt_wrt_Jet(AllElectrons[i],jet),10.);
      //belectron.dR_l_j=dR;
      //belectron.nsip3d=min(fabs(AllElectrons[i].IP3D()/AllElectrons[i].IP3Derr()),15.);
      //belectron.reltrkiso=min(AllElectrons[i].TrkIso()/AllElectrons[i].Pt(),15.);
      //belectron.reliso=min(AllElectrons[i].RelIso(),15.);
      //belectron.charge=AllElectrons[i].Charge();
      //belectron.IsGsfCtfScPixChargeConsistent=AllElectrons[i].IsGsfCtfScPixChargeConsistent();
    }
    if(nbelectron>1) return false;
    
  }
  if(nbelectron==1) return true;
  return false;
}

void bChargeID_TrainTree::Init_bElectronVars(){
  belectron.P_jetrest=0;
  belectron.ptwrtjet=0;
  belectron.dR_l_j=0;
  belectron.nsip3d=0;
  belectron.reltrkiso=0;
  belectron.reliso=0;
  belectron.charge=0;
  belectron.relecalPFClusterIso=0;
  belectron.IsGsfCtfScPixChargeConsistent=0;
  
}






void bChargeID_TrainTree::FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max){
  JHAnalyzerBase::FillHist(histname,value,weight,n_bin,x_min,x_max);
}
void bChargeID_TrainTree::TruthLoop(){
  IsZbLHE=JHAnalyzerBase::TagZbLHE();  
  AnalyzerCore::FillHist("All/IsZbLHE/"+ProcessName,IsZbLHE,1,2,0,2);
}
void bChargeID_TrainTree::EventLoop(){
  if(!IsZbLHE) return;
  RunBasicZregion();
}  
  




