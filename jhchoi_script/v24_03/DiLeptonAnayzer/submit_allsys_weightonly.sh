ARR_DIR=(2016a 2016b 2017 2018)
for D in ${ARR_DIR[@]};do
    echo ${D}
    cd ${D}
    source batch_submit_allsys_weightonly.sh&
    #sleep 60
    cd -
done
#grep -r "RR" 201*/wsyslogs/*.log
#grep -r "rr" 201*/wsyslogs/*.log
