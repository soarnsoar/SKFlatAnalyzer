#include "BBbarRecoTMVA.h"


BBbarRecoTMVA::BBbarRecoTMVA(){//FYI : bottomness = -nb
  //Set Hadron PID vector with nb=+1
  initTMVAmodel_odd_pos();
  initTMVAmodel_even_pos();
  initTMVAmodel_odd_neg();
  initTMVAmodel_even_neg();


  doDebug=false;

  //-----Lepton Cut----//
  MuonCut_v1p0.P_JetRest_min=0.7;
  MuonCut_v1p0.P_JetRest_max=3;
  MuonCut_v1p0.dR_l_bj_min=-1;
  MuonCut_v1p0.dR_l_bj_max=0.4;
  MuonCut_v1p0.reltrkiso_min=-1;
  MuonCut_v1p0.reltrkiso_max=2.5;
  MuonCut_v1p0.nsip3d_min=-1;
  MuonCut_v1p0.nsip3d_max=3;

  ElectronCut_v1p0.P_JetRest_min=0.7;
  ElectronCut_v1p0.P_JetRest_max=3;
  ElectronCut_v1p0.dR_l_bj_min=-1;
  ElectronCut_v1p0.dR_l_bj_max=0.4;
  ElectronCut_v1p0.reltrkiso_min=-1;
  ElectronCut_v1p0.reltrkiso_max=2.5;
  ElectronCut_v1p0.nsip3d_min=-1;
  ElectronCut_v1p0.nsip3d_max=3;
  ElectronCut_v1p0.bool_IsGsfCtfScPixChargeConsistent=true;

  MuonCut_apply=MuonCut_v1p0;
  ElectronCut_apply=ElectronCut_v1p0;


  //jhchoi_newtree=new TTree("dummyTree1","dummyTree1");
  //jhchoi_newtree2=new TTree("dummyTree2","dummyTree2");
  //jhchoi_newtree3=new TTree("dummyTree3","dummyTree3");
  //jhchoi_newtree4=new TTree("dummyTree4","dummyTree4");


}

void BBbarRecoTMVA::initTMVAmodel_odd_pos(){
  double x[61]={0.0, 0.103491806177544, 0.1306782523118751, 0.15832863097409583, 0.18811309926460876, 0.21947493814994634, 0.2505584175185501, 0.2782087961807709, 0.30084870354178384, 0.3178286340625435, 0.33425184554983567, 0.34668523729727724, 0.3571701124275824, 0.3674694145467317, 0.3767480651045239, 0.38537721012327064, 0.3937279956252836, 0.40115091607151737, 0.408666623023329, 0.4154400379305173, 0.42100722826519266, 0.4268527781166017, 0.43223439544012116, 0.4374304397524848, 0.4425336975592705, 0.44828646090510166, 0.453853651239777, 0.4594208415744523, 0.4649880319091276, 0.4718542333218938, 0.4768183113703126, 0.48178238941873147, 0.48846301782034185, 0.49523643272753015, 0.5018242746235626, 0.5085049030251729, 0.5161133964825626, 0.5249281145124651, 0.533371686520056, 0.5423719775611144, 0.552300133657952, 0.5634345143273027, 0.575032827524543, 0.589229162877965, 0.6046317228039, 0.6210549342911922, 0.6376637187896402, 0.655757087377335, 0.6718091528423155, 0.6889746563742309, 0.70910932808464, 0.7306357973787179, 0.7529973452229971, 0.7772146231788347, 0.8027309122127632, 0.8308452234028735, 0.8617431297603215, 0.8900430139615877, 0.914631437939737, 0.9369001992784383, 1.0};
  double y[61]={-1.0, -0.9666666666666667, -0.9333333333333333, -0.9, -0.8666666666666667, -0.8333333333333334, -0.8, -0.7666666666666666, -0.7333333333333334, -0.7, -0.6666666666666667, -0.6333333333333333, -0.6, -0.5666666666666667, -0.5333333333333333, -0.5, -0.4666666666666667, -0.43333333333333335, -0.4, -0.3666666666666667, -0.33333333333333337, -0.30000000000000004, -0.2666666666666667, -0.23333333333333328, -0.19999999999999996, -0.16666666666666663, -0.1333333333333333, -0.09999999999999998, -0.06666666666666665, -0.033333333333333326, 0.0, 0.03333333333333344, 0.06666666666666665, 0.10000000000000009, 0.1333333333333333, 0.16666666666666674, 0.19999999999999996, 0.2333333333333334, 0.2666666666666666, 0.30000000000000004, 0.33333333333333326, 0.3666666666666667, 0.3999999999999999, 0.43333333333333335, 0.46666666666666656, 0.5, 0.5333333333333334, 0.5666666666666667, 0.6000000000000001, 0.6333333333333333, 0.6666666666666667, 0.7, 0.7333333333333334, 0.7666666666666666, 0.8, 0.8333333333333333, 0.8666666666666667, 0.8999999999999999, 0.9333333333333333, 0.9666666666666666, 1.0};
  tgr_odd_pos=new TGraph(61,x,y);


  TString xmlfile="/data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__5000__1000__10__0.2/odd_evt_pos/TMVAClassification_DNN.weights.xml";
  ///data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/nominal_odd_evt/TMVAClassification_DNN.weights.xml";
  ///data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/switch_even_evt
  cout << "define tmvareader"<< endl;
  myreader_odd_pos=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_odd_pos->AddVariable("belectron2_nsip3d",&belectron2_nsip3d);
  myreader_odd_pos->AddVariable("belectron2_p_jetrestf",&belectron2_p_jetrestf);
  myreader_odd_pos->AddVariable("bjet_eta",&bjet_eta);
  myreader_odd_pos->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_odd_pos->AddVariable("bmuon1_charge",&bmuon1_charge_float);
  myreader_odd_pos->AddVariable("belectron2_IsGsfCtfScPixChargeConsistent",&belectron2_IsGsfCtfScPixChargeConsistent_float);
  myreader_odd_pos->AddVariable("bmuon2_reliso",&bmuon2_reliso);
  myreader_odd_pos->AddVariable("bmuon2_nsip3d",&bmuon2_nsip3d);
  myreader_odd_pos->AddVariable("belectron1_pt",&belectron1_pt);
  myreader_odd_pos->AddVariable("n_bmuon",&n_bmuon_float);
  myreader_odd_pos->AddVariable("belectron2_pt",&belectron2_pt);
  myreader_odd_pos->AddVariable("bmuon1_dR_l_j",&bmuon1_dR_l_j);
  myreader_odd_pos->AddVariable("belectron2_dR_l_j",&belectron2_dR_l_j);
  myreader_odd_pos->AddVariable("belectron1_p_jetrestf",&belectron1_p_jetrestf);
  myreader_odd_pos->AddVariable("bjet_DeepJet_CvsB",&bjet_DeepJet_CvsB);
  myreader_odd_pos->AddVariable("belectron1_ptwrtbjet",&belectron1_ptwrtbjet);
  myreader_odd_pos->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader_odd_pos->AddVariable("bjet_DeepJet_CvsL",&bjet_DeepJet_CvsL);
  myreader_odd_pos->AddVariable("bmuon2_ptwrtbjet",&bmuon2_ptwrtbjet);
  myreader_odd_pos->AddVariable("belectron1_dR_l_j",&belectron1_dR_l_j);
  myreader_odd_pos->AddVariable("belectron1_reltrkiso",&belectron1_reltrkiso);
  myreader_odd_pos->AddVariable("belectron2_charge",&belectron2_charge_float);
  myreader_odd_pos->AddVariable("bmuon2_phi",&bmuon2_phi);
  myreader_odd_pos->AddVariable("bjet_phi",&bjet_phi);
  myreader_odd_pos->AddVariable("belectron2_ptwrtbjet",&belectron2_ptwrtbjet);
  myreader_odd_pos->AddVariable("belectron2_elecalclusteriso",&belectron2_elecalclusteriso);
  myreader_odd_pos->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader_odd_pos->AddVariable("belectron1_nsip3d",&belectron1_nsip3d);
  myreader_odd_pos->AddVariable("belectron1_reliso",&belectron1_reliso);
  myreader_odd_pos->AddVariable("bjet_charge",&bjet_charge);
  myreader_odd_pos->AddVariable("bmuon1_p_jetrestf",&bmuon1_p_jetrestf);
  myreader_odd_pos->AddVariable("bmuon2_charge",&bmuon2_charge_float);
  myreader_odd_pos->AddVariable("bmuon1_reltrkiso",&bmuon1_reltrkiso);
  myreader_odd_pos->AddVariable("bmuon1_reliso",&bmuon1_reliso);
  myreader_odd_pos->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  myreader_odd_pos->AddVariable("belectron1_charge",&belectron1_charge_float);
  myreader_odd_pos->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader_odd_pos->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_odd_pos->AddVariable("bjet_DeepJet",&bjet_DeepJet);
  myreader_odd_pos->AddVariable("bmuon1_pt",&bmuon1_pt);
  myreader_odd_pos->AddVariable("bmuon2_reltrkiso",&bmuon2_reltrkiso);
  myreader_odd_pos->AddVariable("bmuon2_p_jetrestf",&bmuon2_p_jetrestf);
  myreader_odd_pos->AddVariable("belectron2_reliso",&belectron2_reliso);
  myreader_odd_pos->AddVariable("belectron1_IsGsfCtfScPixChargeConsistent",&belectron1_IsGsfCtfScPixChargeConsistent_float);
  myreader_odd_pos->AddVariable("belectron2_reltrkiso",&belectron2_reltrkiso);
  myreader_odd_pos->AddVariable("bmuon2_pt",&bmuon2_pt);
  myreader_odd_pos->AddVariable("bjet_pt",&bjet_pt);
  myreader_odd_pos->AddVariable("bmuon1_phi",&bmuon1_phi);
  myreader_odd_pos->AddVariable("belectron1_phi",&belectron1_phi);
  myreader_odd_pos->AddVariable("n_belectron",&n_belectron_float);
  myreader_odd_pos->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader_odd_pos->AddVariable("belectron2_phi",&belectron2_phi);
  myreader_odd_pos->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_odd_pos->AddVariable("bmuon1_ptwrtbjet",&bmuon1_ptwrtbjet);
  myreader_odd_pos->AddVariable("bmuon1_nsip3d",&bmuon1_nsip3d);
  myreader_odd_pos->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_odd_pos->AddVariable("belectron1_elecalclusteriso",&belectron1_elecalclusteriso);  
  myreader_odd_pos->AddVariable("bmuon2_dR_l_j",&bmuon2_dR_l_j);
  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_odd_pos->BookMVA("PyKeras::DNN",xmlfile);
  //Float_t ret=myreader->EvaluateMVA("PyKeras::DNN");


  
}



