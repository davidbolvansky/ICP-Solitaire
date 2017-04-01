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
    void push(Card &c);
    bool put(Card &c);
    bool put(CardStack &stack);
    int get_size();
    Card* get();
    Card* get(int index);
    Card* pop();
    CardStack pop(Card &c);
    bool is_empty();
    void print();

    static CardStack create_working_pack();
};

#endif // CARD_STACK_H
