#include "MCCorrection.h"

MCCorrection::MCCorrection() : 
IgnoreNoHist(false)
{
  cout << "[MCCorrection::MCCorrection] jhchoi!!" << endl;
  histDir = TDirectoryHelper::GetTempDirectory("MCCorrection");

  genFinderDY = new GenFinderForDY();
  //jhchoi
  //InitBtagChargeAsymFactor();
  
}

void MCCorrection::InitBtagChargeAsymFactor(){
  //--read values in txt
  TString datapath = getenv("DATA_DIR");

  TString filename=datapath+"/"+DataEra+"/btagasym/"+DataEra+"__Uncer__Cons__dAsym__x_eta.txt"; 
  std::ifstream input(filename);
  if (!input) {
    throw std::runtime_error(
			     "Cannot open file: " + filename
			     );
  }
  
  std::string line;
  
  while (std::getline(input, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }
    std::istringstream stream(line);
    
    std::string year;
    std::string ptbin;
    std::string etabin;
    
    double nominal;
    double up;
    double down;
    if (!(stream
	  >> year
	  >> ptbin
	  >> etabin
	  >> nominal
	  >> up
	  >> down)) {
      throw std::runtime_error(
			       "Invalid line: " + line
			       );
    }
    
    dAsym_result_all[year][ptbin][etabin][0]  = nominal;
    dAsym_result_all[year][ptbin][etabin][1]  = up;
    dAsym_result_all[year][ptbin][etabin][-1] = down;
  }
  
  
  
    
    
    
  //---Use only this DataEra
  cout << "define values of [this_dAsym_result]" << endl;
  cout << "DataEra" << DataEra << endl;
  const auto& refMap = dAsym_result_all.at(std::string(DataEra));
  for (const auto& [ptbin_str, etamap] : refMap) {
    int ptidx = GetPtBinIndex(ptbin_str);
    if (ptidx < 0) 1/0;
    //cout << ptbin_str << endl;
    for (const auto& [etabin_str, systmap] : etamap) {
      int etaidx = GetEtaBinIndex(etabin_str);
      if (etaidx < 0) 1/0;
      //cout << etabin_str << endl;
      for (const auto& [systDir, value] : systmap) {
        int systidx = systDir + 1;
        if (systidx < 0 || systidx > 2) 1/0;
        //cout << systDir << endl;
	this_dAsym_result[ptidx][etaidx][systidx] = value;
        cout << ptbin_str <<"/" << etabin_str << "/" << systDir << "/" << value << endl;
	if (fabs(value) > 1){
          cout << "!!!Tooo Large dAsymSF ->" << value << "BIN info. pt:" << ptidx << " eta:" << etaidx << endl;
        }
      }
    }
  }

  

}
void MCCorrection::InitBtagChargeAsymFactor_OLD(){
  cout << "jhchoi[InitBtagChargeAsymFactor]" << endl;
  //2016preVFP
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta0To0p8"][-1]=-0.009927674461544009;
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta0To0p8"][0]=0.00016014180437196046;
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta0To0p8"][1]=0.010230875436166019;
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta0p8To1p6"][-1]=-0.0026573422192386724;
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta0p8To1p6"][0]=0.011892975308001041;
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta0p8To1p6"][1]=0.026504547206004134;
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta1p6To2"][-1]=0.0065547460065941004;
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta1p6To2"][0]=0.03860737383365631;
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta1p6To2"][1]=0.07076813752670881;
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta2To2p5"][-1]=0.02299635031197937;
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta2To2p5"][0]=0.06293671578168869;
dAsym_result_all["2016preVFP"]["PT30To50"]["Eta2To2p5"][1]=0.10273732715699452;

 dAsym_result_all["2016preVFP"]["PT50To70"]["Eta0To0p8"][-1]=-0.01672285165360869;
dAsym_result_all["2016preVFP"]["PT50To70"]["Eta0To0p8"][0]=-0.0010106186382472515;
dAsym_result_all["2016preVFP"]["PT50To70"]["Eta0To0p8"][1]=0.014747742299661224;
dAsym_result_all["2016preVFP"]["PT50To70"]["Eta0p8To1p6"][-1]=-0.04113087160801316;
dAsym_result_all["2016preVFP"]["PT50To70"]["Eta0p8To1p6"][0]=-0.02250700257718563;
dAsym_result_all["2016preVFP"]["PT50To70"]["Eta0p8To1p6"][1]=-0.004126247911804812;
dAsym_result_all["2016preVFP"]["PT50To70"]["Eta1p6To2"][-1]=-0.010647556877706639;
dAsym_result_all["2016preVFP"]["PT50To70"]["Eta1p6To2"][0]=0.021494943648576736;
dAsym_result_all["2016preVFP"]["PT50To70"]["Eta1p6To2"][1]=0.05343547590021772;
dAsym_result_all["2016preVFP"]["PT50To70"]["Eta2To2p5"][-1]=-0.09548851878868296;
dAsym_result_all["2016preVFP"]["PT50To70"]["Eta2To2p5"][0]=-0.062472376972436905;
dAsym_result_all["2016preVFP"]["PT50To70"]["Eta2To2p5"][1]=-0.029438587164043295;

dAsym_result_all["2016preVFP"]["PT70To100"]["Eta0To0p8"][-1]=-0.0037668824110509216;
dAsym_result_all["2016preVFP"]["PT70To100"]["Eta0To0p8"][0]=0.012088972143828869;
dAsym_result_all["2016preVFP"]["PT70To100"]["Eta0To0p8"][1]=0.027992090242336037;
dAsym_result_all["2016preVFP"]["PT70To100"]["Eta0p8To1p6"][-1]=-0.019585034303070924;
dAsym_result_all["2016preVFP"]["PT70To100"]["Eta0p8To1p6"][0]=-0.0009576003067195415;
dAsym_result_all["2016preVFP"]["PT70To100"]["Eta0p8To1p6"][1]=0.017657398049751378;
dAsym_result_all["2016preVFP"]["PT70To100"]["Eta1p6To2"][-1]=-0.048450460076618386;
dAsym_result_all["2016preVFP"]["PT70To100"]["Eta1p6To2"][0]=-0.007427786942571402;
dAsym_result_all["2016preVFP"]["PT70To100"]["Eta1p6To2"][1]=0.03324841288132361;
dAsym_result_all["2016preVFP"]["PT70To100"]["Eta2To2p5"][-1]=-0.0019867457651312898;
dAsym_result_all["2016preVFP"]["PT70To100"]["Eta2To2p5"][0]=0.05138333514332771;
dAsym_result_all["2016preVFP"]["PT70To100"]["Eta2To2p5"][1]=0.10496559054341899;

 dAsym_result_all["2016preVFP"]["PT100To140"]["Eta0To0p8"][-1]=-0.04954994170883666;
dAsym_result_all["2016preVFP"]["PT100To140"]["Eta0To0p8"][0]=-0.030039651319384575;
dAsym_result_all["2016preVFP"]["PT100To140"]["Eta0To0p8"][1]=-0.010796061697198055;
dAsym_result_all["2016preVFP"]["PT100To140"]["Eta0p8To1p6"][-1]=-0.05572701305905405;
dAsym_result_all["2016preVFP"]["PT100To140"]["Eta0p8To1p6"][0]=-0.030031824484467506;
dAsym_result_all["2016preVFP"]["PT100To140"]["Eta0p8To1p6"][1]=-0.004101706707465364;
dAsym_result_all["2016preVFP"]["PT100To140"]["Eta1p6To2"][-1]=-0.02205865727116514;
dAsym_result_all["2016preVFP"]["PT100To140"]["Eta1p6To2"][0]=0.0219557024538517;
dAsym_result_all["2016preVFP"]["PT100To140"]["Eta1p6To2"][1]=0.06564271912408647;
dAsym_result_all["2016preVFP"]["PT100To140"]["Eta2To2p5"][-1]=-0.0983677848374985;
dAsym_result_all["2016preVFP"]["PT100To140"]["Eta2To2p5"][0]=-0.0281731765717268;
dAsym_result_all["2016preVFP"]["PT100To140"]["Eta2To2p5"][1]=0.04238765566562294;


 dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta0To0p8"][-1]=-0.03153844988326076;
dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta0To0p8"][0]=-0.0023065030109137297;
dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta0To0p8"][1]=0.02684694974933528;
dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta0p8To1p6"][-1]=-0.07865925388702343;
dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta0p8To1p6"][0]=-0.03462124243378639;
dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta0p8To1p6"][1]=0.009073869305168812;
dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta1p6To2"][-1]=0.16153999950975167;
dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta1p6To2"][0]=0.27007898688316345;
dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta1p6To2"][1]=0.3744562289556057;
dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta2To2p5"][-1]=-0.4488290627098726;
dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta2To2p5"][0]=-0.2861124873161316;
dAsym_result_all["2016preVFP"]["PT140ToInf"]["Eta2To2p5"][1]=-0.08920688029640511;


  //2016postVFP
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta0To0p8"][-1]=-0.010823177165315934;
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta0To0p8"][0]=0.0004721073783002794;
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta0To0p8"][1]=0.011924056087537964;
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta0p8To1p6"][-1]=-0.007661127511931834;
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta0p8To1p6"][0]=0.008035285398364067;
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta0p8To1p6"][1]=0.024006849672220124;
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta1p6To2"][-1]=-0.015794016595435792;
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta1p6To2"][0]=0.006988563109189272;
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta1p6To2"][1]=0.029788077643274884;
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta2To2p5"][-1]=0.006547790441246815;
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta2To2p5"][0]=0.04512759670615196;
dAsym_result_all["2016postVFP"]["PT30To50"]["Eta2To2p5"][1]=0.08384977418617352;

 
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta0To0p8"][-1]=0.02223661195859104;
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta0To0p8"][0]=0.03729364648461342;
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta0To0p8"][1]=0.052957212609969107;
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta0p8To1p6"][-1]=-0.005722867624995142;
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta0p8To1p6"][0]=0.008709479123353958;
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta0p8To1p6"][1]=0.02282305615076676;
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta1p6To2"][-1]=-0.04607068019916514;
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta1p6To2"][0]=-0.015306144021451473;
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta1p6To2"][1]=0.015713944957868667;
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta2To2p5"][-1]=-0.06447761438727716;
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta2To2p5"][0]=-0.018368743360042572;
dAsym_result_all["2016postVFP"]["PT50To70"]["Eta2To2p5"][1]=0.027318363171983787;



dAsym_result_all["2016postVFP"]["PT70To100"]["Eta0To0p8"][-1]=-0.021184575599342708;
dAsym_result_all["2016postVFP"]["PT70To100"]["Eta0To0p8"][0]=-0.007681427989155054;
dAsym_result_all["2016postVFP"]["PT70To100"]["Eta0To0p8"][1]=0.005672126811775931;
dAsym_result_all["2016postVFP"]["PT70To100"]["Eta0p8To1p6"][-1]=-0.024151219513556175;
dAsym_result_all["2016postVFP"]["PT70To100"]["Eta0p8To1p6"][0]=-0.0034359556157141924;
dAsym_result_all["2016postVFP"]["PT70To100"]["Eta0p8To1p6"][1]=0.016936182361524815;
dAsym_result_all["2016postVFP"]["PT70To100"]["Eta1p6To2"][-1]=-0.025264260335126187;
dAsym_result_all["2016postVFP"]["PT70To100"]["Eta1p6To2"][0]=0.010374306701123714;
dAsym_result_all["2016postVFP"]["PT70To100"]["Eta1p6To2"][1]=0.04605169766601319;
dAsym_result_all["2016postVFP"]["PT70To100"]["Eta2To2p5"][-1]=0.017491878180153797;
dAsym_result_all["2016postVFP"]["PT70To100"]["Eta2To2p5"][0]=0.07073305547237396;
dAsym_result_all["2016postVFP"]["PT70To100"]["Eta2To2p5"][1]=0.12357300276893118;


dAsym_result_all["2016postVFP"]["PT100To140"]["Eta0To0p8"][-1]=0.0014687724021152267;
dAsym_result_all["2016postVFP"]["PT100To140"]["Eta0To0p8"][0]=0.01781371794641018;
dAsym_result_all["2016postVFP"]["PT100To140"]["Eta0To0p8"][1]=0.03416394927108507;
dAsym_result_all["2016postVFP"]["PT100To140"]["Eta0p8To1p6"][-1]=0.02465811820554723;
dAsym_result_all["2016postVFP"]["PT100To140"]["Eta0p8To1p6"][0]=0.04585445299744606;
dAsym_result_all["2016postVFP"]["PT100To140"]["Eta0p8To1p6"][1]=0.0670339818246322;
dAsym_result_all["2016postVFP"]["PT100To140"]["Eta1p6To2"][-1]=0.02538714999474479;
dAsym_result_all["2016postVFP"]["PT100To140"]["Eta1p6To2"][0]=0.0827891007065773;
dAsym_result_all["2016postVFP"]["PT100To140"]["Eta1p6To2"][1]=0.13940307930480425;
dAsym_result_all["2016postVFP"]["PT100To140"]["Eta2To2p5"][-1]=-0.16798622530708157;
dAsym_result_all["2016postVFP"]["PT100To140"]["Eta2To2p5"][0]=-0.07070435583591461;
dAsym_result_all["2016postVFP"]["PT100To140"]["Eta2To2p5"][1]=0.02986886170570295;


dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta0To0p8"][-1]=0.00859240265823074;
dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta0To0p8"][0]=0.040868256241083145;
dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta0To0p8"][1]=0.07238844386217304;
dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta0p8To1p6"][-1]=0.06167818003309371;
dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta0p8To1p6"][0]=0.10550958663225174;
dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta0p8To1p6"][1]=0.14974128696255531;
dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta1p6To2"][-1]=-0.13214023631814575;
dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta1p6To2"][0]=-0.051705025136470795;
dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta1p6To2"][1]=0.029994767288567245;
dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta2To2p5"][-1]=-0.2054722753888219;
dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta2To2p5"][0]=0.0007972741150297225;
dAsym_result_all["2016postVFP"]["PT140ToInf"]["Eta2To2p5"][1]=0.2152569974523346;


//2017
dAsym_result_all["2017"]["PT30To50"]["Eta0To0p8"][-1]=-0.00581086596728349;
dAsym_result_all["2017"]["PT30To50"]["Eta0To0p8"][0]=0.0010965528199449182;
dAsym_result_all["2017"]["PT30To50"]["Eta0To0p8"][1]=0.008016566214789658;
dAsym_result_all["2017"]["PT30To50"]["Eta0p8To1p6"][-1]=-0.006162086524543062;
dAsym_result_all["2017"]["PT30To50"]["Eta0p8To1p6"][0]=0.0029007133562117815;
dAsym_result_all["2017"]["PT30To50"]["Eta0p8To1p6"][1]=0.012015137573653929;
dAsym_result_all["2017"]["PT30To50"]["Eta1p6To2"][-1]=0.021919050388695113;
dAsym_result_all["2017"]["PT30To50"]["Eta1p6To2"][0]=0.03685931861400604;
dAsym_result_all["2017"]["PT30To50"]["Eta1p6To2"][1]=0.05181179732536213;
dAsym_result_all["2017"]["PT30To50"]["Eta2To2p5"][-1]=0.0339962885189903;
dAsym_result_all["2017"]["PT30To50"]["Eta2To2p5"][0]=0.05685530602931976;
dAsym_result_all["2017"]["PT30To50"]["Eta2To2p5"][1]=0.07980137764346165;

dAsym_result_all["2017"]["PT50To70"]["Eta0To0p8"][-1]=-0.010186741841863077;
dAsym_result_all["2017"]["PT50To70"]["Eta0To0p8"][0]=-0.0020362338982522488;
dAsym_result_all["2017"]["PT50To70"]["Eta0To0p8"][1]=0.00611126634408328;
dAsym_result_all["2017"]["PT50To70"]["Eta0p8To1p6"][-1]=-0.0006609534630989209;
dAsym_result_all["2017"]["PT50To70"]["Eta0p8To1p6"][0]=0.008708975277841091;
dAsym_result_all["2017"]["PT50To70"]["Eta0p8To1p6"][1]=0.018099322495020914;
dAsym_result_all["2017"]["PT50To70"]["Eta1p6To2"][-1]=0.01809672940908452;
dAsym_result_all["2017"]["PT50To70"]["Eta1p6To2"][0]=0.04100019484758377;
dAsym_result_all["2017"]["PT50To70"]["Eta1p6To2"][1]=0.06391065050587269;
dAsym_result_all["2017"]["PT50To70"]["Eta2To2p5"][-1]=0.009469285983170421;
dAsym_result_all["2017"]["PT50To70"]["Eta2To2p5"][0]=0.03902658447623253;
dAsym_result_all["2017"]["PT50To70"]["Eta2To2p5"][1]=0.06851490548446783;



dAsym_result_all["2017"]["PT70To100"]["Eta0To0p8"][-1]=-0.02039889611707543;
dAsym_result_all["2017"]["PT70To100"]["Eta0To0p8"][0]=-0.010802765376865864;
dAsym_result_all["2017"]["PT70To100"]["Eta0To0p8"][1]=-0.0013271952529550907;
dAsym_result_all["2017"]["PT70To100"]["Eta0p8To1p6"][-1]=-0.012922065436753538;
dAsym_result_all["2017"]["PT70To100"]["Eta0p8To1p6"][0]=-0.001627036021091044;
dAsym_result_all["2017"]["PT70To100"]["Eta0p8To1p6"][1]=0.009800439799984307;
dAsym_result_all["2017"]["PT70To100"]["Eta1p6To2"][-1]=-0.018735485618811224;
dAsym_result_all["2017"]["PT70To100"]["Eta1p6To2"][0]=0.009165436029434204;
dAsym_result_all["2017"]["PT70To100"]["Eta1p6To2"][1]=0.03693277565465567;
dAsym_result_all["2017"]["PT70To100"]["Eta2To2p5"][-1]=0.020017504224489488;
dAsym_result_all["2017"]["PT70To100"]["Eta2To2p5"][0]=0.05832994356751442;
dAsym_result_all["2017"]["PT70To100"]["Eta2To2p5"][1]=0.09674155608117933;


dAsym_result_all["2017"]["PT100To140"]["Eta0To0p8"][-1]=-0.0402090890971809;
dAsym_result_all["2017"]["PT100To140"]["Eta0To0p8"][0]=-0.027084987610578537;
dAsym_result_all["2017"]["PT100To140"]["Eta0To0p8"][1]=-0.013798666306738552;
dAsym_result_all["2017"]["PT100To140"]["Eta0p8To1p6"][-1]=0.00843939623325551;
dAsym_result_all["2017"]["PT100To140"]["Eta0p8To1p6"][0]=0.02422022446990013;
dAsym_result_all["2017"]["PT100To140"]["Eta0p8To1p6"][1]=0.04031592633901752;
dAsym_result_all["2017"]["PT100To140"]["Eta1p6To2"][-1]=-0.0832243726932413;
dAsym_result_all["2017"]["PT100To140"]["Eta1p6To2"][0]=-0.04384738579392433;
dAsym_result_all["2017"]["PT100To140"]["Eta1p6To2"][1]=-0.0050271661420706465;
dAsym_result_all["2017"]["PT100To140"]["Eta2To2p5"][-1]=-0.048624924319870304;
dAsym_result_all["2017"]["PT100To140"]["Eta2To2p5"][0]=0.012908926233649254;
dAsym_result_all["2017"]["PT100To140"]["Eta2To2p5"][1]=0.07415626633161844;


dAsym_result_all["2017"]["PT140ToInf"]["Eta0To0p8"][-1]=-0.03345837603511652;
dAsym_result_all["2017"]["PT140ToInf"]["Eta0To0p8"][0]=-0.017358504235744476;
dAsym_result_all["2017"]["PT140ToInf"]["Eta0To0p8"][1]=-0.0012825744819283322;
dAsym_result_all["2017"]["PT140ToInf"]["Eta0p8To1p6"][-1]=0.009558452763031158;
dAsym_result_all["2017"]["PT140ToInf"]["Eta0p8To1p6"][0]=0.03575459122657776;
dAsym_result_all["2017"]["PT140ToInf"]["Eta0p8To1p6"][1]=0.06206076943837987;
dAsym_result_all["2017"]["PT140ToInf"]["Eta1p6To2"][-1]=-0.1531098079330084;
dAsym_result_all["2017"]["PT140ToInf"]["Eta1p6To2"][0]=-0.09117455035448074;
dAsym_result_all["2017"]["PT140ToInf"]["Eta1p6To2"][1]=-0.031315274978470316;
dAsym_result_all["2017"]["PT140ToInf"]["Eta2To2p5"][-1]=0.030204268507389276;
dAsym_result_all["2017"]["PT140ToInf"]["Eta2To2p5"][0]=0.2337620109319687;
dAsym_result_all["2017"]["PT140ToInf"]["Eta2To2p5"][1]=0.3984200525570541;


  //2018
dAsym_result_all["2018"]["PT30To50"]["Eta0To0p8"][-1]=0.007358832723149459;
dAsym_result_all["2018"]["PT30To50"]["Eta0To0p8"][0]=0.013248656876385212;
dAsym_result_all["2018"]["PT30To50"]["Eta0To0p8"][1]=0.01914798920942731;
dAsym_result_all["2018"]["PT30To50"]["Eta0p8To1p6"][-1]=0.004894798899910343;
dAsym_result_all["2018"]["PT30To50"]["Eta0p8To1p6"][0]=0.012434265576303005;
dAsym_result_all["2018"]["PT30To50"]["Eta0p8To1p6"][1]=0.020024740654899235;
dAsym_result_all["2018"]["PT30To50"]["Eta1p6To2"][-1]=-0.013079872288501831;
dAsym_result_all["2018"]["PT30To50"]["Eta1p6To2"][0]=0.0008394744945690036;
dAsym_result_all["2018"]["PT30To50"]["Eta1p6To2"][1]=0.014834405818587632;
dAsym_result_all["2018"]["PT30To50"]["Eta2To2p5"][-1]=-0.031998464349122055;
dAsym_result_all["2018"]["PT30To50"]["Eta2To2p5"][0]=-0.011646872386336327;
dAsym_result_all["2018"]["PT30To50"]["Eta2To2p5"][1]=0.008524124381229632;


dAsym_result_all["2018"]["PT50To70"]["Eta0To0p8"][-1]=-0.019449868869687574;
dAsym_result_all["2018"]["PT50To70"]["Eta0To0p8"][0]=-0.013176491484045982;
dAsym_result_all["2018"]["PT50To70"]["Eta0To0p8"][1]=-0.006894222897680952;
dAsym_result_all["2018"]["PT50To70"]["Eta0p8To1p6"][-1]=-0.0027923101716274337;
dAsym_result_all["2018"]["PT50To70"]["Eta0p8To1p6"][0]=0.005137792322784662;
dAsym_result_all["2018"]["PT50To70"]["Eta0p8To1p6"][1]=0.013038363125753363;
dAsym_result_all["2018"]["PT50To70"]["Eta1p6To2"][-1]=0.025783917452140082;
dAsym_result_all["2018"]["PT50To70"]["Eta1p6To2"][0]=0.042356375604867935;
dAsym_result_all["2018"]["PT50To70"]["Eta1p6To2"][1]=0.05941529050749278;
dAsym_result_all["2018"]["PT50To70"]["Eta2To2p5"][-1]=-0.004529787391813745;
dAsym_result_all["2018"]["PT50To70"]["Eta2To2p5"][0]=0.017870064824819565;
dAsym_result_all["2018"]["PT50To70"]["Eta2To2p5"][1]=0.040533236230575295;

dAsym_result_all["2018"]["PT70To100"]["Eta0To0p8"][-1]=-0.012241560362165001;
dAsym_result_all["2018"]["PT70To100"]["Eta0To0p8"][0]=-0.005645238794386387;
dAsym_result_all["2018"]["PT70To100"]["Eta0To0p8"][1]=0.0009521483047481407;
dAsym_result_all["2018"]["PT70To100"]["Eta0p8To1p6"][-1]=-0.007079146701493164;
dAsym_result_all["2018"]["PT70To100"]["Eta0p8To1p6"][0]=0.001498007564805448;
dAsym_result_all["2018"]["PT70To100"]["Eta0p8To1p6"][1]=0.010113858009717449;
dAsym_result_all["2018"]["PT70To100"]["Eta1p6To2"][-1]=-0.014925442015165904;
dAsym_result_all["2018"]["PT70To100"]["Eta1p6To2"][0]=0.008515211753547192;
dAsym_result_all["2018"]["PT70To100"]["Eta1p6To2"][1]=0.03189541003912921;
dAsym_result_all["2018"]["PT70To100"]["Eta2To2p5"][-1]=-0.05280042096770415;
dAsym_result_all["2018"]["PT70To100"]["Eta2To2p5"][0]=-0.026045018807053566;
dAsym_result_all["2018"]["PT70To100"]["Eta2To2p5"][1]=0.0007090533478341307;


dAsym_result_all["2018"]["PT100To140"]["Eta0To0p8"][-1]=-0.007693800045020967;
dAsym_result_all["2018"]["PT100To140"]["Eta0To0p8"][0]=0.0030131840612739325;
dAsym_result_all["2018"]["PT100To140"]["Eta0To0p8"][1]=0.013850932253916162;
dAsym_result_all["2018"]["PT100To140"]["Eta0p8To1p6"][-1]=-5.328310836433606e-05;
dAsym_result_all["2018"]["PT100To140"]["Eta0p8To1p6"][0]=0.014483453705906868;
dAsym_result_all["2018"]["PT100To140"]["Eta0p8To1p6"][1]=0.028904762764860505;
dAsym_result_all["2018"]["PT100To140"]["Eta1p6To2"][-1]=-0.03582112884250092;
dAsym_result_all["2018"]["PT100To140"]["Eta1p6To2"][0]=-0.0033138557337224483;
dAsym_result_all["2018"]["PT100To140"]["Eta1p6To2"][1]=0.02890039275889872;
dAsym_result_all["2018"]["PT100To140"]["Eta2To2p5"][-1]=-0.05450370725711815;
dAsym_result_all["2018"]["PT100To140"]["Eta2To2p5"][0]=-0.005472644232213497;
dAsym_result_all["2018"]["PT100To140"]["Eta2To2p5"][1]=0.043439110071594435;


dAsym_result_all["2018"]["PT140ToInf"]["Eta0To0p8"][-1]=-0.027922979579607078;
dAsym_result_all["2018"]["PT140ToInf"]["Eta0To0p8"][0]=-0.0152486776933074;
dAsym_result_all["2018"]["PT140ToInf"]["Eta0To0p8"][1]=-0.0025833090493880793;
dAsym_result_all["2018"]["PT140ToInf"]["Eta0p8To1p6"][-1]=0.0075035875786103635;
dAsym_result_all["2018"]["PT140ToInf"]["Eta0p8To1p6"][0]=0.02707127295434475;
dAsym_result_all["2018"]["PT140ToInf"]["Eta0p8To1p6"][1]=0.04691202439088519;
dAsym_result_all["2018"]["PT140ToInf"]["Eta1p6To2"][-1]=0.03757474167546396;
dAsym_result_all["2018"]["PT140ToInf"]["Eta1p6To2"][0]=0.10190125554800034;
dAsym_result_all["2018"]["PT140ToInf"]["Eta1p6To2"][1]=0.1654726336722126;
dAsym_result_all["2018"]["PT140ToInf"]["Eta2To2p5"][-1]=-0.15058375357829207;
dAsym_result_all["2018"]["PT140ToInf"]["Eta2To2p5"][0]=-0.07326273620128632;
dAsym_result_all["2018"]["PT140ToInf"]["Eta2To2p5"][1]=0.0061353592776734606;


 
  //---Use only this DataEra
  cout << "define values of [this_dAsym_result]" << endl;
  cout << "DataEra" << DataEra << endl;
  const auto& refMap = dAsym_result_all[std::string(DataEra)];
  for (const auto& [ptbin_str, etamap] : refMap) {
    int ptidx = GetPtBinIndex(ptbin_str);
    if (ptidx < 0) 1/0;
    //cout << ptbin_str << endl;
    for (const auto& [etabin_str, systmap] : etamap) {
      int etaidx = GetEtaBinIndex(etabin_str);
      if (etaidx < 0) 1/0;
      //cout << etabin_str << endl;
      for (const auto& [systDir, value] : systmap) {
        int systidx = systDir + 1;
        if (systidx < 0 || systidx > 2) 1/0;
	//cout << systDir << endl;
        this_dAsym_result[ptidx][etaidx][systidx] = value;
	
	//cout << ptbin_str <<"/" << etabin_str << "/" << systDir << value << endl;
	if(value > 1){
	  cout << "!!!Tooo Large dAsymSF ->" << value << "BIN info. pt:" << ptidx << " eta:" << etaidx << endl;
	}
      }
    }
  }

  
}

int MCCorrection::GetPtBinIndex(const std::string& ptbin) {
  if (ptbin == "PT30To50") return 0;
  if (ptbin == "PT50To70") return 1;
  if (ptbin == "PT70To100") return 2;
  if (ptbin == "PT100To140") return 3;
  if (ptbin == "PT140ToInf") return 4;

  return -1;

}
int MCCorrection::GetEtaBinIndex(const std::string& etabin) {
  if (etabin == "Eta0To0p8") return 0;
  if (etabin == "Eta0p8To1p6") return 1;
  if (etabin == "Eta1p6To2") return 2;
  if (etabin == "Eta2To2p5") return 3;
  return -1;
  
}
vector<TString> MCCorrection::Split(TString s,TString del){
  TObjArray* array=s.Tokenize(del);
  vector<TString> out;
  for(const auto& obj:*array) out.push_back(((TObjString*)obj)->String());
  array->Delete();
  return out;
}
void MCCorrection::ReadHistograms(){

  TString datapath = getenv("DATA_DIR");

  TDirectory* origDir = gDirectory;

  //==== ID/Trigger
  TString IDpath = datapath+"/"+GetEra()+"/ID/";

  vector<TString> elhistmaps=Split(gSystem->GetFromPipe("find "+IDpath+"/Electron/ -name 'histmap*.txt' -type f"),"\n");
  for(const auto& elhistmap:elhistmaps){
    string elline;
    ifstream in(elhistmap);
    while(getline(in,elline)){
      std::istringstream is( elline );

      TString tstring_elline = elline;
      if(tstring_elline.Contains("#")) continue;

      TString a,b,c,d,e,f;
      is >> a; // ID,RECO
      is >> b; // Eff,SF
      is >> c; // <WPnames>
      is >> d; // <rootfilename>
      is >> e; // <histname>
      is >> f; // Class
      TFile *file = new TFile(IDpath+"/Electron/"+d);
      
      if(f=="TH2F"){
	histDir->cd();
	map_hist_Electron[a+"_"+b+"_"+c] = (TH2F *)file->Get(e)->Clone();
      }
      else if(f=="TGraphAsymmErrors"){
	histDir->cd();
	map_graph_Electron[a+"_"+b+"_"+c] = (TGraphAsymmErrors *)file->Get(e)->Clone();
      }
      else{
	cout << "[MCCorrection::MCCorrection] Wrong class type : " << elline << endl;
      }
      file->Close();
      if(file){
	delete file;
	file=nullptr;
      }
      origDir->cd();
    }
  }

  cout << "[MCCorrection::MCCorrection] map_hist_Electron :" << endl;
  for(std::map< TString, TH2F* >::iterator it=map_hist_Electron.begin(); it!=map_hist_Electron.end(); it++){
    cout << "[MCCorrection::MCCorrection] key = " << it->first << endl;
  }
  cout << "[MCCorrection::MCCorrection] map_graph_Electron :" << endl;
  for(std::map< TString, TGraphAsymmErrors* >::iterator it=map_graph_Electron.begin(); it!=map_graph_Electron.end(); it++){
    cout << "[MCCorrection::MCCorrection] key = " << it->first << endl;
  }


  vector<TString> muhistmaps=Split(gSystem->GetFromPipe("find "+IDpath+"/Muon/ -name 'histmap*.txt' -type f"),"\n");
  for(const auto& muhistmap:muhistmaps){
    string elline2;
    ifstream in2(muhistmap);
    while(getline(in2,elline2)){
      std::istringstream is( elline2 );

      TString tstring_elline = elline2;
      if(tstring_elline.Contains("#")) continue;
      
      TString a,b,c,d,e;
      is >> a; // ID,RERCO
      is >> b; // Eff,SF
      is >> c; // <WPnames>
      is >> d; // <rootfilename>
      is >> e; // <histname>
      TFile *file = new TFile(IDpath+"/Muon/"+d);
      histDir->cd();
      map_hist_Muon[a+"_"+b+"_"+c] = (TH2F *)file->Get(e)->Clone();
      file->Close();
      if(file){
	delete file;
	file=nullptr;
      }
      origDir->cd();
    }
  }

  cout << "[MCCorrection::MCCorrection] map_hist_Muon :" << endl;
  for(std::map< TString, TH2F* >::iterator it=map_hist_Muon.begin(); it!=map_hist_Muon.end(); it++){
    cout << "[MCCorrection::MCCorrection] key = " << it->first << endl;
  }


  // == Get Prefiring maps
  TString PrefirePath  = datapath+"/"+GetEra()+"/Prefire/";

  string elline3;
  ifstream in3(PrefirePath+"/histmap.txt");
  while(getline(in3,elline3)){
    std::istringstream is( elline3 );

    TString tstring_elline = elline3;
    if(tstring_elline.Contains("#")) continue;

    TString a,b,c;
    is >> a; // Jet, Photon
    is >> b; // <rootfilename>
    is >> c; // <histname>
    
    TFile *file = new TFile(PrefirePath+b);
    histDir->cd();
    map_hist_prefire[a + "_prefire"] = (TH2F *)file->Get(c)->Clone();
    file->Close();
    if(file){
      delete file;
      file=nullptr;
    }
    origDir->cd();
  }


  // == Get Pileup Reweight maps
  TString PUReweightPath = datapath+"/"+GetEra()+"/PileUp/";

  string elline4;
  ifstream  in4(PUReweightPath+"/histmap.txt");
  while(getline(in4,elline4)){
    std::istringstream is( elline4 );

    TString tstring_elline = elline4;
    if(tstring_elline.Contains("#")) continue;

    TString a,b,c;
    is >> a; // sample name
    is >> b; // syst
    is >> c; // rootfile name

    //if(DataYear == 2017 && a!=MCSample) continue;
    
    TFile *file = new TFile(PUReweightPath+c);
    if( (TH1D *)file->Get(a+"_"+b) ){
      histDir->cd();
      map_hist_pileup[a+"_"+b+"_pileup"] = (TH1D *)file->Get(a+"_"+b)->Clone();
    }
    else{
      cout << "[MCCorrection::ReadHistograms] No : " << a + "_" + b << endl;
    }
    file->Close();
    if(file){
      delete file;
      file=nullptr;
    }
    origDir->cd();
  }
/*
  cout << "[MCCorrection::MCCorrection] map_hist_pileup :" << endl;
  for(std::map< TString, TH1D* >::iterator it=map_hist_pileup.begin(); it!=map_hist_pileup.end(); it++){
    cout << it->first << endl;
  }
*/
  
  // == Get Official DY Pt reweight maps
  TString DYPtReweightPath = datapath+"/"+GetEra()+"/DYPtReweight/Zpt_weights_"+TString::Itoa(DataYear,10)+".root";
  TFile *file_DYPtReweightPath = new TFile(DYPtReweightPath);
  histDir->cd();
  hist_DYPtReweight_2D = (TH2D *)file_DYPtReweightPath->Get("zptmass_weights")->Clone();
  file_DYPtReweightPath->Close();
  if(file_DYPtReweightPath){
    delete file_DYPtReweightPath;
    file_DYPtReweightPath=nullptr;
  }
  origDir->cd();
}

