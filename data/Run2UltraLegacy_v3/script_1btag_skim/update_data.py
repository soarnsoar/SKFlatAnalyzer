import glob
import os
DATADIR=os.getenv('DATA_DIR')
def write_txtfile(txtpath,filelist):
    f=open(txtpath,'w')
    for this_path in filelist:
        f.write(this_path+"\n")
    f.close()
def MakeSmapleInfo(YEAR,SKIM,PD):
    #YEAR='2016preVFP'
    #SKIM='SkimTree_SingleLepton_1DeepJetTightWP'
    #PD='SingleElectron'
    SKFLATDIR='/gv0/DATA/SKFlat/Run2UltraLegacy_v3/'

    SKIMDIR=SKFLATDIR+"/"+YEAR+"/DATA_"+SKIM+"/"+PD
    
    list_period=glob.glob(SKIMDIR+"/*/")
    #print(list_period)
    for period in list_period:
        suffix=period.replace(SKIMDIR+"/period",'').replace('/','')
        #print(suffix)
        txtname=SKIM+"_"+PD+"_"+suffix+".txt"
        #print(txtname)
        txtpath=DATADIR+"/"+YEAR+"/Sample/ForSNU/"+txtname
        #print(txtpath)
        #2018/DATA/EGamma/periodA/220618_055259/0000
        search_prod_date=SKIMDIR+"/period"+suffix+"/*/"
        #print(search_prod_date)
        nprod=len(glob.glob(search_prod_date))
        if nprod>1:
            print("[!] more than one prod dir. please select one of them.")
            print(SKIMDIR+"/"+period)
            continue
        elif nprod==0:
            print("[!] no prod dir")
            print(SKIMDIR+"/"+period)
            continue
        search_filelist1=SKIMDIR+"/period"+suffix+"/*/*/*.root"
        search_filelist2=SKIMDIR+"/period"+suffix+"/*/*.root"
        this_filelist=glob.glob(search_filelist1) + glob.glob(search_filelist2)
        print(SKIMDIR,suffix)
        print('nfiles=',len(this_filelist))
        #print('1stfile=',this_filelist[0])
        print(txtpath)
        write_txtfile(txtpath,this_filelist)
def RunSingleLep():
    dict_YEAR_PD={
        '2016preVFP':['SingleElectron','SingleMuon'],
        '2016postVFP':['SingleElectron','SingleMuon'],
        '2017':['SingleElectron','SingleMuon'],
        '2018':['SingleMuon','EGamma'],
    }
    SKIM='SkimTree_SingleLepton_1DeepJetTightWP'
    for YEAR in dict_YEAR_PD:
        for PD in dict_YEAR_PD[YEAR]:            
            MakeSmapleInfo(YEAR,SKIM,PD)

def RunDiLep():
    dict_YEAR_PD={
        '2016preVFP':['DoubleEG','DoubleMuon'],
        '2016postVFP':['DoubleEG','DoubleMuon'],
        '2017':['DoubleEG','DoubleMuon'],
        '2018':['DoubleMuon','EGamma'],
    }
    SKIM='SkimTree_Dilepton_1DeepJetTightWP'
    for YEAR in dict_YEAR_PD:
        for PD in dict_YEAR_PD[YEAR]:            
            MakeSmapleInfo(YEAR,SKIM,PD)            
if __name__ == '__main__' :

    #RunSingleLep()
    RunDiLep()
