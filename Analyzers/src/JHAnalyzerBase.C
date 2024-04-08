#include "JHAnalyzerBase.h"

JHAnalyzerBase::JHAnalyzerBase(){

  
}
void JHAnalyzerBase::initializeAnalyzer(){
  cout << "[JHAnalyzerBase::initializeAnalyzer]DataEra->" << DataEra << endl;
  IsDYSample=MCSample.Contains("DYJets")||MCSample.Contains("ZToEE")||MCSample.Contains("ZToMuMu")||MCSample.Contains(TRegexp("DY[0-9]Jets"));
  cout << "IsDYSample=" << IsDYSample <<endl;
  AnalyzerCore::SetupEfficiency();
  AnalyzerCore::SetupRoccoR();
  if(IsDYSample)  AnalyzerCore::SetupZptWeight();
  InitSystematicMomentumVariations();
  runSys=HasFlag("runSys");
  checksf=HasFlag("checksf");
  SetUpBtag();
  if(IsDATA){
    ProcessName="Data";
  }
  else{
    ProcessName=MCSample;
  }
  cout << "[JHAnalyzerBase::initializeAnalyzer] runSys=" << runSys << endl;
}
void JHAnalyzerBase::SetUpBtag(){
  std::vector<JetTagging::Parameters> jtps;
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Tight, JetTagging::incl, JetTagging::comb) );
  mcCorr->SetJetTaggingParameters(jtps);
  jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  mcCorr->MCCorrection::SetEra(DataEra);
  btagcut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
  cout << "[JHAnalyzerBase::SetUpBtag]btagcut=" << btagcut << endl;
}
void JHAnalyzerBase::InitSystematicMomentumVariations(){
  //--Define--//
  jesUp.jes=1;                         
  jesUp.name="jes";jesUp.dir="Up";

  jesDown.jes=-1;                      
  jesDown.name="jes";jesDown.dir="Down";   

  jerUp.jer=1;                         
  jerUp.name="jer";jerUp.dir="Up";

  jerDown.jer=-1;                      
  jerDown.name="jer";jerDown.dir="Down";   
  
  /*
  muonscaleUp.muonscale=1;       
  muonscaleUp.name="muonscale";muonscaleUp.dir="Up";

  muonscaleDown.muonscale=-1;    
  muonscaleDown.name="muonscale";muonscaleDown.dir="Down";

  electronscaleUp.electronscale=1;   
  electronscaleUp.name="electronscale"; electronscaleUp.dir="Up";

  electronscaleDown.electronscale=-1;
  electronscaleDown.name="electronscale"; electronscaleDown.dir="Down";
  */
  metUp.met=1;   
  metUp.name="met";   metUp.dir="Up";
  metDown.met=-1;
  metDown.name="met"; metDown.dir="Down";
  //--Variation To Run--//
  //vMomentumVar={jesUp,jesDown,jerUp,jerDown,muonscaleUp,muonscaleDown,
  //		electronscaleUp,electronscaleDown,metUp,metDown};
  vMomentumVar={jesUp,jesDown,jerUp,jerDown,metUp,metDown};
  

  //--vMuonMomentumVar And ElectronMomentumVar
  const vector<int> nmem_mucorr={1,40,1,1,1,1};
  for(unsigned int idx1=0; idx1<nmem_mucorr.size();idx1++){
    int nmem=nmem_mucorr[idx1];
    vector<MuonMomentumVar> this_v;
    for(int idx2=0; idx2 < nmem;idx2++){
      MuonMomentumVar thisvar;
      thisvar.idx1=idx1; thisvar.idx2=idx2; thisvar.name="muonscale";
      this_v.push_back(thisvar);
    }
    vMuonMomentumVar.push_back(this_v);
  }


  const vector<int> nmem_elcorr={1,40,1,1,1,1,1,1,1};
  for(unsigned int idx1=0; idx1<nmem_elcorr.size();idx1++){
    int nmem=nmem_elcorr[idx1];
    vector<ElectronMomentumVar> this_v;
    for(int idx2=0; idx2 < nmem;idx2++){
      ElectronMomentumVar thisvar;
      thisvar.idx1=idx1; thisvar.idx2=idx2; thisvar.name="electronscale";
      this_v.push_back(thisvar);
    }
    vElectronMomentumVar.push_back(this_v);
  }
}

JHAnalyzerBase::~JHAnalyzerBase(){

  //==== Destructor of this Analyzer
  
}

void JHAnalyzerBase::executeEvent(){  


  SetEventBaseSysWeight();//this should be done first due to gen info for rochcorr
  InitAllObjects();
  ev=GetEvent();
  //---Nominal and weight-base variations--//
  //--init variables--//
  runWeightBase=true;
  SetSysStructure();
  

  InitClassVariablesPerEvent();
  InitBtagSys();
  EventLoop();
  //FillReservedHistWeightBase();
  //ClearReserveHist();

  if(!runSys) return;
  //---Momentum variations--//
  runWeightBase=false;
  SetSysStructure();//remove sysvariation weights
  for(const auto &sys : vMomentumVar){
    SetSys(sys);
    InitClassVariablesPerEvent();
    InitBtagSys();
    EventLoop();
    //FillReservedHistMomentumVariations();
    //ClearReserveHist();
  }

  for(const auto &_vsys : vMuonMomentumVar){
    for(const auto &sys : _vsys){
      SetSys(sys);
      InitClassVariablesPerEvent();
      InitBtagSys();
      EventLoop();
      //FillReservedHistLeptonMomentumVariations();
      //ClearReserveHist();
    }
  }

  for(const auto &_vsys : vElectronMomentumVar){
    for(const auto &sys : _vsys){
      SetSys(sys);
      InitClassVariablesPerEvent();
      InitBtagSys();
      EventLoop();
      //FillReservedHistLeptonMomentumVariations();
      //ClearReserveHist();
    }
  }
}

void JHAnalyzerBase::SetEventBaseSysWeight(){
  if(!runSys) return;
  if(IsDATA) return;
  //pu,prefire
  if(GetPileUpWeight(nPileUp,0)){
    r_PU={GetPileUpWeight(nPileUp,1)/GetPileUpWeight(nPileUp,0),GetPileUpWeight(nPileUp,-1)/GetPileUpWeight(nPileUp,0)};
  }
  else{
    r_PU={1.,1.};
  }
  //
  if(L1PrefireReweight_Central){
    r_Prefire={L1PrefireReweight_Up/L1PrefireReweight_Central, L1PrefireReweight_Down/L1PrefireReweight_Central };
  }
  else{
    r_Prefire={1.,1.};
  }
  //zptweight
  lhes=GetLHEs();
  gens=GetGens();
  if(IsDYSample){
    GetAFBLHEParticles(lhes,lhe_p0,lhe_p1,lhe_l0,lhe_l1,lhe_j0);
    GetAFBGenParticles(gens,gen_p0,gen_p1,gen_l0,gen_l1,3);//mode==3 -> before FSR
    GetAFBGenParticles(gens,gen_p0,gen_p1,gen_l0_dressed,gen_l1_dressed,1);//needed for ele rocc
    GetAFBGenParticles(gens,gen_p0,gen_p1,gen_l0_bare,gen_l1_bare,0);
    if(abs(lhe_l0.ID())==11||abs(lhe_l0.ID())==13){
      TLorentzVector genZ=(gen_l0+gen_l1);
      zptweight=GetZptWeight(genZ.M(),genZ.Rapidity(),genZ.Pt());
      weakweight=GetDYWeakWeight(genZ.M());

      //cout << "gen_l0_dressed is set" << gen_l0_dressed.Pt() << endl;
    }
  }//[end] dysample
  z0weight=GetZ0Weight(vertex_Z);

}
void JHAnalyzerBase::SetSysStructure(){
  //---WeightBase Systematic sources Only---//
  if(runSys&&runWeightBase){

    w_ElectronID=fEff->GetStructure(ElectronIDSFKey);
    r_ElectronID=fEff->GetStructure(ElectronIDSFKey);
    w_ElectronRECO=fEff->GetStructure(ElectronRecoSFKey);
    r_ElectronRECO=fEff->GetStructure(ElectronRecoSFKey);
    w_ElectronTrigger=fEff->GetStructure(ElectronTriggerSFKeys[0]);
    r_ElectronTrigger=fEff->GetStructure(ElectronTriggerSFKeys[0]);
    
    w_MuonID=fEff->GetStructure(MuonIDSFKey);
    r_MuonID=fEff->GetStructure(MuonIDSFKey);
    w_MuonRECO=fEff->GetStructure(MuonRecoSFKey);
    r_MuonRECO=fEff->GetStructure(MuonRecoSFKey);
    w_MuonTrigger=fEff->GetStructure(MuonTriggerSFKeys[0]);
    r_MuonTrigger=fEff->GetStructure(MuonTriggerSFKeys[0]);
    w_MuonTrk=fEff->GetStructure(MuonTrkSFKey);
    r_MuonTrk=fEff->GetStructure(MuonTrkSFKey);

    //----below is to check # of sys histograms
    /*
    unsigned int n_efftool_var=0;
    for(unsigned int i =0 ; i < w_ElectronID.size(); i++){
      n_efftool_var+=w_ElectronID[i].size();
    }
    for(unsigned int i =0 ; i < w_ElectronRECO.size(); i++){
      n_efftool_var+=w_ElectronRECO[i].size();
    }
    for(unsigned int i =0 ; i < w_ElectronTrigger.size(); i++){
      n_efftool_var+=w_ElectronTrigger[i].size();
    }
    for(unsigned int i =0 ; i < w_MuonID.size(); i++){
      n_efftool_var+=w_MuonID[i].size();
    }
    for(unsigned int i =0 ; i < w_MuonRECO.size(); i++){
      n_efftool_var+=w_MuonRECO[i].size();
    }
    for(unsigned int i =0 ; i < w_MuonTrigger.size(); i++){
      n_efftool_var+=w_MuonTrigger[i].size();
    }
    for(unsigned int i =0 ; i < w_MuonTrk.size(); i++){
      n_efftool_var+=w_MuonTrk[i].size();
    }
    cout << "[n_efftool_var]=" << n_efftool_var << endl;
    */


  }
  else{//if not weightbase
    //--Electron--//
    w_ElectronID.clear();
    r_ElectronID.clear();
    w_ElectronRECO.clear();
    r_ElectronRECO.clear();
    w_ElectronTrigger.clear();
    r_ElectronTrigger.clear();

    w_ElectronID.push_back({1.});
    r_ElectronID.push_back({1.});
    w_ElectronRECO.push_back({1.});
    r_ElectronRECO.push_back({1.});
    w_ElectronTrigger.push_back({1.});
    r_ElectronTrigger.push_back({1.});

    //---Muon--//
    w_MuonID.clear();
    r_MuonID.clear();
    w_MuonRECO.clear();
    r_MuonRECO.clear();
    w_MuonTrigger.clear();
    r_MuonTrigger.clear();
    w_MuonTrk.clear();
    r_MuonTrk.clear();

    w_MuonID.push_back({1.});
    r_MuonID.push_back({1.});
    w_MuonRECO.push_back({1.});
    r_MuonRECO.push_back({1.});
    w_MuonTrigger.push_back({1.});
    r_MuonTrigger.push_back({1.});
    w_MuonTrk.push_back({1.});
    r_MuonTrk.push_back({1.});

  }

}
void JHAnalyzerBase::InitBtagSys(){
  //---btagSF variations---//
  r_SystUpLTagCorr=1;r_SystDownLTagCorr=1;
  r_SystUpLTagUnCorr=1;r_SystDownLTagUnCorr=1;
  r_SystUpHTagCorr=1;r_SystDownHTagCorr=1;
  r_SystUpHTagUnCorr=1;r_SystDownHTagUnCorr=1;
}

