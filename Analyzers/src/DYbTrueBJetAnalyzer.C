#include "DYbTrueBJetAnalyzer.h"

DYbTrueBJetAnalyzer::DYbTrueBJetAnalyzer(){
  //runSys=true;
}

DYbTrueBJetAnalyzer::~DYbTrueBJetAnalyzer(){
  //==== Destructor of this Analyzer
}

void DYbTrueBJetAnalyzer::initializeAnalyzer(){
  cout << "[DYbTrueBJetAnalyzer::initializeAnalyzer]" << endl;
  JHAnalyzerBase::initializeAnalyzer();
  
  FlavourMatchOnly=false;
  if(HasFlag("FlavourMatchOnly")){
    FlavourMatchOnly=true;
    cout << "FlavourMatchOnly!!!" << endl;
  }
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

void DYbTrueBJetAnalyzer::SetEventWeight(){
  weight=1;
  if(IsDATA) return;
  weight=MCweight()*ev.GetTriggerLumi("Full")*GetPileUpWeight(nPileUp,0)*GetPrefireWeight(0)*zptweight*weakweight*z0weight*topptweight*btagsf*jetpuidsf;
  
}

void DYbTrueBJetAnalyzer::RunReco(){
  v_tightlep={};
  v_tightjet=GetTightJet(v_tightlep,30,jetetacut);
  v_bjetidx=GetBJetIdx(v_tightjet);


  //--Now Objects are ready--//
  SetEventWeight();



  Run();

}
void DYbTrueBJetAnalyzer::Run(){

  //idx_bquark_GEN
  //idx_bbarquark_GEN
  int i_bGEN = -1;
  
  if(nb==1) i_bGEN=idx_bquark_GEN;
  if(nbbar==1) i_bGEN=idx_bbarquark_GEN;
  if(i_bGEN<0) return;

  
  ///-----Let's match them to btagged jets----//
  // conditions => 1. same flavour 2. dRmatch
  int i_b=GetBJet_TightJetIdx_dR_Flavour_Match(i_bGEN);
  if(i_b<0) return;
  
  
  ///Now we have bLep, bHad
  
  double true_bpt=gens[i_bGEN].Pt();

  FillHist_this_bjet(v_tightjet[i_b],"All",i_bGEN);  
  //if(true_bpt>20.) FillHist_this_bjet(v_tightjet[i_b],"All_True_bpt20",i_bGEN);

  if(IsMuMu){
    FillHist_this_bjet(v_tightjet[i_b],"MuMu",i_bGEN);
    //if(true_bpt>20.) FillHist_this_bjet(v_tightjet[i_b],"MuMu_True_bpt20",i_bGEN);
  }
  if(IsEE){
    FillHist_this_bjet(v_tightjet[i_b],"EE",i_bGEN);
    //if(true_bpt>20.) FillHist_this_bjet(v_tightjet[i_b],"EE_True_bpt20",i_bGEN);
  }
}

int DYbTrueBJetAnalyzer::FindBinNumber(double this_eta){
  //vEta
  auto it = std::lower_bound(vEta.begin(), vEta.end(), this_eta);
  return std::distance(vEta.begin(), it)-1; // if eta==-2.4, return 1-1 = 0, when
  //vEta={-2.5, -2.1, -1.8, -1.5, -1.2,-0.9, -0.7, -0.5, -0.3, -0.1, 0, 0.1, 0.3, 0.5 ,0.7, 0.9, 1.2, 1.5, 1.8, 2.1, 2.5};
}

void DYbTrueBJetAnalyzer::FillHist_this_bjet(Jet &_bjet,TString bjetname, int i_GEN){

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
pair<int,int> DYbTrueBJetAnalyzer::GetN_SLTMuon(Jet &_bjet,vector<Muon> &_muoncoll){
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
int DYbTrueBJetAnalyzer::GetN_SLTElectron(Jet &_bjet,vector<Electron> &_electroncoll){
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

int DYbTrueBJetAnalyzer::GetBJet_TightJetIdx_dR_Flavour_Match(int i_GEN){
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




bool DYbTrueBJetAnalyzer::HasMatchedRecoJet(int genidx,double dRcut){
  TLorentzVector this_genptl=gens[genidx];
  for(auto &jet : v_tightjet){
    if(this_genptl.DeltaR(jet) < dRcut) return 1;
  }
  return 0;
}


bool DYbTrueBJetAnalyzer::HasFlavourMatchedRecoJet(int genidx){
  //TLorentzVector this_genptl=gens[genidx];
  int true_pid=gens[genidx].PID();
  for(auto &jet : v_tightjet){
    if(jet.partonFlavour() == true_pid) return 1;
  }
  return 0;
}




void DYbTrueBJetAnalyzer::EventLoop(){
  if(nb+nbbar!=1) return;
  
  RunReco();

}





void DYbTrueBJetAnalyzer::TruthLoop(){
  //it must be TTLJ samples
  if (IsDYSample){
    DYbTrueBJetAnalyzer::RunLHEinfo();
    DYbTrueBJetAnalyzer::RunGENinfo();
  }

}

void DYbTrueBJetAnalyzer::RunLHEinfo(){

  //---
  IsMuMu=0; IsEE=0;

  nb=0;
  nbbar=0;
  idx_lhe_mu1=-1; idx_lhe_mu2=-1;//mu1=mu- , mu2=mu+
  idx_lhe_e1=-1; idx_lhe_e2=-1; //e1=e- , e2=e+
  idx_lhe_b=-1;
  pid_b=0;
  unsigned int nmuon=0;
  unsigned int nelectron=0;
  unsigned int ntau=0;
  unsigned int lhesize=lhes.size();
  for(unsigned int i = 0 ; i < lhesize; i++){
    int status=lhes[i].Status();
    int pid=lhes[i].ID();
    if(status==-1) continue;
    if(abs(pid)==15){//tau
      ntau+=1;
    }
    else if(abs(pid)==13){//muon
      nmuon+=1;
      if(pid>0){
        idx_lhe_mu1=i;
      }else{
        idx_lhe_mu2=i;
      }
    }else if(abs(pid)==11){//electron
      nelectron+=1;
      if(pid>0){
        idx_lhe_e1=i;
      }
      else{
        idx_lhe_e2=i;
      }
    }//end if electron

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



  if(ntau==2){
    IsMuMu=0; IsEE=0;
    idx_lhe_mu1=-1; idx_lhe_mu2=-1;
    idx_lhe_e1=-1; idx_lhe_e2=-1;
    return;
  }
  else if(nmuon==2){
    IsMuMu=1;
    ll_str="MuMu";
    return;
  }
  else if(nelectron==2){
    IsEE=1;
    ll_str="EE";
    return;
  }

  
}
void DYbTrueBJetAnalyzer::RunGENinfo(){




  idx_bquark_GEN=-1, idx_bbarquark_GEN=-1;

  if(nb+nbbar!=1) return;
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

      if(pid==5){
        idx_bquark_GEN=i;
	FillHist("GEN/true_bjet_pt",gens[i].Pt(), weight, 100,0,200);
	//cout << "b!!" << endl; 
      }
      else if(pid==-5){
        idx_bbarquark_GEN=i;
	FillHist("GEN/true_bjet_pt",gens[i].Pt(), weight, 100,0,200);
	//cout << "bbar!!" << endl; 
      }
    }


  }




  

}


