#TTsemilep_ChargeReliability
ARR_OPTION_CHANNEL=(
    "RunSoftMuon"
    "RunSoftElectron"
    "RunJet"
)
ARR_OPTION_BJET=(
    #"RunHadronSide"
    "RunLeptonSide"
)
ARR_OPTION_MEASURE=(
    "RunReliab"
    #"RunChAcc"
)
#REDUCTION="--reduction 1000"
REDUCTION=""
#--skim SkimTree_SingleLepton
for opt1 in ${ARR_OPTION_CHANNEL[@]};do
 
    for opt2 in ${ARR_OPTION_BJET[@]};do
	for opt3 in ${ARR_OPTION_MEASURE[@]};do
	    OPT_TOTAL="${opt1},${opt2},${opt3}"
	    MYLOGNAME="${opt1}__${opt2}__${opt3}"
	    
	    echo ${OPT_TOTAL}
	    mkdir -p major minor qcd tW muon electron ttlj
	    SKFlat.py -a TTsemilep_ChargeReliability -i TTLJ_powheg -n 300 -e 2017 --userflags "RunSyst,${OPT_TOTAL}" $REDUCTION  &> ttlj/${MYLOGNAME}.log&
	    sleep 10s
	    SKFlat.py -a TTsemilep_ChargeReliability -l inputlist_major.txt -n 150 -e 2017 --userflags "RunSyst,${OPT_TOTAL}" $REDUCTION &> major/${MYLOGNAME}.log&
	    sleep 10s
	    SKFlat.py -a TTsemilep_ChargeReliability -l inputlist_minor.txt -n 100 -e 2017 --userflags "RunSyst,${OPT_TOTAL}" $REDUCTION &> minor/${MYLOGNAME}.log&
	    sleep 10s
	    SKFlat.py -a TTsemilep_ChargeReliability -l inputlist_QCD.txt -n 100 -e 2017 --userflags "RunSyst,${OPT_TOTAL}" $REDUCTION &> qcd/${MYLOGNAME}.log&
	    sleep 10s
	    SKFlat.py -a TTsemilep_ChargeReliability -l inputlist_tW.txt -n 100 -e 2017 --userflags "RunSyst,${OPT_TOTAL}" $REDUCTION &> tW/${MYLOGNAME}.log&
	    sleep 10s
	    SKFlat.py -a TTsemilep_ChargeReliability -i SingleMuon -n 50 -e 2017 --userflags "RunSyst,${OPT_TOTAL}" $REDUCTION &> muon/${MYLOGNAME}.log&
	    sleep 10s
	    SKFlat.py -a TTsemilep_ChargeReliability -i SingleElectron -n 50 -e 2017 --userflags "RunSyst,${OPT_TOTAL}" $REDUCTION &> electron/${MYLOGNAME}.log&

	done
    done
done
