#TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING
mkdir -p ApplyBtagSF_use_beff_dasym_JETPUID_L_chi2kincut_logs/
mkdir -p syslogs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
#FLAG="--userflags TopMassWindow"
FLAG="--userflags ApplyBtagSF,use_beff_dasym,JETPUID_L,chi2kincut"
YEAR=2017
MAXJOB=" --nmax 120 "
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_dasym_JETPUID_L_chi2kincut_logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l  inputlist_major.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_dasym_JETPUID_L_chi2kincut_logs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_minor.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_dasym_JETPUID_L_chi2kincut_logs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_dasym_JETPUID_L_chi2kincut_logs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_dasym_JETPUID_L_chi2kincut_logs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleElectron -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_dasym_JETPUID_L_chi2kincut_logs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_dasym_JETPUID_L_chi2kincut_logs/NoSkim.log&
