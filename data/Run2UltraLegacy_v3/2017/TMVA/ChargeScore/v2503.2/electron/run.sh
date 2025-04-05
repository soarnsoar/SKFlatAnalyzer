#!/bin/bash
export PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/external/el9_amd64_gcc12/bin:/cvmfs/cms.cern.ch/share/overrides/bin:/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/bin/el9_amd64_gcc12:/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/external/el9_amd64_gcc12/bin:/cvmfs/cms.cern.ch/el9_amd64_gcc12/external/llvm/17.0.3-c63837ad0d3b09642e66207455f39fed/bin:/cvmfs/cms.cern.ch/el9_amd64_gcc12/external/gcc/12.3.1-40d504be6370b5a30e3947a6e575ca28/bin:/cvmfs/cms.cern.ch/common:/data9/Users/jhchoi/TMVA/el9/TMVA_TOOL/script:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/jhchoi/bin:/home/jhchoi/bin
export JH_TMVA_TOOL_MAINDIR=/data9/Users/jhchoi/TMVA/el9/TMVA_TOOL
export PYTHONPATH=/cvmfs/cms.cern.ch/el9_amd64_gcc12/cms/cmssw/CMSSW_14_1_0_pre4/external/el9_amd64_gcc12/lib:/data9/Users/jhchoi/TMVA/el9/TMVA_TOOL/python:
export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
export SCRAM_ARCH=el9_amd64_gcc12
export cmsswrel=cmssw/CMSSW_14_1_0_pre4
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/src
eval `scramv1 ru -sh`
cd /data9/Users/jhchoi/TMVA/el9/TMVA_TOOL/ws/WORKDIR/2503.2/EEMu_MuMuE_Method/2017/electron/electron2017__6__64__1000__0.1/Trf_G
(cd /data9/Users/jhchoi/TMVA/el9/TMVA_TOOL/ws&&cd WORKDIR/2503.2/EEMu_MuMuE_Method/2017/electron/electron2017__6__64__1000__0.1/Trf_G&&python3 /data9/Users/jhchoi/TMVA/el9/TMVA_TOOL/script/run_single.py --name electron2017__6__64__1000__0.1 --nlayer 6 --nnode 64 --batchsize 1000 --dropout 0.1 --nepoch 300 --version 2503.2 --channel electron --year 2017 --analyzer EEMu_MuMuE_Method --transform G)
myerr=$?
ntry=1
echo "myerr=$myerr"
while [ $myerr -ne 0 ]
do
ntry=`expr $ntry + 1`
(cd /data9/Users/jhchoi/TMVA/el9/TMVA_TOOL/ws&&cd WORKDIR/2503.2/EEMu_MuMuE_Method/2017/electron/electron2017__6__64__1000__0.1/Trf_G&&python3 /data9/Users/jhchoi/TMVA/el9/TMVA_TOOL/script/run_single.py --name electron2017__6__64__1000__0.1 --nlayer 6 --nnode 64 --batchsize 1000 --dropout 0.1 --nepoch 300 --version 2503.2 --channel electron --year 2017 --analyzer EEMu_MuMuE_Method --transform G)
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
mv /data9/Users/jhchoi/TMVA/el9/TMVA_TOOL/ws/WORKDIR/2503.2/EEMu_MuMuE_Method/2017/electron/electron2017__6__64__1000__0.1/Trf_G/run.jid /data9/Users/jhchoi/TMVA/el9/TMVA_TOOL/ws/WORKDIR/2503.2/EEMu_MuMuE_Method/2017/electron/electron2017__6__64__1000__0.1/Trf_G/run.done
fi
