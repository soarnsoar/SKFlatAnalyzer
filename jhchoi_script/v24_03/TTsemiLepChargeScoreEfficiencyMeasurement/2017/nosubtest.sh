mkdir -p _use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge_measure_bchargeeff_logs/

FLAG="--userflags use_beff_dasym,JETPUID_L,newlepveto,chi2kincut,bdt2608.2,splitcharge,measure_bchargeeff"
SKIM="--skim SkimTree_SingleLepton_1DeepJetTightWP"


YEAR=2017
MAXJOB=" --nmax 800 "


MEM_TT="--memory 6400" ##weight=3 -> 120
C_TT="--count 3"
MEM_DY="--memory 6300" ## weight=2 -> 20
C_DY="--count 3"
MEM_tW="--memory 6300"
C_tW="--count 3"
MEM_ST="--memory 6300"
C_ST="--count 3"

##--TTLJ
NJOB=1

SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n ${NJOB} -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} --no_exec --reduction 10000
