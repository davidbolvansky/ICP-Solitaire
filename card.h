#ifndef CARD_H
#define CARD_H

#include <string>

const int CARD_TYPES = 4;
enum Color {SPADES, DIAMONDS, HEARTS, CLUBS};

class Card {
    Color color;
    int value;
    bool turned_face_up;
    public:
    Card(Color c, int value);
    std::string to_string();
    Color get_color();
    bool similar_color_to(Card &c);
    int get_value();
    int compare_value(Card &c);
    bool is_turned_face_up();
    bool turn_face_up();
    bool equals(Card &c);
};


#endif // CARD_H