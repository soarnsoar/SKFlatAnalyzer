#PreselectionAnalyzer
mkdir -p jetpuid_loose_newlepveto_check_tmva_input_syslogs/
SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
FLAG="--userflags runSys"
FLAG="--userflags runSys,jetpuid_loose,newlepveto,check_tmva_input"
NMAX="--nmax 400"
MEM="--memory 6399 --count 2 "


mkdir -p testlog/
YEAR=2016b
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 5 -e ${YEAR} $FLAG ${NMAX}  ${MEM} --reduction 1000 &> testlog/log.txt&

