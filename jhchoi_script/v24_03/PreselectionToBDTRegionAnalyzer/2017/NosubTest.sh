#PreselectionToBDTRegionAnalyzer
mkdir -p jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_measure_bchargeeff_logs/

SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
FLAG="--userflags jetpuid_loose,use_beffasym,newlepveto,bdt2608.2,bdtcut,measure_bchargeeff"


NMAX="--nmax 400"
MEM="--memory 9500"

SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 1  --count 3 -e 2017 $FLAG ${NMAX} ${MEM} --no_exec --reduction 1000
