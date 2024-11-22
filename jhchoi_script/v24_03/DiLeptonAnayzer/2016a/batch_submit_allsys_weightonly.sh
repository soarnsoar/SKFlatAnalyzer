mkdir -p wsyslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,weightonly"
#FLAG=""
YEAR=2016a
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i  DYJetsToMuMu_MiNNLO -n 31 -e ${YEAR} $FLAG &> wsyslogs/DYJetsToMuMu_MiNNLO.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i  DYJetsToEE_MiNNLO -n 18 -e ${YEAR} $FLAG &> wsyslogs/DYJetsToEE_MiNNLO.log&
sleep 120
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> wsyslogs/minor.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG &> wsyslogs/tW.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG &> wsyslogs/DoubleMuon.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG &> wsyslogs/DoubleEG.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> wsyslogs/NoSkim.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG &> wsyslogs/VV.log&

