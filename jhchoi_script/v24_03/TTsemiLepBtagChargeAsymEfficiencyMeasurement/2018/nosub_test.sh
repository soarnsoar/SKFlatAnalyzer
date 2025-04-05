SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG=""

REDUCTION="--reduction 100"
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG


