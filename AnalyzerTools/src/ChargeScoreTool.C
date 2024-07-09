#include "ChargeScoreTool.h"

ChargeScoreTool::ChargeScoreTool(TString objname, TString version, TString DataEra) : TMVATool(Get_xmlpath(objname,version,DataEra)){
  
}

TString ChargeScoreTool::Get_xmlpath(TString objname, TString version, TString DataEra){
  TString _xmlfile=(TString)getenv("DATA_DIR")+"/"+DataEra+"/TMVA/ChargeScore/v"+version+"/"+objname+"/"+objname+DataEra+"__3__50__100__0.1_DNN.weights.xml";
  if(version=="2405.4")_xmlfile=(TString)getenv("DATA_DIR")+"/"+DataEra+"/TMVA/ChargeScore/v"+version+"/"+objname+"/"+objname+DataEra+"__5__64__500__0.2_DNN.weights.xml";
  if(version=="2405.4.3"){
    TString nlayer="0"; TString nnode="0"; TString batchsize="0"; TString dropout="0";
    if(objname.Contains("muon")){
      nlayer="3"; nnode="48"; batchsize="1100";dropout="0.1";
    }
    else if(objname.Contains("electron")){
      nlayer="3"; nnode="48"; batchsize="600";dropout="0.1";
    }
    else if(objname.Contains("jet")){
      nlayer="5"; nnode="64"; batchsize="1000";dropout="0.2";
    }
    else{
      std::cout << "Wrong object->" << objname << std::endl;
    }
      _xmlfile=(TString)getenv("DATA_DIR")+"/"+DataEra+"/TMVA/ChargeScore/v"+version+"/"+objname+"/"+objname+DataEra+"__"+nlayer+"__"+nnode+"__"+batchsize+"__"+dropout+"_DNN.weights.xml";
  }
  std::cout << _xmlfile << std::endl;
  return _xmlfile;
}


ChargeScoreTool::~ChargeScoreTool(){

  
}
