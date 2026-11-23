import os
import glob

class HaddJobManager:
    def __init__(self,logpath):
        self.logpath=logpath
    def GetRunDir(self):
        ##example
        #/cms_scratch/jhchoi/SKFlatRunlog//2026_11_23_171049__893__PreselectionToBDTRegionAnalyzer__Era2016preVFP__SkimTree_Dilepton_1DeepJetTightWP__runSys__jetpuid_loose__use_beffasym__newlepveto__bdt2608.2__bdtcut__apply_chargeid_corrs__jsource__KISTI/WW_pythia/
        self.list_rundir=[]
        f=open(self.logpath)
        lines=f.Readlines()
        for line in lines:
            if 'RunDir = ' in line:
                this_rundir=line.split('RunDir = ')[1]
                parent_path = os.path.dirname(this_rundir.rstrip('/')) + '/'
                self.list_rundir.append(parent_path)
    def Get_WORKDIR_HADD(self):
        self.list_hadddir=[]
        for this_rundir in self.list_rundir:
            self.list_hadddir+=glob.glob(this_rundir+"/*/WORKDIR_HADD*/*/")
        
                
