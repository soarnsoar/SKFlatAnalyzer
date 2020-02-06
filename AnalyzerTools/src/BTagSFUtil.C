#include "BTagSFUtil.h"
#include "BTagCalibrationStandalone.cc"
#include "BTagEfficiencies/BTagEfficienciesTTbar16.C" // Change this if MC are updated
#include "BTagEfficiencies/BTagEfficienciesTTbar17.C" // Change this if MC are updated  
#include "BTagEfficiencies/BTagEfficienciesTTbar18.C" // Change this if MC are updated  

//#################################################
//=== To do list
//#################################################
//--- TODO add fast sim efficiency once one is available  
//--- TODO add AK8 code
//--- TODO add charm tagging code
//#################################################

void BTagSFUtil::SetMCSample(TString s){
  MCSample = s;
}

BTagSFUtil::BTagSFUtil(string MeasurementType, string BTagAlgorithm,  TString OperatingPoint, int year, bool pd, int SystematicIndex) {

  cout << "[BTagSFUtil::BTagSFUtil] Contructing BTagSFUtil class with" << endl;
  cout << "[BTagSFUtil::BTagSFUtil]   MeasurementType = " << MeasurementType << endl;
  cout << "[BTagSFUtil::BTagSFUtil]   BTagAlgorithm = " << BTagAlgorithm << endl;
  cout << "[BTagSFUtil::BTagSFUtil]   OperatingPoint = " << OperatingPoint << endl;
  cout << "[BTagSFUtil::BTagSFUtil]   year = " << year << endl;
  cout << "[BTagSFUtil::BTagSFUtil]   pd = " << pd << endl;
  cout << "[BTagSFUtil::BTagSFUtil]   SystematicIndex = " << SystematicIndex << endl;

  //=== initialise global variables
  MCSample = "";

  measurementType = MeasurementType;
  taggerName = BTagAlgorithm;
  operatingPoint = OperatingPoint;
  DataYear = year;
  period_dependancy = pd;
  
  //=== set paths 
  TString datapath = getenv("DATA_DIR");
  TString btagpath = datapath+"/"+TString::Itoa(DataYear,10)+"/BTag/";

  //=== set systematic flags
  string SystematicFlag = "central";
  if(SystematicIndex<0) SystematicFlag = "down";
  if(SystematicIndex>0) SystematicFlag = "up";

  //=== Initialise taggerCut, set by taggermap.txt
  taggerCut = -1;
  ifstream in_tagger(btagpath+"/taggermap.txt");
  string btaggerline;
  while(getline(in_tagger,btaggerline)){
    std::istringstream is_tag( btaggerline );
    TString tstring_taggerline = btaggerline;
    if(tstring_taggerline.Contains("#")) continue;
    int a;
    TString b,c;
    float cutvalue; 
    
    is_tag >> a; // YEAR
    is_tag >> b; // TAGGER
    is_tag >> c; // WP
    is_tag >> cutvalue;  // cut value

    if(a == DataYear && b == BTagAlgorithm && c == OperatingPoint ) {
      taggerCut = cutvalue; 
      break;
    }
  }// end of taggermap loop
  if(taggerCut<0){
    cerr << "[BTagSFUtil::BTagSFUtil] Tagger working point not found from " << btagpath+"/taggermap.txt" << endl;
    cerr << "[BTagSFUtil::BTagSFUtil] DataYear = " << DataYear << endl;
    cerr << "[BTagSFUtil::BTagSFUtil] BTagAlgorithm = " << BTagAlgorithm << endl;
    cerr << "[BTagSFUtil::BTagSFUtil] OperatingPoint = " << OperatingPoint << endl;
    exit(EXIT_FAILURE);
  }

  //=== Set OperatingPoint passed by var OperatingPoint
  BTagEntry::OperatingPoint op = BTagEntry::OP_LOOSE;
  if(OperatingPoint=="Loose"){
    op = BTagEntry::OP_LOOSE;
  }
  else if(OperatingPoint=="Medium"){
    op = BTagEntry::OP_MEDIUM;
  }
  else if(OperatingPoint=="Tight"){
    op = BTagEntry::OP_TIGHT;
  }
  else{
    cerr << "[BTagSFUtil::BTagSFUtil] Wrong OperatingPoint : " << OperatingPoint << endl;
    exit(EXIT_FAILURE);
  }
    
  //=== open histmap file to tell code which file to use depending on year/tagger
  ifstream in(btagpath+"/histmap.txt");
  string btagline;
  if(period_dependancy) cout << "[BTagSFUtil::BTagSFUtil] setting up Period dependant SF" << endl;
  else  cout << "[BTagSFUtil::BTagSFUtil] setting up non-period dependant SF" << endl;

  btagReader = NULL;
  while(getline(in,btagline)){
    std::istringstream is( btagline );
    
    TString tstring_btagline = btagline;
    if(tstring_btagline.Contains("#")) continue;

    string a,f;
    TString b,c,d,e;

    is >> a; // YEAR
    is >> b; // TAGGER
    is >> c; // Period_dep
    is >> d; // Run_start
    is >> e; // Run_end
    is >> f; // csv file                                                                                                                                                                           

    istringstream buffer(a);
    int dy;
    buffer >> dy;

    if( dy != DataYear) continue;
    if( b != BTagAlgorithm) continue;
    
    if( (period_dependancy&& c=="PeriodDep") || (!period_dependancy && c!="PeriodDep")){   
      BTagCalibration calib(BTagAlgorithm, MeasurementType, string(btagpath)+f);
      btagReader = new BTagCalibrationReader(&calib, op, MeasurementType, SystematicFlag);
      break;
    }
  }
  if(!btagReader){
    cout << "[BTagSFUtil::BTagSFUtil] csv file is not found for" << endl;
    cout << "[BTagSFUtil::BTagSFUtil] measurementType = " << measurementType << endl;
    cout << "[BTagSFUtil::BTagSFUtil] taggerName = " << taggerName << endl;
    cout << "[BTagSFUtil::BTagSFUtil] operatingPoint = " << operatingPoint << endl;
    exit(EXIT_FAILURE);
  }
  
}

