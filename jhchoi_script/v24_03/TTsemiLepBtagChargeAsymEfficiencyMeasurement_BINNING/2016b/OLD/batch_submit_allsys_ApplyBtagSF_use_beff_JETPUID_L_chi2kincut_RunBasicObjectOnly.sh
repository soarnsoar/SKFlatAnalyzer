#TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING
mkdir -p ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_syslogs/
mkdir -p syslogs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys,ApplyBtagSF,use_beff,JETPUID_L,chi2kincut,RunBasicObjectOnly"
#FLAG=""
MAXJOB=" --nmax 300 "
YEAR=2016b
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i TTLJ_powheg -n 150 -e ${YEAR} $FLAG ${MAXJOB} &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l  inputlist_major.txt -n 40 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_syslogs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_minor.txt -n 40 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_tW.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_syslogs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING   -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING   -i SingleElectron -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_syslogs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_RunBasicObjectOnly_syslogs/NoSkim.log&

