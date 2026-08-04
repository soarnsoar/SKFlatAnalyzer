#TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING
mkdir -p ApplyBtagSF_use_beff_noveto_newlepveto_JETPUID_L_chi2kincut_logs/

SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags ApplyBtagSF,use_beff,noveto,newlepveto,JETPUID_L,chi2kincut"
#FLAG=""
YEAR=2018
MAXJOB=" --nmax 400 "
MEM="--memory 3199"
C="--count 1"
MEM2="--memory 3199"

SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i TTLJ_powheg -n 250 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C} &> ApplyBtagSF_use_beff_noveto_newlepveto_JETPUID_L_chi2kincut_logs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l  inputlist_major.txt -n 40 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C}  &> ApplyBtagSF_use_beff_noveto_newlepveto_JETPUID_L_chi2kincut_logs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_minor.txt -n 40 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C}  &> ApplyBtagSF_use_beff_noveto_newlepveto_JETPUID_L_chi2kincut_logs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_tW.txt -n 20 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C}  &> ApplyBtagSF_use_beff_noveto_newlepveto_JETPUID_L_chi2kincut_logs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB ${MEM2} &> ApplyBtagSF_use_beff_noveto_newlepveto_JETPUID_L_chi2kincut_logs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i EGamma -n 20 -e ${YEAR} $FLAG $MAXJOB ${MEM2} &> ApplyBtagSF_use_beff_noveto_newlepveto_JETPUID_L_chi2kincut_logs/EGamma.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG $MAXJOB ${MEM2} &> ApplyBtagSF_use_beff_noveto_newlepveto_JETPUID_L_chi2kincut_logs/NoSkim.log&

