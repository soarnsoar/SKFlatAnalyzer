#include "SkimTree_SingleLepton_1DeepJetTightWP.h"

void SkimTree_SingleLepton_1DeepJetTightWP::initializeAnalyzer(){

  outfile->cd();
  cout << "[SkimTree_SingleLepton_1DeepJetTightWP::initializeAnalyzer()] gDirectory = " << gDirectory->GetName() << endl;
  newtree = fChain->CloneTree(0);

  cout << "[DataEra]=" << DataEra  << endl;

  single_lepton_triggers.clear();
  if(DataYear==2016){
    
    single_lepton_triggers = {
      "HLT_IsoMu24_v",
      "HLT_IsoTkMu24_v",
      "HLT_Ele27_WPTight_Gsf_v",
    };
  }else if(DataYear==2017){
    single_lepton_triggers = {
      "HLT_IsoMu24_v",
      "HLT_IsoMu27_v",

      "HLT_Ele27_WPTight_Gsf_v",
      "HLT_Ele32_WPTight_Gsf_v",
      "HLT_Ele32_WPTight_Gsf_L1DoubleEG_v",
    };
  }else if(DataYear==2018){
    
    single_lepton_triggers = {
      "HLT_IsoMu24_v",
      "HLT_Ele27_WPTight_Gsf_v",
      "HLT_Ele28_WPTight_Gsf_v",
      "HLT_Ele32_WPTight_Gsf_v",
    };
  }else{
    cout<<"[SkimTree_SingleLepton_1DeepJetTightWP::initializeAnalyzer] DataYear is wrong : " << DataYear << endl;
  }

  cout << "[SkimTree_SingleLepton_1DeepJetTightWP::initializeAnalyzer] triggers to skim = " << endl;

  for(unsigned int i=0; i<single_lepton_triggers.size(); i++){
    cout << "[SkimTree_SingleLepton_1DeepJetTightWP::initializeAnalyzer]   " << single_lepton_triggers.at(i) << endl;
  }


}

void SkimTree_SingleLepton_1DeepJetTightWP::executeEvent(){

  Event ev;
  ev.SetTrigger(*HLT_TriggerName);
  //--- single lepton trigger
  if( !ev.PassTrigger(single_lepton_triggers) ){
    //newtree->Fill();
    return;
  }

  //--no requirement on nLep... very little reduction


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
  newtree->Fill();
  
}

void SkimTree_SingleLepton_1DeepJetTightWP::executeEventFromParameter(AnalyzerParameter param){

}

SkimTree_SingleLepton_1DeepJetTightWP::SkimTree_SingleLepton_1DeepJetTightWP(){
  newtree=NULL;
}

SkimTree_SingleLepton_1DeepJetTightWP::~SkimTree_SingleLepton_1DeepJetTightWP(){

}

void SkimTree_SingleLepton_1DeepJetTightWP::WriteHist(){

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree->Write();
  outfile->cd();

}
