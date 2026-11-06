#PreselectionToBDTRegionAnalyzer
#mkdir -p jetpuid_loose_lepveto_logs/
mkdir -p jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs/

SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
FLAG="--userflags runSys,jetpuid_loose,use_beffasym,newlepveto,bdt2608.2,bdtcut,apply_chargeid_eff_corr,apply_chargeid_acc_corr"



YEAR=2018
NMAX="--nmax 400"
MEM="--memory 9500"
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 80 --count 3 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs/major.log&
MEM="--memory 3200"
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 80 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs/minor.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs/tW.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs/DoubleMuon.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs/EGamma.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer ${SKIM} -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs/NoSkim.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs/VV.log&