MCCorrection::~MCCorrection(){
  if(genFinderDY){
    delete genFinderDY;
    genFinderDY=nullptr;
  }
}

void MCCorrection::SetMCSample(TString s){
  MCSample = s;
}
void MCCorrection::SetIsDATA(bool b){
  IsDATA = b;
}
void MCCorrection::SetEventInfo(int r, int l, int e){
  run = r;
  lumi = l;
  event = e;
}
void MCCorrection::SetIsFastSim(bool b){
  IsFastSim = b;
}

double MCCorrection::MuonReco_SF(TString key, double eta, double p, int sys){

  //cout << "[MCCorrection::MuonReco_SF] key = " << key << endl;
  //cout << "[MCCorrection::MuonReco_SF] eta = " << eta << ", p = " << p << endl;

  if(key=="Default") return 1.;

  double value = 1.;
  double error = 0.;

  eta = fabs(eta);

  if(key=="HighPtMuonRecoSF"){

    //==== XXX this histogram uses P not Pt    

    //==== boundaries
    if(p<50.) p = 50.;
    if(p>=3500.) p = 3499.;
    if(eta>=2.4) eta = 2.39;

  }

  //cout << "[MCCorrection::MuonReco_SF] corrected eta = " << eta << ", p = " << p << endl;
  //cout << "[MCCorrection::MuonReco_SF] histname = " << "RECO_SF_"+key << endl;

  TH2F *this_hist = map_hist_Muon["RECO_SF_"+key];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cerr << "[MCCorrection::MuonReco_SF] No "<<"RECO_SF_"+key<<endl;
      exit(ENODATA);
    }
  }

  int this_bin = this_hist->FindBin(p, eta);
  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  //cout << "[MCCorrection::MuonReco_SF] --> value = " << value << "\t" << ", error = " << error << endl;

  return value+double(sys)*error;

}

