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
    path="/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/ws_v2512.3/WORKDIR_FIN"
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
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '5', 'MinNodeSize': '5', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '5', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7566646471791072, 'sigeff_B0p3': [0.678, 0.689], 'sigeff_B0p1': [0.39, 0.386], 'sigeff_B0p01': [0.085, 0.091]
        },
        '2016postVFP':{
           'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.1', 'SeparationType': 'GiniIndex', 'nCuts': '5', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7591284154680494, 'sigeff_B0p3': [0.683, 0.717], 'sigeff_B0p1': [0.397, 0.395], 'sigeff_B0p01': [0.094, 0.1]
        },
        '2017':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '5', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.4', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7580654882687877, 'sigeff_B0p3': [0.683, 0.704], 'sigeff_B0p1': [0.383, 0.419], 'sigeff_B0p01': [0.086, 0.092]
        },
        '2018':{
           'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '5', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.4', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7602839115409992, 'sigeff_B0p3': [0.688, 0.689], 'sigeff_B0p1': [0.39, 0.425], 'sigeff_B0p01': [0.094, 0.104]
        },



    },#                                                                                                                                                                                                                                                                                                                                                              

    'electron':{
        '2016preVFP':{
            'Trf': 'U', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '4', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.4', 'SeparationType': 'GiniIndex', 'nCuts': '5', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7027300133687645, 'sigeff_B0p3': [0.595, 0.604], 'sigeff_B0p1': [0.309, 0.308], 'sigeff_B0p01': [0.067, 0.073]
        },
        '2016postVFP':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.005', 'NTrees': '800', 'MaxDepth': '5', 'MinNodeSize': '5', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.1', 'SeparationType': 'GiniIndex', 'nCuts': '5', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.709673871440592, 'sigeff_B0p3': [0.602, 0.606], 'sigeff_B0p1': [0.322, 0.355], 'sigeff_B0p01': [0.074, 0.075]
        },
        '2017':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.016', 'NTrees': '600', 'MaxDepth': '4', 'MinNodeSize': '3', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '15', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7222877020291533, 'sigeff_B0p3': [0.624, 0.65], 'sigeff_B0p1': [0.334, 0.356], 'sigeff_B0p01': [0.082, 0.09]
        },
        '2018':{
            'Trf': 'G', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '3', 'MinNodeSize': '1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.4', 'SeparationType': 'GiniIndex', 'nCuts': '20', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.7172978087485434, 'sigeff_B0p3': [0.618, 0.636], 'sigeff_B0p1': [0.331, 0.348], 'sigeff_B0p01': [0.073, 0.075]
        },

    },##electron                                                                                                                                                                                                                                                                                                                                                     
    'jet':{
        '2016preVFP':{
            'Trf': 'U', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '4', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.5983127564945151, 'sigeff_B0p3': [0.444, 0.45], 'sigeff_B0p1': [0.189, 0.197], 'sigeff_B0p01': [0.027, 0.03]
            },
        '2016postVFP':{
            'Trf': 'U', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '4', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.5993328591160949, 'sigeff_B0p3': [0.444, 0.452], 'sigeff_B0p1': [0.191, 0.202], 'sigeff_B0p01': [0.027, 0.03]
            },
        '2017':{
           'Trf': 'I', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '5', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.6029237908382435, 'sigeff_B0p3': [0.451, 0.458], 'sigeff_B0p1': [0.197, 0.207], 'sigeff_B0p01': [0.03, 0.031]
            },
        '2018':{
            'Trf': 'U', 'BoostType': 'Grad', 'Shrinkage__AdaBoostBeta': '0.02', 'NTrees': '500', 'MaxDepth': '5', 'MinNodeSize': '0.1', 'UseBaggedBoost': 'True', 'BaggedSampleFraction': '0.7', 'SeparationType': 'GiniIndex', 'nCuts': '50', 'IgnoreNegWeightsInTraining': 'True', 'auc': 0.6022261249795174, 'sigeff_B0p3': [0.449, 0.455], 'sigeff_B0p1': [0.197, 0.204], 'sigeff_B0p01': [0.03, 0.031]
        }
    },

}





list_obj=["muon","electron","jet"]
list_year=["2016preVFP","2016postVFP","2017","2018"]
#list_year=[           "2018"]
version='2512.3'

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