void JHAnalyzerBase::InitClassVariablesPerEvent(){
  //--Event variables--//
  weight=1.;
  btagsf=1.;
  zptweight=1.;
  z0weight=1.;
  weakweight=1.;
}
void JHAnalyzerBase::FillHist(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //---ArgFillHist structure---//
  /*
  struct ArgFillHist{
    TString histname;
    double value; double weight;
    int n_bin; double x_min;
    double x_max;
  };

  */
  if(runWeightBase){
    FillHistWeightBase(histname,value,this_weight,n_bin,x_min,x_max);
  }  
  else{
    //TString histname="SYS/"+arg.histname+"/"+sysname_current+"/0/"+sysdir_current;
    TString newhistname="SYS/"+histname+"/"+sysname_current+"/"+sysidx1_current+"/"+sysidx2_current;
    AnalyzerCore::FillHist(newhistname+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
    //ArgFillHist this_arg={histname,value,this_weight,n_bin,x_min,x_max};
    //vReserveHist.push_back(this_arg);
  }
  //vReserveHist.push_back(make_tuple(histname,value,this_weight,n_bin,x_min,x_max));
}


///----FillHistForSystematic---//
void JHAnalyzerBase::FillHistUp(TString sysname,TString histname,double value,double this_weight,int n_bin,double x_min, double x_max){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/0/Up/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistDown(TString sysname,TString histname,double value,double this_weight,int n_bin,double x_min, double x_max){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/0/Down/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistIdx2(TString sysname, int idx1, int idx2, TString histname,double value,double this_weight,int n_bin,double x_min, double x_max){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/"+std::to_string(idx1)+"/"+std::to_string(idx2)+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistIdx2(TString sysname, TString idx1, TString idx2, TString histname,double value,double this_weight,int n_bin,double x_min, double x_max){
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/"+idx1+"/"+idx2+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
}

void JHAnalyzerBase::FillHistPUSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //PU weight//
  FillHistUp("pu",histname,value,this_weight*r_PU[0],n_bin,x_min,x_max);
  FillHistDown("pu",histname,value,this_weight*r_PU[1],n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistZptWeight(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  double r_zptweight=zptweight ? 1/zptweight : 1;
  FillHistIdx2("zptweight",0,0,histname,value,this_weight*r_zptweight,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistPSSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //PS weight//
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/HowToPDF#Parton_shower_weights
  //"structure":{
  //   0:{"name":"fsrDown","type":"group","group":"fsr"},
  //   1:{"name":"fsrUp","type":"group","group":"fsr"},
  //   2:{"name":"isrDown","type":"group","group":"isr"},
  //   3:{"name":"isrUp","type":"group","group":"isr"},
  int idx=0;
  for(const auto& _pssyst : *weight_PSSyst){
    FillHistIdx2("ps",0,idx,histname,value,this_weight*_pssyst,n_bin,x_min,x_max);
    idx+=1;
  }
}
void JHAnalyzerBase::FillHistPrefireSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //PU weight//
  FillHistUp("prefire",histname,value,this_weight*r_Prefire[0],n_bin,x_min,x_max);
  FillHistDown("prefire",histname,value,this_weight*r_Prefire[1],n_bin,x_min,x_max);
}


void JHAnalyzerBase::FillHistBtag(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //btag weight//  
  FillHistIdx2("btag","LTagCorr","Up",   histname, value,this_weight*r_SystUpLTagCorr,  n_bin,x_min,x_max);
  FillHistIdx2("btag","LTagCorr","Down", histname, value,this_weight*r_SystDownLTagCorr,n_bin,x_min,x_max);

  FillHistIdx2("btag","LTagUnCorr","Up",  histname, value,this_weight*r_SystUpLTagUnCorr,  n_bin,x_min,x_max);
  FillHistIdx2("btag","LTagUnCorr","Down",histname, value,this_weight*r_SystDownLTagUnCorr,n_bin,x_min,x_max);

  FillHistIdx2("btag","HTagCorr","Up",    histname, value,this_weight*r_SystUpHTagCorr,  n_bin,x_min,x_max);
  FillHistIdx2("btag","HTagCorr","Down",  histname, value,this_weight*r_SystDownHTagCorr,n_bin,x_min,x_max);

  FillHistIdx2("btag","HTagUnCorr","Up",   histname, value,this_weight*r_SystUpHTagUnCorr,  n_bin,x_min,x_max);
  FillHistIdx2("btag","HTagUnCorr","Down", histname, value,this_weight*r_SystDownHTagUnCorr,n_bin,x_min,x_max);
}


//----EffTool----//
void JHAnalyzerBase::FillHistElectronID(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //ElectronID weight//
  //vector<vector<double>> w_ElectronID
  unsigned int setsize = w_ElectronID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("electronID",iset,imem,histname,value,this_weight*r_ElectronID[iset][imem],n_bin,x_min,x_max);
    }
  }
}

void JHAnalyzerBase::FillHistElectronRECO(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //ElectronRECO weight//
  //vector<vector<double>> w_ElectronRECO
  unsigned int setsize = w_ElectronRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("electronRECO",iset,imem,histname,value,this_weight*r_ElectronRECO[iset][imem],n_bin,x_min,x_max);
    }
  }
}


void JHAnalyzerBase::FillHistElectronTrigger(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //ElectronTrigger weight//
  //vector<vector<double>> w_ElectronTrigger
  unsigned int setsize = w_ElectronTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("electronTrigger",iset,imem,histname,value,this_weight*r_ElectronTrigger[iset][imem],n_bin,x_min,x_max);
    }
  }
}


void JHAnalyzerBase::FillHistMuonID(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //MuonID weight//
  //vector<vector<double>> w_MuonID
  unsigned int setsize = w_MuonID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonID",iset,imem,histname,value,this_weight*r_MuonID[iset][imem],n_bin,x_min,x_max);
    }
  }
}

void JHAnalyzerBase::FillHistMuonRECO(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //MuonRECO weight//
  //vector<vector<double>> w_MuonRECO
  unsigned int setsize = w_MuonRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonRECO",iset,imem,histname,value,this_weight*r_MuonRECO[iset][imem],n_bin,x_min,x_max);
    }
  }
}

void JHAnalyzerBase::FillHistMuonTrigger(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //MuonTrigger weight//
  //vector<vector<double>> w_MuonTrigger
  unsigned int setsize = w_MuonTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonTrigger",iset,imem,histname,value,this_weight*r_MuonTrigger[iset][imem],n_bin,x_min,x_max);
    }
  }
}

void JHAnalyzerBase::FillHistMuonTrk(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //MuonTrk weight//
  //vector<vector<double>> w_MuonTrk
  unsigned int setsize = w_MuonTrk.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrk[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      FillHistIdx2("muonTrk",iset,imem,histname,value,this_weight*r_MuonTrk[iset][imem],n_bin,x_min,x_max);
    }
  }
}




