#include "BBosillation.h"

BBosillation::BBosillation(){

}

void BBosillation::initializeAnalyzer(){

  RunSyst = HasFlag("RunSyst");
  cout << "[BBosillation::initializeAnalyzer] RunSyst = " << RunSyst << endl;

  if(RunSyst && !IsDATA){
    
  }

}

BBosillation::~BBosillation(){

  //==== Destructor of this Analyzer

}

void BBosillation::executeEvent(){

  std::vector<Gen> GENs = GetGens();
  unsigned int gensize=GENs.size();
  vector<int> oscillation_mother;
  vector<int> no_oscillation_mother;
  set<int> set_oscillation_mother;
  set<int> set_no_oscillation_mother;
  double weight=MCweight();
  for(unsigned int i = 0 ; i < gensize; i++){

    int GEN_pid=GENs[i].PID();
    int GEN_mother=GENs[i].MotherIndex();
    if(GEN_pid==511){
      FillHist("all/Bmeson_Charge/"+MCSample, 0, weight, 4, -2., 2.);
    }
    else if(GEN_pid==521){
      FillHist("all/Bmeson_Charge/"+MCSample, 1, weight, 4, -2., 2.);
    }
    else if(GEN_pid==-521){
      FillHist("all/Bmeson_Charge/"+MCSample, -1, weight, 4, -2., 2.);
    }
    //511(B0) 521(B+) -521(B-)
    /*
    if(abs(GENs[GEN_mother].PID())==511){
      cout << "MOTHER=" << GENs[GEN_mother].PID() << setw(15) << "motheridx=" << GEN_mother << endl;
      
      cout << "GEN_pid=" << GEN_pid << endl;
    }
    */
    if(
       GEN_mother > -1 &&
       ((abs(GEN_pid)==11) || (abs(GEN_pid)==13) || (abs(GEN_pid)==15) ) 
       )
      {
	int mother_pid= GENs[GEN_mother].PID();
	if(abs(mother_pid)==511){
	  if(mother_pid * GEN_pid > 0 ){//e.g) 511=db~, 13=mu- : osillation
	    oscillation_mother.push_back(GEN_mother);
	    set_oscillation_mother.insert(GEN_mother);
	  }
	  else{
	    no_oscillation_mother.push_back(GEN_mother);
	    set_no_oscillation_mother.insert(GEN_mother);
	  }

	}//[end] if abs mother pid ==511
      }//[end] if mother >-1
  }//[end] for loop genparticles

  FillHist("all/IsOscillated/"+MCSample, 0, set_no_oscillation_mother.size()*weight, 4, -1., 3.);
  FillHist("all/IsOscillated/"+MCSample, 1, set_oscillation_mother.size()*weight, 4, -1., 3.);
  //for(unsigned int i = 0 ; i < set_no_oscillation_mother.size(); i++){
  for(const auto& motheridx : set_no_oscillation_mother){
  
    //unsigned int motheridx=set_no_oscillation_mother[i];
    double mother_pt = GENs[motheridx].Pt();
    double mother_E = GENs[motheridx].E();
    int mother_pid= GENs[motheridx].PID();
    FillHist("B0Bbar0_NotOscillated/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
    FillHist("B0Bbar0_NotOscillated/E/"+MCSample, mother_E, weight, 200, 0., 200.);
    FillHist("B0Bbar0/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
    FillHist("B0Bbar0/E/"+MCSample, mother_E, weight, 200, 0., 200.);
    if(mother_pid==511){
      FillHist("B0_NotOscillated/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
      FillHist("B0_NotOscillated/E/"+MCSample, mother_E, weight, 200, 0., 200.);
      FillHist("B0_all/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
      FillHist("B0_all/E/"+MCSample, mother_E, weight, 200, 0., 200.);
    }
    else{
      FillHist("Bbar0_NotOscillated/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
      FillHist("Bbar0_NotOscillated/E/"+MCSample, mother_E, weight, 200, 0., 200.);
      FillHist("Bbar0_all/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
      FillHist("Bbar0_all/E/"+MCSample, mother_E, weight, 200, 0., 200.);
    }
  }

  //for(unsigned int i = 0 ; i < set_oscillation_mother.size(); i++){
  for(const auto& motheridx : set_oscillation_mother){
    //unsigned int motheridx=set_oscillation_mother[i];
    double mother_pt = GENs[motheridx].Pt();
    double mother_E = GENs[motheridx].E();
    int mother_pid= GENs[motheridx].PID();
    FillHist("B0Bbar0/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
    FillHist("B0Bbar0/E/"+MCSample, mother_E, weight, 200, 0., 200.);
    FillHist("B0Bbar0_Oscillated/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
    FillHist("B0Bbar0_Oscillated/E/"+MCSample, mother_E, weight, 200, 0., 200.);
    if(mother_pid==511){
      FillHist("B0_Oscillated/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
      FillHist("B0_Oscillated/E/"+MCSample, mother_E, weight, 200, 0., 200.);
      FillHist("B0_all/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
      FillHist("B0_all/E/"+MCSample, mother_E, weight, 200, 0., 200.);
    }
    else{
      FillHist("Bbar0_Oscillated/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
      FillHist("Bbar0_Oscillated/E/"+MCSample, mother_E, weight, 200, 0., 200.);
      FillHist("Bbar0_all/pt/"+MCSample, mother_pt, weight, 200, 0., 200.);
      FillHist("Bbar0_all/E/"+MCSample, mother_E, weight, 200, 0., 200.);
    }
  }

  /*
  for(unsigned int j = 0 ; j < oscillation_mother.size(); j++){

    cout << "===Mother => " << GENs[oscillation_mother[j]].PID() << endl;
    cout << "i" << setw(15) << "pid" << endl;
    for(unsigned int i =0; i < gensize; i++){  
      int GEN_mother=GENs[i].MotherIndex();
      int GEN_pid=GENs[i].PID();
      if(GEN_mother == oscillation_mother[j] ){
	//cout << i << setw(15) << GEN_pid << endl;
      }
      
      
    }
  }
  */
}

//void BBosillation::executeEventUsingParameter(){
//  vector<Muon> AllMuons_raw=GetAllMuons();
//

//}



