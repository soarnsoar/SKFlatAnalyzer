mkdir -p use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_syslogs/

FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5,splitcharge"
SKIM=""

YEAR=2017
MAXJOB=" --nmax 400 "
MEM="--memory 20000"
MEM_TTLJ="--memory 20000"


SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TTLJ} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l  inputlist_major.txt -n 40 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_syslogs/major.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 40 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_tW.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_syslogs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i SingleElectron -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_syslogs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_syslogs/NoSkim.log&
