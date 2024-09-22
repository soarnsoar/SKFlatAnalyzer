SKIM=""
FLAG=""
FLAG="--userflags runSys"
REDUCTION="--reduction 10000"
#TwoBjets
SKFlat.py -a TwoBjets -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

