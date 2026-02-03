#include "TTSemiLepTrueBJetAnalyzer.h"

TTSemiLepTrueBJetAnalyzer::TTSemiLepTrueBJetAnalyzer(){
  //runSys=true;
}

TTSemiLepTrueBJetAnalyzer::~TTSemiLepTrueBJetAnalyzer(){
  //==== Destructor of this Analyzer
}

void TTSemiLepTrueBJetAnalyzer::initializeAnalyzer(){
  cout << "[TTSemiLepTrueBJetAnalyzer::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  
  FlavourMatchOnly=false;
  if(HasFlag("FlavourMatchOnly")){
    FlavourMatchOnly=true;
    cout << "FlavourMatchOnly!!!" << endl;
  }

  //---iEta
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

void TTSemiLepTrueBJetAnalyzer::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  
}

void TTSemiLepTrueBJetAnalyzer::RunReco(){
  v_tightlep={};
  v_tightjet=GetTightJet(v_tightlep,30,jetetacut);
  v_bjetidx=GetBJetIdx(v_tightjet);


  //--Now Objects are ready--//
  SetEventWeight();



  Run();

}
void TTSemiLepTrueBJetAnalyzer::Run(){
  int i_bHad_GEN = -1;
  int i_bLep_GEN = -1;

  if(bLepCharge_LHE > 0){
    i_bLep_GEN=idx_bbarquark_GEN;
  }
  else if(bLepCharge_LHE < 0){
    i_bLep_GEN=idx_bquark_GEN;
  }

  if(bHadCharge_LHE > 0){
    i_bHad_GEN=idx_bbarquark_GEN;
  }
  else if(bHadCharge_LHE < 0){
    i_bHad_GEN=idx_bquark_GEN;
  }

  if(i_bHad_GEN<0) return;
  if(i_bLep_GEN<0) return;

  
  ///-----Let's match them to btagged jets----//
  // conditions => 1. same flavour 2. dRmatch
  int i_bLep=-1;
  int i_bHad=-1;

  i_bLep=GetBJet_TightJetIdx_dR_Flavour_Match(i_bLep_GEN);
  i_bHad=GetBJet_TightJetIdx_dR_Flavour_Match(i_bHad_GEN);
  


  if(i_bLep<0) return;
  if(i_bHad<0) return;
  

  ///Now we have bLep, bHad
  double true_bLeppt=gens[i_bLep_GEN].Pt();
  double true_bHadpt=gens[i_bHad_GEN].Pt();
  
  FillHist_this_bjet(v_tightjet[i_bLep],"bLep",i_bLep_GEN);
  FillHist_this_bjet(v_tightjet[i_bHad],"bHad",i_bHad_GEN);

  if(IsMuonChannel_LHE){
    FillHist_this_bjet(v_tightjet[i_bLep],"TTMJ__bLep",i_bLep_GEN);
    FillHist_this_bjet(v_tightjet[i_bHad],"TTMJ__bHad",i_bHad_GEN);

  }
  if(IsElectronChannel_LHE){
    FillHist_this_bjet(v_tightjet[i_bLep],"TTEJ__bLep",i_bLep_GEN);
    FillHist_this_bjet(v_tightjet[i_bHad],"TTEJ__bHad",i_bHad_GEN);

  }
}

int TTSemiLepTrueBJetAnalyzer::FindBinNumber(double this_eta){
  //vEta
  auto it = std::lower_bound(vEta.begin(), vEta.end(), this_eta);
  return std::distance(vEta.begin(), it)-1; // if eta==-2.4, return 1-1 = 0, when
  //vEta={-2.5, -2.1, -1.8, -1.5, -1.2,-0.9, -0.7, -0.5, -0.3, -0.1, 0, 0.1, 0.3, 0.5 ,0.7, 0.9, 1.2, 1.5, 1.8, 2.1, 2.5};
}

void TTSemiLepTrueBJetAnalyzer::FillHist_this_bjet(Jet &_bjet,TString bjetname, int i_GEN){
  //this_jet.GetMuonEnergyFraction
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
pair<int,int> TTSemiLepTrueBJetAnalyzer::GetN_SLTMuon(Jet &_bjet,vector<Muon> &_muoncoll){
  int im_selected=-1;
  int im=-1;
  int Nmuon=0;
  for(auto& muon : _muoncoll){
    im+=1;
    if(muon.Pt() < 5.) continue;
    if(muon.DeltaR(_bjet) > 0.4) continue;
    if(muon.RelIso() > 10.) continue;
    if(muon.Chi2()>10) continue;
    if(muon.TrackerLayers()<1) continue;
    if(muon.MatchedStations() <1) continue;
    Nmuon+=1;
    im_selected=im;
  }
  
  return {Nmuon,im_selected};
}


//AllElectrons
int TTSemiLepTrueBJetAnalyzer::GetN_SLTElectron(Jet &_bjet,vector<Electron> &_electroncoll){
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

int TTSemiLepTrueBJetAnalyzer::GetBJet_TightJetIdx_dR_Flavour_Match(int i_GEN){
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
    if(ret>-1) return ret;//if at least one jet is found
  }

  return -1;
}




bool TTSemiLepTrueBJetAnalyzer::HasMatchedRecoJet(int genidx,double dRcut){
  TLorentzVector this_genptl=gens[genidx];
  for(auto &jet : v_tightjet){
    if(this_genptl.DeltaR(jet) < dRcut) return 1;
  }
  return 0;
}


bool TTSemiLepTrueBJetAnalyzer::HasFlavourMatchedRecoJet(int genidx){
  //TLorentzVector this_genptl=gens[genidx];
  int true_pid=gens[genidx].PID();
  for(auto &jet : v_tightjet){
    if(jet.partonFlavour() == true_pid) return 1;
  }
  return 0;
}




void TTSemiLepTrueBJetAnalyzer::EventLoop(){
  RunReco();

}





void TTSemiLepTrueBJetAnalyzer::TruthLoop(){
  //it must be TTLJ samples
  if (IsTTLJSample){
    TTSemiLepTrueBJetAnalyzer::RunLHEinfo();
    TTSemiLepTrueBJetAnalyzer::RunGENinfo();
  }

}

void TTSemiLepTrueBJetAnalyzer::RunLHEinfo(){
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
void TTSemiLepTrueBJetAnalyzer::RunGENinfo(){
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
  FillHist("GEN_bHad/true_bjet_pt",gens[bHad_True_genidx].Pt(), weight, 100,0,200);
  FillHist("GEN_bLep/true_bjet_pt",gens[bLep_True_genidx].Pt(), weight, 100,0,200);
  

}


