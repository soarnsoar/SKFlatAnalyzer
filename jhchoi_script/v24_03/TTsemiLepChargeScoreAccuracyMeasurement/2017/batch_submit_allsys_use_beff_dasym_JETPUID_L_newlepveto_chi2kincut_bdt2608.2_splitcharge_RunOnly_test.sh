ThisID=$1
mkdir -p _use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge_${ThisID}Only_syslogs/

FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,newlepveto,chi2kincut,bdt2608.2,splitcharge,${ThisID}Only"
SKIM="--skim SkimTree_SingleLepton_1DeepJetTightWP"


YEAR=2017
MAXJOB=" --nmax 800 "


MEM_TT="--memory 6400" ##weight=3 -> 120
C_TT="--count 3"
MEM_DY="--memory 3200" ## weight=2 -> 20
C_DY="--count 2"
MEM_tW="--memory 3200"
C_tW="--count 2"
MEM_ST="--memory 3200"
C_ST="--count 2"

##--TTLJ
NJOB=150

#SKFlat.py -a TTsemiLepChargeScoreAccuracyMeasurement  ${SKIM} -l inputlist_ST.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_ST} ${C_ST} &> _use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge_${ThisID}Only_syslogs/ST.log&

SKFlat.py -a TTsemiLepChargeScoreAccuracyMeasurement  ${SKIM} -l  inputlist_DY.txt -n 100 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_DY} ${C_DY} &> _use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge_${ThisID}Only_syslogs/DY.log&
