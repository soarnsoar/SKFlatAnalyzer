#"../"+year+"/BTag/PreselectionAnalyzer_TTLJ_powheg.root"
ARR_YEAR=(2016preVFP 2016postVFP 2017 2018)


ana=TTsemiLepChargeScoreEfficiencyMeasurement
for YEAR in ${ARR_YEAR[@]};do
    #"../"+year+"/BTag/PreselectionAnalyzer_TTLJ_powheg.root"
    rm ${DATA_DIR}/${YEAR}/bChargeTagID/${ana}_DY_HADDED.root
    hadd -f ${DATA_DIR}/${YEAR}/bChargeTagID/${ana}_DY_HADDED.root ${DATA_DIR}/${YEAR}/bChargeTagID/${ana}_DYJetsTo*.root
    #ls ../${YEAR}/BTag/${ana}_${proc}_*.root 
done
