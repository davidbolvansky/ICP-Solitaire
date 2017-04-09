COMPILER=g++
all:
	$(COMPILER) -std=c++11 -c card.cc
	$(COMPILER) -std=c++11 -c card_deck.cc
	$(COMPILER) -std=c++11 -c card_stack.cc
	$(COMPILER) -std=c++11 -c command.cc
	$(COMPILER) -std=c++11 -c game.cc
	$(COMPILER) -std=c++11 -c board.cc
	$(COMPILER) -std=c++11 -c test.cc
	$(COMPILER) -std=c++11 -c hra2017-cli.cc
	$(COMPILER) -std=c++11 test.o card.o card_deck.o card_stack.o command.o game.o board.o -o test
	$(COMPILER) -std=c++11 hra2017-cli.o card.o card_deck.o card_stack.o command.o game.o board.o -o hra2017-cli -lncurses

clean:
	rm -f *.o hra2017-cli test

pack:
	zip icp_solitaire.zip *.cc *.h Makefile
