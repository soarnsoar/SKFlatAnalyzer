#PreselectionToBDTRegionAnalyzer
mkdir -p jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_slteff_corr_logs/


SKIM="--skim SkimTree_Dilepton"
#FLAG="--userflags jetpuid_loose,lepveto"

#FLAG="--userflags jetpuid_loose,lepveto,use_beffasym,bdt2512.5,bdtcut,apply_chargeid_eff_corr,addxsuffix"
FLAG="--userflags runSys,jetpuid_loose,lepveto,use_beffasym,bdt2512.5,bdtcut,apply_chargeid_eff_corr,apply_chargeid_acc_corr,addxsuffix"

NMAX="--nmax 200"
REDUCTION="--reduction 10000"


SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 1 -e 2017 --no_exec $FLAG ${NMAX} ${REDUCTION}

