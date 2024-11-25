#bbbarAsymMeasurement
mkdir -p syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
#FLAG=""
NMAX="--nmax 700"

SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_major.txt -n 40 -e 2017 $FLAG ${NMAX} &> syslogs/major.log&
sleep 120
SKFlat.py -a bbbarAsymMeasurement -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} &> syslogs/NoSkim.log&
sleep 5
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} &> syslogs/minor.log&
sleep 5
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} &> syslogs/tW.log&
sleep 5
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX} &> syslogs/DoubleMuon.log&
sleep 5
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX} &> syslogs/DoubleEG.log&
sleep 5
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} &> syslogs/VV.log&
sleep 5
