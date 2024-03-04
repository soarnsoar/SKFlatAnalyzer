###
#SKFlat.py -a BasicTest -i DYJets -n 1 -e 2017 --no_exec
#SKFlat.py -a B_In_GEN -i DYJets -n 300 -e 2017
#SKFlat.py -a B_Info_Analyzer -i DYJets -n 1500 -e 2017
#SKFlat.py -a B_Info_Analyzer -i DYJets -n 300 -e 2017
#SKFlat.py -a BBbar_Analyzer -i DYJets -n 300 -e 2017
#SKFlat.py -a BBbar_Analyzer -i DYJetsToEE_MiNNLO -n 300 -e 2017
#SKFlat.py -a BBbar_Analyzer -i DYJetsToMuMu_MiNNLO -n 300 -e 2017


#SKFlat.py -a BBbar_Analyzer -l inputlist.txt -n 300 -e 2017


SKFlat.py -a ForTMVA_BBbarAnalyzer -l inputlist.txt -n 300 -e 2017
#SKFlat.py -a ForTMVA_BBbarAnalyzer_pjetrest0p7_3 -l inputlist.txt -n 300 -e 2017
#SKFlat.py -a ForTMVA_BBbarAnalyzer_lepV1 -l inputlist.txt -n 300 -e 2017
