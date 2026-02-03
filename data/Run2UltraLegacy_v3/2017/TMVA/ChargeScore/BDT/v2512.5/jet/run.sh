#!/bin/bash
export PATH=/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/BDT/v2512.5:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/DNN:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/BDT:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/BDT/v2512.4:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/DNN:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/BDT:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/BDT_arg_version:/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/external/el9_amd64_gcc12/bin:/cvmfs/cms.cern.ch/share/overrides/bin:/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/bin/el9_amd64_gcc12:/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/external/el9_amd64_gcc12/bin:/cvmfs/cms.cern.ch/el9_amd64_gcc12/external/llvm/17.0.3-c63837ad0d3b09642e66207455f39fed/bin:/cvmfs/cms.cern.ch/el9_amd64_gcc12/external/gcc/12.3.1-40d504be6370b5a30e3947a6e575ca28/bin:/cvmfs/cms.cern.ch/common:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/DNN:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/BDT:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/BDT:/usr/condabin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/u/cms/bin:/u/cms/hep-tools:/opt/puppetlabs/bin:/u/user/jhchoi/.local/bin:/u/user/jhchoi/bin:/u/cms/bin:/u/cms/hep-tools:/u/user/jhchoi/.local/bin:/u/user/jhchoi/bin
export JH_TMVA_TOOL_MAINDIR=/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL
export PYTHONPATH=/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/external/el9_amd64_gcc12/lib:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/python:
export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
export SCRAM_ARCH=el9_amd64_gcc12
export cmsswrel=cmssw/CMSSW_14_1_0_pre4
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/src
eval `scramv1 ru -sh`
cd /u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/ws_v2512.5/WORKDIR_FIN/2512.5/2017/jet/G__Grad__Shrinkage__0.05__NTrees__400__MaxDepth__5__MinNodeSize__1__UseBaggedBoost__False__BaggedSampleFraction__0__SeparationType__GiniIndex__nCuts__40__IgnoreNegWeightsInTraining__True/idx_0
(echo ${_CONDOR_SCRATCH_DIR}&&cd $_CONDOR_SCRATCH_DIR&&python3 /u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/BDT/run_single_BDT.py  --transform G --BoostType Grad --Shrinkage 0.05 --NTrees 400 --MaxDepth 5 --MinNodeSize 1 --UseBaggedBoost False --BaggedSampleFraction 0 --SeparationType GiniIndex --nCuts 40 --IgnoreNegWeightsInTraining True --analyzer EEMu_MuMuE_Method --version 2512.5_2017 --name FIN_BDT_2017 --year 2017 --channel jet&&ls)
myerr=$?
ntry=1
echo "myerr=$myerr"
while [ $myerr -ne 0 ]
do
ntry=`expr $ntry + 1`
(echo ${_CONDOR_SCRATCH_DIR}&&cd $_CONDOR_SCRATCH_DIR&&python3 /u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/BDT/run_single_BDT.py  --transform G --BoostType Grad --Shrinkage 0.05 --NTrees 400 --MaxDepth 5 --MinNodeSize 1 --UseBaggedBoost False --BaggedSampleFraction 0 --SeparationType GiniIndex --nCuts 40 --IgnoreNegWeightsInTraining True --analyzer EEMu_MuMuE_Method --version 2512.5_2017 --name FIN_BDT_2017 --year 2017 --channel jet&&ls)
myerr=$?
echo ntry="$ntry"
echo "myerr=$myerr"
if [ $ntry -gt 1 ]
then
break
fi
done
echo "[ntry=$ntry]"
if [ $myerr -eq 0 ]
then
mv /u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/ws_v2512.5/WORKDIR_FIN/2512.5/2017/jet/G__Grad__Shrinkage__0.05__NTrees__400__MaxDepth__5__MinNodeSize__1__UseBaggedBoost__False__BaggedSampleFraction__0__SeparationType__GiniIndex__nCuts__40__IgnoreNegWeightsInTraining__True/idx_0/run.jid /u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/ws_v2512.5/WORKDIR_FIN/2512.5/2017/jet/G__Grad__Shrinkage__0.05__NTrees__400__MaxDepth__5__MinNodeSize__1__UseBaggedBoost__False__BaggedSampleFraction__0__SeparationType__GiniIndex__nCuts__40__IgnoreNegWeightsInTraining__True/idx_0/run.done
fi
