mkdir -p use_beff_logs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags use_beff"
YEAR=2016a
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG &> use_beff_logs/TTLJ_powheg.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i TTJJ_powheg -n 50 -e ${YEAR} $FLAG &> use_beff_logs/TTJJ_powheg.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG &> use_beff_logs/major.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> use_beff_logs/minor.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG &> use_beff_logs/tW.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG &> use_beff_logs/SingleMuon.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG &> use_beff_logs/SingleElectron.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG &> use_beff_logs/NoSkim.log&

