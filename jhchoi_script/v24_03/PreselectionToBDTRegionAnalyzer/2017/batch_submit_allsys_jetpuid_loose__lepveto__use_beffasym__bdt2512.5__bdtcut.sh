#PreselectionToBDTRegionAnalyzer
#mkdir -p jetpuid_loose_lepveto_logs/
mkdir -p jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/

SKIM="--skim SkimTree_Dilepton"
#FLAG="--userflags jetpuid_loose,lepveto"
FLAG="--userflags runSys,jetpuid_loose,lepveto,use_beffasym,bdt2512.5,bdtcut"
NMAX="--nmax 400"
MEM="--memory 9500"

SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt --count 3 -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/major.log&
MEM=""
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/NoSkim.log&
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/minor.log&
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/tW.log&
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/DoubleMuon.log&
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/DoubleEG.log&
sleep 3
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/VV.log&

