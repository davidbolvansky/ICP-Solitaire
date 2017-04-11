#include <iostream>
#include "card.h"
#include "card_deck.h"
#include "card_stack.h"
#include "game.h"
#include "board.h"
#include <unistd.h> // DEBUG timer

int main2()
{
	Card f{SPADES, 9};
    Card b{SPADES, 1};
    std::cout << "hello world!\n" << f.to_string() << " " << f.compare_value(b) << std::endl;

	CardDeck d = CardDeck::create_standard_deck();
	//d.print();
	CardStack w = CardStack::create_working_pack();
	Card s13 = Card(SPADES, 13);
	Card d12 = Card(DIAMONDS, 12);
	Card s11 = Card(SPADES, 11);
	Card d10 = Card(DIAMONDS, 10);
	w.put(s13);
	w.put(d12);
	w.put(s11);
	w.put(d10);

	/*CardStack a = CardStack::create_working_pack();
	a.put(Card(SPADES, 9));
	a.put(Card(DIAMONDS, 8));
	w.print();
	a.print();*/

	std::cout << "w: \n"; w.print();

	CardStack s = w.pop(d12);

	CardStack r = CardStack::create_working_pack();
	r.put(s13);
	r.put(s);

	std::cout << "poped: \n"; s.print();
	std::cout << "w2: \n";w.print();

	std::cout << "put stack: \n"; r.print();


	return 0;
}

int main(void) {
	/*Game a;
	a.start();
	sleep(2);
	a.pause();
	sleep(3);
	a.resume();
	sleep(4);*/

	Board main{};
	Game * a = main.create_new_game();
	a->start();
	a->load("file.txt");
	//std::cout << a->get_total_time_in_seconds().count() << "\n";
	std::cout <<"Pocet hier: " <<  main.get_games_count()  << std::endl;

	return 0;
}
