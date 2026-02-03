#include "TMVATool.h"
#include "TFile.h"
#include <chrono>
using namespace std::chrono;

TMVATool::TMVATool(TString _xmlfile){
  //TMVA::PyMethodBase::PyInitialize();
  //std::cout << "Check python version" << std::endl; 
  //gSystem->Exec("python3 --version");

  //ROOT::DisableImplicitMT();

  
  setenv("OMP_NUM_THREADS", "1", 1);
  setenv("OPENBLAS_NUM_THREADS", "1", 1);
  setenv("MKL_NUM_THREADS", "1", 1);
  setenv("VECLIB_MAXIMUM_THREADS", "1", 1);
  setenv("NUMEXPR_NUM_THREADS", "1", 1);
  std::cout << "[TMVATool] _xmlfile=" << _xmlfile << std::endl;

  this_xmlfile=_xmlfile;
  ReadXML();
  //reader=new TMVA::Reader("V");
  reader=new TMVA::Reader("!Color:!Silent");
  setenv("OMP_NUM_THREADS", "1", 1);
  setenv("OPENBLAS_NUM_THREADS", "1", 1);
  setenv("MKL_NUM_THREADS", "1", 1);
  setenv("VECLIB_MAXIMUM_THREADS", "1", 1);
  setenv("NUMEXPR_NUM_THREADS", "1", 1);
  //TotalCall=0;
  //TotalCallTime=0.;
}
TMVATool::~TMVATool(){
  std::cout << "[TMVATool] Delete reader" << std::endl;
  if(reader){
    delete reader;
    reader=nullptr;
  }
  //std::cout << "[TMVATool] SKIP Delete reader" << std::endl;

  std::cout << "[TMVATool] clear inpuvariable map" << std::endl;

  map_InputVariables.clear();

  std::cout << "[TMVATool DONE] clear inpuvariable map" << std::endl;
}

void TMVATool::ReadXML(){
  std::cout << "[TMVATool::ReadXML]" << std::endl;
  TXMLEngine* xml = new TXMLEngine;
  std::cout << "this_xmlfile=" << this_xmlfile << std::endl;
  XMLDocPointer_t xmldoc = xml->ParseFile(this_xmlfile);
  if (!xmldoc) {
    std::cerr << "Error: Could not parse XML file!" << std::endl;
    if(xml){
      delete xml;
      xml=nullptr;
    }
    exit(1);
    return;
  }
  XMLNodePointer_t MethodSetup = xml->DocGetRootElement(xmldoc);
  if (!MethodSetup) {
    std::cerr << "Error: Could not find MethodSetup element!" << std::endl;
    xml->FreeDoc(xmldoc);
    if(xml){
      delete xml;
      xml=nullptr;
    }
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
    std::cout << "!!Fail to find Variables in xml->" << this_xmlfile << std::endl;
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
  if(xml){
    delete xml;
    xml=nullptr;
  }
  std::cout << "END TMVATool::ReadXML" << std::endl;
}
void TMVATool::AddVariable(TString _formula, float *_this_var_address,float min, float max){//
  /*
  struct VarSlot {
    float* addr;
    float min;
    float max;
};

   */
  map_InputVariables[_formula]={_this_var_address,min,max};
}

void TMVATool::SetupTMVA(TString type){
  Type=type;
  std::cout << "[TMVATool::InitTMVA] Check all input variables are added" << std::endl;
  for(auto& exp : vInputVariables){
    if(map_InputVariables.find(exp) == map_InputVariables.end()){//if there's no exp in map
      std::cout << "No variable for->" << exp << std::endl;
      exit(1);
    }
  }
  ///Now all variables are checked
  std::cout << "[TMVATool::SetupTMVA] Printout variable for this model " << std::endl;
  for(auto& exp : vInputVariables){
    std::cout << exp << std::endl;
    reader->AddVariable(exp,map_InputVariables[exp].addr);
  }

  //setenv("KERAS_BACKEND", "tensorflow", true); 
  //std::cout << "[TMVATool::SetupTMVA]TMVA::PyMethodBase::PyInitialize()" << std::endl;
  //TMVA::PyMethodBase::PyInitialize();

  //reader->BookMVA("PyKeras::DNN",xmlfile);
  reader->BookMVA(Type,this_xmlfile);


  
}
void TMVATool::SetScore(){
  //std::cout << "TMVATool::SetScore" << std::endl;
  //for(auto& exp : vInputVariables){
  //  //reader->AddVariable(exp,map_InputVariables[exp]);
  //  std::cout << exp << "=" << *map_InputVariables[exp] << std::endl;
  //}
  //TotalCall+=1;
  //auto t0 = high_resolution_clock::now();

  for (auto& [expr, slot] : map_InputVariables) {
    *(slot.addr) = std::clamp(*(slot.addr), slot.min, slot.max);
    //std::cout << "[expr]" << expr << ",min=" << slot.min << ",max=" << slot.max << std::endl;
  }

  
  score= reader->EvaluateMVA(Type);
  //auto t1 = high_resolution_clock::now();
  //auto duration = duration_cast<microseconds>(t1 - t0).count()/1000./1000.;
  //TotalCallTime+=duration;
    
  //std::cout << "[TMVATool::SetScore]score=" << score << std::endl;
  
  //std::cout << "[END]TMVATool::SetScore" << std::endl;
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
