#include "move.h"

Move::Move(Move move) {
    this->move = move;
}

Move::Move(Move move, int src_index, int dest_index, int card_index) : Move(move) {
    this->src_index = src_index;
    this->dest_index = dest_index;
    this->card_index = card_index;
}

Move Move::get_move() {
    return this->move;
}
int Move::get_source_index() {
    return this->src_index;
}
int Move::get_destination_index() {
    return this->dest_index;
}
int Move::get_card_index() {
    return this->card_index;
}
