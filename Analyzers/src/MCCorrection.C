#include "MCCorrection.h"

MCCorrection::MCCorrection() : 
IgnoreNoHist(false)
{

  TString datapath = getenv("DATA_DIR");
  datapath = datapath+"/ID/";

  string elline;
  ifstream in(datapath+"/Electron/histmap.txt");
  while(getline(in,elline)){
    std::istringstream is( elline );
    TString a,b,c,d,e;
    is >> a; // ID,RERCO
    is >> b; // Eff,SF
    is >> c; // <WPnames>
    is >> d; // <rootfilename>
    is >> e; // <histname>
    TFile *file = new TFile(datapath+"/Electron/"+d);
    map_hist_Electron[a+"_"+b+"_"+c] = (TH2F *)file->Get(e);
  }
/*
  cout << "[MCCorrection::MCCorrection] map_hist_Electron :" << endl;
  for(std::map< TString, TH2F* >::iterator it=map_hist_Electron.begin(); it!=map_hist_Electron.end(); it++){
    cout << it->first << endl;
  }
*/

  string elline2;
  ifstream in2(datapath+"/Muon/histmap.txt");
  while(getline(in2,elline2)){
    std::istringstream is( elline2 );
    TString a,b,c,d,e;
    is >> a; // ID,RERCO
    is >> b; // Eff,SF
    is >> c; // <WPnames>
    is >> d; // <rootfilename>
    is >> e; // <histname>
    TFile *file = new TFile(datapath+"/Muon/"+d);
    map_hist_Muon[a+"_"+b+"_"+c] = (TH2F *)file->Get(e);
  }
/*
  cout << "[MCCorrection::MCCorrection] map_hist_Muon :" << endl;
  for(std::map< TString, TH2F* >::iterator it=map_hist_Muon.begin(); it!=map_hist_Muon.end(); it++){
    cout << it->first << endl;
  }
*/

  // == Get Prefiring maps
  TString prefire_path = getenv("DATA_DIR");
  prefire_path  = prefire_path + "/Prefire/";
  
  string elline3;
  ifstream in3(prefire_path + "histmap.txt");
  while(getline(in3,elline3)){
    std::istringstream is( elline3 );
    TString a,b,c;
    is >> a; // Jet, Photon
    is >> b; // <rootfilename>
    is >> c; // <histname>
    
    TFile *file = new TFile(prefire_path + b);
    map_hist_prefire[a + "_prefire"] = (TH2F *)file->Get(c);
  }


  // == Get Pileup Reweight maps
  TString pileup_path = getenv("DATA_DIR");
  pileup_path = pileup_path + "/PileUp/";

  string elline4;
  ifstream  in4(pileup_path + "histmap.txt");
  while(getline(in4,elline4)){
    std::istringstream is( elline4 );
    TString a,b,c;
    is >> a; // cross sec, up/down
    is >> b; // <root file name>
    is >> c; // <histname>

    TFile *file = new TFile(pileup_path + b);
    map_hist_pileup[a + "_pileup"] = (TH1D *)file->Get(c);
  }

}

MCCorrection::~MCCorrection(){

}

void MCCorrection::SetMCSample(TString s){
  MCSample = s;
}

double MCCorrection::MuonID_SF(TString ID, double eta, double pt, int sys){

  if(ID=="Default") return 1.;

  //cout << "[MCCorrection::MuonID_SF] eta = " << eta << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  eta = fabs(eta);

  if(ID=="NUM_TightID_DEN_genTracks" || ID=="NUM_HighPtID_DEN_genTracks"){
    //==== boundaries
    if(pt<20.) return 1.;
    if(pt>=120.) return 1.;
    if(eta>=2.4) return 1.;
  }

  TH2F *this_hist = map_hist_Muon["ID_SF_"+ID];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cout << "[MCCorrection::MuonID_SF] No "<<"ID_SF_"+ID<<endl;
      exit(EXIT_FAILURE);
    }
  }

  int this_bin = this_hist->FindBin(pt,eta);
  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  //cout << "[MCCorrection::MuonID_SF] value = " << value << endl;

  return value+double(sys)*error;

}