void BBbarRecoTMVA::initTMVAmodel_even_pos(){
  double x[61]={0.0, 0.20567461855162333, 0.2212976963422804, 0.23395528251526643, 0.24639588149671554, 0.25927045486123845, 0.2737362676303654, 0.28856372571872047, 0.3023785769132366, 0.31380656900084686, 0.3237879798115444, 0.33304609998378565, 0.34208723296448995, 0.3499711009236641, 0.3574933235636101, 0.36414759743740843, 0.37094652943889805, 0.3773114870573139, 0.3827361668457365, 0.38830550476185033, 0.3949597786356487, 0.39995048404099753, 0.4052305057017288, 0.41036586923476887, 0.416079865278574, 0.4221555066416073, 0.4278695026854124, 0.43257089183537867, 0.4379955716238012, 0.44450518736990835, 0.4597666198413372, 0.47502805231276607, 0.4814653389950275, 0.48833660006036284, 0.49600348082800005, 0.5026577547017984, 0.5097460029586707, 0.5163279477686233, 0.5224759181955023, 0.5293471792608375, 0.5369417309646292, 0.5456935476899509, 0.5540113900321989, 0.562690877693675, 0.5717320106743793, 0.5809901308466205, 0.5913331869765464, 0.5999403455741767, 0.6086198332356529, 0.6181672696632767, 0.6274977188993636, 0.6371898134546785, 0.6478221858399869, 0.659250177927597, 0.6725587256751938, 0.6895560556789179, 0.7106761423218432, 0.7338214427524462, 0.7591366150984182, 0.7937099076166315, 1.0};
  double y[61]={-1.0, -0.9666666666666667, -0.9333333333333333, -0.9, -0.8666666666666667, -0.8333333333333334, -0.8, -0.7666666666666666, -0.7333333333333334, -0.7, -0.6666666666666667, -0.6333333333333333, -0.6, -0.5666666666666667, -0.5333333333333333, -0.5, -0.4666666666666667, -0.43333333333333335, -0.4, -0.3666666666666667, -0.33333333333333337, -0.30000000000000004, -0.2666666666666667, -0.23333333333333328, -0.19999999999999996, -0.16666666666666663, -0.1333333333333333, -0.09999999999999998, -0.06666666666666665, -0.033333333333333326, 0.0, 0.03333333333333344, 0.06666666666666665, 0.10000000000000009, 0.1333333333333333, 0.16666666666666674, 0.19999999999999996, 0.2333333333333334, 0.2666666666666666, 0.30000000000000004, 0.33333333333333326, 0.3666666666666667, 0.3999999999999999, 0.43333333333333335, 0.46666666666666656, 0.5, 0.5333333333333334, 0.5666666666666667, 0.6000000000000001, 0.6333333333333333, 0.6666666666666667, 0.7, 0.7333333333333334, 0.7666666666666666, 0.8, 0.8333333333333333, 0.8666666666666667, 0.8999999999999999, 0.9333333333333333, 0.9666666666666666, 1.0};
  tgr_even_pos=new TGraph(61,x,y);
  TString xmlfile="/data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__5000__1000__10__0.2/even_evt_pos/TMVAClassification_DNN.weights.xml";
  ///data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/nominal_odd_evt/TMVAClassification_DNN.weights.xml";
  ///data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/switch_even_evt
  cout << "define tmvareader"<< endl;
  myreader_even_pos=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_even_pos->AddVariable("belectron2_nsip3d",&belectron2_nsip3d);
  myreader_even_pos->AddVariable("belectron2_p_jetrestf",&belectron2_p_jetrestf);
  myreader_even_pos->AddVariable("bjet_eta",&bjet_eta);
  myreader_even_pos->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_even_pos->AddVariable("bmuon1_charge",&bmuon1_charge_float);
  myreader_even_pos->AddVariable("belectron2_IsGsfCtfScPixChargeConsistent",&belectron2_IsGsfCtfScPixChargeConsistent_float);
  myreader_even_pos->AddVariable("bmuon2_reliso",&bmuon2_reliso);
  myreader_even_pos->AddVariable("bmuon2_nsip3d",&bmuon2_nsip3d);
  myreader_even_pos->AddVariable("belectron1_pt",&belectron1_pt);
  myreader_even_pos->AddVariable("n_bmuon",&n_bmuon_float);
  myreader_even_pos->AddVariable("belectron2_pt",&belectron2_pt);
  myreader_even_pos->AddVariable("bmuon1_dR_l_j",&bmuon1_dR_l_j);
  myreader_even_pos->AddVariable("belectron2_dR_l_j",&belectron2_dR_l_j);
  myreader_even_pos->AddVariable("belectron1_p_jetrestf",&belectron1_p_jetrestf);
  myreader_even_pos->AddVariable("bjet_DeepJet_CvsB",&bjet_DeepJet_CvsB);
  myreader_even_pos->AddVariable("belectron1_ptwrtbjet",&belectron1_ptwrtbjet);
  myreader_even_pos->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader_even_pos->AddVariable("bjet_DeepJet_CvsL",&bjet_DeepJet_CvsL);
  myreader_even_pos->AddVariable("bmuon2_ptwrtbjet",&bmuon2_ptwrtbjet);
  myreader_even_pos->AddVariable("belectron1_dR_l_j",&belectron1_dR_l_j);
  myreader_even_pos->AddVariable("belectron1_reltrkiso",&belectron1_reltrkiso);
  myreader_even_pos->AddVariable("belectron2_charge",&belectron2_charge_float);
  myreader_even_pos->AddVariable("bmuon2_phi",&bmuon2_phi);
  myreader_even_pos->AddVariable("bjet_phi",&bjet_phi);
  myreader_even_pos->AddVariable("belectron2_ptwrtbjet",&belectron2_ptwrtbjet);
  myreader_even_pos->AddVariable("belectron2_elecalclusteriso",&belectron2_elecalclusteriso);
  myreader_even_pos->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader_even_pos->AddVariable("belectron1_nsip3d",&belectron1_nsip3d);
  myreader_even_pos->AddVariable("belectron1_reliso",&belectron1_reliso);
  myreader_even_pos->AddVariable("bjet_charge",&bjet_charge);
  myreader_even_pos->AddVariable("bmuon1_p_jetrestf",&bmuon1_p_jetrestf);
  myreader_even_pos->AddVariable("bmuon2_charge",&bmuon2_charge_float);
  myreader_even_pos->AddVariable("bmuon1_reltrkiso",&bmuon1_reltrkiso);
  myreader_even_pos->AddVariable("bmuon1_reliso",&bmuon1_reliso);
  myreader_even_pos->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  myreader_even_pos->AddVariable("belectron1_charge",&belectron1_charge_float);
  myreader_even_pos->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader_even_pos->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_even_pos->AddVariable("bjet_DeepJet",&bjet_DeepJet);
  myreader_even_pos->AddVariable("bmuon1_pt",&bmuon1_pt);
  myreader_even_pos->AddVariable("bmuon2_reltrkiso",&bmuon2_reltrkiso);
  myreader_even_pos->AddVariable("bmuon2_p_jetrestf",&bmuon2_p_jetrestf);
  myreader_even_pos->AddVariable("belectron2_reliso",&belectron2_reliso);
  myreader_even_pos->AddVariable("belectron1_IsGsfCtfScPixChargeConsistent",&belectron1_IsGsfCtfScPixChargeConsistent_float);
  myreader_even_pos->AddVariable("belectron2_reltrkiso",&belectron2_reltrkiso);
  myreader_even_pos->AddVariable("bmuon2_pt",&bmuon2_pt);
  myreader_even_pos->AddVariable("bjet_pt",&bjet_pt);
  myreader_even_pos->AddVariable("bmuon1_phi",&bmuon1_phi);
  myreader_even_pos->AddVariable("belectron1_phi",&belectron1_phi);
  myreader_even_pos->AddVariable("n_belectron",&n_belectron_float);
  myreader_even_pos->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader_even_pos->AddVariable("belectron2_phi",&belectron2_phi);
  myreader_even_pos->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_even_pos->AddVariable("bmuon1_ptwrtbjet",&bmuon1_ptwrtbjet);
  myreader_even_pos->AddVariable("bmuon1_nsip3d",&bmuon1_nsip3d);
  myreader_even_pos->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_even_pos->AddVariable("belectron1_elecalclusteriso",&belectron1_elecalclusteriso);  
  myreader_even_pos->AddVariable("bmuon2_dR_l_j",&bmuon2_dR_l_j);
  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_even_pos->BookMVA("PyKeras::DNN",xmlfile);
  //Float_t ret=myreader->EvaluateMVA("PyKeras::DNN");


  
}


