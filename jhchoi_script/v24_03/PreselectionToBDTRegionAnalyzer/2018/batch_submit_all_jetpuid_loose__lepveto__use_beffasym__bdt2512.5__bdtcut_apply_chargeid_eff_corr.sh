#PreselectionToBDTRegionAnalyzer
#mkdir -p jetpuid_loose_lepveto_logs/
mkdir -p jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags jetpuid_loose,lepveto"
FLAG="--userflags jetpuid_loose,lepveto,use_beffasym,bdt2512.5,bdtcut,apply_chargeid_eff_corr"

YEAR=2018
NMAX="--nmax 200"

SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_logs/major.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_logs/minor.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_logs/tW.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_logs/DoubleMuon.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_logs/EGamma.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_logs/NoSkim.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_logs/VV.log&

