SKIM="--skim SkimTree_Dilepton"
FLAG=""
FLAG="--userflags runSys"
FLAG="--userflags runSys,jetpuid_loose,lepveto,check_tmva_input,pusysonly,bdt2512.5"

REDUCTION="--reduction 100"
YEAR=2016b
SKFlat.py -a PreselectionAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 -e ${YEAR} --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a DiLeptonAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 -e ${YEAR} --no_exec ${REDUCTION} $FLAG