void JHAnalyzerBase::FillReservedHistWeightBase(){
  for(const auto& arg : vReserveHist){ 

    TString histname=arg.histname;
    double value=arg.value;
    double this_weight=arg.weight;
    int n_bin=arg.n_bin;
    double x_min=arg.x_min;
    double x_max=arg.x_max;

    
    //Nominal//
    AnalyzerCore::FillHist(histname+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
  }
  if(IsDATA) return;
  if(!runSys) return;
  if(!runWeightBase) return;
  //---Here, weightbase sys varation only--//
  for(const auto& arg : vReserveHist){ 
    TString histname=arg.histname;
    double value=arg.value;
    double this_weight=arg.weight;
    int n_bin=arg.n_bin;
    double x_min=arg.x_min;
    double x_max=arg.x_max;
    //-PU
    FillHistPUSys(histname,value,this_weight,n_bin,x_min,x_max);
    //-PartonShower
    FillHistPSSys(histname,value,this_weight,n_bin,x_min,x_max);
    //prefire//
    FillHistPrefireSys(histname,value,this_weight,n_bin,x_min,x_max);
    //btag
    FillHistBtag(histname,value,this_weight,n_bin,x_min,x_max);
    //zptweight
    FillHistZptWeight(histname,value,this_weight,n_bin,x_min,x_max);
    ///---EffTool--//
    //electronID//
    FillHistElectronID(histname,value,this_weight,n_bin,x_min,x_max);
    //electronRECO
    FillHistElectronRECO(histname,value,this_weight,n_bin,x_min,x_max);
    //electronTrigger
    FillHistElectronTrigger(histname,value,this_weight,n_bin,x_min,x_max);

    //muonID
    FillHistMuonID(histname,value,this_weight,n_bin,x_min,x_max);
    //muonRECO
    FillHistMuonRECO(histname,value,this_weight,n_bin,x_min,x_max);
    //MuonTrigger
    FillHistMuonTrigger(histname,value,this_weight,n_bin,x_min,x_max);
    //MuonTrk
    FillHistMuonTrk(histname,value,this_weight,n_bin,x_min,x_max);
  }

}

void JHAnalyzerBase::FillHistWeightBase(TString histname,double value,double this_weight,int n_bin,double x_min,double x_max){
  //Nominal//
  AnalyzerCore::FillHist(histname+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
  
  if(IsDATA) return;
  if(!runSys) return;
  //-PU
  FillHistPUSys(histname,value,this_weight,n_bin,x_min,x_max);
  //-PartonShower
  FillHistPSSys(histname,value,this_weight,n_bin,x_min,x_max);
  //prefire//
  FillHistPrefireSys(histname,value,this_weight,n_bin,x_min,x_max);
  //btag
  FillHistBtag(histname,value,this_weight,n_bin,x_min,x_max);
  //zptweight
  FillHistZptWeight(histname,value,this_weight,n_bin,x_min,x_max);
  ///---EffTool--//
  //electronID//
  FillHistElectronID(histname,value,this_weight,n_bin,x_min,x_max);
  //electronRECO
  FillHistElectronRECO(histname,value,this_weight,n_bin,x_min,x_max);
  //electronTrigger
  FillHistElectronTrigger(histname,value,this_weight,n_bin,x_min,x_max);
  
  //muonID
  FillHistMuonID(histname,value,this_weight,n_bin,x_min,x_max);
  //muonRECO
  FillHistMuonRECO(histname,value,this_weight,n_bin,x_min,x_max);
  //MuonTrigger
  FillHistMuonTrigger(histname,value,this_weight,n_bin,x_min,x_max);
  //MuonTrk
  FillHistMuonTrk(histname,value,this_weight,n_bin,x_min,x_max);
}





void JHAnalyzerBase::FillReservedHistMomentumVariations(){
 for(const auto &arg : vReserveHist){    
    TString histname="SYS/"+arg.histname+"/"+sysname_current+"/0/"+sysdir_current;
    double value=arg.value;
    double this_weight=arg.weight;
    int n_bin=arg.n_bin;
    double x_min=arg.x_min;
    double x_max=arg.x_max;   
    AnalyzerCore::FillHist(histname+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
 }
}

void JHAnalyzerBase::FillReservedHistLeptonMomentumVariations(){
 for(const auto &arg : vReserveHist){    
   TString histname="SYS/"+arg.histname+"/"+sysname_current+"/"+sysidx1_current+"/"+sysidx2_current;
    double value=arg.value;
    double this_weight=arg.weight;
    int n_bin=arg.n_bin;
    double x_min=arg.x_min;
    double x_max=arg.x_max;   
    AnalyzerCore::FillHist(histname+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
 }
}
void JHAnalyzerBase::ClearReserveHist(){
  vReserveHist.clear();
}

void JHAnalyzerBase::SetSys(MomentumVar _sys){
  sysname_current=_sys.name;
  //sysdir_current=_sys.dir;
  sysidx1_current="0";
  sysidx2_current=_sys.dir;
  /*
  if(_sys.muonscale!=0){
    //AllMuons=ScaleMuons(AllMuons_raw,_sys.muonscale);
    AllMuons=ScaleMuons(AllMuons_roch,_sys.muonscale);
    std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
    PuppiMET=UpdateMETByMuonScale(PuppiMET_roch,_sys.muonscale); 
    //AllElectrons=AllElectrons_raw;//Collection with nominal 
    AllElectrons=AllElectrons_roch;//Collection with nominal 
    AllJets=AllJets_raw;
  }
  else if(_sys.electronscale!=0){ 
    //AllMuons=AllMuons_raw;
    AllMuons=AllMuons_roch;
    PuppiMET=UpdateMETByElectronScale(PuppiMET_roch,_sys.electronscale); 
    // AllElectrons=ScaleElectrons(AllElectrons_raw,_sys.electronscale);
    AllElectrons=ScaleElectrons(AllElectrons_roch,_sys.electronscale);
    std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
    AllJets=AllJets_raw;
  }
  else if(_sys.jes!=0){
  */
  if(_sys.jes!=0){
    //AllMuons=AllMuons_raw;
    AllMuons=AllMuons_roch;
    //AllElectrons=AllElectrons_raw;
    AllElectrons=AllElectrons_roch;
    AllJets=ScaleJets(AllJets_raw,_sys.jes);
    std::sort(AllJets.begin(), AllJets.end(), PtComparing);
    PuppiMET=UpdateMETByJetScale(PuppiMET_roch,_sys.jes); 
  }
  else if(_sys.jer!=0){
    //AllMuons=AllMuons_raw;
    AllMuons=AllMuons_roch;
    //AllElectrons=AllElectrons_raw;
    AllElectrons=AllElectrons_roch;
    AllJets=SmearJets(AllJets_raw,_sys.jer);
    std::sort(AllJets.begin(), AllJets.end(), PtComparing);
    PuppiMET=UpdateMETByJetSmear(PuppiMET_roch,_sys.jer);
  }
  else if(_sys.met!=0){
    //AllMuons=AllMuons_raw;
    AllMuons=AllMuons_roch;
    //AllElectrons=AllElectrons_raw;
    AllElectrons=AllElectrons_roch;
    AllJets=AllJets_raw;
    PuppiMET=GetShiftedMET(_sys.met);
  }
  else{
    cout << "[JHAnalyzerBase::SetSyst] No systematic shift for ->" << sysname_current << endl;
  }


}

void JHAnalyzerBase::SetSys(MuonMomentumVar _sys){
  sysname_current=_sys.name;

  
  AllMuons=MuonMomentumCorrection(AllMuons_raw,_sys.idx1,_sys.idx2);
  //std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
  AllElectrons=AllElectrons_roch;
  AllJets=AllJets_raw;
  PuppiMET=UpdateMETByMuonScale(PuppiMET_roch);
  sysidx1_current=std::to_string(_sys.idx1);
  sysidx2_current=std::to_string(_sys.idx2);
}

void JHAnalyzerBase::SetSys(ElectronMomentumVar _sys){
  sysname_current=_sys.name;
  //sysidx1_current=_sys.idx1;
  //sysidx2_current=_sys.idx2;

  AllMuons=AllMuons_roch;  
  AllElectrons=ElectronEnergyCorrection(AllElectrons_raw,_sys.idx1,_sys.idx2);
  //std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);

  AllJets=AllJets_raw;
  PuppiMET=UpdateMETByElectronScale(PuppiMET_roch);
  sysidx1_current=std::to_string(_sys.idx1);
  sysidx2_current=std::to_string(_sys.idx2);  
}



void JHAnalyzerBase::InitAllObjects(){
  //cout << "[JHAnalyzerBase::InitAllObjects] init to nominal objects" << endl;
  AllMuons_raw=GetAllMuons();
  AllMuons_roch=MuonMomentumCorrection(AllMuons_raw);
  AllMuons=AllMuons_roch;
  //std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);//no need to sort again
  AllElectrons_raw=GetAllElectrons();
  AllElectrons_roch=ElectronEnergyCorrection(AllElectrons_raw);
  AllElectrons=AllElectrons_roch;
  //std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
  AllJets_raw=GetAllJets();
  AllJets=AllJets_raw;
  std::sort(AllJets.begin(), AllJets.end(), PtComparing);
  
  InitMET();
}

void JHAnalyzerBase::InitMET(){
  TLorentzVector PuppiMET_raw;
  PuppiMET_raw.SetPtEtaPhiM(PuppiMET_Type1_pt,0.,PuppiMET_Type1_phi,0.);
  PuppiMET_roch = UpdateMETByMuonRochCorr(PuppiMET_raw,AllMuons_raw);
  PuppiMET=PuppiMET_roch;
}




TLorentzVector JHAnalyzerBase::UpdateMETByMuonRochCorr(const TLorentzVector &met_orig, const vector<Muon> &muons){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& muon : muons){
    px_orig+= muon.MiniAODPt()*TMath::Cos(muon.Phi());
    py_orig+= muon.MiniAODPt()*TMath::Sin(muon.Phi());

    px_corrected += muon.Px();
    py_corrected += muon.Py();
    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}


TLorentzVector JHAnalyzerBase::UpdateMETByMuonElectronRochCorr(const TLorentzVector &met_orig, const vector<Muon> &muons,const vector<Electron> &electrons){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& muon : muons){
    px_orig+= muon.MiniAODPt()*TMath::Cos(muon.Phi());
    py_orig+= muon.MiniAODPt()*TMath::Sin(muon.Phi());

    px_corrected += muon.Px();
    py_corrected += muon.Py();
    
  }
  for(const auto& electron : electrons){
    px_orig+= electron.UncorrPt()*TMath::Cos(electron.Phi());
    py_orig+= electron.UncorrPt()*TMath::Sin(electron.Phi());

    px_corrected += electron.Px();
    py_corrected += electron.Py();
    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}


TLorentzVector JHAnalyzerBase::UpdateMETByMuonScale(const TLorentzVector &met_orig, int sys){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& muon : AllMuons_raw){
    px_orig+= muon.Px();
    py_orig+= muon.Py();

    px_corrected += muon.MomentumShift(sys)*TMath::Cos(muon.Phi());
    py_corrected += muon.MomentumShift(sys)*TMath::Sin(muon.Phi());
    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}

TLorentzVector JHAnalyzerBase::UpdateMETByMuonScale(const TLorentzVector &met_orig){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& muon : AllMuons_roch){//nominal rochcorr
    px_orig+= muon.Px();
    py_orig+= muon.Py();
  }
  for(const auto& muon : AllMuons){//after shift
    px_corrected += muon.Px();
    py_corrected += muon.Py();
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}


TLorentzVector JHAnalyzerBase::UpdateMETByElectronScale(const TLorentzVector &met_orig, int sys){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& electron : AllElectrons_raw){
    px_orig+= electron.Px();
    py_orig+= electron.Py();

    px_corrected += electron.Px()*electron.EnShift(sys);
    py_corrected += electron.Py()*electron.EnShift(sys);

    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}
TLorentzVector JHAnalyzerBase::UpdateMETByElectronScale(const TLorentzVector &met_orig){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& electron : AllElectrons_roch){
    px_orig+= electron.Px();
    py_orig+= electron.Py();
  }
  for(const auto& electron : AllElectrons){
    px_corrected += electron.Px();
    py_corrected += electron.Py();
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}


TLorentzVector JHAnalyzerBase::UpdateMETByJetScale(const TLorentzVector &met_orig, int sys){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& jet : AllJets_raw){
    px_orig+= jet.Px();
    py_orig+= jet.Py();

    px_corrected += jet.Px()*jet.EnShift(sys);
    py_corrected += jet.Py()*jet.EnShift(sys);

    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}

TLorentzVector JHAnalyzerBase::UpdateMETByJetSmear(const TLorentzVector &met_orig, int sys){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& jet : AllJets_raw){
    px_orig+= jet.Px();
    py_orig+= jet.Py();

    px_corrected += jet.Px()*jet.ResShift(sys);
    py_corrected += jet.Py()*jet.ResShift(sys);

    
  }
  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}

TLorentzVector JHAnalyzerBase::GetShiftedMET(int sys){
  //MET shift by Uncluster part
  //UnclusteredEnUp=10, UnclusteredEnDown=11,
  int idx=-1;
  if(sys==1){
    idx=10;
  }
  else if (sys==-1){
    idx=11;
  }
  else{
    cout << "no MET shift for sys==" << sys << endl;
  }
  double pt=PuppiMET_Type1_pt_shifts->at(idx);
  double phi=PuppiMET_Type1_phi_shifts->at(idx);
  TLorentzVector this_met;
  this_met.SetPtEtaPhiM(pt,0,phi,0);
  return this_met;
}



void JHAnalyzerBase::SetupSingleLeptonChannel(){

  //common setup
  MuonID="POGMedium";
  MuonRecoSFKey="Muon_RECO";
  MuonIDSFKey="Muon_MediumID_trkIsoLoose";
  MuonTrkSFKey="Muon_Tracking";
  MuonDZSFKey="";

  ElectronID="passMediumID";
  ElectronRecoSFKey="Electron_RECO";
  ElectronIDSFKey="Electron_MediumID";
  ElectronDZSFKey="";

  if(DataYear==2016){
    if (DataEra=="2016preVFP"){
      MuonID="POGMedium_hip";
    }
    MuonTriggerNames = {"HLT_IsoMu24_v","HLT_IsoTkMu24_v"};
    MuonTriggerSFKeys={"IsoMu24_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 27.;
    TriggerSafeCut_muon2 = -1.;


    ElectronTriggerNames = {"HLT_Ele27_WPTight_Gsf_v"};
    ElectronTriggerSFKeys = {"Ele27_MediumID"};
    TriggerSafeCut_electron1 = 30.;
    TriggerSafeCut_electron2 = -1.;


  }
  else if(DataYear==2017){
    MuonTriggerNames = {"HLT_IsoMu24_v","HLT_IsoMu27_v"};
    MuonTriggerSFKeys={"IsoMu24_MediumID_trkIsoLoose","IsoMu27_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 30.;
    TriggerSafeCut_muon2 = -1.;

    ElectronTriggerNames = {"HLT_Ele27_WPTight_Gsf_v","HLT_Ele32_WPTight_Gsf_v"};
    ElectronTriggerSFKeys = {"Ele27_MediumID","Ele32_MediumID"};
    TriggerSafeCut_electron1 = 35.;
    TriggerSafeCut_electron2 = -1.;

  }

  else if(DataYear==2018){
    MuonTriggerNames = {"HLT_IsoMu24_v"};
    MuonTriggerSFKeys={"IsoMu24_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 27.;
    TriggerSafeCut_muon2 = -1.;

    ElectronTriggerNames = {"HLT_Ele28_WPTight_Gsf_v","HLT_Ele32_WPTight_Gsf_v"};
    ElectronTriggerSFKeys = {"Ele28_MediumID","Ele32_MediumID"};
    TriggerSafeCut_electron1 = 35.;
    TriggerSafeCut_electron2 = -1.;


  }
  SetIsDoubleLeptonTrigger();
  PrintSFStructure();
}

void JHAnalyzerBase::SetupDiLeptonChannel(){
  cout << "[SetupDiLeptonChannel] " << DataYear << "  " << endl;
  cout << "[SetupDiLeptonChannel] " << GetEra() << "  " << endl;

  //common setup
  MuonID="POGMedium";
  MuonRecoSFKey="Muon_RECO";
  MuonIDSFKey="Muon_MediumID_trkIsoLoose";
  MuonTrkSFKey="Muon_Tracking";
  MuonDZSFKey="";

  ElectronID="passMediumID";
  ElectronRecoSFKey="Electron_RECO";
  ElectronIDSFKey="Electron_MediumID";
  ElectronDZSFKey="";


  if(DataYear==2016){
    ElectronDZSFKey="DZ_MediumID";
    if (DataEra=="2016preVFP"){
      MuonID="POGMedium_hip";
    }else{
      MuonDZSFKey="DZ_MediumID_trkIsoLoose";
    }
    MuonTriggerNames={"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v","HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v","HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"};
    MuonTriggerSFKeys={"Mu17Leg1_MediumID_trkIsoLoose","Mu8Leg2_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 20.;
    TriggerSafeCut_muon2 = 11.;
    


    ElectronTriggerNames = {"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"};
    ElectronTriggerSFKeys = {"Ele23Leg1_MediumID","Ele12Leg2_MediumID"};
    TriggerSafeCut_electron1 = 26.;
    TriggerSafeCut_electron2 = 15.;
    ElectronDZSFKey="DZ_MediumID";

  }
  else if(DataYear==2017){
    MuonTriggerNames = {"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v"};
    MuonTriggerSFKeys={"Mu17Leg1_MediumID_trkIsoLoose","Mu8Leg2_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 20.;
    TriggerSafeCut_muon2 = 11.;
    MuonDZSFKey="DZ_MediumID_trkIsoLoose";

    ElectronTriggerNames = {"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"};
    ElectronTriggerSFKeys = {"Ele23Leg1_MediumID","Ele12Leg2_MediumID"};
    TriggerSafeCut_electron1 = 26.;
    TriggerSafeCut_electron2 = 15.;

  }

  else if(DataYear==2018){
    MuonTriggerNames = {"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v"};
    MuonTriggerSFKeys={"Mu17Leg1_MediumID_trkIsoLoose","Mu8Leg2_MediumID_trkIsoLoose"};
    TriggerSafeCut_muon1 = 20.;
    TriggerSafeCut_muon2 = 11.;
    MuonDZSFKey="DZ_MediumID_trkIsoLoose";

    ElectronTriggerNames = {"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"};
    ElectronTriggerSFKeys = {"Ele23Leg1_MediumID","Ele12Leg2_MediumID"};
    TriggerSafeCut_electron1 = 26.;
    TriggerSafeCut_electron2 = 15.;


  }

  SetIsDoubleLeptonTrigger();
  cout << "[SetupDiLeptonChannel] " << DataYear << "  " << endl;
  PrintSFStructure();

    
}

void JHAnalyzerBase::PrintSFStructure(){
  cout << "MuonRecoSFKey" << endl;
  fEff->PrintStructure(MuonRecoSFKey);
  cout << "MuonIDSFKey" << endl;
  fEff->PrintStructure(MuonIDSFKey);
  cout << "MuonTrkSFKey" << endl;
  fEff->PrintStructure(MuonTrkSFKey);
  cout << "MuonTriggerSFKeys[0]" << endl;
  fEff->PrintStructure(MuonTriggerSFKeys[0]);

  cout << "ElectronRecoSFKey" << endl;
  fEff->PrintStructure(ElectronRecoSFKey);
  cout << "ElectronIDSFKey" << endl;
  fEff->PrintStructure(ElectronIDSFKey);
  cout << "ElectronTriggerSFKeys[0]" << endl;
  fEff->PrintStructure(ElectronTriggerSFKeys[0]);
}

void JHAnalyzerBase::SetIsDoubleLeptonTrigger(){
  IsDoubleMuonTrigger=false;
  if( TriggerSafeCut_muon2 > 0. && TriggerSafeCut_muon1 > 0. ){
    IsDoubleMuonTrigger=true;
  }
  IsDoubleElectronTrigger=false;
  if( TriggerSafeCut_electron2 > 0. && TriggerSafeCut_electron1 >0. ){
    IsDoubleElectronTrigger=true;
  }
  cout << "IsDoubleMuonTrigger=" << IsDoubleMuonTrigger << endl; 
  cout << "IsDoubleElectronTrigger=" << IsDoubleElectronTrigger << endl; 

  cout << "---Use Following Muon triggerkeys ---" << endl;
  for (const auto& name : MuonTriggerSFKeys){
    cout << name << endl;
  }

  cout << "---Use Following Electron triggerkeys ---" << endl;
  for (const auto& name : ElectronTriggerSFKeys){
    cout << name << endl;
  }
  
  //----OR Trigger----//
  IsORMuonTrigger=false;
  if(!IsDoubleMuonTrigger){// SingleMuonTrigger
    if(MuonTriggerNames.size()==2  && MuonTriggerSFKeys.size()==2) IsORMuonTrigger=true;
  }
  
  IsORElectronTrigger=false;
  if(!IsDoubleElectronTrigger){// SingleMuonTrigger
    if(ElectronTriggerNames.size()==2  && ElectronTriggerSFKeys.size()==2) IsORElectronTrigger=true;
  }
  
  cout << "IsORMuonTrigger=" << IsORMuonTrigger << endl; 
  cout << "IsORElectronTrigger=" << IsORElectronTrigger << endl; 
}

  //---Get Muon index-base. For SingleMuon Channel
int JHAnalyzerBase::GetIdxSingleMuReco(double ptmin, double etacut, double ptveto){

  unsigned int muonsize = AllMuons.size();
  unsigned int nselected= 0;
  int muonidx=-1;
  //vector<Muon> _vmuons;
  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double eta=AllMuons[i].Eta();
    if(fabs(eta) > etacut) continue;
    double pt=AllMuons[i].Pt();
    if(pt < ptveto) continue;
    bool passLooseID=AllMuons[i].PassID("POGLoose");
    if (!passLooseID) continue;
    bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!passISO) continue;
    //----Loose ID Muon passing pt/eta/iso cut
    nselected+=1;
    if(nselected>1) return -1;
    //--For One selected as prompt lepton--//
    if(pt<ptmin) return -1;
    if(!AllMuons[i].PassID("POGMedium")) return -1;
    muonidx=i;
  }
  if (nselected==0) return -1;
  //---GetSF--//
  vector<int> v_muonidx={muonidx};
  SetMuonSFs(v_muonidx);
  return muonidx;

}
//---Get Muon Object-Base. For SingleMuon Channel.
vector<Muon> JHAnalyzerBase::GetSingleMuReco(double ptmin, double etacut, double ptveto){

  //unsigned int muonsize = AllMuons.size();
  unsigned int nselected= 0;
  vector<Muon> _v_muons;
  //for(unsigned int i = 0 ; i < muonsize; i++ ){
  for(const auto &muon : AllMuons){
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    //double pt=AllMuons[i].Pt();
    if(muon.Pt() < ptveto) continue;
    //bool passLooseID=AllMuons[i].PassID("POGLoose");
    if (!muon.PassID("POGLoose")) continue;
    //bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //----Loose ID Muon passing pt/eta/iso cut
    nselected+=1;
    if(nselected>1) return {};
    //--For One selected as prompt lepton--//
    if(muon.Pt()<ptmin) return {};
    if(!muon.PassID("POGMedium")) return {};
    //muonidx=i;
    _v_muons.push_back(muon);
  }
  if (nselected==0) return {};
  //---GetSF--//
  //vector<int> v_muonidx={muonidx};
  //SetMuonSFs(v_muonidx);
  SetMuonSFs(_v_muons);
  return _v_muons;

}

//---Get Muon ObjectPointer-Base. For SingleMuon Channel.
vector<Lepton*> JHAnalyzerBase::GetPointerSingleMuReco(double ptmin, double etacut, double ptveto){

  //unsigned int muonsize = AllMuons.size();
  unsigned int nselected= 0;
  vector<Lepton*> _v_muons;
  //for(unsigned int i = 0 ; i < muonsize; i++ ){
  for(const auto &muon : AllMuons){
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    //double pt=AllMuons[i].Pt();
    if(muon.Pt() < ptveto) continue;
    //bool passLooseID=AllMuons[i].PassID("POGLoose");
    if (!muon.PassID("POGLoose")) continue;
    //bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //----Loose ID Muon passing pt/eta/iso cut
    nselected+=1;
    if(nselected>1) return {};
    //--For One selected as prompt lepton--//
    if(muon.Pt()<ptmin) return {};
    if(!muon.PassID("POGMedium")) return {};
    //muonidx=i;
    _v_muons.push_back((Lepton*)&muon);
  }
  if (nselected==0) return {};
  //---GetSF--//
  //vector<int> v_muonidx={muonidx};
  //SetMuonSFs(v_muonidx);
  SetMuonSFs(_v_muons);
  return _v_muons;

}



//---Get Muon index-base. For SingleMuon Channel
int JHAnalyzerBase::GetIdxSingleElReco(double ptmin, double etacut, double ptveto){
  unsigned int electronsize = AllElectrons.size();
  unsigned int nselected= 0;
  int electronidx=-1;
  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=AllElectrons[i].Pt();
    if(pt < ptveto) continue;
    double eta=AllElectrons[i].Eta();
    if(fabs(eta) > etacut) continue;
    bool passID=AllElectrons[i].PassID("passLooseID");
    if(!passID) continue;
    nselected+=1;
    if(nselected > 1) return -1;//if # of electron passing ptveto cut > 1, the event cannot pass the selection
    //Now Only 1 electron passing ptvetocut
    if(pt < ptmin) return -1; 
    if (!AllElectrons[i].PassID("passMediumID")) return -1;
    electronidx=i;
  }
  if (nselected==0) return -1;
  vector<int> v_electronidx= {electronidx};
  SetElectronSFs(v_electronidx);
  return electronidx;
}

//---Get Muon Object-base. For SingleMuon Channel
vector<Electron> JHAnalyzerBase::GetSingleElReco(double ptmin, double etacut, double ptveto){
  vector<Electron> _v_electrons;
  unsigned int nselected= 0;
  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  for(const auto& electron : AllElectrons){
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut) continue;
    //bool passID=AllElectrons[i].PassID("passLooseID");
    if(!electron.PassID("passLooseID")) continue;
    nselected+=1;
    if(nselected > 1) return {};//if # of electron passing ptveto cut > 1, the event cannot pass the selection
    //Now Only 1 electron passing ptvetocut
    if(electron.Pt() < ptmin) return {}; 
    //if (!AllElectrons[i].PassID("passMediumID")) return -1;
    if (electron.PassID("passMediumID")) return {};
    _v_electrons.push_back(electron);
  }
  if (nselected==0) return {};

  SetElectronSFs(_v_electrons);
  return _v_electrons;
}

//---Get Muon ObjectPointer-base. For SingleMuon Channel
vector<Lepton*> JHAnalyzerBase::GetPointerSingleElReco(double ptmin, double etacut, double ptveto){
  vector<Lepton*> _v_electrons;
  unsigned int nselected= 0;
  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  for(const auto& electron : AllElectrons){
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut) continue;
    //bool passID=AllElectrons[i].PassID("passLooseID");
    if(!electron.PassID("passLooseID")) continue;
    nselected+=1;
    if(nselected > 1) return {};//if # of electron passing ptveto cut > 1, the event cannot pass the selection
    //Now Only 1 electron passing ptvetocut
    if(electron.Pt() < ptmin) return {}; 
    //if (!AllElectrons[i].PassID("passMediumID")) return -1;
    if (electron.PassID("passMediumID")) return {};
    _v_electrons.push_back((Lepton*)&electron);
  }
  if (nselected==0) return {};

  SetElectronSFs(_v_electrons);
  return _v_electrons;
}


//Get Muons index-base. For DiMuonChannel
vector<int> JHAnalyzerBase::GetIdxDiMuReco(double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<int> v_muonidx;
  unsigned int muonsize = AllMuons.size();
  unsigned int npassveto=0;
  unsigned int npasstight=0;


  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double pt=AllMuons[i].Pt();
    if(pt < ptveto) continue;
    double eta=AllMuons[i].Eta();
    if(fabs(eta) > etacut) continue;
    bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!passISO) continue;
    bool passVetoID=AllMuons[i].PassID("POGLoose");
    if (!passVetoID) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    //Now only 2 muons passing ptveto cut
    bool passID=AllMuons[i].PassID("POGMedium");    
    if (!passID) continue; // the muons must pass ID
    npasstight+=1;
    v_muonidx.push_back(i);
    
  }
  if(npasstight<2) return {};
  if(AllMuons[v_muonidx[0]].Pt() < ptmin1) return {};
  if(AllMuons[v_muonidx[1]].Pt() < ptmin2) return {};
  SetMuonSFs(v_muonidx);
  return v_muonidx;
}
//--GetMuons object-base For DiMuonChannel
vector<Muon> JHAnalyzerBase::GetDiMuReco(double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<Muon> _v_muons;
  unsigned int npassveto=0;
  unsigned int npasstight=0;


  for(const auto& muon : AllMuons){
    //double pt=AllMuons[i].Pt();
    if(muon.Pt() < ptveto) continue;
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    //bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //bool passVetoID=AllMuons[i].PassID("POGLoose");
    if (!muon.PassID("POGLoose")) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    //Now only 2 muons passing ptveto cut
    //bool passID=AllMuons[i].PassID("POGMedium");    
    if (!muon.PassID("POGMedium")) continue; // the muons must pass ID for main selection
    npasstight+=1;
    _v_muons.push_back(muon);
  }

  if(npasstight<2) return {};
  if(_v_muons[0].Pt() < ptmin1) return {};
  if(_v_muons[1].Pt() < ptmin2) return {};

  /*
  for(const auto& muon : AllMuons){                                                                                                                          
    if(muon.Pt() < 25) continue;
    if(fabs(muon.Eta()) > etacut) continue;
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;                                                                                            
    if (!muon.PassID("POGMedium")) continue; // the muons must pass ID for main selection
    _v_muons.push_back(muon);
  }
  */
  SetMuonSFs(_v_muons);
  return _v_muons;
}

//--GetMuons objectPointer-base For DiMuonChannel
vector<Lepton*> JHAnalyzerBase::GetPointerDiMuReco(double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<Lepton*> _v_muons;
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  //for(unsigned int i = 0 ; i < muonsize; i++ ){
  for(const auto& muon : AllMuons){
    //double pt=AllMuons[i].Pt();
    if(muon.Pt() < ptveto) continue;
    //double eta=AllMuons[i].Eta();
    if(fabs(muon.Eta()) > etacut) continue;
    //bool passISO=AllMuons[i].PassSelector(Muon::Selector::TkIsoLoose);
    if (!muon.PassSelector(Muon::Selector::TkIsoLoose)) continue;
    //bool passVetoID=AllMuons[i].PassID("POGLoose");
    if (!muon.PassID("POGLoose")) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    //Now only 2 muons passing ptveto cut
    //bool passID=AllMuons[i].PassID("POGMedium");    
    if (!muon.PassID("POGMedium")) continue; // the muons must pass ID for main selection
    npasstight+=1;
    _v_muons.push_back((Lepton*)&muon);
  }
  if(npasstight<2) return {};
  if(_v_muons[0]->Pt() < ptmin1) return {};
  if(_v_muons[1]->Pt() < ptmin2) return {};
  SetMuonSFs(_v_muons);
  return _v_muons;
}

//Get Electrons index-base. For DiElectron Channel
vector<int> JHAnalyzerBase::GetIdxDiElReco(double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<int> v_electronidx;
  unsigned int electronsize = AllElectrons.size();
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=AllElectrons[i].Pt();
    if(pt < ptveto) continue;
    double eta=AllElectrons[i].Eta();
    if(fabs(eta) > etacut) continue;
    bool passVetoID=AllElectrons[i].PassID("passLooseID");
    if (!passVetoID) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    ///---Now we have only 2 electrons passing ptveto cut
    bool passID=AllElectrons[i].PassID("passMediumID");
    if (!passID) continue;
    npasstight+=1;
    v_electronidx.push_back(i);
  }
  if(npasstight<2) return {};
  if(AllElectrons[v_electronidx[0]].Pt() < ptmin1) return {};
  if(AllElectrons[v_electronidx[1]].Pt() < ptmin2) return {};
  SetElectronSFs(v_electronidx);
  return v_electronidx;
}

