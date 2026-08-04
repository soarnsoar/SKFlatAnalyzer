#TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING
mkdir -p ApplyBtagSF_use_beff_logs/
mkdir -p syslogs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags ApplyBtagSF,use_beff"
#FLAG=""
MAXJOB=" --nmax 120 "
YEAR=2016b
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG ${MAXJOB} &> ApplyBtagSF_use_beff_logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l  inputlist_major.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_logs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_minor.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_logs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_logs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING   -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_logs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING   -i SingleElectron -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_logs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_logs/NoSkim.log&

