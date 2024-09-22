#ifndef TTSemilepJetAssignmentTool_H
#define TTSemilepJetAssignmentTool_H

#include "TMVATool.h"
#include <map>
#include <vector>
#include "TString.h"
#include <TXMLEngine.h>
#include <TSystem.h>
#include <iostream>
#include "TMVA/PyMethodBase.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

class TTSemilepJetAssignmentTool: public TMVATool {
  
 public:
  TTSemilepJetAssignmentTool(TString version, TString DataEra);
  ~TTSemilepJetAssignmentTool();
  TString Get_xmlpath(TString version, TString DataEra);
};
#endif
