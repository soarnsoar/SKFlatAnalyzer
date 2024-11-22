#Preselection_To_bjet
mkdir -p use_beff_MuonOnly_syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys,use_beff,MuonOnly"
#FLAG=""
MEMOERY="--memory 10000"


SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_major.txt -n 40 -e 2017 $FLAG ${MEMOERY} &> use_beff_MuonOnly_syslogs/major.log&
sleep 120
SKFlat.py -a Preselection_To_bjet -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG ${MEMOERY} &> use_beff_MuonOnly_syslogs/NoSkim.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG ${MEMOERY} &> use_beff_MuonOnly_syslogs/minor.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG ${MEMOERY} &> use_beff_MuonOnly_syslogs/tW.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG ${MEMOERY} &> use_beff_MuonOnly_syslogs/DoubleMuon.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG ${MEMOERY} &> use_beff_MuonOnly_syslogs/DoubleEG.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG ${MEMOERY} &> use_beff_MuonOnly_syslogs/VV.log&
sleep 5
