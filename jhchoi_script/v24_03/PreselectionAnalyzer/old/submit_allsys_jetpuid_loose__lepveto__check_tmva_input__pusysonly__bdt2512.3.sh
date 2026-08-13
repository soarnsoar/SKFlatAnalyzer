ARR_DIR=(2016a 2016b 2017 2018)
#ARR_DIR=(2016a 2016b 2018)
for D in ${ARR_DIR[@]};do
    echo ${D}
    cd ${D}
    source batch_submit_allsys_jetpuid_loose__lepveto__check_tmva_input__pusysonly__bdt2512.3.sh
    sleep 60
    cd -
done
