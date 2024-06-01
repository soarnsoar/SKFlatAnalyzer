VERSION="2405.2"
Transform="NUG"
nlayer=3
nnode=50
batchsize=100
dropout=0.1


ARR_YEAR=(2016preVFP 2016postVFP 2017 2018)
OBJS=(muon electron jet)
for YEAR in ${ARR_YEAR[@]};do
    for OBJ in ${OBJS[@]};do
	TARGETDIR=/data6/Users/jhchoi/TMVA/TMVA_TOOL/ws/WORKDIR/${VERSION}/EEMu_MuMuE_Method/${YEAR}/${OBJ}/${OBJ}${YEAR}__${nlayer}__${nnode}__${batchsize}__${dropout}/Trf_${Transform}/${OBJ}${YEAR}__${nlayer}__${nnode}__${batchsize}__${dropout}/weights/
	DES=${YEAR}/TMVA/ChargeScore/v${VERSION}/${OBJ}
	mkdir -p ${DES}
	echo ${TARGETDIR}
	cp ${TARGETDIR}/* ${DES}/
    done
done