double MCCorrection::MuonID_SF(TString ID, double eta, double pt, int sys){

  if(ID=="Default") return 1.;

  //cout << "[MCCorrection::MuonID_SF] ID = " << ID << endl;
  //cout << "[MCCorrection::MuonID_SF] eta = " << eta << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  eta = fabs(eta);

  if(ID=="NUM_TightID_DEN_TrackerMuons" || ID=="NUM_MediumID_DEN_TrackerMuons" || ID=="NUM_HighPtID_DEN_TrackerMuons"){
    //==== boundaries
    if(pt<15.) pt = 15.1;
    if(pt>=120.) pt = 119.9;
    if(eta>=2.4) eta = 2.39;
  }

  TH2F *this_hist = map_hist_Muon["ID_SF_"+ID];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cerr << "[MCCorrection::MuonID_SF] No "<<"ID_SF_"+ID<<endl;
      exit(ENODATA);
    }
  }

  int this_bin(-999);

  this_bin = this_hist->FindBin(eta,pt);

  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  //cout << "[MCCorrection::MuonID_SF] value = " << value << endl;

  return value+double(sys)*error;

}

double MCCorrection::MuonISO_SF(TString ID, double eta, double pt, int sys){

  if(ID=="Default") return 1.;

  //cout << "[MCCorrection::MuonISO_SF] eta = " << eta << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  eta = fabs(eta);

  if(ID=="NUM_TightRelIso_DEN_TightIDandIPCut" || ID=="NUM_TightRelIso_DEN_MediumID" || ID=="NUM_LooseRelTkIso_DEN_HighPtIDandIPCut"){
    //==== boundaries
    if(pt<15.) pt = 15.1;
    if(pt>=120.) pt = 119.9;
    if(eta>=2.4) eta = 2.39;
  }

  TH2F *this_hist = map_hist_Muon["ISO_SF_"+ID];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cerr << "[MCCorrection::MuonISO_SF] No "<<"ISO_SF_"+ID<<endl;
      exit(ENODATA);
    }
  }

  int this_bin(-999);

  this_bin = this_hist->FindBin(eta,pt);

  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  //cout << "[MCCorrection::MuonISO_SF] value = " << value << endl;

  return value+double(sys)*error;

}

double MCCorrection::MuonTrigger_Eff(TString ID, TString trig, int DataOrMC, double eta, double pt, int sys){

  //cout << "[MCCorrection::MuonTrigger_Eff] Called" << endl;

  if(ID=="Default") return 1.;
  if(trig=="Default") return 1.;

  //cout << "[MCCorrection::MuonTrigger_Eff] DataYear = " << DataYear << endl;
  //cout << "[MCCorrection::MuonTrigger_Eff] ID = " << ID << "\t" << "trig = " << trig << endl;
  //cout << "[MCCorrection::MuonTrigger_Eff] DataOrMC = " << DataOrMC << endl;
  //cout << "[MCCorrection::MuonTrigger_Eff] eta = " << eta << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  eta = fabs(eta);

  //==== 2016
  if(DataYear==2016){
    if(trig=="IsoMu24"){
      if(pt<26.) return 1.; //FIXME
      if(eta>=2.4) eta = 2.39;

      if(pt>200.) pt = 199.;
    }
    else if(trig=="Mu50"){
      if(pt<52.) return 1.; //FIXME
      if(eta>=2.4) eta = 2.39;

      if(pt>1000.) pt = 999.;
    }
    else{

    }
  }
  else if(DataYear==2017){
    if(trig=="IsoMu27"){
      //==== FIXME MiniAODPt Pt
      //==== FIXME 28.9918  29.0363
      //==== FIXME This event pass pt>29GeV cut, but MiniAOD pt < 29 GeV
      //==== FIXME So when I return 0., SF goes nan.. let's return 1 for now..
      if(pt<29.) return 1.; //FIXME
      if(eta>=2.4) eta = 2.39;

      if(pt>200.) pt = 199.;
    }
    else if(trig=="Mu50"){
      if(pt<52.) return 1.; //FIXME
      if(eta>=2.4) eta = 2.39;

      if(pt>1000.) pt = 999.;
    }
    else{

    }
  }
  else if(DataYear==2018){
    if(trig=="IsoMu24"){
      if(pt<26.) return 1.; //FIXME
      if(eta>=2.4) eta = 2.39;

      if(pt>200.) pt = 199.;
    }
    else if(trig=="Mu50"){
      if(pt<52.) return 1.; //FIXME
      if(eta>=2.4) eta = 2.39;

      if(pt>1000.) pt = 999.;
    }
    else{

    }
  }
  else{
    cerr << "[MCCorrection::MuonTrigger_Eff] Wrong year : " << DataYear << endl;
    exit(ENODATA);
  }

  TString histkey = "Trigger_Eff_DATA_"+trig+"_"+ID;
  if(DataOrMC==1) histkey = "Trigger_Eff_MC_"+trig+"_"+ID;
  //cout << "[MCCorrection::MuonTrigger_Eff] histkey = " << histkey << endl;
  TH2F *this_hist = map_hist_Muon[histkey];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cerr << "[MCCorrection::MuonTrigger_Eff] No "<<histkey<<endl;
      exit(ENODATA);
    }
  }

  int this_bin = this_hist->FindBin(eta,pt);

  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  //cout << "[MCCorrection::MuonTrigger_Eff] value = " << value << endl;

  return value+double(sys)*error;


}

double MCCorrection::MuonTrigger_SF(TString ID, TString trig, const std::vector<Muon>& muons, int sys){

  if(muons.size() == 0) return 1.;

  if(ID=="Default") return 1.;
  if(trig=="Default") return 1.;

  double value = 1.;

  if(trig=="IsoMu24" || trig=="IsoMu27" || trig=="Mu50"){

    double eff_DATA = 1.;
    double eff_MC = 1.;

    for(unsigned int i=0; i<muons.size(); i++){
      eff_DATA *= ( 1.-MuonTrigger_Eff(ID, trig, 0, muons.at(i).Eta(), muons.at(i).MiniAODPt(), sys) );
      eff_MC   *= ( 1.-MuonTrigger_Eff(ID, trig, 1, muons.at(i).Eta(), muons.at(i).MiniAODPt(), -sys) );
    }

    eff_DATA = 1.-eff_DATA;
    eff_MC = 1.-eff_MC;

    value = eff_DATA/eff_MC;

/*
    if(eff_DATA==0||eff_MC==0){
      cout << "==== Zero Trigger Eff ====" << endl;
      for(unsigned int i=0;i<muons.size();i++){
        cout << muons.at(i).MiniAODPt() << "\t" << muons.at(i).Pt() << endl;
      }
    }
*/

  }

  return value;

}

double MCCorrection::MuonTrigger_SF(TString ID, TString trig, const std::vector<Muon *>& muons, int sys){

  if(muons.size() == 0) return 1.;

  std::vector<Muon> muvec;
  for(unsigned int i=0; i<muons.size(); i++){
    Muon this_muon = *(muons.at(i));
    muvec.push_back( this_muon );
  }

  return MuonTrigger_SF(ID, trig, muvec, sys);

}

double MCCorrection::ElectronID_SF(TString ID, double sceta, double pt, int sys){

  if(ID=="Default") return 1.;

  double value = 1.;
  double error = 0.;

  if(pt<10.) pt = 10.1;
  if(pt>=500.) pt = 499.9;
  if(sceta>=2.5) sceta = 2.49;
  if(sceta<-2.5) sceta = -2.49;

  if( ID.Contains("HEEP") ){

    //==== https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaRunIIRecommendations#HEEPV7_0
    //==== summary: a simple robust ID designed to be safe for high electrons.
    //==== The Et evolution of this ID must be well described in the MC therefore this ID is designed so its scale factor is flat vs Et.
    //==== As a result the HEEP differs in that it provides just a single number for the barrel and a single number for the endcap.
    //==== * note there almost certainly will have to be a retune for 2018 due to HCAL data/MC disagreements
    //==== * 2018 prompt: expected Dec 2018

    bool IsBarrel = fabs(sceta) < 1.479;
    double this_SF(1.);
    double this_SF_staterr(0.); // absolute value
    double this_SF_systerr(0.); // absolute value
    double this_SF_err(0.);

    if(DataYear==2016){
      this_SF         = (IsBarrel ? 0.971 : 0.983);
      this_SF_staterr = (IsBarrel ? 0.001 : 0.001);

      if(IsBarrel) this_SF_systerr = (pt<90. ? 0.01 : min(1.+(pt-90.)*0.0022,3.)*0.01) * this_SF;
      else         this_SF_systerr = (pt<90. ? 0.01 : min(1.+(pt-90.)*0.0143,4.)*0.01) * this_SF;

      this_SF_err = sqrt(this_SF_staterr*this_SF_staterr+this_SF_systerr*this_SF_systerr);
    }
    else if(DataYear==2017){ 
      this_SF         = (IsBarrel ? 0.967 : 0.973);
      this_SF_staterr = (IsBarrel ? 0.001 : 0.002);
      
      if(IsBarrel) this_SF_systerr = (pt<90. ? 0.01 : min(1.+(pt-90.)*0.0022,3.)*0.01) * this_SF;
      else         this_SF_systerr = (pt<90. ? 0.02 : min(1.+(pt-90.)*0.0143,5.)*0.01) * this_SF;
      
      this_SF_err = sqrt(this_SF_staterr*this_SF_staterr+this_SF_systerr*this_SF_systerr);
    }
    else if(DataYear==2018){

      //==== https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaRunIIRecommendations#HEEPv7_0_2018Prompt

      this_SF         = (IsBarrel ? 0.969 : 0.984);
      this_SF_staterr = (IsBarrel ? 0.000 : 0.001);

      if(IsBarrel) this_SF_systerr = (pt<90. ? 0.01 : min(1.+(pt-90.)*0.0022,3.)*0.01) * this_SF;
      else         this_SF_systerr = (pt<90. ? 0.02 : min(1.+(pt-90.)*0.0143,5.)*0.01) * this_SF;

      this_SF_err = sqrt(this_SF_staterr*this_SF_staterr+this_SF_systerr*this_SF_systerr);
    }
    else{
      cerr << "[MCCorrection::ElectronID_SF] (Hist) Wrong year "<< DataYear << endl;
      exit(ENODATA);
    }

    return this_SF+double(sys)*this_SF_err;

  }
  else{

    TH2F *this_hist = map_hist_Electron["ID_SF_"+ID];
    if(!this_hist){
      if(IgnoreNoHist) return 1.;
      else{
        cerr << "[MCCorrection::ElectronID_SF] (Hist) No "<<"ID_SF_"+ID<<endl;
        exit(ENODATA);
      }
    }

    int this_bin = this_hist->FindBin(sceta,pt);
    value = this_hist->GetBinContent(this_bin);
    error = this_hist->GetBinError(this_bin);

    return value+double(sys)*error;

  }

}

