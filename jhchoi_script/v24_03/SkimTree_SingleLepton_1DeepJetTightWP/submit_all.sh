ARR_YEAR=(
    2016a  2016b  2017  2018
)
#submit_skim.sh
CURDIR=$PWD
for YEAR in ${ARR_YEAR[@]};do
    cd ${YEAR}
    source submit_skim.sh
    cd ${CURDIR}
done
