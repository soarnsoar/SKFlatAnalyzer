import ROOT
import os
import glob

def has_zero_bin_histogram(filename):
    f = ROOT.TFile.Open(filename)
    if not f or f.IsZombie():
        return False

    result = False
    for key in f.GetListOfKeys():
        obj = key.ReadObj()
        
        
        if obj.InheritsFrom("TH1"):
            nx = obj.GetNbinsX()
            ny = obj.GetNbinsY()
            nz = obj.GetNbinsZ()
            
            for ix in range(1, nx + 1):
                for iy in range(1, ny + 1):
                    for iz in range(1, nz + 1):
                        if obj.GetBinContent(ix, iy, iz) == 0:
                            return True


    


    f.Close()
    return result

    
list_rootfile=glob.glob('../201*/bChargeTagID/*.root')

for rfpath in list_rootfile:
    HasZeroBin=has_zero_bin_histogram(rfpath)
    if HasZeroBin:
        print(rfpath)
