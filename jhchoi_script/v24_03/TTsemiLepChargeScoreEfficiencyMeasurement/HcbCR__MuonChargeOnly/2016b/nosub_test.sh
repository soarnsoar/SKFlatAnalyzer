SKIM=""
FLAG=""
FLAG="--userflags runSys"
REDUCTION="--reduction 100"
SKFlat.py -a DiLeptonAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a DiLeptonAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

