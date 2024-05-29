#EEMu_MuMuE_Method

SKIM="--skim SkimTree_Dilepton"
#SKIM=""
#FLAG=""
#FLAG="--userflags runSys"
#FLAG="--userflags simple_lepscale,runSys"
FLAG="--userflags cut_v2405.1,treemode"
REDUCTION="--reduction 1000"
#SKFlat.py -a EEMu_MuMuE_Method -i WJets_MG $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a EEMu_MuMuE_Method -i WJets_amcatnlo $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a EEMu_MuMuE_Method -i DYJets $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG


