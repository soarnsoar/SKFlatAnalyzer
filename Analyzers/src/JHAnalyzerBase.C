#include "JHAnalyzerBase.h"

JHAnalyzerBase::JHAnalyzerBase(){

  
  t_InitObj=0;
  t_InitVariable=0;
  t_EventLoop=0;
  t_FillWeightBase=0;
  t_FillMomentumBase=0;

  InitSystematicMomentumVariations();
  AnalyzerCore::SetupEfficiency();
}
void JHAnalyzerBase::initializeAnalyzer(){
  cout << "[JHAnalyzerBase::initializeAnalyzer]DataEra->" << DataEra << endl;
  SetSysStructure();
  InitBtag();
  if(IsDATA){
    ProcessName="Data";
  }
  else{
    ProcessName=MCSample;
  }
}
void JHAnalyzerBase::InitBtag(){
  std::vector<JetTagging::Parameters> jtps;
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Tight, JetTagging::incl, JetTagging::comb) );
  mcCorr->SetJetTaggingParameters(jtps);
  jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  mcCorr->MCCorrection::SetEra(DataEra);
  btagcut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
  cout << "[JHAnalyzerBase::InitBtag]btagcut=" << btagcut << endl;
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
  
  muonscaleUp.muonscale=1;       
  muonscaleUp.name="muonscale";muonscaleUp.dir="Up";

  muonscaleDown.muonscale=-1;    
  muonscaleDown.name="muonscale";muonscaleDown.dir="Down";

  electronscaleUp.electronscale=1;   
  electronscaleUp.name="electronscale"; electronscaleUp.dir="Up";

  electronscaleDown.electronscale=-1;
  electronscaleDown.name="electronscale"; electronscaleDown.dir="Down";

  metUp.met=1;   
  metUp.name="met";   metUp.dir="Up";
  metDown.met=-1;
  metDown.name="met"; metDown.dir="Down";
  //--Variation To Run--//
  vMomentumVar={jesUp,jesDown,jerUp,jerDown,muonscaleUp,muonscaleDown,
		electronscaleUp,electronscaleDown,metUp,metDown};
  
}

JHAnalyzerBase::~JHAnalyzerBase(){
  cout << "t_InitObj=" << t_InitObj << endl;
  cout << "t_InitVariable=" << t_InitVariable << endl;
  cout << "t_EventLoop=" << t_EventLoop << endl;
  cout << "t_FillWeightBase=" << t_FillWeightBase << endl;
  cout << "t_FillMomentumBase=" << t_FillMomentumBase << endl;

  cout << "t_prefire=" << t_prefire << endl;
  cout << "t_ps=" << t_ps << endl;
  cout << "t_pu=" << t_pu << endl;
  cout << "t_btag=" << t_btag << endl;

  cout << "t_ElectronID=" << t_ElectronID << endl;
  cout << "t_ElectronRECO=" << t_ElectronRECO << endl;
  cout << "t_ElectronTrigger=" << t_ElectronTrigger << endl;

  cout << "t_MuonID=" << t_MuonID << endl;
  cout << "t_MuonRECO=" << t_MuonRECO << endl;
  cout << "t_MuonTrigger=" << t_MuonTrigger << endl;
  cout << "t_MuonTrk=" << t_MuonTrk << endl;

  //==== Destructor of this Analyzer
  
}

void JHAnalyzerBase::executeEvent(){  
  timer_InitObj.Start();
  InitAllObjects();
  t_InitObj+=timer_InitObj.RealTime();
  //---Nominal and weight-base variations--//
  timer_InitVariable.Start();
  InitClassVariablesPerEvent();
  t_InitVariable+=timer_InitVariable.RealTime();
  ev=GetEvent();
  SetEventBaseSysWeight();
  timer_EventLoop.Start();
  EventLoop();
  t_EventLoop+=timer_EventLoop.RealTime();
  timer_FillWeightBase.Start();
  FillReservedHistWeightBase();
  t_FillWeightBase+=timer_FillWeightBase.RealTime();
  if(!runSys) return;
  //---Momentum variations--//
  timer_FillMomentumBase.Start();
  for(const auto &sys : vMomentumVar){
    SetSys(sys);
    EventLoop();
    FillReservedHistMomentumVariations();
  }
  t_FillMomentumBase+=timer_FillMomentumBase.RealTime();
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
}
void JHAnalyzerBase::SetSysStructure(){
  if(runSys){
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

  }
  else{
    w_ElectronID.push_back({1.});
    r_ElectronID.push_back({1.});
    w_ElectronRECO.push_back({1.});
    r_ElectronRECO.push_back({1.});
    w_ElectronTrigger.push_back({1.});
    r_ElectronTrigger.push_back({1.});

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
void JHAnalyzerBase::InitClassVariablesPerEvent(){
  //---btagSF variations---//
  r_SystUpLTagCorr=1;r_SystDownLTagCorr=1;
  r_SystUpLTagUnCorr=1;r_SystDownLTagUnCorr=1;
  r_SystUpHTagCorr=1;r_SystDownHTagCorr=1;
  r_SystUpHTagUnCorr=1;r_SystDownHTagUnCorr=1;
  //--Event variables--//
  weight=1.;
  btagsf=1.;

}
void JHAnalyzerBase::FillHist(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  /*
  struct ArgFillHist{
    TString histname;
    double value; double weight;
    int n_bin; double x_min;
    double x_max;
  };

   */
  ArgFillHist this_arg={histname,value,this_weight,n_bin,x_min,x_max};
  vReserveHist.push_back(this_arg);
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
  TString idx1_in_str, idx2_in_str;
  idx1_in_str.Form("%d",idx1);   idx2_in_str.Form("%d",idx2);
  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/"+idx1_in_str+"/"+idx2_in_str+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
}
void JHAnalyzerBase::FillHistIdx2(TString sysname, TString idx1, TString idx2, TString histname,double value,double this_weight,int n_bin,double x_min, double x_max){

  AnalyzerCore::FillHist("SYS/"+histname+"/"+sysname+"/"+idx1+"/"+idx2+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
}

void JHAnalyzerBase::FillHistPUSys(TString histname, double value, double this_weight, int n_bin, double x_min, double x_max){
  //PU weight//
  //double weightUp  =this_weight*r_PU[0];
  //double weightDown=this_weight*r_PU[1];
  //FillHistUp("pu",histname,value,weightUp,n_bin,x_min,x_max);
  //FillHistDown("pu",histname,value,weightDown,n_bin,x_min,x_max);
  FillHistUp("pu",histname,value,this_weight*r_PU[0],n_bin,x_min,x_max);
  FillHistDown("pu",histname,value,this_weight*r_PU[1],n_bin,x_min,x_max);
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

  //double weightUp  = this_weight*r_Prefire[0];
  //double weightDown= this_weight*r_Prefire[1];
  //FillHistUp("prefire",histname,value,weightUp,n_bin,x_min,x_max);
  //FillHistDown("prefire",histname,value,weightDown,n_bin,x_min,x_max);


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
      //double new_weight=w_ElectronID[0][0] ? this_weight*w_ElectronID[iset][imem]/w_ElectronID[0][0] : 0.;
      //double new_weight=this_weight*r_ElectronID[iset][imem];
      //FillHistIdx2("electronID",iset,imem,histname,value,new_weight,n_bin,x_min,x_max);
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
      //double new_weight=w_ElectronRECO[0][0] ? this_weight*w_ElectronRECO[iset][imem]/w_ElectronRECO[0][0] : 0.;
      //double new_weight=this_weight*r_ElectronRECO[iset][imem];
      //FillHistIdx2("electronRECO",iset,imem,histname,value,new_weight,n_bin,x_min,x_max);
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
      //double new_weight=w_ElectronTrigger[0][0] ? this_weight*w_ElectronTrigger[iset][imem]/w_ElectronTrigger[0][0] : 0;
      //double new_weight=this_weight*r_ElectronTrigger[iset][imem];
      //FillHistIdx2("electronTrigger",iset,imem,histname,value,new_weight,n_bin,x_min,x_max);
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
      //double new_weight=w_MuonID[0][0] ? this_weight*w_MuonID[iset][imem]/w_MuonID[0][0] : 0;
      //double new_weight=this_weight*r_MuonID[iset][imem];
      //FillHistIdx2("muonID",iset,imem,histname,value,new_weight,n_bin,x_min,x_max);
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
      //double new_weight=w_MuonRECO[0][0] ?  this_weight*w_MuonRECO[iset][imem]/w_MuonRECO[0][0] : 0;
      //double new_weight=this_weight*r_MuonRECO[iset][imem];
      //FillHistIdx2("muonRECO",iset,imem,histname,value,new_weight,n_bin,x_min,x_max);
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
      //double new_weight=w_MuonTrigger[0][0] ? this_weight*w_MuonTrigger[iset][imem]/w_MuonTrigger[0][0] : 0;
      //double new_weight=this_weight*r_MuonTrigger[iset][imem];
      //FillHistIdx2("muonTrigger",iset,imem,histname,value,new_weight,n_bin,x_min,x_max);
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
      //double new_weight=w_MuonTrk[0][0] ? this_weight*w_MuonTrk[iset][imem]/w_MuonTrk[0][0] : 0;
      //double new_weight=this_weight*r_MuonTrk[iset][imem];
      //FillHistIdx2("muonTrk",iset,imem,histname,value,new_weight,n_bin,x_min,x_max);
      FillHistIdx2("muonTrk",iset,imem,histname,value,this_weight*r_MuonTrk[iset][imem],n_bin,x_min,x_max);
    }
  }
}




void JHAnalyzerBase::FillReservedHistWeightBase(){
  //Because it could be kind of time consuming, it doesn't call defined addtional functions for each sys.
  for(const auto& arg : vReserveHist){ 

    TString histname=arg.histname;
    double value=arg.value;
    double this_weight=arg.weight;
    int n_bin=arg.n_bin;
    double x_min=arg.x_min;
    double x_max=arg.x_max;

    
    //Nominal//
    AnalyzerCore::FillHist(histname+"/"+ProcessName,value,this_weight,n_bin,x_min,x_max);
    if(IsDATA) continue;
    if(!runSys) continue;
    //-PU
    timer_pu.Start();
    FillHistPUSys(histname,value,this_weight,n_bin,x_min,x_max);
    t_pu+=timer_pu.RealTime();
    //-PartonShower
    timer_ps.Start();
    FillHistPSSys(histname,value,this_weight,n_bin,x_min,x_max);
    t_ps+=timer_ps.RealTime();
    //prefire//
    timer_prefire.Start();
    FillHistPrefireSys(histname,value,this_weight,n_bin,x_min,x_max);
    t_prefire+=timer_prefire.RealTime();
    //btag
    timer_btag.Start();
    FillHistBtag(histname,value,this_weight,n_bin,x_min,x_max);
    t_btag+=timer_btag.RealTime();


    ///---EffTool--//
    //electronID//
    timer_ElectronID.Start();
    FillHistElectronID(histname,value,this_weight,n_bin,x_min,x_max);
    t_ElectronID+=timer_ElectronID.RealTime();
    //electronRECO
    
    timer_ElectronRECO.Start();
    FillHistElectronRECO(histname,value,this_weight,n_bin,x_min,x_max);
    t_ElectronRECO+=timer_ElectronRECO.RealTime();

    //electronTrigger
    timer_ElectronTrigger.Start();
    FillHistElectronTrigger(histname,value,this_weight,n_bin,x_min,x_max);
    t_ElectronTrigger+=timer_ElectronTrigger.RealTime();

    //muonID
    timer_MuonID.Start();
    FillHistMuonID(histname,value,this_weight,n_bin,x_min,x_max);
    t_MuonID+=timer_MuonID.RealTime();

    //muonRECO
    timer_MuonRECO.Start();
    FillHistMuonRECO(histname,value,this_weight,n_bin,x_min,x_max);
    t_MuonRECO+=timer_MuonRECO.RealTime();

    //MuonTrigger
    timer_MuonTrigger.Start();
    FillHistMuonTrigger(histname,value,this_weight,n_bin,x_min,x_max);
    t_MuonTrigger+=timer_MuonTrigger.RealTime();
    
    //MuonTrk
    timer_MuonTrk.Start();
    FillHistMuonTrk(histname,value,this_weight,n_bin,x_min,x_max);
    t_MuonTrk+=timer_MuonTrk.RealTime();    
  }
  ClearReserveHist();
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
 ClearReserveHist();
}
void JHAnalyzerBase::ClearReserveHist(){
  vReserveHist.clear();
}

void JHAnalyzerBase::SetSys(MomentumVar _sys){
  sysname_current=_sys.name;
  sysdir_current=_sys.dir;
  //jes=_sys.jes;
  //jer=_sys.jer;
  //muonscale=_sys.muonscale;
  //electronscale=_sys.electronscale;
  //met=_sys.met;
  
  if(_sys.muonscale!=0){
    AllMuons=ScaleMuons(AllMuons_raw,_sys.muonscale);
    std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
    PuppiMET=UpdateMETByMuonScale(PuppiMET_roch,_sys.muonscale); 
    AllElectrons=AllElectrons_raw;
    AllJets=AllJets_raw;
  }
  else if(_sys.electronscale!=0){ 
    AllMuons=AllMuons_raw;
    PuppiMET=UpdateMETByElectronScale(PuppiMET_roch,_sys.electronscale); 
    AllElectrons=ScaleElectrons(AllElectrons_raw,_sys.electronscale);
    std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
    AllJets=AllJets_raw;
  }
  else if(_sys.jes!=0){
    AllMuons=AllMuons_raw;
    AllElectrons=AllElectrons_raw;
    AllJets=ScaleJets(AllJets_raw,_sys.jes);
    std::sort(AllJets.begin(), AllJets.end(), PtComparing);
    PuppiMET=UpdateMETByJetScale(PuppiMET_roch,_sys.jes); 
  }
  else if(_sys.jer!=0){
    AllMuons=AllMuons_raw;
    AllElectrons=AllElectrons_raw;
    AllJets=SmearJets(AllJets_raw,_sys.jer);
    std::sort(AllJets.begin(), AllJets.end(), PtComparing);
    PuppiMET=UpdateMETByJetSmear(PuppiMET_roch,_sys.jer);
  }
  else if(_sys.met!=0){
    AllMuons=AllMuons_raw;
    AllElectrons=AllElectrons_raw;
    AllJets=AllJets_raw;
    PuppiMET=GetShiftedMET(_sys.met);
  }
  else{
    cout << "[JHAnalyzerBase::SetSyst] No systematic shift for ->" << sysname_current << endl;
  }
  SetCurrentSys(_sys);

}
void JHAnalyzerBase::SetCurrentSys(MomentumVar sys){
  _CurrentSys=sys;
}

JHAnalyzerBase::MomentumVar JHAnalyzerBase::GetCurrentSys(){
  return _CurrentSys;
}
TString JHAnalyzerBase::GetCurrentSysName(){
  return _CurrentSys.name;
}
TString JHAnalyzerBase::GetCurrentSysDir(){
  return _CurrentSys.dir;
}


void JHAnalyzerBase::InitAllObjects(){
  AllMuons_raw=GetAllMuons();
  AllMuons=AllMuons_raw;
  std::sort(AllMuons.begin(), AllMuons.end(), PtComparing);
  AllElectrons_raw=GetAllElectrons();
  AllElectrons=AllElectrons_raw;
  std::sort(AllElectrons.begin(), AllElectrons.end(), PtComparing);
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


TLorentzVector JHAnalyzerBase::UpdateMETByMuonScale(const TLorentzVector &met_orig, int sys){
  //it is needed because Rochester Correction is an additional corretion after miniAOD.
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  for(const auto& muon : AllMuons_raw){
    px_orig+= muon.Px();
    py_orig+= muon.Px();

    px_corrected += muon.MomentumShift(sys)*TMath::Cos(muon.Phi());
    py_corrected += muon.MomentumShift(sys)*TMath::Sin(muon.Phi());
    
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
    py_orig+= electron.Px();

    px_corrected += electron.Px()*electron.EnShift(sys);
    py_corrected += electron.Py()*electron.EnShift(sys);

    
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
    py_orig+= jet.Px();

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
    py_orig+= jet.Px();

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

}

void JHAnalyzerBase::SetupDiLeptonChannel(){
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
    MuonTriggerNames ={"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v","HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v","HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"};
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
}

void JHAnalyzerBase::SetIsDoubleLeptonTrigger(){
  IsDoubleMuonTrigger=false;
  if( MuonTriggerSFKeys.size() == 2 ){
    IsDoubleMuonTrigger=true;
  }
  else if( MuonTriggerSFKeys.size() == 1 ){
    IsDoubleMuonTrigger=false;
  }
  else{
    cout << "[JHAnalyzerBase::SetIsDoubleLeptonTrigger] Wrong size of MuonTriggerSFKeys  -> " << MuonTriggerSFKeys.size() << endl;
  }


  IsDoubleElectronTrigger=false;
  if( ElectronTriggerSFKeys.size() == 2 ){
    IsDoubleElectronTrigger=true;
  }
  else if( ElectronTriggerSFKeys.size() == 1 ){
    IsDoubleElectronTrigger=false;
  }
  else{
    cout << "[JHAnalyzerBase::SetIsDoubleLeptonTrigger] Wrong size of ElectronTriggerSFKeys  -> " << ElectronTriggerSFKeys.size() << endl;
  }
    



}

int JHAnalyzerBase::GetIdxSingleMuReco(const vector<Muon> &MuonCollection, double ptmin, double etacut, double ptveto){

  unsigned int muonsize = MuonCollection.size();
  unsigned int nselected= 0;
  int muonidx=-1;
  double maxpt=-100.;
  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double pt=MuonCollection[i].Pt();
    double eta=MuonCollection[i].Eta();
    bool passID=MuonCollection[i].PassID("POGLoose");
    bool passISO=MuonCollection[i].PassSelector(Muon::Selector::TkIsoLoose);
    //double reliso=MuonCollection[i].RelIso();
    if(fabs(eta) > etacut) continue;
    if(pt < ptveto) continue;
    if (!passID) continue;
    if (!passISO) continue;
    if (pt > maxpt) {
      maxpt=pt;
      muonidx=i;
    }
    nselected+=1;
  }


  if (nselected!=1) return -1;
  if (!MuonCollection[muonidx].PassID("POGMedium")) return -1;
  if (maxpt < ptmin) return -1;

  //---GetSF--//
  vector<int> v_muonidx={muonidx};
  SetMuonSFs(v_muonidx);
  return muonidx;

}


int JHAnalyzerBase::GetIdxSingleElReco(const vector<Electron> &ElectronCollection, double ptmin, double etacut, double ptveto){

  unsigned int electronsize = ElectronCollection.size();
  unsigned int nselected= 0;
  int electronidx=-1;
  double maxpt=-100.;
  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=ElectronCollection[i].Pt();
    double eta=ElectronCollection[i].Eta();
    bool passID=ElectronCollection[i].PassID("passLooseID");
    if(fabs(eta) > etacut) continue;
    if(pt < ptveto) continue;
    if(!passID) continue;
    if(pt > maxpt){
      maxpt = pt;
      electronidx=i;
    }
  }
  if (nselected!=1) return -1;
  if (!ElectronCollection[electronidx].PassID("passMediumID")) return -1;
  if (maxpt < ptmin) return -1;
  vector<int> v_electronidx= {electronidx};
  SetElectronSFs(v_electronidx);
  return electronidx;
}



vector<int> JHAnalyzerBase::GetIdxDiMuReco(const vector<Muon> &MuonCollection, double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<int> v_muonidx;
  unsigned int muonsize = MuonCollection.size();
  unsigned int npassveto=0;
  unsigned int npasstight=0;

  double maxpt=-9999.;
  double minpt=9999.;
  int i1=-1,i2=-1;
  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double pt=MuonCollection[i].Pt();
    double eta=MuonCollection[i].Eta();
    bool passID=MuonCollection[i].PassID("POGMedium");
    bool passVetoID=MuonCollection[i].PassID("POGLoose");
    bool passISO=MuonCollection[i].PassSelector(Muon::Selector::TkIsoLoose);
    //double reliso=MuonCollection[i].RelIso();
    if(fabs(eta) > etacut) continue;
    if(pt < ptveto) continue;
    if (!passISO) continue;
    if (!passVetoID) continue;
    if (pt > maxpt){
      maxpt=pt;
      i1=i;
    }
    if (pt < minpt){
      minpt=pt;
      i2=i;
    }
    if (passID) npasstight+=1;
    npassveto+=1;

  }
  if(npassveto>2) return {};
  if(npasstight!=2) return {};
  if(maxpt < ptmin1) return {};
  if(minpt < ptmin2) return {};
  v_muonidx.push_back(i1);
  v_muonidx.push_back(i2);
  SetMuonSFs(v_muonidx);
  return v_muonidx;
}


