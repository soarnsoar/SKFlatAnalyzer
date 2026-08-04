#TTsemiLepChargeScoreEfficiencyMeasurement
mkdir -p use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_logs/

SKIM="--skim SkimTree_SingleLepton"
SKIM=""

FLAG="--userflags use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5"
MAXJOB=" --nmax 150 "
MEM="--memory 10000"



YEAR=2016b
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l  inputlist_major.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_logs/major.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_logs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_logs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement   -i SingleMuon -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_logs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement   -i SingleElectron -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_logs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_logs/NoSkim.log&

