SKIM=""
FLAG=""
#FLAG="--userflags use_beff"
FLAG="--userflags runSys,use_beffs,ForMeasure"

REDUCTION="--reduction 20000"

SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

