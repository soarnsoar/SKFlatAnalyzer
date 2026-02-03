#EEMu_MuMuE_Method
mkdir -p logs/
#SKIM="--skim SkimTree_Dilepton"
SKIM=""
FLAG=""
#FLAG="--userflags runSys"
#FLAG="--userflags simple_lepscale,runSys"
#FLAG="--userflags cut_v2405.1"

#REDUCTION="--reduction 1000"
#YEAR=2018
ARR_YEAR=(2017 2016a 2016b 2018)
ARR_YEAR=(2017)
NMAX=" --nmax 300 "
njob=" -n 50 "
for YEAR in ${ARR_YEAR[@]};do

    SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToMuMu_MiNNLO $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYNNLO_MuMu_${YEAR}.log&
    sleep 10
    SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToEE_MiNNLO $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYNNLO_EE_${YEAR}.log&
    sleep 10


done

for YEAR in ${ARR_YEAR[@]};do
    SKFlat.py -a EEMu_MuMuE_Method -i DYJets $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYNLO_${YEAR}.log&
    sleep 60
    SKFlat.py -a EEMu_MuMuE_Method -i DYJets_MG $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYMG_${YEAR}.log&
    sleep 60

done
