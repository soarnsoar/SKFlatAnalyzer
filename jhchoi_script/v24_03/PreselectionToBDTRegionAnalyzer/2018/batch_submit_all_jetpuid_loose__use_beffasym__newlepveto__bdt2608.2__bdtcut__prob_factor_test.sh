#PreselectionToBDTRegionAnalyzer
#mkdir -p jetpuid_loose_lepveto_logs/
mkdir -p jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/

SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
FLAG="--userflags jetpuid_loose,use_beffasym,newlepveto,bdt2608.2,bdtcut,prob_factor_test"




YEAR=2018
NMAX="--nmax 400"
MEM="--memory 3200"
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 80 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/major.log&
MEM=""
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/minor.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/tW.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/DoubleMuon.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/EGamma.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer ${SKIM} -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/NoSkim.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_prob_factor_test_logs/VV.log&

