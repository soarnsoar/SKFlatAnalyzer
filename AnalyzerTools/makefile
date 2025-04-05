LIBRARY = AnalyzerTools
OBJDIR = obj
DEPDIR = $(OBJDIR)/dep
SRCDIR = src
INCDIR = include
ADDITIONAL_ROOTMAPLIBRARY= -rml libDataFormats.so -rml libHist.so

include $(SKFlat_WD)/makefile.common

INCLUDES += -I$(SKFlat_WD)/DataFormats/include/

#INCLUDES += -I/cvmfs/cms.cern.ch/el9_amd64_gcc12/lcg/root/6.32.11-a1d23f0c91e1aeff81bd016882a5fb71/include/
##For numpy path
INCLUDES += -I/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/py2-numpy/1.16.6/lib/python2.7/site-packages/numpy/core/include/
#INCLUDES += -I/cvmfs/cms.cern.ch/el9_amd64_gcc12/lcg/root/6.32.11-a1d23f0c91e1aeff81bd016882a5fb71/include/

#INCLUDES += -I/cvmfs/cms.cern.ch/slc6_amd64_gcc630/external/lhapdf/6.2.1-fmblme/include/


#LIBRARY_DIRS += -L/cvmfs/cms.cern.ch/el9_amd64_gcc12/lcg/root/6.32.11-a1d23f0c91e1aeff81bd016882a5fb71/lib/
#LIBRARIES += -lXMLIO

LIBRARY_DIRS += -L$(root-config --libdir)
LIBRARIES += -lXMLIO
