#include "card_stack.h"
#include "card.h"

#include <iostream>

CardStack::CardStack(int size) {
        this->size = size;
}


CardStack CardStack::create_working_pack() {
        CardStack working_pack {13};
        return working_pack;

}

bool CardStack::push(Card &c) {
    if (this->get_size() + 1 > this->size) {
            return false;
    }

    this->cards_pack.push_back(c);
    return true;
}

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

int CardStack::get_size() {
        return this->cards_pack.size();
}

Card * CardStack::pop() {
        if (this->is_empty()) return nullptr;
        Card *c = this->get();
        this->cards_pack.pop_back();
        return c;
}

Card * CardStack::get() {
        if (this->is_empty()) return nullptr;
        return &this->cards_pack.back();
}

Card * CardStack::get(int index) {
        if (this->is_empty() || index < 0  || index > this->get_size() - 1) return nullptr;
        return &this->cards_pack[index];
}

bool CardStack::is_empty() {
        return this->cards_pack.empty();
}

bool CardStack::put(CardStack &stack) {
        if (this->is_empty() || this->get_size() + stack.get_size() > this->size) return false;

        for (Card c : stack.cards_pack) {
                this->push(c);
        }

        return true;
}

CardStack CardStack::pop(Card &c) {
        CardStack card_stack {0};
        bool take_cards = false;

        for (Card card : this->cards_pack) {
                if (card.get_value() < c.get_value() && !card.similar_color_to(c) && card.is_turned_face_up()) {
                        take_cards = true;
                }

                if (take_cards) {
                        card_stack.push(card);
                }
        }

        this->cards_pack.erase (this->cards_pack.end() - card_stack.get_size(), this->cards_pack.end());
        card_stack.size = card_stack.get_size();
        return card_stack;
}

void CardStack::print() {
        std::cout << "[DEBUG] Stack (items: " << this->get_size() << ") contains: " << std::endl;
        for (int i = 0; i < this->get_size(); ++i) {
                std::cout << this->get(i)->to_string() << std::endl;
        }

        std::cout << std::endl;
}
