#PreselectionAnalyzer
mkdir -p jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,jetpuid_loose,lepveto,check_tmva_input,bdt2512.5"
NMAX="--nmax 400"
MEM="--memory 9000"


SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/major.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/NoSkim.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/DoubleEG.log&

SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/VV.log&

