#TTsemiLepBtagChargeAsymEfficiencyMeasurement
mkdir -p TopMassWindow_syslogs/
mkdir -p syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys"
#FLAG=""
MAXJOB=" --nmax 300 "
YEAR=2016a
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 150 -e ${YEAR} $FLAG ${MAXJOB} &> syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l  inputlist_major.txt -n 40 -e ${YEAR} $FLAG ${MAXJOB} &> syslogs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 40 -e ${YEAR} $FLAG ${MAXJOB} &> syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l inputlist_tW.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> syslogs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -i SingleElectron -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> syslogs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG ${MAXJOB} &> syslogs/NoSkim.log&

