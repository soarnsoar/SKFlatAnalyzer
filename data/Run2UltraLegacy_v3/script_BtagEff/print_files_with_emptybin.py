import ROOT
import os
import glob

def has_zero_bin_histogram(filename,wp='DeepJet_Tight_eff_B',skip_pt20to30=True):
    f = ROOT.TFile.Open(filename)
    if not f or f.IsZombie():
        return False
    ibiny_start=1
    if skip_pt20to30:ibiny_start=2
    result = False
    for key in f.GetListOfKeys():
        obj = key.ReadObj()
        if obj.InheritsFrom("TH1"):
            histname=obj.GetName()
            if 'denom' in histname or wp in histname:
                #print(histname)
                nx = obj.GetNbinsX()
                ny = obj.GetNbinsY()

            
                for ix in range(1, nx + 1):
                    for iy in range(ibiny_start, ny + 1):
                        if obj.GetBinContent(ix, iy) <= 0:
                            return True


    


    f.Close()
    return result

    
list_rootfile=glob.glob('../201*/BTag/*.root')

for rfpath in list_rootfile:
    HasZeroBin=has_zero_bin_histogram(rfpath)
    if HasZeroBin:
        print(rfpath)
