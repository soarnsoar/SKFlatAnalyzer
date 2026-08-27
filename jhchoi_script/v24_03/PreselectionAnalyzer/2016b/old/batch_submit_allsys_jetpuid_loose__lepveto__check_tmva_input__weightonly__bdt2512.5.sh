#PreselectionAnalyzer
mkdir -p jetpuid_loose_lepveto_check_tmva_input_weightonly_bdt2512_5_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
FLAG="--userflags runSys,jetpuid_loose,lepveto,check_tmva_input,weightonly,bdt2512.5"
YEAR=2016b
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_check_tmva_input_weightonly_bdt2512_5_logs/major.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_check_tmva_input_weightonly_bdt2512_5_logs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_check_tmva_input_weightonly_bdt2512_5_logs/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_check_tmva_input_weightonly_bdt2512_5_logs/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_check_tmva_input_weightonly_bdt2512_5_logs/DoubleEG.log&
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_check_tmva_input_weightonly_bdt2512_5_logs/NoSkim.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_check_tmva_input_weightonly_bdt2512_5_logs/VV.log&
