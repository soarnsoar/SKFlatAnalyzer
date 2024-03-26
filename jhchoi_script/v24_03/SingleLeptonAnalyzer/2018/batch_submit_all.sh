mkdir -p logs/
mkdir -p syslogs/
SKIM="--skim SkimTree_SingleLepton"
FLAG="--userflags runSys"
FLAG=""
YEAR=2018
SKFlat.py -a SingleLeptonAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG &> logs/major.log&
SKFlat.py -a SingleLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> logs/minor.log&
SKFlat.py -a SingleLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG &> logs/tW.log&
SKFlat.py -a SingleLeptonAnalyzer  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG &> logs/SingleMuon.log&
SKFlat.py -a SingleLeptonAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG &> logs/EGamma.log&
SKFlat.py -a SingleLeptonAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> logs/NoSkim.log&

