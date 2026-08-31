#!/bin/bash
export PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/external/el9_amd64_gcc12/bin:/cvmfs/cms.cern.ch/share/overrides/bin:/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/bin/el9_amd64_gcc12:/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/external/el9_amd64_gcc12/bin:/cvmfs/cms.cern.ch/el9_amd64_gcc12/external/llvm/17.0.3-c63837ad0d3b09642e66207455f39fed/bin:/cvmfs/cms.cern.ch/el9_amd64_gcc12/external/gcc/12.3.1-40d504be6370b5a30e3947a6e575ca28/bin:/cvmfs/cms.cern.ch/share/x86_64/cms/prmon/v2026022600/bin:/cvmfs/cms.cern.ch/common:/data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/script/DNN:/data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/script/BDT:/data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/script/BDT:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/opt/pbs/bin:/var/lib/snapd/snap/bin:/home/jhchoi/.local/bin:/home/jhchoi/bin:/opt/pbs/bin:/home/jhchoi/.local/bin:/home/jhchoi/bin
export JH_TMVA_TOOL_MAINDIR=/data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL
export PYTHONPATH=/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/external/el9_amd64_gcc12/lib:/data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/python:
export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
export SCRAM_ARCH=el9_amd64_gcc12
export cmsswrel=cmssw/CMSSW_14_1_0_pre4
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/src
eval `scramv1 ru -sh`
cd /data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/ws/WORKDIR_FIN/2608.2/2017/muon/G/Grad/Shrinkage__0.001/NTrees__3000/MaxDepth__6/MinNodeSize__0.5/UseBaggedBoost__True/BaggedSampleFraction__0.4/SeparationType__CrossEntropy/nCuts__40/IgnoreNegWeightsInTraining__True
(cd /data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/ws&&cd WORKDIR_FIN/2608.2/2017/muon/G/Grad/Shrinkage__0.001/NTrees__3000/MaxDepth__6/MinNodeSize__0.5/UseBaggedBoost__True/BaggedSampleFraction__0.4/SeparationType__CrossEntropy/nCuts__40/IgnoreNegWeightsInTraining__True&&python3 /data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/script/BDT/run_single_BDT.py  --transform G --BoostType Grad --Shrinkage 0.001 --NTrees 3000 --MaxDepth 6 --MinNodeSize 0.5 --UseBaggedBoost True --BaggedSampleFraction 0.4 --SeparationType CrossEntropy --nCuts 40 --IgnoreNegWeightsInTraining True --analyzer EEMu_MuMuE_Method --version 2608.2 --name BDT_2017 --year 2017 --channel muon)
myerr=$?
ntry=1
echo "myerr=$myerr"
while [ $myerr -ne 0 ]
do
ntry=`expr $ntry + 1`
(cd /data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/ws&&cd WORKDIR_FIN/2608.2/2017/muon/G/Grad/Shrinkage__0.001/NTrees__3000/MaxDepth__6/MinNodeSize__0.5/UseBaggedBoost__True/BaggedSampleFraction__0.4/SeparationType__CrossEntropy/nCuts__40/IgnoreNegWeightsInTraining__True&&python3 /data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/script/BDT/run_single_BDT.py  --transform G --BoostType Grad --Shrinkage 0.001 --NTrees 3000 --MaxDepth 6 --MinNodeSize 0.5 --UseBaggedBoost True --BaggedSampleFraction 0.4 --SeparationType CrossEntropy --nCuts 40 --IgnoreNegWeightsInTraining True --analyzer EEMu_MuMuE_Method --version 2608.2 --name BDT_2017 --year 2017 --channel muon)
myerr=$?
echo ntry="$ntry"
echo "myerr=$myerr"
if [ $ntry -gt 3 ]
then
break
fi
done
echo "[ntry=$ntry]"
if [ $myerr -eq 0 ]
then
mv /data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/ws/WORKDIR_FIN/2608.2/2017/muon/G/Grad/Shrinkage__0.001/NTrees__3000/MaxDepth__6/MinNodeSize__0.5/UseBaggedBoost__True/BaggedSampleFraction__0.4/SeparationType__CrossEntropy/nCuts__40/IgnoreNegWeightsInTraining__True/run.jid /data9/Users/jhchoi/Generate_BDT_Model/TMVA_TOOL/ws/WORKDIR_FIN/2608.2/2017/muon/G/Grad/Shrinkage__0.001/NTrees__3000/MaxDepth__6/MinNodeSize__0.5/UseBaggedBoost__True/BaggedSampleFraction__0.4/SeparationType__CrossEntropy/nCuts__40/IgnoreNegWeightsInTraining__True/run.done
fi
