SKIM="--skim SkimTree_SingleLepton"
FLAG=""
FLAG="--userflags runSys"
REDUCTION="--reduction 100"
#YEAR=2016a
YEAR=2016b
#YEAR=2017
#YEAR=2018


SKFlat.py -a SingleLeptonAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG -e ${YEAR}
SKFlat.py -a SingleLeptonAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG -e ${YEAR}

