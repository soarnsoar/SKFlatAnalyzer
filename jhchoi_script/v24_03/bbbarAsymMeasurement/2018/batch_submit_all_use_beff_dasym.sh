#bbbarAsymMeasurement
mkdir -p use_beff_dasym_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags use_beff_dasym"
#FLAG=""
YEAR=2018
NMAX="--nmax 300"
#NMAX=""
NCPU="--req_cpus 2"

SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${NCPU} &> use_beff_dasym_logs/major.log&
sleep 10
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${NCPU} &> use_beff_dasym_logs/minor.log&
sleep 10
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${NCPU} &> use_beff_dasym_logs/tW.log&
sleep 10
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} ${NCPU} &> use_beff_dasym_logs/DoubleMuon.log&
sleep 10
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG ${NMAX} ${NCPU} &> use_beff_dasym_logs/EGamma.log&
sleep 10
SKFlat.py -a bbbarAsymMeasurement -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${NCPU} &> use_beff_dasym_logs/NoSkim.log&
sleep 10
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${NCPU} &> use_beff_dasym_logs/VV.log&

