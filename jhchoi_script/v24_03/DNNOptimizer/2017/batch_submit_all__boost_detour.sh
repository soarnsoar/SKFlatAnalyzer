#DNNOptimizer
mkdir -p boost_detour__logs/

SKIM="--skim SkimTree_Dilepton"
#FLAG="--userflags runSys"
FLAG="--userflags boost_detour"
NMAX="--nmax 120"
SKFlat.py -a DNNOptimizer  ${SKIM} -l  inputlist_major.txt -n 30 -e 2017 $FLAG $NMAX &> boost_detour__logs/major.log&
sleep 3
SKFlat.py -a DNNOptimizer -l inputlist_NoSkim.txt -n 10 -e 2017 $FLAG $NMAX &> boost_detour__logs/NoSkim.log&
sleep 3
SKFlat.py -a DNNOptimizer  ${SKIM} -l inputlist_minor.txt -n 30 -e 2017 $FLAG $NMAX &> boost_detour__logs/minor.log&
SKFlat.py -a DNNOptimizer  ${SKIM} -l inputlist_tW.txt -n 10 -e 2017 $FLAG $NMAX &> boost_detour__logs/tW.log&
SKFlat.py -a DNNOptimizer  ${SKIM} -i DoubleMuon -n 10 -e 2017 $FLAG $NMAX &> boost_detour__logs/DoubleMuon.log&
SKFlat.py -a DNNOptimizer  ${SKIM} -i DoubleEG -n 10 -e 2017 $FLAG $NMAX &> boost_detour__logs/DoubleEG.log&

SKFlat.py -a DNNOptimizer  ${SKIM} -l  inputlist_VV.txt -n 10 -e 2017 $FLAG $NMAX &> boost_detour__logs/VV.log&

