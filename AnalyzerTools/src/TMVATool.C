#include "TMVATool.h"
#include "TFile.h"
TMVATool::TMVATool(TString _xmlfile){
  xmlfile=_xmlfile;
  ReadXML();
  reader=new TMVA::Reader("V");
  
}
TMVATool::~TMVATool(){
  delete reader;

  //for(auto exp : map_InputVariables){
  //  delete map_InputVariables[exp];
  // }
  
}

void TMVATool::ReadXML(){
  std::cout << "[TMVATool::ReadXML]" << std::endl;
  TXMLEngine* xml = new TXMLEngine;

  XMLDocPointer_t xmldoc = xml->ParseFile(xmlfile);
  if (!xmldoc) {
    std::cerr << "Error: Could not parse XML file!" << std::endl;
    delete xml;
    exit(1);
    return;
  }
  XMLNodePointer_t MethodSetup = xml->DocGetRootElement(xmldoc);
  if (!MethodSetup) {
    std::cerr << "Error: Could not find MethodSetup element!" << std::endl;
    xml->FreeDoc(xmldoc);
    delete xml;
    exit(1);
    return;
  }
  
  XMLNodePointer_t ChildPointer = xml->GetChild(MethodSetup);
  bool FindVariables=false;
  while(!xml->IsEmptyNode(ChildPointer)){
    std::cout << "xml->GetNodeName(ChildPointer)=" << xml->GetNodeName(ChildPointer) << std::endl; 
    if((TString)xml->GetNodeName(ChildPointer)!="Variables"){
      ChildPointer=xml->GetNext(ChildPointer);
    }
    else{
      FindVariables=true;
      break;
    }
  }
  if(!FindVariables){
    std::cout << "!!Fail to find Variables in xml->" << xmlfile << std::endl;
    exit(1);
  }
  //ChildPointer=Variables

  XMLNodePointer_t SecondPointer=xml->GetChild(ChildPointer); //Now SecondPointer=Variable
  while(!xml->IsEmptyNode(SecondPointer)){
    //std::cout << "xml->GetNodeName(SecondPointer)=" << xml->GetNodeName(SecondPointer) << std::endl;
    //std::cout << "xml->GetAttr(SecondPointer,Expression)=" << xml->GetAttr(SecondPointer,"Expression") << std::endl;
    TString Expression= xml->GetAttr(SecondPointer,"Expression");
    vInputVariables.push_back(Expression);
    SecondPointer=xml->GetNext(SecondPointer);
  }
  

  for(auto& exp : vInputVariables){
    std::cout << "exp=" << exp << std::endl;
  }

  delete xml;
  std::cout << "END TMVATool::ReadXML" << std::endl;
}
void TMVATool::AddVariable(TString _formula, float *_this_var_address){//
  map_InputVariables[_formula]=_this_var_address;
}

void TMVATool::SetupTMVA(){
  std::cout << "[TMVATool::InitTMVA] Check all input variables are added" << std::endl;
  for(auto& exp : vInputVariables){
    if(map_InputVariables.find(exp) == map_InputVariables.end()){//if there's no exp in map
      std::cout << "No variable for->" << exp << std::endl;
      exit(1);
    }
  }
  ///Now all variables are checked
  for(auto& exp : vInputVariables){
    reader->AddVariable(exp,map_InputVariables[exp]);
  }

  setenv("KERAS_BACKEND", "tensorflow", true);
  TMVA::PyMethodBase::PyInitialize();
  reader->BookMVA("PyKeras::DNN",xmlfile);
  
}
void TMVATool::SetScore(){
  score= reader->EvaluateMVA("PyKeras::DNN");
}
float TMVATool::GetScore(){
  return score;
}
void TMVATool::SetMinCut(float _mincut){
  std::cout << "SetMinCut->" << _mincut << std::endl;
  mincut=_mincut;
}
void TMVATool::SetMaxCut(float _maxcut){
  std::cout << "SetMaxCut->" << _maxcut << std::endl;
  maxcut=_maxcut;
}
float TMVATool::GetCoefficient(){
  float this_score= GetScore();
  if(this_score>mincut){
    return 1.;
  }
  else if(this_score<maxcut){
    return -1.;
  }
  return 0.;
}
