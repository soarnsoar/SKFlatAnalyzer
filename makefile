all: DataFormats Analyzers Archive

DataFormats::
	(cd DataFormats; make)
	(mvexist.sh DataFormats/src/DataFormats_Dict_rdict.pcm lib/)

Analyzers::
	(cd Analyzers; make)
	(mvexist.sh Analyzers/src/Analyzers_Dict_rdict.pcm lib/)

Archive::
	(tar -zcf lib/DataFormats.tar.gz DataFormats)
	(tar -zcf lib/Analyzers.tar.gz Analyzers)

clean::
	(cd DataFormats; make clean)
	(cd Analyzers; make clean)

distclean::
	(cd DataFormats; make distclean)
	(cd Analyzers; make distclean)
