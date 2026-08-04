SKIM=""
FLAG=""
#FLAG="--userflags use_beff"
#FLAG="--userflags apply_bchargeeff_TT,use_beff"
#FLAG="--userflags measure_btageff_partonFlavour_bonly"
FLAG="--userflags use_beff_dasym"
FLAG="--userflags runSys,use_beff_dasym,ForMeasure"
#FLAG="--userflags use_beff_dasym,ForMeasure"
REDUCTION="--reduction 2000"

SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -i TTLL_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG



