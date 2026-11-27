#PreselectionToBDTRegionAnalyzer
mkdir -p jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs/
#
SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
#FLAG="--userflags runSys"
FLAG="--userflags runSys,jetpuid_loose,use_beffasym,newlepveto,bdt2608.2,bdtcut,apply_chargeid_eff_corr,apply_chargeid_acc_corr"

NMAX="--nmax 400"
MEM="--memory 9500"
YEAR=2016a
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DYJetsToMuMu_MiNNLO -n 50 --count 3 -e ${YEAR} $FLAG ${NMAX} ${MEM}&> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs/dymmonly.log&
