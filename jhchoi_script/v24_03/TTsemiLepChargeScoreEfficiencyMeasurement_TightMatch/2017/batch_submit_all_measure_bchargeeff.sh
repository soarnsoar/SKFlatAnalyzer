mkdir -p measure_bchargeeff_logs/

SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags measure_bchargeeff,use_beff"
YEAR=2017
NMAX="--nmax 500"
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG ${NMAX} &> measure_bchargeeff_logs/TTLJ_powheg.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i TTJJ_powheg -n 50 -e ${YEAR} $FLAG ${NMAX} &> measure_bchargeeff_logs/TTJJ_powheg.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> measure_bchargeeff_logs/major.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> measure_bchargeeff_logs/minor.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG ${NMAX} &> measure_bchargeeff_logs/tW.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} &> measure_bchargeeff_logs/SingleMuon.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG ${NMAX} &> measure_bchargeeff_logs/SingleElectron.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG ${NMAX} &> measure_bchargeeff_logs/NoSkim.log&
