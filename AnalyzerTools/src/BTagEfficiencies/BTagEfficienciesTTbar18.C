float BTagSFUtil::TagEfficiencyB_2018(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.81731;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.81863;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.79552;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.79256;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87172;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87088;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.84788;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.84135;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.89547;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.89416;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.87079;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.86038;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.90725;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.90566;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.88332;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87228;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.91481;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.91295;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.89129;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87963;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.91697;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.91382;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.89073;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87871;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.90948;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.90434;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.87989;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.86597;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.89901;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.89136;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.87132;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.85831;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.89751;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.89063;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.87137;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.86194;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.64435;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.64309;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.59196;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.55903;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.73412;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.73033;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.68408;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.65461;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.77390;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.76902;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.72054;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.68557;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.79242;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.78562;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.73324;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.68873;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.80141;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.79080;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.73104;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.67705;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.79652;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.78059;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.71171;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.64617;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.76451;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.74039;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.66093;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.58451;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.71001;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.67681;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.59781;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.53614;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.62651;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.59850;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53121;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.49160;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.44707;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.43956;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37763;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.34294;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.56567;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.55440;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.48884;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.45441;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.61752;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.60486;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53563;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.49554;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.63506;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.62114;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.54706;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.49939;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.63774;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.62012;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53880;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48036;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.62106;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.59908;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.50910;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.43463;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.56297;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.53198;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.43462;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.35127;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.45702;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.41957;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33091;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.27036;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.31056;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.28655;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.22677;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.21549;
      }
    }
  }  
  if(taggerName=="DeepJet"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.90350;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.89771;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.88185;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.88890;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.92639;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.91967;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.90268;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.90322;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.93698;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93072;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.91409;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.90974;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94226;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93624;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.91988;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.91407;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94530;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93966;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92307;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.91687;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94768;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.94219;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92600;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92099;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94867;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.94295;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92720;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92193;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94921;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.94248;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92949;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92215;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94972;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.94485;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.93588;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.93284;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.75455;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.73487;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.67707;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.65673;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.81519;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.79801;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.74967;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.73139;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.84287;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.82739;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.78230;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.76125;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.85616;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.84210;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.79798;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.77521;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.86380;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.85060;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.80624;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.78379;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.86701;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.85440;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.81078;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.79006;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.86344;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.84938;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.80072;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.78314;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.84989;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.83134;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.77771;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.75109;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.82197;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.79957;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.73426;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.74347;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.51269;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.48877;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41524;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39275;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.62874;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.60240;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.52760;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.50520;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.68400;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.65949;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.58546;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.55872;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.70940;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.68748;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.61437;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.58469;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72322;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.70249;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.62912;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.60009;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72747;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.70898;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.63592;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.60692;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.71412;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.69143;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.61088;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.58413;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.66871;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.63777;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.54603;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.51718;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.57947;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.54610;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.44507;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.46922;
      }
    }
  }  
  if(taggerName=="CSVv2"){
    if(operatingPoint=="Loose"){
    }
    if(operatingPoint=="Medium"){
    }
    if(operatingPoint=="Tight"){
    }
  }  
  cout << "[BTagSFUtil::TagEfficiencyB_2018] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  cout << "[BTagSFUtil::TagEfficiencyB_2018] Or, wrong pt and eta range : pt = " << JetPt << ", eta = " << JetEta << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyC_2018(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.34276;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.36197;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37065;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40591;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.32172;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.34342;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.35767;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39445;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.30528;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.32682;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33967;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37890;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.31244;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.33344;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34370;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38576;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.34223;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.35831;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36743;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40426;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.38091;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39125;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.39605;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.42428;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.40770;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.41477;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.40268;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.43533;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.41347;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.41820;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.40344;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.43277;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.41301;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.40751;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41459;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.43061;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11888;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12403;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11306;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10987;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10403;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11392;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11633;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12072;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09783;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10616;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10843;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11525;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10417;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11128;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10987;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11419;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11986;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12357;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11748;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12018;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.13715;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13806;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12825;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12359;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.14108;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13687;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11886;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11394;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.12299;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11461;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09687;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09035;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09193;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.06678;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.05765;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04410;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03171;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03173;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02706;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02408;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02276;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02482;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02506;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02531;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02075;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02233;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02248;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02410;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02279;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02418;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02349;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02380;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02598;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02728;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02537;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02545;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03057;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03064;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02700;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02455;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02781;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02897;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02251;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02134;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02074;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01914;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01540;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01199;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01137;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00747;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00214;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00259;
      }
    }
  }  
  if(taggerName=="DeepJet"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.50905;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.50457;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.50338;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.55451;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.45301;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.44987;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.44693;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48213;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.39407;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39312;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.39222;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.41866;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.37494;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.37452;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36822;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38745;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.38372;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.38139;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37177;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38296;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.41544;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.40692;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.39896;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40606;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.46343;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.44958;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.43480;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.45227;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.51821;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.50449;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.49437;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.51128;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.55453;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.56367;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.57260;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.60311;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.19986;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.18723;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15892;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15608;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.16601;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.16135;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15017;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15309;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.14254;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13721;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12882;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12935;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.13957;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13531;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12422;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12092;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.14585;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.14034;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12916;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12310;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.16261;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.15671;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.14600;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.13572;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.18726;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.17851;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.16041;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15322;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.21449;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.20544;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.17757;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16700;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.24300;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.22148;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.20036;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.19196;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04096;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03830;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03120;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02930;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03130;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03001;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02643;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02671;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02804;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02631;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02359;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02353;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02833;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02771;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02360;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02349;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03063;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02959;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02704;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02636;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03483;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03399;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03139;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02844;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04096;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03971;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03357;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03308;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04885;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.04546;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03941;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03911;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.05634;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.04915;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03665;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02983;
      }
    }
  }  
  if(taggerName=="CSVv2"){
    if(operatingPoint=="Loose"){
    }
    if(operatingPoint=="Medium"){
    }
    if(operatingPoint=="Tight"){
    }
  }  
  cout << "[BTagSFUtil::TagEfficiencyC_2018] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  cout << "[BTagSFUtil::TagEfficiencyC_2018] Or, wrong pt and eta range : pt = " << JetPt << ", eta = " << JetEta << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyLight_2018(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.12958;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.15092;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.18250;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.23031;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11057;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12591;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.14901;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.18949;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08838;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10256;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12403;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16018;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07925;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09265;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11466;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15089;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07990;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09173;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11447;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15344;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08443;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09491;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12083;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16863;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09421;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10456;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13490;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.19391;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11632;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12523;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.16904;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.24016;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.15912;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.16993;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.22930;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.30238;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02135;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02350;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02126;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02121;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01748;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02058;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02254;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02365;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01218;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01481;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01726;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01932;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01091;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01305;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01529;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01731;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01087;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01249;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01452;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01750;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01116;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01183;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01411;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01834;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01186;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01218;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01462;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01966;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01379;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01320;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01753;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02185;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01285;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01199;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01650;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01736;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00191;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00209;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00193;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00177;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00148;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00172;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00189;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00198;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00122;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00143;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00156;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00167;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00117;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00136;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00141;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00145;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00121;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00133;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00134;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00151;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00138;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00142;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00143;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00161;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00157;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00152;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00138;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00168;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00177;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00139;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00142;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00161;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00110;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00090;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00087;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00061;
      }
    }
  }  
  if(taggerName=="DeepJet"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.38928;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39652;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.42683;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.50429;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.26790;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.28002;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.29937;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.34601;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.14340;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.15187;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.17547;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.21146;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10197;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10708;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12427;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.14883;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08479;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.08801;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10486;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12405;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07670;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.07930;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10050;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12512;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08170;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.08460;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11724;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15674;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10945;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11710;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.17986;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.24183;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.19320;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.22218;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33197;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39054;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.06301;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.06032;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04914;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.05329;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03676;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03787;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03857;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04690;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01635;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01727;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01827;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02080;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01089;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01148;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01244;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01400;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00864;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00913;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01027;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01263;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00799;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00837;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01054;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01414;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00900;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00926;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01343;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02026;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01240;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01325;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02255;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03292;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02592;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02893;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.05033;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.05731;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00453;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00415;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00290;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00284;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00273;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00273;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00240;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00272;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00138;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00142;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00138;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00164;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00100;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00105;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00105;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00122;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00082;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00085;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00090;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00119;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00075;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00085;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00098;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00151;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00089;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00096;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00131;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00224;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00128;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00152;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00245;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00386;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00270;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00307;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00540;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00675;
      }
    }
  }  
  if(taggerName=="CSVv2"){
    if(operatingPoint=="Loose"){
    }
    if(operatingPoint=="Medium"){
    }
    if(operatingPoint=="Tight"){
    }
  }  
  cout << "[BTagSFUtil::TagEfficiencyLight_2018] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  cout << "[BTagSFUtil::TagEfficiencyLight_2018] Or, wrong pt and eta range : pt = " << JetPt << ", eta = " << JetEta << endl;
  return 1.;
}
