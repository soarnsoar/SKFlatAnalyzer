#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep err
#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep Err

#grep -r "err" 201*/ApplyBtagSF_use_beff_JETPUID_L_chi2kincut_syslogs/*.log|grep -v HT|grep ERR

logdir=*logs
#logdir=jetpuid_loose_use_beffasym_newlepveto_bdt2608.2_bdtcut_apply_chargeid_eff_corr_apply_chargeid_acc_corr_syslogs
grep -r "err" 201*/${logdir}/*.log|grep -v HT|grep err
grep -r "err" 201*/${logdir}/*.log|grep -v HT|grep Err

grep -r "err" 201*/${logdir}/*.log|grep -v HT|grep ERR
