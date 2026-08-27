# 2017/TMVA/ChargeScore/v2405.4.3/muon
import os
def GetDestination(version,year,obj):
    path=year+"/TMVA/ChargeScore/BDT/v"+version+"/"+obj
    os.system("mkdir -p "+path)
    return path


def GetPathReplicaSNU(version,year,obj,trf,boosttype,shrinkage,ntrees,maxdepth,minnodesize,usebaggedboost,baggedsamplefraction,seperation,ncuts,ignorenegweight,index):
    version=str(version)
    year=str(year)
    shrinkage=str(shrinkage)
    ntrees=str(ntrees)
    maxdepth=str(maxdepth)
    minnodesize=str(minnodesize)
    baggedsamplefraction=str(baggedsamplefraction)
    ncuts=str(ncuts)    
    index=str(index)
    
    #/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/ws/WORKDIR_FIN/2409.2/2018/muon/G__Grad__Shrinkage__0.01__NTrees__500__MaxDepth__5__MinNodeSize__1__UseBaggedBoost__True__BaggedSampleFraction__0.2__SeparationType__GiniIndex__nCuts__40__IgnoreNegWeightsInTraining__True/idx_0
    path="/data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/ws/WORKDIR_FIN/"
    path+="/"+version
    path+="/"+year
    path+="/"+obj+"/"
    #2608.2/2018/muon/G/Grad/Shrinkage__0.005/NTrees__1000/MaxDepth__6/MinNodeSize__1/UseBaggedBoost__True/BaggedSampleFraction__0.6/SeparationType__CrossEntropy/nCuts__20/IgnoreNegWeightsInTraining__True
    path+=  "/".join([trf,boosttype,'Shrinkage__'+shrinkage,'NTrees__'+ntrees,'MaxDepth__'+maxdepth,'MinNodeSize__'+minnodesize,'UseBaggedBoost__'+usebaggedboost,'BaggedSampleFraction__'+baggedsamplefraction,'SeparationType__'+seperation,'nCuts__'+ncuts,'IgnoreNegWeightsInTraining__'+ignorenegweight])
    if index:path+= "/idx_"+index
    return path








