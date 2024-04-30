
#include "JetPUIDTool.h"
#include "TFile.h"
JetPUIDTool::JetPUIDTool(bool _isdata){
  isdata=_isdata;
  map_eraInHist["2016preVFP"]="2016APV";
  map_eraInHist["2016postVFP"]="2016";
  map_eraInHist["2017"]="2017";
  map_eraInHist["2018"]="2018";
}
JetPUIDTool::~JetPUIDTool(){
  if(h) delete h;
  if(hsys) delete hsys;
}
void JetPUIDTool::ReadHist(TString _datadir,TString _era, TString _WP){
  TString filepath=_datadir+"/2017/JetPUID/PUID_106XTraining_ULRun2_EffSFandUncties_v1.root";
  TFile f(filepath);
  TString eraInHist=map_eraInHist[_era];
  //---sf value--//
  TString histpath="h2_eff_sfUL"+eraInHist+"_"+_WP;
  h=(TH2*)f.Get(histpath)->Clone();
  if(!h){
    cout << "[JetPUIDTool::ReadHist] No hist" << histpath << "In file->" << filepath;
    exit(ENODATA);
  }
  h->SetDirectory(0);
  //---sf sys--//
  TString histpath_sys="h2_eff_sfUL"+eraInHist+"_"+_WP+"_Systuncty";
  hsys=(TH2*)f.Get(histpath_sys)->Clone();
  if(!hsys){
    cout << "[JetPUIDTool::ReadHist] No hist" << histpath_sys << "In file->" << filepath;
    exit(ENODATA);
  }
  hsys->SetDirectory(0);
  SetEra(_era);
  SetCut(_WP);
}

void JetPUIDTool::SetEra(TString _era){
  era=_era;
}

void JetPUIDTool::SetCut(TString _WP){//i will only consider |eta|<2.5
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupJetIDUL#Working_Points
  vector<double> vec_cut_T={0,0,0,0};
  vector<double> vec_cut_M={0,0,0,0};
  vector<double> vec_cut_L={0,0,0,0};
  vector<double> vec_cut={0,0,0,0};
  if(era.Contains("2016")){
    vec_cut_T={0.71,0.87,0.94,0.97};//pt 10-20, 20-30, 30-40, 40-50  
    vec_cut_M={0.20,0.62,0.86,0.93};//pt 10-20, 20-30, 30-40, 40-50  
    vec_cut_L={-0.95,-0.90,-0.71,-0.42};//pt 10-20, 20-30, 30-40, 40-50  
  }
  else if(era=="2017" || era=="2018"){
    vec_cut_T={0.77,0.90,0.96,0.98};//pt 10-20, 20-30, 30-40, 40-50  
    vec_cut_M={0.26,0.68,0.90,0.96};//pt 10-20, 20-30, 30-40, 40-50  
    vec_cut_L={-0.95,-0.88,-0.63,-0.19};//pt 10-20, 20-30, 30-40, 40-50  
  }
  else{
    cout << "[JetPUIDTool::SetCut] Wrong Era=" << era << endl;
    exit(ENODATA);    
  }  
  if(_WP=="T"){
    vec_cut=vec_cut_T;
  }
  else if(_WP=="M"){
    vec_cut=vec_cut_M;
  }
  else if(_WP=="L"){
    vec_cut=vec_cut_L;
  }
  else{
    cout << "[JetPUIDTool::SetCut] Wrong WP=" << _WP << endl;
    exit(ENODATA);    
  }

  for(unsigned int i = 0 ; i < vec_cut.size(); i++){
    arr_cut[i]=vec_cut[i];
  }

}


vector<Jet> JetPUIDTool::GetJetsPassPUID(vector<Jet> &jetcoll){
  vector<Jet> jet_pass;
  SF=1.;
  SF_up=1.;
  SF_down=1.;
  for(const auto& jet : jetcoll){
    double this_score=jet.GetPileupJetId();
    double pt=jet.Pt();
    double eta=jet.Eta();
    if(pt > 50.){
      jet_pass.push_back(jet);
    }
    else if((pt > 40.) && (this_score > arr_cut[3])){
      jet_pass.push_back(jet);
      double _SF=GetSF(pt,eta);
      double _SFerr=GetSF_err(pt,eta);
      SF*=_SF;
      SF_up*=(_SF+_SFerr);
      SF_down*=(_SF-_SFerr);
    }
    else if( (pt > 30.) && (this_score > arr_cut[2]) ){
      jet_pass.push_back(jet);
      double _SF=GetSF(pt,eta);
      double _SFerr=GetSF_err(pt,eta);
      SF*=_SF;
      SF_up*=(_SF+_SFerr);
      SF_down*=(_SF-_SFerr);
    }
    else if( (pt > 20.) && (this_score > arr_cut[1])){
      jet_pass.push_back(jet);
      double _SF=GetSF(pt,eta);
      double _SFerr=GetSF_err(pt,eta);
      SF*=_SF;
      SF_up*=(_SF+_SFerr);
      SF_down*=(_SF-_SFerr);
    }
    else if( (pt > 10.) && (this_score > arr_cut[0]) ){
      jet_pass.push_back(jet);
      double _SF=GetSF(pt,eta);
      double _SFerr=GetSF_err(pt,eta);
      SF*=_SF;
      SF_up*=(_SF+_SFerr);
      SF_down*=(_SF-_SFerr);
    }
    else{
      jet_pass.push_back(jet);
    }
  }//[end]jet for loop
  return jet_pass; 
}
double JetPUIDTool::GetSF(double pt, double eta){
  if(isdata) return 1.;
  return h->GetBinContent(h->FindBin(pt,eta));
  
}
double JetPUIDTool::GetSF_err(double pt, double eta){
  if(isdata) return 0.;
  return hsys->GetBinContent(hsys->FindBin(pt,eta));
  
}

double JetPUIDTool::GetCurrentSF(){
  return SF;  
}

double JetPUIDTool::GetCurrentSF_Up(){
  return SF_up;  
}
double JetPUIDTool::GetCurrentSF_Down(){
  return SF_down;  
}
