#TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING
mkdir -p measure_btageff_partonFlavour_bonly_logs/
mkdir -p syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags measure_btageff_partonFlavour_bonly"
#FLAG=""
MAXJOB=" --nmax 120 "
YEAR=2016a
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG ${MAXJOB} &> measure_btageff_partonFlavour_bonly_logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l  inputlist_major.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> measure_btageff_partonFlavour_bonly_logs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_minor.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> measure_btageff_partonFlavour_bonly_logs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG ${MAXJOB} &> measure_btageff_partonFlavour_bonly_logs/tW.log&
sleep 15
#SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> measure_btageff_partonFlavour_bonly_logs/SingleMuon.log&
#sleep 15
#SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleElectron -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> measure_btageff_partonFlavour_bonly_logs/SingleElectron.log&
#sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG ${MAXJOB} &> measure_btageff_partonFlavour_bonly_logs/NoSkim.log&

