#TTsemiLepChargeScoreEfficiencyMeasurement
mkdir -p use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_noveto_syslogs/


SKIM="--skim SkimTree_SingleLepton"
SKIM=""

#FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5"
FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5,splitcharge,noetabin,noveto"




MAXJOB=" --nmax 400 "



MEM_TT="--memory 6400" ##weight=3 -> 120
C_TT="--count 2"
MEM_DY="--memory 6300" ## weight=2 -> 20
C_DY="--count 2"
MEM_tW="--memory 6300"
C_tW="--count 2"
MEM_ST="--memory 6300"
C_ST="--count 2"

YEAR=2016b
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 80 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_noveto_syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLL_powheg -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_noveto_syslogs/TTLL_powheg.log&
sleep 15
##--DY
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l  inputlist_DY.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_DY} ${C_DY} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_noveto_syslogs/DY.log&
sleep 15
##--ST
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_ST.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_ST} ${C_ST} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_noveto_syslogs/ST.log&
sleep 15
##--tW
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_tW.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_tW} ${C_tW} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_noveto_syslogs/tW.log&
sleep 15
##---No specific memory setup
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 10 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_noveto_syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_noveto_syslogs/NoSkim.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement   -i SingleMuon -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_noveto_syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement   -i SingleElectron -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_noveto_syslogs/SingleElectron.log&
sleep 15


