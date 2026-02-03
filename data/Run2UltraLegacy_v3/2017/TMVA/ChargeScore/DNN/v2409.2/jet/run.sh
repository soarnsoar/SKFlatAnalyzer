#!/bin/bash
export PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_6/external/slc7_amd64_gcc700/bin:/cvmfs/cms.cern.ch/share/overrides/bin:/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_6/bin/slc7_amd64_gcc700:/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_6/external/slc7_amd64_gcc700/bin:/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/llvm/6.0.0-ogkkac/bin:/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/gcc/7.0.0-omkpbe2/bin:/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/gsl/2.2.1-omkpbe2/bin:/cvmfs/cms.cern.ch/common:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script:/usr/condabin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/u/cms/bin:/u/cms/hep-tools:/opt/puppetlabs/bin:/u/user/jhchoi/.local/bin:/u/user/jhchoi/bin:/u/cms/bin:/u/cms/hep-tools:/u/user/jhchoi/.local/bin:/u/user/jhchoi/bin
export JH_TMVA_TOOL_MAINDIR=/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL
export PYTHONPATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_6/external/slc7_amd64_gcc700/lib:/u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/python:
export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
export cmsswrel=cmssw/CMSSW_10_2_6
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/src
eval `scramv1 ru -sh`
cd /d0/scratch/jhchoi/v2409.2/WORKDIR_ntrial/2409.2/EEMu_MuMuE_Method/2017/jet/jet2017__10__128__100__0.2/Trf_N/64
(cd /d0/scratch/jhchoi/v2409.2&&cd WORKDIR_ntrial/2409.2/EEMu_MuMuE_Method/2017/jet/jet2017__10__128__100__0.2/Trf_N/64&&python /u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/run_single.py --name jet2017__10__128__100__0.2 --nlayer 10 --nnode 128 --batchsize 100 --dropout 0.2 --nepoch 300 --version 2409.2 --channel jet --year 2017 --analyzer EEMu_MuMuE_Method --transform N)
myerr=$?
ntry=1
echo "myerr=$myerr"
while [ $myerr -ne 0 ]
do
ntry=`expr $ntry + 1`
(cd /d0/scratch/jhchoi/v2409.2&&cd WORKDIR_ntrial/2409.2/EEMu_MuMuE_Method/2017/jet/jet2017__10__128__100__0.2/Trf_N/64&&python /u/user/jhchoi/bbbar_asym/dnn/TMVA_TOOL/script/run_single.py --name jet2017__10__128__100__0.2 --nlayer 10 --nnode 128 --batchsize 100 --dropout 0.2 --nepoch 300 --version 2409.2 --channel jet --year 2017 --analyzer EEMu_MuMuE_Method --transform N)
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
mv /d0/scratch/jhchoi/v2409.2/WORKDIR_ntrial/2409.2/EEMu_MuMuE_Method/2017/jet/jet2017__10__128__100__0.2/Trf_N/64/run.jid /d0/scratch/jhchoi/v2409.2/WORKDIR_ntrial/2409.2/EEMu_MuMuE_Method/2017/jet/jet2017__10__128__100__0.2/Trf_N/64/run.done
fi
