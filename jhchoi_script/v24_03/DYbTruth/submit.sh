mkdir -p logs/

SKIM=""
FLAG=""

#ARR_YEAR=(2017 2016a 2016b 2018)
ARR_YEAR=(2017)
#ARR_YEAR=(2016a 2016b 2018)
NMAX=" --nmax 60 "
njob=" -n 30 "
for YEAR in ${ARR_YEAR[@]};do

    SKFlat.py -a DYbTruth -i DYJetsToMuMu_MiNNLO $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYNNLO_MuMu_${YEAR}.log&
    sleep 10
    SKFlat.py -a DYbTruth -i DYJetsToEE_MiNNLO $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYNNLO_EE_${YEAR}.log&
    sleep 10


done

for YEAR in ${ARR_YEAR[@]};do
    continue
    SKFlat.py -a DYbTruth -i DYJets $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYNLO_${YEAR}.log&
    sleep 60
    SKFlat.py -a DYbTruth -i DYJets_MG $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYMG_${YEAR}.log&
    sleep 60

done
