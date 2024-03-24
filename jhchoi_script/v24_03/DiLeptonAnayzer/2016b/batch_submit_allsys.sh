mkdir -p syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
#FLAG=""
YEAR=2016b
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG &> syslogs/major.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> syslogs/minor.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 5 -e ${YEAR} $FLAG &> syslogs/tW.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 5 -e ${YEAR} $FLAG &> syslogs/DoubleMuon.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleEG -n 5 -e ${YEAR} $FLAG &> syslogs/DoubleEG.log&
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> syslogs/NoSkim.log&

