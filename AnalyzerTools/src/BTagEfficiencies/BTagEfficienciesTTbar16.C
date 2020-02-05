float BTagSFUtil::TagEfficiencyB_2016(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.80678;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.80320;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.77812;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.74541;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.85588;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.85343;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.82988;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.79430;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87167;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.86937;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.84604;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.80502;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88007;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87766;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85328;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.80890;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88473;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88130;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85651;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.81359;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88855;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88353;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85998;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.81867;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.63956;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.63051;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.57673;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.50273;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.71434;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.70699;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.65857;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.58468;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.73461;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.72759;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.67752;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.59510;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.74400;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.73563;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.68221;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.58884;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.74764;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.73770;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.68077;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.58508;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.74157;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.72718;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.66602;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.56246;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.45544;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.44386;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37934;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.30740;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.54815;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.53640;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.47295;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39764;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.57123;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.55950;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.49487;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.41169;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.57852;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.56631;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.49823;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40514;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.57838;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.56428;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.49376;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39873;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.55894;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.54023;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.46506;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.36560;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.86789;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87401;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86024;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.86243;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87536;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87914;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85990;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.85276;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87470;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87817;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85763;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.84797;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87816;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88160;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86003;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.85144;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88511;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88839;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86665;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.85976;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.90590;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.90822;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.88948;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.88301;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.70490;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.70844;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.66198;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.61563;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.73253;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.73476;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.69235;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.65518;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.73591;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.73773;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.69563;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.66143;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.74201;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.74366;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.69982;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.66707;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.75187;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.75351;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.70835;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.67961;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.78167;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.78159;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.73754;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.70789;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.52766;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.52632;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.45884;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39499;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.58407;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.58196;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.51845;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.46599;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.59696;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.59540;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53296;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48181;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.60519;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.60364;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53957;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48798;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.61480;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.61286;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.54769;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.49982;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.64045;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.63604;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.56792;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.52039;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Loose") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Medium") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Tight") {
  }
  cout << "[BTagSFUtil::TagEfficiencyB_2016] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyC_2016(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.34227;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.35424;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36372;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37827;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.30533;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.32213;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34569;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.36339;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.28556;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.30422;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.32896;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.34602;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.28863;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.30891;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33085;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.34636;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.30123;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.31695;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33600;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.34982;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.35496;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.36466;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.38425;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38824;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11139;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11432;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10754;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09288;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09244;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09857;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10125;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09592;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08458;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09027;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09484;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.08772;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08588;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09288;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09467;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.08619;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09154;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09547;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09686;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.08921;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11273;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11367;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11299;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09525;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02592;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02708;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02428;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01872;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01946;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02091;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02145;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01973;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01770;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01909;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01950;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01798;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01865;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01911;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01943;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01761;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01975;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02052;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02076;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01791;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02431;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02457;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02368;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01933;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.47502;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.50682;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.52737;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.59033;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.36435;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39176;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41452;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.45830;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.30679;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.33313;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36025;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40530;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.28977;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.31661;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34020;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39185;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.29525;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.32007;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33783;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38826;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.37679;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39894;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41258;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.45259;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.18011;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.19506;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.18735;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.18483;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11186;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12549;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13231;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.14151;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09071;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10086;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10591;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11804;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08412;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09694;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09998;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11030;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08818;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09788;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09826;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10944;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.12056;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12977;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13199;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.14021;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.05553;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.06039;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.05345;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04380;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03132;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03514;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03423;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03224;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02559;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02881;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02744;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02656;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02406;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02747;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02551;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02451;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02400;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02726;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02544;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02524;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03231;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03413;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03407;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03312;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Loose") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Medium") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Tight") {
  }
  cout << "[BTagSFUtil::TagEfficiencyC_2016] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyLight_2016(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.16139;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.18120;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.20947;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.23536;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11099;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13124;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.17160;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.19360;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08224;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09995;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13571;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15275;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07348;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09136;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12355;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.14302;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07089;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.08688;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11825;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.14002;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08183;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09766;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13728;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16909;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02636;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02982;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03183;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02824;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01545;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01901;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02412;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02382;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01116;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01367;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01725;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01741;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01006;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01203;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01512;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01531;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00948;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01134;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01438;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01467;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01076;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01231;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01732;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01694;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00211;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00237;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00251;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00215;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00148;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00177;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00215;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00218;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00113;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00135;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00155;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00158;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00107;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00123;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00142;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00141;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00105;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00120;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00135;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00131;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00128;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00141;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00179;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00152;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.36060;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39259;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.44399;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.55418;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.20004;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.22432;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.28419;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.35925;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.12237;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.14243;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.20182;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.27604;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09550;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11140;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.16381;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.24091;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08531;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09960;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.14757;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.22128;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09284;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10984;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.16336;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.24524;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08919;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09830;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10617;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12591;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02441;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03098;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04735;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.07235;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01241;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01587;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02374;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04191;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00997;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01257;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01825;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03357;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00916;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01165;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01684;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03067;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01156;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01457;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02348;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04058;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01230;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01405;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01390;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01419;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00314;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00392;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00462;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00593;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00187;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00227;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00270;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00360;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00148;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00186;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00222;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00317;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00133;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00170;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00206;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00312;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00177;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00217;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00334;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00570;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Loose") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Medium") {
  }
  if(taggerName=="CSVv2" && operatingPoint=="Tight") {
  }
  cout << "[BTagSFUtil::TagEfficiencyLight_2016] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  return 1.;
}
