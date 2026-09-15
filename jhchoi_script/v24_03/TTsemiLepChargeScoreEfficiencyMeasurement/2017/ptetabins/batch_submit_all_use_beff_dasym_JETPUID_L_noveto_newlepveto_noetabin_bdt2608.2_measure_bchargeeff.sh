mkdir -p use_beff_dasym_JETPUID_L_noveto_newlepveto_noetabin_bdt2608.2_measure_bchargeeff_logs/

FLAG="--userflags use_beff_dasym,JETPUID_L,noveto,newlepveto,noetabin,bdt2608.2,measure_bchargeeff"
SKIM="--skim SkimTree_SingleLepton_1DeepJetTightWP"

YEAR=2017
MAXJOB=" --nmax 150 "


SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG $MAXJOB  &> use_beff_dasym_JETPUID_L_noveto_newlepveto_noetabin_bdt2608.2_measure_bchargeeff_logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLL_powheg -n 30 -e ${YEAR} $FLAG $MAXJOB &> use_beff_dasym_JETPUID_L_noveto_newlepveto_noetabin_bdt2608.2_measure_bchargeeff_logs/TTLL_powheg.log&
sleep 15
##--DY
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l  inputlist_DY.txt -n 30 -e ${YEAR} $FLAG $MAXJOB &> use_beff_dasym_JETPUID_L_noveto_newlepveto_noetabin_bdt2608.2_measure_bchargeeff_logs/DY.log&
sleep 15
##--ST
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_ST.txt -n 30 -e ${YEAR} $FLAG $MAXJOB &> use_beff_dasym_JETPUID_L_noveto_newlepveto_noetabin_bdt2608.2_measure_bchargeeff_logs/ST.log&
sleep 15
##--tW
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_tW.txt -n 30 -e ${YEAR} $FLAG $MAXJOB  &> use_beff_dasym_JETPUID_L_noveto_newlepveto_noetabin_bdt2608.2_measure_bchargeeff_logs/tW.log&
sleep 15
##---No specific memory setup
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> use_beff_dasym_JETPUID_L_noveto_newlepveto_noetabin_bdt2608.2_measure_bchargeeff_logs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement ${SKIM} -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG $MAXJOB  &> use_beff_dasym_JETPUID_L_noveto_newlepveto_noetabin_bdt2608.2_measure_bchargeeff_logs/NoSkim.log&
sleep 15
