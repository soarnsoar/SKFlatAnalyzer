#PreselectionToBDTRegionAnalyzer
mkdir -p jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_syslogs/
#
SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
FLAG="--userflags runSys,jetpuid_loose,lepveto,use_beffasym,bdt2512.5,bdtcut,apply_chargeid_eff_corr"

NMAX="--nmax 400"
MEM="--memory 9500"
YEAR=2016a
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 --count 3 -e ${YEAR} $FLAG ${NMAX} ${MEM}&> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_syslogs/major.log&
MEM=""
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_syslogs/minor.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_syslogs/tW.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_syslogs/DoubleMuon.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_syslogs/DoubleEG.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_syslogs/NoSkim.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_apply_chargeid_eff_corr_syslogs/VV.log&
