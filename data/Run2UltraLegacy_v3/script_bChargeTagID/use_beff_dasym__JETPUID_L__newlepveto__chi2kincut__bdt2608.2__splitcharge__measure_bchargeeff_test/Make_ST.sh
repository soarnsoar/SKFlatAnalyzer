##eff_hist
ARR_YEAR=(
2016preVFP 2016postVFP 2017 2018
)
for YEAR in ${ARR_YEAR[@]};do
    hadd -f eff_hists${YEAR}/TTsemiLepChargeScoreEfficiencyMeasurement_ST_antitop.root eff_hists${YEAR}/TTsemiLepChargeScoreEfficiencyMeasurement_SingleTop_tch_antitop_Incl.root eff_hists${YEAR}//TTsemiLepChargeScoreEfficiencyMeasurement_SingleTop_tW_antitop_NoFullyHad.root


    hadd -f eff_hists${YEAR}/TTsemiLepChargeScoreEfficiencyMeasurement_ST_top.root eff_hists${YEAR}/TTsemiLepChargeScoreEfficiencyMeasurement_SingleTop_tch_top_Incl.root eff_hists${YEAR}//TTsemiLepChargeScoreEfficiencyMeasurement_SingleTop_tW_top_NoFullyHad.root
done
