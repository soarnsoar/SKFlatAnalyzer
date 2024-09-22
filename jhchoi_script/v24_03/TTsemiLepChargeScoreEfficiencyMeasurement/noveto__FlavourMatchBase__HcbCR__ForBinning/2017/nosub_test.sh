mkdir -p logs/
mkdir -p syslogs/
SKIM=""
FLAG="--userflags noveto,FlavourMatchBase,HcbCR,ForBinning"
REDUCTION="--reduction 10000"
#FLAG=""
YEAR=2017
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG --no_exec ${REDUCTION} -n 1 

