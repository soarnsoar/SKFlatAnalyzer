#include "AnalyzerCore.h"
#include <sys/resource.h>
#include <iostream>

AnalyzerCore::AnalyzerCore(){

  outfile = NULL;
  mcCorr = new MCCorrection();
  puppiCorr = new PuppiSoftdropMassCorr();
  fakeEst = new FakeBackgroundEstimator();
  cfEst = new CFBackgroundEstimator();
  pdfReweight = new PDFReweight();
  muonGE = new GeneralizedEndpoint();
  muonGEScaleSyst = new GEScaleSyst();



  JECSources = {"AbsoluteStat","AbsoluteScale","AbsoluteFlavMap","AbsoluteMPFBias","Fragmentation","SinglePionECAL","SinglePionHCAL","FlavorQCD","TimePtEta","RelativeJEREC1","RelativeJEREC2","RelativeJERHF","RelativePtBB","RelativePtEC1","RelativePtEC2","RelativePtHF","RelativeBal","RelativeSample","RelativeFSR","RelativeStatFSR","RelativeStatEC","RelativeStatHF","PileUpDataMC","PileUpPtRef","PileUpPtBB","PileUpPtEC1","PileUpPtEC2","PileUpPtHF","FlavorZJet","FlavorPhotonJet","FlavorPureGluon","FlavorPureQuark","FlavorPureCharm","FlavorPureBottom","Total"};

  /*
    
    // In your analyser code add this line to constructor to fill map with JEC source values.
    for(auto jec_source : JECSources)   SetupJECUncertainty(jec_source, "AK4PFchs");
  }
    // Then you can get vector of jets with shift calling 
    std::vector<Jet> AnalyzerCore::ScaleJetsIndividualSource(const std::vector<Jet>& jets, int sys, TString source);
    vector<Jet> jets_AbsoluteStatUp = ScaleJetsIndividualSource(jets, 1, "AbsoluteStat");
  */
  //
  jhchoi_newtree=new TTree("dummyTree1","dummyTree1");
  jhchoi_newtree2=new TTree("dummyTree2","dummyTree2");
  jhchoi_newtree3=new TTree("dummyTree3","dummyTree3");
  jhchoi_newtree4=new TTree("dummyTree4","dummyTree4");

  
}
/*
void AnalyzerCore::SetupRoccoR(){
  cout<<"[AnalyzerCore::SetupRoccoR] setting Rocheseter Correction"<<endl;
  TString erashort=GetEraShort();

  //TString rocpath=datapath+"/"+GetEra()+"/RoccoR/RoccoR"+GetEraShort()+"UL.txt"; //central roccor for amc
  TString rocpath=TString(getenv("SKFlat_WD"))+"/external/Aepcor/u_"+erashort(2,3)+"UL_1.txt"; //roccor for minnlo
  if(IsExists(rocpath)) roc=new RoccoR(rocpath.Data());
  else cout<<"[AnalyzerCore::SetupRoccoR] no "+rocpath<<endl;

  TString rocelepath=TString(getenv("SKFlat_WD"))+"/external/Aepcor/e_"+erashort(2,3)+"UL_1.txt";
  if(IsExists(rocelepath)){
    rocele=new Aepcor;
    rocele->init(rocelepath.Data(),Aepres::CB);
  }
  else cout<<"[AnalyzerCore::SetupRoccoR] no "+rocelepath<<endl;
}


std::vector<Electron> AnalyzerCore::ElectronEnergyCorrection(const vector<Electron>& electrons,int set,int member){
  if(!rocele) return std::vector<Electron>(electrons);
  std::vector<Electron> out;
  for(auto electron:electrons){
    if(set>=0){
      double rc=1.;
      //double rcerr=0.;
      double el_eta=electron.scEta();
      double el_phi=electron.Phi();
      if(IsDATA){
        rc=rocele->kScaleDT(electron.UncorrPt(),el_eta,el_phi,electron.R9(),run,set,member);
      }else{
        Gen gen=SMPGetGenMatchedLepton(electron,gens,1);
        gRandom->SetSeed((run<<15)+(lumi<<10)+(event<<5)+electron.Eta()*100);
        double u=gRandom->Rndm();
        if(!gen.IsEmpty()&&fabs(electron.Pt()/gen.Pt()-1.)<0.5){
          rc=rocele->kSpreadMC(electron.UncorrPt(),el_eta,el_phi,electron.R9(),u,gen.Pt(),set,member);
        }else{
          //rc=rocele->kSmearMC(electron.UncorrPt(),el_eta,el_phi,electron.R9(),u,set,member);
          rc=1.;
        }
      }
      if(TMath::IsNaN(rc)) rc=1.;
      electron*=rc*electron.UncorrE()/electron.E();
    }else if(set==-1){ //no energe cor
      electron*=electron.UncorrE()/electron.E();
    }else{
      cout<<"[AnalyzerCore::ElectronEnergyCorrection] wrong set "<<set<<endl;
      exit(ENODATA);
    }
    out.push_back(electron);
  }
  std::sort(out.begin(),out.end(),PtComparing);
  return out;
}

*/
bool AnalyzerCore::IsExists(TString filepath){
  ifstream fcheck(filepath);
  return fcheck.good();
}

void AnalyzerCore::FillCutflow(TString histname,TString label,double weight){
  TH1D* hist=NULL;
  auto it=maphist_TH1D.find(histname);
  if(it==maphist_TH1D.end()){
    hist=new TH1D(histname,"",1,0,1);
    hist->GetXaxis()->SetBinLabel(1,label);
    maphist_TH1D[histname]=hist;
  }else hist=it->second;

  int nbin=hist->GetNbinsX();
  int ibin=0;
  for(int i=1;i<=nbin;i++){
    if(hist->GetXaxis()->GetBinLabel(i)==label){
      ibin=i;
    }
  }

  if(!ibin){
    hist->SetBins(nbin+1,0,nbin+1);
    ibin=nbin+1;
    hist->GetXaxis()->SetBinLabel(ibin,label);
  }
  hist->Fill(ibin-0.5,weight);
}

void AnalyzerCore::SetupEfficiency(){
  TString configpath=getenv("DATA_DIR")+TString("/")+GetEra()+"/ID/eff.conf";
  cout << "[AnalyzerCore::SetupEfficiency] configpath= " << configpath << endl;
  if(IsExists(configpath)){
    fEff=new EfficiencyTool(configpath);
  }
}
void AnalyzerCore::DeleteEfficiency(){
  if(fEff) {
    delete fEff;
    fEff=nullptr;
  }
}
void AnalyzerCore::SetupJetPUIDTool(){
  TString _datadir=getenv("DATA_DIR");
  TString _era=GetEra();
  map_jetpuid_tool["T"]=new JetPUIDTool(IsDATA);
  map_jetpuid_tool["T"]->ReadHist(_datadir,_era,"T");
  map_jetpuid_tool["M"]=new JetPUIDTool(IsDATA);
  map_jetpuid_tool["M"]->ReadHist(_datadir,_era,"M");
  map_jetpuid_tool["L"]=new JetPUIDTool(IsDATA);
  map_jetpuid_tool["L"]->ReadHist(_datadir,_era,"L");
}
void AnalyzerCore::DeleteJetPUIDTool(){
  if(map_jetpuid_tool["T"]){
    delete map_jetpuid_tool["T"];
    map_jetpuid_tool["T"]=nullptr;
  }
  if(map_jetpuid_tool["M"]){
    delete map_jetpuid_tool["M"];
    map_jetpuid_tool["M"]=nullptr;
  }
  if(map_jetpuid_tool["L"]){
    delete map_jetpuid_tool["L"];
    map_jetpuid_tool["L"]=nullptr;
  }
}
double AnalyzerCore::GetLeptonTriggerSF(TString triggerSF_key,const vector<Lepton*>& leps,int set,int mem,TString option){
  if(IsDATA) return 1;
  if(triggerSF_key=="") return 1;
  if(triggerSF_key=="Default") return 1;

  double data_eff=1.,sim_eff=1.;
  for(const auto& lep:leps){
    data_eff*=1-fEff->GetDataEfficiency(triggerSF_key,lep,set,mem,option);
    sim_eff*=1-fEff->GetSimEfficiency(triggerSF_key,lep,set,mem,option);
  }
  data_eff=1-data_eff;
  sim_eff=1-sim_eff;
  if(sim_eff==0) return 1.;
  else return data_eff/sim_eff;
}

double AnalyzerCore::GetLeptonTriggerORSF(Event &_event,vector<TString> triggers, vector<TString> trigSFkeys,const vector<Lepton*>& leps,int set,int mem,TString option){
  if(IsDATA) return 1;
  if(triggers.size()!=2){
    cout<<"[AnalyzerCore::LeptonTriggerOR_SF] triggers.size()= "<<triggers.size()<<endl;
    exit(EXIT_FAILURE);
  }
  if(trigSFkeys.size()!=2){
    cout<<"[AnalyzerCore::LeptonTriggerOR_SF] trigSFkeys.size()= "<<trigSFkeys.size()<<endl;
    exit(EXIT_FAILURE);
  }

  double lumi=_event.GetTriggerLumi("Full");
  double lumi0,lumi1,lumi01;
  if(DataYear==2017&&trigSFkeys[0].Contains("IsoMu24")&&trigSFkeys[1].Contains("IsoMu27")){
    lumi0=_event.GetTriggerLumi(triggers[0]); lumi1=_event.GetTriggerLumi(triggers[1]); lumi01=lumi0;
  }else if(DataYear==2017&&trigSFkeys[0].Contains("Ele27")&&trigSFkeys[1].Contains("Ele32")){
    lumi0=_event.GetTriggerLumi(triggers[0]); lumi1=_event.GetTriggerLumi(triggers[1]); lumi01=17599.732185;
  }else if(DataYear==2018&&trigSFkeys[0].Contains("Ele28")&&trigSFkeys[1].Contains("Ele32")){
    lumi0=_event.GetTriggerLumi(triggers[0]); lumi1=_event.GetTriggerLumi(triggers[1]); lumi01=lumi0;
  }else{
    cout<<"[AnalyzerCore::GetLeptonTriggerORSF] not available combination '"<<trigSFkeys[0]<<"'||'"<<trigSFkeys[1]<<"' for "<<DataEra<<endl;
    exit(EXIT_FAILURE);
  }

  bool newflag=set<0; //temp
  if(newflag) set=0; //temp
  double data_eff0=1.,sim_eff0=1.;
  double data_eff1=1.,sim_eff1=1.;
  for(const auto& lep:leps){
    data_eff0*=1-fEff->GetDataEfficiency(trigSFkeys[0],lep,set,mem,option);
    sim_eff0*=1-fEff->GetSimEfficiency(trigSFkeys[0],lep,set,mem,option);
    data_eff1*=1-fEff->GetDataEfficiency(trigSFkeys[1],lep,set,mem,option);
    sim_eff1*=1-fEff->GetSimEfficiency(trigSFkeys[1],lep,set,mem,option);
  }
  data_eff0=1-data_eff0;
  sim_eff0=1-sim_eff0;
  data_eff1=1-data_eff1;
  sim_eff1=1-sim_eff1;
  double sf=0.;
  if(_event.PassTrigger(triggers[1])){
    double this_sf=(lumi1-lumi01)/lumi;
    if(sim_eff1) this_sf*=data_eff1/sim_eff1;
    sf+=this_sf;
  }
  if(_event.PassTrigger(triggers[0])){
    double this_sf=(lumi0-lumi01)/lumi;
    if(sim_eff0) this_sf*=data_eff0/sim_eff0;
    sf+=this_sf;
  }
  //overlap region                                                                                                                                                                                                                                                                                                                                                   
  if(!newflag){
    if(lumi0>lumi1){
      if(_event.PassTrigger(triggers[0])){
        double this_sf=lumi01/lumi;
        if(sim_eff0) this_sf*=data_eff0/sim_eff0;
        sf+=this_sf;
      }
    }else{
      if(_event.PassTrigger(triggers[1])){
        double this_sf=lumi01/lumi;
        if(sim_eff1) this_sf*=data_eff1/sim_eff1;
        sf+=this_sf;
      }else if(_event.PassTrigger(triggers[0])){
        double this_sf=lumi01/lumi;
        if(sim_eff0) this_sf*=data_eff0/sim_eff0;
        sf+=this_sf;
      }
    }
  }else{
    if(_event.PassTrigger(triggers[0])){
      double this_sf=lumi01/2/lumi;
      if(sim_eff0) this_sf*=data_eff0/sim_eff0;
      sf+=this_sf;
    }
    if(_event.PassTrigger(triggers[1])){
      double this_sf=lumi01/2/lumi;
      if(sim_eff1) this_sf*=data_eff1/sim_eff1;
      sf+=this_sf;
    }else if(_event.PassTrigger(triggers[0])){
      double this_sf=lumi01/2/lumi;
      if(sim_eff0) this_sf*=data_eff0/sim_eff0;
      sf+=this_sf;
    }
  }

  return sf;
}
double AnalyzerCore::GetDileptonTriggerSF(TString triggerSF_key0,TString triggerSF_key1,TString DZSF,const vector<Lepton*>& leps,int set,int mem,TString option){
  if(IsDATA) return 1;
  if((triggerSF_key0==""||triggerSF_key0=="Default")&&(triggerSF_key1==""||triggerSF_key1=="Default")) return 1;
  int nlep=leps.size();
  if(nlep<2){
    cout<<"[AnalyzerCore::DileptonTrigger_SF] nlep < 2. return 1."<<endl;
    return 1.;
  }
  double data_noleg1=1.,sim_noleg1=1.;
  vector<double> data_oneleg1_noleg2(nlep,1.);
  vector<double> sim_oneleg1_noleg2(nlep,1.);
  for(int i=0;i<nlep;i++){
    double data_eff_leg1=fEff->GetDataEfficiency(triggerSF_key0,leps.at(i),set,mem,option);
    double data_eff_leg2=fEff->GetDataEfficiency(triggerSF_key1,leps.at(i),set,mem,option);
    double sim_eff_leg1=fEff->GetSimEfficiency(triggerSF_key0,leps.at(i),set,mem,option);
    double sim_eff_leg2=fEff->GetSimEfficiency(triggerSF_key1,leps.at(i),set,mem,option);
    if(DZSF!=""){
      double data_eff_dz=fEff->GetDataEfficiency(DZSF,leps.at(i),0,0,option);
      double sim_eff_dz=fEff->GetSimEfficiency(DZSF,leps.at(i),0,0,option);
      data_eff_leg1*=data_eff_dz;
      data_eff_leg2*=data_eff_dz;
      sim_eff_leg1*=sim_eff_dz;
      sim_eff_leg2*=sim_eff_dz;
    }
    data_noleg1*=(1-data_eff_leg1);
    sim_noleg1*=(1-sim_eff_leg1);
    for(int j=0;j<nlep;j++){
      if(i==j){
        data_oneleg1_noleg2[j]*=data_eff_leg1;
        sim_oneleg1_noleg2[j]*=sim_eff_leg1;
      }else{
        data_oneleg1_noleg2[j]*=(1-data_eff_leg2);
        sim_oneleg1_noleg2[j]*=(1-sim_eff_leg2);
      }
    }
  }
  double data_eff=1.-data_noleg1;
  double sim_eff=1.-sim_noleg1;
  for(int i=0;i<nlep;i++){
    data_eff-=data_oneleg1_noleg2[i];
    sim_eff-=sim_oneleg1_noleg2[i];
  }
  double sf=1.;
  if(sim_eff==0) return sf=1.;
  else sf=data_eff/sim_eff;
  return sf;
}


////---END jhchoi---///
AnalyzerCore::~AnalyzerCore(){
  //jhchoi
  cout << "DeleteEfficiency" << endl;
  cout << printcurrunttime() << endl;
  cout << "Skip DeleteEfficiency step. Let ROOT do this" << endl;
  //DeleteEfficiency();
  cout << printcurrunttime() << endl;
  cout << "DeleteZptWeight" << endl;
  cout << printcurrunttime() << endl;
  DeleteZptWeight();
  cout << printcurrunttime() << endl;
  cout << "DeleteJetPUIDTool" << endl;
  DeleteJetPUIDTool();
  cout << printcurrunttime() << endl;
  //end jhchoi

  //=== hist maps
  cout << "Delete HistMaps" << endl;
  cout << " maphist_TH1D.size()=" << maphist_TH1D.size() << endl;
  //cout << " vhist_TH1D.size()=" << vhist_TH1D.size() << endl;

  //let's skip this 
  //cout << "skip delete TH objects. Let ROOT release each memory. It's much faster way in ROOT 6.14" << endl;
  cout << "skip delete TH objects. Let ROOT release each memory. It's much faster way in ROOT 6.30" << endl;
  
  for(std::map< TString, TH1D* >::iterator mapit = maphist_TH1D.begin(); mapit!=maphist_TH1D.end(); mapit++){

    continue;
    //cout<<"mapit->second->GetDirectory() =>" <<mapit->second->GetDirectory() << endl;
    delete mapit->second;
    mapit->second=nullptr;
  }
  //maphist_TH1D.clear();
  
  for(std::map< TString, TH2D* >::iterator mapit = maphist_TH2D.begin(); mapit!=maphist_TH2D.end(); mapit++){
    delete mapit->second;
    mapit->second=nullptr;
  }
  maphist_TH2D.clear();

  for(std::map< TString, TH3D* >::iterator mapit = maphist_TH3D.begin(); mapit!=maphist_TH3D.end(); mapit++){
    delete mapit->second;
    mapit->second=nullptr;
  }
  maphist_TH3D.clear();



  /*
  int ih=0;
  for (TH1D* this_hist : vhist_TH1D) {
    if(ih%1000==0) cout << "ih=" << ih << endl;
    delete this_hist;
    ih+=1;
  }
  maphist_TH1D.clear();

  for (TH2D* this_hist : vhist_TH2D) {
    delete this_hist;
  }
  maphist_TH2D.clear();

  for (TH3D* this_hist : vhist_TH3D) {
    delete this_hist;
  }
  maphist_TH3D.clear();
  */


  cout << "[END]Delete HistMaps" << endl;
  cout << printcurrunttime() << endl;
  if(jhchoi_newtree) {
    delete jhchoi_newtree;
    jhchoi_newtree=nullptr;
  }
  if (jhchoi_newtree2){
    delete jhchoi_newtree2;
    jhchoi_newtree2=nullptr;
  }
  if (jhchoi_newtree3){
    delete jhchoi_newtree3;
    jhchoi_newtree3=nullptr;

  }
  if (jhchoi_newtree4){
    delete jhchoi_newtree4;
    jhchoi_newtree4=nullptr;
  }
  cout << printcurrunttime() << endl;
  
  //==== output rootfile

  if(outfile){

    cout << "Close outfile" << endl;
    if(1){
      struct rusage usage;
      getrusage(RUSAGE_SELF, &usage);
      std::cout << "Max RSS: " << usage.ru_maxrss / 1024.0 << " MB\n"; // kilobytes
      
    }
    cout << printcurrunttime() << endl;
    outfile->Close();
    if(1){
      struct rusage usage;
      getrusage(RUSAGE_SELF, &usage);
      std::cout << "Max RSS: " << usage.ru_maxrss / 1024.0 << " MB\n"; // kilobytes
      
    }
    cout << "Delete outfile" << endl;
    cout << printcurrunttime() << endl;
    delete outfile;
    outfile=nullptr;
    if(1){
      struct rusage usage;
      getrusage(RUSAGE_SELF, &usage);
      std::cout << "Max RSS: " << usage.ru_maxrss / 1024.0 << " MB\n"; // kilobytes
      
    }
    cout << "[DONE]Delete outfile" << endl;
    cout << printcurrunttime() << endl;
  }

  //==== Tools
  cout << "Delete mccor" << endl;
  cout << printcurrunttime() << endl;
  if(mcCorr) {
    delete mcCorr;
    mcCorr=nullptr;
  }
  cout << printcurrunttime() << endl;
  cout << "Delete puppiCorr" << endl;
  if(puppiCorr) {
    delete puppiCorr;
    puppiCorr=nullptr;
  }
  if(fakeEst){
    delete fakeEst;
    fakeEst=nullptr;
  }
  if(cfEst) {
    delete cfEst;
    cfEst=nullptr;
  }
  if(pdfReweight) {
    delete pdfReweight;
    pdfReweight=nullptr;
  }
  if(muonGE){
    delete muonGE;
    muonGE=nullptr;
  }
  if(muonGEScaleSyst) {
    delete muonGEScaleSyst;
    muonGEScaleSyst=nullptr;
  }
  cout << printcurrunttime() << endl;
  cout << "clear JECMap" << endl;
  AK4CHSJECUncMap.clear();
  AK4PUPPIJECUncMap.clear();
  AK8CHSJECUncMap.clear();
  AK8PUPPIJECUncMap.clear();
  cout << "[DONE]clear JECMap" << endl;
  cout << printcurrunttime() << endl;
    

}

