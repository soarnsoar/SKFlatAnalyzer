#PreselectionToBDTRegionAnalyzer
mkdir -p jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeacc_logs/
#
SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
#FLAG="--userflags runSys"
FLAG="--userflags jetpuid_loose,use_beffasym,newlepveto,bdt2608.2,bdtcut,measure_bchargeacc"

NMAX="--nmax 400"
MEM="--memory 9500"
YEAR=2016a
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 --count 3 -e ${YEAR} $FLAG ${NMAX} ${MEM}&> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeacc_logs/major.log&
MEM=""
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeacc_logs/minor.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeacc_logs/tW.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeacc_logs/DoubleMuon.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeacc_logs/DoubleEG.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer ${SKIM} -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeacc_logs/NoSkim.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeacc_logs/VV.log&
