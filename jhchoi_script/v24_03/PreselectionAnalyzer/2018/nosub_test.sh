#PreselectionAnalyzer
SKIM="--skim SkimTree_Dilepton"
FLAG=""
FLAG="--userflags runSys,jetpuid_loose,lepveto,check_tmva_input,pusysonly,bdt2512.4"
FLAG="--userflags runSys,jetpuid_loose,lepveto,check_tmva_input,pusysonly,bdt2512.5"
#FLAG="--userflags runSys,jetpuid_loose,lepveto,check_tmva_input,weightonly,bdt2512.5"


REDUCTION="--reduction 100"
YEAR=2018
SKFlat.py -a PreselectionAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 -e ${YEAR} --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a PreselectionAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 -e ${YEAR} --no_exec ${REDUCTION} $FLAG

