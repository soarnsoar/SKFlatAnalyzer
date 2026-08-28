#TTsemiLepChargeScoreEfficiencyMeasurement
mkdir -p _use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_syslogs/

SKIM="--skim SkimTree_SingleLepton_1DeepJetTightWP"

FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,noveto,newlepveto,chi2kincut,bdt2608.2,splitcharge,noetabin"

YEAR=2018
MAXJOB=" --nmax 800 "



MEM_TT="--memory 6300" ##weight=3 -> 120
C_TT="--count 3"
MEM_DY="--memory 6300" ## weight=2 -> 20
C_DY="--count 3"
MEM_tW="--memory 6300"
C_tW="--count 3"
MEM_ST="--memory 6300"
C_ST="--count 3"

SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 180 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} &> _use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLL_powheg -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} &> _use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_syslogs/TTLL_powheg.log&
sleep 15
##--DY
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l  inputlist_DY.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_DY} ${C_DY} &> _use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_syslogs/DY.log&
sleep 15
##--ST
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_ST.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_ST} ${C_ST} &> _use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_syslogs/ST.log&
sleep 15
##--tW
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_tW.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_tW} ${C_tW} &> _use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_syslogs/tW.log&
sleep 15

MEM="--memory 3200 --count 2"
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 10 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> _use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement ${SKIM} -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> _use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_syslogs/NoSkim.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> _use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i EGamma -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> _use_beff_dasym_JETPUID_L_noveto_newlepveto_chi2kincut_bdt2608.2_splitcharge_noetabin_syslogs/EGamma.log&


