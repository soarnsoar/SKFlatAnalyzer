#!/bin/bash
export PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_6/external/slc7_amd64_gcc700/bin:/cvmfs/cms.cern.ch/share/overrides/bin:/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_6/bin/slc7_amd64_gcc700:/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_6/external/slc7_amd64_gcc700/bin:/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/llvm/6.0.0-ogkkac/bin:/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/gcc/7.0.0-omkpbe2/bin:/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/gsl/2.2.1-omkpbe2/bin:/cvmfs/cms.cern.ch/common:/data6/Users/jhchoi/TMVA/TMVA_TOOL/script:/data6/Users/jhchoi/TMVA/TMVA_TOOL/script:/usr/local/texlive/2021/bin/x86_64-linux:/cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.22.06/x86_64-centos7-gcc48-opt/bin:/usr/local/texlive/2021/bin/x86_64-linux:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/opt/ibutils/bin:/opt/dell/srvadmin/bin:/home/jhchoi/bin:/home/jhchoi/bin
export JH_TMVA_TOOL_MAINDIR=/data6/Users/jhchoi/TMVA/TMVA_TOOL
export PYTHONPATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_6/external/slc7_amd64_gcc700/lib:/data6/Users/jhchoi/TMVA/TMVA_TOOL/python:/data6/Users/jhchoi/TMVA/TMVA_TOOL/python:
export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
export cmsswrel=cmssw/CMSSW_10_2_6
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/src
eval `scramv1 ru -sh`
cd /data6/Users/jhchoi/TMVA/TMVA_TOOL/ws/TTSemiLepJetAssignment_ProduceTrainingTree/WORKDIR_TTSemiLepJetAssignment_ntrial/1.0/TTSemiLepJetAssignment_ProduceTrainingTree/2018/2018__5__128__500__0.2/Trf_G/1
(cd /data6/Users/jhchoi/TMVA/TMVA_TOOL/ws/TTSemiLepJetAssignment_ProduceTrainingTree&&cd WORKDIR_TTSemiLepJetAssignment_ntrial/1.0/TTSemiLepJetAssignment_ProduceTrainingTree/2018/2018__5__128__500__0.2/Trf_G/1&&python /data6/Users/jhchoi/TMVA/TMVA_TOOL/script/run_TTSemiLepJetAssignment_ProduceTrainingTree.py --name 2018__5__128__500__0.2 --nlayer 5 --nnode 128 --batchsize 500 --dropout 0.2 --nepoch 300 --version 1.0 --year 2018 --analyzer TTSemiLepJetAssignment_ProduceTrainingTree --transform G --flag reduction_1M__)
myerr=$?
ntry=1
echo "myerr=$myerr"
while [ $myerr -ne 0 ]
do
ntry=`expr $ntry + 1`
(cd /data6/Users/jhchoi/TMVA/TMVA_TOOL/ws/TTSemiLepJetAssignment_ProduceTrainingTree&&cd WORKDIR_TTSemiLepJetAssignment_ntrial/1.0/TTSemiLepJetAssignment_ProduceTrainingTree/2018/2018__5__128__500__0.2/Trf_G/1&&python /data6/Users/jhchoi/TMVA/TMVA_TOOL/script/run_TTSemiLepJetAssignment_ProduceTrainingTree.py --name 2018__5__128__500__0.2 --nlayer 5 --nnode 128 --batchsize 500 --dropout 0.2 --nepoch 300 --version 1.0 --year 2018 --analyzer TTSemiLepJetAssignment_ProduceTrainingTree --transform G --flag reduction_1M__)
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
mv /data6/Users/jhchoi/TMVA/TMVA_TOOL/ws/TTSemiLepJetAssignment_ProduceTrainingTree/WORKDIR_TTSemiLepJetAssignment_ntrial/1.0/TTSemiLepJetAssignment_ProduceTrainingTree/2018/2018__5__128__500__0.2/Trf_G/1/run.jid /data6/Users/jhchoi/TMVA/TMVA_TOOL/ws/TTSemiLepJetAssignment_ProduceTrainingTree/WORKDIR_TTSemiLepJetAssignment_ntrial/1.0/TTSemiLepJetAssignment_ProduceTrainingTree/2018/2018__5__128__500__0.2/Trf_G/1/run.done
fi
