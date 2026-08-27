#PreselectionAnalyzer
#mkdir -p jetpuid_loose_lepveto_logs/
mkdir -p jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtopt_logs/

SKIM="--skim SkimTree_Dilepton"
#FLAG="--userflags jetpuid_loose,lepveto"
FLAG="--userflags jetpuid_loose,lepveto,use_beffasym,bdt2512.5,bdtopt"
NMAX="--nmax 200"


SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtopt_logs/major.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtopt_logs/NoSkim.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtopt_logs/minor.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtopt_logs/tW.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtopt_logs/DoubleMuon.log&
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtopt_logs/DoubleEG.log&

SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtopt_logs/VV.log&

