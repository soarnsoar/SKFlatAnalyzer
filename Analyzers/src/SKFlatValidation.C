#include "SKFlatValidation.h"

void SKFlatValidation::executeEvent(){

  AnalyzerParameter param;

  //==== POG IDs

  param.Name = "POG";

  param.Electron_Tight_ID = "passMVAID_iso_WP80";
  param.Electron_ID_SF_Key = "passMVAID_iso_WP80";

  param.Muon_Tight_ID = "POGTightWithTightIso";
  param.Muon_ID_SF_Key = "NUM_TightID_DEN_genTracks";
  param.Muon_ISO_SF_Key = "NUM_TightRelIso_DEN_TightIDandIPCut";
  param.Muon_Trigger_SF_Key = "POGTight";

  param.Jet_ID = "HN";

  executeEventFromParameter(param);

  //==== POG HighPt

  param.Clear();

  param.Name = "POGHighPt";

  param.Electron_Tight_ID = "passHEEPID";
  param.Electron_ID_SF_Key = "Default";

  param.Muon_Tight_ID = "POGHighPtWithLooseTrkIso";
  param.Muon_ID_SF_Key = "NUM_HighPtID_DEN_genTracks";
  param.Muon_ISO_SF_Key = "NUM_LooseRelTkIso_DEN_HighPtIDandIPCut";
  param.Muon_Trigger_SF_Key = "Default";
  param.Muon_UseTuneP = true;

  param.Jet_ID = "HN";

  executeEventFromParameter(param);


/*
  //=== Same but pt>75 GeV
  param.Name = "POG_pt75";
  executeEventFromParameter(param);
*/
  //==== HNPair ID

  param.Clear();
  param.Name = "HNPair";

  param.MCCorrrectionIgnoreNoHist = true;

  param.Electron_Tight_ID = "HNPairTight";
  param.Electron_Tight_RelIso = 0.1;
  param.Electron_Loose_ID = "HNPairLoose";
  param.Electron_Loose_RelIso = 0.6;
  param.Electron_Veto_ID = "HNPairVeto";
  param.Electron_Veto_RelIso = 0.6;
  param.Electron_UseMini = true;

  param.Muon_Tight_ID = "HNPairTight";
  param.Muon_Tight_RelIso = 0.2;
  param.Muon_Loose_ID = "HNPairLoose";
  param.Muon_Loose_RelIso = 0.6;
  param.Muon_Veto_ID = "HNPairVeto";
  param.Muon_Veto_RelIso = 0.6;
  param.Muon_UseMini = true;

  param.Jet_ID = "HN";

  executeEventFromParameter(param);

/*
  //=== Same but pt>75 GeV
  param.Name = "HNPair_pt75";
  executeEventFromParameter(param);
*/

  //==== HNWR

  param.Clear();
  param.Name = "HNWR";

  param.MCCorrrectionIgnoreNoHist = true;

  param.Electron_Tight_ID = "HNWRTight";
  param.Electron_Tight_RelIso = 0.15;
  param.Electron_Loose_ID = "HNWRLoose";
  param.Electron_Loose_RelIso = 0.6;
  param.Electron_Veto_ID = "HNWRVeto";
  param.Electron_Veto_RelIso = 0.6;
  param.Electron_UseMini = false;
  param.Electron_UsePtCone = false;
  param.Electron_MinPt = 10.;

  param.Muon_Tight_ID = "HNWRTight";
  param.Muon_Tight_RelIso = 0.15;
  param.Muon_Loose_ID = "HNWRLoose";
  param.Muon_Loose_RelIso = 0.6;
  param.Muon_Veto_ID = "HNWRVeto";
  param.Muon_Veto_RelIso = 0.6;
  param.Muon_UseMini = false;
  param.Muon_UsePtCone = false;
  param.Muon_MinPt = 10.;

  param.Jet_ID = "HN";

  executeEventFromParameter(param);

}

void SKFlatValidation::executeEventFromParameter(AnalyzerParameter param){

  if(!PassMETFilter()) return;

  Event ev = GetEvent();

  //bool PassDiMuon = ev.PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v");
  bool PassSingleMuon = ev.PassTrigger("HLT_IsoMu27_v");
  bool PassSingleElectron = ev.PassTrigger("HLT_Ele35_WPTight_Gsf_v");

  double MinLeptonPt = 10.;
  if(param.Name.Contains("pt75")) MinLeptonPt = 75.;

  std::vector<Muon> muons = GetMuons(param.Muon_Tight_ID, MinLeptonPt, 2.4);
  std::vector<Electron> electrons = GetElectrons(param.Electron_Tight_ID, MinLeptonPt, 2.5);

  std::vector<Jet> alljets = GetAllJets();
  std::vector<Jet> myjets;
  int NBJets=0;
  double HT=0;
  for(unsigned int i=0; i<alljets.size(); i++){
    Jet this_jet = alljets.at(i);
    if(this_jet.Pt() > 30. && fabs(this_jet.Eta())<2.5){
      myjets.push_back(this_jet);
      HT += this_jet.Pt();
      if(this_jet.IsTagged(Jet::CSVv2, Jet::Medium)) NBJets++;
    }
  }

  //==== Based on which trigger is fired
  std::vector< TString > Suffixs = {
    "SingleMuon",
    //"DiElectron",
    //"DiPhoton",
    "SingleElectron",
  };
  std::vector< bool > PassTriggers = {
    PassSingleMuon && (muons.size()>=1) && (electrons.size()==0),
    //PassDiElectron && (electrons.size()==2) && (muons.size()==0),
    //PassDiPhoton && (electrons.size()==2) && (muons.size()==0),
    PassSingleElectron && (electrons.size()>=1) && (muons.size()==0),
  };

  for(unsigned int i=0; i<Suffixs.size(); i++){

    TString Suffix = Suffixs.at(i);
    if( !PassTriggers.at(i) ) continue;

    if(Suffix.Contains("SingleMuon")){
      if( muons.at(0).Pt() < 29. ) continue;
    }
    else if(Suffix.Contains("DiElectron")){
      if( electrons.at(0).Pt() < 25. || electrons.at(1).Pt() < 15. ) continue;
    }
    else if(Suffix.Contains("SingleElectron")){
      if( electrons.at(0).Pt() < 38. ) continue;
    }
    else if(Suffix.Contains("DiPhoton")){
      if( electrons.at(0).Pt() < 75. || electrons.at(1).Pt() < 75. ) continue;
    }
    else{

    }

    if(this->IsDATA){
      if(this->DataStream == "SingleMuon"){
        if(!( Suffix.Contains("SingleMuon") )) continue;
      }
      else if(this->DataStream == "DoubleEG"){
        if(!( Suffix.Contains("DiElectron")||Suffix.Contains("DiPhoton") )) continue;
      }
      else if(this->DataStream == "SingleElectron"){
        if(!( Suffix.Contains("SingleElectron") )) continue;
      }
      else{

      }
    }
    
    std::vector<Lepton *> leps;
    if(Suffix.Contains("SingleMuon")){
      leps = MakeLeptonPointerVector(muons);
    }
    else if(Suffix.Contains("DiElectron")||Suffix.Contains("DiPhoton")){
      leps = MakeLeptonPointerVector(electrons);
    }
    else if(Suffix.Contains("SingleElectron")){
      leps = MakeLeptonPointerVector(electrons);
    }
    else{

    }

    Particle METv = ev.GetMETVector();

    int n_lepton = leps.size();
    //==== DiLepton variables
    bool IsOS = false;
    Particle Z;
    if(n_lepton==2){
      IsOS = (leps[0]->Charge() != leps[1]->Charge());
      Z = (*leps[0])+(*leps[1]);
    }
    //==== SingleLepton variables
    double this_MT=-999.;
    if(n_lepton==1){
      this_MT = MT( METv, (*leps[0]) );
    }

    double weight = 1.;
    if(!IsDATA){
      //cout << "weight_norm_1invpb = " << weight_norm_1invpb << endl;
      //cout << "GetTriggerLumi = " << ev.GetTriggerLumi("Full") << endl;
      weight *= weight_norm_1invpb*ev.GetTriggerLumi("Full")*ev.MCweight();

      mcCorr.IgnoreNoHist = param.MCCorrrectionIgnoreNoHist;

      //==== FIXME add third lepton veto later
      if(Suffix.Contains("SingleMuon")){
        for(unsigned int i=0; i<muons.size(); i++){

          double this_pt = muons.at(i).MiniAODPt();
          double this_eta = muons.at(i).Eta();

          if(param.Muon_UseTuneP){
            Particle this_tuneP = muons.at(i).TuneP4();
            this_pt = this_tuneP.Pt();
            this_eta = this_tuneP.Eta();
          }

          double this_idsf  = mcCorr.MuonID_SF (param.Muon_ID_SF_Key,  this_eta, this_pt);
          double this_isosf = mcCorr.MuonISO_SF(param.Muon_ISO_SF_Key, this_eta, this_pt);
          double this_trigsf = mcCorr.MuonTrigger_SF(param.Muon_Trigger_SF_Key, "IsoMu27", muons);

          weight *= this_idsf*this_isosf*this_trigsf;

        }
      }
      if( Suffix.Contains("DiElectron") || Suffix.Contains("SingleElectron") || Suffix.Contains("DiPhoton") ){
        for(unsigned int i=0; i<electrons.size(); i++){
          double this_recosf = mcCorr.ElectronReco_SF(electrons.at(i).scEta(),electrons.at(i).Pt());
          double this_idsf = mcCorr.ElectronID_SF(param.Electron_ID_SF_Key, electrons.at(i).scEta(), electrons.at(i).Pt());
          weight *= this_recosf*this_idsf;
        }
      }

    }

    std::map<TString, bool> map_bool_To_Region;
    if(n_lepton==2){
      if(IsOS){
        //==== generic two OS lepton
        map_bool_To_Region["OS"] = true;
        //==== OnZ event
        map_bool_To_Region["OnZ_OS"] = IsOnZ(Z.M(), 15.);
        //==== OnZ event
        map_bool_To_Region["ZMassgt50_OS"] = (Z.M()>50.);
        //==== With B-jet, MET > 30 for dilepton ttbar
        map_bool_To_Region["WithBJet_METgt30_OS"] = (NBJets>0) && (METv.Pt()>30.);
      }
      else{
        //==== generic two SS lepton
        map_bool_To_Region["SS"] = true;
        //==== OnZ event
        map_bool_To_Region["OnZ_SS"] = IsOnZ(Z.M(), 15.);
        //==== OnZ event
        map_bool_To_Region["ZMassgt50_SS"] = (Z.M()>50.);
        //==== With B-jet, MET > 30 for dilepton ttbar
        map_bool_To_Region["WithBJet_METgt30_SS"] = (NBJets>0) && (METv.Pt()>30.);
      }
    }
    if(n_lepton==1){
      map_bool_To_Region["W_CR"] = ( METv.Pt() > 30. ) && ( this_MT > 30. );
    }

    for(std::map<TString, bool>::iterator it_map = map_bool_To_Region.begin(); it_map != map_bool_To_Region.end(); it_map++){

      TString this_region = it_map->first;
      this_region = (param.Name)+"_"+Suffix+"_"+this_region;

      if(it_map->second){

        JSFillHist(this_region, "NEvent_"+this_region, 0., weight, 1, 0., 1.);

        JSFillHist(this_region, "MET_"+this_region, METv.Pt(), weight, 500, 0., 500.);
        JSFillHist(this_region, "METphi_"+this_region, METv.Phi(), weight, 60, -3., 3.);

        JSFillHist(this_region, "HT_"+this_region, HT, weight, 1000, 0., 1000.);

        JSFillHist(this_region, "Jet_Size_"+this_region, myjets.size(), weight, 10, 0., 10.);
        JSFillHist(this_region, "NBJets_"+this_region, NBJets, weight, 10, 0., 10.);

        FillLeptonPlots(leps, this_region, weight);

        if(n_lepton==1){
          JSFillHist(this_region, "MT_"+this_region, this_MT, weight, 500, 0., 500.);
        }

        if(n_lepton>=2){

          JSFillHist(this_region, "ZCand_Mass_"+this_region, Z.M(), weight, 7000, 0., 7000.);
          JSFillHist(this_region, "ZCand_Pt_"+this_region, Z.Pt(), weight, 500, 0., 500.);
          JSFillHist(this_region, "ZCand_Eta_"+this_region, Z.Eta(), weight, 60, -3., 3.);

        }



      } // END if(pass Region)

    } // END Loop mapRegionBool

  } // END Loop Suffixs

}
