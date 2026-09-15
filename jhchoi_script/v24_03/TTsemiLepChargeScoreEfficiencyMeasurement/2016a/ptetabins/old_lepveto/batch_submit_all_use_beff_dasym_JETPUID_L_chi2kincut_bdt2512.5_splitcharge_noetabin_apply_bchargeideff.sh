mkdir -p use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_apply_bchargeideff_logs/

SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5,splitcharge,noetabin,apply_bchargeideff"

MAXJOB=" --nmax 400 "

MEM_TT="--memory 3200" ##weight=3 -> 120 / weightsum~375
C_TT="--count 1"
MEM_DY="--memory 3200" ## weight=2 -> 15 / weightsum~24
C_DY="--count 1"
MEM_tW="--memory 3200"
C_tW="--count 1"
MEM_ST="--memory 3200"
C_ST="--count 1"

YEAR=2016a
##--TT
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 80 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_apply_bchargeideff_logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLL_powheg -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_apply_bchargeideff_logs/TTLL_powheg.log&
sleep 15
##--DY
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l  inputlist_DY.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_DY} ${C_DY} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_apply_bchargeideff_logs/DY.log&
sleep 15
##--ST
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_ST.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_ST} ${C_ST} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_apply_bchargeideff_logs/ST.log&
sleep 15
##--tW
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_tW.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_tW} ${C_tW} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_apply_bchargeideff_logs/tW.log&
sleep 15
##---No specific memory setup
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 10 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_apply_bchargeideff_logs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_apply_bchargeideff_logs/NoSkim.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_apply_bchargeideff_logs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG ${MAXJOB}  &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_apply_bchargeideff_logs/SingleElectron.log&



