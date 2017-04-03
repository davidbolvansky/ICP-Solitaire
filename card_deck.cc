#include "card_deck.h"
#include "card.h"

#include <iostream>
#include <algorithm>

CardDeck::CardDeck(int size) {
        this->size = size;
        this->color = NO_COLOR;
}

CardDeck::CardDeck(int size, Color color) {
        this->size = size;
        this->color = color;
}

CardDeck CardDeck::create_standard_deck() {
        CardDeck standard_deck {52};
        Card card {Color::CLUBS, 1};

        for (int i = 1; i <= 13; ++i) {
                card = Card(Color::CLUBS,i);
                standard_deck.push(card);
        }
        for (int i = 1; i <= 13; ++i) {
                card = Card(Color::DIAMONDS,i);
                standard_deck.push(card);
        }
        for (int i = 1; i <= 13; ++i) {
                card = Card(Color::HEARTS,i);
                standard_deck.push(card);
        }
        for (int i = 1; i <= 13; ++i) {
                card = Card(Color::SPADES,i);
                standard_deck.push(card);
        }

        return standard_deck;

}


CardDeck CardDeck::create_target_pack(Color color) {
        CardDeck target_pack {13, color};
        return target_pack;

}

void CardDeck::shuffle() {
        std::random_shuffle (this->cards_pack.begin(), this->cards_pack.end() );
}

void CardDeck::swap(CardDeck &deck) {
        this->cards_pack.swap(deck.cards_pack);
}

bool CardDeck::push(Card &c) {
        if (this->get_size() + 1 > this->size) {
                return false;
        }

        this->cards_pack.push_back(c);
        return true;
}

bool CardDeck::put(Card &c) {
        if (this->get_size() + 1 > this->size) {
                return false;
        }

        if (this->color != c.get_color()) {
                return false;
        }

        Card * top_card = this->get();
        if (top_card != NULL) {
                if (c.compare_value(*top_card) != 1) {
                        return false;
                }
        } else {
                if (c.get_value() != 1) {
                        return false;
                }
        }


        this->push(c);
        return true;
}

int CardDeck::get_size() {
        return this->cards_pack.size();
}

Card * CardDeck::pop() {
        if (this->is_empty()) return nullptr;
        Card *c = this->get();
        this->cards_pack.pop_back();
        return c;
}

Card * CardDeck::get() {
        if (this->is_empty()) return nullptr;
        return &this->cards_pack.back();
}

Card * CardDeck::get(int index) {
        if (this->is_empty() || index < 0  || index > this->get_size() - 1) return nullptr;
        return &this->cards_pack[index];
}

bool CardDeck::is_empty() {
        return this->cards_pack.empty();
}

Color CardDeck::get_color() {
        return this->color;
}

void CardDeck::print() {
        std::cout << "[DEBUG] Deck (items: " << this->get_size() << ") contains: " << std::endl;
        for (int i = 0; i < this->get_size(); ++i) {
                std::cout << this->get(i)->to_string() << std::endl;
        }

        std::cout << std::endl;
}
