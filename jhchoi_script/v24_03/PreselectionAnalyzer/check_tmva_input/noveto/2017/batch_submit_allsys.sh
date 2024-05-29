#PreselectionAnalyzer
mkdir -p syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,check_tmva_input,noveto"
#FLAG=""

SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 40 -e 2017 $FLAG &> syslogs/major.log&
sleep 120
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG &> syslogs/NoSkim.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG &> syslogs/minor.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG &> syslogs/tW.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG &> syslogs/DoubleMuon.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG &> syslogs/DoubleEG.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG &> syslogs/VV.log&
sleep 5
