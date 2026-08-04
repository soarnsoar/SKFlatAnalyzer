ARR_DIR=(2017 2016a 2016b 2018)
#ARR_DIR=(2017 2016b 2018)
#ARR_DIR=(2016a 2016b 2018)
#ARR_DIR=(2016a 2016b 2017)
for D in ${ARR_DIR[@]};do
    echo ${D}
    cd ${D}
    source batch_submit_all_ApplyBtagSF_use_beff.sh
    sleep 60
    cd -
done
