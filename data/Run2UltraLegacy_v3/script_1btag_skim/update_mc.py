import glob
import os
DATADIR=os.getenv('DATA_DIR')
def write_txtfile(txtpath,filelist):
    f=open(txtpath,'w')
    for this_path in filelist:
        f.write(this_path+"\n")
    f.close()
def MakeSmapleInfo(YEAR,SKIM,ALIAS,FULLNAME):
    #YEAR='2016preVFP'
    #SKIM='SkimTree_SingleLepton_1DeepJetTightWP'
    #PD='SingleElectron'
    SKFLATDIR='/gv0/DATA/SKFlat/Run2UltraLegacy_v3/'

    SKIMDIR=SKFLATDIR+"/"+YEAR+"/MC_"+SKIM+"/"+FULLNAME
    

    
    txtname=SKIM+"_"+ALIAS+".txt"
    #print(txtname)
    txtpath=DATADIR+"/"+YEAR+"/Sample/ForSNU/"+txtname
    #print(txtpath)
    #2018/DATA/EGamma/periodA/220618_055259/0000
    search_prod_date=SKIMDIR+"/*/"

    nprod=len(glob.glob(search_prod_date))
    if nprod>1:
        print("[!] more than one prod dir. please select one of them.")
        print(SKIMDIR)
        return
    elif nprod==0:
        print("[!] no prod dir")
        print(SKIMDIR)
        return
    search_filelist1=SKIMDIR+"/*/*/*.root"
    search_filelist2=SKIMDIR+"/*/*.root"
    this_filelist=glob.glob(search_filelist1) + glob.glob(search_filelist2)
    print(SKIMDIR)
    print('nfiles=',len(this_filelist))
    #print(txtpath)
    write_txtfile(txtpath,this_filelist)
def Run(SKIM):

    #SKIM='SkimTree_SingleLepton_1DeepJetTightWP'
    SAMPLES16={
        'DYJetsToEE_MiNNLO':'DYJetsToEE_M-50_massWgtFix_TuneCP5_13TeV-powhegMiNNLO-pythia8-photos',
        'DYJetsToMuMu_MiNNLO':'DYJetsToMuMu_M-50_TuneCP5_13TeV-powhegMiNNLO-pythia8-photos',
        'DYJetsToTauTau_MiNNLO':'DYJetsToTauTau_M-50_AtLeastOneEorMuDecay_TuneCP5_13TeV-powhegMiNNLO-pythia8-photos',
        'QCD_bEnriched_HT100to200':'QCD_bEnriched_HT100to200_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT200to300':'QCD_bEnriched_HT200to300_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT300to500':'QCD_bEnriched_HT300to500_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT500to700':'QCD_bEnriched_HT500to700_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT700to1000':'QCD_bEnriched_HT700to1000_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT1000to1500':'QCD_bEnriched_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT1500to2000':'QCD_bEnriched_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT2000toInf':'QCD_bEnriched_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8',
        'ZZ_pythia':'ZZ_TuneCP5_13TeV-pythia8',
        'WZ_pythia':'WZ_TuneCP5_13TeV-pythia8',
        'WW_pythia':'WW_TuneCP5_13TeV-pythia8',
        'SingleTop_tch_antitop_Incl':'ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8',
        'SingleTop_tch_top_Incl':'ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8',
        'SingleTop_sch_Lep':'ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8',
        'TTLL_powheg':'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8',
        'TTLJ_powheg':'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8',
        'WJets_MG':'WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8',
        'SingleTop_tW_antitop_NoFullyHad':'ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8',
        'SingleTop_tW_top_NoFullyHad':'ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8',

    }
    SAMPLES1718={
        'DYJetsToEE_MiNNLO':'DYJetsToEE_M-50_massWgtFix_TuneCP5_13TeV-powhegMiNNLO-pythia8-photos',
        'DYJetsToMuMu_MiNNLO':'DYJetsToMuMu_M-50_massWgtFix_TuneCP5_13TeV-powhegMiNNLO-pythia8-photos',
        'DYJetsToTauTau_MiNNLO':'DYJetsToTauTau_M-50_AtLeastOneEorMuDecay_massWgtFix_TuneCP5_13TeV-powhegMiNNLO-pythia8-photos',
        'QCD_bEnriched_HT100to200':'QCD_bEnriched_HT100to200_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT200to300':'QCD_bEnriched_HT200to300_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT300to500':'QCD_bEnriched_HT300to500_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT500to700':'QCD_bEnriched_HT500to700_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT700to1000':'QCD_bEnriched_HT700to1000_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT1000to1500':'QCD_bEnriched_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT1500to2000':'QCD_bEnriched_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8',
        'QCD_bEnriched_HT2000toInf':'QCD_bEnriched_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8',
        'ZZ_pythia':'ZZ_TuneCP5_13TeV-pythia8',
        'WZ_pythia':'WZ_TuneCP5_13TeV-pythia8',
        'WW_pythia':'WW_TuneCP5_13TeV-pythia8',
        'SingleTop_tch_antitop_Incl':'ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8',
        'SingleTop_tch_top_Incl':'ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8',
        'SingleTop_sch_Lep':'ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8',
        'TTLL_powheg':'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8',
        'TTLJ_powheg':'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8',
        'WJets_MG':'WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8',
        'SingleTop_tW_antitop_NoFullyHad':'ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8',
        'SingleTop_tW_top_NoFullyHad':'ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8',
    }
    YEARS={
        '2016preVFP':SAMPLES16,
        '2016postVFP':SAMPLES16,
        '2017':SAMPLES1718,
        '2018':SAMPLES1718,
    }
    
    for YEAR in YEARS:
        for ALIAS in YEARS[YEAR]:
            FULLNAME=YEARS[YEAR][ALIAS]
            MakeSmapleInfo(YEAR,SKIM,ALIAS,FULLNAME)
if __name__ == '__main__' :
    #SKIM='SkimTree_SingleLepton_1DeepJetTightWP'
    
    SKIM='SkimTree_Dilepton_1DeepJetTightWP'
    
    
    Run(SKIM)
