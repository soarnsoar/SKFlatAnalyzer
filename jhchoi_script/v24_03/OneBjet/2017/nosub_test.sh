SKIM=""
FLAG=""
FLAG="--userflags runSys"
REDUCTION="--reduction 10000"
#OneBjet
SKFlat.py -a OneBjet -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

