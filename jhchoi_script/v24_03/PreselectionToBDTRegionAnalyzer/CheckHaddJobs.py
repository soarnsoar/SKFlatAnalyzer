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
        lines=f.readlines()
        f.close()
        for line in lines:
            if 'RunDir = ' in line:
                this_rundir=line.split('RunDir = ')[1].strip()
                parent_path = os.path.dirname(this_rundir.rstrip('/')) + '/'
                #print('parent_path=',parent_path)
                self.list_rundir.append(parent_path)

        print(self.list_rundir)
    def Get_WORKDIR_HADD(self):
        self.list_hadddir=[]
        for this_rundir in self.list_rundir:
            #print(this_rundir+"/*/WORKDIR_HADD*/*/")
            self.list_hadddir+= glob.glob(this_rundir+"/*/WORKDIR_HADD*/*/")
        #print("len(self.list_hadddir)=",len(self.list_hadddir))
    def PrintFile(self,thispath):
        #print("->print : ",thispath)
        f=open(thispath)
        lines=f.readlines()
        f.close()
        for line in lines:
            ##--exception
            if "IMPORTANT: Setting CMSSW environment to use 'x86-64-v2' target." in line : continue
            print('['+thispath+']',line)
            
    def CheckErrFiles(self):
        for hadddir in self.list_hadddir:
            this_errpath=hadddir+"/run.err"
            if os.path.isfile(this_errpath):
                self.PrintFile(this_errpath)
            this_jidpath=hadddir+"/run.jid"
            if os.path.isfile(this_jidpath):
                self.PrintFile(this_jidpath)
if __name__ == "__main__":
    import sys
    thislog=sys.argv[1]
    thisjob=HaddJobManager(thislog)
    thisjob.GetRunDir()
    thisjob.Get_WORKDIR_HADD()
    thisjob.CheckErrFiles()
