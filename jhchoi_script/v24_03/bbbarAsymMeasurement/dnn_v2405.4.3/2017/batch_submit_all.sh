#bbbarAsymMeasurement
mkdir -p logs/

SKIM="--skim SkimTree_Dilepton"
#FLAG="--userflags runSys"
FLAG=""
FLAG="--userflags dnn_v2405.4.3"
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG &> logs/major.log&
sleep 3
SKFlat.py -a bbbarAsymMeasurement -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG &> logs/NoSkim.log&
sleep 3
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG &> logs/minor.log&
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG &> logs/tW.log&
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG &> logs/DoubleMuon.log&
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG &> logs/DoubleEG.log&

SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG &> logs/VV.log&

