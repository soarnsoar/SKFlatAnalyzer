#ARR_DIR=(2016a 2016b 2017 2018)
ARR_DIR=(2016b 2017 2018)
#ARR_DIR=(2016a 2016b 2018)
for D in ${ARR_DIR[@]};do
    echo ${D}
    cd ${D}
    source batch_submit_allsys_jetpuid_loose__newlepveto__check_tmva_input__1bskim.sh
    #source batch_submit_allsys_jetpuid_loose__newlepveto__check_tmva_input__.sh
    sleep 60
    cd -
done
