all:
	(cd lib; make all; make install)
	(cd daemon1; make all)

install:
	(cd daemon1; make install)

uninstall:
	(cd lib; make uninstall)
	(cd daemon1; make uninstall)

clean:
	(cd lib; make clean)
	(cd daemon1; make clean)