BTagSFUtil::~BTagSFUtil() {

  delete btagReader;

}

float BTagSFUtil::JetTagEfficiency(int JetFlavor, float JetPt, float JetEta) {

  float ThisJetPt = JetPt;

  if     (JetPt > 999.99) ThisJetPt = 999.99;
  else if(JetPt < 20.   ) ThisJetPt = 20.;
  
  if(DataYear == 2016){
    if (abs(JetFlavor)==5) return TagEfficiencyB_2016(ThisJetPt, JetEta);
    else if (abs(JetFlavor)==4) return TagEfficiencyC_2016(ThisJetPt, JetEta);
    else return TagEfficiencyLight_2016(ThisJetPt, JetEta);
  }
  else  if(DataYear == 2017){
    if (abs(JetFlavor)==5) return TagEfficiencyB_2017(ThisJetPt, JetEta);
    else if (abs(JetFlavor)==4) return TagEfficiencyC_2017(ThisJetPt, JetEta);
    else return TagEfficiencyLight_2017(ThisJetPt, JetEta);
  }
  else  if(DataYear == 2018){
    if (abs(JetFlavor)==5) return TagEfficiencyB_2018(ThisJetPt, JetEta);
    else if (abs(JetFlavor)==4) return TagEfficiencyC_2018(ThisJetPt, JetEta);
    else return TagEfficiencyLight_2018(ThisJetPt, JetEta);
  }

  return -999999.;
}



