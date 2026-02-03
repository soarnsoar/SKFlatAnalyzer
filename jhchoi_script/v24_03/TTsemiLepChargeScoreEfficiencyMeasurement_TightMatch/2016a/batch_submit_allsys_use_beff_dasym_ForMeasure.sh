mkdir -p logs/
mkdir -p syslogs/
mkdir -p use_beff_dasym_ForMeasure_syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys,use_beff_dasym,ForMeasure"
MEMORY="--memory 10000"
MEMORYHIGH="--memory 22000"
NMAX="--nmax 300"

YEAR=2016a
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG ${MEMORYHIGH} $NMAX &> use_beff_dasym_ForMeasure_syslogs/TTLJ_powheg.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} $NMAX &> use_beff_dasym_ForMeasure_syslogs/major.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} $NMAX &> use_beff_dasym_ForMeasure_syslogs/minor.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} $NMAX &> use_beff_dasym_ForMeasure_syslogs/tW.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG ${MEMORY} $NMAX &> use_beff_dasym_ForMeasure_syslogs/SingleMuon.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG ${MEMORY} $NMAX &> use_beff_dasym_ForMeasure_syslogs/SingleElectron.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} $NMAX &> use_beff_dasym_ForMeasure_syslogs/NoSkim.log&

