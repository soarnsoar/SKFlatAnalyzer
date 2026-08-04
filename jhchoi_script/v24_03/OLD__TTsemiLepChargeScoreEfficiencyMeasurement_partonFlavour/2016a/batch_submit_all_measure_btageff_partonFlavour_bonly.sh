mkdir -p measure_btageff_partonFlavour_bonly_logs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags measure_btageff_partonFlavour_bonly"
YEAR=2016a
NMAX="--nmax 150"
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG $NMAX &> measure_btageff_partonFlavour_bonly_logs/TTLJ_powheg.log&
sleep 10
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG $NMAX  &> measure_btageff_partonFlavour_bonly_logs/major.log&
sleep 10
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG $NMAX  &> measure_btageff_partonFlavour_bonly_logs/minor.log&
sleep 10
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG $NMAX  &> measure_btageff_partonFlavour_bonly_logs/tW.log&
sleep 10
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG $NMAX  &> measure_btageff_partonFlavour_bonly_logs/SingleMuon.log&
sleep 10
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG $NMAX  &> measure_btageff_partonFlavour_bonly_logs/SingleElectron.log&
sleep 10
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG $NMAX  &> measure_btageff_partonFlavour_bonly_logs/NoSkim.log&

