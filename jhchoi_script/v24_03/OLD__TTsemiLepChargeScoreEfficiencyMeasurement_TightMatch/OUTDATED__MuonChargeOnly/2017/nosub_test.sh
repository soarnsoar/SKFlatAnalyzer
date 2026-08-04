SKIM=""
FLAG=""
FLAG="--userflags MuonChargeOnly"
REDUCTION="--reduction 10000"

SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

