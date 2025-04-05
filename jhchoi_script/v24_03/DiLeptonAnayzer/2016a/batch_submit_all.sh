mkdir -p logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
FLAG=""
YEAR=2016a
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_major.txt -n 10 -e ${YEAR} $FLAG &> logs/major.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 10 -e ${YEAR} $FLAG &> logs/minor.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG &> logs/tW.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 10 -e ${YEAR} $FLAG &> logs/DoubleMuon.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleEG -n 10 -e ${YEAR} $FLAG &> logs/DoubleEG.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG &> logs/NoSkim.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 10 -e ${YEAR} $FLAG &> logs/VV.log&
