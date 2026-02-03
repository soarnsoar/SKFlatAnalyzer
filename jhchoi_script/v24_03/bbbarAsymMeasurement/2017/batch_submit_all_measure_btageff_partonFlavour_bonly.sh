#bbbarAsymMeasurement
mkdir -p measure_btageff_partonFlavour_bonly_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags measure_btageff_partonFlavour_bonly"
#FLAG=""
NMAX="--nmax 150"





SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX} &> measure_btageff_partonFlavour_bonly_logs/DoubleEG.log&
sleep 7
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX} &> measure_btageff_partonFlavour_bonly_logs/DoubleMuon.log&
sleep 7
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} &> measure_btageff_partonFlavour_bonly_logs/tW.log&
sleep 7
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} &> measure_btageff_partonFlavour_bonly_logs/VV.log&
sleep 7
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} &> measure_btageff_partonFlavour_bonly_logs/minor.log&
sleep 7
SKFlat.py -a bbbarAsymMeasurement -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} &> measure_btageff_partonFlavour_bonly_logs/NoSkim.log&
sleep 7
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG ${NMAX} &> measure_btageff_partonFlavour_bonly_logs/major.log&
