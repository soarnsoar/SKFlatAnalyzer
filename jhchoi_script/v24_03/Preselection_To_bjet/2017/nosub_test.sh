SKIM="--skim SkimTree_Dilepton"
FLAG=""
#FLAG="--userflags runSys,check_tmva_input"
#FLAG="--userflags simple_lepscale,runSys"
#FLAG="--userflags checksf"
#FLAG="--userflags jetpuid_tight"
#FLAG="--userflags check_tmva_input"
#FLAG="--userflags runSys,dnn_v2405.4.3"
#FLAG="--userflags runSys"
#FLAG="--userflags use_beff,pfmet,phicorrmet"
#FLAG="--userflags runSys,use_beff,MuonOnly"
FLAG="--userflags runSys,use_beff"

REDUCTION="--reduction 10000"
SKFlat.py -a Preselection_To_bjet -i DYJetsToMuMu_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG


#SKFlat.py -a Preselection_To_bjet -i DYJetsToEE_MiNNLO $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

#SKFlat.py -a Preselection_To_bjet -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

#SKFlat.py -a Preselection_To_bjet -i DoubleEG $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
SKIM=""
#SKFlat.py -a Preselection_To_bjet -i QCD_bEnriched_HT700to1000 $SKIM -n 1 --no_exec ${REDUCTION} $FLAG


