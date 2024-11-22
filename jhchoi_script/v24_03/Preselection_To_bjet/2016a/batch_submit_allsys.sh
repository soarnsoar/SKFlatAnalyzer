#Preselection_To_bjet
mkdir -p syslogs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags runSys"
#FLAG=""
YEAR=2016a
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_major.txt -n 30 -e ${YEAR} $FLAG &> syslogs/major.log&
sleep 120
SKFlat.py -a Preselection_To_bjet -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> syslogs/NoSkim.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> syslogs/minor.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG &> syslogs/tW.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG &> syslogs/DoubleMuon.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleEG -n 50 -e ${YEAR} $FLAG &> syslogs/DoubleEG.log&
sleep 5
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG &> syslogs/VV.log&

