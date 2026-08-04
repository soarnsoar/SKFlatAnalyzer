#PreselectionAnalyzer
mkdir -p jetpuid_loose_newlepveto_kincutopt_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags jetpuid_loose,newlepveto,kincutopt"
NMAX="--nmax 400"

YEAR=2018
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_kincutopt_logs/major.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_kincutopt_logs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_kincutopt_logs/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_kincutopt_logs/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_kincutopt_logs/EGamma.log&
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_kincutopt_logs/NoSkim.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_kincutopt_logs/VV.log&

