SKIM="--skim SkimTree_Dilepton"
FLAG=""
FLAG="--userflags jetpuid_loose,lepveto,jetvetotest"
FLAG="--userflags runSys,jetpuid_loose,lepveto,check_tmva_input,pusysonly,bdt2512.5"


REDUCTION="--reduction 5000"
YEAR=2016a
SKFlat.py -a PreselectionAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -e ${YEAR} -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a DiLeptonAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 -e ${YEAR} --no_exec ${REDUCTION} $FLAG

