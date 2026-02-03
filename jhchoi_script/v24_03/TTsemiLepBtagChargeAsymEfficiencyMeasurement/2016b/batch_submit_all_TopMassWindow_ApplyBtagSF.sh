#TTsemiLepBtagChargeAsymEfficiencyMeasurement
mkdir -p TopMassWindow_ApplyBtagSF_logs/
mkdir -p syslogs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags TopMassWindow,ApplyBtagSF"
#FLAG=""
MAXJOB=" --nmax 120 "
YEAR=2016b
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG ${MAXJOB} &> TopMassWindow_ApplyBtagSF_logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l  inputlist_major.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_logs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_logs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_logs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement   -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_logs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement   -i SingleElectron -n 20 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_logs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_logs/NoSkim.log&

