mkdir -p logs/
mkdir -p syslogs/
mkdir -p use_beff_simplecat_syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys,use_beff,simplecat"
MEMORY="--memory 10000"
MEMORYHIGH="--memory 22000"

YEAR=2016a
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG ${MEMORYHIGH} &> use_beff_simplecat_syslogs/TTLJ_powheg.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i TTJJ_powheg -n 50 -e ${YEAR} $FLAG ${MEMORY} &> use_beff_simplecat_syslogs/TTJJ_powheg.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} &> use_beff_simplecat_syslogs/major.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} &> use_beff_simplecat_syslogs/minor.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} &> use_beff_simplecat_syslogs/tW.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG ${MEMORY} &> use_beff_simplecat_syslogs/SingleMuon.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG ${MEMORY} &> use_beff_simplecat_syslogs/SingleElectron.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} &> use_beff_simplecat_syslogs/NoSkim.log&

