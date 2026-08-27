mkdir -p logs/
YEAR=2017
MAXJOB=" --nmax 100 "

#SkimTree_SingleLepton_1DeepJetTightWP


SKFlat.py -a SkimTree_SingleLepton_1DeepJetTightWP -i TTLJ_powheg -n 300 -e ${YEAR} $MAXJOB &> logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a SkimTree_SingleLepton_1DeepJetTightWP -l  inputlist_major.txt -n 300 -e ${YEAR} $MAXJOB &> logs/major.log&
sleep 15
SKFlat.py -a SkimTree_SingleLepton_1DeepJetTightWP -l inputlist_minor.txt -n 300 -e ${YEAR} $MAXJOB &> logs/minor.log&
sleep 15
SKFlat.py -a SkimTree_SingleLepton_1DeepJetTightWP -l inputlist_tW.txt -n 300 -e ${YEAR} $MAXJOB &> logs/tW.log&
sleep 15
SKFlat.py -a SkimTree_SingleLepton_1DeepJetTightWP -i SingleMuon -n 300 -e ${YEAR} $MAXJOB &> logs/SingleMuon.log&
sleep 15
SKFlat.py -a SkimTree_SingleLepton_1DeepJetTightWP -i SingleElectron -n 300 -e ${YEAR} $MAXJOB &> logs/SingleElectron.log&
sleep 15
SKFlat.py -a SkimTree_SingleLepton_1DeepJetTightWP -l inputlist_NoSkim.txt -n 300 -e ${YEAR} $MAXJOB &> logs/NoSkim.log&
