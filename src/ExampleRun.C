#include "ExampleRun.h"

ExampleRun::ExampleRun(){

  hoe_max = -1.;

}
ExampleRun::~ExampleRun(){

}

void ExampleRun::executeEvent(){


  AnalyzerParameter param;

  param.Name = "HNPair";

  param.MCCorrrectionIgnoreNoHist = true;

  param.Electron_Tight_ID = "HNPairTight";

  param.Muon_Tight_ID = "POGTight";
  param.Muon_Tight_RelIso = 0.15;

  param.Jet_ID = "HN";
  param.FatJet_ID = "HN";

  executeEventFromParameter(param);

}

void ExampleRun::executeEventFromParameter(AnalyzerParameter param){

  Event ev = GetEvent();


  //==== Object pt ordering check
  vector<Muon> muons = GetAllMuons();
  if(muons.size()>0){

    for(unsigned int i=0; i<muons.size()-1; i++){
      Muon mu1 = muons.at(i);
      for(unsigned int j=i+1; j<muons.size(); j++){
        Muon mu2 = muons.at(j);

        if(mu1.Pt()<mu2.Pt()){
          FillHist("Muon_BeforeSorting_ReversedPt", 0., 1., 1, 0., 1.);
        }

      }
    }

    std::sort(muons.begin(), muons.end(), PtComparing);
    for(unsigned int i=0; i<muons.size()-1; i++){
      Muon mu1 = muons.at(i);
      for(unsigned int j=i+1; j<muons.size(); j++){
        Muon mu2 = muons.at(j);

        if(mu1.Pt()<mu2.Pt()){
          FillHist("Muon_AfterSorting_ReversedPt", 0., 1., 1, 0., 1.);
        }

      }

    }

  }

  vector<Electron> electrons = GetAllElectrons();
  if(electrons.size()>0){

    for(unsigned int i=0; i<electrons.size()-1; i++){
      Electron el1 = electrons.at(i);
      for(unsigned int j=i+1; j<electrons.size(); j++){
        Electron el2 = electrons.at(j);

        if(el1.Pt()<el2.Pt()){
          FillHist("Electron_BeforeSorting_ReversedPt", 0., 1., 1, 0., 1.);
        }

      }
    }

    std::sort(electrons.begin(), electrons.end(), PtComparing);
    for(unsigned int i=0; i<electrons.size()-1; i++){
      Electron el1 = electrons.at(i);
      for(unsigned int j=i+1; j<electrons.size(); j++){
        Electron el2 = electrons.at(j);

        if(el1.Pt()<el2.Pt()){
          FillHist("Electron_AfterSorting_ReversedPt", 0., 1., 1, 0., 1.);
        }

      }

    }

  }

  vector<Jet> jets = GetAllJets();
  if(jets.size()>0){

    for(unsigned int i=0; i<jets.size()-1; i++){
      Jet jet1 = jets.at(i);
      for(unsigned int j=i+1; j<jets.size(); j++){
        Jet jet2 = jets.at(j);

        if(jet1.Pt()<jet2.Pt()){
          FillHist("Jet_BeforeSorting_ReversedPt", 0., 1., 1, 0., 1.);
        }

      }
    }

    std::sort(jets.begin(), jets.end(), PtComparing);
    for(unsigned int i=0; i<jets.size()-1; i++){
      Jet jet1 = jets.at(i);
      for(unsigned int j=i+1; j<jets.size(); j++){
        Jet jet2 = jets.at(j);

        if(jet1.Pt()<jet2.Pt()){
          FillHist("Jet_AfterSorting_ReversedPt", 0., 1., 1, 0., 1.);
        }

      }

    }

  }

/*
  //==== Electron Custom-CutBased test

  FillHist("nPV", ev.nPV(), 1., 50, 0., 50.);

  std::vector<Electron> electrons_all = GetAllElectrons();
  std::vector<Muon>     muons_all     = GetAllMuons();

  //==== Comparing POG CutBased and Mine

  for(unsigned int i=0; i<electrons_all.size(); i++){

    Electron el = electrons_all.at(i);

    if(fabs(el.scEta())>2.5) continue;

    bool POGLoose = el.passLooseID();
    bool MyPOGLoose = el.Pass_CutBasedLoose();

    bool POGVeto = el.passVetoID();
    bool MyPOGVeto = el.Pass_CutBasedVeto();

    if(POGLoose)   FillHist("POGLoose", 0., 1., 2, 0., 2.);
    if(MyPOGLoose) FillHist("POGLoose", 1., 1., 2, 0., 2.);
    if(POGVeto)   FillHist("POGVeto", 0., 1., 2, 0., 2.);
    if(MyPOGVeto) FillHist("POGVeto", 1., 1., 2, 0., 2.);


    if( POGLoose && !MyPOGLoose ){
      FillHist("PassPOGLoose__NotMyPOGLoose", 0., 1., 1, 0., 1.);
    }

    if( !POGLoose && MyPOGLoose ){
      FillHist("PassMyPOGLoose__NotPOGLoose", 0., 1., 1, 0., 1.);
    }


    if( POGVeto && !MyPOGVeto ){
      FillHist("PassPOGVeto__NotMyPOGVeto", 0., 1., 1, 0., 1.);
    }
    if( !POGVeto && MyPOGVeto ){
      FillHist("PassMyPOGVeto__NotPOGVeto", 0., 1., 1, 0., 1.);

      cout << "==== DEBUG ====" << endl;
      cout << "MyPOGVeto && !POGVeto" << endl;
      cout << "===============" << endl;
      cout << "fabs(el.scEta()) = " << fabs(el.scEta()) << endl;
      cout << "el.Full5x5_sigmaIetaIeta() = " << el.Full5x5_sigmaIetaIeta() << endl;
      cout << "fabs(el.dEtaSeed()) = " << fabs(el.dEtaSeed()) << endl;
      cout << "fabs(el.dPhiIn()) = " << fabs(el.dPhiIn()) << endl;
      cout << "el.HoverE() = " << el.HoverE() << endl;
      cout << "  el.scE() = " << el.scE() << "\t" << "el.Rho() = " << el.Rho() << endl;
      cout << "el.RelIso() = " << el.RelIso() << endl;
      cout << "  el.Pt() = " << el.Pt() << endl;
      cout << "  el.UncorrE() = " << el.UncorrE() << endl;
      cout << "  el.E() = " << el.E() << endl;
      cout << "fabs(el.InvEminusInvP()) = " << fabs(el.InvEminusInvP()) << endl;
      cout << "el.NMissingHits() = " << el.NMissingHits() << endl;
      cout << "el.PassConversionVeto() =  " << el.PassConversionVeto() << endl;

    }

  } // END Electron Loop
  return;
*/
/*
  //==== Fake Rate

  double MinPt = 40;

  std::vector<Electron> Veto_electrons  = GetElectrons(param.Electron_Veto_ID, MinPt, 2.4);
  std::vector<Muon>     Veto_muons      = MuonWithoutGap(GetMuons(param.Muon_Veto_ID, MinPt, 2.4));
  int n_Veto_leptons = Veto_electrons.size()+Veto_muons.size();

  std::vector<Electron> Loose_electrons = GetElectrons(param.Electron_Loose_ID, MinPt, 2.4);
  std::vector<Muon>     Loose_muons     = MuonWithoutGap(GetMuons(param.Muon_Loose_ID, MinPt, 2.4));

  std::vector<Electron> Tight_electrons = GetElectrons(param.Electron_Tight_ID, MinPt, 2.4);
  std::vector<Muon>     Tight_muons     = MuonWithoutGap(GetMuons(param.Muon_Tight_ID, MinPt, 2.4));

  std::vector<Lepton *> leps_electron = MakeLeptonPointerVector(Loose_electrons, param.Electron_Tight_RelIso, param.Electron_UseMini);
  std::vector<Lepton *> leps_muon     = MakeLeptonPointerVector(Loose_muons, param.Muon_Tight_RelIso, param.Muon_UseMini);
  std::vector<Lepton *> leps;
  for(unsigned int i=0;i<leps_electron.size(); i++) leps.push_back( leps_electron.at(i) );
  for(unsigned int i=0;i<leps_muon.size(); i++) leps.push_back( leps_muon.at(i) );

  bool UseEvent = false;
  if(Loose_electrons.size()==2 && Loose_muons.size()==0){
    if(Loose_electrons.at(0).Charge()==Loose_electrons.at(1).Charge()){
      UseEvent = true;
    }
  }
  if(Loose_electrons.size()==0 && Loose_muons.size()==2){
    if(Loose_muons.at(0).Charge()==Loose_muons.at(1).Charge()){
      UseEvent = true;
    }
  }

  if(UseEvent){

    double mll = ( *(leps.at(0))+*(leps.at(1)) ).M();
    if(mll>120){
      double this_fr_weight = fakeEst.GetWeight(leps, param);
      if(fakeEst.HasLooseLepton) FillHist("hist_exp", 0., this_fr_weight, 1, 0., 1.);
      else                       FillHist("hist_obs", 0., 1., 1, 0., 1.);
    }
  }
*/

/*
  //==== Collineaer DiMuon

  bool PassTrigger = ev.PassTrigger("HLT_IsoMu27_v");
  if(!PassTrigger) return;
  std::vector<Muon>     Tight_muons     = GetMuons(param.Muon_Tight_ID, 10., 2.4);
  std::vector<Lepton *> leps;
  leps = MakeLeptonPointerVector(Tight_muons);

  if(Tight_muons.size()==0) return;
  for(unsigned int i=0; i<Tight_muons.size()-1; i++){
    Muon mu1 = Tight_muons.at(i);
    
    for(unsigned int j=i+1; j<Tight_muons.size(); j++){

      Muon mu2 = Tight_muons.at(j);

      TString chageconf = "OS";
      if(mu1.Charge()==mu2.Charge()) chageconf = "SS";

      double dRmuons = mu1.DeltaR(mu2);
      if(dRmuons < 0.1){

        JSFillHist(chageconf, "DeltaR_"+chageconf, dRmuons, 1, 100, 0., 0.1);

        double m_ll = (mu1+mu2).M();
        JSFillHist(chageconf, "m_ll_Wide_"+chageconf, m_ll, 1, 200, 0., 200.);
        JSFillHist(chageconf, "m_ll_Fine_"+chageconf, m_ll, 1, 200, 0., 20.);

      }


    }

  }
*/



}



