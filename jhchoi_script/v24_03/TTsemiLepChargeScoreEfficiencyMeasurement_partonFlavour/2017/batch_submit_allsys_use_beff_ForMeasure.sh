mkdir -p logs/
mkdir -p syslogs/
mkdir -p use_beff_ForMeasure_syslogs/
SKIM="--skim SkimTree_SingleLepton"
SKIM=""
FLAG="--userflags runSys,use_beff,ForMeasure"
MEMORY="--memory 10000"
MEMORYHIGH="--memory 22000"
NMAX="--nmax 900"
YEAR=2017
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i TTLJ_powheg -n 400 -e ${YEAR} $FLAG ${MEMORYHIGH} ${NMAX} &> use_beff_ForMeasure_syslogs/TTLJ_powheg.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} ${NMAX} &> use_beff_ForMeasure_syslogs/major.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} ${NMAX} &> use_beff_ForMeasure_syslogs/minor.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} ${NMAX} &> use_beff_ForMeasure_syslogs/tW.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i SingleMuon -n 50 -e ${YEAR} $FLAG ${MEMORY} ${NMAX} &> use_beff_ForMeasure_syslogs/SingleMuon.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour  ${SKIM} -i SingleElectron -n 50 -e ${YEAR} $FLAG ${MEMORY} ${NMAX} &> use_beff_ForMeasure_syslogs/SingleElectron.log&
SKFlat.py -a TTsemiLepChargeScoreEfficiencyMeasurement_partonFlavour -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${MEMORY} ${NMAX} &> use_beff_ForMeasure_syslogs/NoSkim.log&

