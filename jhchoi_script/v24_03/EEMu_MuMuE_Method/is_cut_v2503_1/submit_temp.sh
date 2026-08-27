#EEMu_MuMuE_Method
mkdir -p logs/
#SKIM="--skim SkimTree_Dilepton"
SKIM=""
FLAG=""
#FLAG="--userflags runSys"
#FLAG="--userflags simple_lepscale,runSys"
FLAG="--userflags cut_v2503.1,treemode"

#REDUCTION="--reduction 1000"
#YEAR=2018
ARR_YEAR=(2016b)
NMAX=" --nmax 401 "
njob_mm=" -n 100 "
njob_ee=" -n 100 "
#--count 2 "
for YEAR in ${ARR_YEAR[@]};do

    #SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToMuMu_MiNNLO --count 4 $NMAX $SKIM -e ${YEAR} $njob_mm $FLAG &> logs/DYNNLO_MuMu_${YEAR}.log&
    #sleep 5
    SKFlat.py -a EEMu_MuMuE_Method -i DYJetsToEE_MiNNLO --count 4  $NMAX $SKIM -e ${YEAR} $njob_ee $FLAG &> logs/DYNNLO_EE_${YEAR}.log&
    #sleep 5


done
njob=" -n 20 "

for YEAR in ${ARR_YEAR[@]};do
    continue
    SKFlat.py -a EEMu_MuMuE_Method -i DYJets --count 4  $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYNLO_${YEAR}.log&
    sleep 5
    SKFlat.py -a EEMu_MuMuE_Method -i DYJets_MG --count 4  $NMAX $SKIM -e ${YEAR} $njob $FLAG &> logs/DYMG_${YEAR}.log&
    sleep 5

done
