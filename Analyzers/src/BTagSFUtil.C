#include "BTagSFUtil.h"
#include "BTag/BTagCalibrationStandalone.C"
#include "BTag/BTagEfficienciesTTbar16.C" // Change this to your sample efficiency  


void BTagSFUtil::SetMCSample(TString s){
  MCSample = s;
}
void BTagSFUtil::SetDataYear(int i){
  DataYear = i;
}

void BTagSFUtil::SetPeriodDependancy(bool b){
  period_dependancy = b;
}

BTagSFUtil::BTagSFUtil(string MeasurementType, string BTagAlgorithm,  TString OperatingPoint, int SystematicIndex, int Seed) {

  rand_ = new TRandom3(Seed);

  TString datapath = getenv("DATA_DIR");

  TString IDpath = datapath+"/"+TString::Itoa(DataYear,10)+"/BTag/";


  string SystematicFlagBC = "central";
  string SystematicFlagL  = "central";
  if (abs(SystematicIndex)<10) {
    if (SystematicIndex==-1 || SystematicIndex==-2) SystematicFlagBC = "down";
    if (SystematicIndex==+1 || SystematicIndex==+2) SystematicFlagBC = "up";
    if (SystematicIndex==-3) SystematicFlagL = "down";
    if (SystematicIndex==+3) SystematicFlagL = "up";
  }

  /// Initialise TaggerCut, set by taggermap.txt
  TaggerCut = -1;
  ifstream in_tagger(datapath+"/taggermap.txt");
  string btaggerline;
  while(getline(in_tagger,btaggerline)){
    std::istringstream is_tag( btaggerline );
    TString tstring_taggerline = btaggerline;
    if(tstring_taggerline.Contains("#")) continue;
    TString a,b,c;
    float cutvalue; 
    
    is_tag >> a; // YEAR
    is_tag >> b; // TAGGER
    is_tag >> c; // WP
    is_tag >> cutvalue;  // cut value
    
    if(a == DataYear && b == BTagAlgorithm && c == OperatingPoint ) {TaggerCut = cutvalue; break;}
  }

  /// Set OperatingPoint passed by var OperatingPoint
  BTagEntry::OperatingPoint op = BTagEntry::OP_LOOSE;
  if (OperatingPoint=="Loose")        {op = BTagEntry::OP_LOOSE;        TaggerOP += "L";}
  if (OperatingPoint=="Medium")       {op = BTagEntry::OP_MEDIUM;        TaggerOP += "M";}
  if (OperatingPoint=="Tight")        {op = BTagEntry::OP_TIGHT;        TaggerOP += "T";}
  if (OperatingPoint=="Reshaping")    {op = BTagEntry::OP_RESHAPING;        TaggerOP += "R";}
    

  /// open histmap file to tell code which file to use depending on year/tagger
  ifstream in(datapath+"/histmap.txt");
  string btagline;
  while(getline(in,btagline)){
    std::istringstream is( btagline );
    
    TString tstring_btagline = btagline;
    if(tstring_btagline.Contains("#")) continue;
    
    TString a,b,c,d,e;
    string f;
    is >> a; // YEAR
    is >> b; // TAGGER
    is >> c; // Period_dep
    is >> d; // Run_start
    is >> e; // Run_end
    is >> f; // csv file                                                                                                                                                                           

    BTagCalibration calib(BTagAlgorithm, f);
    if (period_dependancy&& c=="PeriodDep"){   

      ReaderMap[a+"_"+b+"_"+d+"_"+e+"_bc"] = new BTagCalibrationReader(&calib, op, MeasurementType, SystematicFlagBC);; 
      ReaderMap[a+"_"+b+"_"+d+"_"+e+"_l"] = new BTagCalibrationReader(&calib, op, MeasurementType, SystematicFlagL);; 
    }
    else if(!period_dependancy && c!="PeriodDep"){
      ReaderMap[a+"_"+b+"_"+d+"_"+e+"_bc"] = new BTagCalibrationReader(&calib, op, MeasurementType, SystematicFlagBC);;
      ReaderMap[a+"_"+b+"_"+d+"_"+e+"_l"] = new BTagCalibrationReader(&calib, op, MeasurementType, SystematicFlagL);;
    }
  }
  
  
  TaggerName = BTagAlgorithm;
  TaggerOP = TaggerName;

  if (TaggerCut==-1) 
    cout << " " << TaggerName << " not supported for " << OperatingPoint << " WP" << endl;

  FastSimSystematic = 0;
  if (abs(SystematicIndex)>10) FastSimSystematic = SystematicIndex%10;

  if (TaggerCut==-1) 
    cout << "BTagSFUtil: " << BTagAlgorithm << " not a supported b-tagging algorithm" << endl;
  
}

BTagSFUtil::~BTagSFUtil() {

  delete rand_;

}

float BTagSFUtil::JetTagEfficiency(int JetFlavor, float JetPt, float JetEta) {

  if (abs(JetFlavor)==5) return TagEfficiencyB(JetPt, JetEta);
  else if (abs(JetFlavor)==4) return TagEfficiencyC(JetPt, JetEta);
  else return TagEfficiencyLight(JetPt, JetEta);

}



