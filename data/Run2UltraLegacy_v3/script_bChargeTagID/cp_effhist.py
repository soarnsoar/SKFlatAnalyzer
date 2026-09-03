import os
import glob
import ROOT
SKFlat_WD=os.getenv("SKFlat_WD")





#_SkimTree_Dilepton
list_year=["2016preVFP", "2016postVFP", "2017", "2018"]
#list_year=["2016preVFP"]

#ANANAME="TTsemiLepChargeScoreEfficiencyMeasurement_TightMatch"
#ANANAME="TTsemiLepBtagChargeAsymEfficiencyMeasurement_BINNING"

#ANANAME="PreselectionToBDTRegionAnalyzer"
#suffix="jetpuid_loose__lepveto__use_beffasym__bdt2512.5__bdtcut__measure_bchargeeff__"

ANANAME="TTsemiLepChargeScoreEfficiencyMeasurement"
#suffix="use_beff_dasym__JETPUID_L__bdt2512.5__measure_bchargeeff__"
#suffix='use_beff_dasym__JETPUID_L__noveto__newlepveto__chi2kincut__bdt2608.2__splitcharge__noetabin__measure_bchargeeff__'
#suffix="use_beff_dasym__JETPUID_L__newlepveto__chi2kincut__bdt2608.2__splitcharge__noetabin__jetlepveto__measure_bchargeeff__"
suffix="use_beff_dasym__JETPUID_L__chi2kincut__bdt2608.2__splitcharge__noetabin__measure_bchargeeff__"

for YEAR in list_year:
    #from_dir="/data6/Users/jhchoi/SKFlatOutput/Run2UltraLegacy_v3/"+ANANAME+"/"+str(YEAR)+"/measure_btageff__"
    from_dir="/data9/Users/jhchoi/SKFlatOutput/Run2UltraLegacy_v3/"+ANANAME+"/"+str(YEAR)+"/"+suffix
    to_dir=SKFlat_WD+"/data/Run2UltraLegacy_v3/"+str(YEAR)+"/bChargeTagID/"

    #os.system("ls "+from_dir)
    list_rootfile=glob.glob(from_dir+"/*.root")
    for rootfile in list_rootfile:
        rootfile_new=rootfile.replace("_SkimTree_SingleLepton_1DeepJetTightWP","").replace("_SkimTree_Dilepton_1DeepJetTightWP","").replace("_SkimTree_Dilepton","").replace("_SkimTree_SingleLepton","")
        rootfile_new=rootfile_new.split("/")[-1]
        print("#"+rootfile_new)
        #os.system("cp "+rootfile+" "+to_dir+"/"+rootfile_new)
        source1=rootfile
        source2=YEAR+"__empty.root"
        #command="hadd -f "+to_dir+"/"+rootfile_new+" "+rootfile+" "+YEAR+"__empty.root"
        tempdir="temp__"+YEAR+"__"+ rootfile_new.replace(".root","") +"/"
        os.system("mkdir -p "+tempdir)
        os.system("cp "+source1+" "+tempdir)
        os.system("cp "+source2+" "+tempdir)

        source1_to_hadd=source1.split("/")[-1]
        print("cd "+tempdir)
        command="hadd -f combine.root "+source2+" "+source1_to_hadd+" &> hadd.log"
        print(command)
        print('mkdir -p '+to_dir)
        print("cp combine.root "+to_dir+"/"+rootfile_new)
        print("cd -")
        #os.system(command)
