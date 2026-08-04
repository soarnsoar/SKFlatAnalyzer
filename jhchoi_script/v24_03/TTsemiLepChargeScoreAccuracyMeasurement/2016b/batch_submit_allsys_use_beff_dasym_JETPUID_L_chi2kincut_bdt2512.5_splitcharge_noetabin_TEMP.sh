#TTsemiLepChargeScoreAccuracyMeasurement
mkdir -p use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_syslogs/


SKIM="--skim SkimTree_SingleLepton"
SKIM=""

#FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5"
FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5,splitcharge,noetabin"




MAXJOB=" --nmax 400 "



MEM_TT="--memory 32000" ##weight=3 -> 120
C_TT="--count 10"
MEM_DY="--memory 6300" ## weight=2 -> 20
C_DY="--count 2"
MEM_tW="--memory 6300"
C_tW="--count 2"
MEM_ST="--memory 6300"
C_ST="--count 2"

YEAR=2016b
SKFlat.py -a TTsemiLepChargeScoreAccuracyMeasurement  ${SKIM} -i TTLJ_powheg -n 133 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} --reduction 10 --no_exec 

