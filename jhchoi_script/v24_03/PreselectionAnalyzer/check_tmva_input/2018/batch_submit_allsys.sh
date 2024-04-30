#PreselectionAnalyzer
mkdir -p syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,check_tmva_input"
#FLAG=""
YEAR=2018
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG &> syslogs/major.log&
sleep 120
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> syslogs/NoSkim.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> syslogs/minor.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG &> syslogs/tW.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG &> syslogs/DoubleMuon.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG &> syslogs/EGamma.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG &> syslogs/VV.log&

