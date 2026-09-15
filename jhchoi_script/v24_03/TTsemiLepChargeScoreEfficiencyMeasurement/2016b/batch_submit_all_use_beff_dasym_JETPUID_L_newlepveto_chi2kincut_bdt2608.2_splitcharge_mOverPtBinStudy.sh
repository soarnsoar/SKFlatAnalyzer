#TTsemiLepChargeScoreEfficiencyMeasurement
mkdir -p _use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge_mOverPtBinStudy_logs/


#SKIM="--skim SkimTree_SingleLepton"
#SKIM=""
SKIM="--skim SkimTree_SingleLepton_1DeepJetTightWP"


FLAG="--userflags use_beff_dasym,JETPUID_L,newlepveto,chi2kincut,bdt2608.2,splitcharge,mOverPtBinStudy"


MAXJOB=" --nmax 800 "



MEM_TT="--memory 6400" ##weight=3 -> 120
C_TT="--count 3"
MEM_DY="--memory 6300" ## weight=2 -> 20
C_DY="--count 3"
MEM_tW="--memory 6300"
C_tW="--count 3"
MEM_ST="--memory 6300"
C_ST="--count 3"

YEAR=2016b

##---No specific memory setup
MEM="--memory 3200 --count 2"

SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement ${SKIM}   -i SingleMuon -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> _use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge_mOverPtBinStudy_logs/SingleMuon.log&
sleep 15
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement ${SKIM}   -i SingleElectron -n 20 -e ${YEAR} $FLAG ${MAXJOB} ${MEM} &> _use_beff_dasym_JETPUID_L_newlepveto_chi2kincut_bdt2608.2_splitcharge_mOverPtBinStudy_logs/SingleElectron.log&
sleep 15


