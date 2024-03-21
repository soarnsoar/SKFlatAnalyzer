SKFlat.py -a BBbarRecoTMVA -l inputlist_major.txt -n 300 -e 2017 &> submit_MC_major.log&
SKFlat.py -a BBbarRecoTMVA -l inputlist_minor.txt -n 50 -e 2017 &> submit_MC_minor.log&
SKFlat.py -a BBbarRecoTMVA -i SingleMuon -n 50 -e 2017 &> submit_Muon.log&
SKFlat.py -a BBbarRecoTMVA -i SingleElectron -n 50 -e 2017 &> submit_Electron.log&
