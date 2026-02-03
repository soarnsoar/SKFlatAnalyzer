#TTsemiLepBtagChargeAsymEfficiencyMeasurement
mkdir -p TopMassWindow_logs/
mkdir -p TopMassWindow_ApplyBtagSF_syslogs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys,TopMassWindow,ApplyBtagSF"
#FLAG=""
YEAR=2017
MAXJOB=" --nmax 300 "
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_syslogs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -l inputlist_tW.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_syslogs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement  ${SKIM} -i SingleElectron -n 20 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_syslogs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> TopMassWindow_ApplyBtagSF_syslogs/NoSkim.log&
