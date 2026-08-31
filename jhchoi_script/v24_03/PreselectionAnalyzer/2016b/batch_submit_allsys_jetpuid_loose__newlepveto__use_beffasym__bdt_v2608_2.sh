#PreselectionAnalyzer
mkdir -p jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/

SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
FLAG="--userflags runSys"
FLAG="--userflags runSys,jetpuid_loose,newlepveto,use_beffasym,bdt_v2608_2"
NMAX="--nmax 800"
MEM="--memory 6399 --count 3 "
YEAR=2016b


SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/major.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_TT.txt -n 150 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/TT.log&
MEM="--memory 3199 --count 2"

SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/DoubleEG.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/NoSkim.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/VV.log&



#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/major.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/minor.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/tW.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/DoubleMuon.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/DoubleEG.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/NoSkim.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX}  ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_syslogs/VV.log&
