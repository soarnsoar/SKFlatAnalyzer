#PreselectionAnalyzer
mkdir -p jetpuid_loose_newlepveto_measure_btageff_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags jetpuid_loose,newlepveto,measure_btageff"
NMAX="--nmax 200"


SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 30 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_logs/major.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_TT.txt -n 150 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_logs/TT.log&

SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 30 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_logs/NoSkim.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 30 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_logs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 30 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_logs/tW.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 30 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_logs/DoubleMuon.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 30 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_logs/DoubleEG.log&

SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 30 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_newlepveto_measure_btageff_logs/VV.log&

