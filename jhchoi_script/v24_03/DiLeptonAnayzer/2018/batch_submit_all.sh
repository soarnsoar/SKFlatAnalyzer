mkdir -p logs/

SKIM="--skim SkimTree_Dilepton"
era=2018
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_major.txt -n 150 -e ${era} &> logs/major.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 150 -e ${era} &> logs/minor.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 150 -e ${era} &> logs/tW.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 300 -e ${era} &> logs/DoubleMuon.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleEG -n 150 -e ${era} &> logs/DoubleEG.log&
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 150 -e ${era} &> logs/NoSkim.log&

