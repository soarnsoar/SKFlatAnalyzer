#ifndef LHAPDFHandler_h
#define LHAPDFHandler_h

#include "TString.h"
#include <iostream>
#include <vector>
#include "LHAPDF/LHAPDF.h"

using namespace std;

class LHAPDFHandler{

public:

  LHAPDFHandler();
  ~LHAPDFHandler();

  //==== PDF Error Set : Name of the central PDF and members (0~100 etc..)
  TString CentralPDFName;
  LHAPDF::PDF* PDFCentral;
  int ErrorSetMember_Start, ErrorSetMember_End;
  std::vector<LHAPDF::PDF*> PDFErrorSet;
  //==== PDF AlphaS Set : Usually the last two member of central PDF sets
  int AlphaSMember_Down, AlphaSMember_Up;
  LHAPDF::PDF* PDFAlphaSDown;
  LHAPDF::PDF* PDFAlphaSUp;

  void init();

};

#endif
