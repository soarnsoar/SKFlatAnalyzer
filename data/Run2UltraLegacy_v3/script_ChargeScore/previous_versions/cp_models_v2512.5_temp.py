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
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.1', 'SeparationType': 'GiniIndex', 'nCuts': '5', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7471860578584434, 'sigeff_B0p3': [0.672, 0.677], 'sigeff_B0p1': [0.347, 0.361], 'sigeff_B0p01': [0.055, 0.059]
        },

        '2016postVFP':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '3', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.75590877674216, 'sigeff_B0p3': [0.676, 0.703], 'sigeff_B0p1': [0.388, 0.38], 'sigeff_B0p01': [0.091, 0.101]
        },
        '2017':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '3', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.1', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7469554244076831, 'sigeff_B0p3': [0.67, 0.669], 'sigeff_B0p1': [0.343, 0.349], 'sigeff_B0p01': [0.049, 0.054]
        },
        '2018':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '5', 'MinNodeSize': '5', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.4', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7517682099201055, 'sigeff_B0p3': [0.681, 0.684], 'sigeff_B0p1': [0.357, 0.378], 'sigeff_B0p01': [0.057, 0.062]
        },



    },#                                                                                                                                                                                                                                                                                                                                                              

    'electron':{
        '2016preVFP':{
            'Trf': 'I', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.03', 'NTrees': '100', 'MaxDepth': '4', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.3', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7019082215457491, 'sigeff_B0p3': [0.594, 0.609], 'sigeff_B0p1': [0.297, 0.312], 'sigeff_B0p01': [0.056, 0.058]
        },
        '2016postVFP':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7083636567117758, 'sigeff_B0p3': [0.604, 0.61], 'sigeff_B0p1': [0.309, 0.343], 'sigeff_B0p01': [0.056, 0.061]
        },
        '2017':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '3', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7211155852554004, 'sigeff_B0p3': [0.625, 0.647], 'sigeff_B0p1': [0.324, 0.351], 'sigeff_B0p01': [0.066, 0.073]
            },
        '2018':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.1', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7163402500194221, 'sigeff_B0p3': [0.616, 0.626], 'sigeff_B0p1': [0.325, 0.332], 'sigeff_B0p01': [0.065, 0.072]

        },

    },##electron                                                                                                                                                                                                                                                                                                                                                     
    'jet':{
        '2016preVFP':{
            'Trf': 'I', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.03', 'NTrees': '600', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.598378487768171, 'sigeff_B0p3': [0.444, 0.45], 'sigeff_B0p1': [0.19, 0.198], 'sigeff_B0p01': [0.028, 0.031]
        },
        '2016postVFP':{
            'Trf': 'I', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '3', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.4', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.5987421111929291, 'sigeff_B0p3': [0.443, 0.448], 'sigeff_B0p1': [0.189, 0.196], 'sigeff_B0p01': [0.026, 0.028]
        },
        '2017':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '800', 'MaxDepth': '5', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.6021450397190814, 'sigeff_B0p3': [0.45, 0.458], 'sigeff_B0p1': [0.195, 0.203], 'sigeff_B0p01': [0.026, 0.028]
        },
        '2018':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '5', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.4', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.6018753706781673, 'sigeff_B0p3': [0.449, 0.455], 'sigeff_B0p1': [0.196, 0.204], 'sigeff_B0p01': [0.028, 0.031]
        }
    },

}


#list_obj=["muon","electron","jet"]
list_obj=["electron"]
#list_year=["2016preVFP","2016postVFP","2017","2018"]
#list_year=["2016preVFP","2016postVFP"]
list_year=[           "2018"]
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
