##
SKIM="--skim SkimTree_Dilepton"

REDUCTION="--reduction 10000"
SKFlat.py -a BasicTest -i DYJetsToEE_MiNNLO -n 1 --no_exec ${REDUCTION} ${SKIM}
