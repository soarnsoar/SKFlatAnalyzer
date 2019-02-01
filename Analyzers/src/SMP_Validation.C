#include "SMP_Validation.h"

void SMP_Validation::initializeAnalyzer(){
  /*
  if(!IsDATA){
    fChain->SetBranchStatus("gen_*",0);
    fChain->SetBranchStatus("gen_weight",1);
  }
  */
  //fChain->SetBranchStatus("jet_*",0);
  //fChain->SetBranchStatus("photon_*",0);
  //fChain->SetBranchStatus("fatjet_*",0);
  //fChain->SetBranchStatus("pfMET_*",0);
  cout<<"[SMP_Validation::initializeAnalyzer] setting zptcor"<<endl;
  TString datapath=getenv("DATA_DIR");
  TFile fzpt(datapath+"/"+TString::Itoa(DataYear,10)+"/ZPt/ZPtWeight.root");
  for(int i=0;i<20;i++){
    TH2D* this_hzpt_muon=(TH2D*)fzpt.Get(Form("muon%d_iter%d",DataYear,i));
    if(this_hzpt_muon){
      if(hzpt_muon){
	hzpt_muon->Multiply(this_hzpt_muon);
	cout<<"[SMP_Validation::initializeAnalyzer] setting muon zptcor iter"<<i<<endl;
      }else{
	hzpt_muon=this_hzpt_muon;
	cout<<"[SMP_Validation::initializeAnalyzer] setting first muon zptcor"<<i<<endl;
      }
    }else break;
  }
  if(hzpt_muon) hzpt_muon->SetDirectory(0);
  hzpt_norm_muon=(TH2D*)fzpt.Get(Form("muon%d_norm",DataYear));
  if(hzpt_norm_muon){
    hzpt_norm_muon->SetDirectory(0);
    cout<<"[SMP_Validation::initializeAnalyzer] setting muon zptcor norm"<<endl;
  }
  for(int i=0;i<20;i++){
    TH2D* this_hzpt_electron=(TH2D*)fzpt.Get(Form("electron%d_iter%d",DataYear,i));
    if(this_hzpt_electron){
      if(hzpt_electron){
	hzpt_electron->Multiply(this_hzpt_electron);
	cout<<"[SMP_Validation::initializeAnalyzer] setting electron zptcor iter"<<i<<endl;
      }else{
	hzpt_electron=this_hzpt_electron;
	cout<<"[SMP_Validation::initializeAnalyzer] setting first electron zptcor"<<i<<endl;
      }
    }else break;
  }
  if(hzpt_electron) hzpt_electron->SetDirectory(0);
  hzpt_norm_electron=(TH2D*)fzpt.Get(Form("electron%d_norm",DataYear));
  if(hzpt_norm_electron){
    hzpt_norm_electron->SetDirectory(0);
    cout<<"[SMP_Validation::initializeAnalyzer] setting electron zptcor norm"<<endl;
  }
}

void SMP_Validation::executeEvent(){
  ////////////////////////check tautau events//////////////////
  prefix="";
  Gen genl0,genl1,genfsr,genhardl0,genhardl1;
  TLorentzVector genZ;
  zptcor=1.;
  if(MCSample.Contains("DYJets")){
    vector<Gen> gens=GetGens();
    for(int i=0;i<(int)gens.size();i++){
      if(!gens.at(i).isPrompt()) continue;
      if(gens.at(i).isHardProcess()){
	if(genhardl0.IsEmpty()&&(abs(gens.at(i).PID())==11||abs(gens.at(i).PID())==13||abs(gens.at(i).PID())==15)) genhardl0=gens.at(i);
	else if(!genhardl0.IsEmpty()&&gens.at(i).PID()==-genhardl0.PID()){
	  genhardl1=gens.at(i);
	  if(abs(genhardl1.PID())==15){
	    prefix="tau_";
	    break;
	  }
	}
      }
      if(gens.at(i).Status()==1){
	if(genl0.IsEmpty()&&(abs(gens.at(i).PID())==11||abs(gens.at(i).PID())==13)) genl0=gens.at(i);
	else if(!genl0.IsEmpty()&&gens.at(i).PID()==-genl0.PID()){
	  genl1=gens.at(i);
	}
	else if(gens.at(i).PID()==22){
	  genfsr+=gens.at(i);
	}
      }	
    }
    if(abs(genhardl0.PID())!=15){
      genZ=(genl0+genl1+genfsr);
      if(genZ.Pt()==0) PrintGens(gens);
      zptcor*=GetZPtWeight(genZ.Pt(),genZ.Rapidity(),abs(genhardl0.PID())==13?Lepton::Flavour::MUON:Lepton::Flavour::ELECTRON);
      FillGenHists(abs(genhardl0.PID())==13?"muon2017gen/":"electron2017gen/","",genl0,genl1,genfsr,weight_norm_1invpb*gen_weight*zptcor);
      FillGenHists(abs(genhardl0.PID())==13?"muon2017gen/":"electron2017gen/","_nozptcor",genl0,genl1,genfsr,weight_norm_1invpb*gen_weight);
      FillHist((abs(genhardl0.PID())==13?"muon2017gen/":"electron2017gen/")+prefix+"dipty",genZ.Pt(),fabs(genZ.Rapidity()),weight_norm_1invpb*gen_weight*zptcor,zptcor_nptbin,(double*)zptcor_ptbin,zptcor_nybin,(double*)zptcor_ybin);
      FillHist((abs(genhardl0.PID())==13?"muon2017gen/":"electron2017gen/")+prefix+"dipty_nozptcor",genZ.Pt(),fabs(genZ.Rapidity()),weight_norm_1invpb*gen_weight,zptcor_nptbin,(double*)zptcor_ptbin,zptcor_nybin,(double*)zptcor_ybin);
    }
  }

  if(!PassMETFilter()) return;

  Event* ev=new Event;
  *ev=GetEvent();
  TString channelname;
  if(DataYear==2016){
    TString electrontrigger;
    vector<TString> muontrigger;
    muontrigger.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v");
    muontrigger.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v");
    muontrigger.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    muontrigger.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
    electrontrigger="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v";
    if(ev->PassTrigger(muontrigger)){
      channelname="muon2016";
      //if(!IsDATA||DataStream.Contains("DoubleMuon")) executeEventFromParameter(channelname,ev);
    }
    if(ev->PassTrigger(electrontrigger)){
      channelname="electron2016";
      //if(!IsDATA||DataStream.Contains("DoubleEG")) executeEventFromParameter(channelname,ev);
    }
  }
  else if(DataYear==2017){
    TString muontrigger,electrontrigger;
    muontrigger="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v";
    electrontrigger="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v";
    if(ev->PassTrigger(muontrigger)){
      channelname="muon2017";
      if(!IsDATA||DataStream.Contains("DoubleMuon")) executeEventFromParameter(channelname,ev);
    }
    if(ev->PassTrigger(electrontrigger)){
      channelname="electron2017";
      if(!IsDATA||DataStream.Contains("DoubleEG")) executeEventFromParameter(channelname,ev);
    }
  }
  delete ev;
}

void SMP_Validation::executeEventFromParameter(TString channelname,Event* ev){
  std::vector<Muon> muons=GetMuons("POGTightWithTightIso",7.,2.4);
  std::sort(muons.begin(),muons.end(),PtComparing);
  std::vector<Electron> electrons=GetElectrons("passMediumID",9.,2.5);
  std::sort(electrons.begin(),electrons.end(),PtComparing);
  std::vector<Lepton*> leps;
  double lep0ptcut,lep1ptcut,etacut;
  double (MCCorrection::*LeptonID_SF)(TString,double,double,int)=NULL;
  double (MCCorrection::*LeptonISO_SF)(TString,double,double,int)=NULL;
  double (MCCorrection::*LeptonReco_SF)(double,double,int)=NULL;
  TString LeptonID_key,LeptonID_key_POG,LeptonISO_key,LeptonReco_key,triggerSF_key0,triggerSF_key1;
  if(channelname.Contains("muon")){
    leps=MakeLeptonPointerVector(muons);
    lep0ptcut=20.;
    lep1ptcut=10.;
    etacut=2.4;
    LeptonID_SF=&MCCorrection::MuonID_SF;
    LeptonISO_SF=&MCCorrection::MuonISO_SF;
    LeptonID_key="NUM_TightID_DEN_genTracks";
    LeptonISO_key="NUM_TightRelIso_DEN_TightIDandIPCut";
    triggerSF_key0="Leg17_POGTight";
    triggerSF_key1="Leg8_POGTight";
 }else if(channelname.Contains("electron")){
    leps=MakeLeptonPointerVector(electrons);
    lep0ptcut=25.;
    lep1ptcut=15.;
    etacut=2.5;
    LeptonID_SF=&MCCorrection::ElectronID_SF;
    LeptonReco_SF=&MCCorrection::ElectronReco_SF;
    LeptonID_key="passMediumID_pt10";
    LeptonID_key_POG="passMediumID";
    triggerSF_key0="LeadEle23_MediumID";
    triggerSF_key1="TailEle12_MediumID";
  }else{
    cout<<"[SMP_Validation::executeEventFromParameter] wrong channelname"<<endl;
    return;
  }
  
  /////////////////lumi weight///////////////////
  double weight=1.,totalweight=1.;
  if(!IsDATA){
    weight=weight_norm_1invpb*ev->MCweight()*ev->GetTriggerLumi("Full");
    totalweight*=weight;
  }
  FillHist("cutflow",0.5,totalweight,20,0,20);

  /////////////////PUreweight///////////////////
  double PUreweight=1.,PUreweight_up=1.,PUreweight_down=1.;
  if(!IsDATA){
    PUreweight=mcCorr.GetPileUpWeightAsSampleName(0,nPileUp);
    PUreweight_up=mcCorr.GetPileUpWeightAsSampleName(1,nPileUp);
    PUreweight_down=mcCorr.GetPileUpWeightAsSampleName(-1,nPileUp);
    totalweight*=PUreweight;
  }
  FillHist("cutflow",1.5,totalweight,20,0,20);
  
  /////////////////kinematic selections///////////////////
  if(leps.size()<2) return;
  FillHist("cutflow",2.5,totalweight,20,0,20);
  if(leps.at(0)->Pt()<lep0ptcut||leps.at(1)->Pt()<lep1ptcut) return;
  if(fabs(leps.at(0)->Eta())>etacut||fabs(leps.at(1)->Eta()>etacut)) return;
  FillHist("cutflow",3.5,totalweight,20,0,20);
  if(leps.size()!=2) return;
  FillHist("cutflow",4.5,totalweight,20,0,20);
  
  /////////////////efficiency scale factors///////////////////
  double IDSF=1.,IDSF_up=1.,IDSF_down=1.;
  double IDSF_POG=1.,IDSF_POG_up=1.,IDSF_POG_down=1.;
  double ISOSF=1.,ISOSF_up=1.,ISOSF_down=1.;
  double RECOSF=1.,RECOSF_up=1.,RECOSF_down=1.;
  if(!IsDATA){
    for(int i=0;i<(int)leps.size();i++){
      double this_pt,this_eta;
      if(leps[i]->LeptonFlavour()==Lepton::MUON){
	this_pt=((Muon*)leps.at(i))->MiniAODPt();
	this_eta=leps.at(i)->Eta();
      }else if(leps[i]->LeptonFlavour()==Lepton::ELECTRON){
	this_pt=leps.at(i)->Pt();
	this_eta=((Electron*)leps.at(i))->scEta();
      }else{
	cout <<"[SMP_Validation::executeEventFromParameter] It is not lepton"<<endl;
	exit(EXIT_FAILURE);
      }

      double this_RECOSF=LeptonReco_SF?(mcCorr.*LeptonReco_SF)(this_eta,this_pt,0):1.;
      double this_RECOSF_up=LeptonReco_SF?(mcCorr.*LeptonReco_SF)(this_eta,this_pt,1):1.;
      double this_RECOSF_down=LeptonReco_SF?(mcCorr.*LeptonReco_SF)(this_eta,this_pt,-1):1.;
      RECOSF*=this_RECOSF; RECOSF_up*=this_RECOSF_up; RECOSF_down*=this_RECOSF_down;

      double this_IDSF=LeptonID_SF?(mcCorr.*LeptonID_SF)(LeptonID_key,this_eta,this_pt,0):1.;
      double this_IDSF_up=LeptonID_SF?(mcCorr.*LeptonID_SF)(LeptonID_key,this_eta,this_pt,1):1.;
      double this_IDSF_down=LeptonID_SF?(mcCorr.*LeptonID_SF)(LeptonID_key,this_eta,this_pt,-1):1.;
      IDSF*=this_IDSF; IDSF_up*=this_IDSF_up; IDSF_down*=this_IDSF_down;
      
      if(LeptonID_key_POG!=""){
	double this_IDSF_POG=LeptonID_SF?(mcCorr.*LeptonID_SF)(LeptonID_key_POG,this_eta,this_pt,0):1.;
	double this_IDSF_POG_up=LeptonID_SF?(mcCorr.*LeptonID_SF)(LeptonID_key_POG,this_eta,this_pt,1):1.;
	double this_IDSF_POG_down=LeptonID_SF?(mcCorr.*LeptonID_SF)(LeptonID_key_POG,this_eta,this_pt,-1):1.;
	IDSF_POG*=this_IDSF_POG; IDSF_POG_up*=this_IDSF_POG_up; IDSF_POG_down*=this_IDSF_POG_down;
      }

      double this_ISOSF=LeptonISO_SF?(mcCorr.*LeptonISO_SF)(LeptonISO_key,this_eta,this_pt,0):1.;
      double this_ISOSF_up=LeptonISO_SF?(mcCorr.*LeptonISO_SF)(LeptonISO_key,this_eta,this_pt,1):1.;
      double this_ISOSF_down=LeptonISO_SF?(mcCorr.*LeptonISO_SF)(LeptonISO_key,this_eta,this_pt,-1):1.;
      ISOSF*=this_ISOSF; ISOSF_up*=this_ISOSF_up; ISOSF_down*=this_ISOSF_down;
    }
  }
  totalweight*=RECOSF;
  FillHist("cutflow",5.5,totalweight,20,0,20);
  totalweight*=IDSF;
  FillHist("cutflow",6.5,totalweight,20,0,20);
  totalweight*=ISOSF;
  FillHist("cutflow",7.5,totalweight,20,0,20);

  double triggerSF=1.,triggerSF_up=1.,triggerSF_down=1.;
  if(!IsDATA){
    triggerSF*=DileptonTrigger_SF(triggerSF_key0,triggerSF_key1,leps,0);
    triggerSF_up*=DileptonTrigger_SF(triggerSF_key0,triggerSF_key1,leps,1);
    triggerSF_down*=DileptonTrigger_SF(triggerSF_key0,triggerSF_key1,leps,-1);
  }
  totalweight*=triggerSF;
  FillHist("cutflow",8.5,totalweight,20,0,20);

  //////////////////////no MC for M<50////////////////
  if(((*leps.at(0))+(*leps.at(1))).M()<60) return;
  FillHist("cutflow",9.5,totalweight,20,0,20);


  //////////////////////PrefileWeight////////////////////
  double prefireweight=GetPrefireWeight(0);
  double prefireweight_up=GetPrefireWeight(1);
  double prefireweight_down=GetPrefireWeight(-1);
  totalweight*=prefireweight;
  FillHist("cutflow",10.5,totalweight,20,0,20);

  totalweight*=zptcor;
  FillHist("cutflow",11.5,totalweight,20,0,20);

  ///////////////////////weight systematics//////////////////
  map<TString,double> map_systematic;
  if(!IsDATA){
    map_systematic["noPUreweight"]=weight*RECOSF*IDSF*ISOSF*triggerSF*prefireweight*zptcor;
    map_systematic["PUreweight_up"]=weight*PUreweight_up*RECOSF*IDSF*ISOSF*triggerSF*prefireweight*zptcor;
    map_systematic["PUreweight_down"]=weight*PUreweight_down*RECOSF*IDSF*ISOSF*triggerSF*prefireweight*zptcor;
  
    map_systematic["noefficiencySF"]=weight*PUreweight*prefireweight*zptcor;
  
    map_systematic["noRECOSF"]=weight*PUreweight*IDSF*ISOSF*triggerSF*prefireweight*zptcor;
    map_systematic["RECOSF_up"]=weight*PUreweight*RECOSF_up*IDSF*ISOSF*triggerSF*prefireweight*zptcor;
    map_systematic["RECOSF_down"]=weight*PUreweight*RECOSF_down*IDSF*ISOSF*triggerSF*prefireweight*zptcor;
    
    map_systematic["noIDSF"]=weight*PUreweight*RECOSF*ISOSF*triggerSF*prefireweight*zptcor;
    map_systematic["IDSF_up"]=weight*PUreweight*RECOSF*IDSF_up*ISOSF*triggerSF*prefireweight*zptcor;
    map_systematic["IDSF_down"]=weight*PUreweight*RECOSF*IDSF_down*ISOSF*triggerSF*prefireweight*zptcor;

    map_systematic["IDSF_POG"]=weight*PUreweight*RECOSF*IDSF_POG*ISOSF*triggerSF*prefireweight*zptcor;
    map_systematic["IDSF_POG_up"]=weight*PUreweight*RECOSF*IDSF_POG_up*ISOSF*triggerSF*prefireweight*zptcor;
    map_systematic["IDSF_POG_down"]=weight*PUreweight*RECOSF*IDSF_POG_down*ISOSF*triggerSF*prefireweight*zptcor;
    
    map_systematic["noISOSF"]=weight*PUreweight*RECOSF*IDSF*triggerSF*prefireweight*zptcor;
    map_systematic["ISOSF_up"]=weight*PUreweight*RECOSF*IDSF*ISOSF_up*triggerSF*prefireweight*zptcor;
    map_systematic["ISOSF_down"]=weight*PUreweight*RECOSF*IDSF*ISOSF_down*triggerSF*prefireweight*zptcor;
    
    map_systematic["notriggerSF"]=weight*PUreweight*RECOSF*IDSF*ISOSF*prefireweight*zptcor;
    map_systematic["triggerSF_up"]=weight*PUreweight*RECOSF*IDSF*ISOSF*triggerSF_up*prefireweight*zptcor;
    map_systematic["triggerSF_down"]=weight*PUreweight*RECOSF*IDSF*ISOSF*triggerSF_down*prefireweight*zptcor;

    map_systematic["noprefireweight"]=weight*PUreweight*RECOSF*IDSF*ISOSF*triggerSF*zptcor;
    map_systematic["prefireweight_up"]=weight*PUreweight*RECOSF*IDSF*ISOSF*triggerSF*prefireweight_up*zptcor;
    map_systematic["prefireweight_down"]=weight*PUreweight*RECOSF*IDSF*ISOSF*triggerSF*prefireweight_down*zptcor;
    
    map_systematic["nozptcor"]=weight*PUreweight*RECOSF*IDSF*ISOSF*triggerSF*prefireweight;

    if(PDFWeights_AlphaS->size()==2){
      map_systematic["alphaS_up"]=weight*PUreweight*RECOSF*IDSF*ISOSF*triggerSF*prefireweight*zptcor*PDFWeights_AlphaS->at(0);
      map_systematic["alphaS_down"]=weight*PUreweight*RECOSF*IDSF*ISOSF*triggerSF*prefireweight*zptcor*PDFWeights_AlphaS->at(1);
    }
  
    for(int i=0;i<(int)PDFWeights_Scale->size();i++){
      map_systematic[Form("scalevariation%d",i)]=weight*PUreweight*RECOSF*IDSF*ISOSF*triggerSF*prefireweight*zptcor*PDFWeights_Scale->at(i);
    }
  }

  
  
  ///////////////////////fill hists///////////////////////
  if(leps.at(0)->Charge()*leps.at(1)->Charge()<0){
    FillHist("cutflow",12.5,totalweight,20,0,20);
    FillBasicHists(channelname+"/OS/"+prefix,"",leps,totalweight);
    FillSystematicHists(channelname+"/OS/"+prefix,"",leps,map_systematic);
    if(((*leps.at(0))+(*leps.at(1))).M()<100&&((*leps.at(0))+(*leps.at(1))).M()>80){
      FillHist("cutflow",13.5,totalweight,20,0,20);
      FillBasicHists(channelname+"/OS_Z/"+prefix,"",leps,totalweight);
      FillSystematicHists(channelname+"/OS_Z/"+prefix,"",leps,map_systematic);
      for(int i=0;i<zptcor_nybin;i++){
	if(fabs(((*leps.at(0))+(*leps.at(1))).Rapidity())>=zptcor_ybin[i]&&fabs(((*leps.at(0))+(*leps.at(1))).Rapidity())<zptcor_ybin[i+1]){
	  FillBasicHists(channelname+Form("/OS_Z_y%.1fto%.1f/",zptcor_ybin[i],zptcor_ybin[i+1])+prefix,"",leps,totalweight);
	  FillSystematicHists(channelname+Form("/OS_Z_y%.1fto%.1f/",zptcor_ybin[i],zptcor_ybin[i+1])+prefix,"",leps,map_systematic);
	}
      }
      FillHist(channelname+"/OS_Z/"+prefix+"dipty",((*leps.at(0))+(*leps.at(1))).Pt(),fabs(((*leps.at(0))+(*leps.at(1))).Rapidity()),totalweight,zptcor_nptbin,(double*)zptcor_ptbin,zptcor_nybin,(double*)zptcor_ybin);
      FillHist(channelname+"/OS_Z/"+prefix+"dipty_nozptcor",((*leps.at(0))+(*leps.at(1))).Pt(),fabs(((*leps.at(0))+(*leps.at(1))).Rapidity()),map_systematic["nozptcor"],zptcor_nptbin,(double*)zptcor_ptbin,zptcor_nybin,(double*)zptcor_ybin);
    }
  }else{
    FillHist("cutflow",14.5,totalweight,20,0,20);
    FillBasicHists(channelname+"/SS/"+prefix,"",leps,totalweight);
    FillSystematicHists(channelname+"/SS/"+prefix,"",leps,map_systematic);
  }
}

void SMP_Validation::FillGenHists(TString pre,TString suf,TLorentzVector genl0,TLorentzVector genl1,TLorentzVector genfsr,double w){
  TLorentzVector genZ=genl0+genl1+genfsr;
  FillHist(pre+"genZmass"+suf,genZ.M(),w,400,0,400);
  FillHist(pre+"genZpt"+suf,genZ.Pt(),w,400,0,400);
  FillHist(pre+"genZrap"+suf,genZ.Rapidity(),w,60,-6,6);
  if(genl0.Pt()<genl1.Pt()){
    TLorentzVector temp=genl0;
    genl0=genl1;
    genl1=temp;
  }
  FillHist(Form("%sgenl0pt%s",pre.Data(),suf.Data()),genl0.Pt(),w,200,0,200);
  FillHist(Form("%sgenl0eta%s",pre.Data(),suf.Data()),genl0.Eta(),w,50,-5,5);
  FillHist(Form("%sgenl1pt%s",pre.Data(),suf.Data()),genl1.Pt(),w,200,0,200);
  FillHist(Form("%sgenl1eta%s",pre.Data(),suf.Data()),genl1.Eta(),w,50,-5,5);
  FillHist(pre+"lldelR"+suf,genl0.DeltaR(genl1),w,70,0,7);  
  FillHist(pre+"lldelphi"+suf,genl0.DeltaPhi(genl1),w,80,-4,4);
}

void SMP_Validation::FillBasicHists(TString pre,TString suf,const vector<Lepton*>& leps,double w){
  Particle dilepton=((*leps.at(0))+(*leps.at(1)));
  FillHist(pre+"dimass"+suf,dilepton.M(),w,400,0,400);
  FillHist(pre+"dipt"+suf,dilepton.Pt(),w,400,0,400);
  FillHist(pre+"dirap"+suf,dilepton.Rapidity(),w,50,-5,5);
  for(int i=0;i<(int)leps.size();i++){
    FillHist(Form("%sl%dpt%s",pre.Data(),i,suf.Data()),leps.at(i)->Pt(),w,200,0,200);
    FillHist(Form("%sl%deta%s",pre.Data(),i,suf.Data()),leps.at(i)->Eta(),w,50,-5,5);
    FillHist(Form("%sl%driso%s",pre.Data(),i,suf.Data()),leps.at(i)->RelIso(),w,30,0,0.3);
  }
  FillHist(pre+"lldelR"+suf,leps.at(0)->DeltaR(*leps.at(1)),w,70,0,7);  
  FillHist(pre+"lldelphi"+suf,leps.at(0)->DeltaPhi(*leps.at(1)),w,80,-4,4);
  FillHist(pre+"nPV"+suf,nPV,w,60,0,60);
}
void SMP_Validation::FillSystematicHists(TString pre,TString suf,const vector<Lepton*>& leps,map<TString,double> map_systematic){
  for(auto iter=map_systematic.begin();iter!=map_systematic.end();iter++){
    FillBasicHists(pre,"_"+iter->first+suf,leps,iter->second);
  }
}
double SMP_Validation::DileptonTrigger_SF(TString SFhistkey0,TString SFhistkey1,const vector<Lepton*>& leps,int sys){
  if(IsDATA) return 1;
  if(leps.size()!=2){
    cout<<"[SMP_Validation::Trigger_SF] only dilepton algorithm"<<endl;
    return 1;
  }
  map<TString,TH2F*>* map_hist_Lepton=NULL;
  if(leps[0]->LeptonFlavour()==Lepton::MUON){
    map_hist_Lepton=&mcCorr.map_hist_Muon;
  }else if(leps[0]->LeptonFlavour()==Lepton::ELECTRON){
    map_hist_Lepton=&mcCorr.map_hist_Electron;
  }else{
    cout <<"[SMP_Validation::Trigger_SF] Not ready"<<endl;
    exit(EXIT_FAILURE);
  }    
      
  TH2F* this_hist[2]={NULL,NULL};
  double triggerSF=1.;
  this_hist[0]=(*map_hist_Lepton)["Trigger_SF_"+SFhistkey0];
  this_hist[1]=(*map_hist_Lepton)["Trigger_SF_"+SFhistkey1];
  if(!this_hist[0]||!this_hist[1]){
    cout << "[SMP_Validation::Trigger_SF] No "<<SFhistkey0<<" or "<<SFhistkey1<<endl;
    exit(EXIT_FAILURE);
  }
  for(int i=0;i<(int)leps.size();i++){
    double this_pt,this_eta;
    if(leps[i]->LeptonFlavour()==Lepton::MUON){
      this_pt=((Muon*)leps.at(i))->MiniAODPt();
      this_eta=leps.at(i)->Eta();
    }else if(leps[i]->LeptonFlavour()==Lepton::ELECTRON){
      this_pt=leps.at(i)->Pt();
      this_eta=((Electron*)leps.at(i))->scEta();
    }else{
      cout << "[SMP_Validation::Trigger_SF] It is not lepton"<<endl;
      exit(EXIT_FAILURE);
    }
    /*
    double ptmin=this_hist[i]->GetYaxis()->GetXmin();
    double ptmax=this_hist[i]->GetYaxis()->GetXmax();
    double etamin=this_hist[i]->GetXaxis()->GetXmin();
    double etamax=this_hist[i]->GetXaxis()->GetXmax();    
    if(this_pt<ptmin) this_pt=ptmin+0.001;
    if(this_pt>ptmax) this_pt=ptmax-0.001;
    if(etamin>=0) this_eta=fabs(this_eta);
    if(this_eta<etamin) this_eta=etamin+0.001;
    if(this_eta>etamax) this_eta=etamax-0.001;
    triggerSF*=this_hist[i]->GetBinContent(this_hist[i]->FindBin(this_eta,this_pt))+sys*this_hist[i]->GetBinError(this_hist[i]->FindBin(this_eta,this_pt));
    */
    triggerSF*=GetBinContentUser(this_hist[i],this_eta,this_pt,sys);
  }
  return triggerSF;
}

