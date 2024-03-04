SKFlat.py -a LepJetChargeReliability_RECO -l inputlist_major.txt -n 300 -e 2017 --skim SkimTree_Dilepton &> submit_MC_major.log&
SKFlat.py -a LepJetChargeReliability_RECO -l inputlist_minor.txt -n 50 -e 2017 --skim SkimTree_Dilepton &> submit_MC_minor.log&
SKFlat.py -a LepJetChargeReliability_RECO -i DoubleMuon -n 50 -e 2017 --skim SkimTree_Dilepton &> submit_Muon.log&
SKFlat.py -a LepJetChargeReliability_RECO -i DoubleEG -n 50 -e 2017 --skim SkimTree_Dilepton &> submit_Electron.log&
