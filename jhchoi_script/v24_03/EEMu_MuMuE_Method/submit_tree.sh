#EEMu_MuMuE_Method
mkdir -p tree_logs/
#SKIM="--skim SkimTree_Dilepton"
SKIM=""
FLAG=""
#FLAG="--userflags runSys"
#FLAG="--userflags simple_lepscale,runSys"
#FLAG="--userflags cut_v2405.3,treemode"
#FLAG="--userflags treemode"
FLAG="--userflags treemode,cut_v2503.2"
#REDUCTION="--reduction 1000"
#YEAR=2018
ARR_YEAR=(2017 2016a 2016b 2018)
#ARR_YEAR=(2017)
NMAX=" --nmax 120 "
njob=" -n 6 "
for YEAR in ${ARR_YEAR[@]};do
    SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToMuMu_MiNNLO $SKIM -e ${YEAR} $njob $FLAG $NMAX &> tree_logs/DYNNLO_MuMu_${YEAR}.log&
    sleep 10
    SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToEE_MiNNLO $SKIM -e ${YEAR} $njob $FLAG $NMAX &> tree_logs/DYNNLO_EE_${YEAR}.log&
    sleep 10
done

for YEAR in ${ARR_YEAR[@]};do
    SKFlat.py -a EEMu_MuMuE_Method -i DYJets $SKIM -e ${YEAR} $njob $FLAG $NMAX &> tree_logs/DYNLO_${YEAR}.log&
    sleep 10
    SKFlat.py -a EEMu_MuMuE_Method -i DYJets_MG $SKIM -e ${YEAR} $njob $FLAG $NMAX &> tree_logs/DYMG_${YEAR}.log&
    sleep 10

done
