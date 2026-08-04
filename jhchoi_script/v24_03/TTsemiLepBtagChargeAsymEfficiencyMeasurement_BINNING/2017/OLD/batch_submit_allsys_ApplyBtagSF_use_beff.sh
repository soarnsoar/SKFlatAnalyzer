#TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING
mkdir -p logs/
mkdir -p ApplyBtagSF_use_beff_syslogs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys,ApplyBtagSF,use_beff"
#FLAG=""
YEAR=2017
MAXJOB=" --nmax 300 "
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_syslogs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_tW.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_syslogs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleElectron -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_syslogs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_syslogs/NoSkim.log&
