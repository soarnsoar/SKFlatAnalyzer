mkdir -p logs/
mkdir -p syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys"
YEAR=2016a
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG &> syslogs/TTLJ_powheg.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i TTJJ_powheg -n 50 -e ${YEAR} $FLAG &> syslogs/TTJJ_powheg.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l  inputlist_major.txt -n 200 -e ${YEAR} $FLAG &> syslogs/major.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> syslogs/minor.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG &> syslogs/tW.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG &> syslogs/SingleMuon.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG &> syslogs/SingleElectron.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> syslogs/NoSkim.log&

