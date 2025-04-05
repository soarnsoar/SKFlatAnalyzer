#EEMu_MuMuE_Method

SKIM="--skim SkimTree_Dilepton"
SKIM=""
#FLAG=""
#FLAG="--userflags runSys"
#FLAG="--userflags simple_lepscale,runSys"
FLAG="--userflags treemode,cut_v2503.1"
REDUCTION="--reduction 1000"
#SKFlat.py -a EEMu_MuMuE_Method -i WJets_MG $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a EEMu_MuMuE_Method -i WJets_amcatnlo $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a EEMu_MuMuE_Method -i DYJets $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG


FLAG=""
SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