//==== Attach the historams to ai different direcotry, not outfile
//==== We will write these histograms in WriteHist() to outfile
void AnalyzerCore::SwitchToTempDir(){

  gROOT->cd();
  TDirectory *tempDir = NULL;
  int counter = 0;
  while (!tempDir) {
    //==== First, let's find a directory name that doesn't exist yet
    std::stringstream dirname;
    dirname << "AnalyzerCore" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    //==== Let's try to make this directory
    tempDir = gROOT->mkdir((dirname.str()).c_str());
  }
  tempDir->cd();

}

void AnalyzerCore::SetOutfilePath(TString outname){
  outfile = new TFile(outname,"RECREATE");
};

Event AnalyzerCore::GetEvent(){

  Event ev;
  ev.SetTrigger(*HLT_TriggerName);
  ev.SetMET(pfMET_Type1_pt,pfMET_Type1_phi);
  ev.SetnPV(nPV);
  ev.SetEra(GetEra());

  return ev;

}

float AnalyzerCore::GetJECUncertainty(TString source, TString JetType, float eta, float pt, int sys){

  std::map<TString, std::vector<std::map<float, std::vector<float> > > >::iterator mapit;
  bool NotFound=false;
  if(JetType=="AK4PFchs") {
    mapit = AK4CHSJECUncMap.find(source); 
    if(mapit == AK4CHSJECUncMap.end()) NotFound=true;
  }
  if(JetType=="AK4PFPuppi") {
    mapit = AK4PUPPIJECUncMap.find(source);
    if(mapit == AK4PUPPIJECUncMap.end()) NotFound=true;
  }
  if(JetType=="AK8PFchs"){
    mapit = AK8CHSJECUncMap.find(source);
    if(mapit == AK8CHSJECUncMap.end()) NotFound=true;
  }
  if(JetType=="AK8PFPuppi") {
    mapit = AK8PUPPIJECUncMap.find(source);
    if(mapit == AK8PUPPIJECUncMap.end()) NotFound=true;
  }
  if(NotFound) {cout<< "ERROR, " << source  << " not found in JEC Uncertainty MAP for " << JetType << endl; return -999.;}

  
  float bin_boundary(-999.);

  std::map<float, std::vector<float> > ptmap = mapit->second.at(0);

  std::vector<float> etabins;  
  for(std::map<float, std::vector<float> >::iterator it = ptmap.begin(); it!= ptmap.end(); it++){
    etabins.push_back(it->first);
  }
  
  for(unsigned int i=0; i < etabins.size()-1 ; i++){
    if(eta >= etabins.at(i) && eta < etabins.at(i+1)){  bin_boundary = float(etabins.at(i)) ; break;}
  }
  
  if(bin_boundary == -999) return 1.;

  std::vector<float> ptbins;
  
  for(std::map<float, std::vector<float> >::iterator pit = ptmap.begin();  pit != ptmap.end(); pit++){
    if(float(pit->first) == float(bin_boundary)) {ptbins = pit->second; }
  }
  
  int ptbin(-999);
  if(pt >= ptbins.at(ptbins.size() - 1)) ptbin = ptbins.size() - 1;
  for(unsigned int j = 0 ; j < ptbins.size()-1; j++){
    if( pt >= ptbins.at(j)  && pt < ptbins.at(j+1)) {ptbin=j; break;}
  }
  
  if(ptbin == -999) return 1.;

  std::map<float, std::vector<float> > upmap = mapit->second.at(1); 
  std::map<float, std::vector<float> > downmap = mapit->second.at(2); 
  
  std::map<float, std::vector<float> >::iterator mapit_unc;
  if(sys> 0) mapit_unc =  mapit->second.at(1).find(bin_boundary);
  else mapit_unc =  mapit->second.at(2).find(bin_boundary);
  
  float unc = (sys> 0) ?   1+ mapit_unc->second.at(ptbin) : 1 - mapit_unc->second.at(ptbin);

  return unc;
}


void AnalyzerCore::SetupJECUncertainty(TString source , TString JetType){
  
  string analysisdir = getenv("DATA_DIR");
  
  string file = analysisdir + "/"+string(GetEra()) + "/JEC/Summer19UL16APV_V7_MC_UncertaintySources_"+string(JetType)+".txt"; 
  if(GetEra() == "2016postVFP") file = analysisdir + "/"+ string(GetEra())+ "/JEC/Summer19UL16_V7_MC_UncertaintySources_"+string(JetType)+".txt";
  if(GetEra() == "2017") file = analysisdir + "/"+ string(GetEra())+ "/JEC/Summer19UL17_V5_MC_UncertaintySources_"+string(JetType)+".txt";
  if(GetEra() == "2018") file = analysisdir + "/"+ string(GetEra())+ "/JEC/Summer19UL18_V5_MC_UncertaintySources_"+string(JetType)+".txt";

 
  string sline;
  vector<string> SourceLines;
  bool ExtractLine=false;
  int nline(0);
  ifstream jec_file(file.c_str());  
  while(getline(jec_file,sline) ){
    if(ExtractLine){
      if(nline==0){nline++; continue;}
      if(sline.find("[")!=string::npos) break;
      if(nline==1)SourceLines.push_back(sline);
    }
    if(sline.find(source)!=string::npos) { ExtractLine=true;}
  }
  
  jec_file.close();
    
  cout << "Setting up JEC uncertainty vector for source ["<<source<< "]." << file << endl;

  std::map<float, std::vector<float> > etaptmap, eta_uncupmap, eta_uncdownmap;
  for(unsigned int ilines =0; ilines <  SourceLines.size(); ilines++){
    
    string line = SourceLines[ilines];
    std::istringstream is( line );
    
    std::string s_eta_min, s_eta_max, s_nBins;
    is >> s_eta_min; 
    is >> s_eta_max;  
    is >> s_nBins;

    double  eta_min = stod(s_eta_min);
    double  eta_max = stod(s_eta_max);
    double  nBins = stod(s_nBins);

    bool EtaBinCheck=true;
    if((ilines == SourceLines.size() -1)){
      if( eta_min != 5.0) EtaBinCheck=false;
      if( eta_max != 5.4) EtaBinCheck=false;
    }
    if(!EtaBinCheck){
      cout << "[AnalyzerCore::SetupJECUncertainty] Eta bin set incorrectly ..." << endl;
      exit(EXIT_FAILURE);      
    }
    std::vector<float> ptbin, unc_up, unc_down;
    bool finalbin(false);
    
    for(int i=0; i < nBins; i++){
      std::string  subString;
      is >> subString;
      double value_from_string =  stod(subString);
      if((i %3) == 0) {	ptbin.push_back(value_from_string); if( i == nBins-3) finalbin=true; }
      if((i %3) == 1) {unc_up.push_back(value_from_string);}
      if((i %3) == 2) {unc_down.push_back(value_from_string);}
      
      // Check Final bin is last bin in txt file for this eta bin
      if((i %3) == 2 && finalbin) {
	string CheckFinalPt; 
	is >> CheckFinalPt;
	if(!CheckFinalPt.empty()) {
	  cout << "[AnalyzerCore::SetupJECUncertainty] Last pt bin of  set incorrectly ..." << endl;
	  exit(EXIT_FAILURE);
	}
      }
    }
    
    etaptmap[eta_min] = ptbin;
    eta_uncupmap[eta_min] =  unc_up;
    eta_uncdownmap[eta_min] = unc_down;
    
    std::vector<float> NULLBin;
    if(ilines ==  SourceLines.size() -1) etaptmap[eta_max] = NULLBin;
  }
        

  jec_file.close();
  std::vector<std::map<float, std::vector<float> > > vec_unc;
  vec_unc.push_back(etaptmap);
  vec_unc.push_back(eta_uncupmap);
  vec_unc.push_back(eta_uncdownmap);

  
  if(JetType=="AK4PFchs") AK4CHSJECUncMap[source] = vec_unc;
  if(JetType=="AK4PFPuppi") AK4PUPPIJECUncMap[source] = vec_unc;
  if(JetType=="AK8PFchs") AK8CHSJECUncMap[source] = vec_unc;
  if(JetType=="AK8PFPuppi") AK8PUPPIJECUncMap[source] = vec_unc;
  return;
  
}



std::vector<Muon> AnalyzerCore::GetAllMuons(){

  std::vector<Muon> out;
  if(!muon_pt) return out;
  for(unsigned int i=0; i<muon_pt->size(); i++){

    Muon mu;

    mu.SetCharge(muon_charge->at(i));
    mu.SetMiniAODPt(muon_pt->at(i));
    mu.SetMiniAODTunePPt(muon_TuneP_pt->at(i));

    double rc = muon_roch_sf->at(i);
    double rc_err = muon_roch_sf_up->at(i)-rc;
    //==== For the Rochester corection, up and down err are the same
    mu.SetMomentumScaleUpDown( muon_pt->at(i) * (rc+rc_err), muon_pt->at(i) * (rc-rc_err)  );
    mu.SetPtEtaPhiM(muon_pt->at(i)*rc, muon_eta->at(i), muon_phi->at(i), muon_mass->at(i));

    //==== TuneP
    //==== Apply scailing later with AnalyzerCore::UseTunePMuon()
    mu.SetTuneP4(muon_TuneP_pt->at(i), muon_TuneP_ptError->at(i), muon_TuneP_eta->at(i), muon_TuneP_phi->at(i), muon_TuneP_charge->at(i));

    mu.SetMVA(muon_MVA->at(i));

    mu.SetdXY(muon_dxyVTX->at(i), muon_dxyerrVTX->at(i));
    mu.SetdZ(muon_dzVTX->at(i), muon_dzerrVTX->at(i));
    mu.SetIP3D(muon_3DIPVTX->at(i), muon_3DIPerrVTX->at(i));
    mu.SetTypeBit(muon_TypeBit->at(i));
    mu.SetIDBit(muon_IDBit->at(i));
    mu.SetisPOGHighPt(muon_ishighpt->at(i));
    mu.SetPOGMediumHIP(muon_ismedium_hip->at(i),muon_ismedium_nohip->at(i));
    mu.SetChi2(muon_normchi->at(i));
    mu.SetIso(muon_PfChargedHadronIsoR04->at(i),muon_PfNeutralHadronIsoR04->at(i),muon_PfGammaIsoR04->at(i),muon_PFSumPUIsoR04->at(i),muon_trkiso->at(i));
    mu.SetTrackerLayers(muon_trackerLayers->at(i));

    //==== Should be set after Eta is set
    mu.SetMiniIso(
      muon_PfChargedHadronMiniIso->at(i), 
      muon_PfNeutralHadronMiniIso->at(i), 
      muon_PfGammaMiniIso->at(i), 
      muon_PFSumPUMiniIso->at(i),
      Rho,
      mu.EA()
    );

    mu.SetFilterBits(muon_filterbits->at(i));
    mu.SetPathBits(muon_pathbits->at(i));

    //[jhchoi] Add Muon variables for ID
    mu.SetTrackerHits(muon_trackerHits->at(i));
    mu.SetPixelHits(muon_pixelHits->at(i));
    mu.SetValidMuonHits(muon_validmuonhits->at(i));
    mu.SetMatchedStations(muon_matchedstations->at(i));



    out.push_back(mu);

  }
  return out;

}

std::vector<Muon> AnalyzerCore::GetMuons(TString id, double ptmin, double fetamax){

  std::vector<Muon> muons = GetAllMuons();
  std::vector<Muon> out;
  for(unsigned int i=0; i<muons.size(); i++){
    if(!( muons.at(i).Pt()>ptmin )){
      //cout << "Fail Pt : pt = " << muons.at(i).Pt() << ", cut = " << ptmin << endl;
      continue;
    }
    if(!( fabs(muons.at(i).Eta())<fetamax )){
      //cout << "Fail Eta : eta = " << fabs(muons.at(i).Eta()) << ", cut = " << fetamax << endl;
      continue;
    }
    if(!( muons.at(i).PassID(id) )){
      //cout << "Fail ID" << endl;
      continue;
    }
    out.push_back( muons.at(i) );
  }
  return out;

}

std::vector<Electron> AnalyzerCore::GetAllElectrons(){

  std::vector<Electron> out;
  if(!electron_Energy) return out;
  for(unsigned int i=0; i<electron_Energy->size(); i++){

    Electron el;

    el.SetEnShift(  electron_Energy_Scale_Up->at(i)/electron_Energy->at(i), electron_Energy_Scale_Down->at(i)/electron_Energy->at(i) );
    el.SetResShift( electron_Energy_Smear_Up->at(i)/electron_Energy->at(i), electron_Energy_Smear_Down->at(i)/electron_Energy->at(i) );

    el.SetPtEtaPhiE(1., electron_eta->at(i), electron_phi->at(i), electron_Energy->at(i));
    double el_theta = el.Theta();
    double el_pt = electron_Energy->at(i) * TMath::Sin( el_theta );
    el.SetPtEtaPhiE( el_pt, electron_eta->at(i), electron_phi->at(i), electron_Energy->at(i));

    el.SetUncorrE(electron_EnergyUnCorr->at(i));
    el.SetSC(electron_scEta->at(i), electron_scPhi->at(i), electron_scEnergy->at(i));
    el.SetCharge(electron_charge->at(i));
    el.SetdXY(electron_dxyVTX->at(i), electron_dxyerrVTX->at(i));
    el.SetdZ(electron_dzVTX->at(i), electron_dzerrVTX->at(i));
    el.SetIP3D(electron_3DIPVTX->at(i), electron_3DIPerrVTX->at(i));
    el.SetMVA(electron_MVAIso->at(i), electron_MVANoIso->at(i));
    el.SetPassConversionVeto(electron_passConversionVeto->at(i));
    el.SetNMissingHits(electron_mHits->at(i));
    el.SetRho(Rho);
    el.SetIsGsfCtfScPixChargeConsistent(electron_isGsfCtfScPixChargeConsistent->at(i));
    el.SetR9(electron_r9->at(i));
    el.SetL1Et(electron_l1et->at(i));

    el.SetCutBasedIDVariables(
      electron_Full5x5_SigmaIEtaIEta->at(i),
      electron_dEtaInSeed->at(i),
      electron_dPhiIn->at(i),
      electron_HoverE->at(i),
      electron_InvEminusInvP->at(i),
      electron_e2x5OverE5x5->at(i),
      electron_e1x5OverE5x5->at(i),
      electron_trackIso->at(i),
      electron_dr03EcalRecHitSumEt->at(i),
      electron_dr03HcalDepth1TowerSumEt->at(i),
      electron_dr03HcalTowerSumEt->at(i),
      electron_dr03TkSumPt->at(i),
      electron_ecalPFClusterIso->at(i),
      electron_hcalPFClusterIso->at(i),
      electron_ecalDriven->at(i)
    );

    el.SetIDBit(electron_IDBit->at(i));
    vector<int> temp_idcutbit;
    for(unsigned int j=0; j<Electron::N_SELECTOR; j++){
      temp_idcutbit.push_back( electron_IDCutBit->at( i*Electron::N_SELECTOR + j ) );
    }
    el.SetIDCutBit(temp_idcutbit);
    el.SetRelPFIso_Rho(electron_RelPFIso_Rho->at(i));

    //==== Should be ran after SCeta is set
    el.SetMiniIso(
      electron_chMiniIso->at(i),
      electron_nhMiniIso->at(i),
      electron_phMiniIso->at(i),
      electron_puChMiniIso->at(i),
      Rho,
      el.EA()
    );

    el.SetFilterBits(electron_filterbits->at(i));
    el.SetPathBits(electron_pathbits->at(i));

    out.push_back(el);

  }
  return out;

}

std::vector<Electron> AnalyzerCore::GetElectrons(TString id, double ptmin, double fetamax, bool vetoHEM){

  std::vector<Electron> electrons = GetAllElectrons();
  std::vector<Electron> out;
  for(unsigned int i=0; i<electrons.size(); i++){
    if(!( electrons.at(i).Pt()>ptmin )){
      //cout << "Fail Pt : pt = " << electrons.at(i).Pt() << ", cut = " << ptmin << endl;
      continue;
    }
    if(!( fabs(electrons.at(i).scEta())<fetamax )){
      //cout << "Fail Eta : eta = " << fabs(electrons.at(i).scEta()) << ", cut = " << fetamax << endl;
      continue;
    }
    if(!( electrons.at(i).PassID(id) )){
      //cout << "Fail ID" << endl;
      continue;
    }
    if(vetoHEM){
      if ( FindHEMElectron (electrons.at(i)) ){
        continue;
      }
    }

    out.push_back( electrons.at(i) );
  }
  return out;

}


std::vector<Tau> AnalyzerCore::GetAllTaus(){

  std::vector<Tau> out;
  if(!tau_pt) return out;
  for(unsigned int i=0; i<tau_pt->size(); i++){

    Tau tau;
    tau.SetCharge(tau_charge->at(i));
    tau.SetPtEtaPhiM(tau_pt->at(i), tau_eta->at(i), tau_phi->at(i), tau_mass->at(i));
    tau.SetDecayMode(tau_decaymode->at(i));
    tau.SetdXY(tau_dxy->at(i),0.);
    tau.SetdZ(tau_dz->at(i),0.);
    tau.SetDecayModeNewDM(tau_idDecayModeNewDMs->at(i));
    tau.SetIDBit(tau_IDBit->at(i));

    out.push_back(tau);

  }
  return out;

}



std::vector<Tau> AnalyzerCore::GetTaus(TString id, double ptmin, double fetamax){

  std::vector<Tau> taus = GetAllTaus();
  std::vector<Tau> out;

  for(unsigned int i=0; i<taus.size(); i++){
    if(!( taus.at(i).Pt()>ptmin )){
      continue;
    }
    if(!( fabs(taus.at(i).Eta())<fetamax )){
      continue;
    }
    if(!( taus.at(i).PassID(id) )){
      continue;
    }
    out.push_back( taus.at(i) );
  }
  return out;

}



