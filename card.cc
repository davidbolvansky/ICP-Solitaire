
#include <iostream>
#include <string>
#include "card.h"

const char Color_short_texts[CARD_TYPES] = { 'S', 'D', 'H', 'C'};
const char * Color_long_texts[CARD_TYPES] = { "Spades", "Diamonds", "Hearts", "Clubs"};

Card::Card(Color c, int value) {
        this->color = c;
        if (value < 1 || value > 13) {
                throw std::out_of_range ("card value out of range");
        }
        this->value = value;
        this->turned_face_up = false;
}

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
        if (this->is_turned_face_up()) {
                card_text += " turned up";
        } else {
                card_text += " turned down";
        }
        return card_text;
}

Color Card::get_color() {
        return this->color;
}

bool Card::similar_color_to(Card &c) {
        if (this->get_color() == SPADES && c.get_color() == CLUBS || this->get_color() == CLUBS && c.get_color() == SPADES) {
                return true;
        } else if (this->get_color() == DIAMONDS && c.get_color() == HEARTS || this->get_color() == HEARTS && c.get_color() == DIAMONDS) {
                return true;
        }

        return false;

}

int Card::get_value() {
        return this->value;
}

int Card::compare_value(Card &c) {
        return this->get_value() - c.get_value();
}

bool Card::is_turned_face_up() {
        return this->turned_face_up;
}

bool Card::turn_face_up() {
    if (this->is_turned_face_up()) {
        return false;
    } else {
        this->turned_face_up = true;
        return true;
    }
}

bool Card::turn_face_down() {
    if (!this->is_turned_face_up()) {
        return false;
    } else {
        this->turned_face_up = false;
        return true;
    }
}

bool Card::equals(Card &c) {
        return (this->get_color() == c.get_color() && this->get_value() == c.get_value());
}
