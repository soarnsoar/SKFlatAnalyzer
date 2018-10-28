#include "GetEffLumi.h"

void GetEffLumi::executeEvent(){

  Event ev = GetEvent();

  FillHist("sumW", 0, ev.MCweight(), 1, 0., 1.);
  if(!IsDATA && PDFWeights_Scale->size()>0){
    FillHist("sumW_Reweight", 0, ev.MCweight()*PDFWeights_Scale->at(0), 1, 0., 1.);
  }

}
