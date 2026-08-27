#PreselectionAnalyzer
mkdir -p jetpuid_loose_lepveto_check_tmva_input_pusysonly_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,jetpuid_loose,lepveto,check_tmva_input,pusysonly"


SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG &> jetpuid_loose_lepveto_check_tmva_input_pusysonly_logs/major.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG &> jetpuid_loose_lepveto_check_tmva_input_pusysonly_logs/NoSkim.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG &> jetpuid_loose_lepveto_check_tmva_input_pusysonly_logs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG &> jetpuid_loose_lepveto_check_tmva_input_pusysonly_logs/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG &> jetpuid_loose_lepveto_check_tmva_input_pusysonly_logs/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG &> jetpuid_loose_lepveto_check_tmva_input_pusysonly_logs/DoubleEG.log&

SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG &> jetpuid_loose_lepveto_check_tmva_input_pusysonly_logs/VV.log&

