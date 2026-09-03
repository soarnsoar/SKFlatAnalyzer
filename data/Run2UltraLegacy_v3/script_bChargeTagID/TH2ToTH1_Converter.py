####
import os
import ROOT
from collections import OrderedDict
from array import array
class TH2ToTH1_Converter:
    def __init__(self, h2,xname, yname):
        self.h2=h2
        self.dict_xdist=OrderedDict()##xdistribution
        self.dict_ydist=OrderedDict()
        
        self.xname=xname
        self.yname=yname

    def Run(self):
        self.ParseAxis()
        self.ScanAllBins()
    
    def ParseAxis(self):
        self.xaxis=self.h2.GetXaxis()
        self.nx=self.xaxis.GetNbins()
        self.xbins=[]
        for i in range(1,self.nx+2):
            self.xbins.append(self.xaxis.GetBinLowEdge(i))

    
        self.yaxis=self.h2.GetYaxis()
        self.ny=self.yaxis.GetNbins()
        self.ybins=[]
        for i in range(1,self.ny+2):
            self.ybins.append(self.yaxis.GetBinLowEdge(i))
    
        ##---Make EmptyHist
        self.hx_empty=ROOT.TH1D("x_empty","x_empty",len(self.xbins)-1,array("d",self.xbins))
        self.hy_empty=ROOT.TH1D("y_empty","y_empty",len(self.ybins)-1,array("d",self.ybins))
   
        self.hx_empty.SetDirectory(0)
        self.hy_empty.SetDirectory(0)
        ##Reset
        ##Clone
        ##----Make nx X ny histograms
        for iy in range(self.ny):
            
            ymin=str(self.ybins[iy])
            ymax=str(self.ybins[iy+1])
            histtitle=self.yname+" : ["+ymin+","+ymax+")"
            histname="y__From__"+ymin+"__To__"+ymax
            this_h=self.hx_empty.Clone()
            this_h.SetTitle(histtitle)
            this_h.SetName(histname)
            self.dict_xdist[histname]=this_h


        for ix in range(self.nx):
            xmin=str(self.xbins[ix])
            xmax=str(self.xbins[ix+1])
            histtitle=self.xname+" : ["+xmin+","+xmax+")"
            histname="x__From__"+xmin+"__To__"+xmax
            this_h=self.hy_empty.Clone()
            this_h.SetTitle(histtitle)
            this_h.SetName(histname)
            self.dict_ydist[histname]=this_h



    def ScanAllBins(self):
        for ix in range(self.nx):
            for iy in range(self.ny):
                this_z=self.h2.GetBinContent(ix+1,iy+1)
                this_zerr=self.h2.GetBinError(ix+1,iy+1)

                ymin=str(self.ybins[iy])
                ymax=str(self.ybins[iy+1])            
                xdistname="y__From__"+ymin+"__To__"+ymax
                self.dict_xdist[xdistname].SetBinContent(ix+1,this_z)
                self.dict_xdist[xdistname].SetBinError(ix+1,this_zerr)

                xmin=str(self.xbins[ix])
                xmax=str(self.xbins[ix+1])            
                ydistname="x__From__"+xmin+"__To__"+xmax
                self.dict_ydist[ydistname].SetBinContent(iy+1,this_z)
                self.dict_ydist[ydistname].SetBinError(iy+1,this_zerr)


    def GetHistDictX(self):
        return self.dict_xdist
    def GetHistDictY(self):
        return self.dict_ydist

    def SaveTest(self):
        os.system("mkdir -p TESTOUTPUT/")
        for xdistname in self.dict_xdist:
            c=ROOT.TCanvas()
            self.dict_xdist[xdistname].Draw()
            c.SaveAs("TESTOUTPUT/"+xdistname+".pdf")
            del c

        for ydistname in self.dict_ydist:
            c=ROOT.TCanvas()
            self.dict_ydist[ydistname].Draw()
            c.SaveAs("TESTOUTPUT/"+ydistname+".pdf")

            del c
if __name__ == '__main__':
    #    def __init__(self, filepath, histpath, xname, yname):
    histname="Jet_2017_DeepJet_Tight_eff_B_num"
    converter=ConverterToTH1("../2017/BTag/MeasureJetTaggingEfficiency_TTLL_TTLJ_hadded.root",histname,"|eta|","pT")
    converter.Run()
    converter.SaveTest()
