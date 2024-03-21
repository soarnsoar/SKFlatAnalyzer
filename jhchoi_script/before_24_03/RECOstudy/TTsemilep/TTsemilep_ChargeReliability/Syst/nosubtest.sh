#TTsemilep_ChargeReliability
ARR_OPTION_CHANNEL=(
    "RunSoftMuon"
    #"RunSoftElectron"
    #"RunJet"
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
	    SKFlat.py -a TTsemilep_ChargeReliability -i TTLJ_powheg -n 1 -e 2017 --no_exec  --reduction 10000 --userflags "RunSyst,${OPT_TOTAL}" $REDUCTION #  &> ttlj/${MYLOGNAME}.log&
	    
	    sleep 10000s
	done
    done
done
