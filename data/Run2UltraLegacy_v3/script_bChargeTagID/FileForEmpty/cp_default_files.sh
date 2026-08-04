#/data6/Users/jhchoi/SKFlatOutput/Run2UltraLegacy_v3/TTsemiLepChargeScoreEfficiencyMeasurement/2017/use_beff_dasym__JETPUID_L__bdt2512.5__measure_bchargeeff__
#PreselectionToBDTRegionAnalyzer
ANA=TTsemiLepChargeScoreEfficiencyMeasurement
SUFFIX=use_beff_dasym__JETPUID_L__bdt2512.5__measure_bchargeeff__
YEARS=(2016preVFP 2016postVFP 2017 2018)
for YEAR in ${YEARS[@]};do
    mkdir -p ${YEAR}
    cp /data6/Users/jhchoi/SKFlatOutput/Run2UltraLegacy_v3/$ANA/${YEAR}/$SUFFIX/*TTLJ*.root ${YEAR}/
    cp /data6/Users/jhchoi/SKFlatOutput/Run2UltraLegacy_v3/$ANA/${YEAR}/$SUFFIX/*TTLL*.root ${YEAR}/
    rm ${YEAR}/hadd_TTLJ_TTLL.root
    hadd -f ${YEAR}/hadd_TTLJ_TTLL.root ${YEAR}/*.root
done
