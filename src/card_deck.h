/**
* @file: card_deck.h
* @brief: Card Deck interface
* @author: Dávid Bolvanský xbolva00
*/

#ifndef CARD_DECK_H
#define CARD_DECK_H

#include <vector>
#include "card.h"

class CardDeck {
    int size;
    Color color;
    std::vector<Card> cards_pack;
    public:
    CardDeck(int size);
    void shuffle();
    void swap(CardDeck &deck);
    void reverse();
    bool push(Card &c);
    bool put(Card &c);
    int get_size();
    Card* get();
    Card* get(int index);
    Card* pop();
    bool is_empty();
    Color get_color();
    void set_color(Color c);

    static CardDeck create_standard_deck();
};

#endif // CARD_DECK_H
