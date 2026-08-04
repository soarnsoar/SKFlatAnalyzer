#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep err
#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep Err

#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep ERR

logdir=use_beff_dasym_JETPUID_L_chi2kincut_bdt2512.5_splitcharge_noetabin_syslogs
grep -r "err" 201*/${logdir}/*.log|grep -v HT|grep err
grep -r "err" 201*/${logdir}/*.log|grep -v HT|grep Err

grep -r "err" 201*/${logdir}/*.log|grep -v HT|grep ERR
