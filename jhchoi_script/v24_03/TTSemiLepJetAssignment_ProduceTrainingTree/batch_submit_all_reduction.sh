mkdir -p logs/
mkdir -p syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys"
FLAG=""
FLAG="--userflags reduction_1M"
#YEARS=(2016preVFP 2016postVFP 2017 2018)
#YEAR=2017


YEAR=2016preVFP
SKFlat.py -a TTSemiLepJetAssignment_ProduceTrainingTree -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG &> logs/reduction_${YEAR}.log&
sleep 30

YEAR=2016postVFP
SKFlat.py -a TTSemiLepJetAssignment_ProduceTrainingTree -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG &> logs/reduction_${YEAR}.log&
sleep 30

YEAR=2017
#SKFlat.py -a TTSemiLepJetAssignment_ProduceTrainingTree -i TTLJ_powheg -n 100 -e ${YEAR} $FLAG &> logs/reduction_${YEAR}.log&
#sleep 30

YEAR=2018
#SKFlat.py -a TTSemiLepJetAssignment_ProduceTrainingTree -i TTLJ_powheg -n 100 -e ${YEAR} $FLAG &> logs/reduction_${YEAR}.log&
#sleep 30

