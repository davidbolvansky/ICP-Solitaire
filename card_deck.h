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
    CardDeck(int size, Color color);
    void shuffle();
    void swap(CardDeck &deck);
    bool push(Card &c);
    bool put(Card &c);
    int get_size();
    Card* get();
    Card* get(int index);
    Card* pop();
    bool is_empty();
    void print();

    static CardDeck create_standard_deck();
    static CardDeck create_target_pack(Color color);
};

#endif // CARD_DECK_H
