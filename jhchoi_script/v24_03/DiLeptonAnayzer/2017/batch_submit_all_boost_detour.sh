##test after cmssw13 root6.26 boost-bug detour

mkdir -p logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
FLAG="--userflag boost_detour"

SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_major.txt -n 10 -e 2017 $FLAG &> logs/major.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 10 -e 2017 $FLAG &> logs/NoSkim.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 10 -e 2017 $FLAG &> logs/minor.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 10 -e 2017 $FLAG &> logs/tW.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 10 -e 2017 $FLAG &> logs/DoubleMuon.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleEG -n 10 -e 2017 $FLAG &> logs/DoubleEG.log&
sleep 15
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 10 -e 2017 $FLAG &> logs/VV.log&

