all: DataFormats Analyzers

DataFormats::
	(cd DataFormats; make)
	(mv DataFormats/src/DataFormats_Dict_rdict.pcm lib/ | true)

Analyzers::
	(cd Analyzers; make)
	(mv Analyzers/src/Analyzers_Dict_rdict.pcm lib/| true)

clean::
	(cd DataFormats; make clean)
	(cd Analyzers; make clean)

distclean::
	(cd DataFormats; make distclean)
	(cd Analyzers; make distclean)
