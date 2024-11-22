SKIM=""
#FLAG="--userflags FlavourMatchOnly"
FLAG=""
REDUCTION="--reduction 10000"
SKFlat.py -a TTSemiLepTrueBJetAnalyzer -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG


