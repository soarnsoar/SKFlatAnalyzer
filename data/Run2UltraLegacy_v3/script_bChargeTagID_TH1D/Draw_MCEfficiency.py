import runpy,ROOT,os,sys
from collections import OrderedDict

leg_x1=0.2
leg_x2=0.5

colorlist_default=[2,4,3,46,6,7,9,46]
LIST_PTBINNAME=[
    'P_{T} : 30 - 50 GeV',
    'P_{T} : 50 - 70 GeV',
    'P_{T} : 70 - 100 GeV',
    'P_{T} : 100 - 140 GeV',
    'P_{T} : > 140 GeV',
    
]


LIST_PTBINNAME=[
    '30 - 50 GeV',
    '50 - 70 GeV',
    '70 - 100 GeV',
    '100 - 140 GeV',
    '> 140 GeV',
    
]

LIST_PTBIN=['PT30To50','PT50To70','PT70To100','PT100To140','PT140ToInf']

def GetFileName(ana,sample):
    return ana+"_"+sample+".root"
class EffTool:
    def __init__(self,ana,year,sample,ID):
        self.ana=ana
        self.sample=sample
        self.ID=ID
        self.year=year
        self.borigins=['bminus','bplus']
        self.PTBINS=OrderedDict()
        self.LIST_PTBIN=['PT30To50','PT50To70','PT70To100','PT100To140','PT140ToInf']

        for PTBIN in self.LIST_PTBIN:
            self.PTBINS[PTBIN]=[]
        self.ReadBins()
        self.ReadHists()
    def ReadBins(self):
        year=self.year
        ID=self.ID
        d = runpy.run_path(f"binlist/{year}__{ID}.py")
        self.binlist = d["binlist"]
        idx=0
        for PTBIN in self.LIST_PTBIN:
            for binname in self.binlist:
                if PTBIN in binname:
                    mOverPts=binname.split(PTBIN)[1].split('mOverPt')[1].split('_')[1:]
                    #print(mOverPt1)                    
                    mOverPt1= mOverPts[0].replace('p','.')
                    mOverPt2= mOverPts[1].replace('p','.')
                    #print(mOverPt1,mOverPt2)
                    self.PTBINS[PTBIN].append((binname,idx,float(mOverPt1),float(mOverPt2)))
                    idx+=1
    def GetPTLines(self,_ymax,_ymin=0):
        list_tline=[]
        for PTBIN in self.PTBINS:
            lastidx=self.PTBINS[PTBIN][-1][1]
            #line = ROOT.TLine(3, h.GetMinimum(), 3, h.GetMaximum())
            this_tline=ROOT.TLine(lastidx+1,_ymin,lastidx+1,_ymax)
            list_tline.append(this_tline)
        return list_tline+[]
    def ReadHists(self):
        DATA_DIR=os.getenv('DATA_DIR')
        fdirpath=f'{DATA_DIR}/{self.year}/bChargeTagID/'
        self.filepath=fdirpath+GetFileName(self.ana,self.sample)
        self.tfile=ROOT.TFile.Open(self.filepath)
        self.dict_hists={}
        for borigin in self.borigins:
            self.dict_hists[f'{borigin}__num']=self.tfile.Get(f'Jet_{self.year}_eff_{borigin}_num__{self.ID}').Clone()
            self.dict_hists[f'{borigin}__denom']=self.tfile.Get(f'Jet_{self.year}_eff_{borigin}_denom__{self.ID}').Clone()
            self.dict_hists[f'{borigin}__eff']=self.dict_hists[f'{borigin}__num'].Clone()
            self.dict_hists[f'{borigin}__eff'].Divide(self.dict_hists[f'{borigin}__num'],self.dict_hists[f'{borigin}__denom'],1.0, 1.0, "B")
    def GetEffHist(self,borigin):
        return self.dict_hists[f'{borigin}__eff']
    def GetYmax(self):
        ret=-99999999
        for borigin in self.borigins:
            this_max=self.dict_hists[f'{borigin}__eff'].GetMaximum()
            if this_max > ret : ret=this_max
        return ret
    def GetYmin(self):
        ret=99999999
        for borigin in self.borigins:
            this_min=self.dict_hists[f'{borigin}__eff'].GetMinimum()
            if this_min < ret : ret=this_min
        return ret    
