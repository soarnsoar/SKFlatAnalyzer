#TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING
mkdir -p logs/
mkdir -p ApplyBtagSF_use_beff_noveto_JETPUID_L_chi2kincut_syslogs/
#SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys,ApplyBtagSF,use_beff,noveto,JETPUID_L,chi2kincut"
#FLAG=""
YEAR=2017
MAXJOB=" --nmax 400 "

MEM_TT="--memory 6400" ##weight=3 -> 120
C_TT="--count 2"
MEM_DY="--memory 6300" ## weight=2 -> 20
C_DY="--count 2"
MEM_tW="--memory 6300"
C_tW="--count 2"
MEM_ST="--memory 6300"
C_ST="--count 2"

MEM="--memory 6399"
C="--count 2"

MEM2="--memory 3199"
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i TTLJ_powheg -n 200 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C} &> ApplyBtagSF_use_beff_noveto_JETPUID_L_chi2kincut_syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C} &> ApplyBtagSF_use_beff_noveto_JETPUID_L_chi2kincut_syslogs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C} &> ApplyBtagSF_use_beff_noveto_JETPUID_L_chi2kincut_syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_tW.txt -n 20 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C} &> ApplyBtagSF_use_beff_noveto_JETPUID_L_chi2kincut_syslogs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB ${MEM2} &> ApplyBtagSF_use_beff_noveto_JETPUID_L_chi2kincut_syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleElectron -n 20 -e ${YEAR} $FLAG $MAXJOB ${MEM2} &> ApplyBtagSF_use_beff_noveto_JETPUID_L_chi2kincut_syslogs/SingleElectron.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG $MAXJOB ${MEM2} &> ApplyBtagSF_use_beff_noveto_JETPUID_L_chi2kincut_syslogs/NoSkim.log&
