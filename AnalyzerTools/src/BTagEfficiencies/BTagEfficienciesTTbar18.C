float BTagSFUtil::TagEfficiencyB_2018(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.84159;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.84154;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.81827;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.81344;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88638;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88542;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86186;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.85326;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.90168;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.89998;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.87697;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.86604;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.90904;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.90769;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.88588;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87486;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.91377;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.91218;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.89061;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87892;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.91496;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.91179;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.88941;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87793;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.68415;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.68138;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.63210;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.60007;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.75891;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.75455;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.70734;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.67640;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.78376;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.77821;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.72860;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.68945;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.79518;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.78793;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.73437;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.68746;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.80070;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.79107;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.73281;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.68065;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.79005;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.77429;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.70795;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.64817;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.49918;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.48936;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.42496;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38974;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.59892;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.58714;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.51954;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48330;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.62800;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.61480;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.54420;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.50061;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.63699;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.62263;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.54718;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.49726;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.63848;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.62191;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.54157;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48553;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.61070;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.58900;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.50366;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.43855;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.91367;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.90721;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.89073;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.89494;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.93285;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.92641;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.90925;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.90708;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.93978;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93362;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.91718;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.91201;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94302;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93707;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92102;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.91483;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94478;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93923;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92261;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.91613;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94733;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.94165;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92544;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.91991;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.78157;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.76263;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.70856;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.68852;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.83209;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.81589;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.76934;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.75056;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.84995;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.83515;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.79108;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.76886;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.85816;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.84447;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.80039;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.77685;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.86286;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.84978;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.80484;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.78232;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.86503;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.85179;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.80756;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.78711;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.56341;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.53758;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.46234;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.43916;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.66292;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.63749;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.56285;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.53892;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.69771;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.67437;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.60143;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.57278;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.71321;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.69174;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.61845;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.58818;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72144;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.70033;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.62701;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.59729;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72214;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.70237;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.62854;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.60216;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Loose") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Medium") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Tight") {
  }
  cout << "[BTagSFUtil::TagEfficiencyB_2018] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyC_2018(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.33764;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.35779;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36855;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40395;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.31002;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.33131;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34447;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38293;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.30500;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.32670;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33938;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37950;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.31646;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.33739;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34679;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39025;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.33402;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.35070;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36032;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40310;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.38449;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39426;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.39377;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.42214;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11487;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12188;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11499;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11373;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09849;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10711;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11054;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11734;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09945;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10718;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10871;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11455;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10634;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11398;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11094;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11539;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11531;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12058;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11467;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11945;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.13268;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13119;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12028;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11777;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02906;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02978;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02666;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02452;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02080;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02249;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02333;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02475;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02126;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02318;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02279;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02376;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02327;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02463;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02359;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02400;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02473;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02605;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02425;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02473;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02772;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02817;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02450;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02332;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.49519;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.49111;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.48941;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.53592;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.41784;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.41571;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41492;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.44496;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.38013;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.37973;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37832;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40119;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.37459;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.37419;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36505;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38496;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.37905;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.37600;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36643;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38119;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.43439;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.42580;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41370;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.41955;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.19109;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.18116;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15819;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15718;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.14956;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.14468;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13606;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.13820;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.13983;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13486;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12640;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12484;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.13978;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13625;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12334;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12044;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.14315;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13804;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12689;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12175;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.17248;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.16486;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.14951;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.13924;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03806;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03592;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02999;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02871;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02880;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02737;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02433;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02464;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02823;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02653;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02332;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02337;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02806;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02800;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02397;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02389;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02956;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02848;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02579;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02507;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03758;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03612;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03205;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03020;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Loose") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Medium") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Tight") {
  }
  cout << "[BTagSFUtil::TagEfficiencyC_2018] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyLight_2018(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.12497;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.14436;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.17397;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.22028;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09726;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11174;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13354;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.17087;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08271;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09675;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11834;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15423;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07845;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09139;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11364;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15007;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07925;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09121;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11395;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15128;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08789;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09876;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12576;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.17408;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02064;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02314;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02211;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02227;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01391;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01689;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01952;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02130;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01142;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01367;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01605;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01807;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01073;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01290;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01505;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01719;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01078;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01257;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01463;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01726;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01141;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01215;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01451;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01862;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00180;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00198;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00194;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00185;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00129;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00155;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00170;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00183;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00117;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00136;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00147;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00155;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00118;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00137;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00139;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00140;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00118;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00132;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00132;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00145;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00140;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00140;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00140;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00162;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.35865;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.36784;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.39544;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.46439;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.19044;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.20187;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.22750;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.27027;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11868;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12513;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.14533;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.17529;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09650;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10127;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11742;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.14041;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08690;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09030;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10703;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12573;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08258;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.08612;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11128;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.13762;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.05616;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.05491;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04797;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.05389;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02277;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02390;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02501;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02985;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01309;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01389;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01485;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01652;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01016;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01068;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01170;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01337;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00884;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00931;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01053;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01241;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00877;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00925;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01202;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01616;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00407;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00381;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00284;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00289;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00178;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00185;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00173;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00207;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00116;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00121;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00120;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00140;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00093;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00099;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00099;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00117;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00084;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00087;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00090;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00117;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00085;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00093;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00116;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00171;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Loose") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Medium") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Tight") {
  }
  cout << "[BTagSFUtil::TagEfficiencyLight_2018] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  return 1.;
}
