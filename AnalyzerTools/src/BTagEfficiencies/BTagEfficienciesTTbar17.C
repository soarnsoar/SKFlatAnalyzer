float BTagSFUtil::TagEfficiencyB_2017(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.81892;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.82658;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.79971;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.78155;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87375;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87960;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85566;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.83479;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.89712;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.90195;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.87893;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.85608;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.90730;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.91177;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.89164;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.86990;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.91330;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.91686;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.89867;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87788;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.91383;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.91551;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.89784;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.87557;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.90460;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.90308;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.88393;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.86311;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88835;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88471;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86767;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.85032;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88061;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87009;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86017;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.83961;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.62596;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.63451;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.58261;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.53685;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72026;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.72630;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.67900;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.63761;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.76186;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.76580;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.71846;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.67358;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.78000;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.78228;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.73285;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.67932;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.78715;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.78558;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.73004;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.66710;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.78089;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.77166;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.70815;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.63178;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.74526;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.72609;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.65144;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.56854;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.67811;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.65248;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.57740;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.50736;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.58362;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.56187;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.50000;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.46953;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.43325;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.43209;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36478;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.32257;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.55396;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.55109;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.48107;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.43821;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.60601;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.60213;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53169;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48437;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.62220;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.61715;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.54540;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48960;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.62182;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.61234;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53508;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.47046;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.60213;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.58565;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.50014;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.42273;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.53934;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.51266;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41976;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.33880;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.42291;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.39301;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.31116;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.24949;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.27302;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.25640;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.20129;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.17025;
      }
    }
  }  
  if(taggerName=="DeepJet"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.91796;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.92407;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.91814;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92902;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.92691;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93156;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92307;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92995;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.92597;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93018;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92146;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92817;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.92577;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.92950;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92017;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.92900;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.93242;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.93545;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.92501;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.93631;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.94469;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.94686;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.93698;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.94618;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.95560;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.95700;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.94702;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.95249;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.95900;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.95857;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.95123;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.95411;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.95995;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.95942;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.95603;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.97401;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.77568;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.78422;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.75544;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.75859;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.79739;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.80339;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.77881;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.78658;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.80033;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.80382;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.77722;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.79057;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.80317;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.80532;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.77548;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.79467;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.81755;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.81845;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.78578;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.80755;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.84304;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.84234;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.80939;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.82635;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.86321;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.86098;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.82363;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.83373;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.85992;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.85251;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.80341;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.80617;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.83733;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.82243;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.75138;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.76703;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.56953;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.57310;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.51990;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.51489;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.63359;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.63455;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.58260;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.58629;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.65673;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.65610;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.60252;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.61233;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.66644;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.66494;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.60841;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.62340;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.68294;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.67943;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.61907;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.63754;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.71082;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.70473;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.64103;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.65442;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72683;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.71544;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.64280;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.65175;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.69900;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.68070;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.58482;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.59060;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.63621;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.60743;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.48790;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.50806;
      }
    }
  }  
  if(taggerName=="CSVv2"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.80005;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.80493;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.76116;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.74379;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.86134;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.86497;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.83648;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.82341;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.87990;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88238;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85846;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.84631;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88733;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88973;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86736;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.85153;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88719;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.88727;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.86130;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.83987;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.88140;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.87851;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.85314;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.82512;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.86223;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.85503;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.82575;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.79804;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.82691;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.82335;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.79331;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.77884;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.79596;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.80415;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.74766;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.74283;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.59054;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.56919;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.52255;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.48491;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.68929;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.67219;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.63667;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.60472;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72030;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.70665;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.66635;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.63165;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72737;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.71698;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.66924;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.63097;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.72217;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.71413;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.66019;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.61466;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.70365;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.69347;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.62336;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.57269;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.65976;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.64574;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53906;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.49107;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.58029;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.57400;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.47511;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.45643;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.48044;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.48716;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.38102;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38978;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.37208;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.32852;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.31076;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.27576;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.47769;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.43749;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41421;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38548;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.51001;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.48020;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.44025;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.41438;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.50712;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.48354;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.43027;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.39943;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.50885;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.49451;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41774;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37714;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.47571;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.46295;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36529;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.32380;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.41817;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.40475;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.26774;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.23484;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.32537;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.31993;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.21151;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.20794;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.21691;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.22021;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13168;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16219;
      }
    }
  }  
  cout << "[BTagSFUtil::TagEfficiencyB_2017] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  cout << "[BTagSFUtil::TagEfficiencyB_2017] Or, wrong pt and eta range : pt = " << JetPt << ", eta = " << JetEta << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyC_2017(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.33403;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.36516;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36809;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.36421;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.31714;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.35456;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37841;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38014;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.29758;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.33869;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.36890;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37010;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.30313;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.34290;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37314;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37957;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.33063;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.36674;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.39576;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.40227;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.36827;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.40034;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.42482;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.42174;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.38924;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.41359;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.43506;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.42875;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.39633;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.40240;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41317;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.42085;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.35963;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.36757;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.38335;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.44159;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10068;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11138;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10466;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.09268;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08735;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10395;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11246;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10692;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08409;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09913;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11025;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10378;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08924;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10551;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11253;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10737;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10433;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11753;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12209;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11556;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11958;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13076;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13287;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11971;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.12325;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12818;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12612;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11164;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10474;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10015;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09040;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.07739;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.06289;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.05608;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04728;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.06192;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02828;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02963;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02517;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02089;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01988;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02358;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02425;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02267;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01852;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02199;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02313;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02246;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02004;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02366;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02519;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02345;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02306;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02641;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02618;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02536;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02565;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02912;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02808;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02549;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02493;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02616;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02435;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02015;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01787;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01595;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01245;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00957;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00518;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00574;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00171;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00234;
      }
    }
  }  
  if(taggerName=="DeepJet"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.57724;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.60951;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.64674;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.69873;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.48654;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.52005;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.55769;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.61360;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.38626;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.42168;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.47169;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.53487;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.34534;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.37823;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.42305;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.49216;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.35280;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.38186;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41970;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.49268;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.40560;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.43407;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.46511;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.52533;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.48953;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.51504;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.53545;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.58762;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.55850;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.58261;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.59312;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.63684;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.60085;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.61929;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.66495;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.69509;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.23965;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.25869;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.26076;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.28934;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.16524;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.18697;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.21349;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.24974;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11642;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13224;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15527;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.18798;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10263;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11528;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13055;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16184;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10445;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11545;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12780;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16241;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.12511;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13892;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.14881;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.18444;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.16616;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.18028;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.18980;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.21859;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.20091;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.20956;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.20675;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.22485;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.22491;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.23654;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.21137;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.26168;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07158;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.07663;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.07255;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.07735;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04333;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.05027;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.05509;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.06494;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03085;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03564;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03922;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04772;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02689;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03126;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03290;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03960;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02705;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03023;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03211;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03999;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03251;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03562;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03528;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04706;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04129;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.04463;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04733;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.05192;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04902;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.04844;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04500;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04967;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.05254;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.05071;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02980;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.05841;
      }
    }
  }  
  if(taggerName=="CSVv2"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.31238;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.33912;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.31795;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.31929;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.30752;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.34292;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.35748;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37970;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.27133;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.30673;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33484;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.36432;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.26999;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.30594;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.33745;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37359;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.28580;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.32048;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.34795;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38583;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.31607;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.35227;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.37598;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.41089;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.34334;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.38024;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.39215;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.42865;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.36242;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.40594;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.40387;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.44083;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.35163;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.38719;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.38746;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.41822;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10747;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10134;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09310;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.08426;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10013;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10069;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11295;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11348;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08554;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.08923;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10138;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10544;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08340;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09109;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09674;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.10684;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08885;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09761;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10627;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.11869;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09815;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10961;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11418;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12560;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10773;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11897;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11157;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12858;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11182;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12641;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11523;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.12861;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10351;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12604;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.08530;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.13084;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03191;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02518;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02516;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02103;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02297;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02019;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02537;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02583;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01844;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01806;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02081;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02296;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01712;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01798;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01865;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02113;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02039;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02233;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02119;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02359;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02326;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02561;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02031;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02532;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02535;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02835;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01878;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02531;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02453;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02935;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01985;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02561;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.02760;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03128;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01165;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01636;
      }
    }
  }  
  cout << "[BTagSFUtil::TagEfficiencyC_2017] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  cout << "[BTagSFUtil::TagEfficiencyC_2017] Or, wrong pt and eta range : pt = " << JetPt << ", eta = " << JetEta << endl;
  return 1.;
}
float BTagSFUtil::TagEfficiencyLight_2017(float JetPt, float JetEta) {
  if(taggerName=="DeepCSV"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11572;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.14148;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.16771;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.18285;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10475;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12945;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.16391;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.17829;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08268;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10568;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.14142;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15972;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07096;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09371;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13070;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15022;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.06966;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09069;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12889;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15103;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07205;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09197;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13592;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16429;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.07809;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09839;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.14653;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.18372;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09149;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10888;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.16639;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.21456;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11943;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13041;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.20318;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.25875;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01483;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01908;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01941;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01683;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01265;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01711;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02197;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02145;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00913;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01262;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01734;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01847;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00815;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01122;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01532;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01610;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00810;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01064;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01453;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01594;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00823;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01015;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01465;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01695;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00880;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01016;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01438;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01677;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00939;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00982;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01358;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01572;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00713;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00746;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01017;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01134;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00169;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00198;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00191;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00159;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00134;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00176;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00214;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00198;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00112;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00148;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00187;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00175;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00103;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00132;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00160;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00149;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00099;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00122;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00142;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00142;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00104;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00117;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00139;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00144;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00112;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00127;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00140;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00139;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00113;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00104;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00112;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00133;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00055;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00046;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00060;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00022;
      }
    }
  }  
  if(taggerName=="DeepJet"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.44486;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.47981;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.56296;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.65045;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.32008;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.34512;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41368;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.50948;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.17082;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.19518;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.27538;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.38937;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11260;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.13153;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.19914;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.30357;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09120;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10663;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.16407;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.25928;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.08428;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.10185;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15929;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.25509;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10369;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12835;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.19548;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.29043;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.16910;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.19973;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.28267;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.37387;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.25717;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.29504;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.41282;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.47529;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.11313;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12436;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13251;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.18653;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.05629;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.06743;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.09756;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.14951;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01903;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02468;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.04301;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.08443;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01186;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01529;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02515;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.05157;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00951;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01238;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01993;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03965;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00953;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01244;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02105;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.03965;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01264;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01631;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.02767;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.04764;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01854;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02306;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.03849;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.05922;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.03280;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.03572;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.05860;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.07682;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01803;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.02048;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01931;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02745;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00672;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00847;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01184;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02118;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00275;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00345;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00500;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00939;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00176;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00220;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00306;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00553;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00134;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00165;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00236;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00434;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00128;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00164;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00247;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00467;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00152;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00195;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00327;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00628;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00225;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00264;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00441;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00782;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00430;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00431;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00510;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00869;
      }
    }
  }  
  if(taggerName=="CSVv2"){
    if(operatingPoint=="Loose"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.10294;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12442;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13411;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15104;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09185;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.11232;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13558;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16508;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.06614;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.08071;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.11086;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15491;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.05529;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.06895;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12535;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.16366;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04606;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.05849;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.10700;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.15819;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.04479;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.05982;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.12101;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.17730;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.05046;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.07093;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.13723;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.19668;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.06678;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.09412;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.15076;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.21044;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.09268;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.12258;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.16186;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.17861;
      }
    }
    if(operatingPoint=="Medium"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01042;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01119;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01390;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01474;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01004;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01097;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01742;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02107;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00786;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00857;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01334;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01737;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00709;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00765;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01167;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01519;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00609;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00665;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01119;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01521;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00583;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00682;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01078;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.01791;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00620;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00842;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01042;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02052;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00866;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01190;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01578;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02976;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.01194;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.01716;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.01596;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.02048;
      }
    }
    if(operatingPoint=="Tight"){
      if(JetPt > 20.0 && JetPt <= 30.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00147;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00135;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00147;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00203;
      }
      if(JetPt > 30.0 && JetPt <= 50.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00099;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00096;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00147;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00287;
      }
      if(JetPt > 50.0 && JetPt <= 70.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00083;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00085;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00112;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00172;
      }
      if(JetPt > 70.0 && JetPt <= 100.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00079;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00086;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00101;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00129;
      }
      if(JetPt > 100.0 && JetPt <= 140.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00092;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00101;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00106;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00142;
      }
      if(JetPt > 140.0 && JetPt <= 200.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00097;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00108;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00106;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00185;
      }
      if(JetPt > 200.0 && JetPt <= 300.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00117;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00147;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00118;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00223;
      }
      if(JetPt > 300.0 && JetPt <= 500.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00182;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00223;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00196;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00396;
      }
      if(JetPt > 500.0 && JetPt <= 1000.0){
        if(fabs(JetEta) > 0.0 && fabs(JetEta) <= 0.6) return 0.00215;
        if(fabs(JetEta) > 0.6 && fabs(JetEta) <= 1.2) return 0.00301;
        if(fabs(JetEta) > 1.2 && fabs(JetEta) <= 1.8) return 0.00185;
        if(fabs(JetEta) > 1.8 && fabs(JetEta) <= 2.4) return 0.00155;
      }
    }
  }  
  cout << "[BTagSFUtil::TagEfficiencyLight_2017] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;
  cout << "[BTagSFUtil::TagEfficiencyLight_2017] Or, wrong pt and eta range : pt = " << JetPt << ", eta = " << JetEta << endl;
  return 1.;
}