double MCCorrection::MuonISO_SF(TString ID, double eta, double pt, int sys){

  if(ID=="Default") return 1.;

  //cout << "[MCCorrection::MuonISO_SF] eta = " << eta << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  eta = fabs(eta);

  if(ID=="NUM_TightRelIso_DEN_TightIDandIPCut" || ID=="NUM_LooseRelTkIso_DEN_HighPtIDandIPCut"){

    //==== boundaries
    if(pt<20.) return 1.;
    if(pt>=120.) return 1.;
    if(eta>=2.4) return 1.;

  }

  TH2F *this_hist = map_hist_Muon["ISO_SF_"+ID];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cout << "[MCCorrection::MuonISO_SF] No "<<"ISO_SF_"+ID<<endl;
      exit(EXIT_FAILURE);
    }
  }

  int this_bin = this_hist->FindBin(pt,eta);
  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  //cout << "[MCCorrection::MuonISO_SF] value = " << value << endl;

  return value+double(sys)*error;

}

double MCCorrection::MuonTrigger_Eff(TString ID, TString trig, int DataOrMC, double eta, double pt, int sys){

  if(ID=="Default") return 1.;

  //cout << "[MCCorrection::MuonTrigger_Eff] ID = " << ID << "\t" << "trig = " << trig << endl;
  //cout << "[MCCorrection::MuonTrigger_Eff] DataOrMC = " << DataOrMC << endl;
  //cout << "[MCCorrection::MuonTrigger_Eff] eta = " << eta << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  eta = fabs(eta);

  if(trig=="IsoMu27"){
    //==== FIXME MiniAODPt Pt
    //==== FIXME 28.9918	29.0363
    //==== FIXME This event pass pt>29GeV cut, but MiniAOD pt < 29 GeV
    //==== FIXME So when I return 0., SF goes nan.. let's returning 1. for now..
    if(pt<29.) return 1.; //FIXME
    if(eta>=2.4) return 1.;

    if(pt>1200.) pt = 1199.;
  }
  else if(trig=="Mu50"){
    if(pt<52.) return 1.; //FIXME
    if(eta>=2.4) return 1.;

    if(pt>1200.) pt = 1199.;
  }
  else{

  }

  TString histkey = "Trigger_Eff_DATA_"+trig+"_"+ID;
  if(DataOrMC==1) histkey = "Trigger_Eff_MC_"+trig+"_"+ID;
  //cout << "[MCCorrection::MuonTrigger_Eff] histkey = " << histkey << endl;
  TH2F *this_hist = map_hist_Muon[histkey];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cout << "[MCCorrection::MuonTrigger_Eff] No "<<histkey<<endl;
      exit(EXIT_FAILURE);
    }
  }
  
  int this_bin = this_hist->FindBin(pt,eta);
  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  //cout << "[MCCorrection::MuonTrigger_Eff] value = " << value << endl;

  return value+double(sys)*error;


}

double MCCorrection::MuonTrigger_SF(TString ID, TString trig, std::vector<Muon> muons, int sys){

  if(ID=="Default") return 1.;

  double value = 1.;

  if(trig=="IsoMu27" || trig=="Mu50"){

    double eff_DATA = 1.;
    double eff_MC = 1.;

    for(unsigned int i=0; i<muons.size(); i++){
      eff_DATA *= ( 1.-MuonTrigger_Eff(ID, trig, 0, muons.at(i).Eta(), muons.at(i).MiniAODPt(), sys) );
      eff_MC   *= ( 1.-MuonTrigger_Eff(ID, trig, 1, muons.at(i).Eta(), muons.at(i).MiniAODPt(), -sys) );
    }

    eff_DATA = 1.-eff_DATA;
    eff_MC = 1.-eff_MC;

    value = eff_DATA/eff_MC;

/*
    if(eff_DATA==0||eff_MC==0){
      cout << "==== Zero Trigger Eff ====" << endl;
      for(unsigned int i=0;i<muons.size();i++){
        cout << muons.at(i).MiniAODPt() << "\t" << muons.at(i).Pt() << endl;
      }
    }
*/

  }

  return value;

}

double MCCorrection::ElectronID_SF(TString ID, double sceta, double pt, int sys){

  if(ID=="Default") return 1.;

  double value = 1.;
  double error = 0.;

  if(ID=="passMVAID_iso_WP80"){
    if(pt<10.) return 1.;
    if(pt>=500.) return 1.;
    if(fabs(sceta)>=2.5) return 1.;
  }

  TH2F *this_hist = map_hist_Electron["ID_SF_"+ID];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cout << "[MCCorrection::ElectronID_SF] No "<<"ID_SF_"+ID<<endl;
      exit(EXIT_FAILURE);
    }
  }

  //cout << "[MCCorrection::ElectronID_SF] " << this_hist->GetBinContent(4,4) << endl;

  int this_bin = this_hist->FindBin(sceta,pt);
  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  return value+double(sys)*error;

}

