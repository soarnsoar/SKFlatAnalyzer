mkdir -p logs/
mkdir -p syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys"
FLAG=""
FLAG="--userflags njet4"
YEAR=2016b
SKFlat.py -a TwoBjets  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG &> logs/major.log&
SKFlat.py -a TwoBjets  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> logs/minor.log&
SKFlat.py -a TwoBjets  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG &> logs/tW.log&
SKFlat.py -a TwoBjets   -i SingleMuon -n 50 -e ${YEAR} $FLAG &> logs/SingleMuon.log&
SKFlat.py -a TwoBjets   -i SingleElectron -n 50 -e ${YEAR} $FLAG &> logs/SingleElectron.log&
SKFlat.py -a TwoBjets -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG &> logs/NoSkim.log&

