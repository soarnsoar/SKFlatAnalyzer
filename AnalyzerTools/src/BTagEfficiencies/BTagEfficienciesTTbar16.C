float BTagSFUtil::TagEfficiencyB_2016(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.77998;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.77645;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.75108;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.71958;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.84008;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.83726;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.81330;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.78016;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.86523;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.86291;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.83947;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.80113;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87787;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87549;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85150;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.80776;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88578;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88195;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85682;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.81460;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88975;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88465;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86137;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.81942;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88722;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88174;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86057;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.82150;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88975;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88127;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86848;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.83471;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.89047;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88687;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.88510;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87278;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.59791;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.58880;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53363;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.45864;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.69096;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.68311;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.63313;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.56166;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72689;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.71977;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.67063;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.59332;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.74154;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.73373;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.68144;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.59110;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.74785;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.73726;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.67877;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.58204;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.74518;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.73090;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.66911;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.56059;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72638;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.70570;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.63877;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.52330;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.70564;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.67782;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.61807;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.50820;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.66844;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.64725;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.61437;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.55438;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.40510;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39471;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33214;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.26151;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.51866;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.50696;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.44270;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37062;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.56306;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.55132;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.48720;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40843;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.57683;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.56484;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.49803;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40789;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.57718;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.56229;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.49059;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39442;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.56440;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.54614;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.46832;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.36255;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.52738;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.50036;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41589;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.30931;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.48176;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.44569;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37375;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.27897;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.41975;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39068;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.35570;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.31641;
      }
    }
  }  
  if(taggerName=="DeepJet"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.86215;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.86993;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85923;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.86572;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87413;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87844;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86092;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.85709;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87485;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87852;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85843;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.84957;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87692;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88029;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85902;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.84967;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88819;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.89122;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86985;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.86365;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.90691;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.90968;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.89190;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.88688;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.92522;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.92775;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.91384;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.90892;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.93497;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93550;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92889;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92359;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94106;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.94639;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.94040;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.94792;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.68658;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.69108;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.64258;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.59257;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72567;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.72846;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.68519;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.64505;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.73482;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.73671;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.69433;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.65947;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.73984;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.74156;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.69843;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.66487;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.75646;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.75765;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.71290;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.68479;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.78456;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.78546;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.74269;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.71440;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.80980;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.80887;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.76591;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.73380;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.80749;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.80221;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.75790;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.71640;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.78193;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.77537;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.72847;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.71918;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.49579;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.49548;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.42721;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.35862;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.56683;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.56497;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.49994;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.44449;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.59244;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.59044;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.52744;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.47640;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.60261;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.60120;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53794;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48622;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.61920;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.61665;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.55101;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.50407;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.64538;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.64220;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.57475;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.52650;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.66298;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.65618;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.58512;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.53627;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.63805;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.62250;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.54394;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.47933;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.57643;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.55886;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.46721;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.42914;
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
  cout << "[BTagSFUtil::TagEfficiencyB_2016] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  cout << "[BTagSFUtil::TagEfficiencyB_2016] Or, wrong pt and eta range : pt = " << JetPt << ", eta = " << JetEta << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyC_2016(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.34547;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.35605;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36165;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37606;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.32676;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.34214;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36182;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37769;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.29172;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.30982;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33358;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.35056;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.28676;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.30591;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.32903;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.34596;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.30644;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.32155;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33955;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.35344;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.33972;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.35260;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37070;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38272;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.37799;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.38355;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.40966;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.41026;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.42511;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.42773;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.46006;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.45475;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.47626;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.49147;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.55136;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.52528;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11427;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11559;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10544;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.08883;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10177;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10750;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10896;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09944;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08702;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09372;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09627;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09075;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08526;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09118;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09378;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.08721;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09388;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09711;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09842;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.08966;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10704;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11134;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10983;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09701;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.12151;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12129;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12112;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09645;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.14017;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13333;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13290;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09794;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.15302;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.14213;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15722;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11891;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02748;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02811;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02413;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01783;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02199;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02380;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02372;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02024;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01812;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01961;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01993;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01862;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01824;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01897;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01934;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01801;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02018;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02088;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02092;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01831;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02270;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02394;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02331;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02030;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02692;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02647;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02623;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01869;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03052;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03002;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02602;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01748;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03288;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02628;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02471;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01592;
      }
    }
  }  
  if(taggerName=="DeepJet"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.49820;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.53148;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.55322;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.62199;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.41267;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.44081;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.45948;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.50768;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.32929;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.35723;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.38286;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.42647;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.29339;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.31889;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34406;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39350;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.30038;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.32490;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34128;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39168;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.34541;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.36915;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.38489;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.43853;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.42393;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.44777;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.46177;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.50386;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.50252;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.52019;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.55051;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.57493;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.56397;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.60416;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.66691;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.69850;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.19609;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.20972;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.19611;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.19084;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.13853;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.15461;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15925;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16354;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09810;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10971;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11522;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12700;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08592;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09715;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10071;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11209;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08984;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09883;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09997;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11259;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10589;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11659;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12139;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.13328;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.14109;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.15196;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15675;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16724;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.17382;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.18274;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.18425;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.18358;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.20666;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.21725;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.21899;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.20506;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.06275;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.06689;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.05741;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04545;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03900;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.04437;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04228;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03794;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02741;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03081;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02970;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02846;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02455;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02744;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02608;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02552;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02456;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02718;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02592;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02584;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02849;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03127;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03161;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03164;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03706;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03975;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04100;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04095;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04704;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.04601;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04604;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04251;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.05223;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.05063;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04869;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04494;
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
  cout << "[BTagSFUtil::TagEfficiencyC_2016] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  cout << "[BTagSFUtil::TagEfficiencyC_2016] Or, wrong pt and eta range : pt = " << JetPt << ", eta = " << JetEta << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyLight_2016(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.16503;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.18289;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.20612;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.23285;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.14089;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.16320;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.20283;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.22715;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09229;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11049;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.14792;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16650;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07551;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09332;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12657;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.14498;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07083;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.08657;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11805;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.14196;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07571;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09059;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12779;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16265;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09141;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10772;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15560;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.19612;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.12975;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.14896;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.21524;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.25071;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.20354;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.22622;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.32144;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.31216;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02772;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03041;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03076;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02691;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02117;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02551;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03087;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02890;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01254;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01545;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01951;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01965;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01032;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01244;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01561;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01579;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00943;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01124;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01440;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01491;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00996;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01139;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01606;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01676;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01172;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01325;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01972;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01841;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01736;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01901;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02887;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02179;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02859;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02741;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04457;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02644;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00217;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00238;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00236;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00195;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00182;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00216;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00260;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00246;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00127;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00149;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00176;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00184;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00108;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00126;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00144;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00143;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00104;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00121;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00135;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00134;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00116;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00131;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00164;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00154;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00149;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00151;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00220;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00158;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00233;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00235;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00323;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00193;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00321;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00309;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00575;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00203;
      }
    }
  }  
  if(taggerName=="DeepJet"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.39123;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.42728;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.48013;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.60114;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.27506;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.29925;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34908;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.42945;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.15159;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.17425;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.23662;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.31044;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10188;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11894;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.17332;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.24947;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08359;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09752;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.14507;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.22070;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07993;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09461;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.14494;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.23055;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10313;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12426;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.18484;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.27818;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.17344;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.20458;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.28604;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.36720;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.29495;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.33567;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.46155;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48504;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10588;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11312;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11331;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.13119;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04855;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.05833;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.07789;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10192;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01590;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02042;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03153;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.05309;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01053;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01330;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01942;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03536;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00904;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01152;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01694;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03110;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00962;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01233;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02012;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03715;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01356;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01739;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02957;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.05179;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02425;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02877;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04861;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.07305;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.05510;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.06024;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09314;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10397;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01579;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01751;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01614;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01557;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00545;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00675;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00798;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00956;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00229;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00283;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00332;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00434;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00157;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00195;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00233;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00325;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00131;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00168;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00210;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00328;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00146;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00177;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00275;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00509;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00199;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00255;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00447;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00846;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00394;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00480;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00826;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01267;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01063;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01051;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01296;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01363;
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
  cout << "[BTagSFUtil::TagEfficiencyLight_2016] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  cout << "[BTagSFUtil::TagEfficiencyLight_2016] Or, wrong pt and eta range : pt = " << JetPt << ", eta = " << JetEta << endl;
  return 1.;
}
