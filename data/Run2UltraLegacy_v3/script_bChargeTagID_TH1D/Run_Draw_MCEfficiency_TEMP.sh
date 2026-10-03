ARR_YEAR=(
    2016preVFP
    #2016postVFP
    #2017
    #2018
)

ARR_ID=(
    muH
    #muL
    #eH
    #eL
)

#    ana=sys.argv[1]
#    year=sys.argv[2]
#    ID=sys.argv[3]
#    ListToDrawStr=sys.argv[4]

ana='TTsemiLepChargeScoreEfficiencyMeasurement'
#ProcList="TTLJ,TTLJ,tW_top,tW_antitop,ST_sch,ST_tch_top,ST_tch_antitop"

for YEAR in ${ARR_YEAR[@]};do
    for ID in ${ARR_ID[@]};do
	##---TT vs DY
	ProcList="DY,TTLJ,TTLL"
	SAVEPATH=plot/$ana/$YEAR/bChargeIDEff_MC_${ID}_TT_vs_DY.pdf
	TITLE="[${YEAR}][${ID}] bChargeID Efficiency in MC"
	python Draw_MCEfficiency.py ${ana} ${YEAR} ${ID} "${ProcList}" $SAVEPATH $TITLE
	##---TT vs tW
	ProcList="tW_top,tW_antitop,TTLJ,TTLL"
	SAVEPATH=plot/$ana/$YEAR/bChargeIDEff_MC_${ID}_TT_vs_tW.pdf
	python Draw_MCEfficiency.py ${ana} ${YEAR} ${ID} "${ProcList}" $SAVEPATH $TITLE
    done
done
