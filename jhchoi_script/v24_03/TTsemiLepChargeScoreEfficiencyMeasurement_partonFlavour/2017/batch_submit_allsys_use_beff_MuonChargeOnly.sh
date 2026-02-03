mkdir -p logs/
mkdir -p syslogs/
mkdir -p use_beff_MuonChargeOnly_syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys,use_beff,MuonChargeOnly"
MEMOERY="--memory 10000"
MEMOERYHIGH="--memory 22000"
YEAR=2017
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG ${MEMOERYHIGH} &> use_beff_MuonChargeOnly_syslogs/TTLJ_powheg.log&
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i TTJJ_powheg -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_MuonChargeOnly_syslogs/TTJJ_powheg.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_MuonChargeOnly_syslogs/major.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_MuonChargeOnly_syslogs/minor.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_MuonChargeOnly_syslogs/tW.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_MuonChargeOnly_syslogs/SingleMuon.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_MuonChargeOnly_syslogs/SingleElectron.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_MuonChargeOnly_syslogs/NoSkim.log&

