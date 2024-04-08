SKIM="--skim SkimTree_Dilepton"
FLAG=""
FLAG="--userflags runSys"
FLAG="--userflags simple_lepscale,runSys"
#FLAG="--userflags checksf"
#REDUCTION="--reduction 10000"
SKFlat.py -a DiLeptonAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a DiLeptonAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a DiLeptonAnalyzer -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

