
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
  if(h) {
    delete h;
    h=nullptr;
  }
  if(hsys) {
    delete hsys;
    hsys=nullptr;
  }
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
  //---eff mc --//
  TString histpath_eff="h2_eff_mcUL"+eraInHist+"_"+_WP;
  heff=(TH2*)f.Get(histpath_eff)->Clone();
  if(!heff){
    cout << "[JetPUIDTool::ReadHist] No hist" << histpath_eff << "In file->" << filepath;
    exit(ENODATA);
  }
  heff->SetDirectory(0);
  

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
  SFtotal=1.;
  SFtotal_up=1.;
  SFtotal_down=1.;
  for(const auto& jet : jetcoll){
    double this_score=jet.GetPileupJetId();
    double pt=jet.Pt();
    double eta=jet.Eta();
    if(pt > 50.){
      jet_pass.push_back(jet);
    }
    else if(pt > 40.){
      if(this_score > arr_cut[3]){
	jet_pass.push_back(jet);
	double _SF=GetSF(pt,eta);
	double _SFerr=GetSF_err(pt,eta);
	SFtotal*=_SF;
	SFtotal_up*=(_SF+_SFerr);
	SFtotal_down*=(_SF-_SFerr);
      }
      /*
      else{
	double _SF=GetSF_Fail(pt,eta);
	//double _SFerr=GetSF_err_Fail(pt,eta);
	SFtotal*=_SF;
	SFtotal_up*=GetSF_Fail_Up(pt,eta);
	SFtotal_down*=GetSF_Fail_Down(pt,eta);
      }
      */ // do not care failed jet
    }
    
    else if(pt > 30.){
      if(this_score > arr_cut[2]){
	jet_pass.push_back(jet);
	double _SF=GetSF(pt,eta);
	double _SFerr=GetSF_err(pt,eta);
	SFtotal*=_SF;
	SFtotal_up*=(_SF+_SFerr);
	SFtotal_down*=(_SF-_SFerr);
      }
      /*
      else{
	double _SF=GetSF_Fail(pt,eta);
	SFtotal*=_SF;
	SFtotal_up*=GetSF_Fail_Up(pt,eta);
	SFtotal_down*=GetSF_Fail_Down(pt,eta);

      }
      */ //do not care failed jet
    }
    else if(pt > 20.){
      if(this_score > arr_cut[1]){
	jet_pass.push_back(jet);
	double _SF=GetSF(pt,eta);
	double _SFerr=GetSF_err(pt,eta);
	SFtotal*=_SF;
	SFtotal_up*=(_SF+_SFerr);
	SFtotal_down*=(_SF-_SFerr);
      }
      /*
      else{
	double _SF=GetSF_Fail(pt,eta);
	SFtotal*=_SF;
	SFtotal_up*=GetSF_Fail_Up(pt,eta);
	SFtotal_down*=GetSF_Fail_Down(pt,eta);
      }
      */ //do not care failed jet
    }
    else if(pt > 10.){
      if(this_score > arr_cut[0]){
	jet_pass.push_back(jet);
	double _SF=GetSF(pt,eta);
	double _SFerr=GetSF_err(pt,eta);
	SFtotal*=_SF;
	SFtotal_up*=(_SF+_SFerr);
	SFtotal_down*=(_SF-_SFerr);
      }
      /*
      else{
	double _SF=GetSF_Fail(pt,eta);
	SFtotal*=_SF;
	SFtotal_up*=GetSF_Fail_Up(pt,eta);
	SFtotal_down*=GetSF_Fail_Down(pt,eta);
      }
      */ ////do not care failed jet 
    }
    else{//pt under 10
      jet_pass.push_back(jet);
    }
  }//[end]jet for loop
  return jet_pass; 
}
double JetPUIDTool::GetSF(double pt, double eta){
  if(isdata) return 1.;
  return h->GetBinContent(h->FindBin(pt,eta));
  
}
double JetPUIDTool::GetEff_MC(double pt, double eta){
  if(isdata) return 1.;
  return heff->GetBinContent(h->FindBin(pt,eta));
}
double JetPUIDTool::GetSF_Fail(double pt, double eta){
  if(isdata) return 1.;
  double SF_pass= GetSF(pt,eta);
  double eff_mc=GetEff_MC(pt,eta);
  double eff_data=SF_pass*eff_mc;
  double SF_fail=(1.-eff_data)/(1.-eff_mc);
  return SF_fail;
  
}
double JetPUIDTool::GetSF_err(double pt, double eta){
  if(isdata) return 0.;
  return hsys->GetBinContent(hsys->FindBin(pt,eta));
  
}

double JetPUIDTool::GetSF_Fail_Up(double pt, double eta){
  if(isdata) return 0.;
  double SF_pass_up= GetSF(pt,eta)+GetSF_err(pt,eta);//h->GetBinContent(h->FindBin(pt,eta))+hsys->GetBinContent(h->FindBin(pt,eta));
  double SF_pass= GetSF(pt,eta);
  double eff_mc=GetEff_MC(pt,eta);
  double eff_mc_up= eff_mc*SF_pass/SF_pass_up;
  double eff_data=SF_pass*eff_mc;
  double SF_fail_up=(1.-eff_data)/(1.-eff_mc_up);
  return SF_fail_up;

  
}


double JetPUIDTool::GetSF_Fail_Down(double pt, double eta){
  if(isdata) return 0.;
  double SF_pass_down= GetSF(pt,eta)-GetSF_err(pt,eta);
  double SF_pass= GetSF(pt,eta);
  double eff_mc=GetEff_MC(pt,eta);
  double eff_mc_down=eff_mc*SF_pass/SF_pass_down;//heff->GetBinContent(h->FindBin(pt,eta))*SF_pass/SF_pass_down;
  double eff_data=SF_pass*eff_mc;
  double SF_fail_down=(1.-eff_data)/(1.-eff_mc_down);
  return SF_fail_down;

  
}


double JetPUIDTool::GetCurrentSF(){
  return SFtotal;  
}

double JetPUIDTool::GetCurrentSF_Up(){
  return SFtotal_up;  
}
double JetPUIDTool::GetCurrentSF_Down(){
  return SFtotal_down;  
}
