SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
FLAG=""
#FLAG="--userflags runSys,check_tmva_input"
#FLAG="--userflags simple_lepscale,runSys"
#FLAG="--userflags checksf"
#FLAG="--userflags jetpuid_tight"
#FLAG="--userflags check_tmva_input"
FLAG="--userflags runSys,jetpuid_loose,lepveto"
FLAG="--userflags runSys,jetpuid_loose,lepveto,check_tmva_input,pusysonly,bdt2512.5"
FLAG="--userflags jetpuid_loose,newlepveto,use_beffasym,bdt_v2608_2,bdtopt,bdtopt_mue"


REDUCTION="--reduction 1000"
SKFlat.py -a PreselectionAnalyzer -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a PreselectionAnalyzer -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a DiLeptonAnalyzer -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

