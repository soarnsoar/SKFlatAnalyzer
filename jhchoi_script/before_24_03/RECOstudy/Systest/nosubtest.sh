###
#SKFlat.py -a BasicTest -i DYJets -n 1 -e 2017 --no_exec
#SKFlat.py -a B_In_GEN -i DYJets -n 1 -e 2017 --no_exec
#SKFlat.py -a B_Info_Analyzer -i DYJets -n 1 -e 2017 --no_exec
#SKFlat.py -a BBbar_Analyzer -i DYJets -n 1 -e 2017 --no_exec
#SKFlat.py -a BBbar_Analyzer_MiNLO -i DYJetsToEE_MiNNLO -n 1 -e 2017 --no_exec
#SKFlat.py -a ForTMVA_BBbarAnalyzer -i DYJetsToEE_MiNNLO -n 1 --reduction 1000 -e 2017 --no_exec


#SKFlat.py -a BBbarRecoTMVA -i DYJetsToEE_MiNNLO -n 1 --reduction 1000 -e 2017 --no_exec &> test_DY_EE.log&
#SKFlat.py -a BBbarRecoTMVA -i DYJetsToMuMu_MiNNLO -n 1 --reduction 1000 -e 2017 --no_exec &> test_DY_MuMu.log&
SKFlat.py -a SysTemplate -i TTLJ_powheg -n 1 --reduction 1000 -e 2017 --no_exec &> test_TTLJ_powheg.log&
#(SKFlat.py -a BBbarRecoTMVA -i TTLJ_powheg -n 1 --reduction 1000 -e 2017 --no_exec &> test_DY_TTLL.log;cat test_DY_TTLL.log)&
