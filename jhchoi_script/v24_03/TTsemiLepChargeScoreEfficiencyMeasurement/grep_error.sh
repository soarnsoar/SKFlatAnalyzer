#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep err
#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep Err

#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep ERR

logdirs=(use_beff_dasym_JETPUID_L_noveto_newlepveto_noetabin_bdt2608.2_measure_bchargeeff_logs)
for logdir in ${logdirs[@]};do
    grep -r "rr" 201*/${logdir}/*.log|grep -v HT
done
