#bbbarAsymMeasurement
mkdir -p measure_bchargeeff_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags measure_bchargeeff"
NMAX="--nmax 999"

SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG ${NMAX} &> measure_bchargeeff_logs/major.log&
SKFlat.py -a bbbarAsymMeasurement -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} &> measure_bchargeeff_logs/NoSkim.log&
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} &> measure_bchargeeff_logs/minor.log&
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} &> measure_bchargeeff_logs/tW.log&
#SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG &> measure_bchargeeff_logs/DoubleMuon.log&
#SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG &> measure_bchargeeff_logs/DoubleEG.log&
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} &> measure_bchargeeff_logs/VV.log&

