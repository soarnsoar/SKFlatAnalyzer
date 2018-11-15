#ifndef SKFlatValidation_h
#define SKFlatValidation_h

#include "AnalyzerCore.h"

class SKFlatValidation : public AnalyzerCore {

public:

  void executeEventFromParameter(AnalyzerParameter param);

  void executeEvent();

  double weight_Prefire;

};



#endif

