import os
SKFlat_WD=os.getenv("SKFlat_WD")


class modelpath:
    def __init__(self):
        self.UseNtrial=1
        self.version="2405.4.3"
        self.Ana="EEMu_MuMuE_Method"
        self.suffix_WORKDIR=""
        self.UseNtrial=1
        self.TMVADIR="/data6/Users/jhchoi/TMVA/TMVA_TOOL/ws/TTSemiLepJetAssignment_ProduceTrainingTree/"
         
    def SetYear(self,year):
        self.year=str(year)
    def SetVersion(self,version):
        self.version=version
    def SetAna(self,ana):
        self.Ana=ana
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
        self.WORKDIR=self.TMVADIR+"/WORKDIR_TTSemiLepJetAssignment"+self.suffix_WORKDIR+"/"+self.version+"/"+self.Ana+"/"+self.year+"/"+self.year+"__"+self.nlayer+"__"+self.nnode+"__"+self.batchsize+"__"+self.dropout+"/Trf_"+self.GetTransformForPath()+"/"+self.index

    def GetWorkdirPath(self):
        return self.WORKDIR

    def CpModel(self):
        self.destination=self.year+"/TMVA/TTSemilepJetAssignment/v"+self.version+"/"
        os.system("mkdir -p "+self.destination)
        self.target=self.WORKDIR+"/*"
        self.target2=self.WORKDIR+"/"+self.year+"__"+self.nlayer+"__"+self.nnode+"__"+self.batchsize+"__"+self.dropout+"/weights/*"
        print "destination=",self.destination
        print "target=",self.target
        print "target2=",self.target2


        os.system("cp "+self.target+" "+self.destination)
        os.system("cp "+self.target2+" "+self.destination)

        self.ModifyXML()

    def ModifyXML(self):
        ##
        self.xmlpath=self.destination+"/"+self.year+"__"+self.nlayer+"__"+self.nnode+"__"+self.batchsize+"__"+self.dropout+"_DNN.weights.xml"
        os.system("cp "+self.xmlpath+" "+self.xmlpath+"_backup")
        PrefixToFindLine='<Option name="FilenameTrainedModel"'


        if os.path.isfile(self.xmlpath+"_backup"):
            f=open(self.xmlpath+"_backup","r")
        else:
            f=open(self.xmlpath,"r")
        lines=f.readlines()
        
        fnew=open(self.xmlpath+"_new","w")
        for line in lines:
            if PrefixToFindLine in line:
                line='    <Option name="FilenameTrainedModel" modified="No">'+SKFlat_WD+"/data/Run2UltraLegacy_v3/"+self.destination+"/TrainedModel_DNN.h5</Option>\n"
            if "<Spectator" in line or " </Spectator" in line:
                continue ### skip spectator
            fnew.write(line)


        f.close()
        fnew.close()
        os.system("mv "+self.xmlpath+"_new "+self.xmlpath)
if __name__ == '__main__':
    version="1.0"
    ana="TTSemiLepJetAssignment_ProduceTrainingTree"
    years=["2016preVFP","2016postVFP","2017","2018"]
    dict_model={
        "2016preVFP":[5, 128, 500, 0.2, 'G',0],
        "2016postVFP":[5, 128, 500, 0.2, 'G',19],

        "2017":[5, 128, 500, 0.2, 'G',0],

        "2018":[5, 128, 500, 0.2, 'G',1]
    }
    

    for year in dict_model:
        print "---",year,"---"
        this_model=modelpath()
        this_model.SetYear(year)
        this_model.SetVersion(version)
        this_model.SetAna(ana)
        params=dict_model[year]
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
        
