mkdir -p logs/
mkdir -p syslogs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags FlavourMatchBase,HcbCR,ForBinning"
#FLAG=""
YEAR=2016a
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG &> logs/SingleMuon.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG &> logs/SingleElectron.log&


