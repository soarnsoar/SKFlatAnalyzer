ARR_ID=(
    muH
    muL
    eH
    eL
    jH
)
ARR_YEAR=(
    2016preVFP
    2016postVFP
    2017
    2018
)
for YEAR in ${ARR_YEAR[@]};do

    for ID in ${ARR_ID[@]};do
	python3 DrawEff.py ${YEAR} ${ID}

    done
done
