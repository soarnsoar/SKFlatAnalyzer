#Preselection_To_bjet
mkdir -p use_beff_pfphicorrmet/

SKIM="--skim SkimTree_Dilepton"
FLAG="--userflags use_beff,pfmet,phicorrmet"
#FLAG=""

SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_major.txt -n 50 -e 2017 $FLAG &> use_beff_pfphicorrmet/major.log&
sleep 3
SKFlat.py -a Preselection_To_bjet -l inputlist_NoSkim.txt -n 50 -e 2017 $FLAG &> use_beff_pfphicorrmet/NoSkim.log&
sleep 3
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_minor.txt -n 50 -e 2017 $FLAG &> use_beff_pfphicorrmet/minor.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -l inputlist_tW.txt -n 50 -e 2017 $FLAG &> use_beff_pfphicorrmet/tW.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleMuon -n 50 -e 2017 $FLAG &> use_beff_pfphicorrmet/DoubleMuon.log&
SKFlat.py -a Preselection_To_bjet  ${SKIM} -i DoubleEG -n 50 -e 2017 $FLAG &> use_beff_pfphicorrmet/DoubleEG.log&

SKFlat.py -a Preselection_To_bjet  ${SKIM} -l  inputlist_VV.txt -n 50 -e 2017 $FLAG &> use_beff_pfphicorrmet/VV.log&

#SKFlat.py -a Preselection_To_bjet  ${SKIM} -i TTJJ_powheg -n 50 -e 2017 $FLAG &> use_beff_pfphicorrmet/TTJJ_powheg.log&
