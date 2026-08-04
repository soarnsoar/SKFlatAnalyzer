#PreselectionToBDTRegionAnalyzer
mkdir -p jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/
#
SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
FLAG="--userflags runSys,jetpuid_loose,lepveto,use_beffasym,bdt2512.5,bdtcut"
NMAX="--nmax 400"
MEM="--memory 9500"
YEAR=2016a
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 --count 3 -e ${YEAR} $FLAG ${NMAX} ${MEM}&> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/major.log&
sleep 5
MEM=""
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/minor.log&
sleep 5
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/tW.log&
sleep 5
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/DoubleMuon.log&
sleep 5
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/DoubleEG.log&
sleep 5
SKFlat.py -a PreselectionToBDTRegionAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/NoSkim.log&
sleep 5
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} ${MEM} &> jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtcut_syslogs/VV.log&
