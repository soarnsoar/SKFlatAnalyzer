#ifndef GeneralizedEndpoint_h
#define GeneralizedEndpoint_h

#include <iostream>
#include <map>

using namespace std;

struct ScaledPts {
  double ScaledPt, ScaeldPt_Up, ScaeldPt_Down;
};

class GeneralizedEndpoint{

public:
  GeneralizedEndpoint();
  virtual ~GeneralizedEndpoint();

  ScaledPts GeneralizedEndpointPt(float MuonPt, int MuonCharge, float MuonEta, float MuonPhi, int seed);

private:
  std::map<int,std::map<int,float> > _Correction;
  std::map<int,std::map<int,float> > _CorrectionError;   

};

#endif
