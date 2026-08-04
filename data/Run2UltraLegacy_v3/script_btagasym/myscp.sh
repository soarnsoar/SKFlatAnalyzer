#from=jhchoi@cms.knu.ac.kr:/u/user/jhchoi/hc/HC_bbar/my/datacards/ShapeAnalysis/bTagChargeAsym/bTagChargeAsym_BINNING__ApplyBtagSF__use_beff__JETPUID_L__chi2kincut__FreezeSF0/result/txt/
from=jhchoi@cms.knu.ac.kr:/u/user/jhchoi/hc/HC_bbar/my/datacards/ShapeAnalysis/bTagChargeAsym/bTagChargeAsym_BINNING__ApplyBtagSF__use_beff__noveto__newlepveto__JETPUID_L__chi2kincut__/result/txt/

ARR_YEAR=(
    2016preVFP 2016postVFP 2017 2018
)

for YEAR in ${ARR_YEAR[@]};do
    to=${DATA_DIR}/${YEAR}/btagasym
    mkdir -p ${to}

    scp $from/*${YEAR}*.txt $to/

done
