/**
* @file card_stack.cc
* @brie: Card Stack interface
* @author Dávid Bolvanský xbolva00
*/

#include "card_stack.h"
#include "card.h"

#include <iostream>

/**
* Card Stack constructor
* @param size capacity of card stack
*/
CardStack::CardStack(int size) {
        this->size = size;
}

/**
* Push card to stack
* @param c card to be pushed
* @return true on success, false if no space in current stack
*/
bool CardStack::push(Card &c) {
    if (this->get_size() + 1 > this->size) {
            return false;
    }

    this->cards_pack.push_back(c);
    return true;
}

/**
* Put card to stack
* @param c card to be put
* @return true on success, false if no space in current stack or card cannot be put due to solitaire rules
*/
bool CardStack::put(Card &c) {
        if (this->get_size() + 1 > this->size) {
                return false;
        }

        Card * top_card = this->get();
        if (top_card != NULL) {
                if (c.compare_value(*top_card) != -1) {
                        return false;
                }

                if (c.similar_color_to(*top_card)) {
                        return false;
                }
        } else {
                if (c.get_value() != 13) {
                        return false;
                }
        }


        this->push(c);

        return true;
}

/**
* Get size of stack
* @return size of stack
*/
int CardStack::get_size() {
        return this->cards_pack.size();
}

/**
* Pop card from stack
* @return pointer top card of stack
*/
Card * CardStack::pop() {
        if (this->is_empty()) return nullptr;
        Card *c = this->get();
        this->cards_pack.pop_back();
        return c;
}

/**
* Get top card from stack
* @return pointer top card of stack
*/
Card * CardStack::get() {
        if (this->is_empty()) return nullptr;
        return &this->cards_pack.back();
}

/**
* Get card at index
* @param index index of card
* @return pointer to card at index
*/
Card * CardStack::get(int index) {
        if (this->is_empty() || index < 0  || index > this->get_size() - 1) return nullptr;
        return &this->cards_pack[index];
}

/**
* Check if stack is empty
* @return true if empty, false otherwise
*/
bool CardStack::is_empty() {
        return this->cards_pack.empty();
}

/**
* Put stack to stack
* @param stack second stack of cards
* @return true on success, false if cannot put cards from second stack to current stack
*/
bool CardStack::put(CardStack &stack) {
        if (this->get_size() + stack.get_size() > this->size) return false;

        for (Card c : stack.cards_pack) {
            if (!this->put(c)) {
                return false;
            }
        }

        return true;
}

/**
* Push stack to stack
* @param stack second stack of cards
* @return true on success, false if cannot put cards from second stack to current stack
*/
bool CardStack::push(CardStack &stack) {
        if (this->get_size() + stack.get_size() > this->size) return false;

        for (Card c : stack.cards_pack) {
                this->push(c);
        }

        return true;
}

/**
* Get stack of cards since specific card
* @param c card in stack
* @return stack with cards containg all cards since the specific card
*/
CardStack CardStack::top(Card &c) {
    CardStack card_stack {13};
    bool take_cards = false;
    for (Card card : this->cards_pack) {
            if (card.equals(c)) {
                    take_cards = true;
            }

            if (take_cards) {
                card_stack.push(card);
            }
    }

    card_stack.size = card_stack.get_size();
    return card_stack;
}

/**
* Pop cards since specific card
* @param c card in stack
* @return stack with cards containg all cards since the specific card
*/
CardStack CardStack::pop(Card &c) {
        CardStack card_stack = this->top(c);
        this->cards_pack.erase (this->cards_pack.end() - card_stack.get_size(), this->cards_pack.end());
        return card_stack;
}
