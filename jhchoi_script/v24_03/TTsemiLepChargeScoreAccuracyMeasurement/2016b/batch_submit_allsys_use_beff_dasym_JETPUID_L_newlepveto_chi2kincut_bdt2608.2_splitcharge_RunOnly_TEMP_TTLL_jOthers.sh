ThisID=jOthers
#TTsemiLepChargeScoreAccuracyMeasurement
mkdir -p _use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge_${ThisID}Only_syslogs/


#SKIM="--skim SkimTree_SingleLepton"
#SKIM=""
SKIM="--skim SkimTree_SingleLepton_1DeepJetTightWP"


FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,newlepveto,chi2kincut,bdt2608.2,splitcharge,${ThisID}Only"


MAXJOB=" --nmax 800 "



MEM_TT="--memory 6400" ##weight=3 -> 120
C_TT="--count 3"
MEM_DY="--memory 3200" ## weight=2 -> 20
C_DY="--count 2"
MEM_tW="--memory 3200"
C_tW="--count 2"
MEM_ST="--memory 3200"
C_ST="--count 2"

YEAR=2016b

NJOB=300




SKFlat.py -a TTsemiLepChargeScoreAccuracyMeasurement  ${SKIM} -i TTLL_powheg -n ${NJOB} -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} &> _use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge_${ThisID}Only_syslogs/TTLL_powheg.log&
