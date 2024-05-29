mkdir -p logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
FLAG=""
YEAR=2016a

ARR_PUID=("jetpuid_tight" "jetpuid_medium" "jetpuid_loose" "nojetpuid")
for PUID in ${ARR_PUID[@]};do
    FLAG="--userflags ${PUID}"
    SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG &> logs/${PUID}_major.log&
    sleep 10
    SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> logs/${PUID}_minor.log&
    sleep 10
    SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG &> logs/${PUID}_tW.log&
    sleep 10
    SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG &> logs/${PUID}_DoubleMuon.log&
    sleep 10
    SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG &> logs/${PUID}_DoubleEG.log&
    sleep 10
    SKFlat.py -a DiLeptonAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> logs/${PUID}_NoSkim.log&
    sleep 10
    SKFlat.py -a DiLeptonAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG &> logs/${PUID}_VV.log&
    sleep 10
done
