#include "GenFinderForDY.h"

GenFinderForDY::GenFinderForDY(){

  FoundGenZ = false;

}

GenFinderForDY::~GenFinderForDY(){
}

Particle GenFinderForDY::Find(vector<Gen>& gens){

  //==== Method 1) Following EXO-19-016, AN2019_019_v3

  Particle ptl_Z;
  vector<Gen> ZLeptons;
  MethodUsed = -1;
  for(unsigned int i=2; i<gens.size(); i++){

    if(ZLeptons.size()==2) break;

    Gen gen = gens.at(i);
    int pid = abs(gen.PID());
    if( pid==11 || pid==13 ){
      if( gen.Status() == 1 && gen.fromHardProcessFinalState() ){
        ZLeptons.push_back( gen );
      }
    }
    else if( pid==15 ){
      if( gen.Status() == 2 ){
        ZLeptons.push_back( gen );
      }
    }

  }
  if(ZLeptons.size()!=2){

    cout << "===========================================================" << endl;
    cout << "ZLeptons.size() = " << ZLeptons.size() << endl;
    cout << "index\tPID\tStatus\tMIdx\tMPID\tStart\tPt\tEta\tPhi\tM" << endl;
    for(unsigned int i=2; i<gens.size(); i++){
      Gen gen = gens.at(i);
      cout << i << "\t" << gen.PID() << "\t" << gen.Status() << "\t" << gen.MotherIndex() << "\t" << gens.at(gen.MotherIndex()).PID()<< "\t" << "-" << "\t";
      printf("%.2f\t%.2f\t%.2f\t%.2f\n",gen.Pt(), gen.Eta(), gen.Phi(), gen.M());
    }

  }
  else{

    //==== Validate

    bool IsSFOS = ( ZLeptons.at(0).PID()+ZLeptons.at(1).PID() ) == 0;
    if(IsSFOS){

      FoundGenZ = true;
      LeptonPID = abs(ZLeptons.at(0).PID());
      ptl_Z = ZLeptons.at(0)+ZLeptons.at(1);

    }

  }



/*
  Particle ptl_Z;

  for(unsigned int i=2; i<gens.size(); i++){

    Gen gen = gens.at(i);

    //cout << "index = " << i << endl;

    bool IsWhatWeWant = false;
    if( gen.Status() == 1 ){

      int mother_index = gen.MotherIndex();
      if(mother_index<0 || mother_index>=gens.size()) continue;
      Gen mother = gens.at(mother_index);

      while(mother.PID()!=2212){
        //cout << "  mother_index = " << mother_index << endl;
        if(mother.Status() >= 21 && mother.Status() <= 24){
          if( abs(mother.PID()) == 23 || IsLepton(mother.PID()) ){
            IsWhatWeWant = true;
            break;
          }
        }
        mother_index = mother.MotherIndex();
        if(mother_index<0 || mother_index>=gens.size()) break;
        mother = gens.at(mother_index);
      }

    } // END If status 1

    if(IsWhatWeWant) ptl_Z += gen;

  }

  return ptl_Z;
*/





/*

  FoundGenZ = false;
  MethodUsed = -1;

  //==== Try to find Z boson directly by PID

  Gen gen_Z;
  Particle ptl_Z;
  for(unsigned int i=0; i<gens.size(); i++){
    Gen gen = gens.at(i);
    if( abs(gen.PID())==23 ){
      //==== nan check
      //==== index PID Status  MIdx  MPID  Start Pt  Eta Phi M
      //==== 4 23  22  2 -1  4 0.00  -100000000000.00  0.00  -nan
      //==== 5 23  44  4 23  4 1.82  -7.33 -1.06 85.88
      //==== 6 23  62  5 23  4 2.09  -7.19 0.61  85.88
      if( gen.M()==gen.M() ){
        gen_Z = gen;
        ptl_Z = gen;
        MethodUsed = 0;
        FoundGenZ = true;
        break;
      }
    }
  }


  vector<Gen> gen_leptons;
*/
/*
  //=== If Z found
  if(!gen_Z.IsEmpty()){

    //==== find the two lepton whos mother is Z boson found
    for(unsigned int i=2; i<gens.size(); i++){
      Gen gen = gens.at(i);
      Gen mother = gens.at( gen.MotherIndex() );
      if( abs(mother.PID())==gen_Z.PID() ){
        if( IsLepton( gen.PID() ) ){
          gen_leptons.push_back( gen );
        }
      }
    }
    //==== safe guard; make sure we have to leptons
    if(gen_leptons.size()!=2){
      FoundGenZ = false;
      //FillHist("ZFound_notTwolepton", 1., 0., 1, 0., 1.);
    }
    else{
      //==== safe guard; make sure both lepton has same flavour
      if(gen_leptons.at(0).PID()+gen_leptons.at(1).PID()==0){
        MethodUsed = 1;
        FoundGenZ = true;
        LeptonPID = abs( gen_leptons.at(0).PID() );
        ptl_Z = gen_leptons.at(0)+gen_leptons.at(1);
      }
      else{
        FoundGenZ = false;
      }
    }

  }
*/
/*
  //==== Still no?

  //==== Case 1 )
  //==== RunNumber:EventNumber = 1:101380086
  //==== index PID Status  MIdx  MPID  Start Pt  Eta Phi M
  //==== 2 1 21  0 2212  2 0.00  -100000000000.00  0.00  -nan
  //==== 3 -1  21  1 2212  3 0.00  -100000000000.00  0.00  -nan
  //==== 4 -13 23  2 1 4 21.58 1.43  3.01  0.11
  //==== 5 13  23  2 1 5 21.58 0.06  -0.13 0.11
  //==== 6 13  44  5 13  5 17.61 -0.21 0.20  0.11
  //==== Somtines it's gamma

  if(!FoundGenZ){

    gen_leptons.clear();
    for(unsigned int i=0; i<gens.size(); i++){
      if(gen_leptons.size()==2) break;
      Gen gen = gens.at(i);
      int MotherIndex = gen.MotherIndex();
      if(MotherIndex<0 || MotherIndex>=gens.size()) continue;
      Gen mother = gens.at( gen.MotherIndex() );
      if( IsLepton( gen.PID() ) ){
        gen_leptons.push_back( gen );
      }
    }

    //==== safe guard; make sure we have to leptons
    if(gen_leptons.size()!=2){
      FoundGenZ = false;
      //FillHist("ZFound_notTwolepton", 1., 0., 1, 0., 1.);
    }
    else{
      //==== safe guard; make sure both lepton has same flavour
      if(gen_leptons.at(0).PID()+gen_leptons.at(1).PID()==0){
        MethodUsed = 2;
        FoundGenZ = true;
        LeptonPID = abs( gen_leptons.at(0).PID() );
        ptl_Z = gen_leptons.at(0)+gen_leptons.at(1);
      }
      else{
        FoundGenZ = false;
      }
    }

  }
*/

  return ptl_Z;

}

bool GenFinderForDY::IsLepton(int pid){

  return ( abs(pid)==11 || abs(pid)==13 || abs(pid)==15 );

}


