#ifndef SKFlatNtuple_h
#define SKFlatNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <iostream>

// Fixed size dimensions of array or collections stored in the TTree if any.

class SKFlatNtuple {
public :

   SKFlatNtuple();
   virtual ~SKFlatNtuple();

   virtual Int_t GetEntry(Long64_t entry);

   virtual void SetTreeName(TString tname){
     fChain = new TChain(tname);
   }

   virtual void AddFile(TString filename){
     fChain->Add(filename);
   }

   Long64_t MaxEvent;
   bool IsThisDataFile;
   virtual void Init();
   virtual void Loop();

   virtual void executeEvent(){

   };

   TChain *fChain;

   // Declaration of leaf types
   Bool_t          IsData;
   Int_t           nTotal;
   Int_t           run;
   ULong64_t       event;
   Int_t           lumi;
   Double_t        PUweight;
   Int_t           nPV;
   Bool_t          Flag_badMuons;
   Bool_t          Flag_duplicateMuons;
   Bool_t          Flag_noBadMuons;
   Bool_t          Flag_goodVertices;
   Bool_t          Flag_globalTightHalo2016Filter;
   Bool_t          Flag_HBHENoiseFilter;
   Bool_t          Flag_HBHENoiseIsoFilter;
   Bool_t          Flag_EcalDeadCellTriggerPrimitiveFilter;
   Bool_t          Flag_BadPFMuonFilter;
   Bool_t          Flag_BadChargedCandidateFilter;
   Bool_t          Flag_eeBadScFilter;
   Bool_t          Flag_ecalBadCalibFilter;
   Int_t           PVtrackSize;
   Double_t        PVchi2;
   Double_t        PVndof;
   Double_t        PVnormalizedChi2;
   Double_t        vertex_X;
   Double_t        vertex_Y;
   Double_t        vertex_Z;
   vector<string>  *HLT_TriggerName;
   vector<bool>    *HLT_TriggerFired;
   vector<int>     *HLT_TriggerPrescale;
   vector<double>  *jet_pt;
   vector<double>  *jet_eta;
   vector<double>  *jet_phi;
   vector<double>  *jet_charge;
   vector<double>  *jet_area;
   vector<double>  *jet_rho;
   vector<int>     *jet_partonFlavour;
   vector<int>     *jet_hadronFlavour;
   vector<double>  *jet_CSVv2;
   vector<double>  *jet_DeepCSV;
   vector<double>  *jet_DeepFlavour;
   vector<double>  *jet_CvsL;
   vector<double>  *jet_CvsB;
   vector<double>  *jet_DeepCvsL;
   vector<double>  *jet_DeepCvsB;
   vector<double>  *jet_chargedHadronEnergyFraction;
   vector<double>  *jet_neutralHadronEnergyFraction;
   vector<double>  *jet_neutralEmEnergyFraction;
   vector<double>  *jet_chargedEmEnergyFraction;
   vector<int>     *jet_chargedMultiplicity;
   vector<int>     *jet_neutralMultiplicity;
   vector<bool>    *jet_looseJetID;
   vector<bool>    *jet_tightJetID;
   vector<bool>    *jet_tightLepVetoJetID;
   vector<int>     *jet_partonPdgId;
   vector<int>     *jet_vtxNtracks;
   vector<double>  *jet_m;
   vector<double>  *jet_energy;
   vector<double>  *jet_PileupJetId;
   vector<double>  *jet_shiftedEnUp;
   vector<double>  *jet_shiftedEnDown;
   vector<double>  *fatjet_pt;
   vector<double>  *fatjet_eta;
   vector<double>  *fatjet_phi;
   vector<double>  *fatjet_charge;
   vector<double>  *fatjet_area;
   vector<double>  *fatjet_rho;
   vector<int>     *fatjet_partonFlavour;
   vector<int>     *fatjet_hadronFlavour;
   vector<double>  *fatjet_CSVv2;
   vector<double>  *fatjet_DeepCSV;
   vector<double>  *fatjet_DeepFlavour;
   vector<double>  *fatjet_CvsL;
   vector<double>  *fatjet_CvsB;
   vector<double>  *fatjet_DeepCvsL;
   vector<double>  *fatjet_DeepCvsB;
   vector<bool>    *fatjet_looseJetID;
   vector<bool>    *fatjet_tightJetID;
   vector<bool>    *fatjet_tightLepVetoJetID;
   vector<int>     *fatjet_partonPdgId;
   vector<int>     *fatjet_vtxNtracks;
   vector<double>  *fatjet_m;
   vector<double>  *fatjet_energy;
   vector<double>  *fatjet_puppi_tau1;
   vector<double>  *fatjet_puppi_tau2;
   vector<double>  *fatjet_puppi_tau3;
   vector<double>  *fatjet_puppi_tau4;
   vector<double>  *fatjet_softdropmass;
   vector<double>  *fatjet_chargedHadronEnergyFraction;
   vector<double>  *fatjet_neutralHadronEnergyFraction;
   vector<double>  *fatjet_neutralEmEnergyFraction;
   vector<double>  *fatjet_chargedEmEnergyFraction;
   vector<int>     *fatjet_chargedMultiplicity;
   vector<int>     *fatjet_neutralMultiplicity;
   vector<double>  *fatjet_shiftedEnUp;
   vector<double>  *fatjet_shiftedEnDown;
   vector<double>  *electron_MVAIso;
   vector<double>  *electron_MVANoIso;
   vector<double>  *electron_et;
   vector<double>  *electron_caloEnergy;
   vector<double>  *electron_Energy;
   vector<double>  *electron_Energy_Scale_Up;
   vector<double>  *electron_Energy_Scale_Down;
   vector<double>  *electron_Energy_Smear_Up;
   vector<double>  *electron_Energy_Smear_Down;
   vector<double>  *electron_pt;
   vector<double>  *electron_pt_Scale_Up;
   vector<double>  *electron_pt_Scale_Down;
   vector<double>  *electron_pt_Smear_Up;
   vector<double>  *electron_pt_Smear_Down;
   vector<double>  *electron_Px;
   vector<double>  *electron_Py;
   vector<double>  *electron_Pz;
   vector<double>  *electron_eta;
   vector<double>  *electron_phi;
   vector<int>     *electron_charge;
   vector<double>  *electron_gsfpt;
   vector<double>  *electron_gsfPx;
   vector<double>  *electron_gsfPy;
   vector<double>  *electron_gsfPz;
   vector<double>  *electron_gsfEta;
   vector<double>  *electron_gsfPhi;
   vector<int>     *electron_gsfCharge;
   vector<double>  *electron_scEta;
   vector<double>  *electron_scPhi;
   vector<double>  *electron_etaWidth;
   vector<double>  *electron_phiWidth;
   vector<double>  *electron_dEtaIn;
   vector<double>  *electron_dEtaInSeed;
   vector<double>  *electron_dPhiIn;
   vector<double>  *electron_sigmaIEtaIEta;
   vector<double>  *electron_Full5x5_SigmaIEtaIEta;
   vector<double>  *electron_HoverE;
   vector<double>  *electron_fbrem;
   vector<double>  *electron_eOverP;
   vector<double>  *electron_energyEC;
   vector<double>  *electron_Pnorm;
   vector<double>  *electron_InvEminusInvP;
   vector<double>  *electron_dxyVTX;
   vector<double>  *electron_dzVTX;
   vector<double>  *electron_dxy;
   vector<double>  *electron_sigdxy;
   vector<double>  *electron_dz;
   vector<double>  *electron_ip3D;
   vector<double>  *electron_sigip3D;
   vector<double>  *electron_dxyBS;
   vector<double>  *electron_dzBS;
   vector<double>  *electron_AEff03;
   vector<double>  *electron_chIso03;
   vector<double>  *electron_nhIso03;
   vector<double>  *electron_phIso03;
   vector<double>  *electron_pcIso03;
   vector<double>  *electron_puChIso03;
   vector<double>  *electron_chIso04;
   vector<double>  *electron_nhIso04;
   vector<double>  *electron_phIso04;
   vector<double>  *electron_pcIso04;
   vector<double>  *electron_puChIso04;
   vector<double>  *electron_relIsoCom03;
   vector<double>  *electron_relIsoCom04;
   vector<double>  *electron_relIsoBeta03;
   vector<double>  *electron_relIsoBeta04;
   vector<double>  *electron_relIsoRho03;
   vector<bool>    *electron_passConversionVeto;
   vector<bool>    *electron_isGsfCtfScPixChargeConsistent;
   vector<int>     *electron_mHits;
   vector<int>     *electron_crack;
   vector<int>     *electron_ecalDriven;
   vector<double>  *electron_isoEMHADDepth1;
   vector<double>  *electron_25over55;
   vector<double>  *electron_15over55;
   vector<double>  *electron_isoHADDepth2;
   vector<double>  *electron_isoptTrks;
   vector<double>  *electron_modIsoEMHADDepth1;
   vector<double>  *electron_modIsoptTrks;
   vector<double>  *electron_modIsoEMHADDepth1Orig;
   vector<double>  *electron_modIsoptTrksOrig;
   vector<double>  *electron_ambGsf0pt;
   vector<double>  *electron_ambGsf0Eta;
   vector<double>  *electron_ambGsf0Phi;
   vector<double>  *electron_ambGsf0Charge;
   vector<double>  *electron_ambGsf1pt;
   vector<double>  *electron_ambGsf1Eta;
   vector<double>  *electron_ambGsf1Phi;
   vector<double>  *electron_ambGsf1Charge;
   vector<double>  *electron_ambGsf2pt;
   vector<double>  *electron_ambGsf2Eta;
   vector<double>  *electron_ambGsf2Phi;
   vector<double>  *electron_ambGsf2Charge;
   vector<double>  *electron_ambGsf3pt;
   vector<double>  *electron_ambGsf3Eta;
   vector<double>  *electron_ambGsf3Phi;
   vector<double>  *electron_ambGsf3Charge;
   vector<double>  *electron_r9;
   vector<double>  *electron_scEnergy;
   vector<double>  *electron_scPreEnergy;
   vector<double>  *electron_scRawEnergy;
   vector<double>  *electron_scEt;
   vector<double>  *electron_E15;
   vector<double>  *electron_E25;
   vector<double>  *electron_E55;
   vector<double>  *electron_RelPFIso_dBeta;
   vector<double>  *electron_RelPFIso_Rho;
   vector<bool>    *electron_passVetoID;
   vector<bool>    *electron_passLooseID;
   vector<bool>    *electron_passMediumID;
   vector<bool>    *electron_passTightID;
   vector<bool>    *electron_passMVAID_noIso_WP80;
   vector<bool>    *electron_passMVAID_noIso_WP90;
   vector<bool>    *electron_passMVAID_iso_WP80;
   vector<bool>    *electron_passMVAID_iso_WP90;
   vector<bool>    *electron_passHEEPID;
   vector<double>  *electron_ptUnCorr;
   vector<double>  *electron_etaUnCorr;
   vector<double>  *electron_phiUnCorr;
   vector<double>  *electron_PxUnCorr;
   vector<double>  *electron_PyUnCorr;
   vector<double>  *electron_PzUnCorr;
   vector<double>  *electron_EnergyUnCorr;
   vector<double>  *electron_scEnergyUnCorr;
   vector<double>  *electron_scEtaUnCorr;
   vector<double>  *electron_scPhiUnCorr;
   vector<double>  *electron_scEtUnCorr;
   vector<double>  *electron_mva;
   vector<double>  *electron_zzmva;
   vector<int>     *electron_missinghits;
   vector<double>  *muon_PfChargedHadronIsoR05;
   vector<double>  *muon_PfNeutralHadronIsoR05;
   vector<double>  *muon_PfGammaIsoR05;
   vector<double>  *muon_PfChargedHadronIsoR04;
   vector<double>  *muon_PfNeutralHadronIsoR04;
   vector<double>  *muon_PfGammaIsoR04;
   vector<double>  *muon_PFSumPUIsoR04;
   vector<double>  *muon_PfChargedHadronIsoR03;
   vector<double>  *muon_PfNeutralHadronIsoR03;
   vector<double>  *muon_PfGammaIsoR03;
   vector<double>  *muon_PFSumPUIsoR03;
   vector<bool>    *muon_isPF;
   vector<bool>    *muon_isGlobal;
   vector<bool>    *muon_isTracker;
   vector<bool>    *muon_isStandAlone;
   vector<bool>    *muon_isTight;
   vector<bool>    *muon_isMedium;
   vector<bool>    *muon_isLoose;
   vector<bool>    *muon_isSoft;
   vector<bool>    *muon_isHighPt;
   vector<double>  *muon_dB;
   vector<double>  *muon_phi;
   vector<double>  *muon_eta;
   vector<double>  *muon_pt;
   vector<double>  *muon_cktpt;
   vector<double>  *muon_cktPx;
   vector<double>  *muon_cktPy;
   vector<double>  *muon_cktPz;
   vector<double>  *muon_cktptError;
   vector<double>  *muon_Px;
   vector<double>  *muon_Py;
   vector<double>  *muon_Pz;
   vector<double>  *muon_sumtrkpt;
   vector<double>  *muon_trkiso;
   vector<double>  *muon_hcaliso;
   vector<double>  *muon_ecaliso;
   vector<double>  *muon_trkisoR05;
   vector<double>  *muon_hcalisoR05;
   vector<double>  *muon_ecalisoR05;
   vector<int>     *muon_charge;
   vector<int>     *muon_nChambers;
   vector<int>     *muon_matchedstations;
   vector<int>     *muon_stationMask;
   vector<int>     *muon_nSegments;
   vector<double>  *muon_normchi;
   vector<int>     *muon_validhits;
   vector<int>     *muon_trackerHits;
   vector<int>     *muon_pixelHits;
   vector<int>     *muon_validmuonhits;
   vector<int>     *muon_trackerLayers;
   vector<double>  *muon_qoverp;
   vector<double>  *muon_theta;
   vector<double>  *muon_lambda;
   vector<double>  *muon_dxy;
   vector<double>  *muon_d0;
   vector<double>  *muon_dsz;
   vector<double>  *muon_dz;
   vector<double>  *muon_dxyBS;
   vector<double>  *muon_dzBS;
   vector<double>  *muon_dszBS;
   vector<double>  *muon_dxyVTX;
   vector<double>  *muon_dzVTX;
   vector<double>  *muon_dszVTX;
   vector<double>  *muon_dxycktVTX;
   vector<double>  *muon_dzcktVTX;
   vector<double>  *muon_dszcktVTX;
   vector<double>  *muon_vx;
   vector<double>  *muon_vy;
   vector<double>  *muon_vz;
   vector<double>  *muon_Best_pt;
   vector<double>  *muon_Best_ptError;
   vector<double>  *muon_Best_Px;
   vector<double>  *muon_Best_Py;
   vector<double>  *muon_Best_Pz;
   vector<double>  *muon_Best_eta;
   vector<double>  *muon_Best_phi;
   vector<double>  *muon_Inner_pt;
   vector<double>  *muon_Inner_ptError;
   vector<double>  *muon_Inner_Px;
   vector<double>  *muon_Inner_Py;
   vector<double>  *muon_Inner_Pz;
   vector<double>  *muon_Inner_eta;
   vector<double>  *muon_Inner_phi;
   vector<double>  *muon_Outer_pt;
   vector<double>  *muon_Outer_ptError;
   vector<double>  *muon_Outer_Px;
   vector<double>  *muon_Outer_Py;
   vector<double>  *muon_Outer_Pz;
   vector<double>  *muon_Outer_eta;
   vector<double>  *muon_Outer_phi;
   vector<double>  *muon_GLB_pt;
   vector<double>  *muon_GLB_ptError;
   vector<double>  *muon_GLB_Px;
   vector<double>  *muon_GLB_Py;
   vector<double>  *muon_GLB_Pz;
   vector<double>  *muon_GLB_eta;
   vector<double>  *muon_GLB_phi;
   vector<double>  *muon_TuneP_pt;
   vector<double>  *muon_TuneP_ptError;
   vector<double>  *muon_TuneP_Px;
   vector<double>  *muon_TuneP_Py;
   vector<double>  *muon_TuneP_Pz;
   vector<double>  *muon_TuneP_eta;
   vector<double>  *muon_TuneP_phi;
   vector<double>  *muon_roch_sf;
   vector<double>  *muon_roch_sf_up;
   vector<double>  *PDFWeights_Scale;
   vector<double>  *PDFWeights_Error;
   vector<double>  *PDFWeights_AlphaS;
   vector<double>  *gen_phi;
   vector<double>  *gen_eta;
   vector<double>  *gen_pt;
   vector<double>  *gen_Px;
   vector<double>  *gen_Py;
   vector<double>  *gen_Pz;
   vector<double>  *gen_E;
   vector<int>     *gen_mother_PID;
   vector<double>  *gen_mother_pt;
   vector<int>     *gen_mother_index;
   vector<int>     *gen_charge;
   vector<int>     *gen_status;
   vector<int>     *gen_PID;
   vector<int>     *gen_isPrompt;
   vector<int>     *gen_isPromptFinalState;
   vector<int>     *gen_isTauDecayProduct;
   vector<int>     *gen_isPromptTauDecayProduct;
   vector<int>     *gen_isDirectPromptTauDecayProductFinalState;
   vector<int>     *gen_isHardProcess;
   vector<int>     *gen_isLastCopy;
   vector<int>     *gen_isLastCopyBeforeFSR;
   vector<int>     *gen_isPromptDecayed;
   vector<int>     *gen_isDecayedLeptonHadron;
   vector<int>     *gen_fromHardProcessBeforeFSR;
   vector<int>     *gen_fromHardProcessDecayed;
   vector<int>     *gen_fromHardProcessFinalState;
   vector<int>     *gen_isMostlyLikePythia6Status3;
   Double_t        gen_weight;
   Double_t        genWeight_Q;
   Double_t        genWeight_X1;
   Double_t        genWeight_X2;
   Int_t           genWeight_id1;
   Int_t           genWeight_id2;
   Double_t        genWeight_alphaQCD;
   Double_t        genWeight_alphaQED;
   vector<double>  *photon_pt;
   vector<double>  *photon_eta;
   vector<double>  *photon_phi;
   vector<double>  *photon_scEta;
   vector<double>  *photon_scPhi;
   vector<double>  *photon_HoverE;
   vector<int>     *photon_hasPixelSeed;
   vector<double>  *photon_Full5x5_SigmaIEtaIEta;
   vector<double>  *photon_ChIso;
   vector<double>  *photon_NhIso;
   vector<double>  *photon_PhIso;
   vector<double>  *photon_ChIsoWithEA;
   vector<double>  *photon_NhIsoWithEA;
   vector<double>  *photon_PhIsoWithEA;
   vector<bool>    *photon_passMVAID_WP80;
   vector<bool>    *photon_passMVAID_WP90;
   vector<bool>    *photon_passLooseID;
   vector<bool>    *photon_passMediumID;
   vector<bool>    *photon_passTightID;
   vector<double>  *photon_ptUnCorr;
   vector<double>  *photon_etaUnCorr;
   vector<double>  *photon_phiUnCorr;
   Int_t           nPileUp;
   Double_t        pileUpReweightIn;
   Double_t        pileUpReweight;
   Double_t        pileUpReweightPlus;
   Double_t        pileUpReweightMinus;
   Double_t        pileUpReweightInMuonPhys;
   Double_t        pileUpReweightMuonPhys;
   Double_t        pileUpReweightPlusMuonPhys;
   Double_t        pileUpReweightMinusMuonPhys;
   Double_t        pfMET_pt;
   Double_t        pfMET_phi;
   Double_t        pfMET_Px;
   Double_t        pfMET_Py;
   Double_t        pfMET_SumEt;
   Double_t        pfMET_Type1_pt;
   Double_t        pfMET_Type1_phi;
   Double_t        pfMET_Type1_Px;
   Double_t        pfMET_Type1_Py;
   Double_t        pfMET_Type1_SumEt;
   Double_t        pfMET_Type1_PhiCor_pt;
   Double_t        pfMET_Type1_PhiCor_phi;
   Double_t        pfMET_Type1_PhiCor_Px;
   Double_t        pfMET_Type1_PhiCor_Py;
   Double_t        pfMET_Type1_PhiCor_SumEt;

