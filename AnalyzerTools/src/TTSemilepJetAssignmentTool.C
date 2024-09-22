#include "TTSemilepJetAssignmentTool.h"

TTSemilepJetAssignmentTool::TTSemilepJetAssignmentTool(TString version, TString DataEra) : TMVATool(Get_xmlpath(version,DataEra)){
  
}

TString TTSemilepJetAssignmentTool::Get_xmlpath(TString version, TString DataEra){
  TString _xmlfile=(TString)getenv("DATA_DIR")+"/"+DataEra+"/TMVA/TTSemilepJetAssignment/v"+version+"/"+DataEra+"__5__128__500__0.2_DNN.weights.xml";
  std::cout << _xmlfile << std::endl;
  return _xmlfile;
}


TTSemilepJetAssignmentTool::~TTSemilepJetAssignmentTool(){
  
  
}
