import os

SKFlatV = os.environ['SKFlatV']
Year = "2017"

Skim = ""
#Skim = "SkimTree_LRSMHighPt"

#txtfilename = 'sample_DATA.txt'
txtfilename = 'sample_MC.txt'
#txtfilename = 'sample_MC_test.txt'
#txtfilename = 'sample_PrivateMC.txt'

IsDATA = ("DATA" in txtfilename)
periods = ["B","C","D","E","F"]

lines = open('samples/'+txtfilename).readlines()

for line in lines:

  line = line.strip('\n')

  if "#" in line:
    continue

  SkimString_Left = "";
  SkimString_Right = "";
  if Skim!="":
    SkimString_Left = "_"+Skim
    SkimString_Right = Skim+"_"

  if IsDATA:

    for period in periods:

      outname = SkimString_Right+line+'_'+period+'.txt'
      os.system('ls -1 /data7/DATA/SKFlat/'+SKFlatV+'/2017/DATA'+SkimString_Left+'/'+line+'/period'+period+'/*/*/*.root > '+outname)

      ## check number of files
      tmp = open(outname).readlines()
      print line+'_'+period+'\t'+str(len(tmp))

  else:
    PD = line.split()[0]
    alias = line.split()[1]

    outname = SkimString_Right+alias+'.txt'
    os.system('ls -1 /data7/DATA/SKFlat/'+SKFlatV+'/2017/MC'+SkimString_Left+'/'+PD+'/*/*/*.root > '+outname)
    ## check number of files
    tmp = open(SkimString_Right+alias+'.txt').readlines()
    print alias+'\t'+str(len(tmp))