vector<int> JHAnalyzerBase::GetIdxDiElReco(const vector<Electron> &ElectronCollection, double ptmin1, double ptmin2, double etacut, double ptveto ){
  vector<int> v_electronidx;
  unsigned int electronsize = ElectronCollection.size();
  unsigned int npassveto=0;
  unsigned int npasstight=0;
  double maxpt=-9999.;
  double minpt=9999.;
  int i1,i2;
  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=ElectronCollection[i].Pt();
    double eta=ElectronCollection[i].Eta();
    bool passID=ElectronCollection[i].PassID("passMediumID");
    bool passVetoID=ElectronCollection[i].PassID("passLooseID");
    if(fabs(eta) > etacut) continue;
    if(pt < ptveto) continue;
    if (!passVetoID) continue;
    if (pt > maxpt){
      maxpt=pt;
      i1=i;
    }
    if (pt < minpt){
      minpt=pt;
      i2=i;
    }
    if (passID) npasstight+=1;
    npassveto+=1;
  }
  if(npassveto>2) return {};
  if(npasstight!=2) return {};
  if(maxpt < ptmin1) return {};
  if(minpt < ptmin2) return {};
  v_electronidx.push_back(i1);
  v_electronidx.push_back(i2);
  SetElectronSFs(v_electronidx);
  return v_electronidx;
}

