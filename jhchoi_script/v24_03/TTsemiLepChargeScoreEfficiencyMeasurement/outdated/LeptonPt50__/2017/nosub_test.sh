SKIM=""
FLAG=""
#FLAG="--userflags runSys"
REDUCTION="--reduction 10000"

SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

