SKIM="--skim SkimTree_Dilepton"
FLAG=""
#FLAG="--userflags runSys,check_tmva_input"
#FLAG="--userflags simple_lepscale,runSys"
#FLAG="--userflags checksf"
#FLAG="--userflags jetpuid_tight"
FLAG="--userflags check_tmva_input"
REDUCTION="--reduction 1000"
SKFlat.py -a PreselectionAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a PreselectionAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a DiLeptonAnalyzer -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

