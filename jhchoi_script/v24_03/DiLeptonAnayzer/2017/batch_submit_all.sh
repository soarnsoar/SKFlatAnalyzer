mkdir -p logs/

SKIM="--skim SkimTree_Dilepton"

SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_major.txt -n 50 -e 2017 &> logs/major.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 &> logs/minor.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 &> logs/tW.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 &> logs/DoubleMuon.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 &> logs/DoubleEG.log&
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 &> logs/NoSkim.log&

