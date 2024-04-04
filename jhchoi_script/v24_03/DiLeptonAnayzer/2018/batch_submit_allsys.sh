mkdir -p syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
#FLAG=""
YEAR=2018
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG &> syslogs/major.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> syslogs/minor.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 5 -e ${YEAR} $FLAG &> syslogs/tW.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 5 -e ${YEAR} $FLAG &> syslogs/DoubleMuon.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i EGamma -n 5 -e ${YEAR} $FLAG &> syslogs/EGamma.log&
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> syslogs/NoSkim.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG &> syslogs/VV.log&

