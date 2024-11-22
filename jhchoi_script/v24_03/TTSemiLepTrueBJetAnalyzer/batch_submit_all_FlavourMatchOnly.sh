mkdir -p logs/
mkdir -p syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags FlavourMatchOnly"
#FLAG=""
#YEARS=(2016preVFP 2016postVFP 2017 2018)
#YEAR=2017


YEAR=2016preVFP
SKFlat.py -a TTSemiLepTrueBJetAnalyzer -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG &> logs/FlavourMatchOnly_${YEAR}.log&
sleep 30

YEAR=2016postVFP
SKFlat.py -a TTSemiLepTrueBJetAnalyzer -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG &> logs/FlavourMatchOnly_${YEAR}.log&
sleep 30

YEAR=2017
SKFlat.py -a TTSemiLepTrueBJetAnalyzer -i TTLJ_powheg -n 100 -e ${YEAR} $FLAG &> logs/FlavourMatchOnly_${YEAR}.log&
sleep 30

YEAR=2018
SKFlat.py -a TTSemiLepTrueBJetAnalyzer -i TTLJ_powheg -n 100 -e ${YEAR} $FLAG &> logs/FlavourMatchOnly_${YEAR}.log&
sleep 30

