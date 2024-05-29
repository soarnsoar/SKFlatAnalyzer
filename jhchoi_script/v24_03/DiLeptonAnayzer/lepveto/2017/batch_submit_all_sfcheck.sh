mkdir -p logs_checksf/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags checksf"
#FLAG=""

SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG &> logs_checksf/major.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG &> logs_checksf/minor.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG &> logs_checksf/tW.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG &> logs_checksf/DoubleMuon.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG &> logs_checksf/DoubleEG.log&
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG &> logs_checksf/NoSkim.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG &> logs_checksf/VV.log&

