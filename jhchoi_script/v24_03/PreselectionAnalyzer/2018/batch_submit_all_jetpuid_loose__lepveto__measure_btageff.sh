#PreselectionAnalyzer
mkdir -p jetpuid_loose_lepveto_measure_btageff_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags jetpuid_loose,lepveto,measure_btageff"
NMAX="--nmax 200"

YEAR=2018
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_measure_btageff_logs/major.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_measure_btageff_logs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_measure_btageff_logs/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_measure_btageff_logs/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i EGamma -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_measure_btageff_logs/EGamma.log&
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_measure_btageff_logs/NoSkim.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_measure_btageff_logs/VV.log&

