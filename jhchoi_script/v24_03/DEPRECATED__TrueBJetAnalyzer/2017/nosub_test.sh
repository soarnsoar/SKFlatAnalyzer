SKIM="--skim SkimTree_Dilepton"
FLAG=""
#FLAG="--userflags runSys,check_tmva_input"
#FLAG="--userflags simple_lepscale,runSys"
#FLAG="--userflags checksf"
#FLAG="--userflags jetpuid_tight"
#FLAG="--userflags check_tmva_input"
#FLAG="--userflags runSys,dnn_v2405.4.3"

REDUCTION="--reduction 1000"
#SKFlat.py -a TrueBJetAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a TrueBJetAnalyzer -i DYJetsToTauTau_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a TrueBJetAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a TrueBJetAnalyzer -i TTLL_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

