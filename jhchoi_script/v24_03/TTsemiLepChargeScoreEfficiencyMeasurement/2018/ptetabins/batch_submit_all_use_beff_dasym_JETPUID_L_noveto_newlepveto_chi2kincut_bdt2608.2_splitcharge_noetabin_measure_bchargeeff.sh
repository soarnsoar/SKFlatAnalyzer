#TTsemiLepChargeScoreEfficiencyMeasurement
mkdir -p use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_measure_bchargeeff_logs/

#SKIM="--skim SkimTree_SingleLepton"
SKIM="--skim SkimTree_SingleLepton_1DeepJetTightWP"
#SKIM=""

#FLAG="--userflags use_beff_dasym,JETPUID_L,bdt2512.5,measure_bchargeeff"
FLAG="--userflags use_beff_dasym,JETPUID_L,noveto,newlepveto,chi2kincut,bdt2608.2,splitcharge,noetabin,measure_bchargeeff"

YEAR=2018
MAXJOB=" --nmax 180 "


SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG $MAXJOB &> use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_measure_bchargeeff_logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLL_powheg -n 30 -e ${YEAR} $FLAG $MAXJOB &> use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_measure_bchargeeff_logs/TTLL_powheg.log&
sleep 15
##--DY
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l  inputlist_DY.txt -n 30 -e ${YEAR} $FLAG $MAXJOB &> use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_measure_bchargeeff_logs/DY.log&
sleep 15
##--ST
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_ST.txt -n 30 -e ${YEAR} $FLAG $MAXJOB &> use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_measure_bchargeeff_logs/ST.log&
sleep 15
##--tW
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_tW.txt -n 30 -e ${YEAR} $FLAG $MAXJOB &> use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_measure_bchargeeff_logs/tW.log&
sleep 15
##---No specific memory setup
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_measure_bchargeeff_logs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement ${SKIM} -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_measure_bchargeeff_logs/NoSkim.log&
sleep 15
