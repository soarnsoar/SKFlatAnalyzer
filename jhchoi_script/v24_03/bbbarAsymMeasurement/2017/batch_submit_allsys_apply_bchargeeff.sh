#bbbarAsymMeasurement
mkdir -p apply_bchargeeff_syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,apply_bchargeeff"
#FLAG=""
NMAX="--nmax 700"

SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG $NMAX &> apply_bchargeeff_syslogs/major.log&
SKFlat.py -a bbbarAsymMeasurement -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG $NMAX &> apply_bchargeeff_syslogs/NoSkim.log&
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG $NMAX &> apply_bchargeeff_syslogs/minor.log&
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG $NMAX &> apply_bchargeeff_syslogs/tW.log&
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG $NMAX &> apply_bchargeeff_syslogs/DoubleMuon.log&
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG $NMAX &> apply_bchargeeff_syslogs/DoubleEG.log&
SKFlat.py -a bbbarAsymMeasurement  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG $NMAX &> apply_bchargeeff_syslogs/VV.log&

