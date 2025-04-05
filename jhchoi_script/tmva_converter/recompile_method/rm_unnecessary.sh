#convert_v1_TO_v2.py

#$SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/TTSemilepJetAssignment/*/*.h5
#ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/ChargeScore/v*/*/*.h5


ARR_RM=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/ChargeScore/v*/*/*v1*v1*))
ARR_RM+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/ChargeScore/v*/*/*v2*v1*))
ARR_RM+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/ChargeScore/v*/*/*v1*v2*))
ARR_RM+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/ChargeScore/v*/*/*v2*v2*))
ARR_RM+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/ChargeScore/v*/*/*ConvertToV2.log))

ARR_RM+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/TTSemilepJetAssignment/*/*v1*v1*))
ARR_RM+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/TTSemilepJetAssignment/*/*v2*v1*))
ARR_RM+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/TTSemilepJetAssignment/*/*v1*v2*))
ARR_RM+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/TTSemilepJetAssignment/*/*v2*v2*))
ARR_RM+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/TTSemilepJetAssignment/*/*ConvertToV2.log ))


for RM in ${ARR_RM[@]};do
    echo $RM
    rm $RM
    
done
