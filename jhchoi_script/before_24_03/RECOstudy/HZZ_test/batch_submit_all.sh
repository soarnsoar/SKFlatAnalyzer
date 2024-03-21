


SKFlat.py -a HZZ_test -i DoubleMuon -n 150 -e 2017 --skim SkimTree_Dilepton &> submit_Muon17.log&
SKFlat.py -a HZZ_test -i DoubleMuon -n 150 -e 2016a --skim SkimTree_Dilepton &> submit_Muon16a.log&
SKFlat.py -a HZZ_test -i DoubleMuon -n 150 -e 2016b --skim SkimTree_Dilepton &> submit_Muon16b.log&
SKFlat.py -a HZZ_test -i DoubleMuon -n 150 -e 2018 --skim SkimTree_Dilepton &> submit_Muon18.log&

SKFlat.py -a HZZ_test -i DoubleEG -n 150 -e 2017 --skim SkimTree_Dilepton &> submit_EG17.log&
SKFlat.py -a HZZ_test -i DoubleEG -n 150 -e 2016a --skim SkimTree_Dilepton &> submit_EG16a.log&
SKFlat.py -a HZZ_test -i DoubleEG -n 150 -e 2016b --skim SkimTree_Dilepton &> submit_EG16b.log&
SKFlat.py -a HZZ_test -i EGamma -n 150 -e 2018 --skim SkimTree_Dilepton &> submit_EG18.log&

SKFlat.py -a HZZ_test -l inputlist_higgs.txt -n 150 -e 2017 &> submit_higgs17.log&
SKFlat.py -a HZZ_test -l inputlist_higgs.txt -n 150 -e 2018 &> submit_higgs18.log&
SKFlat.py -a HZZ_test -l inputlist_higgs.txt -n 150 -e 2016a &> submit_higgs16a.log&
SKFlat.py -a HZZ_test -l inputlist_higgs.txt -n 150 -e 2016b &> submit_higgs16b.log&


SKFlat.py -a HZZ_test -l inputlist_bkg.txt -n 150 -e 2017 &> submit_bkg17.log&
SKFlat.py -a HZZ_test -l inputlist_bkg.txt -n 150 -e 2018 &> submit_bkg18.log&
SKFlat.py -a HZZ_test -l inputlist_bkg.txt -n 150 -e 2016a &> submit_bkg16a.log&
SKFlat.py -a HZZ_test -l inputlist_bkg.txt -n 150 -e 2016b &> submit_bkg16b.log&

#inputlist_ggZZ.txt
SKFlat.py -a HZZ_test -l inputlist_ggZZ.txt -n 150 -e 2017 &> submit_ggZZ17.log&
SKFlat.py -a HZZ_test -l inputlist_ggZZ.txt -n 150 -e 2018 &> submit_ggZZ18.log&
SKFlat.py -a HZZ_test -l inputlist_ggZZ.txt -n 150 -e 2016a &> submit_ggZZ16a.log&
SKFlat.py -a HZZ_test -l inputlist_ggZZ.txt -n 150 -e 2016b &> submit_ggZZ16b.log&

SKFlat.py -a HZZ_test -i ZZTo4L_powheg -n 150 -e 2017 &> submit_qqZZ17.log&
SKFlat.py -a HZZ_test -i ZZTo4L_powheg -n 150 -e 2018 &> submit_qqZZ18.log&
SKFlat.py -a HZZ_test -i ZZTo4L_powheg -n 150 -e 2016a &> submit_qqZZ16a.log&
SKFlat.py -a HZZ_test -i ZZTo4L_powheg -n 150 -e 2016b &> submit_qqZZ16b.log&

SKFlat.py -a HZZ_test -i ZGToLLG -n 150 -e 2017 &> submit_ZG17.log&
SKFlat.py -a HZZ_test -i ZGToLLG -n 150 -e 2018 &> submit_ZG18.log&
SKFlat.py -a HZZ_test -i ZGToLLG -n 150 -e 2016a &> submit_ZG16a.log&
SKFlat.py -a HZZ_test -i ZGToLLG -n 150 -e 2016b &> submit_ZG16b.log&

SKFlat.py -a HZZ_test -l inputlist_DYNNLO.txt -n 150 -e 2017 --skim SkimTree_Dilepton &> submit_DYNNLOjets17.log&
SKFlat.py -a HZZ_test -l inputlist_DYNNLO.txt -n 150 -e 2018 --skim SkimTree_Dilepton &> submit_DYNNLOjets18.log&
SKFlat.py -a HZZ_test -l inputlist_DYNNLO.txt -n 150 -e 2016a --skim SkimTree_Dilepton &> submit_DYNNLOjets16a.log&
SKFlat.py -a HZZ_test -l inputlist_DYNNLO.txt -n 150 -e 2016b --skim SkimTree_Dilepton &> submit_DYNNLOjets16b.log&

SKFlat.py -a HZZ_test -l inputlist_DYnlo_ptbin.txt -n 150 -e 2017 &> submit_DYNLOptbin17.log&
SKFlat.py -a HZZ_test -l inputlist_DYnlo_ptbin.txt -n 150 -e 2018 &> submit_DYNLOptbin18.log&
SKFlat.py -a HZZ_test -l inputlist_DYnlo_ptbin.txt -n 150 -e 2016a &> submit_DYNLOptbin16a.log&
SKFlat.py -a HZZ_test -l inputlist_DYnlo_ptbin.txt -n 150 -e 2016b &> submit_DYNLOptbin16b.log&

#DYJets10to50_MG
SKFlat.py -a HZZ_test -i DYJets10to50_MG  -n 150 -e 2017 &> submit_DY105017.log&
SKFlat.py -a HZZ_test -i DYJets10to50_MG  -n 150 -e 2018 &> submit_DY105018.log&
SKFlat.py -a HZZ_test -i DYJets10to50_MG  -n 150 -e 2016a &> submit_DY105016a.log&
SKFlat.py -a HZZ_test -i DYJets10to50_MG  -n 150 -e 2016b &> submit_DY105016b.log&
