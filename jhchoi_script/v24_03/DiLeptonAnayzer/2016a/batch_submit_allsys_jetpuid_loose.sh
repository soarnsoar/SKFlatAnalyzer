mkdir -p jetpuid_loose_syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,jetpuid_loose"
NMAX="--nmax 400"

#FLAG=""
YEAR=2016a
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i  DYJetsToMuMu_MiNNLO -n 31 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_syslogs/DYJetsToMuMu_MiNNLO.log&
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i  DYJetsToEE_MiNNLO -n 18 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_syslogs/DYJetsToEE_MiNNLO.log&
sleep 120
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_syslogs/minor.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_syslogs/tW.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_syslogs/DoubleMuon.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_syslogs/DoubleEG.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_syslogs/NoSkim.log&
sleep 5
SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_syslogs/VV.log&