double MCCorrection::ElectronReco_SF(double sceta, double pt, int sys){

  double value = 1.;
  double error = 0.;

  TString ptrange = "ptgt20";
  if(pt<20.) ptrange = "ptlt20";

  if(pt<10.) pt = 10.;
  if(pt>=500.) pt = 499.;
  if(sceta>=2.5) sceta = 2.49;
  if(sceta<-2.5) sceta = -2.5;

  TH2F *this_hist = map_hist_Electron["RECO_SF_"+ptrange];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cerr << "[MCCorrection::ElectronReco_SF] No "<<"RECO_SF_"+ptrange<<endl;
      exit(ENODATA);
    }
  }

  //cout << "[MCCorrection::ElectronReco_SF] " << this_hist->GetBinContent(1,1) << endl;

  int this_bin = this_hist->FindBin(sceta,pt);
  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  return value+double(sys)*error;

}

double MCCorrection::ElectronTrigger_Eff(TString ID, TString trig, int DataOrMC, double sceta, double pt, int sys){

  if(ID=="Default") return 1.;
  if(trig=="Default") return 1.;

  //cout << "[MCCorrection::ElectronTrigger_Eff] ID = " << ID << "\t" << "trig = " << trig << endl;
  //cout << "[MCCorrection::ElectronTrigger_Eff] DataOrMC = " << DataOrMC << endl;
  //cout << "[MCCorrection::ElectronTrigger_Eff] sceta = " << sceta << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  if(trig=="WREGammaTrigger"){

    if(pt<50.) pt = 50.;
    if(pt>=500.) pt = 499.;

    if(sceta<-2.5) sceta = -2.5;
    if(sceta>=2.5) sceta = 2.49;

    TString etaregion = "Barrel";
    if(fabs(sceta) > 1.566) etaregion = "EndCap";

    TString histkey = "Trigger_Eff_DATA_"+trig+"_"+ID+"_"+etaregion;
    if(DataOrMC==1) histkey = "Trigger_Eff_MC_"+trig+"_"+ID+"_"+etaregion;
    //cout << "[MCCorrection::ElectronTrigger_Eff] histkey = " << histkey << endl;
    TH2F *this_hist = map_hist_Electron[histkey];
    if(!this_hist){
      if(IgnoreNoHist) return 1.;
      else{
        cerr << "[MCCorrection::ElectronTrigger_Eff] No "<<histkey<<endl;
        exit(ENODATA);
      }
    }

    int this_bin = this_hist->FindBin(sceta, pt);

    value = this_hist->GetBinContent(this_bin);
    error = this_hist->GetBinError(this_bin);

  }

  //cout << "[MCCorrection::ElectronTrigger_Eff] value = " << value << endl;

  return value+double(sys)*error;

}

double MCCorrection::ElectronTrigger_SF(TString ID, TString trig, const std::vector<Electron>& electrons, int sys){

  if(ID=="Default") return 1.;
  if(trig=="Default") return 1.;

  double value = 1.;

  if(trig=="WREGammaTrigger"){

    double eff_DATA = 1.;
    double eff_MC = 1.;

    for(unsigned int i=0; i<electrons.size(); i++){
      eff_DATA *= ( 1.-ElectronTrigger_Eff(ID, trig, 0, electrons.at(i).scEta(), electrons.at(i).Pt(), sys) );
      eff_MC   *= ( 1.-ElectronTrigger_Eff(ID, trig, 1, electrons.at(i).scEta(), electrons.at(i).Pt(), -sys) );
    }

    eff_DATA = 1.-eff_DATA;
    eff_MC = 1.-eff_MC;

    value = eff_DATA/eff_MC;
    if(IsFastSim) value = eff_DATA;


/*
    if(eff_DATA==0||eff_MC==0){
      cout << "==== Zero Trigger Eff ====" << endl;
      for(unsigned int i=0;i<electrons.size();i++){
        cout << electrons.at(i).Pt() << "\t" << electrons.at(i).Pt() << endl;
      }
    }
*/

  }

  return value;

}

double MCCorrection::ElectronTrigger_SF(TString ID, TString trig, const std::vector<Electron *>& electrons, int sys){

  std::vector<Electron> muvec;
  for(unsigned int i=0; i<electrons.size(); i++){
    Electron this_electron = *(electrons.at(i));
    muvec.push_back( this_electron );
  }

  return ElectronTrigger_SF(ID, trig, muvec, sys);

}

double MCCorrection::GetPrefireWeight(const std::vector<Photon>& photons, const std::vector<Jet>& jets, int sys){

  double photon_weight = 1.;
  double jet_weight = 1.;
  
  TH2F *photon_hist = map_hist_prefire["Photon_prefire"];
  TH2F *jet_hist = map_hist_prefire["Jet_prefire"];

  
  for(unsigned int i_pho = 0; i_pho < photons.size(); i_pho++){
    Photon current_photon = photons.at(i_pho);
    double eta = current_photon.scEta();
    double pt = current_photon.Pt();
    
    int this_bin = photon_hist->FindBin(eta, pt);

    double this_eff = photon_hist->GetBinContent(this_bin);
    double this_efferr = photon_hist->GetBinError(this_bin);

    double current_weight = 1. - (this_eff + (double)sys * this_efferr );;
    photon_weight = photon_weight * current_weight;
  }
  
  for(unsigned int i_jet = 0; i_jet < jets.size(); i_jet++){
    Jet current_jet = jets.at(i_jet);
    double eta = current_jet.Eta();
    double pt = current_jet.Pt();
    
    int this_bin = jet_hist->FindBin(eta, pt);

    double this_eff = jet_hist->GetBinContent(this_bin);
    double this_efferr = jet_hist->GetBinError(this_bin);

    double current_weight = 1.- (this_eff + (double)sys * this_efferr);
    jet_weight = jet_weight * current_weight;
  }

  return photon_weight * jet_weight;;

}


double MCCorrection::GetPileUpWeightBySampleName(int N_pileup, int syst){
  
  int this_bin = N_pileup+1;
  if(N_pileup >= 100) this_bin=100;

  TString this_histname = MCSample;
  if(syst == 0){
    this_histname += "_central_pileup";
  }
  else if(syst == -1){
    this_histname += "_sig_down_pileup";
  }
  else if(syst == 1){
    this_histname += "_sig_up_pileup";
  }
  else{
    cerr << "[MCCorrection::GetPileUpWeightBySampleName] syst should be 0, -1, or +1" << endl;
    exit(ENODATA);
  }

  TH1D *this_hist = map_hist_pileup[this_histname];
  if(!this_hist){
    cerr << "[MCCorrection::GetPileUpWeightBySampleName] No " << this_histname << endl;
    exit(ENODATA);
  }

  return this_hist->GetBinContent(this_bin);

}

double MCCorrection::GetPileUpWeight(int N_pileup, int syst){

  TString this_histname = "MC_" + GetEra();
  if(syst == 0){
    this_histname += "_central_pileup";
  }
  else if(syst == -1){
    this_histname += "_sig_down_pileup";
  }
  else if(syst == 1){
    this_histname += "_sig_up_pileup";
  }
  else{
    cerr << "[MCCorrection::GetPileUpWeight] syst should be 0, -1, or +1" << endl;
    exit(ENODATA);
  }

  TH1D *this_hist = map_hist_pileup[this_histname];
  if(!this_hist){
    cerr << "[MCCorrection::GetPileUpWeight] No " << this_histname << endl;
    exit(ENODATA);
  }
  
  int this_bin = N_pileup+1;
  if(this_bin>this_hist->GetNbinsX()) this_bin=this_hist->GetNbinsX();

  double pu_weight=this_hist->GetBinContent(this_bin);
  return pu_weight;

}

double MCCorrection::GetTopPtReweight(const std::vector<Gen>& gens){
  //==== ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting2017
  //==== Only top quarks in SM ttbar events must be reweighted, 
  //==== not single tops or tops from BSM production mechanisms.
  if(!MCSample.Contains("TT") || !MCSample.Contains("powheg")){
    return 1.;
  }
  //==== initialize with large number
  double toppt1=10000, toppt2=10000;
  bool found_top = false, found_atop = false;

  for(vector<Gen>::const_iterator genit=gens.begin(); genit!=gens.end(); genit++){
    
    if(genit->Status() == 22){
      if(genit->PID() == 6){
        toppt1= genit->Pt();
        found_top = true;
      }
      else if(genit->PID() == -6){
        toppt2= genit->Pt();
        found_atop = true;
      }
    }
    //==== after we found top pair, break the loop
    if(found_top && found_atop) break;
  }
  double pt_reweight = 1.;
  //==== if top pair is not found, return 1.
  //==== the measurement covers only the range pt(top)<=800GeV, otherwise, return 1.
  if(toppt1<=800 && toppt2 <=800){
    pt_reweight*=exp(0.0615-0.0005*toppt1);
    pt_reweight*=exp(0.0615-0.0005*toppt2);
    pt_reweight = sqrt(pt_reweight);
  }
  return pt_reweight;
}

double MCCorrection::GetOfficialDYReweight(const vector<Gen>& gens, int sys){

  genFinderDY->Find(gens);
  Particle genZ = genFinderDY->GenZ;

  double mZ = genZ.M();
  double ptZ = genZ.Pt();

  int bin_mass = hist_DYPtReweight_2D->GetXaxis()->FindBin(mZ);
  int bin_pt   = hist_DYPtReweight_2D->GetYaxis()->FindBin(ptZ);

  double value = hist_DYPtReweight_2D->GetBinContent( bin_mass, bin_pt );
  double error = hist_DYPtReweight_2D->GetBinError( bin_mass, bin_pt );

  return value+double(sys)*error;

}

void MCCorrection::SetJetTaggingParameters(std::vector<JetTagging::Parameters> v){
  jetTaggingPars = v;
}

