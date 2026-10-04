mkdir -p _use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge_apply_sltideff_logs/

SKIM="--skim SkimTree_SingleLepton_1DeepJetTightWP"
FLAG="--userflags use_beff_dasym,JETPUID_L,newlepveto,chi2kincut,bdt2608.2,splitcharge,apply_sltideff"

MAXJOB=" --nmax 800 "

MEM_TT="--memory 6400" ##weight=3 -> 120 / weightsum~375
C_TT="--count 3"
MEM_DY="--memory 6400" ## weight=2 -> 15 / weightsum~24
C_DY="--count 3"
MEM_tW="--memory 6400"
C_tW="--count 3"
MEM_ST="--memory 6400"
C_ST="--count 3"

YEAR=2016a
##--TTLJ
NJOB=1

#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n ${NJOB} -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} --reduction 10000 --no_exec
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i ZZ_pythia -n ${NJOB} -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} --reduction 10000 --no_exec