void BBbarRecoTMVA::initTMVAmodel_even_neg(){
  double x[61]={0.0, 0.1108670364981029, 0.15906612356099364, 0.21048444463921664, 0.2612768035477917, 0.30455761642059154, 0.346497081787003, 0.3850384668038971, 0.4191981166332557, 0.45568276880702085, 0.49002126497056453, 0.5164905224299627, 0.5373261203625297, 0.553601136773376, 0.5681771130094635, 0.5801598173998668, 0.5898175194458635, 0.598670412988027, 0.6052877273528766, 0.610921386879708, 0.6158396610697989, 0.6195954340876865, 0.6235300534397592, 0.6270175569563691, 0.6303262141387939, 0.6337242944883112, 0.6365858358352732, 0.6396262235164203, 0.6425771880304748, 0.6457069988787145, 0.650893542570083, 0.6560800862614516, 0.6584945117729508, 0.6607300909502648, 0.6626974006263012, 0.6647541334694301, 0.6670791358138367, 0.6693147149911508, 0.67172914050265, 0.6740541428470566, 0.6763791451914631, 0.6788829938700549, 0.6815656888828318, 0.684784922898164, 0.688451272748959, 0.6922964689339391, 0.6965887809543821, 0.7009705161419176, 0.7063359061674713, 0.7129532205323209, 0.7207330360693738, 0.7302118917811853, 0.7421945961715886, 0.7545349932303621, 0.7694686621348199, 0.785564832211481, 0.8035388887970859, 0.8216023685497834, 0.840649503140499, 0.8628264485794543, 1.0};
  double y[61]={-1.0, -0.9666666666666667, -0.9333333333333333, -0.9, -0.8666666666666667, -0.8333333333333334, -0.8, -0.7666666666666666, -0.7333333333333334, -0.7, -0.6666666666666667, -0.6333333333333333, -0.6, -0.5666666666666667, -0.5333333333333333, -0.5, -0.4666666666666667, -0.43333333333333335, -0.4, -0.3666666666666667, -0.33333333333333337, -0.30000000000000004, -0.2666666666666667, -0.23333333333333328, -0.19999999999999996, -0.16666666666666663, -0.1333333333333333, -0.09999999999999998, -0.06666666666666665, -0.033333333333333326, 0.0, 0.03333333333333344, 0.06666666666666665, 0.10000000000000009, 0.1333333333333333, 0.16666666666666674, 0.19999999999999996, 0.2333333333333334, 0.2666666666666666, 0.30000000000000004, 0.33333333333333326, 0.3666666666666667, 0.3999999999999999, 0.43333333333333335, 0.46666666666666656, 0.5, 0.5333333333333334, 0.5666666666666667, 0.6000000000000001, 0.6333333333333333, 0.6666666666666667, 0.7, 0.7333333333333334, 0.7666666666666666, 0.8, 0.8333333333333333, 0.8666666666666667, 0.8999999999999999, 0.9333333333333333, 0.9666666666666666, 1.0};
  tgr_even_neg=new TGraph(61,x,y);
  TString xmlfile="/data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__5000__1000__10__0.2/even_evt_neg/TMVAClassification_DNN.weights.xml";
  ///data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/nominal_odd_evt/TMVAClassification_DNN.weights.xml";
  ///data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/switch_even_evt
  cout << "define tmvareader"<< endl;
  myreader_even_neg=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_even_neg->AddVariable("belectron2_nsip3d",&belectron2_nsip3d);
  myreader_even_neg->AddVariable("belectron2_p_jetrestf",&belectron2_p_jetrestf);
  myreader_even_neg->AddVariable("bjet_eta",&bjet_eta);
  myreader_even_neg->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_even_neg->AddVariable("bmuon1_charge",&bmuon1_charge_float);
  myreader_even_neg->AddVariable("belectron2_IsGsfCtfScPixChargeConsistent",&belectron2_IsGsfCtfScPixChargeConsistent_float);
  myreader_even_neg->AddVariable("bmuon2_reliso",&bmuon2_reliso);
  myreader_even_neg->AddVariable("bmuon2_nsip3d",&bmuon2_nsip3d);
  myreader_even_neg->AddVariable("belectron1_pt",&belectron1_pt);
  myreader_even_neg->AddVariable("n_bmuon",&n_bmuon_float);
  myreader_even_neg->AddVariable("belectron2_pt",&belectron2_pt);
  myreader_even_neg->AddVariable("bmuon1_dR_l_j",&bmuon1_dR_l_j);
  myreader_even_neg->AddVariable("belectron2_dR_l_j",&belectron2_dR_l_j);
  myreader_even_neg->AddVariable("belectron1_p_jetrestf",&belectron1_p_jetrestf);
  myreader_even_neg->AddVariable("bjet_DeepJet_CvsB",&bjet_DeepJet_CvsB);
  myreader_even_neg->AddVariable("belectron1_ptwrtbjet",&belectron1_ptwrtbjet);
  myreader_even_neg->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader_even_neg->AddVariable("bjet_DeepJet_CvsL",&bjet_DeepJet_CvsL);
  myreader_even_neg->AddVariable("bmuon2_ptwrtbjet",&bmuon2_ptwrtbjet);
  myreader_even_neg->AddVariable("belectron1_dR_l_j",&belectron1_dR_l_j);
  myreader_even_neg->AddVariable("belectron1_reltrkiso",&belectron1_reltrkiso);
  myreader_even_neg->AddVariable("belectron2_charge",&belectron2_charge_float);
  myreader_even_neg->AddVariable("bmuon2_phi",&bmuon2_phi);
  myreader_even_neg->AddVariable("bjet_phi",&bjet_phi);
  myreader_even_neg->AddVariable("belectron2_ptwrtbjet",&belectron2_ptwrtbjet);
  myreader_even_neg->AddVariable("belectron2_elecalclusteriso",&belectron2_elecalclusteriso);
  myreader_even_neg->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader_even_neg->AddVariable("belectron1_nsip3d",&belectron1_nsip3d);
  myreader_even_neg->AddVariable("belectron1_reliso",&belectron1_reliso);
  myreader_even_neg->AddVariable("bjet_charge",&bjet_charge);
  myreader_even_neg->AddVariable("bmuon1_p_jetrestf",&bmuon1_p_jetrestf);
  myreader_even_neg->AddVariable("bmuon2_charge",&bmuon2_charge_float);
  myreader_even_neg->AddVariable("bmuon1_reltrkiso",&bmuon1_reltrkiso);
  myreader_even_neg->AddVariable("bmuon1_reliso",&bmuon1_reliso);
  myreader_even_neg->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  myreader_even_neg->AddVariable("belectron1_charge",&belectron1_charge_float);
  myreader_even_neg->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader_even_neg->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_even_neg->AddVariable("bjet_DeepJet",&bjet_DeepJet);
  myreader_even_neg->AddVariable("bmuon1_pt",&bmuon1_pt);
  myreader_even_neg->AddVariable("bmuon2_reltrkiso",&bmuon2_reltrkiso);
  myreader_even_neg->AddVariable("bmuon2_p_jetrestf",&bmuon2_p_jetrestf);
  myreader_even_neg->AddVariable("belectron2_reliso",&belectron2_reliso);
  myreader_even_neg->AddVariable("belectron1_IsGsfCtfScPixChargeConsistent",&belectron1_IsGsfCtfScPixChargeConsistent_float);
  myreader_even_neg->AddVariable("belectron2_reltrkiso",&belectron2_reltrkiso);
  myreader_even_neg->AddVariable("bmuon2_pt",&bmuon2_pt);
  myreader_even_neg->AddVariable("bjet_pt",&bjet_pt);
  myreader_even_neg->AddVariable("bmuon1_phi",&bmuon1_phi);
  myreader_even_neg->AddVariable("belectron1_phi",&belectron1_phi);
  myreader_even_neg->AddVariable("n_belectron",&n_belectron_float);
  myreader_even_neg->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader_even_neg->AddVariable("belectron2_phi",&belectron2_phi);
  myreader_even_neg->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_even_neg->AddVariable("bmuon1_ptwrtbjet",&bmuon1_ptwrtbjet);
  myreader_even_neg->AddVariable("bmuon1_nsip3d",&bmuon1_nsip3d);
  myreader_even_neg->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_even_neg->AddVariable("belectron1_elecalclusteriso",&belectron1_elecalclusteriso);  
  myreader_even_neg->AddVariable("bmuon2_dR_l_j",&bmuon2_dR_l_j);
  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_even_neg->BookMVA("PyKeras::DNN",xmlfile);
  //Float_t ret=myreader->EvaluateMVA("PyKeras::DNN");


  
}



void BBbarRecoTMVA::initTMVAmodel_odd_neg(){
  double x[61]={0.0, 0.12432412446151733, 0.1451070846539917, 0.16375845918569945, 0.18045588019503783, 0.1971533012043762, 0.211719136552948, 0.2245086505175476, 0.23596592344416809, 0.24795609278598021, 0.25914691750500485, 0.27016011008563234, 0.2795746134206848, 0.28898911675573724, 0.29707137905281067, 0.3048871931422882, 0.31225892688577267, 0.31989710883685296, 0.32691357830354306, 0.3333971513550415, 0.34068006902932735, 0.34671956173483276, 0.35249260623274226, 0.3587097310766449, 0.36448277557455444, 0.3706110843492584, 0.37629531277796935, 0.38153546086068724, 0.38721968928939815, 0.3928151016489105, 0.3955683997940673, 0.39832169793922423, 0.40427237457553095, 0.4100454190734405, 0.4152855671561584, 0.4206145313080749, 0.4265652079443817, 0.43278233278828426, 0.4392659058397827, 0.4454830306836853, 0.45365410904995723, 0.4628021641774139, 0.47319364427365107, 0.48527262968466184, 0.497706879372467, 0.5112069218906554, 0.5278155268307952, 0.5447793960477294, 0.5650294598250122, 0.5831479379415283, 0.6046414266875915, 0.6310197992395782, 0.6576646199991607, 0.6831548318591613, 0.7116647900719146, 0.7434609428450164, 0.7801419794240416, 0.8190434177330321, 0.8543033972048797, 0.8888528481231384, 1.0};
  double y[61]={-1.0, -0.9666666666666667, -0.9333333333333333, -0.9, -0.8666666666666667, -0.8333333333333334, -0.8, -0.7666666666666666, -0.7333333333333334, -0.7, -0.6666666666666667, -0.6333333333333333, -0.6, -0.5666666666666667, -0.5333333333333333, -0.5, -0.4666666666666667, -0.43333333333333335, -0.4, -0.3666666666666667, -0.33333333333333337, -0.30000000000000004, -0.2666666666666667, -0.23333333333333328, -0.19999999999999996, -0.16666666666666663, -0.1333333333333333, -0.09999999999999998, -0.06666666666666665, -0.033333333333333326, 0.0, 0.03333333333333344, 0.06666666666666665, 0.10000000000000009, 0.1333333333333333, 0.16666666666666674, 0.19999999999999996, 0.2333333333333334, 0.2666666666666666, 0.30000000000000004, 0.33333333333333326, 0.3666666666666667, 0.3999999999999999, 0.43333333333333335, 0.46666666666666656, 0.5, 0.5333333333333334, 0.5666666666666667, 0.6000000000000001, 0.6333333333333333, 0.6666666666666667, 0.7, 0.7333333333333334, 0.7666666666666666, 0.8, 0.8333333333333333, 0.8666666666666667, 0.8999999999999999, 0.9333333333333333, 0.9666666666666666, 1.0};
  tgr_odd_neg=new TGraph(61,x,y);

  TString xmlfile="/data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__5000__1000__10__0.2/odd_evt_neg/TMVAClassification_DNN.weights.xml";
  ///data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/nominal_odd_evt/TMVAClassification_DNN.weights.xml";
  ///data6/Users/jhchoi/SKFlatAnalyzers/test/SKFlatAnalyzer/external/TMVA/epoch__batchsize__nlayer__dropout__2000__1000__16__0.1/switch_even_evt
  cout << "define tmvareader"<< endl;
  myreader_odd_neg=new TMVA::Reader("V");
  cout << "add variables"<< endl;
  myreader_odd_neg->AddVariable("belectron2_nsip3d",&belectron2_nsip3d);
  myreader_odd_neg->AddVariable("belectron2_p_jetrestf",&belectron2_p_jetrestf);
  myreader_odd_neg->AddVariable("bjet_eta",&bjet_eta);
  myreader_odd_neg->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_odd_neg->AddVariable("bmuon1_charge",&bmuon1_charge_float);
  myreader_odd_neg->AddVariable("belectron2_IsGsfCtfScPixChargeConsistent",&belectron2_IsGsfCtfScPixChargeConsistent_float);
  myreader_odd_neg->AddVariable("bmuon2_reliso",&bmuon2_reliso);
  myreader_odd_neg->AddVariable("bmuon2_nsip3d",&bmuon2_nsip3d);
  myreader_odd_neg->AddVariable("belectron1_pt",&belectron1_pt);
  myreader_odd_neg->AddVariable("n_bmuon",&n_bmuon_float);
  myreader_odd_neg->AddVariable("belectron2_pt",&belectron2_pt);
  myreader_odd_neg->AddVariable("bmuon1_dR_l_j",&bmuon1_dR_l_j);
  myreader_odd_neg->AddVariable("belectron2_dR_l_j",&belectron2_dR_l_j);
  myreader_odd_neg->AddVariable("belectron1_p_jetrestf",&belectron1_p_jetrestf);
  myreader_odd_neg->AddVariable("bjet_DeepJet_CvsB",&bjet_DeepJet_CvsB);
  myreader_odd_neg->AddVariable("belectron1_ptwrtbjet",&belectron1_ptwrtbjet);
  myreader_odd_neg->AddVariable("bjet_chargedHadronEnergyFraction",&bjet_chargedHadronEnergyFraction);
  myreader_odd_neg->AddVariable("bjet_DeepJet_CvsL",&bjet_DeepJet_CvsL);
  myreader_odd_neg->AddVariable("bmuon2_ptwrtbjet",&bmuon2_ptwrtbjet);
  myreader_odd_neg->AddVariable("belectron1_dR_l_j",&belectron1_dR_l_j);
  myreader_odd_neg->AddVariable("belectron1_reltrkiso",&belectron1_reltrkiso);
  myreader_odd_neg->AddVariable("belectron2_charge",&belectron2_charge_float);
  myreader_odd_neg->AddVariable("bmuon2_phi",&bmuon2_phi);
  myreader_odd_neg->AddVariable("bjet_phi",&bjet_phi);
  myreader_odd_neg->AddVariable("belectron2_ptwrtbjet",&belectron2_ptwrtbjet);
  myreader_odd_neg->AddVariable("belectron2_elecalclusteriso",&belectron2_elecalclusteriso);
  myreader_odd_neg->AddVariable("bjet_chargedEmEnergyFraction",&bjet_chargedEmEnergyFraction);
  myreader_odd_neg->AddVariable("belectron1_nsip3d",&belectron1_nsip3d);
  myreader_odd_neg->AddVariable("belectron1_reliso",&belectron1_reliso);
  myreader_odd_neg->AddVariable("bjet_charge",&bjet_charge);
  myreader_odd_neg->AddVariable("bmuon1_p_jetrestf",&bmuon1_p_jetrestf);
  myreader_odd_neg->AddVariable("bmuon2_charge",&bmuon2_charge_float);
  myreader_odd_neg->AddVariable("bmuon1_reltrkiso",&bmuon1_reltrkiso);
  myreader_odd_neg->AddVariable("bmuon1_reliso",&bmuon1_reliso);
  myreader_odd_neg->AddVariable("bjet_neutralEmEnergyFraction",&bjet_neutralEmEnergyFraction);
  myreader_odd_neg->AddVariable("belectron1_charge",&belectron1_charge_float);
  myreader_odd_neg->AddVariable("bjet_neutralHadronEnergyFraction",&bjet_neutralHadronEnergyFraction);
  myreader_odd_neg->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_odd_neg->AddVariable("bjet_DeepJet",&bjet_DeepJet);
  myreader_odd_neg->AddVariable("bmuon1_pt",&bmuon1_pt);
  myreader_odd_neg->AddVariable("bmuon2_reltrkiso",&bmuon2_reltrkiso);
  myreader_odd_neg->AddVariable("bmuon2_p_jetrestf",&bmuon2_p_jetrestf);
  myreader_odd_neg->AddVariable("belectron2_reliso",&belectron2_reliso);
  myreader_odd_neg->AddVariable("belectron1_IsGsfCtfScPixChargeConsistent",&belectron1_IsGsfCtfScPixChargeConsistent_float);
  myreader_odd_neg->AddVariable("belectron2_reltrkiso",&belectron2_reltrkiso);
  myreader_odd_neg->AddVariable("bmuon2_pt",&bmuon2_pt);
  myreader_odd_neg->AddVariable("bjet_pt",&bjet_pt);
  myreader_odd_neg->AddVariable("bmuon1_phi",&bmuon1_phi);
  myreader_odd_neg->AddVariable("belectron1_phi",&belectron1_phi);
  myreader_odd_neg->AddVariable("n_belectron",&n_belectron_float);
  myreader_odd_neg->AddVariable("bjet_muonEnergyFraction",&bjet_muonEnergyFraction);
  myreader_odd_neg->AddVariable("belectron2_phi",&belectron2_phi);
  myreader_odd_neg->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_odd_neg->AddVariable("bmuon1_ptwrtbjet",&bmuon1_ptwrtbjet);
  myreader_odd_neg->AddVariable("bmuon1_nsip3d",&bmuon1_nsip3d);
  myreader_odd_neg->AddVariable("bmuon2_eta",&bmuon2_eta);
  myreader_odd_neg->AddVariable("belectron1_elecalclusteriso",&belectron1_elecalclusteriso);  
  myreader_odd_neg->AddVariable("bmuon2_dR_l_j",&bmuon2_dR_l_j);
  cout << "setenv"<< endl;
  setenv("KERAS_BACKEND", "tensorflow", true);
  cout << "pyinit"<< endl;
  TMVA::PyMethodBase::PyInitialize();
  cout << "bookmva"<< endl;
  myreader_odd_neg->BookMVA("PyKeras::DNN",xmlfile);
  //Float_t ret=myreader->EvaluateMVA("PyKeras::DNN");


  
}



