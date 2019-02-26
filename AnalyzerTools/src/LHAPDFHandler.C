#include "LHAPDFHandler.h"

LHAPDFHandler::LHAPDFHandler(){

  CentralPDFName = "";
  ErrorSetMember_Start = -1;
  ErrorSetMember_End = -1;

  AlphaSMember_Down = -1;
  AlphaSMember_Up = -1;

}

void LHAPDFHandler::init(){

  cout << "[LHAPDFHandler::init] Central PDF = " << CentralPDFName << endl;
  PDFCentral = LHAPDF::mkPDF(CentralPDFName.Data(), 0);
  if(ErrorSetMember_Start>=0 && ErrorSetMember_End>=0 && ErrorSetMember_Start<=ErrorSetMember_End){
    cout << "[LHAPDFHandler::init] Initializing PDF Error sets;" << endl;
    for(int i=ErrorSetMember_Start; i<=ErrorSetMember_End; i++){
      cout << "[LHAPDFHandler::init]   member = " << i << endl;
      LHAPDF::PDF* this_pdf = LHAPDF::mkPDF(CentralPDFName.Data(), i);
      PDFErrorSet.push_back( this_pdf );
    }
    cout << "[LHAPDFHandler::init] ----" << endl;
  }

  if(AlphaSMember_Down>=0 && AlphaSMember_Up >= 0){
    cout << "[LHAPDFHandler::init] Initializing PDF AlphaS Down and Up" << endl;
    cout << "[LHAPDFHandler::init]   Down from member = " << AlphaSMember_Down;
    PDFAlphaSDown = LHAPDF::mkPDF(CentralPDFName.Data(), AlphaSMember_Down);
    cout << "[LHAPDFHandler::init]   Up from member = " << AlphaSMember_Up;
    PDFAlphaSUp = LHAPDF::mkPDF(CentralPDFName.Data(), AlphaSMember_Up);
    cout << "[LHAPDFHandler::init] ----" << endl;
  }

}

LHAPDFHandler::~LHAPDFHandler(){

}