dict_sub={
    'muon':{
        '2016preVFP':{'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '500', 'MaxDepth': '5', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.2', 'SeparationType': 'CrossEntropy', 'nCuts': '30', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7524418403481035, 'sigeff_B0p3': [0.676, 0.693], 'sigeff_B0p1': [0.382, 0.389], 'sigeff_B0p01': [0.082, 0.101]},
        '2016postVFP':{'Trf': 'I', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '500', 'MaxDepth': '4', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.2', 'SeparationType': 'CrossEntropy', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7538683352211905, 'sigeff_B0p3': [0.676, 0.71], 'sigeff_B0p1': [0.393, 0.422], 'sigeff_B0p01': [0.098, 0.12]},
        '2017':{'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.001', 'NTrees': '3000', 'MaxDepth': '6', 'MinNodeSize': '0.5', 'UseBaggedBoost': 'True', 'BaggedSampleFraction':'0.4', 'SeparationType': 'CrossEntropy', 'nCuts': '40', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7538842748190708, 'sigeff_B0p3': [0.677, 0.699], 'sigeff_B0p1': [0.38, 0.417], 'sigeff_B0p01': [0.088, 0.106]},
        '2018':{'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '1000', 'MaxDepth': '6', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.6', 'SeparationType': 'CrossEntropy', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7550193306431433, 'sigeff_B0p3': [0.679, 0.692], 'sigeff_B0p1': [0.385, 0.425], 'sigeff_B0p01': [0.089, 0.103]},

    },

    'electron':{
        '2016preVFP':{'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.1', 'SeparationType': 'CrossEntropy', 'nCuts': '10', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.699832425178084, 'sigeff_B0p3': [0.592, 0.59], 'sigeff_B0p1': [0.301, 0.293], 'sigeff_B0p01': [0.051, 0.063]},
        '2016postVFP':{'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.01', 'NTrees': '500', 'MaxDepth': '4', 'MinNodeSize': '2.5', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.5', 'SeparationType': 'GiniIndex', 'nCuts': '30', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7042025463210984, 'sigeff_B0p3': [0.597, 0.61], 'sigeff_B0p1': [0.3, 0.332], 'sigeff_B0p01': [0.062, 0.061]},
        '2017':{'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.01', 'NTrees': '1000', 'MaxDepth': '4', 'MinNodeSize': '2.5', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.6', 'SeparationType': 'CrossEntropy', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7193983866183472, 'sigeff_B0p3': [0.622, 0.646], 'sigeff_B0p1': [0.322, 0.348], 'sigeff_B0p01': [0.064, 0.073]},
        '2018':{'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.01', 'NTrees': '1000', 'MaxDepth': '4', 'MinNodeSize': '2.5', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.6', 'SeparationType': 'CrossEntropy', 'nCuts': '30', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7143850462252161, 'sigeff_B0p3': [0.613, 0.632], 'sigeff_B0p1': [0.318, 0.343], 'sigeff_B0p01': [0.064, 0.078]},
    },##electron                                                                                                                                                                                                                                                                                                                                                     
    'jet':{
        '2016preVFP':{'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.01', 'NTrees': '1500', 'MaxDepth': '4', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.6', 'SeparationType': 'CrossEntropy', 'nCuts': '80', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.5982152587696661, 'sigeff_B0p3': [0.444, 0.451], 'sigeff_B0p1': [0.189, 0.199], 'sigeff_B0p01': [0.027, 0.033]},
        '2016postVFP':{'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.01', 'NTrees': '800', 'MaxDepth': '4', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.5', 'SeparationType': 'CrossEntropy', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.598380415466963, 'sigeff_B0p3': [0.444, 0.449], 'sigeff_B0p1': [0.188, 0.2], 'sigeff_B0p01': [0.026, 0.03]},
        '2017':{'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.1', 'NTrees': '50', 'MaxDepth': '6', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'False', 'BaggedSampleFraction': '1', 'SeparationType': 'CrossEntropy', 'nCuts': '40', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.6011577063767876, 'sigeff_B0p3': [0.449, 0.458], 'sigeff_B0p1': [0.193, 0.202], 'sigeff_B0p01': [0.022, 0.024]},
        '2018':{'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.1', 'NTrees': '50', 'MaxDepth': '6', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'False', 'BaggedSampleFraction': '1', 'SeparationType': 'CrossEntropy', 'nCuts': '30', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.600633214899196, 'sigeff_B0p3': [0.448, 0.455], 'sigeff_B0p1': [0.193, 0.201], 'sigeff_B0p01': [0.022, 0.024]},
    },
    
}





list_obj=["muon","electron","jet"]
list_year=["2016preVFP","2016postVFP","2017","2018"]
#list_year=[           "2018"]
version='2608.2'

for obj in list_obj:
    for year in list_year:
        ##From KNU

        this_dict=dict_sub[obj][year]


        trf=this_dict['Trf']
        boosttype=this_dict['BoostType']
        shrinkage=this_dict['Shrinkage__AdaBoostBeta']
        ntrees=this_dict['NTrees']
        maxdepth=this_dict['MaxDepth']
        minnodesize=this_dict['MinNodeSize']
        usebaggedboost=this_dict['UseBaggedBoost']
        baggedsamplefraction=this_dict['BaggedSampleFraction']
        seperation=this_dict['SeparationType']
        ncuts=this_dict['nCuts']
        ignorenegweight=this_dict['IgnoreNegWeightsInTraining']
        index=""
        path=GetPathReplicaSNU(version,year,obj,trf,boosttype,shrinkage,ntrees,maxdepth,minnodesize,usebaggedboost,baggedsamplefraction,seperation,ncuts,ignorenegweight,index)
        des=GetDestination(version,year,obj)
        
        command="cp "+path+"/* "+des+"/" 
        command2="cp "+path+"/*/*/*.xml "+des+"/" 

        print(command)
        print(command2)

        info= "__".join([trf,boosttype,'Shrinkage',shrinkage,'NTrees',ntrees,'MaxDepth',maxdepth,'MinNodeSize',minnodesize,'UseBaggedBoost',usebaggedboost,'BaggedSampleFraction','baggedsamplefraction','SeparationType',seperation,'nCuts',ncuts,'IgnoreNegWeightsInTraining',ignorenegweight])
        command3='echo '+info+" > "+des+"/info.txt"
        print(command3)
