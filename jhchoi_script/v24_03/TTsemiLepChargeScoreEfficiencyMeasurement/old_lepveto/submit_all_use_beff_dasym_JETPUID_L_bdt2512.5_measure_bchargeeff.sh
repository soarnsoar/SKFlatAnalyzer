ARR_DIR=(2017 2016a 2016b 2018)
for D in ${ARR_DIR[@]};do
    echo ${D}
    cd ${D}
    source batch_submit_all_use_beff_dasym_JETPUID_L_bdt2512.5_measure_bchargeeff.sh
    sleep 60
    cd -
done
