#PreselectionAnalyzer
mkdir -p jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/

SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
FLAG="--userflags jetpuid_loose,newlepveto,use_beffasym,bdt_v2608_2,bdtopt,bdtopt_jetfin"
#NMAX="--nmax 480"
#MEM="--memory 6399 --count 3 "
NMAX="--nmax 800"
MEM="--memory 3200 --count 2 "


SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 150 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/major.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_TT.txt -n 150 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/TT.log&
SKFlat.py -a PreselectionAnalyzer ${SKIM} -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/NoSkim.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/DoubleEG.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/VV.log&


#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/major.log&
#SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/NoSkim.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/minor.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/tW.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/DoubleMuon.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/DoubleEG.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtopt_bdtopt_jetfin_logs/VV.log&

