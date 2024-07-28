#bbarAsymAnalyzer
mkdir -p logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
FLAG="--userflags dnn_v2405.4,apply_dnncut"
YEAR=2018
SKFlat.py -a bbarAsymAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG &> logs/major.log&
SKFlat.py -a bbarAsymAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> logs/minor.log&
SKFlat.py -a bbarAsymAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG &> logs/tW.log&
SKFlat.py -a bbarAsymAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG &> logs/DoubleMuon.log&
SKFlat.py -a bbarAsymAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG &> logs/EGamma.log&
SKFlat.py -a bbarAsymAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> logs/NoSkim.log&
SKFlat.py -a bbarAsymAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG &> logs/VV.log&

