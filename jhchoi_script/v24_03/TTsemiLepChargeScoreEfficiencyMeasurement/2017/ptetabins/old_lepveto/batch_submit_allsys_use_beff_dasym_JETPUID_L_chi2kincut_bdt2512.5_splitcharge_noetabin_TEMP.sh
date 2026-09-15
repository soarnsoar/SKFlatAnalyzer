mkdir -p use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_syslogs/

FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5,splitcharge,noetabin"
SKIM=""

YEAR=2017
MAXJOB=" --nmax 400 "
MAXJOB2=" --nmax 400 "
#MAXJOB=""
#MAXJOB2=""


#MEM_TT="--memory 20000"
#MEM_DY="--memory 5000"
#MEM_tW="--memory 15000"
#MEM_ST="--memory 12000"



MEM_TT="--memory 10000" ##weight=3 -> 120
MEM_DY="--memory 10000" ## weight=2 -> 20
MEM_tW="--memory 10000"
MEM_ST="--memory 10000"


##--DY
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l  inputlist_DY.txt -n 50 -e ${YEAR} $FLAG ${MAXJOB2} ${MEM_DY} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_syslogs/DY.log&
sleep 15
##--ST

SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${MAXJOB2} ${MEM_DY} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_syslogs/minor.log&
sleep 15

SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG ${MAXJOB2} ${MEM_DY}  &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_syslogs/SingleElectron.log&
sleep 15

