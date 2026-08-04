mkdir -p logs/

SKIM="--skim SkimTree_Dilepton"


SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_DY.txt -n 100 -e 2017 &> logs/DY.log&


