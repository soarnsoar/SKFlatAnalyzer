import os
import glob
shlist=glob.glob("201*/*.sh")

for sh in shlist:
    UseBackup=os.path.isfile(sh+"_backup")
    f=open(sh,"r")
    fnew=open(sh+"_new","w")
    lines=f.readlines()
    for line in lines:
        line=line.replace("bbbarAsymMeasurement","TrueBJetAnalyzer")
        fnew.write(line)

    f.close()
    fnew.close()
    os.system("mv "+sh+" "+sh+"_backup")
    os.system("mv "+sh+"_new "+sh)
