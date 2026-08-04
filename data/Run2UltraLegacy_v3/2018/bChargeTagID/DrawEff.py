import ROOT
import sys
import os
import copy
class hEff:
    def __init__(self,year,ID,bsign,filepath):
        self.year=year
        self.ID=ID
        self.bsign=bsign
        self.tfile=ROOT.TFile.Open(filepath)
        self.SetHist()
    def GetNumeName(self):
        year=self.year
        ID=self.ID
        bsign=self.bsign
        
        ret="Jet_"+year+"_Has_"+ID+"_eff_b"+bsign+"_num"
        if ID=="jH":
            ret="Jet_"+year+"_jH_eff_bminus_num__NoSL"
        print(ret)
        return ret
        
    def GetDenoName(self):
        year=self.year
        ID=self.ID
        bsign=self.bsign
        
        ret="Jet_"+year+"_eff_b"+bsign+"_denom"
        if ID=="jH":
            ret="Jet_"+year+"_eff_b"+bsign+"_denom__NoSL"
        print(ret)
        return ret
    def SetHist(self):
        NumeName=self.GetNumeName()
        DenoName=self.GetDenoName()
        #print(NumeName,DenoName)
        #self.tfile.ls()
        self.h2_eff=self.tfile.Get(NumeName).Clone()
        h_deno=self.tfile.Get(DenoName).Clone()
        self.h2_eff.Divide(self.h2_eff,h_deno,1.0,1.0,"B")
        self.h1_eff=self.ConvertTH2ToTH1(self.h2_eff,self.year+"__"+self.ID+"__b"+self.bsign)

    
    def ConvertTH2ToTH1(self,h2,name=""):
        Nx=h2.GetNbinsX()
        Ny=h2.GetNbinsY()
        
        Nbins=Nx*Ny
        #TH1D (const char *name, const char *title, Int_t nbinsx, Double_t xlow, Double_t xup)
        h1=ROOT.TH1D(name,name,Nbins,0,Nbins+1)
        for ibin_x in range(1,Nx+1):
            for ibin_y in range(1,Ny+1):
                this_z=h2.GetBinContent(ibin_x,ibin_y)
                this_errz=h2.GetBinError(ibin_x,ibin_y)
                newx=(ibin_x-1)+Nx*(ibin_y-1)
                #h1.Fill(newx,this_z)
                new_ibin=1+(ibin_x-1)+Nx*(ibin_y-1)
                h1.SetBinContent(new_ibin,this_z)
                h1.SetBinError(new_ibin,this_errz)
        h1.SetStats(0)
        return h1

def CompareTwoHists(h1,name1,h2,name2,name):
    #TLegend (Double_t x1, Double_t y1, Double_t x2, Double_t y2, const char *header="", Option_t *option="brNDC")
    c=ROOT.TCanvas()
    h1.Draw()
    h2.Draw('sames')
    h1.SetLineColor(2)
    h2.SetLineColor(4)
    #h1.SetMaximum(1.5)
    #h2.SetMaximum(1.5)
    ymax=max(h1.GetMaximum(),h2.GetMaximum())
    h1.SetMaximum(1.5*ymax)
    h2.SetMaximum(1.5*ymax)
            
    leg=ROOT.TLegend(0.1,0.7,0.4,0.9)
    leg.AddEntry(h1,name1)
    leg.AddEntry(h2,name2)

    leg.Draw()
    c.SaveAs(name+".pdf")

def Run_TTLJ_TTLL(year,ID):
    

    #tfile_TTLJ=ROOT.TFile('TTsemiLepChargeScoreEfficiencyMeasurement_TTLJ_powheg.root')
    #tfile_TTLL=ROOT.TFile('TTsemiLepChargeScoreEfficiencyMeasurement_TTLL_powheg.root')
    filepath_TTLJ="TTsemiLepChargeScoreEfficiencyMeasurement_TTLJ_powheg.root"
    filepath_TTLL="TTsemiLepChargeScoreEfficiencyMeasurement_TTLL_powheg.root"
    
    
    
    
    hEff_TTLJ_bplus=hEff(year,ID,'plus',filepath_TTLJ)
    hEff_TTLJ_bminus=hEff(year,ID,'minus',filepath_TTLJ)
    
    hEff_TTLL_bplus=hEff(year,ID,'plus',filepath_TTLL)
    hEff_TTLL_bminus=hEff(year,ID,'minus',filepath_TTLL)
    #class hEff:
    #    def __init__(self,year,ID,bsign):
    
    
    CompareTwoHists(hEff_TTLJ_bplus.h1_eff,"TTLJ_bplus",hEff_TTLL_bplus.h1_eff,"TTLL_bplus","TTLJ__VS__TTLL__both_bplus")
    CompareTwoHists(hEff_TTLJ_bminus.h1_eff,"TTLJ_bminus",hEff_TTLL_bminus.h1_eff,"TTLL_bminus","TTLJ__VS__TTLL__both_bminus")


def Run_TT_DY(year,ID):
    


    filepath_TT="hadd_TTLJ_TTLL.root"
    filepath_DY="hadd_DY.root"
    
    
    
    
    hEff_TT_bplus=hEff(year,ID,'plus',filepath_TT)
    hEff_TT_bminus=hEff(year,ID,'minus',filepath_TT)
    
    hEff_DY_bplus=hEff(year,ID,'plus',filepath_DY)
    hEff_DY_bminus=hEff(year,ID,'minus',filepath_DY)
    #class hEff:
    #    def __init__(self,year,ID,bsign):
    
    
    CompareTwoHists(hEff_TT_bplus.h1_eff,"TT_bplus",hEff_DY_bplus.h1_eff,"DY_bplus","TT__VS__DY__both_bplus")
    CompareTwoHists(hEff_TT_bminus.h1_eff,"TT_bminus",hEff_DY_bminus.h1_eff,"DY_bminus","TT__VS__DY__both_bminus")

def Run_TT_WJets(year,ID):
    


    filepath_TT="hadd_TTLJ_TTLL.root"
    filepath_WJets="TTsemiLepChargeScoreEfficiencyMeasurement_WJets_MG.root"
    
    
    
    
    hEff_TT_bplus=hEff(year,ID,'plus',filepath_TT)
    hEff_TT_bminus=hEff(year,ID,'minus',filepath_TT)
    
    hEff_WJets_bplus=hEff(year,ID,'plus',filepath_WJets)
    hEff_WJets_bminus=hEff(year,ID,'minus',filepath_WJets)
    #class hEff:
    #    def __init__(self,year,ID,bsign):
    
    
    CompareTwoHists(hEff_TT_bplus.h1_eff,"TT_bplus",hEff_WJets_bplus.h1_eff,"WJets_bplus","TT__VS__WJets__both_bplus")
    CompareTwoHists(hEff_TT_bminus.h1_eff,"TT_bminus",hEff_WJets_bminus.h1_eff,"WJets_bminus","TT__VS__WJets__both_bminus")
    

##----
year=sys.argv[1]
ID=sys.argv[2]
Run_TTLJ_TTLL(year,ID)
Run_TT_DY(year,ID)
Run_TT_WJets(year,ID)
