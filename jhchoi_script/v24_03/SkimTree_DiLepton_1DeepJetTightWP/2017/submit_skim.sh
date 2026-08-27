mkdir -p logs/

SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP  -l inputlist_major.txt -n 300 -e 2017 &> logs/major.log&
sleep 3
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP -l inputlist_NoSkim.txt -n 300 -e 2017 &> logs/NoSkim.log&
sleep 3
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP -l inputlist_minor.txt -n 300 -e 2017 &> logs/minor.log&
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP -l inputlist_tW.txt -n 300 -e 2017 &> logs/tW.log&
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP -i DoubleMuon -n 300 -e 2017 &> logs/DoubleMuon.log&
SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP -i DoubleEG -n 300 -e 2017 &> logs/DoubleEG.log&

SKFlat.py -a SkimTree_Dilepton_1DeepJetTightWP -l  inputlist_VV.txt -n 300 -e 2017 &> logs/VV.log&

