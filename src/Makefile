# Makefile for ICP project 2016/2017 - Solitaire
# Authors: Dávid Bolvanský xbolva00
#		   Katarína Grešová xgreso00

COMPILER=g++
QMAKE=qmake

ifneq ($(wildcard /home/xbolva00/Qt/5.8/gcc_64/bin/qmake),"")
	QMAKE=/home/xbolva00/Qt/5.8/gcc_64/bin/qmake
else ifneq ($(wildcard /usr/local/share/Qt-5.5.1/5.5/gcc_64/bin/qmake),"")
	QMAKE=/usr/local/share/Qt-5.5.1/5.5/gcc_64/bin/qmake
endif

all:
	$(COMPILER) -std=c++11 -c card.cc
	$(COMPILER) -std=c++11 -c card_deck.cc
	$(COMPILER) -std=c++11 -c card_stack.cc
	$(COMPILER) -std=c++11 -c command.cc
	$(COMPILER) -std=c++11 -c game.cc
	$(COMPILER) -std=c++11 -c board.cc
	$(COMPILER) -std=c++11 -c move.cc
	$(COMPILER) -std=c++11 -c hra2017-cli.cc
	$(COMPILER) -std=c++11 hra2017-cli.o card.o card_deck.o card_stack.o command.o game.o board.o move.o -o hra2017-cli -lncurses
	$(QMAKE) solitaire.pro -o qtsolitaire.mk
	make -f qtsolitaire.mk
	rm -f qtsolitaire.mk

clean:
	rm -f *.o hra2017 hra2017-cli qtsolitaire.mk moc*
