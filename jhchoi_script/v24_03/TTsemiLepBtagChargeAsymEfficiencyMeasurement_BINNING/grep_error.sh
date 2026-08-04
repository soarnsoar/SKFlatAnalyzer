#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep err
#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep Err

#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep ERR

suffix=ApplyBtagSF_use_beff_noveto_newlepveto_JETPUID_L_chi2kincut_syslogs
grep -r "err" 201*/$suffix/*.log|grep -v HT|grep err
grep -r "err" 201*/$suffix/*.log|grep -v HT|grep Err

grep -r "err" 201*/$suffix/*.log|grep -v HT|grep ERR
