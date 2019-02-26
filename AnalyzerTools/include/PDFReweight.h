#ifndef PDFReweight_h
#define PDFReweight_h

#include "TString.h"
#include <iostream>
#include <vector>
#include "LHAPDFHandler.h"

using namespace std;

class PDFReweight{

public:

  PDFReweight();
  ~PDFReweight();

  inline void SetProdPDF(LHAPDF::PDF* pdf_){
    ProdPDF = pdf_;
  }
  inline void SetNewPDF(LHAPDF::PDF*  pdf_){
    NewPDF = pdf_;
  }
  inline void SetNewPDFErrorSet(vector<LHAPDF::PDF*> newPDFErrorSet){
    PDFErrorSet = newPDFErrorSet;
    NErrorSet = PDFErrorSet.size();
  }
  inline void SetNewPDFAlphaS(LHAPDF::PDF* newPDFAlphaSDown, LHAPDF::PDF* newPDFAlphaSUp){
    NewPDFAlphaSDown = newPDFAlphaSDown;
    NewPDFAlphaSUp = newPDFAlphaSUp;
  }

  //==== PDF used for the production
  LHAPDF::PDF* ProdPDF;
  //==== New PDF 
  LHAPDF::PDF* NewPDF;
  vector<LHAPDF::PDF*> PDFErrorSet;
  int NErrorSet;
  LHAPDF::PDF* NewPDFAlphaSDown;
  LHAPDF::PDF* NewPDFAlphaSUp;

};

#endif
