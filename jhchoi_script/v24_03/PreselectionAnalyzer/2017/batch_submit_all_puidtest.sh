#PreselectionAnalyzer
mkdir -p logs_jetpuid/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
FLAG=""

ARR_PUID=("jetpuid_tight" "jetpuid_medium" "jetpuid_loose" "nojetpuid")
for PUID in ${ARR_PUID[@]};do
    FLAG="--userflags ${PUID}"
    SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG &> logs_jetpuid/${PUID}_major.log&
    sleep 60
    SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG &> logs_jetpuid/${PUID}_NoSkim.log&
    sleep 60
    SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG &> logs_jetpuid/${PUID}_minor.log&
    sleep 60
    SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG &> logs_jetpuid/${PUID}_tW.log&
    sleep 60
    SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG &> logs_jetpuid/${PUID}_DoubleMuon.log&
    sleep 60
    SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG &> logs_jetpuid/${PUID}_DoubleEG.log&
    sleep 60
    SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG &> logs_jetpuid/${PUID}_VV.log&
    sleep 60
done
