SKIM=""
FLAG=""
FLAG="--userflags scale00test"
#REDUCTION="--reduction 100"
REDUCTION=""
YEAR="2016a"
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -i TTLJ_powheg -n 2000 -e ${YEAR} $SKIM --no_exec ${REDUCTION} $FLAG