float BTagSFUtil::GetJetSF(int JetFlavor, float JetPt, float JetEta) {
  float Btag_SF(-999.);

  if (period_dependancy) {
    
    if(DataYear == 2016){
      float Btag_SF_BF = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2016_" +TaggerName + "_272007_278808");
      float Btag_SF_GH = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2016_" +TaggerName + "_278820_284044");
      
      double lumi_periodB = 5.929001722;
      double lumi_periodC = 2.645968083;
      double lumi_periodD = 4.35344881;
      double lumi_periodE = 4.049732039;
      double lumi_periodF = 3.157020934;
      double lumi_periodG = 7.549615806;
      double lumi_periodH = 8.545039549 + 0.216782873;
      double total_lumi = (lumi_periodB+lumi_periodC+lumi_periodD+lumi_periodE+lumi_periodF+lumi_periodG+lumi_periodH);
      
      double WeightBtoF = (lumi_periodB+lumi_periodC+lumi_periodD+lumi_periodE+lumi_periodF)/total_lumi;
      double WeightGtoH = (lumi_periodG+lumi_periodH)/total_lumi;
      Btag_SF = Btag_SF_BF*WeightBtoF + Btag_SF_GH*WeightGtoH;
      return Btag_SF;
    }

    if(DataYear == 2017){

      float Btag_SF_B    = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2017_" +TaggerName + "_297046_299329");
      float Btag_SF_CtoE = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2017_" +TaggerName + "_297020_304671");
      float Btag_SF_EtoF = GetJetSFPeriodDependant(JetFlavor, JetPt, JetEta, "2017_" +TaggerName + "_304671_306462");
      
      /// lumi taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmV2017Analysis and brilcal 
      double lumi_periodB = 4.823;
      double lumi_periodCtoE = 21.719;
      double lumi_periodEtoF = 15.017;

      double total_lumi = (lumi_periodB+lumi_periodCtoE + lumi_periodEtoF);
      
      double WeightB = (lumi_periodB)/total_lumi;
      double WeightCtoE = lumi_periodCtoE/total_lumi;
      double WeightEtoF = lumi_periodEtoF/ total_lumi;
      Btag_SF = Btag_SF_B*WeightB + Btag_SF_CtoE*WeightCtoE*Btag_SF_EtoF*WeightEtoF;

      return Btag_SF;

    }
  }


  return Btag_SF;
}

float BTagSFUtil::GetJetSFPeriodDependant(int JetFlavor, float JetPt, float JetEta, TString tag_key) {

  /// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco for pt range and systematic correlations
  float Btag_SF;

  float ThisJetPt = JetPt;
  if(TaggerName.Contains("cMVAv2")){
    if(abs(JetFlavor)==4 || abs(JetFlavor)==5){
      if     (JetPt > 599.99)             ThisJetPt = 599.99;
      else if(JetPt < 30. && JetPt > 20.) ThisJetPt = 30.01;
      else                                return 1.;
    }
    else{
      if     (JetPt > 999.99) ThisJetPt = 999.99;
      else if(JetPt < 20.)    return 1.; 
    }
  }
  else if(TaggerName.Contains("CSVv2")){
    if     (JetPt > 999.99) ThisJetPt = 999.99;
    else if(JetPt < 20.   ) return 1.; 
  }
  else return 1.; //For safety.

  map <TString, BTagCalibrationReader*>::iterator reader_bf_it ;
  if (abs(JetFlavor)==5) {
    
    reader_bf_it =    ReaderMap.find(tag_key+"_bc");
    Btag_SF = reader_bf_it->second->eval(BTagEntry::FLAV_B, JetEta, ThisJetPt);
  }
  else if (abs(JetFlavor)==4){ 
    
    reader_bf_it = ReaderMap.find(tag_key+"_bc");
    Btag_SF = reader_bf_it->second->eval(BTagEntry::FLAV_C, JetEta, ThisJetPt);
  }
  else {

    reader_bf_it = ReaderMap.find(tag_key+"_l");
    Btag_SF = reader_bf_it->second->eval(BTagEntry::FLAV_UDSG, JetEta, ThisJetPt);

  }
    
  return Btag_SF;

}

bool BTagSFUtil::IsTagged(float JetDiscriminant, int JetFlavor, float JetPt, float JetEta) {
  
  bool isBTagged = JetDiscriminant>TaggerCut;

  if (JetFlavor==-999999) return isBTagged; // Data: no correction needed

  bool newBTag = isBTagged;

  float Btag_SF = GetJetSF(JetFlavor, JetPt, JetEta);
  
  //cout << "Btag_SF = " << Btag_SF << endl;
  if (Btag_SF == 1) return newBTag; //no correction needed 

  //throw die
  float coin = rand_->Uniform(1.);    
 
  if(Btag_SF > 1){  // use this if SF>1

    if( !isBTagged ) {

      float Btag_eff = JetTagEfficiency(JetFlavor, JetPt, fabs(JetEta));

      //fraction of jets that need to be upgraded
      float mistagPercent = (1.0 - Btag_SF) / (1.0 - (1./Btag_eff) );
      
      //upgrade to tagged
      if( coin < mistagPercent ) {newBTag = true;}
    }

  }else{  // use this if SF<1
      
    //downgrade tagged to untagged
    if( isBTagged && coin > Btag_SF ) {newBTag = false;}

  }

  return newBTag;

}