class DrawHists:
    def __init__(self):

        self.hlist=[]
        self.namelist=[]
        self.colorlist=[]
        self.linetypelist=[]
        self.drawoptlist=[]
        self.colorlist_default=[1,2,4,6,3,7,9,46]
        self.addtoleglist=[]
        self.r=1.6
        self.manual_yminmax=False
        self.xname=False
        self.yname=False
        self.AddToDrawList=[]
        self.title=""
    def SetTitle(self,_title):
        self.title=_title
    def SetXname(self,_xname):
        self.xname=_xname
    def SetYname(self,_yname):
        self.yname=_yname        
    def AddHist(self,_h,_name,_color=False,_linetype=1,_drawopt='',_addtoleg=False):
        self.hlist.append(_h)
        self.namelist.append(_name)
        self.colorlist.append(_color)
        self.linetypelist.append(_linetype)
        self.drawoptlist.append(_drawopt)
        self.addtoleglist.append(_addtoleg)
    def SetMinMax(self,_ymin,_ymax):
        self.ymin=_ymin
        self.ymax=_ymax
        self.manual_yminmax=True
    def CalcMinMax(self):
        self.ymax=-99999999
        self.ymin=99999999
        for i,_h in enumerate(self.hlist):
            this_ymax=_h.GetMaximum()
            this_ymin=_h.GetMinimum()
            if this_ymax > self.ymax : self.ymax = this_ymax
            if this_ymin < self.ymin : self.ymin = this_ymin

        #d=self.ymax-self.ymin
        self.ymax=self.ymax*2
    def AddToDraw(self,_obj):
        self.AddToDrawList.append(_obj)
    def Draw(self,savepath):
        if not self.manual_yminmax : self.CalcMinMax()
        self.c=ROOT.TCanvas()
        #auto legend = new TLegend(x1, y1, x2, y2, header, option);
        self.leg=ROOT.TLegend(leg_x1,0.7,leg_x2,0.9)
        #nColumn=int((len(self.hlist)+1)/2)
        #self.leg.SetNColumns(nColumn)
        
        for i,_h in enumerate(self.hlist):
            option=''
            if i>0 : option='SAMES'
            this_drawopt=self.drawoptlist[i]
            option+=' '+this_drawopt
            _h.SetTitle(self.title)
            _h.Draw(option)
            this_color=self.colorlist[i]
            if not this_color: this_color= self.colorlist_default[i]
            _h.SetLineColor(this_color)
            this_linetype=self.linetypelist[i]

            _h.SetLineStyle(this_linetype)
            _h.SetMarkerColor(this_color)
            _h.SetStats(0)
            _h.GetYaxis().SetRangeUser(self.ymin,self.ymax)
            _h.GetXaxis().SetTitle(self.xname)
            _h.GetYaxis().SetTitle(self.yname)
            addtoleg=self.addtoleglist[i]
            if addtoleg : self.leg.AddEntry(_h,self.namelist[i])
        
        self.leg.Draw()
        for _obj in self.AddToDrawList:
            _obj.Draw('sames')
        dirpath=os.path.dirname(savepath)
        if dirpath:os.system('mkdir -p '+dirpath)
        self.c.SaveAs(savepath)
        
        

def GetPTLines(efftool_list,r):
    ymax=-99999
    ymin=-ymax
    for efftool in efftool_list:
        this_ymax=efftool.GetYmax()
        this_ymin=efftool.GetYmin()
        if this_ymax > ymax : ymax= this_ymax
        if this_ymin < ymin : ymin= this_ymin
    
    ptlines=efftool_list[0].GetPTLines(r*ymax,ymin)
    return ptlines

def GetNameMap():
    ret={
        'TTLJ':'TTLJ_powheg',
        'TTLL':'TTLL_powheg',
        'tW_top':'SingleTop_tW_top_NoFullyHad',
        'tW_antitop':'SingleTop_tW_antitop_NoFullyHad',
        'DY->ee' : 'DYJetsToEE_MiNNLO',
        'DY->#mu#mu' : 'DYJetsToMuMu_MiNNLO',
        'DY' : 'DY_HADDED',
        'ST_sch':'SingleTop_sch_Lep',
        'ST_tch_antitop':'SingleTop_tch_antitop_Incl',
        'ST_tch_top':'SingleTop_tch_top_Incl',
    }    
    return ret
