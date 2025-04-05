import ROOT

#yearlist=["2016preVFP","2016postVFP","2017","2018"]
yearlist=["2017"]
for year in yearlist:
    #2016preVFP/BTag/MeasureJetTaggingEfficiency_TTLL_TTLJ_hadded.root
    #default_file="/data6/Users/jhchoi/SKFlatOutput/Run2UltraLegacy_v3/TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch/"+year+"/measure_bchargeeff__use_beff__/temp/combine.root"
    default_file="/data6/Users/jhchoi/SKFlatOutput/Run2UltraLegacy_v3/bbbarAsymMeasurement/"+year+"/measure_bchargeeff__/temp/combine.root"

    default_tfile=ROOT.TFile.Open(default_file)
    keylist=default_tfile.GetListOfKeys()

    list_hname=[]
    for key in keylist:
        this_classname=key.GetClassName()
        if "Directory" in this_classname : continue
        this_name=key.GetName()
        list_hname.append(this_name)

    tfile_new=ROOT.TFile.Open(year+"__empty.root","RECREATE")
    for hname in list_hname:
        this_h=default_tfile.Get(hname).Clone()
        this_h.SetDirectory(0)
        this_h.Reset()
        this_h.Write()

    tfile_new.Close()
    default_tfile.Close()
