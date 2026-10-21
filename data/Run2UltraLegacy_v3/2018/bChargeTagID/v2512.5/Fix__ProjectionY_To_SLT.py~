##
import ROOT
import os

list_to_fix=[
    "Jet_2017_Has_eH_eff_bminus_num",
    "Jet_2017_Has_eH_eff_bplus_num",	
    "Jet_2017_Has_eL_eff_bminus_num",	
    "Jet_2017_Has_eL_eff_bplus_num",	
    "Jet_2017_Has_muH_eff_bminus_num",	
    "Jet_2017_Has_muH_eff_bplus_num",	
    "Jet_2017_Has_muL_eff_bminus_num",	
    "Jet_2017_Has_muL_eff_bplus_num",	
]

import sys
os.system("mkdir -p fixed_files/")
path_old=sys.argv[1]
path_new='fixed_files/'+os.path.basename(path_old)


tfile_old=ROOT.TFile.Open(path_old)
tfile_new=ROOT.TFile.Open(path_new,"RECREATE")
for key in tfile_old.GetListOfKeys():
    this_name=key.GetName()
    this_h=tfile_old.Get(this_name).Clone()
    #new_h=GetProjectionYHist(this_h)
    if this_name in list_to_fix:
        print("FIX->",this_name)
        this_h.RebinX(this_h.GetNbinsX())

    this_h.Write()
tfile_new.Close()
tfile_old.Close()
