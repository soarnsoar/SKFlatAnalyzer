###
version=v2608.2
#ARR_XML=($(ls ../201*/TMVA/ChargeScore/BDT/${version}/*/*.xml))
ARR_OBJ=(muon electron jet)
ARR_YEAR=(2016preVFP 2016postVFP 2017 2018)
mkdir -p log_expr/
#for XML in ${ARR_XML[@]};do
for OBJ in ${ARR_OBJ[@]};do
    for YEAR in ${ARR_YEAR[@]};do
	XML=../${YEAR}/TMVA/ChargeScore/BDT/${version}/${OBJ}/BDT_${YEAR}_BDT.weights.xml
	python3 ReadEXP_in_XML.py ${XML} > log_expr/${OBJ}__${YEAR}.txt
    done
done
