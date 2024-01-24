#include "SysTemplate.h"

SysTemplate::SysTemplate(){

}

void SysTemplate::initializeAnalyzer(){

  RunSyst = HasFlag("RunSyst");
  cout << "[SysTemplate::initializeAnalyzer] RunSyst = " << RunSyst << endl;

  if(RunSyst && !IsDATA){
    
  }

}

SysTemplate::~SysTemplate(){

  //==== Destructor of this Analyzer

}

void SysTemplate::executeEvent(){
  cout << "--start event--" << endl;
  vector<vector<double>> _mytest = fEff->GetStructure("Muon_RECO");
  unsigned int nset=_mytest.size();
  for(unsigned int is=0; is<nset;is++){
    unsigned int nmem=_mytest[is].size();
    for (unsigned int im=0; im<nmem; im++){
      double this_weight= _mytest[is][im];
      
      cout << is << "," << im << this_weight << endl;
    }
  }
}
 
//void SysTemplate::executeEventUsingParameter(){
//  vector<Muon> AllMuons_raw=GetAllMuons();
//

//}



