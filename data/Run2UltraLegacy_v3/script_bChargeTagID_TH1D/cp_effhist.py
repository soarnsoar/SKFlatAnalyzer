import os
import glob
import ROOT
SKFlat_WD=os.getenv("SKFlat_WD")
hostname=os.getenv('HOSTNAME')




#_SkimTree_Dilepton
list_year=["2016preVFP", "2016postVFP", "2017", "2018"]


ANANAME="TTsemiLepChargeScoreEfficiencyMeasurement"
suffix='use_beff_dasym__JETPUID_L__newlepveto__chi2kincut__bdt2608.2__splitcharge__measure_bchargeeff__'






for YEAR in list_year:
    from_dir="/data9/Users/jhchoi/SKFlatOutput/Run2UltraLegacy_v3/"+ANANAME+"/"+str(YEAR)+"/"+suffix
    if 'knu' in hostname:
        from_dir='/u/user/jhchoi/scratch/SKFlatOutput/Run2UltraLegacy_v3/'+ANANAME+"/"+str(YEAR)+"/"+suffix
    to_dir=SKFlat_WD+"/data/Run2UltraLegacy_v3/"+str(YEAR)+"/bChargeTagID/"

    list_rootfile=glob.glob(from_dir+"/*.root")
    for rootfile in list_rootfile:
        rootfile_new=rootfile.replace("_SkimTree_SingleLepton_1DeepJetTightWP","").replace("_SkimTree_Dilepton_1DeepJetTightWP","").replace("_SkimTree_Dilepton","").replace("_SkimTree_SingleLepton","")
        rootfile_new=rootfile_new.split("/")[-1]
        
        print("#"+rootfile_new)
        source1=rootfile

        os.system("cp "+source1+" "+to_dir+"/"+rootfile_new)

