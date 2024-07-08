import os
SKFlat_WD=os.getenv("SKFlat_WD")

class modify:
    def __init__(self,nlayer=3,nnode=50,batchsize=100,dropout=0.1):
        self.nlayer=str(nlayer)
        self.nnode=str(nnode)
        self.batchsize=str(batchsize)
        self.dropout=str(dropout)

    def SetXMLPath(self,version,year,obj):
        self.version=str(version)
        self.year=str(year)
        self.obj=str(obj)
        self.xmldir=year+"/TMVA/ChargeScore/v"+version+"/"+obj+"/"
        self.xml=self.xmldir+"/"+obj+year+"__"+self.nlayer+"__"+self.nnode+"__"+self.batchsize+"__"+self.dropout+"_DNN.weights.xml"
        

    def FixPath(self):
        print self.xml
        UseBackup=False
        if os.path.isfile(self.xml+"_backup"):
            UseBackup=True

        if UseBackup:
            f=open(self.xml+"_backup","r")
        else:
            f=open(self.xml,"r")
        fnew=open(self.xml+"_new","w")
        lines=f.readlines()
        for line in lines:
            if '<Option name="FilenameTrainedModel"' in line:
                line='    <Option name="FilenameTrainedModel" modified="No">'+SKFlat_WD+"/data/Run2UltraLegacy_v3/"+self.xmldir+"/TrainedModel_DNN.h5</Option>\n"
            if "<Spectator" in line or " </Spectator" in line:
                continue
            fnew.write(line)

        f.close()
        fnew.close()
        if not UseBackup :os.system("cp "+self.xml+" "+self.xml+"_backup")
        os.system("mv "+self.xml+"_new "+self.xml)
#objs=["muon","electron","jet"]
objs=["muon","electron"]
version="2405.4"
years=["2016preVFP","2016postVFP","2017","2018"]
#${YEAR}/TMVA/ChargeScore/v${VERSION}/${OBJ}

dict_version={
    "2405.2":[3,50,100,0.1],
    "2405.4":[5,64,500,0.2],
}

nlayer=dict_version[version][0]
nnode=dict_version[version][1]
batchsize=dict_version[version][2]
dropout=dict_version[version][3]

for year in years:
    for obj in objs:
        job=modify(nlayer,nnode,batchsize,dropout)
        job.SetXMLPath(version,year,obj)
        job.FixPath()