double SMP_Validation::GetZPtWeight(double zpt,double zrap,Lepton::Flavour flavour){
  double valzptcor=1.;
  double valzptcor_norm=1.;
  TH2D* hzpt=NULL;
  TH2D* hzpt_norm=NULL;
  if(flavour==Lepton::MUON){
    hzpt=hzpt_muon;
    hzpt_norm=hzpt_norm_muon;
  }else if(flavour==Lepton::ELECTRON){
    hzpt=hzpt_electron;
    hzpt_norm=hzpt_norm_electron;
  }
  if(hzpt) valzptcor*=GetBinContentUser(hzpt,zpt,zrap,0);
  if(hzpt_norm) valzptcor_norm*=GetBinContentUser(hzpt_norm,zpt,zrap,0);
  return valzptcor*valzptcor_norm;
  /*
  double ptmin=hzpt->GetXaxis()->GetXmin();
  double ptmax=hzpt->GetXaxis()->GetXmax();
  double rapmin=hzpt->GetYaxis()->GetXmin();
  double rapmax=hzpt->GetYaxis()->GetXmax();
  if(zpt<ptmin) zpt=ptmin+0.001;
  if(zpt>ptmax) zpt=ptmax-0.001;
  if(rapmin>=0) zrap=fabs(zrap);
  if(zrap<rapmin) zrap=rapmin+0.001;
  if(zrap>rapmax) zrap=rapmax-0.001;
  */
  
  //cout<<"[SMP_Validation::GetZPtWeight]"<<endl;
  //cout<<zpt<<" "<<zrap<<" "<<hzpt->GetBinContent(hzpt->FindBin(zpt,zrap))<<endl;
  //return hzpt->GetBinContent(hzpt->FindBin(zpt,zrap));
}
void SMP_Validation::PrintGens(const vector<Gen>& gens){
  cout<<"index\tpid\tmother\tstatus\tpropt\thard\n";
  for(int i=0;i<(int)gens.size();i++){
    cout<<gens.at(i).Index()<<"\t"<<gens.at(i).PID()<<"\t"<<gens.at(i).MotherIndex()<<"\t"<<gens.at(i).Status()<<"\t"<<gens.at(i).isPrompt()<<"\t"<<gens.at(i).isHardProcess()<<endl;
  }
}
SMP_Validation::SMP_Validation(){
  hzpt_muon=NULL;
  hzpt_electron=NULL;
  hzpt_norm_muon=NULL;
  hzpt_norm_electron=NULL;
}

SMP_Validation::~SMP_Validation(){
  if(hzpt_muon) delete hzpt_muon;
  if(hzpt_norm_muon) delete hzpt_norm_muon;
  if(hzpt_electron) delete hzpt_electron;
  if(hzpt_norm_electron) delete hzpt_norm_electron;
}

double SMP_Validation::GetBinContentUser(TH2* hist,double valx,double valy,int sys){
  double xmin=hist->GetXaxis()->GetXmin();
  double xmax=hist->GetXaxis()->GetXmax();
  double ymin=hist->GetYaxis()->GetXmin();
  double ymax=hist->GetYaxis()->GetXmax();
  if(xmin>=0) valx=fabs(valx);
  if(valx<xmin) valx=xmin+0.001;
  if(valx>xmax) valx=xmax-0.001;
  if(ymin>=0) valy=fabs(valy);
  if(valy<ymin) valy=ymin+0.001;
  if(valy>ymax) valy=ymax-0.001;
  return hist->GetBinContent(hist->FindBin(valx,valy))+sys*hist->GetBinError(hist->FindBin(valx,valy));
}
