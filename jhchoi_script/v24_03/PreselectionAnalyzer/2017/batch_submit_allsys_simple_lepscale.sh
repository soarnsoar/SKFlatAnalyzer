#PreselectionAnalyzer
mkdir -p simple_lepscale/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,simple_lepscale"
#FLAG=""

SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 125 -e 2017 $FLAG &> simple_lepscale/major.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG &> simple_lepscale/minor.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 5 -e 2017 $FLAG &> simple_lepscale/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 5 -e 2017 $FLAG &> simple_lepscale/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 5 -e 2017 $FLAG &> simple_lepscale/DoubleEG.log&
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG &> simple_lepscale/NoSkim.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG &> simple_lepscale/VV.log&

