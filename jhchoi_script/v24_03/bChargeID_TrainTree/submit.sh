mkdir -p logs/
SKIM="--skim SkimTree_Dilepton"
#SKIM=""
FLAG=""
#FLAG="--userflags runSys"
#FLAG="--userflags simple_lepscale,runSys"
#FLAG="--userflags checksf"
#REDUCTION="--reduction 1000"
#YEAR=2018
ARR_YEAR=(2016a 2016b 2017 2018)
for YEAR in ${ARR_YEAR[@]};do
    SKFlat.py -a bChargeID_TrainTree -i DYJets $SKIM -e ${YEAR} -n 50 $FLAG &> logs/DYNLO_${YEAR}.log&
    sleep 60
    SKFlat.py -a bChargeID_TrainTree -i DYJets_MG $SKIM -e ${YEAR} -n 50 $FLAG &> logs/DYMG_${YEAR}.log&
    sleep 60
done