std::vector<Lepton *> AnalyzerCore::MakeLeptonPointerVector(const std::vector<Muon>& muons, double TightIso, bool UseMini){

  std::vector<Lepton *> out;
  for(unsigned int i=0; i<muons.size(); i++){
    Lepton *l = (Lepton *)(&muons.at(i));
    if( !(l->LeptonFlavour() == Lepton::MUON) ){
      cout << "[AnalyzerCore::MakeLeptonPointerVector(std::vector<Muon>& muons)] Not muon.." << endl;
      exit(EXIT_FAILURE);
    }
    if(TightIso>0){

      double this_RelIso = l->RelIso();
      if(UseMini) this_RelIso = l->MiniRelIso();
      double ptcone = l->CalcPtCone(this_RelIso, TightIso);
      l->SetPtCone( ptcone );

    }
    out.push_back(l);
  }
  return out;

}
std::vector<Lepton *> AnalyzerCore::MakeLeptonPointerVector(const std::vector<Electron>& electrons, double TightIso, bool UseMini){

  std::vector<Lepton *> out;
  for(unsigned int i=0; i<electrons.size(); i++){
    Lepton *l = (Lepton *)(&electrons.at(i));
    if( !(l->LeptonFlavour() == Lepton::ELECTRON) ){
      cout << "[AnalyzerCore::MakeLeptonPointerVector(std::vector<ELECTRON>& electrons)] Not electron.." << endl;
      exit(EXIT_FAILURE);
    }
    if(TightIso>0){

      double this_RelIso = l->RelIso();
      if(UseMini) this_RelIso = l->MiniRelIso();
      double ptcone = l->CalcPtCone(this_RelIso, TightIso);
      l->SetPtCone( ptcone );

    }
    out.push_back(l);
  }
  return out;

}



std::vector<Photon> AnalyzerCore::GetAllPhotons(){

  std::vector<Photon> out;
  for(unsigned int i=0; i<photon_Energy->size(); i++){
    
    Photon pho;

    pho.SetPtEtaPhiE(1., photon_eta->at(i), photon_phi->at(i), photon_Energy->at(i));
    double pho_theta = pho.Theta();
    double pho_pt = photon_Energy->at(i) * TMath::Sin( pho_theta );
    pho.SetPtEtaPhiE( pho_pt, photon_eta->at(i), photon_phi->at(i), photon_Energy->at(i));

    pho.SetSC(photon_scEta->at(i), photon_scPhi->at(i));
    pho.SetRho(Rho);

    pho.SetCutBasedIDVariables(
      photon_Full5x5_SigmaIEtaIEta->at(i),
      photon_HoverE->at(i),
      photon_ChIsoWithEA->at(i),
      photon_NhIsoWithEA->at(i),
      photon_PhIsoWithEA->at(i)
    );
    
    std::vector<bool> ids = {
      photon_passLooseID->at(i),
      photon_passMediumID->at(i),
      photon_passTightID->at(i),
      photon_passMVAID_WP80->at(i),
      photon_passMVAID_WP90->at(i)
     };
    pho.SetPOGIDs(ids);
        
    out.push_back(pho);
    
  }
  return out;
  
}

std::vector<Photon> AnalyzerCore::GetPhotons(TString id, double ptmin, double fetamax){

  std::vector<Photon> photons = GetAllPhotons();
  std::vector<Photon> out;
  for(unsigned int i=0; i<photons.size(); i++){
    if(!( photons.at(i).Pt()>ptmin )){
      continue;
    }
    if(!( fabs(photons.at(i).scEta())<fetamax )){
      continue;
    }
    if(!( photons.at(i).PassID(id) )){
      continue;
    }
    out.push_back( photons.at(i) );
  }
  return out;
}
//jhchoi---MET jer smear
TLorentzVector AnalyzerCore::UpdateMETByJERsmearing_given_MET(double met_orig_pt, double met_orig_phi, double dmet_x, double dmet_y){
  TLorentzVector met_orig;
  met_orig.SetPtEtaPhiM(met_orig_pt,0.,met_orig_phi,0.);
  double met_x = met_orig.Px();
  double met_y = met_orig.Py();
  met_x = met_x + dmet_x;
  met_y = met_y + dmet_y;
  TLorentzVector METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;
  
}
void AnalyzerCore::UpdateMETBySmearNominal(){
  InitMETSmeared();
  double px_orig=0., py_orig=0.;
  double px_corrected=0., py_corrected=0.;
  
  for(unsigned int i=0; i<jet_pt->size(); i++){
    Jet jet;
    jet.SetPtEtaPhiM(jet_pt->at(i), jet_eta->at(i), jet_phi->at(i), jet_m->at(i));
    px_orig+= jet.Px();
    py_orig+= jet.Py();

    Jet jet_smeared= jet;
    jet_smeared*=jet_smearedRes->at(i);
    px_corrected += jet.Px()*jet_smearedRes->at(i);
    py_corrected += jet.Py()*jet_smearedRes->at(i);
    
  }
  double dmet_x=px_orig - px_corrected;
  double dmet_y=py_orig - py_corrected;

  //pfMET,pfMET_Type1,pfMET_Type1_PhiCor,PuppiMET,PuppiMET_Type1,PuppiMET_Type1_PhiCor
  TLorentzVector pfMET_JerSmear=UpdateMETByJERsmearing_given_MET(pfMET_pt,pfMET_phi,dmet_x,dmet_y);
  pfMET_JerSmear_pt=pfMET_JerSmear.Pt(); pfMET_JerSmear_phi=pfMET_JerSmear.Phi();

  TLorentzVector pfMET_Type1_JerSmear=UpdateMETByJERsmearing_given_MET(pfMET_Type1_pt,pfMET_Type1_phi,dmet_x,dmet_y);
  pfMET_Type1_JerSmear_pt=pfMET_Type1_JerSmear.Pt(); pfMET_Type1_JerSmear_phi=pfMET_Type1_JerSmear.Phi();
    
  TLorentzVector pfMET_Type1_PhiCor_JerSmear=UpdateMETByJERsmearing_given_MET(pfMET_Type1_PhiCor_pt,pfMET_Type1_PhiCor_phi,dmet_x,dmet_y);
  pfMET_Type1_PhiCor_JerSmear_pt=pfMET_Type1_PhiCor_JerSmear.Pt(); pfMET_Type1_PhiCor_JerSmear_phi=pfMET_Type1_PhiCor_JerSmear.Phi();
  
  TLorentzVector PuppiMET_JerSmear=UpdateMETByJERsmearing_given_MET(PuppiMET_pt,PuppiMET_phi,dmet_x,dmet_y);
  PuppiMET_JerSmear_pt=PuppiMET_JerSmear.Pt(); PuppiMET_JerSmear_phi=PuppiMET_JerSmear.Phi();
  
  TLorentzVector PuppiMET_Type1_JerSmear=UpdateMETByJERsmearing_given_MET(PuppiMET_Type1_pt,PuppiMET_Type1_phi,dmet_x,dmet_y);
  PuppiMET_Type1_JerSmear_pt=PuppiMET_Type1_JerSmear.Pt(); PuppiMET_Type1_JerSmear_phi=PuppiMET_Type1_JerSmear.Phi();
  
  TLorentzVector PuppiMET_Type1_PhiCor_JerSmear=UpdateMETByJERsmearing_given_MET(PuppiMET_Type1_PhiCor_pt,PuppiMET_Type1_PhiCor_phi,dmet_x,dmet_y);
  PuppiMET_Type1_PhiCor_JerSmear_pt=PuppiMET_Type1_PhiCor_JerSmear.Pt(); PuppiMET_Type1_PhiCor_JerSmear_phi=PuppiMET_Type1_PhiCor_JerSmear.Phi();
}
void AnalyzerCore::InitMETSmeared(){
  pfMET_JerSmear_pt=pfMET_pt;
  pfMET_JerSmear_phi=pfMET_phi;
  pfMET_Type1_JerSmear_pt=pfMET_Type1_pt;
  pfMET_Type1_JerSmear_phi=pfMET_Type1_phi;
  pfMET_Type1_PhiCor_JerSmear_pt=pfMET_Type1_PhiCor_pt;
  pfMET_Type1_PhiCor_JerSmear_phi=pfMET_Type1_PhiCor_phi;
  PuppiMET_JerSmear_pt=PuppiMET_pt;
  PuppiMET_JerSmear_phi=PuppiMET_phi;
  PuppiMET_Type1_JerSmear_pt=PuppiMET_Type1_pt;
  PuppiMET_Type1_JerSmear_phi=PuppiMET_Type1_phi;
  PuppiMET_Type1_PhiCor_JerSmear_pt=PuppiMET_Type1_PhiCor_pt;
  PuppiMET_Type1_PhiCor_JerSmear_phi=PuppiMET_Type1_PhiCor_phi;
}
//---[end]met jer smear 
std::vector<Jet> AnalyzerCore::GetAllJets(){

  std::vector<Jet> out;
  for(unsigned int i=0; i<jet_pt->size(); i++){
    Jet jet;
    jet.SetPtEtaPhiM(jet_pt->at(i), jet_eta->at(i), jet_phi->at(i), jet_m->at(i));

    //==== Jet energy up and down are 1.xx or 0.99, not energy
    jet.SetEnShift( jet_shiftedEnUp->at(i), jet_shiftedEnDown->at(i) );
    if(!IsDATA){
      

      jet *= jet_smearedRes->at(i);

      //jhchoi
      //---need to correct--// jer nom jer up jer down must have the same random seed. But skflat maker assigns the seed independently....
      double ResShiftUp=jet_smearedResUp->at(i)/jet_smearedRes->at(i);
      double ResShiftDown=jet_smearedResDown->at(i)/jet_smearedRes->at(i);
      /*
      bool ResNomBetweenUpDown=true;

      if(  (ResShiftUp-1)*(ResShiftDown-1) > 0){
	ResNomBetweenUpDown=false;
	ResShiftUp=1;
	ResShiftDown=1;//no jer syst is applied temporarilty
      }
      */
      //jet.SetResShift( jet_smearedResUp->at(i)/jet_smearedRes->at(i), jet_smearedResDown->at(i)/jet_smearedRes->at(i) ); //orig
      jet.SetResShift(ResShiftUp,ResShiftDown);
      jet.SetGenFlavours(jet_partonFlavour->at(i), jet_hadronFlavour->at(i));
      jet.SetGenHFHadronMatcher(jet_GenHFHadronMatcher_flavour->at(i),jet_GenHFHadronMatcher_origin->at(i));
    }
    jet.SetBJetNNCorrection(jet_bJetNN_corr->at(i),jet_bJetNN_res->at(i));
    jet.SetCJetNNCorrection(jet_cJetNN_corr->at(i),jet_cJetNN_res->at(i));
    jet.SetCharge(jet_charge->at(i));

    jet.SetArea(jet_area->at(i));
    std::vector<double> tvs = {
      jet_DeepCSV->at(i),
      jet_DeepCSV_CvsL->at(i),
      jet_DeepCSV_CvsB->at(i),
      jet_DeepJet->at(i),
      jet_DeepJet_CvsL->at(i),
      jet_DeepJet_CvsB->at(i),
    };
    jet.SetTaggerResults(tvs);
    jet.SetEnergyFractions(jet_chargedHadronEnergyFraction->at(i), jet_neutralHadronEnergyFraction->at(i), jet_neutralEmEnergyFraction->at(i), jet_chargedEmEnergyFraction->at(i), jet_muonEnergyFraction->at(i));
    jet.SetMultiplicities(jet_chargedMultiplicity->at(i), jet_neutralMultiplicity->at(i));
    jet.SetPileupJetId(jet_PileupJetId->at(i));
    jet.SetTightJetID(jet_tightJetID->at(i));
    jet.SetTightLepVetoJetID(jet_tightLepVetoJetID->at(i));

    //jet.Set_vtxNtracks(jet_vtxNtracks->at(i));

    out.push_back(jet);
  }

  return out;

}

std::vector<Jet> AnalyzerCore::GetJets(TString id, double ptmin, double fetamax){

  std::vector<Jet> jets = GetAllJets();
  std::vector<Jet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    if(!( jets.at(i).Pt()>ptmin )){
      //cout << "Fail Pt : pt = " << jets.at(i).Pt() << ", cut = " << ptmin << endl;
      continue;
    }
    if(!( fabs(jets.at(i).Eta())<fetamax )){
      //cout << "Fail Eta : eta = " << fabs(jets.at(i).Eta()) << ", cut = " << fetamax << endl;
      continue;
    }
    if(!( jets.at(i).PassID(id) )){
      //cout << "Fail ID" << endl;
      continue;
    }
    out.push_back( jets.at(i) );
  }
  return out;

}

std::vector<FatJet> AnalyzerCore::GetAllFatJets(){

  std::vector<FatJet> out;
  for(unsigned int i=0; i<fatjet_pt->size(); i++){
    FatJet jet;
    jet.SetPtEtaPhiM(fatjet_pt->at(i), fatjet_eta->at(i), fatjet_phi->at(i), fatjet_m->at(i));
    jet.SetEnShift( fatjet_shiftedEnUp->at(i), fatjet_shiftedEnDown->at(i) );
    if(!IsDATA){
      jet *= fatjet_smearedRes->at(i);
      jet.SetResShift( fatjet_smearedResUp->at(i)/fatjet_smearedRes->at(i), fatjet_smearedResDown->at(i)/fatjet_smearedRes->at(i) );
    }
    jet.SetCharge(fatjet_charge->at(i));

    jet.SetArea(fatjet_area->at(i));
    jet.SetGenFlavours(fatjet_partonFlavour->at(i), fatjet_hadronFlavour->at(i));
    std::vector<double> tvs = {
      fatjet_DeepCSV->at(i),
      fatjet_DeepCSV_CvsL->at(i),
      fatjet_DeepCSV_CvsB->at(i),
      fatjet_particleNet_TvsQCD->at(i),
      fatjet_particleNet_WvsQCD->at(i),
      fatjet_particleNet_ZvsQCD->at(i),
      fatjet_particleNet_HbbvsQCD->at(i),
      fatjet_particleNet_HccvsQCD->at(i),
      fatjet_particleNet_H4qvsQCD->at(i),
      fatjet_particleNet_QCD->at(i),
      fatjet_particleNetMD_Xbb->at(i),
      fatjet_particleNetMD_Xcc->at(i),
      fatjet_particleNetMD_Xqq->at(i),
      fatjet_particleNetMD_QCD->at(i),
    };
    jet.SetTaggerResults(tvs);
    jet.SetEnergyFractions(fatjet_chargedHadronEnergyFraction->at(i), fatjet_neutralHadronEnergyFraction->at(i), fatjet_neutralEmEnergyFraction->at(i), fatjet_chargedEmEnergyFraction->at(i), fatjet_muonEnergyFraction->at(i));
    jet.SetMultiplicities(fatjet_chargedMultiplicity->at(i), fatjet_neutralMultiplicity->at(i));
    jet.SetLSF(fatjet_LSF->at(i), fatjet_LSFlep_PID->at(i));
    jet.SetTightJetID(fatjet_tightJetID->at(i));
    jet.SetTightLepVetoJetID(fatjet_tightLepVetoJetID->at(i));
    jet.SetPuppiTaus(fatjet_puppi_tau1->at(i), fatjet_puppi_tau2->at(i), fatjet_puppi_tau3->at(i), fatjet_puppi_tau4->at(i));
    jet.SetSDMass(fatjet_softdropmass->at(i));

    out.push_back(jet);
  }

  return out;

}

std::vector<FatJet> AnalyzerCore::GetFatJets(TString id, double ptmin, double fetamax){

  std::vector<FatJet> jets = GetAllFatJets();
  std::vector<FatJet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    if(!( jets.at(i).Pt()>ptmin )){
      //cout << "Fail Pt : pt = " << jets.at(i).Pt() << ", cut = " << ptmin << endl;
      continue;
    }
    if(!( fabs(jets.at(i).Eta())<fetamax )){
      //cout << "Fail Eta : eta = " << fabs(jets.at(i).Eta()) << ", cut = " << fetamax << endl;
      continue;
    }
    if(!( jets.at(i).PassID(id) )){
      //cout << "Fail ID" << endl;
      continue;
    }
    out.push_back( jets.at(i) );
  }
  return out;

}

std::vector<Gen> AnalyzerCore::GetGens(){

  std::vector<Gen> out;
  if(IsDATA) return out;

  for(unsigned int i=0; i<gen_pt->size(); i++){

    Gen gen;

    gen.SetIsEmpty(false);
    gen.SetPtEtaPhiM(gen_pt->at(i), gen_eta->at(i), gen_phi->at(i), gen_mass->at(i));
    gen.SetCharge(gen_charge->at(i));
    gen.SetIndexPIDStatus(i, gen_PID->at(i), gen_status->at(i));
    gen.SetMother(gen_mother_index->at(i));
    gen.SetGenStatusFlag_isPrompt( gen_isPrompt->at(i) );
    gen.SetGenStatusFlag_isPromptFinalState( gen_isPromptFinalState->at(i) );
    gen.SetGenStatusFlag_isTauDecayProduct( gen_isTauDecayProduct->at(i) );
    gen.SetGenStatusFlag_isPromptTauDecayProduct( gen_isPromptTauDecayProduct->at(i) );
    gen.SetGenStatusFlag_isDirectPromptTauDecayProductFinalState( gen_isDirectPromptTauDecayProductFinalState->at(i) );
    gen.SetGenStatusFlag_isHardProcess( gen_isHardProcess->at(i) );
    gen.SetGenStatusFlag_isLastCopy( gen_isLastCopy->at(i) );
    gen.SetGenStatusFlag_isLastCopyBeforeFSR( gen_isLastCopyBeforeFSR->at(i) );
    gen.SetGenStatusFlag_isPromptDecayed( gen_isPromptDecayed->at(i) );
    gen.SetGenStatusFlag_isDecayedLeptonHadron( gen_isDecayedLeptonHadron->at(i) );
    gen.SetGenStatusFlag_fromHardProcessBeforeFSR( gen_fromHardProcessBeforeFSR->at(i) );
    gen.SetGenStatusFlag_fromHardProcessDecayed( gen_fromHardProcessDecayed->at(i) );
    gen.SetGenStatusFlag_fromHardProcessFinalState( gen_fromHardProcessFinalState->at(i) );
    gen.SetGenStatusFlag_isMostlyLikePythia6Status3( gen_isMostlyLikePythia6Status3->at(i) );

    out.push_back(gen);

  }

  return out;

}

std::vector<LHE> AnalyzerCore::GetLHEs(){

  std::vector<LHE> out;
  if(IsDATA) return out;

  for(unsigned int i=0; i<LHE_Px->size(); i++){

    LHE lhe;

    lhe.SetPxPyPzE(LHE_Px->at(i), LHE_Py->at(i), LHE_Pz->at(i), LHE_E->at(i));
    lhe.SetIndexIDStatus(i, LHE_ID->at(i), LHE_Status->at(i));

    out.push_back(lhe);

  }

  return out;

}

std::vector<Muon> AnalyzerCore::UseTunePMuon(const std::vector<Muon>& muons){

  std::vector<Muon> out;
  for(unsigned int i=0; i<muons.size(); i++){
    //==== muons is a const vector. So in this function, we have to copy the elements like below
    Muon this_muon=muons.at(i);

    Particle this_tunep4 = this_muon.TuneP4();

    //==== Momentum scaling
    //==== 1) if tuneP Pt < 200 -> Rochester
    //==== 2) if tuneP pt >= 200 -> Generalized Endpoint

    double new_pt( this_tunep4.Pt() ), new_pt_up( this_tunep4.Pt() ), new_pt_down( this_tunep4.Pt() );
    if(this_tunep4.Pt()<200){

      //==== 19/03/24 (jskim) : For 99% of the muons, MiniAODPt and TunePPt are same
      //==== we can just use MiniAODPt * RochesterCorrection, multiplied by (TuneP Pt)/(MiniAODPt)
      double TunePOverPt = this_tunep4.Pt() / this_muon.MiniAODPt();
      new_pt      = TunePOverPt * this_muon.Pt(); // this_muon.Pt() = MiniAODPt * RochesterCorrection
      new_pt_up   = TunePOverPt * this_muon.MomentumShift(+1);
      new_pt_down = TunePOverPt * this_muon.MomentumShift(-1);

/*
      cout << "## Rochester ##" << endl;
      cout << "this_muon.MiniAODPt() = " << this_muon.MiniAODPt() << endl;
      cout << "this_muon.MiniAODTunePPt() = " << this_muon.MiniAODTunePPt() << endl;
      cout << "new_pt = " << new_pt << endl;
      cout << "new_pt_up = " << new_pt_up << endl;
      cout << "new_pt_down = " << new_pt_down << endl;
*/

    }
    else{

      //==== Unlike rochester, GE method should be only applied to MC

      if(!IsDATA){

        //==== ScaledPts defined in GeneralizedEndpointPt.h ..

        ScaledPts ptvalues;
        //==== TODO FIXME
        //==== 19/09/02 : There is no GEScaleSyst map for 2016
        if(DataYear==2016) ptvalues = muonGE->GeneralizedEndpointPt(this_tunep4.Pt(), this_tunep4.Charge(), this_tunep4.Eta(), this_tunep4.Phi()*180./M_PI, event);
        else ptvalues = muonGEScaleSyst->GEPt(DataYear, this_tunep4.Pt(), this_tunep4.Eta(), this_tunep4.Phi(), this_tunep4.Charge());

        new_pt = ptvalues.ScaledPt;
        //==== Mode == 1 : Kappa up
        //==== Mode == 2 : Kappa down
        new_pt_up = ptvalues.ScaeldPt_Up;
        new_pt_down = ptvalues.ScaeldPt_Down;

/*
        cout << "## GeneralizedEndpointPt ##" << endl;
        cout << "old_pt = " << this_tunep4.Pt() << endl;
        cout << "new_pt = " << new_pt << endl;
        cout << "new_pt_up = " << new_pt_up << endl;
        cout << "new_pt_down = " << new_pt_down << endl;
*/

      }

    }

    //==== Scale the pt
    this_muon.SetPtEtaPhiM( new_pt, this_tunep4.Eta(), this_tunep4.Phi(), this_tunep4.M() );
    this_muon.SetMomentumScaleUpDown(new_pt_up,new_pt_down);
    this_muon.SetCharge( this_tunep4.Charge() );
    this_muon.SetMiniAODPt( this_muon.MiniAODTunePPt() );

/*
    cout << "@@@@ TuneP @@@@" << endl;
    cout << "this_muon.Pt() = " << this_muon.Pt() << endl;
    cout << "this_muon.MiniAODPt() = " << this_muon.MiniAODPt() << endl;
    cout << "this_muon.MiniAODTunePPt() = " << this_muon.MiniAODTunePPt() << endl;
    cout << "this_muon.MomentumShift(0) = " << this_muon.MomentumShift(0) << endl;
    cout << "this_muon.MomentumShift(+1) = " << this_muon.MomentumShift(+1) << endl;
    cout << "this_muon.MomentumShift(-1) = " << this_muon.MomentumShift(-1) << endl;
*/

    out.push_back(this_muon);
  }

  return out;

}

std::vector<Muon> AnalyzerCore::SelectMuons(const std::vector<Muon>& muons, TString id, double ptmin, double fetamax){

  std::vector<Muon> out;
  for(unsigned int i=0; i<muons.size(); i++){
    if(!( muons.at(i).Pt()>ptmin )){
      //cout << "Fail Pt : pt = " << muons.at(i).Pt() << ", cut = " << ptmin << endl;
      continue;
    }
    if(!( fabs(muons.at(i).Eta())<fetamax )){
      //cout << "Fail Eta : eta = " << fabs(muons.at(i).Eta()) << ", cut = " << fetamax << endl;
      continue;
    }
    if(!( muons.at(i).PassID(id) )){
      //cout << "Fail ID" << endl;
      continue;
    }
    out.push_back( muons.at(i) );
  }
  return out;

}

std::vector<Electron> AnalyzerCore::SelectElectrons(const std::vector<Electron>& electrons, TString id, double ptmin, double fetamax, bool vetoHEM){

  std::vector<Electron> out;
  for(unsigned int i=0; i<electrons.size(); i++){
    if(!( electrons.at(i).Pt()>ptmin )){
      //cout << "Fail Pt : pt = " << electrons.at(i).Pt() << ", cut = " << ptmin << endl;
      continue;
    }
    if(!( fabs(electrons.at(i).scEta())<fetamax )){
      //cout << "Fail Eta : eta = " << fabs(electrons.at(i).scEta()) << ", cut = " << fetamax << endl;
      continue;
    }
    if(!( electrons.at(i).PassID(id) )){
      //cout << "Fail ID" << endl;
      continue;
    }
    if(vetoHEM){
      if ( FindHEMElectron (electrons.at(i)) ){
        continue;
      }
    }

    out.push_back(electrons.at(i));
  }
  return out;

}


std::vector<Tau> AnalyzerCore::SelectTaus(const std::vector<Tau>& taus, TString id, double ptmin, double fetamax){

  std::vector<Tau> out;
  for(unsigned int i=0; i<taus.size(); i++){
    if(!( taus.at(i).Pt()>ptmin )){

      continue;
    }
    if(!( fabs(taus.at(i).Eta())<fetamax )){

      continue;
    }
    if(!( taus.at(i).PassID(id) )){
      continue;
    }
    out.push_back( taus.at(i) );
  }
  return out;

}

std::vector<Jet> AnalyzerCore::SelectJets(const std::vector<Jet>& jets, TString id, double ptmin, double fetamax){

  std::vector<Jet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    if(!( jets.at(i).Pt()>ptmin )){
      //cout << "Fail Pt : pt = " << jets.at(i).Pt() << ", cut = " << ptmin << endl;
      continue;
    }
    if(!( fabs(jets.at(i).Eta())<fetamax )){
      //cout << "Fail Eta : eta = " << fabs(jets.at(i).Eta()) << ", cut = " << fetamax << endl;
      continue;
    }
    if(!( jets.at(i).PassID(id) )){
      //cout << "Fail ID" << endl;
      continue;
    }
    out.push_back( jets.at(i) );
  }
  return out;

}

std::vector<FatJet> AnalyzerCore::SelectFatJets(const std::vector<FatJet>& jets, TString id, double ptmin, double fetamax){

  std::vector<FatJet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    if(!( jets.at(i).Pt()>ptmin )){
      //cout << "Fail Pt : pt = " << jets.at(i).Pt() << ", cut = " << ptmin << endl;
      continue;
    }
    if(!( fabs(jets.at(i).Eta())<fetamax )){
      //cout << "Fail Eta : eta = " << fabs(jets.at(i).Eta()) << ", cut = " << fetamax << endl;
      continue;
    }
    if(!( jets.at(i).PassID(id) )){
      //cout << "Fail ID" << endl;
      continue;
    }
    out.push_back( jets.at(i) );
  }
  return out;

}

std::vector<Electron> AnalyzerCore::ScaleElectrons(const std::vector<Electron>& electrons, int sys){

  std::vector<Electron> out;
  for(unsigned int i=0; i<electrons.size(); i++){
    //==== electrons is a const vector. So in this function, we have to copy the elements like below
    Electron this_electron = electrons.at(i);

    double this_sf = this_electron.EnShift(sys);
    this_electron.SetPtEtaPhiM( this_electron.Pt() * this_sf, this_electron.Eta(), this_electron.Phi(), this_electron.M() );

    out.push_back( this_electron );
  }

  return out;

}
std::vector<Electron> AnalyzerCore::SmearElectrons(const std::vector<Electron>& electrons, int sys){

  std::vector<Electron> out;
  for(unsigned int i=0; i<electrons.size(); i++){
    //==== electrons is a const vector. So in this function, we have to copy the elements like below
    Electron this_electron = electrons.at(i);

    double this_sf = this_electron.ResShift(sys);
    this_electron.SetPtEtaPhiM( this_electron.Pt() * this_sf, this_electron.Eta(), this_electron.Phi(), this_electron.M() );

    out.push_back( this_electron );
  }

  return out;

}

bool AnalyzerCore::FindHEMElectron(Electron electron){

    if (DataYear != 2018) return false;

    if (electron.Eta() < -1.25){
        if((electron.Phi() < -0.82) && (electron.Phi() > -1.62)) return true;
    }

    return false;

}

std::vector<Muon> AnalyzerCore::ScaleMuons(const std::vector<Muon>& muons, int sys){

  std::vector<Muon> out;
  for(unsigned int i=0; i<muons.size(); i++){
    //==== muons is a const vector. So in this function, we have to copy the elements like below
    Muon this_muon = muons.at(i);

    //==== Even for TuneP muons, MomentumShift() are set correctly from AnalyzerCore::UseTunePMuon()
    //==== So we can just use MomentumShift()

    this_muon.SetPtEtaPhiM( this_muon.MomentumShift(sys), this_muon.Eta(), this_muon.Phi(), this_muon.M() );

    out.push_back(this_muon);

  }

  return out;

}

std::vector<Jet> AnalyzerCore::ScaleJets(const std::vector<Jet>& jets, int sys){

  std::vector<Jet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    //==== jets is a const vector. So in this function, we have to copy the elements like below
    Jet this_jet = jets.at(i);

    this_jet *= this_jet.EnShift(sys);

    out.push_back( this_jet );
  }

  return out;

}

std::vector<Jet> AnalyzerCore::ScaleJetsIndividualSource(const std::vector<Jet>& jets, int sys, TString source){

  if(!std::count(JECSources.begin(),JECSources.end(), source)) {
    cout << "[AnalyzerCore::ScaleJetsIndividualSource] source " << source << " was not found" << endl;
    exit(EXIT_FAILURE);
  }

  std::vector<Jet> out;
  for(unsigned int i=0; i<jets.size(); i++){

    Jet this_jet = jets.at(i);

    double get_shift = GetJECUncertainty(source , "AK4PFchs",this_jet.Eta(),this_jet.Pt(), sys);
    this_jet *= get_shift;

    out.push_back( this_jet );
  }

  return out;

}


std::vector<Jet> AnalyzerCore::SmearJets(const std::vector<Jet>& jets, int sys){
  
  std::vector<Jet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    //==== jets is a const vector. So in this function, we have to copy the elements like below
    Jet this_jet = jets.at(i);

    this_jet *= this_jet.ResShift(sys);

    out.push_back( this_jet );
  }

  return out;

}

std::vector<FatJet> AnalyzerCore::ScaleFatJets(const std::vector<FatJet>& jets, int sys){

  std::vector<FatJet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    //==== jets is a const vector. So in this function, we have to copy the elements like below
    FatJet this_jet = jets.at(i);

    this_jet *= this_jet.EnShift(sys);

    out.push_back( this_jet );
  }

  return out;

}
std::vector<FatJet> AnalyzerCore::SmearFatJets(const std::vector<FatJet>& jets, int sys){

  std::vector<FatJet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    //==== jets is a const vector. So in this function, we have to copy the elements like below
    FatJet this_jet = jets.at(i);

    this_jet *= this_jet.ResShift(sys);

    out.push_back( this_jet );
  }

  return out;

}
//Fatjet SDMass systematics (https://twiki.cern.ch/twiki/bin/view/CMS/JetWtagging#2016%20scale%20factors%20and%20correctio)
std::vector<FatJet> AnalyzerCore::ScaleSDMassFatJets(const std::vector<FatJet>& jets, int sys){
  
  std::vector<FatJet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    //==== jets is a const vector. So in this function, we have to copy the elements like below
    FatJet this_jet = jets.at(i);
    double current_SDMass = this_jet.SDMass() * (1. + double(sys) * 0.0094 );
    this_jet.SetSDMass( current_SDMass );
    
    out.push_back( this_jet );
  }
  
  return out;
  
}
std::vector<FatJet> AnalyzerCore::SmearSDMassFatJets(const std::vector<FatJet>& jets, int sys){

  std::vector<FatJet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    //==== jets is a const vector. So in this function, we have to copy the elements like below
    FatJet this_jet = jets.at(i);
    double current_SDMass = this_jet.SDMass() * (1. + double(sys) * 0.20 );
    this_jet.SetSDMass( current_SDMass );

    out.push_back( this_jet );
  }

  return out;

}

bool AnalyzerCore::PassMETFilter(){

  //==== https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#UL_data

  if(!Flag_goodVertices) return false;
  if(!IsFastSim){
    if(!Flag_globalSuperTightHalo2016Filter) return false;
  }
  if(!Flag_HBHENoiseFilter) return false;
  if(!Flag_HBHENoiseIsoFilter) return false;
  if(!Flag_EcalDeadCellTriggerPrimitiveFilter) return false;
  if(!Flag_BadPFMuonFilter) return false;
  if(!Flag_BadPFMuonDzFilter) return false;
  if(!Flag_eeBadScFilter) return false;
  if(DataYear>=2017){
    if(!Flag_ecalBadCalibFilter) return false;
  }

  return true;

}
void AnalyzerCore::SetBTagMCEff_Filename(TString _btagmceff_filename, bool _Use_dAsym){
  if(_Use_dAsym) cout << "[SetBTagMCEff_Filename] Try Using dAsym Factor!!" << endl;
  btagmceff_filename=_btagmceff_filename;
  Use_dAsym=_Use_dAsym;
  cout<<"[AnalyzerCore::SetBTagMCEff_Filename]->"<<btagmceff_filename<<endl;
}
void AnalyzerCore::initializeAnalyzerTools(){
  //==== MCCorrection
  mcCorr->SetMCSample(MCSample);
  mcCorr->SetEra(GetEra());
  mcCorr->SetIsDATA(IsDATA);
  mcCorr->SetEventInfo(run, lumi, event);
  mcCorr->SetIsFastSim(IsFastSim);
  if(!IsDATA){
    cout << "[AnalyzerCore::initializeAnalyzerTools] btagmceff_filename=" << btagmceff_filename << endl;
    mcCorr->ReadHistograms();
    mcCorr->SetupJetTagging(btagmceff_filename,Use_dAsym);
  }

  puppiCorr->SetEra(GetEra());
  puppiCorr->ReadHistograms();

  //==== FakeBackgroundEstimator
  fakeEst->SetEra(GetEra());
  fakeEst->ReadHistograms();

  //==== CFBackgroundEstimator
  cfEst->SetEra(GetEra());
  cfEst->ReadHistograms();



}

double AnalyzerCore::MCweight(bool usesign, bool norm_1invpb) const {

  if(IsDATA) return 1.;
  double weight=gen_weight;

  //MiNNLO sample has some events with unphysically large weight
  if(MCSample.Contains("DYJets")&&MCSample.Contains("MiNNLO")){
    double maxweight=2358.0700*5.;
    if(abs(weight)>maxweight){
      weight=weight>0. ? maxweight : -1.0*maxweight;
    }
  }
  //Sherpa sample needs weighted events
  if(MCSample.Contains("WJets") && MCSample.Contains("Sherpa")){
    usesign = false;
  }

  if(usesign){
    if(weight>0) weight=1.0;
    else if(weight<0) weight=-1.0;
    else weight=0.0;
  }
  if(norm_1invpb){
    if(usesign) weight*=xsec/sumSign;
    else weight*=xsec/sumW;
  }
  return weight;
}

double AnalyzerCore::GetPrefireWeight(int sys){

  if(IsDATA) return 1.;
  else{
    if(sys==0) return L1PrefireReweight_Central;
    else if(sys>0) return L1PrefireReweight_Up;
    else return L1PrefireReweight_Down;
  }

  cout << "[AnalyzerCore::GetPrefireWeight] wtf" << endl;
  exit(EXIT_FAILURE);
  return 1.;

}

double AnalyzerCore::GetPileUpWeight(int N_pileup, int syst){
  if(IsDATA) return 1.;
  else return mcCorr->GetPileUpWeight(N_pileup, syst);
}

double AnalyzerCore::GetPDFWeight(LHAPDF::PDF* pdf_){

  double pdf_1 = pdf_->xfxQ(genWeight_id1, genWeight_X1, genWeight_Q);
  double pdf_2 = pdf_->xfxQ(genWeight_id2, genWeight_X2, genWeight_Q);

  return pdf_1 * pdf_2;

}

double AnalyzerCore::GetPDFReweight(){

  return GetPDFWeight(pdfReweight->NewPDF)/GetPDFWeight(pdfReweight->ProdPDF);

}

double AnalyzerCore::GetPDFReweight(int member){

  return GetPDFWeight(pdfReweight->PDFErrorSet.at(member))/GetPDFWeight(pdfReweight->ProdPDF);

}

bool AnalyzerCore::IsOnZ(double m, double width){
  if( fabs(m-M_Z) < width ) return true;
  else return false;
}

double AnalyzerCore::MT(TLorentzVector a, TLorentzVector b){
  double dphi = a.DeltaPhi(b);
  return TMath::Sqrt( 2.*a.Pt()*b.Pt()*(1.- TMath::Cos(dphi) ) );
}

double AnalyzerCore::MT2(TLorentzVector a, TLorentzVector b, Particle METv, double METgap){

  TLorentzVector METa, METb;
  METa.SetPxPyPzE( 0., 0., 0., 0.);
  double MTa, MTb;
  double tempMETa =0., tempMT2 = TMath::Max(MT(a, METv), MT(b, METv));

  while(tempMETa < METv.Pt()){

    METa.SetPxPyPzE(tempMETa*TMath::Cos(METv.Phi()), tempMETa*TMath::Sin(METv.Phi()), 0., tempMETa);
    METb = METv - METa;

    MTa = MT(METa, a);
    MTb = MT(METb, b);

    tempMT2 = TMath::Min(tempMT2, TMath::Max(MTa, MTb));

    tempMETa = tempMETa + METgap;
  }  

  return tempMT2;

}

double AnalyzerCore::projectedMET(TLorentzVector a, TLorentzVector b, Particle METv){

  if( fabs(a.DeltaPhi(METv)) < fabs(b.DeltaPhi(METv)) ){
    return (METv.Pt() * TMath::Sin(fabs(a.DeltaPhi(METv))) );
  }
  else return (METv.Pt() * TMath::Sin(fabs(b.DeltaPhi(METv))) );

}

bool AnalyzerCore::HasFlag(TString flag){

  cout << "[AnalyzerCore::HasFlag] Userflags.size() = " << Userflags.size() << endl;
  for(unsigned int i=0; i<Userflags.size(); i++){
    cout << "[AnalyzerCore::HasFlag] " << Userflags.at(i) << endl;
  }
  
  return std::find(Userflags.begin(), Userflags.end(), flag) != Userflags.end();

}

std::vector<Muon> AnalyzerCore::MuonWithoutGap(const std::vector<Muon>& muons){

  std::vector<Muon> out;
  for(unsigned int i=0; i<muons.size(); i++){
    double this_eta = fabs( muons.at(i).Eta() );
    if( 1.444 <= this_eta && this_eta < 1.566 ) continue;

    out.push_back( muons.at(i) );
  }

  return out;

}

