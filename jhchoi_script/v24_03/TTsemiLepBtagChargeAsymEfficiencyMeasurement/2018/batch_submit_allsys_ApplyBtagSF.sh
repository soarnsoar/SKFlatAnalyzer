#TTsemiLepBtagChargeAsymEfficiencyMeasurement
mkdir -p ApplyBtagSF_syslogs/
mkdir -p syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys,ApplyBtagSF"
#FLAG=""
YEAR=2018
MAXJOB=" --nmax 300 "
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 250 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l  inputlist_major.txt -n 40 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_syslogs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 40 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l inputlist_tW.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_syslogs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -i EGamma -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_syslogs/EGamma.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_syslogs/NoSkim.log&

