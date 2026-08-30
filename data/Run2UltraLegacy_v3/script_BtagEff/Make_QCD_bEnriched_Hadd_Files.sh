#"../"+year+"/BTag/PreselectionAnalyzer_TTLJ_powheg.root"
ARR_YEAR=(2016preVFP 2016postVFP 2017 2018)
proc=QCD_bEnriched
ana=PreselectionAnalyzer
for YEAR in ${ARR_YEAR[@]};do
    #"../"+year+"/BTag/PreselectionAnalyzer_TTLJ_powheg.root"
    hadd -f ../${YEAR}/BTag/${ana}_${proc}_HADDED.root ../${YEAR}/BTag/${ana}_${proc}_*.root
    #ls ../${YEAR}/BTag/${ana}_${proc}_*.root 
done
