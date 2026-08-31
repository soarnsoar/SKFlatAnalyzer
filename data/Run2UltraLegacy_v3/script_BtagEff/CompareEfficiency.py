import ROOT
import os
from math import sqrt
from TH2ToTH1_Converter import TH2ToTH1_Converter


def GetEffTH2(filepath,year,algo,wp,flav,suffix=""):
    year=str(year)
    nume_name="Jet_"+year+"_"+algo+"_"+wp+"_eff_"+flav+"_num"+suffix
    deno_name="Jet_"+year+"_eff_"+flav+"_denom"+suffix
    
    print(filepath)
    tfile=ROOT.TFile.Open(filepath)
    h_nume=tfile.Get(nume_name)
    h_deno=tfile.Get(deno_name)
    
    h2=h_nume.Clone()
    h2.SetDirectory(0)
    h2.Divide(h_nume,h_deno,1.0,1.0,"B")
    ##Add h_deno's error itset
    for ix in range(1,h2.GetXaxis().GetNbins()+1):
        for iy in range(1,h2.GetYaxis().GetNbins()+1):
            deno_z=h_deno.GetBinContent(ix,iy)
            deno_zerr=h_deno.GetBinError(ix,iy)
            deno_relerr=0
            if deno_z>0:
                deno_relerr=deno_zerr/deno_z

            this_z=h2.GetBinContent(ix,iy)
            old_zerr=h2.GetBinError(ix,iy)
            new_zerr=sqrt(old_zerr**2 + (this_z*deno_relerr)**2)
            h2.SetBinError(ix,iy,new_zerr)
            if this_z<0 or this_z>1:
                print(filepath,year,algo,wp,flav,ix,iy,'eff=',this_z)
    return h2


def Compare_TH1(list_h,list_name,savename,savedir):
    
    c1=ROOT.TCanvas()
    list_option=["Esames"]*100
    list_option[0]="E"
    
    #TLegend (Double_t x1, Double_t y1, Double_t x2, Double_t y2, const char *header="", Option_t *option="brNDC")
    leg=ROOT.TLegend(0.5, 0.6, 0.9, 0.9)

    ymax=-1.
    ymin=99999.
    for i,_h in enumerate(list_h):
        this_max=_h.GetMaximum()
        if this_max > ymax : ymax=this_max
        this_min=_h.GetMinimum()
        if this_min < ymin : ymin=this_min
    for i,_h in enumerate(list_h):
        this_option=list_option[i]        
        this_name=list_name[i]
        _h.SetName(this_name)
        _h.Draw(this_option)
        _h.SetLineColor(i+1)
        _h.SetMarkerColor(i+1)
        leg.AddEntry(_h,this_name)
        _h.SetStats(0)


        _h.SetMaximum(min(ymax*2,1.8))
        _h.SetMinimum(ymin*0.5)

        

    leg.Draw()
    os.system("mkdir -p "+savedir)
    c1.SaveAs(savedir+"/"+savename+".pdf")
    del leg
    del c1

def RunComparePOSNEG(ana,year,algo,wp,flav,procs):
    year=str(year)
    dict_converter_POS={}
    dict_h2_Presel_POS={}
    dict_hx_Presel_POS={}
    dict_hy_Presel_POS={}

    dict_converter_NEG={}
    dict_h2_Presel_NEG={}
    dict_hx_Presel_NEG={}
    dict_hy_Presel_NEG={}    
    for proc in procs:
        this_fpath="../"+year+"/BTag/"+ana+"_"+proc+".root"
        if not os.path.isfile(this_fpath) : continue

        ##-POS
        dict_h2_Presel_POS[proc]=GetEffTH2(this_fpath,year,algo,wp,flav,"_POS")
        dict_converter_POS[proc]=TH2ToTH1_Converter(dict_h2_Presel_POS[proc],"|eta|","pT")
        dict_converter_POS[proc].Run()
        dict_hx_Presel_POS[proc]=dict_converter_POS[proc].GetHistDictX()
        dict_hy_Presel_POS[proc]=dict_converter_POS[proc].GetHistDictY()

        #-NEG
        dict_h2_Presel_NEG[proc]=GetEffTH2(this_fpath,year,algo,wp,flav,"_NEG")
        dict_converter_NEG[proc]=TH2ToTH1_Converter(dict_h2_Presel_NEG[proc],"|eta|","pT")
        dict_converter_NEG[proc].Run()
        dict_hx_Presel_NEG[proc]=dict_converter_NEG[proc].GetHistDictX()
        dict_hy_Presel_NEG[proc]=dict_converter_NEG[proc].GetHistDictY()        

        print(year,algo,wp,flav)
        
        outdirname="output/"+ana+"/"+year+"/"+algo+"__"+wp+"__"+flav+"/"+proc+"__comparePOSNEG"
        print('--dict_h2_Presel_NEG')
        print(sorted(dict_h2_Presel_NEG))
        print('--dict_h2_Presel_POS')
        print(sorted(dict_h2_Presel_POS))
        for xdistname in dict_hx_Presel_POS[proc]:
            #def Compare_TH1(list_h,list_name,savename,savedir)
            
            Compare_TH1(
                [dict_hx_Presel_POS[proc][xdistname], dict_hx_Presel_NEG[proc][xdistname]],
                ["Events with weight>0", "Events with weight<0"],
                proc+"__"+xdistname,
                outdirname
            )

        for ydistname in dict_hy_Presel_POS[proc]:
            #def Compare_TH1(list_h,list_name,savename,savedir)
            Compare_TH1(
                [dict_hy_Presel_POS[proc][ydistname], dict_hy_Presel_NEG[proc][ydistname]],
                ["Events with weight>0", "Events with weight<0"],
                proc+"__"+ydistname,
                outdirname
            )



    
