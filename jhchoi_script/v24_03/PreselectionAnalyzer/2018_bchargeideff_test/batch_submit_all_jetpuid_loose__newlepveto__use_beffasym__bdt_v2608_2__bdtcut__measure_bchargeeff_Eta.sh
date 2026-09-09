#PreselectionAnalyzer
mkdir -p jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/

SKIM="--skim SkimTree_Dilepton_1DeepJetTightWP"
FLAG="--userflags jetpuid_loose,newlepveto,use_beffasym,bdt_v2608_2,bdtcut,measure_bchargeeff_Eta"
NMAX="--nmax 400"

YEAR=2018
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/major.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_TT.txt -n 150 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/TT.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/minor.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/tW.log&

#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/DoubleMuon.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/EGamma.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer ${SKIM} -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/NoSkim.log&
sleep 5
SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/VV.log&



#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_major.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/major.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_minor.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/minor.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l inputlist_tW.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/tW.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i DoubleMuon -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/DoubleMuon.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -i EGamma -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/EGamma.log&
#SKFlat.py -a PreselectionAnalyzer -l inputlist_NoSkim.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/NoSkim.log&
#SKFlat.py -a PreselectionAnalyzer  ${SKIM} -l  inputlist_VV.txt -n 50 -e ${YEAR} $FLAG ${NMAX} &> jetpuid_loose_newlepveto_use_beffasym_bdt_v2608_2_bdtcut_measure_bchargeeff_Eta_logs/VV.log&

