#PreselectionToBDTRegionAnalyzer
#mkdir -p jetpuid_loose_lepveto_logs/
mkdir -p jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,jetpuid_loose,use_beffasym,bdt2512.5,bdtcut,apply_chargeid_eff_corr,apply_chargeid_acc_corr,addxsuffix"


YEAR=2018
NMAX="--nmax 400"
MEM="--memory 9500"
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 80 --count 3 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/major.log&
MEM=""
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/minor.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/tW.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/DoubleMuon.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/EGamma.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/NoSkim.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/VV.log&

