#EEMu_MuMuE_Method
mkdir -p logs/

SKIM=""
FLAG=""

ARR_YEAR=(2017 2016a 2016b 2018)
NMAX=" --nmax 120 "
njob=" -n 30 "
for YEAR in ${ARR_YEAR[@]};do

    SKFlat.py -a TTLJ_Truth -i TTLJ_powheg $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/TTLJ_powheg_${YEAR}.log&
    sleep 10



done