if __name__ == "__main__":
    ##---Arguments
    ana=sys.argv[1]
    year=sys.argv[2]
    ID=sys.argv[3]
    ListToDrawStr=sys.argv[4]
    savepath=sys.argv[5]
    title=sys.argv[6]

    ##-----Sample alias to SampleNameInSKFlat
    dict_name=GetNameMap()
    r=1.5 ## yrange ratio

    ##---Parse input samplelist
    ListToDraw=ListToDrawStr.split(',')

    ##---Make Efficiency Hists
    DictToDraw=OrderedDict()
    for p in ListToDraw:
        this_name=dict_name[p]
        DictToDraw[p]=EffTool(ana,year,this_name,ID)
    DictToDraw['Combine']=EffTool(ana,year,'HADDED',ID)



    
    ##---vertical line splitting pt bins 
    ptlines=GetPTLines([DictToDraw[p] for p in DictToDraw],r)
    ##--ptbin titles
    ptbin_titles=[]
    for i,ptline in enumerate(ptlines):
        if i==0:
            x1=0
        else:
            x1=ptlines[i-1].GetX1()
        
        x2=ptlines[i].GetX2()
        xcenter=(x1+x2)/2
        ycenter = ptline.GetY2()*0.8
        ptbinname=LIST_PTBINNAME[i]
        this_latex = ROOT.TLatex(xcenter,ycenter,ptbinname)
        this_latex.SetTextAlign(22)
        this_latex.SetTextSize(0.025)
        ptbin_titles.append(this_latex)
    ##---plotter
    plotter=DrawHists()
    plotter.SetTitle(title)
    ##----pt Line style and add to draw
    for ptline in ptlines:
        ptline.SetLineStyle(3)
        plotter.AddToDraw(ptline)
    ##---ptbin name
    for ptbin_title in ptbin_titles:
        plotter.AddToDraw(ptbin_title)

    ##---legend for binlist
    #self.PTBINS[PTBIN]
    binlist=DictToDraw['Combine'].PTBINS ##take it from Combined hists
    leg_bins = ROOT.TLegend(leg_x2, 0.7, 0.9, 0.9)
    leg_bins.SetMargin(0.02)
    leg_bins.AddEntry(0, "m/p_{T} bin edges", "")
    for ipt,PTBIN in enumerate(LIST_PTBIN):
        mOverPtBins=[ x[2] for x in binlist[PTBIN]   ] + [0.5]
        leg_bins.AddEntry(0,LIST_PTBINNAME[ipt]+" : "+str(mOverPtBins) , "")
        #leg_bins.AddEntry(0, "30-50 GeV : [0, 0.10, 0.15, 0.20, 0.25, 1]", "")
    plotter.AddToDraw(leg_bins)
    ##---Add legend for b+/b- by line
    leg_pm=ROOT.TLegend(0.1,0.7,leg_x1,0.9)
    line_solid = ROOT.TLine()
    line_solid.SetLineStyle(1)
    
    line_dashed = ROOT.TLine()
    line_dashed.SetLineStyle(2)
    
    leg_pm.AddEntry(line_solid, "b^{+}", "l")
    leg_pm.AddEntry(line_dashed, "b^{-}", "l")    

    leg_pm.SetTextSize(0.04)
    plotter.AddToDraw(leg_pm)
        
    ##--axis titles    
    plotter.SetXname('bin index')
    plotter.SetYname('Efficiency')


    for i,p in enumerate(DictToDraw):
        this_color=colorlist_default[i]
        drawopt=''
        if i == len(DictToDraw)-1 :
            this_color=1
            drawopt='HIST L P'
        plotter.AddHist(DictToDraw[p].GetEffHist('bplus'),f'{p}',this_color,1,drawopt,True)
        plotter.AddHist(DictToDraw[p].GetEffHist('bminus'),f'{p}',this_color,2,drawopt,False)

    plotter.Draw(savepath)
