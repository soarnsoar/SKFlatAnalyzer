SKIM=""
FLAG=""

FLAG="--userflags ApplyBtagSF,use_beff_dasym,runSys,scale00test"
#FLAG="--userflags ApplyBtagSF,use_beff_dasym,runSys,scale00test"
#FLAG="--userflags ApplyBtagSF"

#REDUCTION="--reduction 20000"
REDUCTION=""
#SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -i SingleMuon $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -i SingleTop_tW_antitop_NoFullyHad $SKIM -n 300  ${REDUCTION} $FLAG &> scale00_test_logs/SingleTop_tW_antitop_NoFullyHad.log&

#SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -i SingleTop_tW_antitop_NoFullyHad $SKIM -n 300  ${REDUCTION} $FLAG --no_exec
#SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -i QCD_bEnriched_HT700to1000 $SKIM -n 10 --no_exec ${REDUCTION} $FLAG


