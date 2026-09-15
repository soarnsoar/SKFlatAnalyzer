mkdir -p use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_HighJetOnly_syslogs/

FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5,splitcharge,noetabin,HighJetOnly"
FLAG="--userflags runSys,use_beff_dasym,JETPUID_L,chi2kincut,bdt2512.5,splitcharge,noetabin,HighJetOnly"

SKIM=""

YEAR=2017
MAXJOB=" --nmax 400 "


MEM_TT="--memory 9500" ##weight=3 -> 120
C_TT="--count 3"
MEM_DY="--memory 6000" ## weight=2 -> 20
C_DY="--count 2"
MEM_tW="--memory 6000"
C_tW="--count 2"
MEM_ST="--memory 6000"
C_ST="--count 2"

SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 1 -e ${YEAR} $FLAG --no_exec --reduction 10000
