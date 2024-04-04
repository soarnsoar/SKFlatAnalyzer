mkdir -p syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
#FLAG=""

SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG &> syslogs/major.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG &> syslogs/minor.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 5 -e 2017 $FLAG &> syslogs/tW.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 5 -e 2017 $FLAG &> syslogs/DoubleMuon.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleEG -n 5 -e 2017 $FLAG &> syslogs/DoubleEG.log&
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG &> syslogs/NoSkim.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG &> syslogs/VV.log&

