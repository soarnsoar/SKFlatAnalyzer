#PreselectionAnalyzer
mkdir -p jetpuid_loose_kincut_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags jetpuid_loose,kincutopt"
NMAX="--nmax 400"
YEAR=2016b
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_kincut_logs/major.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_kincut_logs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_kincut_logs/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_kincut_logs/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_kincut_logs/DoubleEG.log&
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_kincut_logs/NoSkim.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_kincut_logs/VV.log&
