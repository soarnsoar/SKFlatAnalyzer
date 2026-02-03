#include "TrueBJetAnalyzer_AddRecoSel.h"

TrueBJetAnalyzer_AddRecoSel::TrueBJetAnalyzer_AddRecoSel(){
  //runSys=true;
}

TrueBJetAnalyzer_AddRecoSel::~TrueBJetAnalyzer_AddRecoSel(){
  //==== Destructor of this Analyzer
}

void TrueBJetAnalyzer_AddRecoSel::initializeAnalyzer(){
  cout << "[TrueBJetAnalyzer_AddRecoSel::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  UseSingleLepSel=1;  
  if(MCSample.Contains("WJets") || MCSample.Contains("SingleTop") || MCSample.Contains("TTLJ")){
    JHAnalyzerBase::SetupSingleLeptonChannel();
  }
  else{
    UseSingleLepSel=0;
    JHAnalyzerBase::SetupDiLeptonChannel();
  }

  FlavourMatchOnly=false;
  if(HasFlag("FlavourMatchOnly")){
    FlavourMatchOnly=true;
    cout << "FlavourMatchOnly!!!" << endl;
  }

  
  
  //AddRecoSel=HasFlag("AddRecoSel");
  AddRecoSel=1;
  if(AddRecoSel) cout << "[Add Flag]AddRecoSel!!!" << endl;



  vEta={-2.5, -2.1, -1.8, -1.5, -1.2,-0.9, -0.7, -0.5, -0.3, -0.1, 0, 0.1, 0.3, 0.5 ,0.7, 0.9, 1.2, 1.5, 1.8, 2.1, 2.5};
  nEta=vEta.size()-1;
  nPt=50;
  nTotal=nPt*nEta;
  Ptmax=200.;  

  //charge
  TString v_muonScore="2409.2";
  TString v_electronScore="2409.2";
  TString v_jetScore="2409.2";

  bool apply_dnncut=1;
  LoadChargeScoreTool(v_muonScore,v_electronScore,v_jetScore,apply_dnncut);

}

void TrueBJetAnalyzer_AddRecoSel::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  
}

void TrueBJetAnalyzer_AddRecoSel::RunReco(){
  v_tightlep={};
  v_tightjet=GetTightJet(v_tightlep,30,jetetacut);
  v_bjetidx=GetBJetIdx(v_tightjet);


  //--Now Objects are ready--//
  //
  SetEventWeight();
  //v_idx_bquark_GEN
  //v_idx_bbarquark_GEN
  for(const auto ib:v_idx_bquark_GEN){
    Run(ib);
  }
  for(const auto ibbar:v_idx_bbarquark_GEN){
    Run(ibbar);
  }

}
void TrueBJetAnalyzer_AddRecoSel::Run(int i_bGEN){

  //idx_bquark_GEN
  //idx_bbarquark_GEN
  //int i_bGEN = -1;
  //if(idx_bquark_GEN>-1){ 
  //  i_bGEN=idx_bquark_GEN;
  //}
  //if(idx_bbarquark_GEN>-1){
  //  i_bGEN=idx_bbarquark_GEN;
  //}
  //if(i_bGEN<0) return;

  
  ///-----Let's match them to btagged jets----//
  // conditions => 1. same flavour 2. dRmatch
  int i_b=GetBJet_TightJetIdx_dR_Flavour_Match(i_bGEN);
  if(i_b<0) return;
  
  
  ///Now we have bLep, bHad
  
  double true_bpt=gens[i_bGEN].Pt();

  FillHist_this_bjet(v_tightjet[i_b],"All",i_bGEN);  
  //if(true_bpt>20.) FillHist_this_bjet(v_tightjet[i_b],"All_True_bpt20",i_bGEN);
  
  TString LeptonChannel="";
  //if(IsMu) LeptonChannel+="Mu";
  //if(IsE) LeptonChannel+="E";
  //if(IsTau) LeptonChannel+="Tau";
  if(nTau==0 && nE==0){
    LeptonChannel="NoPromptElectron";
  }
  else if(nTau==0 && nMu==0){
    LeptonChannel="NoPromptMuon";
  }
  else{
    LeptonChannel="MuEMixed";
  }

  FillHist_this_bjet(v_tightjet[i_b],LeptonChannel,i_bGEN);

  TString nGen_b=std::to_string(nb)+"b_evt";
  //nb
  //std::to_string
  FillHist_this_bjet(v_tightjet[i_b],LeptonChannel+"__"+nGen_b,i_bGEN);
  

  //----AddRecoSel---//

  if(UseSingleLepSel){//SingleLeptonChannel
    if(!PassSingleLeptonCut()) return;
    FillHist_this_bjet(v_tightjet[i_b],LeptonChannel+"__AddRecoSel",i_bGEN);

  }
  else if(IsDYSample){
    if(!PassPresel()) return;
    FillHist_this_bjet(v_tightjet[i_b],LeptonChannel+"__AddRecoSel",i_bGEN);
  }
  else{
    if(!PassDiLeptonCut()) return;
    FillHist_this_bjet(v_tightjet[i_b],LeptonChannel+"__AddRecoSel",i_bGEN);
  }


}