std::vector<Muon> AnalyzerCore::MuonPromptOnly(const std::vector<Muon>& muons, const std::vector<Gen>& gens){

  if(IsDATA) return muons;

  std::vector<Muon> out;

  for(unsigned int i=0; i<muons.size(); i++){
    if(GetLeptonType(muons.at(i), gens)<=0) continue;
    out.push_back( muons.at(i) );
  }

  return out;

}

std::vector<Muon> AnalyzerCore::MuonUsePtCone(const std::vector<Muon>& muons){

  std::vector<Muon> out;

  for(unsigned int i=0; i<muons.size(); i++){
    //==== muons is a const vector. So in this function, we have to copy the elements like below
    Muon this_muon = muons.at(i);
    this_muon.SetPtEtaPhiM( muons.at(i).PtCone(), muons.at(i).Eta(), muons.at(i).Phi(), muons.at(i).M() );
    out.push_back( this_muon );
  }

  return out;

}

Muon AnalyzerCore::MuonUsePtCone(const Muon& muon){

  //==== muon is a const object. So in this function, we have to copy the object like below
  Muon this_muon = muon;
  this_muon.SetPtEtaPhiM( muon.PtCone(), muon.Eta(), muon.Phi(), muon.M() );
  return this_muon;

}

Particle AnalyzerCore::UpdateMET(const Particle& METv, const std::vector<Muon>& muons){

  float met_x = METv.Px();
  float met_y = METv.Py();

  double px_orig(0.), py_orig(0.),px_corrected(0.), py_corrected(0.);
  for(unsigned int i=0; i<muons.size(); i++){

    px_orig+= muons.at(i).MiniAODPt()*TMath::Cos(muons.at(i).Phi());
    py_orig+= muons.at(i).MiniAODPt()*TMath::Sin(muons.at(i).Phi());

    px_corrected += muons.at(i).Px();
    py_corrected += muons.at(i).Py();

  }

  met_x = met_x + px_orig - px_corrected;
  met_y = met_y + py_orig - py_corrected;

  Particle METout;
  METout.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x+met_y*met_y));
  return METout;

}

std::vector<Muon> AnalyzerCore::MuonApplyPtCut(const std::vector<Muon>& muons, double ptcut){

  std::vector<Muon> out;

  for(unsigned int i=0; i<muons.size(); i++){
    if(!( muons.at(i).Pt() > ptcut )) continue;
    out.push_back( muons.at(i) );
  }

  return out;

}

std::vector<Electron> AnalyzerCore::ElectronPromptOnly(const std::vector<Electron>& electrons, const std::vector<Gen>& gens){

  if(IsDATA) return electrons;

  std::vector<Electron> out;

  for(unsigned int i=0; i<electrons.size(); i++){
    if(GetLeptonType(electrons.at(i), gens)<=0) continue;
    out.push_back( electrons.at(i) );
  }

  return out;

}

std::vector<Electron> AnalyzerCore::ElectronUsePtCone(const std::vector<Electron>& electrons){

  std::vector<Electron> out;

  for(unsigned int i=0; i<electrons.size(); i++){
    //==== electrons is a const vector. So in this function, we have to copy the elements like below
    Electron this_electron = electrons.at(i);
    this_electron.SetPtEtaPhiM( electrons.at(i).PtCone(), electrons.at(i).Eta(), electrons.at(i).Phi(), electrons.at(i).M() );
    out.push_back( this_electron );
  }

  return out;

}

Electron AnalyzerCore::ElectronUsePtCone(const Electron& electron){

  //==== electron is a const object. So in this function, we have to copy the object like below
  Electron this_electron = electron;
  this_electron.SetPtEtaPhiM( electron.PtCone(), electron.Eta(), electron.Phi(), electron.M() );
  return this_electron;

}

std::vector<Electron> AnalyzerCore::ElectronApplyPtCut(const std::vector<Electron>& electrons, double ptcut){

  std::vector<Electron> out;

  for(unsigned int i=0; i<electrons.size(); i++){
    if(!( electrons.at(i).Pt() > ptcut )) continue;
    out.push_back( electrons.at(i) );
  }

  return out;

}

std::vector<Jet> AnalyzerCore::JetsAwayFromFatJet(const std::vector<Jet>& jets, const std::vector<FatJet>& fatjets, double mindr){

  std::vector<Jet> out;
  for(unsigned int i=0; i<jets.size(); i++){

    bool Overlap = false;
    for(unsigned int j=0; j<fatjets.size(); j++){
      if( ( jets.at(i) ).DeltaR( fatjets.at(j) ) < mindr ){
        Overlap = true;
        break;
      }
    }
    if(!Overlap) out.push_back( jets.at(i) );

  }

  return out;

}

std::vector<Jet> AnalyzerCore::JetsVetoLeptonInside(const std::vector<Jet>& jets, const std::vector<Electron>& els, const std::vector<Muon>& mus, double dR){

  std::vector<Jet> out;
  for(unsigned int i=0; i<jets.size(); i++){

    bool HasLeptonInside = false;

    for(unsigned int j=0; j<els.size(); j++){
      if( jets.at(i).DeltaR( els.at(j) ) < dR ){
        HasLeptonInside = true;
        break;
      }
    }
    if(HasLeptonInside) continue;

    for(unsigned int j=0; j<mus.size(); j++){
      if( jets.at(i).DeltaR( mus.at(j) ) < dR ){
        HasLeptonInside = true;
        break;
      }
    }
    if(HasLeptonInside) continue;

    //==== if all fine,
    out.push_back( jets.at(i) );

  }
  return out;

}

std::vector<FatJet> AnalyzerCore::FatJetsVetoLeptonInside(const std::vector<FatJet>& jets, const std::vector<Electron>& els, const std::vector<Muon>& mus, double dR){

  std::vector<FatJet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    FatJet this_jet = jets.at(i);

    bool HasLeptonInside = false;

    for(unsigned int j=0; j<els.size(); j++){
      if( this_jet.DeltaR( els.at(j) ) < dR ){
        HasLeptonInside = true;
        break;
      }
    }
    if(HasLeptonInside) continue;

    for(unsigned int j=0; j<mus.size(); j++){
      if( this_jet.DeltaR( mus.at(j) ) < dR ){
        HasLeptonInside = true;
        break;
      }
    }
    if(HasLeptonInside) continue;

    //==== if all fine,
    out.push_back( this_jet );

  }

  return out;

}

std::vector<Jet> AnalyzerCore::JetsAwayFromPhoton(const std::vector<Jet>& jets, const std::vector<Photon>& photons, double mindr){
  
  std::vector<Jet> out;
  for(unsigned int i=0; i<jets.size(); i++){
    
    bool Overlap = false;
    for(unsigned int j=0; j<photons.size(); j++){
      if( ( jets.at(i) ).DeltaR( photons.at(j) ) < mindr ){
        Overlap = true;
        break;
      }
    }
    if(!Overlap) out.push_back( jets.at(i) );

  }

  return out;

}


Particle AnalyzerCore::AddFatJetAndLepton(const FatJet& fatjet, const Lepton& lep){

  if(fatjet.DeltaR( lep )<0.8){
    return fatjet;
  }
  else{
    return fatjet+lep;
  }

}

//=========================================================
//==== Gen Matching Tools

void AnalyzerCore::PrintGen(const std::vector<Gen>& gens){

  cout << "===========================================================" << endl;
  cout << "RunNumber:EventNumber = " << run << ":" << event << endl;
  cout << "index\tPID\tStatus\tMIdx\tMPID\tStart\tPt\tEta\tPhi\tM" << endl;
  for(unsigned int i=2; i<gens.size(); i++){
    Gen gen = gens.at(i);
    vector<int> history = TrackGenSelfHistory(gen, gens);
    cout << i << "\t" << gen.PID() << "\t" << gen.Status() << "\t" << gen.MotherIndex() << "\t" << gens.at(gen.MotherIndex()).PID()<< "\t" << history[0] << "\t";
    printf("%.2f\t%.2f\t%.2f\t%.2f\n",gen.Pt(), gen.Eta(), gen.Phi(), gen.M());
  }

}

Gen AnalyzerCore::GetGenMatchedLepton(const Lepton& lep, const std::vector<Gen>& gens){

  //==== find status 1 lepton

  int reco_PID = -999;
  if(lep.LeptonFlavour()==Lepton::ELECTRON) reco_PID = 11;
  else if(lep.LeptonFlavour()==Lepton::MUON) reco_PID = 13;
  else{
    cout << "[AnalyzerCore::GetGenMatchedLepton] input lepton flavour not set" << endl;
    exit(EXIT_FAILURE);
  }

  double min_dR = 0.1;
  Gen gen_closest;
  for(unsigned int i=2; i<gens.size(); i++){

    Gen gen = gens.at(i);

    //==== Status 1
    if( gen.Status() != 1 ) continue;
    //==== PID
    if( abs( gen.PID() ) != reco_PID ) continue;
    //==== reject ISR?
    if( gen.MotherIndex() < 0 ) continue;
    //==== dR matching
    if( gen.DeltaR( lep ) < min_dR ){
      min_dR = gen.DeltaR( lep ) ;
      gen_closest = gen;
    }

  }

  return gen_closest;

}

Gen AnalyzerCore::GetGenMatchedPhoton(const Lepton& lep, const std::vector<Gen>& gens){
//Find if there is a photon candidate for a source of external conversion (similar pt, direction of lepton)

  double min_dR = 0.2;//1)
  Gen gen_closest;
  double pt_min = 10., dPtRelmax=0.5, dRmax=0.2;//1)
  for(unsigned int i=2; i<gens.size(); i++){

    Gen gen = gens.at(i);

    if( gen.MotherIndex() < 0 ) continue;
    if( ! ( abs(gen.PID())==22 && (gen.Status()==1 || gen.Status()==23) ) ) continue;//2)
    if( gen.Pt() < pt_min ) continue;
    if( !(lep.Pt()/gen.Pt()>(1.-dPtRelmax) && lep.Pt()/gen.Pt()<(1.+dPtRelmax)) ) continue;
    if( gen.DeltaR( lep ) > dRmax ) continue;
    if( gen.Status()==23 && !IsFinalPhotonSt23_Public(gens) ) continue;//2)

    if( gen.DeltaR( lep ) < min_dR ){
      min_dR = gen.DeltaR( lep ) ;
      gen_closest = gen;
    }

  }

  return gen_closest;

//1) Validity of cuts are checked for electron with PT>10. Note that the previous dPtRel<0.2 cut in the CatNtuple analysis was optimized for PT(e)>25.
//   External conversion rate proportionate to M^{-2}, thus muon external conversion rate is negligible.
//2) As the algorithm targets stable photon near lepton, only status-1 photon should be investigated theoretically. 
//   However, in some events, last status in photon history is 23. This is believed to be due to skimming of GEN history between pythia & MiniAOD. 
//   This case is also covered here. Note that IsFinalPhotonSt23 has to analyze whole history, i.e. computationally heavier part in this function.
//   Therefore it is put at last part of criteria for efficient functioning.
//For more details about the optimization, ask J.B..
}

vector<int> AnalyzerCore::TrackGenSelfHistory(const Gen& me, const std::vector<Gen>& gens){
//returns {index of the first history of the gen, index of the last history of the gen's mother}

  int myindex = me.Index();

  if(myindex<2){
    vector<int> out = {myindex, -1};
    return out;
  }

  int mypid = gens.at(myindex).PID();

  int currentidx = myindex;
  int motherindex = me.MotherIndex();

  while(gens.at(motherindex).PID() == mypid){

    //==== Go one generation up
    currentidx = motherindex;
    motherindex = gens.at(motherindex).MotherIndex();

    if(motherindex<0) break;
  }

  vector<int> out = {currentidx, motherindex};

  return out;

}

bool AnalyzerCore::IsFromHadron(const Gen& me, const std::vector<Gen>& gens){

  bool out = false;

  int myindex = me.Index();
  if(myindex<2) return true;

  vector<int> my_history = TrackGenSelfHistory(me, gens);
  Gen          Start = gens.at( my_history[0] );
  Gen MotherOf_Start = gens.at( my_history[1] );

  //==== Status 21~29 are from hardprocess
  //==== Means it's lepton from hardprocess
  //==== e.g., leptons from Z start their lives with status 23
  if( 20 < Start.Status() && Start.Status() < 30 ) return false;

  Gen current_me = Start; // me will always be Start
  Gen current_mother = Start; // initializing
  while( current_mother.Index() >= 2 ){

    vector<int> current_history = TrackGenSelfHistory(current_me, gens);

    //==== Go one generation up
    //==== not being used after this line
    //==== not a bug!!
    current_me = gens.at(current_history[1]);

    //==== Now look at mother of previous "me"
    current_mother = gens.at(current_history[1]);

    vector<int> current_mother_history = TrackGenSelfHistory(current_mother, gens);
    Gen StartOf_current_mother = gens.at(current_mother_history[0]);
    int current_mother_PID = current_mother.PID();

    //==== From Z,W,H,t
    if( current_mother_PID==23 || current_mother_PID==24 || current_mother_PID==25 || current_mother_PID==6 ){
      out = false;
      break;
    }
    //==== From Signal
    if( IsSignalPID(current_mother_PID) ){
      out = false;
    }
    if( (current_mother_PID==11 || current_mother_PID==13 || current_mother_PID==15 || current_mother_PID==22) && (StartOf_current_mother.Status()>20 && StartOf_current_mother.Status()<30)){
      out = false;
      break;
    }
    if( current_mother_PID>50 ){
      out=true;
      break;
    }
    if( (current_mother_PID>=1 && current_mother_PID<=5) || current_mother_PID==21 ){
      out=true; 
      break;
    }

  }

  return out;

}


int AnalyzerCore::GetPrElType_InSameSCRange_Public(int TruthIdx, const std::vector<Gen>& TruthColl){
//Abbreviation: Get Prompt Electron Type In Same Supercluster Range (Public (shared) version of J.B.'s original gen-matching code)
//Prompt e>eee (int. conv.) case, collimated electrons can be merged in one SC & track is selected among them, and reconstructed as single electron. 
//In this case, still there will be a nearby prompt electron of LepType 1-3 within supercluster merging range.
//Supercluster merging range: |dphi|<0.3/0.3 (EB/EE), |deta|<0/0.07 (EB/EE) (additionally put 0.03 for marginal difference from size of crystals)
//Ref:JINST 10 (2015) P06005, arXiv:1502.02701
//Return Value: 1/2/3:LeptonType-1/2/3 electron found in same SC range
//             -1: No LeptonType-1/2/3 electron found in same SC range
//
//Note: Hadronic origins are not included in this algo. as I am not sure of effect of many nearby particles in jets on the ele-reco performance.
//      + it is not of my interest yet.

  if(TruthIdx<2) return false;
  if(abs(TruthColl.at(TruthIdx).PID())!=11) return false;
  if(TruthColl.at(TruthIdx).Status()!=1) return false;

  float dPhiMax=0.3, dEtaMax=0.1;
  int NearbyElType=-1;

  for(unsigned int it_gen=2; it_gen<TruthColl.size(); it_gen++){
    if(TruthColl.at(it_gen).Status()!=1) continue;
    if(abs(TruthColl.at(it_gen).PID())!=11) continue;
    if(fabs(TruthColl.at(TruthIdx).Eta()-TruthColl.at(it_gen).Eta())>dEtaMax) continue;
    if(TruthColl.at(TruthIdx).DeltaPhi(TruthColl.at(it_gen))>dPhiMax) continue;

    int LepType = GetLeptonType_Public(it_gen, TruthColl);
    if(!(LepType>=1 && LepType<=3)) continue;
    NearbyElType  = LepType;
  }

  return NearbyElType;
}


