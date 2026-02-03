#TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING
mkdir -p logs/
mkdir -p syslogs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
#FLAG="--userflags TopMassWindow"
FLAG=""
MAXJOB=" --nmax 120 "
YEAR=2016b
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG ${MAXJOB} &> logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l  inputlist_major.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> logs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_minor.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> logs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> logs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING   -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB &> logs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING   -i SingleElectron -n 20 -e ${YEAR} $FLAG $MAXJOB &> logs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> logs/NoSkim.log&

