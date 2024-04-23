SKIM="--skim SkimTree_Dilepton"
#SKIM=""
FLAG=""
#FLAG="--userflags runSys"
#FLAG="--userflags simple_lepscale,runSys"
#FLAG="--userflags checksf"
REDUCTION="--reduction 1000"
#SKFlat.py -a bChargeID_TrainTree -i WJets_MG $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a bChargeID_TrainTree -i WJets_amcatnlo $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKFlat.py -a bChargeID_TrainTree -i DYJets $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a bChargeID_TrainTree -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG


