# 2017/TMVA/ChargeScore/v2405.4.3/muon
import os
def GetDestination(version,year,obj):
    path=year+"/TMVA/ChargeScore/BDT/v"+version+"/"+obj
    os.system("mkdir -p "+path)
    return path


def GetPathReplicaKNU(version,year,obj,trf,boosttype,shrinkage,ntrees,maxdepth,minnodesize,usebaggedboost,baggedsamplefraction,seperation,ncuts,ignorenegweight,index):
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
    path="/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/ws_v2512.5/WORKDIR_FIN"
    path+="/"+version
    path+="/"+year
    path+="/"+obj+"/"
    path+=  "__".join([trf,boosttype,'Shrinkage',shrinkage,'NTrees',ntrees,'MaxDepth',maxdepth,'MinNodeSize',minnodesize,'UseBaggedBoost',usebaggedboost,'BaggedSampleFraction',baggedsamplefraction,'SeparationType',seperation,'nCuts',ncuts,'IgnoreNegWeightsInTraining',ignorenegweight])
    if index:path+= "/idx_"+index
    return path






def GetPathModel(FromSNU,version,year,obj,nlayer,nnode,batch,dropout,trf,index):
    UseOrig=False
    if index < 0 : UseOrig=True
    if FromSNU:
        return GetPathReplicaSNU(version,year,obj,nlayer,nnode,batch,dropout,trf,index)
    else:
        #def GetPathReplicaKNU(version,year,obj,trf,boosttype,shrinkage,ntrees,maxdepth,minnodesize,usebaggedboost,baggedsamplefraction,seperation,ncuts,ignorenegweight,index)

        return GetPathReplicaKNU(version,year,obj,trf,boosttype,shrinkage,ntrees,maxdepth,minnodesize,usebaggedboost,baggedsamplefraction,seperation,ncuts,ignorenegweight,index)



dict_sub={
    'muon':{
        '2016preVFP':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.1', 'NTrees': '100', 'MaxDepth': '5', 'MinNodeSize': '8', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.5', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7457763020078991, 'sigeff_B0p3': [0.669, 0.671], 'sigeff_B0p1': [0.345, 0.334], 'sigeff_B0p01': [0.066, 0.072]
        },

        '2016postVFP':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.01', 'NTrees': '400', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.3', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegW\
eightsInTraining': 'True', 'auc': 0.7549642451715497, 'sigeff_B0p3': [0.67, 0.718], 'sigeff_B0p1': [0.387, 0.413], 'sigeff_B0p01': [0.098, 0.104]


        },
        '2017':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.01', 'NTrees': '400', 'MaxDepth': '5', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '40', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7519555647607854, 'sigeff_B0p3': [0.672, 0.684], 'sigeff_B0p1': [0.371, 0.399], 'sigeff_B0p01': [0.084, 0.087]
        },
        '2018':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.01', 'NTrees': '400', 'MaxDepth': '5', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.3', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.757134080196027, 'sigeff_B0p3': [0.683, 0.689], 'sigeff_B0p1': [0.382, 0.42], 'sigeff_B0p01': [0.09, 0.091]
        },
    },#                                                                                                                                                                                                                                                                                                                                                              

    'electron':{
        '2016preVFP':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.05', 'NTrees': '200', 'MaxDepth': '3', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.3', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7018028873569405, 'sigeff_B0p3': [0.594, 0.601], 'sigeff_B0p1': [0.297, 0.303], 'sigeff_B0p01': [0.054, 0.055]

        },
        '2016postVFP':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.01', 'NTrees': '400', 'MaxDepth': '4', 'MinNodeSize': '3', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.3', 'SeparationType': 'GiniIndex', 'nCuts': '10', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7028231882174749, 'sigeff_B0p3': [0.6, 0.602], 'sigeff_B0p1': [0.289, 0.305], 'sigeff_B0p01': [0.042, 0.04]
        },
        '2017':{
            'Trf': 'I', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.01', 'NTrees': '400', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.1', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7196561468707919, 'sigeff_B0p3': [0.624, 0.643], 'sigeff_B0p1': [0.318, 0.33], 'sigeff_B0p01': [0.059, 0.065]
        },
        '2018':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.05', 'NTrees': '200', 'MaxDepth': '3', 'MinNodeSize': '3', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.3', 'SeparationType': 'GiniIndex', 'nCuts': '5', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.711184222524016, 'sigeff_B0p3': [0.61, 0.613], 'sigeff_B0p1': [0.312, 0.314], 'sigeff_B0p01': [0.061, 0.065]
        },

    },##electron                                                                                                                                                                                                                                                                                                                                                     
    'jet':{
        '2016preVFP':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.1', 'NTrees': '200', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'False', 'BaggedSampleFraction': '0', 'SeparationType': 'GiniIndex', 'nCuts': '40', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.5980422694120171, 'sigeff_B0p3': [0.444, 0.452], 'sigeff_B0p1': [0.189, 0.195], 'sigeff_B0p01': [0.028, 0.031]
        },
        '2016postVFP':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.05', 'NTrees': '200', 'MaxDepth': '5', 'MinNodeSize': '3', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.5', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.5977490827063703, 'sigeff_B0p3': [0.444, 0.448], 'sigeff_B0p1': [0.189, 0.197], 'sigeff_B0p01': [0.025, 0.027]
        },
        '2017':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.05', 'NTrees': '400', 'MaxDepth': '5', 'MinNodeSize': '1', 'UseBaggedBoost': 'False', 'BaggedSampleFraction': '0', 'SeparationType': 'GiniIndex', 'nCuts': '40', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.5993543784386072, 'sigeff_B0p3': [0.447, 0.454], 'sigeff_B0p1': [0.191, 0.2], 'sigeff_B0p01': [0.022, 0.024]

        },
        '2018':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.05', 'NTrees': '400', 'MaxDepth': '5', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.6007871576255216, 'sigeff_B0p3': [0.448, 0.455], 'sigeff_B0p1': [0.193, 0.199], 'sigeff_B0p01': [0.023, 0.025]
        }
    },

}


list_obj=["muon","electron","jet"]
list_year=["2016preVFP","2016postVFP","2017","2018"]
#list_year=["2016preVFP","2016postVFP"]
#list_year=[           "2018"]
version='2512.5'

for obj in list_obj:
    for year in list_year:
        ##From KNU
        #def GetPathReplicaKNU(version,year,obj,trf,boosttype,shrinkage,ntrees,maxdepth,minnodesize,usebaggedboost,baggedsamplefraction,seperation,ncuts,ignorenegweight,index)
        this_dict=dict_sub[obj][year]
        #'Trf': 'N', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.01', 'NTrees': '1200', 'MaxDepth': '4', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.5992346271043376, 'sigeff_B0p3': [0.445, 0.452], 'sigeff_B0p1': [0.192, 0.199], 'sigeff_B0p01': [0.029, 0.032]

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
        index=0
        path=GetPathReplicaKNU(version,year,obj,trf,boosttype,shrinkage,ntrees,maxdepth,minnodesize,usebaggedboost,baggedsamplefraction,seperation,ncuts,ignorenegweight,index)
        des=GetDestination(version,year,obj)
        
        command="scp jhchoi@cms.knu.ac.kr:"+path+"/* "+des+"/" 
        command2="scp jhchoi@cms.knu.ac.kr:"+path+"/*/*/*.xml "+des+"/" 
        #command3="scp jhchoi@cms.knu.ac.kr:"+path+"/*/*/*.h5 "+des+"/" 
        print(command)
        print(command2)
        #print(command3)
        info= "__".join([trf,boosttype,'Shrinkage',shrinkage,'NTrees',ntrees,'MaxDepth',maxdepth,'MinNodeSize',minnodesize,'UseBaggedBoost',usebaggedboost,'BaggedSampleFraction','baggedsamplefraction','SeparationType',seperation,'nCuts',ncuts,'IgnoreNegWeightsInTraining',ignorenegweight])
        command3='echo '+info+" > "+des+"/info.txt"
        print(command3)
