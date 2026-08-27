#PreselectionAnalyzer
mkdir -p jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,jetpuid_loose,lepveto,check_tmva_input,bdt2512.5"
NMAX="--nmax 400"
MEM="--memory 9000"
YEAR=2018
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/major.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG  ${NMAX} ${MEM}  &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM}  &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG  ${NMAX} ${MEM}  &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM}  &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/EGamma.log&
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM}  &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/NoSkim.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM}  &> jetpuid_loose_lepveto_check_tmva_input_bdt2512.5_syslogs/VV.log&

