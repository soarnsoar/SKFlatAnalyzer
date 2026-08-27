mkdir -p logs/
YEAR=2016a
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP -l  inputlist_major.txt -n 300 -e ${YEAR} &> logs/major.log&
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP  -l inputlist_minor.txt -n 300 -e ${YEAR} &> logs/minor.log&
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP  -l inputlist_tW.txt -n 300 -e ${YEAR} &> logs/tW.log&
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP  -i DoubleMuon -n 300 -e ${YEAR} &> logs/DoubleMuon.log&
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP  -i DoubleEG -n 300 -e ${YEAR} &> logs/DoubleEG.log&
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP -l inputlist_NoSkim.txt -n 300 -e ${YEAR} &> logs/NoSkim.log&
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP  -l  inputlist_VV.txt -n 300 -e ${YEAR} &> logs/VV.log&