double MCCorrection::ElectronReco_SF(double sceta, double pt, int sys){

  double value = 1.;
  double error = 0.;

  TString ptrange = "ptgt20";
  if(pt<20.) ptrange = "ptlt20";

  TH2F *this_hist = map_hist_Electron["RECO_SF_"+ptrange];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cout << "[MCCorrection::ElectronReco_SF] No "<<"RECO_SF_"+ptrange<<endl;
      exit(EXIT_FAILURE);
    }
  }

  //cout << "[MCCorrection::ElectronReco_SF] " << this_hist->GetBinContent(1,1) << endl;

  int this_bin = this_hist->FindBin(sceta,pt);
  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  return value+double(sys)*error;

}


double MCCorrection::GetPrefireWeight(std::vector<Photon> photons, std::vector<Jet> jets, int sys){

  double photon_weight = 1.;
  double jet_weight = 1.;
  
  TH2F *photon_hist = map_hist_prefire["Photon_prefire"];
  TH2F *jet_hist = map_hist_prefire["Jet_prefire"];

  
  for(unsigned int i_pho = 0; i_pho < photons.size(); i_pho++){
    Photon current_photon = photons.at(i_pho);
    double eta = current_photon.scEta();
    double pt = current_photon.Pt();
    
    int this_bin = photon_hist->FindBin(eta, pt);

    double this_eff = photon_hist->GetBinContent(this_bin);
    double this_efferr = photon_hist->GetBinError(this_bin);

    double current_weight = 1. - (this_eff + (double)sys * this_efferr );;
    photon_weight = photon_weight * current_weight;
  }
  
  for(unsigned int i_jet = 0; i_jet < jets.size(); i_jet++){
    Jet current_jet = jets.at(i_jet);
    double eta = current_jet.Eta();
    double pt = current_jet.Pt();
    
    int this_bin = jet_hist->FindBin(eta, pt);

    double this_eff = jet_hist->GetBinContent(this_bin);
    double this_efferr = jet_hist->GetBinError(this_bin);

    double current_weight = 1.- (this_eff + (double)sys * this_efferr);
    jet_weight = jet_weight * current_weight;
  }

  return photon_weight * jet_weight;;

}


double MCCorrection::GetPileUpWeightAsSampleName(int syst, int N_vtx){
  
  double out = 1.;
  if(syst == 0){
    if(!map_hist_pileup[MCSample + "_central_pileup"]) return out;
  }
  else if(syst == -1){
    if(!map_hist_pileup[MCSample + "_down_pileup"]) return out;
  }
  else if(syst == 1){
    if(!map_hist_pileup[MCSample + "_up_pileup"]) return out;
  }
  else return out;
  
  
  if(N_vtx < 100){
    if(syst == 0){
      TH1D *pileup_reweight = map_hist_pileup[MCSample + "_central_pileup"];
      out = pileup_reweight -> GetBinContent(N_vtx+1);
    }
    else if(syst == -1){
      TH1D *pileup_reweight = map_hist_pileup[MCSample + "_down_pileup"];
      out = pileup_reweight -> GetBinContent(N_vtx+1);
    }
    else if(syst == 1){
      TH1D *pileup_reweight = map_hist_pileup[MCSample + "_up_pileup"];
      out = pileup_reweight -> GetBinContent(N_vtx+1);
    }
    else return 1.;
  }
  else{
    if(syst == 0){
      TH1D *pileup_reweight = map_hist_pileup[MCSample + "_central_pileup"];
      out = pileup_reweight -> GetBinContent(100);
    }
    else if(syst == -1){
      TH1D *pileup_reweight = map_hist_pileup[MCSample + "_down_pileup"];
      out = pileup_reweight -> GetBinContent(100);
    }
    else if(syst == 1){
      TH1D *pileup_reweight = map_hist_pileup[MCSample + "_up_pileup"];
      out = pileup_reweight -> GetBinContent(100);
    }
    else return 1.;
  }
  return out;
  
}





