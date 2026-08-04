#PreselectionToBDTRegionAnalyzer
mkdir -p jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,jetpuid_loose,use_beffasym,bdt2512.5,bdtcut,apply_chargeid_eff_corr,apply_chargeid_acc_corr,addxsuffix"

NMAX="--nmax 400"
MEM="--memory 9500"

SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 70  --count 3 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/major.log&
MEM=""
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/NoSkim.log&
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/minor.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/tW.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/DoubleMuon.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/DoubleEG.log&

SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_addxsuffix_syslogs/VV.log&

