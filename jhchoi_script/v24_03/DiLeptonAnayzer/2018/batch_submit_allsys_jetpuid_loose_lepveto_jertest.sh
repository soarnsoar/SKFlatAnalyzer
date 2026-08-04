mkdir -p jetpuid_loose_lepveto_jertest_syslogs/

SKIM="--skim SkimTree_Dilepton"
#FLAG="--userflags runSys"
FLAG="--userflags runSys,jetpuid_loose,lepveto,jertest"

#FLAG=""
YEAR=2018
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DYJetsToMuMu_MiNNLO -n 65 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_jertest_syslogs/DYJetsToMuMu_MiNNLO.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DYJetsToEE_MiNNLO -n 58 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_jertest_syslogs/DYJetsToEE_MiNNLO.log&
sleep 120
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_jertest_syslogs/minor.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_jertest_syslogs/tW.log&
sleep 5
#SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_jertest_syslogs/DoubleMuon.log&
#sleep 5
#SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_jertest_syslogs/EGamma.log&
#sleep 5
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_jertest_syslogs/NoSkim.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG &> jetpuid_loose_lepveto_jertest_syslogs/VV.log&

