#PreselectionToBDTRegionAnalyzer
mkdir -p jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/
#
SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
#FLAG="--userflags runSys"
FLAG="--userflags jetpuid_loose,use_beffasym,newlepveto,bdt2608.2,bdtcut,prob_factor_test"

NMAX="--nmax 400"
MEM="--memory 3200"
YEAR=2016a
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM}&> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/major.log&
MEM=""
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/minor.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/tW.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/DoubleMuon.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/DoubleEG.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer ${SKIM} -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/NoSkim.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/VV.log&