//--Get Electrons Obejct-base. For DiElectron Channel
vector<Electron> JHAnalyzerBase::GetDiElReco(double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<Electron> _v_electrons;
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  for(const auto& electron : AllElectrons){
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut) continue;
    //bool passVetoID=AllElectrons[i].PassID("passLooseID");
    if (!electron.PassID("passLooseID")) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    ///---Now we have only 2 electrons passing ptveto cut
    //bool passID=AllElectrons[i].PassID("passMediumID");
    if (!electron.PassID("passMediumID")) continue;
    npasstight+=1;
    _v_electrons.push_back(electron);
  }
  if(npasstight<2) return {};
  if(_v_electrons[0].Pt() < ptmin1) return {};
  if(_v_electrons[1].Pt() < ptmin2) return {};
  SetElectronSFs(_v_electrons);
  return _v_electrons;
}

//--Get Electrons ObejctPointer-base. For DiElectron Channel
vector<Lepton*> JHAnalyzerBase::GetPointerDiElReco(double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<Lepton*> _v_electrons;
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  //for(unsigned int i = 0 ; i < electronsize; i++ ){
  for(const auto& electron : AllElectrons){
    //double pt=AllElectrons[i].Pt();
    if(electron.Pt() < ptveto) continue;
    //double eta=AllElectrons[i].Eta();
    if(fabs(electron.Eta()) > etacut) continue;
    //bool passVetoID=AllElectrons[i].PassID("passLooseID");
    if (!electron.PassID("passLooseID")) continue;
    npassveto+=1;
    if(npassveto>2) return {};
    ///---Now we have only 2 electrons passing ptveto cut
    //bool passID=AllElectrons[i].PassID("passMediumID");
    if (!electron.PassID("passMediumID")) continue;
    npasstight+=1;
    _v_electrons.push_back((Lepton*)&electron);
  }
  if(npasstight<2) return {};
  if(_v_electrons[0]->Pt() < ptmin1) return {};
  if(_v_electrons[1]->Pt() < ptmin2) return {};
  SetElectronSFs(_v_electrons);
  return _v_electrons;
}

