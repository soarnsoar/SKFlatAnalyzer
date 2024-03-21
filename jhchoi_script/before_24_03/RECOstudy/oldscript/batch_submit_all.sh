SKFlat.py -a BBbarRecoTMVA -l inputlist_all.txt -n 300 -e 2017 &> submit_MC.log&
SKFlat.py -a BBbarRecoTMVA -i SingleMuon -n 300 -e 2017 &> submit_Muon.log&
SKFlat.py -a BBbarRecoTMVA -i SingleElectron -n 300 -e 2017 &> submit_Electron.log&
