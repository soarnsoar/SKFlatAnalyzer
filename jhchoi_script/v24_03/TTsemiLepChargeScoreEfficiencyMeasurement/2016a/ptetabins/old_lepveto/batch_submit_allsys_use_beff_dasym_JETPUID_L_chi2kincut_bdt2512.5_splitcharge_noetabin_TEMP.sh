 mkdir -p use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_syslogs/

SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5,splitcharge,noetabin"
#FLAG=""
MAXJOB=" --nmax 120 "
MAXJOB2=" --nmax 20 "
#MAXJOB=""
#MAXJOB2=""

MEM_TT="--memory 9600"
MEM_DY="--memory 9600"
MEM_tW="--memory 9600"
MEM_ST="--memory 9600"


MAXJOB=" --nmax 400 "
MAXJOB2=" --nmax 400 "

COUNT=" --count 3 "

MEM_TT="--memory 9600" ##weight=3 -> 120 / weightsum~375
MEM_DY="--memory 9600" ## weight=2 -> 15 / weightsum~24
MEM_tW="--memory 9600"
MEM_ST="--memory 9600"


YEAR=2016a
##--DY
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l  inputlist_DY.txt -n 30 -e ${YEAR} $FLAG ${MAXJOB2} ${MEM_DY} ${COUNT} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_syslogs/DY.log&
sleep 15
##---No specific memory setup
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 10 -e ${YEAR} $FLAG ${MAXJOB2} ${COUNT} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i SingleElectron -n 20 -e ${YEAR} $FLAG ${MAXJOB2} ${COUNT} &> use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_syslogs/SingleElectron.log&



