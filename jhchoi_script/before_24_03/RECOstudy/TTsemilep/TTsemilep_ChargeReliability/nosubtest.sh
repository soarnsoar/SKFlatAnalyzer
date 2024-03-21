###


#SKFlat.py -a TTsemilep_ChargeReliability -i TTLJ_powheg -n 1 --reduction 1000 -e 2017 --no_exec 

#SKFlat.py -a TTsemilep_ChargeReliability -i TTLJ_powheg -n 1 --reduction 1000 -e 2017 --userflags RunSyst,RunSoftMuon,RunHadronSide,RunRelib --no_exec
SKFlat.py -a TTsemilep_ChargeReliability -i TTLJ_powheg -n 1 --reduction 10000 -e 2017 --userflags RunSyst,RunSoftMuon,RunHadronSide,RunChAcc --no_exec
#SKFlat.py -a TTsemilep_ChargeReliability -i TTLJ_powheg -n 1 --reduction 1000 -e 2017 --userflags RunSyst --no_exec
