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
    path="/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/ws_v2512.4/WORKDIR_FIN"
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
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.4', 'SeparationType': 'GiniIndex', 'nCuts': '5', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7563001060876468, 'sigeff_B0p3': [0.678, 0.687], 'sigeff_B0p1': [0.388, 0.376], 'sigeff_B0p01': [0.08, 0.088]
        },
        '2016postVFP':{
          'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.1', 'SeparationType': 'GiniIndex', 'nCuts': '5', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7586866699530506, 'sigeff_B0p3': [0.682, 0.714], 'sigeff_B0p1': [0.394, 0.397], 'sigeff_B0p01': [0.092, 0.1]

        },
        '2017':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '5', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.758081187509304, 'sigeff_B0p3': [0.682, 0.706], 'sigeff_B0p1': [0.383, 0.421], 'sigeff_B0p01': [0.086, 0.092]
        },
        '2018':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '500', 'MaxDepth': '5', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.1', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7598026456148739, 'sigeff_B0p3': [0.687, 0.685], 'sigeff_B0p1': [0.388, 0.42], 'sigeff_B0p01': [0.089, 0.097]
        },



    },#                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     

    'electron':{
        '2016preVFP':{
        'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '100', 'MaxDepth': '5', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.4', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.703322262196555, 'sigeff_B0p3': [0.594, 0.621], 'sigeff_B0p1': [0.31, 0.335], 'sigeff_B0p01': [0.066, 0.071]
        },
        '2016postVFP':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '5', 'MinNodeSize': '5', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7095033533195195, 'sigeff_B0p3': [0.603, 0.609], 'sigeff_B0p1': [0.32, 0.353], 'sigeff_B0p01': [0.067, 0.07]
        },
        '2017':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.013', 'NTrees': '700', 'MaxDepth': '5', 'MinNodeSize': '4', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.8', 'SeparationType': 'GiniIndex', 'nCuts': '15', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7222789131361421, 'sigeff_B0p3': [0.623, 0.65], 'sigeff_B0p1': [0.333, 0.356], 'sigeff_B0p01': [0.078, 0.086]
            },
        '2018':{
            'Trf': 'U', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.05', 'NTrees': '500', 'MaxDepth': '2', 'MinNodeSize': '5', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7165745068228799, 'sigeff_B0p3': [0.617, 0.631], 'sigeff_B0p1': [0.328, 0.341], 'sigeff_B0p01': [0.069, 0.073]
        },

    },##electron                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    'jet':{
        '2016preVFP':{
            'Trf': 'N', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '5', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.5978679249769611, 'sigeff_B0p3': [0.444, 0.453], 'sigeff_B0p1': [0.188, 0.198], 'sigeff_B0p01': [0.024, 0.026]
        },
        '2016postVFP':{
            'Trf': 'I', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '800', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.5990029693028639, 'sigeff_B0p3': [0.445, 0.451], 'sigeff_B0p1': [0.19, 0.2], 'sigeff_B0p01': [0.025, 0.027]
            },
        '2017':{
            'Trf': 'U', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '5', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.6026682191033919, 'sigeff_B0p3': [0.451, 0.458], 'sigeff_B0p1': [0.196, 0.206], 'sigeff_B0p01': [0.027, 0.029]
            },
        '2018':{
            'Trf': 'U', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '5', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.4', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.6019327341002363, 'sigeff_B0p3': [0.449, 0.456], 'sigeff_B0p1': [0.196, 0.203], 'sigeff_B0p01': [0.027, 0.028]
        }
    },

}


list_obj=["muon","electron","jet"]
list_year=["2016preVFP","2016postVFP","2017","2018"]
#list_year=[           "2018"]
version='2512.4'

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