void BBbarRecoTMVA::InitTreeValues(){
  //-----Variables to Store for Machine Learning------//
  bjet_charge=0.;
  bjet_pt=0.;
  bjet_eta=0.;
  bjet_phi=0.;
  bjet_DeepJet=0.;
  bjet_DeepJet_CvsL=0.;
  bjet_DeepJet_CvsB=0.;
  bjet_chargedHadronEnergyFraction=0.;
  bjet_neutralHadronEnergyFraction=0.;
  bjet_neutralEmEnergyFraction=0.;
  bjet_chargedEmEnergyFraction=0.;
  bjet_muonEnergyFraction=0.;
  //leading bmuon
  bmuon1_pt=0.;
  bmuon1_eta=0.;
  bmuon1_phi=0.;
  bmuon1_ptwrtbjet=0.;
  bmuon1_p_jetrestf=0.;
  bmuon1_dR_l_j=0.;
  bmuon1_nsip3d=0.;
  bmuon1_reltrkiso=0.;
  bmuon1_reliso=0.;
  bmuon1_charge=0.;
  //subleading bmuon
  bmuon2_pt=0.;
  bmuon2_eta=0.;
  bmuon2_phi=0.;
  bmuon2_ptwrtbjet=0.;
  bmuon2_p_jetrestf=0.;
  bmuon2_dR_l_j=0.;
  bmuon2_nsip3d=0.;
  bmuon2_reltrkiso=0.;
  bmuon2_reliso=0.;
  bmuon2_charge=0.;

  n_bmuon=0;
  //leading belectron
  belectron1_pt=0.;
  belectron1_eta=0.;
  belectron1_phi=0.;
  belectron1_ptwrtbjet=0.;
  belectron1_p_jetrestf=0.;
  belectron1_dR_l_j=0.;
  belectron1_nsip3d=0.;
  belectron1_reltrkiso=0.;
  belectron1_elecalclusteriso=0.;
  belectron1_IsGsfCtfScPixChargeConsistent=0;
  belectron1_reliso=0.;
  belectron1_charge=0.;
  //subleading belectron
  belectron2_pt=0.;
  belectron2_eta=0.;
  belectron2_phi=0.;
  belectron2_ptwrtbjet=0.;
  belectron2_p_jetrestf=0.;
  belectron2_dR_l_j=0.;
  belectron2_nsip3d=0.;
  belectron2_reltrkiso=0.;
  belectron2_elecalclusteriso=0.;
  belectron2_IsGsfCtfScPixChargeConsistent=0;
  belectron2_reliso=0.;
  belectron2_charge=0.;
  n_belectron=0;
  //truth
  bjetPartonFlavourCharge=0;
  DNN_odd_pos=0;
  DNN_even_pos=0;
  DNN_odd_neg=0;
  DNN_even_neg=0;
  DNN_b=0;
  DNN_s=0;
}



void BBbarRecoTMVA::initializeAnalyzer(){
  //==== if you use "--userflags RunSyst" with SKFlat.py, HasFlag("RunSyst") will return "true"
  RunSyst = HasFlag("RunSyst");
  cout << "[BBbarRecoTMVA::initializeAnalyzer] RunSyst = " << RunSyst << endl;

  if(IsDATA){
    //ProcessName=DataStream;    
    ProcessName="Data";
  }
  else{
    ProcessName=MCSample;
    if(ProcessName.Contains("DY")){
      ProcessName="DY";
    }
  }
  cout << "[BBbarRecoTMVA::initializeAnalyzer Setting ProcessName = " << ProcessName << endl;


  std::vector<JetTagging::Parameters> jtps;
  //==== If you want to use 1a or 2a method,
  jtps.push_back( JetTagging::Parameters(JetTagging::DeepJet, JetTagging::Tight, JetTagging::incl, JetTagging::comb) );
  //==== set
  mcCorr->SetJetTaggingParameters(jtps);
  jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  //btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);


}

BBbarRecoTMVA::~BBbarRecoTMVA(){

  //==== Destructor of this Analyzer

}

bool BBbarRecoTMVA::Tag_gbToZb(){
  LHEs=GetLHEs();
  BBbarRecoTMVA::myLHE.LHEsize = LHEs.size();  
  myLHE.ngluon_incoming = 0;
  myLHE.nb_incoming = 0;
  myLHE.nb_outgoing = 0;
  myLHE.abs_nb_outgoing = 0;
  myLHE.nparton_outgoing = 0;
  myLHE.evt_nb = 0;
  myLHE.nincoming_b = 0;
  myLHE.nincoming_bbar = 0;

  //for LHE
  //We want event with
  //incoming : 1 g + 1 b
  //outgoing : 1 b , no other partons
  //double LHE_E;
  double LHE_status,LHE_id;
  unsigned int ntau = 0, nmu = 0, nele = 0;
  for(unsigned int i =0; i < myLHE.LHEsize ; i++){
    //LHE_E=LHEs[i].E();
    LHE_status=LHEs[i].Status();
    LHE_id=LHEs[i].ID();
    //LHE_index=LHEs[i].Index();
    //LHE_pt=LHEs[i].Pt();
    //LHE_eta=LHEs[i].Eta();
    //LHE_phi=LHEs[i].Phi();
    if (LHE_status==-1){//if incoming 
      if(LHE_id==5){//if incoming b
	myLHE.evt_nb += 1;
	myLHE.nb_incoming    += 1;
	myLHE.nincoming_b+=1;
      }
      else if(LHE_id==-5){//if bbar
	myLHE.evt_nb += -1;
	myLHE.nb_incoming    += 1;
	myLHE.nincoming_bbar+=1;
      }
      else if(LHE_id==21){//if gluon
	myLHE.ngluon_incoming += 1;
      }
    }//[END]if incoming
    else if (LHE_status==1){//if outgoing
      if (LHE_id==15){
	ntau += 1;
	myLHE.i_lepn = i; 
      }
      else if (LHE_id==-15){
	ntau += 1;
	myLHE.i_lepp = i; 
      }
      else if (LHE_id==13){
	nmu += 1;
	myLHE.i_lepn = i;
      }
      else if (LHE_id==-13){
	nmu += 1;
	myLHE.i_lepp = i;
      }
      else if (LHE_id==11){
	nele += 1;
	myLHE.i_lepn = i;
      }
      else if (LHE_id==-11){
	nele += 1;
	myLHE.i_lepp = i;
      }

      if (abs(LHE_id)==5){
	myLHE.nb_outgoing += 1;
	myLHE.vb=LHEs[i];
	myLHE.nparton_outgoing += 1;	
      }
      else if(
	 abs(LHE_id)>0 
	 &&
	 abs(LHE_id)<5
	 )
	{//if quark
	  myLHE.nparton_outgoing += 1;
	}
      else if (LHE_id == 21){//if gluon
	myLHE.nparton_outgoing += 1;
      }
    }//[END]if outgoing
  }//[END]for each LHE
  //Whether it's a tautau event

  if(myLHE.nincoming_bbar==1){
    //ProcessName="DY_gbToZbbar";
    IncomingPartonTag+="bbar";
  }
  if(myLHE.nincoming_b==1){
    //ProcessName="DY_gbToZb";
    IncomingPartonTag+="bevt";
  }
  if(myLHE.nincoming_b==0 && myLHE.nincoming_bbar==0){
    //ProcessName="DY_others";
    IncomingPartonTag="others";
  }

  myLHE.is_tautau= (ntau==2) ? true : false;
  myLHE.is_mumu= (nmu==2) ? true : false;
  myLHE.is_ee= (nele==2) ? true : false;

  //Check whether g+b scattering
  if(1 != myLHE.ngluon_incoming) return false;
  if(1 != myLHE.nb_incoming) return false;
  //Check whether only 1b among outgoing partons
  //<=> 1b outgoing && nparton outgoing=1
  if(1 != myLHE.nb_outgoing) return false;
  //if(1 != myLHE.nparton_outgoing) return false; // skip this. Only 1 b outgoing quark
  //else, it is one of the events we want.
  return true;

}//[END]Tag_gbToZb()




//Sorting Leptons with P@j restframe , near 1.7
int BBbarRecoTMVA::Rank1n2Leptons(std::vector<int> &v_blep_idx, std::vector<double> &v_blep_value){
  double center=1.7;
  unsigned int vsize=v_blep_idx.size();
  vector<double> v_diff;
  for(unsigned int i = 0 ; i < vsize ; i++){
    v_diff.push_back(fabs(v_blep_value[i]-center));
  }//v loop
  //----idx to return----//
  int idx_rank1=-1;
  int idx_rank2=-1;
  //////---/////

  //--Comparison--//
  for(unsigned int i = 0 ; i < vsize ; i++){
    double this_diff=v_diff[i];
    int this_rank=0;
    for(unsigned int j = 0 ; j < vsize ; j++){
      if(i==j) continue;
      if(this_diff == v_diff[j]){
	if(i>j) this_rank+=1;
      };
      if(this_diff > v_diff[j]){//if i is more far from center than j 
	this_rank+=1;
      }
      
    }//end of j loop
    if(this_rank==0){
      idx_rank1=v_blep_idx[i];//save mu or e idx
    }
    else if(this_rank==1){
      idx_rank2=v_blep_idx[i];//save mu or e idx
    }
  }//end of i loop
  //pair<int,int> _idxpair=make_pair(idx_rank1,idx_rank2);
  //return _idxpair;
  return idx_rank1+idx_rank2*100;
}


void BBbarRecoTMVA::RunLeptonCutStudyMuon(){
  std::vector<int> v_tmva_bmuonidx;
  std::vector<double> v_tmva_bmuon_p_jetrestf;
  for(unsigned int i=0; i < muonsize; i++){
    if((int)i==myRECO.idx_Zmuon1) continue;
    if((int)i==myRECO.idx_Zmuon2) continue;
    
    //---Boost muon to jet restframe
    TLorentzVector vl(AllMuons[i]);
    vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
    //variables//
    p_jetrestf=vl.P();//
    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllMuons[i]);//
    ip3d=AllMuons[i].IP3D();
    nsip3d=fabs(AllMuons[i].IP3D()/AllMuons[i].IP3Derr());
    reliso=AllMuons[i].RelIso();
    reltrkiso=AllMuons[i].TrkIso()/AllMuons[i].Pt();

    //int muon_charge=AllMuons[i].Charge();


    if((dR_l_j<0.4) && (p_jetrestf>0.7) && (p_jetrestf<3)){
      FillHist("nTMVAmuon",1, weight, 1, 0, 2);
      v_tmva_bmuonidx.push_back(i);
      v_tmva_bmuon_p_jetrestf.push_back(p_jetrestf);

    }
  }//end of muon loop

    if(v_tmva_bmuonidx.size()>0){
      i_bmuon=v_tmva_bmuonidx[0];
      //--check only muon channel!

      if(v_tmva_bmuonidx.size()==1){
	SetTreeValuesMuon(i_bmuon,-1,1);
      }//[END] #muon==1
      else{
	int idxIn100=Rank1n2Leptons(v_tmva_bmuonidx,v_tmva_bmuon_p_jetrestf);
	int i_bmuon1=idxIn100%100;
	int i_bmuon2=idxIn100/100;
	SetTreeValuesMuon(i_bmuon1,i_bmuon2,v_tmva_bmuonidx.size());
	
      }
    }//[end]if tmva muons are tagged
    
}//end RunLeptonCutStudyMuon

void BBbarRecoTMVA::SetTreeValuesMuon(int i_bmuon1,int i_bmuon2,int nbmuon){
  //cout << "SetTreeValuesMuon" << endl;
  doFillTree=true;
  FillHist("SetTreeValuesMuon",1, weight, 1, 0, 2);

  //--p jetrestf
  TLorentzVector vl(AllMuons[i_bmuon1]);
  vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
  p_jetrestf=vl.P();//                                                                                                          
  dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllMuons[i_bmuon1]);
  //ip3d=AllMuons[i_bmuon1].IP3D();
  nsip3d=fabs(AllMuons[i_bmuon1].IP3D()/AllMuons[i_bmuon1].IP3Derr());
  reliso=AllMuons[i_bmuon1].RelIso();
  reltrkiso=AllMuons[i_bmuon1].TrkIso()/AllMuons[i_bmuon1].Pt();
  //pt wrt bjet
  double ptwrtbjet=AllMuons[i_bmuon1].P()*sin(AllMuons[i_bmuon1].Angle(AllJets[myRECO.ij_B].Vect()));


  bmuon1_pt=min(AllMuons[i_bmuon1].Pt(),50.);
  bmuon1_eta=AllMuons[i_bmuon1].Eta();
  bmuon1_phi=AllMuons[i_bmuon1].Phi();
  bmuon1_ptwrtbjet=ptwrtbjet;
  bmuon1_p_jetrestf=p_jetrestf;
  bmuon1_dR_l_j=dR_l_j;
  
  bmuon1_nsip3d=min(nsip3d,5.);
  bmuon1_reltrkiso=min(reltrkiso,15.);
  bmuon1_reliso=min(reliso,15.);
  bmuon1_charge=AllMuons[i_bmuon1].Charge();
  bmuon1_charge_float=bmuon1_charge;
  if(i_bmuon2<0){
    bmuon2_pt=0.;
    bmuon2_eta=0.;
    bmuon2_phi=0.;
    bmuon2_ptwrtbjet=0.;
    bmuon2_p_jetrestf=0.;
    bmuon2_dR_l_j=0.;
    bmuon2_nsip3d=0.;
    bmuon2_reltrkiso=0.;
    bmuon2_reliso=0.;
    bmuon2_charge=0.;
    bmuon2_charge_float=0.;
  }
  else{
    //--p jetrestf
    TLorentzVector vl2(AllMuons[i_bmuon2]);
    vl2.Boost(-AllJets[myRECO.ij_B].BoostVector());
    p_jetrestf=vl2.P();//
    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllMuons[i_bmuon2]);
    //ip3d=AllMuons[i_bmuon2].IP3D();
    nsip3d=fabs(AllMuons[i_bmuon2].IP3D()/AllMuons[i_bmuon2].IP3Derr());
    reliso=AllMuons[i_bmuon2].RelIso();
    reltrkiso=AllMuons[i_bmuon2].TrkIso()/AllMuons[i_bmuon2].Pt();
    //pt wrt bjet
    ptwrtbjet=AllMuons[i_bmuon2].P()*sin(AllMuons[i_bmuon2].Angle(AllJets[myRECO.ij_B].Vect()));
   

    bmuon2_pt=min(AllMuons[i_bmuon2].Pt(),50.);
    bmuon2_eta=AllMuons[i_bmuon2].Eta();
    bmuon2_phi=AllMuons[i_bmuon2].Phi();
    bmuon2_ptwrtbjet=ptwrtbjet;
    bmuon2_p_jetrestf=p_jetrestf;
    bmuon2_dR_l_j=dR_l_j;
    bmuon2_nsip3d=min(nsip3d,5.);
    bmuon2_reltrkiso=min(reltrkiso,15.);
    bmuon2_reliso=min(reliso,15.);
    bmuon2_charge=AllMuons[i_bmuon2].Charge(); 
    bmuon2_charge_float=bmuon2_charge;
  }
  n_bmuon=nbmuon;
  n_bmuon_float=n_bmuon;
  //jet
  bjet_charge=AllJets[myRECO.ij_B].Charge();
  bjet_pt=min(AllJets[myRECO.ij_B].Pt(),250.);
  bjet_eta=AllJets[myRECO.ij_B].Eta();
  bjet_phi=AllJets[myRECO.ij_B].Phi();
  bjet_DeepJet=(*jet_DeepJet)[myRECO.ij_B];
  bjet_DeepJet_CvsL=(*jet_DeepJet_CvsL)[myRECO.ij_B];
  bjet_DeepJet_CvsB=(*jet_DeepJet_CvsB)[myRECO.ij_B];
  bjet_chargedHadronEnergyFraction=(*jet_chargedHadronEnergyFraction)[myRECO.ij_B];
  bjet_neutralHadronEnergyFraction=(*jet_neutralHadronEnergyFraction)[myRECO.ij_B];
  bjet_neutralEmEnergyFraction=(*jet_neutralEmEnergyFraction)[myRECO.ij_B];
  bjet_chargedEmEnergyFraction=(*jet_chargedEmEnergyFraction)[myRECO.ij_B];
  bjet_muonEnergyFraction=(*jet_muonEnergyFraction)[myRECO.ij_B];

  bjetPartonFlavourCharge=0.;
  if(!IsDATA){
    if((AllJets[myRECO.ij_B].partonFlavour() == -5)  && (myLHE.evt_nb==-1)){
      bjetPartonFlavourCharge=1.;
      
    }
    else if((AllJets[myRECO.ij_B].partonFlavour() == 5) && (myLHE.evt_nb==1) ){
      bjetPartonFlavourCharge=-1.;
    }
   
  }
}



void BBbarRecoTMVA::RunLeptonCutStudyElectron(){

  std::vector<int> v_tmva_belectronidx;
  std::vector<double> v_tmva_belectron_p_jetrestf;

  for(unsigned int i=0; i < electronsize; i++){
    if((int)i==myRECO.idx_Zelectron1) continue;
    if((int)i==myRECO.idx_Zelectron2) continue;
    
    //---Boost electron to jet restframe
    TLorentzVector vl(AllElectrons[i]);
    vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
    //variables//
    p_jetrestf=vl.P();//
    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllElectrons[i]);//
    ip3d=AllElectrons[i].IP3D();
    nsip3d=fabs(AllElectrons[i].IP3D()/AllElectrons[i].IP3Derr());
    reliso=AllElectrons[i].RelIso();
    reltrkiso=AllElectrons[i].TrkIso()/AllElectrons[i].Pt();
    relecalclusteriso=AllElectrons[i].ecalPFClusterIso()/AllElectrons[i].Pt();
    IsGsfCtfScPixChargeConsistent=AllElectrons[i].IsGsfCtfScPixChargeConsistent();

    //int electron_charge=AllElectrons[i].Charge();

    if((dR_l_j<0.4) && (p_jetrestf>0.7) && (p_jetrestf<3) && (IsGsfCtfScPixChargeConsistent)){
      FillHist("nTMVAelectron",1, weight, 1, 0, 1);
      v_tmva_belectronidx.push_back(i);
      v_tmva_belectron_p_jetrestf.push_back(p_jetrestf);

    }

  }
 
  if(v_tmva_belectronidx.size()>0){
    i_belectron=v_tmva_belectronidx[0];
    //--check only electron channel!
    if(v_tmva_belectronidx.size()==1){
      SetTreeValuesElectron(i_belectron,-1,1);
    }//[END] #electron==1
    else{
      int idxIn100=Rank1n2Leptons(v_tmva_belectronidx,v_tmva_belectron_p_jetrestf);
      int i_belectron1=idxIn100%100;
      int i_belectron2=idxIn100/100;
      SetTreeValuesElectron(i_belectron1,i_belectron2,v_tmva_belectronidx.size());
    }
  }//end of if tmva belectron


}



void BBbarRecoTMVA::SetTreeValuesElectron(int i_belectron1,int i_belectron2,int nbelectron){

  FillHist("SetTreeValuesElectron",1, weight, 1, 0, 2);
  doFillTree=true;
  //--p jetrestf
  TLorentzVector vl(AllElectrons[i_belectron1]);
  vl.Boost(-AllJets[myRECO.ij_B].BoostVector());
  p_jetrestf=vl.P();//                                                                                                          
  dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllElectrons[i_belectron1]);
  //ip3d=AllElectrons[i_belectron1].IP3D();
  nsip3d=fabs(AllElectrons[i_belectron1].IP3D()/AllElectrons[i_belectron1].IP3Derr());
  reliso=AllElectrons[i_belectron1].RelIso();
  reltrkiso=AllElectrons[i_belectron1].TrkIso()/AllElectrons[i_belectron1].Pt();
  //pt wrt bjet
  double ptwrtbjet=AllElectrons[i_belectron1].P()*sin(AllElectrons[i_belectron1].Angle(AllJets[myRECO.ij_B].Vect()));


  belectron1_pt=min(AllElectrons[i_belectron1].Pt(),50.);
  belectron1_eta=AllElectrons[i_belectron1].Eta();
  belectron1_phi=AllElectrons[i_belectron1].Phi();
  belectron1_ptwrtbjet=ptwrtbjet;
  belectron1_p_jetrestf=p_jetrestf;
  belectron1_dR_l_j=dR_l_j;
  belectron1_nsip3d=min(nsip3d,5.);
  belectron1_reltrkiso=min(reltrkiso,15.);
  belectron1_elecalclusteriso=min(AllElectrons[i_belectron1].ecalPFClusterIso()/AllElectrons[i_belectron1].Pt(),10.);
  belectron1_IsGsfCtfScPixChargeConsistent=AllElectrons[i_belectron1].IsGsfCtfScPixChargeConsistent();
  belectron1_IsGsfCtfScPixChargeConsistent_float=belectron1_IsGsfCtfScPixChargeConsistent;
  belectron1_reliso=min(reliso,15.);
  belectron1_charge=AllElectrons[i_belectron1].Charge();
  belectron1_charge_float=belectron1_charge;
  if(i_belectron2<0){
    belectron2_pt=0.;
    belectron2_eta=0.;
    belectron2_phi=0.;
    belectron2_ptwrtbjet=0.;
    belectron2_p_jetrestf=0.;
    belectron2_dR_l_j=0.;
    belectron2_nsip3d=0.;
    belectron2_reltrkiso=0.;
    belectron2_reliso=0.;
    belectron2_charge=0.;
    belectron2_elecalclusteriso=0.;
    belectron2_IsGsfCtfScPixChargeConsistent=0;
    belectron2_IsGsfCtfScPixChargeConsistent_float=0.;
  }
  else{
    //--p jetrestf
    TLorentzVector vl2(AllElectrons[i_belectron2]);
    vl2.Boost(-AllJets[myRECO.ij_B].BoostVector());
    p_jetrestf=vl2.P();//
    dR_l_j=AllJets[myRECO.ij_B].DeltaR(AllElectrons[i_belectron2]);
    //ip3d=AllElectrons[i_belectron2].IP3D();
    nsip3d=fabs(AllElectrons[i_belectron2].IP3D()/AllElectrons[i_belectron2].IP3Derr());
    reliso=AllElectrons[i_belectron2].RelIso();
    reltrkiso=AllElectrons[i_belectron2].TrkIso()/AllElectrons[i_belectron2].Pt();
    //pt wrt bjet
    ptwrtbjet=AllElectrons[i_belectron2].P()*sin(AllElectrons[i_belectron2].Angle(AllJets[myRECO.ij_B].Vect()));
   

    belectron2_pt=min(AllElectrons[i_belectron2].Pt(),50.);
    belectron2_eta=AllElectrons[i_belectron2].Eta();
    belectron2_phi=AllElectrons[i_belectron2].Phi();
    belectron2_ptwrtbjet=ptwrtbjet;
    belectron2_p_jetrestf=p_jetrestf;
    belectron2_dR_l_j=dR_l_j;
    belectron2_nsip3d=min(nsip3d,5.);
    belectron2_reltrkiso=min(reltrkiso,15.);
    belectron2_reliso=min(reliso,15.);
    belectron2_elecalclusteriso=min(AllElectrons[i_belectron2].ecalPFClusterIso()/AllElectrons[i_belectron2].Pt(),10.);
    belectron2_IsGsfCtfScPixChargeConsistent=AllElectrons[i_belectron2].IsGsfCtfScPixChargeConsistent();
    belectron2_IsGsfCtfScPixChargeConsistent_float=belectron2_IsGsfCtfScPixChargeConsistent;
    belectron2_charge=AllElectrons[i_belectron2].Charge(); 
    belectron2_charge_float=belectron2_charge;
  }
  n_belectron=nbelectron;
  n_belectron_float=n_belectron;
  //jet
  bjet_charge=AllJets[myRECO.ij_B].Charge();
  bjet_pt=min(AllJets[myRECO.ij_B].Pt(),250.);
  bjet_eta=AllJets[myRECO.ij_B].Eta();
  bjet_phi=AllJets[myRECO.ij_B].Phi();
  bjet_DeepJet=(*jet_DeepJet)[myRECO.ij_B];
  bjet_DeepJet_CvsL=(*jet_DeepJet_CvsL)[myRECO.ij_B];
  bjet_DeepJet_CvsB=(*jet_DeepJet_CvsB)[myRECO.ij_B];
  bjet_chargedHadronEnergyFraction=(*jet_chargedHadronEnergyFraction)[myRECO.ij_B];
  bjet_neutralHadronEnergyFraction=(*jet_neutralHadronEnergyFraction)[myRECO.ij_B];
  bjet_neutralEmEnergyFraction=(*jet_neutralEmEnergyFraction)[myRECO.ij_B];
  bjet_chargedEmEnergyFraction=(*jet_chargedEmEnergyFraction)[myRECO.ij_B];
  bjet_muonEnergyFraction=(*jet_muonEnergyFraction)[myRECO.ij_B];


  bjetPartonFlavourCharge=0.;
  if(!IsDATA){
    if((AllJets[myRECO.ij_B].partonFlavour() == -5 ) && (myLHE.evt_nb==-1)){
      bjetPartonFlavourCharge=1.;
    }
    else if ((AllJets[myRECO.ij_B].partonFlavour() == 5) && (myLHE.evt_nb==1) ){
      bjetPartonFlavourCharge=-1.;
    }
  }
}




bool BBbarRecoTMVA::ZmmReco(){


  
  vector<int> idx_Zmuon;
  vector<Muon> v_Zmuon;
  double this_leptonid_sf=1.;
  double this_trigger_sf=1.;
  //double this_iso_sf=1.;
  double maxpt=-999.;
  int i_l1=-1;
  int i_l2=-1;
  for(unsigned int i = 0 ; i < muonsize; i++ ){
    double pt=AllMuons[i].Pt();
    double eta=AllMuons[i].Eta();
    bool passID=AllMuons[i].PassID("POGTight");
    double reliso=AllMuons[i].RelIso();
    if(fabs(eta) > 2.4) continue; 
    if(pt <15.) continue;
    if (!passID) continue;
    if(reliso>0.15) continue;//reliso0.15

    idx_Zmuon.push_back(i);
    v_Zmuon.push_back(AllMuons[i]);
    if(!IsDATA) {
      this_leptonid_sf*=mcCorr->MuonID_SF("NUM_TightID_DEN_TrackerMuons",  eta, AllMuons[i].MiniAODPt());
      //this_iso_sf = mcCorr->MuonISO_SF("NUM_TightRelIso_DEN_TightIDandIPCut", eta, AllMuons[i].MiniAODPt());
    }
    if(pt > maxpt){
      maxpt = pt;
      i_l1 = i;
    }
  }

  this_trigger_sf*=mcCorr->MuonTrigger_SF("IsoMu27_POGTight", "HLT_IsoMu27_v", v_Zmuon, 0);
  if (idx_Zmuon.size()<2) return 0;
  if (maxpt<30.) return 0;
  
  unsigned int SelectedMuonSize=idx_Zmuon.size();
  //int i_l1=idx_Zmuon[0];
  //int i_l2=idx_Zmuon[1];
  double second_max_pt=-999;
  for(unsigned int i = 0 ; i <SelectedMuonSize ; i++){
    int idx=idx_Zmuon[i];
    double pt=AllMuons[idx].Pt();
    if(idx==i_l1)continue;
    if(pt > second_max_pt){
      second_max_pt=pt;
      i_l2=idx;
    }
  }


  myRECO.mZ=(AllMuons[i_l1]+AllMuons[i_l2]).M();
  double mZ=myRECO.mZ;
  if(mZ < 60) return 0;
  if(mZ > 120) return 0;


  myRECO.idx_Zmuon1=i_l1;
  myRECO.idx_Zmuon2=i_l2;
  myRECO.goodZmm=true;
  weight*=this_leptonid_sf*this_trigger_sf;
  return 1;


}

bool BBbarRecoTMVA::ZeeReco(){
  vector<int> idx_Zelectron;
  vector<Electron> v_Zelectron;
  double this_leptonid_sf=1.;
  double this_leptonreco_sf=1.;
  //double this_trigger_sf=1.;
  for(unsigned int i = 0 ; i < electronsize; i++ ){
    double pt=AllElectrons[i].Pt();
    double eta=AllElectrons[i].Eta();
    bool passID=AllElectrons[i].PassID("passMediumID");
    if(fabs(eta) > 2.4) continue; 
    if(pt <15.) continue;
    if (!passID) continue;
    idx_Zelectron.push_back(i);
    v_Zelectron.push_back(AllElectrons[i]);
    if(!IsDATA) {
      this_leptonid_sf*=mcCorr->ElectronID_SF ("passMediumID",  AllElectrons[i].scEta(), pt);
      this_leptonreco_sf*=mcCorr->ElectronReco_SF (AllElectrons[i].scEta(), pt,0);

    }
  }

  //this_trigger_sf*=ElectronTrigger_SF(TString ID, "HLT_Ele35_WPTight_Gsf_v", v_Zelectron, 0);

  if (idx_Zelectron.size()<2) return 0;
  if (AllElectrons[idx_Zelectron[0]].Pt()<38) return 0;

  int i_l1=idx_Zelectron[0];
  int i_l2=idx_Zelectron[1];
  myRECO.mZ=(AllElectrons[i_l1]+AllElectrons[i_l2]).M();
  double mZ=myRECO.mZ;
  if(mZ < 60) return 0;
  if(mZ > 120) return 0;
  weight*=this_leptonid_sf*this_leptonreco_sf;
  myRECO.idx_Zelectron1=i_l1;
  myRECO.idx_Zelectron2=i_l2;
  myRECO.goodZmm=true;
  return 1;



    

}


bool BBbarRecoTMVA::Tag1bjet(){
  //JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb
  //double MCCorrection::GetJetTaggingCutValue(JetTagging::Tagger tagger, JetTagging::WP wp){
  //myRECO.ij_B
  //vector<Jet> tightjets = SelectJets(AllJets, "tightLepVeto", 20., 2.4);
  unsigned int _Nb=0;
  tightjets.clear();
  //tightjets.push_back(AllJets[myRECO.ij_B]);
  //jtp=JetTagging::Parameters(JetTagging::DeepJet,JetTagging::Tight,JetTagging::incl,JetTagging::comb);
  btag_cut = mcCorr->MCCorrection::GetJetTaggingCutValue(JetTagging::DeepJet,JetTagging::Tight);
  TLorentzVector l1;
  TLorentzVector l2;
  if(myRECO.passMuonTriggerAndZmm){
    l1=AllMuons[myRECO.idx_Zmuon1];
    l2=AllMuons[myRECO.idx_Zmuon2];
  }
  else if(myRECO.passElectronTriggerAndZee){
    l1=AllElectrons[myRECO.idx_Zelectron1];
    l2=AllElectrons[myRECO.idx_Zelectron2];
  }
  //cout << "btag_cut=" << btag_cut << endl;
  for(unsigned int i = 0 ; i < jetsize; i ++){
    double btag_score=AllJets[i].GetTaggerResult(JetTagging::DeepJet);
    //cout << "btag_score=" << btag_score << endl;
    if(btag_score < btag_cut) continue;
    if(AllJets[i].Pt() < 20) continue;
    if(fabs(AllJets[i].Eta()) > 2.4) continue;
    if(AllJets[i].DeltaR(l1)<0.4) continue;
    if(AllJets[i].DeltaR(l2)<0.4) continue;
    if(AllJets[i].PassID("tight")){
      _Nb+=1;
      myRECO.ij_B=i;
    }
    tightjets.push_back(AllJets[i]);
  }
  if(_Nb!=1) return 0;
  

  

  if(!IsDATA){
    double btagWeight = mcCorr->GetBTaggingReweight_1a(tightjets, jtp);
    weight*=btagWeight;
  }
  return 1;
}

void BBbarRecoTMVA::AnalyzeRECO(){


  
  //call muon/electron
  vector<Muon> AllMuons_raw=GetAllMuons();
  AllMuons=ScaleMuons(AllMuons_raw,0);
  muonsize = AllMuons.size();
  AllElectrons=GetAllElectrons();
  electronsize = AllElectrons.size();
  AllJets = GetAllJets();
  jetsize=AllJets.size();

  //(0) Apply some basic cuts
  TString MuonTriggerName = "HLT_IsoMu27_v";
  TString ElectronTriggerName = "HLT_Ele35_WPTight_Gsf_v";
  myRECO.passMuonTrigger=ev.PassTrigger(MuonTriggerName);
  myRECO.passElectronTrigger=ev.PassTrigger(ElectronTriggerName);

  FillHist("PassBothTrigger",myRECO.passMuonTrigger*myRECO.passElectronTrigger, weight, 2, 0, 2);




  myRECO.goodZee=ZeeReco();
  myRECO.goodZmm=ZmmReco();

  bool passMuonTriggerAndZmm=myRECO.passMuonTrigger&&myRECO.goodZmm;
  bool passElectronTriggerAndZee=myRECO.passElectronTrigger&&myRECO.goodZee;
  
  if((!passMuonTriggerAndZmm) && (!passElectronTriggerAndZee)) return;
  
  myRECO.passMuonTriggerAndZmm=passMuonTriggerAndZmm;
  myRECO.passElectronTriggerAndZee=passElectronTriggerAndZee;

  if(passMuonTriggerAndZmm){ 
    ZllChannel="Zmm";
  }
  else if(passElectronTriggerAndZee){
    ZllChannel="Zee";
  }
  
  FillHist("PassTrigger__and__GoodZ",1, weight, 1, 0, 2);
  FillHist("PassTrigger_and_GoodZ/mZ/"+ProcessName, myRECO.mZ, weight, 200, 60., 120.);


  if(!BBbarRecoTMVA::Tag1bjet()) return;
  FillHist("Pass1bjet",1, weight, 1, 0, 2);
  //->now Z is reconstructed
  //(1) Do Main Analysis
  //(1-1) Set EventTag
  //(1-2)For B hadron to lepton decay
  //BBbarRecoTMVA::RunProtoTypeMuon();
  //BBbarRecoTMVA::RunProtoTypeElectron();
  BBbarRecoTMVA::RunLeptonCutStudyMuon();
  FillHist("PassRunLeptonCutStudyMuon",1, weight, 1, 0, 2);
  BBbarRecoTMVA::RunLeptonCutStudyElectron();
  FillHist("PassRunLeptonCutStudyElectron",1, weight, 1, 0, 2);

}

double BBbarRecoTMVA::CalcDNN(){
   double DNN_odd_pos_raw=myreader_odd_pos->EvaluateMVA("PyKeras::DNN");
   DNN_odd_pos=tgr_odd_pos->Eval(DNN_odd_pos_raw);
   double DNN_even_pos_raw=myreader_even_pos->EvaluateMVA("PyKeras::DNN");
   DNN_even_pos=tgr_even_pos->Eval(DNN_even_pos_raw);
   double DNN_odd_neg_raw=myreader_odd_neg->EvaluateMVA("PyKeras::DNN");
   DNN_odd_neg=tgr_odd_neg->Eval(DNN_odd_neg_raw);
   double DNN_even_neg_raw=myreader_even_neg->EvaluateMVA("PyKeras::DNN");
   DNN_even_neg=tgr_even_neg->Eval(DNN_even_neg_raw);
   
   
   if(event%2==0){//even
     if(DNN_even_pos > DNN_even_neg){
       DNN_b=DNN_even_pos;
       DNN_s=-DNN_even_neg;
      }
     else{
       DNN_s=DNN_even_pos;
       DNN_b=-DNN_even_neg;
       
     }
   }
   else{
     if(DNN_odd_pos > DNN_odd_neg){
       DNN_b=DNN_odd_pos;//take bigger one
       DNN_s=-DNN_odd_neg;
     }
     else{
       DNN_s=DNN_odd_pos;
       DNN_b=-DNN_odd_neg;//
       
     }
   }
   return DNN_s;
}

