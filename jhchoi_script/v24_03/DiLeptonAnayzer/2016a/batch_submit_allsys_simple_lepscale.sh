mkdir -p simple_lepscale/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,simple_lepscale"
#FLAG=""
YEAR=2016a
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_major.txt -n 125 -e ${YEAR} $FLAG &> simple_lepscale/major.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> simple_lepscale/minor.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 5 -e ${YEAR} $FLAG &> simple_lepscale/tW.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 5 -e ${YEAR} $FLAG &> simple_lepscale/DoubleMuon.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleEG -n 5 -e ${YEAR} $FLAG &> simple_lepscale/DoubleEG.log&
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> simple_lepscale/NoSkim.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG &> simple_lepscale/VV.log&

