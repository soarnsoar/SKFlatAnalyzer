#EEMu_MuMuE_Method
mkdir -p logs/
#SKIM="--skim SkimTree_Dilepton"
SKIM=""
FLAG=""
#FLAG="--userflags runSys"
#FLAG="--userflags simple_lepscale,runSys"
FLAG="--userflags cut_v2405.1"
#REDUCTION="--reduction 1000"
#YEAR=2018
ARR_YEAR=(2017 2016a 2016b 2018)
for YEAR in ${ARR_YEAR[@]};do

    SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToMuMu_MiNNLO $SKIM -e ${YEAR} -n 50 $FLAG &> logs/DYNNLO_MuMu_${YEAR}.log&
    sleep 10
    SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToEE_MiNNLO $SKIM -e ${YEAR} -n 50 $FLAG &> logs/DYNNLO_EE_${YEAR}.log&
    sleep 10


done

for YEAR in ${ARR_YEAR[@]};do
    SKFlat.py -a EEMu_MuMuE_Method -i DYJets $SKIM -e ${YEAR} -n 50 $FLAG &> logs/DYNLO_${YEAR}.log&
    sleep 60
    SKFlat.py -a EEMu_MuMuE_Method -i DYJets_MG $SKIM -e ${YEAR} -n 50 $FLAG &> logs/DYMG_${YEAR}.log&
    sleep 60

done
