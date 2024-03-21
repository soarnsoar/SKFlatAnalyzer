###

#(SKFlat.py -a BBbarRecoTMVA -i TTLJ_powheg -n 1 --reduction 1000 -e 2017 --no_exec &> test_DY_TTLL.log;cat test_DY_TTLL.log)&

##test treemode
#(SKFlat.py -a LepJetChargeReliability_RECO -i DYJetsToEE_MiNNLO -n 1 --reduction 1000 -e 2017 --no_exec --userflag TreeMode &> test_DYJetsToEE_MiNNLO.log;cat test_DYJetsToEE_MiNNLO.log)&
##test trainingmode
SKFlat.py -a TTsemilep_JetAssignScore_TrainingInput -i TTLJ_powheg -n 1 --reduction 1000 -e 2017 --no_exec