def Run(ana,year,algo,wp,flav,procs):


    year=str(year)

    fpath_default="../"+year+"/BTag/MeasureJetTaggingEfficiency_TTLL_TTLJ_hadded.root"
    h2_defualt=GetEffTH2(fpath_default,year,algo,wp,flav)
    
    ##----Get defualt h2's h1s

    converter_default=TH2ToTH1_Converter(h2_defualt,"|eta|","pT")
    converter_default.Run()
    dict_hx_default=converter_default.GetHistDictX()
    dict_hy_default=converter_default.GetHistDictY()



    dict_converter={}
    dict_h2_Presel={}
    dict_hx_Presel={}
    dict_hy_Presel={}
    for proc in procs:
        this_fpath="../"+year+"/BTag/"+ana+"_"+proc+".root"
        if not os.path.isfile(this_fpath) : continue
        dict_h2_Presel[proc]=GetEffTH2(this_fpath,year,algo,wp,flav)
        dict_converter[proc]=TH2ToTH1_Converter(dict_h2_Presel[proc],"|eta|","pT")
        dict_converter[proc].Run()
        dict_hx_Presel[proc]=dict_converter[proc].GetHistDictX()
        dict_hy_Presel[proc]=dict_converter[proc].GetHistDictY()


        outdirname="output/"+ana+"/"+year+"/"+algo+"__"+wp+"__"+flav+"/"+proc
        
        for xdistname in dict_hx_Presel[proc]:
            
            #def Compare_TH1(list_h,list_name,savename,savedir)
            
            Compare_TH1(
                [dict_hx_default[xdistname], dict_hx_Presel[proc][xdistname]],
                ["default mc eff", ana+","+proc+" Eff"],
                proc+"__"+xdistname,
                outdirname
            )

        for ydistname in dict_hy_Presel[proc]:
            #def Compare_TH1(list_h,list_name,savename,savedir)            
            Compare_TH1(
                [dict_hy_default[ydistname], dict_hy_Presel[proc][ydistname]],
                ["default mc eff", ana+","+proc+" Eff"],
                proc+"__"+ydistname,
                outdirname
            )


def RunAllHadd(ana,year,algo,wp,flav,procs):


    year=str(year)

    #fpath_default="../"+year+"/BTag/MeasureJetTaggingEfficiency_TTLL_TTLJ_hadded.root"
    fpath_default="../"+year+"/BTag/"+ana+"_HADDED.root"
    h2_defualt=GetEffTH2(fpath_default,year,algo,wp,flav)
    
    ##----Get defualt h2's h1s

    converter_default=TH2ToTH1_Converter(h2_defualt,"|eta|","pT")
    converter_default.Run()
    dict_hx_default=converter_default.GetHistDictX()
    dict_hy_default=converter_default.GetHistDictY()



    dict_converter={}
    dict_h2_Presel={}
    dict_hx_Presel={}
    dict_hy_Presel={}
    for proc in procs:
        this_fpath="../"+year+"/BTag/"+ana+"_"+proc+".root"
        if not os.path.isfile(this_fpath) : continue
        dict_h2_Presel[proc]=GetEffTH2(this_fpath,year,algo,wp,flav)
        dict_converter[proc]=TH2ToTH1_Converter(dict_h2_Presel[proc],"|eta|","pT")
        dict_converter[proc].Run()
        dict_hx_Presel[proc]=dict_converter[proc].GetHistDictX()
        dict_hy_Presel[proc]=dict_converter[proc].GetHistDictY()


        outdirname="output/"+ana+"/"+year+"/"+algo+"__"+wp+"__"+flav+"/"+proc+"_CompareWithAllHadd"
        
        for xdistname in dict_hx_Presel[proc]:
            
            #def Compare_TH1(list_h,list_name,savename,savedir)
            
            Compare_TH1(
                [dict_hx_default[xdistname], dict_hx_Presel[proc][xdistname]],
                [ana+" all mc eff", ana+","+proc+" Eff"],
                proc+"__"+xdistname,
                outdirname
            )

        for ydistname in dict_hy_Presel[proc]:
            #def Compare_TH1(list_h,list_name,savename,savedir)            
            Compare_TH1(
                [dict_hy_default[ydistname], dict_hy_Presel[proc][ydistname]],
                [ana+" all mc eff", ana+","+proc+" Eff"],
                proc+"__"+ydistname,
                outdirname
            )            
if __name__ == '__main__':
    #analist=["Preselection_To_bjet","TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch"]
    #analist=['PreselectionAnalyzer']
    analist=["TTsemiLepChargeScoreEfficiencyMeasurement"]
    #def Run(ana,year,algo,wp,flav):
    list_year=["2016preVFP","2016postVFP","2017","2018"]
    list_algo=["DeepJet"]
    list_wp=["Tight"]
    list_flav=["B","C","Light"]

    procs=["TTLL_powheg","TTLJ_powheg","TTJJ_powheg","DYJetsToMuMu_MiNNLO","DYJetsToEE_MiNNLO","DYJetsToTauTau_MiNNLO","WJets_MG"]+\
        ["SingleTop_sch_Lep","SingleTop_tch_top_Incl","SingleTop_tch_antitop_Incl","SingleTop_tW_antitop_NoFullyHad","SingleTop_tW_top_NoFullyHad"]+\
        ["WW_pythia","WZ_pythia","ZZ_pythia"]
    #procs=["HADDED"]
    for ana in analist:
        for year in list_year:
            for algo in list_algo:
                for wp in list_wp:
                    for flav in list_flav:
                        Run(ana,year,algo,wp,flav,procs)
                        RunAllHadd(ana,year,algo,wp,flav,procs)
                        #RunComparePOSNEG(ana,year,algo,wp,flav,procs)
