float BTagSFUtil::TagEfficiencyB_2017(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.84366;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.85016;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.82409;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.80497;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88838;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.89379;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.87035;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.84781;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.90268;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.90705;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.88511;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.86281;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.90869;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.91339;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.89391;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87237;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.91242;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.91639;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.89796;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87712;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.91174;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.91336;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.89593;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87537;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.66809;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.67499;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.62431;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.58066;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.74640;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.75139;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.70453;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.66210;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.77173;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.77504;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.72724;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.67878;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.78250;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.78440;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.73397;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.67849;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.78670;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.78599;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.73197;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.67100;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.77353;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.76540;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.70406;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.63515;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.48662;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.48405;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41418;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37179;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.58765;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.58440;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.51423;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.46951;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.61631;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.61186;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.54137;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.49049;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.62352;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.61821;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.54560;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48791;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.62296;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.61460;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53862;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.47629;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.59132;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.57624;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.49524;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.42693;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.92259;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.92785;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92058;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92987;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.92706;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93156;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92283;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92898;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.92513;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.92902;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92017;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92770;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.92620;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.92999;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92050;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92978;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.93032;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93345;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92311;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.93446;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94366;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.94570;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.93530;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.94417;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.78649;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.79377;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.76711;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.77205;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.79995;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.80475;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.77924;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.78943;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.80053;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.80314;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.77527;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.79175;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.80448;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.80664;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.77609;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.79611;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.81326;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.81422;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.78192;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.80378;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.83985;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.83893;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.80428;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.82158;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.59868;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.60074;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.54776;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.54614;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.64898;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.64916;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.59630;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.60329;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.66134;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.65993;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.60561;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.61809;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.66834;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.66712;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.60958;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.62536;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.67797;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.67463;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.61535;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.63361;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.70518;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.69858;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.63329;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.64879;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.83171;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.83576;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.79668;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.77934;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87148;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87422;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.84933;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.83858;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88388;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88619;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86424;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.85102;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88775;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.89052;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86815;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.85160;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88612;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88669;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86097;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.84144;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87895;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87670;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85112;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.82657;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.63876;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.61792;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.57643;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.53836;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.70910;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.69380;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.65622;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.62465;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72449;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.71302;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.66783;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.63435;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72711;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.71749;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.67048;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.63058;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72216;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.71479;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.66111;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.61767;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.69840;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.68925;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.62157;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.57769;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.41772;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.37257;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.35870;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.32352;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.50616;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.47165;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.43395;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40770;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.50623;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.48115;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.43438;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.41065;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.50732;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.48478;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.43061;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39712;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.51038;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.49692;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.42013;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38191;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.47171;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.45932;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36676;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.33157;
    }
  }
  cout << "[BTagSFUtil::TagEfficiencyB_2017] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyC_2017(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.33049;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.36373;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37278;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37025;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.30328;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.34303;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37117;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37411;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.29777;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.33721;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36751;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37307;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.30628;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.34651;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37795;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38262;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.32504;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.36096;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.39025;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39794;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.36829;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39636;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41975;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.41965;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09688;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10977;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10773;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09776;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08358;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09934;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11077;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10526;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08527;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10079;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10931;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10427;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09155;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10784;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11414;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10876;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10124;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11465;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12003;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11338;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11469;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12296;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12393;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11422;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02579;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02785;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02502;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02156;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01802;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02210;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02340;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02247;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01919;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02248;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02382;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02253;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02046;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02399;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02546;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02398;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02272;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02553;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02567;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02512;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02362;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02619;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02506;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02308;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.55423;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.58702;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.62417;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.67548;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.42785;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.46287;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.50996;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.57006;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.36080;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39410;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.44137;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.51207;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.34206;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.37519;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41882;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48504;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.34756;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.37554;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41589;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48973;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.43415;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.46095;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.48531;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.53995;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.21927;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.23984;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.25063;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.28088;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.13240;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.15099;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.17806;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.21403;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10798;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12088;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13953;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.17252;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10082;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11454;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12816;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15874;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10211;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11350;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12512;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16017;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.14051;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.15252;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15973;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.18991;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.06331;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.06920;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.06850;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.07494;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03436;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.04021;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04478;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.05404;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02852;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03286;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03518;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04294;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02660;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03101;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03240;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03851;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02689;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02993;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03158;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03813;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03541;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03805;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03810;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04716;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.31723;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.34742;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33357;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.33893;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.27863;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.31327;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34142;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37417;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.26731;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.30164;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33196;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.36891;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.27100;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.30781;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34316;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37883;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.27830;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.31204;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34175;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37916;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.32315;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.35996;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37733;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.41261;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10732;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10329;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10083;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09397;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08898;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09152;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10576;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11064;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08309;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.08794;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09660;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10557;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08384;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09219;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09887;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10872;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08672;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09422;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10256;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11389;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10032;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11205;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11257;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12662;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02926;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02360;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02578;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02272;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02051;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01918;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02238;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02469;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01653;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01714;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01882;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02149;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01731;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01848;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01924;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02178;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01930;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02165;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02031;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02254;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02366;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02617;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02036;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02523;
    }
  }
  cout << "[BTagSFUtil::TagEfficiencyC_2017] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyLight_2017(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11391;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13949;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.16831;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.18273;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09194;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11569;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15109;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16804;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07613;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09860;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13497;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15401;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.06932;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09236;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12948;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.14946;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.06911;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09073;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12805;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.14927;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07438;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09421;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13860;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16752;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01447;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01891;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02060;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01850;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01039;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01424;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01932;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02024;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00848;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01169;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01616;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01703;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00800;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01112;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01509;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01591;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00811;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01071;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01461;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01586;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00834;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01022;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01441;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01652;
    }
  }
  if(taggerName=="DeepCSV" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00158;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00193;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00200;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00173;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00121;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00160;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00200;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00188;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00107;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00140;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00174;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00161;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00101;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00130;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00156;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00147;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00098;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00122;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00144;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00145;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00104;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00118;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00136;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00139;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.41481;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.44628;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.52526;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.61138;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.22953;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.25543;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33606;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.44629;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.13628;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.15821;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.23324;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.34360;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10520;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12282;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.18760;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.28934;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09320;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10881;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.16716;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.26293;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09610;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11546;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.17608;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.26843;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09757;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10951;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12645;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.17940;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02966;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03770;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.06334;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11257;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01441;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01872;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03191;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.06547;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01105;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01427;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02318;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04718;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00965;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01260;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02015;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04034;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01082;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01394;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02324;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04195;
    }
  }
  if(taggerName=="DeepJet" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01441;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01681;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01768;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02657;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00387;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00491;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00712;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01365;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00218;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00271;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00385;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00705;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00161;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00204;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00283;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00506;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00133;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00170;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00238;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00437;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00144;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00177;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00271;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00502;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Loose") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10332;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12538;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13746;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15632;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07312;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.08918;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11685;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15874;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.05999;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.07360;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11864;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15895;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.05317;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.06711;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12539;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16556;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04608;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.05805;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10537;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15632;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04810;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.06451;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12250;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.17714;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Medium") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01066;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01151;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01541;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01678;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00843;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00921;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01490;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01979;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00746;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00806;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01242;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01637;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00690;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00747;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01157;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01519;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00618;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00663;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01099;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01471;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00617;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00750;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01132;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01840;
    }
  }
  if(taggerName=="CSVv2" && operatingPoint=="Tight") {
    if (JetPt > 20.0 && JetPt <= 40.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00131;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00123;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00151;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00230;
    }
    if (JetPt > 40.0 && JetPt <= 60.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00089;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00086;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00123;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00245;
    }
    if (JetPt > 60.0 && JetPt <= 80.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00078;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00083;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00105;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00150;
    }
    if (JetPt > 80.0 && JetPt <= 100.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00080;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00090;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00101;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00128;
    }
    if (JetPt > 100.0 && JetPt <= 120.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00090;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00100;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00103;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00131;
    }
    if (JetPt > 120.0 && JetPt <= 3000.0){
      if (fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00106;
      if (fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00123;
      if (fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00116;
      if (fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00195;
    }
  }
  cout << "[BTagSFUtil::TagEfficiencyLight_2017] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  return 1.;
}
