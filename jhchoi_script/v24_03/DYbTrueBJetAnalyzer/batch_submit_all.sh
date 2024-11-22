mkdir -p logs/
mkdir -p syslogs/

SKIM=""
#FLAG="--userflags runSys"
FLAG=""
#YEARS=(2016preVFP 2016postVFP 2017 2018)
#YEAR=2017


YEAR=2016preVFP
SKFlat.py -a DYbTrueBJetAnalyzer -i DYJetsToMuMu_MiNNLO -n 50 -e ${YEAR} $FLAG &> logs/MuMu${YEAR}.log&
SKFlat.py -a DYbTrueBJetAnalyzer -i DYJetsToEE_MiNNLO -n 50 -e ${YEAR} $FLAG &> logs/EE${YEAR}.log&
sleep 30

YEAR=2016postVFP
SKFlat.py -a DYbTrueBJetAnalyzer -i DYJetsToMuMu_MiNNLO -n 50 -e ${YEAR} $FLAG &> logs/MuMu${YEAR}.log&
SKFlat.py -a DYbTrueBJetAnalyzer -i DYJetsToEE_MiNNLO -n 50 -e ${YEAR} $FLAG &> logs/EE${YEAR}.log&

sleep 30

YEAR=2017
SKFlat.py -a DYbTrueBJetAnalyzer -i DYJetsToMuMu_MiNNLO -n 50 -e ${YEAR} $FLAG &> logs/MuMu${YEAR}.log&
SKFlat.py -a DYbTrueBJetAnalyzer -i DYJetsToEE_MiNNLO -n 50 -e ${YEAR} $FLAG &> logs/EE${YEAR}.log&

#sleep 30

YEAR=2018
SKFlat.py -a DYbTrueBJetAnalyzer -i DYJetsToMuMu_MiNNLO -n 50 -e ${YEAR} $FLAG &> logs/MuMu${YEAR}.log&
SKFlat.py -a DYbTrueBJetAnalyzer -i DYJetsToEE_MiNNLO -n 50 -e ${YEAR} $FLAG &> logs/EE${YEAR}.log&

sleep 30

