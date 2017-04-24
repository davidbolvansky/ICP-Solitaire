/**
* @file: card.cc
* @brief: Card implementation
* @author: Dávid Bolvanský xbolva00
*/

#include <iostream>
#include <string>
#include "card.h"

// Short names of card colors
const char Color_short_texts[CARD_TYPES] = { 'S', 'D', 'H', 'C'};
// Long names of card colors
const char * Color_long_texts[CARD_TYPES] = { "Spades", "Diamonds", "Hearts", "Clubs"};

/**
* Card constructor
* @param color color of card
* @param value value of card
* @param turned_face_up whether card is turned face up
*/
Card::Card(Color color, int value, bool turned_face_up) {
        this->color = color;
        if (value < 1 || value > 13) {
                throw std::out_of_range ("card value out of range");
        }
        this->value = value;
        this->turned_face_up = turned_face_up;
}

/**
* Card constructor
* @param color color of card
* @param value value of card
*/
Card::Card(Color color, int value ): Card(color, value, false) {}

/**
* Get name of card
* @return name of card
*/
std::string Card::to_string() {
        std::string card_text;
        switch (this->value) {
        case 13:
                card_text = "K";
                break;
        case 12:
                card_text = "Q";
                break;
        case 11:
                card_text = "J";
                break;
        case 1:
                card_text = "A";
                break;
        default:
                card_text = std::to_string(this->value);
                break;
        }

        card_text = card_text + "(" + Color_short_texts[this->color] + ")";
        return card_text;
}

/**
* Get color of card
* @return color of card
*/
Color Card::get_color() {
        return this->color;
}

/**
* Check if card has similar color to other card
* @return true if similar, false otherwise
*/
bool Card::similar_color_to(Card &c) {
        if ((this->get_color() == SPADES && c.get_color() == CLUBS) || (this->get_color() == CLUBS && c.get_color() == SPADES)) {
                return true;
        } else if ((this->get_color() == DIAMONDS && c.get_color() == HEARTS) || (this->get_color() == HEARTS && c.get_color() == DIAMONDS)) {
                return true;
        } else if (this->get_color() == c.get_color()) {
            return true;
        }

        return false;

}

/**
* Check if card has same color as other card
* @return true if same, false otherwise
*/
bool Card::is_same_color(Color c) {
    return this->get_color() == c;
}

/**
* Get value of card
* @return value of card
*/
int Card::get_value() {
        return this->value;
}

/**
* Compare values of two cards
* @return difference of two cards (value of first card - value of second card)
*/
int Card::compare_value(Card &c) {
        return this->get_value() - c.get_value();
}

/**
* Check if card is turned face up
* @return true if card is turned face up, false otherwise
*/
bool Card::is_turned_face_up() {
        return this->turned_face_up;
}

/**
* Turn card face up
* @return true if card was turned face up, false otherwise
*/
bool Card::turn_face_up() {
    if (this->is_turned_face_up()) {
        return false;
    } else {
        this->turned_face_up = true;
        return true;
    }
}

/**
* Turn card face down
* @return true if card was turned face down, false otherwise
*/
bool Card::turn_face_down() {
    if (!this->is_turned_face_up()) {
        return false;
    } else {
        this->turned_face_up = false;
        return true;
    }
}

/**
* Check if two cards are same
* @return true if same, false otherwise
*/
bool Card::equals(Card &c) {
        return (this->get_color() == c.get_color() && this->get_value() == c.get_value());
}
