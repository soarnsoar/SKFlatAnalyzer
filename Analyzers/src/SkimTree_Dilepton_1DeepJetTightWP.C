#include "SkimTree_Dilepton_1DeepJetTightWP.h"

void SkimTree_Dilepton_1DeepJetTightWP::initializeAnalyzer(){

  outfile->cd();
  cout << "[SkimTree_Dilepton_1DeepJetTightWP::initializeAnalyzer()] gDirectory = " << gDirectory->GetName() << endl;
  newtree = fChain->CloneTree(0);

  double_triggers.clear();
  single_electron_triggers.clear();
  single_muon_triggers.clear();
  if(DataYear==2016){
    double_triggers = {
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v",
      "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
      "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",
      "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
      "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",              // H
      "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v",
      "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v",       // B-G
      "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v",      // B-G
      "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v",    // H
      "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"    // H
    };
    single_muon_triggers = {
      "HLT_IsoMu24_v",
      "HLT_IsoTkMu24_v",
    };
    single_electron_triggers = {
      "HLT_Ele27_WPTight_Gsf_v",
    };
  }else if(DataYear==2017){
    double_triggers = {
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",                  // B
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v",          // C-F
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v",
      "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v",
      "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v",      // C-F
      "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v",
      "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"
    };
    single_muon_triggers = {
      "HLT_IsoMu24_v",
      "HLT_IsoMu27_v",
    };
    single_electron_triggers = {
      "HLT_Ele27_WPTight_Gsf_v",
      "HLT_Ele32_WPTight_Gsf_v",
      "HLT_Ele32_WPTight_Gsf_L1DoubleEG_v",
    };
  }else if(DataYear==2018){
    double_triggers = {
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v",
      "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v",
      "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v",
      "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v",
      "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"
    };
    single_muon_triggers = {
      "HLT_IsoMu24_v",
    };
    single_electron_triggers = {
      "HLT_Ele27_WPTight_Gsf_v",
      "HLT_Ele28_WPTight_Gsf_v",
      "HLT_Ele32_WPTight_Gsf_v",
    };
  }else{
    cout<<"[SkimTree_Dilepton_1DeepJetTightWP::initializeAnalyzer] DataYear is wrong : " << DataYear << endl;
  }

  cout << "[SkimTree_Dilepton_1DeepJetTightWP::initializeAnalyzer] triggers to skim = " << endl;
  for(unsigned int i=0; i<double_triggers.size(); i++){
    cout << "[SkimTree_Dilepton_1DeepJetTightWP::initializeAnalyzer]   " << double_triggers.at(i) << endl;
  }
  for(unsigned int i=0; i<single_muon_triggers.size(); i++){
    cout << "[SkimTree_Dilepton_1DeepJetTightWP::initializeAnalyzer]   " << single_muon_triggers.at(i) << endl;
  }
  for(unsigned int i=0; i<single_electron_triggers.size(); i++){
    cout << "[SkimTree_Dilepton_1DeepJetTightWP::initializeAnalyzer]   " << single_electron_triggers.at(i) << endl;
  }

}

void SkimTree_Dilepton_1DeepJetTightWP::executeEvent(){

  Event ev;
  ev.SetTrigger(*HLT_TriggerName);

  //--- nbjet>0
  //bjet -> deepjet tight
  double btagcut=1;
  if(DataEra=="2016preVFP"){
    btagcut=0.6502;
  }
  else if(DataEra=="2016postVFP"){
    btagcut=0.6377;
  }
  else if(DataEra=="2017"){
    btagcut=0.7476;
  }
  else if(DataEra=="2018"){
    btagcut=0.7100;
  }
  else{
    cout << "WRONG DATAERA ->" << DataEra << endl;
    1/0;
  }
  vector<Jet> jets = GetJets("tight", 15, 2.5);
  //std::vector<Jet> AnalyzerCore::GetJets(TString id, double ptmin, double fetamax){
  bool Has_btaggedJet=false;
  for(const auto& jet : jets){
    double btagscore=jet.GetTaggerResult(JetTagging::DeepJet);
    if(btagscore < btagcut) continue;
    Has_btaggedJet=true;
    break;
  }

  if(!Has_btaggedJet) return;





  
  if( ev.PassTrigger(double_triggers) ){
    newtree->Fill();
    return;
  }

  vector<Muon> muons=GetAllMuons();
  std::sort(muons.begin(),muons.end(),PtComparing);
  vector<Electron> electrons=GetAllElectrons();
  std::sort(electrons.begin(),electrons.end(),PtComparing);
  int nmuon=muons.size();
  int nelectron=electrons.size();

  if(ev.PassTrigger(single_muon_triggers)){
    for(int i=0;i<nmuon;i++){
      for(int j=i+1;j<nmuon;j++){
	if(muons.at(i).Pt()<20) continue;
	if(muons.at(j).Pt()<7) continue;
	if((muons.at(i)+muons.at(j)).M()<48) continue;
	if(newtree->Fill()<0) exit(EIO);
	return;
      }
    }
    for(int i=0;i<nmuon;i++){
      for(int j=0;j<nelectron;j++){
	if(muons.at(i).Pt()<20) continue;
	if(electrons.at(j).Pt()<7) continue;
	if((muons.at(i)+electrons.at(j)).M()<48) continue;
	if(newtree->Fill()<0) exit(EIO);
	return;
      }
    }
  }

  if(ev.PassTrigger(single_electron_triggers)){
    for(int i=0;i<nelectron;i++){
      for(int j=i+1;j<nelectron;j++){
	if(electrons.at(i).Pt()<25) continue;
	if(electrons.at(j).Pt()<7) continue;
	if((electrons.at(i)+electrons.at(j)).M()<48) continue;
	if(newtree->Fill()<0) exit(EIO);
	return;
      }
    }
    for(int i=0;i<nelectron;i++){
      for(int j=0;j<nmuon;j++){
	if(electrons.at(i).Pt()<25) continue;
	if(muons.at(j).Pt()<7) continue;
	if((electrons.at(i)+muons.at(j)).M()<48) continue;
	if(newtree->Fill()<0) exit(EIO);
	return;
      }
    }
  }
}

void SkimTree_Dilepton_1DeepJetTightWP::executeEventFromParameter(AnalyzerParameter param){

}

SkimTree_Dilepton_1DeepJetTightWP::SkimTree_Dilepton_1DeepJetTightWP(){
  newtree=NULL;
}

SkimTree_Dilepton_1DeepJetTightWP::~SkimTree_Dilepton_1DeepJetTightWP(){

}

void SkimTree_Dilepton_1DeepJetTightWP::WriteHist(){

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree->Write();
  outfile->cd();

}
