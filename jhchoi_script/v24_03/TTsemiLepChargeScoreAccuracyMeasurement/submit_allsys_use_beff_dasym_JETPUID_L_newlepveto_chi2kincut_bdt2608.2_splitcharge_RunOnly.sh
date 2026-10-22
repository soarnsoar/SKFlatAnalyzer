ARR_ID=(
    muH
    muL
    eH
    eL
    jH
    jOthers
)


ARR_DIR=(2017 2016a 2016b 2018)
for ID in ${ARR_ID[@]};do
    for D in ${ARR_DIR[@]};do
	echo ${D}
	cd ${D}
	source batch_submit_allsys_use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge.sh
	sleep 60
	cd -
    done
done
