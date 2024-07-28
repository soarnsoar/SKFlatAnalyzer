SKIM=""
FLAG="--userflags HcbCR"
REDUCTION="--reduction 10000"
SKFlat.py -a TTSemiLepJetAssignment -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG


