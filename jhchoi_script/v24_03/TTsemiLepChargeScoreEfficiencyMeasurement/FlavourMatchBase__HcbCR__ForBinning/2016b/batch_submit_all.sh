mkdir -p logs/
mkdir -p syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags FlavourMatchBase,HcbCR,ForBinning"

YEAR=2016b
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement   -i SingleMuon -n 50 -e ${YEAR} $FLAG &> logs/SingleMuon.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement   -i SingleElectron -n 50 -e ${YEAR} $FLAG &> logs/SingleElectron.log&


