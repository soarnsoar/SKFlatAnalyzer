SKIM=""
#FLAG="--userflags runMomSys"
FLAG=""
REDUCTION="--reduction 1000"
SKFlat.py -a DYbTrueBJetAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG


