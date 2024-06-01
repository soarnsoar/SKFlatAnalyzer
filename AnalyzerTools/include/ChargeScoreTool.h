#ifndef CHARGESCORETOOL_H
#define CHARGESCORETOOL_H

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

class ChargeScoreTool: public TMVATool {
  
 public:
  ChargeScoreTool(TString objname,TString version, TString DataEra);
  ~ChargeScoreTool();
  TString Get_xmlpath(TString objname, TString version, TString DataEra);
};
#endif