void MCCorrection::SetupJetTagging(TString _btagmceff_filename,bool _Use_dAsym,TString _btagmceff_filename2){
  
  if(IsDATA) return;


  
  TString datapath = getenv("DATA_DIR");
  TString btagpath = datapath+"/"+GetEra()+"/BTag/";

  std::map< string, BTagCalibration > tmp_map_BTagCalibration; //==== key = tagger+"_"+method
  for(unsigned int i=0; i<jetTaggingPars.size(); i++){
    //==== (DeepCSV,Medium,incl,comb

    cout << "[MCCorrection::SetJetTaggingParameters] Contructing BTagCalibrationReader with ";jetTaggingPars.at(i).Print();
    string this_tagger = JetTagging::TaggerToString(jetTaggingPars.at(i).j_Tagger);

    string this_wp = JetTagging::WPToString(jetTaggingPars.at(i).j_WP);
    BTagEntry::OperatingPoint op = BTagEntry::OP_LOOSE;
    if(this_wp=="Loose"){
      op = BTagEntry::OP_LOOSE;
    }
    else if(this_wp=="Medium"){
      op = BTagEntry::OP_MEDIUM;
    }
    else if(this_wp=="Tight"){
      op = BTagEntry::OP_TIGHT;
    }
    else{
      cerr << "[MCCorrection::ReadJetTaggingCVSs()] Wrong WP : " << this_wp << endl;
      exit(ENODATA);
    }
    //==== When using iterativefit method, use BTagEntry::OP_RESHAPING
    if(jetTaggingPars.at(i).j_MeasurmentType_Light==JetTagging::iterativefit ||
       jetTaggingPars.at(i).j_MeasurmentType_Heavy==JetTagging::iterativefit ){
      op = BTagEntry::OP_RESHAPING;
    }

    string this_mt_L = JetTagging::MeasurmentTypeToString(jetTaggingPars.at(i).j_MeasurmentType_Light);
    string this_mt_H = JetTagging::MeasurmentTypeToString(jetTaggingPars.at(i).j_MeasurmentType_Heavy);

    ifstream in(btagpath+"/cvsmap.txt");
    string btagline; // dummy
    while(getline(in,btagline)){
      std::istringstream is( btagline );

      TString tstring_btagline = btagline;
      if(tstring_btagline.Contains("#")) continue;

      int tmp_Year, tmp_Run_Start, tmp_Run_End;
      string tmp_tagger, tmp_pd, tmp_filename;

      is >> tmp_Year; // YEAR
      is >> tmp_tagger; // TAGGER
      is >> tmp_pd; // Period_dep
      is >> tmp_Run_Start; // Run_start
      is >> tmp_Run_End; // Run_end
      is >> tmp_filename; // csv file
      if( tmp_tagger != this_tagger ) continue;
      if( tmp_pd != "All") continue; // don't no period dep now

      //==== Get BTagCalibration objects for both heavy-method and light-method first
      //==== BTagCalibration() is where we read and addEntry from csv file, so it takes time
      //==== So let's not contruct it again if it already exists
      string this_key_L = tmp_tagger+"_"+this_mt_L;
      std::map< string, BTagCalibration >::const_iterator tmp_it_L = tmp_map_BTagCalibration.find( tmp_tagger+"_"+this_key_L );
      if(tmp_it_L==tmp_map_BTagCalibration.end()){
        tmp_map_BTagCalibration[tmp_tagger+"_"+this_key_L] = BTagCalibration(tmp_tagger, this_mt_L, btagpath.Data()+tmp_filename);
      }
      string this_key_H = tmp_tagger+"_"+this_mt_H;
      std::map< string, BTagCalibration >::const_iterator tmp_it_H = tmp_map_BTagCalibration.find( tmp_tagger+"_"+this_key_H );
      if(tmp_it_H==tmp_map_BTagCalibration.end()){
        tmp_map_BTagCalibration[tmp_tagger+"_"+this_key_H] = BTagCalibration(tmp_tagger, this_mt_H, btagpath.Data()+tmp_filename);
      }

      //==== Now, contructing BTagCalibrationReader obect

      std::vector<std::string> systvec_L = {"up", "up_correlated", "up_uncorrelated", "down", "down_correlated", "down_uncorrelated"};
      std::vector<std::string> systvec_C = {"up", "up_correlated", "up_uncorrelated", "down", "down_correlated", "down_uncorrelated"};
      std::vector<std::string> systvec_B = {"up", "up_correlated", "up_uncorrelated", "down", "down_correlated", "down_uncorrelated"};
      if(this_mt_L=="iterativefit"){
        systvec_L = {"up_hf","down_hf","up_jes","down_jes","up_lfstats1","down_lfstats1","up_lfstats2","down_lfstats2"};
        systvec_C = {"up_cferr1","down_cferr1","up_cferr2","down_cferr2"};
        systvec_B = {"up_hfstats1","down_hfstats1","up_hfstats2","down_hfstats2","up_lf","down_lf","up_jes","down_jes"};
      }

      //==== Load L
      map_BTagCalibrationReader[tmp_tagger+"_"+this_wp+"_L_"+this_mt_L] = new BTagCalibrationReader(op, "central", systvec_L);
      map_BTagCalibrationReader[tmp_tagger+"_"+this_wp+"_L_"+this_mt_L]->load( tmp_map_BTagCalibration[tmp_tagger+"_"+this_key_L], BTagEntry::FLAV_UDSG, this_mt_L);
      //==== Load C
      map_BTagCalibrationReader[tmp_tagger+"_"+this_wp+"_C_"+this_mt_H] = new BTagCalibrationReader(op, "central", systvec_C);
      map_BTagCalibrationReader[tmp_tagger+"_"+this_wp+"_C_"+this_mt_H]->load( tmp_map_BTagCalibration[tmp_tagger+"_"+this_key_H], BTagEntry::FLAV_C, this_mt_H);
      //==== Load B
      map_BTagCalibrationReader[tmp_tagger+"_"+this_wp+"_B_"+this_mt_H] = new BTagCalibrationReader(op, "central", systvec_B);
      map_BTagCalibrationReader[tmp_tagger+"_"+this_wp+"_B_"+this_mt_H]->load( tmp_map_BTagCalibration[tmp_tagger+"_"+this_key_H], BTagEntry::FLAV_B, this_mt_H);

    }


  } // END loop jetTaggingPars

  cout << "[MCCorrection::SetJetTaggingParameters] Printing all BTagCalibrationReader :" << endl;
  for(std::map< std::string, BTagCalibrationReader* >::iterator it=map_BTagCalibrationReader.begin(); it!=map_BTagCalibrationReader.end(); it++){
    cout << "[MCCorrection::SetJetTaggingParameters] key = " << it->first << endl;
  }
  cout << "[MCCorrection::SetupJetTagging]_btagmceff_filename=" << _btagmceff_filename << endl;
  cout << "[MCCorrection::SetupJetTagging]_btagmceff_filename2=" << _btagmceff_filename2 << endl;
  if(_Use_dAsym){
    cout << "[MCCorrection::SetupJetTagging]Setup MCJetTagEff With dAsym!!" << endl;
    use_dasym=true;
    InitBtagChargeAsymFactor();
  }else{
    cout << "[MCCorrection::SetupJetTagging]Setup MCJetTagEff. NO dAsym!!" << endl;
  }
  SetupMCJetTagEff(_btagmceff_filename,_btagmceff_filename2);
}

double MCCorrection::GetdAsymResult(double JetPt, double JetEta, int SystDir, int iptbinsys, int ietabinsys){
  int JetPtBIN=-1;
  int JetEtaBIN=-1;
  if(JetPt < 30.){
    return 0.;
  }else if(JetPt < 50.){
    JetPtBIN=kPT30To50;
  }else if(JetPt < 70.){
    JetPtBIN=kPT50To70;
  }else if(JetPt < 100.){
    JetPtBIN=kPT70To100;
  }else if(JetPt < 140.){
    JetPtBIN=kPT100To140;
  }else{
    JetPtBIN=kPT140ToInf;
  }

  if(JetEta < 0.8){
    JetEtaBIN=kEta0To0p8;
  }else if(JetEta < 1.6){
    JetEtaBIN=kEta0p8To1p6;
  }else if(JetEta < 2.){
    JetEtaBIN=kEta1p6To2;
  }else if(JetEta < 2.5){
    JetEtaBIN=kEta2To2p5;
  }else{
    return 0.;
  }
  if(SystDir!=0){//syst var
    if(JetPtBIN!=iptbinsys) SystDir=0; // if the variation is not matched to current jet's pt
    if(JetEtaBIN!=ietabinsys) SystDir=0; // if the variation is not matched to current jet's pt
  }
  
  int idx_SystDir=SystDir+1;
  
  return this_dAsym_result[JetPtBIN][JetEtaBIN][idx_SystDir];
}


double MCCorrection::GetJetTaggingSF_dAsymCharge(JetTagging::Parameters jtp, int partonFlavour, int JetFlavor, double JetPt, double JetEta, int SystDir, int iptbinsys, int ietabinsys){
  ///---OnlyFor DeepJet/Tigh
  //---Choose HardCoding for speeed
  if(IsDATA) return 0.;
  if(jtp.j_Tagger != JetTagging::DeepJet) return 0.;
  if(jtp.j_WP != JetTagging::Tight) return 0.;
  if(abs(partonFlavour)!=5) return 0.;
  if(JetFlavor!=5) return 0.;
  
  JetEta=fabs(JetEta);
  //return 0;
  //cout << "[MCCorrection::GetJetTaggingSF_dAsymCharge]Get dAsymSF!!" << endl;
  return GetdAsymResult(JetPt, JetEta, SystDir, iptbinsys,ietabinsys);

  
}



double MCCorrection::GetJetTaggingSF(JetTagging::Parameters jtp, int JetFlavor, double JetPt, double JetEta, double Jetdiscr, string Syst){

  if(IsDATA) return 1.;

  string this_tagger = JetTagging::TaggerToString( jtp.j_Tagger );
  string this_wp = JetTagging::WPToString( jtp.j_WP );
  string this_mt_L = JetTagging::MeasurmentTypeToString(jtp.j_MeasurmentType_Light);
  string this_mt_H = JetTagging::MeasurmentTypeToString(jtp.j_MeasurmentType_Heavy);

  string key = JetTagging::TaggerToString( jtp.j_Tagger )+"_"+this_wp;
  BTagEntry::JetFlavor jf = BTagEntry::FLAV_B;
  if(abs(JetFlavor)==5){
    key += "_B_"+this_mt_H;
    jf = BTagEntry::FLAV_B;
  }
  else if(abs(JetFlavor)==4){
    key += "_C_"+this_mt_H;
    jf = BTagEntry::FLAV_C;
  }
  else{
    key += "_L_"+this_mt_L;
    jf = BTagEntry::FLAV_UDSG;
  }

  std::map< std::string, BTagCalibrationReader* >::const_iterator it = map_BTagCalibrationReader.find(key);
  if(it== map_BTagCalibrationReader.end()){
    cerr << "[MCCorrection::GetJetTaggingSF] b tag SF map not found for key = " << key << endl;
    return 1.;
    exit(ENODATA);
  }

  double this_SF = it->second->eval_auto_bounds(Syst, jf, fabs(JetEta), JetPt, Jetdiscr);
  //cout << "[MCCorrection::GetJetTaggingSF] key = " << it->first << endl;
  //cout << "[MCCorrection::GetJetTaggingSF] Jet tagging parameter : ";jtp.Print();
  //printf("[MCCorrection::GetJetTaggingSF] (JetFlavor, JetPt, JetEta, Jetdiscr, Syst) = (%d, %f, %f, %f, %s)\n",JetFlavor,JetPt,JetEta,Jetdiscr,Syst.c_str());
  //cout << "--> SF = " << this_SF << endl;
  return this_SF;

}



double MCCorrection::GetJetTaggingCutValue(JetTagging::Tagger tagger, JetTagging::WP wp){

  if(DataEra=="2016preVFP"){
    if(tagger==JetTagging::DeepCSV){
      if(wp==JetTagging::Loose)  return 0.2027;
      if(wp==JetTagging::Medium) return 0.6001;
      if(wp==JetTagging::Tight)  return 0.8819;
    }
    if(tagger==JetTagging::DeepCSV_CvsL){
      if(wp==JetTagging::Loose) return 0.088;
      if(wp==JetTagging::Medium) return 0.181;
      if(wp==JetTagging::Tight) return 0.417;
    }
    if(tagger==JetTagging::DeepCSV_CvsB){
      if(wp==JetTagging::Loose) return 0.214;
      if(wp==JetTagging::Medium) return 0.228;
      if(wp==JetTagging::Tight) return 0.138;
    }
    if(tagger==JetTagging::DeepJet){
      if(wp==JetTagging::Loose)  return 0.0508;
      if(wp==JetTagging::Medium) return 0.2598;
      if(wp==JetTagging::Tight)  return 0.6502;
    }
    if(tagger==JetTagging::DeepJet_CvsL){
      if(wp==JetTagging::Loose) return 0.039;
      if(wp==JetTagging::Medium) return 0.098;
      if(wp==JetTagging::Tight) return 0.270;
    }
    if(tagger==JetTagging::DeepJet_CvsB){
      if(wp==JetTagging::Loose) return 0.327;
      if(wp==JetTagging::Medium) return 0.370;
      if(wp==JetTagging::Tight) return 0.256;
    }
  }
  if(DataEra=="2016postVFP"){
    if(tagger==JetTagging::DeepCSV){
      if(wp==JetTagging::Loose)  return 0.1918;
      if(wp==JetTagging::Medium) return 0.5847;
      if(wp==JetTagging::Tight)  return 0.8767;
    }
    if(tagger==JetTagging::DeepCSV_CvsL){
      if(wp==JetTagging::Loose) return 0.088;
      if(wp==JetTagging::Medium) return 0.180;
      if(wp==JetTagging::Tight) return 0.407;
    }
    if(tagger==JetTagging::DeepCSV_CvsB){
      if(wp==JetTagging::Loose) return 0.204;
      if(wp==JetTagging::Medium) return 0.221;
      if(wp==JetTagging::Tight) return 0.136;
    }
    if(tagger==JetTagging::DeepJet){
      if(wp==JetTagging::Loose)  return 0.0480;
      if(wp==JetTagging::Medium) return 0.2489;
      if(wp==JetTagging::Tight)  return 0.6377;
    }
    if(tagger==JetTagging::DeepJet_CvsL){
      if(wp==JetTagging::Loose) return 0.039;
      if(wp==JetTagging::Medium) return 0.099;
      if(wp==JetTagging::Tight) return 0.269;
    }
    if(tagger==JetTagging::DeepJet_CvsB){
      if(wp==JetTagging::Loose) return 0.305;
      if(wp==JetTagging::Medium) return 0.353;
      if(wp==JetTagging::Tight) return 0.247;
    }
  }
  if(DataEra=="2017"){
    if(tagger==JetTagging::DeepCSV){
      if(wp==JetTagging::Loose)  return 0.1355;
      if(wp==JetTagging::Medium) return 0.4506;
      if(wp==JetTagging::Tight)  return 0.7738;
    }
    if(tagger==JetTagging::DeepCSV_CvsL){
      if(wp==JetTagging::Loose) return 0.04;
      if(wp==JetTagging::Medium) return 0.144;
      if(wp==JetTagging::Tight) return 0.73;
    }
    if(tagger==JetTagging::DeepCSV_CvsB){
      if(wp==JetTagging::Loose) return 0.345;
      if(wp==JetTagging::Medium) return 0.29;
      if(wp==JetTagging::Tight) return 0.10;
    }
    if(tagger==JetTagging::DeepJet){
      if(wp==JetTagging::Loose)  return 0.0532;
      if(wp==JetTagging::Medium) return 0.3040;
      if(wp==JetTagging::Tight)  return 0.7476;
    }
    if(tagger==JetTagging::DeepJet_CvsL){
      if(wp==JetTagging::Loose) return 0.03;
      if(wp==JetTagging::Medium) return 0.085;
      if(wp==JetTagging::Tight) return 0.52;
    }
    if(tagger==JetTagging::DeepJet_CvsB){
      if(wp==JetTagging::Loose) return 0.4;
      if(wp==JetTagging::Medium) return 0.34;
      if(wp==JetTagging::Tight) return 0.05;
    }
  }
  if(DataEra=="2018"){
    if(tagger==JetTagging::DeepCSV){
      if(wp==JetTagging::Loose)  return 0.1208;
      if(wp==JetTagging::Medium) return 0.4168;
      if(wp==JetTagging::Tight)  return 0.7665;
    }
    if(tagger==JetTagging::DeepCSV_CvsL){
      if(wp==JetTagging::Loose) return 0.064;
      if(wp==JetTagging::Medium) return 0.153;
      if(wp==JetTagging::Tight) return 0.405;
    }
    if(tagger==JetTagging::DeepCSV_CvsB){
      if(wp==JetTagging::Loose) return 0.313;
      if(wp==JetTagging::Medium) return 0.363;
      if(wp==JetTagging::Tight) return 0.288;
    }
    if(tagger==JetTagging::DeepJet){
      if(wp==JetTagging::Loose)  return 0.0490;
      if(wp==JetTagging::Medium) return 0.2783;
      if(wp==JetTagging::Tight)  return 0.7100;
    }
    if(tagger==JetTagging::DeepJet_CvsL){
      if(wp==JetTagging::Loose) return 0.038;
      if(wp==JetTagging::Medium) return 0.099;
      if(wp==JetTagging::Tight) return 0.282;
    }
    if(tagger==JetTagging::DeepJet_CvsB){
      if(wp==JetTagging::Loose) return 0.246;
      if(wp==JetTagging::Medium) return 0.325;
      if(wp==JetTagging::Tight) return 0.267;
    }
  }

  cout << "[MCCorrection::GetJetTaggingCutValue] Wrong " << endl;
  cout << "[MCCorrection::GetJetTaggingCutValue] DataEra = " << DataEra << endl;
  cout << "[MCCorrection::GetJetTaggingCutValue] tagger = " << tagger << endl;
  cout << "[MCCorrection::GetJetTaggingCutValue] wp = " << wp << endl;
  exit(ENODATA);

  return 1;

}

