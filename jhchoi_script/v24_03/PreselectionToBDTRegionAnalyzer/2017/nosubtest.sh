#PreselectionToBDTRegionAnalyzer
mkdir -p jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/

SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
FLAG="--userflags runSys,jetpuid_loose,use_beffasym,newlepveto,bdt2608.2,bdtcut,apply_chargeid_eff_corr,apply_chargeid_acc_corr,addxsuffix"

NMAX="--nmax 400"
MEM="--memory 9500"

SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 1 --reduction 10000 --no_exec  --count 3 -e 2017 $FLAG ${NMAX} ${MEM}
