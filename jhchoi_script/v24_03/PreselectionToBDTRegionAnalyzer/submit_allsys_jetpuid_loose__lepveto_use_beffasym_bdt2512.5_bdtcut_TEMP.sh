ARR_DIR=(2016a 2017 2018)
#ARR_DIR=(2016a 2016b 2018)
for D in ${ARR_DIR[@]};do
    echo ${D}
    cd ${D}
    source batch_submit_allsys_jetpuid_loose__lepveto__use_beffasym__bdt2512.5__bdtcut.sh
    sleep 60
    cd -
done
