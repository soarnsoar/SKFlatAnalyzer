#TTsemilep_ChargeReliability
SKFlat.py -a TTsemilep_ChargeReliability -l inputlist_major_temp.txt -n 300 -e 2017  &> submit_MC_major_temp.log&##300
sleep 1s
SKFlat.py -a TTsemilep_ChargeReliability -l inputlist_minor.txt -n 100 -e 2017  &> submit_MC_minor.log&##100
sleep 1s
SKFlat.py -a TTsemilep_ChargeReliability -l inputlist_QCD.txt -n 100 -e 2017  &> submit_QCD.log&
sleep 1s
SKFlat.py -a TTsemilep_ChargeReliability -l inputlist_tW.txt -n 100 -e 2017  &> submit_tW.log&
sleep 1s
SKFlat.py -a TTsemilep_ChargeReliability -i SingleMuon -n 100 -e 2017  &> submit_Muon.log&
sleep 1s
SKFlat.py -a TTsemilep_ChargeReliability -i SingleElectron -n 100 -e 2017  &> submit_Electron.log&

#SKFlat.py -a TTsemilep_ChargeReliability -i DYJetsToTauTau_MiNNLO -n 300 -e 2017  &> submit_DYJetsToTauTau_MiNNLO.log&
#SKFlat.py -a TTsemilep_ChargeReliability -i TTLJ_powheg  -n 300 -e 2017  &> TTLJ_powheg_test_only.log& 