void MCCorrection::SetupMCJetTagEff(TString _btagmceff_filename, TString _btagmceff_filename2){
  cout<<"[MCCorrection::SetupMCJetTagEff] setting MCJetTagEff"<<endl;
  cout << "_btagmceff_filename=" << _btagmceff_filename << endl;
  
  TString default_btageff_file="MeasureJetTaggingEfficiency_TTLL_TTLJ_hadded.root";
  TString datapath=getenv("DATA_DIR");
  
  if(_btagmceff_filename==""){
    cout << "[jhchoi]Use default btag mc eff" << endl;
    _btagmceff_filename=default_btageff_file;
  }
  else{
    TString mcjetpath1=datapath+"/"+DataEra+"/BTag/"+_btagmceff_filename;
    cout << "[jhchoi]Use  btag mc eff-->" << mcjetpath1 << endl;
    ifstream fcheck1(mcjetpath1);
    if(!fcheck1.good()){
      cout << "[jhchoi]FAIL!!! to load  btag mc eff-->" << mcjetpath1 << endl;
      cout << "Use default file" << endl;
      _btagmceff_filename=default_btageff_file;
    }
  }



  if(_btagmceff_filename2==""){
    cout << "[jhchoi]Use default btag mc eff" << endl;
    _btagmceff_filename2=default_btageff_file;
  }
  else{
    TString mcjetpath2=datapath+"/"+DataEra+"/BTag/"+_btagmceff_filename2;
    cout << "[jhchoi]Use  2nd btag mc eff-->" << mcjetpath2 << endl;
    ifstream fcheck2(mcjetpath2);
    if(!fcheck2.good()){
      cout << "[jhchoi]FAIL!!! to load  btag mc eff-->" << mcjetpath2 << endl;
      cout << "Use default file" << endl;
      _btagmceff_filename2=default_btageff_file;
    }
  }
  


  //---primary mceff---//
  TString mcjetpath=datapath+"/"+DataEra+"/BTag/"+_btagmceff_filename;
  cout << "[jhchoi]mcjetpath----->" << mcjetpath << endl;
  ifstream fcheck(mcjetpath);
  if(!fcheck.good()){
    cout<<"[MCCorrection::SetupMCJetTagEff] no "+mcjetpath<<endl;
    return;
  }


  TFile fmcjet(mcjetpath);
  // Denominator histogram setup first
  vector<TString> jfs = {"B", "C", "Light"};
  for(unsigned int i=0; i<jfs.size(); i++){
    TString hden="Jet_"+DataEra+"_eff_"+jfs.at(i)+"_denom";
    TH2F* this_hist=(TH2F*)fmcjet.Get(hden);
    map_hist_mcjet[hden]=this_hist;
    this_hist->SetDirectory(0);
    cout<<"[MCCorrection::SetupMCJetTagEff] setting "<<hden<<endl;
  }
  // Numerator histogram setup and divided using "binomial option"
  for(const auto& obj:*(fmcjet.GetListOfKeys())){
    TH2F* this_hist=(TH2F*)((TKey*)obj)->ReadObj();
    TString hnum=this_hist->GetName();
    if(!hnum.Contains("num")) continue;
    TString hden="";
    if(hnum.Contains("_B_")) hden="Jet_"+DataEra+"_eff_B_denom";
    else if(hnum.Contains("_C_")) hden="Jet_"+DataEra+"_eff_C_denom";
    else hden="Jet_"+DataEra+"_eff_Light_denom";

    this_hist->Divide(this_hist,map_hist_mcjet[hden],1.,1.,"b");
    map_hist_mcjet[hnum]=this_hist;
    this_hist->SetDirectory(0);
    cout<<"[MCCorrection::SetupMCJetTagEff] setting "<<hnum<<endl;
  }
  //--secondary mceff file
  TString mcjetpath2=datapath+"/"+DataEra+"/BTag/"+_btagmceff_filename2;
  cout << "[jhchoi]mcjetpath2----->" << mcjetpath2 << endl;
  ifstream fcheck2(mcjetpath2);
  if(!fcheck2.good()){
    cout<<"[MCCorrection::SetupMCJetTagEff] no "+mcjetpath2<<endl;
    return;
  }

  
  TFile fmcjet2(mcjetpath2);
  // Denominator histogram setup first
  for(unsigned int i=0; i<jfs.size(); i++){
    TString hden="Jet_"+DataEra+"_eff_"+jfs.at(i)+"_denom";
    TH2F* this_hist=(TH2F*)fmcjet2.Get(hden);
    map_hist_mcjet2[hden]=this_hist;
    this_hist->SetDirectory(0);
    cout<<"[MCCorrection::SetupMCJetTagEff]2nd mceff setting "<<hden<<endl;
  }
  // Numerator histogram setup and divided using "binomial option"
  for(const auto& obj:*(fmcjet2.GetListOfKeys())){
    TH2F* this_hist=(TH2F*)((TKey*)obj)->ReadObj();
    TString hnum=this_hist->GetName();
    if(!hnum.Contains("num")) continue;
    TString hden="";
    if(hnum.Contains("_B_")) hden="Jet_"+DataEra+"_eff_B_denom";
    else if(hnum.Contains("_C_")) hden="Jet_"+DataEra+"_eff_C_denom";
    else hden="Jet_"+DataEra+"_eff_Light_denom";

    this_hist->Divide(this_hist,map_hist_mcjet2[hden],1.,1.,"b");
    map_hist_mcjet2[hnum]=this_hist;
    this_hist->SetDirectory(0);
    cout<<"[MCCorrection::SetupMCJetTagEff] setting "<<hnum<<endl;
  }
  
}



//---DO NOT USE SetupMCJetTagEffWithAsym. it is outdated
void MCCorrection::SetupMCJetTagEffWithAsym(TString _btagmceff_filename){
  cout<<"[MCCorrection::SetupMCJetTagEffWithAsym] setting MCJetTagEff with dasym"<<endl;
  cout << "_btagmceff_filename=" << _btagmceff_filename << endl;
  
  TString default_btageff_file="MeasureJetTaggingEfficiency_TTLL_TTLJ_hadded.root";
  TString datapath=getenv("DATA_DIR");
  
  if(_btagmceff_filename==""){
    cout << "[jhchoi]Use default btag mc eff---> No dAsym!!!" << endl;
    _btagmceff_filename=default_btageff_file;
    SetupMCJetTagEff(_btagmceff_filename);
    use_dasym=false;
    return;
  }
  else{
    TString mcjetpath1=datapath+"/"+DataEra+"/BTagWithAsym/"+_btagmceff_filename;
    cout << "[jhchoi]Use  btag mc eff-->" << mcjetpath1 << endl;
    ifstream fcheck1(mcjetpath1);
    if(!fcheck1.good()){
      cout << "[jhchoi]FAIL!!! to load  btag mc eff-->" << mcjetpath1 << endl;
      cout << "Use default file --> No dAsym!!" << endl;
      _btagmceff_filename=default_btageff_file;
      use_dasym=false;
      SetupMCJetTagEff(_btagmceff_filename);
      return;
    }
  }

  use_dasym=true;
  TString mcjetpath=datapath+"/"+DataEra+"/BTagWithAsym/"+_btagmceff_filename;
  cout << "[jhchoi]mcjetpath----->" << mcjetpath << endl;
  ifstream fcheck(mcjetpath);
  if(!fcheck.good()){
    cout<<"[MCCorrection::SetupMCJetTagEff] no "+mcjetpath<<endl;
    return;
  }
  TFile fmcjet(mcjetpath);
  // Denominator histogram setup first
  vector<TString> jfs = {"Bminus","Bplus","B", "C", "Light"};
  for(unsigned int i=0; i<jfs.size(); i++){
    TString hden="Jet_"+DataEra+"_eff_"+jfs.at(i)+"_denom";
    TH2F* this_hist=(TH2F*)fmcjet.Get(hden);
    map_hist_mcjet[hden]=this_hist;
    this_hist->SetDirectory(0);
    cout<<"[MCCorrection::SetupMCJetTagEff] setting "<<hden<<endl;
  }
  // Numerator histogram setup and divided using "binomial option"
  for(const auto& obj:*(fmcjet.GetListOfKeys())){
    TH2F* this_hist=(TH2F*)((TKey*)obj)->ReadObj();
    TString hnum=this_hist->GetName();
    if(!hnum.Contains("num")) continue;
    TString hden="";
    if(hnum.Contains("_B_")) hden="Jet_"+DataEra+"_eff_B_denom";
    else if(hnum.Contains("_Bminus_")) hden="Jet_"+DataEra+"_eff_Bminus_denom";
    else if(hnum.Contains("_Bplus_")) hden="Jet_"+DataEra+"_eff_Bplus_denom";
    else if(hnum.Contains("_C_")) hden="Jet_"+DataEra+"_eff_C_denom";
    else hden="Jet_"+DataEra+"_eff_Light_denom";

    this_hist->Divide(this_hist,map_hist_mcjet[hden],1.,1.,"b");
    map_hist_mcjet[hnum]=this_hist;
    this_hist->SetDirectory(0);
    cout<<"[MCCorrection::SetupMCJetTagEff] setting "<<hnum<<endl;
  }
}


