import ROOT
import os
from math import sqrt
from TH2ToTH1_Converter import TH2ToTH1_Converter
from copy import deepcopy

def GetEffTH2(filepath,year,bchargeid,flav,suffix=""):
    year=str(year)
    nume_name="Jet_"+year+"_"+bchargeid+"_eff_"+flav+"_num"+suffix
    deno_name="Jet_"+year+"_eff_"+flav+"_denom"+suffix
    print('nume_name=',nume_name)
    print('deno_name=',deno_name)
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
        print(list_name[i],this_max)
        if this_max > ymax : ymax=this_max
        this_min=_h.GetMinimum()
        if this_min < ymin : ymin=this_min
    for i,_h in enumerate(list_h):
        this_option=list_option[i]        
        this_name=list_name[i]
        #this_h=_h.Clone()
        #this_h.SetDirectory(0)
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


def RunAllHadd(ana,year,bchargeid,procs,suffix=""):


    year=str(year)

    fpath_default="../"+year+"/bChargeTagID/"+ana+"_HADDED.root"
    
    h2_defualt_bminus=GetEffTH2(fpath_default,year,bchargeid,'bminus',suffix)
    h2_defualt_bplus=GetEffTH2(fpath_default,year,bchargeid,'bplus',suffix)
    
    ##----Get defualt h2's h1s

    converter_default_bminus=TH2ToTH1_Converter(h2_defualt_bminus,"|eta|","pT")
    converter_default_bminus.Run()
    dict_hx_default_bminus=converter_default_bminus.GetHistDictX()
    dict_hy_default_bminus=converter_default_bminus.GetHistDictY()

    converter_default_bplus=TH2ToTH1_Converter(h2_defualt_bplus,"|eta|","pT")
    converter_default_bplus.Run()
    dict_hx_default_bplus=converter_default_bplus.GetHistDictX()
    dict_hy_default_bplus=converter_default_bplus.GetHistDictY()

    


    dict_converter_bminus={}
    dict_h2_Presel_bminus={}
    dict_hx_Presel_bminus={}
    dict_hy_Presel_bminus={}
    
    dict_converter_bplus={}
    dict_h2_Presel_bplus={}
    dict_hx_Presel_bplus={}
    dict_hy_Presel_bplus={}
    
    for proc in procs:
        this_fpath="../"+year+"/bChargeTagID/"+ana+"_"+proc+".root"
        if not os.path.isfile(this_fpath) : continue
        dict_h2_Presel_bminus[proc]=GetEffTH2(this_fpath,year,bchargeid,'bminus',suffix)
        dict_converter_bminus[proc]=TH2ToTH1_Converter(dict_h2_Presel_bminus[proc],"|eta|","pT")
        dict_converter_bminus[proc].Run()
        dict_hx_Presel_bminus[proc]=dict_converter_bminus[proc].GetHistDictX()
        dict_hy_Presel_bminus[proc]=dict_converter_bminus[proc].GetHistDictY()

        dict_h2_Presel_bplus[proc]=GetEffTH2(this_fpath,year,bchargeid,'bplus',suffix)
        dict_converter_bplus[proc]=TH2ToTH1_Converter(dict_h2_Presel_bplus[proc],"|eta|","pT")
        dict_converter_bplus[proc].Run()
        dict_hx_Presel_bplus[proc]=dict_converter_bplus[proc].GetHistDictX()
        dict_hy_Presel_bplus[proc]=dict_converter_bplus[proc].GetHistDictY()        


        outdirname="output/"+ana+"/"+year+"/"+bchargeid+"/"+proc+"_CompareWithAllHadd"
        
        for xdistname in dict_hx_Presel_bplus[proc]:
            
            #def Compare_TH1(list_h,list_name,savename,savedir)
            
            Compare_TH1(
                [deepcopy(dict_hx_default_bminus[xdistname]), deepcopy(dict_hx_default_bplus[xdistname]), deepcopy(dict_hx_Presel_bminus[proc][xdistname]),deepcopy(dict_hx_Presel_bplus[proc][xdistname])],
                ["all mc b^{-}", "all mc b^{+}",proc+" b^{-}",proc+" b^{+}"],
                proc+"__"+xdistname,
                outdirname
            )

        for ydistname in dict_hy_Presel_bplus[proc]:
            #def Compare_TH1(list_h,list_name,savename,savedir)            
            Compare_TH1(
                [deepcopy(dict_hy_default_bminus[ydistname]), deepcopy(dict_hy_default_bplus[ydistname]), deepcopy(dict_hy_Presel_bminus[proc][ydistname]),deepcopy(dict_hy_Presel_bplus[proc][ydistname])],
                ["all mc b^{-}", "all mc b^{+}",proc+" b^{-}",proc+" b^{+}"],
                proc+"__"+ydistname,
                outdirname
            )            
if __name__ == '__main__':

    analist=["TTsemiLepChargeScoreEfficiencyMeasurement"]
    list_year=["2016preVFP","2016postVFP","2017","2018"]
    #list_year=["2016preVFP"]
    list_sltid=['Has_muH',"Has_muL","Has_eH","Has_eL"]
    procs=["TTLL_powheg","TTLJ_powheg","TTJJ_powheg","DYJetsToMuMu_MiNNLO","DYJetsToEE_MiNNLO","DYJetsToTauTau_MiNNLO","WJets_MG"]+\
        ["SingleTop_sch_Lep","SingleTop_tch_top_Incl","SingleTop_tch_antitop_Incl","SingleTop_tW_antitop_NoFullyHad","SingleTop_tW_top_NoFullyHad"]+\
        ["WW_pythia","WZ_pythia","ZZ_pythia"]

    for ana in analist:
        for year in list_year:
    
            for sltid in list_sltid:
                RunAllHadd(ana,year,sltid,procs)
            RunAllHadd(ana,year,'jH',procs,'__NoSL')

