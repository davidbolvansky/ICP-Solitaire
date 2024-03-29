/**
* @file card.h
* @brief Card interface
* @author Dávid Bolvanský xbolva00
*/

#ifndef CARD_H
#define CARD_H

#include <string>

const int CARD_TYPES = 4; /** < Types of cards */
enum Color {NO_COLOR = -1, SPADES, DIAMONDS, HEARTS, CLUBS}; /**< Colors of cards */

class Card {
    Color color;
    int value;
    bool turned_face_up;
    public:
    Card(Color c, int value, bool turned_face_up);
    Card(Color c, int value);
    std::string to_string();
    Color get_color();
    bool similar_color_to(Card &c);
    bool is_same_color(Color c);
    int get_value();
    int compare_value(Card &c);
    bool is_turned_face_up();
    bool turn_face_up();
    bool turn_face_down();
    bool equals(Card &c);
};


#endif // CARD_H
