mkdir -p use_beff_apply_bchargeeff_TT_logs/

SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags use_beff,apply_bchargeeff_TT"
YEAR=2017
NMAX="--nmax 150"

SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i TTLJ_powheg -n 150 -e ${YEAR} $FLAG $NMAX &> use_beff_apply_bchargeeff_TT_logs/TTLJ_powheg.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i TTJJ_powheg -n 50 -e ${YEAR} $FLAG $NMAX &> use_beff_apply_bchargeeff_TT_logs/TTJJ_powheg.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG $NMAX &> use_beff_apply_bchargeeff_TT_logs/major.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG $NMAX &> use_beff_apply_bchargeeff_TT_logs/minor.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG $NMAX &> use_beff_apply_bchargeeff_TT_logs/tW.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG $NMAX &> use_beff_apply_bchargeeff_TT_logs/SingleMuon.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG $NMAX &> use_beff_apply_bchargeeff_TT_logs/SingleElectron.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG $NMAX &> use_beff_apply_bchargeeff_TT_logs/NoSkim.log&
