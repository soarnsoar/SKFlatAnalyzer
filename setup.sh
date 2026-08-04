export SKFlat_WD=`pwd`
export SKFlat_LIB_PATH=$SKFlat_WD/lib/
mkdir -p $SKFlat_LIB_PATH
mkdir -p $SKFlat_WD/tar

export SKFlatV="Run2UltraLegacy_v3"
mkdir -p $SKFlat_WD/data/$SKFlatV
export DATA_DIR=$SKFlat_WD/data/$SKFlatV

#### use cvmfs for root ####
export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
#export SCRAM_ARCH=slc7_amd64_gcc900
#export SCRAM_ARCH=slc7_amd64_gcc820
#export SCRAM_ARCH=el9_amd64_gcc12 ## after tamsa os update

#export SCRAM_ARCH=slc7_amd64_gcc630
#export SCRAM_ARCH=slc7_amd64_gcc700
#export cmsswrel='cmssw/CMSSW_11_2_5'
#export cmsswrel='cmssw/CMSSW_10_6_4' ##current//TMVA is working
export SCRAM_ARCH=el9_amd64_gcc12
export cmsswrel='cmssw/CMSSW_15_0_1' ## after tamsa os update
#export SCRAM_ARCH=el9_amd64_gcc12 ## after tamsa os update
#export cmsswrel='cmssw/CMSSW_14_1_0_pre4' ## after tamsa os update//jihunkim recom
#export cmsswrel='cmssw/CMSSW_13_0_2' ## after tamsa os update, test for multi pykeras
#export cmsswrel='cmssw/CMSSW_12_6_3' ## after tamsa os update, test for multi pykeras


#export SCRAM_ARCH=el9_amd64_gcc11 ## after tamsa os update, for multiple pykeras, CMSSW_13_2_9
#export cmsswrel='cmssw/CMSSW_13_2_9' ## after tamsa os update, test for multi pykeras

#export cmsswrel='cmssw/CMSSW_10_2_0'
#export cmsswrel='cmssw/CMSSW_10_2_6'
#export cmsswrel='cmssw/CMSSW_10_2_19'
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/src
echo "@@@@ SCRAM_ARCH = "$SCRAM_ARCH
echo "@@@@ cmsswrel = "$cmsswrel
echo "@@@@ scram..."
eval `scramv1 runtime -sh`
cd -
source /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/external/$SCRAM_ARCH/bin/thisroot.sh
export LD_LIBRARY_PATH=$ROOTSYS/lib:${LD_LIBRARY_PATH} ##jhchoi
export LD_LIBRARY_PATH=$(root-config --libdir):$LD_LIBRARY_PATH ##jhchoi
##For TensorFlow
#export PYTHONPATH=/cvmfs/cms.cern.ch/el9_amd64_gcc12/external/py3-tensorflow/2.12.0-0e51d24cbab7efcdb6842ba3efe14115/lib/python3.9/site-packages/:$PYTHONPATH
#export PYTHONPATH=/cvmfs/cms.cern.ch/el9_amd64_gcc12/external/py3-tensorflow/2.12.0-25a521020bcb1a4a8c486c2ab6293c89/lib/python3.9/site-packages:$PYTHONPATH
#export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/el9_amd64_gcc12/external/py3-tensorflow/2.12.0-25a521020bcb1a4a8c486c2ab6293c89/lib:$LD_LIBRARY_PATH 
#export LD_LIBRARY_PATH=/usr/lib64:$LD_LIBRARY_PATH ## jhchoi
##For TF 1.6 py3-tensorflow/1.6.0/lib
#export PYTHONPATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/py3-tensorflow/1.6.0/lib/python3.6/site-packages:$PYTHONPATH
#export LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/py3-tensorflow/1.6.0/lib:$LD_LIBRARY_PATH
##--TMVA cpu limit
export OMP_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export MKL_NUM_THREADS=1
export VECLIB_MAXIMUM_THREADS=1
export NUMEXPR_NUM_THREADS=1


if [[ $HOSTNAME == *"ui"*".sdfarm.kr"* ]]; then

  echo "@@@@ Working on KISTI"
  export SKFlatRunlogDir="/cms/ldap_home/$USER/SKFlatRunlog/"
  export SKFlatOutputDir="/cms/ldap_home/$USER/SKFlatOutput/"

elif [[ $HOSTNAME == *"tamsa1"* ]]; then

  echo "@@@@ Working on tamsa1"
  export SKFlatRunlogDir="/data6/Users/$USER/SKFlatRunlog/"
  export SKFlatOutputDir="/data6/Users/$USER/SKFlatOutput/"

elif [[ $HOSTNAME == *"tamsa2"* ]]; then

  echo "@@@@ Working on tamsa2"
  #export SKFlatRunlogDir="/data6/Users/$USER/SKFlatRunlog/"
  #export SKFlatOutputDir="/data6/Users/$USER/SKFlatOutput/"
  export SKFlatRunlogDir="/data9/Users/$USER/SKFlatRunlog/"
  export SKFlatOutputDir="/data9/Users/$USER/SKFlatOutput/"
elif [[ $HOSTNAME == *"knu"* ]]; then

  echo "@@@@ Working on KNU"
  export SKFlatRunlogDir="/u/user/$USER/scratch/SKFlatRunlog/"
  export SKFlatOutputDir="/u/user/$USER/scratch/SKFlatOutput/"

fi

alias skout="cd $SKFlatOutputDir/$SKFlatV/"

export MYBIN=$SKFlat_WD/bin/
export PYTHONDIR=$SKFlat_WD/python/
export PATH=${MYBIN}:${PYTHONDIR}:${PATH}

export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$SKFlat_WD/DataFormats/include/:$SKFlat_WD/AnalyzerTools/include/:$SKFlat_WD/Analyzers/include/
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$SKFlat_WD/external/TH4D
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$SKFlat_WD/Plotter/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKFlat_LIB_PATH
export LD_LIBRARY_PATH=/usr/local/lib:/usr/local/bin/python2.7:$LD_LIBRARY_PATH


source $SKFlat_WD/bin/BashColorSets.sh

## submodules ##
#source bin/CheckSubmodules.sh

if [ "$1" = "-q" ];then
    return
fi

alias python="python3"
## Todo list ##
python python/PrintToDoLists.py
source $SKFlat_WD/tmp/ToDoLists.sh
rm $SKFlat_WD/tmp/ToDoLists.sh

CurrentGitBranch=`git branch | grep \* | cut -d ' ' -f2`
printf "> Current SKFlatAnalyzer branch : "${BRed}$CurrentGitBranch${Color_Off}"\n"
echo "-----------------------------------------------------------------"
## Log Dir ##
echo "* Your Log Directory Usage (ctrl+c to skip)"
du -sh $SKFlatRunlogDir
