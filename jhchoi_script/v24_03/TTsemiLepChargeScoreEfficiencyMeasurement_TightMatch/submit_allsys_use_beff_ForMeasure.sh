#ARR_DIR=(2016a 2016b 2017 2018)
ARR_DIR=(2017 2016a 2016b 2018)
for D in ${ARR_DIR[@]};do
    echo ${D}
    cd ${D}
    source batch_submit_allsys_use_beff_ForMeasure.sh
    #sleep 60
    cd -
done
grep -r "RR" 201*/syslogs/*.log
grep -r "rr" 201*/syslogs/*.log
