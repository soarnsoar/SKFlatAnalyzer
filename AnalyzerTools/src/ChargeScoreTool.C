#include "ChargeScoreTool.h"

ChargeScoreTool::ChargeScoreTool(TString objname, TString version, TString DataEra) : TMVATool(Get_xmlpath(objname,version,DataEra)){
  
}
TString ChargeScoreTool::Get_xmlpath(TString objname, TString version, TString DataEra){
  TString _xmlfile=(TString)getenv("DATA_DIR")+"/"+DataEra+"/TMVA/ChargeScore/BDT/v"+version+"/"+objname+"/FIN_BDT_"+DataEra+"_BDT.weights.xml";
  if(version=="2608.2"){
    //BDT_2017_BDT.weights.xml
    _xmlfile=(TString)getenv("DATA_DIR")+"/"+DataEra+"/TMVA/ChargeScore/BDT/v"+version+"/"+objname+"/BDT_"+DataEra+"_BDT.weights.xml";
  }
  std::cout << "[ChargeScoreTool::Get_xmlpath]_xmlfile=" << _xmlfile << std::endl; 
  return _xmlfile;
  
}



ChargeScoreTool::~ChargeScoreTool(){

  
}