int AnalyzerCore::GetLeptonType_Public(int TruthIdx, const std::vector<Gen>& TruthColl){
//Type : 1:EW-Prompt / 2: BSM-Prompt / 3:EW/BSM-Prompt-Tau Daughter 
//       4:Internal Conversion from Soft QED Radiation (PS-level) / 5:Internal Conversion from Hard Process Photon (ME-level)
//      -1:Unmatched & not EW Conversion candidate (mis-reco. or external conversion within jets)
//      -2:Hadron Daughter / -3:Daughter of Tau from Hadron or Parton / -4:Internal Conversion Daughter having hadronic origin
//      -5:External Conversion from Hard process photon / -6:External conversion from t/EWV/EWlep
//      (-4:Daughter of Non-hard scattered photon & has parton or hadron ancestor OR implicit Conv from quark)
//       0:Error / >0: Non-fake: Non-hadronic origin / <0 : Fakes: Hadronic origin or external conversion
//Note: There is no physical distinction between type 4 vs. 5 and type -5 vs. -6. The distinction is only intended for straightforward debugging.


  //Only consider Status 1 lepton
  if(TruthIdx<2) return 0;
  if(TruthColl.at(TruthIdx).Status()!=1) return 0;
  if( !(fabs(TruthColl.at(TruthIdx).PID())==11 || fabs(TruthColl.at(TruthIdx).PID())==13) ) return 0;


  int LeptonType=0;
  int MPID=0, GrMPID=0;
  vector<int> my_history, mom_history, grmom_history;
  int LastSelfIdx=-1, MotherIdx=-1, LastSelfMIdx=-1, GrMotherIdx=-1, LastSelfGrMIdx=-1;
  int Status_orig=0, MStatus_orig=0, MStatus_last=0, GrMStatus_orig=0, GrMStatus_last=0;
  bool HadronicOrigin = false;

  my_history      = TrackGenSelfHistory(TruthColl.at(TruthIdx), TruthColl);
  LastSelfIdx     = my_history[0];
  MotherIdx       = my_history[1];
  Status_orig     = TruthColl.at(LastSelfIdx).Status();
  HadronicOrigin  = IsFromHadron(TruthColl.at(TruthIdx), TruthColl);
  
  if(   MotherIdx!=-1   ){ mom_history  = TrackGenSelfHistory(TruthColl.at(MotherIdx), TruthColl);
                           LastSelfMIdx = mom_history[0];
                           GrMotherIdx  = mom_history[1];
                           MPID         = TruthColl.at(MotherIdx).PID();
                           MStatus_orig = TruthColl.at(LastSelfMIdx).Status();
                           MStatus_last = TruthColl.at(MotherIdx).Status();
                         }
  if(  GrMotherIdx!=-1  ){ grmom_history  = TrackGenSelfHistory(TruthColl.at(GrMotherIdx), TruthColl);
                           LastSelfGrMIdx = grmom_history[0];
                           GrMPID         = TruthColl.at(GrMotherIdx).PID();
                           GrMStatus_orig = TruthColl.at(LastSelfGrMIdx).Status();
                           GrMStatus_last = TruthColl.at(GrMotherIdx).Status();
                         }

  if     ( TruthIdx==-1 )                                       LeptonType= 0;
  else if( fabs(MPID)==23 || fabs(MPID)==24 || fabs(MPID)==25 ) LeptonType= 1;
  else if( IsSignalPID(MPID) )                                  LeptonType= 2;
  else if( Status_orig>20 && Status_orig<30 )                   LeptonType= 1;//1)
  else if( fabs(MPID)>50 )                                      LeptonType=-2;
  else if( fabs(MPID)==15 && MStatus_last==2 ){
           if     ( fabs(GrMPID)==23 || fabs(GrMPID)==24 || fabs(GrMPID)==25 ) LeptonType= 3;
           else if( IsSignalPID(GrMPID) )                                      LeptonType= 3;
           else if( MStatus_orig>20  && MStatus_orig<30  )                     LeptonType= 3;//1)
           else if( HadronicOrigin )                                           LeptonType=-3;//2-a)
           else if( fabs(GrMPID)==22  && GrMStatus_orig>20 && GrMStatus_orig<30 )                     LeptonType= 5;//2-b)
           else if( fabs(GrMPID)==22 )                                                                LeptonType= 4;//2-c)
           else if( (fabs(GrMPID)==11 || fabs(GrMPID)==13 || fabs(GrMPID)==15) && GrMStatus_last!=2 ) LeptonType= 4;//2-d)
           else                                                                                       LeptonType= 0;
         }
  else if( fabs(MPID)==22 ){
           if( MStatus_orig>20 && MStatus_orig<30 )                            LeptonType= 5;//3-a)
           else if( HadronicOrigin )                                           LeptonType=-4;//3-b)
           else if( fabs(GrMPID)==24 || fabs(GrMPID)==23 || fabs(GrMPID)==6  ) LeptonType= 4;//3-c)
           else if( fabs(GrMPID)==11 || fabs(GrMPID)==13 || fabs(GrMPID)==15 ) LeptonType= 4;//3-d)
           else                                                                LeptonType= 0;
         }
  else if( (fabs(MPID)==11 || fabs(MPID)==13 || fabs(MPID)==15) && MStatus_last!=2 && !HadronicOrigin ) LeptonType= 4;//4-a)
  else if( ((fabs(MPID)>=1 && fabs(MPID)<=5) || fabs(MPID)==21) && MStatus_last!=2 )                    LeptonType=-4;//4-b)
  else if( fabs(MPID)==6 ) LeptonType=4;//4-c)
  else LeptonType=0;


  return LeptonType;

//**footnote
//These are based on observation in DY,ZG,TT sample(DY,ZG:amcnlo+pythia, TT:powheg+pythia) for other PS generator, convention may differ.
//1) In MG5aMC@NLO generator, output of ME level generation does not have specific guage field mother if it is not on-shell specific generation.
//   e.g. u u~ > l+ l- -> fabs(MID)=1 .
//   This line is put after checking prompt mother PID checking, in order to distinguish type 1 and 2.
//2-a) e.g. a)Had > ta+X, ta>l+2nu b) q>ta+X in jet fragmentation (ta is not from hard process (ME), as it was already checked in prev. step)
//2-b) e.g. gamma>ta(+)+ta(-)+X, ta>lnu (St=2)
//2-c) e.g. " " " " " " " " " " " " " " " " " ", but soft gamma case. this is not observed in test sample but put here just in case.
//          (hadronic origin was already checked before, so no need to worry about contamination from hadronic origins at this line)
//2-d) e.g. l>tata..+l.. , ta>l+2nu (tau pair produced from internal conversion), photon radiation is not decay: GenStatus!=2
//3-a) e.g. hard process gamma>ll
//3-b) e.g. a) Had>gamma+X, gamma>ll+X (in PS+Had stage intermediate process is omitted you see just Had>Nphoton+Mhadrons+..)
//          b) q>gamma+q, gamma>ll+X in jet fragmentation or radiations of tops.
//          c) gluon>Ngamma+Mhadrons in jet fragmentation (actually observed in samples)
//3-c) e.g. W+>W+ gamma, or t>t+gamma, gamma>ll+X, not yet observed in test sample but possible (upto radiation is observed so far)
//3-d) e.g. ta>ta+gamma, gamma>ll+X, tau not from hadron(e.g. pp>tata)
//4-a) e.g. EW lep l, l>lll... just implicit conversion. 
//4-b) e.g. q or g> Nlepton +MHadrons... in parton shower history
//4-c) e.g. t>t+ll.. implicit conversion
}



int AnalyzerCore::GetLeptonType(const Lepton& lep, const std::vector<Gen>& gens){

  //==== [Type]
  //====  1 : EWPrompt
  //====  2 : Signal Daughter
  //====  3 : EWtau daughter
  //====  4 : Internal Conversion daughter from t/EWV/EWlep(Implicit,Explicit)
  //====  5 : Internal Conversion daughter from HardScatterPhoton
  //==== -1 : Unmatched & not EW Conversion candidate
  //==== -2 : Hadron daughter
  //==== -3 : Daughter of tau from hadron or parton
  //==== -4 : Internal conversion daughter(implicit,explicit) having hadronic origin 
  //==== -5 : External conversion candidate(Hard scattered photon)
  //==== -6 : External conversion from t/EWV/EWlep
  //==== (-4: Daughter of Non-hard scattered photon & has parton or hadron ancestor OR implicit Conv from quark)
  //==== -------------------------------------------------------------
  //====  0 : Error
  //==== >0 : Non-fake; Non-hadronic origin
  //==== <0 : Fakes   ; Hadronic origin or external conversion

  Gen gen_closest = GetGenMatchedLepton(lep, gens); // if gen_closest.IsEmpty(), we should then look for a near photon
  //cout << "[AnalyzerCore::GetLeptonType] [Reco] pt = " << lep.Pt() << "\t, eta = " << lep.Eta() << endl;
  //cout << "[AnalyzerCore::GetLeptonType] [Gen] Index = " << gen_closest.Index() << endl;

/*
  //==== 1) Using Simple Flags
  //==== Prompt
  if( gen_closest.isPromptFinalState() ){
    return 1;
  }
  //=== From Tau
  else if( gen_closest.isDirectPromptTauDecayProductFinalState() ){
    return 2;
  }
  else{
    //=== Fake
    return -1;
  }
*/  

  //==== 2) Use Gen history

  int LeptonType=0, MatchedTruthIdx=-1;
  //==== No matched gen lepton
  if( gen_closest.IsEmpty() ){
    Gen gen_photon_closest = GetGenMatchedPhoton(lep, gens);
    int NearPhotonType = GetGenPhotonType(gen_photon_closest,gens);
    if     ( NearPhotonType<=0 ) LeptonType=-1;//1)
    else if( NearPhotonType==1 ) LeptonType=-5;//2)
    else if( NearPhotonType==2 ) LeptonType=-6;//3)
  }
  //==== Has macthed gen lepton
  else{
    MatchedTruthIdx = gen_closest.Index();
    LeptonType = GetLeptonType_Public(MatchedTruthIdx, gens);//4)
    if(LeptonType>=4 && LeptonType<=5){//5)
      int NearbyPrElType = GetPrElType_InSameSCRange_Public(MatchedTruthIdx, gens);
      if(NearbyPrElType>0) LeptonType = NearbyPrElType;
    }
  }

  return LeptonType;

//**footnote
//1) matched to no gen-lepton nor gen-photon -> mis-reco.
//   matched to no gen-lepton, but to photon with hadronic origin -> mis-reco. (e.g. pions->e) or external conversion from photon in jets
//2) matched to no gen-lepton, but to photon with non-hadronic origin (hard process) -> external conversion from photon with non-hadronic source (ME-level)
//3) matched to no gen-lepton, but to photon with non-hadronic origin (soft QED radiation) -> external conversion from photon with non-hadronic source (PS-level)
//4) matched to gen-lepton, categorize based on the truth categorization algo.: AnalyzerCore::GetLeptonType_Public(int TruthIdx, std::vector<Gen>& TruthColl)
//5) collimated e/gm objects are merged in SC, hence if there is prompt electron within SC-merging range, reco-electron's properties actually represent pre-QED-FSR prompt-electron,
//   rather than the closest internal conversion electron. Therefore shift the type to the prompt lepton's type.
//- Note: distinction between type 4 vs. 5 and type -5 vs. -6 is unphysical. it is only for debugging.
}

int AnalyzerCore::GetGenPhotonType(const Gen& genph, const std::vector<Gen>& gens){

  //==== [Type]
  //====  0 : Invalid input or Error or HardScatter is input when hardscatter is not final state
  //====  1 : HardScatter / 2: Else prompt daughter(l,V,t)
  //==== -1 : Reserved for unmatched(Not used now) / -2: Hadronic origin

  if(genph.IsEmpty()) return 0;

  int genph_index = genph.Index();

  if( genph_index<2 ) return 0;
  if( !(gens.at(genph_index).PID()==22 && (gens.at(genph_index).Status()==1 || gens.at(genph_index).Status()==23)) ) return 0;

  if(gens.at(genph_index).Status()==23){
    if(IsFinalPhotonSt23_Public(gens)) return 1;
    else                               return 0;
  }//From this pt, only St1 Photon is treated.

  vector<int> phhist = TrackGenSelfHistory(genph, gens);

  Gen          Start = gens.at(phhist[0]);
  Gen MotherOf_Start = gens.at(phhist[1]);
  int MotherOf_Start_PID = abs(MotherOf_Start.PID()); // |PID|

  bool fromhadron = IsFromHadron(genph, gens);

  if     ( 20 < Start.Status() && Start.Status() < 30 ) return 1;//1)
  else if( MotherOf_Start_PID==23 || MotherOf_Start_PID==25) return 1;//2)
  else if( MotherOf_Start_PID==24 || MotherOf_Start_PID==6 || IsSignalPID(MotherOf_Start_PID) ) return 2;//3)
  else if( fromhadron ) return -2;//4)
  else if( MotherOf_Start_PID==11 || MotherOf_Start_PID==13 || MotherOf_Start_PID==15 ) return 2;//5)
  else return 0;

//*footnote
//1) Hard process photon's original status is 20's, unless the history is skimmed in MiniAOD.
//2) If part of intermediate history is skimmed at MinoAOD, then last photon status is 1 without any preceding history lines.
//   In that case, intermediate mother is written in history, and this line catches the case.
//3) top and charged bosons can radiate photons.
// - Note that distinction between 1 and 2 is not physical. You should use both 1 & 2 for prompt photons.
//4) this category does not include top, but photons from hadrons and quarks. Predominantly, in most of the cases they are daughter of pi0.
//   Rarer, but other mesons as eta, B, or even some quarks can also radiate energetic photons.
//5) Photons radiated from lepton FSR. Sometimes they are quite energetic.
}


bool AnalyzerCore::IsFinalPhotonSt23_Public(const std::vector<Gen>& TruthColl){
//In Some XG proc events, it is observed that some of photons' last status is 23. Presumably due to skimming of generator history between pythia and MiniAOD.
//The function returns if this is the case.
//And this is designed only for 1 hard photon case as W+G or Z+G or TT+G

  bool IsFinalGammaStatus23 = false;
  bool HasStatus23Photon    = false;
  for(unsigned int i=2; i<TruthColl.size(); i++){
    int fpid  = fabs(TruthColl.at(i).PID());
    int GenSt = TruthColl.at(i).Status();
    int MPID_direct= TruthColl.at(TruthColl.at(i).MotherIndex()).PID();
    if( !((fpid!=22 && MPID_direct==22) || (fpid==22 && (GenSt==23||GenSt==1))) ) continue;

    vector<int> my_history, mom_history;
    my_history  = TrackGenSelfHistory(TruthColl.at(i), TruthColl);
    int LastSelfIdx     = my_history[0];
    int MotherIdx       = my_history[1];
    int LastSelfSt      = TruthColl.at(LastSelfIdx).Status();
    int LastSelfMIdx=-1, MStatus_orig=-1;
    if(MotherIdx!=-1){
      mom_history  = TrackGenSelfHistory(TruthColl.at(MotherIdx), TruthColl);
      LastSelfMIdx = mom_history[0];
      MStatus_orig = TruthColl.at(LastSelfMIdx).Status();
    }

    if(fpid==22){
      if(GenSt==23) {HasStatus23Photon=true; IsFinalGammaStatus23=true;}
      else if(GenSt==1 && LastSelfSt==23) {IsFinalGammaStatus23=false; break;}//a)
    }
    else if( MPID_direct==22 && MStatus_orig==23 ){ IsFinalGammaStatus23=false; break;}//b)
  }

  if(!HasStatus23Photon) return false;

  return IsFinalGammaStatus23;

//**footnotes
//a) Status-23 photon's last is 1. Thus status-23 photon is not the last history.
//b) Daughter particle of status-23 photon is found. Thus status-23 photon is not the last history.
}


bool AnalyzerCore::IsSignalPID(int pid){

  pid = abs(pid);

  //==== HeavyNeutrino
  if(pid>=9900000) return true;
  //==== ChargedHiggs
  if(pid==36 || pid==37) return true;

  return false;

}

//==== END Gen Matching Tools
//==============================================================

TH1D* AnalyzerCore::GetHist1D(TString histname){

  TH1D *h = NULL;
  std::map<TString, TH1D*>::iterator mapit = maphist_TH1D.find(histname);
  if(mapit != maphist_TH1D.end()) return mapit->second;

  return h;

}

TH2D* AnalyzerCore::GetHist2D(TString histname){

  TH2D *h = NULL;
  std::map<TString, TH2D*>::iterator mapit = maphist_TH2D.find(histname);
  if(mapit != maphist_TH2D.end()) return mapit->second;

  return h;

}

TH3D* AnalyzerCore::GetHist3D(TString histname){
  
  TH3D *h = NULL;
  std::map<TString, TH3D*>::iterator mapit = maphist_TH3D.find(histname);
  if(mapit != maphist_TH3D.end()) return mapit->second;
  
  return h;
  
}


void AnalyzerCore::FillHistUnderAndOverFlow(TString histname, double value, double weight, int n_bin, double x_min, double x_max){
  //if overflow==0 -> ignore overflow value
  //if overflow==1 -> fill the firstbin for underflow
  //if overflow==2 -> fill the lastbin for overflow
  //if overflow==3 -> mode2 + mode3
  TH1D *this_hist = GetHist1D(histname);
  if( !this_hist ){
    this_hist = new TH1D(histname, "", n_bin, x_min, x_max);
    this_hist->SetDirectory(NULL);
    maphist_TH1D[histname] = this_hist;
    //vhist_TH1D.push_back(this_hist);
  }
  //jhchoi
  if(value>=x_max){
    double _x1=this_hist->GetBinLowEdge(n_bin);//last valid bin's low edge
    double _dx=this_hist->GetBinWidth(n_bin);//last valid bin's low edge
    value=_x1+_dx/2;
  }
  else if(value<=x_min){
    double _x1=this_hist->GetBinLowEdge(1);//last valid bin's low edge
    double _dx=this_hist->GetBinWidth(1);//last valid bin's low edge
    value=_x1+_dx/2;
  }

  this_hist->Fill(value, weight);

}


void AnalyzerCore::FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max){
  TH1D *this_hist = GetHist1D(histname);
  if( !this_hist ){
    this_hist = new TH1D(histname, "", n_bin, x_min, x_max);
    this_hist->SetDirectory(NULL);
    maphist_TH1D[histname] = this_hist;
    //vhist_TH1D.push_back(this_hist);
  }

  this_hist->Fill(value, weight);

}

void AnalyzerCore::FillHist(TString histname, double value, double weight, int n_bin, double *xbins){

  TH1D *this_hist = GetHist1D(histname);
  if( !this_hist ){
    this_hist = new TH1D(histname, "", n_bin, xbins);
    this_hist->SetDirectory(NULL);
    maphist_TH1D[histname] = this_hist;
    //vhist_TH1D.push_back(this_hist);
  }

  this_hist->Fill(value, weight);

}

void AnalyzerCore::FillHist(TString histname,
                double value_x, double value_y,
                double weight,
                int n_binx, double x_min, double x_max,
                int n_biny, double y_min, double y_max){

  TH2D *this_hist = GetHist2D(histname);
  if( !this_hist ){
    this_hist = new TH2D(histname, "", n_binx, x_min, x_max, n_biny, y_min, y_max);
    this_hist->SetDirectory(NULL);
    maphist_TH2D[histname] = this_hist;
    //vhist_TH2D.push_back(this_hist);
  }

  this_hist->Fill(value_x, value_y, weight);

}

void AnalyzerCore::FillHist(TString histname,
                double value_x, double value_y,
                double weight,
                int n_binx, double *xbins,
                int n_biny, double *ybins){

  TH2D *this_hist = GetHist2D(histname);
  if( !this_hist ){
    this_hist = new TH2D(histname, "", n_binx, xbins, n_biny, ybins);
    this_hist->SetDirectory(NULL);
    maphist_TH2D[histname] = this_hist;
    //vhist_TH2D.push_back(this_hist);
  }

  this_hist->Fill(value_x, value_y, weight);

}

void AnalyzerCore::FillHist(TString histname,
          double value_x, double value_y, double value_z,
          double weight,
          int n_binx, double x_min, double x_max,
          int n_biny, double y_min, double y_max,
          int n_binz, double z_min, double z_max){
  
  TH3D *this_hist = GetHist3D(histname);
  if( !this_hist ){
    this_hist = new TH3D(histname, "", n_binx, x_min, x_max, n_biny, y_min, y_max, n_binz, z_min, z_max);
    this_hist->SetDirectory(NULL);
    maphist_TH3D[histname] = this_hist;
    //vhist_TH3D.push_back(this_hist);
  }
  
  this_hist->Fill(value_x, value_y, value_z, weight);
  
}

void AnalyzerCore::FillHist(TString histname,
          double value_x, double value_y, double value_z,
          double weight,
          int n_binx, const double *xbins,
          int n_biny, const double *ybins,
          int n_binz, const double *zbins){
  
  TH3D *this_hist = GetHist3D(histname);
  if( !this_hist ){
    this_hist = new TH3D(histname, "", n_binx, xbins, n_biny, ybins, n_binz, zbins);
    this_hist->SetDirectory(NULL);
    maphist_TH3D[histname] = this_hist;
    //vhist_TH3D.push_back(this_hist);
  }
  
  this_hist->Fill(value_x, value_y, value_z, weight);
  
}

TH1D* AnalyzerCore::JSGetHist1D(TString suffix, TString histname){

  TH1D *h = NULL;

  std::map< TString, std::map<TString, TH1D*> >::iterator mapit = JSmaphist_TH1D.find(suffix);
  if(mapit==JSmaphist_TH1D.end()){
    return h;
  }
  else{

    std::map<TString, TH1D*> this_maphist = mapit->second;
    std::map<TString, TH1D*>::iterator mapitit = this_maphist.find(histname);
    if(mapitit != this_maphist.end()) return mapitit->second;

  }

  return h;

}

void AnalyzerCore::JSFillHist(TString suffix, TString histname, double value, double weight, int n_bin, double x_min, double x_max){

  TH1D *this_hist = JSGetHist1D(suffix, histname);
  if( !this_hist ){

    this_hist = new TH1D(histname, "", n_bin, x_min, x_max);
    (JSmaphist_TH1D[suffix])[histname] = this_hist;

  }

  this_hist->Fill(value, weight);

}

TH2D* AnalyzerCore::JSGetHist2D(TString suffix, TString histname){

  TH2D *h = NULL;

  std::map< TString, std::map<TString, TH2D*> >::iterator mapit = JSmaphist_TH2D.find(suffix);
  if(mapit==JSmaphist_TH2D.end()){
    return h;
  }
  else{

    std::map<TString, TH2D*> this_maphist = mapit->second;
    std::map<TString, TH2D*>::iterator mapitit = this_maphist.find(histname);
    if(mapitit != this_maphist.end()) return mapitit->second;

  }

  return h;

}

void AnalyzerCore::JSFillHist(TString suffix, TString histname,
                  double value_x, double value_y,
                  double weight,
                  int n_binx, double x_min, double x_max,
                  int n_biny, double y_min, double y_max){

  TH2D *this_hist = JSGetHist2D(suffix, histname);
  if( !this_hist ){

    this_hist = new TH2D(histname, "", n_binx, x_min, x_max, n_biny, y_min, y_max);
    (JSmaphist_TH2D[suffix])[histname] = this_hist;

  }

  this_hist->Fill(value_x, value_y, weight);

}

void AnalyzerCore::JSFillHist(TString suffix, TString histname,
                  double value_x, double value_y,
                  double weight,
                  int n_binx, double *xbins,
                  int n_biny, double *ybins){

  TH2D *this_hist = JSGetHist2D(suffix, histname);
  if( !this_hist ){

    this_hist = new TH2D(histname, "", n_binx, xbins, n_biny, ybins);
    (JSmaphist_TH2D[suffix])[histname] = this_hist;

  }

  this_hist->Fill(value_x, value_y, weight);

}

void AnalyzerCore::WriteHist(){
  cout << "[AnalyzerCore::WriteHist] Start" << endl;
  cout << printcurrunttime() << endl;
  //outfile->SetCompressionLevel(0);
  
  cout << "maphist_TH1D.size()=" << maphist_TH1D.size() << endl;


  outfile->cd();

  int th1d_idx = 0;
  std::vector<TH1D*> toDelete;

  for(std::map< TString, TH1D* >::iterator mapit = maphist_TH1D.begin(); mapit!=maphist_TH1D.end(); mapit++){
    TString this_fullname=mapit->second->GetName();
    TString this_name=this_fullname(this_fullname.Last('/')+1,this_fullname.Length());
    TString this_suffix=this_fullname(0,this_fullname.Last('/'));

    TDirectory *dir = outfile->GetDirectory(this_suffix);
    
    if(!dir){
      outfile->mkdir(this_suffix);
    }

    outfile->cd(this_suffix);
    mapit->second->Write(this_name); //TEMP
    
    outfile->cd();
    //if(th1d_idx % 1000 == 1 )outfile->Flush();//jhchoi add this line
    if(th1d_idx % 10000 == 1 ){
      if(th1d_idx % 100000 == 1){
	cout << "th1d_idx=" << th1d_idx << endl;
	struct rusage usage;
	getrusage(RUSAGE_SELF, &usage);
	std::cout << "Max RSS: " << usage.ru_maxrss / 1024.0 << " MB\n"; // kilobytes
	cout << "close and reopen tfile" <<endl;
      }
      //close and reopen the out
      TString outfilepath=outfile->GetName();
      outfile->Close();
      outfile = new TFile(outfilepath,"UPDATE");
      //cout << "[done]close and reopen tfile" <<endl;
      
    }
    th1d_idx+=1;

    //    delete mapit->second;
  }
 
  outfile->Flush();//jhchoi add this line
  cout << "[AnalyzerCore::WriteHist] done th1d" << endl;
  cout << printcurrunttime() << endl;

  for(std::map< TString, TH2D* >::iterator mapit = maphist_TH2D.begin(); mapit!=maphist_TH2D.end(); mapit++){
    TString this_fullname=mapit->second->GetName();
    TString this_name=this_fullname(this_fullname.Last('/')+1,this_fullname.Length());
    TString this_suffix=this_fullname(0,this_fullname.Last('/'));
    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);
    mapit->second->Write(this_name);
    outfile->cd();
  }
  for(std::map< TString, TH3D* >::iterator mapit = maphist_TH3D.begin(); mapit!=maphist_TH3D.end(); mapit++){
    TString this_fullname=mapit->second->GetName();
    TString this_name=this_fullname(this_fullname.Last('/')+1,this_fullname.Length());
    TString this_suffix=this_fullname(0,this_fullname.Last('/'));
    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);
    mapit->second->Write(this_name);
    outfile->cd();
  }

  outfile->cd();
  for(std::map< TString, std::map<TString, TH1D*> >::iterator mapit=JSmaphist_TH1D.begin(); mapit!=JSmaphist_TH1D.end(); mapit++){

    TString this_suffix = mapit->first;
    std::map< TString, TH1D* > this_maphist = mapit->second;


    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);

    for(std::map< TString, TH1D* >::iterator mapit = this_maphist.begin(); mapit!=this_maphist.end(); mapit++){
      mapit->second->Write();
    }

    outfile->cd();

  }

  for(std::map< TString, std::map<TString, TH2D*> >::iterator mapit=JSmaphist_TH2D.begin(); mapit!=JSmaphist_TH2D.end(); mapit++){

    TString this_suffix = mapit->first;
    std::map< TString, TH2D* > this_maphist = mapit->second;

    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);

    for(std::map< TString, TH2D* >::iterator mapit = this_maphist.begin(); mapit!=this_maphist.end(); mapit++){
      mapit->second->Write();
    }

    outfile->cd();

  }
  //jhchoi
  
  outfile->mkdir("OutTree");
  outfile->cd("OutTree");
  jhchoi_newtree->Write();
  jhchoi_newtree2->Write();
  jhchoi_newtree3->Write();
  jhchoi_newtree4->Write();
  outfile->cd();
  cout << "[AnalyzerCore::WriteHist] End" << endl;
  cout << printcurrunttime() << endl;

}
//----jhchoi---- Systematics---//


void AnalyzerCore::FillLeptonPlots(std::vector<Lepton *> leps, TString this_region, double weight){

  for(unsigned int i=0; i<leps.size(); i++){

    TString this_itoa = TString::Itoa(i,10);

    Lepton *lep = leps[i];

    FillHist(this_region+"/Lepton_"+this_itoa+"_Pt_"+this_region, lep->Pt(), weight, 1000, 0., 1000.);
    FillHist(this_region+"/Lepton_"+this_itoa+"_Eta_"+this_region, lep->Eta(), weight, 60, -3., 3.);
    FillHist(this_region+"/Lepton_"+this_itoa+"_RelIso_"+this_region, lep->RelIso(), weight, 100, 0., 1.);
    FillHist(this_region+"/Lepton_"+this_itoa+"_MiniRelIso_"+this_region, lep->MiniRelIso(), weight, 100, 0., 1.);

    FillHist(this_region+"/Lepton_"+this_itoa+"_dXY_"+this_region, fabs(lep->dXY()), weight, 500, 0., 0.05);
    FillHist(this_region+"/Lepton_"+this_itoa+"_dXYSig_"+this_region, fabs(lep->dXY()/lep->dXYerr()), weight, 100, 0., 10);
    FillHist(this_region+"/Lepton_"+this_itoa+"_dZ_"+this_region, fabs(lep->dZ()), weight, 500, 0., 0.5);
    FillHist(this_region+"/Lepton_"+this_itoa+"_dZSig_"+this_region, fabs(lep->dZ()/lep->dZerr()), weight, 100, 0., 10);
    FillHist(this_region+"/Lepton_"+this_itoa+"_IP3D_"+this_region, fabs(lep->IP3D()), weight, 500, 0., 0.5);
    FillHist(this_region+"/Lepton_"+this_itoa+"_IP3DSig_"+this_region, fabs(lep->IP3D()/lep->IP3Derr()), weight, 100, 0., 10);

    if(lep->LeptonFlavour()==Lepton::ELECTRON){
      Electron *el = (Electron *)lep;
      FillHist(this_region+"/Lepton_"+this_itoa+"_MVANoIso_"+this_region, el->MVANoIso(), weight, 200, -1., 1.);
    }
    else if(lep->LeptonFlavour()==Lepton::MUON){
      Muon *mu = (Muon *)lep;
      FillHist(this_region+"/Lepton_"+this_itoa+"_Chi2_"+this_region, mu->Chi2(), weight, 500, 0., 50.);
      FillHist(this_region+"/Lepton_"+this_itoa+"_TrkRelIso_"+this_region, mu->TrkIso()/mu->TuneP4().Pt(), weight, 100, 0., 1.);
    }
    else{
      cout << "[AnalyzerCore::FillLeptonPlots] lepton flavour wrong.." << endl;
      exit(EXIT_FAILURE);
    }


  }

}

void AnalyzerCore::FillJetPlots(std::vector<Jet> jets, std::vector<FatJet> fatjets, TString this_region, double weight){

  for(unsigned int i=0; i<jets.size(); i++){

    TString this_itoa = TString::Itoa(i,10);
    FillHist(this_region+"/Jet_"+this_itoa+"_Pt_"+this_region, jets.at(i).Pt(), weight, 1000, 0., 1000.);
    FillHist(this_region+"/Jet_"+this_itoa+"_Eta_"+this_region, jets.at(i).Eta(), weight, 60, -3., 3.);

  }

  for(unsigned int i=0; i<fatjets.size(); i++){

    TString this_itoa = TString::Itoa(i,10);
    FillHist(this_region+"/FatJet_"+this_itoa+"_Pt_"+this_region, fatjets.at(i).Pt(), weight, 1000, 0., 1000.);
    FillHist(this_region+"/FatJet_"+this_itoa+"_Eta_"+this_region, fatjets.at(i).Eta(), weight, 60, -3., 3.);
    FillHist(this_region+"/FatJet_"+this_itoa+"_Mass_"+this_region, fatjets.at(i).M(), weight, 3000, 0., 3000.);
    FillHist(this_region+"/FatJet_"+this_itoa+"_SDMass_"+this_region, fatjets.at(i).SDMass(), weight, 3000, 0., 3000.);
    FillHist(this_region+"/FatJet_"+this_itoa+"_LSF_"+this_region, fatjets.at(i).LSF(), weight, 100, 0., 1.);
    FillHist(this_region+"/FatJet_"+this_itoa+"_PuppiTau21_"+this_region, fatjets.at(i).PuppiTau2()/fatjets.at(i).PuppiTau1(), weight, 100, 0., 1.);
    FillHist(this_region+"/FatJet_"+this_itoa+"_PuppiTau31_"+this_region, fatjets.at(i).PuppiTau3()/fatjets.at(i).PuppiTau1(), weight, 100, 0., 1.);
    FillHist(this_region+"/FatJet_"+this_itoa+"_PuppiTau32_"+this_region, fatjets.at(i).PuppiTau3()/fatjets.at(i).PuppiTau2(), weight, 100, 0., 1.);
  }
  
}




void AnalyzerCore::SetupZptWeight(){
  TString _MCSample=MCSample;
  if(MCSample.Contains("MiNNLO")) _MCSample="MiNNLO";
  TString zptpath=(TString)getenv("DATA_DIR")+"/"+GetEra()+"/SMP/ZptWeight_"+_MCSample+".root";
  if(IsExists(zptpath)){
    cout<<"[AnalyzerCore::SetupZptWeight] using file "+zptpath<<endl;
  }else{
    cout<<"[AnalyzerCore::SetupZptWeight] no "+zptpath<<endl;
    return;
  }
  DeleteZptWeight();
  TFile f(zptpath);
  fZptWeightG=(TF1*)f.Get("zptweight_g");
  if(!fZptWeightG){
    cout<<"[AnalyzerCore::SetupZptWeight] no zptweight_g"<<endl;
    exit(ENODATA);
  }
  fZptWeightYaxis=(TAxis*)f.Get("yaxis");
  if(!fZptWeightYaxis){
    cout<<"[AnalyzerCore::SetupZptWeight] no yaxis"<<endl;
    exit(ENODATA);
  }
  fZptWeightY.resize(fZptWeightYaxis->GetNbins()+2,NULL);
  for(int i=1;i<fZptWeightYaxis->GetNbins()+1;i++){
    fZptWeightY[i]=(TF1*)f.Get(Form("zptweight_y%d",i));
    if(!fZptWeightY[i]){
      cout<<"[AnalyzerCore::SetupZptWeight] no zptweight_y"+TString(i)<<endl;
      exit(ENODATA);
    }
  }
  fZptWeightMaxis=(TAxis*)f.Get("maxis");
  if(!fZptWeightMaxis){
    cout<<"[AnalyzerCore::SetupZptWeight] no maxis"<<endl;
    exit(ENODATA);
  }
  fZptWeightM.resize(fZptWeightMaxis->GetNbins()+2,NULL);
  for(int i=1;i<fZptWeightMaxis->GetNbins()+1;i++){
    fZptWeightM[i]=(TF1*)f.Get(Form("zptweight_m%d",i));
    if(!fZptWeightM[i]){
      cout<<"[AnalyzerCore::SetupZptWeight] no zptweight_m"+TString(i)<<endl;
      exit(ENODATA);
    }
  }
}
double AnalyzerCore::GetZptWeight(double mass,double rapidity,double pt,TString opt){
  if(!fZptWeightG) return 1.;
  if(mass==0) return 1.;
  if(isnan(rapidity)) return 1.;
  double m=mass;
  if(m<fZptWeightMaxis->GetXmin()) m=fZptWeightMaxis->GetXmin();
  if(m>=fZptWeightMaxis->GetXmax()) m=fZptWeightMaxis->GetXmax()-1e-6;
  double y=fabs(rapidity);
  if(y>=fZptWeightYaxis->GetXmax()) y=fZptWeightYaxis->GetXmax()-1e-6;
  if(pt<0) pt=0;
  if(pt>=650) pt=649.9;
  double sf=1.;

  opt.ToUpper();
  if(opt.Contains("G")) sf*=fZptWeightG->Eval(pt);

  if(opt.Contains("Y")){
    double ymin=fZptWeightYaxis->GetBinCenter(1);
    double ymax=fZptWeightYaxis->GetBinCenter(fZptWeightYaxis->GetNbins());
    int biny1,biny2;
    if(y<ymin){
      biny1=1;
      biny2=2;
    }else if(y>=ymax){
      biny1=fZptWeightYaxis->GetNbins()-1;
      biny2=fZptWeightYaxis->GetNbins();
    }else{
      int biny=fZptWeightYaxis->FindBin(y);
      if(y>=fZptWeightYaxis->GetBinCenter(biny)){
        biny1=biny;
        biny2=biny+1;
      }else{
        biny1=biny-1;
        biny2=biny;
      }
    }
    double y1=fZptWeightYaxis->GetBinCenter(biny1);
    double y2=fZptWeightYaxis->GetBinCenter(biny2);
    sf*=( (y2-y)*fZptWeightY[biny1]->Eval(pt) + (y-y1)*fZptWeightY[biny2]->Eval(pt) )/(y2-y1);
  }

  if(opt.Contains("M")){
    double mmin=fZptWeightMaxis->GetBinCenter(1);
    double mmax=fZptWeightMaxis->GetBinCenter(fZptWeightMaxis->GetNbins());
    int binm1,binm2;
    if(m<mmin){
      binm1=1;
      binm2=2;
    }else if(m>=mmax){
      binm1=fZptWeightMaxis->GetNbins()-1;
      binm2=fZptWeightMaxis->GetNbins();
    }else{
      int binm=fZptWeightMaxis->FindBin(m);
      if(m>=fZptWeightMaxis->GetBinCenter(binm)){
        binm1=binm;
        binm2=binm+1;
      }else{
        binm1=binm-1;
        binm2=binm;
      }
    }
    double m1=fZptWeightMaxis->GetBinCenter(binm1);
    double m2=fZptWeightMaxis->GetBinCenter(binm2);
    sf*=( (m2-m)*fZptWeightM[binm1]->Eval(pt) + (m-m1)*fZptWeightM[binm2]->Eval(pt) )/(m2-m1);
  }
  return sf;
}

void AnalyzerCore::DeleteZptWeight(){
  if(fZptWeightG){
    delete fZptWeightG;
    fZptWeightG=NULL;
  }
  if(fZptWeightYaxis){
    delete fZptWeightYaxis;
    fZptWeightYaxis=NULL;
  }
  for(auto f:fZptWeightY){
    if(f) {
      delete f;
      f=nullptr;
    }
  }
  fZptWeightY.clear();
  if(fZptWeightMaxis){
    delete fZptWeightMaxis;
    fZptWeightMaxis=NULL;
  }
  for(auto f:fZptWeightM){
    if(f) {
      delete f;
      f=nullptr;
    }
  }
  fZptWeightM.clear();
}


double AnalyzerCore::GetZ0Weight(double valx){
  if(IsDATA) return 1.;
  double rt=1.;
  if(GetEra()=="2016preVFP"){
    double data_val=TMath::Gaus(valx,2.46312e-01,3.50458e+00,true);
    double mc_val=TMath::Gaus(valx,9.28612e-01,3.65203e+00,true);
    rt=data_val/mc_val;
  }else if(GetEra()=="2016postVFP"){
    double data_val=TMath::Gaus(valx,2.41640e-01,3.63717e+00,true);
    double mc_val=TMath::Gaus(valx,9.30108e-01,3.65454e+00,true);
    rt=data_val/mc_val;
  }else if(GetEra()=="2017"){
    double data_val=TMath::Gaus(valx,3.81830e-01,3.67614e+00,true);
    double mc_val=TMath::Gaus(valx,8.19642e-01,3.50992e+00,true);
    rt=data_val/mc_val;
  }else if(GetEra()=="2018"){
    double data_val=TMath::Gaus(valx,-1.36030e-01,3.41464e+00,true);
    double mc_val=TMath::Gaus(valx,3.58575e-02,3.50953e+00,true);
    rt=data_val/mc_val;
  }
  if(rt>2) rt=2;
  return rt;
}
//For Correction, copy AFB functions
void AnalyzerCore::GetAFBGenParticles(const vector<Gen>& gens,Gen& parton0,Gen& parton1,Gen& l0,Gen& l1,int mode){
  
  //mode 0:bare 1:dressed01 2:dressed04 3:beforeFSR
  if(!IsDYSample&&!MCSample.Contains("GamGamToLL")&&!MCSample.Contains("TTLL")){
    cout <<"[AnalyzerCore::GetAFBGenParticles] this is only for dilepton event"<<endl;
    exit(EXIT_FAILURE);
  }
  parton0=Gen();
  parton1=Gen();
  l0=Gen();
  l1=Gen();
  vector<const Gen*> leptons;
  vector<const Gen*> photons;
  int ngen=gens.size();
  for(int i=0;i<ngen;i++){
    if(!gens.at(i).isPrompt()) continue;
    int genpid=gens.at(i).PID();
    if(gens.at(i).isHardProcess()){
      if(abs(genpid)<7||genpid==21||genpid==22){
        if(parton0.IsEmpty()) parton0=gens[i];
        else if(parton1.IsEmpty()) parton1=gens[i];
      }
    }
    if(gens.at(i).Status()==1){
      if(abs(genpid)==11||abs(genpid)==13) leptons.push_back(&gens[i]);
      else if(gens.at(i).PID()==22) photons.push_back(&gens[i]);
    }
  }
  int nlepton=leptons.size();
  const double maxdr=0.4;
  for(int i=0;i<nlepton;i++){
    if(leptons[i]->PID()!=lhe_l0.ID()) continue;
    if(leptons[i]->DeltaR(lhe_l0)>maxdr) continue;
    if( fabs(leptons[i]->E()-lhe_l0.E()) < fabs(l0.E()-lhe_l0.E()) ){
      l0=*leptons[i];
    }
  }
  if(l0.PID()==0){
    for(int i=0;i<nlepton;i++){
      if(leptons[i]->PID()!=lhe_l0.ID()) continue;
      if(l0.PID()==0 || leptons[i]->DeltaR(lhe_l0)<l0.DeltaR(lhe_l0)){
        l0=*leptons[i];
      }
    }
  }
  for(int i=0;i<nlepton;i++){
    if(leptons[i]->PID()!=lhe_l1.ID()) continue;
    if(leptons[i]->DeltaR(lhe_l1)>maxdr) continue;
    if( fabs(leptons[i]->E()-lhe_l1.E()) < fabs(l1.E()-lhe_l1.E()) ){
      l1=*leptons[i];
    }
  }
  if(l1.PID()==0){
    for(int i=0;i<nlepton;i++){
      if(leptons[i]->PID()!=lhe_l1.ID()) continue;
      if(l1.PID()==0 || leptons[i]->DeltaR(lhe_l1)<l1.DeltaR(lhe_l1)){
        l1=*leptons[i];
      }
    }
  }
  if(l0.Pt()<l1.Pt()){
    Gen tmp=l0;
    l0=l1;
    l1=tmp;
  }
  if(mode>=3){
    if(nlepton>=4){
      for(int i=0;i<nlepton;i++){
        if(leptons[i]->Index()==l0.Index()||leptons[i]->Index()==l1.Index()) continue;
        for(int j=i+1;j<nlepton;j++){
          if(leptons[j]->Index()==l0.Index()||leptons[j]->Index()==l1.Index()) continue;
          if(!(leptons[i]->PID()+leptons[j]->PID()==0)) continue;
          vector<int> history_i=TrackGenSelfHistory(*leptons[i],gens);
          vector<int> history_j=TrackGenSelfHistory(*leptons[j],gens);
          if(history_i.at(1)==history_j.at(1)){
            photons.push_back(leptons[i]);
            photons.push_back(leptons[j]);
          }
        }
      }
    }
    for(const auto& photon:photons){
      vector<int> history=TrackGenSelfHistory(*photon,gens);
      if(gens[history.at(1)].PID()==l0.PID()) l0+=*photon;
      else if(gens[history.at(1)].PID()==l1.PID()) l1+=*photon;
      else if(gens[history.at(1)].PID()==23){ // for minnlo+photos
        if(photon->DeltaR(l0)<photon->DeltaR(l1)) l0+=*photon;
        else l1+=*photon;
      }
    }
  }else if(mode>=1){
    double delr=mode==1?0.1:0.4;
    for(const auto& photon:photons){
      if(l0.DeltaR(*photon)>delr&&l1.DeltaR(*photon)>delr) continue;
      if(l0.DeltaR(*photon)<l1.DeltaR(*photon)) l0+=*photon;
      else l1+=*photon;
    }
  }
}


void AnalyzerCore::GetAFBLHEParticles(const vector<LHE>& lhes,LHE& p0,LHE& p1,LHE& l0,LHE& l1,LHE& j0){
  if(!IsDYSample&&!MCSample.Contains("GamGamToLL")&&!MCSample.Contains("TTLL")){
    cout <<"[AnalyzerCore::GetAFBLHEParticles] this is only for dilepton event"<<endl;
    exit(EXIT_FAILURE);
  }
  p0=LHE();
  p1=LHE();
  l0=LHE();
  l1=LHE();
  j0=LHE();
  if(!lhes.size()) return;
  for(int i=0;i<(int)lhes.size();i++){
    if(p0.ID()==0&&lhes[i].Status()==-1&&lhes[i].Eta()>0) p0=lhes[i];
    if(p1.ID()==0&&lhes[i].Status()==-1&&lhes[i].Eta()<0) p1=lhes[i];
    if(l0.ID()==0&&(abs(lhes[i].ID())==11||abs(lhes[i].ID())==13||abs(lhes[i].ID())==15)) l0=lhes[i];
    if(l0.ID()&&(abs(lhes[i].ID())==11||abs(lhes[i].ID())==13||abs(lhes[i].ID())==15)) l1=lhes[i];
    if(lhes[i].Status()==1)
      if(abs(lhes[i].ID())<=6||lhes[i].ID()==21)
        if(lhes[i].Pt()>j0.Pt()) j0=lhes[i];
  }
  if(p0.ID()==0||p1.ID()==0||l0.ID()==0||l1.ID()==0){
    cout <<"[AFBAnalyzer::GetLHEParticles] something is wrong"<<endl;
    exit(EXIT_FAILURE);
  }
  if(l0.Pt()<l1.Pt()){
    LHE temp=l0;
    l0=l1;
    l1=temp;
  }
}
//
double AnalyzerCore::GetDYWeakWeight(double mass){
  if(IsDATA) return 1.;
  if(!IsDYSample) return 1.;
  if(mass<55) return 0.988939;
  else if(mass<60) return 0.992556;
  else if(mass<65) return 0.996362;
  else if(mass<70) return 1.00086;
  else if(mass<75) return 1.00593;
  else if(mass<80) return 1.00989;
  else if(mass<85) return 1.01263;
  else if(mass<90) return 1.01373;
  else if(mass<95) return 1.01338;
  else if(mass<100) return 1.01242;
  else if(mass<110) return 1.01078;
  else if(mass<120) return 1.00839;
  else if(mass<130) return 1.00628;
  else if(mass<140) return 1.00461;
  else if(mass<150) return 1.0033;
  else if(mass<170) return 1.00201;
  else if(mass<200) return 0.999256;
  else if(mass<250) return 0.995825;
  else if(mass<300) return 0.992451;
  else if(mass<400) return 0.986289;
  else if(mass<500) return 0.979024;
  else if(mass<600) return 0.972292;
  else if(mass<700) return 0.967596;
  else if(mass<800) return 0.959725;
  else if(mass<1000) return 0.953025;
  else if(mass<1500) return 0.935142;
  else if(mass<2000) return 0.909548;
  else if(mass<3000) return 0.8895;
  else return 0.900657;
  
}

//---RoccoR
void AnalyzerCore::SetupRoccoR(){
  cout<<"[SMPAnalyzerCore::SetupRoccoR] setting Rocheseter Correction"<<endl;
  TString erashort=GetEraShort();

  //TString rocpath=datapath+"/"+GetEra()+"/RoccoR/RoccoR"+GetEraShort()+"UL.txt"; //central roccor for amc
  TString rocpath=TString(getenv("SKFlat_WD"))+"/external/Aepcor/u_"+erashort(2,3)+"UL_1.txt"; //roccor for minnlo
  cout << rocpath << endl;
  if(IsExists(rocpath)) roc=new RoccoR(rocpath.Data());
  else cout<<"[SMPAnalyzerCore::SetupRoccoR] no "+rocpath<<endl;

  TString rocelepath=TString(getenv("SKFlat_WD"))+"/external/Aepcor/e_"+erashort(2,3)+"UL_1.txt";
  cout << rocelepath << endl;
  if(IsExists(rocelepath)){
    rocele=new Aepcor;
    rocele->init(rocelepath.Data(),Aepres::CB);
  }
  else cout<<"[SMPAnalyzerCore::SetupRoccoR] no "+rocelepath<<endl;

  TString rocresidualpath=TString(getenv("DATA_DIR"))+"/"+GetEra()+"/SMP/RoccorResidual.root";
  if(IsExists(rocresidualpath)){
    TFile f(rocresidualpath);
    for(TString suffix:{"_scale","_centralRes","_leftFrac","_leftRes","_rightFrac","_rightRes"}){
      fRoccorResidual["electron"+suffix]=(TH1*)f.Get("ee"+GetEraShort()+suffix);
      fRoccorResidual["muon"+suffix]=(TH1*)f.Get("mm"+GetEraShort()+suffix);
    }
    for(auto& [_,h]:fRoccorResidual){
      if(h){
        h->SetDirectory(0);
      }
    }
  }
  else cout<<"[SMPAnalyzerCore::SetupRoccoR] no "+rocresidualpath<<endl;
}

Gen AnalyzerCore::SMPGetGenMatchedLepton(const Lepton& lep,const std::vector<Gen>& gens,int mode){
  //0: default
  //1: dressed 0.1
  Gen gen_lepton=GetGenMatchedLepton(lep,gens);
  if(gen_lepton.IsEmpty()) return gen_lepton;
  if(mode==1){ // dressed 0.1 cone
    for(const auto& gen: gens){
      if(gen.Status()!=1) continue;
      if(gen.PID()!=22) continue;
      if(gen.DeltaR(gen_lepton)>0.1) continue;
      gen_lepton+=gen;
    }
  }

  return gen_lepton;
}

double AnalyzerCore::MuonMomentumCorrection(const Muon& muon,int set,int member){
  double rc=1.;
  if(IsDATA){
    rc=roc->kScaleDT(muon.Charge(),muon.MiniAODPt(),muon.Eta(),muon.Phi(),set,member);
  }else{
    Gen gen=GetGenMatchedLepton(muon,gens);
    if(gen.IsEmpty()){
      gRandom->SetSeed((run<<15)+(lumi<<10)+(event<<5)+muon.Eta()*100);
      double u=gRandom->Rndm();
      rc=roc->kSmearMC(muon.Charge(),muon.MiniAODPt(),muon.Eta(),muon.Phi(),muon.TrackerLayers(),u,set,member);
    }else{
      rc=roc->kSpreadMC(muon.Charge(),muon.MiniAODPt(),muon.Eta(),muon.Phi(),gen.Pt(),set,member);
    }
  }
  return rc;
}

std::vector<Muon> AnalyzerCore::MuonMomentumCorrection(const vector<Muon>& muons,int set,int member,bool sort){
  if(!roc) return std::vector<Muon>(muons);
  std::vector<Muon> out;
  for(auto muon:muons){
    if(set>=0){
      double rc=MuonMomentumCorrection(muon,set,member);
      muon.SetPtEtaPhiM(muon.MiniAODPt()*rc,muon.Eta(),muon.Phi(),muon.M());
    }else if(set==-2){
      double rc=MuonMomentumCorrection(muon,0,0);
      if(fRoccorResidual.find("muon_scale")!=fRoccorResidual.end() && fRoccorResidual["muon_scale"]){
        double eta=fabs(muon.Eta());
        if(eta>=2.4) eta=2.39;
        int ibin=fRoccorResidual["muon_scale"]->FindBin(eta);
        if(IsDATA){
          double scale=1/(1+fRoccorResidual["muon_scale"]->GetBinContent(ibin));
          rc*=scale;
        }
        gRandom->SetSeed((run<<15)+(lumi<<10)+(event<<5)+muon.Eta()*101);
        double u=gRandom->Rndm();
        double centralRes=fRoccorResidual["muon_centralRes"]->GetBinContent(ibin);
        double leftRes=fRoccorResidual["muon_leftRes"]->GetBinContent(ibin);
        double rightRes=fRoccorResidual["muon_rightRes"]->GetBinContent(ibin);
        if(u<fRoccorResidual["muon_leftFrac"]->GetBinContent(ibin) && (leftRes>0)^IsDATA ){
          rc*=1-fabs(gRandom->Gaus(0,fabs(leftRes)));
        }else if(1-u<fRoccorResidual["muon_rightFrac"]->GetBinContent(ibin) && (rightRes>0)^IsDATA ){
          rc*=1+fabs(gRandom->Gaus(0,fabs(rightRes)));
        }else if((centralRes>0)^IsDATA){
          rc*=gRandom->Gaus(1,fabs(centralRes));
        }
      }
      muon.SetPtEtaPhiM(muon.MiniAODPt()*rc,muon.Eta(),muon.Phi(),muon.M());
    }
    out.push_back(muon);
  }
  if(sort) std::sort(out.begin(),out.end(),PtComparing);
  return out;
}

double AnalyzerCore::ElectronEnergyCorrection(const Electron& electron,int set,int member){
  double rc=1.;
  //double rcerr=0.;
  double el_eta=electron.Eta();
  double el_phi=electron.Phi();
  if(IsDATA){
    rc=rocele->kScaleDT(electron.UncorrPt(),el_eta,el_phi,electron.R9(),run,set,member);
  }else{//for MC, we need gen_l0_dressed
    Gen gen;
    //cout << "[EleRoc] gen_l0_dressed is set pt=" << gen_l0_dressed.Pt() << endl;
    //cout << "[EleRoc] gen_l1_dressed is set pt=" << gen_l1_dressed.Pt() << endl;
    if(!gen_l0_dressed.IsEmpty()&&gen_l0_dressed.DeltaR(electron)<0.1){
      gen=gen_l0_dressed;
      //cout << "[EleRoc]gen_l0_dressed is matched" << endl;
    }else if(!gen_l1_dressed.IsEmpty()&&gen_l1_dressed.DeltaR(electron)<0.1){
      gen=gen_l1_dressed;
      //cout << "[EleRoc]gen_l1_dressed is matched" << endl;
    }else{
      gen=SMPGetGenMatchedLepton(electron,gens,1);
      //cout << "[EleRoc]Run matching due to no matched dressed electron" << endl;
    }
    gRandom->SetSeed((run<<15)+(lumi<<10)+(event<<5)+electron.Eta()*100);
    double u=gRandom->Rndm();
    if(!gen.IsEmpty()&&fabs(electron.Pt()/gen.Pt()-1.)<0.5){
      rc=rocele->kSpreadMC(electron.UncorrPt(),el_eta,el_phi,electron.R9(),u,gen.Pt(),set,member);
      /*
      if(hcfscale){
        if(gen.Charge()*electron.Charge()<0){
          double cfscale=GetBinContentUser(hcfscale,electron.Eta(),electron.Pt()*rc,0);
          rc*=cfscale;
        }
      }
      */ // ignore CF now[24.04.05jhchoi]
    }else{
      rc=rocele->kScaleMC(electron.UncorrPt(),el_eta,el_phi,electron.R9(),set,member);
    }
  }
  if(TMath::IsNaN(rc)) rc=1.;  
  return rc*electron.UncorrE()/electron.E();
}
std::vector<Electron> AnalyzerCore::ElectronEnergyCorrection(const vector<Electron>& electrons,int set,int member,bool sort){
  if(!rocele) return std::vector<Electron>(electrons);
  std::vector<Electron> out;
  for(auto electron:electrons){
    if(set>=0){
      electron*=ElectronEnergyCorrection(electron,set,member);
    }else if(set==-1){ //no energe cor
      electron*=electron.UncorrE()/electron.E();
    }else if(set==-2){ //residual energe cor
      electron*=ElectronEnergyCorrection(electron,0,0);
      if(fRoccorResidual.find("electron_scale")!=fRoccorResidual.end() && fRoccorResidual["electron_scale"]){
        double eta=fabs(electron.Eta());
        if(eta>=2.4) eta=2.39;
        int ibin=fRoccorResidual["electron_scale"]->FindBin(eta);
        if(IsDATA){
          double scale=1/(1+fRoccorResidual["electron_scale"]->GetBinContent(ibin));
          electron*=scale;
        }
        gRandom->SetSeed((run<<15)+(lumi<<10)+(event<<5)+electron.Eta()*101);
        double u=gRandom->Rndm();
        double centralRes=fRoccorResidual["electron_centralRes"]->GetBinContent(ibin);
        double leftRes=fRoccorResidual["electron_leftRes"]->GetBinContent(ibin);
        double rightRes=fRoccorResidual["electron_rightRes"]->GetBinContent(ibin);
        if(u<fRoccorResidual["electron_leftFrac"]->GetBinContent(ibin) && (leftRes>0)^IsDATA ){
          electron*=1-fabs(gRandom->Gaus(0,fabs(leftRes)));
        }else if(1-u<fRoccorResidual["electron_rightFrac"]->GetBinContent(ibin) && (rightRes>0)^IsDATA ){
          electron*=1+fabs(gRandom->Gaus(0,fabs(rightRes)));
        }else if((centralRes>0)^IsDATA){
          electron*=gRandom->Gaus(1,fabs(centralRes));
        }
      }
    }else{
      cout<<"[AnalyzerCore::ElectronEnergyCorrection] wrong set "<<set<<endl;
      exit(ENODATA);
    }
    out.push_back(electron);
  }
  if(sort){
    std::sort(out.begin(),out.end(),PtComparing);
  }
  return out;
}

double AnalyzerCore::GetBinContentUser(TH1* hist,double valx,int sys){
  double xmin=hist->GetXaxis()->GetXmin();
  double xmax=hist->GetXaxis()->GetXmax();
  if(xmin>=0) valx=fabs(valx);
  if(valx<xmin) valx=xmin+0.001;
  if(valx>=xmax) valx=xmax-0.001;
  return hist->GetBinContent(hist->FindBin(valx))+sys*hist->GetBinError(hist->FindBin(valx));
}
double AnalyzerCore::GetBinContentUser(TH2* hist,double valx,double valy,int sys){
  double xmin=hist->GetXaxis()->GetXmin();
  double xmax=hist->GetXaxis()->GetXmax();
  double ymin=hist->GetYaxis()->GetXmin();
  double ymax=hist->GetYaxis()->GetXmax();
  if(xmin>=0) valx=fabs(valx);
  if(valx<xmin) valx=xmin+0.001;
  if(valx>=xmax) valx=xmax-0.001;
  if(ymin>=0) valy=fabs(valy);
  if(valy<ymin) valy=ymin+0.001;
  if(valy>=ymax) valy=ymax-0.001;
  return hist->GetBinContent(hist->FindBin(valx,valy))+sys*hist->GetBinError(hist->FindBin(valx,valy));
}
double AnalyzerCore::GetBinContentUser(TH3* hist,double valx,double valy,double valz,int sys){
  double xmin=hist->GetXaxis()->GetXmin();
  double xmax=hist->GetXaxis()->GetXmax();
  double ymin=hist->GetYaxis()->GetXmin();
  double ymax=hist->GetYaxis()->GetXmax();
  double zmin=hist->GetZaxis()->GetXmin();
  double zmax=hist->GetZaxis()->GetXmax();
  if(xmin>=0) valx=fabs(valx);
  if(valx<xmin) valx=xmin+0.001;
  if(valx>xmax) valx=xmax-0.001;
  if(ymin>=0) valy=fabs(valy);
  if(valy<ymin) valy=ymin+0.001;
  if(valy>ymax) valy=ymax-0.001;
  if(zmin>=0) valz=fabs(valz);
  if(valz<zmin) valz=zmin+0.001;
  if(valz>zmax) valz=zmax-0.001;
  return hist->GetBinContent(hist->FindBin(valx,valy,valz))+sys*hist->GetBinError(hist->FindBin(valx,valy,valz));
}

double AnalyzerCore::GetTopPtReweight2(const std::vector<Gen>& gens){
  //==== ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting2017
  //==== Only top quarks in SM ttbar events must be reweighted,
  //==== not single tops or tops from BSM production mechanisms.
  if(!MCSample.Contains("TT") || !MCSample.Contains("powheg")){
    return 1.;
  }
  //==== initialize with large number
  double toppt1=10000, toppt2=10000;
  bool found_top = false, found_atop = false;

  for(vector<Gen>::const_iterator genit=gens.begin(); genit!=gens.end(); genit++){

    if(genit->Status() == 22){
      if(genit->PID() == 6){
        toppt1= genit->Pt();
        found_top = true;
      }
      else if(genit->PID() == -6){
        toppt2= genit->Pt();
        found_atop = true;
      }
    }
    //==== after we found top pair, break the loop
    if(found_top && found_atop) break;
  }
  double pt_reweight = 1.;
  //==== if top pair is not found, return 1.
  pt_reweight*=0.103*exp(-0.0118*toppt1)-0.000134*toppt1+0.973;
  pt_reweight*=0.103*exp(-0.0118*toppt2)-0.000134*toppt2+0.973;
  pt_reweight = sqrt(pt_reweight);
  return pt_reweight;
}
