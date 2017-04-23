all: clean
	cd src && make && mv hra2017-cli ../hra2017-cli

run: all
	./hra2017-cli
	#./hra2017


doxygen:
	#mkdir doc
	doxygen src/doxyfile

clean:
	rm -f hra2017-cli hra2017
	cd src && make clean


pack: clean
	zip xgreso00-xbolva00.zip -r Makefile src doc examples README.txt
