SKIM="--skim SkimTree_Dilepton"
FLAG=""
FLAG="--userflags runSys"
FLAG="--userflags checksf"
REDUCTION="--reduction 1000"
SKFlat.py -a DiLeptonAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a DiLeptonAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