   // List of branches
   TBranch        *b_IsData;   //!
   TBranch        *b_nTotal;   //!
   TBranch        *b_runNum;   //!
   TBranch        *b_evtNum;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_PUweight;   //!
   TBranch        *b_nVertices;   //!
   TBranch        *b_Flag_badMuons;   //!
   TBranch        *b_Flag_duplicateMuons;   //!
   TBranch        *b_Flag_noBadMuons;   //!
   TBranch        *b_Flag_goodVertices;   //!
   TBranch        *b_Flag_globalTightHalo2016Filter;   //!
   TBranch        *b_Flag_HBHENoiseFilter;   //!
   TBranch        *b_Flag_HBHENoiseIsoFilter;   //!
   TBranch        *b_Flag_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_Flag_BadPFMuonFilter;   //!
   TBranch        *b_Flag_BadChargedCandidateFilter;   //!
   TBranch        *b_Flag_eeBadScFilter;   //!
   TBranch        *b_Flag_ecalBadCalibFilter;   //!
   TBranch        *b_PVtrackSize;   //!
   TBranch        *b_PVchi2;   //!
   TBranch        *b_PVndof;   //!
   TBranch        *b_PVnormalizedChi2;   //!
   TBranch        *b_PVx;   //!
   TBranch        *b_PVy;   //!
   TBranch        *b_PVz;   //!
   TBranch        *b_HLT_TriggerName;   //!
   TBranch        *b_HLT_TriggerFired;   //!
   TBranch        *b_HLT_TriggerPrescale;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_charge;   //!
   TBranch        *b_jet_area;   //!
   TBranch        *b_jet_rho;   //!
   TBranch        *b_jet_partonFlavour;   //!
   TBranch        *b_jet_hadronFlavour;   //!
   TBranch        *b_jet_CSVv2;   //!
   TBranch        *b_jet_DeepCSV;   //!
   TBranch        *b_jet_DeepFlavour;   //!
   TBranch        *b_jet_CvsL;   //!
   TBranch        *b_jet_CvsB;   //!
   TBranch        *b_jet_DeepCvsL;   //!
   TBranch        *b_jet_DeepCvsB;   //!
   TBranch        *b_jet_chargedHadronEnergyFraction;   //!
   TBranch        *b_jet_neutralHadronEnergyFraction;   //!
   TBranch        *b_jet_neutralEmEnergyFraction;   //!
   TBranch        *b_jet_chargedEmEnergyFraction;   //!
   TBranch        *b_jet_chargedMultiplicity;   //!
   TBranch        *b_jet_neutralMultiplicity;   //!
   TBranch        *b_jet_looseJetID;   //!
   TBranch        *b_jet_tightJetID;   //!
   TBranch        *b_jet_tightLepVetoJetID;   //!
   TBranch        *b_jet_partonPdgId;   //!
   TBranch        *b_jet_vtxNtracks;   //!
   TBranch        *b_jet_m;   //!
   TBranch        *b_jet_energy;   //!
   TBranch        *b_jet_PileupJetId;   //!
   TBranch        *b_jet_shiftedEnUp;   //!
   TBranch        *b_jet_shiftedEnDown;   //!
   TBranch        *b_fatjet_pt;   //!
   TBranch        *b_fatjet_eta;   //!
   TBranch        *b_fatjet_phi;   //!
   TBranch        *b_fatjet_charge;   //!
   TBranch        *b_fatjet_area;   //!
   TBranch        *b_fatjet_rho;   //!
   TBranch        *b_fatjet_partonFlavour;   //!
   TBranch        *b_fatjet_hadronFlavour;   //!
   TBranch        *b_fatjet_CSVv2;   //!
   TBranch        *b_fatjet_DeepCSV;   //!
   TBranch        *b_fatjet_DeepFlavour;   //!
   TBranch        *b_fatjet_CvsL;   //!
   TBranch        *b_fatjet_CvsB;   //!
   TBranch        *b_fatjet_DeepCvsL;   //!
   TBranch        *b_fatjet_DeepCvsB;   //!
   TBranch        *b_fatjet_looseJetID;   //!
   TBranch        *b_fatjet_tightJetID;   //!
   TBranch        *b_fatjet_tightLepVetoJetID;   //!
   TBranch        *b_fatjet_partonPdgId;   //!
   TBranch        *b_fatjet_vtxNtracks;   //!
   TBranch        *b_fatjet_m;   //!
   TBranch        *b_fatjet_energy;   //!
   TBranch        *b_fatjet_puppi_tau1;   //!
   TBranch        *b_fatjet_puppi_tau2;   //!
   TBranch        *b_fatjet_puppi_tau3;   //!
   TBranch        *b_fatjet_puppi_tau4;   //!
   TBranch        *b_fatjet_softdropmass;   //!
   TBranch        *b_fatjet_chargedHadronEnergyFraction;   //!
   TBranch        *b_fatjet_neutralHadronEnergyFraction;   //!
   TBranch        *b_fatjet_neutralEmEnergyFraction;   //!
   TBranch        *b_fatjet_chargedEmEnergyFraction;   //!
   TBranch        *b_fatjet_chargedMultiplicity;   //!
   TBranch        *b_fatjet_neutralMultiplicity;   //!
   TBranch        *b_fatjet_shiftedEnUp;   //!
   TBranch        *b_fatjet_shiftedEnDown;   //!
   TBranch        *b_electron_MVAIso;   //!
   TBranch        *b_electron_MVANoIso;   //!
   TBranch        *b_electron_et;   //!
   TBranch        *b_electron_caloEnergy;   //!
   TBranch        *b_electron_Energy;   //!
   TBranch        *b_electron_Energy_Scale_Up;   //!
   TBranch        *b_electron_Energy_Scale_Down;   //!
   TBranch        *b_electron_Energy_Smear_Up;   //!
   TBranch        *b_electron_Energy_Smear_Down;   //!
   TBranch        *b_electron_pt;   //!
   TBranch        *b_electron_pt_Scale_Up;   //!
   TBranch        *b_electron_pt_Scale_Down;   //!
   TBranch        *b_electron_pt_Smear_Up;   //!
   TBranch        *b_electron_pt_Smear_Down;   //!
   TBranch        *b_electron_Px;   //!
   TBranch        *b_electron_Py;   //!
   TBranch        *b_electron_Pz;   //!
   TBranch        *b_electron_eta;   //!
   TBranch        *b_electron_phi;   //!
   TBranch        *b_electron_charge;   //!
   TBranch        *b_electron_gsfpt;   //!
   TBranch        *b_electron_gsfPx;   //!
   TBranch        *b_electron_gsfPy;   //!
   TBranch        *b_electron_gsfPz;   //!
   TBranch        *b_electron_gsfEta;   //!
   TBranch        *b_electron_gsfPhi;   //!
   TBranch        *b_electron_gsfCharge;   //!
   TBranch        *b_electron_scEta;   //!
   TBranch        *b_electron_scPhi;   //!
   TBranch        *b_electron_etaWidth;   //!
   TBranch        *b_electron_phiWidth;   //!
   TBranch        *b_electron_dEtaIn;   //!
   TBranch        *b_electron_dEtaInSeed;   //!
   TBranch        *b_electron_dPhiIn;   //!
   TBranch        *b_electron_sigmaIEtaIEta;   //!
   TBranch        *b_electron_Full5x5_SigmaIEtaIEta;   //!
   TBranch        *b_electron_HoverE;   //!
   TBranch        *b_electron_fbrem;   //!
   TBranch        *b_electron_eOverP;   //!
   TBranch        *b_electron_energyEC;   //!
   TBranch        *b_electron_Pnorm;   //!
   TBranch        *b_electron_InvEminusInvP;   //!
   TBranch        *b_electron_dxyVTX;   //!
   TBranch        *b_electron_dzVTX;   //!
   TBranch        *b_electron_dxy;   //!
   TBranch        *b_electron_sigdxy;   //!
   TBranch        *b_electron_dz;   //!
   TBranch        *b_electron_ip3D;   //!
   TBranch        *b_electron_sigip3D;   //!
   TBranch        *b_electron_dxyBS;   //!
   TBranch        *b_electron_dzBS;   //!
   TBranch        *b_electron_AEff03;   //!
   TBranch        *b_electron_chIso03;   //!
   TBranch        *b_electron_nhIso03;   //!
   TBranch        *b_electron_phIso03;   //!
   TBranch        *b_electron_pcIso03;   //!
   TBranch        *b_electron_puChIso03;   //!
   TBranch        *b_electron_chIso04;   //!
   TBranch        *b_electron_nhIso04;   //!
   TBranch        *b_electron_phIso04;   //!
   TBranch        *b_electron_pcIso04;   //!
   TBranch        *b_electron_puChIso04;   //!
   TBranch        *b_electron_relIsoCom03;   //!
   TBranch        *b_electron_relIsoCom04;   //!
   TBranch        *b_electron_relIsoBeta03;   //!
   TBranch        *b_electron_relIsoBeta04;   //!
   TBranch        *b_electron_relIsoRho03;   //!
   TBranch        *b_electron_passConversionVeto;   //!
   TBranch        *b_electron_isGsfCtfScPixChargeConsistent;   //!
   TBranch        *b_electron_mHits;   //!
   TBranch        *b_electron_crack;   //!
   TBranch        *b_electron_ecalDriven;   //!
   TBranch        *b_electron_isoEMHADDepth1;   //!
   TBranch        *b_electron_25over55;   //!
   TBranch        *b_electron_15over55;   //!
   TBranch        *b_electron_isoHADDepth2;   //!
   TBranch        *b_electron_isoptTrks;   //!
   TBranch        *b_electron_modIsoEMHADDepth1;   //!
   TBranch        *b_electron_modIsoptTrks;   //!
   TBranch        *b_electron_modIsoEMHADDepth1Orig;   //!
   TBranch        *b_electron_modIsoptTrksOrig;   //!
   TBranch        *b_electron_ambGsf0pt;   //!
   TBranch        *b_electron_ambGsf0Eta;   //!
   TBranch        *b_electron_ambGsf0Phi;   //!
   TBranch        *b_electron_ambGsf0Charge;   //!
   TBranch        *b_electron_ambGsf1pt;   //!
   TBranch        *b_electron_ambGsf1Eta;   //!
   TBranch        *b_electron_ambGsf1Phi;   //!
   TBranch        *b_electron_ambGsf1Charge;   //!
   TBranch        *b_electron_ambGsf2pt;   //!
   TBranch        *b_electron_ambGsf2Eta;   //!
   TBranch        *b_electron_ambGsf2Phi;   //!
   TBranch        *b_electron_ambGsf2Charge;   //!
   TBranch        *b_electron_ambGsf3pt;   //!
   TBranch        *b_electron_ambGsf3Eta;   //!
   TBranch        *b_electron_ambGsf3Phi;   //!
   TBranch        *b_electron_ambGsf3Charge;   //!
   TBranch        *b_electron_r9;   //!
   TBranch        *b_electron_scEnergy;   //!
   TBranch        *b_electron_scPreEnergy;   //!
   TBranch        *b_electron_scRawEnergy;   //!
   TBranch        *b_electron_scEt;   //!
   TBranch        *b_electron_E15;   //!
   TBranch        *b_electron_E25;   //!
   TBranch        *b_electron_E55;   //!
   TBranch        *b_electron_RelPFIso_dBeta;   //!
   TBranch        *b_electron_RelPFIso_Rho;   //!
   TBranch        *b_electron_passVetoID;   //!
   TBranch        *b_electron_passLooseID;   //!
   TBranch        *b_electron_passMediumID;   //!
   TBranch        *b_electron_passTightID;   //!
   TBranch        *b_electron_passMVAID_noIso_WP80;   //!
   TBranch        *b_electron_passMVAID_noIso_WP90;   //!
   TBranch        *b_electron_passMVAID_iso_WP80;   //!
   TBranch        *b_electron_passMVAID_iso_WP90;   //!
   TBranch        *b_electron_passHEEPID;   //!
   TBranch        *b_electron_ptUnCorr;   //!
   TBranch        *b_electron_etaUnCorr;   //!
   TBranch        *b_electron_phiUnCorr;   //!
   TBranch        *b_electron_PxUnCorr;   //!
   TBranch        *b_electron_PyUnCorr;   //!
   TBranch        *b_electron_PzUnCorr;   //!
   TBranch        *b_electron_EnergyUnCorr;   //!
   TBranch        *b_electron_scEnergyUnCorr;   //!
   TBranch        *b_electron_scEtaUnCorr;   //!
   TBranch        *b_electron_scPhiUnCorr;   //!
   TBranch        *b_electron_scEtUnCorr;   //!
   TBranch        *b_electron_mva;   //!
   TBranch        *b_electron_zzmva;   //!
   TBranch        *b_electron_missinghits;   //!
   TBranch        *b_muon_PfChargedHadronIsoR05;   //!
   TBranch        *b_muon_PfNeutralHadronIsoR05;   //!
   TBranch        *b_muon_PfGammaIsoR05;   //!
   TBranch        *b_muon_PfChargedHadronIsoR04;   //!
   TBranch        *b_muon_PfNeutralHadronIsoR04;   //!
   TBranch        *b_muon_PfGammaIsoR04;   //!
   TBranch        *b_muon_PFSumPUIsoR04;   //!
   TBranch        *b_muon_PfChargedHadronIsoR03;   //!
   TBranch        *b_muon_PfNeutralHadronIsoR03;   //!
   TBranch        *b_muon_PfGammaIsoR03;   //!
   TBranch        *b_muon_PFSumPUIsoR03;   //!
   TBranch        *b_muon_isPF;   //!
   TBranch        *b_muon_isGlobal;   //!
   TBranch        *b_muon_isTracker;   //!
   TBranch        *b_muon_isStandAlone;   //!
   TBranch        *b_muon_isTight;   //!
   TBranch        *b_muon_isMedium;   //!
   TBranch        *b_muon_isLoose;   //!
   TBranch        *b_muon_isSoft;   //!
   TBranch        *b_muon_isHighPt;   //!
   TBranch        *b_muon_dB;   //!
   TBranch        *b_muon_phi;   //!
   TBranch        *b_muon_eta;   //!
   TBranch        *b_muon_pt;   //!
   TBranch        *b_muon_cktpt;   //!
   TBranch        *b_muon_cktPx;   //!
   TBranch        *b_muon_cktPy;   //!
   TBranch        *b_muon_cktPz;   //!
   TBranch        *b_muon_cktptError;   //!
   TBranch        *b_muon_Px;   //!
   TBranch        *b_muon_Py;   //!
   TBranch        *b_muon_Pz;   //!
   TBranch        *b_muon_sumtrkpt;   //!
   TBranch        *b_muon_trkiso;   //!
   TBranch        *b_muon_hcaliso;   //!
   TBranch        *b_muon_ecaliso;   //!
   TBranch        *b_muon_trkisoR05;   //!
   TBranch        *b_muon_hcalisoR05;   //!
   TBranch        *b_muon_ecalisoR05;   //!
   TBranch        *b_muon_charge;   //!
   TBranch        *b_muon_nChambers;   //!
   TBranch        *b_muon_matchedstations;   //!
   TBranch        *b_muon_stationMask;   //!
   TBranch        *b_muon_nSegments;   //!
   TBranch        *b_muon_normchi;   //!
   TBranch        *b_muon_validhits;   //!
   TBranch        *b_muon_trackerHits;   //!
   TBranch        *b_muon_pixelHits;   //!
   TBranch        *b_muon_validmuonhits;   //!
   TBranch        *b_muon_trackerLayers;   //!
   TBranch        *b_muon_qoverp;   //!
   TBranch        *b_muon_theta;   //!
   TBranch        *b_muon_lambda;   //!
   TBranch        *b_muon_dxy;   //!
   TBranch        *b_muon_d0;   //!
   TBranch        *b_muon_dsz;   //!
   TBranch        *b_muon_dz;   //!
   TBranch        *b_muon_dxyBS;   //!
   TBranch        *b_muon_dzBS;   //!
   TBranch        *b_muon_dszBS;   //!
   TBranch        *b_muon_dxyVTX;   //!
   TBranch        *b_muon_dzVTX;   //!
   TBranch        *b_muon_dszVTX;   //!
   TBranch        *b_muon_dxycktVTX;   //!
   TBranch        *b_muon_dzcktVTX;   //!
   TBranch        *b_muon_dszcktVTX;   //!
   TBranch        *b_muon_vx;   //!
   TBranch        *b_muon_vy;   //!
   TBranch        *b_muon_vz;   //!
   TBranch        *b_muon_Best_pt;   //!
   TBranch        *b_muon_Best_ptError;   //!
   TBranch        *b_muon_Best_Px;   //!
   TBranch        *b_muon_Best_Py;   //!
   TBranch        *b_muon_Best_Pz;   //!
   TBranch        *b_muon_Best_eta;   //!
   TBranch        *b_muon_Best_phi;   //!
   TBranch        *b_muon_Inner_pt;   //!
   TBranch        *b_muon_Inner_ptError;   //!
   TBranch        *b_muon_Inner_Px;   //!
   TBranch        *b_muon_Inner_Py;   //!
   TBranch        *b_muon_Inner_Pz;   //!
   TBranch        *b_muon_Inner_eta;   //!
   TBranch        *b_muon_Inner_phi;   //!
   TBranch        *b_muon_Outer_pt;   //!
   TBranch        *b_muon_Outer_ptError;   //!
   TBranch        *b_muon_Outer_Px;   //!
   TBranch        *b_muon_Outer_Py;   //!
   TBranch        *b_muon_Outer_Pz;   //!
   TBranch        *b_muon_Outer_eta;   //!
   TBranch        *b_muon_Outer_phi;   //!
   TBranch        *b_muon_GLB_pt;   //!
   TBranch        *b_muon_GLB_ptError;   //!
   TBranch        *b_muon_GLB_Px;   //!
   TBranch        *b_muon_GLB_Py;   //!
   TBranch        *b_muon_GLB_Pz;   //!
   TBranch        *b_muon_GLB_eta;   //!
   TBranch        *b_muon_GLB_phi;   //!
   TBranch        *b_muon_TuneP_pt;   //!
   TBranch        *b_muon_TuneP_ptError;   //!
   TBranch        *b_muon_TuneP_Px;   //!
   TBranch        *b_muon_TuneP_Py;   //!
   TBranch        *b_muon_TuneP_Pz;   //!
   TBranch        *b_muon_TuneP_eta;   //!
   TBranch        *b_muon_TuneP_phi;   //!
   TBranch        *b_muon_roch_sf;   //!
   TBranch        *b_muon_roch_sf_up;   //!
   TBranch        *b_PDFWeights_Scale;   //!
   TBranch        *b_PDFWeights_Error;   //!
   TBranch        *b_PDFWeights_AlphaS;   //!
   TBranch        *b_gen_phi;   //!
   TBranch        *b_gen_eta;   //!
   TBranch        *b_gen_pt;   //!
   TBranch        *b_gen_Px;   //!
   TBranch        *b_gen_Py;   //!
   TBranch        *b_gen_Pz;   //!
   TBranch        *b_gen_E;   //!
   TBranch        *b_gen_mother_PID;   //!
   TBranch        *b_gen_mother_pt;   //!
   TBranch        *b_gen_mother_index;   //!
   TBranch        *b_gen_charge;   //!
   TBranch        *b_gen_status;   //!
   TBranch        *b_gen_PID;   //!
   TBranch        *b_gen_isPrompt;   //!
   TBranch        *b_gen_isPromptFinalState;   //!
   TBranch        *b_gen_isTauDecayProduct;   //!
   TBranch        *b_gen_isPromptTauDecayProduct;   //!
   TBranch        *b_gen_isDirectPromptTauDecayProductFinalState;   //!
   TBranch        *b_gen_isHardProcess;   //!
   TBranch        *b_gen_isLastCopy;   //!
   TBranch        *b_gen_isLastCopyBeforeFSR;   //!
   TBranch        *b_gen_isPromptDecayed;   //!
   TBranch        *b_gen_isDecayedLeptonHadron;   //!
   TBranch        *b_gen_fromHardProcessBeforeFSR;   //!
   TBranch        *b_gen_fromHardProcessDecayed;   //!
   TBranch        *b_gen_fromHardProcessFinalState;   //!
   TBranch        *b_gen_isMostlyLikePythia6Status3;   //!
   TBranch        *b_gen_weight;   //!
   TBranch        *b_genWeight_Q;   //!
   TBranch        *b_genWeight_X1;   //!
   TBranch        *b_genWeight_X2;   //!
   TBranch        *b_genWeight_id1;   //!
   TBranch        *b_genWeight_id2;   //!
   TBranch        *b_genWeight_alphaQCD;   //!
   TBranch        *b_genWeight_alphaQED;   //!
   TBranch        *b_photon_pt;   //!
   TBranch        *b_photon_eta;   //!
   TBranch        *b_photon_phi;   //!
   TBranch        *b_photon_scEta;   //!
   TBranch        *b_photon_scPhi;   //!
   TBranch        *b_photon_HoverE;   //!
   TBranch        *b_photon_hasPixelSeed;   //!
   TBranch        *b_photon_Full5x5_SigmaIEtaIEta;   //!
   TBranch        *b_photon_ChIso;   //!
   TBranch        *b_photon_NhIso;   //!
   TBranch        *b_photon_PhIso;   //!
   TBranch        *b_photon_ChIsoWithEA;   //!
   TBranch        *b_photon_NhIsoWithEA;   //!
   TBranch        *b_photon_PhIsoWithEA;   //!
   TBranch        *b_photon_passMVAID_WP80;   //!
   TBranch        *b_photon_passMVAID_WP90;   //!
   TBranch        *b_photon_passLooseID;   //!
   TBranch        *b_photon_passMediumID;   //!
   TBranch        *b_photon_passTightID;   //!
   TBranch        *b_photon_ptUnCorr;   //!
   TBranch        *b_photon_etaUnCorr;   //!
   TBranch        *b_photon_phiUnCorr;   //!
   TBranch        *b_nPileUp;   //!
   TBranch        *b_pileUpReweightIn;   //!
   TBranch        *b_pileUpReweight;   //!
   TBranch        *b_pileUpReweightPlus;   //!
   TBranch        *b_pileUpReweightMinus;   //!
   TBranch        *b_pileUpReweightInMuonPhys;   //!
   TBranch        *b_pileUpReweightMuonPhys;   //!
   TBranch        *b_pileUpReweightPlusMuonPhys;   //!
   TBranch        *b_pileUpReweightMinusMuonPhys;   //!
   TBranch        *b_pfMET_pt;   //!
   TBranch        *b_pfMET_phi;   //!
   TBranch        *b_pfMET_Px;   //!
   TBranch        *b_pfMET_Py;   //!
   TBranch        *b_pfMET_SumEt;   //!
   TBranch        *b_pfMET_Type1_pt;   //!
   TBranch        *b_pfMET_Type1_phi;   //!
   TBranch        *b_pfMET_Type1_Px;   //!
   TBranch        *b_pfMET_Type1_Py;   //!
   TBranch        *b_pfMET_Type1_SumEt;   //!
   TBranch        *b_pfMET_Type1_PhiCor_pt;   //!
   TBranch        *b_pfMET_Type1_PhiCor_phi;   //!
   TBranch        *b_pfMET_Type1_PhiCor_Px;   //!
   TBranch        *b_pfMET_Type1_PhiCor_Py;   //!
   TBranch        *b_pfMET_Type1_PhiCor_SumEt;   //!

};

#endif
