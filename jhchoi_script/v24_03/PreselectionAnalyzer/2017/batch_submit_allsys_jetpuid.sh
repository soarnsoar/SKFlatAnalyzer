#PreselectionAnalyzer
mkdir -p jetpuid_loose_syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,jetpuid_loose"

NMAX="--nmax 400"
MEM="--memory 9500"

SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 --count 3 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_syslogs/major.log&
sleep 3
MEM="--memory 3200"
SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_syslogs/NoSkim.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_syslogs/minor.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_syslogs/tW.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_syslogs/DoubleMuon.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_syslogs/DoubleEG.log&
sleep 3
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${NMAX} ${MEM} &> jetpuid_loose_syslogs/VV.log&

