import ROOT
import json
import sys
from numpy import array
jsonname=sys.argv[1]
era=sys.argv[2]
#outputname=jsonname.split(".json")[0]
#outputname+=".root"
outputname="PileupWeight"+era+".root"
histname="MC_"+era


with open(jsonname,"r") as file:
    data = json.load(file)


##---
#MC_2017         central         PileupWeight2017.root
#MC_2017         sig_up          PileupWeight2017.root
#MC_2017         sig_down        PileupWeight2017.root

corr=data["corrections"][0]["data"]["content"] ##it is a list

h_nominal=ROOT.TH1D(histname+"_central",histname+"_central",99,0,99)
h_up=ROOT.TH1D(histname+"_sig_up",histname+"_sig_up",99,0,99)
h_down=ROOT.TH1D(histname+"_sig_down",histname+"_sig_down",99,0,99)

hdict={
    "nominal":h_nominal,
    "up":h_up,
    "down":h_down

}

dict_y={
    "up":[],
    "down":[],
    "nominal":[],
    "eyh":[],
    "eyl":[],
}


xlist=[]

outfile = ROOT.TFile(outputname, "RECREATE");

for element in corr:
    #print ("element=",element)
    direction=element["key"]
    h=hdict[direction]


    #print ("element_value_edges",element["value"]["edges"])
    #print ("element_value_content",element["value"]["content"])

    edges=element["value"]["edges"]
    content=element["value"]["content"]
    #print content
    #N=len(edges)
    N=len(content)

    for i in range(N):
        x=edges[i]
        y=content[i]
        #print y
        ibin=h.FindBin(x)
        h.SetBinContent(ibin,y)
        dict_y[direction].append(y)        

        if direction=="nominal": xlist.append(x)
    h.Write()




for i in range(N):
    _eyh=dict_y["up"][i]-dict_y["nominal"][i]
    dict_y["eyh"].append(_eyh)

    _eyl=dict_y["nominal"][i]-dict_y["down"][i]
    dict_y["eyl"].append(_eyl)

zerolist=array([0]*N)

gr=ROOT.TGraphAsymmErrors(N,array(xlist),array(dict_y["nominal"]),zerolist,zerolist,array(dict_y["eyl"]),array(dict_y["eyh"]) )

gr.Write()

outfile.Close()