void BBbarRecoTMVA::FillHists(TString cutname){

  //IncomingPartonTag

  TString Tags[]={"","_"+IncomingPartonTag};
  const int TagsSize=sizeof(Tags)/sizeof(TString);
  for(unsigned int i = 0 ; i < TagsSize ; i++){
    TString Tag=Tags[i];
    TString this_ProcessName=ProcessName+Tag;
    FillHist(cutname+"/mZ/"+this_ProcessName,myRECO.mZ, weight, 200, 60., 120.);
    FillHist(cutname+"/MET/"+this_ProcessName,MET, weight, 100, 0., 200.);
    FillHist(cutname+"/nPileUp/"+this_ProcessName,nPileUp, weight, 80, 0., 80.);
  
  
  
    if(myRECO.passMuonTrigger && myRECO.goodZmm){
      FillHist(cutname+"/Zmuon1_pt/"+this_ProcessName,AllMuons[myRECO.idx_Zmuon1].Pt(), weight, 100, 20., 220.);
      FillHist(cutname+"/Zmuon2_pt/"+this_ProcessName,AllMuons[myRECO.idx_Zmuon2].Pt(), weight, 100, 20., 220.);
      
      FillHist(cutname+"/Zmuon1_eta/"+this_ProcessName,AllMuons[myRECO.idx_Zmuon1].Eta(), weight, 100, -2.4, 2.4);
      FillHist(cutname+"/Zmuon2_eta/"+this_ProcessName,AllMuons[myRECO.idx_Zmuon2].Eta(), weight, 100, -2.4, 2.4);
      
      FillHist(cutname+"/log_Zmuon1_reliso/"+this_ProcessName, log10(AllMuons[myRECO.idx_Zmuon1].RelIso()), weight, 100, -5., 2.);
      FillHist(cutname+"/log_Zmuon2_reliso/"+this_ProcessName, log10(AllMuons[myRECO.idx_Zmuon1].RelIso()), weight, 100, -5., 2.);
    }
    if(myRECO.passElectronTrigger && myRECO.goodZee){
      FillHist(cutname+"/Zelectron1_pt/"+this_ProcessName,AllElectrons[myRECO.idx_Zelectron1].Pt(), weight, 100, 20., 220.);
      FillHist(cutname+"/Zelectron2_pt/"+this_ProcessName,AllElectrons[myRECO.idx_Zelectron2].Pt(), weight, 100, 20., 220.);
      
      FillHist(cutname+"/Zelectron1_eta/"+this_ProcessName,AllElectrons[myRECO.idx_Zelectron1].Eta(), weight, 100, -2.4, 2.4);
      FillHist(cutname+"/Zelectron2_eta/"+this_ProcessName,AllElectrons[myRECO.idx_Zelectron2].Eta(), weight, 100, -2.4, 2.4);
      
      FillHist(cutname+"/log_Zelectron1_reliso/"+this_ProcessName, log10(AllElectrons[myRECO.idx_Zelectron1].RelIso()), weight, 100, -5., 2.);
      FillHist(cutname+"/log_Zelectron2_reliso/"+this_ProcessName, log10(AllElectrons[myRECO.idx_Zelectron1].RelIso()), weight, 100, -5., 2.);
      
    }
    
    //---
    if(bmuon1_pt>0){
      FillHist(cutname+"/bmuon1_p_jetrestf/"+this_ProcessName, bmuon1_p_jetrestf, weight, 200, 0., 10.);
      FillHist(cutname+"/bmuon1_dR_l_j/"+this_ProcessName, bmuon1_dR_l_j, weight, 200, 0., 5.);
      FillHist(cutname+"/bmuon1_nsip3d/"+this_ProcessName, bmuon1_nsip3d, weight, 100, -10., 10.);
      FillHist(cutname+"/log_bmuon1_reliso/"+this_ProcessName, log10(bmuon1_reliso), weight, 100, -5., 2.);
      FillHist(cutname+"/log_bmuon1_reltrkiso/"+this_ProcessName, log10(bmuon1_reltrkiso), weight, 100, -5., 2.);
      FillHist(cutname+"/bmuon1_charge/"+this_ProcessName, bmuon1_charge, weight, 4, -2., 2.);
      FillHist(cutname+"/bmuon1_pt/"+this_ProcessName, bmuon1_pt, weight, 100, 0., 100.);
      FillHist(cutname+"/bmuon1_eta/"+this_ProcessName, bmuon1_eta, weight, 100, -5., 5.);
      FillHist(cutname+"/bmuon1_phi/"+this_ProcessName, bmuon1_phi, weight, 100, -4., 4.);
      FillHist(cutname+"/bmuon1_ptwrtbjet/"+this_ProcessName, bmuon1_ptwrtbjet, weight, 100, 0., 10.);
      FillHist(cutname+"/DNNscore_if_bmuon1/"+this_ProcessName, DNNscore, weight, 100, -1., 1.);  
    }
    if(bmuon2_pt>0){
      FillHist(cutname+"/bmuon2_p_jetrestf/"+this_ProcessName, bmuon2_p_jetrestf, weight, 200, 0., 10.);
      FillHist(cutname+"/bmuon2_dR_l_j/"+this_ProcessName, bmuon2_dR_l_j, weight, 200, 0., 5.);
      FillHist(cutname+"/bmuon2_nsip3d/"+this_ProcessName, bmuon2_nsip3d, weight, 100, -10., 10.);
      FillHist(cutname+"/log_bmuon2_reliso/"+this_ProcessName, log10(bmuon2_reliso), weight, 100, -5., 2.);
      FillHist(cutname+"/log_bmuon2_reltrkiso/"+this_ProcessName, log10(bmuon2_reltrkiso), weight, 100, -5., 2.);
      FillHist(cutname+"/bmuon2_charge/"+this_ProcessName, bmuon2_charge, weight, 4, -2., 2.);
      FillHist(cutname+"/bmuon2_pt/"+this_ProcessName, bmuon2_pt, weight, 100, 0., 100.);
      FillHist(cutname+"/bmuon2_eta/"+this_ProcessName, bmuon2_eta, weight, 100, -5., 5.);
      FillHist(cutname+"/bmuon2_phi/"+this_ProcessName, bmuon2_phi, weight, 100, -4., 4.);
      FillHist(cutname+"/bmuon2_ptwrtbjet/"+this_ProcessName, bmuon2_ptwrtbjet, weight, 100, 0., 10.);
      FillHist(cutname+"/DNNscore_if_bmuon2/"+this_ProcessName, DNNscore, weight, 100, -1., 1.);  
    }
    if(belectron1_pt>0){
      FillHist(cutname+"/belectron1_p_jetrestf/"+this_ProcessName, belectron1_p_jetrestf, weight, 200, 0., 10.);
      FillHist(cutname+"/belectron1_dR_l_j/"+this_ProcessName, belectron1_dR_l_j, weight, 200, 0., 5.);
      FillHist(cutname+"/belectron1_nsip3d/"+this_ProcessName, belectron1_nsip3d, weight, 100, -10., 10.);
      FillHist(cutname+"/log_belectron1_reliso/"+this_ProcessName, log10(belectron1_reliso), weight, 100, -5., 2.);
      FillHist(cutname+"/log_belectron1_reltrkiso/"+this_ProcessName, log10(belectron1_reltrkiso), weight, 100, -5., 2.);
      FillHist(cutname+"/log_belectron1_elecalclusteriso/"+this_ProcessName, log10(belectron1_elecalclusteriso), weight, 100, -5., 2.);
      FillHist(cutname+"/belectron1_IsGsfCtfScPixChargeConsistent/"+this_ProcessName, belectron1_IsGsfCtfScPixChargeConsistent_float, weight, 2, 0., 2.);
      FillHist(cutname+"/belectron1_charge/"+this_ProcessName, belectron1_charge, weight, 4, -2., 2.);
      FillHist(cutname+"/belectron1_pt/"+this_ProcessName, belectron1_pt, weight, 100, 0., 100.);
      FillHist(cutname+"/belectron1_eta/"+this_ProcessName, belectron1_eta, weight, 100, -5., 5.);
      FillHist(cutname+"/belectron1_phi/"+this_ProcessName, belectron1_phi, weight, 100, -4., 4.);
      FillHist(cutname+"/belectron1_ptwrtbjet/"+this_ProcessName, belectron1_ptwrtbjet, weight, 100, 0., 10.);
      FillHist(cutname+"/DNNscore_if_belectron1/"+this_ProcessName, DNNscore, weight, 100, -1., 1.);  
    }
    
    if(belectron2_pt>0){
      FillHist(cutname+"/belectron2_p_jetrestf/"+this_ProcessName, belectron2_p_jetrestf, weight, 200, 0., 10.);
      FillHist(cutname+"/belectron2_dR_l_j/"+this_ProcessName, belectron2_dR_l_j, weight, 200, 0., 5.);
      FillHist(cutname+"/belectron2_nsip3d/"+this_ProcessName, belectron2_nsip3d, weight, 100, -10., 10.);
      FillHist(cutname+"/log_belectron2_reliso/"+this_ProcessName, log10(belectron2_reliso), weight, 100, -5., 2.);
      FillHist(cutname+"/log_belectron2_reltrkiso/"+this_ProcessName, log10(belectron2_reltrkiso), weight, 100, -5., 2.);
      FillHist(cutname+"/log_belectron2_elecalclusteriso/"+this_ProcessName, log10(belectron2_elecalclusteriso), weight, 100, -5., 2.);
      FillHist(cutname+"/belectron2_IsGsfCtfScPixChargeConsistent/"+this_ProcessName, belectron2_IsGsfCtfScPixChargeConsistent_float, weight, 2, 0., 2.);
      FillHist(cutname+"/belectron2_charge/"+this_ProcessName, belectron2_charge, weight, 4, -2., 2.);
      FillHist(cutname+"/belectron2_pt/"+this_ProcessName, belectron2_pt, weight, 100, 0., 100.);
      FillHist(cutname+"/belectron2_eta/"+this_ProcessName, belectron2_eta, weight, 100, -5., 5.);
      FillHist(cutname+"/belectron2_phi/"+this_ProcessName, belectron2_phi, weight, 100, -4., 4.);
      FillHist(cutname+"/belectron2_ptwrtbjet/"+this_ProcessName, belectron2_ptwrtbjet, weight, 100, 0., 10.);
      FillHist(cutname+"/DNNscore_if_belectron2/"+this_ProcessName, DNNscore, weight, 100, -1., 1.);  
    }
    
    FillHist(cutname+"/bjet_charge/"+this_ProcessName, bjet_charge, weight, 100, -1., 1.);
    FillHist(cutname+"/bjet_neutralEmEnergyFraction/"+this_ProcessName, bjet_neutralEmEnergyFraction, weight, 100, 0., 1.);
    FillHist(cutname+"/bjet_neutralHadronEnergyFraction/"+this_ProcessName, bjet_neutralHadronEnergyFraction, weight, 100, 0., 1.);
    FillHist(cutname+"/bjet_muonEnergyFraction/"+this_ProcessName, bjet_muonEnergyFraction, weight, 100, 0., 1.);
    FillHist(cutname+"/bjet_DeepJet/"+this_ProcessName, bjet_DeepJet, weight, 100, 0., 1.);
    FillHist(cutname+"/bjet_pt/"+this_ProcessName, bjet_pt, weight, 100, 20., 220.);
    FillHist(cutname+"/bjet_eta/"+this_ProcessName, bjet_eta, weight, 100, -3., 3.);
    FillHist(cutname+"/bjet_phi/"+this_ProcessName, bjet_phi, weight, 100, -4., 4.);
    FillHist(cutname+"/DNNscore/"+this_ProcessName, DNNscore, weight, 100, -1., 1.);  
  }
}

void BBbarRecoTMVA::executeEvent(){
  ev = GetEvent();
  FillHist("event_start",1, weight, 1, 0, 1);
  isEvenEvent=((event%2)==0);
  //---initialize--//
  //EventTag="";
  //EventTagJetParton="";
  ZllChannel="";
  IncomingPartonTag="";
  doPrint=false;
  weight = 1.;//init event weight
  myRECO.idx_Zmuon1=-1;
  myRECO.idx_Zmuon2=-1;
  myRECO.idx_Zelectron1=-1;
  myRECO.idx_Zelectron2=-1;
  myRECO.goodZmm=false;
  myRECO.goodZee=false;
  DNNscore=-999.;

  MET = ev.GetMETVector().Pt();


  weight*=GetPrefireWeight(0);
  weight*=GetPileUpWeight(nPileUp,0);
  if(!IsDATA){
    weight *= MCweight();
    weight *= ev.GetTriggerLumi("Full");
  }
  //initialize//
  myLHE.incoming_parton_pid.clear();
  InitTreeValues();
  doFillTree=false;
  //(1)---Let's tag only events with following process..
  //         g      =====o----- b(or bbar)
  //                     |
  //                     |
  //   b(or bbar)   -----o======     Z
  //
  
  //if (MCSample.Contains("DY")){
  if(!IsDATA){
    myLHE.is_gbToZb = BBbarRecoTMVA::Tag_gbToZb(); 
  }
  //BBbarRecoTMVA::AnalyzeLHE();
  //}
  BBbarRecoTMVA::AnalyzeRECO();
  //NowFillTree
  if(doFillTree){

    DNNscore=CalcDNN();
    //TString cutname="recoZb";
    FillHists("ZbRegion");
    if(nPileUp<10) FillHists("ZbRegion_nPileUpUnder10");
    if(nPileUp>40) FillHists("ZbRegion_nPileUpOver40");
    //bevent 10%up
    if(IncomingPartonTag.Contains("bevt")){
      weight*=1.1;
      FillHists("ZbRegion_bevt0p1Up");      
      weight*=1/1.1;
    }
    else{
      FillHists("ZbRegion_bevt0p1Up");
    }

    //bbar 10%up
    if(IncomingPartonTag.Contains("bbar")){
      weight*=1.1;
      FillHists("ZbRegion_bbar0p1Up");      
      weight*=1/1.1;
    }
    else{
      FillHists("ZbRegion_bbar0p1Up");
    }



    if(myRECO.passMuonTrigger&&myRECO.goodZmm){
      FillHists("ZbRegion_Zmm");
      //bevent 10%up
      if(IncomingPartonTag.Contains("bevt")){
	weight*=1.1;
	FillHists("ZbRegion_Zmm_bevt0p1Up");
	weight*=1/1.1;
      }
      else{
	FillHists("ZbRegion_Zmm_bevt0p1Up");
      }

      //bbar 10%up
      if(IncomingPartonTag.Contains("bbar")){
	weight*=1.1;
	FillHists("ZbRegion_Zmm_bbar0p1Up");      
	weight*=1/1.1;
      }
      else{
	FillHists("ZbRegion_Zmm_bbar0p1Up");
      }
    }
    else if(myRECO.passElectronTrigger&&myRECO.goodZee){
      FillHists("ZbRegion_Zee");
      //bevent 10%up
      if(IncomingPartonTag.Contains("bevt")){
	weight*=1.1;
	FillHists("ZbRegion_Zee_bevt0p1Up");
	weight*=1/1.1;
      }
      else{
	FillHists("ZbRegion_Zee_bevt0p1Up");
      }

      //bbar 10%up
      if(IncomingPartonTag.Contains("bbar")){
	weight*=1.1;
	FillHists("ZbRegion_Zee_bbar0p1Up");      
	weight*=1/1.1;
      }
      else{
	FillHists("ZbRegion_Zee_bbar0p1Up");
      }



    }

    //10%up only for bevent

  }//end dofilltree
  
  //  FillHist("BasicCut/ZCand_Mass/"+ProcessName, ZCand.M(), weight, 40, 70., 110.);
  
  
}
