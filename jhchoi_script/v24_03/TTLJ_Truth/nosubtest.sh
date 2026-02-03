#EEMu_MuMuE_Method
mkdir -p logs/

SKIM=""
FLAG="--no_exec"

#ARR_YEAR=(2017 2016a 2016b 2018)
ARR_YEAR=(2017 )
NMAX=" --nmax 120 "
njob=" -n 10 "
for YEAR in ${ARR_YEAR[@]};do

    SKFlat.py -a TTLJ_Truth -i TTLJ_powheg $NMAX $SKIM -e ${YEAR} $njob $FLAG 
    sleep 10



done
