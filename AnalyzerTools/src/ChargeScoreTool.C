#include "ChargeScoreTool.h"

ChargeScoreTool::ChargeScoreTool(TString objname, TString version, TString DataEra) : TMVATool(Get_xmlpath(objname,version,DataEra)){
  
  }

TString ChargeScoreTool::Get_xmlpath(TString objname, TString version, TString DataEra){
  TString _xmlfile=(TString)getenv("DATA_DIR")+"/"+DataEra+"/TMVA/ChargeScore/v"+version+"/"+objname+"/"+objname+DataEra+"__3__50__100__0.1_DNN.weights.xml";
  std::cout << _xmlfile << std::endl;
  return _xmlfile;
}

ChargeScoreTool::~ChargeScoreTool(){

  
}
