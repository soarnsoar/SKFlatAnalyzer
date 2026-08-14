#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep err
#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep Err

#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep ERR

logdirs=(jetpuid_loose_newlepveto_check_tmva_input_syslogs jetpuid_loose_newlepveto_kincutopt_logs)
for logdir in ${logdirs[@]};do
    grep -r "rr" 201*/${logdir}/*.log|grep -v HT
    grep -r "RR" 201*/${logdir}/*.log|grep -v HT
done
