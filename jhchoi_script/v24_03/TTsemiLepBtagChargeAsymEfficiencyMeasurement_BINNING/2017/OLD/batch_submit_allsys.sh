#TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING
mkdir -p TopMassWindow_logs/
mkdir -p syslogs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys"
#FLAG=""
YEAR=2017
MAXJOB=" --nmax 300 "
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG $MAXJOB &> syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG $MAXJOB &> syslogs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG $MAXJOB &> syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_tW.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> syslogs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB &> syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleElectron -n 20 -e ${YEAR} $FLAG $MAXJOB &> syslogs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> syslogs/NoSkim.log&
