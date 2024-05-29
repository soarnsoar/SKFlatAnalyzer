SKIM="--skim SkimTree_SingleLepton"
FLAG=""
FLAG="--userflags runSys"
REDUCTION="--reduction 100"
SKFlat.py -a SingleLeptonAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a SingleLeptonAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

