#PreselectionAnalyzer
mkdir -p jetpuid_loose_newlepveto_measure_btageff_tight_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
FLAG="--userflags jetpuid_loose,newlepveto,measure_btageff_tight"
NMAX="--nmax 200"

YEAR=2016b
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_tight_logs/major.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_TT.txt -n 150 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_tight_logs/TT.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_tight_logs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_tight_logs/tW.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_tight_logs/DoubleMuon.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_tight_logs/DoubleEG.log&
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_tight_logs/NoSkim.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 30 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_tight_logs/VV.log&