double MCCorrection::GetMCJetTagEff(JetTagging::Tagger tagger, JetTagging::WP wp, int JetFlavor, double JetPt, double JetEta, int sys){

  if(IsDATA) return 1.;

  if(JetPt<20) JetPt = 20.;
  if(JetPt>=1000.) JetPt = 999.;
  if(JetEta>=2.5) JetEta = 2.49;
  if(JetEta<-2.5) JetEta = -2.5;

  TString jf = "";
  if(JetFlavor == 5) jf = "B";
  else if(JetFlavor == 4) jf = "C";
  else if(JetFlavor == 0) jf = "Light";
  else{
    cout<<"[MCCorrection::GetMCJetTagEff] no JetFlavor"<<endl;
    exit(EXIT_FAILURE);
  }

  double value = 1., error = 0., out = 1.;
  TString hnum="Jet_"+DataEra+"_"+JetTagging::TaggerToString(tagger)+"_"+JetTagging::WPToString(wp)+"_eff_"+jf+"_num";
  TH2F *this_hist = map_hist_mcjet[hnum];
  int this_bin = this_hist->FindBin(fabs(JetEta),JetPt);
  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  out = value+double(sys)*error;
  //if(out<=0.) out = 1E-10;
  //if(out>=1.) out = 1.-1E-10;
  //jhchoi
  //if(out<=0.) out = -999.;
  //if(out>=1.) out = 999.;
  if(out<=0. || out>=1.){
    TH2F *this_hist2 = map_hist_mcjet2[hnum];
    //int this_bin2 = this_hist2->FindBin(fabs(JetEta),JetPt);
    value = this_hist2->GetBinContent(this_bin);
    error = this_hist2->GetBinError(this_bin);
    out = value+double(sys)*error;

  }
  if(out<=0.) out = 1E-10;
  if(out>=1.) out = 1.-1E-10;                                                                                                                                                                                                             

  return out;
}


//jhchoi
double MCCorrection::GetMCJetTagEffWithAsym(JetTagging::Tagger tagger, JetTagging::WP wp, int JetPartonFlavour ,int JetHadronFlavour, double JetPt, double JetEta, int sys){
  //outdated
  if(IsDATA) return 1.;

  if(JetPt<20) JetPt = 20.;
  if(JetPt>=1000.) JetPt = 999.;
  if(JetEta>=2.5) JetEta = 2.49;
  if(JetEta<-2.5) JetEta = -2.5;

  TString jf = "";
  if(JetHadronFlavour == 5){
    if(JetPartonFlavour == 5){
      jf = "Bminus";
    }else if(JetPartonFlavour == -5 ){
      jf = "Bplus";
    }else{
      jf = "B";
    }
    
  }
  else if(JetHadronFlavour == 4) jf = "C";
  else if(JetHadronFlavour == 0) jf = "Light";
  else{
    cout<<"[MCCorrection::GetMCJetTagEff] no JetHadronFlavour"<<endl;
    exit(EXIT_FAILURE);
  }
  //cout << "jf=" << jf << endl;
  double value = 1., error = 0., out = 1.;
  TString hnum="Jet_"+DataEra+"_"+JetTagging::TaggerToString(tagger)+"_"+JetTagging::WPToString(wp)+"_eff_"+jf+"_num";
  TH2F *this_hist = map_hist_mcjet[hnum];
  int this_bin = this_hist->FindBin(fabs(JetEta),JetPt);
  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  out = value+double(sys)*error;
  if(out<=0.) out = 1E-10;
  if(out>=1.) out = 1.-1E-10;
  return out;
}


double MCCorrection::GetBTaggingReweight_1a(const vector<Jet>& jets, JetTagging::Parameters jtp, string Syst, int iptbinsys, int ietabinsys){
  //Syst. usage ex.: "SystUpHTag"(all component variation for heavy flav(b,c).), 
  //                 "SystUpHTagCorr"(variation of heavy flav(b,c) sf only for yearly correlated components)
  //change H->L for light flav., Up->Down for downward variation, Corr->UnCorr for yearly independent components
  
  //jhchoi
  //bTagChargeAsymFactor -> partonFlavour==5 || -5 and hadronFlavour==5
  //global var -> use_dasym(MC bTag with parton+-5 origin)
  if(IsDATA) return 1.;


  TString SystStr(Syst);
  double Prob_MC(1.), Prob_DATA(1.), SF(1.);
  bool Syst_HTag=false, Syst_LTag=false; int SystDir=0, CorrType=0;
  string SystKey;
  if(SystStr.Contains("Syst")){
    if     (SystStr.Contains("HTag")) Syst_HTag=true;    
    else if(SystStr.Contains("LTag")) Syst_LTag=true;
    if     (SystStr.Contains("Up")  ) SystDir= 1;
    else if(SystStr.Contains("Down")) SystDir=-1;
    if     (SystStr.Contains("UnCorr")) CorrType=-1;
    else if(SystStr.Contains("Corr"))   CorrType= 1;
    if(SystDir==0){ cout<<"SystStr in not correct form"<<endl; exit(ENODATA); }
    if(!(Syst_HTag or Syst_LTag)){ cout<<"SystMode but no H/L mode assigned"<<endl; exit(ENODATA); }
  }else if(SystStr.Contains("dAsym")){
    if     (SystStr.Contains("Up")  ) SystDir= 1;
    else if(SystStr.Contains("Down")) SystDir=-1;
  }

  for(unsigned int i=0; i<jets.size(); i++){
    int JetHadFlav = jets.at(i).hadronFlavour();
    bool ApplySyst=false;
    if     (Syst_HTag && (JetHadFlav==4 or JetHadFlav==5)){ ApplySyst=true; }
    else if(Syst_LTag && (JetHadFlav==0                 )){ ApplySyst=true; }

    if     (ApplySyst && CorrType==0) SystKey=SystDir>0? "up":"down";
    else if(ApplySyst && CorrType >0) SystKey=SystDir>0? "up_correlated":"down_correlated";
    else if(ApplySyst && CorrType <0) SystKey=SystDir>0? "up_uncorrelated":"down_uncorrelated";
    else                              SystKey="central";

    ///need to fix to one with parton Flavour
    //double this_MC_Eff = use_dasym ? GetMCJetTagEffWithAsym(jtp.j_Tagger, jtp.j_WP, jets.at(i).partonFlavour(),jets.at(i).hadronFlavour(), jets.at(i).Pt(), jets.at(i).Eta())
    //  : GetMCJetTagEff(jtp.j_Tagger, jtp.j_WP, jets.at(i).hadronFlavour(), jets.at(i).Pt(), jets.at(i).Eta());
    double this_MC_Eff = GetMCJetTagEff(jtp.j_Tagger, jtp.j_WP, jets.at(i).hadronFlavour(), jets.at(i).Pt(), jets.at(i).Eta());
    double this_SF = GetJetTaggingSF(jtp,
                                     jets.at(i).hadronFlavour(),
                                     jets.at(i).Pt(),
                                     jets.at(i).Eta(),
                                     jets.at(i).GetTaggerResult(jtp.j_Tagger),
                                     SystKey );


    
    //jhchoi
    double this_dAsym_SF=0.;
    if(use_dasym) this_dAsym_SF=GetJetTaggingSF_dAsymCharge(jtp,
						     jets.at(i).partonFlavour(),
						     jets.at(i).hadronFlavour(),
						     jets.at(i).Pt(),
						     jets.at(i).Eta(),
							    SystDir,
							    iptbinsys,
							    ietabinsys
						     );

    if(fabs(this_dAsym_SF)>=1) this_dAsym_SF=0.;
    double this_DATA_Eff = this_MC_Eff*this_SF*(1.+this_dAsym_SF);
    
    bool isTagged = jets.at(i).GetTaggerResult(jtp.j_Tagger) > GetJetTaggingCutValue(jtp.j_Tagger, jtp.j_WP);


    if(isTagged){
      //Prob_MC *= this_MC_Eff;
      //Prob_DATA *= this_DATA_Eff;
      Prob_DATA=Prob_DATA*this_SF*(1.+this_dAsym_SF);//jhchoi
    }
    else{
      Prob_MC *= 1.-this_MC_Eff;
      Prob_DATA *= 1.-this_DATA_Eff;
    }//

  }//end of jet loop

  if(Prob_MC>0. && Prob_DATA>0.) SF=Prob_DATA/Prob_MC;
  else SF=0.;

  return SF;
}

double MCCorrection::GetBTaggingReweight_1d(const vector<Jet>& jets, JetTagging::Parameters jtp, string Syst){

  if(IsDATA) return 1.;

  if(jtp.j_MeasurmentType_Light!=JetTagging::iterativefit || 
     jtp.j_MeasurmentType_Heavy!=JetTagging::iterativefit){
    cout << "[MCCorrection::GetBTaggingReweight_1d] This method only works for iterativefit method" << endl;
    cout << "[MCCorrection::GetBTaggingReweight_1d] jtp.j_MeasurmentType_Light = " << jtp.j_MeasurmentType_Light << endl;
    cout << "[MCCorrection::GetBTaggingReweight_1d] jtp.j_MeasurmentType_Heavy = " << jtp.j_MeasurmentType_Heavy << endl;
    exit(ENODATA);
    return 1.;
  }

  double rew(1.);

  for(unsigned int i=0; i<jets.size(); i++){

    int abs_hadFlavour = abs(jets.at(i).hadronFlavour());
    TString tmp_Syst(Syst);

/*
    systvec_L = {"up_hf","down_hf","up_jes","down_jes","up_lfstats1","down_lfstats1","up_lfstats2","down_lfstats2"};
    systvec_C = {"up_cferr1","down_cferr1","up_cferr2","down_cferr2"};
    systvec_B = {"up_hfstats1","down_hfstats1","up_hfstats2","down_hfstats2","up_lf","down_lf","up_jes","down_jes"};
*/

    bool GoodSyst = false;
    if(abs_hadFlavour==5){
      if(      tmp_Syst.Contains(TRegexp("hfstats[1-2]$")) ) GoodSyst = true;
      else if( tmp_Syst.Contains(TRegexp("lf$"))           ) GoodSyst = true;
      else if( tmp_Syst.Contains(TRegexp("jes$"))          ) GoodSyst = true;
    }
    else if(abs_hadFlavour==4){
      if(      tmp_Syst.Contains(TRegexp("cferr[1-2]$"))   ) GoodSyst = true;
    }
    else{
      if(      tmp_Syst.Contains(TRegexp("hf$")) )           GoodSyst = true;
      else if( tmp_Syst.Contains(TRegexp("jes$")) )          GoodSyst = true;
      else if( tmp_Syst.Contains(TRegexp("lfstats[1-2]$")) ) GoodSyst = true;
    }

    if(!GoodSyst) tmp_Syst = "central";

    double this_SF = GetJetTaggingSF(jtp,
                                     jets.at(i).hadronFlavour(),
                                     jets.at(i).Pt(),
                                     jets.at(i).Eta(),
                                     jets.at(i).GetTaggerResult(jtp.j_Tagger),
                                     string(tmp_Syst) );
    rew *= this_SF;
  }

  return rew;

}

bool MCCorrection::IsBTagged_2a(JetTagging::Parameters jtp, const Jet& jet, string Syst){

  double this_discr = jet.GetTaggerResult(jtp.j_Tagger);
  double cutValue = GetJetTaggingCutValue(jtp.j_Tagger, jtp.j_WP);

  bool isBTagged = this_discr > cutValue;

  if(IsDATA) return isBTagged;

  //==== Set seed
  unsigned int runNum_uint  = static_cast <unsigned int> (run);
  unsigned int lumiNum_uint = static_cast <unsigned int> (lumi);
  unsigned int evNum_uint   = static_cast <unsigned int> (event);
  unsigned int jet0eta = uint32_t(fabs(jet.Eta())/0.01);
  int m_nomVar=1;
  std::uint32_t seed = jet0eta + m_nomVar + (lumiNum_uint<<10) + (runNum_uint<<20) + evNum_uint;

  TRandom3 rand_(seed);

  bool newBTag = isBTagged;

  //=== Get SF
  double Btag_SF =  GetJetTaggingSF(jtp,
                                    jet.hadronFlavour(),
                                    jet.Pt(),
                                    jet.Eta(),
                                    jet.GetTaggerResult(jtp.j_Tagger),
                                    Syst );


  if(Btag_SF == 1) return newBTag; //no correction needed

  //=== throw random number to apply correction
  float coin = rand_.Uniform(1.);
  if(Btag_SF > 1){
    //=== use this if SF>1

    if( !isBTagged ) {

      double Btag_eff = GetMCJetTagEff(jtp.j_Tagger, jtp.j_WP, jet.hadronFlavour(), jet.Pt(), jet.Eta());
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

