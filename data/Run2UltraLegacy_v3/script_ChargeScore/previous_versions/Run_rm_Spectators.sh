###
version=v2512.5
ARR_XML=($(ls ../201*/TMVA/ChargeScore/BDT/${version}/*/*.xml))

for XML in ${ARR_XML[@]};do
    python3 rm_Spectators.py ${XML}
done
