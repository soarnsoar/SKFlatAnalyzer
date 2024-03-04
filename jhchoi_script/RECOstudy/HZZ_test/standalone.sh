#SKFlat.py -a HZZ_test -i GluGluHToZZTo4L -n 1 -e 2017 --no_exec
SKFlat.py -a HZZ_test -l inputlist_higgs.txt -n 1 --no_exec -e 2017 &> submit_higgs.stdal.log&
SKFlat.py -a HZZ_test -i DoubleMuon -n 1 -e 2017 --no_exec --skim SkimTree_Dilepton &> submit_Muon.stdal.log&
