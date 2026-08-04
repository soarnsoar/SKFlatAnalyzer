#/data6/Users/jhchoi/SKFlatOutput//Run2UltraLegacy_v3/TTsemiLepChargeScoreAccuracyMeasurement/2017/use_beff_dasym__JETPUID_L__chi2kincut__bdt2512.5__splitcharge__noetabin__measure_bchargeacc__

YEARS=(2016preVFP 2016postVFP 2017 2018)
for YEAR in ${YEARS[@]};do
    mkdir -p ${YEAR}

    
    cp ${YEAR}/hadd_TTLJ_TTLL.root ../../${YEAR}/bChargeAcc/
done
