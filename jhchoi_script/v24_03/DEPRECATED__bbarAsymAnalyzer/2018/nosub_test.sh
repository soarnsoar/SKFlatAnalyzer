#bbarAsymAnalyzer
SKIM="--skim SkimTree_Dilepton"
FLAG=""
FLAG="--userflags runSys"
REDUCTION="--reduction 100"
YEAR=2018
SKFlat.py -a bbarAsymAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 -e ${YEAR} --no_exec ${REDUCTION} $FLAG
SKFlat.py -a bbarAsymAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 -e ${YEAR} --no_exec ${REDUCTION} $FLAG

