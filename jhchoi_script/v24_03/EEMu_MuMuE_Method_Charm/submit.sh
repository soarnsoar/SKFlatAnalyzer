#EEMu_MuMuE_Method_Charm
mkdir -p logs/
#SKIM="--skim SkimTree_Dilepton"
SKIM=""
FLAG=""
#FLAG="--userflags runSys"
#FLAG="--userflags simple_lepscale,runSys"
FLAG="--userflags cut_v2608.2,treemode"

#REDUCTION="--reduction 1000"
#YEAR=2018
ARR_YEAR=(2017 2016a 2016b 2018)
NMAX=" --nmax 400 "
njob_mm=" -n 10 "
njob_ee=" -n 15 "
#--count 2 "
for YEAR in ${ARR_YEAR[@]};do

    SKFlat.py -a EEMu_MuMuE_Method_Charm -i DYJetsToMuMu_MiNNLO --count 4 $NMAX $SKIM -e ${YEAR} $njob_mm $FLAG &> logs/DYNNLO_MuMu_${YEAR}.log&
    sleep 5
    SKFlat.py -a EEMu_MuMuE_Method_Charm -i DYJetsToEE_MiNNLO --count 4  $NMAX $SKIM -e ${YEAR} $njob_ee $FLAG &> logs/DYNNLO_EE_${YEAR}.log&
    sleep 5


done
njob=" -n 20 "

for YEAR in ${ARR_YEAR[@]};do
    SKFlat.py -a EEMu_MuMuE_Method_Charm -i DYJets --count 4  $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYNLO_${YEAR}.log&
    sleep 5
    SKFlat.py -a EEMu_MuMuE_Method_Charm -i DYJets_MG --count 4  $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYMG_${YEAR}.log&
    sleep 5

done
