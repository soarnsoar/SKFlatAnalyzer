#Preselection_To_bjet
mkdir -p use_beff_syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,use_beff"
MEMOERY="--memory 10000"


YEAR=2016b
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_syslogs/major.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_syslogs/minor.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_syslogs/tW.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_syslogs/DoubleMuon.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_syslogs/DoubleEG.log&
SKFlat.py -a Preselection_To_bjet -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_syslogs/NoSkim.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${MEMOERY} &> use_beff_syslogs/VV.log&
