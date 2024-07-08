import os
SKFlat_WD=os.getenv("SKFlat_WD")
import ROOT
class efftool:
    def __init__(self,nlayer=3,nnode=50,batchsize=100,dropout=0.1):
        self.nlayer=str(nlayer)
        self.nnode=str(nnode)
        self.batchsize=str(batchsize)
        self.dropout=str(dropout)

        self.FromCutToRight=True
        self.effrun=False
        self.stobrun=False
    def SetFromLeftToCut(self):
        self.FromCutToRight=False
    def SetFromCutToRight():
        self.FromCutToRight=True
    def SetRootFile(self,version,year,obj):
        self.version=str(version)
        self.year=str(year)
        self.obj=str(obj)
        self.dir=year+"/TMVA/ChargeScore/v"+version+"/"+obj+"/"
        self.name=obj+year+"__"+self.nlayer+"__"+self.nnode+"__"+self.batchsize+"__"+self.dropout
        self.rf=self.dir+"/"+self.name+".root"
        self.histopath_S= self.name+"/Method_DNN/DNN/MVA_DNN_S_high"#muon2017__3__50__100__0.1/Method_DNN/DNN/MVA_DNN_S_high
        self.histopath_B= self.name+"/Method_DNN/DNN/MVA_DNN_B_high"#muon2017__3__50__100__0.1/Method_DNN/DNN/MVA_DNN_S_high
    def SetSigEff(self,_sigeff):
        self.sigeff=_sigeff
        self.effrun=1
    def SetBkgEff(self,_bkgeff):
        self.bkgeff=_bkgeff
    def SetStoB(self,_stob):
        self.stob=_stob
        self.stobrun=1
    def FindCut(self):
        ##integral direction
        print "self.FromCutToRight>>>",self.FromCutToRight
        tfile=ROOT.TFile.Open(self.rf)
        self.h_s=tfile.Get(self.histopath_S)
        self.h_b=tfile.Get(self.histopath_B)
        self.Entry=self.h_s.GetEntries()+self.h_b.GetEntries()
        
        CutToFind=[]
        IsFound=False
        N=self.h_s.GetNbinsX()+2
        precision=0.0005
        
        if self.FromCutToRight:
            for i in range(N):
                this_sigeff=self.h_s.Integral(i,N)/self.h_s.Integral()
                this_bkgeff=self.h_b.Integral(i,N)/self.h_b.Integral()

                stob=0
                if this_bkgeff!=0 : stob=this_sigeff/this_bkgeff
                #if (self.effrun and abs(this_sigeff- self.sigeff)<precision) or (self.stobrun and stob > self.stob): ##First Found
                if (this_sigeff > self.sigeff) and (stob > self.stob): ##First Found
                    CutToFind.append(self.h_s.GetBinLowEdge(i))
                    print self.h_s.GetBinLowEdge(i)
                    print "this_sigeff=",this_sigeff
                    print "this_bkgeff=",this_bkgeff
                    IsFound=1
                    break
        else:
            for i in range(N):
                j=N-i-1
                this_bkgeff=1.-self.h_s.Integral(j,N)/self.h_s.Integral()
                this_sigeff=1.-self.h_b.Integral(j,N)/self.h_b.Integral()
                
                stob=0
                if this_bkgeff!=0 : stob=this_sigeff/this_bkgeff
                if (this_sigeff > self.sigeff) and (stob > self.stob): ##First Found
                    CutToFind.append(self.h_s.GetBinLowEdge(j))
                    print self.h_s.GetBinLowEdge(j)
                    print "this_sigeff=",this_sigeff
                    print "this_bkgeff=",this_bkgeff
                    IsFound=1
                    break

        tfile.Close()
        if not IsFound : print "[FailToFind Cut!!!!!]"
        return CutToFind
objs=["muon","electron","jet"]
version="2405.2"
years=["2016preVFP","2016postVFP","2017","2018"]
#${YEAR}/TMVA/ChargeScore/v${VERSION}/${OBJ}

#dict_effcut_stobcut={}
#dict_effcut_stobcut["muon"]={"eff":0.3 , "stob":4 }
#dict_effcut_stobcut["electron"]={"eff":0.3 , "stob":3 }
#dict_effcut_stobcut["jet"]={"eff":0.05 , "stob":2.3 }

#dict_effcut_stobcut_opp={}
#dict_effcut_stobcut_opp["muon"]={"eff":0.01 , "stob":4 }
#dict_effcut_stobcut_opp["electron"]={"eff":0.01 , "stob":3 }
#dict_effcut_stobcut_opp["jet"]={"eff":0.001 , "stob":2.3 }

dict_stobcut={##Signal To Bkg
    "2016preVFP":{
        "muon":4,
        "electron":2.8,
        "jet":2,
    },
    "2016postVFP":{
        "muon":4,
        "electron":3,
        "jet":2,
    },
    "2017":{
        "muon":4,
        "electron":3,
        "jet":2,
    },
    "2018":{
        "muon":4,
        "electron":3,
        "jet":2,
    },
}


dict_N={}
for FromCutToRight in [True, False]:
    for year in years:
        dict_N[year]={}
        for obj in objs:

            print "----"
            print year,obj
            job=efftool()
            job.SetRootFile(version,year,obj)
            if FromCutToRight:
                effcut=0.05#dict_effcut_stobcut[obj]["eff"]
                stobcut=dict_stobcut[year][obj]#dict_effcut_stobcut[obj]["stob"]
            else:
                job.SetFromLeftToCut()
                effcut=0.005#dict_effcut_stobcut_opp[obj]["eff"]
                stobcut=dict_stobcut[year][obj]#dict_effcut_stobcut_opp[obj]["stob"]
            job.SetSigEff(effcut)
            job.SetStoB(stobcut)
            job.FindCut()
            dict_N[year][obj]=job.Entry
            


    print "<",year,">"
    print "MuonEff_Presel=",dict_N[year]["muon"]/dict_N[year]["jet"]
    print "ElectronEff_Presel=",dict_N[year]["electron"]/dict_N[year]["jet"]
