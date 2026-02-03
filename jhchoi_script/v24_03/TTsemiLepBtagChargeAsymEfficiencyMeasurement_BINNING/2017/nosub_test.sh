SKIM=""
FLAG=""

#FLAG="--userflags ApplyBtagSF,use_beff_dasym,runSys"
#FLAG="--userflags ApplyBtagSF,use_beff"
#FLAG="--userflags ApplyBtagSF"
#FLAG="--userflags runSys,ApplyBtagSF,use_beff"
#FLAG="--userflags ApplyBtagSF,use_beff"
FLAG="--userflags runSys,ApplyBtagSF,use_beff,JETPUID_L,chi2kincut,RunBasicObjectOnly"

REDUCTION="--reduction 5000"
#REDUCTION=""
#njob=150
SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -i TTLJ_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -i TTLL_powheg $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch -i SingleMuon $SKIM -n 1 --no_exec ${REDUCTION} $FLAG

#SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -i SingleTop_tW_antitop_NoFullyHad $SKIM -n 1 --no_exec ${REDUCTION} $FLAG
#SKFlat.py -a TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING -i QCD_bEnriched_HT700to1000 $SKIM -n 10 --no_exec ${REDUCTION} $FLAG


