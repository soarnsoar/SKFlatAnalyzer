#Preselection_To_bjet
mkdir -p use_beff_apply_bchargeeff_syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,use_beff,apply_bchargeeff"
#FLAG=""
MEMOERY="--memory 10000"
NMAX="--nmax 500"

SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_major.txt -n 40 -e 2017 $FLAG ${MEMOERY} ${NMAX} &> use_beff_apply_bchargeeff_syslogs/major.log&
sleep 120
SKFlat.py -a Preselection_To_bjet -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${MEMOERY} ${NMAX} &> use_beff_apply_bchargeeff_syslogs/NoSkim.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${MEMOERY} ${NMAX} &> use_beff_apply_bchargeeff_syslogs/minor.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${MEMOERY} ${NMAX} &> use_beff_apply_bchargeeff_syslogs/tW.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${MEMOERY} ${NMAX} &> use_beff_apply_bchargeeff_syslogs/DoubleMuon.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${MEMOERY} ${NMAX} &> use_beff_apply_bchargeeff_syslogs/DoubleEG.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${MEMOERY} ${NMAX} &> use_beff_apply_bchargeeff_syslogs/VV.log&
sleep 5
