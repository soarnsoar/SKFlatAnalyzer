SKIM="--skim SkimTree_Dilepton"
FLAG=""
FLAG="--userflags runSys,pusysonly"
REDUCTION="--reduction 1000"
YEAR=2018
SKFlat.py -a DiLeptonAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 -e ${YEAR} --no_exec ${REDUCTION} $FLAG
SKFlat.py -a DiLeptonAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 -e ${YEAR} --no_exec ${REDUCTION} $FLAG

