#TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING
mkdir -p ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_logs/
mkdir -p syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
#FLAG="--userflags TopMassWindow"
#FLAG=""
FLAG="--userflags ApplyBtagSF,use_beff,JETPUID_L,chi2kincut,RunBasicObjectOnly"
YEAR=2018
MAXJOB=" --nmax 120 "
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i TTLJ_powheg -n 50 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l  inputlist_major.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_logs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_minor.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_logs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_tW.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_logs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_logs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i EGamma -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_logs/EGamma.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -l inputlist_NoSkim.txt -n 10 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_logs/NoSkim.log&

