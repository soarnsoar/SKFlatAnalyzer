import os



class modelpath:
    def __init__(self):
        self.UseNtrial=1
        self.version="2405.4.3"
        self.Ana="EEMu_MuMuE_Method"
        self.suffix_WORKDIR=""
        self.UseNtrial=1
        self.TMVADIR="/data6/Users/jhchoi/TMVA/TMVA_TOOL/ws/"
         
    def SetYear(self,year):
        self.year=str(year)
    def SetVersion(self,version):
        self.version=version
    def SetAna(self,ana):
        self.Ana=ana
    def SetObj(self,obj):
        self.obj=obj
    def SetNlayer(self,nlayer):
        self.nlayer=str(nlayer)
    def SetNnode(self,nnode):
        self.nnode=str(nnode)
    def SetBatchsize(self,batchsize):
        self.batchsize=str(batchsize)
    def SetDropout(self,dropout):
        self.dropout=str(dropout)
    def SetTransform(self,transform):
        self.transform=transform
    def SetIndex(self,index):
        self.index=str(index)
    def GetTransformForPath(self):
        return self.transform.replace(",","")


    def SetWorkdirPath(self):
        if self.UseNtrial:
            self.suffix_WORKDIR="_ntrial"
        self.WORKDIR=self.TMVADIR+"/WORKDIR"+self.suffix_WORKDIR+"/"+self.version+"/"+self.Ana+"/"+self.year+"/"+self.obj+"/"+self.obj+self.year+"__"+self.nlayer+"__"+self.nnode+"__"+self.batchsize+"__"+self.dropout+"/Trf_"+self.GetTransformForPath()+"/"+self.index

    def GetWorkdirPath(self):
        return self.WORKDIR

    def CpModel(self):
        destination=self.year+"/TMVA/ChargeScore/v"+self.version+"/"+self.obj+"/"
        os.system("mkdir -p "+destination)
        target=self.WORKDIR+"/*"
        target2=self.WORKDIR+"/"+self.obj+self.year+"__"+self.nlayer+"__"+self.nnode+"__"+self.batchsize+"__"+self.dropout+"/weights/*"
        print "destination=",destination
        print "target=",target
        print "target2=",target2


        os.system("cp "+target+" "+destination)
        os.system("cp "+target2+" "+destination)

if __name__ == '__main__':
    version="2405.4.3"
    ana="EEMu_MuMuE_Method"
    years=["2016preVFP","2016postVFP","2017","2018"]
    dict_obj={
        "2016preVFP":{
            "muon":[3,48,1100,0.1,"G",39],
            "electron":[3,48,600,0.1,"G",4],
            "jet":[5,64,1000,0.2,"G",53],
        },
        "2016postVFP":{
            "muon":[3,48,1100,0.1,"G",64],
            "electron":[3,48,600,0.1,"G",51],
            "jet":[5,64,1000,0.2,"G",74],
        },

        "2017":{
            "muon":[3,48,1100,0.1,"G",49],
            "electron":[3,48,600,0.1,"G",27],
            "jet":[5,64,1000,0.2,"G",82],
        },

        "2018":{
            "muon":[3,48,1100,0.1,"G",65],
            "electron":[3,48,600,0.1,"G",34],
            "jet":[5,64,1000,0.2,"G",23],
        },


    }
    

    for year in dict_obj:
        print "---",year,"---"
        for obj in dict_obj[year]:
            this_model=modelpath()
            this_model.SetYear(year)
            this_model.SetVersion(version)
            this_model.SetAna(ana)
            this_model.SetObj(obj)


            params=dict_obj[year][obj]
            nlayer=params[0]
            nnode=params[1]
            batchsize=params[2]
            dropout=params[3]
            transform=params[4]
            index=params[5]

            this_model.SetNlayer(nlayer)
            this_model.SetNnode(nnode)
            this_model.SetBatchsize(batchsize)
            this_model.SetDropout(dropout)
            this_model.SetTransform(transform)
            this_model.SetIndex(index)
            
            this_model.SetWorkdirPath()
            this_model.CpModel()

            print ""
