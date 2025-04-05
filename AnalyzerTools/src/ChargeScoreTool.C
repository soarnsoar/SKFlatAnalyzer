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


  //2409.2
  if(version=="2409.2"){
    TString nlayer="0"; TString nnode="0"; TString batchsize="0"; TString dropout="0";
    if(DataEra=="2016preVFP"){
      if(objname.Contains("muon")){
	nlayer="5"; nnode="64"; batchsize="100"; dropout="0.2";
      }
      else if(objname.Contains("electron")){
	nlayer="5"; nnode="256"; batchsize="1000"; dropout="0.4";
      }
      else if(objname.Contains("jet")){
	nlayer="5"; nnode="64"; batchsize="1000"; dropout="0.2";
      }
      else{
	std::cout << "Wrong object->" << objname << std::endl;
      }

    }//
    else if(DataEra=="2016postVFP"){
      if(objname.Contains("muon")){
	nlayer="5"; nnode="128"; batchsize="1000"; dropout="0.4";
      }
      else if(objname.Contains("electron")){
	nlayer="5"; nnode="128"; batchsize="1000"; dropout="0.4";
      }
      else if(objname.Contains("jet")){
	nlayer="10"; nnode="256"; batchsize="1000"; dropout="0.2";
      }
      else{
	std::cout << "Wrong object->" << objname << std::endl;
      }

    }

    else if(DataEra=="2017"){
      if(objname.Contains("muon")){
	nlayer="10"; nnode="64"; batchsize="1000"; dropout="0.2";
      }
      else if(objname.Contains("electron")){
	nlayer="5"; nnode="64"; batchsize="1000"; dropout="0.2";
      }
      else if(objname.Contains("jet")){
	nlayer="10"; nnode="128"; batchsize="100"; dropout="0.2";
      }
      else{
	std::cout << "Wrong object->" << objname << std::endl;
      }

    }



    else if(DataEra=="2018"){
      if(objname.Contains("muon")){
	nlayer="10"; nnode="256"; batchsize="500"; dropout="0.4";
      }
      else if(objname.Contains("electron")){
	nlayer="20"; nnode="256"; batchsize="100"; dropout="0.2";
      }
      else if(objname.Contains("jet")){
	nlayer="5"; nnode="256"; batchsize="1000"; dropout="0.2";
      }
      else{
	std::cout << "Wrong object->" << objname << std::endl;
      }

    }

    _xmlfile=(TString)getenv("DATA_DIR")+"/"+DataEra+"/TMVA/ChargeScore/v"+version+"/"+objname+"/"+objname+DataEra+"__"+nlayer+"__"+nnode+"__"+batchsize+"__"+dropout+"_DNN.weights.xml";
  }//[end of 2409.2]
  
  else if(version=="2503.2"){
    TString nlayer="0"; TString nnode="0"; TString batchsize="0"; TString dropout="0";
    if(DataEra=="2016preVFP"){
      if(objname.Contains("muon")){
	nlayer="5"; nnode="64"; batchsize="1000"; dropout="0.2";
      }
      else if(objname.Contains("electron")){
	nlayer="5"; nnode="64"; batchsize="800"; dropout="0.2";
      }
      else if(objname.Contains("jet")){
	nlayer="4"; nnode="64"; batchsize="300"; dropout="0.1";
      }
      else{
	std::cout << "Wrong object->" << objname << std::endl;
      }

    }//
    else if(DataEra=="2016postVFP"){
      if(objname.Contains("muon")){
	nlayer="5"; nnode="200"; batchsize="1200"; dropout="0.5";
      }
      else if(objname.Contains("electron")){
	nlayer="10"; nnode="128"; batchsize="100"; dropout="0.2";
      }
      else if(objname.Contains("jet")){
	nlayer="5"; nnode="64"; batchsize="1000"; dropout="0.2";
      }
      else{
	std::cout << "Wrong object->" << objname << std::endl;
      }

    }

    else if(DataEra=="2017"){
      if(objname.Contains("muon")){
	nlayer="3"; nnode="64"; batchsize="1200"; dropout="0.2";
      }
      else if(objname.Contains("electron")){
	nlayer="6"; nnode="64"; batchsize="1000"; dropout="0.1";
      }
      else if(objname.Contains("jet")){
	nlayer="4"; nnode="50"; batchsize="700"; dropout="0.1";
      }
      else{
	std::cout << "Wrong object->" << objname << std::endl;
      }

    }



    else if(DataEra=="2018"){
      if(objname.Contains("muon")){
	nlayer="3"; nnode="64"; batchsize="1200"; dropout="0.2";
      }
      else if(objname.Contains("electron")){
	nlayer="5"; nnode="128"; batchsize="500"; dropout="0.2";
      }
      else if(objname.Contains("jet")){
	nlayer="5"; nnode="50"; batchsize="700"; dropout="0.1";
      }
      else{
	std::cout << "Wrong object->" << objname << std::endl;
      }

    }


    

    _xmlfile=(TString)getenv("DATA_DIR")+"/"+DataEra+"/TMVA/ChargeScore/v"+version+"/"+objname+"/"+objname+DataEra+"__"+nlayer+"__"+nnode+"__"+batchsize+"__"+dropout+"_DNN.weights.xml";

  }//end of 2503.2

  std::cout << _xmlfile << std::endl;
  return _xmlfile;
}


ChargeScoreTool::~ChargeScoreTool(){

  
}
