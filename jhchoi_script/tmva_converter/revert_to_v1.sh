#convert_v1_TO_v2.py

#$SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/TTSemilepJetAssignment/*/*.h5
#ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/ChargeScore/v*/*/*.h5


#ARR_MODEL=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/ChargeScore/v*/*/TrainedModel_DNN.h5))
#ARR_MODEL+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/ChargeScore/v*/*/model.h5))
#ARR_MODEL+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/TTSemilepJetAssignment/*/TrainedModel_DNN.h5))
#ARR_MODEL+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/TTSemilepJetAssignment/*/model.h5))


#ARR_MODEL=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/ChargeScore/v2409.2/*/TrainedModel_DNN.h5))
#ARR_MODEL+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/201*/TMVA/ChargeScore/v2409.2/*/model.h5))

ARR_MODEL=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/2018/TMVA/ChargeScore/v2409.2/*/TrainedModel_DNN.h5))
ARR_MODEL+=($(ls $SKFlat_WD/data/Run2UltraLegacy_v3/2018/TMVA/ChargeScore/v2409.2/*/model.h5))



for MODEL in ${ARR_MODEL[@]};do
    echo "[REVERT]"
    echo ${MODEL}
    cp ${MODEL}__v1.h5 ${MODEL}
done
