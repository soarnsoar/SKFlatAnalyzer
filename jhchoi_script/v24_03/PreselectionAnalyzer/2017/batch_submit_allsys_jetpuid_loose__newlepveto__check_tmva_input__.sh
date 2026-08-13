#PreselectionAnalyzer
mkdir -p jetpuid_loose_newlepveto_check_tmva_input_syslogs/

SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
FLAG="--userflags runSys,jetpuid_loose,newlepveto,check_tmva_input"
NMAX="--nmax 400"
MEM="--memory 6399 --count 2 "

SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_check_tmva_input_syslogs/major.log&
sleep 3
MEM="--memory 3199 --count 1"
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_check_tmva_input_syslogs/NoSkim.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_check_tmva_input_syslogs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_check_tmva_input_syslogs/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_check_tmva_input_syslogs/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_check_tmva_input_syslogs/DoubleEG.log&

SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_check_tmva_input_syslogs/VV.log&