//---SingleLepChannel---//

void TrueBJetAnalyzer_AddRecoSel::SetElectron(const Electron& _l1){
  el1=_l1;
}
void TrueBJetAnalyzer_AddRecoSel::SetMuon(const Muon& _l1){
  mu1=_l1;
}


bool TrueBJetAnalyzer_AddRecoSel::CheckIsSingleMuonChannel(){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  vector<Muon> v_muon= GetSingleMuReco(TriggerSafeCut_muon1);
  if( v_muon.size()!=1) return 0;
  SetMuon(v_muon[0]);

  return 1;
}

bool TrueBJetAnalyzer_AddRecoSel::CheckIsSingleElectronChannel(){
  if (!ev.PassTrigger(ElectronTriggerNames)) return 0;
  bool isElectronData = DataStream.Contains("EG")||DataStream.Contains("Electron");
  if ( IsDATA && isElectronData && ev.PassTrigger(MuonTriggerNames)) return 0; // to avoid double count
  
  vector<Electron> v_electron=GetSingleElReco(TriggerSafeCut_electron1);
  if( v_electron.size()!=1) return 0;
  SetElectron(v_electron[0]);
  return 1;
}


bool TrueBJetAnalyzer_AddRecoSel::PassSingleLeptonCut(){
  bool IsSingleMuonChannel=false;
  bool IsSingleElectronChannel=false;
  
  
  IsSingleMuonChannel=CheckIsSingleMuonChannel();
  if(!IsSingleMuonChannel) IsSingleElectronChannel=CheckIsSingleElectronChannel();
  

  TString LepCh="";
  if(IsSingleMuonChannel){
    vtW=GetTransverseVector(mu1)+CurrentMET;
    LepCh="Muon";
  }
  else if(IsSingleElectronChannel){
    vtW=GetTransverseVector(el1)+CurrentMET;
    LepCh="Electron";
  }

  else{
    return 0;
  }
  if(CurrentMET.Pt() < 30.) return 0;
  if(vtW.M() < 60. ) return 0;

  return 1;


}

//---
void TrueBJetAnalyzer_AddRecoSel::SetMuon(const Muon& _l1, const Muon& _l2){
  mu1=_l1;
  mu2=_l2;

}
bool TrueBJetAnalyzer_AddRecoSel::CheckIsDiMuonChannel(double min_mll,double max_mll){
  if (!ev.PassTrigger(MuonTriggerNames)) return 0;
  //vector<int> v_muonidx=GetIdxDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  vector<Muon> v_muon=GetDiMuReco(TriggerSafeCut_muon1, TriggerSafeCut_muon2);
  if( v_muon.size()<2) return 0;
  double mll=(v_muon[0]+v_muon[1]).M();
  if (mll < min_mll) return 0;
  if (mll > max_mll) return 0;

  SetMuon(v_muon[0],v_muon[1]);

  return 1;
}


void TrueBJetAnalyzer_AddRecoSel::SetElectron(const Electron& _l1, const Electron& _l2){
  el1=_l1;
  el2=_l2;

}

