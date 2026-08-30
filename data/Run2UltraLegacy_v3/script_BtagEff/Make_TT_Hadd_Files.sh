#"../"+year+"/BTag/PreselectionAnalyzer_TTLJ_powheg.root"
ARR_YEAR=(2016preVFP 2016postVFP 2017 2018)
for YEAR in ${ARR_YEAR[@]};do
    #"../"+year+"/BTag/PreselectionAnalyzer_TTLJ_powheg.root"
    hadd -f ../${YEAR}/BTag/PreselectionAnalyzer_TTLJ_TTLL_HADDED.root ../${YEAR}/BTag/PreselectionAnalyzer_TTLJ_powheg.root  ../${YEAR}/BTag/PreselectionAnalyzer_TTLL_powheg.root
done
