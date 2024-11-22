#Preselection_To_bjet
mkdir -p btag_logs/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags measure_btageff"
YEAR=2018
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG &> btag_logs/major.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG &> btag_logs/minor.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG &> btag_logs/tW.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG &> btag_logs/DoubleMuon.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG &> btag_logs/EGamma.log&
SKFlat.py -a Preselection_To_bjet -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG &> btag_logs/NoSkim.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG &> btag_logs/VV.log&

