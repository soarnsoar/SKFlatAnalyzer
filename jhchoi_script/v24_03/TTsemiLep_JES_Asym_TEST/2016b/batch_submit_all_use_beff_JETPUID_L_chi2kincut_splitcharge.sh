#TTsemiLep_JES_Asym_TEST
mkdir -p use_beff_JETPUID_L_splitcharge_syslogs/


SKIM="--skim SkimTree_SingleLepton"
SKIM=""


FLAG="--userflags runSys,use_beff,JETPUID_L,splitcharge"




MAXJOB=" --nmax 400 "



MEM_TT="--memory 3200" ##weight=3 -> 120
C_TT="--count 1"
MEM_DY="--memory 3200" ## weight=2 -> 20
C_DY="--count 1"
MEM_tW="--memory 3200"
C_tW="--count 1"
MEM_ST="--memory 3200"
C_ST="--count 1"

YEAR=2016b
SKFlat.py -a TTsemiLep_JES_Asym_TEST  ${SKIM} -i TTLJ_powheg -n 80 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} &> use_beff_JETPUID_L_splitcharge_syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLep_JES_Asym_TEST  ${SKIM} -i TTLL_powheg -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_TT} ${C_TT} &> use_beff_JETPUID_L_splitcharge_syslogs/TTLL_powheg.log&
sleep 15
##--DY
SKFlat.py -a TTsemiLep_JES_Asym_TEST  ${SKIM} -l  inputlist_DY.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_DY} ${C_DY} &> use_beff_JETPUID_L_splitcharge_syslogs/DY.log&
sleep 15
##--ST
SKFlat.py -a TTsemiLep_JES_Asym_TEST  ${SKIM} -l inputlist_ST.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_ST} ${C_ST} &> use_beff_JETPUID_L_splitcharge_syslogs/ST.log&
sleep 15
##--tW
SKFlat.py -a TTsemiLep_JES_Asym_TEST  ${SKIM} -l inputlist_tW.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB} ${MEM_tW} ${C_tW} &> use_beff_JETPUID_L_splitcharge_syslogs/tW.log&
sleep 15
##---No specific memory setup
SKFlat.py -a TTsemiLep_JES_Asym_TEST  ${SKIM} -l inputlist_minor.txt -n 10 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_JETPUID_L_splitcharge_syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLep_JES_Asym_TEST -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_JETPUID_L_splitcharge_syslogs/NoSkim.log&
sleep 15
SKFlat.py -a TTsemiLep_JES_Asym_TEST   -i SingleMuon -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_JETPUID_L_splitcharge_syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLep_JES_Asym_TEST   -i SingleElectron -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> use_beff_JETPUID_L_splitcharge_syslogs/SingleElectron.log&
sleep 15


