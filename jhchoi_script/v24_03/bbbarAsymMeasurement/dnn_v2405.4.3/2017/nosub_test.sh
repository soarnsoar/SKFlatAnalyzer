SKIM="--skim SkimTree_Dilepton"
FLAG=""
FLAG="--userflags runSys,dnn_v2405.4.3"
#FLAG="--userflags simple_lepscale,runSys"
#FLAG="--userflags checksf"
#FLAG="--userflags jetpuid_tight"
#FLAG="--userflags check_tmva_input"
#FLAG="--userflags dnn_v2405.4"

REDUCTION="--reduction 3000"
SKFlat.py -a bbbarAsymMeasurement -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a bbbarAsymMeasurement -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a DiLeptonAnalyzer -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

