#Preselection_To_bjet
mkdir -p btag_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags measure_btageff"
#FLAG=""

SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG &> btag_logs/major.log&
sleep 3
SKFlat.py -a Preselection_To_bjet -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG &> btag_logs/NoSkim.log&
sleep 3
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG &> btag_logs/minor.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG &> btag_logs/tW.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG &> btag_logs/DoubleMuon.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG &> btag_logs/DoubleEG.log&

SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG &> btag_logs/VV.log&

#SKFlat.py -a Preselection_To_bjet  ${SKIM} -i TTJJ_powheg -n 50 -e 2017 $FLAG &> btag_logs/TTJJ_powheg.log&