bool TrueBJetAnalyzer_AddRecoSel::CheckIsDiElectronChannel(double min_mll,double max_mll){
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


bool TrueBJetAnalyzer_AddRecoSel::PassDiLeptonCut(){
  bool IsDiMuonChannel=false;
  bool IsDiElectronChannel=false;
  double min_mll = 0;
  double max_mll = 999999999999999999999;

  IsDiMuonChannel=CheckIsDiMuonChannel(min_mll,max_mll);
  if(!IsDiMuonChannel) IsDiElectronChannel=CheckIsDiElectronChannel(min_mll,max_mll);

  if(!IsDiMuonChannel && !IsDiElectronChannel)return 0;

  return 1;

}


bool TrueBJetAnalyzer_AddRecoSel::PassPresel(){
  bool IsDiMuonChannel=false;
  bool IsDiElectronChannel=false;
  double min_mll = 60;
  double max_mll = 120;

  IsDiMuonChannel=CheckIsDiMuonChannel(min_mll,max_mll);
  if(!IsDiMuonChannel) IsDiElectronChannel=CheckIsDiElectronChannel(min_mll,max_mll);

  if(!IsDiMuonChannel && !IsDiElectronChannel)return 0;

  TLorentzVector vZ;
  if(IsDiMuonChannel){
    vZ=mu1+mu2;
  }
  else if(IsDiElectronChannel){
    vZ=el1+el2;
  }
  else{
    return 0;
  }

  if(v_bjetidx.size()!=1) return 0;
  
  int ib=v_bjetidx[0];
  double dphi_z_b= fabs(v_tightjet[ib].DeltaPhi(vZ));
  double ptzb=(v_tightjet[ib]+vZ).Pt();
  if(CurrentMET.Pt() > 75.) return 0;
  if(dphi_z_b < 1.6) return 0;
  if(vZ.Pt()<15.) return 0;
  if(ptzb>60.) return 0;


  return 1;

}


int TrueBJetAnalyzer_AddRecoSel::FindBinNumber(double this_eta){
  //vEta
  auto it = std::lower_bound(vEta.begin(), vEta.end(), this_eta);
  return std::distance(vEta.begin(), it)-1; // if eta==-2.4, return 1-1 = 0, when
  //vEta={-2.5, -2.1, -1.8, -1.5, -1.2,-0.9, -0.7, -0.5, -0.3, -0.1, 0, 0.1, 0.3, 0.5 ,0.7, 0.9, 1.2, 1.5, 1.8, 2.1, 2.5};
}

void TrueBJetAnalyzer_AddRecoSel::FillHist_this_bjet(Jet &_bjet,TString bjetname, int i_GEN){

  FillHist(bjetname+"/bjet_pt",_bjet.Pt(), weight, 100,0,200);
  FillHist(bjetname+"/true_bjet_pt",gens[i_GEN].Pt(), weight, 100,0,200);
  FillHist(bjetname+"/bjet_eta",_bjet.Eta(), weight, 50,-3,3);
  //FillHist(bjetname+"/bjet_MuonEnergyFraction",_bjet.GetMuonEnergyFraction(), weight, 50,0,1);
  //FillHist(bjetname+"/bjet_logMuonEnergyFraction",log(_bjet.GetMuonEnergyFraction()), weight, 50,-2,0);
  //FillHist(bjetname+"/bjet_ChargedMultiplicity",_bjet.ChargedMultiplicity(), weight, 30,0,30);
  //FillHist(bjetname+"/bjet_NeutralMultiplicity",_bjet.NeutralMultiplicity(), weight, 30,0,30);

  //int ieta=FindBinNumber(_bjet.Eta());
  //double orig_pt= _bjet.Pt() < Ptmax ? _bjet.Pt() : Ptmax;
  //double this_pt= orig_pt + ieta*Ptmax;

  //FillHist(bjetname+"/bjet_pt__ieta",this_pt, weight, nTotal,0,Ptmax*nEta);


  //---SLTMuon
  pair<int,int> nSLTMuon__idxSLTMuon=GetN_SLTMuon(_bjet,AllMuons);
  int nSLTMuon=nSLTMuon__idxSLTMuon.first;
  int idxSLTMuon=nSLTMuon__idxSLTMuon.second;  
  FillHist(bjetname+"/bjet_nSLTMuon",nSLTMuon, weight, 10,0,10);

  if(nSLTMuon>0){
    FillHist(bjetname+"_Has_SLTMuon/bjet_pt",_bjet.Pt(), weight, 100,0,200);
    FillHist(bjetname+"_Has_SLTMuon/true_bjet_pt",gens[i_GEN].Pt(), weight, 100,0,200);
    FillHist(bjetname+"_Has_SLTMuon/bjet_eta",_bjet.Eta(), weight, 50,-3,3);
    //FillHist(bjetname+"_Has_SLTMuon/bjet_pt__ieta",this_pt, weight, nTotal,0,200*nEta);
    //FillHist(bjetname+"_Has_SLTMuon/bjet_MuonEnergyFraction",_bjet.GetMuonEnergyFraction(), weight, 50,0,1);
    //FillHist(bjetname+"_Has_SLTMuon/bjet_logMuonEnergyFraction",log(_bjet.GetMuonEnergyFraction()), weight, 50,-2,0);
    //FillHist(bjetname+"_Has_SLTMuon/bjet_ChargedMultiplicity",_bjet.ChargedMultiplicity(), weight, 30,0,30);
    //FillHist(bjetname+"_Has_SLTMuon/bjet_NeutralMultiplicity",_bjet.NeutralMultiplicity(), weight, 30,0,30);
    
    if(nSLTMuon==1){
      FillHist(bjetname+"_Has_1SLTMuon/bjet_pt",_bjet.Pt(), weight, 100,0,200);
      FillHist(bjetname+"_Has_1SLTMuon/true_bjet_pt",gens[i_GEN].Pt(), weight, 100,0,200);
      FillHist(bjetname+"_Has_1SLTMuon/bjet_eta",_bjet.Eta(), weight, 50,-3,3);
      //FillHist(bjetname+"_Has_1SLTMuon/bjet_pt__ieta",this_pt, weight, nTotal,0,200*nEta);
      FillHist(bjetname+"_Has_1SLTMuon/SLTMuon_pt",AllMuons[idxSLTMuon].Pt(), weight, 100,0,200); 
      //{im_max,bmuon_score_max,bmuon_charge_max,im_min,bmuon_score_min,bmuon_charge_min
      tuple<int,double,double,int,double,double> ret=GetBJetMuonScore_v2409_2(_bjet, AllMuons);
      int im_max=std::get<0>(ret);
      double bmuon_score_max=std::get<1>(ret);
      double bmuon_charge_max=std::get<2>(ret);
      int im_min=std::get<3>(ret);
      double bmuon_score_min=std::get<4>(ret);
      double bmuon_charge_min=std::get<5>(ret);
      
      if(bmuon_score_max > mChargeTool->mincut){
        FillHist(bjetname+"_Has_1SLTMuonHigh/bjet_pt",_bjet.Pt(), weight, 100,0,200);
        FillHist(bjetname+"_Has_1SLTMuonHigh/true_bjet_pt",gens[i_GEN].Pt(), weight, 100,0,200);
        FillHist(bjetname+"_Has_1SLTMuonHigh/bjet_eta",_bjet.Eta(), weight, 50,-3,3);
        FillHist(bjetname+"_Has_1SLTMuonHigh/SLTMuon_pt",AllMuons[im_max].Pt(), weight, 100,0,200);

      }
    }

  }



  //---SLTElectron
  int nSLTElectron=GetN_SLTElectron(_bjet,AllElectrons);
  FillHist(bjetname+"/bjet_nSLTElectron",nSLTElectron, weight, 10,0,10);
  if(nSLTElectron>0){
    FillHist(bjetname+"_Has_SLTElectron/bjet_pt",_bjet.Pt(), weight, 100,0,200);
    FillHist(bjetname+"_Has_SLTElectron/bjet_eta",_bjet.Eta(), weight, 50,-3,3);
    //FillHist(bjetname+"_Has_SLTElectron/bjet_pt__ieta",this_pt, weight, nTotal,0,200*nEta);
  }


}


//AllMuons
pair<int,int> TrueBJetAnalyzer_AddRecoSel::GetN_SLTMuon(Jet &_bjet,vector<Muon> &_muoncoll){
  int im=-1;
  int im_selected=-1;
  int Nmuon=0;
  for(auto& muon : _muoncoll){
    im+=1;
    if(muon.Pt() < 5.) continue;
    if(muon.DeltaR(_bjet) > 0.4) continue;
    if(muon.RelIso() > 10.) continue;
    if(muon.Chi2()>10) continue;
    if(muon.TrackerLayers()<1) continue;
    if(muon.MatchedStations() <1) continue;
    im_selected=im;
    Nmuon+=1;
  }

  return {Nmuon,im_selected};
}



//AllElectrons
int TrueBJetAnalyzer_AddRecoSel::GetN_SLTElectron(Jet &_bjet,vector<Electron> &_electroncoll){
  int ie=-1;
  int Nelectron=0;
  for(auto& electron : _electroncoll){
    ie+=1;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(electron.Pt() < 5.) continue;
    if(electron.DeltaR(_bjet) > 0.4) continue;
    if(!electron.IsGsfCtfScPixChargeConsistent()) continue;
    if(!electron.PassConversionVeto()) continue;
    if(electron.RelIso() > 10.) continue;
    if(electron.NMissingHits() != 0) continue;
    Nelectron+=1;
  }
  return Nelectron;
}

int TrueBJetAnalyzer_AddRecoSel::GetBJet_TightJetIdx_dR_Flavour_Match(int i_GEN){
  int truepid=gens[i_GEN].PID();
  if(FlavourMatchOnly){
    for(auto &bidx : v_bjetidx){
      //v_tightjet[bidx];
      if (truepid != v_tightjet[bidx].partonFlavour()) continue; //flavour match
      return bidx;
    }  
  }
  else{
    int ret=-1; double mindpt=9999999999.;
    double true_pt=gens[i_GEN].Pt();
    for(auto &bidx : v_bjetidx){
      //v_tightjet[bidx];
      if ( gens[i_GEN].DeltaR(v_tightjet[bidx]) > 0.4) continue; //dR cut
      if (truepid != v_tightjet[bidx].partonFlavour()) continue; //flavour match
      //return bidx;
      double this_dpt= fabs(v_tightjet[bidx].Pt()-true_pt);
      if(this_dpt < mindpt){
	mindpt=this_dpt;
	ret=bidx;
      } 
      
      
    } //[end of forloop]
    if(ret>-1) return ret;
    
 
  }
  return -1;
}




bool TrueBJetAnalyzer_AddRecoSel::HasMatchedRecoJet(int genidx,double dRcut){
  TLorentzVector this_genptl=gens[genidx];
  for(auto &jet : v_tightjet){
    if(this_genptl.DeltaR(jet) < dRcut) return 1;
  }
  return 0;
}


bool TrueBJetAnalyzer_AddRecoSel::HasFlavourMatchedRecoJet(int genidx){
  //TLorentzVector this_genptl=gens[genidx];
  int true_pid=gens[genidx].PID();
  for(auto &jet : v_tightjet){
    if(jet.partonFlavour() == true_pid) return 1;
  }
  return 0;
}




void TrueBJetAnalyzer_AddRecoSel::EventLoop(){
  
  
  RunReco();

}





void TrueBJetAnalyzer_AddRecoSel::TruthLoop(){
  //it must be TTLJ samples
  
  if(IsDATA) return;
  TrueBJetAnalyzer_AddRecoSel::RunGENinfo();
  

}

void TrueBJetAnalyzer_AddRecoSel::RunGENinfo(){


  IsE=0; IsMu=0;IsTau=0;
  nE=0; nMu=0; nTau=0;
  nb=0;
  v_idx_bquark_GEN={}; 
  v_idx_bbarquark_GEN={};

  //if(nb+nbbar!=1) return;
  unsigned int gensize=gens.size();
  //cout << "-----start----" << endl;
  //cout << "i" << setw(10) << "mother" << setw(10) << "status" << setw(10) << "pid"  <<endl;
  for(unsigned int i = 0 ; i < gensize ; i++){
    int pid=gens[i].PID();
    int status=gens[i].Status();
    int mother=gens[i].MotherIndex();
    int isHardProcess=gens[i].isHardProcess();


    /// Outgoing HardProcess parton
    //if(mother < 0) continue;
    //if(isHardProcess)      cout << i << setw(10) << mother << setw(10) << status << setw(10) << pid  <<endl;
    if (isHardProcess && (status!=21)){//status21===incoming quark
      if(abs(pid)==11){
	IsE=true;
	nE+=1;
      }
      if(abs(pid)==13){
	IsMu=true;
	nMu+=1;
      }
      if(abs(pid)==15){
	IsTau=true;
	nTau+=1;
      }
      if(pid==5){
        v_idx_bquark_GEN.push_back(i);
	FillHist("GEN/true_bjet_pt",gens[i].Pt(), weight, 100,0,200);
	nb+=1;
	//cout << "b!!" << endl; 
      }
      else if(pid==-5){
        v_idx_bbarquark_GEN.push_back(i);
	FillHist("GEN/true_bjet_pt",gens[i].Pt(), weight, 100,0,200);
	nb+=1;
	//cout << "bbar!!" << endl; 
      }
    }


  }




  

}


