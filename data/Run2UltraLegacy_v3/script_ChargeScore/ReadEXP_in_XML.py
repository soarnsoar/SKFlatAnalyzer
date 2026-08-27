import sys
from html import unescape
import os


def GetX(expr):
    bvar=""
    if 'bmuon_' in expr :
        bvar="bmuon_ChargeTool."
    elif 'belectron_' in expr :
        bvar="belectron_ChargeTool."
    else:
        bvar="bjet_ChargeTool."
    if 'dR_l_j' in expr:return bvar+'dR_l_j'
    if 'P_jetrest' in expr:return bvar+'P_jetrest'
    if 'nsip3d' in expr:return bvar+'nsip3d'
    if 'palongjet' in expr:return bvar+'palongjet'
    if 'ptwrtbjet' in expr:return bvar+'ptwrtjet'
    if 'reliso' in expr:
        if 'log10' in expr:
            return bvar+'log10_1_reliso'
        else:
            return bvar+'reliso'
    if 'bjet_charge*bmuon_charge' in expr: return bvar+'bjet_charge_dot_bmuon_charge'
    if 'bjet_charge*belectron_charge' in expr: return bvar+'bjet_charge_dot_belectron_charge'

    if 'bjet_ChargedEmEnergyFraction' in expr : return bvar+'ChargedEmEnergyFraction'
    if 'bjet_ChargedHadronEnergyFraction' in expr :return bvar+'ChargedHadronEnergyFraction'
    if 'bjet_ChargedMultiplicity' in expr : return bvar+'ChargedMultiplicity'
    if 'bjet_MuonEnergyFraction' in expr:
        if 'log' in expr :
            return bvar+'log_MuonEnergyFraction'
        else:
            return bvar+'MuonEnergyFraction'
    if 'bjet_NeutralEmEnergyFraction' in expr :return bvar+'NeutralEmEnergyFraction'
    if 'bjet_NeutralHadronEnergyFraction' in expr :
        if 'log' in expr:
            return bvar+'log_NeutralHadronEnergyFraction'
        else:
            return bvar+'NeutralHadronEnergyFraction'
    if 'bjet_NeutralMultiplicity' in expr : return bvar+'NeutralMultiplicity'
    if 'fabs(bjet_charge)' in expr : return bvar+'abs_charge'


        
SKFlat_WD=os.getenv("SKFlat_WD")
#/Variables


path=sys.argv[1]

f=open(path)
lines=f.readlines()
f.close()
doRead=0
print(path)
list_expr=[]
for line in lines:
    if "<Variables" in line:
        doRead=1
        continue

    if doRead and "<Variable " in line:
        #print(line)
        expr = line.split('Expression="', 1)[1].split('"', 1)[0]
        expr = unescape(expr)
        #print(expr)
        list_expr.append(expr)
    if "</Variables" in line:
        doRead=0
        break


obj=""
ChargeTool="ChargeTool"
bvar=""
if "/muon/" in path:
    obj="muon"
    ChargeTool="mChargeTool"
    bvar="bmuon_ChargeTool"
if "/electron/" in path:
    obj="electron"
    ChargeTool="eChargeTool"
    bvar="belectron_ChargeTool"
if "/jet/" in path:
    obj="jet"
    ChargeTool="jChargeTool"
    bvar="bjet_ChargeTool"

for expr in list_expr:
    
    #clamp=ParseMinMax(exp)
    clamp=""
    X=GetX(expr)
    mystr=ChargeTool+'->AddVariable("'+expr+'",&'+X+clamp+');'
    print(mystr)
