mkdir -p logs/
mkdir -p syslogs/
mkdir -p use_beff_ForMeasure_syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags use_beff,ForMeasure"
MEMORY="--memory 10000"
MEMORYHIGH="--memory 22000"
NMAX="--nmax 900"
REDUCTION="--reduction 1000"
YEAR=2018
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour -n 1 --no_exec  ${SKIM} -i TTLJ_powheg -e ${YEAR} $FLAG ${MEMORYHIGH} ${NMAX} ${REDUCTION}
 
