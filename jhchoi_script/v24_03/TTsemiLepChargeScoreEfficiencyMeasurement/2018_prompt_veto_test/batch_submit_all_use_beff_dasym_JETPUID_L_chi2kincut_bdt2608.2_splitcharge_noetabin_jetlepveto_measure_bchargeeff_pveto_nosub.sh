mkdir -p use_beff_dasym_JETPUID_L_chi2kincut_bdt2608.2_splitcharge_noetabin_jetlepveto_measure_bchargeeff_pveto_logs/

SKIM="--skim SkimTree_SingleLepton_1DeepJetTightWP"
FLAG="--userflags use_beff_dasym,JETPUID_L,chi2kincut,bdt2608.2,splitcharge,noetabin,jetlepveto,measure_bchargeeff_pveto"

MAXJOB=" --nmax 180 "


YEAR=2018
##--TT
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement --no_exec ${SKIM} -i TTLJ_powheg -n 140 -e ${YEAR} $FLAG $MAXJOB

