/**
* @file card_stack.h
* @brief Card Stack interface
* @author Dávid Bolvanský xbolva00
*/

#ifndef CARD_STACK_H
#define CARD_STACK_H

#include <vector>
#include "card.h"

class CardStack {
    int size;
    Color color;
    std::vector<Card> cards_pack;
    public:
    CardStack(int size);
    bool push(Card &c);
    bool push(CardStack &stack);
    bool put(Card &c);
    bool put(CardStack &stack);
    int get_size();
    Card* get();
    Card* get(int index);
    Card* pop();
    CardStack top(Card &c);
    CardStack pop(Card &c);
    bool is_empty();
};

#endif // CARD_STACK_H
