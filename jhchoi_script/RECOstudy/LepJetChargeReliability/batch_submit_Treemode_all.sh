SKFlat.py -a LepJetChargeReliability_RECO -l inputlist_major.txt -n 300 -e 2017 --skim SkimTree_Dilepton --userflags TreeMode &> submit_MC_major_TREEMODE.log&
SKFlat.py -a LepJetChargeReliability_RECO -l inputlist_minor.txt -n 50 -e 2017 --skim SkimTree_Dilepton --userflags TreeMode &> submit_MC_minor_TREEMODE.log&
SKFlat.py -a LepJetChargeReliability_RECO -i DoubleMuon -n 50 -e 2017 --skim SkimTree_Dilepton --userflags TreeMode &> submit_Muon_TREEMODE.log&
SKFlat.py -a LepJetChargeReliability_RECO -i DoubleEG -n 50 -e 2017 --skim SkimTree_Dilepton --userflags TreeMode &> submit_Electron_TREEMODE.log&

