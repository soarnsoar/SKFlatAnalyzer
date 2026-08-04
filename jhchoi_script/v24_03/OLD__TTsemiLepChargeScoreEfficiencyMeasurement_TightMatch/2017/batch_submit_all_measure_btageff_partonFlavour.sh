mkdir -p measure_btageff_partonFlavour_logs/

SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags measure_btageff_partonFlavour"
YEAR=2017
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG &> measure_btageff_partonFlavour_logs/TTLJ_powheg.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i TTJJ_powheg -n 50 -e ${YEAR} $FLAG &> measure_btageff_partonFlavour_logs/TTJJ_powheg.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG &> measure_btageff_partonFlavour_logs/major.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> measure_btageff_partonFlavour_logs/minor.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG &> measure_btageff_partonFlavour_logs/tW.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG &> measure_btageff_partonFlavour_logs/SingleMuon.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG &> measure_btageff_partonFlavour_logs/SingleElectron.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG &> measure_btageff_partonFlavour_logs/NoSkim.log&
