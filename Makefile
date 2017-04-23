all: clean
	cd src && make

run: all
	./src/hra2017-cli
	#./hra2017


doxygen:
	#mkdir doc
	doxygen src/doxyfile

clean:
	cd src && make clean


pack: clean
	zip xgreso00-xbolva00.zip -r Makefile src doc examples README.txt
