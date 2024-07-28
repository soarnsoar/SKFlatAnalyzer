SKIM=""
FLAG="--userflags reduction_1M"
REDUCTION="--reduction 10000"
SKFlat.py -a TTSemiLepJetAssignment_ProduceTrainingTree -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG


