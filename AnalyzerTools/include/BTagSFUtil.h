#include "BTagCalibrationStandalone.h"
#include <Riostream.h>
#include "TRandom3.h"
#include "TMath.h"
#include "TF1.h"
#include <iostream>
#include <sstream>

using namespace std;

class BTagSFUtil{

 public:
    
  // constructors
  BTagSFUtil(string MeasurementType, string BTagAlgorithmBF, TString OperatingPoint, int year, bool period,  int SystematicIndex);

  // destructor
  ~BTagSFUtil();


  // Function used in analyzer to determine if jet is tagged
  bool IsTagged(float JetDiscriminant, int JetFlavor, float JetPt, float JetEta, int seed);
  bool IsUncorrectedTagged(float JetDiscriminant, int JetFlavor, float JetPt, float JetEta);

  // Functions used in IsTagged to determine tag rate with syst                                                                                                                                                                                                      
  float GetJetSF(int JetFlavor, float JetPt, float JetEta);
  float GetJetSFPeriodDependant(int JetFlavor, float JetPt, float JetEta, TString iperiod, bool isperiodDep, TString tagger);
  float JetTagEfficiency(int JetFlavor, float JetPt, float JetEta);

  // New functions for SKAnalzyer
  void SetMCSample(TString s);

 private:


  // map to store BTagCalibrationReader objects, determined by setup/year
  BTagCalibrationReader* btagReader;
  
  void GetBTagPayload(TString BTagAlgorithm, TString DataPeriod);

  // SF functions
  float ScaleFactorB(float JetPt, int SystematicFlag);
  float ScaleFactorLight(float JetPt, float JetEta, int SystematicFlag);
  float ScaleFactorJet(int JetFlavor, float JetPt, float JetEta, int SystematicFlag);

  // Efficiency functions
  float TagEfficiencyB_2016(float JetPt, float JetEta);
  float TagEfficiencyC_2016(float JetPt, float JetEta);
  float TagEfficiencyLight_2016(float JetPt, float JetEta);

  float TagEfficiencyB_2017(float JetPt, float JetEta);
  float TagEfficiencyC_2017(float JetPt, float JetEta);
  float TagEfficiencyLight_2017(float JetPt, float JetEta);

  float TagEfficiencyB_2018(float JetPt, float JetEta);
  float TagEfficiencyC_2018(float JetPt, float JetEta);
  float TagEfficiencyLight_2018(float JetPt, float JetEta);

  string measurementType;
  string taggerName;
  string operatingPoint;
  float taggerCut;

  TString MCSample;

  int DataYear;

 
  bool period_dependancy;
};
