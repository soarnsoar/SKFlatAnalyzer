import os,ROOT

sample = 'TTLL_powheg'

SKFlat_WD = os.environ['SKFlat_WD']
SKFlatV = os.environ['SKFlatV']
DATA_DIR = os.environ['DATA_DIR']
SKFlatOutputDir = os.environ['SKFlatOutputDir']

Years = [
"2016",
"2017",
"2018",
]

Taggers = [
'DeepCSV',
'DeepJet',
'CSVv2',
]

WPs = [
'Loose',
'Medium',
'Tight',
]

Flavours = [
'B',
'C',
'Light',
]

for Year in Years:

  f = ROOT.TFile(SKFlatOutputDir+SKFlatV+'/MeasureJetTaggingEfficiency/'+Year+'/MeasureJetTaggingEfficiency_'+sample+'.root')

  out = open('BTagEfficienciesTTbar'+Year.replace('20','')+'.C','w')

  for Flavour in Flavours:

    h_Den = f.Get('Jet_'+Year+'_eff_'+Flavour+'_denom')

    print>>out,'''float BTagSFUtil::TagEfficiency{1}_{0}(float JetPt, float JetEta) {{'''.format(Year,Flavour)

    for Tagger in Taggers:

      for WP in WPs:

        print>>out,'''  if(taggerName=="{0}" && operatingPoint=="{1}") {{'''.format(Tagger,WP)

        h_Eff = f.Get('Jet_'+Year+'_'+Tagger+'_'+WP+'_eff_'+Flavour+'_num')
        if not h_Eff:
          out.write('  }\n')
          continue
        h_Eff.Divide(h_Den)

        for iy in range(0,h_Eff.GetYaxis().GetNbins()):

          y_l = h_Eff.GetYaxis().GetBinLowEdge(iy+1)
          y_r = h_Eff.GetYaxis().GetBinUpEdge(iy+1)

          print>>out,'''    if (JetPt > {0} && JetPt <= {1}){{'''.format(y_l,y_r)

          for ix in range(0,h_Eff.GetXaxis().GetNbins()):

            x_l = h_Eff.GetXaxis().GetBinLowEdge(ix+1)
            x_r = h_Eff.GetXaxis().GetBinUpEdge(ix+1)

            this_eff_str = '%.5f'%(h_Eff.GetBinContent(ix+1,iy+1))

            print>>out,'''      if (fabs(JetEta) > {0} && fabs(JetEta) <= {1}) return {2};'''.format(x_l,x_r,this_eff_str)

            #print '%s\t%s\t%s\t\t[%f,%f]\t[%f,%f]'%(Tagger,Flavour,WP,x_l,x_r,y_l,y_r)
          out.write('    }\n') ## End of this pt range

        out.write('  }\n') ## end of this working point

    print>>out,'''  cout << "[BTagSFUtil::TagEfficiency{1}_{0}] No eff found for taggerName = " << taggerName << ", operatingPoint = " << operatingPoint << endl;'''.format(Year,Flavour)
    out.write('  return 1.;\n')
    out.write('}\n') ## end of this flavour

  out.close()
  print 'cp '+'BTagEfficienciesTTbar'+Year.replace('20','')+'.C'+' '+SKFlat_WD+'/AnalyzerTools/src/BTagEfficiencies/'
