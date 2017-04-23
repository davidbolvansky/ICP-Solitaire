all: clean
	cd src && make && mv hra2017-cli ../hra2017-cli && mv hra2017 ../hra2017

run: all
	./hra2017
	./hra2017-cli

doxygen:
	#mkdir doc
	#doxygen src/doxyfile

clean:
	rm -f hra2017-cli hra2017
	cd src && make clean


pack: clean
	zip xgreso00-xbolva00.zip -r Makefile src doc examples README.txt
