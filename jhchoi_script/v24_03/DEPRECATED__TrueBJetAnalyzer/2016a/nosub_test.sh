SKIM="--skim SkimTree_Dilepton"
FLAG=""
#FLAG="--userflags runSys"
REDUCTION="--reduction 100"
YEAR=2016a
SKFlat.py -a TrueBJetAnalyzer -i TTLL_powheg $SKIM -e ${YEAR} -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a TrueBJetAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 -e ${YEAR} --no_exec ${REDUCTION} $FLAG

