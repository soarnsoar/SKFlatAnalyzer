#CheckHaddJobs.py
suffix=jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs
arr_log=(201*/$suffix/*.log)

for log in ${arr_log[@]};do
    echo "-----${log}----"
    python3 CheckHaddJobs.py ${log}
done
