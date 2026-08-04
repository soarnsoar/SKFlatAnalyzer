#TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING
mkdir -p ApplyBtagSF_use_beff_JETPUID_L_syslogs/
mkdir -p syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys,ApplyBtagSF,use_beff,JETPUID_L"
#FLAG=""
YEAR=2018
MAXJOB=" --nmax 400 "
MEM="--memory 6400"
C="--count 2"

SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i TTLJ_powheg -n 250 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C} &> ApplyBtagSF_use_beff_JETPUID_L_syslogs/TTLJ_powheg.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l  inputlist_major.txt -n 40 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C}  &> ApplyBtagSF_use_beff_JETPUID_L_syslogs/major.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_minor.txt -n 40 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C}  &> ApplyBtagSF_use_beff_JETPUID_L_syslogs/minor.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -l inputlist_tW.txt -n 20 -e ${YEAR} $FLAG $MAXJOB ${MEM} ${C}  &> ApplyBtagSF_use_beff_JETPUID_L_syslogs/tW.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i SingleMuon -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_syslogs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING  ${SKIM} -i EGamma -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_syslogs/EGamma.log&
sleep 15
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -l inputlist_NoSkim.txt -n 20 -e ${YEAR} $FLAG $MAXJOB &> ApplyBtagSF_use_beff_JETPUID_L_syslogs/NoSkim.log&

