#TTsemiLepChargeScoreAccuracyMeasurement
mkdir -p use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_measure_bchargeacc_logs/


SKIM="--skim SkimTree_SingleLepton"
SKIM=""

FLAG="--userflags use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5,splitcharge,noetabin,measure_bchargeacc"
MAXJOB=" --nmax 60 "

YEAR=2016b
SKFlat.py -a TTsemiLepChargeScoreAccuracyMeasurement  ${SKIM} -i TTLJ_powheg -n 40 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_measure_bchargeacc_logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreAccuracyMeasurement  ${SKIM} -i TTLL_powheg -n 30 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_measure_bchargeacc_logs/TTLL_powheg.log&
sleep 15
##--DY
SKFlat.py -a TTsemiLepChargeScoreAccuracyMeasurement  ${SKIM} -l  inputlist_DY.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_measure_bchargeacc_logs/DY.log&
sleep 15
##--ST
SKFlat.py -a TTsemiLepChargeScoreAccuracyMeasurement  ${SKIM} -l inputlist_ST.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_measure_bchargeacc_logs/ST.log&
sleep 15
##--tW
SKFlat.py -a TTsemiLepChargeScoreAccuracyMeasurement  ${SKIM} -l inputlist_tW.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_measure_bchargeacc_logs/tW.log&
#sleep 15
##---No specific memory setup
#SKFlat.py -a TTsemiLepChargeScoreAccuracyMeasurement  ${SKIM} -l inputlist_minor.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_measure_bchargeacc_logs/minor.log&
#sleep 15
#SKFlat.py -a TTsemiLepChargeScoreAccuracyMeasurement -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_measure_bchargeacc_logs/NoSkim.log&

