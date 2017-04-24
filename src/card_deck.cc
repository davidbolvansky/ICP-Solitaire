/**
* @file: card_deck.cc
* @brief: Card Deck implementation
* @author: Dávid Bolvanský xbolva00
*/

#include "card_deck.h"
#include "card.h"

#include <iostream>
#include <algorithm>

/*
* Card Deck constructor
* @size: capacity of card deck
*/
CardDeck::CardDeck(int size) {
        this->size = size;
        this->color = NO_COLOR;
}

/**
* Create standard solitaire deck
* @return standard deck
*/
CardDeck CardDeck::create_standard_deck() {
        CardDeck standard_deck {52};
        for (int i = 1; i <= 13; ++i) {
                Card card = Card(Color::CLUBS,i);
                standard_deck.push(card);
        }
        for (int i = 1; i <= 13; ++i) {
                Card card = Card(Color::DIAMONDS,i);
                standard_deck.push(card);
        }
        for (int i = 1; i <= 13; ++i) {
                Card card = Card(Color::HEARTS,i);
                standard_deck.push(card);
        }
        for (int i = 1; i <= 13; ++i) {
                Card card = Card(Color::SPADES,i);
                standard_deck.push(card);
        }

        return standard_deck;

}

/**
* Shuffle deck
*/
void CardDeck::shuffle() {
        std::srand(time(NULL));
        std::random_shuffle (this->cards_pack.begin(), this->cards_pack.end());
}

/**
* Swap two decks
* @deck: second deck for swapping
*/
void CardDeck::swap(CardDeck &deck) {
        this->cards_pack.swap(deck.cards_pack);
}

/**
* Reverse deck
*/
void CardDeck::reverse() {
        std::reverse(this->cards_pack.begin(), this->cards_pack.end());
}

/**
* Push card to deck
* @c: card to be pushed
* @return: true on success, false if no space in current deck
*/
bool CardDeck::push(Card &c) {
        if (this->get_size() + 1 > this->size) {
                return false;
        }

        this->cards_pack.push_back(c);
        return true;
}

/**
* Put card to deck
* @c: card to be put
* @return: true on success, false if no space in current deck or card cannot be put due to solitaire rules
*/
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

/**
* Get size of deck
* @return: size of deck
*/
int CardDeck::get_size() {
        return this->cards_pack.size();
}

/**
* Pop card from deck
* @return: pointer to top card of deck
*/
Card * CardDeck::pop() {
        if (this->is_empty()) return nullptr;
        Card *c = this->get();
        this->cards_pack.pop_back();
        return c;
}

/**
* Get top card of deck
* @return: pointer to top card of deck
*/
Card * CardDeck::get() {
        if (this->is_empty()) return nullptr;
        return &this->cards_pack.back();
}

/**
* Get card at index
* @index: index of card
* @return: pointer to card at index
*/
Card * CardDeck::get(int index) {
        if (this->is_empty() || index < 0  || index > this->get_size() - 1) return nullptr;
        return &this->cards_pack[index];
}

/**
* Check if deck is empty
* @return: true if empty, false otherwise
*/
bool CardDeck::is_empty() {
        return this->cards_pack.empty();
}

/**
* Get color of deck
* @return: color of deck
*/
Color CardDeck::get_color() {
        return this->color;
}

/**
* Set color of deck
* @c: color
*/
void CardDeck::set_color(Color c) {
        this->color = c;
}
