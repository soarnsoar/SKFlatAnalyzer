#!/usr/bin/env python2.7
import optparse
from ExportShellCondorSetup_tamsa import Export
from glob import glob
from collections import OrderedDict
import os
from math import sqrt
class hadd_submitter:
    def __init__(self,jobname):
        self.jobname=jobname
    def GetFileList(self,search_phrase):
        print "search_phrase=",search_phrase
        searches=search_phrase.split()
        self.filelist=[]
        for search in searches:
            self.filelist += glob(search)

        print "[filelist]"
        print self.filelist

        this_N=len(self.filelist)
        print "automatically set njobs--->",int(sqrt(this_N))
        self.SetNJobs(int(sqrt(this_N)))
        self.SetFileGroups()
    def SetNJobs(self,N):
        self.N=int(N)


    def SetFileGroups(self):
        self.dict_group=OrderedDict()
        for j in range(self.N):
            self.dict_group[j]=[]
        for i,f in enumerate(self.filelist):
            this_j= i%self.N
            self.dict_group[this_j].append(f)

    def GetTempOutDir(self):
        outdir="tmp__"+self.jobname
        return outdir
    def MakeCommandGroupIdx(self,j):

        outdir=self.GetTempOutDir()
        command="mkdir -p "+outdir
        outname=outdir+"/__hadd__"+str(j)+".root"
        arg_inputs = " ".join(self.dict_group[j])
        
        nf=len(self.dict_group[j])
        if nf ==1 :
            command+="&&cp "+outname+" "+arg_inputs

        else:
            command+="&&hadd -f "+outname+" "+arg_inputs

        return command

    def GetMaxFileSize(self,_list):
        maxsize=-1.
        for f in _list:
            this_size=os.path.getsize(f)
            if this_size > maxsize : maxsize=this_size
        maxsize= maxsize/1024./1024.
        return maxsize

    def GetMemoryForFileList(self,_list):
        nfiles=len(_list)
        this_maxsize=self.GetMaxFileSize(_list)
        _req_memory=int(this_maxsize*nfiles)
        if _req_memory < 13000:
            _req_memory=13000
        elif _req_memory<30000:
            _req_memory=30000
        if _req_memory > 200000 : _req_memory=200000
        return _req_memory
    
    def MakeJobGroupIdx(self,j):
        command="cd "+os.getcwd()
        command+="&&"+ self.MakeCommandGroupIdx(j)
        WORKDIR="WORKDIR_HADD_"+self.jobname+"/group_"+str(j)
        submit=0
        jobname=WORKDIR
        memory=self.GetMemoryForFileList(self.dict_group[j])
        nretry=3
        #ncpu=len(self.dict_group[j])
        ncpu=1
        Export(WORKDIR,command,jobname,submit,ncpu,memory,nretry)

    def MakeJobFinalHadd(self,outputname,FinalOutputPathToMove):
        command="cd "+os.getcwd()
        command+="&&hadd -f "+outputname+" "+self.GetTempOutDir()+"/*.root"
        if FinalOutputPathToMove:
            command+="&&mv "+outputname+" "+FinalOutputPathToMove
        WORKDIR="WORKDIR_HADD_"+self.jobname+"/FINAL"
        submit=0
        jobname=WORKDIR
        memory=self.GetMemoryForFileList(glob(self.GetTempOutDir()+"/*.root"))
        nretry=3
        ncpu=1
        Export(WORKDIR,command,jobname,submit,ncpu,memory,nretry)


    def MakeDAG(self):
        f=open("hadd_manager_"+self.jobname+".dag","w")
        arg_parent=""
        for j in range(self.N):
            f.write("JOB J"+str(j)+" WORKDIR_HADD_"+self.jobname+"/group_"+str(j)+"/run.jds\n")
            arg_parent+=" J"+str(j)

        f.write("JOB FIN WORKDIR_HADD_"+self.jobname+"/FINAL/run.jds\n")


        f.write("PARENT "+arg_parent+" CHILD FIN")
        f.close()


    def MakeJobsAll(self,FinalOutputPathToMove):
        for j in range(self.N):
            self.MakeJobGroupIdx(j)
        self.MakeJobFinalHadd(self.jobname+".root",FinalOutputPathToMove)
        self.MakeDAG()
if __name__ == '__main__':
   usage = 'usage: %prog [options]'
   parser = optparse.OptionParser(usage)
   parser.add_option("-n","--jobname",   dest="jobname", help="jobname")
   parser.add_option("-i","--inputs",   dest="inputs", help="inputs")
   parser.add_option("-f","--finalpath",   dest="finalpath", help="inputs")
   parser.add_option("-s","--submit",   dest="submit",action="store_true", help="submit",default=False)
   (options, args) = parser.parse_args()
   

   jobname=options.jobname
   inputs=options.inputs
   finalpath=options.finalpath
   submit=options.submit
   
   this_hadd=hadd_submitter(jobname)
   this_hadd.GetFileList(inputs)
   this_hadd.MakeJobsAll(finalpath)
   if submit:
       submit_command="condor_submit_dag "+"hadd_manager_"+this_hadd.jobname+".dag"
       print submit_command
       os.system(submit_command)