//---GetTightJet index base
vector<int> JHAnalyzerBase::GetIdxTightJet(const vector<Lepton> &v_tightlep, double ptmin, double etacut, TString JetID ){
  vector<int> v_jetidx;
  unsigned int jetsize = AllJets.size();
  for(unsigned int i=0; i < jetsize; i++){
    if(AllJets[i].Pt() < ptmin) continue;
    if(fabs(AllJets[i].Eta()) > etacut) continue;
    if(!AllJets[i].PassID(JetID)) continue;
    //--Lepton Cleaning--//
    bool HasCloseLep=false;
    for(const auto& lep : v_tightlep){
      if (AllJets[i].DeltaR(lep)<0.4){
	HasCloseLep=true;
	break;
      }
    }
    if(HasCloseLep)continue;
    //--end lepton cleaning--//
    v_jetidx.push_back(i);
  }
  SetBtagSF(v_jetidx);
  return v_jetidx;
}
//---Get TightJet Object base
vector<Jet> JHAnalyzerBase::GetTightJet(const vector<Lepton> &v_tightlep, double ptmin, double etacut, TString JetID ){
  vector<Jet> v_tightjet;
  for(const auto& jet : AllJets){
    if(jet.Pt() < ptmin) continue;
    if(fabs(jet.Eta()) > etacut) continue;
    if(!jet.PassID(JetID)) continue;
    //--Lepton Cleaning--//
    bool HasCloseLep=false;
    for(const auto& lep : v_tightlep){
      if (jet.DeltaR(lep)<0.4){
	HasCloseLep=true;
	break;
      }
    }
    if(HasCloseLep)continue;
    //--end lepton cleaning--//
    v_tightjet.push_back(jet);
  }
  SetBtagSF(v_tightjet);
  return v_tightjet;
}

//---Get TightJet ObjectPointer base
vector<Jet*> JHAnalyzerBase::GetPointerTightJet(const vector<Lepton*> &v_tightlep, double ptmin, double etacut, TString JetID ){
  vector<Jet*> v_tightjet;
  vector<Jet> v_jetobj;
  for(const auto& jet : AllJets){
    if(jet.Pt() < ptmin) continue;
    if(fabs(jet.Eta()) > etacut) continue;
    if(!jet.PassID(JetID)) continue;
    //--Lepton Cleaning--//
    bool HasCloseLep=false;
    for(const auto& lep : v_tightlep){
      if (lep->DeltaR(jet)<0.4){
	HasCloseLep=true;
	break;
      }
    }
    if(HasCloseLep)continue;
    //--end lepton cleaning--//
    v_tightjet.push_back((Jet*)&jet);
    v_jetobj.push_back(jet);
  }
  SetBtagSF(v_jetobj);
  return v_tightjet;
}


//--Get BJet index base
vector<int> JHAnalyzerBase::GetIdxBJet(const vector<int> &v_TightjetIdx){
  vector<int> v_bjetidx;
  for(const auto& i : v_TightjetIdx){
    double btagscore=AllJets[i].GetTaggerResult(JetTagging::DeepJet);
    if(btagscore < btagcut) continue;
    v_bjetidx.push_back(i);
  }
  return v_bjetidx;
}
//--Get BJet Object base
vector<Jet> JHAnalyzerBase::GetBJet(const vector<Jet> &v_Tightjet){
  vector<Jet> v_bjet;
  for(const auto& jet : v_Tightjet){
    double btagscore=jet.GetTaggerResult(JetTagging::DeepJet);
    if(btagscore < btagcut) continue;
    v_bjet.push_back(jet);
  }
  return v_bjet;
}

//--Get BJet ObjectPointer base
vector<Jet*> JHAnalyzerBase::GetPointerBJet(const vector<Jet*> &v_Tightjet){
  vector<Jet*> v_bjet;
  for(const auto& jet : v_Tightjet){
    double btagscore=jet->GetTaggerResult(JetTagging::DeepJet);
    if(btagscore < btagcut) continue;
    v_bjet.push_back(jet);
  }
  return v_bjet;
}

void JHAnalyzerBase::SetBtagSF(const vector<int> &v_jetidx){
  //r_SystUpLTagUnCorr
  vector<Jet> v_tightjet;
  for(const auto& i : v_jetidx){
    v_tightjet.push_back(AllJets[i]);
  }
  btagsf = mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp);
  if(runSys){
    r_SystUpLTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpLTagCorr")/btagsf;
    r_SystDownLTagCorr   =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownLTagCorr")/btagsf;
    r_SystUpLTagUnCorr   =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpLTagUnCorr")/btagsf;
    r_SystDownLTagUnCorr =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownLTagUnCorr")/btagsf;
    r_SystUpHTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpHTagCorr")/btagsf;
    r_SystDownHTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownHTagCorr")/btagsf;
    r_SystUpHTagUnCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpHTagUnCorr")/btagsf;
    r_SystDownHTagUnCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownHTagUnCorr")/btagsf;
  }
}

void JHAnalyzerBase::SetBtagSF(const vector<Jet> &v_tightjet){

  btagsf = mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp);
  if(runSys){
    r_SystUpLTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpLTagCorr")/btagsf;
    r_SystDownLTagCorr   =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownLTagCorr")/btagsf;
    r_SystUpLTagUnCorr   =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpLTagUnCorr")/btagsf;
    r_SystDownLTagUnCorr =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownLTagUnCorr")/btagsf;
    r_SystUpHTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpHTagCorr")/btagsf;
    r_SystDownHTagCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownHTagCorr")/btagsf;
    r_SystUpHTagUnCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystUpHTagUnCorr")/btagsf;
    r_SystDownHTagUnCorr     =mcCorr->GetBTaggingReweight_1a(v_tightjet, jtp,"SystDownHTagUnCorr")/btagsf;
  }
}

void JHAnalyzerBase::SetMuonSFs(const vector<int> &v_muonidx){
  SetMuonRecoSF(v_muonidx);
  SetMuonIDSF(v_muonidx);
  SetMuonTrkSF(v_muonidx);
  SetMuonTriggerSF(v_muonidx);
}

void JHAnalyzerBase::SetMuonSFs(const vector<Muon> &v_muon){
  vector<Lepton*> v_lepton;
  for(const auto& muon : v_muon){
    v_lepton.push_back((Lepton*)&muon);
  }
  SetMuonRecoSF(v_lepton);
  SetMuonIDSF(v_lepton);
  SetMuonTrkSF(v_lepton);
  SetMuonTriggerSF(v_lepton);
}

void JHAnalyzerBase::SetMuonSFs(const vector<Lepton*> &v_lepton){
  SetMuonRecoSF(v_lepton);
  SetMuonIDSF(v_lepton);
  SetMuonTrkSF(v_lepton);
  SetMuonTriggerSF(v_lepton);
}

void JHAnalyzerBase::SetElectronSFs(const vector<int> &v_electronidx){
  SetElectronRecoSF(v_electronidx);
  SetElectronIDSF(v_electronidx);
  SetElectronTriggerSF(v_electronidx);
}

void JHAnalyzerBase::SetElectronSFs(const vector<Electron> &v_electron){
  vector<Lepton*> v_lepton;
  for(const auto& electron : v_electron){
    v_lepton.push_back((Lepton*)&electron);
  }
  SetElectronRecoSF(v_lepton);
  SetElectronIDSF(v_lepton);
  SetElectronTriggerSF(v_lepton);
}

void JHAnalyzerBase::SetElectronSFs(const vector<Lepton*> &v_lepton){
  SetElectronRecoSF(v_lepton);
  SetElectronIDSF(v_lepton);
  SetElectronTriggerSF(v_lepton);
}
void JHAnalyzerBase::SetMuonRecoSF(const vector<int> &v_muonidx){

  unsigned int setsize = w_MuonRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonRECO[iset][imem]=1;
      for(const auto& muonidx : v_muonidx){
	w_MuonRECO[iset][imem]*=fEff->GetEfficiencySF(MuonRecoSFKey,(Lepton *)&AllMuons[muonidx],iset,imem);
      }
      r_MuonRECO[iset][imem]= w_MuonRECO[0][0] ? w_MuonRECO[iset][imem]/w_MuonRECO[0][0] : 0;
    }
  }
}
void JHAnalyzerBase::SetMuonRecoSF(const vector<Lepton*> &v_muon){

  unsigned int setsize = w_MuonRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonRECO[iset][imem]=1;
      for(const auto& muon : v_muon){
	w_MuonRECO[iset][imem]*=fEff->GetEfficiencySF(MuonRecoSFKey,(Lepton *)muon,iset,imem);
      }
      r_MuonRECO[iset][imem]= w_MuonRECO[0][0] ? w_MuonRECO[iset][imem]/w_MuonRECO[0][0] : 0;
    }
  }
}


void JHAnalyzerBase::SetElectronRecoSF(const vector<int> &v_electronidx){
  unsigned int setsize = w_ElectronRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_ElectronRECO[iset][imem]=1;
      for(const auto& electronidx : v_electronidx){
	w_ElectronRECO[iset][imem]*=fEff->GetEfficiencySF(ElectronRecoSFKey,(Lepton *)&AllElectrons[electronidx],iset,imem);
      }
      r_ElectronRECO[iset][imem]= w_ElectronRECO[0][0] ? w_ElectronRECO[iset][imem]/w_ElectronRECO[0][0] : 0;
    }
  }
}

void JHAnalyzerBase::SetElectronRecoSF(const vector<Lepton*> &v_electron){
  unsigned int setsize = w_ElectronRECO.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronRECO[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_ElectronRECO[iset][imem]=1;
      for(const auto& electron : v_electron){
	w_ElectronRECO[iset][imem]*=fEff->GetEfficiencySF(ElectronRecoSFKey,(Lepton *)electron,iset,imem);
      }
      r_ElectronRECO[iset][imem]= w_ElectronRECO[0][0] ? w_ElectronRECO[iset][imem]/w_ElectronRECO[0][0] : 0;
    }
  }
}

void JHAnalyzerBase::SetMuonIDSF(const vector<int> &v_muonidx){
  unsigned int setsize = w_MuonID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonID[iset][imem]=1;
      for(const auto& muonidx : v_muonidx){
	w_MuonID[iset][imem]*=fEff->GetEfficiencySF(MuonIDSFKey,(Lepton *)&AllMuons[muonidx],iset,imem);
      }
      r_MuonID[iset][imem]= w_MuonID[0][0] ? w_MuonID[iset][imem]/w_MuonID[0][0] : 0;
    }
  }
}

void JHAnalyzerBase::SetMuonIDSF(const vector<Lepton*> &v_muon){
  unsigned int setsize = w_MuonID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonID[iset][imem]=1;
      for(const auto& muon : v_muon){
	w_MuonID[iset][imem]*=fEff->GetEfficiencySF(MuonIDSFKey,(Lepton *)muon,iset,imem);
      }
      r_MuonID[iset][imem]= w_MuonID[0][0] ? w_MuonID[iset][imem]/w_MuonID[0][0] : 0;
    }
  }
}


