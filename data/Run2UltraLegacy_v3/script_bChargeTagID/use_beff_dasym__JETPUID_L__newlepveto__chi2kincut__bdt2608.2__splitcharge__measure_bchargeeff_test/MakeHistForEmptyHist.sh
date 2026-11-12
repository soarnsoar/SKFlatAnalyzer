ARR_YEAR=(2016preVFP 2016postVFP 2017 2018)
for YEAR in ${ARR_YEAR[@]};do
    mkdir -p FileForEmpty/${YEAR}
    hadd -f FileForEmpty/${YEAR}/hadd.root temp__${YEAR}_*/*.root
done
