#PreselectionToBDTRegionAnalyzer
mkdir -p jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_addxsuffix_logs/


SKIM="--skim SkimTree_Dilepton"
#FLAG="--userflags jetpuid_loose,lepveto"
FLAG="--userflags jetpuid_loose,lepveto,use_beffasym,bdt2512.5,bdtcut,apply_chargeid_eff_corr,addxsuffix"
NMAX="--nmax 150"


SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_addxsuffix_logs/major.log&
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_addxsuffix_logs/NoSkim.log&
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_addxsuffix_logs/minor.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_addxsuffix_logs/tW.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_addxsuffix_logs/DoubleMuon.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_addxsuffix_logs/DoubleEG.log&

SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_addxsuffix_logs/VV.log&

