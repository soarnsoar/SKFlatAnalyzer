#PreselectionToBDTRegionAnalyzer
#mkdir -p jetpuid_loose_lepveto_use_beffasym_bdt2512.5_bdtopt_logs/
mkdir -p jetpuid_loose_lepveto_bdt2512.5_bdtcut_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
FLAG="--userflags jetpuid_loose,lepveto,bdt2512.5,bdtcut"
NMAX="--nmax 200"

YEAR=2016b
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_bdt2512.5_bdtcut_logs/major.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_bdt2512.5_bdtcut_logs/minor.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_bdt2512.5_bdtcut_logs/tW.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_bdt2512.5_bdtcut_logs/DoubleMuon.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_bdt2512.5_bdtcut_logs/DoubleEG.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_bdt2512.5_bdtcut_logs/NoSkim.log&
SKFlat.py -a PreselectionToBDTRegionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_lepveto_bdt2512.5_bdtcut_logs/VV.log&
