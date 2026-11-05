#PreselectionToBDTRegionAnalyzer
mkdir -p jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeeff_logs/

SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
FLAG="--userflags jetpuid_loose,use_beffasym,newlepveto,bdt2608.2,bdtcut,measure_bchargeeff"


NMAX="--nmax 400"
MEM="--memory 9500"

SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 70  --count 3 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeeff_logs/major.log&
MEM=""
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer ${SKIM} -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeeff_logs/NoSkim.log&
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeeff_logs/minor.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeeff_logs/tW.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeeff_logs/DoubleMuon.log&
#SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeeff_logs/DoubleEG.log&

SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeeff_logs/VV.log&

