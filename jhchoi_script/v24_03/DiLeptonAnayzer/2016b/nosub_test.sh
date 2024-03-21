SKIM="--skim SkimTree_Dilepton"
SKFlat.py -a DiLeptonAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec  --reduction 10000
SKFlat.py -a DiLeptonAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec  --reduction 10000

