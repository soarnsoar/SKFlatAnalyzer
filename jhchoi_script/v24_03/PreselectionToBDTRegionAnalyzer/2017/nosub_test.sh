#PreselectionToBDTRegionAnalyzer

SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"

FLAG="--userflags runSys,jetpuid_loose,use_beffasym,newlepveto,bdt2608.2,bdtcut,apply_chargeid_corrs,jsource"


NMAX="--nmax 200"
REDUCTION="--reduction 10000"


SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 1 -e 2017 --no_exec $FLAG ${NMAX} ${REDUCTION}