void JHAnalyzerBase::SetElectronIDSF(const vector<int> &v_electronidx){
  unsigned int setsize = w_ElectronID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_ElectronID[iset][imem]=1;
      for(const auto& electronidx : v_electronidx){
	w_ElectronID[iset][imem]*=fEff->GetEfficiencySF(ElectronIDSFKey,(Lepton *)&AllElectrons[electronidx],iset,imem);
      }
      r_ElectronID[iset][imem]= w_ElectronID[0][0] ? w_ElectronID[iset][imem]/w_ElectronID[0][0] : 0;
    }
  }
}


void JHAnalyzerBase::SetElectronIDSF(const vector<Lepton*> &v_electron){
  unsigned int setsize = w_ElectronID.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronID[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_ElectronID[iset][imem]=1;
      for(const auto& electron : v_electron){
	w_ElectronID[iset][imem]*=fEff->GetEfficiencySF(ElectronIDSFKey,(Lepton *)electron,iset,imem);
      }
      r_ElectronID[iset][imem]= w_ElectronID[0][0] ? w_ElectronID[iset][imem]/w_ElectronID[0][0] : 0;
    }
  }
}

void JHAnalyzerBase::SetMuonTrkSF(const vector<int> &v_muonidx){
  unsigned int setsize = w_MuonTrk.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrk[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonTrk[iset][imem]=1;
      for(const auto& muonidx : v_muonidx){
	w_MuonTrk[iset][imem]*=fEff->GetEfficiencySF(MuonTrkSFKey,(Lepton *)&AllMuons[muonidx],iset,imem);
      }
      r_MuonTrk[iset][imem]=w_MuonTrk[0][0] ? w_MuonTrk[iset][imem]/w_MuonTrk[0][0] : 0;
    }
  }
}


void JHAnalyzerBase::SetMuonTrkSF(const vector<Lepton*> &v_muon){
  unsigned int setsize = w_MuonTrk.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrk[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonTrk[iset][imem]=1;
      for(const auto& muon : v_muon){
	w_MuonTrk[iset][imem]*=fEff->GetEfficiencySF(MuonTrkSFKey,(Lepton *)muon,iset,imem);
      }
      r_MuonTrk[iset][imem]=w_MuonTrk[0][0] ? w_MuonTrk[iset][imem]/w_MuonTrk[0][0] : 0;
    }
  }
}


void JHAnalyzerBase::SetMuonTriggerSF(const vector<int> &v_muonidx){
  //---Make vector whose elements are Lepton pointers
  vector<Lepton*> _v_muons;
  for(const auto& muonidx : v_muonidx){
    _v_muons.push_back((Lepton*)&AllMuons[muonidx] );
  }

  if(!IsDoubleMuonTrigger){
    if(IsORMuonTrigger){
      SetSingleMuonTriggerORSF(_v_muons);
    }
    else{
      SetSingleMuonTriggerSF(_v_muons);
    }
  }
  else{
    SetDoubleMuonTriggerSF(_v_muons);
  }
  
}
void JHAnalyzerBase::SetMuonTriggerSF(const vector<Lepton*> &v_muon){
  if(!IsDoubleMuonTrigger){
    if(IsORMuonTrigger){
      SetSingleMuonTriggerORSF(v_muon);
    }
    else{
      SetSingleMuonTriggerSF(v_muon);
    }
  }
  else{
    SetDoubleMuonTriggerSF(v_muon);
  }

}

void JHAnalyzerBase::SetSingleMuonTriggerSF(const vector<Lepton*> &v_muons){

  unsigned int setsize = w_MuonTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      if(IsORMuonTrigger){
	w_MuonTrigger[iset][imem]=AnalyzerCore::GetLeptonTriggerORSF(ev,MuonTriggerNames,MuonTriggerSFKeys,v_muons,iset,imem,"");
      }else{
	w_MuonTrigger[iset][imem]=AnalyzerCore::GetLeptonTriggerSF(MuonTriggerSFKeys[0],v_muons,iset,imem,"");
      }
      r_MuonTrigger[iset][imem]=w_MuonTrigger[0][0] ? w_MuonTrigger[iset][imem]/w_MuonTrigger[0][0] : 0;
    }
  }
}


void JHAnalyzerBase::SetSingleMuonTriggerORSF(const vector<Lepton*> &v_muons){

  unsigned int setsize = w_MuonTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_MuonTrigger[iset][imem]=AnalyzerCore::GetLeptonTriggerORSF(ev,MuonTriggerNames,MuonTriggerSFKeys,v_muons,iset,imem,"");
      r_MuonTrigger[iset][imem]=w_MuonTrigger[0][0] ? w_MuonTrigger[iset][imem]/w_MuonTrigger[0][0] : 0;
    }
  }
}



void JHAnalyzerBase::SetDoubleMuonTriggerSF(const vector<Lepton*> &v_muons){

  unsigned int setsize = w_MuonTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_MuonTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      //double AnalyzerCore::GetDileptonTriggerSF(TString triggerSF_key0,TString triggerSF_key1,TString DZSF,const vector<Lepton*>& leps,int set,int mem)
      w_MuonTrigger[iset][imem]=AnalyzerCore::GetDileptonTriggerSF(MuonTriggerSFKeys[0],MuonTriggerSFKeys[1],MuonDZSFKey,v_muons,iset,imem);
      r_MuonTrigger[iset][imem]=w_MuonTrigger[0][0] ? w_MuonTrigger[iset][imem]/w_MuonTrigger[0][0] : 0;
    }
  }
}


//

void JHAnalyzerBase::SetElectronTriggerSF(const vector<int> &v_electronidx){
  vector<Lepton*> _v_electrons;
  for(const auto& electronidx : v_electronidx){
    _v_electrons.push_back((Lepton*)&AllElectrons[electronidx] );
  }
  if(!IsDoubleElectronTrigger){
    if(IsORElectronTrigger){
      SetSingleElectronTriggerORSF(_v_electrons);
    }
    else{
      SetSingleElectronTriggerSF(_v_electrons);
    }
  }
  else{
    SetDoubleElectronTriggerSF(_v_electrons);
  }

}


void JHAnalyzerBase::SetElectronTriggerSF(const vector<Lepton*> &v_electron){

  if(!IsDoubleElectronTrigger){
    if(IsORElectronTrigger){
      SetSingleElectronTriggerORSF(v_electron);
    }
    else{
      SetSingleElectronTriggerSF(v_electron);
    }
  }
  else{
    SetDoubleElectronTriggerSF(v_electron);
  }

}

void JHAnalyzerBase::SetSingleElectronTriggerSF(const vector<Lepton*> &v_electrons){

  unsigned int setsize = w_ElectronTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      w_ElectronTrigger[iset][imem]=AnalyzerCore::GetLeptonTriggerSF(ElectronTriggerSFKeys[0],v_electrons,iset,imem,"");
      r_ElectronTrigger[iset][imem]=w_ElectronTrigger[0][0] ? w_ElectronTrigger[iset][imem]/w_ElectronTrigger[0][0] : 0;
    }
  }
}



void JHAnalyzerBase::SetSingleElectronTriggerORSF(const vector<Lepton*> &v_electrons){

  unsigned int setsize = w_ElectronTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      
      w_ElectronTrigger[iset][imem]=AnalyzerCore::GetLeptonTriggerORSF(ev,ElectronTriggerNames,ElectronTriggerSFKeys,v_electrons,iset,imem,"");
      r_ElectronTrigger[iset][imem]=w_ElectronTrigger[0][0] ? w_ElectronTrigger[iset][imem]/w_ElectronTrigger[0][0] : 0;
    }
  }
}



void JHAnalyzerBase::SetDoubleElectronTriggerSF(const vector<Lepton*> &v_electrons){

  unsigned int setsize = w_ElectronTrigger.size();
  for(unsigned int iset=0;iset<setsize;iset++){
    unsigned int memsize = w_ElectronTrigger[iset].size();
    for(unsigned int imem=0;imem<memsize;imem++){
      //double AnalyzerCore::GetDileptonTriggerSF(TString triggerSF_key0,TString triggerSF_key1,TString DZSF,const vector<Lepton*>& leps,int set,int mem)
      w_ElectronTrigger[iset][imem]=AnalyzerCore::GetDileptonTriggerSF(ElectronTriggerSFKeys[0],ElectronTriggerSFKeys[1],ElectronDZSFKey,v_electrons,iset,imem);
      r_ElectronTrigger[iset][imem]=w_ElectronTrigger[0][0] ? w_ElectronTrigger[iset][imem]/w_ElectronTrigger[0][0] : 0;
    }
  }
}




//---For Calc
TLorentzVector JHAnalyzerBase::GetTransverseVector(const TLorentzVector &v){
  // 2nd section of 
  //https://en.wikipedia.org/wiki/Transverse_mass
  //cout << "GetTransverseVector" << endl;
  double px=v.Px();
  double py=v.Py();
  double pz=0.;
  double m =v.M();
  double ee=sqrt(m*m+px*px+py*py);
  TLorentzVector ret;
  ret.SetPxPyPzE(px,py,pz,ee);
  return ret;
}

TLorentzVector JHAnalyzerBase::GetTransverseVector(double pt, double phi){
  //No mass
  double px=pt*cos(phi);
  double py=pt*sin(phi);
  double pz=0.;
  double ee=sqrt(px*px+py*py);
  TLorentzVector ret;
  ret.SetPxPyPzE(px,py,pz,ee);
  return ret;
}
