

#ARR_DIR=(2016a 2016b)
#ARR_DIR=(2016a 2016b)
ARR_DIR=(2017 2018)


for D in ${ARR_DIR[@]};do
    echo ${D}
    cd ${D}
    source batch_submit_allsys_use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge_muLeLOnly.sh
    sleep 60
    cd -
done

