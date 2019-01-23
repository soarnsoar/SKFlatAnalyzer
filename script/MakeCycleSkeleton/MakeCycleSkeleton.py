import os

cyclename = "NewAnalyzer"

out_h = open(cyclename+'.h','w')
print>>out_h,'''#ifndef {0}_h
#define {0}_h

#include "AnalyzerCore.h"

class {0} : public AnalyzerCore {{

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  {0}();
  ~{0}();

}};



#endif
'''.format(cyclename)
out_h.close()

out_c = open(cyclename+'.C','w')
print>>out_c,'''#include "{0}.h"

void {0}::initializeAnalyzer(){{

}}

void {0}::executeEvent(){{


  AnalyzerParameter param;

  executeEventFromParameter(param);

}}

void {0}::executeEventFromParameter(AnalyzerParameter param){{

  if(!PassMETFilter()) return;

  Event ev = GetEvent();

}}

{0}::{0}(){{

}}

{0}::~{0}(){{

}}

'''.format(cyclename)
out_c.close()

print 'mv '+cyclename+'.h $SKFlat_WD/Analyzers/include/'
print 'mv '+cyclename+'.C $SKFlat_WD/Analyzers/src/'

out_run = open('run_'+cyclename+'.C','w')
print>>out_run,'''R__LOAD_LIBRARY(libPhysics.so)
R__LOAD_LIBRARY(libTree.so)
R__LOAD_LIBRARY(libHist.so)
R__LOAD_LIBRARY(libDataFormats.so)
R__LOAD_LIBRARY(libAnalyzers.so)

void run_{0}(){{

  {0} m;

  TString outputdir = getenv("OUTPUTDIR");

  m.SetTreeName("recoTree/SKFlat");

  m.MaxEvent = 10;

/*
  //==== For Data Run
  m.IsDATA = true;
  m.DataStream = "SingleMuon";
*/

  //==== For MC Run
/*
  m.MCSample = "DYJets";
  m.IsDATA = false;
  m.AddFile("root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/jskim/SKFlat/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/SKFlat_v946p1_3/180528_224136/0000/SKFlatNtuple_1.root");
*/

  m.SetOutfilePath("hists.root");

  m.Init();

  m.initializeAnalyzer();
  m.Loop();

  m.WriteHist();

}}
'''.format(cyclename)
out_run.close()

print '## For Single job test ##'
print 'mv run_'+cyclename+'.C ../../'
