ARR_DIR=(2016a 2016b 2017 2018)
#ARR_DIR=(2016a 2016b 2018)
for D in ${ARR_DIR[@]};do
    echo ${D}
    cd ${D}
    source batch_submit_all_jetpuid_loose__newlepveto__use_beffasym__bdt_v2608_2__bdtopt.sh
    sleep 60
    cd -
done
