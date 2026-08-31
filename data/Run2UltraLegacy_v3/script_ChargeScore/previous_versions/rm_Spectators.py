import os
SKFlat_WD=os.getenv("SKFlat_WD")

def FixPath(xmlpath):
    #UseBackup=False
    #if os.path.isfile(xmlpath+"_backup"):
    #    UseBackup=True

    #if UseBackup:
    #    f=open(xmlpath+"_backup","r")
    #else:
    #    f=open(xmlpath,"r")
    f=open(xmlpath,"r")
    fnew=open(xmlpath+"_new","w")
    lines=f.readlines()
    for line in lines:
        
        if "<Spectator" in line or " </Spectator" in line:
            continue
        fnew.write(line)

    f.close()
    fnew.close()
    #if not UseBackup :
    os.system("cp "+xmlpath+" "+xmlpath+"_backup")
    os.system("mv "+xmlpath+"_new "+xmlpath)
    print('[done]',xmlpath)

if __name__ == '__main__':
    import sys
    path=sys.argv[1]
    FixPath(path)