vector<int> JHAnalyzerBase::GetIdxTightJet(const vector<Jet> &JetCollection, const vector<Lepton> &v_tightlep, double ptmin, double etacut, TString JetID ){
  vector<int> v_jetidx;
  unsigned int jetsize = JetCollection.size();
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
  return v_jetidx;
}

vector<int> JHAnalyzerBase::GetIdxBJet(const vector<int> &v_TightjetIdx){
  vector<int> v_bjetidx;
  for(const auto& i : v_TightjetIdx){
    double btagscore=AllJets[i].GetTaggerResult(JetTagging::DeepJet);
    if(btagscore < btagcut) continue;
    v_bjetidx.push_back(i);
  }
  SetBtagSF(v_bjetidx);
  return v_bjetidx;
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

void JHAnalyzerBase::SetMuonSFs(const vector<int> &v_muonidx){
  SetMuonRecoSF(v_muonidx);
  SetMuonIDSF(v_muonidx);
  SetMuonTrkSF(v_muonidx);
  SetMuonTriggerSF(v_muonidx);
}

void JHAnalyzerBase::SetElectronSFs(const vector<int> &v_electronidx){
  SetElectronRecoSF(v_electronidx);
  SetElectronIDSF(v_electronidx);
  SetElectronTriggerSF(v_electronidx);
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


void JHAnalyzerBase::SetMuonTriggerSF(const vector<int> &v_muonidx){
  vector<Lepton*> _v_muons;
  for(const auto& muonidx : v_muonidx){
    _v_muons.push_back((Lepton*)&AllMuons[muonidx] );
  }
  if(!IsDoubleMuonTrigger){
    SetSingleMuonTriggerSF(_v_muons);
  }
  else{
    SetDoubleMuonTriggerSF(_v_muons);
  }

}

void JHAnalyzerBase::SetSingleMuonTriggerSF(const vector<Lepton*> &v_muons){

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
    SetSingleElectronTriggerSF(_v_electrons);
  }
  else{
    SetDoubleElectronTriggerSF(_v_electrons);
  }

}

void JHAnalyzerBase::SetSingleElectronTriggerSF(const vector<Lepton*> &v_electrons){

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