float BTagSFUtil::GetJetSF(int JetFlavor, float JetPt, float JetEta) {
  float Btag_SF(-999.);

  //=== If chosen period dependant SF, then use lumi to weight

  //=== Currently only CVSv2/DeepCSV 2017 have period dependancy
  //=== If period dependancy set true for other year give warning and set false 

  if (period_dependancy && DataYear != 2017) {
    cout << "[BTagSFUtil::GetJetSF] period dependancy set true for year other than 2017.... This is not available currently...." << endl;
  }
  

  if (period_dependancy) {
    
    if(DataYear == 2016){
      float Btag_SF_BF = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2016_" +taggerName + "_272007_278808", true, taggerName);
      float Btag_SF_GH = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2016_" +taggerName + "_278820_284044", true, taggerName);
      
      double lumi_periodB = 5.750490644;
      double lumi_periodC = 2.572903489;
      double lumi_periodD = 4.242291557;
      double lumi_periodE = 4.025228137;
      double lumi_periodF = 3.104509132;
      double lumi_periodG = 7.575824256;
      double lumi_periodH = 8.650628380;
      double total_lumi =  (lumi_periodB+lumi_periodC+lumi_periodD+lumi_periodE+lumi_periodF+lumi_periodG+lumi_periodH);
      
      double WeightBtoF = (lumi_periodB+lumi_periodC+lumi_periodD+lumi_periodE+lumi_periodF)/total_lumi;
      double WeightGtoH = (lumi_periodG+lumi_periodH)/total_lumi;
      Btag_SF = Btag_SF_BF*WeightBtoF + Btag_SF_GH*WeightGtoH;
      return Btag_SF;
    }
    
    else if(DataYear == 2017){

      float Btag_SF_B    = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2017_" +taggerName + "_297046_299329", true, taggerName);
      float Btag_SF_CtoE = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2017_" +taggerName + "_297020_304671", true, taggerName);
      float Btag_SF_EtoF = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2017_" +taggerName + "_304671_306462", true, taggerName);
      
      /// lumi taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmV2017Analysis and brilcal 
      double lumi_periodB = 4.7939;
      double lumi_periodCtoE = 9.6327 + 4.2478 + 7.8380;
      double lumi_periodEtoF = 1.4765 + 13.5401;

      double total_lumi = (lumi_periodB+lumi_periodCtoE + lumi_periodEtoF);
      
      double WeightB    = lumi_periodB   / total_lumi;
      double WeightCtoE = lumi_periodCtoE/ total_lumi;
      double WeightEtoF = lumi_periodEtoF/ total_lumi;
      Btag_SF = Btag_SF_B*WeightB + Btag_SF_CtoE*WeightCtoE +  Btag_SF_EtoF*WeightEtoF;

      return Btag_SF;

    }
    else if(DataYear == 2018){
      //=== https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation102X TBA 
    }
  }
  else{
    
    //=== Access SF using Full data year, no periods

    if(DataYear == 2016){

      float Btag_SF_BH = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2016_" +taggerName + "_272007_284044", false, taggerName);
      return Btag_SF_BH;
    }
    else if(DataYear == 2017){
      float Btag_SF_BF = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2017_" +taggerName + "_297046_306462",false,taggerName);
      return Btag_SF_BF;
    }
    else if(DataYear == 2018){
      float Btag_SF_AD = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2018_" +taggerName + "_315252_325175",false,taggerName);
      return Btag_SF_AD;
    }

  }


  return Btag_SF;
}

float BTagSFUtil::GetJetSFPeriodDependant(int JetFlavor, float JetPt, float JetEta, TString tag_key, bool isPeriodDependant, TString taggerName) {

  /// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco for pt range and systematic correlations

  float ThisJetPt = JetPt;

  //=== SF available for 20 < pt  1000 GeV
  if     (JetPt > 999.99) ThisJetPt = 999.99;
  else if(JetPt < 20.   ) ThisJetPt = 20.;
 
  BTagEntry::JetFlavor jF = BTagEntry::FLAV_B;
  if (abs(JetFlavor)==5){
    jF = BTagEntry::FLAV_B;
  }
  else if (abs(JetFlavor)==4){ 
    jF = BTagEntry::FLAV_C;
  }
  else{
    jF = BTagEntry::FLAV_UDSG;
  }

  return btagReader->eval(jF, JetEta, ThisJetPt);
}

bool BTagSFUtil::IsUncorrectedTagged(float JetDiscriminant, int JetFlavor, float JetPt, float JetEta) {
  /// return false if year is not set                                                                                                                                                                       
  if (DataYear == 0) return false;


  bool isBTagged = JetDiscriminant>taggerCut;

  return isBTagged;

}


bool BTagSFUtil::IsTagged(float JetDiscriminant, int JetFlavor, float JetPt, float JetEta, int seed) {

  //=== set up rand number gen.
  
  TRandom3 rand_(seed);

  /// return false if year is not set
  if (DataYear == 0) return false;


  bool isBTagged = JetDiscriminant>taggerCut;
  
  //=== Data: no correction needed
  if (JetFlavor==-999999) return isBTagged; 

  
  bool newBTag = isBTagged;

  //=== Get SF 
  JetEta= fabs(JetEta);
  float Btag_SF = GetJetSF(JetFlavor, JetPt, JetEta);

  if (Btag_SF == 1) return newBTag; //no correction needed 

  //=== throw random number to apply correction
  float coin = rand_.Uniform(1.);    
  if(Btag_SF > 1){ 
    //=== use this if SF>1

    if( !isBTagged ) {

      float Btag_eff = JetTagEfficiency(JetFlavor, JetPt, fabs(JetEta));
      //=== fraction of jets that need to be upgraded
      float mistagPercent = (1.0 - Btag_SF) / (1.0 - (1./Btag_eff) );
      
      //=== upgrade to tagged
      if( coin < mistagPercent ) {newBTag = true;}
    }

  }else{  
    //=== use this if SF<1
      
    //=== downgrade tagged to untagged
    if( isBTagged && coin > Btag_SF ) {newBTag = false;}

  }

  return newBTag;

}

